begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_UPSTREAM_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_UPSTREAM_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_UPSTREAM_H_INCLUDED_
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
file|<ngx_event.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_connect.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_pipe.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_ERROR
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_ERROR
value|0x00000002
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_TIMEOUT
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_TIMEOUT
value|0x00000004
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_INVALID_HEADER
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_INVALID_HEADER
value|0x00000008
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_500
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_500
value|0x00000010
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_502
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_502
value|0x00000020
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_503
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_503
value|0x00000040
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_504
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_504
value|0x00000080
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_403
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_403
value|0x00000100
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_404
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_404
value|0x00000200
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_429
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_429
value|0x00000400
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_UPDATING
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_UPDATING
value|0x00000800
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_BUSY_LOCK
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_BUSY_LOCK
value|0x00001000
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_MAX_WAITING
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_MAX_WAITING
value|0x00002000
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_NON_IDEMPOTENT
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_NON_IDEMPOTENT
value|0x00004000
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_NOLIVE
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_NOLIVE
value|0x40000000
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_OFF
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_OFF
value|0x80000000
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_STATUS
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_STATUS
value|(NGX_HTTP_UPSTREAM_FT_HTTP_500  \                                              |NGX_HTTP_UPSTREAM_FT_HTTP_502  \                                              |NGX_HTTP_UPSTREAM_FT_HTTP_503  \                                              |NGX_HTTP_UPSTREAM_FT_HTTP_504  \                                              |NGX_HTTP_UPSTREAM_FT_HTTP_403  \                                              |NGX_HTTP_UPSTREAM_FT_HTTP_404  \                                              |NGX_HTTP_UPSTREAM_FT_HTTP_429)
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_INVALID_HEADER
define|#
directive|define
name|NGX_HTTP_UPSTREAM_INVALID_HEADER
value|40
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_XA_REDIRECT
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_XA_REDIRECT
value|0x00000002
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_XA_EXPIRES
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_XA_EXPIRES
value|0x00000004
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_EXPIRES
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_EXPIRES
value|0x00000008
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_CACHE_CONTROL
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_CACHE_CONTROL
value|0x00000010
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_SET_COOKIE
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_SET_COOKIE
value|0x00000020
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_XA_LIMIT_RATE
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_XA_LIMIT_RATE
value|0x00000040
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_XA_BUFFERING
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_XA_BUFFERING
value|0x00000080
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_XA_CHARSET
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_XA_CHARSET
value|0x00000100
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_IGN_VARY
define|#
directive|define
name|NGX_HTTP_UPSTREAM_IGN_VARY
value|0x00000200
end_define

