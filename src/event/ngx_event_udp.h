begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_UDP_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_UDP_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_UDP_H_INCLUDED_
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

begin_if
if|#
directive|if
operator|!
operator|(
name|NGX_WIN32
operator|)
end_if

begin_if
if|#
directive|if
operator|(
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
expr|\
operator|&&
operator|(
name|NGX_HAVE_IP_SENDSRCADDR
operator|||
name|NGX_HAVE_IP_RECVDSTADDR
expr|\
operator|||
name|NGX_HAVE_IP_PKTINFO
expr|\
operator|||
operator|(
name|NGX_HAVE_INET6
operator|&&
name|NGX_HAVE_IPV6_RECVPKTINFO
operator|)
operator|)
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_ADDRINFO_CMSG
define|#
directive|define
name|NGX_HAVE_ADDRINFO_CMSG
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_ADDRINFO_CMSG
operator|)
end_if

begin_typedef
DECL|union|__anon2a0924d6010a
typedef|typedef
union|union
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_IP_SENDSRCADDR
operator|||
name|NGX_HAVE_IP_RECVDSTADDR
operator|)
DECL|member|addr
name|struct
name|in_addr
name|addr
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_IP_PKTINFO
operator|)
DECL|member|pkt
name|struct
name|in_pktinfo
name|pkt
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
DECL|member|pkt6
name|struct
name|in6_pktinfo
name|pkt6
decl_stmt|;
endif|#
directive|endif
DECL|typedef|ngx_addrinfo_t
block|}
name|ngx_addrinfo_t
typedef|;
end_typedef

begin_function_decl
name|size_t
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_event_recvmsg
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ssize_t
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_udp_rbtree_insert_value
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
name|temp
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_delete_udp_connection
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_UDP_H_INCLUDED_ */
end_comment

end_unit

