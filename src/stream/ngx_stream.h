begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Roman Arutyunyan  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_STREAM_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_STREAM_H_INCLUDED_
define|#
directive|define
name|_NGX_STREAM_H_INCLUDED_
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

begin_if
if|#
directive|if
operator|(
name|NGX_STREAM_SSL
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_stream_ssl_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_stream_session_t
typedef|typedef
name|struct
name|ngx_stream_session_s
name|ngx_stream_session_t
typedef|;
end_typedef

begin_include
include|#
directive|include
file|<ngx_stream_variables.h>
end_include

begin_include
include|#
directive|include
file|<ngx_stream_script.h>
end_include

begin_include
include|#
directive|include
file|<ngx_stream_upstream.h>
end_include

begin_include
include|#
directive|include
file|<ngx_stream_upstream_round_robin.h>
end_include

begin_typedef
DECL|struct|__anon2a2381e70108
typedef|typedef
struct|struct
block|{
DECL|member|main_conf
name|void
modifier|*
modifier|*
name|main_conf
decl_stmt|;
DECL|member|srv_conf
name|void
modifier|*
modifier|*
name|srv_conf
decl_stmt|;
DECL|typedef|ngx_stream_conf_ctx_t
block|}
name|ngx_stream_conf_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a2381e70208
typedef|typedef
struct|struct
block|{
DECL|member|sockaddr
name|ngx_sockaddr_t
name|sockaddr
decl_stmt|;
DECL|member|socklen
name|socklen_t
name|socklen
decl_stmt|;
comment|/* server ctx */
DECL|member|ctx
name|ngx_stream_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
DECL|member|bind
name|unsigned
name|bind
range|:
literal|1
decl_stmt|;
DECL|member|wildcard
name|unsigned
name|wildcard
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_STREAM_SSL
operator|)
DECL|member|ssl
name|unsigned
name|ssl
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|&&
name|defined
name|IPV6_V6ONLY
operator|)
DECL|member|ipv6only
name|unsigned
name|ipv6only
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_REUSEPORT
operator|)
DECL|member|reuseport
name|unsigned
name|reuseport
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
DECL|member|so_keepalive
name|unsigned
name|so_keepalive
range|:
literal|2
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_KEEPALIVE_TUNABLE
operator|)
DECL|member|tcp_keepidle
name|int
name|tcp_keepidle
decl_stmt|;
DECL|member|tcp_keepintvl
name|int
name|tcp_keepintvl
decl_stmt|;
DECL|member|tcp_keepcnt
name|int
name|tcp_keepcnt
decl_stmt|;
endif|#
directive|endif
DECL|member|backlog
name|int
name|backlog
decl_stmt|;
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|typedef|ngx_stream_listen_t
block|}
name|ngx_stream_listen_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a2381e70308
typedef|typedef
struct|struct
block|{
DECL|member|ctx
name|ngx_stream_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
DECL|member|addr_text
name|ngx_str_t
name|addr_text
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_STREAM_SSL
operator|)
DECL|member|ssl
name|ngx_uint_t
name|ssl
decl_stmt|;
comment|/* unsigned   ssl:1; */
endif|#
directive|endif
DECL|typedef|ngx_stream_addr_conf_t
block|}
name|ngx_stream_addr_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a2381e70408
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|conf
name|ngx_stream_addr_conf_t
name|conf
decl_stmt|;
DECL|typedef|ngx_stream_in_addr_t
block|}
name|ngx_stream_in_addr_t
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
DECL|struct|__anon2a2381e70508
typedef|typedef
struct|struct
block|{
DECL|member|addr6
name|struct
name|in6_addr
name|addr6
decl_stmt|;
DECL|member|conf
name|ngx_stream_addr_conf_t
name|conf
decl_stmt|;
DECL|typedef|ngx_stream_in6_addr_t
block|}
name|ngx_stream_in6_addr_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2a2381e70608
typedef|typedef
struct|struct
block|{
comment|/* ngx_stream_in_addr_t or ngx_stream_in6_addr_t */
DECL|member|addrs
name|void
modifier|*
name|addrs
decl_stmt|;
DECL|member|naddrs
name|ngx_uint_t
name|naddrs
decl_stmt|;
DECL|typedef|ngx_stream_port_t
block|}
name|ngx_stream_port_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a2381e70708
typedef|typedef
struct|struct
block|{
DECL|member|family
name|int
name|family
decl_stmt|;
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|addrs
name|ngx_array_t
name|addrs
decl_stmt|;
comment|/* array of ngx_stream_conf_addr_t */
DECL|typedef|ngx_stream_conf_port_t
block|}
name|ngx_stream_conf_port_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a2381e70808
typedef|typedef
struct|struct
block|{
DECL|member|opt
name|ngx_stream_listen_t
name|opt
decl_stmt|;
DECL|typedef|ngx_stream_conf_addr_t
block|}
name|ngx_stream_conf_addr_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_access_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_stream_access_pt
function_decl|)
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2a2381e70908
typedef|typedef
struct|struct
block|{
DECL|member|servers
name|ngx_array_t
name|servers
decl_stmt|;
comment|/* ngx_stream_core_srv_conf_t */
DECL|member|listen
name|ngx_array_t
name|listen
decl_stmt|;
comment|/* ngx_stream_listen_t */
DECL|member|limit_conn_handler
name|ngx_stream_access_pt
name|limit_conn_handler
decl_stmt|;
DECL|member|access_handler
name|ngx_stream_access_pt
name|access_handler
decl_stmt|;
DECL|member|variables_hash
name|ngx_hash_t
name|variables_hash
decl_stmt|;
DECL|member|variables
name|ngx_array_t
name|variables
decl_stmt|;
comment|/* ngx_stream_variable_t */
DECL|member|ncaptures
name|ngx_uint_t
name|ncaptures
decl_stmt|;
DECL|member|variables_hash_max_size
name|ngx_uint_t
name|variables_hash_max_size
decl_stmt|;
DECL|member|variables_hash_bucket_size
name|ngx_uint_t
name|variables_hash_bucket_size
decl_stmt|;
DECL|member|variables_keys
name|ngx_hash_keys_arrays_t
modifier|*
name|variables_keys
decl_stmt|;
DECL|typedef|ngx_stream_core_main_conf_t
block|}
name|ngx_stream_core_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_handler_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_stream_handler_pt
function_decl|)
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2a2381e70a08
typedef|typedef
struct|struct
block|{
DECL|member|handler
name|ngx_stream_handler_pt
name|handler
decl_stmt|;
DECL|member|ctx
name|ngx_stream_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
DECL|member|file_name
name|u_char
modifier|*
name|file_name
decl_stmt|;
DECL|member|line
name|ngx_uint_t
name|line
decl_stmt|;
DECL|member|tcp_nodelay
name|ngx_flag_t
name|tcp_nodelay
decl_stmt|;
DECL|member|error_log
name|ngx_log_t
modifier|*
name|error_log
decl_stmt|;
DECL|member|resolver_timeout
name|ngx_msec_t
name|resolver_timeout
decl_stmt|;
DECL|member|resolver
name|ngx_resolver_t
modifier|*
name|resolver
decl_stmt|;
DECL|member|listen
name|ngx_uint_t
name|listen
decl_stmt|;
comment|/* unsigned  listen:1; */
DECL|typedef|ngx_stream_core_srv_conf_t
block|}
name|ngx_stream_core_srv_conf_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_stream_session_s
struct|struct
name|ngx_stream_session_s
block|{
DECL|member|signature
name|uint32_t
name|signature
decl_stmt|;
comment|/* "STRM" */
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
decl_stmt|;
DECL|member|received
name|off_t
name|received
decl_stmt|;
DECL|member|start_sec
name|time_t
name|start_sec
decl_stmt|;
DECL|member|start_msec
name|ngx_msec_t
name|start_msec
decl_stmt|;
DECL|member|log_handler
name|ngx_log_handler_pt
name|log_handler
decl_stmt|;
DECL|member|ctx
name|void
modifier|*
modifier|*
name|ctx
decl_stmt|;
DECL|member|main_conf
name|void
modifier|*
modifier|*
name|main_conf
decl_stmt|;
DECL|member|srv_conf
name|void
modifier|*
modifier|*
name|srv_conf
decl_stmt|;
DECL|member|upstream
name|ngx_stream_upstream_t
modifier|*
name|upstream
decl_stmt|;
DECL|member|variables
name|ngx_stream_variable_value_t
modifier|*
name|variables
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
DECL|member|ncaptures
name|ngx_uint_t
name|ncaptures
decl_stmt|;
DECL|member|captures
name|int
modifier|*
name|captures
decl_stmt|;
DECL|member|captures_data
name|u_char
modifier|*
name|captures_data
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2a2381e70b08
typedef|typedef
struct|struct
block|{
DECL|member|preconfiguration
name|ngx_int_t
function_decl|(
modifier|*
name|preconfiguration
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|postconfiguration
name|ngx_int_t
function_decl|(
modifier|*
name|postconfiguration
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|create_main_conf
name|void
modifier|*
function_decl|(
modifier|*
name|create_main_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|init_main_conf
name|char
modifier|*
function_decl|(
modifier|*
name|init_main_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
DECL|member|create_srv_conf
name|void
modifier|*
function_decl|(
modifier|*
name|create_srv_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|merge_srv_conf
name|char
modifier|*
function_decl|(
modifier|*
name|merge_srv_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|prev
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
DECL|typedef|ngx_stream_module_t
block|}
name|ngx_stream_module_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_STREAM_MODULE
define|#
directive|define
name|NGX_STREAM_MODULE
value|0x4d525453
end_define

begin_comment
DECL|macro|NGX_STREAM_MODULE
comment|/* "STRM" */
end_comment

begin_define
DECL|macro|NGX_STREAM_MAIN_CONF
define|#
directive|define
name|NGX_STREAM_MAIN_CONF
value|0x02000000
end_define

begin_define
DECL|macro|NGX_STREAM_SRV_CONF
define|#
directive|define
name|NGX_STREAM_SRV_CONF
value|0x04000000
end_define

begin_define
DECL|macro|NGX_STREAM_UPS_CONF
define|#
directive|define
name|NGX_STREAM_UPS_CONF
value|0x08000000
end_define

begin_define
DECL|macro|NGX_STREAM_MAIN_CONF_OFFSET
define|#
directive|define
name|NGX_STREAM_MAIN_CONF_OFFSET
value|offsetof(ngx_stream_conf_ctx_t, main_conf)
end_define

begin_define
DECL|macro|NGX_STREAM_SRV_CONF_OFFSET
define|#
directive|define
name|NGX_STREAM_SRV_CONF_OFFSET
value|offsetof(ngx_stream_conf_ctx_t, srv_conf)
end_define

begin_define
DECL|macro|ngx_stream_get_module_ctx (s,module)
define|#
directive|define
name|ngx_stream_get_module_ctx
parameter_list|(
name|s
parameter_list|,
name|module
parameter_list|)
value|(s)->ctx[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_stream_set_ctx (s,c,module)
define|#
directive|define
name|ngx_stream_set_ctx
parameter_list|(
name|s
parameter_list|,
name|c
parameter_list|,
name|module
parameter_list|)
value|s->ctx[module.ctx_index] = c;
end_define

begin_define
DECL|macro|ngx_stream_delete_ctx (s,module)
define|#
directive|define
name|ngx_stream_delete_ctx
parameter_list|(
name|s
parameter_list|,
name|module
parameter_list|)
value|s->ctx[module.ctx_index] = NULL;
end_define

begin_define
DECL|macro|ngx_stream_get_module_main_conf (s,module)
define|#
directive|define
name|ngx_stream_get_module_main_conf
parameter_list|(
name|s
parameter_list|,
name|module
parameter_list|)
define|\
value|(s)->main_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_stream_get_module_srv_conf (s,module)
define|#
directive|define
name|ngx_stream_get_module_srv_conf
parameter_list|(
name|s
parameter_list|,
name|module
parameter_list|)
define|\
value|(s)->srv_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_stream_conf_get_module_main_conf (cf,module)
define|#
directive|define
name|ngx_stream_conf_get_module_main_conf
parameter_list|(
name|cf
parameter_list|,
name|module
parameter_list|)
define|\
value|((ngx_stream_conf_ctx_t *) cf->ctx)->main_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_stream_conf_get_module_srv_conf (cf,module)
define|#
directive|define
name|ngx_stream_conf_get_module_srv_conf
parameter_list|(
name|cf
parameter_list|,
name|module
parameter_list|)
define|\
value|((ngx_stream_conf_ctx_t *) cf->ctx)->srv_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_stream_cycle_get_module_main_conf (cycle,module)
define|#
directive|define
name|ngx_stream_cycle_get_module_main_conf
parameter_list|(
name|cycle
parameter_list|,
name|module
parameter_list|)
define|\
value|(cycle->conf_ctx[ngx_stream_module.index] ?                                \         ((ngx_stream_conf_ctx_t *) cycle->conf_ctx[ngx_stream_module.index])   \             ->main_conf[module.ctx_index]:                                     \         NULL)
end_define

begin_function_decl
name|void
name|ngx_stream_init_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_stream_close_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_stream_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_stream_max_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_stream_core_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_STREAM_H_INCLUDED_ */
end_comment

end_unit

