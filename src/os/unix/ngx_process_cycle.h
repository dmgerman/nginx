begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_PROCESS_CYCLE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_PROCESS_CYCLE_H_INCLUDED_
define|#
directive|define
name|_NGX_PROCESS_CYCLE_H_INCLUDED_
end_define

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

begin_define
DECL|macro|NGX_CMD_OPEN_CHANNEL
define|#
directive|define
name|NGX_CMD_OPEN_CHANNEL
value|1
end_define

begin_define
DECL|macro|NGX_CMD_CLOSE_CHANNEL
define|#
directive|define
name|NGX_CMD_CLOSE_CHANNEL
value|2
end_define

begin_define
DECL|macro|NGX_CMD_QUIT
define|#
directive|define
name|NGX_CMD_QUIT
value|3
end_define

begin_define
DECL|macro|NGX_CMD_TERMINATE
define|#
directive|define
name|NGX_CMD_TERMINATE
value|4
end_define

begin_define
DECL|macro|NGX_CMD_REOPEN
define|#
directive|define
name|NGX_CMD_REOPEN
value|5
end_define

begin_typedef
DECL|struct|__anon28a5f28d0108
typedef|typedef
struct|struct
block|{
DECL|member|argc
name|int
name|argc
decl_stmt|;
DECL|member|argv
name|char
modifier|*
specifier|const
modifier|*
name|argv
decl_stmt|;
DECL|typedef|ngx_master_ctx_t
block|}
name|ngx_master_ctx_t
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
name|void
name|ngx_master_process_cycle
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_master_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_single_process_cycle
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_master_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_process
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
name|ngx_new_binary
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_inherited
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_daemonized
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_threaded
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_exiting
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_reap
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_timer
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_sigio
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_quit
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_terminate
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_noaccept
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_reconfigure
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_reopen
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_change_binary
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PROCESS_CYCLE_H_INCLUDED_ */
end_comment

end_unit

