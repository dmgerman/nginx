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

begin_typedef
DECL|struct|__anon2955f3bc0108
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
parameter_list|,
name|ngx_uint_t
name|down
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

