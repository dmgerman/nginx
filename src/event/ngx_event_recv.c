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
file|<ngx_errno.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_recv.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_function
DECL|function|ngx_event_recv_core (ngx_event_t * ev,char * buf,size_t size)
name|int
name|ngx_event_recv_core
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|c
operator|=
operator|(
name|ngx_connection_t
operator|*
operator|)
name|ev
operator|->
name|data
expr_stmt|;
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
name|ngx_log_debug
argument_list|(
argument|ev->log
argument_list|,
literal|"ngx_event_recv: eof:%d, avail:%d, err:%d"
argument|_                   ev->eof _ ev->available _ ev->error
argument_list|)
empty_stmt|;
if|#
directive|if
operator|!
operator|(
name|USE_KQUEUE
operator|)
if|if
condition|(
name|ngx_event_type
operator|==
name|NGX_KQUEUE_EVENT
condition|)
endif|#
directive|endif
if|if
condition|(
name|ev
operator|->
name|eof
operator|&&
name|ev
operator|->
name|available
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|ev
operator|->
name|error
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|ev
operator|->
name|error
argument_list|,
literal|"ngx_event_recv: recv() failed while %s"
argument_list|,
name|ev
operator|->
name|log
operator|->
name|action
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
literal|0
return|;
block|}
endif|#
directive|endif
name|n
operator|=
name|ngx_recv
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
name|ngx_socket_errno
expr_stmt|;
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
name|ev
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"ngx_event_recv: recv() returns EAGAIN while %s"
argument_list|,
name|ev
operator|->
name|log
operator|->
name|action
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"ngx_event_recv: recv() failed while %s"
argument_list|,
name|ev
operator|->
name|log
operator|->
name|action
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
if|#
directive|if
operator|!
operator|(
name|USE_KQUEUE
operator|)
if|if
condition|(
name|ngx_event_type
operator|==
name|NGX_KQUEUE_EVENT
condition|)
endif|#
directive|endif
name|ev
operator|->
name|available
operator|-=
name|n
expr_stmt|;
endif|#
directive|endif
return|return
name|n
return|;
block|}
end_function

end_unit

