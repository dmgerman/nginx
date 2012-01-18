begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

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

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_RESOLVER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_RESOLVER_H_INCLUDED_
define|#
directive|define
name|_NGX_RESOLVER_H_INCLUDED_
end_define

begin_define
DECL|macro|NGX_RESOLVE_A
define|#
directive|define
name|NGX_RESOLVE_A
value|1
end_define

begin_define
DECL|macro|NGX_RESOLVE_CNAME
define|#
directive|define
name|NGX_RESOLVE_CNAME
value|5
end_define

begin_define
DECL|macro|NGX_RESOLVE_PTR
define|#
directive|define
name|NGX_RESOLVE_PTR
value|12
end_define

begin_define
DECL|macro|NGX_RESOLVE_MX
define|#
directive|define
name|NGX_RESOLVE_MX
value|15
end_define

begin_define
DECL|macro|NGX_RESOLVE_TXT
define|#
directive|define
name|NGX_RESOLVE_TXT
value|16
end_define

begin_define
DECL|macro|NGX_RESOLVE_DNAME
define|#
directive|define
name|NGX_RESOLVE_DNAME
value|39
end_define

begin_define
DECL|macro|NGX_RESOLVE_FORMERR
define|#
directive|define
name|NGX_RESOLVE_FORMERR
value|1
end_define

begin_define
DECL|macro|NGX_RESOLVE_SERVFAIL
define|#
directive|define
name|NGX_RESOLVE_SERVFAIL
value|2
end_define

begin_define
DECL|macro|NGX_RESOLVE_NXDOMAIN
define|#
directive|define
name|NGX_RESOLVE_NXDOMAIN
value|3
end_define

begin_define
DECL|macro|NGX_RESOLVE_NOTIMP
define|#
directive|define
name|NGX_RESOLVE_NOTIMP
value|4
end_define

begin_define
DECL|macro|NGX_RESOLVE_REFUSED
define|#
directive|define
name|NGX_RESOLVE_REFUSED
value|5
end_define

begin_define
DECL|macro|NGX_RESOLVE_TIMEDOUT
define|#
directive|define
name|NGX_RESOLVE_TIMEDOUT
value|NGX_ETIMEDOUT
end_define

begin_define
DECL|macro|NGX_NO_RESOLVER
define|#
directive|define
name|NGX_NO_RESOLVER
value|(void *) -1
end_define

begin_define
DECL|macro|NGX_RESOLVER_MAX_RECURSION
define|#
directive|define
name|NGX_RESOLVER_MAX_RECURSION
value|50
end_define