begin_typedef
DECL|struct|__anon2935b9cd0108
typedef|typedef
struct|struct
block|{
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|response_time
name|ngx_msec_t
name|response_time
decl_stmt|;
DECL|member|connect_time
name|ngx_msec_t
name|connect_time
decl_stmt|;
DECL|member|header_time
name|ngx_msec_t
name|header_time
decl_stmt|;
DECL|member|queue_time
name|ngx_msec_t
name|queue_time
decl_stmt|;
DECL|member|response_length
name|off_t
name|response_length
decl_stmt|;
DECL|member|bytes_received
name|off_t
name|bytes_received
decl_stmt|;
DECL|member|bytes_sent
name|off_t
name|bytes_sent
decl_stmt|;
DECL|member|peer
name|ngx_str_t
modifier|*
name|peer
decl_stmt|;
DECL|typedef|ngx_http_upstream_state_t
block|}
name|ngx_http_upstream_state_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2935b9cd0208
typedef|typedef
struct|struct
block|{
DECL|member|headers_in_hash
name|ngx_hash_t
name|headers_in_hash
decl_stmt|;
DECL|member|upstreams
name|ngx_array_t
name|upstreams
decl_stmt|;
comment|/* ngx_http_upstream_srv_conf_t */
DECL|typedef|ngx_http_upstream_main_conf_t
block|}
name|ngx_http_upstream_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_upstream_srv_conf_t
typedef|typedef
name|struct
name|ngx_http_upstream_srv_conf_s
name|ngx_http_upstream_srv_conf_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_upstream_init_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_http_upstream_init_pt
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_http_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_upstream_init_peer_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_http_upstream_init_peer_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2935b9cd0308
typedef|typedef
struct|struct
block|{
DECL|member|init_upstream
name|ngx_http_upstream_init_pt
name|init_upstream
decl_stmt|;
DECL|member|init
name|ngx_http_upstream_init_peer_pt
name|init
decl_stmt|;
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|typedef|ngx_http_upstream_peer_t
block|}
name|ngx_http_upstream_peer_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2935b9cd0408
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|addrs
name|ngx_addr_t
modifier|*
name|addrs
decl_stmt|;
DECL|member|naddrs
name|ngx_uint_t
name|naddrs
decl_stmt|;
DECL|member|weight
name|ngx_uint_t
name|weight
decl_stmt|;
DECL|member|max_conns
name|ngx_uint_t
name|max_conns
decl_stmt|;
DECL|member|max_fails
name|ngx_uint_t
name|max_fails
decl_stmt|;
DECL|member|fail_timeout
name|time_t
name|fail_timeout
decl_stmt|;
DECL|member|slow_start
name|ngx_msec_t
name|slow_start
decl_stmt|;
DECL|member|down
name|ngx_uint_t
name|down
decl_stmt|;
DECL|member|backup
name|unsigned
name|backup
range|:
literal|1
decl_stmt|;
name|NGX_COMPAT_BEGIN
argument_list|(
literal|6
argument_list|)
name|NGX_COMPAT_END
DECL|typedef|ngx_http_upstream_server_t
block|}
name|ngx_http_upstream_server_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_CREATE
define|#
directive|define
name|NGX_HTTP_UPSTREAM_CREATE
value|0x0001
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_WEIGHT
define|#
directive|define
name|NGX_HTTP_UPSTREAM_WEIGHT
value|0x0002
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_MAX_FAILS
define|#
directive|define
name|NGX_HTTP_UPSTREAM_MAX_FAILS
value|0x0004
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FAIL_TIMEOUT
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FAIL_TIMEOUT
value|0x0008
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_DOWN
define|#
directive|define
name|NGX_HTTP_UPSTREAM_DOWN
value|0x0010
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_BACKUP
define|#
directive|define
name|NGX_HTTP_UPSTREAM_BACKUP
value|0x0020
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_MAX_CONNS
define|#
directive|define
name|NGX_HTTP_UPSTREAM_MAX_CONNS
value|0x0100
end_define

