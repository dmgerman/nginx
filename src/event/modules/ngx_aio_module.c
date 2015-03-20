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

begin_decl_stmt
specifier|extern
name|ngx_event_module_t
name|ngx_kqueue_module_ctx
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_aio_init
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
name|ngx_aio_done
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
name|ngx_aio_add_event
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
name|ngx_aio_del_event
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
name|ngx_aio_del_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_aio_process_events
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

begin_decl_stmt
DECL|variable|ngx_os_aio
name|ngx_os_io_t
name|ngx_os_aio
init|=
block|{
name|ngx_aio_read
block|,
name|ngx_aio_read_chain
block|,
name|NULL
block|,
name|ngx_aio_write
block|,
name|ngx_aio_write_chain
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|aio_name
specifier|static
name|ngx_str_t
name|aio_name
init|=
name|ngx_string
argument_list|(
literal|"aio"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_aio_module_ctx
name|ngx_event_module_t
name|ngx_aio_module_ctx
init|=
block|{
operator|&
name|aio_name
block|,
name|NULL
block|,
comment|/* create configuration */
name|NULL
block|,
comment|/* init configuration */
block|{
name|ngx_aio_add_event
block|,
comment|/* add an event */
name|ngx_aio_del_event
block|,
comment|/* delete an event */
name|NULL
block|,
comment|/* enable an event */
name|NULL
block|,
comment|/* disable an event */
name|NULL
block|,
comment|/* add an connection */
name|ngx_aio_del_connection
block|,
comment|/* delete an connection */
name|NULL
block|,
comment|/* trigger a notify */
name|ngx_aio_process_events
block|,
comment|/* process the events */
name|ngx_aio_init
block|,
comment|/* init the events */
name|ngx_aio_done
comment|/* done the events */
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_aio_module
name|ngx_module_t
name|ngx_aio_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_aio_module_ctx
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
end_if

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_aio_init (ngx_cycle_t * cycle,ngx_msec_t timer)
name|ngx_aio_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|)
block|{
if|if
condition|(
name|ngx_kqueue_module_ctx
operator|.
name|actions
operator|.
name|init
argument_list|(
name|cycle
argument_list|,
name|timer
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_io
operator|=
name|ngx_os_aio
expr_stmt|;
name|ngx_event_flags
operator|=
name|NGX_USE_AIO_EVENT
expr_stmt|;
name|ngx_event_actions
operator|=
name|ngx_aio_module_ctx
operator|.
name|actions
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_aio_done (ngx_cycle_t * cycle)
name|ngx_aio_done
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_kqueue_module_ctx
operator|.
name|actions
operator|.
name|done
argument_list|(
name|cycle
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* the event adding and deleting are needed for the listening sockets */
end_comment

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_aio_add_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_aio_add_event
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
return|return
name|ngx_kqueue_module_ctx
operator|.
name|actions
operator|.
name|add
argument_list|(
name|ev
argument_list|,
name|event
argument_list|,
name|flags
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_aio_del_event (ngx_event_t * ev,ngx_int_t event,ngx_uint_t flags)
name|ngx_aio_del_event
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
return|return
name|ngx_kqueue_module_ctx
operator|.
name|actions
operator|.
name|del
argument_list|(
name|ev
argument_list|,
name|event
argument_list|,
name|flags
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_aio_del_connection (ngx_connection_t * c,ngx_uint_t flags)
name|ngx_aio_del_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
if|if
condition|(
name|c
operator|->
name|read
operator|->
name|active
operator|==
literal|0
operator|&&
name|c
operator|->
name|write
operator|->
name|active
operator|==
literal|0
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
name|NGX_CLOSE_EVENT
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|rc
operator|=
name|aio_cancel
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"aio_cancel: %d"
argument_list|,
name|rc
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|AIO_CANCELED
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|active
operator|=
literal|0
expr_stmt|;
name|c
operator|->
name|write
operator|->
name|active
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|AIO_ALLDONE
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|active
operator|=
literal|0
expr_stmt|;
name|c
operator|->
name|write
operator|->
name|active
operator|=
literal|0
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"aio_cancel() returned AIO_ALLDONE"
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|rc
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"aio_cancel() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|AIO_NOTCANCELED
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"aio_cancel() returned AIO_NOTCANCELED"
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

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_aio_process_events (ngx_cycle_t * cycle,ngx_msec_t timer,ngx_uint_t flags)
name|ngx_aio_process_events
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
return|return
name|ngx_kqueue_module_ctx
operator|.
name|actions
operator|.
name|process_events
argument_list|(
name|cycle
argument_list|,
name|timer
argument_list|,
name|flags
argument_list|)
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* NGX_HAVE_KQUEUE */
end_comment

end_unit

