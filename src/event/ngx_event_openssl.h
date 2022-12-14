begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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

begin_define
DECL|macro|OPENSSL_SUPPRESS_DEPRECATED
define|#
directive|define
name|OPENSSL_SUPPRESS_DEPRECATED
end_define

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

begin_include
include|#
directive|include
file|<openssl/bn.h>
end_include

begin_include
include|#
directive|include
file|<openssl/conf.h>
end_include

begin_include
include|#
directive|include
file|<openssl/crypto.h>
end_include

begin_include
include|#
directive|include
file|<openssl/dh.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|OPENSSL_NO_ENGINE
end_ifndef

begin_include
include|#
directive|include
file|<openssl/engine.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<openssl/evp.h>
end_include

begin_include
include|#
directive|include
file|<openssl/hmac.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|OPENSSL_NO_OCSP
end_ifndef

begin_include
include|#
directive|include
file|<openssl/ocsp.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<openssl/rand.h>
end_include

begin_include
include|#
directive|include
file|<openssl/x509.h>
end_include

begin_include
include|#
directive|include
file|<openssl/x509v3.h>
end_include

begin_define
DECL|macro|NGX_SSL_NAME
define|#
directive|define
name|NGX_SSL_NAME
value|"OpenSSL"
end_define

begin_if
if|#
directive|if
operator|(
name|defined
name|LIBRESSL_VERSION_NUMBER
operator|&&
name|OPENSSL_VERSION_NUMBER
operator|==
literal|0x20000000L
operator|)
end_if

begin_undef
undef|#
directive|undef
name|OPENSSL_VERSION_NUMBER
end_undef

begin_if
if|#
directive|if
operator|(
name|LIBRESSL_VERSION_NUMBER
operator|>=
literal|0x2080000fL
operator|)
end_if

begin_define
DECL|macro|OPENSSL_VERSION_NUMBER
define|#
directive|define
name|OPENSSL_VERSION_NUMBER
value|0x1010000fL
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|OPENSSL_VERSION_NUMBER
define|#
directive|define
name|OPENSSL_VERSION_NUMBER
value|0x1000107fL
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|OPENSSL_VERSION_NUMBER
operator|>=
literal|0x10100001L
operator|)
end_if

begin_define
DECL|macro|ngx_ssl_version ()
define|#
directive|define
name|ngx_ssl_version
parameter_list|()
value|OpenSSL_version(OPENSSL_VERSION)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_ssl_version ()
define|#
directive|define
name|ngx_ssl_version
parameter_list|()
value|SSLeay_version(SSLEAY_VERSION)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_ssl_session_t
define|#
directive|define
name|ngx_ssl_session_t
value|SSL_SESSION
end_define

begin_define
DECL|macro|ngx_ssl_conn_t
define|#
directive|define
name|ngx_ssl_conn_t
value|SSL
end_define

begin_if
if|#
directive|if
operator|(
name|OPENSSL_VERSION_NUMBER
operator|<
literal|0x10002000L
operator|)
end_if

begin_define
DECL|macro|SSL_is_server (s)
define|#
directive|define
name|SSL_is_server
parameter_list|(
name|s
parameter_list|)
value|(s)->server
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|OPENSSL_VERSION_NUMBER
operator|>=
literal|0x30000000L
operator|&&
operator|!
name|defined
name|SSL_get_peer_certificate
operator|)
end_if

begin_define
DECL|macro|SSL_get_peer_certificate (s)
define|#
directive|define
name|SSL_get_peer_certificate
parameter_list|(
name|s
parameter_list|)
value|SSL_get1_peer_certificate(s)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|OPENSSL_VERSION_NUMBER
operator|<
literal|0x30000000L
operator|&&
operator|!
name|defined
name|ERR_peek_error_data
operator|)
end_if

