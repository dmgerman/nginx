begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_ATOMIC_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_ATOMIC_H_INCLUDED_
define|#
directive|define
name|_NGX_ATOMIC_H_INCLUDED_
end_define

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
name|__i386__
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_typedef
DECL|typedef|ngx_atomic_int_t
typedef|typedef
name|int32_t
name|ngx_atomic_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_uint_t
typedef|typedef
name|uint32_t
name|ngx_atomic_uint_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_t
typedef|typedef
specifier|volatile
name|ngx_atomic_uint_t
name|ngx_atomic_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_ATOMIC_T_LEN
define|#
directive|define
name|NGX_ATOMIC_T_LEN
value|sizeof("-2147483648") - 1
end_define

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
comment|/*  * the "=q" is any of the %eax, %ebx, %ecx, or %edx registers.  * the '"0" (1)' parameter preloads 1 into %0.  * the "cc" means that flags were changed.  *  * "xadd  r, [m]":  *  *     temp = [m];  *     [m] += r;  *     r = temp;  */
end_comment

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_inc (ngx_atomic_t * value)
name|ngx_atomic_inc
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|old
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    xaddl  %0, %2;   "     "    incl   %0;       "      : "=q" (old) : "0" (1), "m" (*value) : "cc", "memory");
return|return
name|old
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_dec (ngx_atomic_t * value)
name|ngx_atomic_dec
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|old
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    xaddl  %0, %2;   "     "    decl   %0;       "      : "=q" (old) : "0" (-1), "m" (*value) : "cc", "memory");
return|return
name|old
return|;
block|}
end_function

begin_comment
comment|/*  * the "q" is any of the %eax, %ebx, %ecx, or %edx registers.  * the "=a" and "a" are the %eax register.  Although we can return result  * in any register, we use %eax because it is used in cmpxchg anyway.  *  * "cmpxchg  r, [m]":  *  *     if (eax == [m]) {  *         zf = 1;  *         [m] = r;  *     } else {  *         zf = 0;  *         eax = [m];  *     }  */
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

begin_elif
elif|#
directive|elif
operator|(
name|__amd64__
operator|)
end_elif

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_typedef
DECL|typedef|ngx_atomic_int_t
typedef|typedef
name|int64_t
name|ngx_atomic_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_uint_t
typedef|typedef
name|uint64_t
name|ngx_atomic_uint_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_t
typedef|typedef
specifier|volatile
name|ngx_atomic_uint_t
name|ngx_atomic_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_ATOMIC_T_LEN
define|#
directive|define
name|NGX_ATOMIC_T_LEN
value|sizeof("-9223372036854775808") - 1
end_define

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

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_inc (ngx_atomic_t * value)
name|ngx_atomic_inc
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|old
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    xaddq  %0, %2;   "     "    incq   %0;       "      : "=r" (old) : "0" (1), "m" (*value) : "cc", "memory");
return|return
name|old
return|;
block|}
end_function

begin_comment
comment|/* the '"0" (-1LL)' parameter preloads -1 into the 64-bit %0 register */
end_comment

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_dec (ngx_atomic_t * value)
name|ngx_atomic_dec
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|old
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(           NGX_SMP_LOCK     "    xaddq  %0, %2;   "     "    decq   %0;       "      : "=r" (old) : "0" (-1LL), "m" (*value) : "cc", "memory");
return|return
name|old
return|;
block|}
end_function

begin_comment
comment|/* the "=a" and "a" are the %rax register. */
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

begin_elif
elif|#
directive|elif
operator|(
name|__sparc__
operator|)
end_elif

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_PTR_SIZE
operator|==
literal|8
operator|)
end_if

begin_typedef
DECL|typedef|ngx_atomic_int_t
typedef|typedef
name|int64_t
name|ngx_atomic_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_uint_t
typedef|typedef
name|uint64_t
name|ngx_atomic_uint_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_ATOMIC_T_LEN
define|#
directive|define
name|NGX_ATOMIC_T_LEN
value|sizeof("-9223372036854775808") - 1
end_define