begin_typedef
DECL|struct|__anon28dbda370108
typedef|typedef
struct|struct
block|{
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
decl_stmt|;
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
DECL|member|server
name|ngx_str_t
name|server
decl_stmt|;
DECL|member|log
name|ngx_log_t
name|log
decl_stmt|;
DECL|typedef|ngx_udp_connection_t
block|}
name|ngx_udp_connection_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_resolver_ctx_t
typedef|typedef
name|struct
name|ngx_resolver_ctx_s
name|ngx_resolver_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_resolver_handler_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_resolver_handler_pt
function_decl|)
parameter_list|(
name|ngx_resolver_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon28dbda370208
typedef|typedef
struct|struct
block|{
DECL|member|node
name|ngx_rbtree_node_t
name|node
decl_stmt|;
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
comment|/* PTR: resolved name, A: name to resolve */
DECL|member|name
name|u_char
modifier|*
name|name
decl_stmt|;
DECL|member|nlen
name|u_short
name|nlen
decl_stmt|;
DECL|member|qlen
name|u_short
name|qlen
decl_stmt|;
DECL|member|query
name|u_char
modifier|*
name|query
decl_stmt|;
DECL|union|__anon28dbda37030a
union|union
block|{
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|addrs
name|in_addr_t
modifier|*
name|addrs
decl_stmt|;
DECL|member|cname
name|u_char
modifier|*
name|cname
decl_stmt|;
DECL|member|u
block|}
name|u
union|;
DECL|member|naddrs
name|u_short
name|naddrs
decl_stmt|;
DECL|member|cnlen
name|u_short
name|cnlen
decl_stmt|;
DECL|member|expire
name|time_t
name|expire
decl_stmt|;
DECL|member|valid
name|time_t
name|valid
decl_stmt|;
DECL|member|waiting
name|ngx_resolver_ctx_t
modifier|*
name|waiting
decl_stmt|;
DECL|typedef|ngx_resolver_node_t
block|}
name|ngx_resolver_node_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28dbda370408
typedef|typedef
struct|struct
block|{
comment|/* has to be pointer because of "incomplete type" */
DECL|member|event
name|ngx_event_t
modifier|*
name|event
decl_stmt|;
DECL|member|dummy
name|void
modifier|*
name|dummy
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
comment|/* ident must be after 3 pointers */
DECL|member|ident
name|ngx_int_t
name|ident
decl_stmt|;
comment|/* simple round robin DNS peers balancer */
DECL|member|udp_connections
name|ngx_array_t
name|udp_connections
decl_stmt|;
DECL|member|last_connection
name|ngx_uint_t
name|last_connection
decl_stmt|;
DECL|member|name_rbtree
name|ngx_rbtree_t
name|name_rbtree
decl_stmt|;
DECL|member|name_sentinel
name|ngx_rbtree_node_t
name|name_sentinel
decl_stmt|;
DECL|member|addr_rbtree
name|ngx_rbtree_t
name|addr_rbtree
decl_stmt|;
DECL|member|addr_sentinel
name|ngx_rbtree_node_t
name|addr_sentinel
decl_stmt|;
DECL|member|name_resend_queue
name|ngx_queue_t
name|name_resend_queue
decl_stmt|;
DECL|member|addr_resend_queue
name|ngx_queue_t
name|addr_resend_queue
decl_stmt|;
DECL|member|name_expire_queue
name|ngx_queue_t
name|name_expire_queue
decl_stmt|;
DECL|member|addr_expire_queue
name|ngx_queue_t
name|addr_expire_queue
decl_stmt|;
DECL|member|resend_timeout
name|time_t
name|resend_timeout
decl_stmt|;
DECL|member|expire
name|time_t
name|expire
decl_stmt|;
DECL|member|valid
name|time_t
name|valid
decl_stmt|;
DECL|member|log_level
name|ngx_uint_t
name|log_level
decl_stmt|;
DECL|typedef|ngx_resolver_t
block|}
name|ngx_resolver_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_resolver_ctx_s
struct|struct
name|ngx_resolver_ctx_s
block|{
DECL|member|next
name|ngx_resolver_ctx_t
modifier|*
name|next
decl_stmt|;
DECL|member|resolver
name|ngx_resolver_t
modifier|*
name|resolver
decl_stmt|;
DECL|member|udp_connection
name|ngx_udp_connection_t
modifier|*
name|udp_connection
decl_stmt|;
comment|/* ident must be after 3 pointers */
DECL|member|ident
name|ngx_int_t
name|ident
decl_stmt|;
DECL|member|state
name|ngx_int_t
name|state
decl_stmt|;
DECL|member|type
name|ngx_int_t
name|type
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|naddrs
name|ngx_uint_t
name|naddrs
decl_stmt|;
DECL|member|addrs
name|in_addr_t
modifier|*
name|addrs
decl_stmt|;
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|handler
name|ngx_resolver_handler_pt
name|handler
decl_stmt|;
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|timeout
name|ngx_msec_t
name|timeout
decl_stmt|;
DECL|member|quick
name|ngx_uint_t
name|quick
decl_stmt|;
comment|/* unsigned  quick:1; */
DECL|member|recursion
name|ngx_uint_t
name|recursion
decl_stmt|;
DECL|member|event
name|ngx_event_t
modifier|*
name|event
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|ngx_resolver_t
modifier|*
name|ngx_resolver_create
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_str_t
modifier|*
name|names
parameter_list|,
name|ngx_uint_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_resolver_ctx_t
modifier|*
name|ngx_resolve_start
parameter_list|(
name|ngx_resolver_t
modifier|*
name|r
parameter_list|,
name|ngx_resolver_ctx_t
modifier|*
name|temp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_resolve_name
parameter_list|(
name|ngx_resolver_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_resolve_name_done
parameter_list|(
name|ngx_resolver_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_resolve_addr
parameter_list|(
name|ngx_resolver_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_resolve_addr_done
parameter_list|(
name|ngx_resolver_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_resolver_strerror
parameter_list|(
name|ngx_int_t
name|err
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_RESOLVER_H_INCLUDED_ */
end_comment

end_unit

