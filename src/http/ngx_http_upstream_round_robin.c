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
file|<ngx_http.h>
end_include

begin_function_decl
specifier|static
name|int
name|ngx_http_upstream_cmp_servers
parameter_list|(
specifier|const
name|void
modifier|*
name|one
parameter_list|,
specifier|const
name|void
modifier|*
name|two
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_uint_t
name|ngx_http_upstream_get_peer
parameter_list|(
name|ngx_http_upstream_rr_peers_t
modifier|*
name|peers
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|ngx_int_t
DECL|function|ngx_http_upstream_init_round_robin (ngx_conf_t * cf,ngx_http_upstream_srv_conf_t * us)
name|ngx_http_upstream_init_round_robin
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_http_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
block|{
name|ngx_url_t
name|u
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|j
decl_stmt|,
name|n
decl_stmt|;
name|ngx_http_upstream_server_t
modifier|*
name|server
decl_stmt|;
name|ngx_http_upstream_rr_peers_t
modifier|*
name|peers
decl_stmt|,
modifier|*
name|backup
decl_stmt|;
name|us
operator|->
name|peer
operator|.
name|init
operator|=
name|ngx_http_upstream_init_round_robin_peer
expr_stmt|;
if|if
condition|(
name|us
operator|->
name|servers
condition|)
block|{
name|server
operator|=
name|us
operator|->
name|servers
operator|->
name|elts
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|us
operator|->
name|servers
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|server
index|[
name|i
index|]
operator|.
name|backup
condition|)
block|{
continue|continue;
block|}
name|n
operator|+=
name|server
index|[
name|i
index|]
operator|.
name|naddrs
expr_stmt|;
block|}
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
name|ngx_http_upstream_rr_peers_t
argument_list|)
operator|+
sizeof|sizeof
argument_list|(
name|ngx_http_upstream_rr_peer_t
argument_list|)
operator|*
operator|(
name|n
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
name|NGX_ERROR
return|;
block|}
name|peers
operator|->
name|single
operator|=
operator|(
name|n
operator|==
literal|1
operator|)
expr_stmt|;
name|peers
operator|->
name|number
operator|=
name|n
expr_stmt|;
name|peers
operator|->
name|name
operator|=
operator|&
name|us
operator|->
name|host
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|us
operator|->
name|servers
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|server
index|[
name|i
index|]
operator|.
name|naddrs
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|server
index|[
name|i
index|]
operator|.
name|backup
condition|)
block|{
continue|continue;
block|}
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|sockaddr
operator|=
name|server
index|[
name|i
index|]
operator|.
name|addrs
index|[
name|j
index|]
operator|.
name|sockaddr
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|socklen
operator|=
name|server
index|[
name|i
index|]
operator|.
name|addrs
index|[
name|j
index|]
operator|.
name|socklen
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|name
operator|=
name|server
index|[
name|i
index|]
operator|.
name|addrs
index|[
name|j
index|]
operator|.
name|name
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|max_fails
operator|=
name|server
index|[
name|i
index|]
operator|.
name|max_fails
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|fail_timeout
operator|=
name|server
index|[
name|i
index|]
operator|.
name|fail_timeout
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|down
operator|=
name|server
index|[
name|i
index|]
operator|.
name|down
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|weight
operator|=
name|server
index|[
name|i
index|]
operator|.
name|down
condition|?
literal|0
else|:
name|server
index|[
name|i
index|]
operator|.
name|weight
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|current_weight
operator|=
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|weight
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
block|}
name|us
operator|->
name|peer
operator|.
name|data
operator|=
name|peers
expr_stmt|;
name|ngx_sort
argument_list|(
operator|&
name|peers
operator|->
name|peer
index|[
literal|0
index|]
argument_list|,
operator|(
name|size_t
operator|)
name|n
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_upstream_rr_peer_t
argument_list|)
argument_list|,
name|ngx_http_upstream_cmp_servers
argument_list|)
expr_stmt|;
comment|/* backup servers */
name|n
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|us
operator|->
name|servers
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|server
index|[
name|i
index|]
operator|.
name|backup
condition|)
block|{
continue|continue;
block|}
name|n
operator|+=
name|server
index|[
name|i
index|]
operator|.
name|naddrs
expr_stmt|;
block|}
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|backup
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_upstream_rr_peers_t
argument_list|)
operator|+
sizeof|sizeof
argument_list|(
name|ngx_http_upstream_rr_peer_t
argument_list|)
operator|*
operator|(
name|n
operator|-
literal|1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|backup
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|peers
operator|->
name|single
operator|=
literal|0
expr_stmt|;
name|backup
operator|->
name|single
operator|=
literal|0
expr_stmt|;
name|backup
operator|->
name|number
operator|=
name|n
expr_stmt|;
name|backup
operator|->
name|name
operator|=
operator|&
name|us
operator|->
name|host
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|us
operator|->
name|servers
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|server
index|[
name|i
index|]
operator|.
name|naddrs
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
operator|!
name|server
index|[
name|i
index|]
operator|.
name|backup
condition|)
block|{
continue|continue;
block|}
name|backup
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|sockaddr
operator|=
name|server
index|[
name|i
index|]
operator|.
name|addrs
index|[
name|j
index|]
operator|.
name|sockaddr
expr_stmt|;
name|backup
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|socklen
operator|=
name|server
index|[
name|i
index|]
operator|.
name|addrs
index|[
name|j
index|]
operator|.
name|socklen
expr_stmt|;
name|backup
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|name
operator|=
name|server
index|[
name|i
index|]
operator|.
name|addrs
index|[
name|j
index|]
operator|.
name|name
expr_stmt|;
name|backup
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|weight
operator|=
name|server
index|[
name|i
index|]
operator|.
name|weight
expr_stmt|;
name|backup
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|current_weight
operator|=
name|server
index|[
name|i
index|]
operator|.
name|weight
expr_stmt|;
name|backup
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|max_fails
operator|=
name|server
index|[
name|i
index|]
operator|.
name|max_fails
expr_stmt|;
name|backup
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|fail_timeout
operator|=
name|server
index|[
name|i
index|]
operator|.
name|fail_timeout
expr_stmt|;
name|backup
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|down
operator|=
name|server
index|[
name|i
index|]
operator|.
name|down
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
block|}
name|peers
operator|->
name|next
operator|=
name|backup
expr_stmt|;
name|ngx_sort
argument_list|(
operator|&
name|backup
operator|->
name|peer
index|[
literal|0
index|]
argument_list|,
operator|(
name|size_t
operator|)
name|n
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_upstream_rr_peer_t
argument_list|)
argument_list|,
name|ngx_http_upstream_cmp_servers
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
comment|/* an upstream implicitly defined by proxy_pass, etc. */
if|if
condition|(
name|us
operator|->
name|port
operator|==
literal|0
operator|&&
name|us
operator|->
name|default_port
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no port in upstream \"%V\" in %s:%ui"
argument_list|,
operator|&
name|us
operator|->
name|host
argument_list|,
name|us
operator|->
name|file_name
argument_list|,
name|us
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_memzero
argument_list|(
operator|&
name|u
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_url_t
argument_list|)
argument_list|)
expr_stmt|;
name|u
operator|.
name|host
operator|=
name|us
operator|->
name|host
expr_stmt|;
name|u
operator|.
name|port
operator|=
operator|(
name|in_port_t
operator|)
operator|(
name|us
operator|->
name|port
condition|?
name|us
operator|->
name|port
else|:
name|us
operator|->
name|default_port
operator|)
expr_stmt|;
if|if
condition|(
name|ngx_inet_resolve_host
argument_list|(
name|cf
argument_list|,
operator|&
name|u
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
if|if
condition|(
name|u
operator|.
name|err
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"%s in upstream \"%V\" in %s:%ui"
argument_list|,
name|u
operator|.
name|err
argument_list|,
operator|&
name|us
operator|->
name|host
argument_list|,
name|us
operator|->
name|file_name
argument_list|,
name|us
operator|->
name|line
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
name|n
operator|=
name|u
operator|.
name|naddrs
expr_stmt|;
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
name|ngx_http_upstream_rr_peers_t
argument_list|)
operator|+
sizeof|sizeof
argument_list|(
name|ngx_http_upstream_rr_peer_t
argument_list|)
operator|*
operator|(
name|n
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
name|NGX_ERROR
return|;
block|}
name|peers
operator|->
name|single
operator|=
operator|(
name|n
operator|==
literal|1
operator|)
expr_stmt|;
name|peers
operator|->
name|number
operator|=
name|n
expr_stmt|;
name|peers
operator|->
name|name
operator|=
operator|&
name|us
operator|->
name|host
expr_stmt|;
name|n
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|u
operator|.
name|naddrs
condition|;
name|i
operator|++
control|)
block|{
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|sockaddr
operator|=
name|u
operator|.
name|addrs
index|[
name|i
index|]
operator|.
name|sockaddr
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|socklen
operator|=
name|u
operator|.
name|addrs
index|[
name|i
index|]
operator|.
name|socklen
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|name
operator|=
name|u
operator|.
name|addrs
index|[
name|i
index|]
operator|.
name|name
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|weight
operator|=
literal|1
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|current_weight
operator|=
literal|1
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|max_fails
operator|=
literal|1
expr_stmt|;
name|peers
operator|->
name|peer
index|[
name|n
index|]
operator|.
name|fail_timeout
operator|=
literal|10
expr_stmt|;
name|n
operator|++
expr_stmt|;
block|}
name|us
operator|->
name|peer
operator|.
name|data
operator|=
name|peers
expr_stmt|;
comment|/* implicitly defined upstream has no backup servers */
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|int
DECL|function|ngx_http_upstream_cmp_servers (const void * one,const void * two)
name|ngx_http_upstream_cmp_servers
parameter_list|(
specifier|const
name|void
modifier|*
name|one
parameter_list|,
specifier|const
name|void
modifier|*
name|two
parameter_list|)
block|{
name|ngx_http_upstream_rr_peer_t
modifier|*
name|first
decl_stmt|,
modifier|*
name|second
decl_stmt|;
name|first
operator|=
operator|(
name|ngx_http_upstream_rr_peer_t
operator|*
operator|)
name|one
expr_stmt|;
name|second
operator|=
operator|(
name|ngx_http_upstream_rr_peer_t
operator|*
operator|)
name|two
expr_stmt|;
return|return
operator|(
name|first
operator|->
name|weight
operator|<
name|second
operator|->
name|weight
operator|)
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_http_upstream_init_round_robin_peer (ngx_http_request_t * r,ngx_http_upstream_srv_conf_t * us)
name|ngx_http_upstream_init_round_robin_peer
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
block|{
name|ngx_uint_t
name|n
decl_stmt|;
name|ngx_http_upstream_rr_peer_data_t
modifier|*
name|rrp
decl_stmt|;
name|rrp
operator|=
name|r
operator|->
name|upstream
operator|->
name|peer
operator|.
name|data
expr_stmt|;
if|if
condition|(
name|rrp
operator|==
name|NULL
condition|)
block|{
name|rrp
operator|=
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_upstream_rr_peer_data_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rrp
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|r
operator|->
name|upstream
operator|->
name|peer
operator|.
name|data
operator|=
name|rrp
expr_stmt|;
block|}
name|rrp
operator|->
name|peers
operator|=
name|us
operator|->
name|peer
operator|.
name|data
expr_stmt|;
name|rrp
operator|->
name|current
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|rrp
operator|->
name|peers
operator|->
name|number
operator|<=
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
condition|)
block|{
name|rrp
operator|->
name|tried
operator|=
operator|&
name|rrp
operator|->
name|data
expr_stmt|;
name|rrp
operator|->
name|data
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|n
operator|=
operator|(
name|rrp
operator|->
name|peers
operator|->
name|number
operator|+
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|-
literal|1
operator|)
operator|)
operator|/
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
name|rrp
operator|->
name|tried
operator|=
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|n
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rrp
operator|->
name|tried
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
name|r
operator|->
name|upstream
operator|->
name|peer
operator|.
name|get
operator|=
name|ngx_http_upstream_get_round_robin_peer
expr_stmt|;
name|r
operator|->
name|upstream
operator|->
name|peer
operator|.
name|free
operator|=
name|ngx_http_upstream_free_round_robin_peer
expr_stmt|;
name|r
operator|->
name|upstream
operator|->
name|peer
operator|.
name|tries
operator|=
name|rrp
operator|->
name|peers
operator|->
name|number
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
operator|)
name|r
operator|->
name|upstream
operator|->
name|peer
operator|.
name|set_session
operator|=
name|ngx_http_upstream_set_round_robin_peer_session
expr_stmt|;
name|r
operator|->
name|upstream
operator|->
name|peer
operator|.
name|save_session
operator|=
name|ngx_http_upstream_save_round_robin_peer_session
expr_stmt|;
endif|#
directive|endif
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_http_upstream_get_round_robin_peer (ngx_peer_connection_t * pc,void * data)
name|ngx_http_upstream_get_round_robin_peer
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
name|ngx_http_upstream_rr_peer_data_t
modifier|*
name|rrp
init|=
name|data
decl_stmt|;
name|time_t
name|now
decl_stmt|;
name|uintptr_t
name|m
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_http_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|;
name|ngx_http_upstream_rr_peers_t
modifier|*
name|peers
decl_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"get rr peer, try: %ui"
argument_list|,
name|pc
operator|->
name|tries
argument_list|)
expr_stmt|;
name|now
operator|=
name|ngx_time
argument_list|()
expr_stmt|;
comment|/* ngx_lock_mutex(rrp->peers->mutex); */
if|if
condition|(
name|rrp
operator|->
name|peers
operator|->
name|last_cached
condition|)
block|{
comment|/* cached connection */
name|c
operator|=
name|rrp
operator|->
name|peers
operator|->
name|cached
index|[
name|rrp
operator|->
name|peers
operator|->
name|last_cached
index|]
expr_stmt|;
name|rrp
operator|->
name|peers
operator|->
name|last_cached
operator|--
expr_stmt|;
comment|/* ngx_unlock_mutex(ppr->peers->mutex); */
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
name|c
operator|->
name|read
operator|->
name|lock
operator|=
name|c
operator|->
name|read
operator|->
name|own_lock
expr_stmt|;
name|c
operator|->
name|write
operator|->
name|lock
operator|=
name|c
operator|->
name|write
operator|->
name|own_lock
expr_stmt|;
endif|#
directive|endif
name|pc
operator|->
name|connection
operator|=
name|c
expr_stmt|;
name|pc
operator|->
name|cached
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|pc
operator|->
name|cached
operator|=
literal|0
expr_stmt|;
name|pc
operator|->
name|connection
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|rrp
operator|->
name|peers
operator|->
name|single
condition|)
block|{
name|peer
operator|=
operator|&
name|rrp
operator|->
name|peers
operator|->
name|peer
index|[
literal|0
index|]
expr_stmt|;
block|}
else|else
block|{
comment|/* there are several peers */
if|if
condition|(
name|pc
operator|->
name|tries
operator|==
name|rrp
operator|->
name|peers
operator|->
name|number
condition|)
block|{
comment|/* it's a first try - get a current peer */
name|i
operator|=
name|pc
operator|->
name|tries
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|rrp
operator|->
name|current
operator|=
name|ngx_http_upstream_get_peer
argument_list|(
name|rrp
operator|->
name|peers
argument_list|)
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"get rr peer, current: %ui %i"
argument_list|,
name|rrp
operator|->
name|current
argument_list|,
name|rrp
operator|->
name|peers
operator|->
name|peer
index|[
name|rrp
operator|->
name|current
index|]
operator|.
name|current_weight
argument_list|)
expr_stmt|;
name|n
operator|=
name|rrp
operator|->
name|current
operator|/
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
name|m
operator|=
operator|(
name|uintptr_t
operator|)
literal|1
operator|<<
name|rrp
operator|->
name|current
operator|%
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|rrp
operator|->
name|tried
index|[
name|n
index|]
operator|&
name|m
operator|)
condition|)
block|{
name|peer
operator|=
operator|&
name|rrp
operator|->
name|peers
operator|->
name|peer
index|[
name|rrp
operator|->
name|current
index|]
expr_stmt|;
if|if
condition|(
operator|!
name|peer
operator|->
name|down
condition|)
block|{
if|if
condition|(
name|peer
operator|->
name|max_fails
operator|==
literal|0
operator|||
name|peer
operator|->
name|fails
operator|<
name|peer
operator|->
name|max_fails
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|now
operator|-
name|peer
operator|->
name|accessed
operator|>
name|peer
operator|->
name|fail_timeout
condition|)
block|{
name|peer
operator|->
name|fails
operator|=
literal|0
expr_stmt|;
break|break;
block|}
name|peer
operator|->
name|current_weight
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|rrp
operator|->
name|tried
index|[
name|n
index|]
operator||=
name|m
expr_stmt|;
block|}
name|pc
operator|->
name|tries
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|pc
operator|->
name|tries
operator|==
literal|0
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
if|if
condition|(
operator|--
name|i
operator|==
literal|0
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
literal|0
argument_list|,
literal|"round robin upstream stuck on %ui tries"
argument_list|,
name|pc
operator|->
name|tries
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
block|}
name|peer
operator|->
name|current_weight
operator|--
expr_stmt|;
block|}
else|else
block|{
name|i
operator|=
name|pc
operator|->
name|tries
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|n
operator|=
name|rrp
operator|->
name|current
operator|/
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
name|m
operator|=
operator|(
name|uintptr_t
operator|)
literal|1
operator|<<
name|rrp
operator|->
name|current
operator|%
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|rrp
operator|->
name|tried
index|[
name|n
index|]
operator|&
name|m
operator|)
condition|)
block|{
name|peer
operator|=
operator|&
name|rrp
operator|->
name|peers
operator|->
name|peer
index|[
name|rrp
operator|->
name|current
index|]
expr_stmt|;
if|if
condition|(
operator|!
name|peer
operator|->
name|down
condition|)
block|{
if|if
condition|(
name|peer
operator|->
name|max_fails
operator|==
literal|0
operator|||
name|peer
operator|->
name|fails
operator|<
name|peer
operator|->
name|max_fails
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|now
operator|-
name|peer
operator|->
name|accessed
operator|>
name|peer
operator|->
name|fail_timeout
condition|)
block|{
name|peer
operator|->
name|fails
operator|=
literal|0
expr_stmt|;
break|break;
block|}
name|peer
operator|->
name|current_weight
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|rrp
operator|->
name|tried
index|[
name|n
index|]
operator||=
name|m
expr_stmt|;
block|}
name|pc
operator|->
name|tries
operator|--
expr_stmt|;
block|}
name|rrp
operator|->
name|current
operator|++
expr_stmt|;
if|if
condition|(
name|rrp
operator|->
name|current
operator|>=
name|rrp
operator|->
name|peers
operator|->
name|number
condition|)
block|{
name|rrp
operator|->
name|current
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|pc
operator|->
name|tries
operator|==
literal|0
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
if|if
condition|(
operator|--
name|i
operator|==
literal|0
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
literal|0
argument_list|,
literal|"round robin upstream stuck on %ui tries"
argument_list|,
name|pc
operator|->
name|tries
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
block|}
name|peer
operator|->
name|current_weight
operator|--
expr_stmt|;
block|}
name|rrp
operator|->
name|tried
index|[
name|n
index|]
operator||=
name|m
expr_stmt|;
block|}
name|pc
operator|->
name|sockaddr
operator|=
name|peer
operator|->
name|sockaddr
expr_stmt|;
name|pc
operator|->
name|socklen
operator|=
name|peer
operator|->
name|socklen
expr_stmt|;
name|pc
operator|->
name|name
operator|=
operator|&
name|peer
operator|->
name|name
expr_stmt|;
comment|/* ngx_unlock_mutex(rrp->peers->mutex); */
if|if
condition|(
name|pc
operator|->
name|tries
operator|==
literal|1
operator|&&
name|rrp
operator|->
name|peers
operator|->
name|next
condition|)
block|{
name|pc
operator|->
name|tries
operator|+=
name|rrp
operator|->
name|peers
operator|->
name|next
operator|->
name|number
expr_stmt|;
name|n
operator|=
name|rrp
operator|->
name|peers
operator|->
name|next
operator|->
name|number
operator|/
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
operator|+
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
block|{
name|rrp
operator|->
name|tried
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
block|}
block|}
return|return
name|NGX_OK
return|;
name|failed
label|:
name|peers
operator|=
name|rrp
operator|->
name|peers
expr_stmt|;
if|if
condition|(
name|peers
operator|->
name|next
condition|)
block|{
comment|/* ngx_unlock_mutex(peers->mutex); */
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"backup servers"
argument_list|)
expr_stmt|;
name|rrp
operator|->
name|peers
operator|=
name|peers
operator|->
name|next
expr_stmt|;
name|pc
operator|->
name|tries
operator|=
name|rrp
operator|->
name|peers
operator|->
name|number
expr_stmt|;
name|n
operator|=
name|rrp
operator|->
name|peers
operator|->
name|number
operator|/
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
operator|+
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
block|{
name|rrp
operator|->
name|tried
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
block|}
name|rc
operator|=
name|ngx_http_upstream_get_round_robin_peer
argument_list|(
name|pc
argument_list|,
name|rrp
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_BUSY
condition|)
block|{
return|return
name|rc
return|;
block|}
comment|/* ngx_lock_mutex(peers->mutex); */
block|}
comment|/* all peers failed, mark them as live for quick recovery */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|peers
operator|->
name|number
condition|;
name|i
operator|++
control|)
block|{
name|peers
operator|->
name|peer
index|[
name|i
index|]
operator|.
name|fails
operator|=
literal|0
expr_stmt|;
block|}
comment|/* ngx_unlock_mutex(peers->mutex); */
name|pc
operator|->
name|name
operator|=
name|peers
operator|->
name|name
expr_stmt|;
return|return
name|NGX_BUSY
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_uint_t
DECL|function|ngx_http_upstream_get_peer (ngx_http_upstream_rr_peers_t * peers)
name|ngx_http_upstream_get_peer
parameter_list|(
name|ngx_http_upstream_rr_peers_t
modifier|*
name|peers
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_http_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|;
name|peer
operator|=
operator|&
name|peers
operator|->
name|peer
index|[
literal|0
index|]
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|peers
operator|->
name|number
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|peer
index|[
name|i
index|]
operator|.
name|current_weight
operator|<=
literal|0
condition|)
block|{
continue|continue;
block|}
name|n
operator|=
name|i
expr_stmt|;
while|while
condition|(
name|i
operator|<
name|peers
operator|->
name|number
operator|-
literal|1
condition|)
block|{
name|i
operator|++
expr_stmt|;
if|if
condition|(
name|peer
index|[
name|i
index|]
operator|.
name|current_weight
operator|<=
literal|0
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|peer
index|[
name|n
index|]
operator|.
name|current_weight
operator|*
literal|1000
operator|/
name|peer
index|[
name|i
index|]
operator|.
name|current_weight
operator|>
name|peer
index|[
name|n
index|]
operator|.
name|weight
operator|*
literal|1000
operator|/
name|peer
index|[
name|i
index|]
operator|.
name|weight
condition|)
block|{
return|return
name|n
return|;
block|}
name|n
operator|=
name|i
expr_stmt|;
block|}
if|if
condition|(
name|peer
index|[
name|i
index|]
operator|.
name|current_weight
operator|>
literal|0
condition|)
block|{
name|n
operator|=
name|i
expr_stmt|;
block|}
return|return
name|n
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|peers
operator|->
name|number
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|peer
operator|->
name|max_fails
operator|==
literal|0
operator|||
name|peer
operator|->
name|fails
operator|<
name|peer
operator|->
name|max_fails
condition|)
block|{
name|peer
index|[
name|i
index|]
operator|.
name|current_weight
operator|+=
name|peer
index|[
name|i
index|]
operator|.
name|weight
expr_stmt|;
block|}
else|else
block|{
comment|/* 1 allows to go to quick recovery when all peers failed */
name|peer
index|[
name|i
index|]
operator|.
name|current_weight
operator|=
literal|1
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
name|void
DECL|function|ngx_http_upstream_free_round_robin_peer (ngx_peer_connection_t * pc,void * data,ngx_uint_t state)
name|ngx_http_upstream_free_round_robin_peer
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
block|{
name|ngx_http_upstream_rr_peer_data_t
modifier|*
name|rrp
init|=
name|data
decl_stmt|;
name|time_t
name|now
decl_stmt|;
name|ngx_http_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"free rr peer %ui %ui"
argument_list|,
name|pc
operator|->
name|tries
argument_list|,
name|state
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|==
literal|0
operator|&&
name|pc
operator|->
name|tries
operator|==
literal|0
condition|)
block|{
return|return;
block|}
comment|/* TODO: NGX_PEER_KEEPALIVE */
if|if
condition|(
name|rrp
operator|->
name|peers
operator|->
name|single
condition|)
block|{
name|pc
operator|->
name|tries
operator|=
literal|0
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|state
operator|&
name|NGX_PEER_FAILED
condition|)
block|{
name|now
operator|=
name|ngx_time
argument_list|()
expr_stmt|;
name|peer
operator|=
operator|&
name|rrp
operator|->
name|peers
operator|->
name|peer
index|[
name|rrp
operator|->
name|current
index|]
expr_stmt|;
comment|/* ngx_lock_mutex(rrp->peers->mutex); */
name|peer
operator|->
name|fails
operator|++
expr_stmt|;
name|peer
operator|->
name|accessed
operator|=
name|now
expr_stmt|;
name|peer
operator|->
name|current_weight
operator|-=
name|peer
operator|->
name|weight
operator|/
name|peer
operator|->
name|max_fails
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"free rr peer failed: %ui %i"
argument_list|,
name|rrp
operator|->
name|current
argument_list|,
name|peer
operator|->
name|current_weight
argument_list|)
expr_stmt|;
if|if
condition|(
name|peer
operator|->
name|current_weight
operator|<
literal|0
condition|)
block|{
name|peer
operator|->
name|current_weight
operator|=
literal|0
expr_stmt|;
block|}
comment|/* ngx_unlock_mutex(rrp->peers->mutex); */
block|}
name|rrp
operator|->
name|current
operator|++
expr_stmt|;
if|if
condition|(
name|rrp
operator|->
name|current
operator|>=
name|rrp
operator|->
name|peers
operator|->
name|number
condition|)
block|{
name|rrp
operator|->
name|current
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|pc
operator|->
name|tries
condition|)
block|{
name|pc
operator|->
name|tries
operator|--
expr_stmt|;
block|}
comment|/* ngx_unlock_mutex(rrp->peers->mutex); */
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
operator|)
end_if

