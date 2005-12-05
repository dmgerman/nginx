begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_OPENSSL_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_OPENSSL_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_OPENSSL_H_INCLUDED_
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
file|<openssl/ssl.h>
end_include

begin_include
include|#
directive|include
file|<openssl/err.h>
end_include

begin_if
if|#
directive|if
name|OPENSSL_VERSION_NUMBER
operator|>=
literal|0x00907000
end_if

begin_include
include|#
directive|include
file|<openssl/engine.h>
end_include

begin_define
DECL|macro|NGX_SSL_ENGINE
define|#
directive|define
name|NGX_SSL_ENGINE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_SSL_NAME
define|#
directive|define
name|NGX_SSL_NAME
value|"OpenSSL"
end_define

begin_typedef
DECL|struct|__anon2b65ea960108
typedef|typedef
struct|struct
block|{
DECL|member|ctx
name|SSL_CTX
modifier|*
name|ctx
decl_stmt|;
DECL|member|rsa512_key
name|RSA
modifier|*
name|rsa512_key
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_ssl_t
block|}
name|ngx_ssl_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b65ea960208
typedef|typedef
struct|struct
block|{
DECL|member|connection
name|SSL
modifier|*
name|connection
decl_stmt|;
DECL|member|last
name|ngx_int_t
name|last
decl_stmt|;
DECL|member|buf
name|ngx_buf_t
modifier|*
name|buf
decl_stmt|;
DECL|member|handler
name|ngx_connection_handler_pt
name|handler
decl_stmt|;
DECL|member|saved_read_handler
name|ngx_event_handler_pt
name|saved_read_handler
decl_stmt|;
DECL|member|saved_write_handler
name|ngx_event_handler_pt
name|saved_write_handler
decl_stmt|;
DECL|member|handshaked
name|unsigned
name|handshaked
range|:
literal|1
decl_stmt|;
DECL|member|buffer
name|unsigned
name|buffer
range|:
literal|1
decl_stmt|;
DECL|member|no_wait_shutdown
name|unsigned
name|no_wait_shutdown
range|:
literal|1
decl_stmt|;
DECL|member|no_send_shutdown
name|unsigned
name|no_send_shutdown
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_ssl_connection_t
block|}
name|ngx_ssl_connection_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_ssl_session_t
define|#
directive|define
name|ngx_ssl_session_t
value|SSL_SESSION
end_define

begin_define
DECL|macro|NGX_SSL_SSLv2
define|#
directive|define
name|NGX_SSL_SSLv2
value|2
end_define

begin_define
DECL|macro|NGX_SSL_SSLv3
define|#
directive|define
name|NGX_SSL_SSLv3
value|4
end_define

begin_define
DECL|macro|NGX_SSL_TLSv1
define|#
directive|define
name|NGX_SSL_TLSv1
value|8
end_define

begin_define
DECL|macro|NGX_SSL_BUFFER
define|#
directive|define
name|NGX_SSL_BUFFER
value|1
end_define

begin_define
DECL|macro|NGX_SSL_CLIENT
define|#
directive|define
name|NGX_SSL_CLIENT
value|2
end_define

begin_define
DECL|macro|NGX_SSL_BUFSIZE
define|#
directive|define
name|NGX_SSL_BUFSIZE
value|16384
end_define

begin_function_decl
name|ngx_int_t
name|ngx_ssl_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_create
parameter_list|(
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_uint_t
name|protocols
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_certificate
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_str_t
modifier|*
name|cert
parameter_list|,
name|ngx_str_t
modifier|*
name|key
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_generate_rsa512_key
parameter_list|(
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_create_connection
parameter_list|(
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_set_session
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_ssl_session_t
modifier|*
name|session
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_ssl_get_session (c)
define|#
directive|define
name|ngx_ssl_get_session
parameter_list|(
name|c
parameter_list|)
value|SSL_get1_session(c->ssl->connection)
end_define

begin_define
DECL|macro|ngx_ssl_free_session
define|#
directive|define
name|ngx_ssl_free_session
value|SSL_SESSION_free
end_define

begin_function_decl
name|ngx_int_t
name|ngx_ssl_handshake
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ssize_t
name|ngx_ssl_recv
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
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
name|ssize_t
name|ngx_ssl_write
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_char
modifier|*
name|data
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ssize_t
name|ngx_ssl_recv_chain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|cl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_chain_t
modifier|*
name|ngx_ssl_send_chain
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
name|ngx_int_t
name|ngx_ssl_shutdown
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_cdecl
name|ngx_ssl_error
parameter_list|(
name|ngx_uint_t
name|level
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|ngx_err_t
name|err
parameter_list|,
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_ssl_cleanup_ctx
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_OPENSSL_H_INCLUDED_ */
end_comment

end_unit

