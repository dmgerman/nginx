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

begin_decl_stmt
DECL|variable|ngx_max_sockets
name|int
name|ngx_max_sockets
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_inherited_nonblocking
name|int
name|ngx_inherited_nonblocking
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|(
name|NGX_POSIX_IO
operator|)
end_if

begin_decl_stmt
DECL|variable|ngx_os_io
name|ngx_os_io_t
name|ngx_os_io
init|=
block|{
name|ngx_unix_recv
block|,
name|ngx_readv_chain
block|,
name|NULL
block|,
name|ngx_writev_chain
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_os_init (ngx_log_t * log)
name|int
name|ngx_os_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
return|return
name|ngx_posix_init
argument_list|(
name|log
argument_list|)
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_signal_handler
parameter_list|(
name|int
name|signo
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|struct|__anon2b16639e0108
typedef|typedef
struct|struct
block|{
DECL|member|signo
name|int
name|signo
decl_stmt|;
DECL|member|signame
name|char
modifier|*
name|signame
decl_stmt|;
DECL|member|handler
name|void
function_decl|(
modifier|*
name|handler
function_decl|)
parameter_list|(
name|int
name|signo
parameter_list|)
function_decl|;
DECL|typedef|ngx_signal_t
block|}
name|ngx_signal_t
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|signals
name|ngx_signal_t
name|signals
index|[]
init|=
block|{
block|{
name|ngx_signal_value
argument_list|(
name|NGX_RECONFIGURE_SIGNAL
argument_list|)
block|,
literal|"SIG"
name|ngx_value
argument_list|(
name|NGX_RECONFIGURE_SIGNAL
argument_list|)
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|ngx_signal_value
argument_list|(
name|NGX_REOPEN_SIGNAL
argument_list|)
block|,
literal|"SIG"
name|ngx_value
argument_list|(
name|NGX_REOPEN_SIGNAL
argument_list|)
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|ngx_signal_value
argument_list|(
name|NGX_NOACCEPT_SIGNAL
argument_list|)
block|,
literal|"SIG"
name|ngx_value
argument_list|(
name|NGX_NOACCEPT_SIGNAL
argument_list|)
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|ngx_signal_value
argument_list|(
name|NGX_TERMINATE_SIGNAL
argument_list|)
block|,
literal|"SIG"
name|ngx_value
argument_list|(
name|NGX_TERMINATE_SIGNAL
argument_list|)
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|ngx_signal_value
argument_list|(
name|NGX_SHUTDOWN_SIGNAL
argument_list|)
block|,
literal|"SIG"
name|ngx_value
argument_list|(
name|NGX_SHUTDOWN_SIGNAL
argument_list|)
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|ngx_signal_value
argument_list|(
name|NGX_CHANGEBIN_SIGNAL
argument_list|)
block|,
literal|"SIG"
name|ngx_value
argument_list|(
name|NGX_CHANGEBIN_SIGNAL
argument_list|)
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGALRM
block|,
literal|"SIGALRM"
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGINT
block|,
literal|"SIGINT"
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGIO
block|,
literal|"SIGIO"
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGCHLD
block|,
literal|"SIGCHLD"
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGPIPE
block|,
literal|"SIGPIPE, SIG_IGN"
block|,
name|SIG_IGN
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_posix_init (ngx_log_t * log)
name|int
name|ngx_posix_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_signal_t
modifier|*
name|sig
decl_stmt|;
name|struct
name|rlimit
name|rlmt
decl_stmt|;
name|struct
name|sigaction
name|sa
decl_stmt|;
name|ngx_pagesize
operator|=
name|getpagesize
argument_list|()
expr_stmt|;
for|for
control|(
name|sig
operator|=
name|signals
init|;
name|sig
operator|->
name|signo
operator|!=
literal|0
condition|;
name|sig
operator|++
control|)
block|{
name|ngx_memzero
argument_list|(
operator|&
name|sa
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|sigaction
argument_list|)
argument_list|)
expr_stmt|;
name|sa
operator|.
name|sa_handler
operator|=
name|sig
operator|->
name|handler
expr_stmt|;
name|sigemptyset
argument_list|(
operator|&
name|sa
operator|.
name|sa_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|sigaction
argument_list|(
name|sig
operator|->
name|signo
argument_list|,
operator|&
name|sa
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
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
literal|"sigaction(%s) failed"
argument_list|,
name|sig
operator|->
name|signame
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
if|if
condition|(
name|getrlimit
argument_list|(
name|RLIMIT_NOFILE
argument_list|,
operator|&
name|rlmt
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|errno
argument_list|,
literal|"getrlimit(RLIMIT_NOFILE) failed)"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"getrlimit(RLIMIT_NOFILE): "
name|RLIM_T_FMT
literal|":"
name|RLIM_T_FMT
argument_list|,
name|rlmt
operator|.
name|rlim_cur
argument_list|,
name|rlmt
operator|.
name|rlim_max
argument_list|)
expr_stmt|;
name|ngx_max_sockets
operator|=
name|rlmt
operator|.
name|rlim_cur
expr_stmt|;
if|#
directive|if
operator|(
name|HAVE_INHERITED_NONBLOCK
operator|)
name|ngx_inherited_nonblocking
operator|=
literal|1
expr_stmt|;
else|#
directive|else
name|ngx_inherited_nonblocking
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_signal_handler (int signo)
name|void
name|ngx_signal_handler
parameter_list|(
name|int
name|signo
parameter_list|)
block|{
name|char
modifier|*
name|action
decl_stmt|;
name|struct
name|timeval
name|tv
decl_stmt|;
name|ngx_int_t
name|ignore
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_signal_t
modifier|*
name|sig
decl_stmt|;
name|ignore
operator|=
literal|0
expr_stmt|;
name|err
operator|=
name|ngx_errno
expr_stmt|;
for|for
control|(
name|sig
operator|=
name|signals
init|;
name|sig
operator|->
name|signo
operator|!=
literal|0
condition|;
name|sig
operator|++
control|)
block|{
if|if
condition|(
name|sig
operator|->
name|signo
operator|==
name|signo
condition|)
block|{
break|break;
block|}
block|}
name|ngx_gettimeofday
argument_list|(
operator|&
name|tv
argument_list|)
expr_stmt|;
name|ngx_time_update
argument_list|(
name|tv
operator|.
name|tv_sec
argument_list|)
expr_stmt|;
name|action
operator|=
literal|""
expr_stmt|;
switch|switch
condition|(
name|ngx_process
condition|)
block|{
case|case
name|NGX_PROCESS_MASTER
case|:
case|case
name|NGX_PROCESS_SINGLE
case|:
switch|switch
condition|(
name|signo
condition|)
block|{
case|case
name|ngx_signal_value
argument_list|(
name|NGX_SHUTDOWN_SIGNAL
argument_list|)
case|:
name|ngx_quit
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", shutting down"
expr_stmt|;
break|break;
case|case
name|ngx_signal_value
argument_list|(
name|NGX_TERMINATE_SIGNAL
argument_list|)
case|:
case|case
name|SIGINT
case|:
name|ngx_terminate
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", exiting"
expr_stmt|;
break|break;
case|case
name|ngx_signal_value
argument_list|(
name|NGX_NOACCEPT_SIGNAL
argument_list|)
case|:
name|ngx_noaccept
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", stop the accepting connections"
expr_stmt|;
break|break;
case|case
name|ngx_signal_value
argument_list|(
name|NGX_RECONFIGURE_SIGNAL
argument_list|)
case|:
name|ngx_reconfigure
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", reconfiguring"
expr_stmt|;
break|break;
case|case
name|ngx_signal_value
argument_list|(
name|NGX_REOPEN_SIGNAL
argument_list|)
case|:
name|ngx_reopen
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", reopen logs"
expr_stmt|;
break|break;
case|case
name|ngx_signal_value
argument_list|(
name|NGX_CHANGEBIN_SIGNAL
argument_list|)
case|:
if|if
condition|(
name|getppid
argument_list|()
operator|>
literal|1
operator|||
name|ngx_new_binary
operator|>
literal|0
condition|)
block|{
comment|/*                  * Ignore the signal in the new binary if its parent is                  * not the init process, i.e. the old binary's process                  * is still running.  Or ingore the signal in the old binary's                  * process if the new binary's process is already running.                  */
name|action
operator|=
literal|", ignoring"
expr_stmt|;
name|ignore
operator|=
literal|1
expr_stmt|;
break|break;
block|}
name|ngx_change_binary
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", changing binary"
expr_stmt|;
break|break;
case|case
name|SIGALRM
case|:
if|if
condition|(
operator|!
name|ngx_terminate
condition|)
block|{
name|ngx_timer
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", shutting down old worker processes"
expr_stmt|;
block|}
break|break;
case|case
name|SIGIO
case|:
name|ngx_sigio
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|SIGCHLD
case|:
name|ngx_reap
operator|=
literal|1
expr_stmt|;
break|break;
block|}
break|break;
case|case
name|NGX_PROCESS_WORKER
case|:
switch|switch
condition|(
name|signo
condition|)
block|{
case|case
name|ngx_signal_value
argument_list|(
name|NGX_SHUTDOWN_SIGNAL
argument_list|)
case|:
name|ngx_quit
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", shutting down"
expr_stmt|;
break|break;
case|case
name|ngx_signal_value
argument_list|(
name|NGX_TERMINATE_SIGNAL
argument_list|)
case|:
case|case
name|SIGINT
case|:
name|ngx_terminate
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", exiting"
expr_stmt|;
break|break;
case|case
name|ngx_signal_value
argument_list|(
name|NGX_REOPEN_SIGNAL
argument_list|)
case|:
name|ngx_reopen
operator|=
literal|1
expr_stmt|;
name|action
operator|=
literal|", reopen logs"
expr_stmt|;
break|break;
case|case
name|ngx_signal_value
argument_list|(
name|NGX_RECONFIGURE_SIGNAL
argument_list|)
case|:
case|case
name|ngx_signal_value
argument_list|(
name|NGX_NOACCEPT_SIGNAL
argument_list|)
case|:
case|case
name|ngx_signal_value
argument_list|(
name|NGX_CHANGEBIN_SIGNAL
argument_list|)
case|:
case|case
name|SIGIO
case|:
name|action
operator|=
literal|", ignoring"
expr_stmt|;
break|break;
block|}
break|break;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"signal %d (%s) received%s"
argument_list|,
name|signo
argument_list|,
name|sig
operator|->
name|signame
argument_list|,
name|action
argument_list|)
expr_stmt|;
if|if
condition|(
name|ignore
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"the changing binary signal is ignored: "
literal|"you should shutdown or terminate "
literal|"before either old or new binary's process"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|signo
operator|==
name|SIGCHLD
condition|)
block|{
name|ngx_process_get_status
argument_list|()
expr_stmt|;
block|}
name|ngx_set_errno
argument_list|(
name|err
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_posix_post_conf_init (ngx_log_t * log)
name|int
name|ngx_posix_post_conf_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_fd_t
name|pp
index|[
literal|2
index|]
decl_stmt|;
if|if
condition|(
name|pipe
argument_list|(
name|pp
argument_list|)
operator|==
operator|-
literal|1
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
literal|"pipe() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|dup2
argument_list|(
name|pp
index|[
literal|1
index|]
argument_list|,
name|STDERR_FILENO
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|errno
argument_list|,
literal|"dup2(STDERR) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|pp
index|[
literal|1
index|]
operator|>
name|STDERR_FILENO
condition|)
block|{
if|if
condition|(
name|close
argument_list|(
name|pp
index|[
literal|1
index|]
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|errno
argument_list|,
literal|"close() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

