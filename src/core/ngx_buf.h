begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_BUF_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_BUF_H_INCLUDED_
define|#
directive|define
name|_NGX_BUF_H_INCLUDED_
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
literal|0
end_if

begin_comment
comment|/* the buf type */
end_comment

begin_comment
comment|/* the buf's content is in memory */
end_comment

begin_define
define|#
directive|define
name|NGX_HUNK_IN_MEMORY
value|0x0001
end_define

begin_comment
comment|/* the buf's content can be changed */
end_comment

begin_define
define|#
directive|define
name|NGX_HUNK_TEMP
value|0x0002
end_define

begin_comment
comment|/* the buf's content is in cache and can not be changed */
end_comment

begin_define
define|#
directive|define
name|NGX_HUNK_MEMORY
value|0x0004
end_define

begin_define
define|#
directive|define
name|NGX_HUNK_MMAP
value|0x0008
end_define

begin_comment
comment|/* the buf's content is recycled */
end_comment

begin_define
define|#
directive|define
name|NGX_HUNK_RECYCLED
value|0x0010
end_define

begin_comment
comment|/* the buf's content is in a file */
end_comment

begin_define
define|#
directive|define
name|NGX_HUNK_FILE
value|0x0020
end_define

begin_define
define|#
directive|define
name|NGX_HUNK_STORAGE
value|(NGX_HUNK_IN_MEMORY                            \                                |NGX_HUNK_TEMP|NGX_HUNK_MEMORY|NGX_HUNK_MMAP  \                                |NGX_HUNK_RECYCLED|NGX_HUNK_FILE)
end_define

begin_comment
comment|/* the buf flags */
end_comment

begin_comment
comment|/* in thread state flush means to write the buf completely before return */
end_comment

begin_comment
comment|/* in event state flush means to start to write the buf */
end_comment

begin_define
define|#
directive|define
name|NGX_HUNK_FLUSH
value|0x0100
end_define

begin_comment
comment|/* the last buf */
end_comment

begin_define
define|#
directive|define
name|NGX_HUNK_LAST
value|0x0200
end_define

begin_define
define|#
directive|define
name|NGX_HUNK_PREREAD
value|0x2000
end_define

begin_define
define|#
directive|define
name|NGX_HUNK_LAST_SHADOW
value|0x4000
end_define

