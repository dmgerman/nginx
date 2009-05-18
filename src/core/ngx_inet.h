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
DECL|macro|NGX_INET_ADDRSTRLEN
define|#
directive|define
name|NGX_INET_ADDRSTRLEN
value|(sizeof("255.255.255.255") - 1)
end_define

begin_define
DECL|macro|NGX_INET6_ADDRSTRLEN
define|#
directive|define
name|NGX_INET6_ADDRSTRLEN
define|\
value|(sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255") - 1)
end_define

begin_define
DECL|macro|NGX_SOCKADDR_STRLEN
define|#
directive|define
name|NGX_SOCKADDR_STRLEN
value|(NGX_INET6_ADDRSTRLEN + sizeof(":65535") - 1)
end_define

begin_comment
comment|/*  * TODO: autoconfigure NGX_SOCKADDRLEN as  *       sizeof(struct sockaddr_storage)  *       sizeof(struct sockaddr_un)  *       sizeof(struct sockaddr_in6)  *       sizeof(struct sockaddr_in)  */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
end_if

begin_define
DECL|macro|NGX_SOCKADDRLEN
define|#
directive|define
name|NGX_SOCKADDRLEN
value|sizeof(struct sockaddr_un)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_SOCKADDRLEN
define|#
directive|define
name|NGX_SOCKADDRLEN
value|512
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2934e7be0108
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
DECL|typedef|ngx_in_cidr_t
block|}
name|ngx_in_cidr_t
typedef|;
end_typedef

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
end_if

begin_typedef
DECL|struct|__anon2934e7be0208
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|struct
name|in6_addr
name|addr
decl_stmt|;
DECL|member|mask
name|struct
name|in6_addr
name|mask
decl_stmt|;
DECL|typedef|ngx_in6_cidr_t
block|}
name|ngx_in6_cidr_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2934e7be0308
typedef|typedef
struct|struct
block|{
DECL|member|family
name|ngx_uint_t
name|family
decl_stmt|;
DECL|union|__anon2934e7be040a
union|union
block|{
DECL|member|in
name|ngx_in_cidr_t
name|in
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
DECL|member|in6
name|ngx_in6_cidr_t
name|in6
decl_stmt|;
endif|#
directive|endif
DECL|member|u
block|}
name|u
union|;
DECL|typedef|ngx_cidr_t
block|}
name|ngx_cidr_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2934e7be0508
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
DECL|typedef|ngx_peer_addr_t
block|}
name|ngx_peer_addr_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2934e7be0608
typedef|typedef
struct|struct
block|{
DECL|member|url
name|ngx_str_t
name|url
decl_stmt|;
DECL|member|host
name|ngx_str_t
name|host
decl_stmt|;
DECL|member|port_text
name|ngx_str_t
name|port_text
decl_stmt|;
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|default_port
name|in_port_t
name|default_port
decl_stmt|;
DECL|member|family
name|int
name|family
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
DECL|member|no_resolve
name|unsigned
name|no_resolve
range|:
literal|1
decl_stmt|;
DECL|member|one_addr
name|unsigned
name|one_addr
range|:
literal|1
decl_stmt|;
DECL|member|no_port
name|unsigned
name|no_port
range|:
literal|1
decl_stmt|;
DECL|member|wildcard
name|unsigned
name|wildcard
range|:
literal|1
decl_stmt|;
DECL|member|socklen
name|socklen_t
name|socklen
decl_stmt|;
DECL|member|sockaddr
name|u_char
name|sockaddr
index|[
name|NGX_SOCKADDRLEN
index|]
decl_stmt|;
DECL|member|addrs
name|ngx_peer_addr_t
modifier|*
name|addrs
decl_stmt|;
DECL|member|naddrs
name|ngx_uint_t
name|naddrs
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
name|in_addr_t
name|ngx_inet_addr
parameter_list|(
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
name|ngx_sock_ntop
parameter_list|(
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
parameter_list|,
name|ngx_uint_t
name|port
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
name|ngx_cidr_t
modifier|*
name|cidr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_parse_url
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_url_t
modifier|*
name|u
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_inet_resolve_host
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_url_t
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

