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
unit|ngx_int_t     ngx_process; ngx_pid_t     ngx_pid; ngx_pid_t     ngx_new_binary; ngx_int_t     ngx_inherited;  sig_atomic_t  ngx_reap; sig_atomic_t  ngx_timer;
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|ngx_threaded
name|ngx_int_t
name|ngx_threaded
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_terminate
name|sig_atomic_t
name|ngx_terminate
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_quit
name|sig_atomic_t
name|ngx_quit
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|sig_atomic_t  ngx_noaccept; sig_atomic_t  ngx_reconfigure; sig_atomic_t  ngx_reopen; sig_atomic_t  ngx_change_binary;
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
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"master mode is not supported"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|2
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_single_process_cycle (ngx_cycle_t * cycle,ngx_master_ctx_t * ctx)
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
block|{
name|ngx_int_t
name|i
decl_stmt|;
name|ngx_init_temp_number
argument_list|()
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|i
index|]
operator|->
name|init_process
condition|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|i
index|]
operator|->
name|init_process
argument_list|(
name|cycle
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
comment|/* fatal */
name|exit
argument_list|(
literal|2
argument_list|)
expr_stmt|;
block|}
block|}
block|}
for|for
control|(
init|;
condition|;
control|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"worker cycle"
argument_list|)
expr_stmt|;
name|ngx_process_events
argument_list|(
name|cycle
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

