begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_POSTED_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_POSTED_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_POSTED_H_INCLUDED_
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

begin_typedef
DECL|typedef|ngx_posted_event_t
typedef|typedef
name|struct
name|ngx_posted_events_s
name|ngx_posted_event_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_posted_events_s
struct|struct
name|ngx_posted_events_s
block|{
DECL|member|event
name|ngx_event_t
modifier|*
name|event
decl_stmt|;
DECL|member|next
name|ngx_posted_event_t
modifier|*
name|next
decl_stmt|;
DECL|member|instance
name|unsigned
name|instance
range|:
literal|1
decl_stmt|;
DECL|member|ready
name|unsigned
name|ready
range|:
literal|1
decl_stmt|;
DECL|member|timedout
name|unsigned
name|timedout
range|:
literal|1
decl_stmt|;
DECL|member|complete
name|unsigned
name|complete
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|ngx_post_event (ev)
define|#
directive|define
name|ngx_post_event
parameter_list|(
name|ev
parameter_list|)
define|\
value|if (!ev->posted) {                                                \                 ev->next = (ngx_event_t *) ngx_posted_events;                 \                 ngx_posted_events = ev;                                       \                 ev->posted = 1;                                               \             }
end_define

begin_comment
comment|/* \    ngx_log_debug3(NGX_LOG_DEBUG_CORE, ngx_cycle->log, 0, \                "POST: %08X %08X %08X", ngx_posted_events, \                (ngx_posted_events ? ngx_posted_events->next: 0), \                ((ngx_posted_events&& ngx_posted_events->next) ? \                                ngx_posted_events->next->next: 0)); \ \ */
end_comment

begin_comment
comment|/* \ { int i; ngx_event_t *e;\   e = (ngx_event_t *) ngx_posted_events; \ for (i = 0; e&& i< 10; e = e->next, i++) { \    ngx_log_debug2(NGX_LOG_DEBUG_CORE, ngx_cycle->log, 0, \                   "POST: %d %08X", i, e);\ }} \ \ */
end_comment

begin_function_decl
name|void
name|ngx_event_process_posted
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_thread_volatile
name|ngx_event_t
modifier|*
name|ngx_posted_events
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_function_decl
name|ngx_int_t
name|ngx_event_thread_process_posted
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_mutex_t
modifier|*
name|ngx_posted_events_mutex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_cond_t
modifier|*
name|ngx_posted_events_cv
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_POSTED_H_INCLUDED_ */
end_comment

end_unit

