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
comment|/*  * "cmpxchgq  r, [m]":  *  *     if (rax == [m]) {  *         zf = 1;  *         [m] = r;  *     } else {  *         zf = 0;  *         rax = [m];  *     }  *  *  * The "r" is any register, %rax (%r0) - %r16.  * The "=a" and "a" are the %rax register.  Although we can return result  * in any register, we use %rax because it is used in cmpxchgq anyway.  * The "cc" means that flags were changed.  */
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
asm|(           NGX_SMP_LOCK     "    cmpxchgq  %3, %1;   "     "    setz      %b0;      "     "    movzbq    %b0, %0;  "      : "=a" (res) : "m" (*lock), "a" (old), "r" (set) : "cc", "memory");
return|return
name|res
return|;
block|}
end_function

begin_comment
comment|/*  * "xaddq  r, [m]":  *  *     temp = [m];  *     [m] += r;  *     r = temp;  *  *  * The "+r" is any register, %rax (%r0) - %r16.  * The "cc" means that flags were changed.  */
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
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    xaddq  %0, %1;   "      : "+q" (add) : "m" (*value) : "cc", "memory");
return|return
name|add
return|;
block|}
end_function

end_unit

