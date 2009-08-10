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

begin_include
include|#
directive|include
file|<ngx_channel.h>
end_include

begin_typedef
DECL|struct|__anon28e32abd0108
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
DECL|member|name
name|char
modifier|*
name|name
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

begin_function_decl
specifier|static
name|void
name|ngx_execute_proc
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_signal_handler
parameter_list|(
name|int
name|signo
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_process_get_status
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_argc
name|int
name|ngx_argc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_argv
name|char
modifier|*
modifier|*
name|ngx_argv
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_os_argv
name|char
modifier|*
modifier|*
name|ngx_os_argv
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_process_slot
name|ngx_int_t
name|ngx_process_slot
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_channel
name|ngx_socket_t
name|ngx_channel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_last_process
name|ngx_int_t
name|ngx_last_process
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_processes
name|ngx_process_t
name|ngx_processes
index|[
name|NGX_MAX_PROCESSES
index|]
decl_stmt|;
end_decl_stmt

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
literal|"reload"
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
literal|"reopen"
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
literal|""
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
literal|"stop"
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
literal|"quit"
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
literal|""
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGALRM
block|,
literal|"SIGALRM"
block|,
literal|""
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGINT
block|,
literal|"SIGINT"
block|,
literal|""
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGIO
block|,
literal|"SIGIO"
block|,
literal|""
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGCHLD
block|,
literal|"SIGCHLD"
block|,
literal|""
block|,
name|ngx_signal_handler
block|}
block|,
block|{
name|SIGPIPE
block|,
literal|"SIGPIPE, SIG_IGN"
block|,
literal|""
block|,
name|SIG_IGN
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
literal|""
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|ngx_pid_t
DECL|function|ngx_spawn_process (ngx_cycle_t * cycle,ngx_spawn_proc_pt proc,void * data,char * name,ngx_int_t respawn)
name|ngx_spawn_process
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_spawn_proc_pt
name|proc
parameter_list|,
name|void
modifier|*
name|data
parameter_list|,
name|char
modifier|*
name|name
parameter_list|,
name|ngx_int_t
name|respawn
parameter_list|)
block|{
name|u_long
name|on
decl_stmt|;
name|ngx_pid_t
name|pid
decl_stmt|;
name|ngx_int_t
name|s
decl_stmt|;
if|if
condition|(
name|respawn
operator|>=
literal|0
condition|)
block|{
name|s
operator|=
name|respawn
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|s
operator|=
literal|0
init|;
name|s
operator|<
name|ngx_last_process
condition|;
name|s
operator|++
control|)
block|{
if|if
condition|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|pid
operator|==
operator|-
literal|1
condition|)
block|{
break|break;
block|}
block|}
if|if
condition|(
name|s
operator|==
name|NGX_MAX_PROCESSES
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no more than %d processes can be spawned"
argument_list|,
name|NGX_MAX_PROCESSES
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
block|}
if|if
condition|(
name|respawn
operator|!=
name|NGX_PROCESS_DETACHED
condition|)
block|{
comment|/* Solaris 9 still has no AF_LOCAL */
if|if
condition|(
name|socketpair
argument_list|(
name|AF_UNIX
argument_list|,
name|SOCK_STREAM
argument_list|,
literal|0
argument_list|,
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"socketpair() failed while spawning \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"channel %d:%d"
argument_list|,
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|0
index|]
argument_list|,
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_nonblocking
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|0
index|]
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_nonblocking_n
literal|" failed while spawning \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|ngx_close_channel
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
if|if
condition|(
name|ngx_nonblocking
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
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
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_nonblocking_n
literal|" failed while spawning \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|ngx_close_channel
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
name|on
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ioctl
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|0
index|]
argument_list|,
name|FIOASYNC
argument_list|,
operator|&
name|on
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"ioctl(FIOASYNC) failed while spawning \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|ngx_close_channel
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
if|if
condition|(
name|fcntl
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|0
index|]
argument_list|,
name|F_SETOWN
argument_list|,
name|ngx_pid
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(F_SETOWN) failed while spawning \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|ngx_close_channel
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
if|if
condition|(
name|fcntl
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|0
index|]
argument_list|,
name|F_SETFD
argument_list|,
name|FD_CLOEXEC
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(FD_CLOEXEC) failed while spawning \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|ngx_close_channel
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
if|if
condition|(
name|fcntl
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|1
index|]
argument_list|,
name|F_SETFD
argument_list|,
name|FD_CLOEXEC
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(FD_CLOEXEC) failed while spawning \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|ngx_close_channel
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
name|ngx_channel
operator|=
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|1
index|]
expr_stmt|;
block|}
else|else
block|{
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|0
index|]
operator|=
operator|-
literal|1
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
index|[
literal|1
index|]
operator|=
operator|-
literal|1
expr_stmt|;
block|}
name|ngx_process_slot
operator|=
name|s
expr_stmt|;
name|pid
operator|=
name|fork
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|pid
condition|)
block|{
case|case
operator|-
literal|1
case|:
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fork() failed while spawning \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|ngx_close_channel
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|channel
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
case|case
literal|0
case|:
name|ngx_pid
operator|=
name|ngx_getpid
argument_list|()
expr_stmt|;
name|proc
argument_list|(
name|cycle
argument_list|,
name|data
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"start %s %P"
argument_list|,
name|name
argument_list|,
name|pid
argument_list|)
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|pid
operator|=
name|pid
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|exited
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|respawn
operator|>=
literal|0
condition|)
block|{
return|return
name|pid
return|;
block|}
name|ngx_processes
index|[
name|s
index|]
operator|.
name|proc
operator|=
name|proc
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|data
operator|=
name|data
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|name
operator|=
name|name
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|exiting
operator|=
literal|0
expr_stmt|;
switch|switch
condition|(
name|respawn
condition|)
block|{
case|case
name|NGX_PROCESS_NORESPAWN
case|:
name|ngx_processes
index|[
name|s
index|]
operator|.
name|respawn
operator|=
literal|0
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|just_spawn
operator|=
literal|0
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|detached
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|NGX_PROCESS_JUST_SPAWN
case|:
name|ngx_processes
index|[
name|s
index|]
operator|.
name|respawn
operator|=
literal|0
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|just_spawn
operator|=
literal|1
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|detached
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|NGX_PROCESS_RESPAWN
case|:
name|ngx_processes
index|[
name|s
index|]
operator|.
name|respawn
operator|=
literal|1
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|just_spawn
operator|=
literal|0
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|detached
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|NGX_PROCESS_JUST_RESPAWN
case|:
name|ngx_processes
index|[
name|s
index|]
operator|.
name|respawn
operator|=
literal|1
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|just_spawn
operator|=
literal|1
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|detached
operator|=
literal|0
expr_stmt|;
break|break;
case|case
name|NGX_PROCESS_DETACHED
case|:
name|ngx_processes
index|[
name|s
index|]
operator|.
name|respawn
operator|=
literal|0
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|just_spawn
operator|=
literal|0
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|detached
operator|=
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|s
operator|==
name|ngx_last_process
condition|)
block|{
name|ngx_last_process
operator|++
expr_stmt|;
block|}
return|return
name|pid
return|;
block|}
end_function

