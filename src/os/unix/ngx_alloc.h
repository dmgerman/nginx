begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_ALLOC_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_ALLOC_H_INCLUDED_
define|#
directive|define
name|_NGX_ALLOC_H_INCLUDED_
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

begin_function_decl
name|void
modifier|*
name|ngx_alloc
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_calloc
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_free
define|#
directive|define
name|ngx_free
value|free
end_define

begin_comment
comment|/*  * Linux has memalign() or posix_memalign()  * Solaris has memalign()  * FreeBSD has not memalign() or posix_memalign() but its malloc() alignes  * allocations bigger than page size at page boundary.  */
end_comment

begin_if
if|#
directive|if
operator|(
name|HAVE_POSIX_MEMALIGN
operator|||
name|HAVE_MEMALIGN
operator|)
end_if

begin_function_decl
name|void
modifier|*
name|ngx_memalign
parameter_list|(
name|size_t
name|alignment
parameter_list|,
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_memalign (alignment,size,log)
define|#
directive|define
name|ngx_memalign
parameter_list|(
name|alignment
parameter_list|,
name|size
parameter_list|,
name|log
parameter_list|)
value|ngx_alloc(size, log)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|int
name|ngx_pagesize
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ALLOC_H_INCLUDED_ */
end_comment

end_unit

