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

begin_define
DECL|macro|ngx_atomic_inc (p)
define|#
directive|define
name|ngx_atomic_inc
parameter_list|(
name|p
parameter_list|)
value|InterlockedIncrement((long *) p)
end_define

begin_define
DECL|macro|ngx_atomic_dec (p)
define|#
directive|define
name|ngx_atomic_dec
parameter_list|(
name|p
parameter_list|)
value|InterlockedDecrement((long *) p)
end_define

begin_if
if|#
directive|if
name|defined
argument_list|(
name|__WATCOMC__
argument_list|)
operator|||
name|defined
argument_list|(
name|__BORLANDC__
argument_list|)
end_if

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
define|\
value|(InterlockedCompareExchange((long *) lock, set, old) == old)
end_define

begin_else
else|#
directive|else
end_else

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
define|\
value|(InterlockedCompareExchange((void **) lock, (void *) set, (void *) old)  \       == (void *) old)
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

