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
file|<ngx_log.h>
end_include

begin_comment
comment|/* NGX_MAX_ALLOC_FROM_POOL should be (PAGE_SIZE - 1), i.e. 4095 on x86.    On FreeBSD 5.x it allows to use zero copy send.    On Windows NT it decreases number of locked pages in kernel.  */
end_comment

begin_define
DECL|macro|NGX_MAX_ALLOC_FROM_POOL
define|#
directive|define
name|NGX_MAX_ALLOC_FROM_POOL
value|4095
end_define

begin_define
DECL|macro|NGX_DEFAULT_POOL_SIZE
define|#
directive|define
name|NGX_DEFAULT_POOL_SIZE
value|(16 * 1024)
end_define

begin_define
DECL|macro|ngx_test_null (p,alloc,rc)
define|#
directive|define
name|ngx_test_null
parameter_list|(
name|p
parameter_list|,
name|alloc
parameter_list|,
name|rc
parameter_list|)
value|if ((p = alloc) == NULL) { return rc; }
end_define

begin_typedef
DECL|typedef|ngx_pool_large_t
typedef|typedef
name|struct
name|ngx_pool_large_s
name|ngx_pool_large_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_pool_large_s
struct|struct
name|ngx_pool_large_s
block|{
DECL|member|next
name|ngx_pool_large_t
modifier|*
name|next
decl_stmt|;
DECL|member|alloc
name|void
modifier|*
name|alloc
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|ngx_pool_t
typedef|typedef
name|struct
name|ngx_pool_s
name|ngx_pool_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_pool_s
struct|struct
name|ngx_pool_s
block|{
DECL|member|last
name|char
modifier|*
name|last
decl_stmt|;
DECL|member|end
name|char
modifier|*
name|end
decl_stmt|;
DECL|member|next
name|ngx_pool_t
modifier|*
name|next
decl_stmt|;
DECL|member|large
name|ngx_pool_large_t
modifier|*
name|large
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
block|}
struct|;
end_struct

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

begin_function_decl
name|ngx_pool_t
modifier|*
name|ngx_create_pool
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
name|ngx_destroy_pool
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_palloc
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_pcalloc
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ALLOC_H_INCLUDED_ */
end_comment

end_unit