begin_function
name|ngx_pid_t
DECL|function|ngx_execute (ngx_cycle_t * cycle,ngx_exec_ctx_t * ctx)
name|ngx_execute
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_exec_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
return|return
name|ngx_spawn_process
argument_list|(
name|cycle
argument_list|,
name|ngx_execute_proc
argument_list|,
name|ctx
argument_list|,
name|ctx
operator|->
name|name
argument_list|,
name|NGX_PROCESS_DETACHED
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_execute_proc (ngx_cycle_t * cycle,void * data)
name|ngx_execute_proc
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|ngx_exec_ctx_t
modifier|*
name|ctx
init|=
name|data
decl_stmt|;
if|if
condition|(
name|execve
argument_list|(
name|ctx
operator|->
name|path
argument_list|,
name|ctx
operator|->
name|argv
argument_list|,
name|ctx
operator|->
name|envp
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"execve() failed while executing %s \"%s\""
argument_list|,
name|ctx
operator|->
name|name
argument_list|,
name|ctx
operator|->
name|path
argument_list|)
expr_stmt|;
block|}
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_init_signals (ngx_log_t * log)
name|ngx_init_signals
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
name|sigaction
name|sa
decl_stmt|;
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
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_signal_handler (int signo)
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
name|ngx_time_update
argument_list|(
literal|0
argument_list|,
literal|0
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
literal|", stop accepting connections"
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
literal|", reopening logs"
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
comment|/*                  * Ignore the signal in the new binary if its parent is                  * not the init process, i.e. the old binary's process                  * is still running.  Or ignore the signal in the old binary's                  * process if the new binary's process is already running.                  */
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
name|NGX_NOACCEPT_SIGNAL
argument_list|)
case|:
name|ngx_debug_quit
operator|=
literal|1
expr_stmt|;
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
literal|", reopening logs"
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
name|NGX_LOG_NOTICE
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
specifier|static
name|void
DECL|function|ngx_process_get_status (void)
name|ngx_process_get_status
parameter_list|(
name|void
parameter_list|)
block|{
name|int
name|status
decl_stmt|;
name|char
modifier|*
name|process
decl_stmt|;
name|ngx_pid_t
name|pid
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_int_t
name|i
decl_stmt|;
name|ngx_uint_t
name|one
decl_stmt|;
name|one
operator|=
literal|0
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|pid
operator|=
name|waitpid
argument_list|(
operator|-
literal|1
argument_list|,
operator|&
name|status
argument_list|,
name|WNOHANG
argument_list|)
expr_stmt|;
if|if
condition|(
name|pid
operator|==
literal|0
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|pid
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
name|NGX_EINTR
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|err
operator|==
name|NGX_ECHILD
operator|&&
name|one
condition|)
block|{
return|return;
block|}
if|#
directive|if
operator|(
name|NGX_SOLARIS
operator|||
name|NGX_FREEBSD
operator|)
comment|/*              * Solaris always calls the signal handler for each exited process              * despite waitpid() may be already called for this process.              *              * When several processes exit at the same time FreeBSD may              * erroneously call the signal handler for exited process              * despite waitpid() may be already called for this process.              */
if|if
condition|(
name|err
operator|==
name|NGX_ECHILD
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
name|errno
argument_list|,
literal|"waitpid() failed"
argument_list|)
expr_stmt|;
return|return;
block|}
endif|#
directive|endif
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
name|errno
argument_list|,
literal|"waitpid() failed"
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|ngx_accept_mutex_ptr
condition|)
block|{
comment|/*              * unlock the accept mutex if the abnormally exited process              * held it              */
name|ngx_atomic_cmp_set
argument_list|(
name|ngx_accept_mutex_ptr
argument_list|,
name|pid
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
name|one
operator|=
literal|1
expr_stmt|;
name|process
operator|=
literal|"unknown process"
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ngx_last_process
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_processes
index|[
name|i
index|]
operator|.
name|pid
operator|==
name|pid
condition|)
block|{
name|ngx_processes
index|[
name|i
index|]
operator|.
name|status
operator|=
name|status
expr_stmt|;
name|ngx_processes
index|[
name|i
index|]
operator|.
name|exited
operator|=
literal|1
expr_stmt|;
name|process
operator|=
name|ngx_processes
index|[
name|i
index|]
operator|.
name|name
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|WTERMSIG
argument_list|(
name|status
argument_list|)
condition|)
block|{
ifdef|#
directive|ifdef
name|WCOREDUMP
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"%s %P exited on signal %d%s"
argument_list|,
name|process
argument_list|,
name|pid
argument_list|,
name|WTERMSIG
argument_list|(
name|status
argument_list|)
argument_list|,
name|WCOREDUMP
argument_list|(
name|status
argument_list|)
condition|?
literal|" (core dumped)"
else|:
literal|""
argument_list|)
expr_stmt|;
else|#
directive|else
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"%s %P exited on signal %d"
argument_list|,
name|process
argument_list|,
name|pid
argument_list|,
name|WTERMSIG
argument_list|(
name|status
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
else|else
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"%s %P exited with code %d"
argument_list|,
name|process
argument_list|,
name|pid
argument_list|,
name|WEXITSTATUS
argument_list|(
name|status
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|WEXITSTATUS
argument_list|(
name|status
argument_list|)
operator|==
literal|2
operator|&&
name|ngx_processes
index|[
name|i
index|]
operator|.
name|respawn
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"%s %P exited with fatal code %d "
literal|"and can not be respawn"
argument_list|,
name|process
argument_list|,
name|pid
argument_list|,
name|WEXITSTATUS
argument_list|(
name|status
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_processes
index|[
name|i
index|]
operator|.
name|respawn
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|ngx_debug_point (void)
name|ngx_debug_point
parameter_list|(
name|void
parameter_list|)
block|{
name|ngx_core_conf_t
modifier|*
name|ccf
decl_stmt|;
name|ccf
operator|=
operator|(
name|ngx_core_conf_t
operator|*
operator|)
name|ngx_get_conf
argument_list|(
name|ngx_cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_core_module
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|ccf
operator|->
name|debug_points
condition|)
block|{
case|case
name|NGX_DEBUG_POINTS_STOP
case|:
name|raise
argument_list|(
name|SIGSTOP
argument_list|)
expr_stmt|;
break|break;
case|case
name|NGX_DEBUG_POINTS_ABORT
case|:
name|ngx_abort
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_os_signal_process (ngx_cycle_t * cycle,char * name,ngx_int_t pid)
name|ngx_os_signal_process
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|char
modifier|*
name|name
parameter_list|,
name|ngx_int_t
name|pid
parameter_list|)
block|{
name|ngx_signal_t
modifier|*
name|sig
decl_stmt|;
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
name|ngx_strcmp
argument_list|(
name|name
argument_list|,
name|sig
operator|->
name|name
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|kill
argument_list|(
name|pid
argument_list|,
name|sig
operator|->
name|signo
argument_list|)
operator|!=
operator|-
literal|1
condition|)
block|{
return|return
literal|0
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kill(%P, %d) failed"
argument_list|,
name|pid
argument_list|,
name|sig
operator|->
name|signo
argument_list|)
expr_stmt|;
block|}
block|}
return|return
literal|1
return|;
block|}
end_function

end_unit

