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

begin_decl_stmt
DECL|variable|ngx_event_timer_rbtree
name|ngx_rbtree_t
modifier|*
name|ngx_event_timer_rbtree
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_event_timer_init (ngx_cycle_t * cycle)
name|int
name|ngx_event_timer_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_event_timer_rbtree
operator|=
operator|&
name|sentinel
expr_stmt|;
name|sentinel
operator|.
name|left
operator|=
operator|&
name|sentinel
expr_stmt|;
name|sentinel
operator|.
name|right
operator|=
operator|&
name|sentinel
expr_stmt|;
name|sentinel
operator|.
name|parent
operator|=
operator|&
name|sentinel
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_timer_done (ngx_cycle_t * cycle)
name|void
name|ngx_event_timer_done
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
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
name|ngx_rbtree_t
modifier|*
name|node
decl_stmt|;
name|node
operator|=
name|ngx_rbtree_min
argument_list|(
name|ngx_event_timer_rbtree
argument_list|)
expr_stmt|;
if|if
condition|(
name|node
operator|==
operator|&
name|sentinel
condition|)
block|{
return|return
literal|0
return|;
block|}
else|else
block|{
return|return
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
operator|)
return|;
block|}
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
name|node
operator|=
name|ngx_rbtree_min
argument_list|(
name|ngx_event_timer_rbtree
argument_list|)
expr_stmt|;
if|if
condition|(
name|node
operator|==
operator|&
name|sentinel
condition|)
block|{
break|break;
block|}
if|if
condition|(
operator|(
name|ngx_msec_t
operator|)
name|node
operator|->
name|key
operator|<=
operator|(
name|ngx_msec_t
operator|)
operator|(
name|ngx_elapsed_msec
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
name|ngx_del_timer
argument_list|(
name|ev
argument_list|)
expr_stmt|;
if|if
condition|(
name|ev
operator|->
name|delayed
condition|)
block|{
name|ev
operator|->
name|delayed
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ev
operator|->
name|ready
operator|==
literal|0
condition|)
block|{
continue|continue;
block|}
block|}
else|else
block|{
name|ev
operator|->
name|timedout
operator|=
literal|1
expr_stmt|;
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
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* TODO: in multithreaded enviroment all timer operations must be    protected by the single mutex */
end_comment

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static ngx_event_t  *ngx_timer_queue, ngx_temp_timer_queue; static int           ngx_expire_timers;
endif|#
directive|endif
end_endif

begin_comment
unit|static ngx_event_t  *ngx_timer_queue; static ngx_msec_t   *ngx_timer_delta; static int           ngx_timer_cur_queue; static int           ngx_timer_queue_num;   int ngx_event_timer_init(ngx_cycle_t *cycle) {     ngx_int_t          i;     ngx_msec_t        *new_delta;     ngx_event_t       *new_queue;     ngx_event_conf_t  *ecf;      ecf = ngx_event_get_conf(cycle->conf_ctx, ngx_event_core_module);      if (ngx_timer_queue_num< ecf->timer_queues) {         ngx_test_null(new_queue,                       ngx_alloc(ecf->timer_queues * sizeof(ngx_event_t),                                 cycle->log),                       NGX_ERROR);          for (i = 0; i< ngx_timer_queue_num; i++) {             new_queue[i] = ngx_timer_queue[i];         }          if (ngx_timer_queue) {             ngx_free(ngx_timer_queue);         }          ngx_timer_queue = new_queue;          ngx_test_null(new_delta,                       ngx_calloc(ecf->timer_queues * sizeof(ngx_msec_t),                                  cycle->log),                       NGX_ERROR);          for (i = 0; i< ngx_timer_queue_num; i++) {             new_delta[i] = ngx_timer_delta[i];         }          if (ngx_timer_delta) {             ngx_free(ngx_timer_delta);         }          ngx_timer_delta = new_delta;          ngx_timer_queue_num = ecf->timer_queues;         ngx_timer_cur_queue = 0;          for (
comment|/* void */
end_comment

begin_comment
unit|; i< ngx_timer_queue_num; i++) {             ngx_timer_queue[i].timer_prev =&ngx_timer_queue[i];             ngx_timer_queue[i].timer_next =&ngx_timer_queue[i];         }      } else if (ngx_timer_queue_num> ecf->timer_queues) {
comment|/* STUB */
end_comment

begin_if
unit|ngx_log_error(NGX_LOG_ALERT, cycle->log, 0, "NOT READY: timer");         exit(1);     }
if|#
directive|if
literal|0
end_if

begin_endif
unit|ngx_temp_timer_queue.timer_prev =&ngx_temp_timer_queue;     ngx_temp_timer_queue.timer_next =&ngx_temp_timer_queue;
endif|#
directive|endif
end_endif

begin_if
unit|return NGX_OK;; }   void ngx_event_timer_done(ngx_cycle_t *cycle) {     ngx_free(ngx_timer_queue);     ngx_timer_queue = NULL;      ngx_free(ngx_timer_delta);     ngx_timer_delta = NULL;      ngx_timer_queue_num = 0; }   void ngx_event_add_timer(ngx_event_t *ev, ngx_msec_t timer) {     ngx_event_t  *e, *queue;
if|#
directive|if
operator|(
name|NGX_DEBUG_EVENT
operator|)
end_if

begin_endif
unit|ngx_connection_t *c;
endif|#
directive|endif
end_endif

begin_if
unit|if (ev->timer_set) {         ngx_del_timer(ev);     }
if|#
directive|if
operator|(
name|NGX_DEBUG_EVENT
operator|)
end_if

begin_endif
unit|c = ev->data;     ngx_log_debug(ev->log, "set timer: %d:%d:%d, slot: %d" _                   c->fd _ ev->write _ timer _ ngx_timer_cur_queue);
endif|#
directive|endif
end_endif

begin_if
unit|if (ev->timer_next || ev->timer_prev) {         ngx_log_error(NGX_LOG_ALERT, ev->log, 0, "timer already set");         return;     }      queue =&ngx_timer_queue[ngx_timer_cur_queue];     timer += ngx_timer_delta[ngx_timer_cur_queue++];      if (ngx_timer_cur_queue>= ngx_timer_queue_num) {         ngx_timer_cur_queue = 0;     }
if|#
directive|if
literal|0
end_if

begin_endif
unit|if (ngx_expire_timers) {         queue =&ngx_temp_timer_queue;      } else {         queue =&ngx_timer_queue[ngx_timer_cur_queue++];          if (ngx_timer_cur_queue>= ngx_timer_queue_num) {             ngx_timer_cur_queue = 0;         }     }
endif|#
directive|endif
end_endif

begin_comment
unit|for (e = queue->timer_next;          e != queue&& timer> e->timer_delta;          e = e->timer_next)     {         timer -= e->timer_delta;     }      ev->timer_delta = timer;      ev->timer_next = e;     ev->timer_prev = e->timer_prev;      e->timer_prev->timer_next = ev;     e->timer_prev = ev;      ev->timer_set = 1;      return; }   int ngx_event_find_timer(void) {     ngx_int_t   i;     ngx_msec_t  timer;      timer = NGX_MAX_MSEC;      for (i = 0; i< ngx_timer_queue_num; i++) {         if (ngx_timer_queue[i].timer_next ==&ngx_timer_queue[i]) {             continue;         }          if (timer> ngx_timer_queue[i].timer_next->timer_delta) {             timer = ngx_timer_queue[i].timer_next->timer_delta;         }     }      if (timer == NGX_MAX_MSEC) {         return 0;     }      return timer; }   void ngx_event_set_timer_delta(ngx_msec_t timer) {     ngx_int_t  i;      for (i = 0; i< ngx_timer_queue_num; i++) {         ngx_timer_delta[i] = timer;     } }
comment|/* void ngx_event_expire_timers() */
end_comment

begin_if
unit|void ngx_event_expire_timers(ngx_msec_t timer) {     ngx_int_t     i;
if|#
directive|if
literal|0
end_if

begin_endif
unit|ngx_msec_t    delta;
endif|#
directive|endif
end_endif

begin_if
unit|ngx_event_t  *ev;
if|#
directive|if
literal|0
end_if

begin_endif
unit|ngx_expire_timers = 1;
endif|#
directive|endif
end_endif

begin_if
unit|for (i = 0; i< ngx_timer_queue_num; i++) {
if|#
directive|if
literal|0
end_if

begin_endif
unit|delta = timer;
endif|#
directive|endif
end_endif

begin_if
unit|for ( ;; ) {             ev = ngx_timer_queue[i].timer_next;              if (ev ==&ngx_timer_queue[i]) {                 break;             }              if (ev->timer_delta> ngx_timer_delta[i]) {                 ev->timer_delta -= ngx_timer_delta[i];                 break;             }              ngx_timer_delta[i] -= ev->timer_delta;
if|#
directive|if
literal|0
end_if

begin_endif
unit|if (ev->timer_delta> delta) {                 ev->timer_delta -= delta;                 break;             }              delta -= ev->timer_delta;
endif|#
directive|endif
end_endif

begin_if
unit|ngx_del_timer(ev);              if (ev->delayed) {                 ev->delayed = 0;                 if (ev->ready == 0) {                     continue;                 }              } else {                 ev->timedout = 1;             }              ev->event_handler(ev);         }          ngx_timer_delta[i] = 0;     }
if|#
directive|if
literal|0
end_if

begin_if
unit|ngx_expire_timers = 0;      if (ngx_temp_timer_queue.timer_next ==&ngx_temp_timer_queue) {         return;     }      timer = 0;      while (ngx_temp_timer_queue.timer_next !=&ngx_temp_timer_queue) {         timer += ngx_temp_timer_queue.timer_next->timer_delta;         ev = ngx_temp_timer_queue.timer_next;
if|#
directive|if
operator|(
name|NGX_DEBUG_EVENT
operator|)
end_if

begin_endif
unit|ngx_log_debug(ev->log, "process temp timer queue");
endif|#
directive|endif
end_endif

begin_endif
unit|ngx_del_timer(ev);         ngx_add_timer(ev, timer);     }
endif|#
directive|endif
end_endif

begin_endif
unit|}
endif|#
directive|endif
end_endif

end_unit

