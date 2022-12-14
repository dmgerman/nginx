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

begin_function_decl
specifier|static
name|ngx_chain_t
modifier|*
name|ngx_udp_output_chain_to_iovec
parameter_list|(
name|ngx_iovec_t
modifier|*
name|vec
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ssize_t
name|ngx_sendmsg_vec
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_iovec_t
modifier|*
name|vec
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_udp_unix_sendmsg_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_udp_unix_sendmsg_chain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|,
name|off_t
name|limit
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|;
name|off_t
name|send
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|ngx_iovec_t
name|vec
decl_stmt|;
name|struct
name|iovec
name|iovs
index|[
name|NGX_IOVS_PREALLOCATE
index|]
decl_stmt|;
name|wev
operator|=
name|c
operator|->
name|write
expr_stmt|;
if|if
condition|(
operator|!
name|wev
operator|->
name|ready
condition|)
block|{
return|return
name|in
return|;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
if|if
condition|(
operator|(
name|ngx_event_flags
operator|&
name|NGX_USE_KQUEUE_EVENT
operator|)
operator|&&
name|wev
operator|->
name|pending_eof
condition|)
block|{
operator|(
name|void
operator|)
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|wev
operator|->
name|kq_errno
argument_list|,
literal|"kevent() reported about an closed connection"
argument_list|)
expr_stmt|;
name|wev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
endif|#
directive|endif
comment|/* the maximum limit size is the maximum size_t value - the page size */
if|if
condition|(
name|limit
operator|==
literal|0
operator|||
name|limit
operator|>
operator|(
name|off_t
operator|)
operator|(
name|NGX_MAX_SIZE_T_VALUE
operator|-
name|ngx_pagesize
operator|)
condition|)
block|{
name|limit
operator|=
name|NGX_MAX_SIZE_T_VALUE
operator|-
name|ngx_pagesize
expr_stmt|;
block|}
name|send
operator|=
literal|0
expr_stmt|;
name|vec
operator|.
name|iovs
operator|=
name|iovs
expr_stmt|;
name|vec
operator|.
name|nalloc
operator|=
name|NGX_IOVS_PREALLOCATE
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
comment|/* create the iovec and coalesce the neighbouring bufs */
name|cl
operator|=
name|ngx_udp_output_chain_to_iovec
argument_list|(
operator|&
name|vec
argument_list|,
name|in
argument_list|,
name|c
operator|->
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|==
name|NGX_CHAIN_ERROR
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
if|if
condition|(
name|cl
operator|&&
name|cl
operator|->
name|buf
operator|->
name|in_file
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"file buf in sendmsg "
literal|"t:%d r:%d f:%d %p %p-%p %p %O-%O"
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|temporary
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|recycled
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|in_file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|start
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|last
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_pos
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|file_last
argument_list|)
expr_stmt|;
name|ngx_debug_point
argument_list|()
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
if|if
condition|(
name|cl
operator|==
name|in
condition|)
block|{
return|return
name|in
return|;
block|}
name|send
operator|+=
name|vec
operator|.
name|size
expr_stmt|;
name|n
operator|=
name|ngx_sendmsg_vec
argument_list|(
name|c
argument_list|,
operator|&
name|vec
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
name|wev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
return|return
name|in
return|;
block|}
name|c
operator|->
name|sent
operator|+=
name|n
expr_stmt|;
name|in
operator|=
name|ngx_chain_update_sent
argument_list|(
name|in
argument_list|,
name|n
argument_list|)
expr_stmt|;
if|if
condition|(
name|send
operator|>=
name|limit
operator|||
name|in
operator|==
name|NULL
condition|)
block|{
return|return
name|in
return|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|ngx_chain_t
modifier|*
DECL|function|ngx_udp_output_chain_to_iovec (ngx_iovec_t * vec,ngx_chain_t * in,ngx_log_t * log)
name|ngx_udp_output_chain_to_iovec
parameter_list|(
name|ngx_iovec_t
modifier|*
name|vec
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|size_t
name|total
decl_stmt|,
name|size
decl_stmt|;
name|u_char
modifier|*
name|prev
decl_stmt|;
name|ngx_uint_t
name|n
decl_stmt|,
name|flush
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|struct
name|iovec
modifier|*
name|iov
decl_stmt|;
name|cl
operator|=
name|in
expr_stmt|;
name|iov
operator|=
name|NULL
expr_stmt|;
name|prev
operator|=
name|NULL
expr_stmt|;
name|total
operator|=
literal|0
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
name|flush
operator|=
literal|0
expr_stmt|;
for|for
control|(
comment|/* void */
init|;
name|in
operator|&&
operator|!
name|flush
condition|;
name|in
operator|=
name|in
operator|->
name|next
control|)
block|{
if|if
condition|(
name|in
operator|->
name|buf
operator|->
name|flush
operator|||
name|in
operator|->
name|buf
operator|->
name|last_buf
condition|)
block|{
name|flush
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|ngx_buf_special
argument_list|(
name|in
operator|->
name|buf
argument_list|)
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|in
operator|->
name|buf
operator|->
name|in_file
condition|)
block|{
break|break;
block|}
if|if
condition|(
operator|!
name|ngx_buf_in_memory
argument_list|(
name|in
operator|->
name|buf
argument_list|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"bad buf in output chain "
literal|"t:%d r:%d f:%d %p %p-%p %p %O-%O"
argument_list|,
name|in
operator|->
name|buf
operator|->
name|temporary
argument_list|,
name|in
operator|->
name|buf
operator|->
name|recycled
argument_list|,
name|in
operator|->
name|buf
operator|->
name|in_file
argument_list|,
name|in
operator|->
name|buf
operator|->
name|start
argument_list|,
name|in
operator|->
name|buf
operator|->
name|pos
argument_list|,
name|in
operator|->
name|buf
operator|->
name|last
argument_list|,
name|in
operator|->
name|buf
operator|->
name|file
argument_list|,
name|in
operator|->
name|buf
operator|->
name|file_pos
argument_list|,
name|in
operator|->
name|buf
operator|->
name|file_last
argument_list|)
expr_stmt|;
name|ngx_debug_point
argument_list|()
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|size
operator|=
name|in
operator|->
name|buf
operator|->
name|last
operator|-
name|in
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
if|if
condition|(
name|prev
operator|==
name|in
operator|->
name|buf
operator|->
name|pos
condition|)
block|{
name|iov
operator|->
name|iov_len
operator|+=
name|size
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|n
operator|==
name|vec
operator|->
name|nalloc
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"too many parts in a datagram"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|iov
operator|=
operator|&
name|vec
operator|->
name|iovs
index|[
name|n
operator|++
index|]
expr_stmt|;
name|iov
operator|->
name|iov_base
operator|=
operator|(
name|void
operator|*
operator|)
name|in
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|iov
operator|->
name|iov_len
operator|=
name|size
expr_stmt|;
block|}
name|prev
operator|=
name|in
operator|->
name|buf
operator|->
name|pos
operator|+
name|size
expr_stmt|;
name|total
operator|+=
name|size
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|flush
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_SUPPRESS_WARN
operator|)
name|vec
operator|->
name|size
operator|=
literal|0
expr_stmt|;
name|vec
operator|->
name|count
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
return|return
name|cl
return|;
block|}
comment|/* zero-sized datagram; pretend to have at least 1 iov */
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|iov
operator|=
operator|&
name|vec
operator|->
name|iovs
index|[
name|n
operator|++
index|]
expr_stmt|;
name|iov
operator|->
name|iov_base
operator|=
name|NULL
expr_stmt|;
name|iov
operator|->
name|iov_len
operator|=
literal|0
expr_stmt|;
block|}
name|vec
operator|->
name|count
operator|=
name|n
expr_stmt|;
name|vec
operator|->
name|size
operator|=
name|total
expr_stmt|;
return|return
name|in
return|;
block|}
end_function

begin_function
specifier|static
name|ssize_t
DECL|function|ngx_sendmsg_vec (ngx_connection_t * c,ngx_iovec_t * vec)
name|ngx_sendmsg_vec
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_iovec_t
modifier|*
name|vec
parameter_list|)
block|{
name|struct
name|msghdr
name|msg
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_ADDRINFO_CMSG
operator|)
name|struct
name|cmsghdr
modifier|*
name|cmsg
decl_stmt|;
name|u_char
name|msg_control
index|[
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_addrinfo_t
argument_list|)
argument_list|)
index|]
decl_stmt|;
endif|#
directive|endif
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
if|if
condition|(
name|c
operator|->
name|socklen
condition|)
block|{
name|msg
operator|.
name|msg_name
operator|=
name|c
operator|->
name|sockaddr
expr_stmt|;
name|msg
operator|.
name|msg_namelen
operator|=
name|c
operator|->
name|socklen
expr_stmt|;
block|}
name|msg
operator|.
name|msg_iov
operator|=
name|vec
operator|->
name|iovs
expr_stmt|;
name|msg
operator|.
name|msg_iovlen
operator|=
name|vec
operator|->
name|count
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_ADDRINFO_CMSG
operator|)
if|if
condition|(
name|c
operator|->
name|listening
operator|&&
name|c
operator|->
name|listening
operator|->
name|wildcard
operator|&&
name|c
operator|->
name|local_sockaddr
condition|)
block|{
name|msg
operator|.
name|msg_control
operator|=
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
name|ngx_memzero
argument_list|(
name|msg_control
argument_list|,
sizeof|sizeof
argument_list|(
name|msg_control
argument_list|)
argument_list|)
expr_stmt|;
name|cmsg
operator|=
name|CMSG_FIRSTHDR
argument_list|(
operator|&
name|msg
argument_list|)
expr_stmt|;
name|msg
operator|.
name|msg_controllen
operator|=
name|ngx_set_srcaddr_cmsg
argument_list|(
name|cmsg
argument_list|,
name|c
operator|->
name|local_sockaddr
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
return|return
name|ngx_sendmsg
argument_list|(
name|c
argument_list|,
operator|&
name|msg
argument_list|,
literal|0
argument_list|)
return|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_ADDRINFO_CMSG
operator|)
end_if

begin_function
name|size_t
DECL|function|ngx_set_srcaddr_cmsg (struct cmsghdr * cmsg,struct sockaddr * local_sockaddr)
name|ngx_set_srcaddr_cmsg
parameter_list|(
name|struct
name|cmsghdr
modifier|*
name|cmsg
parameter_list|,
name|struct
name|sockaddr
modifier|*
name|local_sockaddr
parameter_list|)
block|{
name|size_t
name|len
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_IP_SENDSRCADDR
operator|)
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
elif|#
directive|elif
operator|(
name|NGX_HAVE_IP_PKTINFO
operator|)
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
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|&&
name|NGX_HAVE_IPV6_RECVPKTINFO
operator|)
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
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_IP_SENDSRCADDR
operator|)
operator|||
operator|(
name|NGX_HAVE_IP_PKTINFO
operator|)
if|if
condition|(
name|local_sockaddr
operator|->
name|sa_family
operator|==
name|AF_INET
condition|)
block|{
name|cmsg
operator|->
name|cmsg_level
operator|=
name|IPPROTO_IP
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_IP_SENDSRCADDR
operator|)
name|cmsg
operator|->
name|cmsg_type
operator|=
name|IP_SENDSRCADDR
expr_stmt|;
name|cmsg
operator|->
name|cmsg_len
operator|=
name|CMSG_LEN
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in_addr
argument_list|)
argument_list|)
expr_stmt|;
name|len
operator|=
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in_addr
argument_list|)
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
operator|*
name|addr
operator|=
name|sin
operator|->
name|sin_addr
expr_stmt|;
elif|#
directive|elif
operator|(
name|NGX_HAVE_IP_PKTINFO
operator|)
name|cmsg
operator|->
name|cmsg_type
operator|=
name|IP_PKTINFO
expr_stmt|;
name|cmsg
operator|->
name|cmsg_len
operator|=
name|CMSG_LEN
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in_pktinfo
argument_list|)
argument_list|)
expr_stmt|;
name|len
operator|=
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in_pktinfo
argument_list|)
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
name|ngx_memzero
argument_list|(
name|pkt
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|in_pktinfo
argument_list|)
argument_list|)
expr_stmt|;
name|pkt
operator|->
name|ipi_spec_dst
operator|=
name|sin
operator|->
name|sin_addr
expr_stmt|;
endif|#
directive|endif
return|return
name|len
return|;
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
name|local_sockaddr
operator|->
name|sa_family
operator|==
name|AF_INET6
condition|)
block|{
name|cmsg
operator|->
name|cmsg_level
operator|=
name|IPPROTO_IPV6
expr_stmt|;
name|cmsg
operator|->
name|cmsg_type
operator|=
name|IPV6_PKTINFO
expr_stmt|;
name|cmsg
operator|->
name|cmsg_len
operator|=
name|CMSG_LEN
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in6_pktinfo
argument_list|)
argument_list|)
expr_stmt|;
name|len
operator|=
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
expr|struct
name|in6_pktinfo
argument_list|)
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
name|ngx_memzero
argument_list|(
name|pkt6
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|in6_pktinfo
argument_list|)
argument_list|)
expr_stmt|;
name|pkt6
operator|->
name|ipi6_addr
operator|=
name|sin6
operator|->
name|sin6_addr
expr_stmt|;
return|return
name|len
return|;
block|}
endif|#
directive|endif
return|return
literal|0
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_get_srcaddr_cmsg (struct cmsghdr * cmsg,struct sockaddr * local_sockaddr)
name|ngx_get_srcaddr_cmsg
parameter_list|(
name|struct
name|cmsghdr
modifier|*
name|cmsg
parameter_list|,
name|struct
name|sockaddr
modifier|*
name|local_sockaddr
parameter_list|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_IP_RECVDSTADDR
operator|)
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
elif|#
directive|elif
operator|(
name|NGX_HAVE_IP_PKTINFO
operator|)
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
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|&&
name|NGX_HAVE_IPV6_RECVPKTINFO
operator|)
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
endif|#
directive|endif
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
return|return
name|NGX_OK
return|;
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
return|return
name|NGX_OK
return|;
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
return|return
name|NGX_OK
return|;
block|}
endif|#
directive|endif
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|ssize_t
DECL|function|ngx_sendmsg (ngx_connection_t * c,struct msghdr * msg,int flags)
name|ngx_sendmsg
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|struct
name|msghdr
modifier|*
name|msg
parameter_list|,
name|int
name|flags
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
name|size_t
name|size
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
endif|#
directive|endif
name|eintr
label|:
name|n
operator|=
name|sendmsg
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|msg
argument_list|,
name|flags
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
name|ngx_errno
expr_stmt|;
switch|switch
condition|(
name|err
condition|)
block|{
case|case
name|NGX_EAGAIN
case|:
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"sendmsg() not ready"
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
case|case
name|NGX_EINTR
case|:
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"sendmsg() was interrupted"
argument_list|)
expr_stmt|;
goto|goto
name|eintr
goto|;
default|default:
name|c
operator|->
name|write
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|err
argument_list|,
literal|"sendmsg() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|size
operator|=
literal|0
init|;
name|i
operator|<
operator|(
name|size_t
operator|)
name|msg
operator|->
name|msg_iovlen
condition|;
name|i
operator|++
control|)
block|{
name|size
operator|+=
name|msg
operator|->
name|msg_iov
index|[
name|i
index|]
operator|.
name|iov_len
expr_stmt|;
block|}
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"sendmsg: %z of %uz"
argument_list|,
name|n
argument_list|,
name|size
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|n
return|;
block|}
end_function

end_unit

