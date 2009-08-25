begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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
name|NGX_TEST_BUILD_DEVPOLL
operator|)
end_if

begin_comment
comment|/* Solaris declarations */
end_comment

begin_define
DECL|macro|POLLREMOVE
define|#
directive|define
name|POLLREMOVE
value|0x0800
end_define

begin_define
DECL|macro|DP_POLL
define|#
directive|define
name|DP_POLL
value|0xD001
end_define

begin_define
DECL|macro|DP_ISPOLLED
define|#
directive|define
name|DP_ISPOLLED
value|0xD002
end_define

begin_struct
DECL|struct|dvpoll
struct|struct
name|dvpoll
block|{
DECL|member|dp_fds
name|struct
name|pollfd
modifier|*
name|dp_fds
decl_stmt|;
DECL|member|dp_nfds
name|int
name|dp_nfds
decl_stmt|;
DECL|member|dp_timeout
name|int
name|dp_timeout
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2c30a1a50108
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
DECL|typedef|ngx_devpoll_conf_t
block|}
name|ngx_devpoll_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_devpoll_init
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

begin_function_decl
specifier|static
name|void
name|ngx_devpoll_done
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
name|ngx_devpoll_add_event
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
name|ngx_devpoll_del_event
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
name|ngx_devpoll_set_event
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
name|ngx_devpoll_process_events
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
name|void
modifier|*
name|ngx_devpoll_create_conf
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
name|ngx_devpoll_init_conf
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
DECL|variable|dp
specifier|static
name|int
name|dp
init|=
operator|-
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|change_list
DECL|variable|event_list
specifier|static
name|struct
name|pollfd
modifier|*
name|change_list
decl_stmt|,
modifier|*
name|event_list
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|nchanges
DECL|variable|max_changes
DECL|variable|nevents
specifier|static
name|ngx_uint_t
name|nchanges
decl_stmt|,
name|max_changes
decl_stmt|,
name|nevents
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|change_index
specifier|static
name|ngx_event_t
modifier|*
modifier|*
name|change_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|devpoll_name
specifier|static
name|ngx_str_t
name|devpoll_name
init|=
name|ngx_string
argument_list|(
literal|"/dev/poll"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_devpoll_commands
specifier|static
name|ngx_command_t
name|ngx_devpoll_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"devpoll_changes"
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
name|ngx_devpoll_conf_t
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
literal|"devpoll_events"
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
name|ngx_devpoll_conf_t
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
DECL|variable|ngx_devpoll_module_ctx
name|ngx_event_module_t
name|ngx_devpoll_module_ctx
init|=
block|{
operator|&
name|devpoll_name
block|,
name|ngx_devpoll_create_conf
block|,
comment|/* create configuration */
name|ngx_devpoll_init_conf
block|,
comment|/* init configuration */
block|{
name|ngx_devpoll_add_event
block|,
comment|/* add an event */
name|ngx_devpoll_del_event
block|,
comment|/* delete an event */
name|ngx_devpoll_add_event
block|,
comment|/* enable an event */
name|ngx_devpoll_del_event
block|,
comment|/* disable an event */
name|NULL
block|,
comment|/* add an connection */
name|NULL
block|,
comment|/* delete an connection */
name|NULL
block|,
comment|/* process the changes */
name|ngx_devpoll_process_events
block|,
comment|/* process the events */
name|ngx_devpoll_init
block|,
comment|/* init the events */
name|ngx_devpoll_done
block|,
comment|/* done the events */
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_devpoll_module
name|ngx_module_t
name|ngx_devpoll_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_devpoll_module_ctx
block|,
comment|/* module context */
name|ngx_devpoll_commands
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
DECL|function|ngx_devpoll_init (ngx_cycle_t * cycle,ngx_msec_t timer)
name|ngx_devpoll_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|)
block|{
name|size_t
name|n
decl_stmt|;
name|ngx_devpoll_conf_t
modifier|*
name|dpcf
decl_stmt|;
name|dpcf
operator|=
name|ngx_event_get_conf
argument_list|(
name|cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_devpoll_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|dp
operator|==
operator|-
literal|1
condition|)
block|{
name|dp
operator|=
name|open
argument_list|(
literal|"/dev/poll"
argument_list|,
name|O_RDWR
argument_list|)
expr_stmt|;
if|if
condition|(
name|dp
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
literal|"open(/dev/poll) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
if|if
condition|(
name|max_changes
operator|<
name|dpcf
operator|->
name|changes
condition|)
block|{
if|if
condition|(
name|nchanges
condition|)
block|{
name|n
operator|=
name|nchanges
operator|*
sizeof|sizeof
argument_list|(
expr|struct
name|pollfd
argument_list|)
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|dp
argument_list|,
name|change_list
argument_list|,
name|n
argument_list|)
operator|!=
operator|(
name|ssize_t
operator|)
name|n
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
literal|"write(/dev/poll) failed"
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
sizeof|sizeof
argument_list|(
expr|struct
name|pollfd
argument_list|)
operator|*
name|dpcf
operator|->
name|changes
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
if|if
condition|(
name|change_index
condition|)
block|{
name|ngx_free
argument_list|(
name|change_index
argument_list|)
expr_stmt|;
block|}
name|change_index
operator|=
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_event_t
operator|*
argument_list|)
operator|*
name|dpcf
operator|->
name|changes
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|change_index
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
name|dpcf
operator|->
name|changes
expr_stmt|;
if|if
condition|(
name|nevents
operator|<
name|dpcf
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
sizeof|sizeof
argument_list|(
expr|struct
name|pollfd
argument_list|)
operator|*
name|dpcf
operator|->
name|events
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
name|nevents
operator|=
name|dpcf
operator|->
name|events
expr_stmt|;
name|ngx_io
operator|=
name|ngx_os_io
expr_stmt|;
name|ngx_event_actions
operator|=
name|ngx_devpoll_module_ctx
operator|.
name|actions
expr_stmt|;
name|ngx_event_flags
operator|=
name|NGX_USE_LEVEL_EVENT
operator||
name|NGX_USE_FD_EVENT
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_devpoll_done (ngx_cycle_t * cycle)
name|ngx_devpoll_done
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
name|dp
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
literal|"close(/dev/poll) failed"
argument_list|)
expr_stmt|;
block|}
name|dp
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
name|ngx_free
argument_list|(
name|change_index
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
name|change_index
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
DECL|function|ngx_devpoll_add_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_devpoll_add_event
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
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_READ_EVENT
operator|!=
name|POLLIN
operator|)
name|event
operator|=
operator|(
name|event
operator|==
name|NGX_READ_EVENT
operator|)
condition|?
name|POLLIN
else|:
name|POLLOUT
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
name|c
operator|=
name|ev
operator|->
name|data
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
literal|"devpoll add event: fd:%d ev:%04Xi"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|event
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|ev
operator|->
name|active
operator|=
literal|1
expr_stmt|;
return|return
name|ngx_devpoll_set_event
argument_list|(
name|ev
argument_list|,
name|event
argument_list|,
literal|0
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_devpoll_del_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_devpoll_del_event
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
name|ngx_event_t
modifier|*
name|e
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
if|#
directive|if
operator|(
name|NGX_READ_EVENT
operator|!=
name|POLLIN
operator|)
name|event
operator|=
operator|(
name|event
operator|==
name|NGX_READ_EVENT
operator|)
condition|?
name|POLLIN
else|:
name|POLLOUT
expr_stmt|;
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
literal|"devpoll del event: fd:%d ev:%04Xi"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|event
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_devpoll_set_event
argument_list|(
name|ev
argument_list|,
name|POLLREMOVE
argument_list|,
name|flags
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ev
operator|->
name|active
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|flags
operator|&
name|NGX_CLOSE_EVENT
condition|)
block|{
name|e
operator|=
operator|(
name|event
operator|==
name|POLLIN
operator|)
condition|?
name|c
operator|->
name|write
else|:
name|c
operator|->
name|read
expr_stmt|;
if|if
condition|(
name|e
condition|)
block|{
name|e
operator|->
name|active
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
comment|/* restore the pair event if it exists */
if|if
condition|(
name|event
operator|==
name|POLLIN
condition|)
block|{
name|e
operator|=
name|c
operator|->
name|write
expr_stmt|;
name|event
operator|=
name|POLLOUT
expr_stmt|;
block|}
else|else
block|{
name|e
operator|=
name|c
operator|->
name|read
expr_stmt|;
name|event
operator|=
name|POLLIN
expr_stmt|;
block|}
if|if
condition|(
name|e
operator|&&
name|e
operator|->
name|active
condition|)
block|{
return|return
name|ngx_devpoll_set_event
argument_list|(
name|e
argument_list|,
name|event
argument_list|,
literal|0
argument_list|)
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_devpoll_set_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_devpoll_set_event
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
name|size_t
name|n
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
literal|"devpoll fd:%d ev:%04Xi fl:%04Xi"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|event
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
literal|"/dev/pool change list is filled up"
argument_list|)
expr_stmt|;
name|n
operator|=
name|nchanges
operator|*
sizeof|sizeof
argument_list|(
expr|struct
name|pollfd
argument_list|)
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|dp
argument_list|,
name|change_list
argument_list|,
name|n
argument_list|)
operator|!=
operator|(
name|ssize_t
operator|)
name|n
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
literal|"write(/dev/poll) failed"
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
name|change_list
index|[
name|nchanges
index|]
operator|.
name|fd
operator|=
name|c
operator|->
name|fd
expr_stmt|;
name|change_list
index|[
name|nchanges
index|]
operator|.
name|events
operator|=
operator|(
name|short
operator|)
name|event
expr_stmt|;
name|change_list
index|[
name|nchanges
index|]
operator|.
name|revents
operator|=
literal|0
expr_stmt|;
name|change_index
index|[
name|nchanges
index|]
operator|=
name|ev
expr_stmt|;
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
name|NGX_CLOSE_EVENT
condition|)
block|{
name|n
operator|=
name|nchanges
operator|*
sizeof|sizeof
argument_list|(
expr|struct
name|pollfd
argument_list|)
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|dp
argument_list|,
name|change_list
argument_list|,
name|n
argument_list|)
operator|!=
operator|(
name|ssize_t
operator|)
name|n
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
literal|"write(/dev/poll) failed"
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

begin_function
name|ngx_int_t
DECL|function|ngx_devpoll_process_events (ngx_cycle_t * cycle,ngx_msec_t timer,ngx_uint_t flags)
name|ngx_devpoll_process_events
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
name|revents
decl_stmt|,
name|rc
decl_stmt|;
name|size_t
name|n
decl_stmt|;
name|ngx_fd_t
name|fd
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_int_t
name|i
decl_stmt|;
name|ngx_uint_t
name|level
decl_stmt|;
name|ngx_event_t
modifier|*
name|rev
decl_stmt|,
modifier|*
name|wev
decl_stmt|,
modifier|*
modifier|*
name|queue
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|struct
name|pollfd
name|pfd
decl_stmt|;
name|struct
name|dvpoll
name|dvp
decl_stmt|;
comment|/* NGX_TIMER_INFINITE == INFTIM */
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
literal|"devpoll timer: %M"
argument_list|,
name|timer
argument_list|)
expr_stmt|;
if|if
condition|(
name|nchanges
condition|)
block|{
name|n
operator|=
name|nchanges
operator|*
sizeof|sizeof
argument_list|(
expr|struct
name|pollfd
argument_list|)
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|dp
argument_list|,
name|change_list
argument_list|,
name|n
argument_list|)
operator|!=
operator|(
name|ssize_t
operator|)
name|n
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
literal|"write(/dev/poll) failed"
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
name|dvp
operator|.
name|dp_fds
operator|=
name|event_list
expr_stmt|;
name|dvp
operator|.
name|dp_nfds
operator|=
operator|(
name|int
operator|)
name|nevents
expr_stmt|;
name|dvp
operator|.
name|dp_timeout
operator|=
name|timer
expr_stmt|;
name|events
operator|=
name|ioctl
argument_list|(
name|dp
argument_list|,
name|DP_POLL
argument_list|,
operator|&
name|dvp
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
condition|)
block|{
name|ngx_time_update
argument_list|(
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
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
literal|"ioctl(DP_POLL) failed"
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
literal|"ioctl(DP_POLL) returned no events without timeout"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_mutex_lock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
expr_stmt|;
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
name|fd
operator|=
name|event_list
index|[
name|i
index|]
operator|.
name|fd
expr_stmt|;
name|revents
operator|=
name|event_list
index|[
name|i
index|]
operator|.
name|revents
expr_stmt|;
name|c
operator|=
name|ngx_cycle
operator|->
name|files
index|[
name|fd
index|]
expr_stmt|;
if|if
condition|(
name|c
operator|==
name|NULL
operator|||
name|c
operator|->
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|pfd
operator|.
name|fd
operator|=
name|fd
expr_stmt|;
name|pfd
operator|.
name|events
operator|=
literal|0
expr_stmt|;
name|pfd
operator|.
name|revents
operator|=
literal|0
expr_stmt|;
name|rc
operator|=
name|ioctl
argument_list|(
name|dp
argument_list|,
name|DP_ISPOLLED
argument_list|,
operator|&
name|pfd
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|rc
condition|)
block|{
case|case
operator|-
literal|1
case|:
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
literal|"ioctl(DP_ISPOLLED) failed for socket %d, event"
argument_list|,
name|fd
argument_list|,
name|revents
argument_list|)
expr_stmt|;
break|break;
case|case
literal|0
case|:
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
literal|"phantom event %04Xd for closed and removed socket %d"
argument_list|,
name|revents
argument_list|,
name|fd
argument_list|)
expr_stmt|;
break|break;
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
literal|"unexpected event %04Xd for closed and removed socket %d, "
argument_list|,
literal|"ioctl(DP_ISPOLLED) returned rc:%d, fd:%d, event %04Xd"
argument_list|,
name|revents
argument_list|,
name|fd
argument_list|,
name|rc
argument_list|,
name|pfd
operator|.
name|fd
argument_list|,
name|pfd
operator|.
name|revents
argument_list|)
expr_stmt|;
name|pfd
operator|.
name|fd
operator|=
name|fd
expr_stmt|;
name|pfd
operator|.
name|events
operator|=
name|POLLREMOVE
expr_stmt|;
name|pfd
operator|.
name|revents
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|write
argument_list|(
name|dp
argument_list|,
operator|&
name|pfd
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|pollfd
argument_list|)
argument_list|)
operator|!=
operator|(
name|ssize_t
operator|)
sizeof|sizeof
argument_list|(
expr|struct
name|pollfd
argument_list|)
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
literal|"write(/dev/poll) for %d failed, fd"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|close
argument_list|(
name|fd
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
literal|"close(%d) failed"
argument_list|,
name|fd
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
continue|continue;
block|}
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"devpoll: fd:%d, ev:%04Xd, rev:%04Xd"
argument_list|,
name|fd
argument_list|,
name|event_list
index|[
name|i
index|]
operator|.
name|events
argument_list|,
name|revents
argument_list|)
expr_stmt|;
if|if
condition|(
name|revents
operator|&
operator|(
name|POLLERR
operator||
name|POLLHUP
operator||
name|POLLNVAL
operator|)
condition|)
block|{
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"ioctl(DP_POLL) error fd:%d ev:%04Xd rev:%04Xd"
argument_list|,
name|fd
argument_list|,
name|event_list
index|[
name|i
index|]
operator|.
name|events
argument_list|,
name|revents
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|revents
operator|&
operator|~
operator|(
name|POLLIN
operator||
name|POLLOUT
operator||
name|POLLERR
operator||
name|POLLHUP
operator||
name|POLLNVAL
operator|)
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
literal|0
argument_list|,
literal|"strange ioctl(DP_POLL) events "
literal|"fd:%d ev:%04Xd rev:%04Xd"
argument_list|,
name|fd
argument_list|,
name|event_list
index|[
name|i
index|]
operator|.
name|events
argument_list|,
name|revents
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|revents
operator|&
operator|(
name|POLLERR
operator||
name|POLLHUP
operator||
name|POLLNVAL
operator|)
operator|)
operator|&&
operator|(
name|revents
operator|&
operator|(
name|POLLIN
operator||
name|POLLOUT
operator|)
operator|)
operator|==
literal|0
condition|)
block|{
comment|/*              * if the error events were returned without POLLIN or POLLOUT,              * then add these flags to handle the events at least in one              * active handler              */
name|revents
operator||=
name|POLLIN
operator||
name|POLLOUT
expr_stmt|;
block|}
name|rev
operator|=
name|c
operator|->
name|read
expr_stmt|;
if|if
condition|(
operator|(
name|revents
operator|&
name|POLLIN
operator|)
operator|&&
name|rev
operator|->
name|active
condition|)
block|{
if|if
condition|(
operator|(
name|flags
operator|&
name|NGX_POST_THREAD_EVENTS
operator|)
operator|&&
operator|!
name|rev
operator|->
name|accept
condition|)
block|{
name|rev
operator|->
name|posted_ready
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
name|rev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
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
operator|(
name|ngx_event_t
operator|*
operator|*
operator|)
operator|(
name|rev
operator|->
name|accept
condition|?
operator|&
name|ngx_posted_accept_events
else|:
operator|&
name|ngx_posted_events
operator|)
expr_stmt|;
name|ngx_locked_post_event
argument_list|(
name|rev
argument_list|,
name|queue
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|rev
operator|->
name|handler
argument_list|(
name|rev
argument_list|)
expr_stmt|;
block|}
block|}
name|wev
operator|=
name|c
operator|->
name|write
expr_stmt|;
if|if
condition|(
operator|(
name|revents
operator|&
name|POLLOUT
operator|)
operator|&&
name|wev
operator|->
name|active
condition|)
block|{
if|if
condition|(
name|flags
operator|&
name|NGX_POST_THREAD_EVENTS
condition|)
block|{
name|wev
operator|->
name|posted_ready
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
name|wev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|flags
operator|&
name|NGX_POST_EVENTS
condition|)
block|{
name|ngx_locked_post_event
argument_list|(
name|wev
argument_list|,
operator|&
name|ngx_posted_events
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|wev
operator|->
name|handler
argument_list|(
name|wev
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|ngx_mutex_unlock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_devpoll_create_conf (ngx_cycle_t * cycle)
name|ngx_devpoll_create_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_devpoll_conf_t
modifier|*
name|dpcf
decl_stmt|;
name|dpcf
operator|=
name|ngx_palloc
argument_list|(
name|cycle
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_devpoll_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dpcf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|dpcf
operator|->
name|changes
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|dpcf
operator|->
name|events
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|dpcf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_devpoll_init_conf (ngx_cycle_t * cycle,void * conf)
name|ngx_devpoll_init_conf
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
name|ngx_devpoll_conf_t
modifier|*
name|dpcf
init|=
name|conf
decl_stmt|;
name|ngx_conf_init_uint_value
argument_list|(
name|dpcf
operator|->
name|changes
argument_list|,
literal|32
argument_list|)
expr_stmt|;
name|ngx_conf_init_uint_value
argument_list|(
name|dpcf
operator|->
name|events
argument_list|,
literal|32
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

