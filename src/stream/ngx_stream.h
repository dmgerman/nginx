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

begin_define
DECL|macro|NGX_STREAM_OK
define|#
directive|define
name|NGX_STREAM_OK
value|200
end_define

begin_define
DECL|macro|NGX_STREAM_BAD_REQUEST
define|#
directive|define
name|NGX_STREAM_BAD_REQUEST
value|400
end_define

begin_define
DECL|macro|NGX_STREAM_FORBIDDEN
define|#
directive|define
name|NGX_STREAM_FORBIDDEN
value|403
end_define

begin_define
DECL|macro|NGX_STREAM_INTERNAL_SERVER_ERROR
define|#
directive|define
name|NGX_STREAM_INTERNAL_SERVER_ERROR
value|500
end_define

begin_define
DECL|macro|NGX_STREAM_BAD_GATEWAY
define|#
directive|define
name|NGX_STREAM_BAD_GATEWAY
value|502
end_define

begin_define
DECL|macro|NGX_STREAM_SERVICE_UNAVAILABLE
define|#
directive|define
name|NGX_STREAM_SERVICE_UNAVAILABLE
value|503
end_define

begin_typedef
DECL|struct|__anon27a97c070108
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
DECL|struct|__anon27a97c070208
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
DECL|member|ssl
name|unsigned
name|ssl
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
DECL|member|ipv6only
name|unsigned
name|ipv6only
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
DECL|member|reuseport
name|unsigned
name|reuseport
range|:
literal|1
decl_stmt|;
DECL|member|so_keepalive
name|unsigned
name|so_keepalive
range|:
literal|2
decl_stmt|;
DECL|member|proxy_protocol
name|unsigned
name|proxy_protocol
range|:
literal|1
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
DECL|member|rcvbuf
name|int
name|rcvbuf
decl_stmt|;
DECL|member|sndbuf
name|int
name|sndbuf
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
DECL|struct|__anon27a97c070308
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
DECL|member|ssl
name|unsigned
name|ssl
range|:
literal|1
decl_stmt|;
DECL|member|proxy_protocol
name|unsigned
name|proxy_protocol
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_stream_addr_conf_t
block|}
name|ngx_stream_addr_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27a97c070408
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
DECL|struct|__anon27a97c070508
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
DECL|struct|__anon27a97c070608
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
DECL|struct|__anon27a97c070708
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
DECL|struct|__anon27a97c070808
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
DECL|enum|__anon27a97c070903
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_STREAM_POST_ACCEPT_PHASE
name|NGX_STREAM_POST_ACCEPT_PHASE
init|=
literal|0
block|,
DECL|enumerator|NGX_STREAM_PREACCESS_PHASE
name|NGX_STREAM_PREACCESS_PHASE
block|,
DECL|enumerator|NGX_STREAM_ACCESS_PHASE
name|NGX_STREAM_ACCESS_PHASE
block|,
DECL|enumerator|NGX_STREAM_SSL_PHASE
name|NGX_STREAM_SSL_PHASE
block|,
DECL|enumerator|NGX_STREAM_PREREAD_PHASE
name|NGX_STREAM_PREREAD_PHASE
block|,
DECL|enumerator|NGX_STREAM_CONTENT_PHASE
name|NGX_STREAM_CONTENT_PHASE
block|,
DECL|enumerator|NGX_STREAM_LOG_PHASE
name|NGX_STREAM_LOG_PHASE
DECL|typedef|ngx_stream_phases
block|}
name|ngx_stream_phases
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_phase_handler_t
typedef|typedef
name|struct
name|ngx_stream_phase_handler_s
name|ngx_stream_phase_handler_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_phase_handler_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_stream_phase_handler_pt
function_decl|)
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_handler_pt
typedef|typedef
name|ngx_int_t
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
DECL|typedef|ngx_stream_content_handler_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_stream_content_handler_pt
function_decl|)
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_stream_phase_handler_s
struct|struct
name|ngx_stream_phase_handler_s
block|{
DECL|member|checker
name|ngx_stream_phase_handler_pt
name|checker
decl_stmt|;
DECL|member|handler
name|ngx_stream_handler_pt
name|handler
decl_stmt|;
DECL|member|next
name|ngx_uint_t
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon27a97c070a08
typedef|typedef
struct|struct
block|{
DECL|member|handlers
name|ngx_stream_phase_handler_t
modifier|*
name|handlers
decl_stmt|;
DECL|typedef|ngx_stream_phase_engine_t
block|}
name|ngx_stream_phase_engine_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27a97c070b08
typedef|typedef
struct|struct
block|{
DECL|member|handlers
name|ngx_array_t
name|handlers
decl_stmt|;
DECL|typedef|ngx_stream_phase_t
block|}
name|ngx_stream_phase_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27a97c070c08
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
DECL|member|phase_engine
name|ngx_stream_phase_engine_t
name|phase_engine
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
DECL|member|prefix_variables
name|ngx_array_t
name|prefix_variables
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
DECL|member|phases
name|ngx_stream_phase_t
name|phases
index|[
name|NGX_STREAM_LOG_PHASE
operator|+
literal|1
index|]
decl_stmt|;
DECL|typedef|ngx_stream_core_main_conf_t
block|}
name|ngx_stream_core_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27a97c070d08
typedef|typedef
struct|struct
block|{
DECL|member|handler
name|ngx_stream_content_handler_pt
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
DECL|member|preread_buffer_size
name|size_t
name|preread_buffer_size
decl_stmt|;
DECL|member|preread_timeout
name|ngx_msec_t
name|preread_timeout
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
DECL|member|proxy_protocol_timeout
name|ngx_msec_t
name|proxy_protocol_timeout
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
DECL|member|upstream_states
name|ngx_array_t
modifier|*
name|upstream_states
decl_stmt|;
comment|/* of ngx_stream_upstream_state_t */
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
DECL|member|phase_handler
name|ngx_int_t
name|phase_handler
decl_stmt|;
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|ssl
name|unsigned
name|ssl
range|:
literal|1
decl_stmt|;
DECL|member|stat_processing
name|unsigned
name|stat_processing
range|:
literal|1
decl_stmt|;
DECL|member|health_check
name|unsigned
name|health_check
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon27a97c070e08
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

begin_define
DECL|macro|NGX_STREAM_WRITE_BUFFERED
define|#
directive|define
name|NGX_STREAM_WRITE_BUFFERED
value|0x10
end_define

begin_function_decl
name|void
name|ngx_stream_core_run_phases
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_core_generic_phase
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_core_preread_phase
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_core_content_phase
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

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
name|ngx_stream_session_handler
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_stream_finalize_session
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_uint_t
name|rc
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

begin_typedef
DECL|typedef|ngx_stream_filter_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_stream_filter_pt
function_decl|)
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_chain_t
modifier|*
name|chain
parameter_list|,
name|ngx_uint_t
name|from_upstream
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_stream_filter_pt
name|ngx_stream_top_filter
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

