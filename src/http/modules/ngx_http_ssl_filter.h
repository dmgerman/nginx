begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_SSL_FILTER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_SSL_FILTER_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_SSL_FILTER_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<openssl/ssl.h>
end_include

begin_function_decl
name|ngx_int_t
name|ngx_http_ssl_read
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_ssl_close_request
parameter_list|(
name|SSL
modifier|*
name|ssl
parameter_list|,
name|int
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_SSL_FILTER_H_INCLUDED_ */
end_comment

end_unit

