begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_SSL_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_SSL_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_SSL_H_INCLUDED_
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
DECL|struct|__anon291b191d0108
typedef|typedef
struct|struct
block|{
DECL|member|enable
name|ngx_flag_t
name|enable
decl_stmt|;
DECL|member|certificate
name|ngx_str_t
name|certificate
decl_stmt|;
DECL|member|certificate_key
name|ngx_str_t
name|certificate_key
decl_stmt|;
DECL|member|ssl_ctx
name|ngx_ssl_ctx_t
modifier|*
name|ssl_ctx
decl_stmt|;
DECL|typedef|ngx_http_ssl_srv_conf_t
block|}
name|ngx_http_ssl_srv_conf_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_http_ssl_read
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_ssl_shutdown
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_chain_t
modifier|*
name|ngx_http_ssl_write
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|,
name|off_t
name|limit
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_ssl_close_connection
parameter_list|(
name|SSL
modifier|*
name|ssl
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_ssl_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_SSL_H_INCLUDED_ */
end_comment

end_unit

