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
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_errno.h>
end_include

begin_include
include|#
directive|include
file|<ngx_time.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_timer.h>
end_include

begin_include
include|#
directive|include
file|<ngx_iocp_module.h>
end_include

begin_decl_stmt
DECL|variable|ngx_iocp_threads
name|int
name|ngx_iocp_threads
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_empty_stmt
DECL|variable|ngx_iocp_threads
empty_stmt|;
end_empty_stmt

begin_decl_stmt
DECL|variable|iocp
specifier|static
name|HANDLE
name|iocp
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|timer_queue
specifier|static
name|ngx_event_t
modifier|*
name|timer_queue
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_iocp_init (int max_connections,ngx_log_t * log)
name|int
name|ngx_iocp_init
parameter_list|(
name|int
name|max_connections
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|iocp
operator|=
name|CreateIoCompletionPort
argument_list|(
name|INVALID_HANDLE_VALUE
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|ngx_iocp_threads
argument_list|)
expr_stmt|;
if|if
condition|(
name|iocp
operator|==
name|NULL
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"CreateIoCompletionPort() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|timer_queue
operator|=
name|ngx_event_init_timer
argument_list|(
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|timer_queue
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_event_actions
operator|.
name|process
operator|=
name|ngx_iocp_process_events
expr_stmt|;
name|ngx_event_flags
operator|=
name|NGX_HAVE_AIO_EVENT
operator||
name|NGX_HAVE_IOCP_EVENT
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_iocp_add_event (ngx_event_t * ev)
name|int
name|ngx_iocp_add_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
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
name|ngx_log_debug
argument_list|(
argument|ev->log
argument_list|,
literal|"iocp: %d, %08x:%08x"
argument|_ c->fd _ ev _&ev->ovlp
argument_list|)
empty_stmt|;
if|if
condition|(
name|CreateIoCompletionPort
argument_list|(
operator|(
name|HANDLE
operator|)
name|c
operator|->
name|fd
argument_list|,
name|iocp
argument_list|,
operator|(
name|DWORD
operator|)
name|ev
argument_list|,
literal|0
argument_list|)
operator|==
name|NULL
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"CreateIoCompletionPort() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_iocp_process_events (ngx_log_t * log)
name|int
name|ngx_iocp_process_events
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|size_t
name|bytes
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_msec_t
name|timer
decl_stmt|,
name|delta
decl_stmt|;
name|ngx_event_t
modifier|*
name|ev
decl_stmt|,
modifier|*
name|e
decl_stmt|;
name|ngx_event_ovlp_t
modifier|*
name|ovlp
decl_stmt|;
name|ngx_log_debug
argument_list|(
name|log
argument_list|,
literal|"iocp"
argument_list|)
expr_stmt|;
name|timer
operator|=
name|ngx_event_find_timer
argument_list|()
expr_stmt|;
if|if
condition|(
name|timer
condition|)
block|{
name|delta
operator|=
name|ngx_msec
argument_list|()
expr_stmt|;
block|}
else|else
block|{
name|timer
operator|=
name|INFINITE
expr_stmt|;
name|delta
operator|=
literal|0
expr_stmt|;
block|}
name|ngx_log_debug
argument_list|(
argument|log
argument_list|,
literal|"iocp timer: %d"
argument|_ timer
argument_list|)
empty_stmt|;
if|#
directive|if
literal|1
name|rc
operator|=
name|GetQueuedCompletionStatus
argument_list|(
name|iocp
argument_list|,
operator|&
name|bytes
argument_list|,
operator|(
name|LPDWORD
operator|)
operator|&
name|e
argument_list|,
operator|(
name|LPOVERLAPPED
operator|*
operator|)
operator|&
name|ovlp
argument_list|,
name|timer
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|log
argument_list|,
literal|"iocp: %d, %d:%08x:%08x"
argument|_ rc _ bytes _ e _ ovlp
argument_list|)
empty_stmt|;
if|if
condition|(
name|rc
operator|==
literal|0
condition|)
block|{
else|#
directive|else
if|if
condition|(
name|GetQueuedCompletionStatus
argument_list|(
name|iocp
argument_list|,
operator|&
name|bytes
argument_list|,
operator|(
name|LPDWORD
operator|)
operator|&
name|e
argument_list|,
operator|(
name|LPOVERLAPPED
operator|*
operator|)
operator|&
name|ovlp
argument_list|,
name|timer
argument_list|)
operator|==
literal|0
condition|)
block|{
endif|#
directive|endif
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|ovlp
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|err
operator|!=
name|WAIT_TIMEOUT
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
literal|"GetQueuedCompletionStatus() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
else|else
block|{
name|ovlp
operator|->
name|error
operator|=
name|err
expr_stmt|;
block|}
block|}
if|if
condition|(
name|timer
operator|!=
name|INFINITE
condition|)
block|{
name|delta
operator|=
name|ngx_msec
argument_list|()
operator|-
name|delta
expr_stmt|;
block|}
if|if
condition|(
name|ovlp
condition|)
block|{
name|ev
operator|=
name|ovlp
operator|->
name|event
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|log
argument_list|,
literal|"iocp ev: %08x"
argument|_ ev
argument_list|)
empty_stmt|;
if|if
condition|(
name|ev
operator|==
name|e
condition|)
block|{
name|ev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
name|ev
operator|->
name|available
operator|=
name|bytes
expr_stmt|;
block|}
name|ngx_log_debug
argument_list|(
argument|log
argument_list|,
literal|"iocp ev: %08x"
argument|_ ev->event_handler
argument_list|)
empty_stmt|;
if|if
condition|(
name|ev
operator|->
name|event_handler
argument_list|(
name|ev
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|ev
operator|->
name|close_handler
argument_list|(
name|ev
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|timer
operator|!=
name|INFINITE
condition|)
block|{
name|ngx_event_expire_timers
argument_list|(
name|delta
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

