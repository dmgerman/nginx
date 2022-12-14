begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Ruslan Ermilov  * Copyright (C) Nginx, Inc.  */
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_ATOMIC_OPS
operator|)
end_if

begin_define
DECL|macro|NGX_RWLOCK_SPIN
define|#
directive|define
name|NGX_RWLOCK_SPIN
value|2048
end_define

begin_define
DECL|macro|NGX_RWLOCK_WLOCK
define|#
directive|define
name|NGX_RWLOCK_WLOCK
value|((ngx_atomic_uint_t) -1)
end_define

begin_function
name|void
DECL|function|ngx_rwlock_wlock (ngx_atomic_t * lock)
name|ngx_rwlock_wlock
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
operator|*
name|lock
operator|==
literal|0
operator|&&
name|ngx_atomic_cmp_set
argument_list|(
name|lock
argument_list|,
literal|0
argument_list|,
name|NGX_RWLOCK_WLOCK
argument_list|)
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|ngx_ncpu
operator|>
literal|1
condition|)
block|{
for|for
control|(
name|n
operator|=
literal|1
init|;
name|n
operator|<
name|NGX_RWLOCK_SPIN
condition|;
name|n
operator|<<=
literal|1
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
block|{
name|ngx_cpu_pause
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
operator|*
name|lock
operator|==
literal|0
operator|&&
name|ngx_atomic_cmp_set
argument_list|(
name|lock
argument_list|,
literal|0
argument_list|,
name|NGX_RWLOCK_WLOCK
argument_list|)
condition|)
block|{
return|return;
block|}
block|}
block|}
name|ngx_sched_yield
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|ngx_rwlock_rlock (ngx_atomic_t * lock)
name|ngx_rwlock_rlock
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_atomic_uint_t
name|readers
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|readers
operator|=
operator|*
name|lock
expr_stmt|;
if|if
condition|(
name|readers
operator|!=
name|NGX_RWLOCK_WLOCK
operator|&&
name|ngx_atomic_cmp_set
argument_list|(
name|lock
argument_list|,
name|readers
argument_list|,
name|readers
operator|+
literal|1
argument_list|)
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|ngx_ncpu
operator|>
literal|1
condition|)
block|{
for|for
control|(
name|n
operator|=
literal|1
init|;
name|n
operator|<
name|NGX_RWLOCK_SPIN
condition|;
name|n
operator|<<=
literal|1
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
block|{
name|ngx_cpu_pause
argument_list|()
expr_stmt|;
block|}
name|readers
operator|=
operator|*
name|lock
expr_stmt|;
if|if
condition|(
name|readers
operator|!=
name|NGX_RWLOCK_WLOCK
operator|&&
name|ngx_atomic_cmp_set
argument_list|(
name|lock
argument_list|,
name|readers
argument_list|,
name|readers
operator|+
literal|1
argument_list|)
condition|)
block|{
return|return;
block|}
block|}
block|}
name|ngx_sched_yield
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|ngx_rwlock_unlock (ngx_atomic_t * lock)
name|ngx_rwlock_unlock
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
block|{
if|if
condition|(
operator|*
name|lock
operator|==
name|NGX_RWLOCK_WLOCK
condition|)
block|{
operator|(
name|void
operator|)
name|ngx_atomic_cmp_set
argument_list|(
name|lock
argument_list|,
name|NGX_RWLOCK_WLOCK
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|(
name|void
operator|)
name|ngx_atomic_fetch_add
argument_list|(
name|lock
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|ngx_rwlock_downgrade (ngx_atomic_t * lock)
name|ngx_rwlock_downgrade
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
block|{
if|if
condition|(
operator|*
name|lock
operator|==
name|NGX_RWLOCK_WLOCK
condition|)
block|{
operator|*
name|lock
operator|=
literal|1
expr_stmt|;
block|}
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_UPSTREAM_ZONE
operator|||
name|NGX_STREAM_UPSTREAM_ZONE
operator|)
end_if

begin_error
error|#
directive|error
error|ngx_atomic_cmp_set() is not defined!
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

end_unit

