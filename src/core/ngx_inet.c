begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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

begin_comment
comment|/*  * ngx_sock_ntop() and ngx_inet_ntop() may be implemented as  * "ngx_sprintf(text, "%ud.%ud.%ud.%ud", p[0], p[1], p[2], p[3])",  * however, they were implemented long before the ngx_sprintf() appeared  * and they are faster by 1.5-2.5 times, so it is worth to keep them.  *  * By the way, the implementation using ngx_sprintf() is faster by 2.5-3 times  * than using FreeBSD libc's snprintf().  */
end_comment

begin_function
specifier|static
DECL|function|ngx_sprint_uchar (u_char * text,u_char c,size_t len)
name|ngx_inline
name|size_t
name|ngx_sprint_uchar
parameter_list|(
name|u_char
modifier|*
name|text
parameter_list|,
name|u_char
name|c
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|size_t
name|n
decl_stmt|;
name|ngx_uint_t
name|c1
decl_stmt|,
name|c2
decl_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
return|return
name|n
return|;
block|}
name|c1
operator|=
name|c
operator|/
literal|100
expr_stmt|;
if|if
condition|(
name|c1
condition|)
block|{
operator|*
name|text
operator|++
operator|=
operator|(
name|u_char
operator|)
operator|(
name|c1
operator|+
literal|'0'
operator|)
expr_stmt|;
name|n
operator|++
expr_stmt|;
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
return|return
name|n
return|;
block|}
block|}
name|c2
operator|=
operator|(
name|c
operator|%
literal|100
operator|)
operator|/
literal|10
expr_stmt|;
if|if
condition|(
name|c1
operator|||
name|c2
condition|)
block|{
operator|*
name|text
operator|++
operator|=
operator|(
name|u_char
operator|)
operator|(
name|c2
operator|+
literal|'0'
operator|)
expr_stmt|;
name|n
operator|++
expr_stmt|;
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
return|return
name|n
return|;
block|}
block|}
name|c2
operator|=
name|c
operator|%
literal|10
expr_stmt|;
operator|*
name|text
operator|++
operator|=
operator|(
name|u_char
operator|)
operator|(
name|c2
operator|+
literal|'0'
operator|)
expr_stmt|;
name|n
operator|++
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_comment
comment|/* AF_INET only */
end_comment

