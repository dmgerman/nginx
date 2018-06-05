begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

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
file|<ngx_event_connect.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_TRANSPARENT_PROXY
operator|)
end_if

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_event_connect_set_transparent
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|ngx_socket_t
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|ngx_int_t
DECL|function|ngx_event_connect_peer (ngx_peer_connection_t * pc)
name|ngx_event_connect_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|)
block|{
name|int
name|rc
decl_stmt|,
name|type
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_IP_BIND_ADDRESS_NO_PORT
operator|||
name|NGX_LINUX
operator|)
name|in_port_t
name|port
decl_stmt|;
endif|#
directive|endif
name|ngx_int_t
name|event
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_uint_t
name|level
decl_stmt|;
name|ngx_socket_t
name|s
decl_stmt|;
name|ngx_event_t
modifier|*
name|rev
decl_stmt|,
modifier|*
name|wev
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|rc
operator|=
name|pc
operator|->
name|get
argument_list|(
name|pc
argument_list|,
name|pc
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|rc
return|;
block|}
name|type
operator|=
operator|(
name|pc
operator|->
name|type
condition|?
name|pc
operator|->
name|type
else|:
name|SOCK_STREAM
operator|)
expr_stmt|;
name|s
operator|=
name|ngx_socket
argument_list|(
name|pc
operator|->
name|sockaddr
operator|->
name|sa_family
argument_list|,
name|type
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"%s socket %d"
argument_list|,
operator|(
name|type
operator|==
name|SOCK_STREAM
operator|)
condition|?
literal|"stream"
else|:
literal|"dgram"
argument_list|,
name|s
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|==
operator|(
name|ngx_socket_t
operator|)
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_socket_n
literal|" failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|c
operator|=
name|ngx_get_connection
argument_list|(
name|s
argument_list|,
name|pc
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|ngx_close_socket
argument_list|(
name|s
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_close_socket_n
literal|" failed"
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
name|c
operator|->
name|type
operator|=
name|type
expr_stmt|;
if|if
condition|(
name|pc
operator|->
name|rcvbuf
condition|)
block|{
if|if
condition|(
name|setsockopt
argument_list|(
name|s
argument_list|,
name|SOL_SOCKET
argument_list|,
name|SO_RCVBUF
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|pc
operator|->
name|rcvbuf
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"setsockopt(SO_RCVBUF) failed"
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
block|}
if|if
condition|(
name|ngx_nonblocking
argument_list|(
name|s
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_nonblocking_n
literal|" failed"
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
if|if
condition|(
name|pc
operator|->
name|local
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_TRANSPARENT_PROXY
operator|)
if|if
condition|(
name|pc
operator|->
name|transparent
condition|)
block|{
if|if
condition|(
name|ngx_event_connect_set_transparent
argument_list|(
name|pc
argument_list|,
name|s
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_IP_BIND_ADDRESS_NO_PORT
operator|||
name|NGX_LINUX
operator|)
name|port
operator|=
name|ngx_inet_get_port
argument_list|(
name|pc
operator|->
name|local
operator|->
name|sockaddr
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_IP_BIND_ADDRESS_NO_PORT
operator|)
if|if
condition|(
name|pc
operator|->
name|sockaddr
operator|->
name|sa_family
operator|!=
name|AF_UNIX
operator|&&
name|port
operator|==
literal|0
condition|)
block|{
specifier|static
name|int
name|bind_address_no_port
init|=
literal|1
decl_stmt|;
if|if
condition|(
name|bind_address_no_port
condition|)
block|{
if|if
condition|(
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_IP
argument_list|,
name|IP_BIND_ADDRESS_NO_PORT
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|bind_address_no_port
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
if|if
condition|(
name|err
operator|!=
name|NGX_EOPNOTSUPP
operator|&&
name|err
operator|!=
name|NGX_ENOPROTOOPT
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"setsockopt(IP_BIND_ADDRESS_NO_PORT) "
literal|"failed, ignored"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|bind_address_no_port
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_LINUX
operator|)
if|if
condition|(
name|pc
operator|->
name|type
operator|==
name|SOCK_DGRAM
operator|&&
name|port
operator|!=
literal|0
condition|)
block|{
name|int
name|reuse_addr
init|=
literal|1
decl_stmt|;
if|if
condition|(
name|setsockopt
argument_list|(
name|s
argument_list|,
name|SOL_SOCKET
argument_list|,
name|SO_REUSEADDR
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|reuse_addr
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"setsockopt(SO_REUSEADDR) failed"
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
block|}
endif|#
directive|endif
if|if
condition|(
name|bind
argument_list|(
name|s
argument_list|,
name|pc
operator|->
name|local
operator|->
name|sockaddr
argument_list|,
name|pc
operator|->
name|local
operator|->
name|socklen
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"bind(%V) failed"
argument_list|,
operator|&
name|pc
operator|->
name|local
operator|->
name|name
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
block|}
if|if
condition|(
name|type
operator|==
name|SOCK_STREAM
condition|)
block|{
name|c
operator|->
name|recv
operator|=
name|ngx_recv
expr_stmt|;
name|c
operator|->
name|send
operator|=
name|ngx_send
expr_stmt|;
name|c
operator|->
name|recv_chain
operator|=
name|ngx_recv_chain
expr_stmt|;
name|c
operator|->
name|send_chain
operator|=
name|ngx_send_chain
expr_stmt|;
name|c
operator|->
name|sendfile
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|pc
operator|->
name|sockaddr
operator|->
name|sa_family
operator|==
name|AF_UNIX
condition|)
block|{
name|c
operator|->
name|tcp_nopush
operator|=
name|NGX_TCP_NOPUSH_DISABLED
expr_stmt|;
name|c
operator|->
name|tcp_nodelay
operator|=
name|NGX_TCP_NODELAY_DISABLED
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_SOLARIS
operator|)
comment|/* Solaris's sendfilev() supports AF_NCA, AF_INET, and AF_INET6 */
name|c
operator|->
name|sendfile
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
block|}
block|}
else|else
block|{
comment|/* type == SOCK_DGRAM */
name|c
operator|->
name|recv
operator|=
name|ngx_udp_recv
expr_stmt|;
name|c
operator|->
name|send
operator|=
name|ngx_send
expr_stmt|;
name|c
operator|->
name|send_chain
operator|=
name|ngx_udp_send_chain
expr_stmt|;
block|}
name|c
operator|->
name|log_error
operator|=
name|pc
operator|->
name|log_error
expr_stmt|;
name|rev
operator|=
name|c
operator|->
name|read
expr_stmt|;
name|wev
operator|=
name|c
operator|->
name|write
expr_stmt|;
name|rev
operator|->
name|log
operator|=
name|pc
operator|->
name|log
expr_stmt|;
name|wev
operator|->
name|log
operator|=
name|pc
operator|->
name|log
expr_stmt|;
name|pc
operator|->
name|connection
operator|=
name|c
expr_stmt|;
name|c
operator|->
name|number
operator|=
name|ngx_atomic_fetch_add
argument_list|(
name|ngx_connection_counter
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_add_conn
condition|)
block|{
if|if
condition|(
name|ngx_add_conn
argument_list|(
name|c
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
block|}
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"connect to %V, fd:%d #%uA"
argument_list|,
name|pc
operator|->
name|name
argument_list|,
name|s
argument_list|,
name|c
operator|->
name|number
argument_list|)
expr_stmt|;
name|rc
operator|=
name|connect
argument_list|(
name|s
argument_list|,
name|pc
operator|->
name|sockaddr
argument_list|,
name|pc
operator|->
name|socklen
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
if|if
condition|(
name|err
operator|!=
name|NGX_EINPROGRESS
if|#
directive|if
operator|(
name|NGX_WIN32
operator|)
comment|/* Winsock returns WSAEWOULDBLOCK (NGX_EAGAIN) */
operator|&&
name|err
operator|!=
name|NGX_EAGAIN
endif|#
directive|endif
condition|)
block|{
if|if
condition|(
name|err
operator|==
name|NGX_ECONNREFUSED
if|#
directive|if
operator|(
name|NGX_LINUX
operator|)
comment|/*                  * Linux returns EAGAIN instead of ECONNREFUSED                  * for unix sockets if listen queue is full                  */
operator|||
name|err
operator|==
name|NGX_EAGAIN
endif|#
directive|endif
operator|||
name|err
operator|==
name|NGX_ECONNRESET
operator|||
name|err
operator|==
name|NGX_ENETDOWN
operator|||
name|err
operator|==
name|NGX_ENETUNREACH
operator|||
name|err
operator|==
name|NGX_EHOSTDOWN
operator|||
name|err
operator|==
name|NGX_EHOSTUNREACH
condition|)
block|{
name|level
operator|=
name|NGX_LOG_ERR
expr_stmt|;
block|}
else|else
block|{
name|level
operator|=
name|NGX_LOG_CRIT
expr_stmt|;
block|}
name|ngx_log_error
argument_list|(
name|level
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"connect() to %V failed"
argument_list|,
name|pc
operator|->
name|name
argument_list|)
expr_stmt|;
name|ngx_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
name|pc
operator|->
name|connection
operator|=
name|NULL
expr_stmt|;
return|return
name|NGX_DECLINED
return|;
block|}
block|}
if|if
condition|(
name|ngx_add_conn
condition|)
block|{
if|if
condition|(
name|rc
operator|==
operator|-
literal|1
condition|)
block|{
comment|/* NGX_EINPROGRESS */
return|return
name|NGX_AGAIN
return|;
block|}
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"connected"
argument_list|)
expr_stmt|;
name|wev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_IOCP_EVENT
condition|)
block|{
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"connect(): %d"
argument_list|,
name|rc
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_blocking
argument_list|(
name|s
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_blocking_n
literal|" failed"
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
comment|/*          * FreeBSD's aio allows to post an operation on non-connected socket.          * NT does not support it.          *          * TODO: check in Win32, etc. As workaround we can use NGX_ONESHOT_EVENT          */
name|rev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
name|wev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_CLEAR_EVENT
condition|)
block|{
comment|/* kqueue */
name|event
operator|=
name|NGX_CLEAR_EVENT
expr_stmt|;
block|}
else|else
block|{
comment|/* select, poll, /dev/poll */
name|event
operator|=
name|NGX_LEVEL_EVENT
expr_stmt|;
block|}
if|if
condition|(
name|ngx_add_event
argument_list|(
name|rev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|event
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
if|if
condition|(
name|rc
operator|==
operator|-
literal|1
condition|)
block|{
comment|/* NGX_EINPROGRESS */
if|if
condition|(
name|ngx_add_event
argument_list|(
name|wev
argument_list|,
name|NGX_WRITE_EVENT
argument_list|,
name|event
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
return|return
name|NGX_AGAIN
return|;
block|}
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"connected"
argument_list|)
expr_stmt|;
name|wev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
name|failed
label|:
name|ngx_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
name|pc
operator|->
name|connection
operator|=
name|NULL
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_TRANSPARENT_PROXY
operator|)
end_if

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_event_connect_set_transparent (ngx_peer_connection_t * pc,ngx_socket_t s)
name|ngx_event_connect_set_transparent
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|int
name|value
decl_stmt|;
name|value
operator|=
literal|1
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|SO_BINDANY
argument_list|)
if|if
condition|(
name|setsockopt
argument_list|(
name|s
argument_list|,
name|SOL_SOCKET
argument_list|,
name|SO_BINDANY
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|value
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"setsockopt(SO_BINDANY) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
else|#
directive|else
switch|switch
condition|(
name|pc
operator|->
name|local
operator|->
name|sockaddr
operator|->
name|sa_family
condition|)
block|{
case|case
name|AF_INET
case|:
if|#
directive|if
name|defined
argument_list|(
name|IP_TRANSPARENT
argument_list|)
if|if
condition|(
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_IP
argument_list|,
name|IP_TRANSPARENT
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|value
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"setsockopt(IP_TRANSPARENT) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|IP_BINDANY
argument_list|)
if|if
condition|(
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_IP
argument_list|,
name|IP_BINDANY
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|value
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"setsockopt(IP_BINDANY) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
break|break;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
case|case
name|AF_INET6
case|:
if|#
directive|if
name|defined
argument_list|(
name|IPV6_TRANSPARENT
argument_list|)
if|if
condition|(
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_IPV6
argument_list|,
name|IPV6_TRANSPARENT
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|value
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"setsockopt(IPV6_TRANSPARENT) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
elif|#
directive|elif
name|defined
argument_list|(
name|IPV6_BINDANY
argument_list|)
if|if
condition|(
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_IPV6
argument_list|,
name|IPV6_BINDANY
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|value
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"setsockopt(IPV6_BINDANY) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
else|#
directive|else
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"could not enable transparent proxying for IPv6 "
literal|"on this platform"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
endif|#
directive|endif
break|break;
endif|#
directive|endif
comment|/* NGX_HAVE_INET6 */
block|}
endif|#
directive|endif
comment|/* SO_BINDANY */
return|return
name|NGX_OK
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|ngx_int_t
DECL|function|ngx_event_get_peer (ngx_peer_connection_t * pc,void * data)
name|ngx_event_get_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

