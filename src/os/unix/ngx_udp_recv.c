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
DECL|function|ngx_udp_unix_recv (ngx_connection_t * c,u_char * buf,size_t size)
name|ngx_udp_unix_recv
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
name|rev
decl_stmt|;
name|rev
operator|=
name|c
operator|->
name|read
expr_stmt|;
do|do
block|{
name|n
operator|=
name|recv
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
literal|"recv: fd:%d %z of %uz"
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
operator|>=
literal|0
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_KQUEUE_EVENT
condition|)
block|{
name|rev
operator|->
name|available
operator|-=
name|n
expr_stmt|;
comment|/*                  * rev->available may be negative here because some additional                  * bytes may be received between kevent() and recv()                  */
if|if
condition|(
name|rev
operator|->
name|available
operator|<=
literal|0
condition|)
block|{
name|rev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
name|rev
operator|->
name|available
operator|=
literal|0
expr_stmt|;
block|}
block|}
endif|#
directive|endif
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
name|err
operator|==
name|NGX_EAGAIN
operator|||
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
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
literal|"recv() not ready"
argument_list|)
expr_stmt|;
name|n
operator|=
name|NGX_AGAIN
expr_stmt|;
block|}
else|else
block|{
name|n
operator|=
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|err
argument_list|,
literal|"recv() failed"
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
do|while
condition|(
name|err
operator|==
name|NGX_EINTR
condition|)
do|;
name|rev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
name|rev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
block|}
return|return
name|n
return|;
block|}
end_function

end_unit

