begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_LOG_HANDLER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_LOG_HANDLER_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_LOG_HANDLER_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon28a544270108
typedef|typedef
struct|struct
block|{
DECL|member|dummy
name|int
name|dummy
decl_stmt|;
DECL|typedef|ngx_http_log_conf_t
block|}
name|ngx_http_log_conf_t
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon28a544270203
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_HTTP_LOG_HANDLER
name|NGX_HTTP_LOG_HANDLER
init|=
literal|0
block|,
if|#
directive|if
literal|0
comment|/* the ngx_str_t field of the request */
block|NGX_HTTP_LOG_REQUEST_STR_FIELD,
comment|/* the ngx_str_t field of the r->headers_in */
block|NGX_HTTP_LOG_REQUEST_HEADER_IN_FIELD,
comment|/* the ngx_str_t field of the r->headers_out */
block|NGX_HTTP_LOG_REQUEST_HEADER_OUT_FIELD,
endif|#
directive|endif
DECL|typedef|ngx_http_log_code_e
block|}
name|ngx_http_log_code_e
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28a544270308
typedef|typedef
struct|struct
block|{
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|member|size
name|int
name|size
decl_stmt|;
DECL|member|handler
name|char
modifier|*
function_decl|(
modifier|*
name|handler
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|char
modifier|*
name|p
parameter_list|)
function_decl|;
DECL|member|offset
name|int
name|offset
decl_stmt|;
DECL|typedef|ngx_http_log_code_t
block|}
name|ngx_http_log_code_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_LOG_HANDLER_H_INCLUDED_ */
end_comment

end_unit

