begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_write.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_output_filter.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_write_filter.h>
end_include

begin_decl_stmt
DECL|variable|ngx_http_write_filter_module
name|ngx_http_module_t
name|ngx_http_write_filter_module
init|=
block|{
name|NGX_HTTP_MODULE
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* STUB */
end_comment

begin_comment
comment|/* */
end_comment

begin_function
DECL|function|ngx_http_write_filter (ngx_http_request_t * r,ngx_chain_t * in)
name|int
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
name|int
name|last
decl_stmt|;
name|off_t
name|size
decl_stmt|,
name|flush
decl_stmt|;
name|ngx_chain_t
modifier|*
name|ch
decl_stmt|,
modifier|*
modifier|*
name|prev
decl_stmt|,
modifier|*
name|chain
decl_stmt|;
name|ngx_http_write_filter_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_write_filter_conf_t
modifier|*
name|conf
decl_stmt|;
name|ctx
operator|=
operator|(
name|ngx_http_write_filter_ctx_t
operator|*
operator|)
name|ngx_get_module_ctx
argument_list|(
name|r
operator|->
expr|main
operator|?
name|r
operator|->
expr|main
operator|:
name|r
argument_list|,
name|ngx_http_write_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|==
name|NULL
condition|)
name|ngx_test_null
argument_list|(
name|ctx
argument_list|,
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_write_filter_ctx_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|size
operator|=
name|flush
operator|=
literal|0
expr_stmt|;
name|last
operator|=
literal|0
expr_stmt|;
name|prev
operator|=
operator|&
name|ctx
operator|->
name|out
expr_stmt|;
comment|/* find size, flush point and last link of saved chain */
for|for
control|(
name|ch
operator|=
name|ctx
operator|->
name|out
init|;
name|ch
condition|;
name|ch
operator|=
name|ch
operator|->
name|next
control|)
block|{
name|prev
operator|=
operator|&
name|ch
operator|->
name|next
expr_stmt|;
name|size
operator|+=
name|ch
operator|->
name|hunk
operator|->
name|last
operator|.
name|file
operator|-
name|ch
operator|->
name|hunk
operator|->
name|pos
operator|.
name|file
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"old chunk: %x "
argument|QX_FMT
literal|" "
argument|QD_FMT _                       ch->hunk->type _ ch->hunk->pos.file _                       ch->hunk->last.file - ch->hunk->pos.file
argument_list|)
empty_stmt|;
if|if
condition|(
name|ch
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_FLUSH
operator||
name|NGX_HUNK_RECYCLED
condition|)
name|flush
operator|=
name|size
expr_stmt|;
if|if
condition|(
name|ch
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_LAST
condition|)
name|last
operator|=
literal|1
expr_stmt|;
block|}
comment|/* add new chain to existent one */
for|for
control|(
comment|/* void */
init|;
name|in
condition|;
name|in
operator|=
name|in
operator|->
name|next
control|)
block|{
name|ngx_test_null
argument_list|(
name|ch
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_chain_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ch
operator|->
name|hunk
operator|=
name|in
operator|->
name|hunk
expr_stmt|;
name|ch
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
operator|*
name|prev
operator|=
name|ch
expr_stmt|;
name|prev
operator|=
operator|&
name|ch
operator|->
name|next
expr_stmt|;
name|size
operator|+=
name|ch
operator|->
name|hunk
operator|->
name|last
operator|.
name|file
operator|-
name|ch
operator|->
name|hunk
operator|->
name|pos
operator|.
name|file
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"new chunk: %x "
argument|QX_FMT
literal|" "
argument|QD_FMT _                       ch->hunk->type _ ch->hunk->pos.file _                       ch->hunk->last.file - ch->hunk->pos.file
argument_list|)
empty_stmt|;
if|if
condition|(
name|ch
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_FLUSH
operator||
name|NGX_HUNK_RECYCLED
condition|)
name|flush
operator|=
name|size
expr_stmt|;
if|if
condition|(
name|ch
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_LAST
condition|)
name|last
operator|=
literal|1
expr_stmt|;
block|}
name|conf
operator|=
operator|(
name|ngx_http_write_filter_conf_t
operator|*
operator|)
name|ngx_get_module_loc_conf
argument_list|(
name|r
operator|->
expr|main
operator|?
name|r
operator|->
expr|main
operator|:
name|r
argument_list|,
name|ngx_http_write_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|last
operator|&&
name|flush
operator|==
literal|0
operator|&&
name|size
operator|<
name|conf
operator|->
name|buffer_output
condition|)
return|return
name|NGX_OK
return|;
name|chain
operator|=
name|ngx_event_write
argument_list|(
name|r
operator|->
name|connection
argument_list|,
name|ctx
operator|->
name|out
argument_list|,
name|flush
argument_list|)
expr_stmt|;
if|if
condition|(
name|chain
operator|==
operator|(
name|ngx_chain_t
operator|*
operator|)
operator|-
literal|1
condition|)
return|return
name|NGX_ERROR
return|;
name|ctx
operator|->
name|out
operator|=
name|chain
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"write filter %x"
argument|_ chain
argument_list|)
empty_stmt|;
return|return
operator|(
name|chain
condition|?
name|NGX_AGAIN
else|:
name|NGX_OK
operator|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_write_filter_create_conf (ngx_pool_t * pool)
specifier|static
name|void
modifier|*
name|ngx_http_write_filter_create_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_http_write_filter_conf_t
modifier|*
name|conf
decl_stmt|;
name|ngx_test_null
argument_list|(
name|conf
argument_list|,
name|ngx_pcalloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_write_filter_conf_t
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|conf
operator|->
name|buffer_output
operator|=
literal|16384
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_http_write_filter_set_hunk_size (ngx_pool_t * pool,void * conf,char * size)
specifier|static
name|void
modifier|*
name|ngx_http_write_filter_set_hunk_size
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|,
name|char
modifier|*
name|size
parameter_list|)
block|{
name|ngx_http_write_filter_conf_t
modifier|*
name|cf
init|=
operator|(
name|ngx_http_write_filter_conf_t
operator|*
operator|)
name|conf
decl_stmt|;
name|cf
operator|->
name|buffer_output
operator|=
name|atoi
argument_list|(
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|cf
operator|->
name|buffer_output
operator|<=
literal|0
condition|)
return|return
literal|"Error"
return|;
name|cf
operator|->
name|buffer_output
operator|*=
literal|1024
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

