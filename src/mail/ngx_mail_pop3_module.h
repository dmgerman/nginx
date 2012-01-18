begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_MAIL_POP3_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_MAIL_POP3_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_MAIL_POP3_MODULE_H_INCLUDED_
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
file|<ngx_mail.h>
end_include

begin_typedef
DECL|struct|__anon297aba8a0108
typedef|typedef
struct|struct
block|{
DECL|member|capability
name|ngx_str_t
name|capability
decl_stmt|;
DECL|member|starttls_capability
name|ngx_str_t
name|starttls_capability
decl_stmt|;
DECL|member|starttls_only_capability
name|ngx_str_t
name|starttls_only_capability
decl_stmt|;
DECL|member|auth_capability
name|ngx_str_t
name|auth_capability
decl_stmt|;
DECL|member|auth_methods
name|ngx_uint_t
name|auth_methods
decl_stmt|;
DECL|member|capabilities
name|ngx_array_t
name|capabilities
decl_stmt|;
DECL|typedef|ngx_mail_pop3_srv_conf_t
block|}
name|ngx_mail_pop3_srv_conf_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_mail_pop3_init_session
parameter_list|(
name|ngx_mail_session_t
modifier|*
name|s
parameter_list|,
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_mail_pop3_init_protocol
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_mail_pop3_auth_state
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_mail_pop3_parse_command
parameter_list|(
name|ngx_mail_session_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_mail_pop3_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_MAIL_POP3_MODULE_H_INCLUDED_ */
end_comment

end_unit