begin_define
DECL|macro|NGX_CASXA
define|#
directive|define
name|NGX_CASXA
value|"casxa"
end_define

begin_else
else|#
directive|else
end_else

begin_typedef
DECL|typedef|ngx_atomic_int_t
typedef|typedef
name|int32_t
name|ngx_atomic_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_uint_t
typedef|typedef
name|uint32_t
name|ngx_atomic_uint_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_ATOMIC_T_LEN
define|#
directive|define
name|NGX_ATOMIC_T_LEN
value|sizeof("-2147483648") - 1
end_define

begin_define
DECL|macro|NGX_CASXA
define|#
directive|define
name|NGX_CASXA
value|"casa"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_atomic_t
typedef|typedef
specifier|volatile
name|ngx_atomic_uint_t
name|ngx_atomic_t
typedef|;
end_typedef

begin_comment
comment|/*  * the "+r" means the general register used for both input and output.  *  * "casa   [r1] 0x80, r2, r0"  and  * "casxa  [r1] 0x80, r2, r0"  do the following:  *  *     if ([r1] == r2) {  *         swap(r0, [r1]);  *     } else {  *         r0 = [r1];  *     }  *  * so "r0 == r2" means that the operation was successfull.  */
end_comment

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_inc (ngx_atomic_t * value)
name|ngx_atomic_inc
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|old
decl_stmt|,
name|new
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
name|new
operator|=
name|old
operator|+
literal|1
expr_stmt|;
name|res
operator|=
name|new
expr_stmt|;
asm|__asm__
specifier|volatile
asm|(          NGX_CASXA " [%1] 0x80, %2, %0"          : "+r" (res) : "r" (value), "r" (old) : "memory");
if|if
condition|(
name|res
operator|==
name|old
condition|)
block|{
return|return
name|new
return|;
block|}
name|old
operator|=
name|res
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_dec (ngx_atomic_t * value)
name|ngx_atomic_dec
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|old
decl_stmt|,
name|new
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
name|new
operator|=
name|old
operator|-
literal|1
expr_stmt|;
name|res
operator|=
name|new
expr_stmt|;
asm|__asm__
specifier|volatile
asm|(          NGX_CASXA " [%1] 0x80, %2, %0"          : "+r" (res) : "r" (value), "r" (old) : "memory");
if|if
condition|(
name|res
operator|==
name|old
condition|)
block|{
return|return
name|new
return|;
block|}
name|old
operator|=
name|res
expr_stmt|;
block|}
block|}
end_function

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
asm|(      NGX_CASXA " [%1] 0x80, %2, %0"      : "+r" (set) : "r" (lock), "r" (old) : "memory");
return|return
operator|(
name|set
operator|==
name|old
operator|)
return|;
block|}
end_function

begin_elif
elif|#
directive|elif
operator|(
name|__ppc__
operator|)
end_elif

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_PTR_SIZE
operator|==
literal|8
operator|)
end_if

begin_typedef
DECL|typedef|ngx_atomic_int_t
typedef|typedef
name|int64_t
name|ngx_atomic_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_uint_t
typedef|typedef
name|uint64_t
name|ngx_atomic_uint_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_ATOMIC_T_LEN
define|#
directive|define
name|NGX_ATOMIC_T_LEN
value|sizeof("-9223372036854775808") - 1
end_define

begin_else
else|#
directive|else
end_else

begin_typedef
DECL|typedef|ngx_atomic_int_t
typedef|typedef
name|int32_t
name|ngx_atomic_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_uint_t
typedef|typedef
name|uint32_t
name|ngx_atomic_uint_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_ATOMIC_T_LEN
define|#
directive|define
name|NGX_ATOMIC_T_LEN
value|sizeof("-2147483648") - 1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_atomic_t
typedef|typedef
specifier|volatile
name|ngx_atomic_uint_t
name|ngx_atomic_t
typedef|;
end_typedef

