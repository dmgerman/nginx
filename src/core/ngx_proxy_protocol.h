begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Roman Arutyunyan  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_PROXY_PROTOCOL_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_PROXY_PROTOCOL_H_INCLUDED_
define|#
directive|define
name|_NGX_PROXY_PROTOCOL_H_INCLUDED_
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
DECL|macro|NGX_PROXY_PROTOCOL_MAX_HEADER
define|#
directive|define
name|NGX_PROXY_PROTOCOL_MAX_HEADER
value|107
end_define

begin_function_decl
name|u_char
modifier|*
name|ngx_proxy_protocol_parse
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PROXY_PROTOCOL_H_INCLUDED_ */
end_comment

end_unit