begin_function
name|size_t
DECL|function|ngx_sock_ntop (int family,struct sockaddr * sa,u_char * text,size_t len)
name|ngx_sock_ntop
parameter_list|(
name|int
name|family
parameter_list|,
name|struct
name|sockaddr
modifier|*
name|sa
parameter_list|,
name|u_char
modifier|*
name|text
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
name|size_t
name|n
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
if|if
condition|(
name|len
operator|==
literal|0
condition|)
block|{
return|return
literal|0
return|;
block|}
if|if
condition|(
name|family
operator|!=
name|AF_INET
condition|)
block|{
return|return
literal|0
return|;
block|}
name|sin
operator|=
operator|(
expr|struct
name|sockaddr_in
operator|*
operator|)
name|sa
expr_stmt|;
name|p
operator|=
operator|(
name|u_char
operator|*
operator|)
operator|&
name|sin
operator|->
name|sin_addr
expr_stmt|;
if|if
condition|(
name|len
operator|>
name|INET_ADDRSTRLEN
condition|)
block|{
name|len
operator|=
name|INET_ADDRSTRLEN
expr_stmt|;
block|}
name|n
operator|=
name|ngx_sprint_uchar
argument_list|(
name|text
argument_list|,
name|p
index|[
literal|0
index|]
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|i
operator|=
literal|1
expr_stmt|;
do|do
block|{
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
name|text
index|[
name|n
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|n
return|;
block|}
name|text
index|[
name|n
operator|++
index|]
operator|=
literal|'.'
expr_stmt|;
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
name|text
index|[
name|n
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|n
return|;
block|}
name|n
operator|+=
name|ngx_sprint_uchar
argument_list|(
operator|&
name|text
index|[
name|n
index|]
argument_list|,
name|p
index|[
name|i
operator|++
index|]
argument_list|,
name|len
operator|-
name|n
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|i
operator|<
literal|4
condition|)
do|;
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
name|text
index|[
name|n
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|n
return|;
block|}
name|text
index|[
name|n
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_function
name|size_t
DECL|function|ngx_inet_ntop (int family,void * addr,u_char * text,size_t len)
name|ngx_inet_ntop
parameter_list|(
name|int
name|family
parameter_list|,
name|void
modifier|*
name|addr
parameter_list|,
name|u_char
modifier|*
name|text
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
name|size_t
name|n
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
if|if
condition|(
name|len
operator|==
literal|0
condition|)
block|{
return|return
literal|0
return|;
block|}
if|if
condition|(
name|family
operator|!=
name|AF_INET
condition|)
block|{
return|return
literal|0
return|;
block|}
name|p
operator|=
operator|(
name|u_char
operator|*
operator|)
name|addr
expr_stmt|;
if|if
condition|(
name|len
operator|>
name|INET_ADDRSTRLEN
condition|)
block|{
name|len
operator|=
name|INET_ADDRSTRLEN
expr_stmt|;
block|}
name|n
operator|=
name|ngx_sprint_uchar
argument_list|(
name|text
argument_list|,
name|p
index|[
literal|0
index|]
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|i
operator|=
literal|1
expr_stmt|;
do|do
block|{
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
name|text
index|[
name|n
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|n
return|;
block|}
name|text
index|[
name|n
operator|++
index|]
operator|=
literal|'.'
expr_stmt|;
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
name|text
index|[
name|n
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|n
return|;
block|}
name|n
operator|+=
name|ngx_sprint_uchar
argument_list|(
operator|&
name|text
index|[
name|n
index|]
argument_list|,
name|p
index|[
name|i
operator|++
index|]
argument_list|,
name|len
operator|-
name|n
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|i
operator|<
literal|4
condition|)
do|;
if|if
condition|(
name|len
operator|==
name|n
condition|)
block|{
name|text
index|[
name|n
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|n
return|;
block|}
name|text
index|[
name|n
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_comment
comment|/* AF_INET only */
end_comment

begin_function
name|ngx_int_t
DECL|function|ngx_ptocidr (ngx_str_t * text,void * cidr)
name|ngx_ptocidr
parameter_list|(
name|ngx_str_t
modifier|*
name|text
parameter_list|,
name|void
modifier|*
name|cidr
parameter_list|)
block|{
name|ngx_int_t
name|m
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_inet_cidr_t
modifier|*
name|in_cidr
decl_stmt|;
name|in_cidr
operator|=
name|cidr
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|text
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|text
operator|->
name|data
index|[
name|i
index|]
operator|==
literal|'/'
condition|)
block|{
break|break;
block|}
block|}
if|if
condition|(
name|i
operator|==
name|text
operator|->
name|len
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|text
operator|->
name|data
index|[
name|i
index|]
operator|=
literal|'\0'
expr_stmt|;
name|in_cidr
operator|->
name|addr
operator|=
name|inet_addr
argument_list|(
operator|(
name|char
operator|*
operator|)
name|text
operator|->
name|data
argument_list|)
expr_stmt|;
name|text
operator|->
name|data
index|[
name|i
index|]
operator|=
literal|'/'
expr_stmt|;
if|if
condition|(
name|in_cidr
operator|->
name|addr
operator|==
name|INADDR_NONE
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|m
operator|=
name|ngx_atoi
argument_list|(
operator|&
name|text
operator|->
name|data
index|[
name|i
operator|+
literal|1
index|]
argument_list|,
name|text
operator|->
name|len
operator|-
operator|(
name|i
operator|+
literal|1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|m
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|m
operator|==
literal|0
condition|)
block|{
comment|/* the x86 compilers use the shl instruction that shifts by modulo 32 */
name|in_cidr
operator|->
name|mask
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|in_cidr
operator|->
name|mask
operator|=
name|htonl
argument_list|(
operator|(
name|ngx_uint_t
operator|)
operator|(
literal|0
operator|-
operator|(
literal|1
operator|<<
operator|(
literal|32
operator|-
name|m
operator|)
operator|)
operator|)
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_peers_t
modifier|*
DECL|function|ngx_inet_upstream_parse (ngx_conf_t * cf,ngx_inet_upstream_t * u)
name|ngx_inet_upstream_parse
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_inet_upstream_t
modifier|*
name|u
parameter_list|)
block|{
name|char
modifier|*
name|err
decl_stmt|;
name|u_char
modifier|*
name|host
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|in_addr_t
name|in_addr
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_peers_t
modifier|*
name|peers
decl_stmt|;
name|struct
name|hostent
modifier|*
name|h
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
name|err
operator|=
name|ngx_inet_parse_host_port
argument_list|(
name|u
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"%s in upstream \"%V\""
argument_list|,
name|err
argument_list|,
operator|&
name|u
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|u
operator|->
name|default_port
condition|)
block|{
if|if
condition|(
name|u
operator|->
name|default_port_value
operator|==
literal|0
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"no port in upstream \"%V\""
argument_list|,
operator|&
name|u
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|u
operator|->
name|port
operator|=
name|u
operator|->
name|default_port_value
expr_stmt|;
name|u
operator|->
name|port_text
operator|.
name|data
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
literal|"65536"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|u
operator|->
name|port_text
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|u
operator|->
name|port_text
operator|.
name|len
operator|=
name|ngx_sprintf
argument_list|(
name|u
operator|->
name|port_text
operator|.
name|data
argument_list|,
literal|"%d"
argument_list|,
name|u
operator|->
name|default_port_value
argument_list|)
operator|-
name|u
operator|->
name|port_text
operator|.
name|data
expr_stmt|;
block|}
if|else if
condition|(
name|u
operator|->
name|port
condition|)
block|{
if|if
condition|(
name|u
operator|->
name|port
operator|==
name|u
operator|->
name|default_port_value
condition|)
block|{
name|u
operator|->
name|default_port
operator|=
literal|1
expr_stmt|;
block|}
block|}
else|else
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"no port in upstream \"%V\""
argument_list|,
operator|&
name|u
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|u
operator|->
name|host
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"no host in upstream \"%V\""
argument_list|,
operator|&
name|u
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|u
operator|->
name|port
operator|=
name|htons
argument_list|(
name|u
operator|->
name|port
argument_list|)
expr_stmt|;
name|host
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|u
operator|->
name|host
operator|.
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|host
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
operator|(
name|void
operator|)
name|ngx_cpystrn
argument_list|(
name|host
argument_list|,
name|u
operator|->
name|host
operator|.
name|data
argument_list|,
name|u
operator|->
name|host
operator|.
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
comment|/* AF_INET only */
name|in_addr
operator|=
name|inet_addr
argument_list|(
operator|(
name|char
operator|*
operator|)
name|host
argument_list|)
expr_stmt|;
if|if
condition|(
name|in_addr
operator|==
name|INADDR_NONE
condition|)
block|{
name|h
operator|=
name|gethostbyname
argument_list|(
operator|(
name|char
operator|*
operator|)
name|host
argument_list|)
expr_stmt|;
if|if
condition|(
name|h
operator|==
name|NULL
operator|||
name|h
operator|->
name|h_addr_list
index|[
literal|0
index|]
operator|==
name|NULL
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"host %s is not found in upstream \"%V\""
argument_list|,
name|host
argument_list|,
operator|&
name|u
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|h
operator|->
name|h_addr_list
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
comment|/* void */
block|}
comment|/* MP: ngx_shared_palloc() */
name|peers
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_peers_t
argument_list|)
operator|+
sizeof|sizeof
argument_list|(
name|ngx_peer_t
argument_list|)
operator|*
operator|(
name|i
operator|-
literal|1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|peers
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|peers
operator|->
name|number
operator|=
name|i
expr_stmt|;
name|peers
operator|->
name|weight
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|h
operator|->
name|h_addr_list
index|[
name|i
index|]
operator|!=
name|NULL
condition|;
name|i
operator|++
control|)
block|{
name|sin
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|sin
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|sin
operator|->
name|sin_family
operator|=
name|AF_INET
expr_stmt|;
name|sin
operator|->
name|sin_port
operator|=
name|u
operator|->
name|port
expr_stmt|;
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
operator|=
operator|*
operator|(
name|in_addr_t
operator|*
operator|)
operator|(
name|h
operator|->
name|h_addr_list
index|[
name|i
index|]
operator|)
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|sockaddr
operator|=
operator|(
expr|struct
name|sockaddr
operator|*
operator|)
name|sin
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|socklen
operator|=
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|)
expr_stmt|;
name|len
operator|=
name|INET_ADDRSTRLEN
operator|-
literal|1
operator|+
literal|1
operator|+
name|u
operator|->
name|port_text
operator|.
name|len
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|len
operator|=
name|ngx_sock_ntop
argument_list|(
name|AF_INET
argument_list|,
operator|(
expr|struct
name|sockaddr
operator|*
operator|)
name|sin
argument_list|,
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
index|[
name|len
operator|++
index|]
operator|=
literal|':'
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
operator|+
name|len
argument_list|,
name|u
operator|->
name|port_text
operator|.
name|data
argument_list|,
name|u
operator|->
name|port_text
operator|.
name|len
argument_list|)
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|=
name|len
operator|+
name|u
operator|->
name|port_text
operator|.
name|len
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|uri_separator
operator|=
literal|""
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/* MP: ngx_shared_palloc() */
name|peers
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_peers_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|peers
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|sin
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|sin
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|peers
operator|->
name|number
operator|=
literal|1
expr_stmt|;
name|sin
operator|->
name|sin_family
operator|=
name|AF_INET
expr_stmt|;
name|sin
operator|->
name|sin_port
operator|=
name|u
operator|->
name|port
expr_stmt|;
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
operator|=
name|in_addr
expr_stmt|;
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|sockaddr
operator|=
operator|(
expr|struct
name|sockaddr
operator|*
operator|)
name|sin
expr_stmt|;
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|socklen
operator|=
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|)
expr_stmt|;
name|len
operator|=
name|u
operator|->
name|host
operator|.
name|len
operator|+
literal|1
operator|+
name|u
operator|->
name|port_text
operator|.
name|len
expr_stmt|;
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|name
operator|.
name|len
operator|=
name|len
expr_stmt|;
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|name
operator|.
name|data
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|name
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|len
operator|=
name|u
operator|->
name|host
operator|.
name|len
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|name
operator|.
name|data
argument_list|,
name|u
operator|->
name|host
operator|.
name|data
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|name
operator|.
name|data
index|[
name|len
operator|++
index|]
operator|=
literal|':'
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|name
operator|.
name|data
operator|+
name|len
argument_list|,
name|u
operator|->
name|port_text
operator|.
name|data
argument_list|,
name|u
operator|->
name|port_text
operator|.
name|len
argument_list|)
expr_stmt|;
name|peers
operator|->
name|peer
index|[
literal|0
index|]
operator|.
name|uri_separator
operator|=
literal|""
expr_stmt|;
block|}
return|return
name|peers
return|;
block|}
end_function

begin_function
name|char
modifier|*
DECL|function|ngx_inet_parse_host_port (ngx_inet_upstream_t * u)
name|ngx_inet_parse_host_port
parameter_list|(
name|ngx_inet_upstream_t
modifier|*
name|u
parameter_list|)
block|{
name|size_t
name|i
decl_stmt|;
name|ngx_int_t
name|port
decl_stmt|;
name|ngx_str_t
modifier|*
name|url
decl_stmt|;
name|url
operator|=
operator|&
name|u
operator|->
name|url
expr_stmt|;
if|if
condition|(
name|u
operator|->
name|port_only
condition|)
block|{
name|i
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|url
operator|->
name|data
index|[
literal|0
index|]
operator|==
literal|':'
operator|||
name|url
operator|->
name|data
index|[
literal|0
index|]
operator|==
literal|'/'
condition|)
block|{
return|return
literal|"invalid host"
return|;
block|}
name|i
operator|=
literal|1
expr_stmt|;
block|}
name|u
operator|->
name|host
operator|.
name|data
operator|=
name|url
operator|->
name|data
expr_stmt|;
name|u
operator|->
name|host_header
operator|=
operator|*
name|url
expr_stmt|;
for|for
control|(
comment|/* void */
init|;
name|i
operator|<
name|url
operator|->
name|len
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|url
operator|->
name|data
index|[
name|i
index|]
operator|==
literal|':'
condition|)
block|{
name|u
operator|->
name|port_text
operator|.
name|data
operator|=
operator|&
name|url
operator|->
name|data
index|[
name|i
index|]
operator|+
literal|1
expr_stmt|;
name|u
operator|->
name|host
operator|.
name|len
operator|=
name|i
expr_stmt|;
if|if
condition|(
operator|!
name|u
operator|->
name|uri_part
condition|)
block|{
name|u
operator|->
name|port_text
operator|.
name|len
operator|=
operator|&
name|url
operator|->
name|data
index|[
name|url
operator|->
name|len
index|]
operator|-
name|u
operator|->
name|port_text
operator|.
name|data
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
name|url
operator|->
name|data
index|[
name|i
index|]
operator|==
literal|'/'
condition|)
block|{
name|u
operator|->
name|uri
operator|.
name|data
operator|=
operator|&
name|url
operator|->
name|data
index|[
name|i
index|]
expr_stmt|;
name|u
operator|->
name|uri
operator|.
name|len
operator|=
name|url
operator|->
name|len
operator|-
name|i
expr_stmt|;
name|u
operator|->
name|host_header
operator|.
name|len
operator|=
name|i
expr_stmt|;
if|if
condition|(
name|u
operator|->
name|host
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|u
operator|->
name|host
operator|.
name|len
operator|=
name|i
expr_stmt|;
block|}
if|if
condition|(
name|u
operator|->
name|port_text
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|u
operator|->
name|default_port
operator|=
literal|1
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|u
operator|->
name|port_text
operator|.
name|len
operator|=
operator|&
name|url
operator|->
name|data
index|[
name|i
index|]
operator|-
name|u
operator|->
name|port_text
operator|.
name|data
expr_stmt|;
if|if
condition|(
name|u
operator|->
name|port_text
operator|.
name|len
operator|==
literal|0
condition|)
block|{
return|return
literal|"invalid port"
return|;
block|}
break|break;
block|}
block|}
if|if
condition|(
name|u
operator|->
name|port_text
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|port
operator|=
name|ngx_atoi
argument_list|(
name|url
operator|->
name|data
argument_list|,
name|url
operator|->
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|port
operator|==
name|NGX_ERROR
condition|)
block|{
name|u
operator|->
name|default_port
operator|=
literal|1
expr_stmt|;
name|u
operator|->
name|host
operator|.
name|len
operator|=
name|url
operator|->
name|len
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|u
operator|->
name|port_text
operator|=
operator|*
name|url
expr_stmt|;
name|u
operator|->
name|wildcard
operator|=
literal|1
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|u
operator|->
name|port_text
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|u
operator|->
name|default_port
operator|=
literal|1
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|port
operator|=
name|ngx_atoi
argument_list|(
name|u
operator|->
name|port_text
operator|.
name|data
argument_list|,
name|u
operator|->
name|port_text
operator|.
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|port
operator|==
name|NGX_ERROR
operator|||
name|port
argument_list|<
literal|1
operator|||
name|port
argument_list|>
literal|65536
condition|)
block|{
return|return
literal|"invalid port"
return|;
block|}
block|}
name|u
operator|->
name|port
operator|=
operator|(
name|in_port_t
operator|)
name|port
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

