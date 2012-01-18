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

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_write_filter_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_write_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_write_filter_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_write_filter_init
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
block|,
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_write_filter_module
name|ngx_module_t
name|ngx_http_write_filter_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_write_filter_module_ctx
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
name|ngx_int_t
DECL|function|ngx_http_write_filter (ngx_http_request_t * r,ngx_chain_t * in)
name|ngx_http_write_filter
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
name|off_t
name|size
decl_stmt|,
name|sent
decl_stmt|,
name|nsent
decl_stmt|,
name|limit
decl_stmt|;
name|ngx_uint_t
name|last
decl_stmt|,
name|flush
decl_stmt|;
name|ngx_msec_t
name|delay
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|,
modifier|*
name|ln
decl_stmt|,
modifier|*
modifier|*
name|ll
decl_stmt|,
modifier|*
name|chain
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
name|c
operator|=
name|r
operator|->
name|connection
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|error
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|size
operator|=
literal|0
expr_stmt|;
name|flush
operator|=
literal|0
expr_stmt|;
name|last
operator|=
literal|0
expr_stmt|;
name|ll
operator|=
operator|&
name|r
operator|->
name|out
expr_stmt|;
comment|/* find the size, the flush point and the last link of the saved chain */
for|for
control|(
name|cl
operator|=
name|r
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
name|ll
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
name|ngx_log_debug7
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"write old buf t:%d f:%d %p, pos %p, size: %z "
literal|"file: %O, size: %z"
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|temporary
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|in_file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|start
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|last
operator|-
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_last
operator|-
name|cl
operator|->
name|buf
operator|->
name|file_pos
argument_list|)
expr_stmt|;
if|#
directive|if
literal|1
if|if
condition|(
name|ngx_buf_size
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
operator|==
literal|0
operator|&&
operator|!
name|ngx_buf_special
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"zero size buf in writer "
literal|"t:%d r:%d f:%d %p %p-%p %p %O-%O"
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|temporary
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|recycled
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|in_file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|start
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|last
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_last
argument_list|)
expr_stmt|;
name|ngx_debug_point
argument_list|()
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
name|size
operator|+=
name|ngx_buf_size
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|->
name|buf
operator|->
name|flush
operator|||
name|cl
operator|->
name|buf
operator|->
name|recycled
condition|)
block|{
name|flush
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|cl
operator|->
name|buf
operator|->
name|last_buf
condition|)
block|{
name|last
operator|=
literal|1
expr_stmt|;
block|}
block|}
comment|/* add the new chain to the existent one */
for|for
control|(
name|ln
operator|=
name|in
init|;
name|ln
condition|;
name|ln
operator|=
name|ln
operator|->
name|next
control|)
block|{
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
name|ln
operator|->
name|buf
expr_stmt|;
operator|*
name|ll
operator|=
name|cl
expr_stmt|;
name|ll
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
name|ngx_log_debug7
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"write new buf t:%d f:%d %p, pos %p, size: %z "
literal|"file: %O, size: %z"
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|temporary
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|in_file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|start
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|last
operator|-
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_last
operator|-
name|cl
operator|->
name|buf
operator|->
name|file_pos
argument_list|)
expr_stmt|;
if|#
directive|if
literal|1
if|if
condition|(
name|ngx_buf_size
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
operator|==
literal|0
operator|&&
operator|!
name|ngx_buf_special
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"zero size buf in writer "
literal|"t:%d r:%d f:%d %p %p-%p %p %O-%O"
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|temporary
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|recycled
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|in_file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|start
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|last
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_last
argument_list|)
expr_stmt|;
name|ngx_debug_point
argument_list|()
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
name|size
operator|+=
name|ngx_buf_size
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|->
name|buf
operator|->
name|flush
operator|||
name|cl
operator|->
name|buf
operator|->
name|recycled
condition|)
block|{
name|flush
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|cl
operator|->
name|buf
operator|->
name|last_buf
condition|)
block|{
name|last
operator|=
literal|1
expr_stmt|;
block|}
block|}
operator|*
name|ll
operator|=
name|NULL
expr_stmt|;
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"http write filter: l:%d f:%d s:%O"
argument_list|,
name|last
argument_list|,
name|flush
argument_list|,
name|size
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
comment|/*      * avoid the output if there are no last buf, no flush point,      * there are the incoming bufs and the size of all bufs      * is smaller than "postpone_output" directive      */
if|if
condition|(
operator|!
name|last
operator|&&
operator|!
name|flush
operator|&&
name|in
operator|&&
name|size
operator|<
operator|(
name|off_t
operator|)
name|clcf
operator|->
name|postpone_output
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|c
operator|->
name|write
operator|->
name|delayed
condition|)
block|{
name|c
operator|->
name|buffered
operator||=
name|NGX_HTTP_WRITE_BUFFERED
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|size
operator|==
literal|0
operator|&&
operator|!
operator|(
name|c
operator|->
name|buffered
operator|&
name|NGX_LOWLEVEL_BUFFERED
operator|)
condition|)
block|{
if|if
condition|(
name|last
condition|)
block|{
name|r
operator|->
name|out
operator|=
name|NULL
expr_stmt|;
name|c
operator|->
name|buffered
operator|&=
operator|~
name|NGX_HTTP_WRITE_BUFFERED
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|flush
condition|)
block|{
do|do
block|{
name|r
operator|->
name|out
operator|=
name|r
operator|->
name|out
operator|->
name|next
expr_stmt|;
block|}
do|while
condition|(
name|r
operator|->
name|out
condition|)
do|;
name|c
operator|->
name|buffered
operator|&=
operator|~
name|NGX_HTTP_WRITE_BUFFERED
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"the http output chain is empty"
argument_list|)
expr_stmt|;
name|ngx_debug_point
argument_list|()
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|r
operator|->
name|limit_rate
condition|)
block|{
name|limit
operator|=
name|r
operator|->
name|limit_rate
operator|*
operator|(
name|ngx_time
argument_list|()
operator|-
name|r
operator|->
name|start_sec
operator|+
literal|1
operator|)
operator|-
operator|(
name|c
operator|->
name|sent
operator|-
name|clcf
operator|->
name|limit_rate_after
operator|)
expr_stmt|;
if|if
condition|(
name|limit
operator|<=
literal|0
condition|)
block|{
name|c
operator|->
name|write
operator|->
name|delayed
operator|=
literal|1
expr_stmt|;
name|ngx_add_timer
argument_list|(
name|c
operator|->
name|write
argument_list|,
operator|(
name|ngx_msec_t
operator|)
operator|(
operator|-
name|limit
operator|*
literal|1000
operator|/
name|r
operator|->
name|limit_rate
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
name|c
operator|->
name|buffered
operator||=
name|NGX_HTTP_WRITE_BUFFERED
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|clcf
operator|->
name|sendfile_max_chunk
operator|&&
operator|(
name|off_t
operator|)
name|clcf
operator|->
name|sendfile_max_chunk
operator|<
name|limit
condition|)
block|{
name|limit
operator|=
name|clcf
operator|->
name|sendfile_max_chunk
expr_stmt|;
block|}
block|}
else|else
block|{
name|limit
operator|=
name|clcf
operator|->
name|sendfile_max_chunk
expr_stmt|;
block|}
name|sent
operator|=
name|c
operator|->
name|sent
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"http write filter limit %O"
argument_list|,
name|limit
argument_list|)
expr_stmt|;
name|chain
operator|=
name|c
operator|->
name|send_chain
argument_list|(
name|c
argument_list|,
name|r
operator|->
name|out
argument_list|,
name|limit
argument_list|)
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"http write filter %p"
argument_list|,
name|chain
argument_list|)
expr_stmt|;
if|if
condition|(
name|chain
operator|==
name|NGX_CHAIN_ERROR
condition|)
block|{
name|c
operator|->
name|error
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|r
operator|->
name|limit_rate
condition|)
block|{
name|nsent
operator|=
name|c
operator|->
name|sent
expr_stmt|;
if|if
condition|(
name|clcf
operator|->
name|limit_rate_after
condition|)
block|{
name|sent
operator|-=
name|clcf
operator|->
name|limit_rate_after
expr_stmt|;
if|if
condition|(
name|sent
operator|<
literal|0
condition|)
block|{
name|sent
operator|=
literal|0
expr_stmt|;
block|}
name|nsent
operator|-=
name|clcf
operator|->
name|limit_rate_after
expr_stmt|;
if|if
condition|(
name|nsent
operator|<
literal|0
condition|)
block|{
name|nsent
operator|=
literal|0
expr_stmt|;
block|}
block|}
name|delay
operator|=
operator|(
name|ngx_msec_t
operator|)
operator|(
operator|(
name|nsent
operator|-
name|sent
operator|)
operator|*
literal|1000
operator|/
name|r
operator|->
name|limit_rate
operator|)
expr_stmt|;
if|if
condition|(
name|delay
operator|>
literal|0
condition|)
block|{
name|limit
operator|=
literal|0
expr_stmt|;
name|c
operator|->
name|write
operator|->
name|delayed
operator|=
literal|1
expr_stmt|;
name|ngx_add_timer
argument_list|(
name|c
operator|->
name|write
argument_list|,
name|delay
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|limit
operator|&&
name|c
operator|->
name|write
operator|->
name|ready
operator|&&
name|c
operator|->
name|sent
operator|-
name|sent
operator|>=
name|limit
operator|-
operator|(
name|off_t
operator|)
operator|(
literal|2
operator|*
name|ngx_pagesize
operator|)
condition|)
block|{
name|c
operator|->
name|write
operator|->
name|delayed
operator|=
literal|1
expr_stmt|;
name|ngx_add_timer
argument_list|(
name|c
operator|->
name|write
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|cl
operator|=
name|r
operator|->
name|out
init|;
name|cl
operator|&&
name|cl
operator|!=
name|chain
condition|;
comment|/* void */
control|)
block|{
name|ln
operator|=
name|cl
expr_stmt|;
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
name|ngx_free_chain
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|ln
argument_list|)
expr_stmt|;
block|}
name|r
operator|->
name|out
operator|=
name|chain
expr_stmt|;
if|if
condition|(
name|chain
condition|)
block|{
name|c
operator|->
name|buffered
operator||=
name|NGX_HTTP_WRITE_BUFFERED
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|c
operator|->
name|buffered
operator|&=
operator|~
name|NGX_HTTP_WRITE_BUFFERED
expr_stmt|;
if|if
condition|(
operator|(
name|c
operator|->
name|buffered
operator|&
name|NGX_LOWLEVEL_BUFFERED
operator|)
operator|&&
name|r
operator|->
name|postponed
operator|==
name|NULL
condition|)
block|{
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
DECL|function|ngx_http_write_filter_init (ngx_conf_t * cf)
name|ngx_http_write_filter_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_top_body_filter
operator|=
name|ngx_http_write_filter
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

