begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_CORE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_CORE_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_CORE_H_INCLUDED_
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
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_OFF
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_OFF
value|0x0002
end_define

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_EXPIRED
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_EXPIRED
value|0x0004
end_define

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_NO_CACHE
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_NO_CACHE
value|0x0008
end_define

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_NO_STORE
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_NO_STORE
value|0x0010
end_define

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_PRIVATE
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_PRIVATE
value|0x0020
end_define

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_NO_LM
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_NO_LM
value|0x0040
end_define

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_NO_ETAG
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_NO_ETAG
value|0x0080
end_define

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_AUTH
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_AUTH
value|0x0100
end_define

begin_define
DECL|macro|NGX_HTTP_GZIP_PROXIED_ANY
define|#
directive|define
name|NGX_HTTP_GZIP_PROXIED_ANY
value|0x0200
end_define

begin_define
DECL|macro|NGX_HTTP_AIO_OFF
define|#
directive|define
name|NGX_HTTP_AIO_OFF
value|0
end_define

begin_define
DECL|macro|NGX_HTTP_AIO_ON
define|#
directive|define
name|NGX_HTTP_AIO_ON
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_AIO_SENDFILE
define|#
directive|define
name|NGX_HTTP_AIO_SENDFILE
value|2
end_define

begin_define
DECL|macro|NGX_HTTP_SATISFY_ALL
define|#
directive|define
name|NGX_HTTP_SATISFY_ALL
value|0
end_define

begin_define
DECL|macro|NGX_HTTP_SATISFY_ANY
define|#
directive|define
name|NGX_HTTP_SATISFY_ANY
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_LINGERING_OFF
define|#
directive|define
name|NGX_HTTP_LINGERING_OFF
value|0
end_define

begin_define
DECL|macro|NGX_HTTP_LINGERING_ON
define|#
directive|define
name|NGX_HTTP_LINGERING_ON
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_LINGERING_ALWAYS
define|#
directive|define
name|NGX_HTTP_LINGERING_ALWAYS
value|2
end_define

begin_define
DECL|macro|NGX_HTTP_IMS_OFF
define|#
directive|define
name|NGX_HTTP_IMS_OFF
value|0
end_define

begin_define
DECL|macro|NGX_HTTP_IMS_EXACT
define|#
directive|define
name|NGX_HTTP_IMS_EXACT
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_IMS_BEFORE
define|#
directive|define
name|NGX_HTTP_IMS_BEFORE
value|2
end_define

begin_define
DECL|macro|NGX_HTTP_KEEPALIVE_DISABLE_NONE
define|#
directive|define
name|NGX_HTTP_KEEPALIVE_DISABLE_NONE
value|0x0002
end_define

begin_define
DECL|macro|NGX_HTTP_KEEPALIVE_DISABLE_MSIE6
define|#
directive|define
name|NGX_HTTP_KEEPALIVE_DISABLE_MSIE6
value|0x0004
end_define

begin_define
DECL|macro|NGX_HTTP_KEEPALIVE_DISABLE_SAFARI
define|#
directive|define
name|NGX_HTTP_KEEPALIVE_DISABLE_SAFARI
value|0x0008
end_define

