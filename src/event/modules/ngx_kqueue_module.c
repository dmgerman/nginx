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

begin_typedef
DECL|struct|__anon2b9ccd1c0108
typedef|typedef
struct|struct
block|{
DECL|member|changes
name|ngx_uint_t
name|changes
decl_stmt|;
DECL|member|events
name|ngx_uint_t
name|events
decl_stmt|;
DECL|typedef|ngx_kqueue_conf_t
block|}
name|ngx_kqueue_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_kqueue_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|EVFILT_USER
end_ifdef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_kqueue_notify_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|void
name|ngx_kqueue_done
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_kqueue_add_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|ngx_int_t
name|event
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_kqueue_del_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|ngx_int_t
name|event
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_kqueue_set_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|ngx_int_t
name|filter
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|EVFILT_USER
end_ifdef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_kqueue_notify
parameter_list|(
name|ngx_event_handler_pt
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_kqueue_process_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_inline
name|void
name|ngx_kqueue_dump_event
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|struct
name|kevent
modifier|*
name|kev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_kqueue_create_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_kqueue_init_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_kqueue
name|int
name|ngx_kqueue
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|change_list
specifier|static
name|struct
name|kevent
modifier|*
name|change_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|event_list
specifier|static
name|struct
name|kevent
modifier|*
name|event_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_changes
DECL|variable|nchanges
DECL|variable|nevents
specifier|static
name|ngx_uint_t
name|max_changes
decl_stmt|,
name|nchanges
decl_stmt|,
name|nevents
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|EVFILT_USER
end_ifdef

begin_decl_stmt
DECL|variable|notify_event
specifier|static
name|ngx_event_t
name|notify_event
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|notify_kev
specifier|static
name|struct
name|kevent
name|notify_kev
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|kqueue_name
specifier|static
name|ngx_str_t
name|kqueue_name
init|=
name|ngx_string
argument_list|(
literal|"kqueue"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_kqueue_commands
specifier|static
name|ngx_command_t
name|ngx_kqueue_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"kqueue_changes"
argument_list|)
block|,
name|NGX_EVENT_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_num_slot
block|,
literal|0
block|,
name|offsetof
argument_list|(
name|ngx_kqueue_conf_t
argument_list|,
name|changes
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"kqueue_events"
argument_list|)
block|,
name|NGX_EVENT_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_num_slot
block|,
literal|0
block|,
name|offsetof
argument_list|(
name|ngx_kqueue_conf_t
argument_list|,
name|events
argument_list|)
block|,
name|NULL
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_kqueue_module_ctx
name|ngx_event_module_t
name|ngx_kqueue_module_ctx
init|=
block|{
operator|&
name|kqueue_name
block|,
name|ngx_kqueue_create_conf
block|,
comment|/* create configuration */
name|ngx_kqueue_init_conf
block|,
comment|/* init configuration */
block|{
name|ngx_kqueue_add_event
block|,
comment|/* add an event */
name|ngx_kqueue_del_event
block|,
comment|/* delete an event */
name|ngx_kqueue_add_event
block|,
comment|/* enable an event */
name|ngx_kqueue_del_event
block|,
comment|/* disable an event */
name|NULL
block|,
comment|/* add an connection */
name|NULL
block|,
comment|/* delete an connection */
ifdef|#
directive|ifdef
name|EVFILT_USER
name|ngx_kqueue_notify
block|,
comment|/* trigger a notify */
else|#
directive|else
name|NULL
block|,
comment|/* trigger a notify */
endif|#
directive|endif
name|ngx_kqueue_process_events
block|,
comment|/* process the events */
name|ngx_kqueue_init
block|,
comment|/* init the events */
name|ngx_kqueue_done
comment|/* done the events */
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_kqueue_module
name|ngx_module_t
name|ngx_kqueue_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_kqueue_module_ctx
block|,
comment|/* module context */
name|ngx_kqueue_commands
block|,
comment|/* module directives */
name|NGX_EVENT_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|NULL
block|,
comment|/* init module */
name|NULL
block|,
comment|/* init process */
name|NULL
block|,
comment|/* init thread */
name|NULL
block|,
comment|/* exit thread */
name|NULL
block|,
comment|/* exit process */
name|NULL
block|,
comment|/* exit master */
name|NGX_MODULE_V1_PADDING
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_kqueue_init (ngx_cycle_t * cycle,ngx_msec_t timer)
name|ngx_kqueue_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|)
block|{
name|ngx_kqueue_conf_t
modifier|*
name|kcf
decl_stmt|;
name|struct
name|timespec
name|ts
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_TIMER_EVENT
operator|)
name|struct
name|kevent
name|kev
decl_stmt|;
endif|#
directive|endif
name|kcf
operator|=
name|ngx_event_get_conf
argument_list|(
name|cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_kqueue_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_kqueue
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_kqueue
operator|=
name|kqueue
argument_list|()
expr_stmt|;
if|if
condition|(
name|ngx_kqueue
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kqueue() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
ifdef|#
directive|ifdef
name|EVFILT_USER
if|if
condition|(
name|ngx_kqueue_notify_init
argument_list|(
name|cycle
operator|->
name|log
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
block|}
if|if
condition|(
name|max_changes
operator|<
name|kcf
operator|->
name|changes
condition|)
block|{
if|if
condition|(
name|nchanges
condition|)
block|{
name|ts
operator|.
name|tv_sec
operator|=
literal|0
expr_stmt|;
name|ts
operator|.
name|tv_nsec
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|kevent
argument_list|(
name|ngx_kqueue
argument_list|,
name|change_list
argument_list|,
operator|(
name|int
operator|)
name|nchanges
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
operator|&
name|ts
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kevent() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|nchanges
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|change_list
condition|)
block|{
name|ngx_free
argument_list|(
name|change_list
argument_list|)
expr_stmt|;
block|}
name|change_list
operator|=
name|ngx_alloc
argument_list|(
name|kcf
operator|->
name|changes
operator|*
sizeof|sizeof
argument_list|(
expr|struct
name|kevent
argument_list|)
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|change_list
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
name|max_changes
operator|=
name|kcf
operator|->
name|changes
expr_stmt|;
if|if
condition|(
name|nevents
operator|<
name|kcf
operator|->
name|events
condition|)
block|{
if|if
condition|(
name|event_list
condition|)
block|{
name|ngx_free
argument_list|(
name|event_list
argument_list|)
expr_stmt|;
block|}
name|event_list
operator|=
name|ngx_alloc
argument_list|(
name|kcf
operator|->
name|events
operator|*
sizeof|sizeof
argument_list|(
expr|struct
name|kevent
argument_list|)
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|event_list
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
name|ngx_event_flags
operator|=
name|NGX_USE_ONESHOT_EVENT
operator||
name|NGX_USE_KQUEUE_EVENT
operator||
name|NGX_USE_VNODE_EVENT
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_TIMER_EVENT
operator|)
if|if
condition|(
name|timer
condition|)
block|{
name|kev
operator|.
name|ident
operator|=
literal|0
expr_stmt|;
name|kev
operator|.
name|filter
operator|=
name|EVFILT_TIMER
expr_stmt|;
name|kev
operator|.
name|flags
operator|=
name|EV_ADD
operator||
name|EV_ENABLE
expr_stmt|;
name|kev
operator|.
name|fflags
operator|=
literal|0
expr_stmt|;
name|kev
operator|.
name|data
operator|=
name|timer
expr_stmt|;
name|kev
operator|.
name|udata
operator|=
literal|0
expr_stmt|;
name|ts
operator|.
name|tv_sec
operator|=
literal|0
expr_stmt|;
name|ts
operator|.
name|tv_nsec
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|kevent
argument_list|(
name|ngx_kqueue
argument_list|,
operator|&
name|kev
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
operator|&
name|ts
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kevent(EVFILT_TIMER) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_event_flags
operator||=
name|NGX_USE_TIMER_EVENT
expr_stmt|;
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_CLEAR_EVENT
operator|)
name|ngx_event_flags
operator||=
name|NGX_USE_CLEAR_EVENT
expr_stmt|;
else|#
directive|else
name|ngx_event_flags
operator||=
name|NGX_USE_LEVEL_EVENT
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_LOWAT_EVENT
operator|)
name|ngx_event_flags
operator||=
name|NGX_USE_LOWAT_EVENT
expr_stmt|;
endif|#
directive|endif
name|nevents
operator|=
name|kcf
operator|->
name|events
expr_stmt|;
name|ngx_io
operator|=
name|ngx_os_io
expr_stmt|;
name|ngx_event_actions
operator|=
name|ngx_kqueue_module_ctx
operator|.
name|actions
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|EVFILT_USER
end_ifdef

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_kqueue_notify_init (ngx_log_t * log)
name|ngx_kqueue_notify_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|notify_kev
operator|.
name|ident
operator|=
literal|0
expr_stmt|;
name|notify_kev
operator|.
name|filter
operator|=
name|EVFILT_USER
expr_stmt|;
name|notify_kev
operator|.
name|data
operator|=
literal|0
expr_stmt|;
name|notify_kev
operator|.
name|flags
operator|=
name|EV_ADD
operator||
name|EV_CLEAR
expr_stmt|;
name|notify_kev
operator|.
name|fflags
operator|=
literal|0
expr_stmt|;
name|notify_kev
operator|.
name|udata
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|kevent
argument_list|(
name|ngx_kqueue
argument_list|,
operator|&
name|notify_kev
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kevent(EVFILT_USER, EV_ADD) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|notify_event
operator|.
name|active
operator|=
literal|1
expr_stmt|;
name|notify_event
operator|.
name|log
operator|=
name|log
expr_stmt|;
name|notify_kev
operator|.
name|flags
operator|=
literal|0
expr_stmt|;
name|notify_kev
operator|.
name|fflags
operator|=
name|NOTE_TRIGGER
expr_stmt|;
name|notify_kev
operator|.
name|udata
operator|=
name|NGX_KQUEUE_UDATA_T
argument_list|(
operator|(
name|uintptr_t
operator|)
operator|&
name|notify_event
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|void
DECL|function|ngx_kqueue_done (ngx_cycle_t * cycle)
name|ngx_kqueue_done
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
if|if
condition|(
name|close
argument_list|(
name|ngx_kqueue
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kqueue close() failed"
argument_list|)
expr_stmt|;
block|}
name|ngx_kqueue
operator|=
operator|-
literal|1
expr_stmt|;
name|ngx_free
argument_list|(
name|change_list
argument_list|)
expr_stmt|;
name|ngx_free
argument_list|(
name|event_list
argument_list|)
expr_stmt|;
name|change_list
operator|=
name|NULL
expr_stmt|;
name|event_list
operator|=
name|NULL
expr_stmt|;
name|max_changes
operator|=
literal|0
expr_stmt|;
name|nchanges
operator|=
literal|0
expr_stmt|;
name|nevents
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_kqueue_add_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_kqueue_add_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|ngx_int_t
name|event
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
if|#
directive|if
literal|0
block_content|ngx_event_t       *e;     ngx_connection_t  *c;
endif|#
directive|endif
name|ev
operator|->
name|active
operator|=
literal|1
expr_stmt|;
name|ev
operator|->
name|disabled
operator|=
literal|0
expr_stmt|;
name|ev
operator|->
name|oneshot
operator|=
operator|(
name|flags
operator|&
name|NGX_ONESHOT_EVENT
operator|)
condition|?
literal|1
else|:
literal|0
expr_stmt|;
if|#
directive|if
literal|0
block_content|if (ev->index< nchanges&& ((uintptr_t) change_list[ev->index].udata& (uintptr_t) ~1)             == (uintptr_t) ev)     {         if (change_list[ev->index].flags == EV_DISABLE) {
comment|/*              * if the EV_DISABLE is still not passed to a kernel              * we will not pass it              */
block_content|ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,                            "kevent activated: %d: ft:%i",                            ngx_event_ident(ev->data), event);              if (ev->index< --nchanges) {                 e = (ngx_event_t *)                     ((uintptr_t) change_list[nchanges].udata& (uintptr_t) ~1);                 change_list[ev->index] = change_list[nchanges];                 e->index = ev->index;             }              return NGX_OK;         }          c = ev->data;          ngx_log_error(NGX_LOG_ALERT, ev->log, 0,                       "previous event on #%d were not passed in kernel", c->fd);          return NGX_ERROR;     }
endif|#
directive|endif
name|rc
operator|=
name|ngx_kqueue_set_event
argument_list|(
name|ev
argument_list|,
name|event
argument_list|,
name|EV_ADD
operator||
name|EV_ENABLE
operator||
name|flags
argument_list|)
expr_stmt|;
return|return
name|rc
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_kqueue_del_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_kqueue_del_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|ngx_int_t
name|event
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_event_t
modifier|*
name|e
decl_stmt|;
name|ev
operator|->
name|active
operator|=
literal|0
expr_stmt|;
name|ev
operator|->
name|disabled
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ev
operator|->
name|index
operator|<
name|nchanges
operator|&&
operator|(
operator|(
name|uintptr_t
operator|)
name|change_list
index|[
name|ev
operator|->
name|index
index|]
operator|.
name|udata
operator|&
operator|(
name|uintptr_t
operator|)
operator|~
literal|1
operator|)
operator|==
operator|(
name|uintptr_t
operator|)
name|ev
condition|)
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
literal|"kevent deleted: %d: ft:%i"
argument_list|,
name|ngx_event_ident
argument_list|(
name|ev
operator|->
name|data
argument_list|)
argument_list|,
name|event
argument_list|)
expr_stmt|;
comment|/* if the event is still not passed to a kernel we will not pass it */
name|nchanges
operator|--
expr_stmt|;
if|if
condition|(
name|ev
operator|->
name|index
operator|<
name|nchanges
condition|)
block|{
name|e
operator|=
operator|(
name|ngx_event_t
operator|*
operator|)
operator|(
operator|(
name|uintptr_t
operator|)
name|change_list
index|[
name|nchanges
index|]
operator|.
name|udata
operator|&
operator|(
name|uintptr_t
operator|)
operator|~
literal|1
operator|)
expr_stmt|;
name|change_list
index|[
name|ev
operator|->
name|index
index|]
operator|=
name|change_list
index|[
name|nchanges
index|]
expr_stmt|;
name|e
operator|->
name|index
operator|=
name|ev
operator|->
name|index
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
comment|/*      * when the file descriptor is closed the kqueue automatically deletes      * its filters so we do not need to delete explicitly the event      * before the closing the file descriptor.      */
if|if
condition|(
name|flags
operator|&
name|NGX_CLOSE_EVENT
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|flags
operator|&
name|NGX_DISABLE_EVENT
condition|)
block|{
name|ev
operator|->
name|disabled
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
name|flags
operator||=
name|EV_DELETE
expr_stmt|;
block|}
name|rc
operator|=
name|ngx_kqueue_set_event
argument_list|(
name|ev
argument_list|,
name|event
argument_list|,
name|flags
argument_list|)
expr_stmt|;
return|return
name|rc
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_kqueue_set_event (ngx_event_t * ev,ngx_int_t filter,ngx_uint_t flags)
name|ngx_kqueue_set_event
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|ngx_int_t
name|filter
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
block|{
name|struct
name|kevent
modifier|*
name|kev
decl_stmt|;
name|struct
name|timespec
name|ts
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|c
operator|=
name|ev
operator|->
name|data
expr_stmt|;
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"kevent set event: %d: ft:%i fl:%04Xi"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|filter
argument_list|,
name|flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|nchanges
operator|>=
name|max_changes
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"kqueue change list is filled up"
argument_list|)
expr_stmt|;
name|ts
operator|.
name|tv_sec
operator|=
literal|0
expr_stmt|;
name|ts
operator|.
name|tv_nsec
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|kevent
argument_list|(
name|ngx_kqueue
argument_list|,
name|change_list
argument_list|,
operator|(
name|int
operator|)
name|nchanges
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
operator|&
name|ts
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kevent() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|nchanges
operator|=
literal|0
expr_stmt|;
block|}
name|kev
operator|=
operator|&
name|change_list
index|[
name|nchanges
index|]
expr_stmt|;
name|kev
operator|->
name|ident
operator|=
name|c
operator|->
name|fd
expr_stmt|;
name|kev
operator|->
name|filter
operator|=
operator|(
name|short
operator|)
name|filter
expr_stmt|;
name|kev
operator|->
name|flags
operator|=
operator|(
name|u_short
operator|)
name|flags
expr_stmt|;
name|kev
operator|->
name|udata
operator|=
name|NGX_KQUEUE_UDATA_T
argument_list|(
operator|(
name|uintptr_t
operator|)
name|ev
operator||
name|ev
operator|->
name|instance
argument_list|)
expr_stmt|;
if|if
condition|(
name|filter
operator|==
name|EVFILT_VNODE
condition|)
block|{
name|kev
operator|->
name|fflags
operator|=
name|NOTE_DELETE
operator||
name|NOTE_WRITE
operator||
name|NOTE_EXTEND
operator||
name|NOTE_ATTRIB
operator||
name|NOTE_RENAME
if|#
directive|if
operator|(
name|__FreeBSD__
operator|==
literal|4
operator|&&
name|__FreeBSD_version
operator|>=
literal|430000
operator|)
expr|\
operator|||
name|__FreeBSD_version
operator|>=
literal|500018
operator||
name|NOTE_REVOKE
endif|#
directive|endif
expr_stmt|;
name|kev
operator|->
name|data
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_LOWAT_EVENT
operator|)
if|if
condition|(
name|flags
operator|&
name|NGX_LOWAT_EVENT
condition|)
block|{
name|kev
operator|->
name|fflags
operator|=
name|NOTE_LOWAT
expr_stmt|;
name|kev
operator|->
name|data
operator|=
name|ev
operator|->
name|available
expr_stmt|;
block|}
else|else
block|{
name|kev
operator|->
name|fflags
operator|=
literal|0
expr_stmt|;
name|kev
operator|->
name|data
operator|=
literal|0
expr_stmt|;
block|}
else|#
directive|else
name|kev
operator|->
name|fflags
operator|=
literal|0
expr_stmt|;
name|kev
operator|->
name|data
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
block|}
name|ev
operator|->
name|index
operator|=
name|nchanges
expr_stmt|;
name|nchanges
operator|++
expr_stmt|;
if|if
condition|(
name|flags
operator|&
name|NGX_FLUSH_EVENT
condition|)
block|{
name|ts
operator|.
name|tv_sec
operator|=
literal|0
expr_stmt|;
name|ts
operator|.
name|tv_nsec
operator|=
literal|0
expr_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"kevent flush"
argument_list|)
expr_stmt|;
if|if
condition|(
name|kevent
argument_list|(
name|ngx_kqueue
argument_list|,
name|change_list
argument_list|,
operator|(
name|int
operator|)
name|nchanges
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
operator|&
name|ts
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kevent() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|nchanges
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_ifdef
ifdef|#
directive|ifdef
name|EVFILT_USER
end_ifdef

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_kqueue_notify (ngx_event_handler_pt handler)
name|ngx_kqueue_notify
parameter_list|(
name|ngx_event_handler_pt
name|handler
parameter_list|)
block|{
name|notify_event
operator|.
name|handler
operator|=
name|handler
expr_stmt|;
if|if
condition|(
name|kevent
argument_list|(
name|ngx_kqueue
argument_list|,
operator|&
name|notify_kev
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|notify_event
operator|.
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"kevent(EVFILT_USER, NOTE_TRIGGER) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_kqueue_process_events (ngx_cycle_t * cycle,ngx_msec_t timer,ngx_uint_t flags)
name|ngx_kqueue_process_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
block|{
name|int
name|events
decl_stmt|,
name|n
decl_stmt|;
name|ngx_int_t
name|i
decl_stmt|,
name|instance
decl_stmt|;
name|ngx_uint_t
name|level
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_event_t
modifier|*
name|ev
decl_stmt|;
name|ngx_queue_t
modifier|*
name|queue
decl_stmt|;
name|struct
name|timespec
name|ts
decl_stmt|,
modifier|*
name|tp
decl_stmt|;
name|n
operator|=
operator|(
name|int
operator|)
name|nchanges
expr_stmt|;
name|nchanges
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|timer
operator|==
name|NGX_TIMER_INFINITE
condition|)
block|{
name|tp
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|ts
operator|.
name|tv_sec
operator|=
name|timer
operator|/
literal|1000
expr_stmt|;
name|ts
operator|.
name|tv_nsec
operator|=
operator|(
name|timer
operator|%
literal|1000
operator|)
operator|*
literal|1000000
expr_stmt|;
comment|/*          * 64-bit Darwin kernel has the bug: kernel level ts.tv_nsec is          * the int32_t while user level ts.tv_nsec is the long (64-bit),          * so on the big endian PowerPC all nanoseconds are lost.          */
if|#
directive|if
operator|(
name|NGX_DARWIN_KEVENT_BUG
operator|)
name|ts
operator|.
name|tv_nsec
operator|<<=
literal|32
expr_stmt|;
endif|#
directive|endif
name|tp
operator|=
operator|&
name|ts
expr_stmt|;
block|}
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"kevent timer: %M, changes: %d"
argument_list|,
name|timer
argument_list|,
name|n
argument_list|)
expr_stmt|;
name|events
operator|=
name|kevent
argument_list|(
name|ngx_kqueue
argument_list|,
name|change_list
argument_list|,
name|n
argument_list|,
name|event_list
argument_list|,
operator|(
name|int
operator|)
name|nevents
argument_list|,
name|tp
argument_list|)
expr_stmt|;
name|err
operator|=
operator|(
name|events
operator|==
operator|-
literal|1
operator|)
condition|?
name|ngx_errno
else|:
literal|0
expr_stmt|;
if|if
condition|(
name|flags
operator|&
name|NGX_UPDATE_TIME
operator|||
name|ngx_event_timer_alarm
condition|)
block|{
name|ngx_time_update
argument_list|()
expr_stmt|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"kevent events: %d"
argument_list|,
name|events
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
condition|)
block|{
if|if
condition|(
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
if|if
condition|(
name|ngx_event_timer_alarm
condition|)
block|{
name|ngx_event_timer_alarm
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|level
operator|=
name|NGX_LOG_INFO
expr_stmt|;
block|}
else|else
block|{
name|level
operator|=
name|NGX_LOG_ALERT
expr_stmt|;
block|}
name|ngx_log_error
argument_list|(
name|level
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"kevent() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|events
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|timer
operator|!=
name|NGX_TIMER_INFINITE
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"kevent() returned no events without timeout"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|events
condition|;
name|i
operator|++
control|)
block|{
name|ngx_kqueue_dump_event
argument_list|(
name|cycle
operator|->
name|log
argument_list|,
operator|&
name|event_list
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|event_list
index|[
name|i
index|]
operator|.
name|flags
operator|&
name|EV_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|event_list
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"kevent() error on %d filter:%d flags:%04Xd"
argument_list|,
name|event_list
index|[
name|i
index|]
operator|.
name|ident
argument_list|,
name|event_list
index|[
name|i
index|]
operator|.
name|filter
argument_list|,
name|event_list
index|[
name|i
index|]
operator|.
name|flags
argument_list|)
expr_stmt|;
continue|continue;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_TIMER_EVENT
operator|)
if|if
condition|(
name|event_list
index|[
name|i
index|]
operator|.
name|filter
operator|==
name|EVFILT_TIMER
condition|)
block|{
name|ngx_time_update
argument_list|()
expr_stmt|;
continue|continue;
block|}
endif|#
directive|endif
name|ev
operator|=
operator|(
name|ngx_event_t
operator|*
operator|)
name|event_list
index|[
name|i
index|]
operator|.
name|udata
expr_stmt|;
switch|switch
condition|(
name|event_list
index|[
name|i
index|]
operator|.
name|filter
condition|)
block|{
case|case
name|EVFILT_READ
case|:
case|case
name|EVFILT_WRITE
case|:
name|instance
operator|=
operator|(
name|uintptr_t
operator|)
name|ev
operator|&
literal|1
expr_stmt|;
name|ev
operator|=
operator|(
name|ngx_event_t
operator|*
operator|)
operator|(
operator|(
name|uintptr_t
operator|)
name|ev
operator|&
operator|(
name|uintptr_t
operator|)
operator|~
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|ev
operator|->
name|closed
operator|||
name|ev
operator|->
name|instance
operator|!=
name|instance
condition|)
block|{
comment|/*                  * the stale event from a file descriptor                  * that was just closed in this iteration                  */
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"kevent: stale event %p"
argument_list|,
name|ev
argument_list|)
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|ev
operator|->
name|log
operator|&&
operator|(
name|ev
operator|->
name|log
operator|->
name|log_level
operator|&
name|NGX_LOG_DEBUG_CONNECTION
operator|)
condition|)
block|{
name|ngx_kqueue_dump_event
argument_list|(
name|ev
operator|->
name|log
argument_list|,
operator|&
name|event_list
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ev
operator|->
name|oneshot
condition|)
block|{
name|ev
operator|->
name|active
operator|=
literal|0
expr_stmt|;
block|}
name|ev
operator|->
name|available
operator|=
name|event_list
index|[
name|i
index|]
operator|.
name|data
expr_stmt|;
if|if
condition|(
name|event_list
index|[
name|i
index|]
operator|.
name|flags
operator|&
name|EV_EOF
condition|)
block|{
name|ev
operator|->
name|pending_eof
operator|=
literal|1
expr_stmt|;
name|ev
operator|->
name|kq_errno
operator|=
name|event_list
index|[
name|i
index|]
operator|.
name|fflags
expr_stmt|;
block|}
name|ev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|EVFILT_VNODE
case|:
name|ev
operator|->
name|kq_vnode
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|EVFILT_AIO
case|:
name|ev
operator|->
name|complete
operator|=
literal|1
expr_stmt|;
name|ev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
break|break;
ifdef|#
directive|ifdef
name|EVFILT_USER
case|case
name|EVFILT_USER
case|:
break|break;
endif|#
directive|endif
default|default:
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"unexpected kevent() filter %d"
argument_list|,
name|event_list
index|[
name|i
index|]
operator|.
name|filter
argument_list|)
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|flags
operator|&
name|NGX_POST_EVENTS
condition|)
block|{
name|queue
operator|=
name|ev
operator|->
name|accept
condition|?
operator|&
name|ngx_posted_accept_events
else|:
operator|&
name|ngx_posted_events
expr_stmt|;
name|ngx_post_event
argument_list|(
name|ev
argument_list|,
name|queue
argument_list|)
expr_stmt|;
continue|continue;
block|}
name|ev
operator|->
name|handler
argument_list|(
name|ev
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_kqueue_dump_event (ngx_log_t * log,struct kevent * kev)
name|ngx_kqueue_dump_event
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|struct
name|kevent
modifier|*
name|kev
parameter_list|)
block|{
name|ngx_log_debug6
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
operator|(
name|kev
operator|->
name|ident
operator|>
literal|0x8000000
operator|&&
name|kev
operator|->
name|ident
operator|!=
operator|(
name|unsigned
operator|)
operator|-
literal|1
operator|)
condition|?
literal|"kevent: %p: ft:%d fl:%04Xd ff:%08Xd d:%d ud:%p"
else|:
literal|"kevent: %d: ft:%d fl:%04Xd ff:%08Xd d:%d ud:%p"
argument_list|,
name|kev
operator|->
name|ident
argument_list|,
name|kev
operator|->
name|filter
argument_list|,
name|kev
operator|->
name|flags
argument_list|,
name|kev
operator|->
name|fflags
argument_list|,
name|kev
operator|->
name|data
argument_list|,
name|kev
operator|->
name|udata
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_kqueue_create_conf (ngx_cycle_t * cycle)
name|ngx_kqueue_create_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_kqueue_conf_t
modifier|*
name|kcf
decl_stmt|;
name|kcf
operator|=
name|ngx_palloc
argument_list|(
name|cycle
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_kqueue_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|kcf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|kcf
operator|->
name|changes
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|kcf
operator|->
name|events
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|kcf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_kqueue_init_conf (ngx_cycle_t * cycle,void * conf)
name|ngx_kqueue_init_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_kqueue_conf_t
modifier|*
name|kcf
init|=
name|conf
decl_stmt|;
name|ngx_conf_init_uint_value
argument_list|(
name|kcf
operator|->
name|changes
argument_list|,
literal|512
argument_list|)
expr_stmt|;
name|ngx_conf_init_uint_value
argument_list|(
name|kcf
operator|->
name|events
argument_list|,
literal|512
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

