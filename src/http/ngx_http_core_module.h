begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
DECL|struct|__anon2957d5470108
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|port
name|int
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
name|int
name|line
decl_stmt|;
DECL|member|default_server
name|unsigned
name|default_server
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_listen_t
block|}
name|ngx_http_listen_t
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2957d5470203
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_HTTP_REWRITE_PHASE
name|NGX_HTTP_REWRITE_PHASE
init|=
literal|0
block|,
DECL|enumerator|NGX_HTTP_FIND_CONFIG_PHASE
name|NGX_HTTP_FIND_CONFIG_PHASE
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
DECL|struct|__anon2957d5470308
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
DECL|struct|__anon2957d5470408
typedef|typedef
struct|struct
block|{
DECL|member|servers
name|ngx_array_t
name|servers
decl_stmt|;
comment|/* array of ngx_http_core_srv_conf_t */
DECL|member|phases
name|ngx_http_phase_t
name|phases
index|[
name|NGX_HTTP_LAST_PHASE
index|]
decl_stmt|;
DECL|member|index_handlers
name|ngx_array_t
name|index_handlers
decl_stmt|;
DECL|typedef|ngx_http_core_main_conf_t
block|}
name|ngx_http_core_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2957d5470508
typedef|typedef
struct|struct
block|{
DECL|member|locations
name|ngx_array_t
name|locations
decl_stmt|;
comment|/* array of ngx_http_core_loc_conf_t,                                   used in the translation handler                                   and in the merge phase */
DECL|member|listen
name|ngx_array_t
name|listen
decl_stmt|;
comment|/* 'listen', array of ngx_http_listen_t */
DECL|member|server_names
name|ngx_array_t
name|server_names
decl_stmt|;
comment|/* 'server_name',                                   array of ngx_http_server_name_t */
DECL|member|ctx
name|ngx_http_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
comment|/* server ctx */
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
DECL|member|post_accept_timeout
name|ngx_msec_t
name|post_accept_timeout
decl_stmt|;
DECL|member|client_header_timeout
name|ngx_msec_t
name|client_header_timeout
decl_stmt|;
DECL|member|large_client_header
name|ngx_flag_t
name|large_client_header
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
DECL|struct|__anon2957d5470608
typedef|typedef
struct|struct
block|{
DECL|member|port
name|int
name|port
decl_stmt|;
DECL|member|port_name
name|ngx_str_t
name|port_name
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

begin_typedef
DECL|struct|__anon2957d5470708
typedef|typedef
struct|struct
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
DECL|member|core_srv_conf
name|ngx_http_core_srv_conf_t
modifier|*
name|core_srv_conf
decl_stmt|;
comment|/* default server conf                                                   for this address:port */
DECL|member|default_server
name|unsigned
name|default_server
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_in_addr_t
block|}
name|ngx_http_in_addr_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2957d5470808
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
DECL|typedef|ngx_http_server_name_t
block|}
name|ngx_http_server_name_t
typedef|;
end_typedef

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
value|{                                                                   \             u_int n;                                                        \             for (key = 0, n = 0; n< ext.len; n++) {                        \                 key += ext.data[n];                                         \             }                                                               \             key %= NGX_HTTP_TYPES_HASH_PRIME;                               \         }
end_define

begin_typedef
DECL|struct|__anon2957d5470908
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
DECL|struct|__anon2957d5470a08
typedef|typedef
struct|struct
block|{
DECL|member|code
name|int
name|code
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
DECL|struct|__anon2957d5470b08
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
comment|/* location name */
DECL|member|loc_conf
name|void
modifier|*
modifier|*
name|loc_conf
decl_stmt|;
comment|/* pointer to the modules' loc_conf */
DECL|member|handler
name|int
function_decl|(
modifier|*
name|handler
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
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
DECL|member|send_lowat
name|size_t
name|send_lowat
decl_stmt|;
comment|/* send_lowat */
DECL|member|discarded_buffer_size
name|size_t
name|discarded_buffer_size
decl_stmt|;
comment|/* discarded_buffer_size */
DECL|member|client_body_buffer_size
name|size_t
name|client_body_buffer_size
decl_stmt|;
comment|/* client_body_buffer_size */
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
DECL|member|msie_padding
name|ngx_flag_t
name|msie_padding
decl_stmt|;
comment|/* msie_padding */
DECL|member|error_pages
name|ngx_array_t
modifier|*
name|error_pages
decl_stmt|;
comment|/* error_page */
DECL|member|open_files
name|ngx_http_cache_hash_t
modifier|*
name|open_files
decl_stmt|;
if|#
directive|if
operator|(
name|HAVE_PCRE
operator|)
DECL|member|regex
name|ngx_regex_t
modifier|*
name|regex
decl_stmt|;
endif|#
directive|endif
DECL|member|exact_match
name|unsigned
name|exact_match
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
DECL|member|err_log
name|ngx_log_t
modifier|*
name|err_log
decl_stmt|;
DECL|typedef|ngx_http_core_loc_conf_t
block|}
name|ngx_http_core_loc_conf_t
typedef|;
end_typedef

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
name|int
name|ngx_http_max_module
decl_stmt|;
end_decl_stmt

begin_function_decl
name|int
name|ngx_http_find_location_config
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_core_translate_handler
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
name|int
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CORE_H_INCLUDED_ */
end_comment

end_unit

