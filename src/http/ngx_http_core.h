begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_CORE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_CORE_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_CORE_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon279036b70108
typedef|typedef
struct|struct
block|{
DECL|member|dummy
name|int
name|dummy
decl_stmt|;
DECL|typedef|ngx_http_core_conf_t
block|}
name|ngx_http_core_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon279036b70208
typedef|typedef
struct|struct
block|{
DECL|member|dummy
name|int
name|dummy
decl_stmt|;
DECL|typedef|ngx_http_core_srv_conf_t
block|}
name|ngx_http_core_srv_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon279036b70308
typedef|typedef
struct|struct
block|{
DECL|member|send_timeout
name|time_t
name|send_timeout
decl_stmt|;
DECL|typedef|ngx_http_core_loc_conf_t
block|}
name|ngx_http_core_loc_conf_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_http_module_t
name|ngx_http_core_module_ctx
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_core_module
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|extern
name|int
function_decl|(
modifier|*
name|ngx_http_top_header_filter
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|int
name|ngx_http_max_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CORE_H_INCLUDED_ */
end_comment

end_unit

