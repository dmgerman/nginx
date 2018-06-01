begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Roman Arutyunyan  * Copyright (C) Nginx, Inc.  */
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

begin_if
if|#
directive|if
operator|!
operator|(
name|NGX_WIN32
operator|)
end_if

begin_function_decl
specifier|static
name|void
name|ngx_close_accepted_udp_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|ngx_event_recvmsg (ngx_event_t * ev)
name|ngx_event_recvmsg
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|;
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|socklen_t
name|socklen
decl_stmt|,
name|local_socklen
decl_stmt|;
name|ngx_event_t
modifier|*
name|rev
decl_stmt|,
modifier|*
name|wev
decl_stmt|;
name|struct
name|iovec
name|iov
index|[
literal|1
index|]
decl_stmt|;
name|struct
name|msghdr
name|msg
decl_stmt|;
name|ngx_sockaddr_t
name|sa
decl_stmt|,
name|lsa
decl_stmt|;
name|struct
name|sockaddr
modifier|*
name|sockaddr
decl_stmt|,
modifier|*
name|local_sockaddr
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
name|ngx_event_conf_t
modifier|*
name|ecf
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|,
modifier|*
name|lc
decl_stmt|;
specifier|static
name|u_char
name|buffer
index|[
literal|65535
index|]
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
if|#
directive|if
operator|(
name|NGX_HAVE_IP_RECVDSTADDR
operator|)
name|u_char
name|msg_control
index|[
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in_addr
argument_list|)
argument_list|)
index|]
decl_stmt|;
elif|#
directive|elif
operator|(
name|NGX_HAVE_IP_PKTINFO
operator|)
name|u_char
name|msg_control
index|[
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in_pktinfo
argument_list|)
argument_list|)
index|]
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|&&
name|NGX_HAVE_IPV6_RECVPKTINFO
operator|)
name|u_char
name|msg_control6
index|[
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in6_pktinfo
argument_list|)
argument_list|)
index|]
decl_stmt|;
endif|#
directive|endif
endif|#
directive|endif
if|if
condition|(
name|ev
operator|->
name|timedout
condition|)
block|{
if|if
condition|(
name|ngx_enable_accept_events
argument_list|(
operator|(
name|ngx_cycle_t
operator|*
operator|)
name|ngx_cycle
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return;
block|}
name|ev
operator|->
name|timedout
operator|=
literal|0
expr_stmt|;
block|}
name|ecf
operator|=
name|ngx_event_get_conf
argument_list|(
name|ngx_cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_event_core_module
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|ngx_event_flags
operator|&
name|NGX_USE_KQUEUE_EVENT
operator|)
condition|)
block|{
name|ev
operator|->
name|available
operator|=
name|ecf
operator|->
name|multi_accept
expr_stmt|;
block|}
name|lc
operator|=
name|ev
operator|->
name|data
expr_stmt|;
name|ls
operator|=
name|lc
operator|->
name|listening
expr_stmt|;
name|ev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"recvmsg on %V, ready: %d"
argument_list|,
operator|&
name|ls
operator|->
name|addr_text
argument_list|,
name|ev
operator|->
name|available
argument_list|)
expr_stmt|;
do|do
block|{
name|ngx_memzero
argument_list|(
operator|&
name|msg
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|msghdr
argument_list|)
argument_list|)
expr_stmt|;
name|iov
index|[
literal|0
index|]
operator|.
name|iov_base
operator|=
operator|(
name|void
operator|*
operator|)
name|buffer
expr_stmt|;
name|iov
index|[
literal|0
index|]
operator|.
name|iov_len
operator|=
sizeof|sizeof
argument_list|(
name|buffer
argument_list|)
expr_stmt|;
name|msg
operator|.
name|msg_name
operator|=
operator|&
name|sa
expr_stmt|;
name|msg
operator|.
name|msg_namelen
operator|=
sizeof|sizeof
argument_list|(
name|ngx_sockaddr_t
argument_list|)
expr_stmt|;
name|msg
operator|.
name|msg_iov
operator|=
name|iov
expr_stmt|;
name|msg
operator|.
name|msg_iovlen
operator|=
literal|1
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
if|if
condition|(
name|ls
operator|->
name|wildcard
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_IP_RECVDSTADDR
operator|||
name|NGX_HAVE_IP_PKTINFO
operator|)
if|if
condition|(
name|ls
operator|->
name|sockaddr
operator|->
name|sa_family
operator|==
name|AF_INET
condition|)
block|{
name|msg
operator|.
name|msg_control
operator|=
operator|&
name|msg_control
expr_stmt|;
name|msg
operator|.
name|msg_controllen
operator|=
sizeof|sizeof
argument_list|(
name|msg_control
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|&&
name|NGX_HAVE_IPV6_RECVPKTINFO
operator|)
if|if
condition|(
name|ls
operator|->
name|sockaddr
operator|->
name|sa_family
operator|==
name|AF_INET6
condition|)
block|{
name|msg
operator|.
name|msg_control
operator|=
operator|&
name|msg_control6
expr_stmt|;
name|msg
operator|.
name|msg_controllen
operator|=
sizeof|sizeof
argument_list|(
name|msg_control6
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
block|}
endif|#
directive|endif
name|n
operator|=
name|recvmsg
argument_list|(
name|lc
operator|->
name|fd
argument_list|,
operator|&
name|msg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
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
operator|==
name|NGX_EAGAIN
condition|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"recvmsg() not ready"
argument_list|)
expr_stmt|;
return|return;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"recvmsg() failed"
argument_list|)
expr_stmt|;
return|return;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
if|if
condition|(
name|msg
operator|.
name|msg_flags
operator|&
operator|(
name|MSG_TRUNC
operator||
name|MSG_CTRUNC
operator|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"recvmsg() truncated data"
argument_list|)
expr_stmt|;
continue|continue;
block|}
endif|#
directive|endif
name|sockaddr
operator|=
name|msg
operator|.
name|msg_name
expr_stmt|;
name|socklen
operator|=
name|msg
operator|.
name|msg_namelen
expr_stmt|;
if|if
condition|(
name|socklen
operator|>
operator|(
name|socklen_t
operator|)
sizeof|sizeof
argument_list|(
name|ngx_sockaddr_t
argument_list|)
condition|)
block|{
name|socklen
operator|=
sizeof|sizeof
argument_list|(
name|ngx_sockaddr_t
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|socklen
operator|==
literal|0
condition|)
block|{
comment|/*              * on Linux recvmsg() returns zero msg_namelen              * when receiving packets from unbound AF_UNIX sockets              */
name|socklen
operator|=
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|sa
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr
argument_list|)
argument_list|)
expr_stmt|;
name|sa
operator|.
name|sockaddr
operator|.
name|sa_family
operator|=
name|ls
operator|->
name|sockaddr
operator|->
name|sa_family
expr_stmt|;
block|}
name|local_sockaddr
operator|=
name|ls
operator|->
name|sockaddr
expr_stmt|;
name|local_socklen
operator|=
name|ls
operator|->
name|socklen
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
if|if
condition|(
name|ls
operator|->
name|wildcard
condition|)
block|{
name|struct
name|cmsghdr
modifier|*
name|cmsg
decl_stmt|;
name|ngx_memcpy
argument_list|(
operator|&
name|lsa
argument_list|,
name|local_sockaddr
argument_list|,
name|local_socklen
argument_list|)
expr_stmt|;
name|local_sockaddr
operator|=
operator|&
name|lsa
operator|.
name|sockaddr
expr_stmt|;
for|for
control|(
name|cmsg
operator|=
name|CMSG_FIRSTHDR
argument_list|(
operator|&
name|msg
argument_list|)
init|;
name|cmsg
operator|!=
name|NULL
condition|;
name|cmsg
operator|=
name|CMSG_NXTHDR
argument_list|(
operator|&
name|msg
argument_list|,
name|cmsg
argument_list|)
control|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_IP_RECVDSTADDR
operator|)
if|if
condition|(
name|cmsg
operator|->
name|cmsg_level
operator|==
name|IPPROTO_IP
operator|&&
name|cmsg
operator|->
name|cmsg_type
operator|==
name|IP_RECVDSTADDR
operator|&&
name|local_sockaddr
operator|->
name|sa_family
operator|==
name|AF_INET
condition|)
block|{
name|struct
name|in_addr
modifier|*
name|addr
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
name|addr
operator|=
operator|(
expr|struct
name|in_addr
operator|*
operator|)
name|CMSG_DATA
argument_list|(
name|cmsg
argument_list|)
expr_stmt|;
name|sin
operator|=
operator|(
expr|struct
name|sockaddr_in
operator|*
operator|)
name|local_sockaddr
expr_stmt|;
name|sin
operator|->
name|sin_addr
operator|=
operator|*
name|addr
expr_stmt|;
break|break;
block|}
elif|#
directive|elif
operator|(
name|NGX_HAVE_IP_PKTINFO
operator|)
if|if
condition|(
name|cmsg
operator|->
name|cmsg_level
operator|==
name|IPPROTO_IP
operator|&&
name|cmsg
operator|->
name|cmsg_type
operator|==
name|IP_PKTINFO
operator|&&
name|local_sockaddr
operator|->
name|sa_family
operator|==
name|AF_INET
condition|)
block|{
name|struct
name|in_pktinfo
modifier|*
name|pkt
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
name|pkt
operator|=
operator|(
expr|struct
name|in_pktinfo
operator|*
operator|)
name|CMSG_DATA
argument_list|(
name|cmsg
argument_list|)
expr_stmt|;
name|sin
operator|=
operator|(
expr|struct
name|sockaddr_in
operator|*
operator|)
name|local_sockaddr
expr_stmt|;
name|sin
operator|->
name|sin_addr
operator|=
name|pkt
operator|->
name|ipi_addr
expr_stmt|;
break|break;
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|&&
name|NGX_HAVE_IPV6_RECVPKTINFO
operator|)
if|if
condition|(
name|cmsg
operator|->
name|cmsg_level
operator|==
name|IPPROTO_IPV6
operator|&&
name|cmsg
operator|->
name|cmsg_type
operator|==
name|IPV6_PKTINFO
operator|&&
name|local_sockaddr
operator|->
name|sa_family
operator|==
name|AF_INET6
condition|)
block|{
name|struct
name|in6_pktinfo
modifier|*
name|pkt6
decl_stmt|;
name|struct
name|sockaddr_in6
modifier|*
name|sin6
decl_stmt|;
name|pkt6
operator|=
operator|(
expr|struct
name|in6_pktinfo
operator|*
operator|)
name|CMSG_DATA
argument_list|(
name|cmsg
argument_list|)
expr_stmt|;
name|sin6
operator|=
operator|(
expr|struct
name|sockaddr_in6
operator|*
operator|)
name|local_sockaddr
expr_stmt|;
name|sin6
operator|->
name|sin6_addr
operator|=
name|pkt6
operator|->
name|ipi6_addr
expr_stmt|;
break|break;
block|}
endif|#
directive|endif
block|}
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_STAT_STUB
operator|)
operator|(
name|void
operator|)
name|ngx_atomic_fetch_add
argument_list|(
name|ngx_stat_accepted
argument_list|,
literal|1
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|ngx_accept_disabled
operator|=
name|ngx_cycle
operator|->
name|connection_n
operator|/
literal|8
operator|-
name|ngx_cycle
operator|->
name|free_connection_n
expr_stmt|;
name|c
operator|=
name|ngx_get_connection
argument_list|(
name|lc
operator|->
name|fd
argument_list|,
name|ev
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
return|return;
block|}
name|c
operator|->
name|shared
operator|=
literal|1
expr_stmt|;
name|c
operator|->
name|type
operator|=
name|SOCK_DGRAM
expr_stmt|;
name|c
operator|->
name|socklen
operator|=
name|socklen
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_STAT_STUB
operator|)
operator|(
name|void
operator|)
name|ngx_atomic_fetch_add
argument_list|(
name|ngx_stat_active
argument_list|,
literal|1
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|c
operator|->
name|pool
operator|=
name|ngx_create_pool
argument_list|(
name|ls
operator|->
name|pool_size
argument_list|,
name|ev
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|pool
operator|==
name|NULL
condition|)
block|{
name|ngx_close_accepted_udp_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|c
operator|->
name|sockaddr
operator|=
name|ngx_palloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|socklen
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|sockaddr
operator|==
name|NULL
condition|)
block|{
name|ngx_close_accepted_udp_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|ngx_memcpy
argument_list|(
name|c
operator|->
name|sockaddr
argument_list|,
name|sockaddr
argument_list|,
name|socklen
argument_list|)
expr_stmt|;
name|log
operator|=
name|ngx_palloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_log_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|log
operator|==
name|NULL
condition|)
block|{
name|ngx_close_accepted_udp_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
operator|*
name|log
operator|=
name|ls
operator|->
name|log
expr_stmt|;
name|c
operator|->
name|send
operator|=
name|ngx_udp_send
expr_stmt|;
name|c
operator|->
name|send_chain
operator|=
name|ngx_udp_send_chain
expr_stmt|;
name|c
operator|->
name|log
operator|=
name|log
expr_stmt|;
name|c
operator|->
name|pool
operator|->
name|log
operator|=
name|log
expr_stmt|;
name|c
operator|->
name|listening
operator|=
name|ls
expr_stmt|;
if|if
condition|(
name|local_sockaddr
operator|==
operator|&
name|lsa
operator|.
name|sockaddr
condition|)
block|{
name|local_sockaddr
operator|=
name|ngx_palloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|local_socklen
argument_list|)
expr_stmt|;
if|if
condition|(
name|local_sockaddr
operator|==
name|NULL
condition|)
block|{
name|ngx_close_accepted_udp_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|ngx_memcpy
argument_list|(
name|local_sockaddr
argument_list|,
operator|&
name|lsa
argument_list|,
name|local_socklen
argument_list|)
expr_stmt|;
block|}
name|c
operator|->
name|local_sockaddr
operator|=
name|local_sockaddr
expr_stmt|;
name|c
operator|->
name|local_socklen
operator|=
name|local_socklen
expr_stmt|;
name|c
operator|->
name|buffer
operator|=
name|ngx_create_temp_buf
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|n
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|buffer
operator|==
name|NULL
condition|)
block|{
name|ngx_close_accepted_udp_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|c
operator|->
name|buffer
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|c
operator|->
name|buffer
operator|->
name|last
argument_list|,
name|buffer
argument_list|,
name|n
argument_list|)
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
name|wev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
name|rev
operator|->
name|log
operator|=
name|log
expr_stmt|;
name|wev
operator|->
name|log
operator|=
name|log
expr_stmt|;
comment|/*          * TODO: MT: - ngx_atomic_fetch_add()          *             or protection by critical section or light mutex          *          * TODO: MP: - allocated in a shared memory          *           - ngx_atomic_fetch_add()          *             or protection by critical section or light mutex          */
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
if|#
directive|if
operator|(
name|NGX_STAT_STUB
operator|)
operator|(
name|void
operator|)
name|ngx_atomic_fetch_add
argument_list|(
name|ngx_stat_handled
argument_list|,
literal|1
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|ls
operator|->
name|addr_ntop
condition|)
block|{
name|c
operator|->
name|addr_text
operator|.
name|data
operator|=
name|ngx_pnalloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|ls
operator|->
name|addr_text_max_len
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|addr_text
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|ngx_close_accepted_udp_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|c
operator|->
name|addr_text
operator|.
name|len
operator|=
name|ngx_sock_ntop
argument_list|(
name|c
operator|->
name|sockaddr
argument_list|,
name|c
operator|->
name|socklen
argument_list|,
name|c
operator|->
name|addr_text
operator|.
name|data
argument_list|,
name|ls
operator|->
name|addr_text_max_len
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|addr_text
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|ngx_close_accepted_udp_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
block|{
name|ngx_str_t
name|addr
decl_stmt|;
name|u_char
name|text
index|[
name|NGX_SOCKADDR_STRLEN
index|]
decl_stmt|;
name|ngx_debug_accepted_connection
argument_list|(
name|ecf
argument_list|,
name|c
argument_list|)
expr_stmt|;
if|if
condition|(
name|log
operator|->
name|log_level
operator|&
name|NGX_LOG_DEBUG_EVENT
condition|)
block|{
name|addr
operator|.
name|data
operator|=
name|text
expr_stmt|;
name|addr
operator|.
name|len
operator|=
name|ngx_sock_ntop
argument_list|(
name|c
operator|->
name|sockaddr
argument_list|,
name|c
operator|->
name|socklen
argument_list|,
name|text
argument_list|,
name|NGX_SOCKADDR_STRLEN
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|ngx_log_debug4
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"*%uA recvmsg: %V fd:%d n:%z"
argument_list|,
name|c
operator|->
name|number
argument_list|,
operator|&
name|addr
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|n
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
name|log
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
name|log
operator|->
name|handler
operator|=
name|NULL
expr_stmt|;
name|ls
operator|->
name|handler
argument_list|(
name|c
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_KQUEUE_EVENT
condition|)
block|{
name|ev
operator|->
name|available
operator|-=
name|n
expr_stmt|;
block|}
block|}
do|while
condition|(
name|ev
operator|->
name|available
condition|)
do|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_close_accepted_udp_connection (ngx_connection_t * c)
name|ngx_close_accepted_udp_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
name|ngx_free_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
name|c
operator|->
name|fd
operator|=
operator|(
name|ngx_socket_t
operator|)
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|pool
condition|)
block|{
name|ngx_destroy_pool
argument_list|(
name|c
operator|->
name|pool
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_STAT_STUB
operator|)
operator|(
name|void
operator|)
name|ngx_atomic_fetch_add
argument_list|(
name|ngx_stat_active
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

