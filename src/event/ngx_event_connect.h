begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_CONNECT_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_CONNECT_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_CONNECT_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_typedef
DECL|struct|__anon2788f8a70108
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
DECL|typedef|ngx_peer_t
block|}
name|ngx_peer_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2788f8a70208
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
comment|/* ngx_mutex_t       *mutex; */
comment|/* ngx_connection_t  *cached; */
DECL|member|peers
name|ngx_peer_t
name|peers
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|ngx_peers_t
block|}
name|ngx_peers_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2788f8a70308
typedef|typedef
struct|struct
block|{
DECL|member|peers
name|ngx_peers_t
modifier|*
name|peers
decl_stmt|;
DECL|member|cur_peer
name|int
name|cur_peer
decl_stmt|;
DECL|member|tries
name|int
name|tries
decl_stmt|;
DECL|typedef|ngx_connect_peer_t
block|}
name|ngx_connect_peer_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_CONNECT_H_INCLUDED_ */
end_comment

end_unit

