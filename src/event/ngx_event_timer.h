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
comment|/*  * 32 bit timer key value resolution  *  * 1 msec - 49 days  * 10 msec - 1 years 4 months  * 50 msec - 6 years 10 months  * 100 msec - 13 years 8 months  */
end_comment

begin_define
DECL|macro|NGX_TIMER_RESOLUTION
define|#
directive|define
name|NGX_TIMER_RESOLUTION
value|1
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|int  ngx_event_timer_init(void);
endif|#
directive|endif
end_endif

begin_comment
comment|/* STUB */
end_comment

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

begin_comment
comment|/* STUB */
end_comment

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

begin_define
DECL|macro|ngx_event_ident (p)
define|#
directive|define
name|ngx_event_ident
parameter_list|(
name|p
parameter_list|)
value|((ngx_connection_t *) (p))->fd
end_define

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
operator|/
name|NGX_TIMER_RESOLUTION
operator|*
name|NGX_TIMER_RESOLUTION
operator|+
name|timer
operator|)
operator|/
name|NGX_TIMER_RESOLUTION
expr_stmt|;
if|#
directive|if
literal|0
block_content|(ngx_elapsed_msec + timer) / NGX_TIMER_RESOLUTION;
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
literal|"event timer add: %d: %d"
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_TIMER_H_INCLUDED_ */
end_comment

end_unit

