begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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

begin_define
DECL|macro|NGX_IOVS
define|#
directive|define
name|NGX_IOVS
value|16
end_define

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_writev_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_writev_chain
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
name|u_char
modifier|*
name|prev
decl_stmt|;
name|ssize_t
name|n
decl_stmt|,
name|size
decl_stmt|,
name|sent
decl_stmt|;
name|off_t
name|send
decl_stmt|,
name|prev_send
decl_stmt|;
name|ngx_uint_t
name|eintr
decl_stmt|,
name|complete
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_array_t
name|vec
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|struct
name|iovec
modifier|*
name|iov
decl_stmt|,
name|iovs
index|[
name|NGX_IOVS
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
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
if|if
condition|(
operator|(
name|ngx_event_flags
operator|&
name|NGX_USE_KQUEUE_EVENT
operator|)
operator|&&
name|wev
operator|->
name|pending_eof
condition|)
block|{
operator|(
name|void
operator|)
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|wev
operator|->
name|kq_errno
argument_list|,
literal|"kevent() reported about an closed connection"
argument_list|)
expr_stmt|;
name|wev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
endif|#
directive|endif
comment|/* the maximum limit size is the maximum size_t value - the page size */
if|if
condition|(
name|limit
operator|==
literal|0
operator|||
name|limit
operator|>
name|NGX_MAX_SIZE_T_VALUE
operator|-
name|ngx_pagesize
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
name|complete
operator|=
literal|0
expr_stmt|;
name|vec
operator|.
name|elts
operator|=
name|iovs
expr_stmt|;
name|vec
operator|.
name|size
operator|=
sizeof|sizeof
argument_list|(
expr|struct
name|iovec
argument_list|)
expr_stmt|;
name|vec
operator|.
name|nalloc
operator|=
name|NGX_IOVS
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
name|prev
operator|=
name|NULL
expr_stmt|;
name|iov
operator|=
name|NULL
expr_stmt|;
name|eintr
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
comment|/* create the iovec and coalesce the neighbouring bufs */
for|for
control|(
name|cl
operator|=
name|in
init|;
name|cl
operator|&&
name|vec
operator|.
name|nelts
operator|<
name|IOV_MAX
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
if|#
directive|if
literal|1
if|if
condition|(
operator|!
name|ngx_buf_in_memory
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
name|ngx_debug_point
argument_list|()
expr_stmt|;
block|}
endif|#
directive|endif
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
name|iov
operator|->
name|iov_len
operator|+=
name|size
expr_stmt|;
block|}
else|else
block|{
name|iov
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|vec
argument_list|)
expr_stmt|;
if|if
condition|(
name|iov
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|iov
operator|->
name|iov_base
operator|=
operator|(
name|void
operator|*
operator|)
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|iov
operator|->
name|iov_len
operator|=
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
name|size
expr_stmt|;
name|send
operator|+=
name|size
expr_stmt|;
block|}
name|n
operator|=
name|writev
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
if|if
condition|(
name|err
operator|==
name|NGX_EAGAIN
operator|||
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
if|if
condition|(
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
name|eintr
operator|=
literal|1
expr_stmt|;
block|}
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
literal|"writev() not ready"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|wev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
operator|(
name|void
operator|)
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|err
argument_list|,
literal|"writev() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
block|}
name|sent
operator|=
name|n
operator|>
literal|0
condition|?
name|n
else|:
literal|0
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"writev: %z"
argument_list|,
name|sent
argument_list|)
expr_stmt|;
if|if
condition|(
name|send
operator|-
name|prev_send
operator|==
name|sent
condition|)
block|{
name|complete
operator|=
literal|1
expr_stmt|;
block|}
name|c
operator|->
name|sent
operator|+=
name|sent
expr_stmt|;
for|for
control|(
name|cl
operator|=
name|in
init|;
name|cl
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
name|sent
operator|==
literal|0
condition|)
block|{
break|break;
block|}
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
name|sent
operator|>=
name|size
condition|)
block|{
name|sent
operator|-=
name|size
expr_stmt|;
name|cl
operator|->
name|buf
operator|->
name|pos
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
expr_stmt|;
continue|continue;
block|}
name|cl
operator|->
name|buf
operator|->
name|pos
operator|+=
name|sent
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|eintr
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
operator|!
name|complete
condition|)
block|{
name|wev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
return|return
name|cl
return|;
block|}
if|if
condition|(
name|send
operator|>=
name|limit
operator|||
name|cl
operator|==
name|NULL
condition|)
block|{
return|return
name|cl
return|;
block|}
name|in
operator|=
name|cl
expr_stmt|;
block|}
block|}
end_function

end_unit

