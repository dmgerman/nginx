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
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon27917ff10108
typedef|typedef
struct|struct
block|{
DECL|member|percent
name|uint32_t
name|percent
decl_stmt|;
DECL|member|value
name|ngx_http_variable_value_t
name|value
decl_stmt|;
DECL|typedef|ngx_http_split_clients_part_t
block|}
name|ngx_http_split_clients_part_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27917ff10208
typedef|typedef
struct|struct
block|{
DECL|member|value
name|ngx_http_complex_value_t
name|value
decl_stmt|;
DECL|member|parts
name|ngx_array_t
name|parts
decl_stmt|;
DECL|typedef|ngx_http_split_clients_ctx_t
block|}
name|ngx_http_split_clients_ctx_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_conf_split_clients_block
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
name|ngx_http_split_clients
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
DECL|variable|ngx_http_split_clients_commands
specifier|static
name|ngx_command_t
name|ngx_http_split_clients_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"split_clients"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_CONF_BLOCK
operator||
name|NGX_CONF_TAKE2
block|,
name|ngx_conf_split_clients_block
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
DECL|variable|ngx_http_split_clients_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_split_clients_module_ctx
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
DECL|variable|ngx_http_split_clients_module
name|ngx_module_t
name|ngx_http_split_clients_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_split_clients_module_ctx
block|,
comment|/* module context */
name|ngx_http_split_clients_commands
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

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_split_clients_variable (ngx_http_request_t * r,ngx_http_variable_value_t * v,uintptr_t data)
name|ngx_http_split_clients_variable
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
name|ngx_http_split_clients_ctx_t
modifier|*
name|ctx
init|=
operator|(
name|ngx_http_split_clients_ctx_t
operator|*
operator|)
name|data
decl_stmt|;
name|uint32_t
name|hash
decl_stmt|;
name|ngx_str_t
name|val
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_http_split_clients_part_t
modifier|*
name|part
decl_stmt|;
operator|*
name|v
operator|=
name|ngx_http_variable_null_value
expr_stmt|;
if|if
condition|(
name|ngx_http_complex_value
argument_list|(
name|r
argument_list|,
operator|&
name|ctx
operator|->
name|value
argument_list|,
operator|&
name|val
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|hash
operator|=
name|ngx_murmur_hash2
argument_list|(
name|val
operator|.
name|data
argument_list|,
name|val
operator|.
name|len
argument_list|)
expr_stmt|;
name|part
operator|=
name|ctx
operator|->
name|parts
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
name|parts
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
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
literal|"http split: %uD %uD"
argument_list|,
name|hash
argument_list|,
name|part
index|[
name|i
index|]
operator|.
name|percent
argument_list|)
expr_stmt|;
if|if
condition|(
name|hash
operator|<
name|part
index|[
name|i
index|]
operator|.
name|percent
condition|)
block|{
operator|*
name|v
operator|=
name|part
index|[
name|i
index|]
operator|.
name|value
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_conf_split_clients_block (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_conf_split_clients_block
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
name|ngx_uint_t
name|i
decl_stmt|,
name|sum
decl_stmt|,
name|last
decl_stmt|;
name|ngx_conf_t
name|save
decl_stmt|;
name|ngx_http_variable_t
modifier|*
name|var
decl_stmt|;
name|ngx_http_split_clients_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_split_clients_part_t
modifier|*
name|part
decl_stmt|;
name|ngx_http_compile_complex_value_t
name|ccv
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
name|ngx_http_split_clients_ctx_t
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
name|ccv
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_compile_complex_value_t
argument_list|)
argument_list|)
expr_stmt|;
name|ccv
operator|.
name|cf
operator|=
name|cf
expr_stmt|;
name|ccv
operator|.
name|value
operator|=
operator|&
name|value
index|[
literal|1
index|]
expr_stmt|;
name|ccv
operator|.
name|complex_value
operator|=
operator|&
name|ctx
operator|->
name|value
expr_stmt|;
if|if
condition|(
name|ngx_http_compile_complex_value
argument_list|(
operator|&
name|ccv
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|name
operator|=
name|value
index|[
literal|2
index|]
expr_stmt|;
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
name|var
operator|=
name|ngx_http_add_variable
argument_list|(
name|cf
argument_list|,
operator|&
name|name
argument_list|,
name|NGX_HTTP_VAR_CHANGEABLE
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
name|get_handler
operator|=
name|ngx_http_split_clients_variable
expr_stmt|;
name|var
operator|->
name|data
operator|=
operator|(
name|uintptr_t
operator|)
name|ctx
expr_stmt|;
if|if
condition|(
name|ngx_array_init
argument_list|(
operator|&
name|ctx
operator|->
name|parts
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|2
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_split_clients_part_t
argument_list|)
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|save
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
name|handler
operator|=
name|ngx_http_split_clients
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
name|sum
operator|=
literal|0
expr_stmt|;
name|last
operator|=
literal|0
expr_stmt|;
name|part
operator|=
name|ctx
operator|->
name|parts
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
name|parts
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|sum
operator|=
name|part
index|[
name|i
index|]
operator|.
name|percent
condition|?
name|sum
operator|+
name|part
index|[
name|i
index|]
operator|.
name|percent
else|:
literal|10000
expr_stmt|;
if|if
condition|(
name|sum
operator|>
literal|10000
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
literal|"percent sum is more than 100%%"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|part
index|[
name|i
index|]
operator|.
name|percent
condition|)
block|{
name|part
index|[
name|i
index|]
operator|.
name|percent
operator|=
operator|(
name|uint32_t
operator|)
operator|(
name|last
operator|+
literal|0xffffffff
operator|/
literal|10000
operator|*
name|part
index|[
name|i
index|]
operator|.
name|percent
operator|)
expr_stmt|;
block|}
else|else
block|{
name|part
index|[
name|i
index|]
operator|.
name|percent
operator|=
literal|0xffffffff
expr_stmt|;
block|}
name|last
operator|=
name|part
index|[
name|i
index|]
operator|.
name|percent
expr_stmt|;
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
DECL|function|ngx_http_split_clients (ngx_conf_t * cf,ngx_command_t * dummy,void * conf)
name|ngx_http_split_clients
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
name|n
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_http_split_clients_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_split_clients_part_t
modifier|*
name|part
decl_stmt|;
name|ctx
operator|=
name|cf
operator|->
name|ctx
expr_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|part
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|ctx
operator|->
name|parts
argument_list|)
expr_stmt|;
if|if
condition|(
name|part
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
name|value
index|[
literal|0
index|]
operator|.
name|len
operator|==
literal|1
operator|&&
name|value
index|[
literal|0
index|]
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'*'
condition|)
block|{
name|part
operator|->
name|percent
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|value
index|[
literal|0
index|]
operator|.
name|data
index|[
name|value
index|[
literal|0
index|]
operator|.
name|len
operator|-
literal|1
index|]
operator|!=
literal|'%'
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
name|n
operator|=
name|ngx_atofp
argument_list|(
name|value
index|[
literal|0
index|]
operator|.
name|data
argument_list|,
name|value
index|[
literal|0
index|]
operator|.
name|len
operator|-
literal|1
argument_list|,
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
operator|||
name|n
operator|==
literal|0
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
name|part
operator|->
name|percent
operator|=
operator|(
name|uint32_t
operator|)
name|n
expr_stmt|;
block|}
name|part
operator|->
name|value
operator|.
name|len
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|len
expr_stmt|;
name|part
operator|->
name|value
operator|.
name|valid
operator|=
literal|1
expr_stmt|;
name|part
operator|->
name|value
operator|.
name|no_cacheable
operator|=
literal|0
expr_stmt|;
name|part
operator|->
name|value
operator|.
name|not_found
operator|=
literal|0
expr_stmt|;
name|part
operator|->
name|value
operator|.
name|data
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|data
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
name|invalid
label|:
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid percent value \"%V\""
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
end_function

end_unit

