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

begin_typedef
DECL|struct|__anon27c5e4120108
typedef|typedef
struct|struct
block|{
DECL|member|ssl
name|SSL
modifier|*
name|ssl
decl_stmt|;
DECL|member|buf
name|ngx_buf_t
modifier|*
name|buf
decl_stmt|;
DECL|member|saved_handler
name|ngx_event_handler_pt
name|saved_handler
decl_stmt|;
DECL|member|buffer
name|unsigned
name|buffer
range|:
literal|1
decl_stmt|;
DECL|member|no_rcv_shut
name|unsigned
name|no_rcv_shut
range|:
literal|1
decl_stmt|;
DECL|member|no_send_shut
name|unsigned
name|no_send_shut
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_ssl_t
block|}
name|ngx_ssl_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_ssl_ctx_t
typedef|typedef
name|SSL_CTX
name|ngx_ssl_ctx_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_SSL_BUFFER
define|#
directive|define
name|NGX_SSL_BUFFER
value|1
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
name|ngx_ssl_create_session
parameter_list|(
name|ngx_ssl_ctx_t
modifier|*
name|ctx
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

begin_define
DECL|macro|ngx_ssl_handshake (c)
define|#
directive|define
name|ngx_ssl_handshake
parameter_list|(
name|c
parameter_list|)
value|NGX_OK
end_define

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

begin_define
DECL|macro|ngx_ssl_set_nosendshut (ssl)
define|#
directive|define
name|ngx_ssl_set_nosendshut
parameter_list|(
name|ssl
parameter_list|)
define|\
value|if (ssl) {                                                       \                 ssl->no_send_shut = 1;                                       \             }
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_OPENSSL_H_INCLUDED_ */
end_comment

end_unit

