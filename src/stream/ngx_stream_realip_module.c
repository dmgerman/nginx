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
file|<ngx_stream.h>
end_include

begin_typedef
DECL|struct|__anon29c40f010108
typedef|typedef
struct|struct
block|{
DECL|member|from
name|ngx_array_t
modifier|*
name|from
decl_stmt|;
comment|/* array of ngx_cidr_t */
DECL|typedef|ngx_stream_realip_srv_conf_t
block|}
name|ngx_stream_realip_srv_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29c40f010208
typedef|typedef
struct|struct
block|{
DECL|member|sockaddr
name|struct
name|sockaddr
modifier|*
name|sockaddr
decl_stmt|;
DECL|member|socklen
name|socklen_t
name|socklen
decl_stmt|;
DECL|member|addr_text
name|ngx_str_t
name|addr_text
decl_stmt|;
DECL|typedef|ngx_stream_realip_ctx_t
block|}
name|ngx_stream_realip_ctx_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_realip_handler
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_realip_set_addr
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_addr_t
modifier|*
name|addr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_stream_realip_from
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
name|ngx_stream_realip_create_srv_conf
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
name|ngx_stream_realip_merge_srv_conf
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
name|ngx_int_t
name|ngx_stream_realip_add_variables
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_realip_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_realip_remote_addr_variable
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_variable_value_t
modifier|*
name|v
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_realip_remote_port_variable
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_variable_value_t
modifier|*
name|v
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_stream_realip_commands
specifier|static
name|ngx_command_t
name|ngx_stream_realip_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"set_real_ip_from"
argument_list|)
block|,
name|NGX_STREAM_MAIN_CONF
operator||
name|NGX_STREAM_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_stream_realip_from
block|,
name|NGX_STREAM_SRV_CONF_OFFSET
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
DECL|variable|ngx_stream_realip_module_ctx
specifier|static
name|ngx_stream_module_t
name|ngx_stream_realip_module_ctx
init|=
block|{
name|ngx_stream_realip_add_variables
block|,
comment|/* preconfiguration */
name|ngx_stream_realip_init
block|,
comment|/* postconfiguration */
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|ngx_stream_realip_create_srv_conf
block|,
comment|/* create server configuration */
name|ngx_stream_realip_merge_srv_conf
comment|/* merge server configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_stream_realip_module
name|ngx_module_t
name|ngx_stream_realip_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_stream_realip_module_ctx
block|,
comment|/* module context */
name|ngx_stream_realip_commands
block|,
comment|/* module directives */
name|NGX_STREAM_MODULE
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

begin_decl_stmt
DECL|variable|ngx_stream_realip_vars
specifier|static
name|ngx_stream_variable_t
name|ngx_stream_realip_vars
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"realip_remote_addr"
argument_list|)
block|,
name|NULL
block|,
name|ngx_stream_realip_remote_addr_variable
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"realip_remote_port"
argument_list|)
block|,
name|NULL
block|,
name|ngx_stream_realip_remote_port_variable
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|,
block|{
name|ngx_null_string
block|,
name|NULL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_realip_handler (ngx_stream_session_t * s)
name|ngx_stream_realip_handler
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|)
block|{
name|ngx_addr_t
name|addr
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_stream_realip_srv_conf_t
modifier|*
name|rscf
decl_stmt|;
name|rscf
operator|=
name|ngx_stream_get_module_srv_conf
argument_list|(
name|s
argument_list|,
name|ngx_stream_realip_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|rscf
operator|->
name|from
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|c
operator|=
name|s
operator|->
name|connection
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|proxy_protocol_addr
operator|.
name|len
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
if|if
condition|(
name|ngx_cidr_match
argument_list|(
name|c
operator|->
name|sockaddr
argument_list|,
name|rscf
operator|->
name|from
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
if|if
condition|(
name|ngx_parse_addr
argument_list|(
name|c
operator|->
name|pool
argument_list|,
operator|&
name|addr
argument_list|,
name|c
operator|->
name|proxy_protocol_addr
operator|.
name|data
argument_list|,
name|c
operator|->
name|proxy_protocol_addr
operator|.
name|len
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|ngx_inet_set_port
argument_list|(
name|addr
operator|.
name|sockaddr
argument_list|,
name|c
operator|->
name|proxy_protocol_port
argument_list|)
expr_stmt|;
return|return
name|ngx_stream_realip_set_addr
argument_list|(
name|s
argument_list|,
operator|&
name|addr
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_realip_set_addr (ngx_stream_session_t * s,ngx_addr_t * addr)
name|ngx_stream_realip_set_addr
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_addr_t
modifier|*
name|addr
parameter_list|)
block|{
name|size_t
name|len
decl_stmt|;
name|u_char
modifier|*
name|p
decl_stmt|;
name|u_char
name|text
index|[
name|NGX_SOCKADDR_STRLEN
index|]
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_stream_realip_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|c
operator|=
name|s
operator|->
name|connection
expr_stmt|;
name|ctx
operator|=
name|ngx_palloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_realip_ctx_t
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
name|NGX_ERROR
return|;
block|}
name|len
operator|=
name|ngx_sock_ntop
argument_list|(
name|addr
operator|->
name|sockaddr
argument_list|,
name|addr
operator|->
name|socklen
argument_list|,
name|text
argument_list|,
name|NGX_SOCKADDR_STRLEN
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|p
operator|=
name|ngx_pnalloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_memcpy
argument_list|(
name|p
argument_list|,
name|text
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|ngx_stream_set_ctx
argument_list|(
name|s
argument_list|,
name|ctx
argument_list|,
name|ngx_stream_realip_module
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|sockaddr
operator|=
name|c
operator|->
name|sockaddr
expr_stmt|;
name|ctx
operator|->
name|socklen
operator|=
name|c
operator|->
name|socklen
expr_stmt|;
name|ctx
operator|->
name|addr_text
operator|=
name|c
operator|->
name|addr_text
expr_stmt|;
name|c
operator|->
name|sockaddr
operator|=
name|addr
operator|->
name|sockaddr
expr_stmt|;
name|c
operator|->
name|socklen
operator|=
name|addr
operator|->
name|socklen
expr_stmt|;
name|c
operator|->
name|addr_text
operator|.
name|len
operator|=
name|len
expr_stmt|;
name|c
operator|->
name|addr_text
operator|.
name|data
operator|=
name|p
expr_stmt|;
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_stream_realip_from (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_stream_realip_from
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
name|ngx_stream_realip_srv_conf_t
modifier|*
name|rscf
init|=
name|conf
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_cidr_t
modifier|*
name|cidr
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
name|rscf
operator|->
name|from
operator|==
name|NULL
condition|)
block|{
name|rscf
operator|->
name|from
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|2
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_cidr_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rscf
operator|->
name|from
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
name|cidr
operator|=
name|ngx_array_push
argument_list|(
name|rscf
operator|->
name|from
argument_list|)
expr_stmt|;
if|if
condition|(
name|cidr
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
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
literal|"unix:"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|cidr
operator|->
name|family
operator|=
name|AF_UNIX
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
endif|#
directive|endif
name|rc
operator|=
name|ngx_ptocidr
argument_list|(
operator|&
name|value
index|[
literal|1
index|]
argument_list|,
name|cidr
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
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
literal|"invalid parameter \"%V\""
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
if|if
condition|(
name|rc
operator|==
name|NGX_DONE
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"low address bits of %V are meaningless"
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_stream_realip_create_srv_conf (ngx_conf_t * cf)
name|ngx_stream_realip_create_srv_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_stream_realip_srv_conf_t
modifier|*
name|conf
decl_stmt|;
name|conf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_realip_srv_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
comment|/*      * set by ngx_pcalloc():      *      *     conf->from = NULL;      */
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_stream_realip_merge_srv_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_stream_realip_merge_srv_conf
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
name|ngx_stream_realip_srv_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_stream_realip_srv_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
if|if
condition|(
name|conf
operator|->
name|from
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|from
operator|=
name|prev
operator|->
name|from
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_realip_add_variables (ngx_conf_t * cf)
name|ngx_stream_realip_add_variables
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_stream_variable_t
modifier|*
name|var
decl_stmt|,
modifier|*
name|v
decl_stmt|;
for|for
control|(
name|v
operator|=
name|ngx_stream_realip_vars
init|;
name|v
operator|->
name|name
operator|.
name|len
condition|;
name|v
operator|++
control|)
block|{
name|var
operator|=
name|ngx_stream_add_variable
argument_list|(
name|cf
argument_list|,
operator|&
name|v
operator|->
name|name
argument_list|,
name|v
operator|->
name|flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|var
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|var
operator|->
name|get_handler
operator|=
name|v
operator|->
name|get_handler
expr_stmt|;
name|var
operator|->
name|data
operator|=
name|v
operator|->
name|data
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_realip_init (ngx_conf_t * cf)
name|ngx_stream_realip_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_stream_handler_pt
modifier|*
name|h
decl_stmt|;
name|ngx_stream_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
name|cmcf
operator|=
name|ngx_stream_conf_get_module_main_conf
argument_list|(
name|cf
argument_list|,
name|ngx_stream_core_module
argument_list|)
expr_stmt|;
name|h
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|cmcf
operator|->
name|phases
index|[
name|NGX_STREAM_POST_ACCEPT_PHASE
index|]
operator|.
name|handlers
argument_list|)
expr_stmt|;
if|if
condition|(
name|h
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
operator|*
name|h
operator|=
name|ngx_stream_realip_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_realip_remote_addr_variable (ngx_stream_session_t * s,ngx_stream_variable_value_t * v,uintptr_t data)
name|ngx_stream_realip_remote_addr_variable
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_variable_value_t
modifier|*
name|v
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
block|{
name|ngx_str_t
modifier|*
name|addr_text
decl_stmt|;
name|ngx_stream_realip_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ctx
operator|=
name|ngx_stream_get_module_ctx
argument_list|(
name|s
argument_list|,
name|ngx_stream_realip_module
argument_list|)
expr_stmt|;
name|addr_text
operator|=
name|ctx
condition|?
operator|&
name|ctx
operator|->
name|addr_text
else|:
operator|&
name|s
operator|->
name|connection
operator|->
name|addr_text
expr_stmt|;
name|v
operator|->
name|len
operator|=
name|addr_text
operator|->
name|len
expr_stmt|;
name|v
operator|->
name|valid
operator|=
literal|1
expr_stmt|;
name|v
operator|->
name|no_cacheable
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|not_found
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|data
operator|=
name|addr_text
operator|->
name|data
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_realip_remote_port_variable (ngx_stream_session_t * s,ngx_stream_variable_value_t * v,uintptr_t data)
name|ngx_stream_realip_remote_port_variable
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_variable_value_t
modifier|*
name|v
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
block|{
name|ngx_uint_t
name|port
decl_stmt|;
name|struct
name|sockaddr
modifier|*
name|sa
decl_stmt|;
name|ngx_stream_realip_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ctx
operator|=
name|ngx_stream_get_module_ctx
argument_list|(
name|s
argument_list|,
name|ngx_stream_realip_module
argument_list|)
expr_stmt|;
name|sa
operator|=
name|ctx
condition|?
name|ctx
operator|->
name|sockaddr
else|:
name|s
operator|->
name|connection
operator|->
name|sockaddr
expr_stmt|;
name|v
operator|->
name|len
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|valid
operator|=
literal|1
expr_stmt|;
name|v
operator|->
name|no_cacheable
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|not_found
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|data
operator|=
name|ngx_pnalloc
argument_list|(
name|s
operator|->
name|connection
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
literal|"65535"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|v
operator|->
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|port
operator|=
name|ngx_inet_get_port
argument_list|(
name|sa
argument_list|)
expr_stmt|;
if|if
condition|(
name|port
operator|>
literal|0
operator|&&
name|port
operator|<
literal|65536
condition|)
block|{
name|v
operator|->
name|len
operator|=
name|ngx_sprintf
argument_list|(
name|v
operator|->
name|data
argument_list|,
literal|"%ui"
argument_list|,
name|port
argument_list|)
operator|-
name|v
operator|->
name|data
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit
