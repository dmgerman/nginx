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
file|<ngx_event.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_pipe.h>
end_include

begin_function_decl
specifier|static
name|int
name|ngx_event_pipe_read_upstream
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_event_pipe_write_to_downstream
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_event_pipe_write_chain_to_temp_file
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_inline
specifier|static
name|void
name|ngx_event_pipe_remove_shadow_links
parameter_list|(
name|ngx_hunk_t
modifier|*
name|hunk
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_inline
specifier|static
name|void
name|ngx_event_pipe_free_shadow_raw_hunk
parameter_list|(
name|ngx_chain_t
modifier|*
modifier|*
name|free
parameter_list|,
name|ngx_hunk_t
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_inline
specifier|static
name|void
name|ngx_event_pipe_add_free_hunk
parameter_list|(
name|ngx_chain_t
modifier|*
modifier|*
name|chain
parameter_list|,
name|ngx_chain_t
modifier|*
name|cl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_event_pipe_drain_chains
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function
DECL|function|ngx_event_pipe (ngx_event_pipe_t * p,int do_write)
name|int
name|ngx_event_pipe
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|,
name|int
name|do_write
parameter_list|)
block|{
name|ngx_event_t
modifier|*
name|rev
decl_stmt|,
modifier|*
name|wev
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|do_write
condition|)
block|{
if|if
condition|(
name|ngx_event_pipe_write_to_downstream
argument_list|(
name|p
argument_list|)
operator|==
name|NGX_ABORT
condition|)
block|{
return|return
name|NGX_ABORT
return|;
block|}
block|}
name|p
operator|->
name|read
operator|=
literal|0
expr_stmt|;
name|p
operator|->
name|upstream_blocked
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ngx_event_pipe_read_upstream
argument_list|(
name|p
argument_list|)
operator|==
name|NGX_ABORT
condition|)
block|{
return|return
name|NGX_ABORT
return|;
block|}
if|if
condition|(
operator|!
name|p
operator|->
name|read
operator|&&
operator|!
name|p
operator|->
name|upstream_blocked
condition|)
block|{
break|break;
block|}
name|do_write
operator|=
literal|1
expr_stmt|;
block|}
name|rev
operator|=
name|p
operator|->
name|upstream
operator|->
name|read
expr_stmt|;
if|if
condition|(
name|ngx_handle_read_event
argument_list|(
name|rev
argument_list|,
operator|(
name|rev
operator|->
name|eof
operator|||
name|rev
operator|->
name|error
operator|)
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ABORT
return|;
block|}
if|if
condition|(
name|rev
operator|->
name|active
condition|)
block|{
name|ngx_add_timer
argument_list|(
name|rev
argument_list|,
name|p
operator|->
name|read_timeout
argument_list|)
expr_stmt|;
block|}
name|wev
operator|=
name|p
operator|->
name|downstream
operator|->
name|write
expr_stmt|;
if|if
condition|(
name|ngx_handle_write_event
argument_list|(
name|wev
argument_list|,
name|p
operator|->
name|send_lowat
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ABORT
return|;
block|}
if|if
condition|(
name|wev
operator|->
name|active
condition|)
block|{
name|ngx_add_timer
argument_list|(
name|wev
argument_list|,
name|p
operator|->
name|send_timeout
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_pipe_read_upstream (ngx_event_pipe_t * p)
name|int
name|ngx_event_pipe_read_upstream
parameter_list|(
name|ngx_event_pipe_t
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
decl_stmt|;
name|ngx_chain_t
modifier|*
name|chain
decl_stmt|,
modifier|*
name|cl
decl_stmt|,
modifier|*
name|tl
decl_stmt|;
if|if
condition|(
name|p
operator|->
name|upstream_eof
operator|||
name|p
operator|->
name|upstream_error
operator|||
name|p
operator|->
name|upstream_done
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"read upstream: %d"
argument|_ p->upstream->read->ready
argument_list|)
empty_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|p
operator|->
name|upstream_eof
operator|||
name|p
operator|->
name|upstream_error
operator|||
name|p
operator|->
name|upstream_done
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|p
operator|->
name|preread_hunks
operator|==
name|NULL
operator|&&
operator|!
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|ready
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|p
operator|->
name|preread_hunks
condition|)
block|{
comment|/* use the pre-read hunks if they exist */
name|p
operator|->
name|read
operator|=
literal|1
expr_stmt|;
name|chain
operator|=
name|p
operator|->
name|preread_hunks
expr_stmt|;
name|p
operator|->
name|preread_hunks
operator|=
name|NULL
expr_stmt|;
name|n
operator|=
name|p
operator|->
name|preread_size
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"preread: %d"
argument|_ n
argument_list|)
empty_stmt|;
block|}
else|else
block|{
comment|/*              * kqueue notifies about the end of file or a pending error.              * This test allows not to allocate a hunk on these conditions              * and not to call ngx_recv_chain().              */
if|if
condition|(
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|available
operator|==
literal|0
operator|&&
operator|(
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|kq_eof
operator|||
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|aio_eof
operator|)
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
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|eof
operator|=
literal|0
expr_stmt|;
name|p
operator|->
name|upstream_eof
operator|=
literal|1
expr_stmt|;
name|p
operator|->
name|read
operator|=
literal|1
expr_stmt|;
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
if|if
condition|(
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|kq_errno
condition|)
block|{
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|p
operator|->
name|upstream_error
operator|=
literal|1
expr_stmt|;
name|p
operator|->
name|upstream_eof
operator|=
literal|0
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|p
operator|->
name|log
argument_list|,
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|kq_errno
argument_list|,
literal|"readv() failed"
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
break|break;
block|}
if|if
condition|(
name|p
operator|->
name|free_raw_hunks
condition|)
block|{
comment|/* use the free hunks if they exist */
name|chain
operator|=
name|p
operator|->
name|free_raw_hunks
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|single_buf
condition|)
block|{
name|p
operator|->
name|free_raw_hunks
operator|=
name|p
operator|->
name|free_raw_hunks
operator|->
name|next
expr_stmt|;
name|chain
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|free_raw_hunks
operator|=
name|NULL
expr_stmt|;
block|}
block|}
if|else if
condition|(
name|p
operator|->
name|hunks
operator|<
name|p
operator|->
name|bufs
operator|.
name|num
condition|)
block|{
comment|/* allocate a new hunk if it's still allowed */
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
name|bufs
operator|.
name|size
argument_list|)
argument_list|,
name|NGX_ABORT
argument_list|)
expr_stmt|;
name|p
operator|->
name|hunks
operator|++
expr_stmt|;
name|ngx_alloc_link_and_set_hunk
argument_list|(
name|tl
argument_list|,
name|h
argument_list|,
name|p
operator|->
name|pool
argument_list|,
name|NGX_ABORT
argument_list|)
expr_stmt|;
name|chain
operator|=
name|tl
expr_stmt|;
block|}
if|else if
condition|(
operator|!
name|p
operator|->
name|cachable
operator|&&
name|p
operator|->
name|downstream
operator|->
name|write
operator|->
name|ready
condition|)
block|{
comment|/*                  * if the hunks are not needed to be saved in a cache and                  * a downstream is ready then write the hunks to a downstream                  */
name|p
operator|->
name|upstream_blocked
operator|=
literal|1
expr_stmt|;
name|ngx_log_debug
argument_list|(
name|p
operator|->
name|log
argument_list|,
literal|"downstream ready"
argument_list|)
expr_stmt|;
break|break;
block|}
if|else if
condition|(
name|p
operator|->
name|cachable
operator|||
name|p
operator|->
name|temp_offset
operator|<
name|p
operator|->
name|max_temp_file_size
condition|)
block|{
comment|/*                  * if it's allowed then save some hunks from r->in                  * to a temporary file, and add them to a r->out chain                  */
name|rc
operator|=
name|ngx_event_pipe_write_chain_to_temp_file
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
operator|==
name|NGX_AGAIN
condition|)
block|{
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_LEVEL_EVENT
operator|&&
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|active
operator|&&
name|p
operator|->
name|upstream
operator|->
name|read
operator|->
name|ready
condition|)
block|{
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
name|NGX_ABORT
return|;
block|}
block|}
block|}
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
name|free_raw_hunks
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|single_buf
condition|)
block|{
name|p
operator|->
name|free_raw_hunks
operator|=
name|p
operator|->
name|free_raw_hunks
operator|->
name|next
expr_stmt|;
name|chain
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|free_raw_hunks
operator|=
name|NULL
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* if there're no hunks to read in then disable a level event */
name|ngx_log_debug
argument_list|(
name|p
operator|->
name|log
argument_list|,
literal|"no hunks to read in"
argument_list|)
expr_stmt|;
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
name|p
operator|->
name|free_raw_hunks
condition|)
block|{
name|chain
operator|->
name|next
operator|=
name|p
operator|->
name|free_raw_hunks
expr_stmt|;
block|}
name|p
operator|->
name|free_raw_hunks
operator|=
name|chain
expr_stmt|;
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
name|single_buf
condition|)
block|{
name|ngx_event_pipe_remove_shadow_links
argument_list|(
name|chain
operator|->
name|hunk
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
name|p
operator|->
name|read
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|p
operator|->
name|upstream_eof
operator|=
literal|1
expr_stmt|;
break|break;
block|}
block|}
name|cl
operator|=
name|chain
expr_stmt|;
while|while
condition|(
name|cl
operator|&&
name|n
operator|>
literal|0
condition|)
block|{
name|ngx_event_pipe_remove_shadow_links
argument_list|(
name|cl
operator|->
name|hunk
argument_list|)
expr_stmt|;
name|size
operator|=
name|cl
operator|->
name|hunk
operator|->
name|end
operator|-
name|cl
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
name|cl
operator|->
name|hunk
operator|->
name|last
operator|=
name|cl
operator|->
name|hunk
operator|->
name|end
expr_stmt|;
comment|/* STUB */
name|cl
operator|->
name|hunk
operator|->
name|num
operator|=
name|p
operator|->
name|num
operator|++
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|input_filter
argument_list|(
name|p
argument_list|,
name|cl
operator|->
name|hunk
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ABORT
return|;
block|}
name|n
operator|-=
name|size
expr_stmt|;
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
block|}
else|else
block|{
name|cl
operator|->
name|hunk
operator|->
name|last
operator|+=
name|n
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
block|}
block|}
name|p
operator|->
name|free_raw_hunks
operator|=
name|cl
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|p
operator|->
name|upstream_eof
operator|||
name|p
operator|->
name|upstream_error
operator|)
operator|&&
name|p
operator|->
name|free_raw_hunks
condition|)
block|{
comment|/* STUB */
name|p
operator|->
name|free_raw_hunks
operator|->
name|hunk
operator|->
name|num
operator|=
name|p
operator|->
name|num
operator|++
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|input_filter
argument_list|(
name|p
argument_list|,
name|p
operator|->
name|free_raw_hunks
operator|->
name|hunk
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ABORT
return|;
block|}
name|p
operator|->
name|free_raw_hunks
operator|=
name|p
operator|->
name|free_raw_hunks
operator|->
name|next
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|free_bufs
condition|)
block|{
for|for
control|(
name|cl
operator|=
name|p
operator|->
name|free_raw_hunks
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
name|ngx_pfree
argument_list|(
name|p
operator|->
name|pool
argument_list|,
name|cl
operator|->
name|hunk
operator|->
name|start
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|p
operator|->
name|cachable
operator|&&
name|p
operator|->
name|in
condition|)
block|{
if|if
condition|(
name|ngx_event_pipe_write_chain_to_temp_file
argument_list|(
name|p
argument_list|)
operator|==
name|NGX_ABORT
condition|)
block|{
return|return
name|NGX_ABORT
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_pipe_write_to_downstream (ngx_event_pipe_t * p)
name|int
name|ngx_event_pipe_write_to_downstream
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|)
block|{
name|size_t
name|bsize
decl_stmt|,
name|to_write
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
modifier|*
name|out
decl_stmt|,
modifier|*
modifier|*
name|ll
decl_stmt|,
modifier|*
name|cl
decl_stmt|,
modifier|*
name|tl
decl_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"write downstream: %d"
argument|_ p->downstream->write->ready
argument_list|)
empty_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|p
operator|->
name|downstream_error
condition|)
block|{
return|return
name|ngx_event_pipe_drain_chains
argument_list|(
name|p
argument_list|)
return|;
block|}
if|if
condition|(
operator|(
name|p
operator|->
name|upstream_eof
operator|||
name|p
operator|->
name|upstream_error
operator|||
name|p
operator|->
name|upstream_done
operator|)
operator|&&
name|p
operator|->
name|out
operator|==
name|NULL
operator|&&
name|p
operator|->
name|in
operator|==
name|NULL
condition|)
block|{
name|p
operator|->
name|downstream_done
operator|=
literal|1
expr_stmt|;
break|break;
block|}
if|if
condition|(
operator|!
name|p
operator|->
name|downstream
operator|->
name|write
operator|->
name|ready
condition|)
block|{
break|break;
block|}
comment|/*          * bsize is the busy hunks size          * to_write is the size of data that to be written          */
name|bsize
operator|=
literal|0
expr_stmt|;
name|to_write
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|p
operator|->
name|upstream_eof
operator|||
name|p
operator|->
name|upstream_error
operator|||
name|p
operator|->
name|upstream_done
operator|)
condition|)
block|{
for|for
control|(
name|cl
operator|=
name|p
operator|->
name|busy
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
name|bsize
operator|+=
name|cl
operator|->
name|hunk
operator|->
name|end
operator|-
name|cl
operator|->
name|hunk
operator|->
name|start
expr_stmt|;
name|to_write
operator|+=
name|ngx_hunk_size
argument_list|(
name|cl
operator|->
name|hunk
argument_list|)
expr_stmt|;
block|}
block|}
name|out
operator|=
name|NULL
expr_stmt|;
name|ll
operator|=
name|NULL
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|p
operator|->
name|out
condition|)
block|{
name|cl
operator|=
name|p
operator|->
name|out
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|p
operator|->
name|upstream_eof
operator|||
name|p
operator|->
name|upstream_error
operator|||
name|p
operator|->
name|upstream_done
operator|)
operator|&&
operator|(
name|bsize
operator|+
name|ngx_hunk_size
argument_list|(
name|cl
operator|->
name|hunk
argument_list|)
operator|>
name|p
operator|->
name|busy_size
operator|)
condition|)
block|{
break|break;
block|}
name|p
operator|->
name|out
operator|=
name|p
operator|->
name|out
operator|->
name|next
expr_stmt|;
name|ngx_event_pipe_free_shadow_raw_hunk
argument_list|(
operator|&
name|p
operator|->
name|free_raw_hunks
argument_list|,
name|cl
operator|->
name|hunk
argument_list|)
expr_stmt|;
block|}
if|else if
condition|(
operator|!
name|p
operator|->
name|cachable
operator|&&
name|p
operator|->
name|in
condition|)
block|{
name|cl
operator|=
name|p
operator|->
name|in
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|p
operator|->
name|upstream_eof
operator|||
name|p
operator|->
name|upstream_error
operator|||
name|p
operator|->
name|upstream_done
operator|)
operator|&&
operator|(
name|bsize
operator|+
name|ngx_hunk_size
argument_list|(
name|cl
operator|->
name|hunk
argument_list|)
operator|>
name|p
operator|->
name|busy_size
operator|)
condition|)
block|{
break|break;
block|}
name|p
operator|->
name|in
operator|=
name|p
operator|->
name|in
operator|->
name|next
expr_stmt|;
block|}
else|else
block|{
break|break;
block|}
name|bsize
operator|+=
name|ngx_hunk_size
argument_list|(
name|cl
operator|->
name|hunk
argument_list|)
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
name|ngx_chain_add_link
argument_list|(
name|out
argument_list|,
name|ll
argument_list|,
name|cl
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|out
operator|==
name|NULL
condition|)
block|{
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"no hunks to write BUSY: %d"
argument|_ to_write
argument_list|)
empty_stmt|;
if|if
condition|(
operator|!
operator|(
name|p
operator|->
name|upstream_blocked
operator|&&
name|to_write
operator|)
condition|)
block|{
break|break;
block|}
comment|/*              * if the upstream is blocked and there are the busy hunks              * to write then write these hunks              */
block|}
if|if
condition|(
name|p
operator|->
name|output_filter
argument_list|(
name|p
operator|->
name|output_ctx
argument_list|,
name|out
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|p
operator|->
name|downstream_error
operator|=
literal|1
expr_stmt|;
comment|/* handle the downstream error at the begin of a cycle */
continue|continue;
block|}
name|ngx_chain_update_chains
argument_list|(
operator|&
name|p
operator|->
name|free
argument_list|,
operator|&
name|p
operator|->
name|busy
argument_list|,
operator|&
name|out
argument_list|,
name|p
operator|->
name|tag
argument_list|)
expr_stmt|;
for|for
control|(
name|cl
operator|=
name|p
operator|->
name|free
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
comment|/* TODO: free hunk if p->free_bufs&& upstream done */
comment|/* add the free shadow raw hunk to p->free_raw_hunks */
if|if
condition|(
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_LAST_SHADOW
condition|)
block|{
name|h
operator|=
name|cl
operator|->
name|hunk
operator|->
name|shadow
expr_stmt|;
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
name|h
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|ngx_alloc_link_and_set_hunk
argument_list|(
name|tl
argument_list|,
name|h
argument_list|,
name|p
operator|->
name|pool
argument_list|,
name|NGX_ABORT
argument_list|)
expr_stmt|;
name|ngx_event_pipe_add_free_hunk
argument_list|(
operator|&
name|p
operator|->
name|free_raw_hunks
argument_list|,
name|tl
argument_list|)
expr_stmt|;
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&=
operator|~
name|NGX_HUNK_LAST_SHADOW
expr_stmt|;
block|}
name|cl
operator|->
name|hunk
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|cyclic_temp_file
operator|&&
operator|(
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_TEMP_FILE
operator|)
condition|)
block|{
comment|/* reset p->temp_offset if all hunks had been sent */
if|if
condition|(
name|cl
operator|->
name|hunk
operator|->
name|file_last
operator|==
name|p
operator|->
name|temp_offset
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
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_pipe_write_chain_to_temp_file (ngx_event_pipe_t * p)
specifier|static
name|int
name|ngx_event_pipe_write_chain_to_temp_file
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|)
block|{
name|int
name|rc
decl_stmt|,
name|size
decl_stmt|,
name|hsize
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|,
modifier|*
name|tl
decl_stmt|,
modifier|*
name|next
decl_stmt|,
modifier|*
name|out
decl_stmt|,
modifier|*
modifier|*
name|ll
decl_stmt|,
modifier|*
modifier|*
name|last_free
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
name|cachable
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
name|NGX_ABORT
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
operator|!
name|p
operator|->
name|cachable
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
name|out
operator|=
name|p
operator|->
name|in
expr_stmt|;
if|if
condition|(
operator|!
name|p
operator|->
name|cachable
condition|)
block|{
name|size
operator|=
literal|0
expr_stmt|;
name|cl
operator|=
name|p
operator|->
name|in
expr_stmt|;
name|ll
operator|=
name|NULL
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"offset: %d"
argument|_ p->temp_offset
argument_list|)
empty_stmt|;
do|do
block|{
name|hsize
operator|=
name|cl
operator|->
name|hunk
operator|->
name|last
operator|-
name|cl
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"hunk size: %d"
argument|_ hsize
argument_list|)
empty_stmt|;
if|if
condition|(
operator|(
name|size
operator|+
name|hsize
operator|>
name|p
operator|->
name|temp_file_write_size
operator|)
operator|||
operator|(
name|p
operator|->
name|temp_offset
operator|+
name|size
operator|+
name|hsize
operator|>
name|p
operator|->
name|max_temp_file_size
operator|)
condition|)
block|{
break|break;
block|}
name|size
operator|+=
name|hsize
expr_stmt|;
name|ll
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
block|}
do|while
condition|(
name|cl
condition|)
do|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"size: %d"
argument|_ size
argument_list|)
empty_stmt|;
if|if
condition|(
name|cl
condition|)
block|{
name|p
operator|->
name|in
operator|=
name|cl
expr_stmt|;
operator|*
name|ll
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|p
operator|->
name|in
operator|=
name|NULL
expr_stmt|;
name|p
operator|->
name|last_in
operator|=
operator|&
name|p
operator|->
name|in
expr_stmt|;
block|}
block|}
else|else
block|{
name|p
operator|->
name|in
operator|=
name|NULL
expr_stmt|;
name|p
operator|->
name|last_in
operator|=
operator|&
name|p
operator|->
name|in
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
name|out
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
name|NGX_ABORT
return|;
block|}
for|for
control|(
name|last_free
operator|=
operator|&
name|p
operator|->
name|free_raw_hunks
init|;
operator|*
name|last_free
operator|!=
name|NULL
condition|;
name|last_free
operator|=
operator|&
operator|(
operator|*
name|last_free
operator|)
operator|->
name|next
control|)
block|{
comment|/* void */
block|}
for|for
control|(
name|cl
operator|=
name|out
init|;
name|cl
condition|;
name|cl
operator|=
name|next
control|)
block|{
name|next
operator|=
name|cl
operator|->
name|next
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
name|h
operator|=
name|cl
operator|->
name|hunk
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
if|if
condition|(
name|p
operator|->
name|cachable
condition|)
block|{
name|h
operator|->
name|type
operator||=
name|NGX_HUNK_FILE
expr_stmt|;
block|}
else|else
block|{
name|h
operator|->
name|type
operator||=
name|NGX_HUNK_FILE
operator||
name|NGX_HUNK_TEMP_FILE
expr_stmt|;
block|}
name|ngx_chain_add_link
argument_list|(
name|p
operator|->
name|out
argument_list|,
name|p
operator|->
name|last_out
argument_list|,
name|cl
argument_list|)
expr_stmt|;
if|if
condition|(
name|h
operator|->
name|type
operator|&
name|NGX_HUNK_LAST_SHADOW
condition|)
block|{
name|h
operator|->
name|shadow
operator|->
name|last
operator|=
name|h
operator|->
name|shadow
operator|->
name|pos
operator|=
name|h
operator|->
name|shadow
operator|->
name|start
expr_stmt|;
name|ngx_alloc_link_and_set_hunk
argument_list|(
name|tl
argument_list|,
name|h
operator|->
name|shadow
argument_list|,
name|p
operator|->
name|pool
argument_list|,
name|NGX_ABORT
argument_list|)
expr_stmt|;
operator|*
name|last_free
operator|=
name|tl
expr_stmt|;
name|last_free
operator|=
operator|&
name|tl
operator|->
name|next
expr_stmt|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_comment
comment|/* the copy input filter */
end_comment

begin_function
DECL|function|ngx_event_pipe_copy_input_filter (ngx_event_pipe_t * p,ngx_hunk_t * hunk)
name|int
name|ngx_event_pipe_copy_input_filter
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|,
name|ngx_hunk_t
modifier|*
name|hunk
parameter_list|)
block|{
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
if|if
condition|(
name|hunk
operator|->
name|pos
operator|==
name|hunk
operator|->
name|last
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|p
operator|->
name|free
condition|)
block|{
name|h
operator|=
name|p
operator|->
name|free
operator|->
name|hunk
expr_stmt|;
name|p
operator|->
name|free
operator|=
name|p
operator|->
name|free
operator|->
name|next
expr_stmt|;
block|}
else|else
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
block|}
name|ngx_memcpy
argument_list|(
name|h
argument_list|,
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
name|hunk
expr_stmt|;
name|h
operator|->
name|tag
operator|=
name|p
operator|->
name|tag
expr_stmt|;
name|h
operator|->
name|type
operator||=
name|NGX_HUNK_LAST_SHADOW
operator||
name|NGX_HUNK_RECYCLED
expr_stmt|;
name|hunk
operator|->
name|shadow
operator|=
name|h
expr_stmt|;
name|ngx_alloc_link_and_set_hunk
argument_list|(
name|cl
argument_list|,
name|h
argument_list|,
name|p
operator|->
name|pool
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|p->log
argument_list|,
literal|"HUNK %d"
argument|_ h->num
argument_list|)
empty_stmt|;
name|ngx_chain_add_link
argument_list|(
name|p
operator|->
name|in
argument_list|,
name|p
operator|->
name|last_in
argument_list|,
name|cl
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_event_pipe_remove_shadow_links (ngx_hunk_t * hunk)
name|ngx_inline
specifier|static
name|void
name|ngx_event_pipe_remove_shadow_links
parameter_list|(
name|ngx_hunk_t
modifier|*
name|hunk
parameter_list|)
block|{
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|,
modifier|*
name|next
decl_stmt|;
if|if
condition|(
name|hunk
operator|->
name|shadow
operator|==
name|NULL
condition|)
block|{
return|return;
block|}
name|h
operator|=
name|hunk
operator|->
name|shadow
expr_stmt|;
while|while
condition|(
operator|!
operator|(
name|h
operator|->
name|type
operator|&
name|NGX_HUNK_LAST_SHADOW
operator|)
condition|)
block|{
name|next
operator|=
name|h
operator|->
name|shadow
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
name|h
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|h
operator|=
name|next
expr_stmt|;
block|}
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
name|h
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|hunk
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_event_pipe_free_shadow_raw_hunk (ngx_chain_t ** free,ngx_hunk_t * h)
name|ngx_inline
specifier|static
name|void
name|ngx_event_pipe_free_shadow_raw_hunk
parameter_list|(
name|ngx_chain_t
modifier|*
modifier|*
name|free
parameter_list|,
name|ngx_hunk_t
modifier|*
name|h
parameter_list|)
block|{
name|ngx_hunk_t
modifier|*
name|s
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|,
modifier|*
modifier|*
name|ll
decl_stmt|;
if|if
condition|(
name|h
operator|->
name|shadow
operator|==
name|NULL
condition|)
block|{
return|return;
block|}
for|for
control|(
name|s
operator|=
name|h
operator|->
name|shadow
init|;
operator|!
operator|(
name|s
operator|->
name|type
operator|&
name|NGX_HUNK_LAST_SHADOW
operator|)
condition|;
name|s
operator|=
name|s
operator|->
name|shadow
control|)
block|{
comment|/* void */
block|}
name|ll
operator|=
name|free
expr_stmt|;
for|for
control|(
name|cl
operator|=
operator|*
name|free
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
name|hunk
operator|==
name|s
condition|)
block|{
operator|*
name|ll
operator|=
name|cl
operator|->
name|next
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|cl
operator|->
name|hunk
operator|->
name|shadow
condition|)
block|{
break|break;
block|}
name|ll
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_event_pipe_add_free_hunk (ngx_chain_t ** chain,ngx_chain_t * cl)
name|ngx_inline
specifier|static
name|void
name|ngx_event_pipe_add_free_hunk
parameter_list|(
name|ngx_chain_t
modifier|*
modifier|*
name|chain
parameter_list|,
name|ngx_chain_t
modifier|*
name|cl
parameter_list|)
block|{
if|if
condition|(
operator|*
name|chain
operator|==
name|NULL
condition|)
block|{
operator|*
name|chain
operator|=
name|cl
expr_stmt|;
return|return;
block|}
if|if
condition|(
operator|(
operator|*
name|chain
operator|)
operator|->
name|hunk
operator|->
name|pos
operator|!=
operator|(
operator|*
name|chain
operator|)
operator|->
name|hunk
operator|->
name|last
condition|)
block|{
name|cl
operator|->
name|next
operator|=
operator|(
operator|*
name|chain
operator|)
operator|->
name|next
expr_stmt|;
operator|(
operator|*
name|chain
operator|)
operator|->
name|next
operator|=
name|cl
expr_stmt|;
block|}
else|else
block|{
name|cl
operator|->
name|next
operator|=
operator|(
operator|*
name|chain
operator|)
expr_stmt|;
operator|(
operator|*
name|chain
operator|)
operator|=
name|cl
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_event_pipe_drain_chains (ngx_event_pipe_t * p)
specifier|static
name|int
name|ngx_event_pipe_drain_chains
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|)
block|{
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|,
modifier|*
name|tl
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|p
operator|->
name|busy
condition|)
block|{
name|cl
operator|=
name|p
operator|->
name|busy
expr_stmt|;
block|}
if|else if
condition|(
name|p
operator|->
name|out
condition|)
block|{
name|cl
operator|=
name|p
operator|->
name|out
expr_stmt|;
block|}
if|else if
condition|(
name|p
operator|->
name|in
condition|)
block|{
name|cl
operator|=
name|p
operator|->
name|in
expr_stmt|;
block|}
else|else
block|{
return|return
name|NGX_OK
return|;
block|}
while|while
condition|(
name|cl
condition|)
block|{
if|if
condition|(
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_LAST_SHADOW
condition|)
block|{
name|h
operator|=
name|cl
operator|->
name|hunk
operator|->
name|shadow
expr_stmt|;
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
name|h
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|ngx_alloc_link_and_set_hunk
argument_list|(
name|tl
argument_list|,
name|h
argument_list|,
name|p
operator|->
name|pool
argument_list|,
name|NGX_ABORT
argument_list|)
expr_stmt|;
name|ngx_event_pipe_add_free_hunk
argument_list|(
operator|&
name|p
operator|->
name|free_raw_hunks
argument_list|,
name|tl
argument_list|)
expr_stmt|;
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&=
operator|~
name|NGX_HUNK_LAST_SHADOW
expr_stmt|;
block|}
name|cl
operator|->
name|hunk
operator|->
name|shadow
operator|=
name|NULL
expr_stmt|;
name|tl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|p
operator|->
name|free
expr_stmt|;
name|p
operator|->
name|free
operator|=
name|cl
expr_stmt|;
name|cl
operator|=
name|tl
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

