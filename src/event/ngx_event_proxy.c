begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_event_proxy.h>
end_include

begin_function
DECL|function|ngx_event_proxy_read_upstream (ngx_event_proxy_t * p)
name|int
name|ngx_event_proxy_read_upstream
parameter_list|(
name|ngx_event_proxy_t
modifier|*
name|p
parameter_list|)
block|{
name|int
name|n
decl_stmt|,
name|rc
decl_stmt|,
name|size
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|,
modifier|*
name|nh
decl_stmt|;
name|ngx_chain_t
modifier|*
name|chain
decl_stmt|,
modifier|*
name|temp
decl_stmt|,
modifier|*
name|entry
decl_stmt|,
modifier|*
name|next
decl_stmt|;
name|p
operator|->
name|level
operator|++
expr_stmt|;
name|ngx_log_debug
argument_list|(
name|p
operator|->
name|log
argument_list|,
literal|"read upstream"
argument_list|)
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
comment|/* use the free hunks if they exist */
if|if
condition|(
name|p
operator|->
name|free_hunks
condition|)
block|{
name|chain
operator|=
name|p
operator|->
name|free_hunks
expr_stmt|;
name|p
operator|->
name|free_hunks
operator|=
name|NULL
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"free hunk: %08X:%d"
argument|_ chain->hunk _               chain->hunk->end - chain->hunk->last
argument_list|)
empty_stmt|;
comment|/* allocate a new hunk if it's still allowed */
block|}
if|else if
condition|(
name|p
operator|->
name|allocated
operator|<
name|p
operator|->
name|max_block_size
condition|)
block|{
name|ngx_test_null
argument_list|(
name|h
argument_list|,
name|ngx_create_temp_hunk
argument_list|(
name|p
operator|->
name|pool
argument_list|,
name|p
operator|->
name|block_size
argument_list|,
literal|20
argument_list|,
literal|20
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|p
operator|->
name|allocated
operator|+=
name|p
operator|->
name|block_size
expr_stmt|;
name|ngx_test_null
argument_list|(
name|temp
argument_list|,
name|ngx_alloc_chain_entry
argument_list|(
name|p
operator|->
name|pool
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|temp
operator|->
name|hunk
operator|=
name|h
expr_stmt|;
name|temp
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
name|chain
operator|=
name|temp
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"new hunk: %08X"
argument|_ chain->hunk
argument_list|)
empty_stmt|;
comment|/* use the shadow hunks if they exist */
block|}
if|else if
condition|(
name|p
operator|->
name|shadow_hunks
condition|)
block|{
name|chain
operator|=
name|p
operator|->
name|shadow_hunks
expr_stmt|;
name|p
operator|->
name|shadow_hunks
operator|=
name|NULL
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"shadow hunk: %08X"
argument|_ chain->hunk
argument_list|)
empty_stmt|;
comment|/* if it's allowed then save the incoming hunks to a temporary file,            move the saved hunks to a shadow chain,            and add the file hunks to an outgoing chain */
block|}
if|else if
condition|(
name|p
operator|->
name|temp_offset
operator|<
name|p
operator|->
name|max_temp_size
condition|)
block|{
name|rc
operator|=
name|ngx_event_proxy_write_chain_to_temp_file
argument_list|(
name|p
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"temp offset: %d"
argument|_ p->temp_offset
argument_list|)
empty_stmt|;
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
name|chain
operator|=
name|p
operator|->
name|shadow_hunks
expr_stmt|;
name|p
operator|->
name|shadow_hunks
operator|=
name|NULL
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"new shadow hunk: %08X"
argument|_ chain->hunk
argument_list|)
empty_stmt|;
comment|/* if there're no hunks to read in then disable a level event */
block|}
else|else
block|{
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_LEVEL_EVENT
condition|)
block|{
name|p
operator|->
name|block_upstream
operator|=
literal|1
expr_stmt|;
block|}
break|break;
block|}
name|n
operator|=
name|ngx_recv_chain
argument_list|(
name|p
operator|->
name|upstream
argument_list|,
name|chain
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"recv_chain: %d"
argument|_ n
argument_list|)
empty_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
name|p
operator|->
name|upstream_error
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|blocked
condition|)
block|{
if|if
condition|(
name|ngx_add_event
argument_list|(
name|p
operator|->
name|upstream
operator|->
name|read
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_LEVEL_EVENT
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|blocked
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|p
operator|->
name|free_hunks
operator|=
name|chain
expr_stmt|;
name|p
operator|->
name|upstream_eof
operator|=
literal|1
expr_stmt|;
name|p
operator|->
name|block_upstream
operator|=
literal|0
expr_stmt|;
break|break;
block|}
comment|/* move the full hunks to a read chain            and the partial filled hunk to a free chain            and remove the shadow links for these hunks */
for|for
control|(
name|entry
operator|=
name|chain
init|;
name|entry
operator|&&
name|n
operator|>
literal|0
condition|;
name|entry
operator|=
name|next
control|)
block|{
name|next
operator|=
name|entry
operator|->
name|next
expr_stmt|;
name|entry
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|hunk
operator|->
name|shadow
condition|)
block|{
for|for
control|(
name|h
operator|=
name|entry
operator|->
name|hunk
operator|->
name|shadow
init|;
operator|(
name|h
operator|->
name|type
operator|&
name|NGX_HUNK_LAST_SHADOW
operator|)
operator|==
literal|0
condition|;
name|h
operator|=
name|nh
control|)
block|{
name|nh
operator|=
name|h
operator|->
name|shadow
expr_stmt|;
name|h
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|h
operator|->
name|type
operator|&=
operator|~
operator|(
name|NGX_HUNK_TEMP
operator||
name|NGX_HUNK_IN_MEMORY
operator||
name|NGX_HUNK_RECYCLED
operator|)
expr_stmt|;
block|}
name|h
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|h
operator|->
name|type
operator|&=
operator|~
operator|(
name|NGX_HUNK_TEMP
operator||
name|NGX_HUNK_IN_MEMORY
operator||
name|NGX_HUNK_RECYCLED
operator||
name|NGX_HUNK_LAST_SHADOW
operator|)
expr_stmt|;
name|entry
operator|->
name|hunk
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
block|}
name|size
operator|=
name|entry
operator|->
name|hunk
operator|->
name|end
operator|-
name|entry
operator|->
name|hunk
operator|->
name|last
expr_stmt|;
if|if
condition|(
name|n
operator|>=
name|size
condition|)
block|{
name|entry
operator|->
name|hunk
operator|->
name|last
operator|=
name|entry
operator|->
name|hunk
operator|->
name|end
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|read_hunks
condition|)
block|{
name|p
operator|->
name|last_read_hunk
operator|->
name|next
operator|=
name|entry
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|read_hunks
operator|=
name|entry
expr_stmt|;
block|}
name|p
operator|->
name|last_read_hunk
operator|=
name|entry
expr_stmt|;
name|n
operator|-=
name|size
expr_stmt|;
comment|/* the copy input filter */
if|if
condition|(
name|p
operator|->
name|input_filter
operator|==
name|NULL
condition|)
block|{
name|ngx_test_null
argument_list|(
name|h
argument_list|,
name|ngx_alloc_hunk
argument_list|(
name|p
operator|->
name|pool
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|h
argument_list|,
name|entry
operator|->
name|hunk
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_hunk_t
argument_list|)
argument_list|)
expr_stmt|;
name|h
operator|->
name|shadow
operator|=
name|entry
operator|->
name|hunk
expr_stmt|;
name|h
operator|->
name|type
operator||=
name|NGX_HUNK_LAST_SHADOW
expr_stmt|;
name|ngx_test_null
argument_list|(
name|temp
argument_list|,
name|ngx_alloc_chain_entry
argument_list|(
name|p
operator|->
name|pool
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|temp
operator|->
name|hunk
operator|=
name|h
expr_stmt|;
name|temp
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|in_hunks
condition|)
block|{
name|p
operator|->
name|last_in_hunk
operator|->
name|next
operator|=
name|temp
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|in_hunks
operator|=
name|temp
expr_stmt|;
block|}
name|p
operator|->
name|last_in_hunk
operator|=
name|temp
expr_stmt|;
block|}
block|}
else|else
block|{
name|entry
operator|->
name|hunk
operator|->
name|last
operator|+=
name|n
expr_stmt|;
name|p
operator|->
name|free_hunks
operator|=
name|entry
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
block|}
block|}
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"rest chain: %08X"
argument|_ entry
argument_list|)
empty_stmt|;
comment|/* if the rest hunks are shadow then move them to a shadow chain            otherwise add them to a free chain */
if|if
condition|(
name|entry
condition|)
block|{
if|if
condition|(
name|entry
operator|->
name|hunk
operator|->
name|shadow
condition|)
block|{
name|p
operator|->
name|shadow_hunks
operator|=
name|entry
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|p
operator|->
name|free_hunks
condition|)
block|{
name|p
operator|->
name|free_hunks
operator|->
name|next
operator|=
name|entry
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|free_hunks
operator|=
name|entry
expr_stmt|;
block|}
block|}
name|p
operator|->
name|block_upstream
operator|=
literal|0
expr_stmt|;
break|break;
block|}
comment|/* the input filter i.e. that moves HTTP/1.1 chunks            from a read chain to an incoming chain */
if|if
condition|(
name|p
operator|->
name|input_filter
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|input_filter
argument_list|(
name|p
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
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"eof: %d block: %d"
argument|_               p->upstream_eof _ p->block_upstream
argument_list|)
empty_stmt|;
comment|/* if there's the end of upstream response then move        the partially filled hunk from a free chain to an incoming chain */
if|if
condition|(
name|p
operator|->
name|upstream_eof
condition|)
block|{
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|free_hunks
operator|&&
name|p
operator|->
name|free_hunks
operator|->
name|hunk
operator|->
name|pos
operator|<
name|p
operator|->
name|free_hunks
operator|->
name|hunk
operator|->
name|last
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|input_filter
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|input_filter
argument_list|(
name|p
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
else|else
block|{
name|entry
operator|=
name|p
operator|->
name|free_hunks
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|in_hunks
condition|)
block|{
name|p
operator|->
name|last_in_hunk
operator|->
name|next
operator|=
name|entry
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|in_hunks
operator|=
name|entry
expr_stmt|;
block|}
name|p
operator|->
name|last_in_hunk
operator|=
name|entry
expr_stmt|;
block|}
name|p
operator|->
name|free_hunks
operator|=
name|entry
operator|->
name|next
expr_stmt|;
name|entry
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
if|#
directive|if
literal|0
comment|/* free the unneeded hunks */
block_content|for (entry = p->free_hunks; entry; entry = ce->next) {             ngx_free_hunk(p->pool, entry->hunk);         }
endif|#
directive|endif
if|if
condition|(
name|p
operator|->
name|in_hunks
condition|)
block|{
name|p
operator|->
name|last_in_hunk
operator|->
name|hunk
operator|->
name|type
operator||=
name|NGX_HUNK_LAST
expr_stmt|;
block|}
if|else if
condition|(
name|p
operator|->
name|out_hunks
condition|)
block|{
name|p
operator|->
name|last_out_hunk
operator|->
name|hunk
operator|->
name|type
operator||=
name|NGX_HUNK_LAST
expr_stmt|;
block|}
block|}
if|if
condition|(
name|p
operator|->
name|cachable
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|in_hunks
condition|)
block|{
name|rc
operator|=
name|ngx_event_proxy_write_chain_to_temp_file
argument_list|(
name|p
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
block|}
if|if
condition|(
name|p
operator|->
name|out_hunks
operator|&&
name|p
operator|->
name|client
operator|->
name|write
operator|->
name|ready
condition|)
block|{
name|rc
operator|=
name|ngx_event_proxy_write_to_client
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
block|}
if|else if
condition|(
operator|(
name|p
operator|->
name|out_hunks
operator|||
name|p
operator|->
name|in_hunks
operator|)
operator|&&
name|p
operator|->
name|client
operator|->
name|write
operator|->
name|ready
condition|)
block|{
name|rc
operator|=
name|ngx_event_proxy_write_to_client
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
name|p
operator|->
name|level
operator|--
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"level: %d"
argument|_ p->level
argument_list|)
empty_stmt|;
if|if
condition|(
name|p
operator|->
name|level
operator|==
literal|0
operator|&&
name|p
operator|->
name|block_upstream
condition|)
block|{
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|blocked
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ngx_del_event
argument_list|(
name|p
operator|->
name|upstream
operator|->
name|read
argument_list|,
name|NGX_READ_EVENT
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|p
operator|->
name|upstream_eof
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
else|else
block|{
return|return
name|NGX_AGAIN
return|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_event_proxy_write_to_client (ngx_event_proxy_t * p)
name|int
name|ngx_event_proxy_write_to_client
parameter_list|(
name|ngx_event_proxy_t
modifier|*
name|p
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
modifier|*
name|entry
decl_stmt|;
name|ngx_log_debug
argument_list|(
name|p
operator|->
name|log
argument_list|,
literal|"write to client"
argument_list|)
expr_stmt|;
name|h
operator|=
name|p
operator|->
name|busy_hunk
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|h
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|out_hunks
condition|)
block|{
name|entry
operator|=
name|p
operator|->
name|out_hunks
expr_stmt|;
name|p
operator|->
name|out_hunks
operator|=
name|entry
operator|->
name|next
expr_stmt|;
name|h
operator|=
name|entry
operator|->
name|hunk
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|shadow_hunks
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|shadow_hunks
operator|->
name|hunk
operator|==
name|h
operator|->
name|shadow
condition|)
block|{
name|p
operator|->
name|shadow_hunks
operator|=
name|p
operator|->
name|shadow_hunks
operator|->
name|next
expr_stmt|;
block|}
block|}
name|entry
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
if|else if
condition|(
name|p
operator|->
name|cachable
operator|==
literal|0
operator|&&
name|p
operator|->
name|in_hunks
condition|)
block|{
name|entry
operator|=
name|p
operator|->
name|in_hunks
expr_stmt|;
name|p
operator|->
name|in_hunks
operator|=
name|entry
operator|->
name|next
expr_stmt|;
name|h
operator|=
name|entry
operator|->
name|hunk
expr_stmt|;
name|entry
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"event proxy write hunk: %08X:%08X"
argument|_ h _ h->pos
argument_list|)
empty_stmt|;
if|if
condition|(
name|h
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|ready
condition|)
block|{
name|rc
operator|=
name|ngx_event_proxy_read_upstream
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
block|}
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"event proxy write: %d"
argument|_ h->last - h->pos
argument_list|)
empty_stmt|;
name|rc
operator|=
name|p
operator|->
name|output_filter
argument_list|(
name|p
operator|->
name|output_data
argument_list|,
name|h
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"event proxy: %d"
argument|_ rc
argument_list|)
empty_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_AGAIN
operator|||
operator|(
name|h
operator|->
name|type
operator|&
name|NGX_HUNK_IN_MEMORY
operator|&&
name|h
operator|->
name|pos
operator|<
name|h
operator|->
name|last
operator|)
operator|||
operator|(
name|h
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
operator|&&
name|h
operator|->
name|file_pos
operator|<
name|h
operator|->
name|file_last
operator|)
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|busy_hunk
operator|==
name|NULL
condition|)
block|{
name|p
operator|->
name|busy_hunk
operator|=
name|h
expr_stmt|;
block|}
return|return
name|NGX_AGAIN
return|;
block|}
name|p
operator|->
name|busy_hunk
operator|=
name|NULL
expr_stmt|;
comment|/* if the complete hunk is the file hunk and it has a shadow hunk            then add a shadow hunk to a free chain */
if|if
condition|(
name|h
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|cachable
operator|==
literal|0
operator|&&
name|p
operator|->
name|out_hunks
operator|==
name|NULL
condition|)
block|{
name|p
operator|->
name|temp_offset
operator|=
literal|0
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|(
name|h
operator|->
name|type
operator|&
name|NGX_HUNK_LAST_SHADOW
operator|)
operator|==
literal|0
condition|)
block|{
name|h
operator|=
name|NULL
expr_stmt|;
continue|continue;
block|}
name|h
operator|->
name|shadow
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|h
operator|=
name|h
operator|->
name|shadow
expr_stmt|;
if|#
directive|if
literal|0
comment|/* free the unneeded hunk */
block_content|if (p->upstream_eof) {             ngx_free_hunk(p->pool, h);             continue;         }
endif|#
directive|endif
name|h
operator|->
name|pos
operator|=
name|h
operator|->
name|last
operator|=
name|h
operator|->
name|start
expr_stmt|;
name|entry
operator|->
name|hunk
operator|=
name|h
expr_stmt|;
comment|/* if the first hunk in a free chain is partially filled            then add the complete hunk after the first free hunk */
if|if
condition|(
name|p
operator|->
name|free_hunks
operator|&&
name|p
operator|->
name|free_hunks
operator|->
name|hunk
operator|->
name|start
operator|!=
name|p
operator|->
name|free_hunks
operator|->
name|hunk
operator|->
name|last
condition|)
block|{
name|entry
operator|->
name|next
operator|=
name|p
operator|->
name|free_hunks
operator|->
name|next
expr_stmt|;
name|p
operator|->
name|free_hunks
operator|->
name|next
operator|=
name|entry
expr_stmt|;
block|}
else|else
block|{
name|entry
operator|->
name|next
operator|=
name|p
operator|->
name|free_hunks
expr_stmt|;
name|p
operator|->
name|free_hunks
operator|=
name|entry
expr_stmt|;
block|}
name|h
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_event_proxy_write_chain_to_temp_file (ngx_event_proxy_t * p)
name|int
name|ngx_event_proxy_write_chain_to_temp_file
parameter_list|(
name|ngx_event_proxy_t
modifier|*
name|p
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|rc
decl_stmt|,
name|size
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
modifier|*
name|entry
decl_stmt|,
modifier|*
name|next
decl_stmt|,
modifier|*
name|saved_in
decl_stmt|,
modifier|*
name|saved_read
decl_stmt|;
name|ngx_log_debug
argument_list|(
name|p
operator|->
name|log
argument_list|,
literal|"write to file"
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|temp_file
operator|->
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|rc
operator|=
name|ngx_create_temp_file
argument_list|(
name|p
operator|->
name|temp_file
argument_list|,
name|p
operator|->
name|temp_path
argument_list|,
name|p
operator|->
name|pool
argument_list|,
name|p
operator|->
name|number
argument_list|,
name|p
operator|->
name|random
argument_list|,
name|p
operator|->
name|cachable
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
if|if
condition|(
name|p
operator|->
name|cachable
operator|==
literal|0
operator|&&
name|p
operator|->
name|temp_file_warn
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|p
operator|->
name|log
argument_list|,
literal|0
argument_list|,
name|p
operator|->
name|temp_file_warn
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|p
operator|->
name|cachable
operator|==
literal|0
condition|)
block|{
name|entry
operator|=
name|p
operator|->
name|read_hunks
expr_stmt|;
name|size
operator|=
literal|0
expr_stmt|;
do|do
block|{
name|size
operator|+=
name|entry
operator|->
name|hunk
operator|->
name|last
operator|-
name|entry
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
if|if
condition|(
name|size
operator|>=
name|p
operator|->
name|file_block_size
condition|)
block|{
break|break;
block|}
name|entry
operator|=
name|entry
operator|->
name|next
expr_stmt|;
block|}
do|while
condition|(
name|entry
condition|)
do|;
name|saved_read
operator|=
name|entry
operator|->
name|next
expr_stmt|;
name|entry
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|saved_read
condition|)
block|{
for|for
control|(
name|entry
operator|=
name|p
operator|->
name|in_hunks
init|;
name|entry
operator|->
name|next
condition|;
name|entry
operator|=
name|entry
operator|->
name|next
control|)
block|{
if|if
condition|(
name|entry
operator|->
name|next
operator|->
name|hunk
operator|->
name|shadow
operator|==
name|saved_read
operator|->
name|hunk
condition|)
block|{
break|break;
block|}
block|}
name|saved_in
operator|=
name|entry
operator|->
name|next
expr_stmt|;
name|entry
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|saved_in
operator|=
name|NULL
expr_stmt|;
block|}
block|}
else|else
block|{
name|saved_read
operator|=
name|NULL
expr_stmt|;
name|saved_in
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|ngx_write_chain_to_file
argument_list|(
name|p
operator|->
name|temp_file
argument_list|,
name|p
operator|->
name|in_hunks
argument_list|,
name|p
operator|->
name|temp_offset
argument_list|,
name|p
operator|->
name|pool
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
for|for
control|(
name|entry
operator|=
name|p
operator|->
name|in_hunks
init|;
name|entry
condition|;
name|entry
operator|=
name|next
control|)
block|{
name|next
operator|=
name|entry
operator|->
name|next
expr_stmt|;
name|entry
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
name|h
operator|=
name|entry
operator|->
name|hunk
expr_stmt|;
name|h
operator|->
name|type
operator||=
name|NGX_HUNK_FILE
expr_stmt|;
name|h
operator|->
name|file
operator|=
name|p
operator|->
name|temp_file
expr_stmt|;
name|h
operator|->
name|file_pos
operator|=
name|p
operator|->
name|temp_offset
expr_stmt|;
name|p
operator|->
name|temp_offset
operator|+=
name|h
operator|->
name|last
operator|-
name|h
operator|->
name|pos
expr_stmt|;
name|h
operator|->
name|file_last
operator|=
name|p
operator|->
name|temp_offset
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"event proxy file hunk: %08X:%08X"
argument|_ h _ h->pos
argument_list|)
empty_stmt|;
if|if
condition|(
name|entry
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_LAST_SHADOW
condition|)
block|{
name|entry
operator|->
name|hunk
operator|->
name|shadow
operator|->
name|last
operator|=
name|entry
operator|->
name|hunk
operator|->
name|shadow
operator|->
name|pos
expr_stmt|;
block|}
if|if
condition|(
name|p
operator|->
name|out_hunks
condition|)
block|{
name|p
operator|->
name|last_out_hunk
operator|->
name|next
operator|=
name|entry
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|out_hunks
operator|=
name|entry
expr_stmt|;
block|}
name|p
operator|->
name|last_out_hunk
operator|=
name|entry
expr_stmt|;
block|}
name|p
operator|->
name|shadow_hunks
operator|=
name|p
operator|->
name|read_hunks
expr_stmt|;
name|p
operator|->
name|read_hunks
operator|=
name|saved_read
expr_stmt|;
name|p
operator|->
name|in_hunks
operator|=
name|saved_in
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

