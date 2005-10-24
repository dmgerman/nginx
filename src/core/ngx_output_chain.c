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
file|<ngx_event.h>
end_include

begin_if
if|#
directive|if
literal|0
end_if

begin_define
define|#
directive|define
name|NGX_SENDFILE_LIMIT
value|4096
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_NONE
define|#
directive|define
name|NGX_NONE
value|1
end_define

begin_function_decl
specifier|static
name|ngx_inline
name|ngx_int_t
name|ngx_output_chain_need_to_copy
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_buf_t
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_output_chain_add_copy
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_chain_t
modifier|*
modifier|*
name|chain
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_output_chain_copy_buf
parameter_list|(
name|ngx_buf_t
modifier|*
name|dst
parameter_list|,
name|ngx_buf_t
modifier|*
name|src
parameter_list|,
name|ngx_uint_t
name|sendfile
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|ngx_int_t
DECL|function|ngx_output_chain (ngx_output_chain_ctx_t * ctx,ngx_chain_t * in)
name|ngx_output_chain
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
block|{
name|int
name|rc
decl_stmt|,
name|last
decl_stmt|;
name|off_t
name|bsize
decl_stmt|;
name|size_t
name|size
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|,
modifier|*
name|out
decl_stmt|,
modifier|*
modifier|*
name|last_out
decl_stmt|;
if|if
condition|(
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
condition|)
block|{
comment|/*          * the short path for the case when the ctx->in and ctx->busy chains          * are empty, the incoming chain is empty too or has the single buf          * that does not require the copy          */
if|if
condition|(
name|in
operator|==
name|NULL
condition|)
block|{
return|return
name|ctx
operator|->
name|output_filter
argument_list|(
name|ctx
operator|->
name|filter_ctx
argument_list|,
name|in
argument_list|)
return|;
block|}
if|if
condition|(
name|in
operator|->
name|next
operator|==
name|NULL
if|#
directive|if
operator|(
name|NGX_SENDFILE_LIMIT
operator|)
operator|&&
operator|!
operator|(
name|in
operator|->
name|buf
operator|->
name|in_file
operator|&&
name|in
operator|->
name|buf
operator|->
name|file_last
operator|>
name|NGX_SENDFILE_LIMIT
operator|)
endif|#
directive|endif
operator|&&
operator|!
name|ngx_output_chain_need_to_copy
argument_list|(
name|ctx
argument_list|,
name|in
operator|->
name|buf
argument_list|)
condition|)
block|{
return|return
name|ctx
operator|->
name|output_filter
argument_list|(
name|ctx
operator|->
name|filter_ctx
argument_list|,
name|in
argument_list|)
return|;
block|}
block|}
comment|/* add the incoming buf to the chain ctx->in */
if|if
condition|(
name|in
condition|)
block|{
if|if
condition|(
name|ngx_output_chain_add_copy
argument_list|(
name|ctx
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
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
name|out
operator|=
name|NULL
expr_stmt|;
name|last_out
operator|=
operator|&
name|out
expr_stmt|;
name|last
operator|=
name|NGX_NONE
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
while|while
condition|(
name|ctx
operator|->
name|in
condition|)
block|{
comment|/*              * cycle while there are the ctx->in bufs              * or there are the free output bufs to copy in              */
name|bsize
operator|=
name|ngx_buf_size
argument_list|(
name|ctx
operator|->
name|in
operator|->
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|bsize
operator|==
literal|0
operator|&&
operator|!
name|ngx_buf_special
argument_list|(
name|ctx
operator|->
name|in
operator|->
name|buf
argument_list|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ctx
operator|->
name|pool
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"zero size buf in output "
literal|"t:%d r:%d f:%d %p %p-%p %p %O-%O"
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|temporary
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|recycled
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|in_file
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|start
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|last
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|file
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|file_pos
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|file_last
argument_list|)
expr_stmt|;
name|ngx_debug_point
argument_list|()
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
continue|continue;
block|}
if|if
condition|(
operator|!
name|ngx_output_chain_need_to_copy
argument_list|(
name|ctx
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
argument_list|)
condition|)
block|{
comment|/* move the chain link to the output chain */
name|cl
operator|=
name|ctx
operator|->
name|in
expr_stmt|;
name|ctx
operator|->
name|in
operator|=
name|cl
operator|->
name|next
expr_stmt|;
operator|*
name|last_out
operator|=
name|cl
expr_stmt|;
name|last_out
operator|=
operator|&
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
continue|continue;
block|}
if|if
condition|(
name|ctx
operator|->
name|buf
operator|==
name|NULL
condition|)
block|{
comment|/* get the free buf */
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
name|buf
operator|=
name|cl
operator|->
name|buf
expr_stmt|;
name|ctx
operator|->
name|free
operator|=
name|cl
operator|->
name|next
expr_stmt|;
name|ngx_free_chain
argument_list|(
name|ctx
operator|->
name|pool
argument_list|,
name|cl
argument_list|)
expr_stmt|;
block|}
if|else if
condition|(
name|out
operator|||
name|ctx
operator|->
name|allocated
operator|==
name|ctx
operator|->
name|bufs
operator|.
name|num
condition|)
block|{
break|break;
block|}
else|else
block|{
name|size
operator|=
name|ctx
operator|->
name|bufs
operator|.
name|size
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|in
operator|->
name|buf
operator|->
name|last_in_chain
condition|)
block|{
if|if
condition|(
name|bsize
operator|<
operator|(
name|off_t
operator|)
name|ctx
operator|->
name|bufs
operator|.
name|size
condition|)
block|{
comment|/*                             * allocate small temp buf for the small last buf                             * or its small last part                             */
name|size
operator|=
operator|(
name|size_t
operator|)
name|bsize
expr_stmt|;
block|}
if|else if
condition|(
name|ctx
operator|->
name|bufs
operator|.
name|num
operator|==
literal|1
operator|&&
operator|(
name|bsize
operator|<
operator|(
name|off_t
operator|)
operator|(
name|ctx
operator|->
name|bufs
operator|.
name|size
operator|+
operator|(
name|ctx
operator|->
name|bufs
operator|.
name|size
operator|>>
literal|2
operator|)
operator|)
operator|)
condition|)
block|{
comment|/*                              * allocate a temp buf that equals                              * to the last buf if the last buf size is lesser                              * than 1.25 of bufs.size and a temp buf is single                              */
name|size
operator|=
operator|(
name|size_t
operator|)
name|bsize
expr_stmt|;
block|}
block|}
name|ctx
operator|->
name|buf
operator|=
name|ngx_create_temp_buf
argument_list|(
name|ctx
operator|->
name|pool
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|buf
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
name|buf
operator|->
name|tag
operator|=
name|ctx
operator|->
name|tag
expr_stmt|;
name|ctx
operator|->
name|buf
operator|->
name|recycled
operator|=
literal|1
expr_stmt|;
name|ctx
operator|->
name|allocated
operator|++
expr_stmt|;
block|}
block|}
name|rc
operator|=
name|ngx_output_chain_copy_buf
argument_list|(
name|ctx
operator|->
name|buf
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|buf
argument_list|,
name|ctx
operator|->
name|sendfile
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
name|rc
operator|==
name|NGX_AGAIN
condition|)
block|{
if|if
condition|(
name|out
condition|)
block|{
break|break;
block|}
return|return
name|rc
return|;
block|}
comment|/* delete the completed buf from the ctx->in chain */
if|if
condition|(
name|ngx_buf_size
argument_list|(
name|ctx
operator|->
name|in
operator|->
name|buf
argument_list|)
operator|==
literal|0
condition|)
block|{
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
block|}
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|ctx
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
name|buf
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
operator|*
name|last_out
operator|=
name|cl
expr_stmt|;
name|last_out
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
name|ctx
operator|->
name|buf
operator|=
name|NULL
expr_stmt|;
block|}
if|if
condition|(
name|out
operator|==
name|NULL
operator|&&
name|last
operator|!=
name|NGX_NONE
condition|)
block|{
if|if
condition|(
name|ctx
operator|->
name|in
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
return|return
name|last
return|;
block|}
name|last
operator|=
name|ctx
operator|->
name|output_filter
argument_list|(
name|ctx
operator|->
name|filter_ctx
argument_list|,
name|out
argument_list|)
expr_stmt|;
if|if
condition|(
name|last
operator|==
name|NGX_ERROR
operator|||
name|last
operator|==
name|NGX_DONE
condition|)
block|{
return|return
name|last
return|;
block|}
name|ngx_chain_update_chains
argument_list|(
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
name|out
argument_list|,
name|ctx
operator|->
name|tag
argument_list|)
expr_stmt|;
name|last_out
operator|=
operator|&
name|out
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|ngx_int_t
DECL|function|ngx_output_chain_need_to_copy (ngx_output_chain_ctx_t * ctx,ngx_buf_t * buf)
name|ngx_output_chain_need_to_copy
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_buf_t
modifier|*
name|buf
parameter_list|)
block|{
name|ngx_uint_t
name|sendfile
decl_stmt|;
if|if
condition|(
name|ngx_buf_special
argument_list|(
name|buf
argument_list|)
condition|)
block|{
return|return
literal|0
return|;
block|}
name|sendfile
operator|=
name|ctx
operator|->
name|sendfile
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_SENDFILE_LIMIT
operator|)
if|if
condition|(
name|buf
operator|->
name|in_file
operator|&&
name|buf
operator|->
name|file_pos
operator|>=
name|NGX_SENDFILE_LIMIT
condition|)
block|{
name|sendfile
operator|=
literal|0
expr_stmt|;
block|}
endif|#
directive|endif
if|if
condition|(
operator|!
name|sendfile
condition|)
block|{
if|if
condition|(
operator|!
name|ngx_buf_in_memory
argument_list|(
name|buf
argument_list|)
condition|)
block|{
return|return
literal|1
return|;
block|}
name|buf
operator|->
name|in_file
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|ctx
operator|->
name|need_in_memory
operator|&&
operator|!
name|ngx_buf_in_memory
argument_list|(
name|buf
argument_list|)
condition|)
block|{
return|return
literal|1
return|;
block|}
if|if
condition|(
name|ctx
operator|->
name|need_in_temp
operator|&&
operator|(
name|buf
operator|->
name|memory
operator|||
name|buf
operator|->
name|mmap
operator|)
condition|)
block|{
return|return
literal|1
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_output_chain_add_copy (ngx_pool_t * pool,ngx_chain_t ** chain,ngx_chain_t * in)
name|ngx_output_chain_add_copy
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_chain_t
modifier|*
modifier|*
name|chain
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
block|{
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|,
modifier|*
modifier|*
name|ll
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_SENDFILE_LIMIT
operator|)
name|ngx_buf_t
modifier|*
name|b
decl_stmt|,
modifier|*
name|buf
decl_stmt|;
endif|#
directive|endif
name|ll
operator|=
name|chain
expr_stmt|;
for|for
control|(
name|cl
operator|=
operator|*
name|chain
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
block|}
while|while
condition|(
name|in
condition|)
block|{
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
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
if|#
directive|if
operator|(
name|NGX_SENDFILE_LIMIT
operator|)
name|buf
operator|=
name|in
operator|->
name|buf
expr_stmt|;
if|if
condition|(
name|buf
operator|->
name|in_file
operator|&&
name|buf
operator|->
name|file_pos
operator|<
name|NGX_SENDFILE_LIMIT
operator|&&
name|buf
operator|->
name|file_last
operator|>
name|NGX_SENDFILE_LIMIT
condition|)
block|{
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
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
name|ngx_memcpy
argument_list|(
name|b
argument_list|,
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_buf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_buf_in_memory
argument_list|(
name|buf
argument_list|)
condition|)
block|{
name|buf
operator|->
name|pos
operator|+=
operator|(
name|ssize_t
operator|)
operator|(
name|NGX_SENDFILE_LIMIT
operator|-
name|buf
operator|->
name|file_pos
operator|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|buf
operator|->
name|pos
expr_stmt|;
block|}
name|buf
operator|->
name|file_pos
operator|=
name|NGX_SENDFILE_LIMIT
expr_stmt|;
name|b
operator|->
name|file_last
operator|=
name|NGX_SENDFILE_LIMIT
expr_stmt|;
name|cl
operator|->
name|buf
operator|=
name|b
expr_stmt|;
block|}
else|else
block|{
name|cl
operator|->
name|buf
operator|=
name|buf
expr_stmt|;
name|in
operator|=
name|in
operator|->
name|next
expr_stmt|;
block|}
else|#
directive|else
name|cl
operator|->
name|buf
operator|=
name|in
operator|->
name|buf
expr_stmt|;
name|in
operator|=
name|in
operator|->
name|next
expr_stmt|;
endif|#
directive|endif
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
block|}
operator|*
name|ll
operator|=
name|NULL
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_output_chain_copy_buf (ngx_buf_t * dst,ngx_buf_t * src,ngx_uint_t sendfile)
name|ngx_output_chain_copy_buf
parameter_list|(
name|ngx_buf_t
modifier|*
name|dst
parameter_list|,
name|ngx_buf_t
modifier|*
name|src
parameter_list|,
name|ngx_uint_t
name|sendfile
parameter_list|)
block|{
name|off_t
name|size
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|size
operator|=
name|ngx_buf_size
argument_list|(
name|src
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|>
name|dst
operator|->
name|end
operator|-
name|dst
operator|->
name|pos
condition|)
block|{
name|size
operator|=
name|dst
operator|->
name|end
operator|-
name|dst
operator|->
name|pos
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_SENDFILE_LIMIT
operator|)
if|if
condition|(
name|src
operator|->
name|in_file
operator|&&
name|src
operator|->
name|file_pos
operator|>=
name|NGX_SENDFILE_LIMIT
condition|)
block|{
name|sendfile
operator|=
literal|0
expr_stmt|;
block|}
endif|#
directive|endif
if|if
condition|(
name|ngx_buf_in_memory
argument_list|(
name|src
argument_list|)
condition|)
block|{
name|ngx_memcpy
argument_list|(
name|dst
operator|->
name|pos
argument_list|,
name|src
operator|->
name|pos
argument_list|,
operator|(
name|size_t
operator|)
name|size
argument_list|)
expr_stmt|;
name|src
operator|->
name|pos
operator|+=
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
name|dst
operator|->
name|last
operator|+=
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
if|if
condition|(
name|src
operator|->
name|in_file
condition|)
block|{
if|if
condition|(
name|sendfile
condition|)
block|{
name|dst
operator|->
name|in_file
operator|=
literal|1
expr_stmt|;
name|dst
operator|->
name|file
operator|=
name|src
operator|->
name|file
expr_stmt|;
name|dst
operator|->
name|file_pos
operator|=
name|src
operator|->
name|file_pos
expr_stmt|;
name|dst
operator|->
name|file_last
operator|=
name|src
operator|->
name|file_pos
operator|+
name|size
expr_stmt|;
block|}
else|else
block|{
name|dst
operator|->
name|in_file
operator|=
literal|0
expr_stmt|;
block|}
name|src
operator|->
name|file_pos
operator|+=
name|size
expr_stmt|;
block|}
else|else
block|{
name|dst
operator|->
name|in_file
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|src
operator|->
name|last_buf
operator|&&
name|src
operator|->
name|pos
operator|==
name|src
operator|->
name|last
condition|)
block|{
name|dst
operator|->
name|last_buf
operator|=
literal|1
expr_stmt|;
block|}
block|}
else|else
block|{
name|n
operator|=
name|ngx_read_file
argument_list|(
name|src
operator|->
name|file
argument_list|,
name|dst
operator|->
name|pos
argument_list|,
operator|(
name|size_t
operator|)
name|size
argument_list|,
name|src
operator|->
name|file_pos
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
operator|(
name|ngx_int_t
operator|)
name|n
return|;
block|}
if|#
directive|if
operator|(
name|NGX_FILE_AIO_READ
operator|)
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return
operator|(
name|ngx_int_t
operator|)
name|n
return|;
block|}
endif|#
directive|endif
if|if
condition|(
name|n
operator|!=
name|size
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|src
operator|->
name|file
operator|->
name|log
argument_list|,
literal|0
argument_list|,
name|ngx_read_file_n
literal|" reads only %z of %O from file"
argument_list|,
name|n
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
name|dst
operator|->
name|last
operator|+=
name|n
expr_stmt|;
if|if
condition|(
name|sendfile
condition|)
block|{
name|dst
operator|->
name|in_file
operator|=
literal|1
expr_stmt|;
name|dst
operator|->
name|file
operator|=
name|src
operator|->
name|file
expr_stmt|;
name|dst
operator|->
name|file_pos
operator|=
name|src
operator|->
name|file_pos
expr_stmt|;
name|dst
operator|->
name|file_last
operator|=
name|src
operator|->
name|file_pos
operator|+
name|n
expr_stmt|;
block|}
else|else
block|{
name|dst
operator|->
name|in_file
operator|=
literal|0
expr_stmt|;
block|}
name|src
operator|->
name|file_pos
operator|+=
name|n
expr_stmt|;
if|if
condition|(
name|src
operator|->
name|last_buf
operator|&&
name|src
operator|->
name|file_pos
operator|==
name|src
operator|->
name|file_last
condition|)
block|{
name|dst
operator|->
name|last_buf
operator|=
literal|1
expr_stmt|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_chain_writer (void * data,ngx_chain_t * in)
name|ngx_chain_writer
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
block|{
name|ngx_chain_writer_ctx_t
modifier|*
name|ctx
init|=
name|data
decl_stmt|;
name|off_t
name|size
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
for|for
control|(
name|size
operator|=
literal|0
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
if|#
directive|if
literal|1
if|if
condition|(
name|ngx_buf_size
argument_list|(
name|in
operator|->
name|buf
argument_list|)
operator|==
literal|0
operator|&&
operator|!
name|ngx_buf_special
argument_list|(
name|in
operator|->
name|buf
argument_list|)
condition|)
block|{
name|ngx_debug_point
argument_list|()
expr_stmt|;
block|}
endif|#
directive|endif
name|size
operator|+=
name|ngx_buf_size
argument_list|(
name|in
operator|->
name|buf
argument_list|)
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ctx
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"chain writer buf size: %uz"
argument_list|,
name|ngx_buf_size
argument_list|(
name|in
operator|->
name|buf
argument_list|)
argument_list|)
expr_stmt|;
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|ctx
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
name|in
operator|->
name|buf
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
name|last
operator|=
name|cl
expr_stmt|;
name|ctx
operator|->
name|last
operator|=
operator|&
name|cl
operator|->
name|next
expr_stmt|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ctx
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"chain writer in: %p"
argument_list|,
name|ctx
operator|->
name|out
argument_list|)
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
name|ngx_debug_point
argument_list|()
expr_stmt|;
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
block|}
if|if
condition|(
name|size
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|ctx
operator|->
name|out
operator|=
name|ngx_send_chain
argument_list|(
name|ctx
operator|->
name|connection
argument_list|,
name|ctx
operator|->
name|out
argument_list|,
name|ctx
operator|->
name|limit
argument_list|)
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ctx
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"chain writer out: %p"
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
name|out
operator|==
name|NGX_CHAIN_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
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
name|ctx
operator|->
name|last
operator|=
operator|&
name|ctx
operator|->
name|out
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

end_unit

