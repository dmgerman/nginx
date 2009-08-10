begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_PROCESS_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_PROCESS_H_INCLUDED_
define|#
directive|define
name|_NGX_PROCESS_H_INCLUDED_
end_define

begin_typedef
DECL|typedef|ngx_pid_t
typedef|typedef
name|DWORD
name|ngx_pid_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_INVALID_PID
define|#
directive|define
name|NGX_INVALID_PID
value|0
end_define

begin_define
DECL|macro|ngx_getpid
define|#
directive|define
name|ngx_getpid
value|GetCurrentProcessId
end_define

begin_define
DECL|macro|ngx_log_pid
define|#
directive|define
name|ngx_log_pid
value|ngx_pid
end_define

begin_define
DECL|macro|NGX_PROCESS_SYNC_NAME
define|#
directive|define
name|NGX_PROCESS_SYNC_NAME
define|\
value|(sizeof("ngx_cache_manager_mutex_") + NGX_INT32_LEN)
end_define

begin_typedef
DECL|struct|__anon2c788a920108
typedef|typedef
struct|struct
block|{
DECL|member|handle
name|HANDLE
name|handle
decl_stmt|;
DECL|member|pid
name|ngx_pid_t
name|pid
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|term
name|HANDLE
name|term
decl_stmt|;
DECL|member|quit
name|HANDLE
name|quit
decl_stmt|;
DECL|member|reopen
name|HANDLE
name|reopen
decl_stmt|;
DECL|member|term_event
name|u_char
name|term_event
index|[
name|NGX_PROCESS_SYNC_NAME
index|]
decl_stmt|;
DECL|member|quit_event
name|u_char
name|quit_event
index|[
name|NGX_PROCESS_SYNC_NAME
index|]
decl_stmt|;
DECL|member|reopen_event
name|u_char
name|reopen_event
index|[
name|NGX_PROCESS_SYNC_NAME
index|]
decl_stmt|;
DECL|member|just_spawn
name|unsigned
name|just_spawn
range|:
literal|1
decl_stmt|;
DECL|member|exiting
name|unsigned
name|exiting
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_process_t
block|}
name|ngx_process_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c788a920208
typedef|typedef
struct|struct
block|{
DECL|member|path
name|char
modifier|*
name|path
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|args
name|char
modifier|*
name|args
decl_stmt|;
DECL|member|argv
name|char
modifier|*
specifier|const
modifier|*
name|argv
decl_stmt|;
DECL|member|envp
name|char
modifier|*
specifier|const
modifier|*
name|envp
decl_stmt|;
DECL|member|child
name|HANDLE
name|child
decl_stmt|;
DECL|typedef|ngx_exec_ctx_t
block|}
name|ngx_exec_ctx_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_PROCESS_SINGLE
define|#
directive|define
name|NGX_PROCESS_SINGLE
value|0
end_define

begin_define
DECL|macro|NGX_PROCESS_MASTER
define|#
directive|define
name|NGX_PROCESS_MASTER
value|1
end_define

begin_define
DECL|macro|NGX_PROCESS_WORKER
define|#
directive|define
name|NGX_PROCESS_WORKER
value|2
end_define

begin_function_decl
name|ngx_pid_t
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
function_decl|;
end_function_decl

begin_function_decl
name|ngx_pid_t
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
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_debug_point ()
define|#
directive|define
name|ngx_debug_point
parameter_list|()
end_define

begin_define
DECL|macro|ngx_sched_yield ()
define|#
directive|define
name|ngx_sched_yield
parameter_list|()
value|Sleep(0)
end_define

begin_define
DECL|macro|NGX_MAX_PROCESSES
define|#
directive|define
name|NGX_MAX_PROCESSES
value|(MAXIMUM_WAIT_OBJECTS - 4)
end_define

begin_define
DECL|macro|NGX_PROCESS_RESPAWN
define|#
directive|define
name|NGX_PROCESS_RESPAWN
value|-2
end_define

begin_define
DECL|macro|NGX_PROCESS_JUST_RESPAWN
define|#
directive|define
name|NGX_PROCESS_JUST_RESPAWN
value|-3
end_define

begin_decl_stmt
specifier|extern
name|int
name|ngx_argc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|char
modifier|*
modifier|*
name|ngx_argv
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|char
modifier|*
modifier|*
name|ngx_os_argv
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_int_t
name|ngx_last_process
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_process_t
name|ngx_processes
index|[
name|NGX_MAX_PROCESSES
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_pid_t
name|ngx_pid
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PROCESS_H_INCLUDED_ */
end_comment

end_unit

