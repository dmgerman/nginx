begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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

begin_include
include|#
directive|include
file|<ngx_setaffinity.h>
end_include

begin_include
include|#
directive|include
file|<ngx_setproctitle.h>
end_include

begin_typedef
DECL|typedef|ngx_pid_t
typedef|typedef
name|pid_t
name|ngx_pid_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_INVALID_PID
define|#
directive|define
name|NGX_INVALID_PID
value|-1
end_define

begin_typedef
DECL|typedef|ngx_spawn_proc_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_spawn_proc_pt
function_decl|)
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
end_typedef

begin_typedef
DECL|struct|__anon2be49d740108
typedef|typedef
struct|struct
block|{
DECL|member|pid
name|ngx_pid_t
name|pid
decl_stmt|;
DECL|member|status
name|int
name|status
decl_stmt|;
DECL|member|channel
name|ngx_socket_t
name|channel
index|[
literal|2
index|]
decl_stmt|;
DECL|member|proc
name|ngx_spawn_proc_pt
name|proc
decl_stmt|;
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|respawn
name|unsigned
name|respawn
range|:
literal|1
decl_stmt|;
DECL|member|just_spawn
name|unsigned
name|just_spawn
range|:
literal|1
decl_stmt|;
DECL|member|detached
name|unsigned
name|detached
range|:
literal|1
decl_stmt|;
DECL|member|exiting
name|unsigned
name|exiting
range|:
literal|1
decl_stmt|;
DECL|member|exited
name|unsigned
name|exited
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_process_t
block|}
name|ngx_process_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2be49d740208
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
DECL|typedef|ngx_exec_ctx_t
block|}
name|ngx_exec_ctx_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_MAX_PROCESSES
define|#
directive|define
name|NGX_MAX_PROCESSES
value|1024
end_define

begin_define
DECL|macro|NGX_PROCESS_NORESPAWN
define|#
directive|define
name|NGX_PROCESS_NORESPAWN
value|-1
end_define

begin_define
DECL|macro|NGX_PROCESS_JUST_SPAWN
define|#
directive|define
name|NGX_PROCESS_JUST_SPAWN
value|-2
end_define

begin_define
DECL|macro|NGX_PROCESS_RESPAWN
define|#
directive|define
name|NGX_PROCESS_RESPAWN
value|-3
end_define

begin_define
DECL|macro|NGX_PROCESS_JUST_RESPAWN
define|#
directive|define
name|NGX_PROCESS_JUST_RESPAWN
value|-4
end_define

begin_define
DECL|macro|NGX_PROCESS_DETACHED
define|#
directive|define
name|NGX_PROCESS_DETACHED
value|-5
end_define

begin_define
DECL|macro|ngx_getpid
define|#
directive|define
name|ngx_getpid
value|getpid
end_define

begin_define
DECL|macro|ngx_getppid
define|#
directive|define
name|ngx_getppid
value|getppid
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|ngx_log_pid
end_ifndef

begin_define
DECL|macro|ngx_log_pid
define|#
directive|define
name|ngx_log_pid
value|ngx_pid
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|ngx_pid_t
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

begin_function_decl
name|ngx_int_t
name|ngx_init_signals
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_debug_point
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SCHED_YIELD
operator|)
end_if

begin_define
DECL|macro|ngx_sched_yield ()
define|#
directive|define
name|ngx_sched_yield
parameter_list|()
value|sched_yield()
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_sched_yield ()
define|#
directive|define
name|ngx_sched_yield
parameter_list|()
value|usleep(1)
end_define

begin_endif
endif|#
directive|endif
end_endif

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
name|ngx_pid_t
name|ngx_pid
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_pid_t
name|ngx_parent
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_socket_t
name|ngx_channel
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_int_t
name|ngx_process_slot
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PROCESS_H_INCLUDED_ */
end_comment

end_unit