begin_function
name|ngx_int_t
DECL|function|ngx_http_upstream_set_round_robin_peer_session (ngx_peer_connection_t * pc,void * data)
name|ngx_http_upstream_set_round_robin_peer_session
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
name|ngx_http_upstream_rr_peer_data_t
modifier|*
name|rrp
init|=
name|data
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_ssl_session_t
modifier|*
name|ssl_session
decl_stmt|;
name|ngx_http_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|;
name|peer
operator|=
operator|&
name|rrp
operator|->
name|peers
operator|->
name|peer
index|[
name|rrp
operator|->
name|current
index|]
expr_stmt|;
comment|/* TODO: threads only mutex */
comment|/* ngx_lock_mutex(rrp->peers->mutex); */
name|ssl_session
operator|=
name|peer
operator|->
name|ssl_session
expr_stmt|;
name|rc
operator|=
name|ngx_ssl_set_session
argument_list|(
name|pc
operator|->
name|connection
argument_list|,
name|ssl_session
argument_list|)
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"set session: %p:%d"
argument_list|,
name|ssl_session
argument_list|,
name|ssl_session
condition|?
name|ssl_session
operator|->
name|references
else|:
literal|0
argument_list|)
expr_stmt|;
comment|/* ngx_unlock_mutex(rrp->peers->mutex); */
return|return
name|rc
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_http_upstream_save_round_robin_peer_session (ngx_peer_connection_t * pc,void * data)
name|ngx_http_upstream_save_round_robin_peer_session
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
name|ngx_http_upstream_rr_peer_data_t
modifier|*
name|rrp
init|=
name|data
decl_stmt|;
name|ngx_ssl_session_t
modifier|*
name|old_ssl_session
decl_stmt|,
modifier|*
name|ssl_session
decl_stmt|;
name|ngx_http_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|;
name|ssl_session
operator|=
name|ngx_ssl_get_session
argument_list|(
name|pc
operator|->
name|connection
argument_list|)
expr_stmt|;
if|if
condition|(
name|ssl_session
operator|==
name|NULL
condition|)
block|{
return|return;
block|}
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"save session: %p:%d"
argument_list|,
name|ssl_session
argument_list|,
name|ssl_session
operator|->
name|references
argument_list|)
expr_stmt|;
name|peer
operator|=
operator|&
name|rrp
operator|->
name|peers
operator|->
name|peer
index|[
name|rrp
operator|->
name|current
index|]
expr_stmt|;
comment|/* TODO: threads only mutex */
comment|/* ngx_lock_mutex(rrp->peers->mutex); */
name|old_ssl_session
operator|=
name|peer
operator|->
name|ssl_session
expr_stmt|;
name|peer
operator|->
name|ssl_session
operator|=
name|ssl_session
expr_stmt|;
comment|/* ngx_unlock_mutex(rrp->peers->mutex); */
if|if
condition|(
name|old_ssl_session
condition|)
block|{
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"old session: %p:%d"
argument_list|,
name|old_ssl_session
argument_list|,
name|old_ssl_session
operator|->
name|references
argument_list|)
expr_stmt|;
comment|/* TODO: may block */
name|ngx_ssl_free_session
argument_list|(
name|old_ssl_session
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

