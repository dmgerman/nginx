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
DECL|struct|__anon2a32f84f0108
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|u_int32_t
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
DECL|member|flags
name|int
name|flags
decl_stmt|;
comment|/* 'default' */
DECL|member|file_name
name|ngx_str_t
name|file_name
decl_stmt|;
DECL|member|line
name|int
name|line
decl_stmt|;
DECL|typedef|ngx_http_listen_t
block|}
name|ngx_http_listen_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a32f84f0208
typedef|typedef
struct|struct
block|{
DECL|member|locations
name|ngx_array_t
name|locations
decl_stmt|;
comment|/* array of ngx_http_core_loc_conf_t */
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
DECL|typedef|ngx_http_core_srv_conf_t
block|}
name|ngx_http_core_srv_conf_t
typedef|;
end_typedef

begin_comment
comment|/* list of structures to find core_srv_conf quickly at run time */
end_comment

begin_typedef
DECL|struct|__anon2a32f84f0308
typedef|typedef
struct|struct
block|{
DECL|member|port
name|int
name|port
decl_stmt|;
DECL|member|addr
name|ngx_array_t
name|addr
decl_stmt|;
comment|/* array of ngx_http_in_addr_t */
DECL|typedef|ngx_http_in_port_t
block|}
name|ngx_http_in_port_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a32f84f0408
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|u_int32_t
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
DECL|member|flags
name|int
name|flags
decl_stmt|;
DECL|typedef|ngx_http_in_addr_t
block|}
name|ngx_http_in_addr_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_DEFAULT_SERVER
define|#
directive|define
name|NGX_HTTP_DEFAULT_SERVER
value|1
end_define

begin_typedef
DECL|struct|__anon2a32f84f0508
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

begin_typedef
DECL|struct|__anon2a32f84f0608
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
comment|/* pointer to modules loc_conf,                                   used in translation handler */
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
DECL|member|doc_root
name|ngx_str_t
name|doc_root
decl_stmt|;
comment|/* root */
DECL|member|sendfile
name|int
name|sendfile
decl_stmt|;
comment|/* sendfile */
DECL|member|send_timeout
name|time_t
name|send_timeout
decl_stmt|;
comment|/* send_timeout */
DECL|member|send_lowat
name|size_t
name|send_lowat
decl_stmt|;
comment|/* send_lowa */
DECL|member|discarded_buffer_size
name|size_t
name|discarded_buffer_size
decl_stmt|;
comment|/* discarded_buffer_size */
DECL|member|lingering_time
name|time_t
name|lingering_time
decl_stmt|;
comment|/* lingering_time */
DECL|member|lingering_timeout
name|ngx_msec_t
name|lingering_timeout
decl_stmt|;
comment|/* lingering_timeout */
DECL|typedef|ngx_http_core_loc_conf_t
block|}
name|ngx_http_core_loc_conf_t
typedef|;
end_typedef

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|typedef struct {     int dummy; } ngx_http_core_conf_t;
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
literal|0
end_if

begin_define
define|#
directive|define
name|ngx_http_set_loc_handler
parameter_list|(
name|conf_ctx
parameter_list|,
name|ngx_http_handler
parameter_list|)
define|\
value|{                                                                         \         ngx_http_conf_ctx_t       *cx = conf_ctx;                             \         ngx_http_core_loc_conf_t  *lcf;                                       \         lcf = cx->loc_conf[ngx_http_core_module_ctx.index];                   \         lcf->handler = ngx_http_handler;                                      \     }
end_define

begin_endif
endif|#
directive|endif
end_endif

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
name|ngx_http_core_translate_handler
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
name|uri
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_error
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
name|int
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
name|int
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CORE_H_INCLUDED_ */
end_comment

end_unit

