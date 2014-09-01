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

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_decl_stmt
DECL|variable|ngx_event_timer_mutex
name|ngx_mutex_t
modifier|*
name|ngx_event_timer_mutex
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|ngx_event_timer_rbtree
name|ngx_thread_volatile
name|ngx_rbtree_t
name|ngx_event_timer_rbtree
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_event_timer_sentinel
specifier|static
name|ngx_rbtree_node_t
name|ngx_event_timer_sentinel
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * the event timer rbtree may contain the duplicate keys, however,  * it should not be a problem, because we use the rbtree to find  * a minimum timer value only  */
end_comment

begin_function
name|ngx_int_t
DECL|function|ngx_event_timer_init (ngx_log_t * log)
name|ngx_event_timer_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_rbtree_init
argument_list|(
operator|&
name|ngx_event_timer_rbtree
argument_list|,
operator|&
name|ngx_event_timer_sentinel
argument_list|,
name|ngx_rbtree_insert_timer_value
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
if|if
condition|(
name|ngx_event_timer_mutex
condition|)
block|{
name|ngx_event_timer_mutex
operator|->
name|log
operator|=
name|log
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|ngx_event_timer_mutex
operator|=
name|ngx_mutex_init
argument_list|(
name|log
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_event_timer_mutex
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_msec_t
DECL|function|ngx_event_find_timer (void)
name|ngx_event_find_timer
parameter_list|(
name|void
parameter_list|)
block|{
name|ngx_msec_int_t
name|timer
decl_stmt|;
name|ngx_rbtree_node_t
modifier|*
name|node
decl_stmt|,
modifier|*
name|root
decl_stmt|,
modifier|*
name|sentinel
decl_stmt|;
if|if
condition|(
name|ngx_event_timer_rbtree
operator|.
name|root
operator|==
operator|&
name|ngx_event_timer_sentinel
condition|)
block|{
return|return
name|NGX_TIMER_INFINITE
return|;
block|}
name|ngx_mutex_lock
argument_list|(
name|ngx_event_timer_mutex
argument_list|)
expr_stmt|;
name|root
operator|=
name|ngx_event_timer_rbtree
operator|.
name|root
expr_stmt|;
name|sentinel
operator|=
name|ngx_event_timer_rbtree
operator|.
name|sentinel
expr_stmt|;
name|node
operator|=
name|ngx_rbtree_min
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
name|ngx_event_timer_mutex
argument_list|)
expr_stmt|;
name|timer
operator|=
operator|(
name|ngx_msec_int_t
operator|)
operator|(
name|node
operator|->
name|key
operator|-
name|ngx_current_msec
operator|)
expr_stmt|;
return|return
operator|(
name|ngx_msec_t
operator|)
operator|(
name|timer
operator|>
literal|0
condition|?
name|timer
else|:
literal|0
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_event_expire_timers (void)
name|ngx_event_expire_timers
parameter_list|(
name|void
parameter_list|)
block|{
name|ngx_event_t
modifier|*
name|ev
decl_stmt|;
name|ngx_rbtree_node_t
modifier|*
name|node
decl_stmt|,
modifier|*
name|root
decl_stmt|,
modifier|*
name|sentinel
decl_stmt|;
name|sentinel
operator|=
name|ngx_event_timer_rbtree
operator|.
name|sentinel
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|ngx_mutex_lock
argument_list|(
name|ngx_event_timer_mutex
argument_list|)
expr_stmt|;
name|root
operator|=
name|ngx_event_timer_rbtree
operator|.
name|root
expr_stmt|;
if|if
condition|(
name|root
operator|==
name|sentinel
condition|)
block|{
return|return;
block|}
name|node
operator|=
name|ngx_rbtree_min
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|)
expr_stmt|;
comment|/* node->key<= ngx_current_time */
if|if
condition|(
operator|(
name|ngx_msec_int_t
operator|)
operator|(
name|node
operator|->
name|key
operator|-
name|ngx_current_msec
operator|)
operator|<=
literal|0
condition|)
block|{
name|ev
operator|=
operator|(
name|ngx_event_t
operator|*
operator|)
operator|(
operator|(
name|char
operator|*
operator|)
name|node
operator|-
name|offsetof
argument_list|(
name|ngx_event_t
argument_list|,
name|timer
argument_list|)
operator|)
expr_stmt|;
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
literal|"event timer del: %d: %M"
argument_list|,
name|ngx_event_ident
argument_list|(
name|ev
operator|->
name|data
argument_list|)
argument_list|,
name|ev
operator|->
name|timer
operator|.
name|key
argument_list|)
expr_stmt|;
name|ngx_rbtree_delete
argument_list|(
operator|&
name|ngx_event_timer_rbtree
argument_list|,
operator|&
name|ev
operator|->
name|timer
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
name|ngx_event_timer_mutex
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
name|ev
operator|->
name|timer
operator|.
name|left
operator|=
name|NULL
expr_stmt|;
name|ev
operator|->
name|timer
operator|.
name|right
operator|=
name|NULL
expr_stmt|;
name|ev
operator|->
name|timer
operator|.
name|parent
operator|=
name|NULL
expr_stmt|;
endif|#
directive|endif
name|ev
operator|->
name|timer_set
operator|=
literal|0
expr_stmt|;
name|ev
operator|->
name|timedout
operator|=
literal|1
expr_stmt|;
name|ev
operator|->
name|handler
argument_list|(
name|ev
argument_list|)
expr_stmt|;
continue|continue;
block|}
break|break;
block|}
name|ngx_mutex_unlock
argument_list|(
name|ngx_event_timer_mutex
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

