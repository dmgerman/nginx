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

begin_if
if|#
directive|if
operator|(
name|NGX_TEST_BUILD_SOLARIS_SENDFILEV
operator|)
end_if

begin_comment
comment|/* Solaris declarations */
end_comment

begin_typedef
DECL|struct|sendfilevec
typedef|typedef
struct|struct
name|sendfilevec
block|{
DECL|member|sfv_fd
name|int
name|sfv_fd
decl_stmt|;
DECL|member|sfv_flag
name|u_int
name|sfv_flag
decl_stmt|;
DECL|member|sfv_off
name|off_t
name|sfv_off
decl_stmt|;
DECL|member|sfv_len
name|size_t
name|sfv_len
decl_stmt|;
DECL|typedef|sendfilevec_t
block|}
name|sendfilevec_t
typedef|;
end_typedef

begin_define
DECL|macro|SFV_FD_SELF
define|#
directive|define
name|SFV_FD_SELF
value|-2
end_define

begin_function
DECL|function|sendfilev (int fd,const struct sendfilevec * vec,int sfvcnt,size_t * xferred)
specifier|static
name|ssize_t
name|sendfilev
parameter_list|(
name|int
name|fd
parameter_list|,
specifier|const
name|struct
name|sendfilevec
modifier|*
name|vec
parameter_list|,
name|int
name|sfvcnt
parameter_list|,
name|size_t
modifier|*
name|xferred
parameter_list|)
block|{
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function_decl
name|ngx_chain_t
modifier|*
name|ngx_solaris_sendfilev_chain
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_SENDFILEVECS
define|#
directive|define
name|NGX_SENDFILEVECS
value|NGX_IOVS_PREALLOCATE
end_define

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_solaris_sendfilev_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_solaris_sendfilev_chain
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
name|fd
decl_stmt|;
name|u_char
modifier|*
name|prev
decl_stmt|;
name|off_t
name|size
decl_stmt|,
name|send
decl_stmt|,
name|prev_send
decl_stmt|,
name|aligned
decl_stmt|,
name|fprev
decl_stmt|;
name|size_t
name|sent
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|ngx_int_t
name|eintr
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|sendfilevec_t
modifier|*
name|sfv
decl_stmt|,
name|sfvs
index|[
name|NGX_SENDFILEVECS
index|]
decl_stmt|;
name|ngx_array_t
name|vec
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
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
if|if
condition|(
operator|!
name|c
operator|->
name|sendfile
condition|)
block|{
return|return
name|ngx_writev_chain
argument_list|(
name|c
argument_list|,
name|in
argument_list|,
name|limit
argument_list|)
return|;
block|}
comment|/* the maximum limit size is the maximum size_t value - the page size */
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
name|NGX_MAX_SIZE_T_VALUE
operator|-
name|ngx_pagesize
operator|)
condition|)
block|{
name|limit
operator|=
name|NGX_MAX_SIZE_T_VALUE
operator|-
name|ngx_pagesize
expr_stmt|;
block|}
name|send
operator|=
literal|0
expr_stmt|;
name|vec
operator|.
name|elts
operator|=
name|sfvs
expr_stmt|;
name|vec
operator|.
name|size
operator|=
sizeof|sizeof
argument_list|(
name|sendfilevec_t
argument_list|)
expr_stmt|;
name|vec
operator|.
name|nalloc
operator|=
name|NGX_SENDFILEVECS
expr_stmt|;
name|vec
operator|.
name|pool
operator|=
name|c
operator|->
name|pool
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|fd
operator|=
name|SFV_FD_SELF
expr_stmt|;
name|prev
operator|=
name|NULL
expr_stmt|;
name|fprev
operator|=
literal|0
expr_stmt|;
name|sfv
operator|=
name|NULL
expr_stmt|;
name|eintr
operator|=
literal|0
expr_stmt|;
name|sent
operator|=
literal|0
expr_stmt|;
name|prev_send
operator|=
name|send
expr_stmt|;
name|vec
operator|.
name|nelts
operator|=
literal|0
expr_stmt|;
comment|/* create the sendfilevec and coalesce the neighbouring bufs */
for|for
control|(
name|cl
operator|=
name|in
init|;
name|cl
operator|&&
name|send
operator|<
name|limit
condition|;
name|cl
operator|=
name|cl
operator|->
name|next
control|)
block|{
if|if
condition|(
name|ngx_buf_special
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|ngx_buf_in_memory_only
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
name|fd
operator|=
name|SFV_FD_SELF
expr_stmt|;
name|size
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
operator|-
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
if|if
condition|(
name|send
operator|+
name|size
operator|>
name|limit
condition|)
block|{
name|size
operator|=
name|limit
operator|-
name|send
expr_stmt|;
block|}
if|if
condition|(
name|prev
operator|==
name|cl
operator|->
name|buf
operator|->
name|pos
condition|)
block|{
name|sfv
operator|->
name|sfv_len
operator|+=
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|vec
operator|.
name|nelts
operator|>=
name|IOV_MAX
condition|)
block|{
break|break;
block|}
name|sfv
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|vec
argument_list|)
expr_stmt|;
if|if
condition|(
name|sfv
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|sfv
operator|->
name|sfv_fd
operator|=
name|SFV_FD_SELF
expr_stmt|;
name|sfv
operator|->
name|sfv_flag
operator|=
literal|0
expr_stmt|;
name|sfv
operator|->
name|sfv_off
operator|=
operator|(
name|off_t
operator|)
operator|(
name|uintptr_t
operator|)
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|sfv
operator|->
name|sfv_len
operator|=
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
block|}
name|prev
operator|=
name|cl
operator|->
name|buf
operator|->
name|pos
operator|+
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
name|send
operator|+=
name|size
expr_stmt|;
block|}
else|else
block|{
name|prev
operator|=
name|NULL
expr_stmt|;
name|size
operator|=
name|cl
operator|->
name|buf
operator|->
name|file_last
operator|-
name|cl
operator|->
name|buf
operator|->
name|file_pos
expr_stmt|;
if|if
condition|(
name|send
operator|+
name|size
operator|>
name|limit
condition|)
block|{
name|size
operator|=
name|limit
operator|-
name|send
expr_stmt|;
name|aligned
operator|=
operator|(
name|cl
operator|->
name|buf
operator|->
name|file_pos
operator|+
name|size
operator|+
name|ngx_pagesize
operator|-
literal|1
operator|)
operator|&
operator|~
operator|(
operator|(
name|off_t
operator|)
name|ngx_pagesize
operator|-
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|aligned
operator|<=
name|cl
operator|->
name|buf
operator|->
name|file_last
condition|)
block|{
name|size
operator|=
name|aligned
operator|-
name|cl
operator|->
name|buf
operator|->
name|file_pos
expr_stmt|;
block|}
block|}
if|if
condition|(
name|fd
operator|==
name|cl
operator|->
name|buf
operator|->
name|file
operator|->
name|fd
operator|&&
name|fprev
operator|==
name|cl
operator|->
name|buf
operator|->
name|file_pos
condition|)
block|{
name|sfv
operator|->
name|sfv_len
operator|+=
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|vec
operator|.
name|nelts
operator|>=
name|IOV_MAX
condition|)
block|{
break|break;
block|}
name|sfv
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|vec
argument_list|)
expr_stmt|;
if|if
condition|(
name|sfv
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|fd
operator|=
name|cl
operator|->
name|buf
operator|->
name|file
operator|->
name|fd
expr_stmt|;
name|sfv
operator|->
name|sfv_fd
operator|=
name|fd
expr_stmt|;
name|sfv
operator|->
name|sfv_flag
operator|=
literal|0
expr_stmt|;
name|sfv
operator|->
name|sfv_off
operator|=
name|cl
operator|->
name|buf
operator|->
name|file_pos
expr_stmt|;
name|sfv
operator|->
name|sfv_len
operator|=
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
block|}
name|fprev
operator|=
name|cl
operator|->
name|buf
operator|->
name|file_pos
operator|+
name|size
expr_stmt|;
name|send
operator|+=
name|size
expr_stmt|;
block|}
block|}
name|n
operator|=
name|sendfilev
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|vec
operator|.
name|elts
argument_list|,
name|vec
operator|.
name|nelts
argument_list|,
operator|&
name|sent
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
break|break;
case|case
name|NGX_EINTR
case|:
name|eintr
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
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
literal|"sendfilev() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"sendfilev() sent only %uz bytes"
argument_list|,
name|sent
argument_list|)
expr_stmt|;
block|}
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
literal|"sendfilev: %z %z"
argument_list|,
name|n
argument_list|,
name|sent
argument_list|)
expr_stmt|;
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
name|eintr
condition|)
block|{
name|send
operator|=
name|prev_send
operator|+
name|sent
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|send
operator|-
name|prev_send
operator|!=
operator|(
name|off_t
operator|)
name|sent
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

end_unit

