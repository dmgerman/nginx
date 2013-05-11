begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_H_INCLUDED_
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
DECL|typedef|ngx_http_request_t
typedef|typedef
name|struct
name|ngx_http_request_s
name|ngx_http_request_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_upstream_t
typedef|typedef
name|struct
name|ngx_http_upstream_s
name|ngx_http_upstream_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_cache_t
typedef|typedef
name|struct
name|ngx_http_cache_s
name|ngx_http_cache_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_file_cache_t
typedef|typedef
name|struct
name|ngx_http_file_cache_s
name|ngx_http_file_cache_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_log_ctx_t
typedef|typedef
name|struct
name|ngx_http_log_ctx_s
name|ngx_http_log_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_chunked_t
typedef|typedef
name|struct
name|ngx_http_chunked_s
name|ngx_http_chunked_t
typedef|;
end_typedef

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_SPDY
operator|)
end_if

begin_typedef
DECL|typedef|ngx_http_spdy_stream_t
typedef|typedef
name|struct
name|ngx_http_spdy_stream_s
name|ngx_http_spdy_stream_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_http_header_handler_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_http_header_handler_pt
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
name|ngx_uint_t
name|offset
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_log_handler_pt
typedef|typedef
name|u_char
modifier|*
function_decl|(
modifier|*
name|ngx_http_log_handler_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_request_t
modifier|*
name|sr
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_typedef

begin_include
include|#
directive|include
file|<ngx_http_variables.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_request.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_script.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_upstream.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_upstream_round_robin.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_busy_lock.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_core_module.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_SPDY
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_http_spdy.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_CACHE
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_http_cache.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_SSI
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_http_ssi_filter_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_http_ssl_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_struct
DECL|struct|ngx_http_log_ctx_s
struct|struct
name|ngx_http_log_ctx_s
block|{
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
decl_stmt|;
DECL|member|request
name|ngx_http_request_t
modifier|*
name|request
decl_stmt|;
DECL|member|current_request
name|ngx_http_request_t
modifier|*
name|current_request
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|ngx_http_chunked_s
struct|struct
name|ngx_http_chunked_s
block|{
DECL|member|state
name|ngx_uint_t
name|state
decl_stmt|;
DECL|member|size
name|off_t
name|size
decl_stmt|;
DECL|member|length
name|off_t
name|length
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2923da600108
typedef|typedef
struct|struct
block|{
DECL|member|http_version
name|ngx_uint_t
name|http_version
decl_stmt|;
DECL|member|code
name|ngx_uint_t
name|code
decl_stmt|;
DECL|member|count
name|ngx_uint_t
name|count
decl_stmt|;
DECL|member|start
name|u_char
modifier|*
name|start
decl_stmt|;
DECL|member|end
name|u_char
modifier|*
name|end
decl_stmt|;
DECL|typedef|ngx_http_status_t
block|}
name|ngx_http_status_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_http_get_module_ctx (r,module)
define|#
directive|define
name|ngx_http_get_module_ctx
parameter_list|(
name|r
parameter_list|,
name|module
parameter_list|)
value|(r)->ctx[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_http_set_ctx (r,c,module)
define|#
directive|define
name|ngx_http_set_ctx
parameter_list|(
name|r
parameter_list|,
name|c
parameter_list|,
name|module
parameter_list|)
value|r->ctx[module.ctx_index] = c;
end_define

begin_function_decl
name|ngx_int_t
name|ngx_http_add_location
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_queue_t
modifier|*
modifier|*
name|locations
parameter_list|,
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_add_listen
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_http_core_srv_conf_t
modifier|*
name|cscf
parameter_list|,
name|ngx_http_listen_opt_t
modifier|*
name|lsopt
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_init_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_close_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
operator|&&
name|defined
name|SSL_CTRL_SET_TLSEXT_HOSTNAME
operator|)
end_if

begin_function_decl
name|int
name|ngx_http_ssl_servername
parameter_list|(
name|ngx_ssl_conn_t
modifier|*
name|ssl_conn
parameter_list|,
name|int
modifier|*
name|ad
parameter_list|,
name|void
modifier|*
name|arg
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|ngx_int_t
name|ngx_http_parse_request_line
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_buf_t
modifier|*
name|b
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_parse_uri
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_parse_complex_uri
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_uint_t
name|merge_slashes
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_parse_status_line
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_buf_t
modifier|*
name|b
parameter_list|,
name|ngx_http_status_t
modifier|*
name|status
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_parse_unsafe_uri
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
name|ngx_uint_t
modifier|*
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_parse_header_line
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_buf_t
modifier|*
name|b
parameter_list|,
name|ngx_uint_t
name|allow_underscores
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_parse_multi_header_lines
parameter_list|(
name|ngx_array_t
modifier|*
name|headers
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|ngx_str_t
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_arg
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|u_char
modifier|*
name|name
parameter_list|,
name|size_t
name|len
parameter_list|,
name|ngx_str_t
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_split_args
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
name|ngx_http_parse_chunked
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_buf_t
modifier|*
name|b
parameter_list|,
name|ngx_http_chunked_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_http_request_t
modifier|*
name|ngx_http_create_request
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_process_request_uri
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_process_request_header
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_process_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_update_location_config
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_run_posted_requests
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_post_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_posted_request_t
modifier|*
name|pr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_finalize_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_int_t
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_free_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_int_t
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_empty_handler
parameter_list|(
name|ngx_event_t
modifier|*
name|wev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_request_empty_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_http_ephemeral (r)
define|#
directive|define
name|ngx_http_ephemeral
parameter_list|(
name|r
parameter_list|)
value|(void *) (&r->uri_start)
end_define

begin_define
DECL|macro|NGX_HTTP_LAST
define|#
directive|define
name|NGX_HTTP_LAST
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_FLUSH
define|#
directive|define
name|NGX_HTTP_FLUSH
value|2
end_define

begin_function_decl
name|ngx_int_t
name|ngx_http_send_special
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_read_client_request_body
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_client_body_handler_pt
name|post_handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_send_header
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_special_response_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_int_t
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_filter_finalize_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_module_t
modifier|*
name|m
parameter_list|,
name|ngx_int_t
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_clean_header
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|time_t
name|ngx_http_parse_time
parameter_list|(
name|u_char
modifier|*
name|value
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_get_time
parameter_list|(
name|char
modifier|*
name|buf
parameter_list|,
name|time_t
name|t
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_discard_request_body
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_discarded_request_body_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_block_reading
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_test_reading
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_http_types_slot
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
name|ngx_http_merge_types
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_array_t
modifier|*
modifier|*
name|keys
parameter_list|,
name|ngx_hash_t
modifier|*
name|types_hash
parameter_list|,
name|ngx_array_t
modifier|*
modifier|*
name|prev_keys
parameter_list|,
name|ngx_hash_t
modifier|*
name|prev_types_hash
parameter_list|,
name|ngx_str_t
modifier|*
name|default_types
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_set_default_types
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_array_t
modifier|*
modifier|*
name|types
parameter_list|,
name|ngx_str_t
modifier|*
name|default_type
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_DEGRADATION
operator|)
end_if

begin_function_decl
name|ngx_uint_t
name|ngx_http_degraded
parameter_list|(
name|ngx_http_request_t
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_str_t
name|ngx_http_html_default_types
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_http_output_header_filter_pt
name|ngx_http_top_header_filter
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_http_output_body_filter_pt
name|ngx_http_top_body_filter
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_H_INCLUDED_ */
end_comment

end_unit

