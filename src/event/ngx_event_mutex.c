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

begin_function
DECL|function|ngx_event_mutex_timedlock (ngx_event_mutex_t * m,ngx_msec_t timer,ngx_event_t * ev)
name|ngx_int_t
name|ngx_event_mutex_timedlock
parameter_list|(
name|ngx_event_mutex_t
modifier|*
name|m
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|,
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"lock event mutex %p lock:%XD"
argument_list|,
name|m
argument_list|,
name|m
operator|->
name|lock
argument_list|)
expr_stmt|;
if|if
condition|(
name|m
operator|->
name|lock
condition|)
block|{
if|if
condition|(
name|m
operator|->
name|events
operator|==
name|NULL
condition|)
block|{
name|m
operator|->
name|events
operator|=
name|ev
expr_stmt|;
block|}
else|else
block|{
name|m
operator|->
name|last
operator|->
name|next
operator|=
name|ev
expr_stmt|;
block|}
name|m
operator|->
name|last
operator|=
name|ev
expr_stmt|;
name|ev
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS0
operator|)
name|ev
operator|->
name|light
operator|=
literal|1
expr_stmt|;
endif|#
directive|endif
name|ngx_add_timer
argument_list|(
name|ev
argument_list|,
name|timer
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|m
operator|->
name|lock
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_mutex_unlock (ngx_event_mutex_t * m,ngx_log_t * log)
name|ngx_int_t
name|ngx_event_mutex_unlock
parameter_list|(
name|ngx_event_mutex_t
modifier|*
name|m
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_event_t
modifier|*
name|ev
decl_stmt|;
if|if
condition|(
name|m
operator|->
name|lock
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"tring to unlock the free event mutex %p"
argument_list|,
name|m
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"unlock event mutex %p, next event: %p"
argument_list|,
name|m
argument_list|,
name|m
operator|->
name|events
argument_list|)
expr_stmt|;
name|m
operator|->
name|lock
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|m
operator|->
name|events
condition|)
block|{
name|ev
operator|=
name|m
operator|->
name|events
expr_stmt|;
name|m
operator|->
name|events
operator|=
name|ev
operator|->
name|next
expr_stmt|;
name|ev
operator|->
name|next
operator|=
name|ngx_posted_events
expr_stmt|;
name|ngx_posted_events
operator|=
name|ev
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

