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
name|ngx_pool_t
modifier|*
DECL|function|ngx_create_pool (size_t size,ngx_log_t * log)
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
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|p
operator|->
name|last
operator|=
operator|(
name|u_char
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
name|u_char
operator|*
operator|)
name|p
operator|+
name|size
expr_stmt|;
name|p
operator|->
name|current
operator|=
name|p
expr_stmt|;
name|p
operator|->
name|chain
operator|=
name|NULL
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
name|cleanup
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
name|void
DECL|function|ngx_destroy_pool (ngx_pool_t * pool)
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
name|ngx_pool_cleanup_t
modifier|*
name|c
decl_stmt|;
for|for
control|(
name|c
operator|=
name|pool
operator|->
name|cleanup
init|;
name|c
condition|;
name|c
operator|=
name|c
operator|->
name|next
control|)
block|{
if|if
condition|(
name|c
operator|->
name|handler
condition|)
block|{
name|c
operator|->
name|handler
argument_list|(
name|c
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
block|}
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
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_ALLOC
argument_list|,
name|pool
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"free: %p"
argument_list|,
name|l
operator|->
name|alloc
argument_list|)
expr_stmt|;
if|if
condition|(
name|l
operator|->
name|alloc
condition|)
block|{
name|ngx_free
argument_list|(
name|l
operator|->
name|alloc
argument_list|)
expr_stmt|;
block|}
block|}
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
comment|/*      * we could allocate the pool->log from this pool      * so we can not use this log while the free()ing the pool      */
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
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_ALLOC
argument_list|,
name|pool
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"free: %p, unused: %uz"
argument_list|,
name|p
argument_list|,
name|p
operator|->
name|end
operator|-
name|p
operator|->
name|last
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
name|ngx_free
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
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|ngx_palloc (ngx_pool_t * pool,size_t size)
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
name|u_char
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
decl_stmt|;
if|if
condition|(
name|size
operator|<=
operator|(
name|size_t
operator|)
name|NGX_MAX_ALLOC_FROM_POOL
operator|&&
name|size
operator|<=
operator|(
name|size_t
operator|)
operator|(
name|pool
operator|->
name|end
operator|-
operator|(
name|u_char
operator|*
operator|)
name|pool
operator|)
operator|-
operator|(
name|size_t
operator|)
name|ngx_align_ptr
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_pool_t
argument_list|)
argument_list|,
name|NGX_ALIGNMENT
argument_list|)
condition|)
block|{
for|for
control|(
name|p
operator|=
name|pool
operator|->
name|current
init|;
comment|/* void */
condition|;
name|p
operator|=
name|p
operator|->
name|next
control|)
block|{
if|if
condition|(
name|size
operator|<
sizeof|sizeof
argument_list|(
name|int
argument_list|)
operator|||
operator|(
name|size
operator|&
literal|1
operator|)
condition|)
block|{
name|m
operator|=
name|p
operator|->
name|last
expr_stmt|;
block|}
else|else
block|{
name|m
operator|=
name|ngx_align_ptr
argument_list|(
name|p
operator|->
name|last
argument_list|,
name|NGX_ALIGNMENT
argument_list|)
expr_stmt|;
block|}
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
operator|<
name|NGX_ALIGNMENT
condition|)
block|{
name|pool
operator|->
name|current
operator|=
name|p
operator|->
name|next
expr_stmt|;
block|}
if|if
condition|(
name|p
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
break|break;
block|}
block|}
comment|/* allocate a new pool block */
name|n
operator|=
name|ngx_create_pool
argument_list|(
operator|(
name|size_t
operator|)
operator|(
name|p
operator|->
name|end
operator|-
operator|(
name|u_char
operator|*
operator|)
name|p
operator|)
argument_list|,
name|p
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|pool
operator|->
name|current
operator|==
name|NULL
condition|)
block|{
name|pool
operator|->
name|current
operator|=
name|n
expr_stmt|;
block|}
name|p
operator|->
name|next
operator|=
name|n
expr_stmt|;
name|m
operator|=
name|ngx_align_ptr
argument_list|(
name|n
operator|->
name|last
argument_list|,
name|NGX_ALIGNMENT
argument_list|)
expr_stmt|;
name|n
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
if|#
directive|if
literal|0
block_content|p = ngx_memalign(ngx_pagesize, size, pool->log);     if (p == NULL) {         return NULL;     }
else|#
directive|else
name|p
operator|=
name|ngx_alloc
argument_list|(
name|size
argument_list|,
name|pool
operator|->
name|log
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
endif|#
directive|endif
name|large
operator|=
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_pool_large_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|large
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|large
operator|->
name|alloc
operator|=
name|p
expr_stmt|;
name|large
operator|->
name|next
operator|=
name|pool
operator|->
name|large
expr_stmt|;
name|pool
operator|->
name|large
operator|=
name|large
expr_stmt|;
return|return
name|p
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_pfree (ngx_pool_t * pool,void * p)
name|ngx_pfree
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|void
modifier|*
name|p
parameter_list|)
block|{
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
if|if
condition|(
name|p
operator|==
name|l
operator|->
name|alloc
condition|)
block|{
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_ALLOC
argument_list|,
name|pool
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"free: %p"
argument_list|,
name|l
operator|->
name|alloc
argument_list|)
expr_stmt|;
name|ngx_free
argument_list|(
name|l
operator|->
name|alloc
argument_list|)
expr_stmt|;
name|l
operator|->
name|alloc
operator|=
name|NULL
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
block|}
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|ngx_pcalloc (ngx_pool_t * pool,size_t size)
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

