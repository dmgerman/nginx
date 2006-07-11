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
name|ngx_http_postpone_filter_output_postponed_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_postpone_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_postpone_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_postpone_filter_module_ctx
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
DECL|variable|ngx_http_postpone_filter_module
name|ngx_module_t
name|ngx_http_postpone_filter_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_postpone_filter_module_ctx
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
name|ngx_http_postpone_filter_init
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
DECL|variable|ngx_http_next_filter
specifier|static
name|ngx_http_output_body_filter_pt
name|ngx_http_next_filter
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_postpone_filter (ngx_http_request_t * r,ngx_chain_t * in)
name|ngx_http_postpone_filter
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
name|ngx_chain_t
modifier|*
name|out
decl_stmt|;
name|ngx_http_postponed_request_t
modifier|*
name|pr
decl_stmt|,
modifier|*
modifier|*
name|ppr
decl_stmt|;
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
literal|"http postpone filter \"%V?%V\" %p"
argument_list|,
operator|&
name|r
operator|->
name|uri
argument_list|,
operator|&
name|r
operator|->
name|args
argument_list|,
name|in
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|!=
name|r
operator|->
name|connection
operator|->
name|data
operator|||
operator|(
name|r
operator|->
name|postponed
operator|&&
name|in
operator|)
condition|)
block|{
if|if
condition|(
name|r
operator|->
name|postponed
condition|)
block|{
for|for
control|(
name|pr
operator|=
name|r
operator|->
name|postponed
init|;
name|pr
operator|->
name|next
condition|;
name|pr
operator|=
name|pr
operator|->
name|next
control|)
block|{
comment|/* void */
block|}
name|ppr
operator|=
name|pr
operator|->
name|request
condition|?
operator|&
name|pr
operator|->
name|next
else|:
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|ppr
operator|=
operator|&
name|r
operator|->
name|postponed
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_SUPPRESS_WARN
operator|)
name|pr
operator|=
name|NULL
expr_stmt|;
endif|#
directive|endif
block|}
if|if
condition|(
name|ppr
condition|)
block|{
name|pr
operator|=
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_postponed_request_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|pr
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
operator|*
name|ppr
operator|=
name|pr
expr_stmt|;
name|pr
operator|->
name|request
operator|=
name|NULL
expr_stmt|;
name|pr
operator|->
name|out
operator|=
name|NULL
expr_stmt|;
name|pr
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|ngx_chain_add_copy
argument_list|(
name|r
operator|->
name|pool
argument_list|,
operator|&
name|pr
operator|->
name|out
argument_list|,
name|in
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
if|#
directive|if
literal|1
block|{
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
init|=
name|NULL
decl_stmt|;
for|for
control|(
name|cl
operator|=
name|pr
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
literal|"the same buf was used in postponed %p %p"
argument_list|,
name|b
argument_list|,
name|b
operator|->
name|pos
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
block|}
endif|#
directive|endif
if|if
condition|(
name|r
operator|!=
name|r
operator|->
name|connection
operator|->
name|data
operator|||
name|r
operator|->
name|postponed
operator|->
name|request
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
block|}
if|if
condition|(
name|r
operator|->
name|postponed
condition|)
block|{
name|out
operator|=
name|r
operator|->
name|postponed
operator|->
name|out
expr_stmt|;
if|if
condition|(
name|out
condition|)
block|{
name|r
operator|->
name|postponed
operator|=
name|r
operator|->
name|postponed
operator|->
name|next
expr_stmt|;
block|}
block|}
else|else
block|{
name|out
operator|=
name|in
expr_stmt|;
block|}
name|rc
operator|=
name|NGX_OK
expr_stmt|;
if|if
condition|(
name|out
operator|||
operator|(
name|r
operator|->
name|connection
operator|->
name|buffered
operator|&
operator|(
name|NGX_HTTP_LOWLEVEL_BUFFERED
operator||
name|NGX_LOWLEVEL_BUFFERED
operator|)
operator|)
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
literal|"http postpone filter out \"%V?%V\""
argument_list|,
operator|&
name|r
operator|->
name|uri
argument_list|,
operator|&
name|r
operator|->
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|out
operator|&&
name|out
operator|->
name|next
operator|==
name|NULL
operator|&&
name|ngx_buf_sync_only
argument_list|(
name|out
operator|->
name|buf
argument_list|)
operator|)
condition|)
block|{
name|rc
operator|=
name|ngx_http_next_filter
argument_list|(
name|r
operator|->
expr|main
argument_list|,
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
comment|/* NGX_ERROR may be returned by any filter */
name|r
operator|->
name|connection
operator|->
name|error
operator|=
literal|1
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|r
operator|->
name|postponed
operator|==
name|NULL
condition|)
block|{
return|return
name|rc
return|;
block|}
name|rc
operator|=
name|ngx_http_postpone_filter_output_postponed_request
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
comment|/* NGX_ERROR may be returned by any filter */
name|r
operator|->
name|connection
operator|->
name|error
operator|=
literal|1
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
DECL|function|ngx_http_postpone_filter_output_postponed_request (ngx_http_request_t * r)
name|ngx_http_postpone_filter_output_postponed_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_chain_t
modifier|*
name|out
decl_stmt|;
name|ngx_http_log_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_postponed_request_t
modifier|*
name|pr
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|pr
operator|=
name|r
operator|->
name|postponed
expr_stmt|;
if|if
condition|(
name|pr
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|pr
operator|->
name|request
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
literal|"http postpone filter handle \"%V?%V\""
argument_list|,
operator|&
name|pr
operator|->
name|request
operator|->
name|uri
argument_list|,
operator|&
name|pr
operator|->
name|request
operator|->
name|args
argument_list|)
expr_stmt|;
name|ctx
operator|=
name|r
operator|->
name|connection
operator|->
name|log
operator|->
name|data
expr_stmt|;
name|ctx
operator|->
name|current_request
operator|=
name|pr
operator|->
name|request
expr_stmt|;
if|if
condition|(
operator|!
name|pr
operator|->
name|request
operator|->
name|done
condition|)
block|{
name|r
operator|->
name|connection
operator|->
name|data
operator|=
name|pr
operator|->
name|request
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|rc
operator|=
name|ngx_http_postpone_filter_output_postponed_request
argument_list|(
name|pr
operator|->
name|request
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_AGAIN
operator|||
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|rc
return|;
block|}
name|r
operator|->
name|postponed
operator|=
name|r
operator|->
name|postponed
operator|->
name|next
expr_stmt|;
name|pr
operator|=
name|r
operator|->
name|postponed
expr_stmt|;
block|}
if|if
condition|(
name|pr
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|out
operator|=
name|pr
operator|->
name|out
expr_stmt|;
if|if
condition|(
name|out
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
literal|"http postpone filter out postponed \"%V?%V\""
argument_list|,
operator|&
name|r
operator|->
name|uri
argument_list|,
operator|&
name|r
operator|->
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|out
operator|&&
name|out
operator|->
name|next
operator|==
name|NULL
operator|&&
name|ngx_buf_sync_only
argument_list|(
name|out
operator|->
name|buf
argument_list|)
operator|)
condition|)
block|{
if|if
condition|(
name|ngx_http_next_filter
argument_list|(
name|r
operator|->
expr|main
argument_list|,
name|out
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
block|}
name|r
operator|->
name|postponed
operator|=
name|r
operator|->
name|postponed
operator|->
name|next
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_postpone_filter_init (ngx_cycle_t * cycle)
name|ngx_http_postpone_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_http_next_filter
operator|=
name|ngx_http_top_body_filter
expr_stmt|;
name|ngx_http_top_body_filter
operator|=
name|ngx_http_postpone_filter
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

