begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon2947b6210108
typedef|typedef
struct|struct
block|{
DECL|member|host
name|ngx_str_t
name|host
decl_stmt|;
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|location
name|ngx_str_t
modifier|*
name|location
decl_stmt|;
DECL|member|host_header
name|ngx_str_t
name|host_header
decl_stmt|;
DECL|member|port_text
name|ngx_str_t
name|port_text
decl_stmt|;
DECL|member|port
name|int
name|port
decl_stmt|;
DECL|typedef|ngx_http_proxy_upstream_t
block|}
name|ngx_http_proxy_upstream_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2947b6210208
typedef|typedef
struct|struct
block|{
DECL|member|connect_timeout
name|ngx_msec_t
name|connect_timeout
decl_stmt|;
DECL|member|send_timeout
name|ngx_msec_t
name|send_timeout
decl_stmt|;
DECL|member|header_size
name|ssize_t
name|header_size
decl_stmt|;
DECL|member|read_timeout
name|ngx_msec_t
name|read_timeout
decl_stmt|;
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
comment|/* STUB */
DECL|member|max_busy_len
name|int
name|max_busy_len
decl_stmt|;
DECL|member|max_temp_file_size
name|int
name|max_temp_file_size
decl_stmt|;
DECL|member|temp_file_write_size
name|int
name|temp_file_write_size
decl_stmt|;
comment|/* */
DECL|member|temp_path
name|ngx_path_t
modifier|*
name|temp_path
decl_stmt|;
DECL|member|upstream
name|ngx_http_proxy_upstream_t
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

begin_typedef
DECL|struct|__anon2947b6210308
typedef|typedef
struct|struct
block|{
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
DECL|member|accept_ranges
name|ngx_table_elt_t
modifier|*
name|accept_ranges
decl_stmt|;
DECL|member|content_length_n
name|off_t
name|content_length_n
decl_stmt|;
DECL|member|headers
name|ngx_table_t
modifier|*
name|headers
decl_stmt|;
DECL|typedef|ngx_http_proxy_headers_in_t
block|}
name|ngx_http_proxy_headers_in_t
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
DECL|member|upstream
name|ngx_peer_connection_t
name|upstream
decl_stmt|;
DECL|member|peer
name|ngx_peer_t
modifier|*
name|peer
decl_stmt|;
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
DECL|member|headers_in
name|ngx_http_proxy_headers_in_t
name|headers_in
decl_stmt|;
DECL|member|header_in
name|ngx_hunk_t
modifier|*
name|header_in
decl_stmt|;
DECL|member|status
name|int
name|status
decl_stmt|;
DECL|member|status_line
name|ngx_str_t
name|status_line
decl_stmt|;
DECL|member|work_request_hunks
name|ngx_chain_t
modifier|*
name|work_request_hunks
decl_stmt|;
DECL|member|request_hunks
name|ngx_chain_t
modifier|*
name|request_hunks
decl_stmt|;
DECL|member|method
name|int
name|method
decl_stmt|;
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|location_len
name|int
name|location_len
decl_stmt|;
DECL|member|host_header
name|ngx_str_t
name|host_header
decl_stmt|;
DECL|member|event_pipe
name|ngx_event_pipe_t
modifier|*
name|event_pipe
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
DECL|member|fatal_error
name|unsigned
name|fatal_error
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
DECL|member|status_start
name|char
modifier|*
name|status_start
decl_stmt|;
DECL|member|status_end
name|char
modifier|*
name|status_end
decl_stmt|;
DECL|member|status_count
name|int
name|status_count
decl_stmt|;
DECL|member|state
name|int
name|state
decl_stmt|;
DECL|member|action
name|char
modifier|*
name|action
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|NGX_HTTP_PROXY_PARSE_NO_HEADER
define|#
directive|define
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
value|20
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_PROXY_HANDLER_H_INCLUDED_ */
end_comment

end_unit

