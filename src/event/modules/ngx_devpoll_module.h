begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_DEVPOLL_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_DEVPOLL_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_DEVPOLL_MODULE_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_function_decl
name|int
name|ngx_devpoll_init
parameter_list|(
name|int
name|max_connections
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_devpoll_add_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|int
name|event
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_devpoll_del_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|int
name|event
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_devpoll_add_timer
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_devpoll_process_events
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* DEBUG */
end_comment

begin_define
define|#
directive|define
name|POLLREMOVE
value|0x0800
end_define

begin_define
define|#
directive|define
name|DP_POLL
value|0xD001
end_define

begin_endif
unit|struct dvpoll {     struct pollfd* dp_fds;     int dp_nfds;     int dp_timeout; };
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_DEVPOLL_MODULE_H_INCLUDED_ */
end_comment

end_unit

