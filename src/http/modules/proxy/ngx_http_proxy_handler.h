begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_PROXY_HANDLER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_PROXY_HANDLER_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_PROXY_HANDLER_H_INCLUDED_
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

begin_typedef
DECL|enum|__anon29922e6d0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_HTTP_PROXY_CACHE_PASS
name|NGX_HTTP_PROXY_CACHE_PASS
init|=
literal|1
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_BYPASS
name|NGX_HTTP_PROXY_CACHE_BYPASS
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_AUTH
name|NGX_HTTP_PROXY_CACHE_AUTH
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_PGNC
name|NGX_HTTP_PROXY_CACHE_PGNC
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_MISS
name|NGX_HTTP_PROXY_CACHE_MISS
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_EXPR
name|NGX_HTTP_PROXY_CACHE_EXPR
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_AGED
name|NGX_HTTP_PROXY_CACHE_AGED
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_HIT
name|NGX_HTTP_PROXY_CACHE_HIT
DECL|typedef|ngx_http_proxy_state_e
block|}
name|ngx_http_proxy_state_e
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon29922e6d0203
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_HTTP_PROXY_CACHE_BPS
name|NGX_HTTP_PROXY_CACHE_BPS
init|=
literal|1
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_XAE
name|NGX_HTTP_PROXY_CACHE_XAE
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_CTL
name|NGX_HTTP_PROXY_CACHE_CTL
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_EXP
name|NGX_HTTP_PROXY_CACHE_EXP
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_MVD
name|NGX_HTTP_PROXY_CACHE_MVD
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_LMF
name|NGX_HTTP_PROXY_CACHE_LMF
block|,
DECL|enumerator|NGX_HTTP_PROXY_CACHE_PDE
name|NGX_HTTP_PROXY_CACHE_PDE
DECL|typedef|ngx_http_proxy_reason_e
block|}
name|ngx_http_proxy_reason_e
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29922e6d0308
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
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|host_header
name|ngx_str_t
name|host_header
decl_stmt|;
DECL|member|port_text
name|ngx_str_t
name|port_text
decl_stmt|;
DECL|member|location
name|ngx_str_t
modifier|*
name|location
decl_stmt|;
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|default_port
name|unsigned
name|default_port
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_proxy_upstream_conf_t
block|}
name|ngx_http_proxy_upstream_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29922e6d0408
typedef|typedef
struct|struct
block|{
DECL|member|send_lowat
name|size_t
name|send_lowat
decl_stmt|;
DECL|member|header_buffer_size
name|size_t
name|header_buffer_size
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
DECL|member|default_expires
name|time_t
name|default_expires
decl_stmt|;
DECL|member|lm_factor
name|ngx_int_t
name|lm_factor
decl_stmt|;
DECL|member|next_upstream
name|ngx_uint_t
name|next_upstream
decl_stmt|;
DECL|member|use_stale
name|ngx_uint_t
name|use_stale
decl_stmt|;
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
DECL|member|cyclic_temp_file
name|ngx_flag_t
name|cyclic_temp_file
decl_stmt|;
DECL|member|cache
name|ngx_flag_t
name|cache
decl_stmt|;
DECL|member|preserve_host
name|ngx_flag_t
name|preserve_host
decl_stmt|;
DECL|member|set_x_url
name|ngx_flag_t
name|set_x_url
decl_stmt|;
DECL|member|set_x_real_ip
name|ngx_flag_t
name|set_x_real_ip
decl_stmt|;
DECL|member|add_x_forwarded_for
name|ngx_flag_t
name|add_x_forwarded_for
decl_stmt|;
DECL|member|pass_server
name|ngx_flag_t
name|pass_server
decl_stmt|;
DECL|member|pass_x_accel_expires
name|ngx_flag_t
name|pass_x_accel_expires
decl_stmt|;
DECL|member|ignore_expires
name|ngx_flag_t
name|ignore_expires
decl_stmt|;
DECL|member|cache_path
name|ngx_path_t
modifier|*
name|cache_path
decl_stmt|;
DECL|member|temp_path
name|ngx_path_t
modifier|*
name|temp_path
decl_stmt|;
DECL|member|busy_lock
name|ngx_http_busy_lock_t
modifier|*
name|busy_lock
decl_stmt|;
DECL|member|upstream
name|ngx_http_proxy_upstream_conf_t
modifier|*
name|upstream
decl_stmt|;
DECL|member|peers
name|ngx_peers_t
modifier|*
name|peers
decl_stmt|;
DECL|typedef|ngx_http_proxy_loc_conf_t
block|}
name|ngx_http_proxy_loc_conf_t
typedef|;
end_typedef

