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

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_select_init
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
name|ngx_select_done
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
name|ngx_select_add_event
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
name|ngx_select_del_event
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
name|ngx_select_process_events
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
name|ngx_select_repair_fd_sets
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
name|ngx_select_init_conf
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
DECL|variable|master_read_fd_set
specifier|static
name|fd_set
name|master_read_fd_set
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|master_write_fd_set
specifier|static
name|fd_set
name|master_write_fd_set
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|work_read_fd_set
specifier|static
name|fd_set
name|work_read_fd_set
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|work_write_fd_set
specifier|static
name|fd_set
name|work_write_fd_set
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_read
specifier|static
name|ngx_uint_t
name|max_read
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_write
specifier|static
name|ngx_uint_t
name|max_write
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|nevents
specifier|static
name|ngx_uint_t
name|nevents
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|event_index
specifier|static
name|ngx_event_t
modifier|*
modifier|*
name|event_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|select_name
specifier|static
name|ngx_str_t
name|select_name
init|=
name|ngx_string
argument_list|(
literal|"select"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_select_module_ctx
name|ngx_event_module_t
name|ngx_select_module_ctx
init|=
block|{
operator|&
name|select_name
block|,
name|NULL
block|,
comment|/* create configuration */
name|ngx_select_init_conf
block|,
comment|/* init configuration */
block|{
name|ngx_select_add_event
block|,
comment|/* add an event */
name|ngx_select_del_event
block|,
comment|/* delete an event */
name|ngx_select_add_event
block|,
comment|/* enable an event */
name|ngx_select_del_event
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
name|ngx_select_process_events
block|,
comment|/* process the events */
name|ngx_select_init
block|,
comment|/* init the events */
name|ngx_select_done
comment|/* done the events */
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_select_module
name|ngx_module_t
name|ngx_select_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_select_module_ctx
block|,
comment|/* module context */
name|NULL
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
DECL|function|ngx_select_init (ngx_cycle_t * cycle,ngx_msec_t timer)
name|ngx_select_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|)
block|{
name|ngx_event_t
modifier|*
modifier|*
name|index
decl_stmt|;
if|if
condition|(
name|event_index
operator|==
name|NULL
condition|)
block|{
name|FD_ZERO
argument_list|(
operator|&
name|master_read_fd_set
argument_list|)
expr_stmt|;
name|FD_ZERO
argument_list|(
operator|&
name|master_write_fd_set
argument_list|)
expr_stmt|;
name|nevents
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|ngx_process
operator|==
name|NGX_PROCESS_WORKER
operator|||
name|cycle
operator|->
name|old_cycle
operator|==
name|NULL
operator|||
name|cycle
operator|->
name|old_cycle
operator|->
name|connection_n
operator|<
name|cycle
operator|->
name|connection_n
condition|)
block|{
name|index
operator|=
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_event_t
operator|*
argument_list|)
operator|*
literal|2
operator|*
name|cycle
operator|->
name|connection_n
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
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
name|event_index
condition|)
block|{
name|ngx_memcpy
argument_list|(
name|index
argument_list|,
name|event_index
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_event_t
operator|*
argument_list|)
operator|*
name|nevents
argument_list|)
expr_stmt|;
name|ngx_free
argument_list|(
name|event_index
argument_list|)
expr_stmt|;
block|}
name|event_index
operator|=
name|index
expr_stmt|;
block|}
name|ngx_io
operator|=
name|ngx_os_io
expr_stmt|;
name|ngx_event_actions
operator|=
name|ngx_select_module_ctx
operator|.
name|actions
expr_stmt|;
name|ngx_event_flags
operator|=
name|NGX_USE_LEVEL_EVENT
expr_stmt|;
name|max_read
operator|=
literal|0
expr_stmt|;
name|max_write
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_select_done (ngx_cycle_t * cycle)
name|ngx_select_done
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_free
argument_list|(
name|event_index
argument_list|)
expr_stmt|;
name|event_index
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_select_add_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_select_add_event
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
literal|"select add event fd:%d ev:%i"
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
name|ev
operator|->
name|index
operator|!=
name|NGX_INVALID_INDEX
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
literal|0
argument_list|,
literal|"select event fd:%d ev:%i is already set"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|event
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
operator|(
name|event
operator|==
name|NGX_READ_EVENT
operator|&&
name|ev
operator|->
name|write
operator|)
operator|||
operator|(
name|event
operator|==
name|NGX_WRITE_EVENT
operator|&&
operator|!
name|ev
operator|->
name|write
operator|)
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
literal|0
argument_list|,
literal|"invalid select %s event fd:%d ev:%i"
argument_list|,
name|ev
operator|->
name|write
condition|?
literal|"write"
else|:
literal|"read"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|event
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
operator|(
name|event
operator|==
name|NGX_READ_EVENT
operator|)
operator|&&
operator|(
name|max_read
operator|>=
name|FD_SETSIZE
operator|)
operator|||
operator|(
name|event
operator|==
name|NGX_WRITE_EVENT
operator|)
operator|&&
operator|(
name|max_write
operator|>=
name|FD_SETSIZE
operator|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"maximum number of descriptors "
literal|"supported by select() is %d"
argument_list|,
name|FD_SETSIZE
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|event
operator|==
name|NGX_READ_EVENT
condition|)
block|{
name|FD_SET
argument_list|(
name|c
operator|->
name|fd
argument_list|,
operator|&
name|master_read_fd_set
argument_list|)
expr_stmt|;
name|max_read
operator|++
expr_stmt|;
block|}
if|else if
condition|(
name|event
operator|==
name|NGX_WRITE_EVENT
condition|)
block|{
name|FD_SET
argument_list|(
name|c
operator|->
name|fd
argument_list|,
operator|&
name|master_write_fd_set
argument_list|)
expr_stmt|;
name|max_write
operator|++
expr_stmt|;
block|}
name|ev
operator|->
name|active
operator|=
literal|1
expr_stmt|;
name|event_index
index|[
name|nevents
index|]
operator|=
name|ev
expr_stmt|;
name|ev
operator|->
name|index
operator|=
name|nevents
expr_stmt|;
name|nevents
operator|++
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_select_del_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_select_del_event
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
name|ev
operator|->
name|active
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ev
operator|->
name|index
operator|==
name|NGX_INVALID_INDEX
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
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
literal|"select del event fd:%d ev:%i"
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
name|event
operator|==
name|NGX_READ_EVENT
condition|)
block|{
name|FD_CLR
argument_list|(
name|c
operator|->
name|fd
argument_list|,
operator|&
name|master_read_fd_set
argument_list|)
expr_stmt|;
name|max_read
operator|--
expr_stmt|;
block|}
if|else if
condition|(
name|event
operator|==
name|NGX_WRITE_EVENT
condition|)
block|{
name|FD_CLR
argument_list|(
name|c
operator|->
name|fd
argument_list|,
operator|&
name|master_write_fd_set
argument_list|)
expr_stmt|;
name|max_write
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|ev
operator|->
name|index
operator|<
operator|--
name|nevents
condition|)
block|{
name|e
operator|=
name|event_index
index|[
name|nevents
index|]
expr_stmt|;
name|event_index
index|[
name|ev
operator|->
name|index
index|]
operator|=
name|e
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
name|ev
operator|->
name|index
operator|=
name|NGX_INVALID_INDEX
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_select_process_events (ngx_cycle_t * cycle,ngx_msec_t timer,ngx_uint_t flags)
name|ngx_select_process_events
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
name|ready
decl_stmt|,
name|nready
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|found
decl_stmt|;
name|ngx_event_t
modifier|*
name|ev
decl_stmt|,
modifier|*
modifier|*
name|queue
decl_stmt|;
name|struct
name|timeval
name|tv
decl_stmt|,
modifier|*
name|tp
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
if|if
condition|(
name|cycle
operator|->
name|log
operator|->
name|log_level
operator|&
name|NGX_LOG_DEBUG_ALL
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nevents
condition|;
name|i
operator|++
control|)
block|{
name|ev
operator|=
name|event_index
index|[
name|i
index|]
expr_stmt|;
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
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"select event: fd:%d wr:%d"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|ev
operator|->
name|write
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
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
name|tv
operator|.
name|tv_sec
operator|=
operator|(
name|long
operator|)
operator|(
name|timer
operator|/
literal|1000
operator|)
expr_stmt|;
name|tv
operator|.
name|tv_usec
operator|=
operator|(
name|long
operator|)
operator|(
operator|(
name|timer
operator|%
literal|1000
operator|)
operator|*
literal|1000
operator|)
expr_stmt|;
name|tp
operator|=
operator|&
name|tv
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
literal|"select timer: %M"
argument_list|,
name|timer
argument_list|)
expr_stmt|;
name|work_read_fd_set
operator|=
name|master_read_fd_set
expr_stmt|;
name|work_write_fd_set
operator|=
name|master_write_fd_set
expr_stmt|;
if|if
condition|(
name|max_read
operator|||
name|max_write
condition|)
block|{
name|ready
operator|=
name|select
argument_list|(
literal|0
argument_list|,
operator|&
name|work_read_fd_set
argument_list|,
operator|&
name|work_write_fd_set
argument_list|,
name|NULL
argument_list|,
name|tp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*          * Winsock select() requires that at least one descriptor set must be          * be non-null, and any non-null descriptor set must contain at least          * one handle to a socket.  Otherwise select() returns WSAEINVAL.          */
name|ngx_msleep
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|ready
operator|=
literal|0
expr_stmt|;
block|}
name|err
operator|=
operator|(
name|ready
operator|==
operator|-
literal|1
operator|)
condition|?
name|ngx_socket_errno
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
literal|"select ready %d"
argument_list|,
name|ready
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
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
name|err
argument_list|,
literal|"select() failed"
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|WSAENOTSOCK
condition|)
block|{
name|ngx_select_repair_fd_sets
argument_list|(
name|cycle
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|ready
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
literal|"select() returned no events without timeout"
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
name|nready
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|nevents
condition|;
name|i
operator|++
control|)
block|{
name|ev
operator|=
name|event_index
index|[
name|i
index|]
expr_stmt|;
name|c
operator|=
name|ev
operator|->
name|data
expr_stmt|;
name|found
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ev
operator|->
name|write
condition|)
block|{
if|if
condition|(
name|FD_ISSET
argument_list|(
name|c
operator|->
name|fd
argument_list|,
operator|&
name|work_write_fd_set
argument_list|)
condition|)
block|{
name|found
operator|=
literal|1
expr_stmt|;
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
literal|"select write %d"
argument_list|,
name|c
operator|->
name|fd
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|FD_ISSET
argument_list|(
name|c
operator|->
name|fd
argument_list|,
operator|&
name|work_read_fd_set
argument_list|)
condition|)
block|{
name|found
operator|=
literal|1
expr_stmt|;
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
literal|"select read %d"
argument_list|,
name|c
operator|->
name|fd
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|found
condition|)
block|{
name|ev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
name|queue
operator|=
operator|(
name|ngx_event_t
operator|*
operator|*
operator|)
operator|(
name|ev
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
name|ev
argument_list|,
name|queue
argument_list|)
expr_stmt|;
name|nready
operator|++
expr_stmt|;
block|}
block|}
name|ngx_mutex_unlock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|ready
operator|!=
name|nready
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
literal|"select ready != events: %d:%d"
argument_list|,
name|ready
argument_list|,
name|nready
argument_list|)
expr_stmt|;
name|ngx_select_repair_fd_sets
argument_list|(
name|cycle
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
name|void
DECL|function|ngx_select_repair_fd_sets (ngx_cycle_t * cycle)
name|ngx_select_repair_fd_sets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
name|u_int
name|i
decl_stmt|;
name|socklen_t
name|len
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_socket_t
name|s
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|master_read_fd_set
operator|.
name|fd_count
condition|;
name|i
operator|++
control|)
block|{
name|s
operator|=
name|master_read_fd_set
operator|.
name|fd_array
index|[
name|i
index|]
expr_stmt|;
name|len
operator|=
sizeof|sizeof
argument_list|(
name|int
argument_list|)
expr_stmt|;
if|if
condition|(
name|getsockopt
argument_list|(
name|s
argument_list|,
name|SOL_SOCKET
argument_list|,
name|SO_TYPE
argument_list|,
operator|(
name|char
operator|*
operator|)
operator|&
name|n
argument_list|,
operator|&
name|len
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"invalid descriptor #%d in read fd_set"
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|FD_CLR
argument_list|(
name|s
argument_list|,
operator|&
name|master_read_fd_set
argument_list|)
expr_stmt|;
block|}
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|master_write_fd_set
operator|.
name|fd_count
condition|;
name|i
operator|++
control|)
block|{
name|s
operator|=
name|master_write_fd_set
operator|.
name|fd_array
index|[
name|i
index|]
expr_stmt|;
name|len
operator|=
sizeof|sizeof
argument_list|(
name|int
argument_list|)
expr_stmt|;
if|if
condition|(
name|getsockopt
argument_list|(
name|s
argument_list|,
name|SOL_SOCKET
argument_list|,
name|SO_TYPE
argument_list|,
operator|(
name|char
operator|*
operator|)
operator|&
name|n
argument_list|,
operator|&
name|len
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"invalid descriptor #%d in write fd_set"
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|FD_CLR
argument_list|(
name|s
argument_list|,
operator|&
name|master_write_fd_set
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_select_init_conf (ngx_cycle_t * cycle,void * conf)
name|ngx_select_init_conf
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
name|ngx_event_conf_t
modifier|*
name|ecf
decl_stmt|;
name|ecf
operator|=
name|ngx_event_get_conf
argument_list|(
name|cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_event_core_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ecf
operator|->
name|use
operator|!=
name|ngx_select_module
operator|.
name|ctx_index
condition|)
block|{
return|return
name|NGX_CONF_OK
return|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

