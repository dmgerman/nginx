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
DECL|struct|__anon298b219f0108
typedef|typedef
struct|struct
block|{
DECL|member|before_body
name|ngx_str_t
name|before_body
decl_stmt|;
DECL|member|after_body
name|ngx_str_t
name|after_body
decl_stmt|;
DECL|member|types
name|ngx_hash_t
name|types
decl_stmt|;
DECL|member|types_keys
name|ngx_array_t
modifier|*
name|types_keys
decl_stmt|;
DECL|typedef|ngx_http_addition_conf_t
block|}
name|ngx_http_addition_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon298b219f0208
typedef|typedef
struct|struct
block|{
DECL|member|before_body_sent
name|ngx_uint_t
name|before_body_sent
decl_stmt|;
DECL|typedef|ngx_http_addition_ctx_t
block|}
name|ngx_http_addition_ctx_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_addition_create_conf
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
name|ngx_http_addition_merge_conf
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
name|ngx_http_addition_filter_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_addition_commands
specifier|static
name|ngx_command_t
name|ngx_http_addition_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"add_before_body"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_addition_conf_t
argument_list|,
name|before_body
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"add_after_body"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_addition_conf_t
argument_list|,
name|after_body
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"addition_types"
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
name|ngx_http_addition_conf_t
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
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_addition_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_addition_filter_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_addition_filter_init
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
name|ngx_http_addition_create_conf
block|,
comment|/* create location configuration */
name|ngx_http_addition_merge_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_addition_filter_module
name|ngx_module_t
name|ngx_http_addition_filter_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_addition_filter_module_ctx
block|,
comment|/* module context */
name|ngx_http_addition_commands
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
DECL|function|ngx_http_addition_header_filter (ngx_http_request_t * r)
name|ngx_http_addition_header_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_http_addition_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_addition_conf_t
modifier|*
name|conf
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|status
operator|!=
name|NGX_HTTP_OK
operator|||
name|r
operator|!=
name|r
operator|->
expr|main
condition|)
block|{
return|return
name|ngx_http_next_header_filter
argument_list|(
name|r
argument_list|)
return|;
block|}
name|conf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_addition_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|->
name|before_body
operator|.
name|len
operator|==
literal|0
operator|&&
name|conf
operator|->
name|after_body
operator|.
name|len
operator|==
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
if|if
condition|(
name|ngx_http_test_content_type
argument_list|(
name|r
argument_list|,
operator|&
name|conf
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
name|ngx_http_addition_ctx_t
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
name|ngx_http_addition_filter_module
argument_list|)
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
name|ngx_http_clear_etag
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
DECL|function|ngx_http_addition_body_filter (ngx_http_request_t * r,ngx_chain_t * in)
name|ngx_http_addition_body_filter
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
name|ngx_uint_t
name|last
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|ngx_http_request_t
modifier|*
name|sr
decl_stmt|;
name|ngx_http_addition_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_addition_conf_t
modifier|*
name|conf
decl_stmt|;
if|if
condition|(
name|in
operator|==
name|NULL
operator|||
name|r
operator|->
name|header_only
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
name|ctx
operator|=
name|ngx_http_get_module_ctx
argument_list|(
name|r
argument_list|,
name|ngx_http_addition_filter_module
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
name|conf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_addition_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|ctx
operator|->
name|before_body_sent
condition|)
block|{
name|ctx
operator|->
name|before_body_sent
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|conf
operator|->
name|before_body
operator|.
name|len
condition|)
block|{
if|if
condition|(
name|ngx_http_subrequest
argument_list|(
name|r
argument_list|,
operator|&
name|conf
operator|->
name|before_body
argument_list|,
name|NULL
argument_list|,
operator|&
name|sr
argument_list|,
name|NULL
argument_list|,
literal|0
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
block|}
if|if
condition|(
name|conf
operator|->
name|after_body
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|ngx_http_set_ctx
argument_list|(
name|r
argument_list|,
name|NULL
argument_list|,
name|ngx_http_addition_filter_module
argument_list|)
expr_stmt|;
return|return
name|ngx_http_next_body_filter
argument_list|(
name|r
argument_list|,
name|in
argument_list|)
return|;
block|}
name|last
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|cl
operator|=
name|in
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
if|if
condition|(
name|cl
operator|->
name|buf
operator|->
name|last_buf
condition|)
block|{
name|cl
operator|->
name|buf
operator|->
name|last_buf
operator|=
literal|0
expr_stmt|;
name|cl
operator|->
name|buf
operator|->
name|sync
operator|=
literal|1
expr_stmt|;
name|last
operator|=
literal|1
expr_stmt|;
block|}
block|}
name|rc
operator|=
name|ngx_http_next_body_filter
argument_list|(
name|r
argument_list|,
name|in
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
operator|!
name|last
operator|||
name|conf
operator|->
name|after_body
operator|.
name|len
operator|==
literal|0
condition|)
block|{
return|return
name|rc
return|;
block|}
if|if
condition|(
name|ngx_http_subrequest
argument_list|(
name|r
argument_list|,
operator|&
name|conf
operator|->
name|after_body
argument_list|,
name|NULL
argument_list|,
operator|&
name|sr
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
operator|!=
name|NGX_OK
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
name|NULL
argument_list|,
name|ngx_http_addition_filter_module
argument_list|)
expr_stmt|;
return|return
name|ngx_http_send_special
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_LAST
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_addition_filter_init (ngx_conf_t * cf)
name|ngx_http_addition_filter_init
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
name|ngx_http_addition_header_filter
expr_stmt|;
name|ngx_http_next_body_filter
operator|=
name|ngx_http_top_body_filter
expr_stmt|;
name|ngx_http_top_body_filter
operator|=
name|ngx_http_addition_body_filter
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
DECL|function|ngx_http_addition_create_conf (ngx_conf_t * cf)
name|ngx_http_addition_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_addition_conf_t
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
name|ngx_http_addition_conf_t
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
comment|/*      * set by ngx_pcalloc():      *      *     conf->before_body = { 0, NULL };      *     conf->after_body = { 0, NULL };      *     conf->types = { NULL };      *     conf->types_keys = NULL;      */
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_addition_merge_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_addition_merge_conf
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
name|ngx_http_addition_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_addition_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|before_body
argument_list|,
name|prev
operator|->
name|before_body
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|after_body
argument_list|,
name|prev
operator|->
name|after_body
argument_list|,
literal|""
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_http_merge_types
argument_list|(
name|cf
argument_list|,
operator|&
name|conf
operator|->
name|types_keys
argument_list|,
operator|&
name|conf
operator|->
name|types
argument_list|,
operator|&
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

end_unit

