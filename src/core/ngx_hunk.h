begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HUNK_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HUNK_H_INCLUDED_
define|#
directive|define
name|_NGX_HUNK_H_INCLUDED_
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
comment|/* hunk type */
end_comment

begin_comment
comment|/* the hunk is in memory */
end_comment

begin_define
DECL|macro|NGX_HUNK_IN_MEMORY
define|#
directive|define
name|NGX_HUNK_IN_MEMORY
value|0x0001
end_define

begin_comment
comment|/* the hunk's content can be changed */
end_comment

begin_define
DECL|macro|NGX_HUNK_TEMP
define|#
directive|define
name|NGX_HUNK_TEMP
value|0x0002
end_define

begin_comment
comment|/* the hunk's content is in cache and can not be changed */
end_comment

begin_define
DECL|macro|NGX_HUNK_MEMORY
define|#
directive|define
name|NGX_HUNK_MEMORY
value|0x0004
end_define

begin_comment
comment|/* the hunk's content is mmap()ed and can not be changed */
end_comment

begin_define
DECL|macro|NGX_HUNK_MMAP
define|#
directive|define
name|NGX_HUNK_MMAP
value|0x0008
end_define

begin_define
DECL|macro|NGX_HUNK_RECYCLED
define|#
directive|define
name|NGX_HUNK_RECYCLED
value|0x0010
end_define

begin_comment
comment|/* the hunk is in file */
end_comment

begin_define
DECL|macro|NGX_HUNK_FILE
define|#
directive|define
name|NGX_HUNK_FILE
value|0x0100
end_define

begin_define
DECL|macro|NGX_HUNK_STORAGE
define|#
directive|define
name|NGX_HUNK_STORAGE
value|(NGX_HUNK_IN_MEMORY                            \                                |NGX_HUNK_TEMP|NGX_HUNK_MEMORY|NGX_HUNK_MMAP  \                                |NGX_HUNK_RECYCLED|NGX_HUNK_FILE)
end_define

begin_comment
comment|/* hunk flags */
end_comment

begin_comment
comment|/* in thread state flush means to write the hunk completely before return */
end_comment

begin_comment
comment|/* in event state flush means to start to write the hunk */
end_comment

begin_define
DECL|macro|NGX_HUNK_FLUSH
define|#
directive|define
name|NGX_HUNK_FLUSH
value|0x1000
end_define

begin_comment
comment|/* last hunk */
end_comment

begin_define
DECL|macro|NGX_HUNK_LAST
define|#
directive|define
name|NGX_HUNK_LAST
value|0x2000
end_define

begin_define
DECL|macro|NGX_HUNK_LAST_SHADOW
define|#
directive|define
name|NGX_HUNK_LAST_SHADOW
value|0x4000
end_define

