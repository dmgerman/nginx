begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_decl_stmt
specifier|extern
name|ngx_mutex_t
modifier|*
name|ngx_posted_events_mutex
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_locked_post_event (ev,queue)
define|#
directive|define
name|ngx_locked_post_event
parameter_list|(
name|ev
parameter_list|,
name|queue
parameter_list|)
define|\                                                                               \
value|if (ev->prev == NULL) {                                                   \         ev->next = (ngx_event_t *) *queue;                                    \         ev->prev = (ngx_event_t **) queue;                                    \         *queue = ev;                                                          \                                                                               \         if (ev->next) {                                                       \             ev->next->prev =&ev->next;                                       \         }                                                                     \                                                                               \         ngx_log_debug1(NGX_LOG_DEBUG_CORE, ev->log, 0, "post event %p", ev);  \                                                                               \     } else  {                                                                 \         ngx_log_debug1(NGX_LOG_DEBUG_CORE, ev->log, 0,                        \                        "update posted event %p", ev);                         \     }
end_define

begin_define
DECL|macro|ngx_post_event (ev,queue)
define|#
directive|define
name|ngx_post_event
parameter_list|(
name|ev
parameter_list|,
name|queue
parameter_list|)
define|\                                                                               \
value|ngx_mutex_lock(ngx_posted_events_mutex);                                  \     ngx_locked_post_event(ev, queue);                                         \     ngx_mutex_unlock(ngx_posted_events_mutex);
end_define

begin_define
DECL|macro|ngx_delete_posted_event (ev)
define|#
directive|define
name|ngx_delete_posted_event
parameter_list|(
name|ev
parameter_list|)
define|\                                                                               \
value|*(ev->prev) = ev->next;                                                   \                                                                               \     if (ev->next) {                                                           \         ev->next->prev = ev->prev;                                            \     }                                                                         \                                                                               \     ev->prev = NULL;                                                          \     ngx_log_debug1(NGX_LOG_DEBUG_CORE, ev->log, 0,                            \                    "delete posted event %p", ev);
end_define

begin_function_decl
name|void
name|ngx_event_process_posted
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_thread_volatile
name|ngx_event_t
modifier|*
modifier|*
name|posted
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_wakeup_worker_thread
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

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

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|ngx_thread_volatile
name|ngx_event_t
modifier|*
name|ngx_posted_accept_events
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_thread_volatile
name|ngx_event_t
modifier|*
name|ngx_posted_events
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_POSTED_H_INCLUDED_ */
end_comment

end_unit

