begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_REQUEST_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_REQUEST_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_REQUEST_H_INCLUDED_
end_define

begin_define
DECL|macro|NGX_HTTP_VERSION_9
define|#
directive|define
name|NGX_HTTP_VERSION_9
value|9
end_define

begin_define
DECL|macro|NGX_HTTP_VERSION_10
define|#
directive|define
name|NGX_HTTP_VERSION_10
value|1000
end_define

begin_define
DECL|macro|NGX_HTTP_VERSION_11
define|#
directive|define
name|NGX_HTTP_VERSION_11
value|1001
end_define

begin_define
DECL|macro|NGX_HTTP_GET
define|#
directive|define
name|NGX_HTTP_GET
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_HEAD
define|#
directive|define
name|NGX_HTTP_HEAD
value|2
end_define

begin_define
DECL|macro|NGX_HTTP_POST
define|#
directive|define
name|NGX_HTTP_POST
value|3
end_define

begin_define
DECL|macro|NGX_HTTP_CONN_CLOSE
define|#
directive|define
name|NGX_HTTP_CONN_CLOSE
value|0
end_define

begin_define
DECL|macro|NGX_HTTP_CONN_KEEP_ALIVE
define|#
directive|define
name|NGX_HTTP_CONN_KEEP_ALIVE
value|1
end_define

begin_define
DECL|macro|NGX_NONE
define|#
directive|define
name|NGX_NONE
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_HEADER_DONE
define|#
directive|define
name|NGX_HTTP_PARSE_HEADER_DONE
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_INVALID_METHOD
define|#
directive|define
name|NGX_HTTP_PARSE_INVALID_METHOD
value|10
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_INVALID_REQUEST
define|#
directive|define
name|NGX_HTTP_PARSE_INVALID_REQUEST
value|11
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_TOO_LONG_URI
define|#
directive|define
name|NGX_HTTP_PARSE_TOO_LONG_URI
value|12
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_INVALID_09_METHOD
define|#
directive|define
name|NGX_HTTP_PARSE_INVALID_09_METHOD
value|13
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_INVALID_HEADER
define|#
directive|define
name|NGX_HTTP_PARSE_INVALID_HEADER
value|14
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_TOO_LONG_HEADER
define|#
directive|define
name|NGX_HTTP_PARSE_TOO_LONG_HEADER
value|15
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_NO_HOST_HEADER
define|#
directive|define
name|NGX_HTTP_PARSE_NO_HOST_HEADER
value|16
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_INVALID_CL_HEADER
define|#
directive|define
name|NGX_HTTP_PARSE_INVALID_CL_HEADER
value|17
end_define

begin_define
DECL|macro|NGX_HTTP_OK
define|#
directive|define
name|NGX_HTTP_OK
value|200
end_define

begin_define
DECL|macro|NGX_HTTP_PARTIAL_CONTENT
define|#
directive|define
name|NGX_HTTP_PARTIAL_CONTENT
value|206
end_define

begin_define
DECL|macro|NGX_HTTP_SPECIAL_RESPONSE
define|#
directive|define
name|NGX_HTTP_SPECIAL_RESPONSE
value|300
end_define

begin_define
DECL|macro|NGX_HTTP_MOVED_PERMANENTLY
define|#
directive|define
name|NGX_HTTP_MOVED_PERMANENTLY
value|301
end_define

begin_define
DECL|macro|NGX_HTTP_MOVED_TEMPORARILY
define|#
directive|define
name|NGX_HTTP_MOVED_TEMPORARILY
value|302
end_define

begin_define
DECL|macro|NGX_HTTP_NOT_MODIFIED
define|#
directive|define
name|NGX_HTTP_NOT_MODIFIED
value|304
end_define

begin_define
DECL|macro|NGX_HTTP_BAD_REQUEST
define|#
directive|define
name|NGX_HTTP_BAD_REQUEST
value|400
end_define

begin_define
DECL|macro|NGX_HTTP_FORBIDDEN
define|#
directive|define
name|NGX_HTTP_FORBIDDEN
value|403
end_define