begin_typedef
DECL|typedef|ngx_hunk_t
typedef|typedef
name|struct
name|ngx_hunk_s
name|ngx_hunk_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_hunk_s
struct|struct
name|ngx_hunk_s
block|{
DECL|member|pos
name|char
modifier|*
name|pos
decl_stmt|;
DECL|member|last
name|char
modifier|*
name|last
decl_stmt|;
DECL|member|file_pos
name|off_t
name|file_pos
decl_stmt|;
DECL|member|file_last
name|off_t
name|file_last
decl_stmt|;
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|member|start
name|char
modifier|*
name|start
decl_stmt|;
comment|/* start of hunk */
DECL|member|end
name|char
modifier|*
name|end
decl_stmt|;
comment|/* end of hunk */
DECL|member|pre_start
name|char
modifier|*
name|pre_start
decl_stmt|;
comment|/* start of pre-allocated hunk */
DECL|member|post_end
name|char
modifier|*
name|post_end
decl_stmt|;
comment|/* end of post-allocated hunk */
DECL|member|tag
name|int
name|tag
decl_stmt|;
DECL|member|file
name|ngx_file_t
modifier|*
name|file
decl_stmt|;
DECL|member|shadow
name|ngx_hunk_t
modifier|*
name|shadow
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|ngx_chain_t
typedef|typedef
name|struct
name|ngx_chain_s
name|ngx_chain_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_chain_s
struct|struct
name|ngx_chain_s
block|{
DECL|member|hunk
name|ngx_hunk_t
modifier|*
name|hunk
decl_stmt|;
DECL|member|next
name|ngx_chain_t
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon27d93d6c0108
typedef|typedef
struct|struct
block|{
DECL|member|num
name|int
name|num
decl_stmt|;
DECL|member|size
name|ssize_t
name|size
decl_stmt|;
DECL|typedef|ngx_bufs_t
block|}
name|ngx_bufs_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_CHAIN_ERROR
define|#
directive|define
name|NGX_CHAIN_ERROR
value|(ngx_chain_t *) NGX_ERROR
end_define

begin_define
DECL|macro|ngx_hunk_in_memory_only (h)
define|#
directive|define
name|ngx_hunk_in_memory_only
parameter_list|(
name|h
parameter_list|)
define|\
value|((h->type& (NGX_HUNK_IN_MEMORY|NGX_HUNK_FILE)) == NGX_HUNK_IN_MEMORY)
end_define

begin_comment
comment|/*     ((h->type& (NGX_HUNK_TEMP|NGX_HUNK_MEMORY|NGX_HUNK_MMAP|NGX_HUNK_FILE)) \                   == (h->type& (NGX_HUNK_TEMP|NGX_HUNK_MEMORY|NGX_HUNK_MMAP)))  */
end_comment

begin_define
DECL|macro|ngx_hunk_special (h)
define|#
directive|define
name|ngx_hunk_special
parameter_list|(
name|h
parameter_list|)
define|\
value|(h->type == (h->type& (NGX_HUNK_FLUSH|NGX_HUNK_LAST)))
end_define

begin_function_decl
name|ngx_hunk_t
modifier|*
name|ngx_create_temp_hunk
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|int
name|size
parameter_list|,
name|int
name|before
parameter_list|,
name|int
name|after
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_alloc_hunk (pool)
define|#
directive|define
name|ngx_alloc_hunk
parameter_list|(
name|pool
parameter_list|)
value|ngx_palloc(pool, sizeof(ngx_hunk_t))
end_define

begin_define
DECL|macro|ngx_calloc_hunk (pool)
define|#
directive|define
name|ngx_calloc_hunk
parameter_list|(
name|pool
parameter_list|)
value|ngx_pcalloc(pool, sizeof(ngx_hunk_t))
end_define

begin_define
DECL|macro|ngx_alloc_chain_entry (pool)
define|#
directive|define
name|ngx_alloc_chain_entry
parameter_list|(
name|pool
parameter_list|)
value|ngx_palloc(pool, sizeof(ngx_chain_t))
end_define

begin_define
DECL|macro|ngx_add_hunk_to_chain (chain,h,pool,error)
define|#
directive|define
name|ngx_add_hunk_to_chain
parameter_list|(
name|chain
parameter_list|,
name|h
parameter_list|,
name|pool
parameter_list|,
name|error
parameter_list|)
define|\
value|do {                                                             \                 ngx_test_null(chain, ngx_alloc_chain_entry(pool), error);    \                 chain->hunk = h;                                             \                 chain->next = NULL;                                          \             } while (0);
end_define

begin_define
DECL|macro|ngx_alloc_ce_and_set_hunk
define|#
directive|define
name|ngx_alloc_ce_and_set_hunk
value|ngx_add_hunk_to_chain
end_define

begin_define
DECL|macro|ngx_chain_add_ce (ngx_chain_t,chain,ngx_chain_t,last,ngx_chain_t,ce)
define|#
directive|define
name|ngx_chain_add_ce
parameter_list|(
name|ngx_chain_t
modifier|*
name|chain
parameter|,
name|ngx_chain_t
modifier|*
modifier|*
name|last
parameter|,             \
name|ngx_chain_t
modifier|*
name|ce
parameter_list|)
define|\
value|if (chain) {                                                     \                 last->next = ce;                                             \             } else {                                                         \                 chain = ce;                                                  \             }                                                                \             last = ce;
end_define

begin_function_decl
name|int
name|ngx_chain_add_copy
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_chain_t
modifier|*
modifier|*
name|ch
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_chain_update_chains
parameter_list|(
name|ngx_chain_t
modifier|*
modifier|*
name|free
parameter_list|,
name|ngx_chain_t
modifier|*
modifier|*
name|busy
parameter_list|,
name|ngx_chain_t
modifier|*
modifier|*
name|out
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HUNK_H_INCLUDED_ */
end_comment

end_unit

