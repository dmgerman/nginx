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
DECL|struct|__anon2911b8c40108
typedef|typedef
struct|struct
block|{
DECL|member|send_timeout
name|ngx_msec_t
name|send_timeout
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
DECL|member|lcf
name|ngx_http_proxy_loc_conf_t
modifier|*
name|lcf
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
DECL|member|action
name|char
modifier|*
name|action
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_PROXY_HANDLER_H_INCLUDED_ */
end_comment

end_unit

