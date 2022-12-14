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

begin_function_decl
specifier|static
name|ssize_t
name|ngx_linux_sendfile
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_buf_t
modifier|*
name|file
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_thread_pool.h>
end_include

begin_if
if|#
directive|if
operator|!
operator|(
name|NGX_HAVE_SENDFILE64
operator|)
end_if

begin_error
error|#
directive|error
error|sendfile64() is required!
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|ssize_t
name|ngx_linux_sendfile_thread
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_buf_t
modifier|*
name|file
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_linux_sendfile_thread_handler
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * On Linux up to 2.4.21 sendfile() (syscall #187) works with 32-bit  * offsets only, and the including<sys/sendfile.h> breaks the compiling,  * if off_t is 64 bit wide.  So we use own sendfile() definition, where offset  * parameter is int32_t, and use sendfile() for the file parts below 2G only,  * see src/os/unix/ngx_linux_config.h  *  * Linux 2.4.21 has the new sendfile64() syscall #239.  *  * On Linux up to 2.6.16 sendfile() does not allow to pass the count parameter  * more than 2G-1 bytes even on 64-bit platforms: it returns EINVAL,  * so we limit it to 2G-1 bytes.  *  * On Linux 2.6.16 and later, sendfile() silently limits the count parameter  * to 2G minus the page size, even on 64-bit platforms.  */
end_comment

begin_define
DECL|macro|NGX_SENDFILE_MAXSIZE
define|#
directive|define
name|NGX_SENDFILE_MAXSIZE
value|2147483647L
end_define

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_linux_sendfile_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_linux_sendfile_chain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|,
name|off_t
name|limit
parameter_list|)
block|{
name|int
name|tcp_nodelay
decl_stmt|;
name|off_t
name|send
decl_stmt|,
name|prev_send
decl_stmt|;
name|size_t
name|file_size
decl_stmt|,
name|sent
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_buf_t
modifier|*
name|file
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|ngx_iovec_t
name|header
decl_stmt|;
name|struct
name|iovec
name|headers
index|[
name|NGX_IOVS_PREALLOCATE
index|]
decl_stmt|;
name|wev
operator|=
name|c
operator|->
name|write
expr_stmt|;
if|if
condition|(
operator|!
name|wev
operator|->
name|ready
condition|)
block|{
return|return
name|in
return|;
block|}
comment|/* the maximum limit size is 2G-1 - the page size */
if|if
condition|(
name|limit
operator|==
literal|0
operator|||
name|limit
operator|>
operator|(
name|off_t
operator|)
operator|(
name|NGX_SENDFILE_MAXSIZE
operator|-
name|ngx_pagesize
operator|)
condition|)
block|{
name|limit
operator|=
name|NGX_SENDFILE_MAXSIZE
operator|-
name|ngx_pagesize
expr_stmt|;
block|}
name|send
operator|=
literal|0
expr_stmt|;
name|header
operator|.
name|iovs
operator|=
name|headers
expr_stmt|;
name|header
operator|.
name|nalloc
operator|=
name|NGX_IOVS_PREALLOCATE
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|prev_send
operator|=
name|send
expr_stmt|;
comment|/* create the iovec and coalesce the neighbouring bufs */
name|cl
operator|=
name|ngx_output_chain_to_iovec
argument_list|(
operator|&
name|header
argument_list|,
name|in
argument_list|,
name|limit
operator|-
name|send
argument_list|,
name|c
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|==
name|NGX_CHAIN_ERROR
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|send
operator|+=
name|header
operator|.
name|size
expr_stmt|;
comment|/* set TCP_CORK if there is a header before a file */
if|if
condition|(
name|c
operator|->
name|tcp_nopush
operator|==
name|NGX_TCP_NOPUSH_UNSET
operator|&&
name|header
operator|.
name|count
operator|!=
literal|0
operator|&&
name|cl
operator|&&
name|cl
operator|->
name|buf
operator|->
name|in_file
condition|)
block|{
comment|/* the TCP_CORK and TCP_NODELAY are mutually exclusive */
if|if
condition|(
name|c
operator|->
name|tcp_nodelay
operator|==
name|NGX_TCP_NODELAY_SET
condition|)
block|{
name|tcp_nodelay
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|setsockopt
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|IPPROTO_TCP
argument_list|,
name|TCP_NODELAY
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|tcp_nodelay
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
comment|/*                      * there is a tiny chance to be interrupted, however,                      * we continue a processing with the TCP_NODELAY                      * and without the TCP_CORK                      */
if|if
condition|(
name|err
operator|!=
name|NGX_EINTR
condition|)
block|{
name|wev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|err
argument_list|,
literal|"setsockopt(TCP_NODELAY) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
block|}
else|else
block|{
name|c
operator|->
name|tcp_nodelay
operator|=
name|NGX_TCP_NODELAY_UNSET
expr_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no tcp_nodelay"
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|c
operator|->
name|tcp_nodelay
operator|==
name|NGX_TCP_NODELAY_UNSET
condition|)
block|{
if|if
condition|(
name|ngx_tcp_nopush
argument_list|(
name|c
operator|->
name|fd
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
comment|/*                      * there is a tiny chance to be interrupted, however,                      * we continue a processing without the TCP_CORK                      */
if|if
condition|(
name|err
operator|!=
name|NGX_EINTR
condition|)
block|{
name|wev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|err
argument_list|,
name|ngx_tcp_nopush_n
literal|" failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
block|}
else|else
block|{
name|c
operator|->
name|tcp_nopush
operator|=
name|NGX_TCP_NOPUSH_SET
expr_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"tcp_nopush"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/* get the file buf */
if|if
condition|(
name|header
operator|.
name|count
operator|==
literal|0
operator|&&
name|cl
operator|&&
name|cl
operator|->
name|buf
operator|->
name|in_file
operator|&&
name|send
operator|<
name|limit
condition|)
block|{
name|file
operator|=
name|cl
operator|->
name|buf
expr_stmt|;
comment|/* coalesce the neighbouring file bufs */
name|file_size
operator|=
operator|(
name|size_t
operator|)
name|ngx_chain_coalesce_file
argument_list|(
operator|&
name|cl
argument_list|,
name|limit
operator|-
name|send
argument_list|)
expr_stmt|;
name|send
operator|+=
name|file_size
expr_stmt|;
if|#
directive|if
literal|1
if|if
condition|(
name|file_size
operator|==
literal|0
condition|)
block|{
name|ngx_debug_point
argument_list|()
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
endif|#
directive|endif
name|n
operator|=
name|ngx_linux_sendfile
argument_list|(
name|c
argument_list|,
name|file
argument_list|,
name|file_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
if|if
condition|(
name|n
operator|==
name|NGX_DONE
condition|)
block|{
comment|/* thread task posted */
return|return
name|in
return|;
block|}
name|sent
operator|=
operator|(
name|n
operator|==
name|NGX_AGAIN
operator|)
condition|?
literal|0
else|:
name|n
expr_stmt|;
block|}
else|else
block|{
name|n
operator|=
name|ngx_writev
argument_list|(
name|c
argument_list|,
operator|&
name|header
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|sent
operator|=
operator|(
name|n
operator|==
name|NGX_AGAIN
operator|)
condition|?
literal|0
else|:
name|n
expr_stmt|;
block|}
name|c
operator|->
name|sent
operator|+=
name|sent
expr_stmt|;
name|in
operator|=
name|ngx_chain_update_sent
argument_list|(
name|in
argument_list|,
name|sent
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
name|wev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
return|return
name|in
return|;
block|}
if|if
condition|(
operator|(
name|size_t
operator|)
operator|(
name|send
operator|-
name|prev_send
operator|)
operator|!=
name|sent
condition|)
block|{
comment|/*              * sendfile() on Linux 4.3+ might be interrupted at any time,              * and provides no indication if it was interrupted or not,              * so we have to retry till an explicit EAGAIN              *              * sendfile() in threads can also report less bytes written              * than we are prepared to send now, since it was started in              * some point in the past, so we again have to retry              */
name|send
operator|=
name|prev_send
operator|+
name|sent
expr_stmt|;
block|}
if|if
condition|(
name|send
operator|>=
name|limit
operator|||
name|in
operator|==
name|NULL
condition|)
block|{
return|return
name|in
return|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|ssize_t
DECL|function|ngx_linux_sendfile (ngx_connection_t * c,ngx_buf_t * file,size_t size)
name|ngx_linux_sendfile
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_buf_t
modifier|*
name|file
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE64
operator|)
name|off_t
name|offset
decl_stmt|;
else|#
directive|else
name|int32_t
name|offset
decl_stmt|;
endif|#
directive|endif
name|ssize_t
name|n
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
if|if
condition|(
name|file
operator|->
name|file
operator|->
name|thread_handler
condition|)
block|{
return|return
name|ngx_linux_sendfile_thread
argument_list|(
name|c
argument_list|,
name|file
argument_list|,
name|size
argument_list|)
return|;
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE64
operator|)
name|offset
operator|=
name|file
operator|->
name|file_pos
expr_stmt|;
else|#
directive|else
name|offset
operator|=
operator|(
name|int32_t
operator|)
name|file
operator|->
name|file_pos
expr_stmt|;
endif|#
directive|endif
name|eintr
label|:
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"sendfile: @%O %uz"
argument_list|,
name|file
operator|->
name|file_pos
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|n
operator|=
name|sendfile
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|file
operator|->
name|file
operator|->
name|fd
argument_list|,
operator|&
name|offset
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_errno
expr_stmt|;
switch|switch
condition|(
name|err
condition|)
block|{
case|case
name|NGX_EAGAIN
case|:
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"sendfile() is not ready"
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
case|case
name|NGX_EINTR
case|:
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"sendfile() was interrupted"
argument_list|)
expr_stmt|;
goto|goto
name|eintr
goto|;
default|default:
name|c
operator|->
name|write
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|err
argument_list|,
literal|"sendfile() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
comment|/*          * if sendfile returns zero, then someone has truncated the file,          * so the offset became beyond the end of the file          */
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"sendfile() reported that \"%s\" was truncated at %O"
argument_list|,
name|file
operator|->
name|file
operator|->
name|name
operator|.
name|data
argument_list|,
name|file
operator|->
name|file_pos
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"sendfile: %z of %uz @%O"
argument_list|,
name|n
argument_list|,
name|size
argument_list|,
name|file
operator|->
name|file_pos
argument_list|)
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_typedef
DECL|struct|__anon28b03e5a0108
typedef|typedef
struct|struct
block|{
DECL|member|file
name|ngx_buf_t
modifier|*
name|file
decl_stmt|;
DECL|member|socket
name|ngx_socket_t
name|socket
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|sent
name|size_t
name|sent
decl_stmt|;
DECL|member|err
name|ngx_err_t
name|err
decl_stmt|;
DECL|typedef|ngx_linux_sendfile_ctx_t
block|}
name|ngx_linux_sendfile_ctx_t
typedef|;
end_typedef

begin_function
specifier|static
name|ssize_t
DECL|function|ngx_linux_sendfile_thread (ngx_connection_t * c,ngx_buf_t * file,size_t size)
name|ngx_linux_sendfile_thread
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_buf_t
modifier|*
name|file
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|ngx_thread_task_t
modifier|*
name|task
decl_stmt|;
name|ngx_linux_sendfile_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"linux sendfile thread: %d, %uz, %O"
argument_list|,
name|file
operator|->
name|file
operator|->
name|fd
argument_list|,
name|size
argument_list|,
name|file
operator|->
name|file_pos
argument_list|)
expr_stmt|;
name|task
operator|=
name|c
operator|->
name|sendfile_task
expr_stmt|;
if|if
condition|(
name|task
operator|==
name|NULL
condition|)
block|{
name|task
operator|=
name|ngx_thread_task_alloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_linux_sendfile_ctx_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|task
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|task
operator|->
name|handler
operator|=
name|ngx_linux_sendfile_thread_handler
expr_stmt|;
name|c
operator|->
name|sendfile_task
operator|=
name|task
expr_stmt|;
block|}
name|ctx
operator|=
name|task
operator|->
name|ctx
expr_stmt|;
name|wev
operator|=
name|c
operator|->
name|write
expr_stmt|;
if|if
condition|(
name|task
operator|->
name|event
operator|.
name|complete
condition|)
block|{
name|task
operator|->
name|event
operator|.
name|complete
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|err
operator|==
name|NGX_EAGAIN
condition|)
block|{
comment|/*              * if wev->complete is set, this means that a write event              * happened while we were waiting for the thread task, so              * we have to retry sending even on EAGAIN              */
if|if
condition|(
name|wev
operator|->
name|complete
condition|)
block|{
return|return
literal|0
return|;
block|}
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|ctx
operator|->
name|err
condition|)
block|{
name|wev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|ctx
operator|->
name|err
argument_list|,
literal|"sendfile() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|ctx
operator|->
name|sent
operator|==
literal|0
condition|)
block|{
comment|/*              * if sendfile returns zero, then someone has truncated the file,              * so the offset became beyond the end of the file              */
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"sendfile() reported that \"%s\" was truncated at %O"
argument_list|,
name|file
operator|->
name|file
operator|->
name|name
operator|.
name|data
argument_list|,
name|file
operator|->
name|file_pos
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|ctx
operator|->
name|sent
return|;
block|}
name|ctx
operator|->
name|file
operator|=
name|file
expr_stmt|;
name|ctx
operator|->
name|socket
operator|=
name|c
operator|->
name|fd
expr_stmt|;
name|ctx
operator|->
name|size
operator|=
name|size
expr_stmt|;
name|wev
operator|->
name|complete
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|file
operator|->
name|file
operator|->
name|thread_handler
argument_list|(
name|task
argument_list|,
name|file
operator|->
name|file
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_DONE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_linux_sendfile_thread_handler (void * data,ngx_log_t * log)
name|ngx_linux_sendfile_thread_handler
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_linux_sendfile_ctx_t
modifier|*
name|ctx
init|=
name|data
decl_stmt|;
name|off_t
name|offset
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|ngx_buf_t
modifier|*
name|file
decl_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"linux sendfile thread handler"
argument_list|)
expr_stmt|;
name|file
operator|=
name|ctx
operator|->
name|file
expr_stmt|;
name|offset
operator|=
name|file
operator|->
name|file_pos
expr_stmt|;
name|again
label|:
name|n
operator|=
name|sendfile
argument_list|(
name|ctx
operator|->
name|socket
argument_list|,
name|file
operator|->
name|file
operator|->
name|fd
argument_list|,
operator|&
name|offset
argument_list|,
name|ctx
operator|->
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
operator|-
literal|1
condition|)
block|{
name|ctx
operator|->
name|err
operator|=
name|ngx_errno
expr_stmt|;
block|}
else|else
block|{
name|ctx
operator|->
name|sent
operator|=
name|n
expr_stmt|;
name|ctx
operator|->
name|err
operator|=
literal|0
expr_stmt|;
block|}
if|#
directive|if
literal|0
block_content|ngx_time_update();
endif|#
directive|endif
name|ngx_log_debug4
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"sendfile: %z (err: %d) of %uz @%O"
argument_list|,
name|n
argument_list|,
name|ctx
operator|->
name|err
argument_list|,
name|ctx
operator|->
name|size
argument_list|,
name|file
operator|->
name|file_pos
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
goto|goto
name|again
goto|;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* NGX_THREADS */
end_comment

end_unit

