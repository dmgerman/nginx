begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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

begin_define
DECL|macro|ngx_post_event (ev,q)
define|#
directive|define
name|ngx_post_event
parameter_list|(
name|ev
parameter_list|,
name|q
parameter_list|)
define|\                                                                               \
value|if (!(ev)->posted) {                                                      \         (ev)->posted = 1;                                                     \         ngx_queue_insert_tail(q,&(ev)->queue);                               \                                                                               \         ngx_log_debug1(NGX_LOG_DEBUG_CORE, (ev)->log, 0, "post event %p", ev);\                                                                               \     } else  {                                                                 \         ngx_log_debug1(NGX_LOG_DEBUG_CORE, (ev)->log, 0,                      \                        "update posted event %p", ev);                         \     }
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
value|(ev)->posted = 0;                                                         \     ngx_queue_remove(&(ev)->queue);                                           \                                                                               \     ngx_log_debug1(NGX_LOG_DEBUG_CORE, (ev)->log, 0,                          \                    "delete posted event %p", ev);
end_define

begin_function_decl
name|void
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
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_queue_t
name|ngx_posted_accept_events
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_queue_t
name|ngx_posted_next_events
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_queue_t
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

