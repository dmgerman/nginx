begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_STREAM_UPSTREAM_ROUND_ROBIN_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_STREAM_UPSTREAM_ROUND_ROBIN_H_INCLUDED_
define|#
directive|define
name|_NGX_STREAM_UPSTREAM_ROUND_ROBIN_H_INCLUDED_
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

begin_typedef
DECL|typedef|ngx_stream_upstream_rr_peer_t
typedef|typedef
name|struct
name|ngx_stream_upstream_rr_peer_s
name|ngx_stream_upstream_rr_peer_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_stream_upstream_rr_peer_s
struct|struct
name|ngx_stream_upstream_rr_peer_s
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
DECL|member|server
name|ngx_str_t
name|server
decl_stmt|;
DECL|member|current_weight
name|ngx_int_t
name|current_weight
decl_stmt|;
DECL|member|effective_weight
name|ngx_int_t
name|effective_weight
decl_stmt|;
DECL|member|weight
name|ngx_int_t
name|weight
decl_stmt|;
DECL|member|conns
name|ngx_uint_t
name|conns
decl_stmt|;
DECL|member|fails
name|ngx_uint_t
name|fails
decl_stmt|;
DECL|member|accessed
name|time_t
name|accessed
decl_stmt|;
DECL|member|checked
name|time_t
name|checked
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
name|ngx_uint_t
name|down
decl_stmt|;
comment|/* unsigned  down:1; */
if|#
directive|if
operator|(
name|NGX_STREAM_SSL
operator|)
DECL|member|ssl_session
name|void
modifier|*
name|ssl_session
decl_stmt|;
DECL|member|ssl_session_len
name|int
name|ssl_session_len
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_STREAM_UPSTREAM_ZONE
operator|)
DECL|member|lock
name|ngx_atomic_t
name|lock
decl_stmt|;
endif|#
directive|endif
DECL|member|next
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|ngx_stream_upstream_rr_peers_t
typedef|typedef
name|struct
name|ngx_stream_upstream_rr_peers_s
name|ngx_stream_upstream_rr_peers_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_stream_upstream_rr_peers_s
struct|struct
name|ngx_stream_upstream_rr_peers_s
block|{
DECL|member|number
name|ngx_uint_t
name|number
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_STREAM_UPSTREAM_ZONE
operator|)
DECL|member|shpool
name|ngx_slab_pool_t
modifier|*
name|shpool
decl_stmt|;
DECL|member|rwlock
name|ngx_atomic_t
name|rwlock
decl_stmt|;
DECL|member|zone_next
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|zone_next
decl_stmt|;
endif|#
directive|endif
DECL|member|total_weight
name|ngx_uint_t
name|total_weight
decl_stmt|;
DECL|member|single
name|unsigned
name|single
range|:
literal|1
decl_stmt|;
DECL|member|weighted
name|unsigned
name|weighted
range|:
literal|1
decl_stmt|;
DECL|member|name
name|ngx_str_t
modifier|*
name|name
decl_stmt|;
DECL|member|next
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|next
decl_stmt|;
DECL|member|peer
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|;
block|}
struct|;
end_struct

begin_if
if|#
directive|if
operator|(
name|NGX_STREAM_UPSTREAM_ZONE
operator|)
end_if

begin_define
DECL|macro|ngx_stream_upstream_rr_peers_rlock (peers)
define|#
directive|define
name|ngx_stream_upstream_rr_peers_rlock
parameter_list|(
name|peers
parameter_list|)
define|\                                                                               \
value|if (peers->shpool) {                                                      \         ngx_rwlock_rlock(&peers->rwlock);                                     \     }
end_define

begin_define
DECL|macro|ngx_stream_upstream_rr_peers_wlock (peers)
define|#
directive|define
name|ngx_stream_upstream_rr_peers_wlock
parameter_list|(
name|peers
parameter_list|)
define|\                                                                               \
value|if (peers->shpool) {                                                      \         ngx_rwlock_wlock(&peers->rwlock);                                     \     }
end_define

begin_define
DECL|macro|ngx_stream_upstream_rr_peers_unlock (peers)
define|#
directive|define
name|ngx_stream_upstream_rr_peers_unlock
parameter_list|(
name|peers
parameter_list|)
define|\                                                                               \
value|if (peers->shpool) {                                                      \         ngx_rwlock_unlock(&peers->rwlock);                                    \     }
end_define

begin_define
DECL|macro|ngx_stream_upstream_rr_peer_lock (peers,peer)
define|#
directive|define
name|ngx_stream_upstream_rr_peer_lock
parameter_list|(
name|peers
parameter_list|,
name|peer
parameter_list|)
define|\                                                                               \
value|if (peers->shpool) {                                                      \         ngx_rwlock_wlock(&peer->lock);                                        \     }
end_define

begin_define
DECL|macro|ngx_stream_upstream_rr_peer_unlock (peers,peer)
define|#
directive|define
name|ngx_stream_upstream_rr_peer_unlock
parameter_list|(
name|peers
parameter_list|,
name|peer
parameter_list|)
define|\                                                                               \
value|if (peers->shpool) {                                                      \         ngx_rwlock_unlock(&peer->lock);                                       \     }
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_stream_upstream_rr_peers_rlock (peers)
define|#
directive|define
name|ngx_stream_upstream_rr_peers_rlock
parameter_list|(
name|peers
parameter_list|)
end_define

begin_define
DECL|macro|ngx_stream_upstream_rr_peers_wlock (peers)
define|#
directive|define
name|ngx_stream_upstream_rr_peers_wlock
parameter_list|(
name|peers
parameter_list|)
end_define

begin_define
DECL|macro|ngx_stream_upstream_rr_peers_unlock (peers)
define|#
directive|define
name|ngx_stream_upstream_rr_peers_unlock
parameter_list|(
name|peers
parameter_list|)
end_define

begin_define
DECL|macro|ngx_stream_upstream_rr_peer_lock (peers,peer)
define|#
directive|define
name|ngx_stream_upstream_rr_peer_lock
parameter_list|(
name|peers
parameter_list|,
name|peer
parameter_list|)
end_define

begin_define
DECL|macro|ngx_stream_upstream_rr_peer_unlock (peers,peer)
define|#
directive|define
name|ngx_stream_upstream_rr_peer_unlock
parameter_list|(
name|peers
parameter_list|,
name|peer
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2b7408560108
typedef|typedef
struct|struct
block|{
DECL|member|peers
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|peers
decl_stmt|;
DECL|member|current
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|current
decl_stmt|;
DECL|member|tried
name|uintptr_t
modifier|*
name|tried
decl_stmt|;
DECL|member|data
name|uintptr_t
name|data
decl_stmt|;
DECL|typedef|ngx_stream_upstream_rr_peer_data_t
block|}
name|ngx_stream_upstream_rr_peer_data_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_stream_upstream_init_round_robin
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
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_upstream_init_round_robin_peer
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
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_upstream_create_round_robin_peer
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_upstream_resolved_t
modifier|*
name|ur
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_upstream_get_round_robin_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_stream_upstream_free_round_robin_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|void
modifier|*
name|data
parameter_list|,
name|ngx_uint_t
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_STREAM_UPSTREAM_ROUND_ROBIN_H_INCLUDED_ */
end_comment

end_unit