begin_define
DECL|macro|ERR_peek_error_data (d,f)
define|#
directive|define
name|ERR_peek_error_data
parameter_list|(
name|d
parameter_list|,
name|f
parameter_list|)
value|ERR_peek_error_line_data(NULL, NULL, d, f)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_ssl_ocsp_t
typedef|typedef
name|struct
name|ngx_ssl_ocsp_s
name|ngx_ssl_ocsp_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_ssl_s
struct|struct
name|ngx_ssl_s
block|{
DECL|member|ctx
name|SSL_CTX
modifier|*
name|ctx
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|buffer_size
name|size_t
name|buffer_size
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|ngx_ssl_connection_s
struct|struct
name|ngx_ssl_connection_s
block|{
DECL|member|connection
name|ngx_ssl_conn_t
modifier|*
name|connection
decl_stmt|;
DECL|member|session_ctx
name|SSL_CTX
modifier|*
name|session_ctx
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
DECL|member|buffer_size
name|size_t
name|buffer_size
decl_stmt|;
DECL|member|handler
name|ngx_connection_handler_pt
name|handler
decl_stmt|;
DECL|member|session
name|ngx_ssl_session_t
modifier|*
name|session
decl_stmt|;
DECL|member|save_session
name|ngx_connection_handler_pt
name|save_session
decl_stmt|;
DECL|member|saved_read_handler
name|ngx_event_handler_pt
name|saved_read_handler
decl_stmt|;
DECL|member|saved_write_handler
name|ngx_event_handler_pt
name|saved_write_handler
decl_stmt|;
DECL|member|ocsp
name|ngx_ssl_ocsp_t
modifier|*
name|ocsp
decl_stmt|;
DECL|member|early_buf
name|u_char
name|early_buf
decl_stmt|;
DECL|member|handshaked
name|unsigned
name|handshaked
range|:
literal|1
decl_stmt|;
DECL|member|handshake_rejected
name|unsigned
name|handshake_rejected
range|:
literal|1
decl_stmt|;
DECL|member|renegotiation
name|unsigned
name|renegotiation
range|:
literal|1
decl_stmt|;
DECL|member|buffer
name|unsigned
name|buffer
range|:
literal|1
decl_stmt|;
DECL|member|sendfile
name|unsigned
name|sendfile
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
DECL|member|shutdown_without_free
name|unsigned
name|shutdown_without_free
range|:
literal|1
decl_stmt|;
DECL|member|handshake_buffer_set
name|unsigned
name|handshake_buffer_set
range|:
literal|1
decl_stmt|;
DECL|member|session_timeout_set
name|unsigned
name|session_timeout_set
range|:
literal|1
decl_stmt|;
DECL|member|try_early_data
name|unsigned
name|try_early_data
range|:
literal|1
decl_stmt|;
DECL|member|in_early
name|unsigned
name|in_early
range|:
literal|1
decl_stmt|;
DECL|member|in_ocsp
name|unsigned
name|in_ocsp
range|:
literal|1
decl_stmt|;
DECL|member|early_preread
name|unsigned
name|early_preread
range|:
literal|1
decl_stmt|;
DECL|member|write_blocked
name|unsigned
name|write_blocked
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|NGX_SSL_NO_SCACHE
define|#
directive|define
name|NGX_SSL_NO_SCACHE
value|-2
end_define

begin_define
DECL|macro|NGX_SSL_NONE_SCACHE
define|#
directive|define
name|NGX_SSL_NONE_SCACHE
value|-3
end_define

begin_define
DECL|macro|NGX_SSL_NO_BUILTIN_SCACHE
define|#
directive|define
name|NGX_SSL_NO_BUILTIN_SCACHE
value|-4
end_define

begin_define
DECL|macro|NGX_SSL_DFLT_BUILTIN_SCACHE
define|#
directive|define
name|NGX_SSL_DFLT_BUILTIN_SCACHE
value|-5
end_define

begin_define
DECL|macro|NGX_SSL_MAX_SESSION_SIZE
define|#
directive|define
name|NGX_SSL_MAX_SESSION_SIZE
value|4096
end_define

begin_typedef
DECL|typedef|ngx_ssl_sess_id_t
typedef|typedef
name|struct
name|ngx_ssl_sess_id_s
name|ngx_ssl_sess_id_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_ssl_sess_id_s
struct|struct
name|ngx_ssl_sess_id_s
block|{
DECL|member|node
name|ngx_rbtree_node_t
name|node
decl_stmt|;
DECL|member|len
name|size_t
name|len
decl_stmt|;
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
DECL|member|expire
name|time_t
name|expire
decl_stmt|;
DECL|member|id
name|u_char
name|id
index|[
literal|32
index|]
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_PTR_SIZE
operator|==
literal|8
operator|)
DECL|member|session
name|u_char
modifier|*
name|session
decl_stmt|;
else|#
directive|else
DECL|member|session
name|u_char
name|session
index|[
literal|1
index|]
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2c2bd3c60108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|u_char
name|name
index|[
literal|16
index|]
decl_stmt|;
DECL|member|hmac_key
name|u_char
name|hmac_key
index|[
literal|32
index|]
decl_stmt|;
DECL|member|aes_key
name|u_char
name|aes_key
index|[
literal|32
index|]
decl_stmt|;
DECL|member|expire
name|time_t
name|expire
decl_stmt|;
DECL|member|size
name|unsigned
name|size
range|:
literal|8
decl_stmt|;
DECL|member|shared
name|unsigned
name|shared
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_ssl_ticket_key_t
block|}
name|ngx_ssl_ticket_key_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c2bd3c60208
typedef|typedef
struct|struct
block|{
DECL|member|session_rbtree
name|ngx_rbtree_t
name|session_rbtree
decl_stmt|;
DECL|member|sentinel
name|ngx_rbtree_node_t
name|sentinel
decl_stmt|;
DECL|member|expire_queue
name|ngx_queue_t
name|expire_queue
decl_stmt|;
DECL|member|ticket_keys
name|ngx_ssl_ticket_key_t
name|ticket_keys
index|[
literal|3
index|]
decl_stmt|;
DECL|member|fail_time
name|time_t
name|fail_time
decl_stmt|;
DECL|typedef|ngx_ssl_session_cache_t
block|}
name|ngx_ssl_session_cache_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_SSL_SSLv2
define|#
directive|define
name|NGX_SSL_SSLv2
value|0x0002
end_define

begin_define
DECL|macro|NGX_SSL_SSLv3
define|#
directive|define
name|NGX_SSL_SSLv3
value|0x0004
end_define

begin_define
DECL|macro|NGX_SSL_TLSv1
define|#
directive|define
name|NGX_SSL_TLSv1
value|0x0008
end_define

begin_define
DECL|macro|NGX_SSL_TLSv1_1
define|#
directive|define
name|NGX_SSL_TLSv1_1
value|0x0010
end_define

begin_define
DECL|macro|NGX_SSL_TLSv1_2
define|#
directive|define
name|NGX_SSL_TLSv1_2
value|0x0020
end_define

begin_define
DECL|macro|NGX_SSL_TLSv1_3
define|#
directive|define
name|NGX_SSL_TLSv1_3
value|0x0040
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
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_certificates
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_array_t
modifier|*
name|certs
parameter_list|,
name|ngx_array_t
modifier|*
name|keys
parameter_list|,
name|ngx_array_t
modifier|*
name|passwords
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
parameter_list|,
name|ngx_array_t
modifier|*
name|passwords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_connection_certificate
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|cert
parameter_list|,
name|ngx_str_t
modifier|*
name|key
parameter_list|,
name|ngx_array_t
modifier|*
name|passwords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_ciphers
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
name|ciphers
parameter_list|,
name|ngx_uint_t
name|prefer_server_ciphers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_client_certificate
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
name|ngx_int_t
name|depth
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_trusted_certificate
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
name|ngx_int_t
name|depth
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_crl
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
name|crl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_stapling
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
name|file
parameter_list|,
name|ngx_str_t
modifier|*
name|responder
parameter_list|,
name|ngx_uint_t
name|verify
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_stapling_resolver
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_resolver_t
modifier|*
name|resolver
parameter_list|,
name|ngx_msec_t
name|resolver_timeout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_ocsp
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
name|responder
parameter_list|,
name|ngx_uint_t
name|depth
parameter_list|,
name|ngx_shm_zone_t
modifier|*
name|shm_zone
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_ocsp_resolver
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_resolver_t
modifier|*
name|resolver
parameter_list|,
name|ngx_msec_t
name|resolver_timeout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_ocsp_validate
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_ocsp_get_status
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
specifier|const
name|char
modifier|*
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_ssl_ocsp_cleanup
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_ocsp_cache_init
parameter_list|(
name|ngx_shm_zone_t
modifier|*
name|shm_zone
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_array_t
modifier|*
name|ngx_ssl_read_password_file
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_str_t
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_array_t
modifier|*
name|ngx_ssl_preserve_passwords
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_array_t
modifier|*
name|passwords
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_dhparam
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
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_ecdh_curve
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
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_early_data
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_uint_t
name|enable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_conf_commands
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_array_t
modifier|*
name|commands
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_client_session_cache
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_uint_t
name|enable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_session_cache
parameter_list|(
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_str_t
modifier|*
name|sess_ctx
parameter_list|,
name|ngx_array_t
modifier|*
name|certificates
parameter_list|,
name|ssize_t
name|builtin_session_cache
parameter_list|,
name|ngx_shm_zone_t
modifier|*
name|shm_zone
parameter_list|,
name|time_t
name|timeout
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_session_ticket_keys
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_array_t
modifier|*
name|paths
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_session_cache_init
parameter_list|(
name|ngx_shm_zone_t
modifier|*
name|shm_zone
parameter_list|,
name|void
modifier|*
name|data
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
name|void
name|ngx_ssl_remove_cached_session
parameter_list|(
name|SSL_CTX
modifier|*
name|ssl
parameter_list|,
name|ngx_ssl_session_t
modifier|*
name|sess
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

begin_function_decl
name|ngx_ssl_session_t
modifier|*
name|ngx_ssl_get_session
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_ssl_session_t
modifier|*
name|ngx_ssl_get0_session
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_ssl_free_session
define|#
directive|define
name|ngx_ssl_free_session
value|SSL_SESSION_free
end_define

begin_define
DECL|macro|ngx_ssl_get_connection (ssl_conn)
define|#
directive|define
name|ngx_ssl_get_connection
parameter_list|(
name|ssl_conn
parameter_list|)
define|\
value|SSL_get_ex_data(ssl_conn, ngx_ssl_connection_index)
end_define

begin_define
DECL|macro|ngx_ssl_get_server_conf (ssl_ctx)
define|#
directive|define
name|ngx_ssl_get_server_conf
parameter_list|(
name|ssl_ctx
parameter_list|)
define|\
value|SSL_CTX_get_ex_data(ssl_ctx, ngx_ssl_server_conf_index)
end_define

begin_define
DECL|macro|ngx_ssl_verify_error_optional (n)
define|#
directive|define
name|ngx_ssl_verify_error_optional
parameter_list|(
name|n
parameter_list|)
define|\
value|(n == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT                              \      || n == X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN                             \      || n == X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY                     \      || n == X509_V_ERR_CERT_UNTRUSTED                                        \      || n == X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE)
end_define

begin_function_decl
name|ngx_int_t
name|ngx_ssl_check_host
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_protocol
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_cipher_name
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_ciphers
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_curve
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_curves
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_session_id
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_session_reused
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_early_data
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_server_name
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_alpn_protocol
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_raw_certificate
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_certificate
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_escaped_certificate
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_subject_dn
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_issuer_dn
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_subject_dn_legacy
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_issuer_dn_legacy
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_serial_number
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_fingerprint
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_client_verify
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_client_v_start
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_client_v_end
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ssl_get_client_v_remain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

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
parameter_list|,
name|off_t
name|limit
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
name|void
name|ngx_ssl_free_buffer
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
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

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_connection_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_server_conf_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_session_cache_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_ticket_keys_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_ocsp_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_certificate_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_next_certificate_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_certificate_name_index
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_ssl_stapling_index
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_OPENSSL_H_INCLUDED_ */
end_comment

end_unit

