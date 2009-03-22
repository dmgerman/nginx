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
DECL|struct|__anon2a0550830108
typedef|typedef
struct|struct
block|{
DECL|member|match
name|ngx_str_t
name|match
decl_stmt|;
DECL|member|value
name|ngx_http_complex_value_t
name|value
decl_stmt|;
DECL|member|types
name|ngx_hash_t
name|types
decl_stmt|;
DECL|member|once
name|ngx_flag_t
name|once
decl_stmt|;
DECL|member|types_keys
name|ngx_array_t
modifier|*
name|types_keys
decl_stmt|;
DECL|typedef|ngx_http_sub_loc_conf_t
block|}
name|ngx_http_sub_loc_conf_t
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2a0550830203
typedef|typedef
enum|enum
block|{
DECL|enumerator|sub_start_state
name|sub_start_state
init|=
literal|0
block|,
DECL|enumerator|sub_match_state
name|sub_match_state
block|, }
DECL|typedef|ngx_http_sub_state_e
name|ngx_http_sub_state_e
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a0550830308
typedef|typedef
struct|struct
block|{
DECL|member|match
name|ngx_str_t
name|match
decl_stmt|;
DECL|member|once
name|ngx_uint_t
name|once
decl_stmt|;
comment|/* unsigned  once:1 */
DECL|member|buf
name|ngx_buf_t
modifier|*
name|buf
decl_stmt|;
DECL|member|pos
name|u_char
modifier|*
name|pos
decl_stmt|;
DECL|member|copy_start
name|u_char
modifier|*
name|copy_start
decl_stmt|;
DECL|member|copy_end
name|u_char
modifier|*
name|copy_end
decl_stmt|;
DECL|member|in
name|ngx_chain_t
modifier|*
name|in
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
DECL|member|busy
name|ngx_chain_t
modifier|*
name|busy
decl_stmt|;
DECL|member|free
name|ngx_chain_t
modifier|*
name|free
decl_stmt|;
DECL|member|sub
name|ngx_str_t
name|sub
decl_stmt|;
DECL|member|state
name|ngx_uint_t
name|state
decl_stmt|;
DECL|member|saved
name|size_t
name|saved
decl_stmt|;
DECL|member|looked
name|size_t
name|looked
decl_stmt|;
DECL|typedef|ngx_http_sub_ctx_t
block|}
name|ngx_http_sub_ctx_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_sub_output
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_sub_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_sub_parse
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_sub_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_sub_filter
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
name|ngx_http_sub_create_conf
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
name|ngx_http_sub_merge_conf
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
name|ngx_http_sub_filter_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_sub_filter_commands
specifier|static
name|ngx_command_t
name|ngx_http_sub_filter_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"sub_filter"
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
name|ngx_http_sub_filter
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"sub_filter_types"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_http_types_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_sub_loc_conf_t
argument_list|,
name|types_keys
argument_list|)
block|,
operator|&
name|ngx_http_html_default_types
index|[
literal|0
index|]
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"sub_filter_once"
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
name|ngx_http_sub_loc_conf_t
argument_list|,
name|once
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
DECL|variable|ngx_http_sub_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_sub_filter_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_sub_filter_init
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
name|ngx_http_sub_create_conf
block|,
comment|/* create location configuration */
name|ngx_http_sub_merge_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_sub_filter_module
name|ngx_module_t
name|ngx_http_sub_filter_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_sub_filter_module_ctx
block|,
comment|/* module context */
name|ngx_http_sub_filter_commands
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
DECL|function|ngx_http_sub_header_filter (ngx_http_request_t * r)
name|ngx_http_sub_header_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_http_sub_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_sub_loc_conf_t
modifier|*
name|slcf
decl_stmt|;
name|slcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_sub_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|slcf
operator|->
name|match
operator|.
name|len
operator|==
literal|0
operator|||
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|==
literal|0
operator|||
name|ngx_http_test_content_type
argument_list|(
name|r
argument_list|,
operator|&
name|slcf
operator|->
name|types
argument_list|)
operator|==
name|NULL
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
name|ngx_http_sub_ctx_t
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
name|ngx_http_sub_filter_module
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|match
operator|=
name|slcf
operator|->
name|match
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
name|r
operator|->
name|filter_need_in_memory
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|r
operator|==
name|r
operator|->
expr|main
condition|)
block|{
name|ngx_http_clear_content_length
argument_list|(
name|r
argument_list|)
expr_stmt|;
name|ngx_http_clear_last_modified
argument_list|(
name|r
argument_list|)
expr_stmt|;
block|}
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
DECL|function|ngx_http_sub_body_filter (ngx_http_request_t * r,ngx_chain_t * in)
name|ngx_http_sub_body_filter
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
name|ngx_int_t
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
name|ngx_http_sub_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_sub_loc_conf_t
modifier|*
name|slcf
decl_stmt|;
name|ctx
operator|=
name|ngx_http_get_module_ctx
argument_list|(
name|r
argument_list|,
name|ngx_http_sub_filter_module
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
name|ngx_http_next_body_filter
argument_list|(
name|r
argument_list|,
name|in
argument_list|)
return|;
block|}
if|if
condition|(
operator|(
name|in
operator|==
name|NULL
operator|&&
name|ctx
operator|->
name|buf
operator|==
name|NULL
operator|&&
name|ctx
operator|->
name|in
operator|==
name|NULL
operator|&&
name|ctx
operator|->
name|busy
operator|==
name|NULL
operator|)
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
if|if
condition|(
name|ctx
operator|->
name|once
operator|&&
operator|(
name|ctx
operator|->
name|buf
operator|==
name|NULL
operator|||
name|ctx
operator|->
name|in
operator|==
name|NULL
operator|)
condition|)
block|{
if|if
condition|(
name|ctx
operator|->
name|busy
condition|)
block|{
if|if
condition|(
name|ngx_http_sub_output
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
return|return
name|ngx_http_next_body_filter
argument_list|(
name|r
argument_list|,
name|in
argument_list|)
return|;
block|}
comment|/* add the incoming chain to the chain ctx->in */
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
return|return
name|NGX_ERROR
return|;
block|}
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
literal|"http sub filter \"%V\""
argument_list|,
operator|&
name|r
operator|->
name|uri
argument_list|)
expr_stmt|;
while|while
condition|(
name|ctx
operator|->
name|in
operator|||
name|ctx
operator|->
name|buf
condition|)
block|{
if|if
condition|(
name|ctx
operator|->
name|buf
operator|==
name|NULL
condition|)
block|{
name|ctx
operator|->
name|buf
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
name|pos
operator|=
name|ctx
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
block|}
if|if
condition|(
name|ctx
operator|->
name|state
operator|==
name|sub_start_state
condition|)
block|{
name|ctx
operator|->
name|copy_start
operator|=
name|ctx
operator|->
name|pos
expr_stmt|;
name|ctx
operator|->
name|copy_end
operator|=
name|ctx
operator|->
name|pos
expr_stmt|;
block|}
name|b
operator|=
name|NULL
expr_stmt|;
while|while
condition|(
name|ctx
operator|->
name|pos
operator|<
name|ctx
operator|->
name|buf
operator|->
name|last
condition|)
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
literal|"saved: %d state: %d"
argument_list|,
name|ctx
operator|->
name|saved
argument_list|,
name|ctx
operator|->
name|state
argument_list|)
expr_stmt|;
name|rc
operator|=
name|ngx_http_sub_parse
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|)
expr_stmt|;
name|ngx_log_debug4
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
literal|"parse: %d, looked: %d %p-%p"
argument_list|,
name|rc
argument_list|,
name|ctx
operator|->
name|looked
argument_list|,
name|ctx
operator|->
name|copy_start
argument_list|,
name|ctx
operator|->
name|copy_end
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
name|rc
return|;
block|}
if|if
condition|(
name|ctx
operator|->
name|copy_start
operator|!=
name|ctx
operator|->
name|copy_end
condition|)
block|{
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
literal|"saved: %d"
argument_list|,
name|ctx
operator|->
name|saved
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|saved
condition|)
block|{
if|if
condition|(
name|ctx
operator|->
name|free
condition|)
block|{
name|cl
operator|=
name|ctx
operator|->
name|free
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
name|b
operator|=
name|cl
operator|->
name|buf
expr_stmt|;
name|ngx_memzero
argument_list|(
name|b
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_buf_t
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|r
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
block|}
name|b
operator|->
name|memory
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|pos
operator|=
name|ctx
operator|->
name|match
operator|.
name|data
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ctx
operator|->
name|match
operator|.
name|data
operator|+
name|ctx
operator|->
name|saved
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
name|saved
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|ctx
operator|->
name|free
condition|)
block|{
name|cl
operator|=
name|ctx
operator|->
name|free
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
name|b
operator|=
name|cl
operator|->
name|buf
expr_stmt|;
block|}
else|else
block|{
name|b
operator|=
name|ngx_alloc_buf
argument_list|(
name|r
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
block|}
name|ngx_memcpy
argument_list|(
name|b
argument_list|,
name|ctx
operator|->
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_buf_t
argument_list|)
argument_list|)
expr_stmt|;
name|b
operator|->
name|pos
operator|=
name|ctx
operator|->
name|copy_start
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ctx
operator|->
name|copy_end
expr_stmt|;
name|b
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|b
operator|->
name|last_buf
operator|=
literal|0
expr_stmt|;
name|b
operator|->
name|recycled
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|b
operator|->
name|in_file
condition|)
block|{
name|b
operator|->
name|file_last
operator|=
name|b
operator|->
name|file_pos
operator|+
operator|(
name|b
operator|->
name|last
operator|-
name|ctx
operator|->
name|buf
operator|->
name|pos
operator|)
expr_stmt|;
name|b
operator|->
name|file_pos
operator|+=
name|b
operator|->
name|pos
operator|-
name|ctx
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
block|}
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
block|}
if|if
condition|(
name|ctx
operator|->
name|state
operator|==
name|sub_start_state
condition|)
block|{
name|ctx
operator|->
name|copy_start
operator|=
name|ctx
operator|->
name|pos
expr_stmt|;
name|ctx
operator|->
name|copy_end
operator|=
name|ctx
operator|->
name|pos
expr_stmt|;
block|}
else|else
block|{
name|ctx
operator|->
name|copy_start
operator|=
name|NULL
expr_stmt|;
name|ctx
operator|->
name|copy_end
operator|=
name|NULL
expr_stmt|;
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
comment|/* rc == NGX_OK */
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|r
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
name|slcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_sub_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|sub
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|ngx_http_complex_value
argument_list|(
name|r
argument_list|,
operator|&
name|slcf
operator|->
name|value
argument_list|,
operator|&
name|ctx
operator|->
name|sub
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
if|if
condition|(
name|ctx
operator|->
name|sub
operator|.
name|len
condition|)
block|{
name|b
operator|->
name|memory
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|pos
operator|=
name|ctx
operator|->
name|sub
operator|.
name|data
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ctx
operator|->
name|sub
operator|.
name|data
operator|+
name|ctx
operator|->
name|sub
operator|.
name|len
expr_stmt|;
block|}
else|else
block|{
name|b
operator|->
name|sync
operator|=
literal|1
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
name|once
operator|=
name|slcf
operator|->
name|once
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|ctx
operator|->
name|buf
operator|->
name|last_buf
operator|||
name|ngx_buf_in_memory
argument_list|(
name|ctx
operator|->
name|buf
argument_list|)
condition|)
block|{
if|if
condition|(
name|b
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|ctx
operator|->
name|free
condition|)
block|{
name|cl
operator|=
name|ctx
operator|->
name|free
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
name|b
operator|=
name|cl
operator|->
name|buf
expr_stmt|;
name|ngx_memzero
argument_list|(
name|b
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_buf_t
argument_list|)
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|r
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
block|}
name|b
operator|->
name|sync
operator|=
literal|1
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
block|}
name|b
operator|->
name|last_buf
operator|=
name|ctx
operator|->
name|buf
operator|->
name|last_buf
expr_stmt|;
name|b
operator|->
name|shadow
operator|=
name|ctx
operator|->
name|buf
expr_stmt|;
name|b
operator|->
name|recycled
operator|=
name|ctx
operator|->
name|buf
operator|->
name|recycled
expr_stmt|;
block|}
name|ctx
operator|->
name|buf
operator|=
name|NULL
expr_stmt|;
name|ctx
operator|->
name|saved
operator|=
name|ctx
operator|->
name|looked
expr_stmt|;
block|}
if|if
condition|(
name|ctx
operator|->
name|out
operator|==
name|NULL
operator|&&
name|ctx
operator|->
name|busy
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
return|return
name|ngx_http_sub_output
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_sub_output (ngx_http_request_t * r,ngx_http_sub_ctx_t * ctx)
name|ngx_http_sub_output
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_sub_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|ngx_int_t
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
if|#
directive|if
literal|1
name|b
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|cl
operator|=
name|ctx
operator|->
name|out
init|;
name|cl
condition|;
name|cl
operator|=
name|cl
operator|->
name|next
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
literal|"sub out: %p %p"
argument_list|,
name|cl
operator|->
name|buf
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|->
name|buf
operator|==
name|b
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
literal|"the same buf was used in sub"
argument_list|)
expr_stmt|;
name|ngx_debug_point
argument_list|()
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|b
operator|=
name|cl
operator|->
name|buf
expr_stmt|;
block|}
endif|#
directive|endif
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
name|ctx
operator|->
name|busy
operator|==
name|NULL
condition|)
block|{
name|ctx
operator|->
name|busy
operator|=
name|ctx
operator|->
name|out
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|cl
operator|=
name|ctx
operator|->
name|busy
init|;
name|cl
operator|->
name|next
condition|;
name|cl
operator|=
name|cl
operator|->
name|next
control|)
block|{
comment|/* void */
block|}
name|cl
operator|->
name|next
operator|=
name|ctx
operator|->
name|out
expr_stmt|;
block|}
name|ctx
operator|->
name|out
operator|=
name|NULL
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
while|while
condition|(
name|ctx
operator|->
name|busy
condition|)
block|{
name|cl
operator|=
name|ctx
operator|->
name|busy
expr_stmt|;
name|b
operator|=
name|cl
operator|->
name|buf
expr_stmt|;
if|if
condition|(
name|ngx_buf_size
argument_list|(
name|b
argument_list|)
operator|!=
literal|0
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|b
operator|->
name|shadow
condition|)
block|{
name|b
operator|->
name|shadow
operator|->
name|pos
operator|=
name|b
operator|->
name|shadow
operator|->
name|last
expr_stmt|;
block|}
name|ctx
operator|->
name|busy
operator|=
name|cl
operator|->
name|next
expr_stmt|;
if|if
condition|(
name|ngx_buf_in_memory
argument_list|(
name|b
argument_list|)
operator|||
name|b
operator|->
name|in_file
condition|)
block|{
comment|/* add data bufs only to the free buf chain */
name|cl
operator|->
name|next
operator|=
name|ctx
operator|->
name|free
expr_stmt|;
name|ctx
operator|->
name|free
operator|=
name|cl
expr_stmt|;
block|}
block|}
if|if
condition|(
name|ctx
operator|->
name|in
operator|||
name|ctx
operator|->
name|buf
condition|)
block|{
name|r
operator|->
name|buffered
operator||=
name|NGX_HTTP_SUB_BUFFERED
expr_stmt|;
block|}
else|else
block|{
name|r
operator|->
name|buffered
operator|&=
operator|~
name|NGX_HTTP_SUB_BUFFERED
expr_stmt|;
block|}
return|return
name|rc
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_sub_parse (ngx_http_request_t * r,ngx_http_sub_ctx_t * ctx)
name|ngx_http_sub_parse
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_sub_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|,
modifier|*
name|last
decl_stmt|,
modifier|*
name|copy_end
decl_stmt|,
name|ch
decl_stmt|,
name|match
decl_stmt|;
name|size_t
name|looked
decl_stmt|;
name|ngx_http_sub_state_e
name|state
decl_stmt|;
if|if
condition|(
name|ctx
operator|->
name|once
condition|)
block|{
name|ctx
operator|->
name|copy_start
operator|=
name|ctx
operator|->
name|pos
expr_stmt|;
name|ctx
operator|->
name|copy_end
operator|=
name|ctx
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|ctx
operator|->
name|pos
operator|=
name|ctx
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|ctx
operator|->
name|looked
operator|=
literal|0
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
literal|"once"
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|state
operator|=
name|ctx
operator|->
name|state
expr_stmt|;
name|looked
operator|=
name|ctx
operator|->
name|looked
expr_stmt|;
name|last
operator|=
name|ctx
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|copy_end
operator|=
name|ctx
operator|->
name|copy_end
expr_stmt|;
for|for
control|(
name|p
operator|=
name|ctx
operator|->
name|pos
init|;
name|p
operator|<
name|last
condition|;
name|p
operator|++
control|)
block|{
name|ch
operator|=
operator|*
name|p
expr_stmt|;
name|ch
operator|=
name|ngx_tolower
argument_list|(
name|ch
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|==
name|sub_start_state
condition|)
block|{
comment|/* the tight loop */
name|match
operator|=
name|ctx
operator|->
name|match
operator|.
name|data
index|[
literal|0
index|]
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|ch
operator|==
name|match
condition|)
block|{
name|copy_end
operator|=
name|p
expr_stmt|;
name|looked
operator|=
literal|1
expr_stmt|;
name|state
operator|=
name|sub_match_state
expr_stmt|;
goto|goto
name|match_started
goto|;
block|}
if|if
condition|(
operator|++
name|p
operator|==
name|last
condition|)
block|{
break|break;
block|}
name|ch
operator|=
operator|*
name|p
expr_stmt|;
name|ch
operator|=
name|ngx_tolower
argument_list|(
name|ch
argument_list|)
expr_stmt|;
block|}
name|ctx
operator|->
name|state
operator|=
name|state
expr_stmt|;
name|ctx
operator|->
name|pos
operator|=
name|p
expr_stmt|;
name|ctx
operator|->
name|looked
operator|=
name|looked
expr_stmt|;
name|ctx
operator|->
name|copy_end
operator|=
name|p
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|copy_start
operator|==
name|NULL
condition|)
block|{
name|ctx
operator|->
name|copy_start
operator|=
name|ctx
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
block|}
return|return
name|NGX_AGAIN
return|;
name|match_started
label|:
continue|continue;
block|}
comment|/* state == sub_match_state */
if|if
condition|(
name|ch
operator|==
name|ctx
operator|->
name|match
operator|.
name|data
index|[
name|looked
index|]
condition|)
block|{
name|looked
operator|++
expr_stmt|;
if|if
condition|(
name|looked
operator|==
name|ctx
operator|->
name|match
operator|.
name|len
condition|)
block|{
if|if
condition|(
operator|(
name|size_t
operator|)
operator|(
name|p
operator|-
name|ctx
operator|->
name|pos
operator|)
operator|<
name|looked
condition|)
block|{
name|ctx
operator|->
name|saved
operator|=
literal|0
expr_stmt|;
block|}
name|ctx
operator|->
name|state
operator|=
name|sub_start_state
expr_stmt|;
name|ctx
operator|->
name|pos
operator|=
name|p
operator|+
literal|1
expr_stmt|;
name|ctx
operator|->
name|looked
operator|=
literal|0
expr_stmt|;
name|ctx
operator|->
name|copy_end
operator|=
name|copy_end
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|copy_start
operator|==
name|NULL
operator|&&
name|copy_end
condition|)
block|{
name|ctx
operator|->
name|copy_start
operator|=
name|ctx
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
block|}
if|else if
condition|(
name|ch
operator|==
name|ctx
operator|->
name|match
operator|.
name|data
index|[
literal|0
index|]
condition|)
block|{
name|copy_end
operator|=
name|p
expr_stmt|;
name|looked
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
name|copy_end
operator|=
name|p
expr_stmt|;
name|looked
operator|=
literal|0
expr_stmt|;
name|state
operator|=
name|sub_start_state
expr_stmt|;
block|}
block|}
name|ctx
operator|->
name|state
operator|=
name|state
expr_stmt|;
name|ctx
operator|->
name|pos
operator|=
name|p
expr_stmt|;
name|ctx
operator|->
name|looked
operator|=
name|looked
expr_stmt|;
name|ctx
operator|->
name|copy_end
operator|=
operator|(
name|state
operator|==
name|sub_start_state
operator|)
condition|?
name|p
else|:
name|copy_end
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|copy_start
operator|==
name|NULL
operator|&&
name|ctx
operator|->
name|copy_end
condition|)
block|{
name|ctx
operator|->
name|copy_start
operator|=
name|ctx
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
block|}
return|return
name|NGX_AGAIN
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_sub_filter (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_sub_filter
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
name|ngx_http_sub_loc_conf_t
modifier|*
name|slcf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_http_compile_complex_value_t
name|ccv
decl_stmt|;
if|if
condition|(
name|slcf
operator|->
name|match
operator|.
name|len
condition|)
block|{
return|return
literal|"is duplicate"
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
name|ngx_strlow
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
name|value
index|[
literal|1
index|]
operator|.
name|len
argument_list|)
expr_stmt|;
name|slcf
operator|->
name|match
operator|=
name|value
index|[
literal|1
index|]
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
literal|2
index|]
expr_stmt|;
name|ccv
operator|.
name|complex_value
operator|=
operator|&
name|slcf
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
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_sub_create_conf (ngx_conf_t * cf)
name|ngx_http_sub_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_sub_loc_conf_t
modifier|*
name|slcf
decl_stmt|;
name|slcf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_sub_loc_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|slcf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
comment|/*      * set by ngx_pcalloc():      *      *     conf->match = { 0, NULL };      *     conf->sub = { 0, NULL };      *     conf->sub_lengths = NULL;      *     conf->sub_values = NULL;      *     conf->types = { NULL };      *     conf->types_keys = NULL;      */
name|slcf
operator|->
name|once
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|slcf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_sub_merge_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_sub_merge_conf
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
name|ngx_http_sub_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_sub_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|once
argument_list|,
name|prev
operator|->
name|once
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|match
argument_list|,
name|prev
operator|->
name|match
argument_list|,
literal|""
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|->
name|value
operator|.
name|value
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|conf
operator|->
name|value
operator|=
name|prev
operator|->
name|value
expr_stmt|;
block|}
if|if
condition|(
name|ngx_http_merge_types
argument_list|(
name|cf
argument_list|,
name|conf
operator|->
name|types_keys
argument_list|,
operator|&
name|conf
operator|->
name|types
argument_list|,
name|prev
operator|->
name|types_keys
argument_list|,
operator|&
name|prev
operator|->
name|types
argument_list|,
name|ngx_http_html_default_types
argument_list|)
operator|!=
name|NGX_OK
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
specifier|static
name|ngx_int_t
DECL|function|ngx_http_sub_filter_init (ngx_conf_t * cf)
name|ngx_http_sub_filter_init
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
name|ngx_http_sub_header_filter
expr_stmt|;
name|ngx_http_next_body_filter
operator|=
name|ngx_http_top_body_filter
expr_stmt|;
name|ngx_http_top_body_filter
operator|=
name|ngx_http_sub_body_filter
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

