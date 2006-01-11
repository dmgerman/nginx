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
name|ngx_int_t
name|ngx_http_not_modified_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_not_modified_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_not_modified_filter_module_ctx
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
DECL|variable|ngx_http_not_modified_filter_module
name|ngx_module_t
name|ngx_http_not_modified_filter_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_not_modified_filter_module_ctx
block|,
comment|/* module context */
name|NULL
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|ngx_http_not_modified_filter_init
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

begin_function
DECL|function|ngx_http_not_modified_header_filter (ngx_http_request_t * r)
specifier|static
name|ngx_int_t
name|ngx_http_not_modified_header_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|time_t
name|ims
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
operator|||
name|r
operator|->
name|headers_in
operator|.
name|if_modified_since
operator|==
name|NULL
operator|||
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
operator|==
operator|-
literal|1
condition|)
block|{
return|return
name|ngx_http_next_header_filter
argument_list|(
name|r
argument_list|)
return|;
block|}
name|ims
operator|=
name|ngx_http_parse_time
argument_list|(
name|r
operator|->
name|headers_in
operator|.
name|if_modified_since
operator|->
name|value
operator|.
name|data
argument_list|,
name|r
operator|->
name|headers_in
operator|.
name|if_modified_since
operator|->
name|value
operator|.
name|len
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
literal|"http ims:%d lm:%d"
argument_list|,
name|ims
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
argument_list|)
expr_stmt|;
comment|/*      * I think that the equality of the dates is correcter      */
if|if
condition|(
name|ims
operator|!=
name|NGX_ERROR
operator|&&
name|ims
operator|==
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|NGX_HTTP_NOT_MODIFIED
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|.
name|len
operator|=
literal|0
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
DECL|function|ngx_http_not_modified_filter_init (ngx_cycle_t * cycle)
specifier|static
name|ngx_int_t
name|ngx_http_not_modified_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_http_next_header_filter
operator|=
name|ngx_http_top_header_filter
expr_stmt|;
name|ngx_http_top_header_filter
operator|=
name|ngx_http_not_modified_header_filter
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

