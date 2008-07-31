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
name|NGX_DARWIN_ATOMIC
operator|)
end_if

begin_comment
comment|/*  * use Darwin 8 atomic(3) and barrier(3) operations  * optimized at run-time for UP and SMP  */
end_comment

begin_include
include|#
directive|include
file|<libkern/OSAtomic.h>
end_include

begin_comment
comment|/* "bool" conflicts with perl's CORE/handy.h */
end_comment

begin_undef
undef|#
directive|undef
name|bool
end_undef

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
DECL|macro|ngx_atomic_cmp_set (lock,old,new)
define|#
directive|define
name|ngx_atomic_cmp_set
parameter_list|(
name|lock
parameter_list|,
name|old
parameter_list|,
name|new
parameter_list|)
define|\
value|OSAtomicCompareAndSwap64Barrier(old, new, (int64_t *) lock)
end_define

begin_define
DECL|macro|ngx_atomic_fetch_add (value,add)
define|#
directive|define
name|ngx_atomic_fetch_add
parameter_list|(
name|value
parameter_list|,
name|add
parameter_list|)
define|\
value|(OSAtomicAdd64(add, (int64_t *) value) - add)
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
DECL|macro|ngx_atomic_cmp_set (lock,old,new)
define|#
directive|define
name|ngx_atomic_cmp_set
parameter_list|(
name|lock
parameter_list|,
name|old
parameter_list|,
name|new
parameter_list|)
define|\
value|OSAtomicCompareAndSwap32Barrier(old, new, (int32_t *) lock)
end_define

begin_define
DECL|macro|ngx_atomic_fetch_add (value,add)
define|#
directive|define
name|ngx_atomic_fetch_add
parameter_list|(
name|value
parameter_list|,
name|add
parameter_list|)
define|\
value|(OSAtomicAdd32(add, (int32_t *) value) - add)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_memory_barrier ()
define|#
directive|define
name|ngx_memory_barrier
parameter_list|()
value|OSMemoryBarrier()
end_define

begin_define
DECL|macro|ngx_cpu_pause ()
define|#
directive|define
name|ngx_cpu_pause
parameter_list|()
end_define

begin_typedef
DECL|typedef|ngx_atomic_t
typedef|typedef
specifier|volatile
name|ngx_atomic_uint_t
name|ngx_atomic_t
typedef|;
end_typedef

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !(NGX_DARWIN) */
end_comment

begin_if
if|#
directive|if
operator|(
name|__i386__
operator|||
name|__i386
operator|)
end_if

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
name|__SUNPRO_C
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_function_decl
name|ngx_atomic_uint_t
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
function_decl|;
end_function_decl

begin_function_decl
name|ngx_atomic_int_t
name|ngx_atomic_fetch_add
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|,
name|ngx_atomic_int_t
name|add
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Sun Studio 12 exits with segmentation fault on '__asm ("pause")',  * so ngx_cpu_pause is declared in src/os/unix/ngx_sunpro_x86.il  */
end_comment

begin_function_decl
name|void
name|ngx_cpu_pause
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* the code in src/os/unix/ngx_sunpro_x86.il */
end_comment

begin_define
DECL|macro|ngx_memory_barrier ()
define|#
directive|define
name|ngx_memory_barrier
parameter_list|()
value|__asm (".volatile"); __asm (".nonvolatile")
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* ( __GNUC__ || __INTEL_COMPILER ) */
end_comment

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_include
include|#
directive|include
file|"ngx_gcc_atomic_x86.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_elif
elif|#
directive|elif
operator|(
name|__amd64__
operator|||
name|__amd64
operator|)
end_elif

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
name|__SUNPRO_C
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_function_decl
name|ngx_atomic_uint_t
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
function_decl|;
end_function_decl

begin_function_decl
name|ngx_atomic_int_t
name|ngx_atomic_fetch_add
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|,
name|ngx_atomic_int_t
name|add
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Sun Studio 12 exits with segmentation fault on '__asm ("pause")',  * so ngx_cpu_pause is declared in src/os/unix/ngx_sunpro_amd64.il  */
end_comment

begin_function_decl
name|void
name|ngx_cpu_pause
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* the code in src/os/unix/ngx_sunpro_amd64.il */
end_comment

begin_define
DECL|macro|ngx_memory_barrier ()
define|#
directive|define
name|ngx_memory_barrier
parameter_list|()
value|__asm (".volatile"); __asm (".nonvolatile")
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* ( __GNUC__ || __INTEL_COMPILER ) */
end_comment

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_include
include|#
directive|include
file|"ngx_gcc_atomic_amd64.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_elif
elif|#
directive|elif
operator|(
name|__sparc__
operator|||
name|__sparc
operator|||
name|__sparcv9
operator|)
end_elif

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

begin_if
if|#
directive|if
operator|(
name|__SUNPRO_C
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_include
include|#
directive|include
file|"ngx_sunpro_atomic_sparc64.h"
end_include

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* ( __GNUC__ || __INTEL_COMPILER ) */
end_comment

begin_define
DECL|macro|NGX_HAVE_ATOMIC_OPS
define|#
directive|define
name|NGX_HAVE_ATOMIC_OPS
value|1
end_define

begin_include
include|#
directive|include
file|"ngx_gcc_atomic_sparc64.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_elif
elif|#
directive|elif
operator|(
name|__powerpc__
operator|||
name|__POWERPC__
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

begin_include
include|#
directive|include
file|"ngx_gcc_atomic_ppc.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|!
operator|(
name|NGX_HAVE_ATOMIC_OPS
operator|)
end_if

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
DECL|macro|NGX_ATOMIC_T_LEN
define|#
directive|define
name|NGX_ATOMIC_T_LEN
value|sizeof("-2147483648") - 1
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
if|if
condition|(
operator|*
name|lock
operator|==
name|old
condition|)
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
return|return
literal|0
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
name|ngx_atomic_int_t
name|old
decl_stmt|;
name|old
operator|=
operator|*
name|value
expr_stmt|;
operator|*
name|value
operator|+=
name|add
expr_stmt|;
return|return
name|old
return|;
block|}
end_function

begin_define
DECL|macro|ngx_memory_barrier ()
define|#
directive|define
name|ngx_memory_barrier
parameter_list|()
end_define

begin_define
DECL|macro|ngx_cpu_pause ()
define|#
directive|define
name|ngx_cpu_pause
parameter_list|()
end_define

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
name|ngx_atomic_int_t
name|value
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

