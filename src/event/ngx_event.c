begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
file|<ngx_listen.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_define
DECL|macro|DEF_CONNECTIONS
define|#
directive|define
name|DEF_CONNECTIONS
value|1024
end_define

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_select_module
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_kqueue_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_DEVPOLL
operator|)
end_if

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_devpoll_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_AIO
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_aio_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_event_acceptex.h>
end_include

begin_include
include|#
directive|include
file|<ngx_iocp_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_events_block
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_event_use
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_event_create_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_event_init_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_event_flags
name|int
name|ngx_event_flags
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_event_actions
name|ngx_event_actions_t
name|ngx_event_actions
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_connections
name|ngx_connection_t
modifier|*
name|ngx_connections
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_read_events
DECL|variable|ngx_write_events
name|ngx_event_t
modifier|*
name|ngx_read_events
decl_stmt|,
modifier|*
name|ngx_write_events
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_event_max_module
specifier|static
name|int
name|ngx_event_max_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_event_connections
specifier|static
name|int
name|ngx_event_connections
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|events_name
specifier|static
name|ngx_str_t
name|events_name
init|=
name|ngx_string
argument_list|(
literal|"events"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|event_name
specifier|static
name|ngx_str_t
name|event_name
init|=
name|ngx_string
argument_list|(
literal|"event"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_events_commands
specifier|static
name|ngx_command_t
name|ngx_events_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"events"
argument_list|)
block|,
name|NGX_MAIN_CONF
operator||
name|NGX_CONF_BLOCK
operator||
name|NGX_CONF_NOARGS
block|,
name|ngx_events_block
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_events_module
name|ngx_module_t
name|ngx_events_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|events_name
block|,
comment|/* module context */
name|ngx_events_commands
block|,
comment|/* module directives */
name|NGX_CORE_MODULE
block|,
comment|/* module type */
name|NULL
comment|/* init module */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_event_commands
specifier|static
name|ngx_command_t
name|ngx_event_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"connections"
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
name|ngx_event_conf_t
argument_list|,
name|connections
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"use"
argument_list|)
block|,
name|NGX_EVENT_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_event_use
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"timer_queues"
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
name|ngx_event_conf_t
argument_list|,
name|timer_queues
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
DECL|variable|ngx_event_module_ctx
name|ngx_event_module_t
name|ngx_event_module_ctx
init|=
block|{
operator|&
name|event_name
block|,
name|ngx_event_create_conf
block|,
comment|/* create configuration */
name|ngx_event_init_conf
block|,
comment|/* init configuration */
block|{
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_event_module
name|ngx_module_t
name|ngx_event_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_event_module_ctx
block|,
comment|/* module context */
name|ngx_event_commands
block|,
comment|/* module directives */
name|NGX_EVENT_MODULE
block|,
comment|/* module type */
name|NULL
comment|/* init module */
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_pre_thread (ngx_array_t * ls,ngx_pool_t * pool,ngx_log_t * log)
name|int
name|ngx_pre_thread
parameter_list|(
name|ngx_array_t
modifier|*
name|ls
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|int
name|m
decl_stmt|,
name|i
decl_stmt|,
name|fd
decl_stmt|;
name|ngx_listen_t
modifier|*
name|s
decl_stmt|;
name|ngx_event_t
modifier|*
name|ev
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_event_conf_t
modifier|*
name|ecf
decl_stmt|;
name|ngx_event_module_t
modifier|*
name|module
decl_stmt|;
name|ecf
operator|=
name|ngx_event_get_conf
argument_list|(
name|ngx_event_module
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|log
argument_list|,
literal|"CONN: %d"
argument|_ ecf->connections
argument_list|)
empty_stmt|;
name|ngx_log_debug
argument_list|(
argument|log
argument_list|,
literal|"TYPE: %d"
argument|_ ecf->use
argument_list|)
empty_stmt|;
for|for
control|(
name|m
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|m
index|]
condition|;
name|m
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|m
index|]
operator|->
name|type
operator|!=
name|NGX_EVENT_MODULE
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx_index
operator|==
name|ecf
operator|->
name|use
condition|)
block|{
name|module
operator|=
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx
expr_stmt|;
if|if
condition|(
name|module
operator|->
name|actions
operator|.
name|init
argument_list|(
name|log
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
break|break;
block|}
block|}
name|ngx_test_null
argument_list|(
name|ngx_connections
argument_list|,
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_connection_t
argument_list|)
operator|*
name|ecf
operator|->
name|connections
argument_list|,
name|log
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|ngx_read_events
argument_list|,
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_event_t
argument_list|)
operator|*
name|ecf
operator|->
name|connections
argument_list|,
name|log
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|ngx_write_events
argument_list|,
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_event_t
argument_list|)
operator|*
name|ecf
operator|->
name|connections
argument_list|,
name|log
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
comment|/* for each listening socket */
name|s
operator|=
operator|(
name|ngx_listen_t
operator|*
operator|)
name|ls
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ls
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|fd
operator|=
name|s
index|[
name|i
index|]
operator|.
name|fd
expr_stmt|;
name|c
operator|=
operator|&
name|ngx_connections
index|[
name|fd
index|]
expr_stmt|;
name|ev
operator|=
operator|&
name|ngx_read_events
index|[
name|fd
index|]
expr_stmt|;
name|ngx_memzero
argument_list|(
name|c
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_connection_t
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
name|ev
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_event_t
argument_list|)
argument_list|)
expr_stmt|;
name|c
operator|->
name|fd
operator|=
name|fd
expr_stmt|;
name|c
operator|->
name|family
operator|=
name|s
index|[
name|i
index|]
operator|.
name|family
expr_stmt|;
name|c
operator|->
name|socklen
operator|=
name|s
index|[
name|i
index|]
operator|.
name|socklen
expr_stmt|;
name|c
operator|->
name|sockaddr
operator|=
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
name|s
index|[
name|i
index|]
operator|.
name|socklen
argument_list|)
expr_stmt|;
name|c
operator|->
name|addr
operator|=
name|s
index|[
name|i
index|]
operator|.
name|addr
expr_stmt|;
name|c
operator|->
name|addr_text
operator|=
name|s
index|[
name|i
index|]
operator|.
name|addr_text
expr_stmt|;
name|c
operator|->
name|addr_text_max_len
operator|=
name|s
index|[
name|i
index|]
operator|.
name|addr_text_max_len
expr_stmt|;
name|c
operator|->
name|post_accept_timeout
operator|=
name|s
index|[
name|i
index|]
operator|.
name|post_accept_timeout
expr_stmt|;
name|c
operator|->
name|handler
operator|=
name|s
index|[
name|i
index|]
operator|.
name|handler
expr_stmt|;
name|c
operator|->
name|ctx
operator|=
name|s
index|[
name|i
index|]
operator|.
name|ctx
expr_stmt|;
name|c
operator|->
name|servers
operator|=
name|s
index|[
name|i
index|]
operator|.
name|servers
expr_stmt|;
name|c
operator|->
name|log
operator|=
name|s
index|[
name|i
index|]
operator|.
name|log
expr_stmt|;
name|c
operator|->
name|pool_size
operator|=
name|s
index|[
name|i
index|]
operator|.
name|pool_size
expr_stmt|;
name|ngx_test_null
argument_list|(
name|ev
operator|->
name|log
argument_list|,
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_log_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|ev
operator|->
name|log
argument_list|,
name|c
operator|->
name|log
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_log_t
argument_list|)
argument_list|)
expr_stmt|;
name|c
operator|->
name|read
operator|=
name|ev
expr_stmt|;
name|ev
operator|->
name|data
operator|=
name|c
expr_stmt|;
name|ev
operator|->
name|index
operator|=
name|NGX_INVALID_INDEX
expr_stmt|;
if|#
directive|if
literal|0
block_content|ev->listening = 1;
endif|#
directive|endif
name|ev
operator|->
name|available
operator|=
literal|0
expr_stmt|;
if|#
directive|if
operator|(
name|HAVE_DEFERRED_ACCEPT
operator|)
name|ev
operator|->
name|deferred_accept
operator|=
name|s
index|[
name|i
index|]
operator|.
name|deferred_accept
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_HAVE_IOCP_EVENT
condition|)
block|{
name|ev
operator|->
name|event_handler
operator|=
operator|&
name|ngx_event_acceptex
expr_stmt|;
comment|/* LOOK: we call ngx_iocp_add_event() also                in ngx_event_post_acceptex() */
if|if
condition|(
name|ngx_iocp_add_event
argument_list|(
name|ev
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_event_post_acceptex
argument_list|(
operator|&
name|s
index|[
name|i
index|]
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|ev
operator|->
name|event_handler
operator|=
operator|&
name|ngx_event_accept
expr_stmt|;
block|}
else|#
directive|else
name|ev
operator|->
name|event_handler
operator|=
operator|&
name|ngx_event_accept
expr_stmt|;
name|ngx_add_event
argument_list|(
name|ev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_worker (ngx_log_t * log)
name|void
name|ngx_worker
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
for|for
control|(
init|;
condition|;
control|)
block|{
name|ngx_log_debug
argument_list|(
name|log
argument_list|,
literal|"ngx_worker cycle"
argument_list|)
expr_stmt|;
name|ngx_process_events
argument_list|(
name|log
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_events_block (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
specifier|static
name|char
modifier|*
name|ngx_events_block
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|int
name|m
decl_stmt|;
name|char
modifier|*
name|rv
decl_stmt|;
name|void
modifier|*
modifier|*
modifier|*
name|ctx
decl_stmt|;
name|ngx_conf_t
name|pcf
decl_stmt|;
name|ngx_event_module_t
modifier|*
name|module
decl_stmt|;
comment|/* count the number of the event modules and set up their indices */
name|ngx_event_max_module
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|m
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|m
index|]
condition|;
name|m
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|m
index|]
operator|->
name|type
operator|!=
name|NGX_EVENT_MODULE
condition|)
block|{
continue|continue;
block|}
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx_index
operator|=
name|ngx_event_max_module
operator|++
expr_stmt|;
block|}
name|ngx_test_null
argument_list|(
name|ctx
argument_list|,
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|void
operator|*
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
operator|*
name|ctx
argument_list|,
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|ngx_event_max_module
operator|*
sizeof|sizeof
argument_list|(
name|void
operator|*
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
operator|*
operator|(
name|void
operator|*
operator|*
operator|)
name|conf
operator|=
name|ctx
expr_stmt|;
for|for
control|(
name|m
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|m
index|]
condition|;
name|m
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|m
index|]
operator|->
name|type
operator|!=
name|NGX_EVENT_MODULE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx
expr_stmt|;
if|if
condition|(
name|module
operator|->
name|create_conf
condition|)
block|{
name|ngx_test_null
argument_list|(
operator|(
operator|*
name|ctx
operator|)
index|[
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx_index
index|]
argument_list|,
name|module
operator|->
name|create_conf
argument_list|(
name|cf
operator|->
name|pool
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
block|}
block|}
name|pcf
operator|=
operator|*
name|cf
expr_stmt|;
name|cf
operator|->
name|ctx
operator|=
name|ctx
expr_stmt|;
name|cf
operator|->
name|module_type
operator|=
name|NGX_EVENT_MODULE
expr_stmt|;
name|cf
operator|->
name|cmd_type
operator|=
name|NGX_EVENT_CONF
expr_stmt|;
name|rv
operator|=
name|ngx_conf_parse
argument_list|(
name|cf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|cf
operator|=
name|pcf
expr_stmt|;
if|if
condition|(
name|rv
operator|!=
name|NGX_CONF_OK
condition|)
return|return
name|rv
return|;
for|for
control|(
name|m
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|m
index|]
condition|;
name|m
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|m
index|]
operator|->
name|type
operator|!=
name|NGX_EVENT_MODULE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx
expr_stmt|;
if|if
condition|(
name|module
operator|->
name|init_conf
condition|)
block|{
name|rv
operator|=
name|module
operator|->
name|init_conf
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
operator|(
operator|*
name|ctx
operator|)
index|[
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx_index
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|rv
operator|!=
name|NGX_CONF_OK
condition|)
block|{
return|return
name|rv
return|;
block|}
block|}
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_use (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
specifier|static
name|char
modifier|*
name|ngx_event_use
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_event_conf_t
modifier|*
name|ecf
init|=
name|conf
decl_stmt|;
name|int
name|m
decl_stmt|;
name|ngx_str_t
modifier|*
name|args
decl_stmt|;
name|ngx_event_module_t
modifier|*
name|module
decl_stmt|;
if|if
condition|(
name|ecf
operator|->
name|use
operator|!=
name|NGX_CONF_UNSET
condition|)
block|{
return|return
literal|"is duplicate"
return|;
block|}
name|args
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|m
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|m
index|]
condition|;
name|m
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|m
index|]
operator|->
name|type
operator|!=
name|NGX_EVENT_MODULE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx
expr_stmt|;
if|if
condition|(
name|module
operator|->
name|name
operator|->
name|len
operator|==
name|args
index|[
literal|1
index|]
operator|.
name|len
condition|)
block|{
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|module
operator|->
name|name
operator|->
name|data
argument_list|,
name|args
index|[
literal|1
index|]
operator|.
name|data
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ecf
operator|->
name|use
operator|=
name|ngx_modules
index|[
name|m
index|]
operator|->
name|ctx_index
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
block|}
block|}
return|return
literal|"invalid event type"
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_create_conf (ngx_pool_t * pool)
specifier|static
name|void
modifier|*
name|ngx_event_create_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_event_conf_t
modifier|*
name|ecf
decl_stmt|;
name|ngx_test_null
argument_list|(
name|ecf
argument_list|,
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_event_conf_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ecf
operator|->
name|connections
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|ecf
operator|->
name|timer_queues
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|ecf
operator|->
name|use
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|ecf
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_init_conf (ngx_pool_t * pool,void * conf)
specifier|static
name|char
modifier|*
name|ngx_event_init_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_event_conf_t
modifier|*
name|ecf
init|=
name|conf
decl_stmt|;
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
if|#
directive|if
literal|0
block_content|if (ecf->connections != NGX_CONF_UNSET) {         ecf->connections = (ngx_max_connections< DEF_CONNECTIONS) ?                                         ngx_max_connections : DEF_CONNECTIONS;      } else if (ecf->connections> ngx_max_connections) {     }
endif|#
directive|endif
name|ngx_conf_init_value
argument_list|(
name|ecf
operator|->
name|connections
argument_list|,
name|DEF_CONNECTIONS
argument_list|)
expr_stmt|;
name|ngx_conf_init_value
argument_list|(
name|ecf
operator|->
name|use
argument_list|,
name|ngx_kqueue_module
operator|.
name|ctx_index
argument_list|)
expr_stmt|;
elif|#
directive|elif
operator|(
name|HAVE_DEVPOLL
operator|)
name|ngx_conf_init_value
argument_list|(
name|ecf
operator|->
name|connections
argument_list|,
name|DEF_CONNECTIONS
argument_list|)
expr_stmt|;
name|ngx_conf_init_value
argument_list|(
name|ecf
operator|->
name|use
argument_list|,
name|ngx_devpoll_module
operator|.
name|ctx_index
argument_list|)
expr_stmt|;
else|#
directive|else
comment|/* HAVE_SELECT */
name|ngx_conf_init_value
argument_list|(
name|ecf
operator|->
name|connections
argument_list|,
name|FD_SETSIZE
operator|<
name|DEF_CONNECTIONS
condition|?
name|FD_SETSIZE
else|:
name|DEF_CONNECTIONS
argument_list|)
expr_stmt|;
name|ngx_conf_init_value
argument_list|(
name|ecf
operator|->
name|use
argument_list|,
name|ngx_select_module
operator|.
name|ctx_index
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|ngx_conf_init_value
argument_list|(
name|ecf
operator|->
name|timer_queues
argument_list|,
literal|10
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

