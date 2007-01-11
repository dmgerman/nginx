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
comment|/*  * "cmpxchgl  r, [m]":  *  *     if (eax == [m]) {  *         zf = 1;  *         [m] = r;  *     } else {  *         zf = 0;  *         eax = [m];  *     }  *  *  * The "r" means the general register.  * The "=a" and "a" are the %eax register.  * Although we can return result in any register, we use "a" because it is  * used in cmpxchgl anyway.  The result is actually in %al but not in %eax,  * however, as the code is inlined gcc can test %al as well as %eax,  * and icc adds "movzbl %al, %eax" by itself.  *  * The "cc" means that flags were changed.  */
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
name|u_char
name|res
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    cmpxchgl  %3, %1;   "     "    sete      %0;       "      : "=a" (res) : "m" (*lock), "a" (old), "r" (set) : "cc", "memory");
return|return
name|res
return|;
block|}
end_function

begin_comment
comment|/*  * "xaddl  r, [m]":  *  *     temp = [m];  *     [m] += r;  *     r = temp;  *  *  * The "+r" means the general register.  * The "cc" means that flags were changed.  */
end_comment

begin_if
if|#
directive|if
operator|!
operator|(
operator|(
name|__GNUC__
operator|==
literal|2
operator|&&
name|__GNUC_MINOR__
operator|<=
literal|7
operator|)
operator|||
operator|(
name|__INTEL_COMPILER
operator|>=
literal|800
operator|)
operator|)
end_if

begin_comment
comment|/*  * icc 8.1 and 9.0 compile broken code with -march=pentium4 option:  * ngx_atomic_fetch_add() always return the input "add" value,  * so we use the gcc 2.7 version.  *  * icc 8.1 and 9.0 with -march=pentiumpro option or icc 7.1 compile  * correct code.  */
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
asm|(           NGX_SMP_LOCK     "    xaddl  %0, %1;   "      : "+r" (add) : "m" (*value) : "cc", "memory");
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
comment|/*  * gcc 2.7 does not support "+r", so we have to use the fixed  * %eax ("=a" and "a") and this adds two superfluous instructions in the end  * of code, something like this: "mov %eax, %edx / mov %edx, %eax".  */
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

begin_comment
comment|/*  * on x86 the write operations go in a program order, so we need only  * to disable the gcc reorder optimizations  */
end_comment

begin_define
DECL|macro|ngx_memory_barrier ()
define|#
directive|define
name|ngx_memory_barrier
parameter_list|()
value|__asm__ volatile ("" ::: "memory")
end_define

begin_comment
comment|/* old as does not support "pause" opcode */
end_comment

begin_define
DECL|macro|ngx_cpu_pause ()
define|#
directive|define
name|ngx_cpu_pause
parameter_list|()
value|__asm__ (".byte 0xf3, 0x90")
end_define

end_unit

