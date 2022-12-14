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

begin_function
name|ssize_t
DECL|function|ngx_unix_send (ngx_connection_t * c,u_char * buf,size_t size)
name|ngx_unix_send
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|wev
operator|=
name|c
operator|->
name|write
expr_stmt|;
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
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
for|for
control|(
init|;
condition|;
control|)
block|{
name|n
operator|=
name|send
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|buf
argument_list|,
name|size
argument_list|,
literal|0
argument_list|)
expr_stmt|;
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
literal|"send: fd:%d %z of %uz"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|n
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|>
literal|0
condition|)
block|{
if|if
condition|(
name|n
operator|<
operator|(
name|ssize_t
operator|)
name|size
condition|)
block|{
name|wev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
block|}
name|c
operator|->
name|sent
operator|+=
name|n
expr_stmt|;
return|return
name|n
return|;
block|}
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"send() returned zero"
argument_list|)
expr_stmt|;
name|wev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
return|return
name|n
return|;
block|}
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
name|wev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
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
literal|"send() not ready"
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_EAGAIN
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
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
literal|"send() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
block|}
end_function

end_unit

