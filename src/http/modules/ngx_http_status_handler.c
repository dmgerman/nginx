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
DECL|struct|__anon28dce74e0108
typedef|typedef
struct|struct
block|{
DECL|member|request
name|ngx_http_request_t
modifier|*
name|request
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|head
name|ngx_chain_t
modifier|*
name|head
decl_stmt|;
DECL|member|last
name|ngx_buf_t
modifier|*
name|last
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|typedef|ngx_http_status_ctx_t
block|}
name|ngx_http_status_ctx_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_status
parameter_list|(
name|ngx_http_status_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_set_status
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
DECL|variable|ngx_http_status_commands
specifier|static
name|ngx_command_t
name|ngx_http_status_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"status"
argument_list|)
block|,
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_http_set_status
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
DECL|variable|ngx_http_status_module_ctx
name|ngx_http_module_t
name|ngx_http_status_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* pre conf */
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
DECL|variable|ngx_http_status_module
name|ngx_module_t
name|ngx_http_status_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_status_module_ctx
block|,
comment|/* module context */
name|ngx_http_status_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init module */
name|NULL
comment|/* init process */
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_status_handler (ngx_http_request_t * r)
specifier|static
name|ngx_int_t
name|ngx_http_status_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_http_status_ctx_t
name|ctx
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|method
operator|!=
name|NGX_HTTP_GET
operator|&&
name|r
operator|->
name|method
operator|!=
name|NGX_HTTP_HEAD
condition|)
block|{
return|return
name|NGX_HTTP_NOT_ALLOWED
return|;
block|}
name|rc
operator|=
name|ngx_http_discard_body
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
operator|&&
name|rc
operator|!=
name|NGX_AGAIN
condition|)
block|{
return|return
name|rc
return|;
block|}
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|=
name|ngx_list_push
argument_list|(
operator|&
name|r
operator|->
name|headers_out
operator|.
name|headers
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|key
operator|.
name|len
operator|=
literal|0
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|key
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"text/plain"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|data
operator|=
operator|(
name|u_char
operator|*
operator|)
literal|"text/plain"
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|method
operator|==
name|NGX_HTTP_HEAD
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|NGX_HTTP_OK
expr_stmt|;
name|rc
operator|=
name|ngx_http_send_header
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|rc
operator|>
name|NGX_OK
operator|||
name|r
operator|->
name|header_only
condition|)
block|{
return|return
name|rc
return|;
block|}
block|}
name|ctx
operator|.
name|request
operator|=
name|r
expr_stmt|;
name|ctx
operator|.
name|pool
operator|=
name|r
operator|->
name|pool
expr_stmt|;
name|ctx
operator|.
name|head
operator|=
name|NULL
expr_stmt|;
name|ctx
operator|.
name|size
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ngx_http_status
argument_list|(
operator|&
name|ctx
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|NGX_HTTP_OK
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|=
name|ctx
operator|.
name|size
expr_stmt|;
name|rc
operator|=
name|ngx_http_send_header
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|rc
operator|>
name|NGX_OK
operator|||
name|r
operator|->
name|header_only
condition|)
block|{
return|return
name|rc
return|;
block|}
if|if
condition|(
operator|!
name|r
operator|->
expr|main
condition|)
block|{
name|ctx
operator|.
name|last
operator|->
name|last_buf
operator|=
literal|1
expr_stmt|;
block|}
return|return
name|ngx_http_output_filter
argument_list|(
name|r
argument_list|,
name|ctx
operator|.
name|head
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_status (ngx_http_status_ctx_t * ctx)
specifier|static
name|ngx_int_t
name|ngx_http_status
parameter_list|(
name|ngx_http_status_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|u_char
name|ch
decl_stmt|;
name|size_t
name|len
decl_stmt|,
name|n
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|dash
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|,
modifier|*
modifier|*
name|ll
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_http_request_t
modifier|*
name|r
decl_stmt|;
name|ngx_http_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
name|cmcf
operator|=
name|ngx_http_get_module_main_conf
argument_list|(
name|ctx
operator|->
name|request
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_SUPPRESS_WARN
operator|)
name|b
operator|=
name|NULL
expr_stmt|;
name|ll
operator|=
name|NULL
expr_stmt|;
endif|#
directive|endif
name|dash
operator|=
literal|0
expr_stmt|;
comment|/* TODO: old connections */
name|c
operator|=
name|ngx_cycle
operator|->
name|connections
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ngx_cycle
operator|->
name|connection_n
condition|;
name|i
operator|++
control|)
block|{
comment|/* TODO: trylock connection mutex */
name|r
operator|=
name|c
index|[
name|i
index|]
operator|.
name|data
expr_stmt|;
if|if
condition|(
name|r
operator|&&
name|r
operator|->
name|signature
operator|==
name|NGX_HTTP_MODULE
condition|)
block|{
comment|/* STUB: should be NGX_PID_T_LEN */
name|len
operator|=
name|NGX_INT64_LEN
comment|/* pid */
operator|+
literal|1
operator|+
name|NGX_INT32_LEN
comment|/* connection */
operator|+
literal|1
operator|+
literal|1
comment|/* state */
operator|+
literal|1
operator|+
name|INET_ADDRSTRLEN
operator|+
literal|1
operator|+
operator|(
name|r
operator|->
name|server_name
condition|?
name|cmcf
operator|->
name|max_server_name_len
else|:
literal|1
operator|)
operator|+
literal|2
expr_stmt|;
comment|/* "\r\n" */
comment|/* BUG: cmcf->max_server_name_len and "*.domain.tld" */
if|if
condition|(
name|r
operator|->
name|request_line
operator|.
name|len
condition|)
block|{
name|len
operator|+=
literal|1
operator|+
literal|1
operator|+
name|r
operator|->
name|request_line
operator|.
name|len
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|b
operator|=
name|ngx_create_temp_buf
argument_list|(
name|ctx
operator|->
name|pool
argument_list|,
name|len
argument_list|)
operator|)
condition|)
block|{
comment|/* TODO: unlock mutex */
return|return
name|NGX_ERROR
return|;
block|}
name|b
operator|->
name|last
operator|=
name|ngx_sprintf
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"%P %5ui"
argument_list|,
name|ngx_pid
argument_list|,
name|i
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|r
operator|->
name|http_state
condition|)
block|{
case|case
name|NGX_HTTP_INITING_REQUEST_STATE
case|:
name|ch
operator|=
literal|'I'
expr_stmt|;
break|break;
case|case
name|NGX_HTTP_READING_REQUEST_STATE
case|:
name|ch
operator|=
literal|'R'
expr_stmt|;
break|break;
case|case
name|NGX_HTTP_PROCESS_REQUEST_STATE
case|:
name|ch
operator|=
literal|'P'
expr_stmt|;
break|break;
case|case
name|NGX_HTTP_WRITING_REQUEST_STATE
case|:
name|ch
operator|=
literal|'W'
expr_stmt|;
break|break;
case|case
name|NGX_HTTP_KEEPALIVE_STATE
case|:
name|ch
operator|=
literal|'K'
expr_stmt|;
break|break;
default|default:
name|ch
operator|=
literal|'?'
expr_stmt|;
block|}
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|' '
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|ch
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|' '
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|c
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|,
name|c
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|len
argument_list|)
expr_stmt|;
for|for
control|(
name|n
operator|=
name|c
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|len
init|;
name|n
operator|<
name|INET_ADDRSTRLEN
condition|;
name|n
operator|++
control|)
block|{
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|' '
expr_stmt|;
block|}
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|' '
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|server_name
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|server_name
operator|->
name|data
argument_list|,
name|r
operator|->
name|server_name
operator|->
name|len
argument_list|)
expr_stmt|;
for|for
control|(
name|n
operator|=
name|r
operator|->
name|server_name
operator|->
name|len
init|;
name|n
operator|<
name|cmcf
operator|->
name|max_server_name_len
condition|;
name|n
operator|++
control|)
block|{
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|' '
expr_stmt|;
block|}
block|}
else|else
block|{
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|'?'
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|request_line
operator|.
name|len
condition|)
block|{
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|' '
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|'"'
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|request_line
operator|.
name|data
argument_list|,
name|r
operator|->
name|request_line
operator|.
name|len
argument_list|)
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|'"'
expr_stmt|;
block|}
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
name|dash
operator|=
literal|0
expr_stmt|;
block|}
if|else if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|fd
operator|!=
operator|-
literal|1
condition|)
block|{
name|len
operator|=
name|NGX_INT64_LEN
comment|/* pid */
operator|+
literal|1
operator|+
name|NGX_INT32_LEN
comment|/* connection */
operator|+
literal|1
operator|+
literal|1
comment|/* state */
operator|+
literal|2
expr_stmt|;
comment|/* "\r\n" */
if|if
condition|(
operator|!
operator|(
name|b
operator|=
name|ngx_create_temp_buf
argument_list|(
name|ctx
operator|->
name|pool
argument_list|,
name|len
argument_list|)
operator|)
condition|)
block|{
comment|/* TODO: unlock mutex */
return|return
name|NGX_ERROR
return|;
block|}
name|b
operator|->
name|last
operator|=
name|ngx_sprintf
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"%P %5ui"
argument_list|,
name|ngx_pid
argument_list|,
name|i
argument_list|)
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|' '
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|'s'
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
name|dash
operator|=
literal|0
expr_stmt|;
block|}
if|else if
condition|(
operator|!
name|dash
condition|)
block|{
name|len
operator|=
literal|3
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|b
operator|=
name|ngx_create_temp_buf
argument_list|(
name|ctx
operator|->
name|pool
argument_list|,
name|len
argument_list|)
operator|)
condition|)
block|{
comment|/* TODO: unlock mutex */
return|return
name|NGX_ERROR
return|;
block|}
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|'-'
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
name|dash
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
continue|continue;
block|}
comment|/* TODO: unlock mutex */
if|if
condition|(
operator|!
operator|(
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|ctx
operator|->
name|pool
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|ctx
operator|->
name|head
condition|)
block|{
operator|*
name|ll
operator|=
name|cl
expr_stmt|;
block|}
else|else
block|{
name|ctx
operator|->
name|head
operator|=
name|cl
expr_stmt|;
block|}
name|cl
operator|->
name|buf
operator|=
name|b
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
name|ll
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
name|ctx
operator|->
name|size
operator|+=
name|b
operator|->
name|last
operator|-
name|b
operator|->
name|pos
expr_stmt|;
block|}
name|ctx
operator|->
name|last
operator|=
name|b
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_set_status (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
specifier|static
name|char
modifier|*
name|ngx_http_set_status
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
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
name|clcf
operator|=
name|ngx_http_conf_get_module_loc_conf
argument_list|(
name|cf
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
name|clcf
operator|->
name|handler
operator|=
name|ngx_http_status_handler
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

