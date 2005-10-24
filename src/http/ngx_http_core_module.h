begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_array.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon2791f8ac0108
typedef|typedef
struct|struct
block|{
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
DECL|typedef|ngx_http_listen_conf_t
block|}
name|ngx_http_listen_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2791f8ac0208
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|family
name|int
name|family
decl_stmt|;
DECL|member|file_name
name|ngx_str_t
name|file_name
decl_stmt|;
DECL|member|line
name|ngx_int_t
name|line
decl_stmt|;
DECL|member|conf
name|ngx_http_listen_conf_t
name|conf
decl_stmt|;
DECL|typedef|ngx_http_listen_t
block|}
name|ngx_http_listen_t
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2791f8ac0303
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_HTTP_FIND_CONFIG_PHASE
name|NGX_HTTP_FIND_CONFIG_PHASE
init|=
literal|0
block|,
DECL|enumerator|NGX_HTTP_REWRITE_PHASE
name|NGX_HTTP_REWRITE_PHASE
block|,
DECL|enumerator|NGX_HTTP_ACCESS_PHASE
name|NGX_HTTP_ACCESS_PHASE
block|,
DECL|enumerator|NGX_HTTP_CONTENT_PHASE
name|NGX_HTTP_CONTENT_PHASE
block|,
DECL|enumerator|NGX_HTTP_LAST_PHASE
name|NGX_HTTP_LAST_PHASE
DECL|typedef|ngx_http_phases
block|}
name|ngx_http_phases
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2791f8ac0408
typedef|typedef
struct|struct
block|{
DECL|member|handlers
name|ngx_array_t
name|handlers
decl_stmt|;
DECL|member|type
name|ngx_int_t
name|type
decl_stmt|;
comment|/* NGX_OK, NGX_DECLINED */
DECL|typedef|ngx_http_phase_t
block|}
name|ngx_http_phase_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2791f8ac0508
typedef|typedef
struct|struct
block|{
DECL|member|servers
name|ngx_array_t
name|servers
decl_stmt|;
comment|/* ngx_http_core_srv_conf_t */
DECL|member|phases
name|ngx_http_phase_t
name|phases
index|[
name|NGX_HTTP_LAST_PHASE
index|]
decl_stmt|;
DECL|member|log_handler
name|ngx_http_handler_pt
name|log_handler
decl_stmt|;
DECL|member|headers_in_hash
name|ngx_hash_t
name|headers_in_hash
decl_stmt|;
DECL|member|variables_hash
name|ngx_hash_t
name|variables_hash
decl_stmt|;
DECL|member|server_names_hash
name|ngx_uint_t
name|server_names_hash
decl_stmt|;
DECL|member|server_names_hash_threshold
name|ngx_uint_t
name|server_names_hash_threshold
decl_stmt|;
DECL|member|max_server_name_len
name|size_t
name|max_server_name_len
decl_stmt|;
DECL|member|variables
name|ngx_array_t
name|variables
decl_stmt|;
comment|/* ngx_http_variable_t */
DECL|member|all_variables
name|ngx_array_t
name|all_variables
decl_stmt|;
comment|/* ngx_http_variable_t */
DECL|typedef|ngx_http_core_main_conf_t
block|}
name|ngx_http_core_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2791f8ac0608
typedef|typedef
struct|struct
block|{
comment|/*      * array of the ngx_http_core_loc_conf_t,      * used in the translation handler and in the merge phase      */
DECL|member|locations
name|ngx_array_t
name|locations
decl_stmt|;
comment|/* array of the ngx_http_listen_t, "listen" directive */
DECL|member|listen
name|ngx_array_t
name|listen
decl_stmt|;
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
DECL|member|restrict_host_names
name|ngx_uint_t
name|restrict_host_names
decl_stmt|;
DECL|member|ignore_invalid_headers
name|ngx_flag_t
name|ignore_invalid_headers
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
DECL|struct|__anon2791f8ac0708
typedef|typedef
struct|struct
block|{
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|port_text
name|ngx_str_t
name|port_text
decl_stmt|;
DECL|member|addrs
name|ngx_array_t
name|addrs
decl_stmt|;
comment|/* array of ngx_http_in_addr_t */
DECL|typedef|ngx_http_in_port_t
block|}
name|ngx_http_in_port_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_in_addr_s
struct|struct
name|ngx_http_in_addr_s
block|{
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|names
name|ngx_array_t
name|names
decl_stmt|;
comment|/* array of ngx_http_server_name_t */
DECL|member|hash
name|ngx_array_t
modifier|*
name|hash
decl_stmt|;
comment|/* hash of ngx_http_server_name_t */
DECL|member|wildcards
name|ngx_array_t
name|wildcards
decl_stmt|;
comment|/* array of ngx_http_server_name_t */
comment|/* the default server configuration for this address:port */
DECL|member|core_srv_conf
name|ngx_http_core_srv_conf_t
modifier|*
name|core_srv_conf
decl_stmt|;
DECL|member|conf
name|ngx_http_listen_conf_t
name|conf
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2791f8ac0808
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|core_srv_conf
name|ngx_http_core_srv_conf_t
modifier|*
name|core_srv_conf
decl_stmt|;
comment|/* virtual name server conf */
DECL|member|wildcard
name|ngx_uint_t
name|wildcard
decl_stmt|;
comment|/* unsigned  wildcard:1 */
DECL|typedef|ngx_http_server_name_t
block|}
name|ngx_http_server_name_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_http_server_names_hash_key (key,name,len,prime)
define|#
directive|define
name|ngx_http_server_names_hash_key
parameter_list|(
name|key
parameter_list|,
name|name
parameter_list|,
name|len
parameter_list|,
name|prime
parameter_list|)
define|\
value|{                                                                   \             ngx_uint_t  n;                                                  \             for (key = 0, n = 0; n< len; n++) {                            \                 key += name[n];                                             \             }                                                               \             key %= prime;                                                   \         }
end_define

begin_define
DECL|macro|NGX_HTTP_TYPES_HASH_PRIME
define|#
directive|define
name|NGX_HTTP_TYPES_HASH_PRIME
value|13
end_define

begin_define
DECL|macro|ngx_http_types_hash_key (key,ext)
define|#
directive|define
name|ngx_http_types_hash_key
parameter_list|(
name|key
parameter_list|,
name|ext
parameter_list|)
define|\
value|{                                                                   \             ngx_uint_t  n;                                                  \             for (key = 0, n = 0; n< ext.len; n++) {                        \                 key += ext.data[n];                                         \             }                                                               \             key %= NGX_HTTP_TYPES_HASH_PRIME;                               \         }
end_define

begin_typedef
DECL|struct|__anon2791f8ac0908
typedef|typedef
struct|struct
block|{
DECL|member|exten
name|ngx_str_t
name|exten
decl_stmt|;
DECL|member|type
name|ngx_str_t
name|type
decl_stmt|;
DECL|typedef|ngx_http_type_t
block|}
name|ngx_http_type_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2791f8ac0a08
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
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|typedef|ngx_http_err_page_t
block|}
name|ngx_http_err_page_t
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
name|ngx_regex_t
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
comment|/* "if () {}" block */
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
DECL|member|alias
name|unsigned
name|alias
range|:
literal|1
decl_stmt|;
comment|/* array of inclusive ngx_http_core_loc_conf_t */
DECL|member|locations
name|ngx_array_t
name|locations
decl_stmt|;
comment|/* pointer to the modules' loc_conf */
DECL|member|loc_conf
name|void
modifier|*
modifier|*
name|loc_conf
decl_stmt|;
DECL|member|handler
name|ngx_http_handler_pt
name|handler
decl_stmt|;
DECL|member|root
name|ngx_str_t
name|root
decl_stmt|;
comment|/* root, alias */
DECL|member|types
name|ngx_array_t
modifier|*
name|types
decl_stmt|;
DECL|member|default_type
name|ngx_str_t
name|default_type
decl_stmt|;
DECL|member|client_max_body_size
name|size_t
name|client_max_body_size
decl_stmt|;
comment|/* client_max_body_size */
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
DECL|member|keepalive_header
name|time_t
name|keepalive_header
decl_stmt|;
comment|/* keepalive_timeout */
DECL|member|satisfy_any
name|ngx_flag_t
name|satisfy_any
decl_stmt|;
comment|/* satisfy_any */
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
DECL|member|log_not_found
name|ngx_flag_t
name|log_not_found
decl_stmt|;
comment|/* log_not_found */
DECL|member|error_pages
name|ngx_array_t
modifier|*
name|error_pages
decl_stmt|;
comment|/* error_page */
DECL|member|client_body_temp_path
name|ngx_path_t
modifier|*
name|client_body_temp_path
decl_stmt|;
comment|/* client_body_temp_path */
DECL|member|open_files
name|ngx_http_cache_hash_t
modifier|*
name|open_files
decl_stmt|;
DECL|member|err_log
name|ngx_log_t
modifier|*
name|err_log
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

begin_decl_stmt
specifier|extern
name|ngx_http_module_t
name|ngx_http_core_module_ctx
decl_stmt|;
end_decl_stmt

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

begin_function_decl
name|ngx_int_t
name|ngx_http_find_location_config
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
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
name|ngx_int_t
name|ngx_http_set_exten
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CORE_H_INCLUDED_ */
end_comment

end_unit

