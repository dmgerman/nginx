begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SLAB_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SLAB_H_INCLUDED_
define|#
directive|define
name|_NGX_SLAB_H_INCLUDED_
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

begin_typedef
DECL|typedef|ngx_free_slab_t
typedef|typedef
name|struct
name|ngx_free_slab_s
name|ngx_free_slab_t
typedef|;
end_typedef

begin_typedef
DECL|struct|ngx_free_slab_s
typedef|typedef
struct|struct
name|ngx_free_slab_s
block|{
DECL|member|next
name|ngx_free_slab_t
modifier|*
name|next
decl_stmt|;
block|}
DECL|typedef|ngx_slab_block_t
typedef|typedef struct
name|ngx_slab_block_s
name|ngx_slab_block_t
typedef|;
end_typedef

begin_typedef
DECL|struct|ngx_slab_block_s
typedef|typedef
struct|struct
name|ngx_slab_block_s
block|{
DECL|member|free
name|ngx_free_slab_t
modifier|*
name|free
decl_stmt|;
DECL|member|next
name|ngx_slab_buf_t
modifier|*
name|next
decl_stmt|;
DECL|member|color
name|size_t
name|color
decl_stmt|;
block|}
empty_stmt|;
end_typedef

begin_typedef
DECL|struct|__anon2a2729750108
typedef|typedef
struct|struct
block|{
DECL|member|blocks
name|ngx_slab_buf_t
modifier|*
name|blocks
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|start
name|void
modifier|*
name|start
decl_stmt|;
DECL|member|map
name|uint32_t
name|map
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|free
name|ngx_free_pool_t
name|free
decl_stmt|;
DECL|typedef|ngx_slab_pool_t
block|}
name|ngx_slab_pool_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SLAB_H_INCLUDED_ */
end_comment

end_unit

