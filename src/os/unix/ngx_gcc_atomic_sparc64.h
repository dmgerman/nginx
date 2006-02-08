begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_comment
comment|/*  * "casa   [r1] 0x80, r2, r0"  and  * "casxa  [r1] 0x80, r2, r0"  do the following:  *  *     if ([r1] == r2) {  *         swap(r0, [r1]);  *     } else {  *         r0 = [r1];  *     }  *  * so "r0 == r2" means that the operation was successfull.  *  *  * The "r" means the general register.  * The "+r" means the general register used for both input and output.  */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_PTR_SIZE
operator|==
literal|4
operator|)
end_if

begin_define
DECL|macro|NGX_CASA
define|#
directive|define
name|NGX_CASA
value|"casa"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_CASA
define|#
directive|define
name|NGX_CASA
value|"casxa"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_cmp_set (ngx_atomic_t * lock,ngx_atomic_uint_t old,ngx_atomic_uint_t set)
name|ngx_atomic_cmp_set
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|,
name|ngx_atomic_uint_t
name|old
parameter_list|,
name|ngx_atomic_uint_t
name|set
parameter_list|)
block|{
asm|__asm__
specifier|volatile
asm|(      NGX_CASA " [%1] 0x80, %2, %0"      : "+r" (set) : "r" (lock), "r" (old) : "memory");
return|return
operator|(
name|set
operator|==
name|old
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_int_t
DECL|function|ngx_atomic_fetch_add (ngx_atomic_t * value,ngx_atomic_int_t add)
name|ngx_atomic_fetch_add
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|,
name|ngx_atomic_int_t
name|add
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|old
decl_stmt|,
name|res
decl_stmt|;
name|old
operator|=
operator|*
name|value
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|res
operator|=
name|old
operator|+
name|add
expr_stmt|;
asm|__asm__
specifier|volatile
asm|(          NGX_CASA " [%1] 0x80, %2, %0"          : "+r" (res) : "r" (value), "r" (old) : "memory");
if|if
condition|(
name|res
operator|==
name|old
condition|)
block|{
return|return
name|res
return|;
block|}
name|old
operator|=
name|res
expr_stmt|;
block|}
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_SMP
operator|)
end_if

begin_define
DECL|macro|ngx_memory_barrier ()
define|#
directive|define
name|ngx_memory_barrier
parameter_list|()
define|\
value|__asm__ volatile (                                                \             "membar #LoadLoad | #LoadStore | #StoreStore | #StoreLoad"        \             ::: "memory")
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_memory_barrier ()
define|#
directive|define
name|ngx_memory_barrier
parameter_list|()
value|__asm__ volatile ("" ::: "memory")
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_cpu_pause ()
define|#
directive|define
name|ngx_cpu_pause
parameter_list|()
end_define

end_unit

