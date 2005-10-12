begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_SMP
operator|)
end_if

begin_define
DECL|macro|NGX_SMP_LOCK
define|#
directive|define
name|NGX_SMP_LOCK
value|"lock;"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_SMP_LOCK
define|#
directive|define
name|NGX_SMP_LOCK
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * "cmpxchgl  r, [m]":  *  *     if (eax == [m]) {  *         zf = 1;  *         [m] = r;  *     } else {  *         zf = 0;  *         eax = [m];  *     }  *  *   * The "q" is any of the %eax, %ebx, %ecx, or %edx registers.  * The "=a" and "a" are the %eax register.  Although we can return result  * in any register, we use %eax because it is used in cmpxchgl anyway.  * The "cc" means that flags were changed.  */
end_comment

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
name|ngx_atomic_uint_t
name|res
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    cmpxchgl  %3, %1;   "     "    setz      %b0;      "     "    movzbl    %b0, %0;  "      : "=a" (res) : "m" (*lock), "a" (old), "q" (set) : "cc", "memory");
return|return
name|res
return|;
block|}
end_function

begin_comment
comment|/*  * "xaddl  r, [m]":  *  *     temp = [m];  *     [m] += r;  *     r = temp;  *  *  * The "+q" is any of the %eax, %ebx, %ecx, or %edx registers.  * The "cc" means that flags were changed.  */
end_comment

begin_if
if|#
directive|if
operator|!
operator|(
name|__GNUC__
operator|==
literal|2
operator|&&
name|__GNUC_MINOR__
operator|<=
literal|7
operator|)
end_if

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
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    xaddl  %0, %1;   "      : "+q" (add) : "m" (*value) : "cc", "memory");
return|return
name|add
return|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* (__GNUC__ == 2&& __GNUC_MINOR__<= 7) */
end_comment

begin_comment
comment|/*  * gcc 2.7 does not support "+q", so we have to use the fixed %eax ("=a" and  * "a") and this adds two superfluous instructions in the end of code,  * something like this: "mov %eax, %edx / mov %edx, %eax".  */
end_comment

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
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    xaddl  %2, %1;   "      : "=a" (old) : "m" (*value), "a" (add) : "cc", "memory");
return|return
name|old
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