begin_comment
comment|/*  * "EXPR/10/5/- 200/EXP/60 4"  * "MISS/-/-/B 503/-/- -"  * "EXPR/10/20/SB HIT/-/- -"  * "EXPR/10/15/NB HIT/-/- -"  */
end_comment

begin_typedef
DECL|struct|__anon29922e6d0508
typedef|typedef
struct|struct
block|{
DECL|member|cache_state
name|ngx_http_proxy_state_e
name|cache_state
decl_stmt|;
DECL|member|expired
name|time_t
name|expired
decl_stmt|;
DECL|member|bl_time
name|time_t
name|bl_time
decl_stmt|;
DECL|member|bl_state
name|ngx_uint_t
name|bl_state
decl_stmt|;
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|reason
name|ngx_http_proxy_reason_e
name|reason
decl_stmt|;
DECL|member|time
name|time_t
name|time
decl_stmt|;
DECL|member|expires
name|time_t
name|expires
decl_stmt|;
DECL|member|peer
name|ngx_str_t
modifier|*
name|peer
decl_stmt|;
DECL|typedef|ngx_http_proxy_state_t
block|}
name|ngx_http_proxy_state_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29922e6d0608
typedef|typedef
struct|struct
block|{
DECL|member|headers
name|ngx_list_t
name|headers
decl_stmt|;
if|#
directive|if
literal|0
block|ngx_table_t                      headers;
comment|/* it must be first field */
endif|#
directive|endif
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
DECL|member|expires
name|ngx_table_elt_t
modifier|*
name|expires
decl_stmt|;
DECL|member|cache_control
name|ngx_table_elt_t
modifier|*
name|cache_control
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
DECL|member|connection
name|ngx_table_elt_t
modifier|*
name|connection
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
DECL|member|content_encoding
name|ngx_table_elt_t
modifier|*
name|content_encoding
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
DECL|member|accept_ranges
name|ngx_table_elt_t
modifier|*
name|accept_ranges
decl_stmt|;
DECL|member|x_pad
name|ngx_table_elt_t
modifier|*
name|x_pad
decl_stmt|;
DECL|member|content_length_n
name|off_t
name|content_length_n
decl_stmt|;
DECL|typedef|ngx_http_proxy_headers_in_t
block|}
name|ngx_http_proxy_headers_in_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29922e6d0708
typedef|typedef
struct|struct
block|{
DECL|member|ctx
name|ngx_http_cache_ctx_t
name|ctx
decl_stmt|;
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|status_line
name|ngx_str_t
name|status_line
decl_stmt|;
DECL|member|headers_in
name|ngx_http_proxy_headers_in_t
name|headers_in
decl_stmt|;
DECL|typedef|ngx_http_proxy_cache_t
block|}
name|ngx_http_proxy_cache_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29922e6d0808
typedef|typedef
struct|struct
block|{
DECL|member|peer
name|ngx_peer_connection_t
name|peer
decl_stmt|;
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|status_line
name|ngx_str_t
name|status_line
decl_stmt|;
DECL|member|method
name|ngx_uint_t
name|method
decl_stmt|;
DECL|member|output_chain_ctx
name|ngx_output_chain_ctx_t
modifier|*
name|output_chain_ctx
decl_stmt|;
DECL|member|event_pipe
name|ngx_event_pipe_t
modifier|*
name|event_pipe
decl_stmt|;
DECL|member|headers_in
name|ngx_http_proxy_headers_in_t
name|headers_in
decl_stmt|;
DECL|typedef|ngx_http_proxy_upstream_t
block|}
name|ngx_http_proxy_upstream_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_proxy_ctx_t
typedef|typedef
name|struct
name|ngx_http_proxy_ctx_s
name|ngx_http_proxy_ctx_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_proxy_ctx_s
struct|struct
name|ngx_http_proxy_ctx_s
block|{
DECL|member|request
name|ngx_http_request_t
modifier|*
name|request
decl_stmt|;
DECL|member|lcf
name|ngx_http_proxy_loc_conf_t
modifier|*
name|lcf
decl_stmt|;
DECL|member|upstream
name|ngx_http_proxy_upstream_t
modifier|*
name|upstream
decl_stmt|;
DECL|member|cache
name|ngx_http_proxy_cache_t
modifier|*
name|cache
decl_stmt|;
DECL|member|header_in
name|ngx_buf_t
modifier|*
name|header_in
decl_stmt|;
DECL|member|busy_lock
name|ngx_http_busy_lock_ctx_t
name|busy_lock
decl_stmt|;
DECL|member|accel
name|unsigned
name|accel
range|:
literal|1
decl_stmt|;
DECL|member|cachable
name|unsigned
name|cachable
range|:
literal|1
decl_stmt|;
DECL|member|stale
name|unsigned
name|stale
range|:
literal|1
decl_stmt|;
DECL|member|try_busy_lock
name|unsigned
name|try_busy_lock
range|:
literal|1
decl_stmt|;
DECL|member|busy_locked
name|unsigned
name|busy_locked
range|:
literal|1
decl_stmt|;
DECL|member|valid_header_in
name|unsigned
name|valid_header_in
range|:
literal|1
decl_stmt|;
DECL|member|request_sent
name|unsigned
name|request_sent
range|:
literal|1
decl_stmt|;
DECL|member|header_sent
name|unsigned
name|header_sent
range|:
literal|1
decl_stmt|;
comment|/* used to parse an upstream HTTP header */
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|status_start
name|u_char
modifier|*
name|status_start
decl_stmt|;
DECL|member|status_end
name|u_char
modifier|*
name|status_end
decl_stmt|;
DECL|member|status_count
name|ngx_uint_t
name|status_count
decl_stmt|;
DECL|member|parse_state
name|ngx_uint_t
name|parse_state
decl_stmt|;
DECL|member|state
name|ngx_http_proxy_state_t
modifier|*
name|state
decl_stmt|;
DECL|member|states
name|ngx_array_t
name|states
decl_stmt|;
comment|/* of ngx_http_proxy_state_t */
comment|/*      * we declare "action" as "char *" because the actions are usually      * the static strings and in the "u_char *" case we have to override      * all the time their types      */
DECL|member|action
name|char
modifier|*
name|action
decl_stmt|;
DECL|member|saved_ctx
name|ngx_http_log_ctx_t
modifier|*
name|saved_ctx
decl_stmt|;
DECL|member|saved_handler
name|ngx_log_handler_pt
name|saved_handler
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon29922e6d0908
typedef|typedef
struct|struct
block|{
DECL|member|connection
name|ngx_uint_t
name|connection
decl_stmt|;
DECL|member|proxy
name|ngx_http_proxy_ctx_t
modifier|*
name|proxy
decl_stmt|;
DECL|typedef|ngx_http_proxy_log_ctx_t
block|}
name|ngx_http_proxy_log_ctx_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_PROXY_PARSE_NO_HEADER
define|#
directive|define
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
value|30
end_define

begin_define
DECL|macro|NGX_HTTP_PROXY_FT_ERROR
define|#
directive|define
name|NGX_HTTP_PROXY_FT_ERROR
value|0x02
end_define

begin_define
DECL|macro|NGX_HTTP_PROXY_FT_TIMEOUT
define|#
directive|define
name|NGX_HTTP_PROXY_FT_TIMEOUT
value|0x04
end_define

begin_define
DECL|macro|NGX_HTTP_PROXY_FT_INVALID_HEADER
define|#
directive|define
name|NGX_HTTP_PROXY_FT_INVALID_HEADER
value|0x08
end_define

begin_define
DECL|macro|NGX_HTTP_PROXY_FT_HTTP_500
define|#
directive|define
name|NGX_HTTP_PROXY_FT_HTTP_500
value|0x10
end_define

begin_define
DECL|macro|NGX_HTTP_PROXY_FT_HTTP_404
define|#
directive|define
name|NGX_HTTP_PROXY_FT_HTTP_404
value|0x20
end_define

begin_define
DECL|macro|NGX_HTTP_PROXY_FT_BUSY_LOCK
define|#
directive|define
name|NGX_HTTP_PROXY_FT_BUSY_LOCK
value|0x40
end_define

begin_define
DECL|macro|NGX_HTTP_PROXY_FT_MAX_WAITING
define|#
directive|define
name|NGX_HTTP_PROXY_FT_MAX_WAITING
value|0x80
end_define

begin_function_decl
name|int
name|ngx_http_proxy_request_upstream
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_FILE_CACHE
operator|)
end_if

begin_function_decl
name|int
name|ngx_http_proxy_get_cached_response
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_proxy_send_cached_response
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_proxy_is_cachable
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_proxy_update_cache
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_proxy_cache_busy_lock
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_http_proxy_check_broken_connection
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_proxy_busy_lock_handler
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_proxy_upstream_busy_lock
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_proxy_log_error
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_proxy_finalize_request
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|,
name|int
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_proxy_close_connection
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_proxy_parse_status_line
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_proxy_copy_header
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|,
name|ngx_http_proxy_headers_in_t
modifier|*
name|headers_in
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_proxy_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_http_header_t
name|ngx_http_proxy_headers_in
index|[]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_PROXY_HANDLER_H_INCLUDED_ */
end_comment

end_unit

