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
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
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

begin_if
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_kqueue_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_aio_init (int max_connections,ngx_log_t * log)
name|int
name|ngx_aio_init
parameter_list|(
name|int
name|max_connections
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
name|int
name|rc
decl_stmt|;
name|rc
operator|=
name|ngx_kqueue_init
argument_list|(
name|max_connections
argument_list|,
name|log
argument_list|)
expr_stmt|;
name|ngx_event_flags
operator|=
name|NGX_HAVE_AIO_EVENT
expr_stmt|;
name|ngx_write_chain_proc
operator|=
name|ngx_aio_write_chain
expr_stmt|;
return|return
name|rc
return|;
endif|#
directive|endif
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* 1 */
end_comment

begin_comment
unit|int ngx_posix_aio_process_events(ngx_log_t *log) {     listen via SIGIO;     aio_* via SIGxxx;      sigsuspend()/sigwaitinfo()/sigtimedwait(); }
comment|/* 2 */
end_comment

begin_comment
unit|int ngx_posix_aio_process_events(ngx_log_t *log) {     unmask signal      listen via SIGIO;
comment|/* BUG: SIGIO can be delivered before aio_*() */
end_comment

begin_comment
unit|aio_suspend()/aiowait()/aio_waitcomplete() with timeout      mask signal      if (ngx_socket_errno == NGX_EINTR)         look listen         select()/accept() nb listen sockets     else         aio }
comment|/* 3 */
end_comment

begin_comment
unit|int ngx_posix_aio_process_events(ngx_log_t *log) {     unmask signal
comment|/* BUG: AIO signal can be delivered before select() */
end_comment

begin_endif
unit|select(listen);      mask signal      if (ngx_socket_errno == NGX_EINTR)         look ready array }  void aio_sig_handler(int signo, siginfo_t *siginfo, void *context) {     push siginfo->si_value.sival_ptr }
endif|#
directive|endif
end_endif

end_unit

