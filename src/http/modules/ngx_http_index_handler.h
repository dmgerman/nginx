begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_INDEX_HANDLER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_INDEX_HANDLER_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_INDEX_HANDLER_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_array.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_INDEX
define|#
directive|define
name|NGX_HTTP_INDEX
value|"index.html"
end_define

begin_typedef
DECL|struct|__anon2895264c0108
typedef|typedef
struct|struct
block|{
DECL|member|indices
name|ngx_array_t
modifier|*
name|indices
decl_stmt|;
DECL|member|max_index_len
name|size_t
name|max_index_len
decl_stmt|;
DECL|typedef|ngx_http_index_conf_t
block|}
name|ngx_http_index_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2895264c0208
typedef|typedef
struct|struct
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|len
name|size_t
name|len
decl_stmt|;
DECL|typedef|ngx_http_index_file_t
block|}
name|ngx_http_index_file_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_http_module_t
name|ngx_http_index_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_INDEX_HANDLER_H_INCLUDED_ */
end_comment

end_unit