begin_struct
DECL|struct|ngx_http_upstream_srv_conf_s
struct|struct
name|ngx_http_upstream_srv_conf_s
block|{
DECL|member|peer
name|ngx_http_upstream_peer_t
name|peer
decl_stmt|;
DECL|member|srv_conf
name|void
modifier|*
modifier|*
name|srv_conf
decl_stmt|;
DECL|member|servers
name|ngx_array_t
modifier|*
name|servers
decl_stmt|;
comment|/* ngx_http_upstream_server_t */
DECL|member|flags
name|ngx_uint_t
name|flags
decl_stmt|;
DECL|member|host
name|ngx_str_t
name|host
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
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|no_port
name|ngx_uint_t
name|no_port
decl_stmt|;
comment|/* unsigned no_port:1 */
if|#
directive|if
operator|(
name|NGX_HTTP_UPSTREAM_ZONE
operator|)
DECL|member|shm_zone
name|ngx_shm_zone_t
modifier|*
name|shm_zone
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2935b9cd0508
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|ngx_addr_t
modifier|*
name|addr
decl_stmt|;
DECL|member|value
name|ngx_http_complex_value_t
modifier|*
name|value
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_TRANSPARENT_PROXY
operator|)
DECL|member|transparent
name|ngx_uint_t
name|transparent
decl_stmt|;
comment|/* unsigned  transparent:1; */
endif|#
directive|endif
DECL|typedef|ngx_http_upstream_local_t
block|}
name|ngx_http_upstream_local_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2935b9cd0608
typedef|typedef
struct|struct
block|{
DECL|member|upstream
name|ngx_http_upstream_srv_conf_t
modifier|*
name|upstream
decl_stmt|;
DECL|member|connect_timeout
name|ngx_msec_t
name|connect_timeout
decl_stmt|;
DECL|member|send_timeout
name|ngx_msec_t
name|send_timeout
decl_stmt|;
DECL|member|read_timeout
name|ngx_msec_t
name|read_timeout
decl_stmt|;
DECL|member|next_upstream_timeout
name|ngx_msec_t
name|next_upstream_timeout
decl_stmt|;
DECL|member|send_lowat
name|size_t
name|send_lowat
decl_stmt|;
DECL|member|buffer_size
name|size_t
name|buffer_size
decl_stmt|;
DECL|member|limit_rate
name|size_t
name|limit_rate
decl_stmt|;
DECL|member|busy_buffers_size
name|size_t
name|busy_buffers_size
decl_stmt|;
DECL|member|max_temp_file_size
name|size_t
name|max_temp_file_size
decl_stmt|;
DECL|member|temp_file_write_size
name|size_t
name|temp_file_write_size
decl_stmt|;
DECL|member|busy_buffers_size_conf
name|size_t
name|busy_buffers_size_conf
decl_stmt|;
DECL|member|max_temp_file_size_conf
name|size_t
name|max_temp_file_size_conf
decl_stmt|;
DECL|member|temp_file_write_size_conf
name|size_t
name|temp_file_write_size_conf
decl_stmt|;
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
DECL|member|ignore_headers
name|ngx_uint_t
name|ignore_headers
decl_stmt|;
DECL|member|next_upstream
name|ngx_uint_t
name|next_upstream
decl_stmt|;
DECL|member|store_access
name|ngx_uint_t
name|store_access
decl_stmt|;
DECL|member|next_upstream_tries
name|ngx_uint_t
name|next_upstream_tries
decl_stmt|;
DECL|member|buffering
name|ngx_flag_t
name|buffering
decl_stmt|;
DECL|member|request_buffering
name|ngx_flag_t
name|request_buffering
decl_stmt|;
DECL|member|pass_request_headers
name|ngx_flag_t
name|pass_request_headers
decl_stmt|;
DECL|member|pass_request_body
name|ngx_flag_t
name|pass_request_body
decl_stmt|;
DECL|member|ignore_client_abort
name|ngx_flag_t
name|ignore_client_abort
decl_stmt|;
DECL|member|intercept_errors
name|ngx_flag_t
name|intercept_errors
decl_stmt|;
DECL|member|cyclic_temp_file
name|ngx_flag_t
name|cyclic_temp_file
decl_stmt|;
DECL|member|force_ranges
name|ngx_flag_t
name|force_ranges
decl_stmt|;
DECL|member|temp_path
name|ngx_path_t
modifier|*
name|temp_path
decl_stmt|;
DECL|member|hide_headers_hash
name|ngx_hash_t
name|hide_headers_hash
decl_stmt|;
DECL|member|hide_headers
name|ngx_array_t
modifier|*
name|hide_headers
decl_stmt|;
DECL|member|pass_headers
name|ngx_array_t
modifier|*
name|pass_headers
decl_stmt|;
DECL|member|local
name|ngx_http_upstream_local_t
modifier|*
name|local
decl_stmt|;
DECL|member|socket_keepalive
name|ngx_flag_t
name|socket_keepalive
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_CACHE
operator|)
DECL|member|cache_zone
name|ngx_shm_zone_t
modifier|*
name|cache_zone
decl_stmt|;
DECL|member|cache_value
name|ngx_http_complex_value_t
modifier|*
name|cache_value
decl_stmt|;
DECL|member|cache_min_uses
name|ngx_uint_t
name|cache_min_uses
decl_stmt|;
DECL|member|cache_use_stale
name|ngx_uint_t
name|cache_use_stale
decl_stmt|;
DECL|member|cache_methods
name|ngx_uint_t
name|cache_methods
decl_stmt|;
DECL|member|cache_max_range_offset
name|off_t
name|cache_max_range_offset
decl_stmt|;
DECL|member|cache_lock
name|ngx_flag_t
name|cache_lock
decl_stmt|;
DECL|member|cache_lock_timeout
name|ngx_msec_t
name|cache_lock_timeout
decl_stmt|;
DECL|member|cache_lock_age
name|ngx_msec_t
name|cache_lock_age
decl_stmt|;
DECL|member|cache_revalidate
name|ngx_flag_t
name|cache_revalidate
decl_stmt|;
DECL|member|cache_convert_head
name|ngx_flag_t
name|cache_convert_head
decl_stmt|;
DECL|member|cache_background_update
name|ngx_flag_t
name|cache_background_update
decl_stmt|;
DECL|member|cache_valid
name|ngx_array_t
modifier|*
name|cache_valid
decl_stmt|;
DECL|member|cache_bypass
name|ngx_array_t
modifier|*
name|cache_bypass
decl_stmt|;
DECL|member|cache_purge
name|ngx_array_t
modifier|*
name|cache_purge
decl_stmt|;
DECL|member|no_cache
name|ngx_array_t
modifier|*
name|no_cache
decl_stmt|;
endif|#
directive|endif
DECL|member|store_lengths
name|ngx_array_t
modifier|*
name|store_lengths
decl_stmt|;
DECL|member|store_values
name|ngx_array_t
modifier|*
name|store_values
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_CACHE
operator|)
DECL|member|cache
name|signed
name|cache
range|:
literal|2
decl_stmt|;
endif|#
directive|endif
DECL|member|store
name|signed
name|store
range|:
literal|2
decl_stmt|;
DECL|member|intercept_404
name|unsigned
name|intercept_404
range|:
literal|1
decl_stmt|;
DECL|member|change_buffering
name|unsigned
name|change_buffering
range|:
literal|1
decl_stmt|;
DECL|member|pass_trailers
name|unsigned
name|pass_trailers
range|:
literal|1
decl_stmt|;
DECL|member|preserve_output
name|unsigned
name|preserve_output
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
operator|||
name|NGX_COMPAT
operator|)
DECL|member|ssl
name|ngx_ssl_t
modifier|*
name|ssl
decl_stmt|;
DECL|member|ssl_session_reuse
name|ngx_flag_t
name|ssl_session_reuse
decl_stmt|;
DECL|member|ssl_name
name|ngx_http_complex_value_t
modifier|*
name|ssl_name
decl_stmt|;
DECL|member|ssl_server_name
name|ngx_flag_t
name|ssl_server_name
decl_stmt|;
DECL|member|ssl_verify
name|ngx_flag_t
name|ssl_verify
decl_stmt|;
DECL|member|ssl_certificate
name|ngx_http_complex_value_t
modifier|*
name|ssl_certificate
decl_stmt|;
DECL|member|ssl_certificate_key
name|ngx_http_complex_value_t
modifier|*
name|ssl_certificate_key
decl_stmt|;
DECL|member|ssl_passwords
name|ngx_array_t
modifier|*
name|ssl_passwords
decl_stmt|;
endif|#
directive|endif
DECL|member|module
name|ngx_str_t
name|module
decl_stmt|;
name|NGX_COMPAT_BEGIN
argument_list|(
literal|2
argument_list|)
name|NGX_COMPAT_END
DECL|typedef|ngx_http_upstream_conf_t
block|}
name|ngx_http_upstream_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2935b9cd0708
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|handler
name|ngx_http_header_handler_pt
name|handler
decl_stmt|;
DECL|member|offset
name|ngx_uint_t
name|offset
decl_stmt|;
DECL|member|copy_handler
name|ngx_http_header_handler_pt
name|copy_handler
decl_stmt|;
DECL|member|conf
name|ngx_uint_t
name|conf
decl_stmt|;
DECL|member|redirect
name|ngx_uint_t
name|redirect
decl_stmt|;
comment|/* unsigned   redirect:1; */
DECL|typedef|ngx_http_upstream_header_t
block|}
name|ngx_http_upstream_header_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2935b9cd0808
typedef|typedef
struct|struct
block|{
DECL|member|headers
name|ngx_list_t
name|headers
decl_stmt|;
DECL|member|trailers
name|ngx_list_t
name|trailers
decl_stmt|;
DECL|member|status_n
name|ngx_uint_t
name|status_n
decl_stmt|;
DECL|member|status_line
name|ngx_str_t
name|status_line
decl_stmt|;
DECL|member|status
name|ngx_table_elt_t
modifier|*
name|status
decl_stmt|;
DECL|member|date
name|ngx_table_elt_t
modifier|*
name|date
decl_stmt|;
DECL|member|server
name|ngx_table_elt_t
modifier|*
name|server
decl_stmt|;
DECL|member|connection
name|ngx_table_elt_t
modifier|*
name|connection
decl_stmt|;
DECL|member|expires
name|ngx_table_elt_t
modifier|*
name|expires
decl_stmt|;
DECL|member|etag
name|ngx_table_elt_t
modifier|*
name|etag
decl_stmt|;
DECL|member|x_accel_expires
name|ngx_table_elt_t
modifier|*
name|x_accel_expires
decl_stmt|;
DECL|member|x_accel_redirect
name|ngx_table_elt_t
modifier|*
name|x_accel_redirect
decl_stmt|;
DECL|member|x_accel_limit_rate
name|ngx_table_elt_t
modifier|*
name|x_accel_limit_rate
decl_stmt|;
DECL|member|content_type
name|ngx_table_elt_t
modifier|*
name|content_type
decl_stmt|;
DECL|member|content_length
name|ngx_table_elt_t
modifier|*
name|content_length
decl_stmt|;
DECL|member|last_modified
name|ngx_table_elt_t
modifier|*
name|last_modified
decl_stmt|;
DECL|member|location
name|ngx_table_elt_t
modifier|*
name|location
decl_stmt|;
DECL|member|refresh
name|ngx_table_elt_t
modifier|*
name|refresh
decl_stmt|;
DECL|member|www_authenticate
name|ngx_table_elt_t
modifier|*
name|www_authenticate
decl_stmt|;
DECL|member|transfer_encoding
name|ngx_table_elt_t
modifier|*
name|transfer_encoding
decl_stmt|;
DECL|member|vary
name|ngx_table_elt_t
modifier|*
name|vary
decl_stmt|;
DECL|member|cache_control
name|ngx_table_elt_t
modifier|*
name|cache_control
decl_stmt|;
DECL|member|set_cookie
name|ngx_table_elt_t
modifier|*
name|set_cookie
decl_stmt|;
DECL|member|content_length_n
name|off_t
name|content_length_n
decl_stmt|;
DECL|member|last_modified_time
name|time_t
name|last_modified_time
decl_stmt|;
DECL|member|connection_close
name|unsigned
name|connection_close
range|:
literal|1
decl_stmt|;
DECL|member|chunked
name|unsigned
name|chunked
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_upstream_headers_in_t
block|}
name|ngx_http_upstream_headers_in_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2935b9cd0908
typedef|typedef
struct|struct
block|{
DECL|member|host
name|ngx_str_t
name|host
decl_stmt|;
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|no_port
name|ngx_uint_t
name|no_port
decl_stmt|;
comment|/* unsigned no_port:1 */
DECL|member|naddrs
name|ngx_uint_t
name|naddrs
decl_stmt|;
DECL|member|addrs
name|ngx_resolver_addr_t
modifier|*
name|addrs
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
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|ctx
name|ngx_resolver_ctx_t
modifier|*
name|ctx
decl_stmt|;
DECL|typedef|ngx_http_upstream_resolved_t
block|}
name|ngx_http_upstream_resolved_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_upstream_handler_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_http_upstream_handler_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_upstream_t
modifier|*
name|u
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_http_upstream_s
struct|struct
name|ngx_http_upstream_s
block|{
DECL|member|read_event_handler
name|ngx_http_upstream_handler_pt
name|read_event_handler
decl_stmt|;
DECL|member|write_event_handler
name|ngx_http_upstream_handler_pt
name|write_event_handler
decl_stmt|;
DECL|member|peer
name|ngx_peer_connection_t
name|peer
decl_stmt|;
DECL|member|pipe
name|ngx_event_pipe_t
modifier|*
name|pipe
decl_stmt|;
DECL|member|request_bufs
name|ngx_chain_t
modifier|*
name|request_bufs
decl_stmt|;
DECL|member|output
name|ngx_output_chain_ctx_t
name|output
decl_stmt|;
DECL|member|writer
name|ngx_chain_writer_ctx_t
name|writer
decl_stmt|;
DECL|member|conf
name|ngx_http_upstream_conf_t
modifier|*
name|conf
decl_stmt|;
DECL|member|upstream
name|ngx_http_upstream_srv_conf_t
modifier|*
name|upstream
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_CACHE
operator|)
DECL|member|caches
name|ngx_array_t
modifier|*
name|caches
decl_stmt|;
endif|#
directive|endif
DECL|member|headers_in
name|ngx_http_upstream_headers_in_t
name|headers_in
decl_stmt|;
DECL|member|resolved
name|ngx_http_upstream_resolved_t
modifier|*
name|resolved
decl_stmt|;
DECL|member|from_client
name|ngx_buf_t
name|from_client
decl_stmt|;
DECL|member|buffer
name|ngx_buf_t
name|buffer
decl_stmt|;
DECL|member|length
name|off_t
name|length
decl_stmt|;
DECL|member|out_bufs
name|ngx_chain_t
modifier|*
name|out_bufs
decl_stmt|;
DECL|member|busy_bufs
name|ngx_chain_t
modifier|*
name|busy_bufs
decl_stmt|;
DECL|member|free_bufs
name|ngx_chain_t
modifier|*
name|free_bufs
decl_stmt|;
DECL|member|input_filter_init
name|ngx_int_t
function_decl|(
modifier|*
name|input_filter_init
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
DECL|member|input_filter
name|ngx_int_t
function_decl|(
modifier|*
name|input_filter
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|ssize_t
name|bytes
parameter_list|)
function_decl|;
DECL|member|input_filter_ctx
name|void
modifier|*
name|input_filter_ctx
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_CACHE
operator|)
DECL|member|create_key
name|ngx_int_t
function_decl|(
modifier|*
name|create_key
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
endif|#
directive|endif
DECL|member|create_request
name|ngx_int_t
function_decl|(
modifier|*
name|create_request
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|reinit_request
name|ngx_int_t
function_decl|(
modifier|*
name|reinit_request
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|process_header
name|ngx_int_t
function_decl|(
modifier|*
name|process_header
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|abort_request
name|void
function_decl|(
modifier|*
name|abort_request
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|finalize_request
name|void
function_decl|(
modifier|*
name|finalize_request
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_int_t
name|rc
parameter_list|)
function_decl|;
DECL|member|rewrite_redirect
name|ngx_int_t
function_decl|(
modifier|*
name|rewrite_redirect
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_table_elt_t
modifier|*
name|h
parameter_list|,
name|size_t
name|prefix
parameter_list|)
function_decl|;
DECL|member|rewrite_cookie
name|ngx_int_t
function_decl|(
modifier|*
name|rewrite_cookie
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_table_elt_t
modifier|*
name|h
parameter_list|)
function_decl|;
DECL|member|start_time
name|ngx_msec_t
name|start_time
decl_stmt|;
DECL|member|state
name|ngx_http_upstream_state_t
modifier|*
name|state
decl_stmt|;
DECL|member|method
name|ngx_str_t
name|method
decl_stmt|;
DECL|member|schema
name|ngx_str_t
name|schema
decl_stmt|;
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
operator|||
name|NGX_COMPAT
operator|)
DECL|member|ssl_name
name|ngx_str_t
name|ssl_name
decl_stmt|;
endif|#
directive|endif
DECL|member|cleanup
name|ngx_http_cleanup_pt
modifier|*
name|cleanup
decl_stmt|;
DECL|member|store
name|unsigned
name|store
range|:
literal|1
decl_stmt|;
DECL|member|cacheable
name|unsigned
name|cacheable
range|:
literal|1
decl_stmt|;
DECL|member|accel
name|unsigned
name|accel
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
name|NGX_HTTP_CACHE
operator|)
DECL|member|cache_status
name|unsigned
name|cache_status
range|:
literal|3
decl_stmt|;
endif|#
directive|endif
DECL|member|buffering
name|unsigned
name|buffering
range|:
literal|1
decl_stmt|;
DECL|member|keepalive
name|unsigned
name|keepalive
range|:
literal|1
decl_stmt|;
DECL|member|upgrade
name|unsigned
name|upgrade
range|:
literal|1
decl_stmt|;
DECL|member|error
name|unsigned
name|error
range|:
literal|1
decl_stmt|;
DECL|member|request_sent
name|unsigned
name|request_sent
range|:
literal|1
decl_stmt|;
DECL|member|request_body_sent
name|unsigned
name|request_body_sent
range|:
literal|1
decl_stmt|;
DECL|member|request_body_blocked
name|unsigned
name|request_body_blocked
range|:
literal|1
decl_stmt|;
DECL|member|header_sent
name|unsigned
name|header_sent
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2935b9cd0a08
typedef|typedef
struct|struct
block|{
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|mask
name|ngx_uint_t
name|mask
decl_stmt|;
DECL|typedef|ngx_http_upstream_next_t
block|}
name|ngx_http_upstream_next_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2935b9cd0b08
typedef|typedef
struct|struct
block|{
DECL|member|key
name|ngx_str_t
name|key
decl_stmt|;
DECL|member|value
name|ngx_str_t
name|value
decl_stmt|;
DECL|member|skip_empty
name|ngx_uint_t
name|skip_empty
decl_stmt|;
DECL|typedef|ngx_http_upstream_param_t
block|}
name|ngx_http_upstream_param_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_http_upstream_create
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_upstream_init
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_upstream_non_buffered_filter_init
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_upstream_non_buffered_filter
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|ssize_t
name|bytes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_http_upstream_srv_conf_t
modifier|*
name|ngx_http_upstream_add
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_url_t
modifier|*
name|u
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_http_upstream_bind_set_slot
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_http_upstream_param_set_slot
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_upstream_hide_headers_hash
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_http_upstream_conf_t
modifier|*
name|conf
parameter_list|,
name|ngx_http_upstream_conf_t
modifier|*
name|prev
parameter_list|,
name|ngx_str_t
modifier|*
name|default_hide_headers
parameter_list|,
name|ngx_hash_init_t
modifier|*
name|hash
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_http_conf_upstream_srv_conf (uscf,module)
define|#
directive|define
name|ngx_http_conf_upstream_srv_conf
parameter_list|(
name|uscf
parameter_list|,
name|module
parameter_list|)
define|\
value|uscf->srv_conf[module.ctx_index]
end_define

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_upstream_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_conf_bitmask_t
name|ngx_http_upstream_cache_method_mask
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_conf_bitmask_t
name|ngx_http_upstream_ignore_headers_masks
index|[]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_UPSTREAM_H_INCLUDED_ */
end_comment

end_unit

