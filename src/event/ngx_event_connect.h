begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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
file|<ngx_core.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_define
DECL|macro|NGX_CONNECT_ERROR
define|#
directive|define
name|NGX_CONNECT_ERROR
value|-10
end_define

begin_typedef
DECL|struct|__anon2bbf56830108
typedef|typedef
struct|struct
block|{
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
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|uri_separator
name|char
modifier|*
name|uri_separator
decl_stmt|;
DECL|member|weight
name|ngx_uint_t
name|weight
decl_stmt|;
DECL|member|fails
name|ngx_uint_t
name|fails
decl_stmt|;
DECL|member|accessed
name|time_t
name|accessed
decl_stmt|;
DECL|member|max_fails
name|ngx_uint_t
name|max_fails
decl_stmt|;
DECL|member|fail_timeout
name|time_t
name|fail_timeout
decl_stmt|;
DECL|typedef|ngx_peer_t
block|}
name|ngx_peer_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_peers_s
struct|struct
name|ngx_peers_s
block|{
DECL|member|current
name|ngx_uint_t
name|current
decl_stmt|;
DECL|member|weight
name|ngx_uint_t
name|weight
decl_stmt|;
DECL|member|number
name|ngx_uint_t
name|number
decl_stmt|;
DECL|member|last_cached
name|ngx_uint_t
name|last_cached
decl_stmt|;
comment|/* ngx_mutex_t        *mutex; */
DECL|member|cached
name|ngx_connection_t
modifier|*
modifier|*
name|cached
decl_stmt|;
DECL|member|peer
name|ngx_peer_t
name|peer
index|[
literal|1
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2bbf56830208
typedef|typedef
struct|struct
block|{
DECL|member|peers
name|ngx_peers_t
modifier|*
name|peers
decl_stmt|;
DECL|member|cur_peer
name|ngx_uint_t
name|cur_peer
decl_stmt|;
DECL|member|tries
name|ngx_uint_t
name|tries
decl_stmt|;
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
DECL|member|lock
name|ngx_atomic_t
modifier|*
name|lock
decl_stmt|;
endif|#
directive|endif
DECL|member|rcvbuf
name|int
name|rcvbuf
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|cached
name|unsigned
name|cached
range|:
literal|1
decl_stmt|;
DECL|member|log_error
name|unsigned
name|log_error
range|:
literal|2
decl_stmt|;
comment|/* ngx_connection_log_error_e */
DECL|typedef|ngx_peer_connection_t
block|}
name|ngx_peer_connection_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_event_connect_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_event_connect_peer_failed
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_CONNECT_H_INCLUDED_ */
end_comment

end_unit

