begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
DECL|typedef|ngx_http_cleanup_t
typedef|typedef
name|struct
name|ngx_http_cleanup_s
name|ngx_http_cleanup_t
typedef|;
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
file|<ngx_http_request.h>
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
file|<ngx_http_log_handler.h>
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

begin_typedef
DECL|struct|__anon2886fc9e0108
typedef|typedef
struct|struct
block|{
DECL|member|connection
name|u_int
name|connection
decl_stmt|;
comment|/*      * we declare "action" as "char *" because the actions are usually      * the static strings and in the "u_char *" case we have to override      * all the time their types      */
DECL|member|action
name|char
modifier|*
name|action
decl_stmt|;
DECL|member|client
name|u_char
modifier|*
name|client
decl_stmt|;
DECL|member|url
name|u_char
modifier|*
name|url
decl_stmt|;
DECL|typedef|ngx_http_log_ctx_t
block|}
name|ngx_http_log_ctx_t
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
value|r->ctx[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_http_get_module_err_ctx (r,module)
define|#
directive|define
name|ngx_http_get_module_err_ctx
parameter_list|(
name|r
parameter_list|,
name|module
parameter_list|)
define|\
value|(r->err_ctx ? r->err_ctx[module.ctx_index] : r->ctx[module.ctx_index])
end_define

begin_define
DECL|macro|ngx_http_create_ctx (r,cx,module,size,error)
define|#
directive|define
name|ngx_http_create_ctx
parameter_list|(
name|r
parameter_list|,
name|cx
parameter_list|,
name|module
parameter_list|,
name|size
parameter_list|,
name|error
parameter_list|)
define|\
value|do {                                                              \                 ngx_test_null(cx, ngx_pcalloc(r->pool, size), error);         \                 r->ctx[module.ctx_index] = cx;                                \             } while (0)
end_define

begin_define
DECL|macro|ngx_http_delete_ctx (r,module)
define|#
directive|define
name|ngx_http_delete_ctx
parameter_list|(
name|r
parameter_list|,
name|module
parameter_list|)
define|\
value|r->ctx[module.ctx_index] = NULL;
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
name|int
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_writer
parameter_list|(
name|ngx_event_t
modifier|*
name|wev
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
name|ngx_int_t
name|ngx_http_send_last
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_close_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|int
name|error
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

begin_function_decl
name|ngx_int_t
name|ngx_http_read_client_request_body
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
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
name|int
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

