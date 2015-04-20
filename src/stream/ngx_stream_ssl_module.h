begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_STREAM_SSL_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_STREAM_SSL_H_INCLUDED_
define|#
directive|define
name|_NGX_STREAM_SSL_H_INCLUDED_
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
file|<ngx_stream.h>
end_include

begin_typedef
DECL|struct|__anon276f02ba0108
typedef|typedef
struct|struct
block|{
DECL|member|handshake_timeout
name|ngx_msec_t
name|handshake_timeout
decl_stmt|;
DECL|member|prefer_server_ciphers
name|ngx_flag_t
name|prefer_server_ciphers
decl_stmt|;
DECL|member|ssl
name|ngx_ssl_t
name|ssl
decl_stmt|;
DECL|member|protocols
name|ngx_uint_t
name|protocols
decl_stmt|;
DECL|member|builtin_session_cache
name|ssize_t
name|builtin_session_cache
decl_stmt|;
DECL|member|session_timeout
name|time_t
name|session_timeout
decl_stmt|;
DECL|member|certificate
name|ngx_str_t
name|certificate
decl_stmt|;
DECL|member|certificate_key
name|ngx_str_t
name|certificate_key
decl_stmt|;
DECL|member|dhparam
name|ngx_str_t
name|dhparam
decl_stmt|;
DECL|member|ecdh_curve
name|ngx_str_t
name|ecdh_curve
decl_stmt|;
DECL|member|ciphers
name|ngx_str_t
name|ciphers
decl_stmt|;
DECL|member|passwords
name|ngx_array_t
modifier|*
name|passwords
decl_stmt|;
DECL|member|shm_zone
name|ngx_shm_zone_t
modifier|*
name|shm_zone
decl_stmt|;
DECL|member|session_tickets
name|ngx_flag_t
name|session_tickets
decl_stmt|;
DECL|member|session_ticket_keys
name|ngx_array_t
modifier|*
name|session_ticket_keys
decl_stmt|;
DECL|typedef|ngx_stream_ssl_conf_t
block|}
name|ngx_stream_ssl_conf_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_stream_ssl_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_STREAM_SSL_H_INCLUDED_ */
end_comment

end_unit

