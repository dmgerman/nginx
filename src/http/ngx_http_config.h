begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_CONFIG_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_LOC_CONF
define|#
directive|define
name|NGX_HTTP_LOC_CONF
value|0
end_define

begin_function_decl
name|int
name|ngx_http_config_modules
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_http_module_t
modifier|*
modifier|*
name|modules
parameter_list|)
function_decl|;
end_function_decl

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
name|void
modifier|*
modifier|*
name|ngx_srv_conf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|void
modifier|*
modifier|*
name|ngx_loc_conf
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
endif|_NGX_HTTP_CONFIG_H_INCLUDED_
end_endif

end_unit

