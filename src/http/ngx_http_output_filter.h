begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_OUTPUT_FILTER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_OUTPUT_FILTER_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_OUTPUT_FILTER_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_conf_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_FILTER_NEED_IN_MEMORY
define|#
directive|define
name|NGX_HTTP_FILTER_NEED_IN_MEMORY
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_FILTER_NEED_TEMP
define|#
directive|define
name|NGX_HTTP_FILTER_NEED_TEMP
value|2
end_define

begin_typedef
DECL|struct|__anon2976ad250108
typedef|typedef
struct|struct
block|{
DECL|member|hunk_size
name|size_t
name|hunk_size
decl_stmt|;
DECL|typedef|ngx_http_output_filter_conf_t
block|}
name|ngx_http_output_filter_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2976ad250208
typedef|typedef
struct|struct
block|{
DECL|member|hunk
name|ngx_hunk_t
modifier|*
name|hunk
decl_stmt|;
DECL|member|in
name|ngx_chain_t
modifier|*
name|in
decl_stmt|;
DECL|member|out
name|ngx_chain_t
name|out
decl_stmt|;
DECL|member|last
name|unsigned
name|last
decl_stmt|;
DECL|typedef|ngx_http_output_filter_ctx_t
block|}
name|ngx_http_output_filter_ctx_t
typedef|;
end_typedef

begin_function_decl
name|int
name|ngx_http_output_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_hunk_t
modifier|*
name|hunk
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_output_filter_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_OUTPUT_FILTER_H_INCLUDED_ */
end_comment

end_unit

