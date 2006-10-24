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

begin_define
DECL|macro|NGX_PARSE_URL_INET
define|#
directive|define
name|NGX_PARSE_URL_INET
value|1
end_define

begin_define
DECL|macro|NGX_PARSE_URL_UNIX
define|#
directive|define
name|NGX_PARSE_URL_UNIX
value|2
end_define

begin_typedef
DECL|struct|__anon2c6be6030108
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
DECL|struct|__anon2c6be6030208
typedef|typedef
struct|struct
block|{
DECL|member|sockaddr
name|struct
name|sockaddr
modifier|*
name|sockaddr
decl_stmt|;
DECL|member|socklen
name|socklen_t
name|socklen
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|uri_separator
name|char
modifier|*
name|uri_separator
decl_stmt|;
DECL|member|current_weight
name|ngx_uint_t
name|current_weight
decl_stmt|;
DECL|member|weight
name|ngx_uint_t
name|weight
decl_stmt|;
DECL|member|fails
name|ngx_uint_t
name|fails
decl_stmt|;
DECL|member|accessed
name|time_t
name|accessed
decl_stmt|;
DECL|member|max_fails
name|ngx_uint_t
name|max_fails
decl_stmt|;
DECL|member|fail_timeout
name|time_t
name|fail_timeout
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_SSL
operator|)
DECL|member|ssl_session
name|ngx_ssl_session_t
modifier|*
name|ssl_session
decl_stmt|;
endif|#
directive|endif
DECL|typedef|ngx_peer_t
block|}
name|ngx_peer_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_peers_s
struct|struct
name|ngx_peers_s
block|{
DECL|member|current
name|ngx_uint_t
name|current
decl_stmt|;
DECL|member|number
name|ngx_uint_t
name|number
decl_stmt|;
DECL|member|last_cached
name|ngx_uint_t
name|last_cached
decl_stmt|;
comment|/* ngx_mutex_t        *mutex; */
DECL|member|cached
name|ngx_connection_t
modifier|*
modifier|*
name|cached
decl_stmt|;
DECL|member|peer
name|ngx_peer_t
name|peer
index|[
literal|1
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|union|__anon2c6be603030a
typedef|typedef
union|union
block|{
DECL|member|in_addr
name|in_addr_t
name|in_addr
decl_stmt|;
DECL|typedef|ngx_url_addr_t
block|}
name|ngx_url_addr_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c6be6030408
typedef|typedef
struct|struct
block|{
DECL|member|type
name|ngx_int_t
name|type
decl_stmt|;
DECL|member|peers
name|ngx_peers_t
modifier|*
name|peers
decl_stmt|;
DECL|member|url
name|ngx_str_t
name|url
decl_stmt|;
DECL|member|host
name|ngx_str_t
name|host
decl_stmt|;
DECL|member|host_header
name|ngx_str_t
name|host_header
decl_stmt|;
DECL|member|port
name|ngx_str_t
name|port
decl_stmt|;
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|portn
name|in_port_t
name|portn
decl_stmt|;
DECL|member|default_portn
name|in_port_t
name|default_portn
decl_stmt|;
DECL|member|listen
name|unsigned
name|listen
range|:
literal|1
decl_stmt|;
DECL|member|uri_part
name|unsigned
name|uri_part
range|:
literal|1
decl_stmt|;
DECL|member|upstream
name|unsigned
name|upstream
range|:
literal|1
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
DECL|member|addr
name|ngx_url_addr_t
name|addr
decl_stmt|;
DECL|member|err
name|char
modifier|*
name|err
decl_stmt|;
DECL|typedef|ngx_url_t
block|}
name|ngx_url_t
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
name|ngx_int_t
name|ngx_parse_url
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_url_t
modifier|*
name|u
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_peers_t
modifier|*
name|ngx_inet_resolve_peer
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|in_port_t
name|port
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

