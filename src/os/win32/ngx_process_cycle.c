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
file|<ngx_event.h>
end_include

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|ngx_int_t     ngx_process; ngx_pid_t     ngx_pid; ngx_pid_t     ngx_new_binary; ngx_int_t     ngx_inherited;  sig_atomic_t  ngx_reap; sig_atomic_t  ngx_timer; sig_atomic_t  ngx_terminate; sig_atomic_t  ngx_quit; sig_atomic_t  ngx_noaccept; sig_atomic_t  ngx_reconfigure; sig_atomic_t  ngx_reopen; sig_atomic_t  ngx_change_binary;
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_master_process_cycle (ngx_cycle_t * cycle,ngx_master_ctx_t * ctx)
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
block|{
block|}
end_function

end_unit