begin_define
DECL|macro|NGX_HTTP_NOT_FOUND
define|#
directive|define
name|NGX_HTTP_NOT_FOUND
value|404
end_define

begin_define
DECL|macro|NGX_HTTP_NOT_ALLOWED
define|#
directive|define
name|NGX_HTTP_NOT_ALLOWED
value|405
end_define

begin_define
DECL|macro|NGX_HTTP_REQUEST_TIME_OUT
define|#
directive|define
name|NGX_HTTP_REQUEST_TIME_OUT
value|408
end_define

begin_define
DECL|macro|NGX_HTTP_REQUEST_URI_TOO_LARGE
define|#
directive|define
name|NGX_HTTP_REQUEST_URI_TOO_LARGE
value|414
end_define

begin_define
DECL|macro|NGX_HTTP_RANGE_NOT_SATISFIABLE
define|#
directive|define
name|NGX_HTTP_RANGE_NOT_SATISFIABLE
value|416
end_define

begin_define
DECL|macro|NGX_HTTP_INTERNAL_SERVER_ERROR
define|#
directive|define
name|NGX_HTTP_INTERNAL_SERVER_ERROR
value|500
end_define

begin_define
DECL|macro|NGX_HTTP_NOT_IMPLEMENTED
define|#
directive|define
name|NGX_HTTP_NOT_IMPLEMENTED
value|501
end_define

begin_define
DECL|macro|NGX_HTTP_BAD_GATEWAY
define|#
directive|define
name|NGX_HTTP_BAD_GATEWAY
value|502
end_define

begin_define
DECL|macro|NGX_HTTP_SERVICE_UNAVAILABLE
define|#
directive|define
name|NGX_HTTP_SERVICE_UNAVAILABLE
value|503
end_define

begin_define
DECL|macro|NGX_HTTP_GATEWAY_TIME_OUT
define|#
directive|define
name|NGX_HTTP_GATEWAY_TIME_OUT
value|504
end_define

begin_define
DECL|macro|NGX_HTTP_STATIC_HANDLER
define|#
directive|define
name|NGX_HTTP_STATIC_HANDLER
value|0
end_define

begin_define
DECL|macro|NGX_HTTP_DIRECTORY_HANDLER
define|#
directive|define
name|NGX_HTTP_DIRECTORY_HANDLER
value|1
end_define

