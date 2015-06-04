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

begin_include
include|#
directive|include
file|<ngx_stream.h>
end_include

begin_function_decl
specifier|static
name|u_char
modifier|*
name|ngx_stream_log_error
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_stream_init_session
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_STREAM_SSL
operator|)
end_if

begin_function_decl
specifier|static
name|void
name|ngx_stream_ssl_init_connection
parameter_list|(
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_stream_ssl_handshake_handler
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|ngx_stream_init_connection (ngx_connection_t * c)
name|ngx_stream_init_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
name|u_char
name|text
index|[
name|NGX_SOCKADDR_STRLEN
index|]
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|struct
name|sockaddr
modifier|*
name|sa
decl_stmt|;
name|ngx_stream_port_t
modifier|*
name|port
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
name|ngx_stream_in_addr_t
modifier|*
name|addr
decl_stmt|;
name|ngx_stream_session_t
modifier|*
name|s
decl_stmt|;
name|ngx_stream_addr_conf_t
modifier|*
name|addr_conf
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
name|struct
name|sockaddr_in6
modifier|*
name|sin6
decl_stmt|;
name|ngx_stream_in6_addr_t
modifier|*
name|addr6
decl_stmt|;
endif|#
directive|endif
name|ngx_stream_core_srv_conf_t
modifier|*
name|cscf
decl_stmt|;
name|ngx_stream_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
comment|/* find the server configuration for the address:port */
name|port
operator|=
name|c
operator|->
name|listening
operator|->
name|servers
expr_stmt|;
if|if
condition|(
name|port
operator|->
name|naddrs
operator|>
literal|1
condition|)
block|{
comment|/*          * There are several addresses on this port and one of them          * is the "*:port" wildcard so getsockname() is needed to determine          * the server address.          *          * AcceptEx() already gave this address.          */
if|if
condition|(
name|ngx_connection_local_sockaddr
argument_list|(
name|c
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
name|ngx_stream_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|sa
operator|=
name|c
operator|->
name|local_sockaddr
expr_stmt|;
switch|switch
condition|(
name|sa
operator|->
name|sa_family
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
case|case
name|AF_INET6
case|:
name|sin6
operator|=
operator|(
expr|struct
name|sockaddr_in6
operator|*
operator|)
name|sa
expr_stmt|;
name|addr6
operator|=
name|port
operator|->
name|addrs
expr_stmt|;
comment|/* the last address is "*" */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|port
operator|->
name|naddrs
operator|-
literal|1
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_memcmp
argument_list|(
operator|&
name|addr6
index|[
name|i
index|]
operator|.
name|addr6
argument_list|,
operator|&
name|sin6
operator|->
name|sin6_addr
argument_list|,
literal|16
argument_list|)
operator|==
literal|0
condition|)
block|{
break|break;
block|}
block|}
name|addr_conf
operator|=
operator|&
name|addr6
index|[
name|i
index|]
operator|.
name|conf
expr_stmt|;
break|break;
endif|#
directive|endif
default|default:
comment|/* AF_INET */
name|sin
operator|=
operator|(
expr|struct
name|sockaddr_in
operator|*
operator|)
name|sa
expr_stmt|;
name|addr
operator|=
name|port
operator|->
name|addrs
expr_stmt|;
comment|/* the last address is "*" */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|port
operator|->
name|naddrs
operator|-
literal|1
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|addr
index|[
name|i
index|]
operator|.
name|addr
operator|==
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
condition|)
block|{
break|break;
block|}
block|}
name|addr_conf
operator|=
operator|&
name|addr
index|[
name|i
index|]
operator|.
name|conf
expr_stmt|;
break|break;
block|}
block|}
else|else
block|{
switch|switch
condition|(
name|c
operator|->
name|local_sockaddr
operator|->
name|sa_family
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
case|case
name|AF_INET6
case|:
name|addr6
operator|=
name|port
operator|->
name|addrs
expr_stmt|;
name|addr_conf
operator|=
operator|&
name|addr6
index|[
literal|0
index|]
operator|.
name|conf
expr_stmt|;
break|break;
endif|#
directive|endif
default|default:
comment|/* AF_INET */
name|addr
operator|=
name|port
operator|->
name|addrs
expr_stmt|;
name|addr_conf
operator|=
operator|&
name|addr
index|[
literal|0
index|]
operator|.
name|conf
expr_stmt|;
break|break;
block|}
block|}
name|s
operator|=
name|ngx_pcalloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_session_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|==
name|NULL
condition|)
block|{
name|ngx_stream_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|s
operator|->
name|signature
operator|=
name|NGX_STREAM_MODULE
expr_stmt|;
name|s
operator|->
name|main_conf
operator|=
name|addr_conf
operator|->
name|ctx
operator|->
name|main_conf
expr_stmt|;
name|s
operator|->
name|srv_conf
operator|=
name|addr_conf
operator|->
name|ctx
operator|->
name|srv_conf
expr_stmt|;
name|s
operator|->
name|connection
operator|=
name|c
expr_stmt|;
name|c
operator|->
name|data
operator|=
name|s
expr_stmt|;
name|cscf
operator|=
name|ngx_stream_get_module_srv_conf
argument_list|(
name|s
argument_list|,
name|ngx_stream_core_module
argument_list|)
expr_stmt|;
name|ngx_set_connection_log
argument_list|(
name|c
argument_list|,
name|cscf
operator|->
name|error_log
argument_list|)
expr_stmt|;
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
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"*%uA client %*s connected to %V"
argument_list|,
name|c
operator|->
name|number
argument_list|,
name|len
argument_list|,
name|text
argument_list|,
operator|&
name|addr_conf
operator|->
name|addr_text
argument_list|)
expr_stmt|;
name|c
operator|->
name|log
operator|->
name|connection
operator|=
name|c
operator|->
name|number
expr_stmt|;
name|c
operator|->
name|log
operator|->
name|handler
operator|=
name|ngx_stream_log_error
expr_stmt|;
name|c
operator|->
name|log
operator|->
name|data
operator|=
name|s
expr_stmt|;
name|c
operator|->
name|log
operator|->
name|action
operator|=
literal|"initializing connection"
expr_stmt|;
name|c
operator|->
name|log_error
operator|=
name|NGX_ERROR_INFO
expr_stmt|;
name|cmcf
operator|=
name|ngx_stream_get_module_main_conf
argument_list|(
name|s
argument_list|,
name|ngx_stream_core_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|cmcf
operator|->
name|access_handler
condition|)
block|{
name|rc
operator|=
name|cmcf
operator|->
name|access_handler
argument_list|(
name|s
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
operator|&&
name|rc
operator|!=
name|NGX_DECLINED
condition|)
block|{
name|ngx_stream_close_connection
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
name|NGX_STREAM_SSL
operator|)
block|{
name|ngx_stream_ssl_conf_t
modifier|*
name|sslcf
decl_stmt|;
name|sslcf
operator|=
name|ngx_stream_get_module_srv_conf
argument_list|(
name|s
argument_list|,
name|ngx_stream_ssl_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|addr_conf
operator|->
name|ssl
condition|)
block|{
name|c
operator|->
name|log
operator|->
name|action
operator|=
literal|"SSL handshaking"
expr_stmt|;
if|if
condition|(
name|sslcf
operator|->
name|ssl
operator|.
name|ctx
operator|==
name|NULL
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no \"ssl_certificate\" is defined "
literal|"in server listening on SSL port"
argument_list|)
expr_stmt|;
name|ngx_stream_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|ngx_stream_ssl_init_connection
argument_list|(
operator|&
name|sslcf
operator|->
name|ssl
argument_list|,
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
endif|#
directive|endif
name|ngx_stream_init_session
argument_list|(
name|c
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_stream_init_session (ngx_connection_t * c)
name|ngx_stream_init_session
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
name|ngx_stream_session_t
modifier|*
name|s
decl_stmt|;
name|ngx_stream_core_srv_conf_t
modifier|*
name|cscf
decl_stmt|;
name|s
operator|=
name|c
operator|->
name|data
expr_stmt|;
name|c
operator|->
name|log
operator|->
name|action
operator|=
literal|"handling client connection"
expr_stmt|;
name|cscf
operator|=
name|ngx_stream_get_module_srv_conf
argument_list|(
name|s
argument_list|,
name|ngx_stream_core_module
argument_list|)
expr_stmt|;
name|s
operator|->
name|ctx
operator|=
name|ngx_pcalloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|void
operator|*
argument_list|)
operator|*
name|ngx_stream_max_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|->
name|ctx
operator|==
name|NULL
condition|)
block|{
name|ngx_stream_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
name|cscf
operator|->
name|handler
argument_list|(
name|s
argument_list|)
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_STREAM_SSL
operator|)
end_if

begin_function
specifier|static
name|void
DECL|function|ngx_stream_ssl_init_connection (ngx_ssl_t * ssl,ngx_connection_t * c)
name|ngx_stream_ssl_init_connection
parameter_list|(
name|ngx_ssl_t
modifier|*
name|ssl
parameter_list|,
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
name|ngx_stream_session_t
modifier|*
name|s
decl_stmt|;
name|ngx_stream_ssl_conf_t
modifier|*
name|sslcf
decl_stmt|;
if|if
condition|(
name|ngx_ssl_create_connection
argument_list|(
name|ssl
argument_list|,
name|c
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_stream_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|ngx_ssl_handshake
argument_list|(
name|c
argument_list|)
operator|==
name|NGX_AGAIN
condition|)
block|{
name|s
operator|=
name|c
operator|->
name|data
expr_stmt|;
name|sslcf
operator|=
name|ngx_stream_get_module_srv_conf
argument_list|(
name|s
argument_list|,
name|ngx_stream_ssl_module
argument_list|)
expr_stmt|;
name|ngx_add_timer
argument_list|(
name|c
operator|->
name|read
argument_list|,
name|sslcf
operator|->
name|handshake_timeout
argument_list|)
expr_stmt|;
name|c
operator|->
name|ssl
operator|->
name|handler
operator|=
name|ngx_stream_ssl_handshake_handler
expr_stmt|;
return|return;
block|}
name|ngx_stream_ssl_handshake_handler
argument_list|(
name|c
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_stream_ssl_handshake_handler (ngx_connection_t * c)
name|ngx_stream_ssl_handshake_handler
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
if|if
condition|(
operator|!
name|c
operator|->
name|ssl
operator|->
name|handshaked
condition|)
block|{
name|ngx_stream_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|c
operator|->
name|read
operator|->
name|timer_set
condition|)
block|{
name|ngx_del_timer
argument_list|(
name|c
operator|->
name|read
argument_list|)
expr_stmt|;
block|}
name|ngx_stream_init_session
argument_list|(
name|c
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|ngx_stream_close_connection (ngx_connection_t * c)
name|ngx_stream_close_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_STREAM
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"close stream connection: %d"
argument_list|,
name|c
operator|->
name|fd
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_STREAM_SSL
operator|)
if|if
condition|(
name|c
operator|->
name|ssl
condition|)
block|{
if|if
condition|(
name|ngx_ssl_shutdown
argument_list|(
name|c
argument_list|)
operator|==
name|NGX_AGAIN
condition|)
block|{
name|c
operator|->
name|ssl
operator|->
name|handler
operator|=
name|ngx_stream_close_connection
expr_stmt|;
return|return;
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
name|ngx_stat_active
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|pool
operator|=
name|c
operator|->
name|pool
expr_stmt|;
name|ngx_close_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
name|ngx_destroy_pool
argument_list|(
name|pool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|u_char
modifier|*
DECL|function|ngx_stream_log_error (ngx_log_t * log,u_char * buf,size_t len)
name|ngx_stream_log_error
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
name|ngx_stream_session_t
modifier|*
name|s
decl_stmt|;
if|if
condition|(
name|log
operator|->
name|action
condition|)
block|{
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|buf
argument_list|,
name|len
argument_list|,
literal|" while %s"
argument_list|,
name|log
operator|->
name|action
argument_list|)
expr_stmt|;
name|len
operator|-=
name|p
operator|-
name|buf
expr_stmt|;
name|buf
operator|=
name|p
expr_stmt|;
block|}
name|s
operator|=
name|log
operator|->
name|data
expr_stmt|;
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|buf
argument_list|,
name|len
argument_list|,
literal|", client: %V, server: %V"
argument_list|,
operator|&
name|s
operator|->
name|connection
operator|->
name|addr_text
argument_list|,
operator|&
name|s
operator|->
name|connection
operator|->
name|listening
operator|->
name|addr_text
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|->
name|log_handler
condition|)
block|{
return|return
name|s
operator|->
name|log_handler
argument_list|(
name|log
argument_list|,
name|p
argument_list|,
name|len
argument_list|)
return|;
block|}
return|return
name|p
return|;
block|}
end_function

end_unit