begin_typedef
DECL|typedef|ngx_http_location_tree_node_t
typedef|typedef
name|struct
name|ngx_http_location_tree_node_s
name|ngx_http_location_tree_node_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_core_loc_conf_t
typedef|typedef
name|struct
name|ngx_http_core_loc_conf_s
name|ngx_http_core_loc_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a0108
typedef|typedef
struct|struct
block|{
DECL|union|__anon2931794a020a
union|union
block|{
DECL|member|sockaddr
name|struct
name|sockaddr
name|sockaddr
decl_stmt|;
DECL|member|sockaddr_in
name|struct
name|sockaddr_in
name|sockaddr_in
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
DECL|member|sockaddr_in6
name|struct
name|sockaddr_in6
name|sockaddr_in6
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
DECL|member|sockaddr_un
name|struct
name|sockaddr_un
name|sockaddr_un
decl_stmt|;
endif|#
directive|endif
DECL|member|sockaddr_data
name|u_char
name|sockaddr_data
index|[
name|NGX_SOCKADDRLEN
index|]
decl_stmt|;
DECL|member|u
block|}
name|u
union|;
DECL|member|socklen
name|socklen_t
name|socklen
decl_stmt|;
DECL|member|set
name|unsigned
name|set
range|:
literal|1
decl_stmt|;
DECL|member|default_server
name|unsigned
name|default_server
range|:
literal|1
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
name|NGX_HTTP_SSL
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
name|NGX_HTTP_SPDY
operator|)
DECL|member|spdy
name|unsigned
name|spdy
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
DECL|member|so_keepalive
name|unsigned
name|so_keepalive
range|:
literal|2
decl_stmt|;
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
if|#
directive|if
operator|(
name|NGX_HAVE_SETFIB
operator|)
DECL|member|setfib
name|int
name|setfib
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_TCP_FASTOPEN
operator|)
DECL|member|fastopen
name|int
name|fastopen
decl_stmt|;
endif|#
directive|endif
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
if|#
directive|if
operator|(
name|NGX_HAVE_DEFERRED_ACCEPT
operator|&&
name|defined
name|SO_ACCEPTFILTER
operator|)
DECL|member|accept_filter
name|char
modifier|*
name|accept_filter
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_DEFERRED_ACCEPT
operator|&&
name|defined
name|TCP_DEFER_ACCEPT
operator|)
DECL|member|deferred_accept
name|ngx_uint_t
name|deferred_accept
decl_stmt|;
endif|#
directive|endif
DECL|member|addr
name|u_char
name|addr
index|[
name|NGX_SOCKADDR_STRLEN
operator|+
literal|1
index|]
decl_stmt|;
DECL|typedef|ngx_http_listen_opt_t
block|}
name|ngx_http_listen_opt_t
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2931794a0303
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_HTTP_POST_READ_PHASE
name|NGX_HTTP_POST_READ_PHASE
init|=
literal|0
block|,
DECL|enumerator|NGX_HTTP_SERVER_REWRITE_PHASE
name|NGX_HTTP_SERVER_REWRITE_PHASE
block|,
DECL|enumerator|NGX_HTTP_FIND_CONFIG_PHASE
name|NGX_HTTP_FIND_CONFIG_PHASE
block|,
DECL|enumerator|NGX_HTTP_REWRITE_PHASE
name|NGX_HTTP_REWRITE_PHASE
block|,
DECL|enumerator|NGX_HTTP_POST_REWRITE_PHASE
name|NGX_HTTP_POST_REWRITE_PHASE
block|,
DECL|enumerator|NGX_HTTP_PREACCESS_PHASE
name|NGX_HTTP_PREACCESS_PHASE
block|,
DECL|enumerator|NGX_HTTP_ACCESS_PHASE
name|NGX_HTTP_ACCESS_PHASE
block|,
DECL|enumerator|NGX_HTTP_POST_ACCESS_PHASE
name|NGX_HTTP_POST_ACCESS_PHASE
block|,
DECL|enumerator|NGX_HTTP_TRY_FILES_PHASE
name|NGX_HTTP_TRY_FILES_PHASE
block|,
DECL|enumerator|NGX_HTTP_CONTENT_PHASE
name|NGX_HTTP_CONTENT_PHASE
block|,
DECL|enumerator|NGX_HTTP_LOG_PHASE
name|NGX_HTTP_LOG_PHASE
DECL|typedef|ngx_http_phases
block|}
name|ngx_http_phases
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_phase_handler_t
typedef|typedef
name|struct
name|ngx_http_phase_handler_s
name|ngx_http_phase_handler_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_phase_handler_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_http_phase_handler_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_http_phase_handler_s
struct|struct
name|ngx_http_phase_handler_s
block|{
DECL|member|checker
name|ngx_http_phase_handler_pt
name|checker
decl_stmt|;
DECL|member|handler
name|ngx_http_handler_pt
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
DECL|struct|__anon2931794a0408
typedef|typedef
struct|struct
block|{
DECL|member|handlers
name|ngx_http_phase_handler_t
modifier|*
name|handlers
decl_stmt|;
DECL|member|server_rewrite_index
name|ngx_uint_t
name|server_rewrite_index
decl_stmt|;
DECL|member|location_rewrite_index
name|ngx_uint_t
name|location_rewrite_index
decl_stmt|;
DECL|typedef|ngx_http_phase_engine_t
block|}
name|ngx_http_phase_engine_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a0508
typedef|typedef
struct|struct
block|{
DECL|member|handlers
name|ngx_array_t
name|handlers
decl_stmt|;
DECL|typedef|ngx_http_phase_t
block|}
name|ngx_http_phase_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a0608
typedef|typedef
struct|struct
block|{
DECL|member|servers
name|ngx_array_t
name|servers
decl_stmt|;
comment|/* ngx_http_core_srv_conf_t */
DECL|member|phase_engine
name|ngx_http_phase_engine_t
name|phase_engine
decl_stmt|;
DECL|member|headers_in_hash
name|ngx_hash_t
name|headers_in_hash
decl_stmt|;
DECL|member|variables_hash
name|ngx_hash_t
name|variables_hash
decl_stmt|;
DECL|member|variables
name|ngx_array_t
name|variables
decl_stmt|;
comment|/* ngx_http_variable_t */
DECL|member|ncaptures
name|ngx_uint_t
name|ncaptures
decl_stmt|;
DECL|member|server_names_hash_max_size
name|ngx_uint_t
name|server_names_hash_max_size
decl_stmt|;
DECL|member|server_names_hash_bucket_size
name|ngx_uint_t
name|server_names_hash_bucket_size
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
DECL|member|ports
name|ngx_array_t
modifier|*
name|ports
decl_stmt|;
DECL|member|try_files
name|ngx_uint_t
name|try_files
decl_stmt|;
comment|/* unsigned  try_files:1 */
DECL|member|phases
name|ngx_http_phase_t
name|phases
index|[
name|NGX_HTTP_LOG_PHASE
operator|+
literal|1
index|]
decl_stmt|;
DECL|typedef|ngx_http_core_main_conf_t
block|}
name|ngx_http_core_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a0708
typedef|typedef
struct|struct
block|{
comment|/* array of the ngx_http_server_name_t, "server_name" directive */
DECL|member|server_names
name|ngx_array_t
name|server_names
decl_stmt|;
comment|/* server ctx */
DECL|member|ctx
name|ngx_http_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
DECL|member|server_name
name|ngx_str_t
name|server_name
decl_stmt|;
DECL|member|connection_pool_size
name|size_t
name|connection_pool_size
decl_stmt|;
DECL|member|request_pool_size
name|size_t
name|request_pool_size
decl_stmt|;
DECL|member|client_header_buffer_size
name|size_t
name|client_header_buffer_size
decl_stmt|;
DECL|member|large_client_header_buffers
name|ngx_bufs_t
name|large_client_header_buffers
decl_stmt|;
DECL|member|client_header_timeout
name|ngx_msec_t
name|client_header_timeout
decl_stmt|;
DECL|member|ignore_invalid_headers
name|ngx_flag_t
name|ignore_invalid_headers
decl_stmt|;
DECL|member|merge_slashes
name|ngx_flag_t
name|merge_slashes
decl_stmt|;
DECL|member|underscores_in_headers
name|ngx_flag_t
name|underscores_in_headers
decl_stmt|;
DECL|member|listen
name|unsigned
name|listen
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
DECL|member|captures
name|unsigned
name|captures
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
DECL|member|named_locations
name|ngx_http_core_loc_conf_t
modifier|*
modifier|*
name|named_locations
decl_stmt|;
DECL|typedef|ngx_http_core_srv_conf_t
block|}
name|ngx_http_core_srv_conf_t
typedef|;
end_typedef

begin_comment
comment|/* list of structures to find core_srv_conf quickly at run time */
end_comment

begin_typedef
DECL|struct|__anon2931794a0808
typedef|typedef
struct|struct
block|{
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
DECL|member|regex
name|ngx_http_regex_t
modifier|*
name|regex
decl_stmt|;
endif|#
directive|endif
DECL|member|server
name|ngx_http_core_srv_conf_t
modifier|*
name|server
decl_stmt|;
comment|/* virtual name server conf */
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|typedef|ngx_http_server_name_t
block|}
name|ngx_http_server_name_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a0908
typedef|typedef
struct|struct
block|{
DECL|member|names
name|ngx_hash_combined_t
name|names
decl_stmt|;
DECL|member|nregex
name|ngx_uint_t
name|nregex
decl_stmt|;
DECL|member|regex
name|ngx_http_server_name_t
modifier|*
name|regex
decl_stmt|;
DECL|typedef|ngx_http_virtual_names_t
block|}
name|ngx_http_virtual_names_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_addr_conf_s
struct|struct
name|ngx_http_addr_conf_s
block|{
comment|/* the default server configuration for this address:port */
DECL|member|default_server
name|ngx_http_core_srv_conf_t
modifier|*
name|default_server
decl_stmt|;
DECL|member|virtual_names
name|ngx_http_virtual_names_t
modifier|*
name|virtual_names
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
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
name|NGX_HTTP_SPDY
operator|)
DECL|member|spdy
name|unsigned
name|spdy
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2931794a0a08
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|conf
name|ngx_http_addr_conf_t
name|conf
decl_stmt|;
DECL|typedef|ngx_http_in_addr_t
block|}
name|ngx_http_in_addr_t
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
DECL|struct|__anon2931794a0b08
typedef|typedef
struct|struct
block|{
DECL|member|addr6
name|struct
name|in6_addr
name|addr6
decl_stmt|;
DECL|member|conf
name|ngx_http_addr_conf_t
name|conf
decl_stmt|;
DECL|typedef|ngx_http_in6_addr_t
block|}
name|ngx_http_in6_addr_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2931794a0c08
typedef|typedef
struct|struct
block|{
comment|/* ngx_http_in_addr_t or ngx_http_in6_addr_t */
DECL|member|addrs
name|void
modifier|*
name|addrs
decl_stmt|;
DECL|member|naddrs
name|ngx_uint_t
name|naddrs
decl_stmt|;
DECL|typedef|ngx_http_port_t
block|}
name|ngx_http_port_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a0d08
typedef|typedef
struct|struct
block|{
DECL|member|family
name|ngx_int_t
name|family
decl_stmt|;
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|addrs
name|ngx_array_t
name|addrs
decl_stmt|;
comment|/* array of ngx_http_conf_addr_t */
DECL|typedef|ngx_http_conf_port_t
block|}
name|ngx_http_conf_port_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a0e08
typedef|typedef
struct|struct
block|{
DECL|member|opt
name|ngx_http_listen_opt_t
name|opt
decl_stmt|;
DECL|member|hash
name|ngx_hash_t
name|hash
decl_stmt|;
DECL|member|wc_head
name|ngx_hash_wildcard_t
modifier|*
name|wc_head
decl_stmt|;
DECL|member|wc_tail
name|ngx_hash_wildcard_t
modifier|*
name|wc_tail
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
DECL|member|nregex
name|ngx_uint_t
name|nregex
decl_stmt|;
DECL|member|regex
name|ngx_http_server_name_t
modifier|*
name|regex
decl_stmt|;
endif|#
directive|endif
comment|/* the default server configuration for this address:port */
DECL|member|default_server
name|ngx_http_core_srv_conf_t
modifier|*
name|default_server
decl_stmt|;
DECL|member|servers
name|ngx_array_t
name|servers
decl_stmt|;
comment|/* array of ngx_http_core_srv_conf_t */
DECL|typedef|ngx_http_conf_addr_t
block|}
name|ngx_http_conf_addr_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a0f08
typedef|typedef
struct|struct
block|{
DECL|member|status
name|ngx_int_t
name|status
decl_stmt|;
DECL|member|overwrite
name|ngx_int_t
name|overwrite
decl_stmt|;
DECL|member|value
name|ngx_http_complex_value_t
name|value
decl_stmt|;
DECL|member|args
name|ngx_str_t
name|args
decl_stmt|;
DECL|typedef|ngx_http_err_page_t
block|}
name|ngx_http_err_page_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2931794a1008
typedef|typedef
struct|struct
block|{
DECL|member|lengths
name|ngx_array_t
modifier|*
name|lengths
decl_stmt|;
DECL|member|values
name|ngx_array_t
modifier|*
name|values
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|code
name|unsigned
name|code
range|:
literal|10
decl_stmt|;
DECL|member|test_dir
name|unsigned
name|test_dir
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_try_file_t
block|}
name|ngx_http_try_file_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_core_loc_conf_s
struct|struct
name|ngx_http_core_loc_conf_s
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
comment|/* location name */
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
DECL|member|regex
name|ngx_http_regex_t
modifier|*
name|regex
decl_stmt|;
endif|#
directive|endif
DECL|member|noname
name|unsigned
name|noname
range|:
literal|1
decl_stmt|;
comment|/* "if () {}" block or limit_except */
DECL|member|lmt_excpt
name|unsigned
name|lmt_excpt
range|:
literal|1
decl_stmt|;
DECL|member|named
name|unsigned
name|named
range|:
literal|1
decl_stmt|;
DECL|member|exact_match
name|unsigned
name|exact_match
range|:
literal|1
decl_stmt|;
DECL|member|noregex
name|unsigned
name|noregex
range|:
literal|1
decl_stmt|;
DECL|member|auto_redirect
name|unsigned
name|auto_redirect
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_GZIP
operator|)
DECL|member|gzip_disable_msie6
name|unsigned
name|gzip_disable_msie6
range|:
literal|2
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_DEGRADATION
operator|)
DECL|member|gzip_disable_degradation
name|unsigned
name|gzip_disable_degradation
range|:
literal|2
decl_stmt|;
endif|#
directive|endif
endif|#
directive|endif
DECL|member|static_locations
name|ngx_http_location_tree_node_t
modifier|*
name|static_locations
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
DECL|member|regex_locations
name|ngx_http_core_loc_conf_t
modifier|*
modifier|*
name|regex_locations
decl_stmt|;
endif|#
directive|endif
comment|/* pointer to the modules' loc_conf */
DECL|member|loc_conf
name|void
modifier|*
modifier|*
name|loc_conf
decl_stmt|;
DECL|member|limit_except
name|uint32_t
name|limit_except
decl_stmt|;
DECL|member|limit_except_loc_conf
name|void
modifier|*
modifier|*
name|limit_except_loc_conf
decl_stmt|;
DECL|member|handler
name|ngx_http_handler_pt
name|handler
decl_stmt|;
comment|/* location name length for inclusive location with inherited alias */
DECL|member|alias
name|size_t
name|alias
decl_stmt|;
DECL|member|root
name|ngx_str_t
name|root
decl_stmt|;
comment|/* root, alias */
DECL|member|post_action
name|ngx_str_t
name|post_action
decl_stmt|;
DECL|member|root_lengths
name|ngx_array_t
modifier|*
name|root_lengths
decl_stmt|;
DECL|member|root_values
name|ngx_array_t
modifier|*
name|root_values
decl_stmt|;
DECL|member|types
name|ngx_array_t
modifier|*
name|types
decl_stmt|;
DECL|member|types_hash
name|ngx_hash_t
name|types_hash
decl_stmt|;
DECL|member|default_type
name|ngx_str_t
name|default_type
decl_stmt|;
DECL|member|client_max_body_size
name|off_t
name|client_max_body_size
decl_stmt|;
comment|/* client_max_body_size */
DECL|member|directio
name|off_t
name|directio
decl_stmt|;
comment|/* directio */
DECL|member|directio_alignment
name|off_t
name|directio_alignment
decl_stmt|;
comment|/* directio_alignment */
DECL|member|client_body_buffer_size
name|size_t
name|client_body_buffer_size
decl_stmt|;
comment|/* client_body_buffer_size */
DECL|member|send_lowat
name|size_t
name|send_lowat
decl_stmt|;
comment|/* send_lowat */
DECL|member|postpone_output
name|size_t
name|postpone_output
decl_stmt|;
comment|/* postpone_output */
DECL|member|limit_rate
name|size_t
name|limit_rate
decl_stmt|;
comment|/* limit_rate */
DECL|member|limit_rate_after
name|size_t
name|limit_rate_after
decl_stmt|;
comment|/* limit_rate_after */
DECL|member|sendfile_max_chunk
name|size_t
name|sendfile_max_chunk
decl_stmt|;
comment|/* sendfile_max_chunk */
DECL|member|read_ahead
name|size_t
name|read_ahead
decl_stmt|;
comment|/* read_ahead */
DECL|member|client_body_timeout
name|ngx_msec_t
name|client_body_timeout
decl_stmt|;
comment|/* client_body_timeout */
DECL|member|send_timeout
name|ngx_msec_t
name|send_timeout
decl_stmt|;
comment|/* send_timeout */
DECL|member|keepalive_timeout
name|ngx_msec_t
name|keepalive_timeout
decl_stmt|;
comment|/* keepalive_timeout */
DECL|member|lingering_time
name|ngx_msec_t
name|lingering_time
decl_stmt|;
comment|/* lingering_time */
DECL|member|lingering_timeout
name|ngx_msec_t
name|lingering_timeout
decl_stmt|;
comment|/* lingering_timeout */
DECL|member|resolver_timeout
name|ngx_msec_t
name|resolver_timeout
decl_stmt|;
comment|/* resolver_timeout */
DECL|member|resolver
name|ngx_resolver_t
modifier|*
name|resolver
decl_stmt|;
comment|/* resolver */
DECL|member|keepalive_header
name|time_t
name|keepalive_header
decl_stmt|;
comment|/* keepalive_timeout */
DECL|member|keepalive_requests
name|ngx_uint_t
name|keepalive_requests
decl_stmt|;
comment|/* keepalive_requests */
DECL|member|keepalive_disable
name|ngx_uint_t
name|keepalive_disable
decl_stmt|;
comment|/* keepalive_disable */
DECL|member|satisfy
name|ngx_uint_t
name|satisfy
decl_stmt|;
comment|/* satisfy */
DECL|member|lingering_close
name|ngx_uint_t
name|lingering_close
decl_stmt|;
comment|/* lingering_close */
DECL|member|if_modified_since
name|ngx_uint_t
name|if_modified_since
decl_stmt|;
comment|/* if_modified_since */
DECL|member|max_ranges
name|ngx_uint_t
name|max_ranges
decl_stmt|;
comment|/* max_ranges */
DECL|member|client_body_in_file_only
name|ngx_uint_t
name|client_body_in_file_only
decl_stmt|;
comment|/* client_body_in_file_only */
DECL|member|client_body_in_single_buffer
name|ngx_flag_t
name|client_body_in_single_buffer
decl_stmt|;
comment|/* client_body_in_singe_buffer */
DECL|member|internal
name|ngx_flag_t
name|internal
decl_stmt|;
comment|/* internal */
DECL|member|sendfile
name|ngx_flag_t
name|sendfile
decl_stmt|;
comment|/* sendfile */
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|)
DECL|member|aio
name|ngx_flag_t
name|aio
decl_stmt|;
comment|/* aio */
endif|#
directive|endif
DECL|member|tcp_nopush
name|ngx_flag_t
name|tcp_nopush
decl_stmt|;
comment|/* tcp_nopush */
DECL|member|tcp_nodelay
name|ngx_flag_t
name|tcp_nodelay
decl_stmt|;
comment|/* tcp_nodelay */
DECL|member|reset_timedout_connection
name|ngx_flag_t
name|reset_timedout_connection
decl_stmt|;
comment|/* reset_timedout_connection */
DECL|member|server_name_in_redirect
name|ngx_flag_t
name|server_name_in_redirect
decl_stmt|;
comment|/* server_name_in_redirect */
DECL|member|port_in_redirect
name|ngx_flag_t
name|port_in_redirect
decl_stmt|;
comment|/* port_in_redirect */
DECL|member|msie_padding
name|ngx_flag_t
name|msie_padding
decl_stmt|;
comment|/* msie_padding */
DECL|member|msie_refresh
name|ngx_flag_t
name|msie_refresh
decl_stmt|;
comment|/* msie_refresh */
DECL|member|log_not_found
name|ngx_flag_t
name|log_not_found
decl_stmt|;
comment|/* log_not_found */
DECL|member|log_subrequest
name|ngx_flag_t
name|log_subrequest
decl_stmt|;
comment|/* log_subrequest */
DECL|member|recursive_error_pages
name|ngx_flag_t
name|recursive_error_pages
decl_stmt|;
comment|/* recursive_error_pages */
DECL|member|server_tokens
name|ngx_flag_t
name|server_tokens
decl_stmt|;
comment|/* server_tokens */
DECL|member|chunked_transfer_encoding
name|ngx_flag_t
name|chunked_transfer_encoding
decl_stmt|;
comment|/* chunked_transfer_encoding */
DECL|member|etag
name|ngx_flag_t
name|etag
decl_stmt|;
comment|/* etag */
if|#
directive|if
operator|(
name|NGX_HTTP_GZIP
operator|)
DECL|member|gzip_vary
name|ngx_flag_t
name|gzip_vary
decl_stmt|;
comment|/* gzip_vary */
DECL|member|gzip_http_version
name|ngx_uint_t
name|gzip_http_version
decl_stmt|;
comment|/* gzip_http_version */
DECL|member|gzip_proxied
name|ngx_uint_t
name|gzip_proxied
decl_stmt|;
comment|/* gzip_proxied */
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
DECL|member|gzip_disable
name|ngx_array_t
modifier|*
name|gzip_disable
decl_stmt|;
comment|/* gzip_disable */
endif|#
directive|endif
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_OPENAT
operator|)
DECL|member|disable_symlinks
name|ngx_uint_t
name|disable_symlinks
decl_stmt|;
comment|/* disable_symlinks */
DECL|member|disable_symlinks_from
name|ngx_http_complex_value_t
modifier|*
name|disable_symlinks_from
decl_stmt|;
endif|#
directive|endif
DECL|member|error_pages
name|ngx_array_t
modifier|*
name|error_pages
decl_stmt|;
comment|/* error_page */
DECL|member|try_files
name|ngx_http_try_file_t
modifier|*
name|try_files
decl_stmt|;
comment|/* try_files */
DECL|member|client_body_temp_path
name|ngx_path_t
modifier|*
name|client_body_temp_path
decl_stmt|;
comment|/* client_body_temp_path */
DECL|member|open_file_cache
name|ngx_open_file_cache_t
modifier|*
name|open_file_cache
decl_stmt|;
DECL|member|open_file_cache_valid
name|time_t
name|open_file_cache_valid
decl_stmt|;
DECL|member|open_file_cache_min_uses
name|ngx_uint_t
name|open_file_cache_min_uses
decl_stmt|;
DECL|member|open_file_cache_errors
name|ngx_flag_t
name|open_file_cache_errors
decl_stmt|;
DECL|member|open_file_cache_events
name|ngx_flag_t
name|open_file_cache_events
decl_stmt|;
DECL|member|error_log
name|ngx_log_t
modifier|*
name|error_log
decl_stmt|;
DECL|member|types_hash_max_size
name|ngx_uint_t
name|types_hash_max_size
decl_stmt|;
DECL|member|types_hash_bucket_size
name|ngx_uint_t
name|types_hash_bucket_size
decl_stmt|;
DECL|member|locations
name|ngx_queue_t
modifier|*
name|locations
decl_stmt|;
if|#
directive|if
literal|0
block|ngx_http_core_loc_conf_t  *prev_location;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2931794a1108
typedef|typedef
struct|struct
block|{
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
DECL|member|exact
name|ngx_http_core_loc_conf_t
modifier|*
name|exact
decl_stmt|;
DECL|member|inclusive
name|ngx_http_core_loc_conf_t
modifier|*
name|inclusive
decl_stmt|;
DECL|member|name
name|ngx_str_t
modifier|*
name|name
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
DECL|member|list
name|ngx_queue_t
name|list
decl_stmt|;
DECL|typedef|ngx_http_location_queue_t
block|}
name|ngx_http_location_queue_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_location_tree_node_s
struct|struct
name|ngx_http_location_tree_node_s
block|{
DECL|member|left
name|ngx_http_location_tree_node_t
modifier|*
name|left
decl_stmt|;
DECL|member|right
name|ngx_http_location_tree_node_t
modifier|*
name|right
decl_stmt|;
DECL|member|tree
name|ngx_http_location_tree_node_t
modifier|*
name|tree
decl_stmt|;
DECL|member|exact
name|ngx_http_core_loc_conf_t
modifier|*
name|exact
decl_stmt|;
DECL|member|inclusive
name|ngx_http_core_loc_conf_t
modifier|*
name|inclusive
decl_stmt|;
DECL|member|auto_redirect
name|u_char
name|auto_redirect
decl_stmt|;
DECL|member|len
name|u_char
name|len
decl_stmt|;
DECL|member|name
name|u_char
name|name
index|[
literal|1
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|ngx_http_core_run_phases
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_core_generic_phase
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_core_rewrite_phase
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_core_find_config_phase
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_core_post_rewrite_phase
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_core_access_phase
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_core_post_access_phase
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_core_try_files_phase
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_core_content_phase
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_phase_handler_t
modifier|*
name|ph
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_http_test_content_type
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_hash_t
modifier|*
name|types_hash
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_set_content_type
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_set_exten
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_set_etag
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_send_response
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_uint_t
name|status
parameter_list|,
name|ngx_str_t
modifier|*
name|ct
parameter_list|,
name|ngx_http_complex_value_t
modifier|*
name|cv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_http_map_uri_to_path
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|size_t
modifier|*
name|root_length
parameter_list|,
name|size_t
name|reserved
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_auth_basic_user
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_GZIP
operator|)
end_if

begin_function_decl
name|ngx_int_t
name|ngx_http_gzip_ok
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|ngx_int_t
name|ngx_http_subrequest
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_str_t
modifier|*
name|uri
parameter_list|,
name|ngx_str_t
modifier|*
name|args
parameter_list|,
name|ngx_http_request_t
modifier|*
modifier|*
name|sr
parameter_list|,
name|ngx_http_post_subrequest_t
modifier|*
name|psr
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_internal_redirect
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_str_t
modifier|*
name|uri
parameter_list|,
name|ngx_str_t
modifier|*
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_named_location
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_http_cleanup_t
modifier|*
name|ngx_http_cleanup_add
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|ngx_http_output_header_filter_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_http_output_header_filter_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_output_body_filter_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_http_output_body_filter_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|chain
parameter_list|)
function_decl|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_http_output_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|chain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_write_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|chain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_set_disable_symlinks
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
parameter_list|,
name|ngx_str_t
modifier|*
name|path
parameter_list|,
name|ngx_open_file_info_t
modifier|*
name|of
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_get_forwarded_addr
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_addr_t
modifier|*
name|addr
parameter_list|,
name|ngx_array_t
modifier|*
name|headers
parameter_list|,
name|ngx_str_t
modifier|*
name|value
parameter_list|,
name|ngx_array_t
modifier|*
name|proxies
parameter_list|,
name|int
name|recursive
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_core_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_http_max_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_str_t
name|ngx_http_core_get_method
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|ngx_http_clear_content_length (r)
define|#
directive|define
name|ngx_http_clear_content_length
parameter_list|(
name|r
parameter_list|)
define|\                                                                               \
value|r->headers_out.content_length_n = -1;                                     \     if (r->headers_out.content_length) {                                      \         r->headers_out.content_length->hash = 0;                              \         r->headers_out.content_length = NULL;                                 \     }
end_define

