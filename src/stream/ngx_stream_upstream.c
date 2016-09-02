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

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_upstream_add_variables
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
name|ngx_stream_upstream_addr_variable
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
name|ngx_stream_upstream_response_time_variable
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
name|ngx_stream_upstream_bytes_variable
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
name|char
modifier|*
name|ngx_stream_upstream
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
name|dummy
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_stream_upstream_server
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
name|ngx_stream_upstream_create_main_conf
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
name|ngx_stream_upstream_init_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_stream_upstream_commands
specifier|static
name|ngx_command_t
name|ngx_stream_upstream_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"upstream"
argument_list|)
block|,
name|NGX_STREAM_MAIN_CONF
operator||
name|NGX_CONF_BLOCK
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_stream_upstream
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
literal|"server"
argument_list|)
block|,
name|NGX_STREAM_UPS_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_stream_upstream_server
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
DECL|variable|ngx_stream_upstream_module_ctx
specifier|static
name|ngx_stream_module_t
name|ngx_stream_upstream_module_ctx
init|=
block|{
name|ngx_stream_upstream_add_variables
block|,
comment|/* preconfiguration */
name|NULL
block|,
comment|/* postconfiguration */
name|ngx_stream_upstream_create_main_conf
block|,
comment|/* create main configuration */
name|ngx_stream_upstream_init_main_conf
block|,
comment|/* init main configuration */
name|NULL
block|,
comment|/* create server configuration */
name|NULL
comment|/* merge server configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_stream_upstream_module
name|ngx_module_t
name|ngx_stream_upstream_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_stream_upstream_module_ctx
block|,
comment|/* module context */
name|ngx_stream_upstream_commands
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
DECL|variable|ngx_stream_upstream_vars
specifier|static
name|ngx_stream_variable_t
name|ngx_stream_upstream_vars
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"upstream_addr"
argument_list|)
block|,
name|NULL
block|,
name|ngx_stream_upstream_addr_variable
block|,
literal|0
block|,
name|NGX_STREAM_VAR_NOCACHEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"upstream_bytes_sent"
argument_list|)
block|,
name|NULL
block|,
name|ngx_stream_upstream_bytes_variable
block|,
literal|0
block|,
name|NGX_STREAM_VAR_NOCACHEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"upstream_connect_time"
argument_list|)
block|,
name|NULL
block|,
name|ngx_stream_upstream_response_time_variable
block|,
literal|2
block|,
name|NGX_STREAM_VAR_NOCACHEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"upstream_first_byte_time"
argument_list|)
block|,
name|NULL
block|,
name|ngx_stream_upstream_response_time_variable
block|,
literal|1
block|,
name|NGX_STREAM_VAR_NOCACHEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"upstream_session_time"
argument_list|)
block|,
name|NULL
block|,
name|ngx_stream_upstream_response_time_variable
block|,
literal|0
block|,
name|NGX_STREAM_VAR_NOCACHEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"upstream_bytes_received"
argument_list|)
block|,
name|NULL
block|,
name|ngx_stream_upstream_bytes_variable
block|,
literal|1
block|,
name|NGX_STREAM_VAR_NOCACHEABLE
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
DECL|function|ngx_stream_upstream_add_variables (ngx_conf_t * cf)
name|ngx_stream_upstream_add_variables
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
name|ngx_stream_upstream_vars
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
DECL|function|ngx_stream_upstream_addr_variable (ngx_stream_session_t * s,ngx_stream_variable_value_t * v,uintptr_t data)
name|ngx_stream_upstream_addr_variable
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
name|u_char
modifier|*
name|p
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_stream_upstream_state_t
modifier|*
name|state
decl_stmt|;
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
if|if
condition|(
name|s
operator|->
name|upstream_states
operator|==
name|NULL
operator|||
name|s
operator|->
name|upstream_states
operator|->
name|nelts
operator|==
literal|0
condition|)
block|{
name|v
operator|->
name|not_found
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|len
operator|=
literal|0
expr_stmt|;
name|state
operator|=
name|s
operator|->
name|upstream_states
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
name|s
operator|->
name|upstream_states
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|state
index|[
name|i
index|]
operator|.
name|peer
condition|)
block|{
name|len
operator|+=
name|state
index|[
name|i
index|]
operator|.
name|peer
operator|->
name|len
expr_stmt|;
block|}
name|len
operator|+=
literal|2
expr_stmt|;
block|}
name|p
operator|=
name|ngx_pnalloc
argument_list|(
name|s
operator|->
name|connection
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
name|v
operator|->
name|data
operator|=
name|p
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|state
index|[
name|i
index|]
operator|.
name|peer
condition|)
block|{
name|p
operator|=
name|ngx_cpymem
argument_list|(
name|p
argument_list|,
name|state
index|[
name|i
index|]
operator|.
name|peer
operator|->
name|data
argument_list|,
name|state
index|[
name|i
index|]
operator|.
name|peer
operator|->
name|len
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|++
name|i
operator|==
name|s
operator|->
name|upstream_states
operator|->
name|nelts
condition|)
block|{
break|break;
block|}
operator|*
name|p
operator|++
operator|=
literal|','
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|' '
expr_stmt|;
block|}
name|v
operator|->
name|len
operator|=
name|p
operator|-
name|v
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
DECL|function|ngx_stream_upstream_bytes_variable (ngx_stream_session_t * s,ngx_stream_variable_value_t * v,uintptr_t data)
name|ngx_stream_upstream_bytes_variable
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
name|u_char
modifier|*
name|p
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_stream_upstream_state_t
modifier|*
name|state
decl_stmt|;
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
if|if
condition|(
name|s
operator|->
name|upstream_states
operator|==
name|NULL
operator|||
name|s
operator|->
name|upstream_states
operator|->
name|nelts
operator|==
literal|0
condition|)
block|{
name|v
operator|->
name|not_found
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|len
operator|=
name|s
operator|->
name|upstream_states
operator|->
name|nelts
operator|*
operator|(
name|NGX_OFF_T_LEN
operator|+
literal|2
operator|)
expr_stmt|;
name|p
operator|=
name|ngx_pnalloc
argument_list|(
name|s
operator|->
name|connection
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
name|v
operator|->
name|data
operator|=
name|p
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
name|state
operator|=
name|s
operator|->
name|upstream_states
operator|->
name|elts
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|data
operator|==
literal|1
condition|)
block|{
name|p
operator|=
name|ngx_sprintf
argument_list|(
name|p
argument_list|,
literal|"%O"
argument_list|,
name|state
index|[
name|i
index|]
operator|.
name|bytes_received
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|p
operator|=
name|ngx_sprintf
argument_list|(
name|p
argument_list|,
literal|"%O"
argument_list|,
name|state
index|[
name|i
index|]
operator|.
name|bytes_sent
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|++
name|i
operator|==
name|s
operator|->
name|upstream_states
operator|->
name|nelts
condition|)
block|{
break|break;
block|}
operator|*
name|p
operator|++
operator|=
literal|','
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|' '
expr_stmt|;
block|}
name|v
operator|->
name|len
operator|=
name|p
operator|-
name|v
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
DECL|function|ngx_stream_upstream_response_time_variable (ngx_stream_session_t * s,ngx_stream_variable_value_t * v,uintptr_t data)
name|ngx_stream_upstream_response_time_variable
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
name|u_char
modifier|*
name|p
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_msec_int_t
name|ms
decl_stmt|;
name|ngx_stream_upstream_state_t
modifier|*
name|state
decl_stmt|;
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
if|if
condition|(
name|s
operator|->
name|upstream_states
operator|==
name|NULL
operator|||
name|s
operator|->
name|upstream_states
operator|->
name|nelts
operator|==
literal|0
condition|)
block|{
name|v
operator|->
name|not_found
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|len
operator|=
name|s
operator|->
name|upstream_states
operator|->
name|nelts
operator|*
operator|(
name|NGX_TIME_T_LEN
operator|+
literal|4
operator|+
literal|2
operator|)
expr_stmt|;
name|p
operator|=
name|ngx_pnalloc
argument_list|(
name|s
operator|->
name|connection
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
name|v
operator|->
name|data
operator|=
name|p
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
name|state
operator|=
name|s
operator|->
name|upstream_states
operator|->
name|elts
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|data
operator|==
literal|1
condition|)
block|{
if|if
condition|(
name|state
index|[
name|i
index|]
operator|.
name|first_byte_time
operator|==
operator|(
name|ngx_msec_t
operator|)
operator|-
literal|1
condition|)
block|{
operator|*
name|p
operator|++
operator|=
literal|'-'
expr_stmt|;
goto|goto
name|next
goto|;
block|}
name|ms
operator|=
name|state
index|[
name|i
index|]
operator|.
name|first_byte_time
expr_stmt|;
block|}
if|else if
condition|(
name|data
operator|==
literal|2
operator|&&
name|state
index|[
name|i
index|]
operator|.
name|connect_time
operator|!=
operator|(
name|ngx_msec_t
operator|)
operator|-
literal|1
condition|)
block|{
name|ms
operator|=
name|state
index|[
name|i
index|]
operator|.
name|connect_time
expr_stmt|;
block|}
else|else
block|{
name|ms
operator|=
name|state
index|[
name|i
index|]
operator|.
name|response_time
expr_stmt|;
block|}
name|ms
operator|=
name|ngx_max
argument_list|(
name|ms
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_sprintf
argument_list|(
name|p
argument_list|,
literal|"%T.%03M"
argument_list|,
operator|(
name|time_t
operator|)
name|ms
operator|/
literal|1000
argument_list|,
name|ms
operator|%
literal|1000
argument_list|)
expr_stmt|;
name|next
label|:
if|if
condition|(
operator|++
name|i
operator|==
name|s
operator|->
name|upstream_states
operator|->
name|nelts
condition|)
block|{
break|break;
block|}
operator|*
name|p
operator|++
operator|=
literal|','
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|' '
expr_stmt|;
block|}
name|v
operator|->
name|len
operator|=
name|p
operator|-
name|v
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
name|char
modifier|*
DECL|function|ngx_stream_upstream (ngx_conf_t * cf,ngx_command_t * cmd,void * dummy)
name|ngx_stream_upstream
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
name|dummy
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
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_url_t
name|u
decl_stmt|;
name|ngx_uint_t
name|m
decl_stmt|;
name|ngx_conf_t
name|pcf
decl_stmt|;
name|ngx_stream_module_t
modifier|*
name|module
decl_stmt|;
name|ngx_stream_conf_ctx_t
modifier|*
name|ctx
decl_stmt|,
modifier|*
name|stream_ctx
decl_stmt|;
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|uscf
decl_stmt|;
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
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|u
operator|.
name|host
operator|=
name|value
index|[
literal|1
index|]
expr_stmt|;
name|u
operator|.
name|no_resolve
operator|=
literal|1
expr_stmt|;
name|u
operator|.
name|no_port
operator|=
literal|1
expr_stmt|;
name|uscf
operator|=
name|ngx_stream_upstream_add
argument_list|(
name|cf
argument_list|,
operator|&
name|u
argument_list|,
name|NGX_STREAM_UPSTREAM_CREATE
operator||
name|NGX_STREAM_UPSTREAM_WEIGHT
operator||
name|NGX_STREAM_UPSTREAM_MAX_FAILS
operator||
name|NGX_STREAM_UPSTREAM_FAIL_TIMEOUT
operator||
name|NGX_STREAM_UPSTREAM_DOWN
operator||
name|NGX_STREAM_UPSTREAM_BACKUP
argument_list|)
expr_stmt|;
if|if
condition|(
name|uscf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
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
name|ngx_stream_conf_ctx_t
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
name|stream_ctx
operator|=
name|cf
operator|->
name|ctx
expr_stmt|;
name|ctx
operator|->
name|main_conf
operator|=
name|stream_ctx
operator|->
name|main_conf
expr_stmt|;
comment|/* the upstream{}'s srv_conf */
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
name|ngx_stream_max_module
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
name|ctx
operator|->
name|srv_conf
index|[
name|ngx_stream_upstream_module
operator|.
name|ctx_index
index|]
operator|=
name|uscf
expr_stmt|;
name|uscf
operator|->
name|srv_conf
operator|=
name|ctx
operator|->
name|srv_conf
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
name|NGX_STREAM_MODULE
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
name|uscf
operator|->
name|servers
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|4
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_server_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uscf
operator|->
name|servers
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
comment|/* parse inside upstream{} */
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
name|NGX_STREAM_UPS_CONF
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
block|{
return|return
name|rv
return|;
block|}
if|if
condition|(
name|uscf
operator|->
name|servers
operator|->
name|nelts
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
literal|"no servers are inside upstream"
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
DECL|function|ngx_stream_upstream_server (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_stream_upstream_server
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
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|uscf
init|=
name|conf
decl_stmt|;
name|time_t
name|fail_timeout
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
name|s
decl_stmt|;
name|ngx_url_t
name|u
decl_stmt|;
name|ngx_int_t
name|weight
decl_stmt|,
name|max_fails
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_stream_upstream_server_t
modifier|*
name|us
decl_stmt|;
name|us
operator|=
name|ngx_array_push
argument_list|(
name|uscf
operator|->
name|servers
argument_list|)
expr_stmt|;
if|if
condition|(
name|us
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
name|us
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_server_t
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|weight
operator|=
literal|1
expr_stmt|;
name|max_fails
operator|=
literal|1
expr_stmt|;
name|fail_timeout
operator|=
literal|10
expr_stmt|;
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
name|ngx_strncmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"weight="
argument_list|,
literal|7
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|uscf
operator|->
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_WEIGHT
operator|)
condition|)
block|{
goto|goto
name|not_supported
goto|;
block|}
name|weight
operator|=
name|ngx_atoi
argument_list|(
operator|&
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|7
index|]
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|7
argument_list|)
expr_stmt|;
if|if
condition|(
name|weight
operator|==
name|NGX_ERROR
operator|||
name|weight
operator|==
literal|0
condition|)
block|{
goto|goto
name|invalid
goto|;
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
literal|"max_fails="
argument_list|,
literal|10
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|uscf
operator|->
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_MAX_FAILS
operator|)
condition|)
block|{
goto|goto
name|not_supported
goto|;
block|}
name|max_fails
operator|=
name|ngx_atoi
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
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|10
argument_list|)
expr_stmt|;
if|if
condition|(
name|max_fails
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|invalid
goto|;
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
literal|"fail_timeout="
argument_list|,
literal|13
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|uscf
operator|->
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_FAIL_TIMEOUT
operator|)
condition|)
block|{
goto|goto
name|not_supported
goto|;
block|}
name|s
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
literal|13
expr_stmt|;
name|s
operator|.
name|data
operator|=
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
expr_stmt|;
name|fail_timeout
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
name|fail_timeout
operator|==
operator|(
name|time_t
operator|)
name|NGX_ERROR
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
continue|continue;
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
literal|"backup"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|uscf
operator|->
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_BACKUP
operator|)
condition|)
block|{
goto|goto
name|not_supported
goto|;
block|}
name|us
operator|->
name|backup
operator|=
literal|1
expr_stmt|;
continue|continue;
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
literal|"down"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|uscf
operator|->
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_DOWN
operator|)
condition|)
block|{
goto|goto
name|not_supported
goto|;
block|}
name|us
operator|->
name|down
operator|=
literal|1
expr_stmt|;
continue|continue;
block|}
goto|goto
name|invalid
goto|;
block|}
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
literal|"%s in upstream \"%V\""
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
if|if
condition|(
name|u
operator|.
name|no_port
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
literal|"no port in upstream \"%V\""
argument_list|,
operator|&
name|u
operator|.
name|url
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|us
operator|->
name|name
operator|=
name|u
operator|.
name|url
expr_stmt|;
name|us
operator|->
name|addrs
operator|=
name|u
operator|.
name|addrs
expr_stmt|;
name|us
operator|->
name|naddrs
operator|=
name|u
operator|.
name|naddrs
expr_stmt|;
name|us
operator|->
name|weight
operator|=
name|weight
expr_stmt|;
name|us
operator|->
name|max_fails
operator|=
name|max_fails
expr_stmt|;
name|us
operator|->
name|fail_timeout
operator|=
name|fail_timeout
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
literal|"invalid parameter \"%V\""
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
name|not_supported
label|:
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"balancing method does not support parameter \"%V\""
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
end_function

begin_function
name|ngx_stream_upstream_srv_conf_t
modifier|*
DECL|function|ngx_stream_upstream_add (ngx_conf_t * cf,ngx_url_t * u,ngx_uint_t flags)
name|ngx_stream_upstream_add
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_url_t
modifier|*
name|u
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_stream_upstream_server_t
modifier|*
name|us
decl_stmt|;
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|uscf
decl_stmt|,
modifier|*
modifier|*
name|uscfp
decl_stmt|;
name|ngx_stream_upstream_main_conf_t
modifier|*
name|umcf
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_CREATE
operator|)
condition|)
block|{
if|if
condition|(
name|ngx_parse_url
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|u
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
if|if
condition|(
name|u
operator|->
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
literal|"%s in upstream \"%V\""
argument_list|,
name|u
operator|->
name|err
argument_list|,
operator|&
name|u
operator|->
name|url
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
block|}
name|umcf
operator|=
name|ngx_stream_conf_get_module_main_conf
argument_list|(
name|cf
argument_list|,
name|ngx_stream_upstream_module
argument_list|)
expr_stmt|;
name|uscfp
operator|=
name|umcf
operator|->
name|upstreams
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
name|umcf
operator|->
name|upstreams
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|uscfp
index|[
name|i
index|]
operator|->
name|host
operator|.
name|len
operator|!=
name|u
operator|->
name|host
operator|.
name|len
operator|||
name|ngx_strncasecmp
argument_list|(
name|uscfp
index|[
name|i
index|]
operator|->
name|host
operator|.
name|data
argument_list|,
name|u
operator|->
name|host
operator|.
name|data
argument_list|,
name|u
operator|->
name|host
operator|.
name|len
argument_list|)
operator|!=
literal|0
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
operator|(
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_CREATE
operator|)
operator|&&
operator|(
name|uscfp
index|[
name|i
index|]
operator|->
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_CREATE
operator|)
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
literal|"duplicate upstream \"%V\""
argument_list|,
operator|&
name|u
operator|->
name|host
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
operator|(
name|uscfp
index|[
name|i
index|]
operator|->
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_CREATE
operator|)
operator|&&
operator|!
name|u
operator|->
name|no_port
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
literal|"upstream \"%V\" may not have port %d"
argument_list|,
operator|&
name|u
operator|->
name|host
argument_list|,
name|u
operator|->
name|port
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
operator|(
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_CREATE
operator|)
operator|&&
operator|!
name|uscfp
index|[
name|i
index|]
operator|->
name|no_port
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"upstream \"%V\" may not have port %d in %s:%ui"
argument_list|,
operator|&
name|u
operator|->
name|host
argument_list|,
name|uscfp
index|[
name|i
index|]
operator|->
name|port
argument_list|,
name|uscfp
index|[
name|i
index|]
operator|->
name|file_name
argument_list|,
name|uscfp
index|[
name|i
index|]
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|uscfp
index|[
name|i
index|]
operator|->
name|port
operator|!=
name|u
operator|->
name|port
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|flags
operator|&
name|NGX_STREAM_UPSTREAM_CREATE
condition|)
block|{
name|uscfp
index|[
name|i
index|]
operator|->
name|flags
operator|=
name|flags
expr_stmt|;
block|}
return|return
name|uscfp
index|[
name|i
index|]
return|;
block|}
name|uscf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_srv_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uscf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|uscf
operator|->
name|flags
operator|=
name|flags
expr_stmt|;
name|uscf
operator|->
name|host
operator|=
name|u
operator|->
name|host
expr_stmt|;
name|uscf
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
name|uscf
operator|->
name|line
operator|=
name|cf
operator|->
name|conf_file
operator|->
name|line
expr_stmt|;
name|uscf
operator|->
name|port
operator|=
name|u
operator|->
name|port
expr_stmt|;
name|uscf
operator|->
name|no_port
operator|=
name|u
operator|->
name|no_port
expr_stmt|;
if|if
condition|(
name|u
operator|->
name|naddrs
operator|==
literal|1
operator|&&
operator|(
name|u
operator|->
name|port
operator|||
name|u
operator|->
name|family
operator|==
name|AF_UNIX
operator|)
condition|)
block|{
name|uscf
operator|->
name|servers
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|1
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_server_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|uscf
operator|->
name|servers
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|us
operator|=
name|ngx_array_push
argument_list|(
name|uscf
operator|->
name|servers
argument_list|)
expr_stmt|;
if|if
condition|(
name|us
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|ngx_memzero
argument_list|(
name|us
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_server_t
argument_list|)
argument_list|)
expr_stmt|;
name|us
operator|->
name|addrs
operator|=
name|u
operator|->
name|addrs
expr_stmt|;
name|us
operator|->
name|naddrs
operator|=
literal|1
expr_stmt|;
block|}
name|uscfp
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|umcf
operator|->
name|upstreams
argument_list|)
expr_stmt|;
if|if
condition|(
name|uscfp
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
operator|*
name|uscfp
operator|=
name|uscf
expr_stmt|;
return|return
name|uscf
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_stream_upstream_create_main_conf (ngx_conf_t * cf)
name|ngx_stream_upstream_create_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_stream_upstream_main_conf_t
modifier|*
name|umcf
decl_stmt|;
name|umcf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_main_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|umcf
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
name|umcf
operator|->
name|upstreams
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|4
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_srv_conf_t
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
return|return
name|umcf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_stream_upstream_init_main_conf (ngx_conf_t * cf,void * conf)
name|ngx_stream_upstream_init_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_stream_upstream_main_conf_t
modifier|*
name|umcf
init|=
name|conf
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_stream_upstream_init_pt
name|init
decl_stmt|;
name|ngx_stream_upstream_srv_conf_t
modifier|*
modifier|*
name|uscfp
decl_stmt|;
name|uscfp
operator|=
name|umcf
operator|->
name|upstreams
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
name|umcf
operator|->
name|upstreams
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|init
operator|=
name|uscfp
index|[
name|i
index|]
operator|->
name|peer
operator|.
name|init_upstream
condition|?
name|uscfp
index|[
name|i
index|]
operator|->
name|peer
operator|.
name|init_upstream
else|:
name|ngx_stream_upstream_init_round_robin
expr_stmt|;
if|if
condition|(
name|init
argument_list|(
name|cf
argument_list|,
name|uscfp
index|[
name|i
index|]
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
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

end_unit

