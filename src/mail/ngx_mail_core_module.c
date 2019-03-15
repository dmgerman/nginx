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

begin_include
include|#
directive|include
file|<ngx_mail.h>
end_include

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_mail_core_create_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_mail_core_create_srv_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_mail_core_merge_srv_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|parent
parameter_list|,
name|void
modifier|*
name|child
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_mail_core_server
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
name|ngx_mail_core_listen
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
name|ngx_mail_core_protocol
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
name|ngx_mail_core_error_log
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
name|ngx_mail_core_resolver
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

begin_decl_stmt
DECL|variable|ngx_mail_core_commands
specifier|static
name|ngx_command_t
name|ngx_mail_core_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"server"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_CONF_BLOCK
operator||
name|NGX_CONF_NOARGS
block|,
name|ngx_mail_core_server
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
literal|"listen"
argument_list|)
block|,
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_mail_core_listen
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"protocol"
argument_list|)
block|,
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_mail_core_protocol
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"timeout"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_msec_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_core_srv_conf_t
argument_list|,
name|timeout
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"server_name"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_core_srv_conf_t
argument_list|,
name|server_name
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"error_log"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_mail_core_error_log
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"resolver"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_mail_core_resolver
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"resolver_timeout"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_msec_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_core_srv_conf_t
argument_list|,
name|resolver_timeout
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
DECL|variable|ngx_mail_core_module_ctx
specifier|static
name|ngx_mail_module_t
name|ngx_mail_core_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* protocol */
name|ngx_mail_core_create_main_conf
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|ngx_mail_core_create_srv_conf
block|,
comment|/* create server configuration */
name|ngx_mail_core_merge_srv_conf
comment|/* merge server configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_mail_core_module
name|ngx_module_t
name|ngx_mail_core_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_mail_core_module_ctx
block|,
comment|/* module context */
name|ngx_mail_core_commands
block|,
comment|/* module directives */
name|NGX_MAIL_MODULE
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
name|void
modifier|*
DECL|function|ngx_mail_core_create_main_conf (ngx_conf_t * cf)
name|ngx_mail_core_create_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_mail_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
name|cmcf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_mail_core_main_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmcf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|ngx_array_init
argument_list|(
operator|&
name|cmcf
operator|->
name|servers
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|4
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_mail_core_srv_conf_t
operator|*
argument_list|)
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|ngx_array_init
argument_list|(
operator|&
name|cmcf
operator|->
name|listen
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|4
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_mail_listen_t
argument_list|)
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NULL
return|;
block|}
return|return
name|cmcf
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_mail_core_create_srv_conf (ngx_conf_t * cf)
name|ngx_mail_core_create_srv_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_mail_core_srv_conf_t
modifier|*
name|cscf
decl_stmt|;
name|cscf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_mail_core_srv_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cscf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
comment|/*      * set by ngx_pcalloc():      *      *     cscf->protocol = NULL;      *     cscf->error_log = NULL;      */
name|cscf
operator|->
name|timeout
operator|=
name|NGX_CONF_UNSET_MSEC
expr_stmt|;
name|cscf
operator|->
name|resolver_timeout
operator|=
name|NGX_CONF_UNSET_MSEC
expr_stmt|;
name|cscf
operator|->
name|resolver
operator|=
name|NGX_CONF_UNSET_PTR
expr_stmt|;
name|cscf
operator|->
name|file_name
operator|=
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
expr_stmt|;
name|cscf
operator|->
name|line
operator|=
name|cf
operator|->
name|conf_file
operator|->
name|line
expr_stmt|;
return|return
name|cscf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_mail_core_merge_srv_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_mail_core_merge_srv_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|parent
parameter_list|,
name|void
modifier|*
name|child
parameter_list|)
block|{
name|ngx_mail_core_srv_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_mail_core_srv_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_msec_value
argument_list|(
name|conf
operator|->
name|timeout
argument_list|,
name|prev
operator|->
name|timeout
argument_list|,
literal|60000
argument_list|)
expr_stmt|;
name|ngx_conf_merge_msec_value
argument_list|(
name|conf
operator|->
name|resolver_timeout
argument_list|,
name|prev
operator|->
name|resolver_timeout
argument_list|,
literal|30000
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|server_name
argument_list|,
name|prev
operator|->
name|server_name
argument_list|,
literal|""
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|->
name|server_name
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|conf
operator|->
name|server_name
operator|=
name|cf
operator|->
name|cycle
operator|->
name|hostname
expr_stmt|;
block|}
if|if
condition|(
name|conf
operator|->
name|protocol
operator|==
name|NULL
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"unknown mail protocol for server in %s:%ui"
argument_list|,
name|conf
operator|->
name|file_name
argument_list|,
name|conf
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|conf
operator|->
name|error_log
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|prev
operator|->
name|error_log
condition|)
block|{
name|conf
operator|->
name|error_log
operator|=
name|prev
operator|->
name|error_log
expr_stmt|;
block|}
else|else
block|{
name|conf
operator|->
name|error_log
operator|=
operator|&
name|cf
operator|->
name|cycle
operator|->
name|new_log
expr_stmt|;
block|}
block|}
name|ngx_conf_merge_ptr_value
argument_list|(
name|conf
operator|->
name|resolver
argument_list|,
name|prev
operator|->
name|resolver
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_mail_core_server (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_core_server
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
name|char
modifier|*
name|rv
decl_stmt|;
name|void
modifier|*
name|mconf
decl_stmt|;
name|ngx_uint_t
name|m
decl_stmt|;
name|ngx_conf_t
name|pcf
decl_stmt|;
name|ngx_mail_module_t
modifier|*
name|module
decl_stmt|;
name|ngx_mail_conf_ctx_t
modifier|*
name|ctx
decl_stmt|,
modifier|*
name|mail_ctx
decl_stmt|;
name|ngx_mail_core_srv_conf_t
modifier|*
name|cscf
decl_stmt|,
modifier|*
modifier|*
name|cscfp
decl_stmt|;
name|ngx_mail_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
name|ctx
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_mail_conf_ctx_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|mail_ctx
operator|=
name|cf
operator|->
name|ctx
expr_stmt|;
name|ctx
operator|->
name|main_conf
operator|=
name|mail_ctx
operator|->
name|main_conf
expr_stmt|;
comment|/* the server{}'s srv_conf */
name|ctx
operator|->
name|srv_conf
operator|=
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
operator|*
name|ngx_mail_max_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|srv_conf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
for|for
control|(
name|m
operator|=
literal|0
init|;
name|cf
operator|->
name|cycle
operator|->
name|modules
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
name|cf
operator|->
name|cycle
operator|->
name|modules
index|[
name|m
index|]
operator|->
name|type
operator|!=
name|NGX_MAIL_MODULE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
name|cf
operator|->
name|cycle
operator|->
name|modules
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
name|create_srv_conf
condition|)
block|{
name|mconf
operator|=
name|module
operator|->
name|create_srv_conf
argument_list|(
name|cf
argument_list|)
expr_stmt|;
if|if
condition|(
name|mconf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|ctx
operator|->
name|srv_conf
index|[
name|cf
operator|->
name|cycle
operator|->
name|modules
index|[
name|m
index|]
operator|->
name|ctx_index
index|]
operator|=
name|mconf
expr_stmt|;
block|}
block|}
comment|/* the server configuration context */
name|cscf
operator|=
name|ctx
operator|->
name|srv_conf
index|[
name|ngx_mail_core_module
operator|.
name|ctx_index
index|]
expr_stmt|;
name|cscf
operator|->
name|ctx
operator|=
name|ctx
expr_stmt|;
name|cmcf
operator|=
name|ctx
operator|->
name|main_conf
index|[
name|ngx_mail_core_module
operator|.
name|ctx_index
index|]
expr_stmt|;
name|cscfp
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|cmcf
operator|->
name|servers
argument_list|)
expr_stmt|;
if|if
condition|(
name|cscfp
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
operator|*
name|cscfp
operator|=
name|cscf
expr_stmt|;
comment|/* parse inside server{} */
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
name|cmd_type
operator|=
name|NGX_MAIL_SRV_CONF
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
operator|==
name|NGX_CONF_OK
operator|&&
operator|!
name|cscf
operator|->
name|listen
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no \"listen\" is defined for server in %s:%ui"
argument_list|,
name|cscf
operator|->
name|file_name
argument_list|,
name|cscf
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
return|return
name|rv
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_mail_core_listen (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_core_listen
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
name|ngx_mail_core_srv_conf_t
modifier|*
name|cscf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
name|size
decl_stmt|;
name|ngx_url_t
name|u
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|,
name|m
decl_stmt|;
name|ngx_mail_listen_t
modifier|*
name|ls
decl_stmt|,
modifier|*
name|als
decl_stmt|;
name|ngx_mail_module_t
modifier|*
name|module
decl_stmt|;
name|ngx_mail_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
name|cscf
operator|->
name|listen
operator|=
literal|1
expr_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|u
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_url_t
argument_list|)
argument_list|)
expr_stmt|;
name|u
operator|.
name|url
operator|=
name|value
index|[
literal|1
index|]
expr_stmt|;
name|u
operator|.
name|listen
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ngx_parse_url
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
operator|&
name|u
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
if|if
condition|(
name|u
operator|.
name|err
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"%s in \"%V\" of the \"listen\" directive"
argument_list|,
name|u
operator|.
name|err
argument_list|,
operator|&
name|u
operator|.
name|url
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|cmcf
operator|=
name|ngx_mail_conf_get_module_main_conf
argument_list|(
name|cf
argument_list|,
name|ngx_mail_core_module
argument_list|)
expr_stmt|;
name|ls
operator|=
name|ngx_array_push_n
argument_list|(
operator|&
name|cmcf
operator|->
name|listen
argument_list|,
name|u
operator|.
name|naddrs
argument_list|)
expr_stmt|;
if|if
condition|(
name|ls
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|ngx_memzero
argument_list|(
name|ls
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_mail_listen_t
argument_list|)
argument_list|)
expr_stmt|;
name|ls
operator|->
name|backlog
operator|=
name|NGX_LISTEN_BACKLOG
expr_stmt|;
name|ls
operator|->
name|rcvbuf
operator|=
operator|-
literal|1
expr_stmt|;
name|ls
operator|->
name|sndbuf
operator|=
operator|-
literal|1
expr_stmt|;
name|ls
operator|->
name|ctx
operator|=
name|cf
operator|->
name|ctx
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
name|ls
operator|->
name|ipv6only
operator|=
literal|1
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|cscf
operator|->
name|protocol
operator|==
name|NULL
condition|)
block|{
for|for
control|(
name|m
operator|=
literal|0
init|;
name|cf
operator|->
name|cycle
operator|->
name|modules
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
name|cf
operator|->
name|cycle
operator|->
name|modules
index|[
name|m
index|]
operator|->
name|type
operator|!=
name|NGX_MAIL_MODULE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
name|cf
operator|->
name|cycle
operator|->
name|modules
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
name|protocol
operator|==
name|NULL
condition|)
block|{
continue|continue;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|module
operator|->
name|protocol
operator|->
name|port
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|module
operator|->
name|protocol
operator|->
name|port
index|[
name|i
index|]
operator|==
name|u
operator|.
name|port
condition|)
block|{
name|cscf
operator|->
name|protocol
operator|=
name|module
operator|->
name|protocol
expr_stmt|;
break|break;
block|}
block|}
block|}
block|}
for|for
control|(
name|i
operator|=
literal|2
init|;
name|i
operator|<
name|cf
operator|->
name|args
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"bind"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ls
operator|->
name|bind
operator|=
literal|1
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|ngx_strncmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"backlog="
argument_list|,
literal|8
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ls
operator|->
name|backlog
operator|=
name|ngx_atoi
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
literal|8
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|8
argument_list|)
expr_stmt|;
name|ls
operator|->
name|bind
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ls
operator|->
name|backlog
operator|==
name|NGX_ERROR
operator|||
name|ls
operator|->
name|backlog
operator|==
literal|0
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid backlog \"%V\""
argument_list|,
operator|&
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
continue|continue;
block|}
if|if
condition|(
name|ngx_strncmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"rcvbuf="
argument_list|,
literal|7
argument_list|)
operator|==
literal|0
condition|)
block|{
name|size
operator|.
name|len
operator|=
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|7
expr_stmt|;
name|size
operator|.
name|data
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
literal|7
expr_stmt|;
name|ls
operator|->
name|rcvbuf
operator|=
name|ngx_parse_size
argument_list|(
operator|&
name|size
argument_list|)
expr_stmt|;
name|ls
operator|->
name|bind
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ls
operator|->
name|rcvbuf
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid rcvbuf \"%V\""
argument_list|,
operator|&
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
continue|continue;
block|}
if|if
condition|(
name|ngx_strncmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"sndbuf="
argument_list|,
literal|7
argument_list|)
operator|==
literal|0
condition|)
block|{
name|size
operator|.
name|len
operator|=
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|7
expr_stmt|;
name|size
operator|.
name|data
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
literal|7
expr_stmt|;
name|ls
operator|->
name|sndbuf
operator|=
name|ngx_parse_size
argument_list|(
operator|&
name|size
argument_list|)
expr_stmt|;
name|ls
operator|->
name|bind
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ls
operator|->
name|sndbuf
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid sndbuf \"%V\""
argument_list|,
operator|&
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
continue|continue;
block|}
if|if
condition|(
name|ngx_strncmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"ipv6only=o"
argument_list|,
literal|10
argument_list|)
operator|==
literal|0
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|&&
name|defined
name|IPV6_V6ONLY
operator|)
if|if
condition|(
name|ngx_strcmp
argument_list|(
operator|&
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|10
index|]
argument_list|,
literal|"n"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ls
operator|->
name|ipv6only
operator|=
literal|1
expr_stmt|;
block|}
if|else if
condition|(
name|ngx_strcmp
argument_list|(
operator|&
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|10
index|]
argument_list|,
literal|"ff"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ls
operator|->
name|ipv6only
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid ipv6only flags \"%s\""
argument_list|,
operator|&
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|9
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|ls
operator|->
name|bind
operator|=
literal|1
expr_stmt|;
continue|continue;
else|#
directive|else
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"bind ipv6only is not supported "
literal|"on this platform"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
endif|#
directive|endif
block|}
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"ssl"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_MAIL_SSL
operator|)
name|ngx_mail_ssl_conf_t
modifier|*
name|sslcf
decl_stmt|;
name|sslcf
operator|=
name|ngx_mail_conf_get_module_srv_conf
argument_list|(
name|cf
argument_list|,
name|ngx_mail_ssl_module
argument_list|)
expr_stmt|;
name|sslcf
operator|->
name|listen
operator|=
literal|1
expr_stmt|;
name|sslcf
operator|->
name|file
operator|=
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
expr_stmt|;
name|sslcf
operator|->
name|line
operator|=
name|cf
operator|->
name|conf_file
operator|->
name|line
expr_stmt|;
name|ls
operator|->
name|ssl
operator|=
literal|1
expr_stmt|;
continue|continue;
else|#
directive|else
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"the \"ssl\" parameter requires "
literal|"ngx_mail_ssl_module"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
endif|#
directive|endif
block|}
if|if
condition|(
name|ngx_strncmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"so_keepalive="
argument_list|,
literal|13
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|ngx_strcmp
argument_list|(
operator|&
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|13
index|]
argument_list|,
literal|"on"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ls
operator|->
name|so_keepalive
operator|=
literal|1
expr_stmt|;
block|}
if|else if
condition|(
name|ngx_strcmp
argument_list|(
operator|&
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|13
index|]
argument_list|,
literal|"off"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ls
operator|->
name|so_keepalive
operator|=
literal|2
expr_stmt|;
block|}
else|else
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_KEEPALIVE_TUNABLE
operator|)
name|u_char
modifier|*
name|p
decl_stmt|,
modifier|*
name|end
decl_stmt|;
name|ngx_str_t
name|s
decl_stmt|;
name|end
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
name|value
index|[
name|i
index|]
operator|.
name|len
expr_stmt|;
name|s
operator|.
name|data
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
literal|13
expr_stmt|;
name|p
operator|=
name|ngx_strlchr
argument_list|(
name|s
operator|.
name|data
argument_list|,
name|end
argument_list|,
literal|':'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
block|{
name|p
operator|=
name|end
expr_stmt|;
block|}
if|if
condition|(
name|p
operator|>
name|s
operator|.
name|data
condition|)
block|{
name|s
operator|.
name|len
operator|=
name|p
operator|-
name|s
operator|.
name|data
expr_stmt|;
name|ls
operator|->
name|tcp_keepidle
operator|=
name|ngx_parse_time
argument_list|(
operator|&
name|s
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|ls
operator|->
name|tcp_keepidle
operator|==
operator|(
name|time_t
operator|)
name|NGX_ERROR
condition|)
block|{
goto|goto
name|invalid_so_keepalive
goto|;
block|}
block|}
name|s
operator|.
name|data
operator|=
operator|(
name|p
operator|<
name|end
operator|)
condition|?
operator|(
name|p
operator|+
literal|1
operator|)
else|:
name|end
expr_stmt|;
name|p
operator|=
name|ngx_strlchr
argument_list|(
name|s
operator|.
name|data
argument_list|,
name|end
argument_list|,
literal|':'
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
block|{
name|p
operator|=
name|end
expr_stmt|;
block|}
if|if
condition|(
name|p
operator|>
name|s
operator|.
name|data
condition|)
block|{
name|s
operator|.
name|len
operator|=
name|p
operator|-
name|s
operator|.
name|data
expr_stmt|;
name|ls
operator|->
name|tcp_keepintvl
operator|=
name|ngx_parse_time
argument_list|(
operator|&
name|s
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|ls
operator|->
name|tcp_keepintvl
operator|==
operator|(
name|time_t
operator|)
name|NGX_ERROR
condition|)
block|{
goto|goto
name|invalid_so_keepalive
goto|;
block|}
block|}
name|s
operator|.
name|data
operator|=
operator|(
name|p
operator|<
name|end
operator|)
condition|?
operator|(
name|p
operator|+
literal|1
operator|)
else|:
name|end
expr_stmt|;
if|if
condition|(
name|s
operator|.
name|data
operator|<
name|end
condition|)
block|{
name|s
operator|.
name|len
operator|=
name|end
operator|-
name|s
operator|.
name|data
expr_stmt|;
name|ls
operator|->
name|tcp_keepcnt
operator|=
name|ngx_atoi
argument_list|(
name|s
operator|.
name|data
argument_list|,
name|s
operator|.
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|ls
operator|->
name|tcp_keepcnt
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|invalid_so_keepalive
goto|;
block|}
block|}
if|if
condition|(
name|ls
operator|->
name|tcp_keepidle
operator|==
literal|0
operator|&&
name|ls
operator|->
name|tcp_keepintvl
operator|==
literal|0
operator|&&
name|ls
operator|->
name|tcp_keepcnt
operator|==
literal|0
condition|)
block|{
goto|goto
name|invalid_so_keepalive
goto|;
block|}
name|ls
operator|->
name|so_keepalive
operator|=
literal|1
expr_stmt|;
else|#
directive|else
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"the \"so_keepalive\" parameter accepts "
literal|"only \"on\" or \"off\" on this platform"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
endif|#
directive|endif
block|}
name|ls
operator|->
name|bind
operator|=
literal|1
expr_stmt|;
continue|continue;
if|#
directive|if
operator|(
name|NGX_HAVE_KEEPALIVE_TUNABLE
operator|)
name|invalid_so_keepalive
label|:
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid so_keepalive value: \"%s\""
argument_list|,
operator|&
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|13
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
endif|#
directive|endif
block|}
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"the invalid \"%V\" parameter"
argument_list|,
operator|&
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|als
operator|=
name|cmcf
operator|->
name|listen
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|n
operator|=
literal|0
init|;
name|n
operator|<
name|u
operator|.
name|naddrs
condition|;
name|n
operator|++
control|)
block|{
name|ls
index|[
name|n
index|]
operator|=
name|ls
index|[
literal|0
index|]
expr_stmt|;
name|ls
index|[
name|n
index|]
operator|.
name|sockaddr
operator|=
name|u
operator|.
name|addrs
index|[
name|n
index|]
operator|.
name|sockaddr
expr_stmt|;
name|ls
index|[
name|n
index|]
operator|.
name|socklen
operator|=
name|u
operator|.
name|addrs
index|[
name|n
index|]
operator|.
name|socklen
expr_stmt|;
name|ls
index|[
name|n
index|]
operator|.
name|addr_text
operator|=
name|u
operator|.
name|addrs
index|[
name|n
index|]
operator|.
name|name
expr_stmt|;
name|ls
index|[
name|n
index|]
operator|.
name|wildcard
operator|=
name|ngx_inet_wildcard
argument_list|(
name|ls
index|[
name|n
index|]
operator|.
name|sockaddr
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
name|cmcf
operator|->
name|listen
operator|.
name|nelts
operator|-
name|u
operator|.
name|naddrs
operator|+
name|n
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_cmp_sockaddr
argument_list|(
name|als
index|[
name|i
index|]
operator|.
name|sockaddr
argument_list|,
name|als
index|[
name|i
index|]
operator|.
name|socklen
argument_list|,
name|ls
index|[
name|n
index|]
operator|.
name|sockaddr
argument_list|,
name|ls
index|[
name|n
index|]
operator|.
name|socklen
argument_list|,
literal|1
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
continue|continue;
block|}
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"duplicate \"%V\" address and port pair"
argument_list|,
operator|&
name|ls
index|[
name|n
index|]
operator|.
name|addr_text
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_mail_core_protocol (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_core_protocol
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
name|ngx_mail_core_srv_conf_t
modifier|*
name|cscf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_uint_t
name|m
decl_stmt|;
name|ngx_mail_module_t
modifier|*
name|module
decl_stmt|;
name|value
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
name|cf
operator|->
name|cycle
operator|->
name|modules
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
name|cf
operator|->
name|cycle
operator|->
name|modules
index|[
name|m
index|]
operator|->
name|type
operator|!=
name|NGX_MAIL_MODULE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
name|cf
operator|->
name|cycle
operator|->
name|modules
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
name|protocol
operator|&&
name|ngx_strcmp
argument_list|(
name|module
operator|->
name|protocol
operator|->
name|name
operator|.
name|data
argument_list|,
name|value
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
name|cscf
operator|->
name|protocol
operator|=
name|module
operator|->
name|protocol
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
block|}
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"unknown protocol \"%V\""
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_mail_core_error_log (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_core_error_log
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
name|ngx_mail_core_srv_conf_t
modifier|*
name|cscf
init|=
name|conf
decl_stmt|;
return|return
name|ngx_log_set_log
argument_list|(
name|cf
argument_list|,
operator|&
name|cscf
operator|->
name|error_log
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_mail_core_resolver (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_core_resolver
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
name|ngx_mail_core_srv_conf_t
modifier|*
name|cscf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
if|if
condition|(
name|cscf
operator|->
name|resolver
operator|!=
name|NGX_CONF_UNSET_PTR
condition|)
block|{
return|return
literal|"is duplicate"
return|;
block|}
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
literal|"off"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|cscf
operator|->
name|resolver
operator|=
name|NULL
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
name|cscf
operator|->
name|resolver
operator|=
name|ngx_resolver_create
argument_list|(
name|cf
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|,
name|cf
operator|->
name|args
operator|->
name|nelts
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|cscf
operator|->
name|resolver
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
name|char
modifier|*
DECL|function|ngx_mail_capabilities (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_capabilities
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
name|char
modifier|*
name|p
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|c
decl_stmt|,
modifier|*
name|value
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_array_t
modifier|*
name|a
decl_stmt|;
name|a
operator|=
operator|(
name|ngx_array_t
operator|*
operator|)
operator|(
name|p
operator|+
name|cmd
operator|->
name|offset
operator|)
expr_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|cf
operator|->
name|args
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|c
operator|=
name|ngx_array_push
argument_list|(
name|a
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
operator|*
name|c
operator|=
name|value
index|[
name|i
index|]
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

