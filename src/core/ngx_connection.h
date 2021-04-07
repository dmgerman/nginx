begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_CONNECTION_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_CONNECTION_H_INCLUDED_
define|#
directive|define
name|_NGX_CONNECTION_H_INCLUDED_
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

begin_typedef
DECL|typedef|ngx_listening_t
typedef|typedef
name|struct
name|ngx_listening_s
name|ngx_listening_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_listening_s
struct|struct
name|ngx_listening_s
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
DECL|member|addr_text_max_len
name|size_t
name|addr_text_max_len
decl_stmt|;
DECL|member|addr_text
name|ngx_str_t
name|addr_text
decl_stmt|;
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|member|backlog
name|int
name|backlog
decl_stmt|;
DECL|member|rcvbuf
name|int
name|rcvbuf
decl_stmt|;
DECL|member|sndbuf
name|int
name|sndbuf
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_KEEPALIVE_TUNABLE
operator|)
DECL|member|keepidle
name|int
name|keepidle
decl_stmt|;
DECL|member|keepintvl
name|int
name|keepintvl
decl_stmt|;
DECL|member|keepcnt
name|int
name|keepcnt
decl_stmt|;
endif|#
directive|endif
comment|/* handler of accepted connection */
DECL|member|handler
name|ngx_connection_handler_pt
name|handler
decl_stmt|;
DECL|member|servers
name|void
modifier|*
name|servers
decl_stmt|;
comment|/* array of ngx_http_in_addr_t, for example */
DECL|member|log
name|ngx_log_t
name|log
decl_stmt|;
DECL|member|logp
name|ngx_log_t
modifier|*
name|logp
decl_stmt|;
DECL|member|pool_size
name|size_t
name|pool_size
decl_stmt|;
comment|/* should be here because of the AcceptEx() preread */
DECL|member|post_accept_buffer_size
name|size_t
name|post_accept_buffer_size
decl_stmt|;
DECL|member|previous
name|ngx_listening_t
modifier|*
name|previous
decl_stmt|;
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
decl_stmt|;
DECL|member|rbtree
name|ngx_rbtree_t
name|rbtree
decl_stmt|;
DECL|member|sentinel
name|ngx_rbtree_node_t
name|sentinel
decl_stmt|;
DECL|member|worker
name|ngx_uint_t
name|worker
decl_stmt|;
DECL|member|open
name|unsigned
name|open
range|:
literal|1
decl_stmt|;
DECL|member|remain
name|unsigned
name|remain
range|:
literal|1
decl_stmt|;
DECL|member|ignore
name|unsigned
name|ignore
range|:
literal|1
decl_stmt|;
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
DECL|member|nonblocking_accept
name|unsigned
name|nonblocking_accept
range|:
literal|1
decl_stmt|;
DECL|member|listen
name|unsigned
name|listen
range|:
literal|1
decl_stmt|;
DECL|member|nonblocking
name|unsigned
name|nonblocking
range|:
literal|1
decl_stmt|;
DECL|member|shared
name|unsigned
name|shared
range|:
literal|1
decl_stmt|;
comment|/* shared between threads or processes */
DECL|member|addr_ntop
name|unsigned
name|addr_ntop
range|:
literal|1
decl_stmt|;
DECL|member|wildcard
name|unsigned
name|wildcard
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
DECL|member|ipv6only
name|unsigned
name|ipv6only
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
DECL|member|reuseport
name|unsigned
name|reuseport
range|:
literal|1
decl_stmt|;
DECL|member|add_reuseport
name|unsigned
name|add_reuseport
range|:
literal|1
decl_stmt|;
DECL|member|keepalive
name|unsigned
name|keepalive
range|:
literal|2
decl_stmt|;
DECL|member|deferred_accept
name|unsigned
name|deferred_accept
range|:
literal|1
decl_stmt|;
DECL|member|delete_deferred
name|unsigned
name|delete_deferred
range|:
literal|1
decl_stmt|;
DECL|member|add_deferred
name|unsigned
name|add_deferred
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_DEFERRED_ACCEPT
operator|&&
name|defined
name|SO_ACCEPTFILTER
operator|)
DECL|member|accept_filter
name|char
modifier|*
name|accept_filter
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_SETFIB
operator|)
DECL|member|setfib
name|int
name|setfib
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_TCP_FASTOPEN
operator|)
DECL|member|fastopen
name|int
name|fastopen
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_typedef
DECL|enum|__anon28a13efd0103
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_ERROR_ALERT
name|NGX_ERROR_ALERT
init|=
literal|0
block|,
DECL|enumerator|NGX_ERROR_ERR
name|NGX_ERROR_ERR
block|,
DECL|enumerator|NGX_ERROR_INFO
name|NGX_ERROR_INFO
block|,
DECL|enumerator|NGX_ERROR_IGNORE_ECONNRESET
name|NGX_ERROR_IGNORE_ECONNRESET
block|,
DECL|enumerator|NGX_ERROR_IGNORE_EINVAL
name|NGX_ERROR_IGNORE_EINVAL
DECL|typedef|ngx_connection_log_error_e
block|}
name|ngx_connection_log_error_e
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon28a13efd0203
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_TCP_NODELAY_UNSET
name|NGX_TCP_NODELAY_UNSET
init|=
literal|0
block|,
DECL|enumerator|NGX_TCP_NODELAY_SET
name|NGX_TCP_NODELAY_SET
block|,
DECL|enumerator|NGX_TCP_NODELAY_DISABLED
name|NGX_TCP_NODELAY_DISABLED
DECL|typedef|ngx_connection_tcp_nodelay_e
block|}
name|ngx_connection_tcp_nodelay_e
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon28a13efd0303
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_TCP_NOPUSH_UNSET
name|NGX_TCP_NOPUSH_UNSET
init|=
literal|0
block|,
DECL|enumerator|NGX_TCP_NOPUSH_SET
name|NGX_TCP_NOPUSH_SET
block|,
DECL|enumerator|NGX_TCP_NOPUSH_DISABLED
name|NGX_TCP_NOPUSH_DISABLED
DECL|typedef|ngx_connection_tcp_nopush_e
block|}
name|ngx_connection_tcp_nopush_e
typedef|;
end_typedef

