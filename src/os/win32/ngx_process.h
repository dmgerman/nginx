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

begin_typedef
DECL|struct|__anon2c98423d0108
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
DECL|macro|ngx_sched_yield ()
define|#
directive|define
name|ngx_sched_yield
parameter_list|()
value|Sleep(0)
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

