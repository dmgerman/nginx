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

begin_comment
comment|/*  * TODO: the P4 optimized assembler version with the "pause" operation  */
end_comment

begin_function
DECL|function|ngx_spinlock (ngx_atomic_t * lock,ngx_uint_t spin)
name|void
name|ngx_spinlock
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
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
name|tries
decl_stmt|;
name|tries
operator|=
literal|0
expr_stmt|;
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
condition|)
block|{
if|if
condition|(
name|ngx_ncpu
operator|>
literal|1
operator|&&
name|tries
operator|++
operator|<
name|spin
condition|)
block|{
continue|continue;
block|}
name|ngx_sched_yield
argument_list|()
expr_stmt|;
name|tries
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|ngx_atomic_cmp_set
argument_list|(
name|lock
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|)
condition|)
block|{
return|return;
block|}
block|}
block|}
else|#
directive|else
if|#
directive|if
operator|(
name|NGX_THREADS
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

