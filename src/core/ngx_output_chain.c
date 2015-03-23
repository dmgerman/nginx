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

begin_comment
comment|/*  * When DIRECTIO is enabled FreeBSD, Solaris, and MacOSX read directly  * to an application memory from a device if parameters are aligned  * to device sector boundary (512 bytes).  They fallback to usual read  * operation if the parameters are not aligned.  * Linux allows DIRECTIO only if the parameters are aligned to a filesystem  * sector boundary, otherwise it returns EINVAL.  The sector size is  * usually 512 bytes, however, on XFS it may be 4096 bytes.  */
end_comment

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
name|ngx_output_chain_as_is
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_AIO_SENDFILE
operator|)
end_if

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_output_chain_aio_setup
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_file_t
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

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
name|ngx_output_chain_align_file_buf
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|off_t
name|bsize
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_output_chain_get_buf
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|off_t
name|bsize
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_output_chain_copy_buf
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
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
name|off_t
name|bsize
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|,
name|last
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
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|||
name|NGX_THREADS
operator|)
operator|&&
operator|!
name|ctx
operator|->
name|aio
endif|#
directive|endif
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
name|ngx_output_chain_as_is
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
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|||
name|NGX_THREADS
operator|)
if|if
condition|(
name|ctx
operator|->
name|aio
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
endif|#
directive|endif
while|while
condition|(
name|ctx
operator|->
name|in
condition|)
block|{
comment|/*              * cycle while there are the ctx->in bufs              * and there are the free output bufs to copy in              */
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
name|ngx_output_chain_as_is
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
name|rc
operator|=
name|ngx_output_chain_align_file_buf
argument_list|(
name|ctx
argument_list|,
name|bsize
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
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
condition|)
block|{
if|if
condition|(
name|ctx
operator|->
name|free
condition|)
block|{
comment|/* get the free buf */
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
if|else if
condition|(
name|ngx_output_chain_get_buf
argument_list|(
name|ctx
argument_list|,
name|bsize
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
name|rc
operator|=
name|ngx_output_chain_copy_buf
argument_list|(
name|ctx
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
name|ctx
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
DECL|function|ngx_output_chain_as_is (ngx_output_chain_ctx_t * ctx,ngx_buf_t * buf)
name|ngx_output_chain_as_is
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
literal|1
return|;
block|}
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
if|if
condition|(
name|buf
operator|->
name|in_file
condition|)
block|{
name|buf
operator|->
name|file
operator|->
name|thread_handler
operator|=
name|ctx
operator|->
name|thread_handler
expr_stmt|;
name|buf
operator|->
name|file
operator|->
name|thread_ctx
operator|=
name|ctx
operator|->
name|filter_ctx
expr_stmt|;
block|}
endif|#
directive|endif
if|if
condition|(
name|buf
operator|->
name|in_file
operator|&&
name|buf
operator|->
name|file
operator|->
name|directio
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
literal|0
return|;
block|}
name|buf
operator|->
name|in_file
operator|=
literal|0
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_AIO_SENDFILE
operator|)
if|if
condition|(
name|ctx
operator|->
name|aio_preload
operator|&&
name|buf
operator|->
name|in_file
condition|)
block|{
operator|(
name|void
operator|)
name|ngx_output_chain_aio_setup
argument_list|(
name|ctx
argument_list|,
name|buf
operator|->
name|file
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
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
literal|0
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
literal|0
return|;
block|}
return|return
literal|1
return|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_AIO_SENDFILE
operator|)
end_if

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_output_chain_aio_setup (ngx_output_chain_ctx_t * ctx,ngx_file_t * file)
name|ngx_output_chain_aio_setup
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_file_t
modifier|*
name|file
parameter_list|)
block|{
name|ngx_event_aio_t
modifier|*
name|aio
decl_stmt|;
if|if
condition|(
name|file
operator|->
name|aio
operator|==
name|NULL
operator|&&
name|ngx_file_aio_init
argument_list|(
name|file
argument_list|,
name|ctx
operator|->
name|pool
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|aio
operator|=
name|file
operator|->
name|aio
expr_stmt|;
name|aio
operator|->
name|data
operator|=
name|ctx
operator|->
name|filter_ctx
expr_stmt|;
name|aio
operator|->
name|preload_handler
operator|=
name|ctx
operator|->
name|aio_preload
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

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
comment|/* split a file buf on two bufs by the sendfile limit */
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
name|cl
operator|->
name|next
operator|=
name|NULL
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
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_output_chain_align_file_buf (ngx_output_chain_ctx_t * ctx,off_t bsize)
name|ngx_output_chain_align_file_buf
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|off_t
name|bsize
parameter_list|)
block|{
name|size_t
name|size
decl_stmt|;
name|ngx_buf_t
modifier|*
name|in
decl_stmt|;
name|in
operator|=
name|ctx
operator|->
name|in
operator|->
name|buf
expr_stmt|;
if|if
condition|(
name|in
operator|->
name|file
operator|==
name|NULL
operator|||
operator|!
name|in
operator|->
name|file
operator|->
name|directio
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|ctx
operator|->
name|directio
operator|=
literal|1
expr_stmt|;
name|size
operator|=
operator|(
name|size_t
operator|)
operator|(
name|in
operator|->
name|file_pos
operator|-
operator|(
name|in
operator|->
name|file_pos
operator|&
operator|~
operator|(
name|ctx
operator|->
name|alignment
operator|-
literal|1
operator|)
operator|)
operator|)
expr_stmt|;
if|if
condition|(
name|size
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|bsize
operator|>=
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
return|return
name|NGX_DECLINED
return|;
block|}
name|size
operator|=
operator|(
name|size_t
operator|)
name|bsize
expr_stmt|;
block|}
else|else
block|{
name|size
operator|=
operator|(
name|size_t
operator|)
name|ctx
operator|->
name|alignment
operator|-
name|size
expr_stmt|;
if|if
condition|(
operator|(
name|off_t
operator|)
name|size
operator|>
name|bsize
condition|)
block|{
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
comment|/*      * we do not set ctx->buf->tag, because we do not want      * to reuse the buf via ctx->free list      */
if|#
directive|if
operator|(
name|NGX_HAVE_ALIGNED_DIRECTIO
operator|)
name|ctx
operator|->
name|unaligned
operator|=
literal|1
expr_stmt|;
endif|#
directive|endif
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_output_chain_get_buf (ngx_output_chain_ctx_t * ctx,off_t bsize)
name|ngx_output_chain_get_buf
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|off_t
name|bsize
parameter_list|)
block|{
name|size_t
name|size
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|,
modifier|*
name|in
decl_stmt|;
name|ngx_uint_t
name|recycled
decl_stmt|;
name|in
operator|=
name|ctx
operator|->
name|in
operator|->
name|buf
expr_stmt|;
name|size
operator|=
name|ctx
operator|->
name|bufs
operator|.
name|size
expr_stmt|;
name|recycled
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|in
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
name|size
condition|)
block|{
comment|/*              * allocate a small temp buf for a small last buf              * or its small last part              */
name|size
operator|=
operator|(
name|size_t
operator|)
name|bsize
expr_stmt|;
name|recycled
operator|=
literal|0
expr_stmt|;
block|}
if|else if
condition|(
operator|!
name|ctx
operator|->
name|directio
operator|&&
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
name|size
operator|+
name|size
operator|/
literal|4
operator|)
operator|)
condition|)
block|{
comment|/*              * allocate a temp buf that equals to a last buf,              * if there is no directio, the last buf size is lesser              * than 1.25 of bufs.size and the temp buf is single              */
name|size
operator|=
operator|(
name|size_t
operator|)
name|bsize
expr_stmt|;
name|recycled
operator|=
literal|0
expr_stmt|;
block|}
block|}
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|ctx
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
if|if
condition|(
name|ctx
operator|->
name|directio
condition|)
block|{
comment|/*          * allocate block aligned to a disk sector size to enable          * userland buffer direct usage conjunctly with directio          */
name|b
operator|->
name|start
operator|=
name|ngx_pmemalign
argument_list|(
name|ctx
operator|->
name|pool
argument_list|,
name|size
argument_list|,
operator|(
name|size_t
operator|)
name|ctx
operator|->
name|alignment
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
operator|->
name|start
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
name|b
operator|->
name|start
operator|=
name|ngx_palloc
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
name|b
operator|->
name|start
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
name|b
operator|->
name|pos
operator|=
name|b
operator|->
name|start
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|b
operator|->
name|start
expr_stmt|;
name|b
operator|->
name|end
operator|=
name|b
operator|->
name|last
operator|+
name|size
expr_stmt|;
name|b
operator|->
name|temporary
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|tag
operator|=
name|ctx
operator|->
name|tag
expr_stmt|;
name|b
operator|->
name|recycled
operator|=
name|recycled
expr_stmt|;
name|ctx
operator|->
name|buf
operator|=
name|b
expr_stmt|;
name|ctx
operator|->
name|allocated
operator|++
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_output_chain_copy_buf (ngx_output_chain_ctx_t * ctx)
name|ngx_output_chain_copy_buf
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|off_t
name|size
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|ngx_buf_t
modifier|*
name|src
decl_stmt|,
modifier|*
name|dst
decl_stmt|;
name|ngx_uint_t
name|sendfile
decl_stmt|;
name|src
operator|=
name|ctx
operator|->
name|in
operator|->
name|buf
expr_stmt|;
name|dst
operator|=
name|ctx
operator|->
name|buf
expr_stmt|;
name|size
operator|=
name|ngx_buf_size
argument_list|(
name|src
argument_list|)
expr_stmt|;
name|size
operator|=
name|ngx_min
argument_list|(
name|size
argument_list|,
name|dst
operator|->
name|end
operator|-
name|dst
operator|->
name|pos
argument_list|)
expr_stmt|;
name|sendfile
operator|=
name|ctx
operator|->
name|sendfile
operator|&
operator|!
name|ctx
operator|->
name|directio
expr_stmt|;
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
name|pos
operator|==
name|src
operator|->
name|last
condition|)
block|{
name|dst
operator|->
name|flush
operator|=
name|src
operator|->
name|flush
expr_stmt|;
name|dst
operator|->
name|last_buf
operator|=
name|src
operator|->
name|last_buf
expr_stmt|;
name|dst
operator|->
name|last_in_chain
operator|=
name|src
operator|->
name|last_in_chain
expr_stmt|;
block|}
block|}
else|else
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_ALIGNED_DIRECTIO
operator|)
if|if
condition|(
name|ctx
operator|->
name|unaligned
condition|)
block|{
if|if
condition|(
name|ngx_directio_off
argument_list|(
name|src
operator|->
name|file
operator|->
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
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
name|ngx_errno
argument_list|,
name|ngx_directio_off_n
literal|" \"%s\" failed"
argument_list|,
name|src
operator|->
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|)
if|if
condition|(
name|ctx
operator|->
name|aio_handler
condition|)
block|{
name|n
operator|=
name|ngx_file_aio_read
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
argument_list|,
name|ctx
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
name|ctx
operator|->
name|aio_handler
argument_list|(
name|ctx
argument_list|,
name|src
operator|->
name|file
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
block|}
if|else
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
if|if
condition|(
name|src
operator|->
name|file
operator|->
name|thread_handler
condition|)
block|{
name|n
operator|=
name|ngx_thread_read
argument_list|(
operator|&
name|ctx
operator|->
name|thread_task
argument_list|,
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
argument_list|,
name|ctx
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
name|ctx
operator|->
name|aio
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
block|}
else|else
endif|#
directive|endif
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
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_ALIGNED_DIRECTIO
operator|)
if|if
condition|(
name|ctx
operator|->
name|unaligned
condition|)
block|{
name|ngx_err_t
name|err
decl_stmt|;
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|ngx_directio_on
argument_list|(
name|src
operator|->
name|file
operator|->
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
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
name|ngx_errno
argument_list|,
name|ngx_directio_on_n
literal|" \"%s\" failed"
argument_list|,
name|src
operator|->
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
name|ngx_set_errno
argument_list|(
name|err
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|unaligned
operator|=
literal|0
expr_stmt|;
block|}
endif|#
directive|endif
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
name|ctx
operator|->
name|pool
operator|->
name|log
argument_list|,
literal|0
argument_list|,
name|ngx_read_file_n
literal|" read only %z of %O from \"%s\""
argument_list|,
name|n
argument_list|,
name|size
argument_list|,
name|src
operator|->
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
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
name|file_pos
operator|==
name|src
operator|->
name|file_last
condition|)
block|{
name|dst
operator|->
name|flush
operator|=
name|src
operator|->
name|flush
expr_stmt|;
name|dst
operator|->
name|last_buf
operator|=
name|src
operator|->
name|last_buf
expr_stmt|;
name|dst
operator|->
name|last_in_chain
operator|=
name|src
operator|->
name|last_in_chain
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
decl_stmt|,
modifier|*
name|ln
decl_stmt|,
modifier|*
name|chain
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|c
operator|=
name|ctx
operator|->
name|connection
expr_stmt|;
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
literal|"zero size buf in chain writer "
literal|"t:%d r:%d f:%d %p %p-%p %p %O-%O"
argument_list|,
name|in
operator|->
name|buf
operator|->
name|temporary
argument_list|,
name|in
operator|->
name|buf
operator|->
name|recycled
argument_list|,
name|in
operator|->
name|buf
operator|->
name|in_file
argument_list|,
name|in
operator|->
name|buf
operator|->
name|start
argument_list|,
name|in
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|in
operator|->
name|buf
operator|->
name|last
argument_list|,
name|in
operator|->
name|buf
operator|->
name|file
argument_list|,
name|in
operator|->
name|buf
operator|->
name|file_pos
argument_list|,
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
continue|continue;
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
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"chain writer buf fl:%d s:%uO"
argument_list|,
name|in
operator|->
name|buf
operator|->
name|flush
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
name|c
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
literal|"zero size buf in chain writer "
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
continue|continue;
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
operator|&&
operator|!
name|c
operator|->
name|buffered
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|chain
operator|=
name|c
operator|->
name|send_chain
argument_list|(
name|c
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
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"chain writer out: %p"
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
return|return
name|NGX_ERROR
return|;
block|}
for|for
control|(
name|cl
operator|=
name|ctx
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
name|ctx
operator|->
name|pool
argument_list|,
name|ln
argument_list|)
expr_stmt|;
block|}
name|ctx
operator|->
name|out
operator|=
name|chain
expr_stmt|;
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
if|if
condition|(
operator|!
name|c
operator|->
name|buffered
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
block|}
return|return
name|NGX_AGAIN
return|;
block|}
end_function

end_unit

