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

begin_function
name|ngx_buf_t
modifier|*
DECL|function|ngx_create_temp_buf (ngx_pool_t * pool,size_t size)
name|ngx_create_temp_buf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
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
name|NULL
return|;
block|}
name|b
operator|->
name|start
operator|=
name|ngx_palloc
argument_list|(
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
name|NULL
return|;
block|}
comment|/*      * set by ngx_calloc_buf():      *      *     b->file_pos = 0;      *     b->file_last = 0;      *     b->file = NULL;      *     b->shadow = NULL;      *     b->tag = 0;      *     and flags      */
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
return|return
name|b
return|;
block|}
end_function

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_alloc_chain_link (ngx_pool_t * pool)
name|ngx_alloc_chain_link
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|cl
operator|=
name|pool
operator|->
name|chain
expr_stmt|;
if|if
condition|(
name|cl
condition|)
block|{
name|pool
operator|->
name|chain
operator|=
name|cl
operator|->
name|next
expr_stmt|;
return|return
name|cl
return|;
block|}
name|cl
operator|=
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_chain_t
argument_list|)
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
name|NULL
return|;
block|}
return|return
name|cl
return|;
block|}
end_function

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_create_chain_of_bufs (ngx_pool_t * pool,ngx_bufs_t * bufs)
name|ngx_create_chain_of_bufs
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_bufs_t
modifier|*
name|bufs
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
name|ngx_int_t
name|i
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
name|ngx_chain_t
modifier|*
name|chain
decl_stmt|,
modifier|*
name|cl
decl_stmt|,
modifier|*
modifier|*
name|ll
decl_stmt|;
name|p
operator|=
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
name|bufs
operator|->
name|num
operator|*
name|bufs
operator|->
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|ll
operator|=
operator|&
name|chain
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|bufs
operator|->
name|num
condition|;
name|i
operator|++
control|)
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
name|NULL
return|;
block|}
comment|/*          * set by ngx_calloc_buf():          *          *     b->file_pos = 0;          *     b->file_last = 0;          *     b->file = NULL;          *     b->shadow = NULL;          *     b->tag = 0;          *     and flags          *          */
name|b
operator|->
name|pos
operator|=
name|p
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|p
expr_stmt|;
name|b
operator|->
name|temporary
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|start
operator|=
name|p
expr_stmt|;
name|p
operator|+=
name|bufs
operator|->
name|size
expr_stmt|;
name|b
operator|->
name|end
operator|=
name|p
expr_stmt|;
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
name|NULL
return|;
block|}
name|cl
operator|->
name|buf
operator|=
name|b
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
operator|*
name|ll
operator|=
name|NULL
expr_stmt|;
return|return
name|chain
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_chain_add_copy (ngx_pool_t * pool,ngx_chain_t ** chain,ngx_chain_t * in)
name|ngx_chain_add_copy
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
name|cl
operator|->
name|buf
operator|=
name|in
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
name|in
operator|=
name|in
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
name|ngx_chain_t
modifier|*
DECL|function|ngx_chain_get_free_buf (ngx_pool_t * p,ngx_chain_t ** free)
name|ngx_chain_get_free_buf
parameter_list|(
name|ngx_pool_t
modifier|*
name|p
parameter_list|,
name|ngx_chain_t
modifier|*
modifier|*
name|free
parameter_list|)
block|{
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
if|if
condition|(
operator|*
name|free
condition|)
block|{
name|cl
operator|=
operator|*
name|free
expr_stmt|;
operator|*
name|free
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
return|return
name|cl
return|;
block|}
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|p
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
name|NULL
return|;
block|}
name|cl
operator|->
name|buf
operator|=
name|ngx_calloc_buf
argument_list|(
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|->
name|buf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|cl
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
return|return
name|cl
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_chain_update_chains (ngx_chain_t ** free,ngx_chain_t ** busy,ngx_chain_t ** out,ngx_buf_tag_t tag)
name|ngx_chain_update_chains
parameter_list|(
name|ngx_chain_t
modifier|*
modifier|*
name|free
parameter_list|,
name|ngx_chain_t
modifier|*
modifier|*
name|busy
parameter_list|,
name|ngx_chain_t
modifier|*
modifier|*
name|out
parameter_list|,
name|ngx_buf_tag_t
name|tag
parameter_list|)
block|{
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
if|if
condition|(
operator|*
name|busy
operator|==
name|NULL
condition|)
block|{
operator|*
name|busy
operator|=
operator|*
name|out
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|cl
operator|=
operator|*
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
operator|*
name|out
expr_stmt|;
block|}
operator|*
name|out
operator|=
name|NULL
expr_stmt|;
while|while
condition|(
operator|*
name|busy
condition|)
block|{
if|if
condition|(
name|ngx_buf_size
argument_list|(
operator|(
operator|*
name|busy
operator|)
operator|->
name|buf
argument_list|)
operator|!=
literal|0
condition|)
block|{
break|break;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_WRITE_ZEROCOPY
operator|)
if|if
condition|(
operator|(
operator|*
name|busy
operator|)
operator|->
name|buf
operator|->
name|zerocopy_busy
condition|)
block|{
break|break;
block|}
endif|#
directive|endif
if|if
condition|(
operator|(
operator|*
name|busy
operator|)
operator|->
name|buf
operator|->
name|tag
operator|!=
name|tag
condition|)
block|{
operator|*
name|busy
operator|=
operator|(
operator|*
name|busy
operator|)
operator|->
name|next
expr_stmt|;
continue|continue;
block|}
operator|(
operator|*
name|busy
operator|)
operator|->
name|buf
operator|->
name|pos
operator|=
operator|(
operator|*
name|busy
operator|)
operator|->
name|buf
operator|->
name|start
expr_stmt|;
operator|(
operator|*
name|busy
operator|)
operator|->
name|buf
operator|->
name|last
operator|=
operator|(
operator|*
name|busy
operator|)
operator|->
name|buf
operator|->
name|start
expr_stmt|;
name|cl
operator|=
operator|*
name|busy
expr_stmt|;
operator|*
name|busy
operator|=
name|cl
operator|->
name|next
expr_stmt|;
name|cl
operator|->
name|next
operator|=
operator|*
name|free
expr_stmt|;
operator|*
name|free
operator|=
name|cl
expr_stmt|;
block|}
block|}
end_function

end_unit

