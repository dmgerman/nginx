begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_core.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_decl_stmt
specifier|extern
name|int
name|ngx_eventfd
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|aio_context_t
name|ngx_aio_ctx
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|void
name|ngx_file_aio_event_handler
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|int
DECL|function|io_submit (aio_context_t ctx,long n,struct iocb ** paiocb)
name|io_submit
parameter_list|(
name|aio_context_t
name|ctx
parameter_list|,
name|long
name|n
parameter_list|,
name|struct
name|iocb
modifier|*
modifier|*
name|paiocb
parameter_list|)
block|{
return|return
name|syscall
argument_list|(
name|SYS_io_submit
argument_list|,
name|ctx
argument_list|,
name|n
argument_list|,
name|paiocb
argument_list|)
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_file_aio_init (ngx_file_t * file,ngx_pool_t * pool)
name|ngx_file_aio_init
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_event_aio_t
modifier|*
name|aio
decl_stmt|;
name|aio
operator|=
name|ngx_pcalloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_event_aio_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|aio
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|aio
operator|->
name|file
operator|=
name|file
expr_stmt|;
name|aio
operator|->
name|fd
operator|=
name|file
operator|->
name|fd
expr_stmt|;
name|aio
operator|->
name|event
operator|.
name|data
operator|=
name|aio
expr_stmt|;
name|aio
operator|->
name|event
operator|.
name|ready
operator|=
literal|1
expr_stmt|;
name|aio
operator|->
name|event
operator|.
name|log
operator|=
name|file
operator|->
name|log
expr_stmt|;
name|file
operator|->
name|aio
operator|=
name|aio
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ssize_t
DECL|function|ngx_file_aio_read (ngx_file_t * file,u_char * buf,size_t size,off_t offset,ngx_pool_t * pool)
name|ngx_file_aio_read
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|,
name|off_t
name|offset
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_err_t
name|err
decl_stmt|;
name|struct
name|iocb
modifier|*
name|piocb
index|[
literal|1
index|]
decl_stmt|;
name|ngx_event_t
modifier|*
name|ev
decl_stmt|;
name|ngx_event_aio_t
modifier|*
name|aio
decl_stmt|;
if|if
condition|(
operator|!
name|ngx_file_aio
condition|)
block|{
return|return
name|ngx_read_file
argument_list|(
name|file
argument_list|,
name|buf
argument_list|,
name|size
argument_list|,
name|offset
argument_list|)
return|;
block|}
if|if
condition|(
name|file
operator|->
name|aio
operator|==
name|NULL
operator|&&
name|ngx_file_aio_init
argument_list|(
name|file
argument_list|,
name|pool
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|aio
operator|=
name|file
operator|->
name|aio
expr_stmt|;
name|ev
operator|=
operator|&
name|aio
operator|->
name|event
expr_stmt|;
if|if
condition|(
operator|!
name|ev
operator|->
name|ready
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|file
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"second aio post for \"%V\""
argument_list|,
operator|&
name|file
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|ngx_log_debug4
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|file
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"aio complete:%d @%O:%uz %V"
argument_list|,
name|ev
operator|->
name|complete
argument_list|,
name|offset
argument_list|,
name|size
argument_list|,
operator|&
name|file
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|ev
operator|->
name|complete
condition|)
block|{
name|ev
operator|->
name|active
operator|=
literal|0
expr_stmt|;
name|ev
operator|->
name|complete
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|aio
operator|->
name|res
operator|>=
literal|0
condition|)
block|{
name|ngx_set_errno
argument_list|(
literal|0
argument_list|)
expr_stmt|;
return|return
name|aio
operator|->
name|res
return|;
block|}
name|ngx_set_errno
argument_list|(
operator|-
name|aio
operator|->
name|res
argument_list|)
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"aio read \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_memzero
argument_list|(
operator|&
name|aio
operator|->
name|aiocb
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|iocb
argument_list|)
argument_list|)
expr_stmt|;
name|aio
operator|->
name|aiocb
operator|.
name|aio_data
operator|=
operator|(
name|uint64_t
operator|)
operator|(
name|uintptr_t
operator|)
name|ev
expr_stmt|;
name|aio
operator|->
name|aiocb
operator|.
name|aio_lio_opcode
operator|=
name|IOCB_CMD_PREAD
expr_stmt|;
name|aio
operator|->
name|aiocb
operator|.
name|aio_fildes
operator|=
name|file
operator|->
name|fd
expr_stmt|;
name|aio
operator|->
name|aiocb
operator|.
name|aio_buf
operator|=
operator|(
name|uint64_t
operator|)
operator|(
name|uintptr_t
operator|)
name|buf
expr_stmt|;
name|aio
operator|->
name|aiocb
operator|.
name|aio_nbytes
operator|=
name|size
expr_stmt|;
name|aio
operator|->
name|aiocb
operator|.
name|aio_offset
operator|=
name|offset
expr_stmt|;
name|aio
operator|->
name|aiocb
operator|.
name|aio_flags
operator|=
name|IOCB_FLAG_RESFD
expr_stmt|;
name|aio
operator|->
name|aiocb
operator|.
name|aio_resfd
operator|=
name|ngx_eventfd
expr_stmt|;
name|ev
operator|->
name|handler
operator|=
name|ngx_file_aio_event_handler
expr_stmt|;
name|piocb
index|[
literal|0
index|]
operator|=
operator|&
name|aio
operator|->
name|aiocb
expr_stmt|;
if|if
condition|(
name|io_submit
argument_list|(
name|ngx_aio_ctx
argument_list|,
literal|1
argument_list|,
name|piocb
argument_list|)
operator|==
literal|1
condition|)
block|{
name|ev
operator|->
name|active
operator|=
literal|1
expr_stmt|;
name|ev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
name|ev
operator|->
name|complete
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_EAGAIN
condition|)
block|{
return|return
name|ngx_read_file
argument_list|(
name|file
argument_list|,
name|buf
argument_list|,
name|size
argument_list|,
name|offset
argument_list|)
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"io_submit(\"%V\") failed"
argument_list|,
operator|&
name|file
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_ENOSYS
condition|)
block|{
name|ngx_file_aio
operator|=
literal|0
expr_stmt|;
return|return
name|ngx_read_file
argument_list|(
name|file
argument_list|,
name|buf
argument_list|,
name|size
argument_list|,
name|offset
argument_list|)
return|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_file_aio_event_handler (ngx_event_t * ev)
name|ngx_file_aio_event_handler
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|ngx_event_aio_t
modifier|*
name|aio
decl_stmt|;
name|aio
operator|=
name|ev
operator|->
name|data
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"aio event handler fd:%d %V"
argument_list|,
name|aio
operator|->
name|fd
argument_list|,
operator|&
name|aio
operator|->
name|file
operator|->
name|name
argument_list|)
expr_stmt|;
name|aio
operator|->
name|handler
argument_list|(
name|ev
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

