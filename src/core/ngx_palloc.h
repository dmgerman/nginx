begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_PALLOC_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_PALLOC_H_INCLUDED_
define|#
directive|define
name|_NGX_PALLOC_H_INCLUDED_
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

begin_comment
comment|/*  * NGX_MAX_ALLOC_FROM_POOL should be (ngx_page_size - 1), i.e. 4095 on x86.  * On FreeBSD 5.x it allows to use the zero copy sending.  * On Windows NT it decreases a number of locked pages in a kernel.  */
end_comment

begin_define
DECL|macro|NGX_MAX_ALLOC_FROM_POOL
define|#
directive|define
name|NGX_MAX_ALLOC_FROM_POOL
value|(ngx_pagesize - 1)
end_define

begin_define
DECL|macro|NGX_DEFAULT_POOL_SIZE
define|#
directive|define
name|NGX_DEFAULT_POOL_SIZE
value|(16 * 1024)
end_define

begin_typedef
DECL|typedef|ngx_pool_cleanup_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_pool_cleanup_pt
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_pool_cleanup_t
typedef|typedef
name|struct
name|ngx_pool_cleanup_s
name|ngx_pool_cleanup_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_pool_cleanup_s
struct|struct
name|ngx_pool_cleanup_s
block|{
DECL|member|handler
name|ngx_pool_cleanup_pt
name|handler
decl_stmt|;
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|next
name|ngx_pool_cleanup_t
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

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

begin_struct
DECL|struct|ngx_pool_s
struct|struct
name|ngx_pool_s
block|{
DECL|member|last
name|u_char
modifier|*
name|last
decl_stmt|;
DECL|member|end
name|u_char
modifier|*
name|end
decl_stmt|;
DECL|member|chain
name|ngx_chain_t
modifier|*
name|chain
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
DECL|member|cleanup
name|ngx_pool_cleanup_t
modifier|*
name|cleanup
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2a9e2be70108
typedef|typedef
struct|struct
block|{
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|member|name
name|u_char
modifier|*
name|name
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_pool_cleanup_file_t
block|}
name|ngx_pool_cleanup_file_t
typedef|;
end_typedef

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

begin_function_decl
name|ngx_int_t
name|ngx_pfree
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|void
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_pool_cleanup_t
modifier|*
name|ngx_pool_cleanup_add
parameter_list|(
name|ngx_pool_t
modifier|*
name|p
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_pool_cleanup_file
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PALLOC_H_INCLUDED_ */
end_comment

end_unit

