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

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_flv
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
DECL|variable|ngx_http_flv_commands
specifier|static
name|ngx_command_t
name|ngx_http_flv_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"flv"
argument_list|)
block|,
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_NOARGS
block|,
name|ngx_http_flv
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
DECL|variable|ngx_flv_header
specifier|static
name|u_char
name|ngx_flv_header
index|[]
init|=
literal|"FLV\x1\x1\0\0\0\x9\0\0\0\x9"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_flv_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_flv_module_ctx
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
DECL|variable|ngx_http_flv_module
name|ngx_module_t
name|ngx_http_flv_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_flv_module_ctx
block|,
comment|/* module context */
name|ngx_http_flv_commands
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
DECL|function|ngx_http_flv_handler (ngx_http_request_t * r)
name|ngx_http_flv_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|,
modifier|*
name|n
decl_stmt|,
modifier|*
name|last
decl_stmt|;
name|off_t
name|start
decl_stmt|,
name|len
decl_stmt|;
name|size_t
name|root
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_uint_t
name|level
decl_stmt|,
name|i
decl_stmt|;
name|ngx_str_t
name|path
decl_stmt|;
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
name|ngx_chain_t
name|out
index|[
literal|2
index|]
decl_stmt|;
name|ngx_open_file_info_t
name|of
decl_stmt|;
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|method
operator|&
operator|(
name|NGX_HTTP_GET
operator||
name|NGX_HTTP_HEAD
operator|)
operator|)
condition|)
block|{
return|return
name|NGX_HTTP_NOT_ALLOWED
return|;
block|}
if|if
condition|(
name|r
operator|->
name|uri
operator|.
name|data
index|[
name|r
operator|->
name|uri
operator|.
name|len
operator|-
literal|1
index|]
operator|==
literal|'/'
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
comment|/* TODO: Win32 */
if|if
condition|(
name|r
operator|->
name|zero_in_uri
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|rc
operator|=
name|ngx_http_discard_request_body
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|rc
return|;
block|}
name|last
operator|=
name|ngx_http_map_uri_to_path
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|,
operator|&
name|root
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|last
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|log
operator|=
name|r
operator|->
name|connection
operator|->
name|log
expr_stmt|;
name|path
operator|.
name|len
operator|=
name|last
operator|-
name|path
operator|.
name|data
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"http flv filename: \"%V\""
argument_list|,
operator|&
name|path
argument_list|)
expr_stmt|;
name|clcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|of
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_open_file_info_t
argument_list|)
argument_list|)
expr_stmt|;
name|of
operator|.
name|valid
operator|=
name|clcf
operator|->
name|open_file_cache_valid
expr_stmt|;
name|of
operator|.
name|min_uses
operator|=
name|clcf
operator|->
name|open_file_cache_min_uses
expr_stmt|;
name|of
operator|.
name|errors
operator|=
name|clcf
operator|->
name|open_file_cache_errors
expr_stmt|;
name|of
operator|.
name|events
operator|=
name|clcf
operator|->
name|open_file_cache_events
expr_stmt|;
if|if
condition|(
name|ngx_open_cached_file
argument_list|(
name|clcf
operator|->
name|open_file_cache
argument_list|,
operator|&
name|path
argument_list|,
operator|&
name|of
argument_list|,
name|r
operator|->
name|pool
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
switch|switch
condition|(
name|of
operator|.
name|err
condition|)
block|{
case|case
literal|0
case|:
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
case|case
name|NGX_ENOENT
case|:
case|case
name|NGX_ENOTDIR
case|:
case|case
name|NGX_ENAMETOOLONG
case|:
name|level
operator|=
name|NGX_LOG_ERR
expr_stmt|;
name|rc
operator|=
name|NGX_HTTP_NOT_FOUND
expr_stmt|;
break|break;
case|case
name|NGX_EACCES
case|:
name|level
operator|=
name|NGX_LOG_ERR
expr_stmt|;
name|rc
operator|=
name|NGX_HTTP_FORBIDDEN
expr_stmt|;
break|break;
default|default:
name|level
operator|=
name|NGX_LOG_CRIT
expr_stmt|;
name|rc
operator|=
name|NGX_HTTP_INTERNAL_SERVER_ERROR
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|rc
operator|!=
name|NGX_HTTP_NOT_FOUND
operator|||
name|clcf
operator|->
name|log_not_found
condition|)
block|{
name|ngx_log_error
argument_list|(
name|level
argument_list|,
name|log
argument_list|,
name|of
operator|.
name|err
argument_list|,
name|ngx_open_file_n
literal|" \"%s\" failed"
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
return|return
name|rc
return|;
block|}
if|if
condition|(
operator|!
name|of
operator|.
name|is_file
condition|)
block|{
if|if
condition|(
name|ngx_close_file
argument_list|(
name|of
operator|.
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_DECLINED
return|;
block|}
name|start
operator|=
literal|0
expr_stmt|;
name|len
operator|=
name|of
operator|.
name|size
expr_stmt|;
name|i
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|args
operator|.
name|len
condition|)
block|{
name|p
operator|=
operator|(
name|u_char
operator|*
operator|)
name|ngx_strnstr
argument_list|(
name|r
operator|->
name|args
operator|.
name|data
argument_list|,
literal|"start="
argument_list|,
name|r
operator|->
name|args
operator|.
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
block|{
name|p
operator|+=
literal|6
expr_stmt|;
for|for
control|(
name|n
operator|=
name|p
init|;
name|n
operator|<
name|r
operator|->
name|args
operator|.
name|data
operator|+
name|r
operator|->
name|args
operator|.
name|len
condition|;
name|n
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|n
operator|==
literal|'&'
condition|)
block|{
break|break;
block|}
block|}
name|start
operator|=
name|ngx_atoof
argument_list|(
name|p
argument_list|,
name|n
operator|-
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|start
operator|==
name|NGX_ERROR
operator|||
name|start
operator|>=
name|len
condition|)
block|{
name|start
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|start
condition|)
block|{
name|len
operator|=
sizeof|sizeof
argument_list|(
name|ngx_flv_header
argument_list|)
operator|-
literal|1
operator|+
name|len
operator|-
name|start
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
name|log
operator|->
name|action
operator|=
literal|"sending flv to client"
expr_stmt|;
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
name|len
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
operator|=
name|of
operator|.
name|mtime
expr_stmt|;
if|if
condition|(
name|ngx_http_set_content_type
argument_list|(
name|r
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
if|if
condition|(
name|i
operator|==
literal|0
condition|)
block|{
name|b
operator|=
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_buf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|b
operator|->
name|pos
operator|=
name|ngx_flv_header
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_flv_header
operator|+
sizeof|sizeof
argument_list|(
name|ngx_flv_header
argument_list|)
operator|-
literal|1
expr_stmt|;
name|b
operator|->
name|memory
operator|=
literal|1
expr_stmt|;
name|out
index|[
literal|0
index|]
operator|.
name|buf
operator|=
name|b
expr_stmt|;
name|out
index|[
literal|0
index|]
operator|.
name|next
operator|=
operator|&
name|out
index|[
literal|1
index|]
expr_stmt|;
block|}
else|else
block|{
name|r
operator|->
name|allow_ranges
operator|=
literal|1
expr_stmt|;
block|}
name|b
operator|=
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_buf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|b
operator|->
name|file
operator|=
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_file_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
operator|->
name|file
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
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
name|b
operator|->
name|file_pos
operator|=
name|start
expr_stmt|;
name|b
operator|->
name|file_last
operator|=
name|of
operator|.
name|size
expr_stmt|;
name|b
operator|->
name|in_file
operator|=
name|b
operator|->
name|file_last
condition|?
literal|1
else|:
literal|0
expr_stmt|;
name|b
operator|->
name|last_buf
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|last_in_chain
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|file
operator|->
name|fd
operator|=
name|of
operator|.
name|fd
expr_stmt|;
name|b
operator|->
name|file
operator|->
name|name
operator|=
name|path
expr_stmt|;
name|b
operator|->
name|file
operator|->
name|log
operator|=
name|log
expr_stmt|;
name|out
index|[
literal|1
index|]
operator|.
name|buf
operator|=
name|b
expr_stmt|;
name|out
index|[
literal|1
index|]
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
return|return
name|ngx_http_output_filter
argument_list|(
name|r
argument_list|,
operator|&
name|out
index|[
name|i
index|]
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_flv (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_flv
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
name|ngx_http_flv_handler
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