begin_function
name|void
modifier|*
DECL|function|ngx_shalloc (size_t size)
name|ngx_shalloc
parameter_list|(
name|size_t
name|size
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
if|if
condition|(
name|size
operator|<
sizeof|sizeof
argument_list|(
name|int
argument_list|)
operator|||
operator|(
name|size
operator|&
literal|1
operator|)
condition|)
block|{
name|p
operator|=
name|ngx_cycle
operator|->
name|shm_last
expr_stmt|;
block|}
else|else
block|{
name|p
operator|=
name|ngx_align_ptr
argument_list|(
name|ngx_cycle
operator|->
name|shm_last
argument_list|,
name|NGX_ALIGNMENT
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|size_t
operator|)
operator|(
name|ngx_cycle
operator|->
name|shm_end
operator|-
name|p
operator|)
operator|>=
name|size
condition|)
block|{
name|ngx_cycle
operator|->
name|shm_last
operator|=
name|p
operator|+
name|size
expr_stmt|;
return|return
name|p
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"allocation of %uz bytes in shared memory failed, "
literal|"only %uz are available"
argument_list|,
name|size
argument_list|,
name|ngx_cycle
operator|->
name|shm_end
operator|-
name|ngx_cycle
operator|->
name|shm_last
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|ngx_shcalloc (size_t size)
name|ngx_shcalloc
parameter_list|(
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
name|ngx_shalloc
argument_list|(
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

begin_function
name|ngx_pool_cleanup_t
modifier|*
DECL|function|ngx_pool_cleanup_add (ngx_pool_t * p,size_t size)
name|ngx_pool_cleanup_add
parameter_list|(
name|ngx_pool_t
modifier|*
name|p
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|ngx_pool_cleanup_t
modifier|*
name|c
decl_stmt|;
name|c
operator|=
name|ngx_palloc
argument_list|(
name|p
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_pool_cleanup_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|size
condition|)
block|{
name|c
operator|->
name|data
operator|=
name|ngx_palloc
argument_list|(
name|p
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
block|}
else|else
block|{
name|c
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
block|}
name|c
operator|->
name|handler
operator|=
name|NULL
expr_stmt|;
name|c
operator|->
name|next
operator|=
name|p
operator|->
name|cleanup
expr_stmt|;
name|p
operator|->
name|cleanup
operator|=
name|c
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_ALLOC
argument_list|,
name|p
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"add cleanup: %p"
argument_list|,
name|c
argument_list|)
expr_stmt|;
return|return
name|c
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_pool_cleanup_file (void * data)
name|ngx_pool_cleanup_file
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
block|{
name|ngx_pool_cleanup_file_t
modifier|*
name|c
init|=
name|data
decl_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_ALLOC
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"run cleanup: %p, fd:%d"
argument_list|,
name|c
argument_list|,
name|c
operator|->
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_close_file
argument_list|(
name|c
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
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|c
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static void * ngx_get_cached_block(size_t size) {     void                     *p;     ngx_cached_block_slot_t  *slot;      if (ngx_cycle->cache == NULL) {         return NULL;     }      slot =&ngx_cycle->cache[(size + ngx_pagesize - 1) / ngx_pagesize];      slot->tries++;      if (slot->number) {         p = slot->block;         slot->block = slot->block->next;         slot->number--;         return p;     }      return NULL; }
endif|#
directive|endif
end_endif

end_unit

