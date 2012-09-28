begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Maxim Dounin  * Copyright (C) Nginx, Inc.  */
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

begin_include
include|#
directive|include
file|<zlib.h>
end_include

begin_typedef
DECL|struct|__anon27edf2190108
typedef|typedef
struct|struct
block|{
DECL|member|enable
name|ngx_flag_t
name|enable
decl_stmt|;
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
DECL|typedef|ngx_http_gunzip_conf_t
block|}
name|ngx_http_gunzip_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27edf2190208
typedef|typedef
struct|struct
block|{
DECL|member|in
name|ngx_chain_t
modifier|*
name|in
decl_stmt|;
DECL|member|free
name|ngx_chain_t
modifier|*
name|free
decl_stmt|;
DECL|member|busy
name|ngx_chain_t
modifier|*
name|busy
decl_stmt|;
DECL|member|out
name|ngx_chain_t
modifier|*
name|out
decl_stmt|;
DECL|member|last_out
name|ngx_chain_t
modifier|*
modifier|*
name|last_out
decl_stmt|;
DECL|member|in_buf
name|ngx_buf_t
modifier|*
name|in_buf
decl_stmt|;
DECL|member|out_buf
name|ngx_buf_t
modifier|*
name|out_buf
decl_stmt|;
DECL|member|bufs
name|ngx_int_t
name|bufs
decl_stmt|;
DECL|member|started
name|unsigned
name|started
range|:
literal|1
decl_stmt|;
DECL|member|flush
name|unsigned
name|flush
range|:
literal|4
decl_stmt|;
DECL|member|redo
name|unsigned
name|redo
range|:
literal|1
decl_stmt|;
DECL|member|done
name|unsigned
name|done
range|:
literal|1
decl_stmt|;
DECL|member|nomem
name|unsigned
name|nomem
range|:
literal|1
decl_stmt|;
DECL|member|zstream
name|z_stream
name|zstream
decl_stmt|;
DECL|member|request
name|ngx_http_request_t
modifier|*
name|request
decl_stmt|;
DECL|typedef|ngx_http_gunzip_ctx_t
block|}
name|ngx_http_gunzip_ctx_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_gunzip_filter_inflate_start
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_gunzip_filter_add_data
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_gunzip_filter_get_buf
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_gunzip_filter_inflate
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_gunzip_filter_inflate_end
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_gunzip_filter_alloc
parameter_list|(
name|void
modifier|*
name|opaque
parameter_list|,
name|u_int
name|items
parameter_list|,
name|u_int
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_http_gunzip_filter_free
parameter_list|(
name|void
modifier|*
name|opaque
parameter_list|,
name|void
modifier|*
name|address
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_gunzip_filter_init
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
name|ngx_http_gunzip_create_conf
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
name|ngx_http_gunzip_merge_conf
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

begin_decl_stmt
DECL|variable|ngx_http_gunzip_filter_commands
specifier|static
name|ngx_command_t
name|ngx_http_gunzip_filter_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"gunzip"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_conf_set_flag_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_gunzip_conf_t
argument_list|,
name|enable
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"gunzip_buffers"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_TAKE2
block|,
name|ngx_conf_set_bufs_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_gunzip_conf_t
argument_list|,
name|bufs
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
DECL|variable|ngx_http_gunzip_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_gunzip_filter_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_gunzip_filter_init
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
name|ngx_http_gunzip_create_conf
block|,
comment|/* create location configuration */
name|ngx_http_gunzip_merge_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_gunzip_filter_module
name|ngx_module_t
name|ngx_http_gunzip_filter_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_gunzip_filter_module_ctx
block|,
comment|/* module context */
name|ngx_http_gunzip_filter_commands
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

begin_decl_stmt
DECL|variable|ngx_http_next_header_filter
specifier|static
name|ngx_http_output_header_filter_pt
name|ngx_http_next_header_filter
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_next_body_filter
specifier|static
name|ngx_http_output_body_filter_pt
name|ngx_http_next_body_filter
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_gunzip_header_filter (ngx_http_request_t * r)
name|ngx_http_gunzip_header_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_gunzip_conf_t
modifier|*
name|conf
decl_stmt|;
name|conf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_gunzip_filter_module
argument_list|)
expr_stmt|;
comment|/* TODO support multiple content-codings */
comment|/* TODO always gunzip - due to configuration or module request */
comment|/* TODO ignore content encoding? */
if|if
condition|(
operator|!
name|conf
operator|->
name|enable
operator|||
name|r
operator|->
name|headers_out
operator|.
name|content_encoding
operator|==
name|NULL
operator|||
name|r
operator|->
name|headers_out
operator|.
name|content_encoding
operator|->
name|value
operator|.
name|len
operator|!=
literal|4
operator|||
name|ngx_strncasecmp
argument_list|(
name|r
operator|->
name|headers_out
operator|.
name|content_encoding
operator|->
name|value
operator|.
name|data
argument_list|,
operator|(
name|u_char
operator|*
operator|)
literal|"gzip"
argument_list|,
literal|4
argument_list|)
operator|!=
literal|0
condition|)
block|{
return|return
name|ngx_http_next_header_filter
argument_list|(
name|r
argument_list|)
return|;
block|}
name|r
operator|->
name|gzip_vary
operator|=
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|r
operator|->
name|gzip_tested
condition|)
block|{
if|if
condition|(
name|ngx_http_gzip_ok
argument_list|(
name|r
argument_list|)
operator|==
name|NGX_OK
condition|)
block|{
return|return
name|ngx_http_next_header_filter
argument_list|(
name|r
argument_list|)
return|;
block|}
block|}
if|else if
condition|(
operator|!
name|r
operator|->
name|gzip_ok
condition|)
block|{
return|return
name|ngx_http_next_header_filter
argument_list|(
name|r
argument_list|)
return|;
block|}
name|ctx
operator|=
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_gunzip_ctx_t
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
name|ngx_http_set_ctx
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|,
name|ngx_http_gunzip_filter_module
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|request
operator|=
name|r
expr_stmt|;
name|r
operator|->
name|filter_need_in_memory
operator|=
literal|1
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_encoding
operator|->
name|hash
operator|=
literal|0
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_encoding
operator|=
name|NULL
expr_stmt|;
name|ngx_http_clear_content_length
argument_list|(
name|r
argument_list|)
expr_stmt|;
name|ngx_http_clear_accept_ranges
argument_list|(
name|r
argument_list|)
expr_stmt|;
return|return
name|ngx_http_next_header_filter
argument_list|(
name|r
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_gunzip_body_filter (ngx_http_request_t * r,ngx_chain_t * in)
name|ngx_http_gunzip_body_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ctx
operator|=
name|ngx_http_get_module_ctx
argument_list|(
name|r
argument_list|,
name|ngx_http_gunzip_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|==
name|NULL
operator|||
name|ctx
operator|->
name|done
condition|)
block|{
return|return
name|ngx_http_next_body_filter
argument_list|(
name|r
argument_list|,
name|in
argument_list|)
return|;
block|}
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
literal|"http gunzip filter"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ctx
operator|->
name|started
condition|)
block|{
if|if
condition|(
name|ngx_http_gunzip_filter_inflate_start
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
block|}
if|if
condition|(
name|in
condition|)
block|{
if|if
condition|(
name|ngx_chain_add_copy
argument_list|(
name|r
operator|->
name|pool
argument_list|,
operator|&
name|ctx
operator|->
name|in
argument_list|,
name|in
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
block|}
if|if
condition|(
name|ctx
operator|->
name|nomem
condition|)
block|{
comment|/* flush busy buffers */
if|if
condition|(
name|ngx_http_next_body_filter
argument_list|(
name|r
argument_list|,
name|NULL
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
name|cl
operator|=
name|NULL
expr_stmt|;
name|ngx_chain_update_chains
argument_list|(
name|r
operator|->
name|pool
argument_list|,
operator|&
name|ctx
operator|->
name|free
argument_list|,
operator|&
name|ctx
operator|->
name|busy
argument_list|,
operator|&
name|cl
argument_list|,
operator|(
name|ngx_buf_tag_t
operator|)
operator|&
name|ngx_http_gunzip_filter_module
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|nomem
operator|=
literal|0
expr_stmt|;
block|}
for|for
control|(
init|;
condition|;
control|)
block|{
comment|/* cycle while we can write to a client */
for|for
control|(
init|;
condition|;
control|)
block|{
comment|/* cycle while there is data to feed zlib and ... */
name|rc
operator|=
name|ngx_http_gunzip_filter_add_data
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_DECLINED
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_AGAIN
condition|)
block|{
continue|continue;
block|}
comment|/* ... there are buffers to write zlib output */
name|rc
operator|=
name|ngx_http_gunzip_filter_get_buf
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_DECLINED
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
name|rc
operator|=
name|ngx_http_gunzip_filter_inflate
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_OK
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
comment|/* rc == NGX_AGAIN */
block|}
if|if
condition|(
name|ctx
operator|->
name|out
operator|==
name|NULL
condition|)
block|{
return|return
name|ctx
operator|->
name|busy
condition|?
name|NGX_AGAIN
else|:
name|NGX_OK
return|;
block|}
name|rc
operator|=
name|ngx_http_next_body_filter
argument_list|(
name|r
argument_list|,
name|ctx
operator|->
name|out
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
name|ngx_chain_update_chains
argument_list|(
name|r
operator|->
name|pool
argument_list|,
operator|&
name|ctx
operator|->
name|free
argument_list|,
operator|&
name|ctx
operator|->
name|busy
argument_list|,
operator|&
name|ctx
operator|->
name|out
argument_list|,
operator|(
name|ngx_buf_tag_t
operator|)
operator|&
name|ngx_http_gunzip_filter_module
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|ctx
operator|->
name|out
expr_stmt|;
name|ngx_log_debug1
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
literal|"gunzip out: %p"
argument_list|,
name|ctx
operator|->
name|out
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|nomem
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|done
condition|)
block|{
return|return
name|rc
return|;
block|}
block|}
comment|/* unreachable */
name|failed
label|:
name|ctx
operator|->
name|done
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_gunzip_filter_inflate_start (ngx_http_request_t * r,ngx_http_gunzip_ctx_t * ctx)
name|ngx_http_gunzip_filter_inflate_start
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|ctx
operator|->
name|zstream
operator|.
name|next_in
operator|=
name|Z_NULL
expr_stmt|;
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
operator|=
literal|0
expr_stmt|;
name|ctx
operator|->
name|zstream
operator|.
name|zalloc
operator|=
name|ngx_http_gunzip_filter_alloc
expr_stmt|;
name|ctx
operator|->
name|zstream
operator|.
name|zfree
operator|=
name|ngx_http_gunzip_filter_free
expr_stmt|;
name|ctx
operator|->
name|zstream
operator|.
name|opaque
operator|=
name|ctx
expr_stmt|;
comment|/* windowBits +16 to decode gzip, zlib 1.2.0.4+ */
name|rc
operator|=
name|inflateInit2
argument_list|(
operator|&
name|ctx
operator|->
name|zstream
argument_list|,
name|MAX_WBITS
operator|+
literal|16
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|Z_OK
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"inflateInit2() failed: %d"
argument_list|,
name|rc
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ctx
operator|->
name|started
operator|=
literal|1
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|ctx
operator|->
name|out
expr_stmt|;
name|ctx
operator|->
name|flush
operator|=
name|Z_NO_FLUSH
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_gunzip_filter_add_data (ngx_http_request_t * r,ngx_http_gunzip_ctx_t * ctx)
name|ngx_http_gunzip_filter_add_data
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
if|if
condition|(
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
operator|||
name|ctx
operator|->
name|flush
operator|!=
name|Z_NO_FLUSH
operator|||
name|ctx
operator|->
name|redo
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_debug1
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
literal|"gunzip in: %p"
argument_list|,
name|ctx
operator|->
name|in
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|in
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|ctx
operator|->
name|in_buf
operator|=
name|ctx
operator|->
name|in
operator|->
name|buf
expr_stmt|;
name|ctx
operator|->
name|in
operator|=
name|ctx
operator|->
name|in
operator|->
name|next
expr_stmt|;
name|ctx
operator|->
name|zstream
operator|.
name|next_in
operator|=
name|ctx
operator|->
name|in_buf
operator|->
name|pos
expr_stmt|;
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
operator|=
name|ctx
operator|->
name|in_buf
operator|->
name|last
operator|-
name|ctx
operator|->
name|in_buf
operator|->
name|pos
expr_stmt|;
name|ngx_log_debug3
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
literal|"gunzip in_buf:%p ni:%p ai:%ud"
argument_list|,
name|ctx
operator|->
name|in_buf
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|next_in
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|in_buf
operator|->
name|last_buf
operator|||
name|ctx
operator|->
name|in_buf
operator|->
name|last_in_chain
condition|)
block|{
name|ctx
operator|->
name|flush
operator|=
name|Z_FINISH
expr_stmt|;
block|}
if|else if
condition|(
name|ctx
operator|->
name|in_buf
operator|->
name|flush
condition|)
block|{
name|ctx
operator|->
name|flush
operator|=
name|Z_SYNC_FLUSH
expr_stmt|;
block|}
if|else if
condition|(
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
operator|==
literal|0
condition|)
block|{
comment|/* ctx->flush == Z_NO_FLUSH */
return|return
name|NGX_AGAIN
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
DECL|function|ngx_http_gunzip_filter_get_buf (ngx_http_request_t * r,ngx_http_gunzip_ctx_t * ctx)
name|ngx_http_gunzip_filter_get_buf
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|ngx_http_gunzip_conf_t
modifier|*
name|conf
decl_stmt|;
if|if
condition|(
name|ctx
operator|->
name|zstream
operator|.
name|avail_out
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|conf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_gunzip_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|free
condition|)
block|{
name|ctx
operator|->
name|out_buf
operator|=
name|ctx
operator|->
name|free
operator|->
name|buf
expr_stmt|;
name|ctx
operator|->
name|free
operator|=
name|ctx
operator|->
name|free
operator|->
name|next
expr_stmt|;
name|ctx
operator|->
name|out_buf
operator|->
name|flush
operator|=
literal|0
expr_stmt|;
block|}
if|else if
condition|(
name|ctx
operator|->
name|bufs
operator|<
name|conf
operator|->
name|bufs
operator|.
name|num
condition|)
block|{
name|ctx
operator|->
name|out_buf
operator|=
name|ngx_create_temp_buf
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|conf
operator|->
name|bufs
operator|.
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|out_buf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ctx
operator|->
name|out_buf
operator|->
name|tag
operator|=
operator|(
name|ngx_buf_tag_t
operator|)
operator|&
name|ngx_http_gunzip_filter_module
expr_stmt|;
name|ctx
operator|->
name|out_buf
operator|->
name|recycled
operator|=
literal|1
expr_stmt|;
name|ctx
operator|->
name|bufs
operator|++
expr_stmt|;
block|}
else|else
block|{
name|ctx
operator|->
name|nomem
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_DECLINED
return|;
block|}
name|ctx
operator|->
name|zstream
operator|.
name|next_out
operator|=
name|ctx
operator|->
name|out_buf
operator|->
name|pos
expr_stmt|;
name|ctx
operator|->
name|zstream
operator|.
name|avail_out
operator|=
name|conf
operator|->
name|bufs
operator|.
name|size
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_gunzip_filter_inflate (ngx_http_request_t * r,ngx_http_gunzip_ctx_t * ctx)
name|ngx_http_gunzip_filter_inflate
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|ngx_log_debug6
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
literal|"inflate in: ni:%p no:%p ai:%ud ao:%ud fl:%d redo:%d"
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|next_in
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|next_out
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|avail_out
argument_list|,
name|ctx
operator|->
name|flush
argument_list|,
name|ctx
operator|->
name|redo
argument_list|)
expr_stmt|;
name|rc
operator|=
name|inflate
argument_list|(
operator|&
name|ctx
operator|->
name|zstream
argument_list|,
name|ctx
operator|->
name|flush
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|Z_OK
operator|&&
name|rc
operator|!=
name|Z_STREAM_END
operator|&&
name|rc
operator|!=
name|Z_BUF_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"inflate() failed: %d, %d"
argument_list|,
name|ctx
operator|->
name|flush
argument_list|,
name|rc
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_debug5
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
literal|"inflate out: ni:%p no:%p ai:%ud ao:%ud rc:%d"
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|next_in
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|next_out
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
argument_list|,
name|ctx
operator|->
name|zstream
operator|.
name|avail_out
argument_list|,
name|rc
argument_list|)
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
literal|"gunzip in_buf:%p pos:%p"
argument_list|,
name|ctx
operator|->
name|in_buf
argument_list|,
name|ctx
operator|->
name|in_buf
operator|->
name|pos
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|zstream
operator|.
name|next_in
condition|)
block|{
name|ctx
operator|->
name|in_buf
operator|->
name|pos
operator|=
name|ctx
operator|->
name|zstream
operator|.
name|next_in
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
operator|==
literal|0
condition|)
block|{
name|ctx
operator|->
name|zstream
operator|.
name|next_in
operator|=
name|NULL
expr_stmt|;
block|}
block|}
name|ctx
operator|->
name|out_buf
operator|->
name|last
operator|=
name|ctx
operator|->
name|zstream
operator|.
name|next_out
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|zstream
operator|.
name|avail_out
operator|==
literal|0
condition|)
block|{
comment|/* zlib wants to output some more data */
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|cl
operator|->
name|buf
operator|=
name|ctx
operator|->
name|out_buf
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
operator|*
name|ctx
operator|->
name|last_out
operator|=
name|cl
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
name|ctx
operator|->
name|redo
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|ctx
operator|->
name|redo
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|flush
operator|==
name|Z_SYNC_FLUSH
condition|)
block|{
name|ctx
operator|->
name|flush
operator|=
name|Z_NO_FLUSH
expr_stmt|;
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|b
operator|=
name|ctx
operator|->
name|out_buf
expr_stmt|;
if|if
condition|(
name|ngx_buf_size
argument_list|(
name|b
argument_list|)
operator|==
literal|0
condition|)
block|{
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|ctx
operator|->
name|request
operator|->
name|pool
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
name|NGX_ERROR
return|;
block|}
block|}
else|else
block|{
name|ctx
operator|->
name|zstream
operator|.
name|avail_out
operator|=
literal|0
expr_stmt|;
block|}
name|b
operator|->
name|flush
operator|=
literal|1
expr_stmt|;
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
operator|*
name|ctx
operator|->
name|last_out
operator|=
name|cl
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|Z_STREAM_END
operator|&&
name|ctx
operator|->
name|flush
operator|==
name|Z_FINISH
operator|&&
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|ngx_http_gunzip_filter_inflate_end
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|Z_STREAM_END
operator|&&
name|ctx
operator|->
name|zstream
operator|.
name|avail_in
operator|>
literal|0
condition|)
block|{
name|rc
operator|=
name|inflateReset
argument_list|(
operator|&
name|ctx
operator|->
name|zstream
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|Z_OK
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"inflateReset() failed: %d"
argument_list|,
name|rc
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ctx
operator|->
name|redo
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|ctx
operator|->
name|in
operator|==
name|NULL
condition|)
block|{
name|b
operator|=
name|ctx
operator|->
name|out_buf
expr_stmt|;
if|if
condition|(
name|ngx_buf_size
argument_list|(
name|b
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ctx
operator|->
name|zstream
operator|.
name|avail_out
operator|=
literal|0
expr_stmt|;
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
operator|*
name|ctx
operator|->
name|last_out
operator|=
name|cl
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
return|return
name|NGX_AGAIN
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_gunzip_filter_inflate_end (ngx_http_request_t * r,ngx_http_gunzip_ctx_t * ctx)
name|ngx_http_gunzip_filter_inflate_end
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
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
literal|"gunzip inflate end"
argument_list|)
expr_stmt|;
name|rc
operator|=
name|inflateEnd
argument_list|(
operator|&
name|ctx
operator|->
name|zstream
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|Z_OK
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"inflateEnd() failed: %d"
argument_list|,
name|rc
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|b
operator|=
name|ctx
operator|->
name|out_buf
expr_stmt|;
if|if
condition|(
name|ngx_buf_size
argument_list|(
name|b
argument_list|)
operator|==
literal|0
condition|)
block|{
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|ctx
operator|->
name|request
operator|->
name|pool
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
name|NGX_ERROR
return|;
block|}
block|}
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
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
operator|*
name|ctx
operator|->
name|last_out
operator|=
name|cl
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
name|b
operator|->
name|last_buf
operator|=
operator|(
name|r
operator|==
name|r
operator|->
expr|main
operator|)
condition|?
literal|1
else|:
literal|0
expr_stmt|;
name|b
operator|->
name|last_in_chain
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|sync
operator|=
literal|1
expr_stmt|;
name|ctx
operator|->
name|done
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_gunzip_filter_alloc (void * opaque,u_int items,u_int size)
name|ngx_http_gunzip_filter_alloc
parameter_list|(
name|void
modifier|*
name|opaque
parameter_list|,
name|u_int
name|items
parameter_list|,
name|u_int
name|size
parameter_list|)
block|{
name|ngx_http_gunzip_ctx_t
modifier|*
name|ctx
init|=
name|opaque
decl_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|ctx
operator|->
name|request
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"gunzip alloc: n:%ud s:%ud"
argument_list|,
name|items
argument_list|,
name|size
argument_list|)
expr_stmt|;
return|return
name|ngx_palloc
argument_list|(
name|ctx
operator|->
name|request
operator|->
name|pool
argument_list|,
name|items
operator|*
name|size
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_http_gunzip_filter_free (void * opaque,void * address)
name|ngx_http_gunzip_filter_free
parameter_list|(
name|void
modifier|*
name|opaque
parameter_list|,
name|void
modifier|*
name|address
parameter_list|)
block|{
if|#
directive|if
literal|0
block_content|ngx_http_gunzip_ctx_t *ctx = opaque;      ngx_log_debug1(NGX_LOG_DEBUG_HTTP, ctx->request->connection->log, 0,                    "gunzip free: %p", address);
endif|#
directive|endif
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_gunzip_create_conf (ngx_conf_t * cf)
name|ngx_http_gunzip_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_gunzip_conf_t
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
name|ngx_http_gunzip_conf_t
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
comment|/*      * set by ngx_pcalloc():      *      *     conf->bufs.num = 0;      */
name|conf
operator|->
name|enable
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_gunzip_merge_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_gunzip_merge_conf
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
name|ngx_http_gunzip_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_gunzip_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|enable
argument_list|,
name|prev
operator|->
name|enable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|ngx_conf_merge_bufs_value
argument_list|(
name|conf
operator|->
name|bufs
argument_list|,
name|prev
operator|->
name|bufs
argument_list|,
operator|(
literal|128
operator|*
literal|1024
operator|)
operator|/
name|ngx_pagesize
argument_list|,
name|ngx_pagesize
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_gunzip_filter_init (ngx_conf_t * cf)
name|ngx_http_gunzip_filter_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_next_header_filter
operator|=
name|ngx_http_top_header_filter
expr_stmt|;
name|ngx_http_top_header_filter
operator|=
name|ngx_http_gunzip_header_filter
expr_stmt|;
name|ngx_http_next_body_filter
operator|=
name|ngx_http_top_body_filter
expr_stmt|;
name|ngx_http_top_body_filter
operator|=
name|ngx_http_gunzip_body_filter
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit
