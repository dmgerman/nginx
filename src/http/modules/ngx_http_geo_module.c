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
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon2bde94410108
typedef|typedef
struct|struct
block|{
DECL|member|tree
name|ngx_radix_tree_t
modifier|*
name|tree
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|values
name|ngx_array_t
name|values
decl_stmt|;
DECL|typedef|ngx_http_geo_conf_ctx_t
block|}
name|ngx_http_geo_conf_ctx_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_geo_block
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
name|ngx_http_geo
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|dummy
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_geo_commands
specifier|static
name|ngx_command_t
name|ngx_http_geo_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"geo"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_CONF_BLOCK
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_geo_block
block|,
name|NGX_HTTP_MAIN_CONF_OFFSET
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
DECL|variable|ngx_http_geo_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_geo_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|NULL
block|,
comment|/* postconfiguration */
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|NULL
block|,
comment|/* create server configuration */
name|NULL
block|,
comment|/* merge server configuration */
name|NULL
block|,
comment|/* create location configuration */
name|NULL
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_geo_module
name|ngx_module_t
name|ngx_http_geo_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_geo_module_ctx
block|,
comment|/* module context */
name|ngx_http_geo_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
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

begin_comment
comment|/* AF_INET only */
end_comment

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_geo_variable (ngx_http_request_t * r,ngx_http_variable_value_t * v,uintptr_t data)
name|ngx_http_geo_variable
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_variable_value_t
modifier|*
name|v
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
block|{
name|ngx_radix_tree_t
modifier|*
name|tree
init|=
operator|(
name|ngx_radix_tree_t
operator|*
operator|)
name|data
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
name|ngx_http_variable_value_t
modifier|*
name|vv
decl_stmt|;
name|sin
operator|=
operator|(
expr|struct
name|sockaddr_in
operator|*
operator|)
name|r
operator|->
name|connection
operator|->
name|sockaddr
expr_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"http geo started"
argument_list|)
expr_stmt|;
name|vv
operator|=
operator|(
name|ngx_http_variable_value_t
operator|*
operator|)
name|ngx_radix32tree_find
argument_list|(
name|tree
argument_list|,
name|ntohl
argument_list|(
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|v
operator|=
operator|*
name|vv
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"http geo: %V %V"
argument_list|,
operator|&
name|r
operator|->
name|connection
operator|->
name|addr_text
argument_list|,
name|v
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_geo_block (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_geo_block
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
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
name|name
decl_stmt|;
name|ngx_conf_t
name|save
decl_stmt|;
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
name|ngx_radix_tree_t
modifier|*
name|tree
decl_stmt|;
name|ngx_http_geo_conf_ctx_t
name|ctx
decl_stmt|;
name|ngx_http_variable_t
modifier|*
name|var
decl_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|name
operator|=
name|value
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|name
operator|.
name|data
index|[
literal|0
index|]
operator|!=
literal|'$'
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
literal|"\"%V\" variable name should start with '$'"
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|name
operator|.
name|len
operator|--
expr_stmt|;
name|name
operator|.
name|data
operator|++
expr_stmt|;
block|}
name|var
operator|=
name|ngx_http_add_variable
argument_list|(
name|cf
argument_list|,
operator|&
name|name
argument_list|,
name|NGX_HTTP_VAR_CHANGABLE
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
name|NGX_CONF_ERROR
return|;
block|}
name|tree
operator|=
name|ngx_radix_tree_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|tree
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|var
operator|->
name|get_handler
operator|=
name|ngx_http_geo_variable
expr_stmt|;
name|var
operator|->
name|data
operator|=
operator|(
name|uintptr_t
operator|)
name|tree
expr_stmt|;
name|pool
operator|=
name|ngx_create_pool
argument_list|(
literal|16384
argument_list|,
name|cf
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|pool
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|ngx_array_init
argument_list|(
operator|&
name|ctx
operator|.
name|values
argument_list|,
name|pool
argument_list|,
literal|512
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_variable_value_t
operator|*
argument_list|)
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
name|ngx_destroy_pool
argument_list|(
name|pool
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|ctx
operator|.
name|tree
operator|=
name|tree
expr_stmt|;
name|ctx
operator|.
name|pool
operator|=
name|cf
operator|->
name|pool
expr_stmt|;
name|save
operator|=
operator|*
name|cf
expr_stmt|;
name|cf
operator|->
name|pool
operator|=
name|pool
expr_stmt|;
name|cf
operator|->
name|ctx
operator|=
operator|&
name|ctx
expr_stmt|;
name|cf
operator|->
name|handler
operator|=
name|ngx_http_geo
expr_stmt|;
name|cf
operator|->
name|handler_conf
operator|=
name|conf
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
name|save
expr_stmt|;
name|ngx_destroy_pool
argument_list|(
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_radix32tree_find
argument_list|(
name|tree
argument_list|,
literal|0
argument_list|)
operator|!=
name|NGX_RADIX_NO_VALUE
condition|)
block|{
return|return
name|rv
return|;
block|}
if|if
condition|(
name|ngx_radix32tree_insert
argument_list|(
name|tree
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|(
name|uintptr_t
operator|)
operator|&
name|ngx_http_variable_null_value
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
return|return
name|rv
return|;
block|}
end_function

begin_comment
comment|/* AF_INET only */
end_comment

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_geo (ngx_conf_t * cf,ngx_command_t * dummy,void * conf)
name|ngx_http_geo
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|dummy
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
name|file
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_inet_cidr_t
name|cidrin
decl_stmt|;
name|ngx_http_geo_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_variable_value_t
modifier|*
name|var
decl_stmt|,
modifier|*
name|old
decl_stmt|,
modifier|*
modifier|*
name|v
decl_stmt|;
name|ctx
operator|=
name|cf
operator|->
name|ctx
expr_stmt|;
if|if
condition|(
name|cf
operator|->
name|args
operator|->
name|nelts
operator|!=
literal|2
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
literal|"invalid number of the geo parameters"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
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
name|ngx_strcmp
argument_list|(
name|value
index|[
literal|0
index|]
operator|.
name|data
argument_list|,
literal|"include"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|file
operator|=
name|value
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|ngx_conf_full_name
argument_list|(
name|cf
operator|->
name|cycle
argument_list|,
operator|&
name|file
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"include %s"
argument_list|,
name|file
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|ngx_conf_parse
argument_list|(
name|cf
argument_list|,
operator|&
name|file
argument_list|)
return|;
block|}
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
literal|0
index|]
operator|.
name|data
argument_list|,
literal|"default"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|cidrin
operator|.
name|addr
operator|=
literal|0
expr_stmt|;
name|cidrin
operator|.
name|mask
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|ngx_ptocidr
argument_list|(
operator|&
name|value
index|[
literal|0
index|]
argument_list|,
operator|&
name|cidrin
argument_list|)
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
literal|0
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|cidrin
operator|.
name|addr
operator|=
name|ntohl
argument_list|(
name|cidrin
operator|.
name|addr
argument_list|)
expr_stmt|;
name|cidrin
operator|.
name|mask
operator|=
name|ntohl
argument_list|(
name|cidrin
operator|.
name|mask
argument_list|)
expr_stmt|;
block|}
name|var
operator|=
name|NULL
expr_stmt|;
name|v
operator|=
name|ctx
operator|->
name|values
operator|.
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
name|ctx
operator|->
name|values
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|size_t
operator|)
name|v
index|[
name|i
index|]
operator|->
name|len
operator|!=
name|value
index|[
literal|1
index|]
operator|.
name|len
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|ngx_strncmp
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
name|v
index|[
name|i
index|]
operator|->
name|data
argument_list|,
name|value
index|[
literal|1
index|]
operator|.
name|len
argument_list|)
operator|==
literal|0
condition|)
block|{
name|var
operator|=
name|v
index|[
name|i
index|]
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|var
operator|==
name|NULL
condition|)
block|{
name|var
operator|=
name|ngx_palloc
argument_list|(
name|ctx
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_variable_value_t
argument_list|)
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
name|NGX_CONF_ERROR
return|;
block|}
name|var
operator|->
name|len
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|len
expr_stmt|;
name|var
operator|->
name|data
operator|=
name|ngx_pstrdup
argument_list|(
name|ctx
operator|->
name|pool
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|var
operator|->
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|var
operator|->
name|valid
operator|=
literal|1
expr_stmt|;
name|var
operator|->
name|no_cachable
operator|=
literal|0
expr_stmt|;
name|var
operator|->
name|not_found
operator|=
literal|0
expr_stmt|;
name|v
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|ctx
operator|->
name|values
argument_list|)
expr_stmt|;
if|if
condition|(
name|v
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
operator|*
name|v
operator|=
name|var
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|2
init|;
name|i
condition|;
name|i
operator|--
control|)
block|{
name|rc
operator|=
name|ngx_radix32tree_insert
argument_list|(
name|ctx
operator|->
name|tree
argument_list|,
name|cidrin
operator|.
name|addr
argument_list|,
name|cidrin
operator|.
name|mask
argument_list|,
operator|(
name|uintptr_t
operator|)
name|var
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_OK
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
comment|/* rc == NGX_BUSY */
name|old
operator|=
operator|(
name|ngx_http_variable_value_t
operator|*
operator|)
name|ngx_radix32tree_find
argument_list|(
name|ctx
operator|->
name|tree
argument_list|,
name|cidrin
operator|.
name|addr
operator|&
name|cidrin
operator|.
name|mask
argument_list|)
expr_stmt|;
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"duplicate parameter \"%V\", value: \"%V\", "
literal|"old value: \"%V\""
argument_list|,
operator|&
name|value
index|[
literal|0
index|]
argument_list|,
name|var
argument_list|,
name|old
argument_list|)
expr_stmt|;
name|rc
operator|=
name|ngx_radix32tree_delete
argument_list|(
name|ctx
operator|->
name|tree
argument_list|,
name|cidrin
operator|.
name|addr
argument_list|,
name|cidrin
operator|.
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
return|return
name|NGX_CONF_ERROR
return|;
block|}
end_function

end_unit

