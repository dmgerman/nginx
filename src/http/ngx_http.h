begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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

begin_include
include|#
directive|include
file|<ngx_garbage_collector.h>
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
DECL|typedef|ngx_http_log_ctx_t
typedef|typedef
name|struct
name|ngx_http_log_ctx_s
name|ngx_http_log_ctx_t
typedef|;
end_typedef

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

begin_comment
comment|/* STUB */
end_comment

begin_include
include|#
directive|include
file|<ngx_http_cache.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_variables.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_request.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_upstream.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_config.h>
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

begin_include
include|#
directive|include
file|<ngx_http_script.h>
end_include

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
DECL|member|client
name|ngx_str_t
modifier|*
name|client
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
name|ngx_http_parse_complex_uri
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
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
name|ngx_http_find_server_conf
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
name|ngx_http_discard_body
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_http_total_requests
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|uint64_t
name|ngx_http_total_sent
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

begin_comment
comment|/* STUB */
end_comment

begin_function_decl
name|ngx_int_t
name|ngx_http_log_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**/
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_H_INCLUDED_ */
end_comment

end_unit

