begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
name|int
name|ngx_unix_recv_error
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|,
name|ngx_err_t
name|err
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
end_if

begin_function
DECL|function|ngx_unix_recv (ngx_connection_t * c,char * buf,size_t size)
name|ssize_t
name|ngx_unix_recv
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|char
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
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_HAVE_KQUEUE_EVENT
condition|)
block|{
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"recv: eof:%d, avail:%d, err:%d"
argument|_                       rev->kq_eof _ rev->available _ rev->kq_errno
argument_list|)
empty_stmt|;
if|if
condition|(
name|rev
operator|->
name|available
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|rev
operator|->
name|kq_eof
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
name|eof
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|rev
operator|->
name|kq_errno
condition|)
block|{
name|rev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|ngx_set_socket_errno
argument_list|(
name|rev
operator|->
name|kq_errno
argument_list|)
expr_stmt|;
return|return
name|ngx_unix_recv_error
argument_list|(
name|rev
argument_list|,
name|rev
operator|->
name|kq_errno
argument_list|)
return|;
block|}
return|return
literal|0
return|;
block|}
else|else
block|{
return|return
name|NGX_AGAIN
return|;
block|}
block|}
block|}
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
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"recv: %d:%d"
argument|_ n _ size
argument_list|)
empty_stmt|;
if|if
condition|(
name|n
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_HAVE_KQUEUE_EVENT
condition|)
block|{
name|rev
operator|->
name|available
operator|-=
name|n
expr_stmt|;
comment|/*                  * rev->available can be negative here because some additional                  * bytes can be received between kevent() and recv()                  */
if|if
condition|(
name|rev
operator|->
name|available
operator|<=
literal|0
condition|)
block|{
if|if
condition|(
operator|!
name|rev
operator|->
name|kq_eof
condition|)
block|{
name|rev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|rev
operator|->
name|available
operator|<
literal|0
condition|)
block|{
name|rev
operator|->
name|available
operator|=
literal|0
expr_stmt|;
block|}
block|}
return|return
name|n
return|;
block|}
if|if
condition|(
operator|(
name|size_t
operator|)
name|n
operator|<
name|size
condition|)
block|{
name|rev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|rev
operator|->
name|eof
operator|=
literal|1
expr_stmt|;
block|}
return|return
name|n
return|;
block|}
name|n
operator|=
name|ngx_unix_recv_error
argument_list|(
name|rev
argument_list|,
name|ngx_socket_errno
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|n
operator|==
name|NGX_EINTR
condition|)
do|;
comment|/* NGX_ERROR || NGX_AGAIN */
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

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* ! NAVE_KQUEUE */
end_comment

begin_function
DECL|function|ngx_unix_recv (ngx_connection_t * c,char * buf,size_t size)
name|ssize_t
name|ngx_unix_recv
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|char
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
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"recv: %d:%d"
argument|_ n _ size
argument_list|)
empty_stmt|;
if|if
condition|(
name|n
operator|>=
literal|0
condition|)
block|{
if|if
condition|(
operator|(
name|size_t
operator|)
name|n
operator|<
name|size
condition|)
block|{
name|rev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|rev
operator|->
name|eof
operator|=
literal|1
expr_stmt|;
block|}
return|return
name|n
return|;
block|}
name|n
operator|=
name|ngx_unix_recv_error
argument_list|(
name|rev
argument_list|,
name|ngx_socket_errno
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|n
operator|==
name|NGX_EINTR
condition|)
do|;
comment|/* NGX_ERROR || NGX_AGAIN */
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* NAVE_KQUEUE */
end_comment

begin_function
DECL|function|ngx_unix_recv_error (ngx_event_t * rev,ngx_err_t err)
specifier|static
name|int
name|ngx_unix_recv_error
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|,
name|ngx_err_t
name|err
parameter_list|)
block|{
if|if
condition|(
name|err
operator|==
name|NGX_ECONNRESET
operator|&&
name|rev
operator|->
name|ignore_econnreset
condition|)
block|{
return|return
literal|0
return|;
block|}
if|if
condition|(
name|err
operator|==
name|NGX_EAGAIN
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|rev
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"recv() returned EAGAIN"
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|rev
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"recv() returned EINTR"
argument_list|)
expr_stmt|;
return|return
name|NGX_EINTR
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"recv() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
end_function

end_unit

