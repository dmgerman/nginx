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
modifier|*
name|ngx_event_timer_rbtree
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_event_timer_sentinel
name|ngx_rbtree_t
name|ngx_event_timer_sentinel
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_event_timer_init (ngx_log_t * log)
name|ngx_int_t
name|ngx_event_timer_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
if|if
condition|(
name|ngx_event_timer_rbtree
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
name|ngx_event_timer_mutex
operator|->
name|log
operator|=
name|log
expr_stmt|;
endif|#
directive|endif
return|return
name|NGX_OK
return|;
block|}
name|ngx_event_timer_rbtree
operator|=
operator|&
name|ngx_event_timer_sentinel
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
if|if
condition|(
operator|!
operator|(
name|ngx_event_timer_mutex
operator|=
name|ngx_mutex_init
argument_list|(
name|log
argument_list|,
literal|0
argument_list|)
operator|)
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
DECL|function|ngx_event_find_timer (void)
name|ngx_msec_t
name|ngx_event_find_timer
parameter_list|(
name|void
parameter_list|)
block|{
name|ngx_msec_t
name|timer
decl_stmt|;
name|ngx_rbtree_t
modifier|*
name|node
decl_stmt|;
if|if
condition|(
name|ngx_event_timer_rbtree
operator|==
operator|&
name|ngx_event_timer_sentinel
condition|)
block|{
return|return
name|NGX_TIMER_INFINITE
return|;
block|}
if|if
condition|(
name|ngx_mutex_lock
argument_list|(
name|ngx_event_timer_mutex
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_TIMER_ERROR
return|;
block|}
name|node
operator|=
name|ngx_rbtree_min
argument_list|(
operator|(
name|ngx_rbtree_t
operator|*
operator|)
name|ngx_event_timer_rbtree
argument_list|,
operator|&
name|ngx_event_timer_sentinel
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
name|ngx_msec_t
operator|)
operator|(
name|node
operator|->
name|key
operator|*
name|NGX_TIMER_RESOLUTION
operator|-
name|ngx_elapsed_msec
operator|/
name|NGX_TIMER_RESOLUTION
operator|*
name|NGX_TIMER_RESOLUTION
operator|)
expr_stmt|;
if|#
directive|if
literal|0
block_content|(node->key * NGX_TIMER_RESOLUTION - ngx_elapsed_msec);
endif|#
directive|endif
return|return
name|timer
operator|>
literal|0
condition|?
name|timer
else|:
literal|0
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_expire_timers (ngx_msec_t timer)
name|void
name|ngx_event_expire_timers
parameter_list|(
name|ngx_msec_t
name|timer
parameter_list|)
block|{
name|ngx_event_t
modifier|*
name|ev
decl_stmt|;
name|ngx_rbtree_t
modifier|*
name|node
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|ngx_event_timer_rbtree
operator|==
operator|&
name|ngx_event_timer_sentinel
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|ngx_mutex_lock
argument_list|(
name|ngx_event_timer_mutex
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return;
block|}
name|node
operator|=
name|ngx_rbtree_min
argument_list|(
operator|(
name|ngx_rbtree_t
operator|*
operator|)
name|ngx_event_timer_rbtree
argument_list|,
operator|&
name|ngx_event_timer_sentinel
argument_list|)
expr_stmt|;
if|if
condition|(
name|node
operator|->
name|key
operator|<=
operator|(
name|ngx_msec_t
operator|)
operator|(
name|ngx_old_elapsed_msec
operator|+
name|timer
operator|)
operator|/
name|NGX_TIMER_RESOLUTION
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
name|rbtree_key
argument_list|)
operator|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
if|if
condition|(
name|ngx_trylock
argument_list|(
name|ev
operator|->
name|lock
argument_list|)
operator|==
literal|0
condition|)
block|{
break|break;
block|}
endif|#
directive|endif
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
literal|"event timer del: %d: %d"
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
name|rbtree_key
argument_list|)
expr_stmt|;
name|ngx_rbtree_delete
argument_list|(
operator|(
name|ngx_rbtree_t
operator|*
operator|*
operator|)
operator|&
name|ngx_event_timer_rbtree
argument_list|,
operator|&
name|ngx_event_timer_sentinel
argument_list|,
operator|(
name|ngx_rbtree_t
operator|*
operator|)
operator|&
name|ev
operator|->
name|rbtree_key
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
name|rbtree_left
operator|=
name|NULL
expr_stmt|;
name|ev
operator|->
name|rbtree_right
operator|=
name|NULL
expr_stmt|;
name|ev
operator|->
name|rbtree_parent
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
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
name|ngx_unlock
argument_list|(
name|ev
operator|->
name|lock
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|ngx_threaded
condition|)
block|{
if|if
condition|(
name|ngx_mutex_lock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return;
block|}
name|ngx_post_event
argument_list|(
name|ev
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|ev
operator|->
name|event_handler
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

