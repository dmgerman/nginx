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

begin_struct
DECL|struct|ngx_proxy_protocol_s
struct|struct
name|ngx_proxy_protocol_s
block|{
DECL|member|src_addr
name|ngx_str_t
name|src_addr
decl_stmt|;
DECL|member|dst_addr
name|ngx_str_t
name|dst_addr
decl_stmt|;
DECL|member|src_port
name|in_port_t
name|src_port
decl_stmt|;
DECL|member|dst_port
name|in_port_t
name|dst_port
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|u_char
modifier|*
name|ngx_proxy_protocol_read
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

begin_function_decl
name|u_char
modifier|*
name|ngx_proxy_protocol_write
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

