begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_STREAM_UPSTREAM_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_STREAM_UPSTREAM_H_INCLUDED_
define|#
directive|define
name|_NGX_STREAM_UPSTREAM_H_INCLUDED_
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
file|<ngx_stream.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_connect.h>
end_include

begin_define
DECL|macro|NGX_STREAM_UPSTREAM_CREATE
define|#
directive|define
name|NGX_STREAM_UPSTREAM_CREATE
value|0x0001
end_define

begin_define
DECL|macro|NGX_STREAM_UPSTREAM_WEIGHT
define|#
directive|define
name|NGX_STREAM_UPSTREAM_WEIGHT
value|0x0002
end_define

begin_define
DECL|macro|NGX_STREAM_UPSTREAM_MAX_FAILS
define|#
directive|define
name|NGX_STREAM_UPSTREAM_MAX_FAILS
value|0x0004
end_define

begin_define
DECL|macro|NGX_STREAM_UPSTREAM_FAIL_TIMEOUT
define|#
directive|define
name|NGX_STREAM_UPSTREAM_FAIL_TIMEOUT
value|0x0008
end_define

begin_define
DECL|macro|NGX_STREAM_UPSTREAM_DOWN
define|#
directive|define
name|NGX_STREAM_UPSTREAM_DOWN
value|0x0010
end_define

begin_define
DECL|macro|NGX_STREAM_UPSTREAM_BACKUP
define|#
directive|define
name|NGX_STREAM_UPSTREAM_BACKUP
value|0x0020
end_define

begin_typedef
DECL|struct|__anon2aceecde0108
typedef|typedef
struct|struct
block|{
DECL|member|upstreams
name|ngx_array_t
name|upstreams
decl_stmt|;
comment|/* ngx_stream_upstream_srv_conf_t */
DECL|typedef|ngx_stream_upstream_main_conf_t
block|}
name|ngx_stream_upstream_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_upstream_srv_conf_t
typedef|typedef
name|struct
name|ngx_stream_upstream_srv_conf_s
name|ngx_stream_upstream_srv_conf_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_upstream_init_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_stream_upstream_init_pt
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_upstream_init_peer_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_stream_upstream_init_peer_pt
function_decl|)
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2aceecde0208
typedef|typedef
struct|struct
block|{
DECL|member|init_upstream
name|ngx_stream_upstream_init_pt
name|init_upstream
decl_stmt|;
DECL|member|init
name|ngx_stream_upstream_init_peer_pt
name|init
decl_stmt|;
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|typedef|ngx_stream_upstream_peer_t
block|}
name|ngx_stream_upstream_peer_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2aceecde0308
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|addrs
name|ngx_addr_t
modifier|*
name|addrs
decl_stmt|;
DECL|member|naddrs
name|ngx_uint_t
name|naddrs
decl_stmt|;
DECL|member|weight
name|ngx_uint_t
name|weight
decl_stmt|;
DECL|member|max_fails
name|ngx_uint_t
name|max_fails
decl_stmt|;
DECL|member|fail_timeout
name|time_t
name|fail_timeout
decl_stmt|;
DECL|member|down
name|unsigned
name|down
range|:
literal|1
decl_stmt|;
DECL|member|backup
name|unsigned
name|backup
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_stream_upstream_server_t
block|}
name|ngx_stream_upstream_server_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_stream_upstream_srv_conf_s
struct|struct
name|ngx_stream_upstream_srv_conf_s
block|{
DECL|member|peer
name|ngx_stream_upstream_peer_t
name|peer
decl_stmt|;
DECL|member|srv_conf
name|void
modifier|*
modifier|*
name|srv_conf
decl_stmt|;
DECL|member|servers
name|ngx_array_t
modifier|*
name|servers
decl_stmt|;
comment|/* ngx_stream_upstream_server_t */
DECL|member|flags
name|ngx_uint_t
name|flags
decl_stmt|;
DECL|member|host
name|ngx_str_t
name|host
decl_stmt|;
DECL|member|file_name
name|u_char
modifier|*
name|file_name
decl_stmt|;
DECL|member|line
name|ngx_uint_t
name|line
decl_stmt|;
DECL|member|port
name|in_port_t
name|port
decl_stmt|;
DECL|member|no_port
name|ngx_uint_t
name|no_port
decl_stmt|;
comment|/* unsigned no_port:1 */
if|#
directive|if
operator|(
name|NGX_STREAM_UPSTREAM_ZONE
operator|)
DECL|member|shm_zone
name|ngx_shm_zone_t
modifier|*
name|shm_zone
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2aceecde0408
typedef|typedef
struct|struct
block|{
DECL|member|peer
name|ngx_peer_connection_t
name|peer
decl_stmt|;
DECL|member|downstream_buf
name|ngx_buf_t
name|downstream_buf
decl_stmt|;
DECL|member|upstream_buf
name|ngx_buf_t
name|upstream_buf
decl_stmt|;
DECL|member|received
name|off_t
name|received
decl_stmt|;
DECL|member|start_sec
name|time_t
name|start_sec
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_STREAM_SSL
operator|)
DECL|member|ssl_name
name|ngx_str_t
name|ssl_name
decl_stmt|;
endif|#
directive|endif
DECL|member|connected
name|unsigned
name|connected
range|:
literal|1
decl_stmt|;
DECL|member|proxy_protocol
name|unsigned
name|proxy_protocol
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_stream_upstream_t
block|}
name|ngx_stream_upstream_t
typedef|;
end_typedef

begin_function_decl
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|ngx_stream_upstream_add
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_url_t
modifier|*
name|u
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_stream_conf_upstream_srv_conf (uscf,module)
define|#
directive|define
name|ngx_stream_conf_upstream_srv_conf
parameter_list|(
name|uscf
parameter_list|,
name|module
parameter_list|)
define|\
value|uscf->srv_conf[module.ctx_index]
end_define

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_stream_upstream_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_STREAM_UPSTREAM_H_INCLUDED_ */
end_comment

end_unit

