begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_INET_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_INET_H_INCLUDED_
define|#
directive|define
name|_NGX_INET_H_INCLUDED_
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

begin_typedef
DECL|struct|__anon288e01790108
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|mask
name|in_addr_t
name|mask
decl_stmt|;
DECL|typedef|ngx_inet_cidr_t
block|}
name|ngx_inet_cidr_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon288e01790208
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
comment|/* "schema:host:port/uri" */
DECL|member|url
name|ngx_str_t
name|url
decl_stmt|;
comment|/* "host:port/uri" */
DECL|member|host
name|ngx_str_t
name|host
decl_stmt|;
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|host_header
name|ngx_str_t
name|host_header
decl_stmt|;
comment|/* "host:port" */
DECL|member|port_text
name|ngx_str_t
name|port_text
decl_stmt|;
comment|/* "port" */
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|default_port_value
name|in_port_t
name|default_port_value
decl_stmt|;
DECL|member|default_port
name|unsigned
name|default_port
range|:
literal|1
decl_stmt|;
DECL|member|wildcard
name|unsigned
name|wildcard
range|:
literal|1
decl_stmt|;
DECL|member|uri_part
name|unsigned
name|uri_part
range|:
literal|1
decl_stmt|;
DECL|member|port_only
name|unsigned
name|port_only
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_inet_upstream_t
block|}
name|ngx_inet_upstream_t
typedef|;
end_typedef

begin_function_decl
name|size_t
name|ngx_sock_ntop
parameter_list|(
name|int
name|family
parameter_list|,
name|struct
name|sockaddr
modifier|*
name|sa
parameter_list|,
name|u_char
modifier|*
name|text
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_inet_ntop
parameter_list|(
name|int
name|family
parameter_list|,
name|void
modifier|*
name|addr
parameter_list|,
name|u_char
modifier|*
name|text
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_ptocidr
parameter_list|(
name|ngx_str_t
modifier|*
name|text
parameter_list|,
name|void
modifier|*
name|cidr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_peers_t
modifier|*
name|ngx_inet_upstream_parse
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_inet_upstream_t
modifier|*
name|u
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_inet_parse_host_port
parameter_list|(
name|ngx_inet_upstream_t
modifier|*
name|u
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_INET_H_INCLUDED_ */
end_comment

end_unit

