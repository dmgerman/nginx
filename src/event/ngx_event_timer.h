begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_TIMER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_TIMER_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_TIMER_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_comment
comment|/*  * 32 bit key value resolution  *  * 1 msec - 49 days  * 10 msec - 1 years 4 months  * 50 msec - 6 years 10 months  * 100 msec - 13 years 8 months  */
end_comment

begin_define
DECL|macro|NGX_TIMER_RESOLUTION
define|#
directive|define
name|NGX_TIMER_RESOLUTION
value|50
end_define

begin_function_decl
name|int
name|ngx_event_timer_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_event_timer_done
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_msec_t
name|ngx_event_find_timer
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_event_expire_timers
parameter_list|(
name|ngx_msec_t
name|timer
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|int  ngx_event_timer_init(ngx_cycle_t *cycle); void ngx_event_timer_done(ngx_cycle_t *cycle); void ngx_event_add_timer(ngx_event_t *ev, ngx_msec_t timer); int  ngx_event_find_timer(void); void ngx_event_set_timer_delta(ngx_msec_t timer); void ngx_event_expire_timers(ngx_msec_t timer);
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|ngx_rbtree_t
modifier|*
name|ngx_event_timer_rbtree
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_rbtree_t
name|ngx_event_timer_sentinel
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_event_del_timer (ngx_event_t * ev)
name|ngx_inline
specifier|static
name|void
name|ngx_event_del_timer
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|ngx_rbtree_delete
argument_list|(
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
name|ev
operator|->
name|timer_set
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_event_add_timer (ngx_event_t * ev,ngx_msec_t timer)
name|ngx_inline
specifier|static
name|void
name|ngx_event_add_timer
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|)
block|{
if|if
condition|(
name|ev
operator|->
name|timer_set
condition|)
block|{
name|ngx_del_timer
argument_list|(
name|ev
argument_list|)
expr_stmt|;
block|}
name|ev
operator|->
name|rbtree_key
operator|=
operator|(
name|ngx_int_t
operator|)
operator|(
name|ngx_elapsed_msec
operator|+
name|timer
operator|)
operator|/
name|NGX_TIMER_RESOLUTION
expr_stmt|;
name|ngx_rbtree_insert
argument_list|(
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
name|ev
operator|->
name|timer_set
operator|=
literal|1
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_if
unit|ngx_inline static void ngx_event_del_timer(ngx_event_t *ev) {
if|#
directive|if
operator|(
name|NGX_DEBUG_EVENT
operator|)
end_if

begin_endif
unit|ngx_connection_t *c = ev->data;     ngx_log_debug(ev->log, "del timer: %d:%d" _ c->fd _ ev->write);
endif|#
directive|endif
end_endif

begin_endif
unit|if (!ev->timer_next || !ev->timer_prev) {         ngx_log_error(NGX_LOG_ALERT, ev->log, 0, "timer already deleted");         return;     }      if (ev->timer_prev) {         ev->timer_prev->timer_next = ev->timer_next;     }      if (ev->timer_next) {         ev->timer_next->timer_delta += ev->timer_delta;         ev->timer_next->timer_prev = ev->timer_prev;         ev->timer_next = NULL;     }      if (ev->timer_prev) {         ev->timer_prev = NULL;     }      ev->timer_set = 0; }
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_TIMER_H_INCLUDED_ */
end_comment

end_unit

