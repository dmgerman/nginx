begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_CHUNK_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_CHUNK_H_INCLUDED_
define|#
directive|define
name|_NGX_CHUNK_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_comment
comment|/* hunk type */
end_comment

begin_comment
comment|/* temp means that hunk's content can be changed */
end_comment

begin_comment
comment|/* other type means that hunk's content can not be changed */
end_comment

begin_define
DECL|macro|NGX_HUNK_TEMP
define|#
directive|define
name|NGX_HUNK_TEMP
value|0x0001
end_define

begin_define
DECL|macro|NGX_HUNK_MEMORY
define|#
directive|define
name|NGX_HUNK_MEMORY
value|0x0002
end_define

begin_define
DECL|macro|NGX_HUNK_MMAP
define|#
directive|define
name|NGX_HUNK_MMAP
value|0x0004
end_define

begin_define
DECL|macro|NGX_HUNK_FILE
define|#
directive|define
name|NGX_HUNK_FILE
value|0x0008
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
value|0x0100
end_define

begin_comment
comment|/* last hunk */
end_comment

begin_define
DECL|macro|NGX_HUNK_LAST
define|#
directive|define
name|NGX_HUNK_LAST
value|0x0200
end_define

begin_comment
comment|/* can be used with NGX_HUNK_LAST only */
end_comment

begin_define
DECL|macro|NGX_HUNK_SHUTDOWN
define|#
directive|define
name|NGX_HUNK_SHUTDOWN
value|0x0400
end_define

begin_define
DECL|macro|NGX_HUNK_IN_MEMORY
define|#
directive|define
name|NGX_HUNK_IN_MEMORY
value|(NGX_HUNK_TEMP|NGX_HUNK_MEMORY|NGX_HUNK_MMAP)
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
DECL|union|__anon29c6ba7f010a
union|union
block|{
DECL|member|mem
name|char
modifier|*
name|mem
decl_stmt|;
comment|/* start of current data */
DECL|member|file
name|off_t
name|file
decl_stmt|;
DECL|member|pos
block|}
name|pos
union|;
DECL|union|__anon29c6ba7f020a
union|union
block|{
DECL|member|mem
name|char
modifier|*
name|mem
decl_stmt|;
comment|/* end of current data */
DECL|member|file
name|off_t
name|file
decl_stmt|;
DECL|member|last
block|}
name|last
union|;
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
DECL|member|fd
name|ngx_file_t
name|fd
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
value|do {                                                             \                 ngx_test_null(chain, ngx_create_chain_entry(pool), error);   \                 chain->hunk = h;                                             \                 chain->next = NULL;                                          \             } while (0);
end_define

begin_function_decl
name|ngx_hunk_t
modifier|*
name|ngx_get_hunk
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_CHUNK_H_INCLUDED_ */
end_comment

end_unit