begin_comment
comment|/*  * the ppc assembler treats ";" as comment, so we have to use "\n".  * the minus in "bne-" is a hint for the branch prediction unit that  * this branch is unlikely to be taken.  *  * the "=&r" means that no input registers can be used.  * the "=&b" means that the base registers can be used only, i.e. any register  * except r0.  the r0 register can not be used in "addi  r0, r0, 1".  * the "1b" means the nearest backward label "1" and the "1f" means  * the nearest forward label "1".  */
end_comment

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_inc (ngx_atomic_t * value)
name|ngx_atomic_inc
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|res
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(      "1:  lwarx   %0, 0, %1  \n"
comment|/* load from [value] into "res"             */
comment|/*   and store reservation                  */
asm|"    addi    %0, %0, 1  \n"
comment|/* add "1" to "res"                         */
asm|"    stwcx.  %0, 0, %1  \n"
comment|/* store "res" into [value] if reservation  */
comment|/*    is not cleared                        */
asm|"    bne-    1b         \n"
comment|/* try again if reservation was cleared     */
asm|: "=&b" (res) : "r" (value) : "cc", "memory");
return|return
name|res
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_dec (ngx_atomic_t * value)
name|ngx_atomic_dec
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|res
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(      "1:  lwarx   %0, 0, %1  \n"
comment|/* load from [value] into "res"             */
comment|/*   and store reservation                  */
asm|"    addi    %0, %0, -1 \n"
comment|/* sub "1" from "res"                       */
asm|"    stwcx.  %0, 0, %1  \n"
comment|/* store "res" into [value] if reservation  */
comment|/*    is not cleared                        */
asm|"    bne-    1b         \n"
comment|/* try again if reservation was cleared     */
asm|: "=&b" (res) : "r" (value) : "cc", "memory");
return|return
name|res
return|;
block|}
end_function

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
decl_stmt|,
name|temp
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(      "    li      %0, 0      \n"
comment|/* preset "0" to "res"                      */
asm|"    lwarx   %1, 0, %2  \n"
comment|/* load from [lock] into "temp"             */
comment|/*   and store reservation                  */
asm|"    cmpw    %1, %3     \n"
comment|/* compare "temp" and "old"                 */
asm|"    bne-    1f         \n"
comment|/* not equal                                */
asm|"    stwcx.  %4, 0, %2  \n"
comment|/* store "set" into [lock] if reservation   */
comment|/*    is not cleared                        */
asm|"    bne-    1f         \n"
comment|/* the reservation was cleared              */
asm|"    li      %0, 1      \n"
comment|/* set "1" to "res"                         */
asm|"1:                     \n"      : "=&r" (res), "=&r" (temp)     : "r" (lock), "r" (old), "r" (set)     : "cc", "memory");
return|return
name|res
return|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|0
end_define

begin_typedef
DECL|typedef|ngx_atomic_int_t
typedef|typedef
name|int32_t
name|ngx_atomic_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_uint_t
typedef|typedef
name|uint32_t
name|ngx_atomic_uint_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_atomic_t
typedef|typedef
specifier|volatile
name|ngx_atomic_uint_t
name|ngx_atomic_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_atomic_inc (x)
define|#
directive|define
name|ngx_atomic_inc
parameter_list|(
name|x
parameter_list|)
value|++(*(x))
end_define

begin_define
DECL|macro|ngx_atomic_dec (x)
define|#
directive|define
name|ngx_atomic_dec
parameter_list|(
name|x
parameter_list|)
value|--(*(x))
end_define

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
operator|*
name|lock
operator|=
name|set
expr_stmt|;
return|return
literal|1
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
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
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_trylock (lock)
define|#
directive|define
name|ngx_trylock
parameter_list|(
name|lock
parameter_list|)
value|(*(lock) == 0&& ngx_atomic_cmp_set(lock, 0, 1))
end_define

begin_define
DECL|macro|ngx_unlock (lock)
define|#
directive|define
name|ngx_unlock
parameter_list|(
name|lock
parameter_list|)
value|*(lock) = 0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ATOMIC_H_INCLUDED_ */
end_comment

end_unit

