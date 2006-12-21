begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_comment
comment|/*  * The ppc assembler treats ";" as comment, so we have to use "\n".  * The minus in "bne-" is a hint for the branch prediction unit that  * this branch is unlikely to be taken.  * The "1b" means the nearest backward label "1" and the "1f" means  * the nearest forward label "1".  *  * The "b" means that the base registers can be used only, i.e.  * any register except r0.  The r0 register always has a zero value and  * could not be used in "addi  r0, r0, 1".  * The "=&b" means that no input registers can be used.  */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_PTR_SIZE
operator|==
literal|8
operator|)
end_if

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
asm|(      "    li      %0, 0       \n"
comment|/* preset "0" to "res"                      */
asm|"1:                      \n"     "    ldarx   %1, 0, %2   \n"
comment|/* load from [lock] into "temp"             */
comment|/*   and store reservation                  */
asm|"    cmpd    %1, %3      \n"
comment|/* compare "temp" and "old"                 */
asm|"    bne-    2f          \n"
comment|/* not equal                                */
asm|"    stdcx.  %4, 0, %2   \n"
comment|/* store "set" into [lock] if reservation   */
comment|/*   is not cleared                         */
asm|"    bne-    1b          \n"
comment|/* the reservation was cleared              */
asm|"    li      %0, 1       \n"
comment|/* set "1" to "res"                         */
asm|"2:                      \n"      : "=&b" (res), "=&b" (temp)     : "b" (lock), "b" (old), "b" (set)     : "cc", "memory");
return|return
name|res
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
name|res
decl_stmt|,
name|temp
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(      "1:  ldarx   %0, 0, %2   \n"
comment|/* load from [value] into "res"             */
comment|/*   and store reservation                  */
asm|"    add     %1, %0, %3  \n"
comment|/* "res" + "add" store in "temp"            */
asm|"    stdcx.  %1, 0, %2   \n"
comment|/* store "temp" into [value] if reservation */
comment|/*   is not cleared                         */
asm|"    bne-    1b          \n"
comment|/* try again if reservation was cleared     */
asm|: "=&b" (res), "=&b" (temp)     : "b" (value), "b" (add)     : "cc", "memory");
return|return
name|res
return|;
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
value|__asm__ volatile ("lwsync\n" ::: "memory")
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

begin_else
else|#
directive|else
end_else

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
asm|(      "    li      %0, 0       \n"
comment|/* preset "0" to "res"                      */
asm|"1:                      \n"     "    lwarx   %1, 0, %2   \n"
comment|/* load from [lock] into "temp"             */
comment|/*   and store reservation                  */
asm|"    cmpw    %1, %3      \n"
comment|/* compare "temp" and "old"                 */
asm|"    bne-    2f          \n"
comment|/* not equal                                */
asm|"    stwcx.  %4, 0, %2   \n"
comment|/* store "set" into [lock] if reservation   */
comment|/*   is not cleared                         */
asm|"    bne-    1b          \n"
comment|/* the reservation was cleared              */
asm|"    li      %0, 1       \n"
comment|/* set "1" to "res"                         */
asm|"2:                      \n"      : "=&b" (res), "=&b" (temp)     : "b" (lock), "b" (old), "b" (set)     : "cc", "memory");
return|return
name|res
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
name|res
decl_stmt|,
name|temp
decl_stmt|;
asm|__asm__
specifier|volatile
asm|(      "1:  lwarx   %0, 0, %2   \n"
comment|/* load from [value] into "res"             */
comment|/*   and store reservation                  */
asm|"    add     %1, %0, %3  \n"
comment|/* "res" + "add" store in "temp"            */
asm|"    stwcx.  %1, 0, %2   \n"
comment|/* store "temp" into [value] if reservation */
comment|/*   is not cleared                         */
asm|"    bne-    1b          \n"
comment|/* try again if reservation was cleared     */
asm|: "=&b" (res), "=&b" (temp)     : "b" (value), "b" (add)     : "cc", "memory");
return|return
name|res
return|;
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
value|__asm__ volatile ("sync\n" ::: "memory")
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

