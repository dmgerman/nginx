begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/* 1 */
end_comment

begin_function
DECL|function|ngx_posix_aio_process_events (ngx_log_t * log)
name|int
name|ngx_posix_aio_process_events
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|listen
name|via
name|SIGIO
decl_stmt|;
name|aio_
modifier|*
name|via
name|SIGxxx
decl_stmt|;
name|sigsuspend
argument_list|()
operator|/
name|sigwaitinfo
argument_list|()
operator|/
name|sigtimedwait
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/* 2 */
end_comment

begin_function
DECL|function|ngx_posix_aio_process_events (ngx_log_t * log)
name|int
name|ngx_posix_aio_process_events
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|unmask
name|signal
name|listen
name|via
name|SIGIO
decl_stmt|;
comment|/* BUG: SIGIO can be delivered before aio_*() */
name|aio_suspend
argument_list|()
operator|/
name|aiowait
argument_list|()
operator|/
name|aio_waitcomplete
argument_list|()
name|with
name|timeout
name|mask
name|signal
if|if
condition|(
name|ngx_socket_errno
operator|==
name|NGX_EINTR
condition|)
name|look
name|listen
name|select
argument_list|()
operator|/
name|accept
argument_list|()
name|nb
name|listen
name|sockets
else|else
name|aio
block|}
end_function

begin_comment
comment|/* 3 */
end_comment

begin_function
DECL|function|ngx_posix_aio_process_events (ngx_log_t * log)
name|int
name|ngx_posix_aio_process_events
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|unmask
name|signal
comment|/* BUG: AIO signal can be delivered before select() */
name|select
argument_list|(
name|listen
argument_list|)
decl_stmt|;
name|mask
name|signal
if|if
condition|(
name|ngx_socket_errno
operator|==
name|NGX_EINTR
condition|)
name|look
name|ready
name|array
block|}
end_function

begin_function
DECL|function|aio_sig_handler (int signo,siginfo_t * siginfo,void * context)
name|void
name|aio_sig_handler
parameter_list|(
name|int
name|signo
parameter_list|,
name|siginfo_t
modifier|*
name|siginfo
parameter_list|,
name|void
modifier|*
name|context
parameter_list|)
block|{
name|push
name|siginfo
operator|->
name|si_value
operator|.
name|sival_ptr
block|}
end_function

end_unit

