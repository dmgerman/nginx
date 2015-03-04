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

begin_function
name|void
DECL|function|ngx_spinlock (ngx_atomic_t * lock,ngx_atomic_int_t value,ngx_uint_t spin)
name|ngx_spinlock
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|,
name|ngx_atomic_int_t
name|value
parameter_list|,
name|ngx_uint_t
name|spin
parameter_list|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_ATOMIC_OPS
operator|)
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
name|value
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
name|spin
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
name|value
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
else|#
directive|else
if|#
directive|if
operator|(
name|NGX_OLD_THREADS
operator|)
error|#
directive|error
error|ngx_spinlock() or ngx_atomic_cmp_set() are not defined !
endif|#
directive|endif
endif|#
directive|endif
block|}
end_function

end_unit