begin_define
DECL|macro|NGX_LOWLEVEL_BUFFERED
define|#
directive|define
name|NGX_LOWLEVEL_BUFFERED
value|0x0f
end_define

begin_define
DECL|macro|NGX_SSL_BUFFERED
define|#
directive|define
name|NGX_SSL_BUFFERED
value|0x01
end_define

begin_define
DECL|macro|NGX_HTTP_V2_BUFFERED
define|#
directive|define
name|NGX_HTTP_V2_BUFFERED
value|0x02
end_define

begin_struct
DECL|struct|ngx_connection_s
struct|struct
name|ngx_connection_s
block|{
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|read
name|ngx_event_t
modifier|*
name|read
decl_stmt|;
DECL|member|write
name|ngx_event_t
modifier|*
name|write
decl_stmt|;
DECL|member|fd
name|ngx_socket_t
name|fd
decl_stmt|;
DECL|member|recv
name|ngx_recv_pt
name|recv
decl_stmt|;
DECL|member|send
name|ngx_send_pt
name|send
decl_stmt|;
DECL|member|recv_chain
name|ngx_recv_chain_pt
name|recv_chain
decl_stmt|;
DECL|member|send_chain
name|ngx_send_chain_pt
name|send_chain
decl_stmt|;
DECL|member|listening
name|ngx_listening_t
modifier|*
name|listening
decl_stmt|;
DECL|member|sent
name|off_t
name|sent
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|type
name|int
name|type
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
DECL|member|addr_text
name|ngx_str_t
name|addr_text
decl_stmt|;
DECL|member|proxy_protocol
name|ngx_proxy_protocol_t
modifier|*
name|proxy_protocol
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_SSL
operator|||
name|NGX_COMPAT
operator|)
DECL|member|ssl
name|ngx_ssl_connection_t
modifier|*
name|ssl
decl_stmt|;
endif|#
directive|endif
DECL|member|udp
name|ngx_udp_connection_t
modifier|*
name|udp
decl_stmt|;
DECL|member|local_sockaddr
name|struct
name|sockaddr
modifier|*
name|local_sockaddr
decl_stmt|;
DECL|member|local_socklen
name|socklen_t
name|local_socklen
decl_stmt|;
DECL|member|buffer
name|ngx_buf_t
modifier|*
name|buffer
decl_stmt|;
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
DECL|member|number
name|ngx_atomic_uint_t
name|number
decl_stmt|;
DECL|member|start_time
name|ngx_msec_t
name|start_time
decl_stmt|;
DECL|member|requests
name|ngx_uint_t
name|requests
decl_stmt|;
DECL|member|buffered
name|unsigned
name|buffered
range|:
literal|8
decl_stmt|;
DECL|member|log_error
name|unsigned
name|log_error
range|:
literal|3
decl_stmt|;
comment|/* ngx_connection_log_error_e */
DECL|member|timedout
name|unsigned
name|timedout
range|:
literal|1
decl_stmt|;
DECL|member|error
name|unsigned
name|error
range|:
literal|1
decl_stmt|;
DECL|member|destroyed
name|unsigned
name|destroyed
range|:
literal|1
decl_stmt|;
DECL|member|idle
name|unsigned
name|idle
range|:
literal|1
decl_stmt|;
DECL|member|reusable
name|unsigned
name|reusable
range|:
literal|1
decl_stmt|;
DECL|member|close
name|unsigned
name|close
range|:
literal|1
decl_stmt|;
DECL|member|shared
name|unsigned
name|shared
range|:
literal|1
decl_stmt|;
DECL|member|sendfile
name|unsigned
name|sendfile
range|:
literal|1
decl_stmt|;
DECL|member|sndlowat
name|unsigned
name|sndlowat
range|:
literal|1
decl_stmt|;
DECL|member|tcp_nodelay
name|unsigned
name|tcp_nodelay
range|:
literal|2
decl_stmt|;
comment|/* ngx_connection_tcp_nodelay_e */
DECL|member|tcp_nopush
name|unsigned
name|tcp_nopush
range|:
literal|2
decl_stmt|;
comment|/* ngx_connection_tcp_nopush_e */
DECL|member|need_last_buf
name|unsigned
name|need_last_buf
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_AIO_SENDFILE
operator|||
name|NGX_COMPAT
operator|)
DECL|member|busy_count
name|unsigned
name|busy_count
range|:
literal|2
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_THREADS
operator|||
name|NGX_COMPAT
operator|)
DECL|member|sendfile_task
name|ngx_thread_task_t
modifier|*
name|sendfile_task
decl_stmt|;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_define
DECL|macro|ngx_set_connection_log (c,l)
define|#
directive|define
name|ngx_set_connection_log
parameter_list|(
name|c
parameter_list|,
name|l
parameter_list|)
define|\                                                                              \
value|c->log->file = l->file;                                                  \     c->log->next = l->next;                                                  \     c->log->writer = l->writer;                                              \     c->log->wdata = l->wdata;                                                \     if (!(c->log->log_level& NGX_LOG_DEBUG_CONNECTION)) {                   \         c->log->log_level = l->log_level;                                    \     }
end_define

begin_function_decl
name|ngx_listening_t
modifier|*
name|ngx_create_listening
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|struct
name|sockaddr
modifier|*
name|sockaddr
parameter_list|,
name|socklen_t
name|socklen
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_clone_listening
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_listening_t
modifier|*
name|ls
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_set_inherited_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_open_listening_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_configure_listening_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_close_listening_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_close_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_close_idle_connections
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_connection_local_sockaddr
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|,
name|ngx_uint_t
name|port
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_tcp_nodelay
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_connection_error
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_err_t
name|err
parameter_list|,
name|char
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_connection_t
modifier|*
name|ngx_get_connection
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_free_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_reusable_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_uint_t
name|reusable
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_CONNECTION_H_INCLUDED_ */
end_comment

end_unit

