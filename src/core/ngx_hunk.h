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
file|<ngx_alloc.h>
end_include

begin_comment
comment|/* type */
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

begin_define
DECL|macro|NGX_HUNK_FLUSH
define|#
directive|define
name|NGX_HUNK_FLUSH
value|0x0010
end_define

begin_comment
comment|/* in thread state flush means to write the hunk completely before return    in event-driven state flush means to start to write the hunk */
end_comment

begin_define
DECL|macro|NGX_HUNK_LAST
define|#
directive|define
name|NGX_HUNK_LAST
value|0x0020
end_define

begin_define
DECL|macro|NGX_HUNK_IN_MEMORY
define|#
directive|define
name|NGX_HUNK_IN_MEMORY
value|(NGX_HUNK_TEMP | NGX_HUNK_MEMORY | NGX_HUNK_MMAP )
end_define

begin_define
DECL|macro|NGX_HUNK_TYPE
define|#
directive|define
name|NGX_HUNK_TYPE
value|0x0ffff
end_define

begin_comment
comment|/* flags */
end_comment

begin_define
DECL|macro|NGX_HUNK_SHUTDOWN
define|#
directive|define
name|NGX_HUNK_SHUTDOWN
value|0x10000
end_define

begin_comment
comment|/* can be used with NGX_HUNK_LAST only */
end_comment

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
DECL|union|__anon28890fee010a
union|union
block|{
DECL|member|p
name|char
modifier|*
name|p
decl_stmt|;
comment|/* start of current data */
DECL|member|f
name|off_t
name|f
decl_stmt|;
DECL|member|pos
block|}
name|pos
union|;
DECL|union|__anon28890fee020a
union|union
block|{
DECL|member|p
name|char
modifier|*
name|p
decl_stmt|;
comment|/* end of current data */
DECL|member|f
name|off_t
name|f
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

