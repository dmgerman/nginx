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

begin_function
DECL|function|ngx_alloc (size_t size,ngx_log_t * log)
name|void
modifier|*
name|ngx_alloc
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|void
modifier|*
name|p
decl_stmt|;
name|p
operator|=
name|malloc
argument_list|(
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
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"malloc() %d bytes failed"
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_DEBUG_ALLOC
operator|)
name|ngx_log_debug
argument_list|(
argument|log
argument_list|,
literal|"malloc: %08x:%d"
argument|_ p _ size
argument_list|)
empty_stmt|;
endif|#
directive|endif
return|return
name|p
return|;
block|}
end_function

begin_function
DECL|function|ngx_calloc (size_t size,ngx_log_t * log)
name|void
modifier|*
name|ngx_calloc
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|void
modifier|*
name|p
decl_stmt|;
name|p
operator|=
name|ngx_alloc
argument_list|(
name|size
argument_list|,
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
block|{
name|ngx_memzero
argument_list|(
name|p
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
return|return
name|p
return|;
block|}
end_function

begin_function
DECL|function|ngx_create_pool (size_t size,ngx_log_t * log)
name|ngx_pool_t
modifier|*
name|ngx_create_pool
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_pool_t
modifier|*
name|p
decl_stmt|;
name|ngx_test_null
argument_list|(
name|p
argument_list|,
name|ngx_alloc
argument_list|(
name|size
argument_list|,
name|log
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|p
operator|->
name|last
operator|=
operator|(
name|char
operator|*
operator|)
name|p
operator|+
sizeof|sizeof
argument_list|(
name|ngx_pool_t
argument_list|)
expr_stmt|;
name|p
operator|->
name|end
operator|=
operator|(
name|char
operator|*
operator|)
name|p
operator|+
name|size
expr_stmt|;
name|p
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
name|p
operator|->
name|large
operator|=
name|NULL
expr_stmt|;
name|p
operator|->
name|log
operator|=
name|log
expr_stmt|;
return|return
name|p
return|;
block|}
end_function

begin_function
DECL|function|ngx_destroy_pool (ngx_pool_t * pool)
name|void
name|ngx_destroy_pool
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_pool_t
modifier|*
name|p
decl_stmt|,
modifier|*
name|n
decl_stmt|;
name|ngx_pool_large_t
modifier|*
name|l
decl_stmt|;
for|for
control|(
name|l
operator|=
name|pool
operator|->
name|large
init|;
name|l
condition|;
name|l
operator|=
name|l
operator|->
name|next
control|)
block|{
if|#
directive|if
operator|(
name|NGX_DEBUG_ALLOC
operator|)
name|ngx_log_debug
argument_list|(
argument|pool->log
argument_list|,
literal|"free: %08x"
argument|_ l->alloc
argument_list|)
empty_stmt|;
endif|#
directive|endif
name|free
argument_list|(
name|l
operator|->
name|alloc
argument_list|)
expr_stmt|;
block|}
comment|/*      * we could allocate pool->log from this pool      * so we can not use this log while free()ing the pool      */
if|#
directive|if
operator|(
name|NGX_DEBUG_ALLOC
operator|)
for|for
control|(
name|p
operator|=
name|pool
operator|,
name|n
operator|=
name|pool
operator|->
name|next
init|;
comment|/* void */
condition|;
name|p
operator|=
name|n
operator|,
name|n
operator|=
name|n
operator|->
name|next
control|)
block|{
name|ngx_log_debug
argument_list|(
argument|pool->log
argument_list|,
literal|"free: %08x"
argument|_ p
argument_list|)
empty_stmt|;
if|if
condition|(
name|n
operator|==
name|NULL
condition|)
block|{
break|break;
block|}
block|}
endif|#
directive|endif
for|for
control|(
name|p
operator|=
name|pool
operator|,
name|n
operator|=
name|pool
operator|->
name|next
init|;
comment|/* void */
condition|;
name|p
operator|=
name|n
operator|,
name|n
operator|=
name|n
operator|->
name|next
control|)
block|{
name|free
argument_list|(
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NULL
condition|)
block|{
break|break;
block|}
block|}
name|pool
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_palloc (ngx_pool_t * pool,size_t size)
name|void
modifier|*
name|ngx_palloc
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|char
modifier|*
name|m
decl_stmt|;
name|ngx_pool_t
modifier|*
name|p
decl_stmt|,
modifier|*
name|n
decl_stmt|;
name|ngx_pool_large_t
modifier|*
name|large
decl_stmt|,
modifier|*
name|last
decl_stmt|;
if|if
condition|(
name|size
operator|<=
name|NGX_MAX_ALLOC_FROM_POOL
condition|)
block|{
for|for
control|(
name|p
operator|=
name|pool
operator|,
name|n
operator|=
name|pool
operator|->
name|next
init|;
comment|/* void */
condition|;
name|p
operator|=
name|n
operator|,
name|n
operator|=
name|n
operator|->
name|next
control|)
block|{
name|m
operator|=
name|ngx_align
argument_list|(
name|p
operator|->
name|last
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|size_t
operator|)
operator|(
name|p
operator|->
name|end
operator|-
name|m
operator|)
operator|>=
name|size
condition|)
block|{
name|p
operator|->
name|last
operator|=
name|m
operator|+
name|size
expr_stmt|;
return|return
name|m
return|;
block|}
if|if
condition|(
name|n
operator|==
name|NULL
condition|)
block|{
break|break;
block|}
block|}
comment|/* alloc new pool block */
name|ngx_test_null
argument_list|(
name|n
argument_list|,
name|ngx_create_pool
argument_list|(
name|p
operator|->
name|end
operator|-
operator|(
name|char
operator|*
operator|)
name|p
argument_list|,
name|p
operator|->
name|log
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|p
operator|->
name|next
operator|=
name|n
expr_stmt|;
name|m
operator|=
name|n
operator|->
name|last
expr_stmt|;
name|n
operator|->
name|last
operator|+=
name|size
expr_stmt|;
return|return
name|m
return|;
comment|/* alloc large block */
block|}
else|else
block|{
name|large
operator|=
name|NULL
expr_stmt|;
name|last
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|pool
operator|->
name|large
condition|)
block|{
for|for
control|(
name|last
operator|=
name|pool
operator|->
name|large
init|;
comment|/* void */
condition|;
name|last
operator|=
name|last
operator|->
name|next
control|)
block|{
if|if
condition|(
name|last
operator|->
name|alloc
operator|==
name|NULL
condition|)
block|{
name|large
operator|=
name|last
expr_stmt|;
name|last
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|last
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
break|break;
block|}
block|}
block|}
if|if
condition|(
name|large
operator|==
name|NULL
condition|)
block|{
name|ngx_test_null
argument_list|(
name|large
argument_list|,
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_pool_large_t
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|large
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
block|}
name|ngx_test_null
argument_list|(
name|p
argument_list|,
name|ngx_alloc
argument_list|(
name|size
argument_list|,
name|pool
operator|->
name|log
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pool
operator|->
name|large
operator|==
name|NULL
condition|)
block|{
name|pool
operator|->
name|large
operator|=
name|large
expr_stmt|;
block|}
if|else if
condition|(
name|last
condition|)
block|{
name|last
operator|->
name|next
operator|=
name|large
expr_stmt|;
block|}
name|large
operator|->
name|alloc
operator|=
name|p
expr_stmt|;
return|return
name|p
return|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_pcalloc (ngx_pool_t * pool,size_t size)
name|void
modifier|*
name|ngx_pcalloc
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|void
modifier|*
name|p
decl_stmt|;
name|p
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
name|p
condition|)
block|{
name|ngx_memzero
argument_list|(
name|p
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
return|return
name|p
return|;
block|}
end_function

end_unit

