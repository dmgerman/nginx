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
file|<ngx_array.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_proxy.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_PROXY_PARSE_NO_HEADER
define|#
directive|define
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
value|20
end_define

begin_define
DECL|macro|NGX_HTTP_PARSE_TOO_LONG_STATUS_LINE
define|#
directive|define
name|NGX_HTTP_PARSE_TOO_LONG_STATUS_LINE
value|21
end_define

begin_typedef
DECL|struct|__anon28a80fb80108
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
DECL|struct|__anon28a80fb80208
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|u_int32_t
name|addr
decl_stmt|;
DECL|member|host
name|ngx_str_t
name|host
decl_stmt|;
DECL|member|port
name|int
name|port
decl_stmt|;
DECL|member|addr_port_name
name|ngx_str_t
name|addr_port_name
decl_stmt|;
DECL|member|fails
name|int
name|fails
decl_stmt|;
DECL|member|accessed
name|time_t
name|accessed
decl_stmt|;
DECL|typedef|ngx_http_proxy_upstream_t
block|}
name|ngx_http_proxy_upstream_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28a80fb80308
typedef|typedef
struct|struct
block|{
DECL|member|current
name|int
name|current
decl_stmt|;
DECL|member|number
name|int
name|number
decl_stmt|;
DECL|member|max_fails
name|int
name|max_fails
decl_stmt|;
DECL|member|fail_timeout
name|int
name|fail_timeout
decl_stmt|;
comment|/* ngx_mutex_t                mutex; */
comment|/* ngx_connection_t          *cached; ??? */
DECL|member|u
name|ngx_http_proxy_upstream_t
name|u
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|ngx_http_proxy_upstreams_t
block|}
name|ngx_http_proxy_upstreams_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28a80fb80408
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
DECL|member|port_name
name|ngx_str_t
name|port_name
decl_stmt|;
DECL|member|port
name|int
name|port
decl_stmt|;
DECL|typedef|ngx_http_proxy_upstream_url_t
block|}
name|ngx_http_proxy_upstream_url_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28a80fb80508
typedef|typedef
struct|struct
block|{
DECL|member|upstreams
name|ngx_http_proxy_upstreams_t
modifier|*
name|upstreams
decl_stmt|;
DECL|member|upstream_url
name|ngx_http_proxy_upstream_url_t
modifier|*
name|upstream_url
decl_stmt|;
DECL|member|rcvbuf
name|int
name|rcvbuf
decl_stmt|;
DECL|member|conn_pool_size
name|int
name|conn_pool_size
decl_stmt|;
DECL|member|connect_timeout
name|int
name|connect_timeout
decl_stmt|;
DECL|member|send_timeout
name|int
name|send_timeout
decl_stmt|;
DECL|member|read_timeout
name|int
name|read_timeout
decl_stmt|;
DECL|member|header_size
name|int
name|header_size
decl_stmt|;
DECL|member|large_header
name|int
name|large_header
decl_stmt|;
DECL|member|block_size
name|int
name|block_size
decl_stmt|;
DECL|member|max_block_size
name|int
name|max_block_size
decl_stmt|;
DECL|member|max_temp_file_size
name|int
name|max_temp_file_size
decl_stmt|;
DECL|member|file_block_size
name|int
name|file_block_size
decl_stmt|;
DECL|member|temp_path
name|ngx_path_t
modifier|*
name|temp_path
decl_stmt|;
DECL|member|temp_file_warn
name|int
name|temp_file_warn
decl_stmt|;
DECL|member|retry_500_error
name|int
name|retry_500_error
decl_stmt|;
DECL|typedef|ngx_http_proxy_loc_conf_t
block|}
name|ngx_http_proxy_loc_conf_t
typedef|;
end_typedef

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* location /one/ { proxy_pass  http://localhost:9000/two/; } */
end_comment

begin_comment
unit|typedef struct {
comment|/* "/one/" */
end_comment

begin_comment
comment|/* "http://localhost:9000/two/" */
end_comment

begin_comment
comment|/* "/two/" */
end_comment

begin_endif
unit|*upstream_farm; } ngx_http_proxy_pass_t;
endif|#
directive|endif
end_endif

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
DECL|member|event_proxy
name|ngx_event_proxy_t
modifier|*
name|event_proxy
decl_stmt|;
DECL|member|in_hunks
name|ngx_chain_t
modifier|*
name|in_hunks
decl_stmt|;
DECL|member|last_in_hunk
name|ngx_chain_t
modifier|*
name|last_in_hunk
decl_stmt|;
DECL|member|shadow_hunks
name|ngx_chain_t
modifier|*
name|shadow_hunks
decl_stmt|;
DECL|member|out_hunks
name|ngx_chain_t
modifier|*
name|out_hunks
decl_stmt|;
DECL|member|last_out_hunk
name|ngx_chain_t
modifier|*
name|last_out_hunk
decl_stmt|;
DECL|member|free_hunks
name|ngx_chain_t
modifier|*
name|free_hunks
decl_stmt|;
DECL|member|request_hunks
name|ngx_chain_t
modifier|*
name|request_hunks
decl_stmt|;
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
DECL|member|headers_in
name|ngx_http_proxy_headers_in_t
name|headers_in
decl_stmt|;
DECL|member|block_size
name|int
name|block_size
decl_stmt|;
DECL|member|allocated
name|int
name|allocated
decl_stmt|;
DECL|member|temp_file
name|ngx_file_t
modifier|*
name|temp_file
decl_stmt|;
DECL|member|temp_offset
name|off_t
name|temp_offset
decl_stmt|;
DECL|member|last_hunk
name|int
name|last_hunk
decl_stmt|;
DECL|member|hunks
name|ngx_array_t
name|hunks
decl_stmt|;
DECL|member|nhunks
name|int
name|nhunks
decl_stmt|;
DECL|member|hunk_n
name|int
name|hunk_n
decl_stmt|;
DECL|member|upstream_url
name|ngx_http_proxy_upstream_url_t
modifier|*
name|upstream_url
decl_stmt|;
DECL|member|upstreams
name|ngx_http_proxy_upstreams_t
modifier|*
name|upstreams
decl_stmt|;
DECL|member|cur_upstream
name|int
name|cur_upstream
decl_stmt|;
DECL|member|tries
name|int
name|tries
decl_stmt|;
DECL|member|sockaddr
name|struct
name|sockaddr
modifier|*
name|sockaddr
decl_stmt|;
DECL|member|lcf
name|ngx_http_proxy_loc_conf_t
modifier|*
name|lcf
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|method
name|int
name|method
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
DECL|member|full_status_line
name|ngx_str_t
name|full_status_line
decl_stmt|;
DECL|member|state
name|int
name|state
decl_stmt|;
DECL|member|status_count
name|int
name|status_count
decl_stmt|;
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
DECL|member|state_write_upstream_handler
name|int
function_decl|(
modifier|*
name|state_write_upstream_handler
function_decl|)
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
DECL|member|state_read_upstream_handler
name|int
function_decl|(
modifier|*
name|state_read_upstream_handler
function_decl|)
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
DECL|member|state_handler
name|int
function_decl|(
modifier|*
name|state_handler
function_decl|)
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
function_decl|;
DECL|member|last_error
name|int
name|last_error
decl_stmt|;
DECL|member|accel
name|unsigned
name|accel
range|:
literal|1
decl_stmt|;
DECL|member|cached_connection
name|unsigned
name|cached_connection
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon28a80fb80608
typedef|typedef
struct|struct
block|{
DECL|member|action
name|char
modifier|*
name|action
decl_stmt|;
DECL|member|upstream
name|char
modifier|*
name|upstream
decl_stmt|;
DECL|member|client
name|char
modifier|*
name|client
decl_stmt|;
DECL|member|url
name|char
modifier|*
name|url
decl_stmt|;
DECL|typedef|ngx_http_proxy_log_ctx_t
block|}
name|ngx_http_proxy_log_ctx_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_proxy_module
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|int
name|ngx_http_proxy_error
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|,
name|int
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_PROXY_HANDLER_H_INCLUDED_ */
end_comment

end_unit

