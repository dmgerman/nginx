begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_LISTEN_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_LISTEN_H_INCLUDED_
define|#
directive|define
name|_NGX_LISTEN_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_typedef
DECL|struct|__anon29558c6c0108
typedef|typedef
struct|struct
block|{
DECL|member|fd
name|ngx_socket_t
name|fd
decl_stmt|;
DECL|member|sockaddr
name|struct
name|sockaddr
modifier|*
name|sockaddr
decl_stmt|;
DECL|member|socklen
name|socklen_t
name|socklen
decl_stmt|;
comment|/* size of sockaddr */
DECL|member|addr
name|int
name|addr
decl_stmt|;
comment|/* offset to address in sockaddr */
DECL|member|addr_text_max_len
name|int
name|addr_text_max_len
decl_stmt|;
DECL|member|addr_text
name|ngx_str_t
name|addr_text
decl_stmt|;
DECL|member|family
name|int
name|family
decl_stmt|;
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|member|protocol
name|int
name|protocol
decl_stmt|;
DECL|member|flags
name|int
name|flags
decl_stmt|;
comment|/* Winsock2 flags */
DECL|member|handler
name|int
function_decl|(
modifier|*
name|handler
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
comment|/* handler of accepted                                                         connection */
DECL|member|ctx
name|void
modifier|*
name|ctx
decl_stmt|;
comment|/* ngx_http_conf_ctx_t, for example */
DECL|member|servers
name|void
modifier|*
name|servers
decl_stmt|;
comment|/* array of ngx_http_in_addr_t, for example */
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|backlog
name|int
name|backlog
decl_stmt|;
DECL|member|post_accept_timeout
name|time_t
name|post_accept_timeout
decl_stmt|;
comment|/* should be here because                                                of the deferred accept */
DECL|member|bound
name|unsigned
name|bound
range|:
literal|1
decl_stmt|;
comment|/* already bound */
DECL|member|inherited
name|unsigned
name|inherited
range|:
literal|1
decl_stmt|;
comment|/* inherited from previous process */
DECL|member|nonblocking
name|unsigned
name|nonblocking
range|:
literal|1
decl_stmt|;
if|#
directive|if
literal|0
block|unsigned          overlapped:1;
comment|/* Winsock2 overlapped */
endif|#
directive|endif
DECL|member|shared
name|unsigned
name|shared
range|:
literal|1
decl_stmt|;
comment|/* shared between threads or processes */
if|#
directive|if
operator|(
name|HAVE_DEFERRED_ACCEPT
operator|)
DECL|member|deferred_accept
name|unsigned
name|deferred_accept
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
DECL|typedef|ngx_listen_t
block|}
name|ngx_listen_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_array_t
name|ngx_listening_sockets
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_LISTEN_H_INCLUDED_ */
end_comment

end_unit

