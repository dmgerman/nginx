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

begin_function
DECL|function|ngx_execute (ngx_cycle_t * cycle,ngx_exec_ctx_t * ctx)
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
block|{
return|return
comment|/* STUB */
literal|0
return|;
block|}
end_function

end_unit

