begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_ifdef
ifdef|#
directive|ifdef
name|__i386__
end_ifdef

begin_typedef
DECL|typedef|ngx_atomic_t
typedef|typedef
name|uint32_t
name|ngx_atomic_t
typedef|;
end_typedef

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
value|"lock"
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
DECL|function|ngx_atomic_inc (ngx_atomic_t * value)
specifier|static
name|ngx_inline
name|uint32_t
name|ngx_atomic_inc
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|uint32_t
name|old
decl_stmt|;
name|__asm__
name|__volatile
argument_list|(
literal|"          movl   $1, %0     "
name|NGX_SMP_LOCK
literal|"   xaddl  %0, %1      "
operator|:
literal|"=a"
operator|(
name|old
operator|)
operator|:
literal|"m"
operator|(
operator|*
name|value
operator|)
argument_list|)
decl_stmt|;
return|return
name|old
return|;
block|}
end_function

begin_function
DECL|function|ngx_atomic_dec (ngx_atomic_t * value)
specifier|static
name|ngx_inline
name|uint32_t
name|ngx_atomic_dec
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|)
block|{
name|uint32_t
name|old
decl_stmt|;
name|__asm__
name|__volatile
argument_list|(
literal|"          movl   $-1, %0     "
name|NGX_SMP_LOCK
literal|"   xaddl  %0, %1      "
operator|:
literal|"=a"
operator|(
name|old
operator|)
operator|:
literal|"m"
operator|(
operator|*
name|value
operator|)
argument_list|)
decl_stmt|;
return|return
name|old
return|;
block|}
end_function

begin_function
DECL|function|ngx_atomic_cmp_set (ngx_atomic_t * lock,ngx_atomic_t old,ngx_atomic_t set)
specifier|static
name|ngx_inline
name|uint32_t
name|ngx_atomic_cmp_set
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|,
name|ngx_atomic_t
name|old
parameter_list|,
name|ngx_atomic_t
name|set
parameter_list|)
block|{
name|uint32_t
name|res
decl_stmt|;
name|__asm__
name|__volatile
argument_list|(
literal|"      "
name|NGX_SMP_LOCK
literal|"   cmpxchgl  %3, %1         setzb     %%al         movzbl    %%al, %0      "
operator|:
literal|"=a"
operator|(
name|res
operator|)
operator|:
literal|"m"
operator|(
operator|*
name|lock
operator|)
argument_list|,
literal|"a"
operator|(
name|old
operator|)
argument_list|,
literal|"q"
operator|(
name|set
operator|)
argument_list|)
decl_stmt|;
return|return
name|res
return|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_typedef
DECL|typedef|ngx_atomic_t
typedef|typedef
name|uint32_t
name|ngx_atomic_t
typedef|;
end_typedef

begin_comment
comment|/* STUB */
end_comment

begin_define
DECL|macro|ngx_atomic_inc (x)
define|#
directive|define
name|ngx_atomic_inc
parameter_list|(
name|x
parameter_list|)
value|x++;
end_define

begin_define
DECL|macro|ngx_atomic_dec (x)
define|#
directive|define
name|ngx_atomic_dec
parameter_list|(
name|x
parameter_list|)
value|x--;
end_define

begin_define
DECL|macro|ngx_atomic_cmp_set (lock,old,set)
define|#
directive|define
name|ngx_atomic_cmp_set
parameter_list|(
name|lock
parameter_list|,
name|old
parameter_list|,
name|set
parameter_list|)
value|1;
end_define

begin_comment
comment|/**/
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ATOMIC_H_INCLUDED_ */
end_comment

end_unit