begin_typedef
DECL|struct|__anon290235230108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|offset
name|int
name|offset
decl_stmt|;
DECL|typedef|ngx_http_header_t
block|}
name|ngx_http_header_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon290235230208
typedef|typedef
struct|struct
block|{
DECL|member|host_name_len
name|size_t
name|host_name_len
decl_stmt|;
DECL|member|content_length_n
name|ssize_t
name|content_length_n
decl_stmt|;
DECL|member|host
name|ngx_table_elt_t
modifier|*
name|host
decl_stmt|;
DECL|member|connection
name|ngx_table_elt_t
modifier|*
name|connection
decl_stmt|;
DECL|member|if_modified_since
name|ngx_table_elt_t
modifier|*
name|if_modified_since
decl_stmt|;
DECL|member|content_length
name|ngx_table_elt_t
modifier|*
name|content_length
decl_stmt|;
DECL|member|range
name|ngx_table_elt_t
modifier|*
name|range
decl_stmt|;
DECL|member|accept_encoding
name|ngx_table_elt_t
modifier|*
name|accept_encoding
decl_stmt|;
DECL|member|user_agent
name|ngx_table_elt_t
modifier|*
name|user_agent
decl_stmt|;
DECL|member|headers
name|ngx_table_t
modifier|*
name|headers
decl_stmt|;
DECL|typedef|ngx_http_headers_in_t
block|}
name|ngx_http_headers_in_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon290235230308
typedef|typedef
struct|struct
block|{
DECL|member|chain
name|ngx_chain_t
name|chain
index|[
literal|4
index|]
decl_stmt|;
DECL|member|header_out
name|ngx_hunk_t
modifier|*
name|header_out
decl_stmt|;
DECL|member|hunk
name|ngx_hunk_t
modifier|*
name|hunk
decl_stmt|;
DECL|member|file_hunk
name|ngx_hunk_t
modifier|*
name|file_hunk
decl_stmt|;
DECL|member|temp_file
name|ngx_file_t
name|temp_file
decl_stmt|;
DECL|member|temp_path
name|ngx_path_t
modifier|*
name|temp_path
decl_stmt|;
DECL|member|offset
name|off_t
name|offset
decl_stmt|;
DECL|member|header_in_pos
name|char
modifier|*
name|header_in_pos
decl_stmt|;
DECL|typedef|ngx_http_request_body_t
block|}
name|ngx_http_request_body_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon290235230408
typedef|typedef
struct|struct
block|{
DECL|member|start
name|off_t
name|start
decl_stmt|;
DECL|member|end
name|off_t
name|end
decl_stmt|;
DECL|member|content_range
name|ngx_str_t
name|content_range
decl_stmt|;
DECL|typedef|ngx_http_range_t
block|}
name|ngx_http_range_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon290235230508
typedef|typedef
struct|struct
block|{
DECL|member|status
name|int
name|status
decl_stmt|;
DECL|member|status_line
name|ngx_str_t
name|status_line
decl_stmt|;
DECL|member|server
name|ngx_table_elt_t
modifier|*
name|server
decl_stmt|;
DECL|member|date
name|ngx_table_elt_t
modifier|*
name|date
decl_stmt|;
DECL|member|content_type
name|ngx_table_elt_t
modifier|*
name|content_type
decl_stmt|;
DECL|member|content_encoding
name|ngx_table_elt_t
modifier|*
name|content_encoding
decl_stmt|;
DECL|member|location
name|ngx_table_elt_t
modifier|*
name|location
decl_stmt|;
DECL|member|last_modified
name|ngx_table_elt_t
modifier|*
name|last_modified
decl_stmt|;
DECL|member|content_range
name|ngx_table_elt_t
modifier|*
name|content_range
decl_stmt|;
DECL|member|accept_ranges
name|ngx_table_elt_t
modifier|*
name|accept_ranges
decl_stmt|;
DECL|member|charset
name|ngx_str_t
name|charset
decl_stmt|;
DECL|member|ranges
name|ngx_array_t
name|ranges
decl_stmt|;
DECL|member|headers
name|ngx_table_t
modifier|*
name|headers
decl_stmt|;
DECL|member|content_length
name|off_t
name|content_length
decl_stmt|;
DECL|member|etag
name|char
modifier|*
name|etag
decl_stmt|;
DECL|member|date_time
name|time_t
name|date_time
decl_stmt|;
DECL|member|last_modified_time
name|time_t
name|last_modified_time
decl_stmt|;
DECL|typedef|ngx_http_headers_out_t
block|}
name|ngx_http_headers_out_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_request_t
typedef|typedef
name|struct
name|ngx_http_request_s
name|ngx_http_request_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_handler_pt
typedef|typedef
name|int
function_decl|(
modifier|*
name|ngx_http_handler_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_http_request_s
struct|struct
name|ngx_http_request_s
block|{
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
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
DECL|member|loc_conf
name|void
modifier|*
modifier|*
name|loc_conf
decl_stmt|;
DECL|member|file
name|ngx_file_t
name|file
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|header_in
name|ngx_hunk_t
modifier|*
name|header_in
decl_stmt|;
DECL|member|request_body
name|ngx_http_request_body_t
modifier|*
name|request_body
decl_stmt|;
DECL|member|headers_in
name|ngx_http_headers_in_t
name|headers_in
decl_stmt|;
DECL|member|headers_out
name|ngx_http_headers_out_t
name|headers_out
decl_stmt|;
DECL|member|lingering_time
name|time_t
name|lingering_time
decl_stmt|;
DECL|member|method
name|int
name|method
decl_stmt|;
DECL|member|http_version
name|int
name|http_version
decl_stmt|;
DECL|member|http_major
name|int
name|http_major
decl_stmt|;
DECL|member|http_minor
name|int
name|http_minor
decl_stmt|;
DECL|member|request_line
name|ngx_str_t
name|request_line
decl_stmt|;
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|args
name|ngx_str_t
name|args
decl_stmt|;
DECL|member|exten
name|ngx_str_t
name|exten
decl_stmt|;
DECL|member|unparsed_uri
name|ngx_str_t
name|unparsed_uri
decl_stmt|;
DECL|member|main
name|ngx_http_request_t
modifier|*
decl|main
decl_stmt|;
DECL|member|in_addr
name|u_int
name|in_addr
decl_stmt|;
DECL|member|port
name|int
name|port
decl_stmt|;
DECL|member|port_name
name|ngx_str_t
modifier|*
name|port_name
decl_stmt|;
comment|/* ":80" */
DECL|member|server_name
name|ngx_str_t
modifier|*
name|server_name
decl_stmt|;
DECL|member|virtual_names
name|ngx_array_t
modifier|*
name|virtual_names
decl_stmt|;
DECL|member|phase
name|int
name|phase
decl_stmt|;
DECL|member|phase_handler
name|int
name|phase_handler
decl_stmt|;
DECL|member|content_handler
name|ngx_http_handler_pt
name|content_handler
decl_stmt|;
DECL|member|discarded_buffer
name|char
modifier|*
name|discarded_buffer
decl_stmt|;
DECL|member|path
name|ngx_str_t
name|path
decl_stmt|;
DECL|member|path_err
name|int
name|path_err
decl_stmt|;
comment|/* URI is not started with '/' - "GET http://" */
DECL|member|unusual_uri
name|unsigned
name|unusual_uri
range|:
literal|1
decl_stmt|;
comment|/* URI with "/.", "%" and on Win32 with "//" */
DECL|member|complex_uri
name|unsigned
name|complex_uri
range|:
literal|1
decl_stmt|;
DECL|member|header_timeout_set
name|unsigned
name|header_timeout_set
range|:
literal|1
decl_stmt|;
DECL|member|proxy
name|unsigned
name|proxy
range|:
literal|1
decl_stmt|;
if|#
directive|if
literal|0
block|unsigned             cachable:1;
endif|#
directive|endif
DECL|member|pipeline
name|unsigned
name|pipeline
range|:
literal|1
decl_stmt|;
DECL|member|chunked
name|unsigned
name|chunked
range|:
literal|1
decl_stmt|;
DECL|member|header_only
name|unsigned
name|header_only
range|:
literal|1
decl_stmt|;
DECL|member|keepalive
name|unsigned
name|keepalive
range|:
literal|1
decl_stmt|;
DECL|member|lingering_close
name|unsigned
name|lingering_close
range|:
literal|1
decl_stmt|;
DECL|member|closed
name|unsigned
name|closed
range|:
literal|1
decl_stmt|;
comment|/* TODO: use filter or bits ???? */
DECL|member|filter
name|int
name|filter
decl_stmt|;
comment|/* used to parse HTTP headers */
DECL|member|state
name|int
name|state
decl_stmt|;
DECL|member|uri_start
name|char
modifier|*
name|uri_start
decl_stmt|;
DECL|member|uri_end
name|char
modifier|*
name|uri_end
decl_stmt|;
DECL|member|uri_ext
name|char
modifier|*
name|uri_ext
decl_stmt|;
DECL|member|args_start
name|char
modifier|*
name|args_start
decl_stmt|;
DECL|member|request_start
name|char
modifier|*
name|request_start
decl_stmt|;
DECL|member|request_end
name|char
modifier|*
name|request_end
decl_stmt|;
DECL|member|header_name_start
name|char
modifier|*
name|header_name_start
decl_stmt|;
DECL|member|header_name_end
name|char
modifier|*
name|header_name_end
decl_stmt|;
DECL|member|header_start
name|char
modifier|*
name|header_start
decl_stmt|;
DECL|member|header_end
name|char
modifier|*
name|header_end
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_REQUEST_H_INCLUDED_ */
end_comment

end_unit

