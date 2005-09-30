begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_IMAP_SSL_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_IMAP_SSL_H_INCLUDED_
define|#
directive|define
name|_NGX_IMAP_SSL_H_INCLUDED_
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
file|<ngx_imap.h>
end_include

begin_typedef
DECL|struct|__anon2b216e400108
typedef|typedef
struct|struct
block|{
DECL|member|enable
name|ngx_flag_t
name|enable
decl_stmt|;
DECL|member|ssl
name|ngx_ssl_t
name|ssl
decl_stmt|;
DECL|member|prefer_server_ciphers
name|ngx_flag_t
name|prefer_server_ciphers
decl_stmt|;
DECL|member|protocols
name|ngx_uint_t
name|protocols
decl_stmt|;
DECL|member|certificate
name|ngx_str_t
name|certificate
decl_stmt|;
DECL|member|certificate_key
name|ngx_str_t
name|certificate_key
decl_stmt|;
DECL|member|ciphers
name|ngx_str_t
name|ciphers
decl_stmt|;
DECL|typedef|ngx_imap_ssl_conf_t
block|}
name|ngx_imap_ssl_conf_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_imap_ssl_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_IMAP_SSL_H_INCLUDED_ */
end_comment

end_unit