begin_expr_stmt
unit|\
DECL|macro|ngx_http_clear_accept_ranges (r)
operator|#
name|define
name|ngx_http_clear_accept_ranges
argument_list|(
argument|r
argument_list|)
expr|\                                                                               \
name|r
operator|->
name|allow_ranges
operator|=
literal|0
expr_stmt|;
end_expr_stmt

begin_if_stmt
unit|\
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|accept_ranges
condition|)
block|{
block_content|\
name|r
operator|->
name|headers_out
operator|.
name|accept_ranges
operator|->
name|hash
operator|=
literal|0
expr_stmt|;
block_content|\
name|r
operator|->
name|headers_out
operator|.
name|accept_ranges
operator|=
name|NULL
expr_stmt|;
block_content|\
block|}
end_if_stmt

begin_define
DECL|macro|ngx_http_clear_last_modified (r)
define|#
directive|define
name|ngx_http_clear_last_modified
parameter_list|(
name|r
parameter_list|)
define|\                                                                               \
value|r->headers_out.last_modified_time = -1;                                   \     if (r->headers_out.last_modified) {                                       \         r->headers_out.last_modified->hash = 0;                               \         r->headers_out.last_modified = NULL;                                  \     }
end_define

begin_define
DECL|macro|ngx_http_clear_location (r)
define|#
directive|define
name|ngx_http_clear_location
parameter_list|(
name|r
parameter_list|)
define|\                                                                               \
value|if (r->headers_out.location) {                                            \         r->headers_out.location->hash = 0;                                    \         r->headers_out.location = NULL;                                       \     }
end_define

begin_define
DECL|macro|ngx_http_clear_etag (r)
define|#
directive|define
name|ngx_http_clear_etag
parameter_list|(
name|r
parameter_list|)
define|\                                                                               \
value|if (r->headers_out.etag) {                                                \         r->headers_out.etag->hash = 0;                                        \         r->headers_out.etag = NULL;                                           \     }
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CORE_H_INCLUDED_ */
end_comment

end_unit

