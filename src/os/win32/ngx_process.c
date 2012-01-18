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

begin_function
name|ngx_pid_t
DECL|function|ngx_spawn_process (ngx_cycle_t * cycle,char * name,ngx_int_t respawn)
name|ngx_spawn_process
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
name|respawn
parameter_list|)
block|{
name|u_long
name|rc
decl_stmt|,
name|n
decl_stmt|,
name|code
decl_stmt|;
name|ngx_int_t
name|s
decl_stmt|;
name|ngx_pid_t
name|pid
decl_stmt|;
name|ngx_exec_ctx_t
name|ctx
decl_stmt|;
name|HANDLE
name|events
index|[
literal|2
index|]
decl_stmt|;
name|char
name|file
index|[
name|MAX_PATH
operator|+
literal|1
index|]
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
name|handle
operator|==
name|NULL
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
name|n
operator|=
name|GetModuleFileName
argument_list|(
name|NULL
argument_list|,
name|file
argument_list|,
name|MAX_PATH
argument_list|)
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"GetModuleFileName() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_INVALID_PID
return|;
block|}
name|file
index|[
name|n
index|]
operator|=
literal|'\0'
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"GetModuleFileName: \"%s\""
argument_list|,
name|file
argument_list|)
expr_stmt|;
name|ctx
operator|.
name|path
operator|=
name|file
expr_stmt|;
name|ctx
operator|.
name|name
operator|=
name|name
expr_stmt|;
name|ctx
operator|.
name|args
operator|=
name|GetCommandLine
argument_list|()
expr_stmt|;
name|ctx
operator|.
name|argv
operator|=
name|NULL
expr_stmt|;
name|ctx
operator|.
name|envp
operator|=
name|NULL
expr_stmt|;
name|pid
operator|=
name|ngx_execute
argument_list|(
name|cycle
argument_list|,
operator|&
name|ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|pid
operator|==
name|NGX_INVALID_PID
condition|)
block|{
return|return
name|pid
return|;
block|}
name|ngx_memzero
argument_list|(
operator|&
name|ngx_processes
index|[
name|s
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_process_t
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_processes
index|[
name|s
index|]
operator|.
name|handle
operator|=
name|ctx
operator|.
name|child
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
name|name
operator|=
name|name
expr_stmt|;
name|ngx_sprintf
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|term_event
argument_list|,
literal|"ngx_%s_term_%ul%Z"
argument_list|,
name|name
argument_list|,
name|pid
argument_list|)
expr_stmt|;
name|ngx_sprintf
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|quit_event
argument_list|,
literal|"ngx_%s_quit_%ul%Z"
argument_list|,
name|name
argument_list|,
name|pid
argument_list|)
expr_stmt|;
name|ngx_sprintf
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|reopen_event
argument_list|,
literal|"ngx_%s_reopen_%ul%Z"
argument_list|,
name|name
argument_list|,
name|pid
argument_list|)
expr_stmt|;
name|events
index|[
literal|0
index|]
operator|=
name|ngx_master_process_event
expr_stmt|;
name|events
index|[
literal|1
index|]
operator|=
name|ctx
operator|.
name|child
expr_stmt|;
name|rc
operator|=
name|WaitForMultipleObjects
argument_list|(
literal|2
argument_list|,
name|events
argument_list|,
literal|0
argument_list|,
literal|5000
argument_list|)
expr_stmt|;
name|ngx_time_update
argument_list|()
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"WaitForMultipleObjects: %ul"
argument_list|,
name|rc
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|rc
condition|)
block|{
case|case
name|WAIT_OBJECT_0
case|:
name|ngx_processes
index|[
name|s
index|]
operator|.
name|term
operator|=
name|OpenEvent
argument_list|(
name|EVENT_MODIFY_STATE
argument_list|,
literal|0
argument_list|,
operator|(
name|char
operator|*
operator|)
name|ngx_processes
index|[
name|s
index|]
operator|.
name|term_event
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|term
operator|==
name|NULL
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
literal|"OpenEvent(\"%s\") failed"
argument_list|,
name|ngx_processes
index|[
name|s
index|]
operator|.
name|term_event
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
name|ngx_processes
index|[
name|s
index|]
operator|.
name|quit
operator|=
name|OpenEvent
argument_list|(
name|EVENT_MODIFY_STATE
argument_list|,
literal|0
argument_list|,
operator|(
name|char
operator|*
operator|)
name|ngx_processes
index|[
name|s
index|]
operator|.
name|quit_event
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|quit
operator|==
name|NULL
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
literal|"OpenEvent(\"%s\") failed"
argument_list|,
name|ngx_processes
index|[
name|s
index|]
operator|.
name|quit_event
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
name|ngx_processes
index|[
name|s
index|]
operator|.
name|reopen
operator|=
name|OpenEvent
argument_list|(
name|EVENT_MODIFY_STATE
argument_list|,
literal|0
argument_list|,
operator|(
name|char
operator|*
operator|)
name|ngx_processes
index|[
name|s
index|]
operator|.
name|reopen_event
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|reopen
operator|==
name|NULL
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
literal|"OpenEvent(\"%s\") failed"
argument_list|,
name|ngx_processes
index|[
name|s
index|]
operator|.
name|reopen_event
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
if|if
condition|(
name|ResetEvent
argument_list|(
name|ngx_master_process_event
argument_list|)
operator|==
literal|0
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
literal|"ResetEvent(\"%s\") failed"
argument_list|,
name|ngx_master_process_event_name
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
break|break;
case|case
name|WAIT_OBJECT_0
operator|+
literal|1
case|:
if|if
condition|(
name|GetExitCodeProcess
argument_list|(
name|ctx
operator|.
name|child
argument_list|,
operator|&
name|code
argument_list|)
operator|==
literal|0
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
literal|"GetExitCodeProcess(%P) failed"
argument_list|,
name|pid
argument_list|)
expr_stmt|;
block|}
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
literal|"%s process %P exited with code %Xul"
argument_list|,
name|name
argument_list|,
name|pid
argument_list|,
name|code
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
case|case
name|WAIT_TIMEOUT
case|:
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
literal|"the event \"%s\" was not signaled for 5s"
argument_list|,
name|ngx_master_process_event_name
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
case|case
name|WAIT_FAILED
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
literal|"WaitForSingleObject(\"%s\") failed"
argument_list|,
name|ngx_master_process_event_name
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
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
switch|switch
condition|(
name|respawn
condition|)
block|{
case|case
name|NGX_PROCESS_RESPAWN
case|:
name|ngx_processes
index|[
name|s
index|]
operator|.
name|just_spawn
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
name|just_spawn
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
name|failed
label|:
if|if
condition|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|reopen
condition|)
block|{
name|ngx_close_handle
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|reopen
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|quit
condition|)
block|{
name|ngx_close_handle
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|quit
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|term
condition|)
block|{
name|ngx_close_handle
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|term
argument_list|)
expr_stmt|;
block|}
name|TerminateProcess
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|handle
argument_list|,
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|handle
condition|)
block|{
name|ngx_close_handle
argument_list|(
name|ngx_processes
index|[
name|s
index|]
operator|.
name|handle
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_INVALID_PID
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
name|STARTUPINFO
name|si
decl_stmt|;
name|PROCESS_INFORMATION
name|pi
decl_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|si
argument_list|,
sizeof|sizeof
argument_list|(
name|STARTUPINFO
argument_list|)
argument_list|)
expr_stmt|;
name|si
operator|.
name|cb
operator|=
sizeof|sizeof
argument_list|(
name|STARTUPINFO
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|pi
argument_list|,
sizeof|sizeof
argument_list|(
name|PROCESS_INFORMATION
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|CreateProcess
argument_list|(
name|ctx
operator|->
name|path
argument_list|,
name|ctx
operator|->
name|args
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|CREATE_NO_WINDOW
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
operator|&
name|si
argument_list|,
operator|&
name|pi
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"CreateProcess(\"%s\") failed"
argument_list|,
name|ngx_argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
name|ctx
operator|->
name|child
operator|=
name|pi
operator|.
name|hProcess
expr_stmt|;
if|if
condition|(
name|CloseHandle
argument_list|(
name|pi
operator|.
name|hThread
argument_list|)
operator|==
literal|0
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
literal|"CloseHandle(pi.hThread) failed"
argument_list|)
expr_stmt|;
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
literal|"start %s process %P"
argument_list|,
name|ctx
operator|->
name|name
argument_list|,
name|pi
operator|.
name|dwProcessId
argument_list|)
expr_stmt|;
return|return
name|pi
operator|.
name|dwProcessId
return|;
block|}
end_function

end_unit