begin_define
define|#
directive|define
name|NGX_HUNK_TEMP_FILE
value|0x8000
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_buf_tag_t
typedef|typedef
name|void
modifier|*
name|ngx_buf_tag_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_buf_t
typedef|typedef
name|struct
name|ngx_buf_s
name|ngx_buf_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_buf_s
struct|struct
name|ngx_buf_s
block|{
DECL|member|pos
name|u_char
modifier|*
name|pos
decl_stmt|;
DECL|member|last
name|u_char
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
name|u_char
modifier|*
name|start
decl_stmt|;
comment|/* start of buffer */
DECL|member|end
name|u_char
modifier|*
name|end
decl_stmt|;
comment|/* end of buffer */
DECL|member|tag
name|ngx_buf_tag_t
name|tag
decl_stmt|;
DECL|member|file
name|ngx_file_t
modifier|*
name|file
decl_stmt|;
DECL|member|shadow
name|ngx_buf_t
modifier|*
name|shadow
decl_stmt|;
comment|/* the buf's content can be changed */
DECL|member|temporary
name|unsigned
name|temporary
range|:
literal|1
decl_stmt|;
comment|/*      * the buf's content is in a memory cache or in a read only memory      * and can not be changed      */
DECL|member|memory
name|unsigned
name|memory
range|:
literal|1
decl_stmt|;
comment|/* the buf's content is mmap()ed and can not be changed */
DECL|member|mmap
name|unsigned
name|mmap
range|:
literal|1
decl_stmt|;
DECL|member|recycled
name|unsigned
name|recycled
range|:
literal|1
decl_stmt|;
DECL|member|in_file
name|unsigned
name|in_file
range|:
literal|1
decl_stmt|;
DECL|member|flush
name|unsigned
name|flush
range|:
literal|1
decl_stmt|;
DECL|member|last_buf
name|unsigned
name|last_buf
range|:
literal|1
decl_stmt|;
DECL|member|last_shadow
name|unsigned
name|last_shadow
range|:
literal|1
decl_stmt|;
DECL|member|temp_file
name|unsigned
name|temp_file
range|:
literal|1
decl_stmt|;
DECL|member|zerocopy_busy
name|unsigned
name|zerocopy_busy
range|:
literal|1
decl_stmt|;
DECL|member|num
comment|/* STUB */
name|int
name|num
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
DECL|member|buf
name|ngx_buf_t
modifier|*
name|buf
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
DECL|struct|__anon29c5d6240108
typedef|typedef
struct|struct
block|{
DECL|member|num
name|ngx_int_t
name|num
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|typedef|ngx_bufs_t
block|}
name|ngx_bufs_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_output_chain_filter_pt
typedef|typedef
name|int
function_decl|(
modifier|*
name|ngx_output_chain_filter_pt
function_decl|)
parameter_list|(
name|void
modifier|*
name|ctx
parameter_list|,
name|ngx_chain_t
modifier|*
name|out
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon29c5d6240208
typedef|typedef
struct|struct
block|{
DECL|member|buf
name|ngx_buf_t
modifier|*
name|buf
decl_stmt|;
DECL|member|in
name|ngx_chain_t
modifier|*
name|in
decl_stmt|;
DECL|member|free
name|ngx_chain_t
modifier|*
name|free
decl_stmt|;
DECL|member|busy
name|ngx_chain_t
modifier|*
name|busy
decl_stmt|;
DECL|member|sendfile
name|unsigned
name|sendfile
decl_stmt|;
DECL|member|need_in_memory
name|unsigned
name|need_in_memory
decl_stmt|;
DECL|member|need_in_temp
name|unsigned
name|need_in_temp
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|allocated
name|ngx_int_t
name|allocated
decl_stmt|;
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
DECL|member|tag
name|ngx_buf_tag_t
name|tag
decl_stmt|;
DECL|member|output_filter
name|ngx_output_chain_filter_pt
name|output_filter
decl_stmt|;
DECL|member|filter_ctx
name|void
modifier|*
name|filter_ctx
decl_stmt|;
DECL|typedef|ngx_output_chain_ctx_t
block|}
name|ngx_output_chain_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29c5d6240308
typedef|typedef
struct|struct
block|{
DECL|member|out
name|ngx_chain_t
modifier|*
name|out
decl_stmt|;
DECL|member|last
name|ngx_chain_t
modifier|*
modifier|*
name|last
decl_stmt|;
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|typedef|ngx_chain_writer_ctx_t
block|}
name|ngx_chain_writer_ctx_t
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
DECL|macro|ngx_buf_in_memory (b)
define|#
directive|define
name|ngx_buf_in_memory
parameter_list|(
name|b
parameter_list|)
value|(b->temporary || b->memory || b->mmap)
end_define

begin_define
DECL|macro|ngx_buf_in_memory_only (b)
define|#
directive|define
name|ngx_buf_in_memory_only
parameter_list|(
name|b
parameter_list|)
value|(ngx_buf_in_memory(b)&& !b->in_file)
end_define

begin_define
DECL|macro|ngx_buf_special (b)
define|#
directive|define
name|ngx_buf_special
parameter_list|(
name|b
parameter_list|)
define|\
value|((b->flush || b->last)&& !ngx_buf_in_memory(b)&& !b->in_file)
end_define

begin_define
DECL|macro|ngx_buf_size (b)
define|#
directive|define
name|ngx_buf_size
parameter_list|(
name|b
parameter_list|)
define|\
value|(ngx_buf_in_memory(b) ? (size_t) (b->last - b->pos):                 \                                 (size_t) (b->file_last - b->file_pos))
end_define

begin_function_decl
name|ngx_buf_t
modifier|*
name|ngx_create_temp_buf
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
name|ngx_chain_t
modifier|*
name|ngx_create_chain_of_bufs
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_bufs_t
modifier|*
name|bufs
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_alloc_buf (pool)
define|#
directive|define
name|ngx_alloc_buf
parameter_list|(
name|pool
parameter_list|)
value|ngx_palloc(pool, sizeof(ngx_buf_t))
end_define

begin_define
DECL|macro|ngx_calloc_buf (pool)
define|#
directive|define
name|ngx_calloc_buf
parameter_list|(
name|pool
parameter_list|)
value|ngx_pcalloc(pool, sizeof(ngx_buf_t))
end_define

begin_define
DECL|macro|ngx_alloc_chain_link (pool)
define|#
directive|define
name|ngx_alloc_chain_link
parameter_list|(
name|pool
parameter_list|)
value|ngx_palloc(pool, sizeof(ngx_chain_t))
end_define

begin_define
DECL|macro|ngx_alloc_link_and_set_buf (chain,b,pool,error)
define|#
directive|define
name|ngx_alloc_link_and_set_buf
parameter_list|(
name|chain
parameter_list|,
name|b
parameter_list|,
name|pool
parameter_list|,
name|error
parameter_list|)
define|\
value|do {                                                             \                 ngx_test_null(chain, ngx_alloc_chain_link(pool), error);     \                 chain->buf = b;                                              \                 chain->next = NULL;                                          \             } while (0);
end_define

begin_define
DECL|macro|ngx_chain_add_link (chain,last,cl)
define|#
directive|define
name|ngx_chain_add_link
parameter_list|(
name|chain
parameter_list|,
name|last
parameter_list|,
name|cl
parameter_list|)
define|\
value|if (chain) {                                                     \                 *last = cl;                                                  \             } else {                                                         \                 chain = cl;                                                  \             }                                                                \             last =&cl->next
end_define

begin_function_decl
name|int
name|ngx_output_chain
parameter_list|(
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_chain_writer
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
function_decl|;
end_function_decl

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
name|chain
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
parameter_list|,
name|ngx_buf_tag_t
name|tag
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_BUF_H_INCLUDED_ */
end_comment

end_unit

