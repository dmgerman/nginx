begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
name|pid_t
name|ngx_pid_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_getpid
define|#
directive|define
name|ngx_getpid
value|getpid
end_define

begin_function_decl
name|int
name|ngx_spawn_process
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_sigchld_handler
parameter_list|(
name|int
name|signo
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PROCESS_H_INCLUDED_ */
end_comment

end_unit

