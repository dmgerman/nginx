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

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_decl_stmt
DECL|variable|ngx_posted_accept_events
name|ngx_queue_t
name|ngx_posted_accept_events
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_posted_next_events
name|ngx_queue_t
name|ngx_posted_next_events
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_posted_events
name|ngx_queue_t
name|ngx_posted_events
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|ngx_event_process_posted (ngx_cycle_t * cycle,ngx_queue_t * posted)
name|ngx_event_process_posted
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_queue_t
modifier|*
name|posted
parameter_list|)
block|{
name|ngx_queue_t
modifier|*
name|q
decl_stmt|;
name|ngx_event_t
modifier|*
name|ev
decl_stmt|;
while|while
condition|(
operator|!
name|ngx_queue_empty
argument_list|(
name|posted
argument_list|)
condition|)
block|{
name|q
operator|=
name|ngx_queue_head
argument_list|(
name|posted
argument_list|)
expr_stmt|;
name|ev
operator|=
name|ngx_queue_data
argument_list|(
name|q
argument_list|,
name|ngx_event_t
argument_list|,
name|queue
argument_list|)
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"posted event %p"
argument_list|,
name|ev
argument_list|)
expr_stmt|;
name|ngx_delete_posted_event
argument_list|(
name|ev
argument_list|)
expr_stmt|;
name|ev
operator|->
name|handler
argument_list|(
name|ev
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

