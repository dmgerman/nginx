begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_decl_stmt
DECL|variable|ngx_io
name|ngx_os_io_t
name|ngx_io
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_set_inherited_sockets (ngx_cycle_t * cycle)
name|ngx_int_t
name|ngx_set_inherited_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_int_t
name|i
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|addr_in
decl_stmt|;
name|ls
operator|=
name|cycle
operator|->
name|listening
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cycle
operator|->
name|listening
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
comment|/* AF_INET only */
name|ls
index|[
name|i
index|]
operator|.
name|sockaddr
operator|=
name|ngx_palloc
argument_list|(
name|cycle
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
name|ls
index|[
name|i
index|]
operator|.
name|sockaddr
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ls
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
if|if
condition|(
name|getsockname
argument_list|(
name|ls
index|[
name|i
index|]
operator|.
name|fd
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|sockaddr
argument_list|,
operator|&
name|ls
index|[
name|i
index|]
operator|.
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
name|cycle
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"getsockname() of the inherited "
literal|"socket #%d failed"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|fd
argument_list|)
expr_stmt|;
name|ls
index|[
name|i
index|]
operator|.
name|ignore
operator|=
literal|1
expr_stmt|;
continue|continue;
block|}
name|addr_in
operator|=
operator|(
expr|struct
name|sockaddr_in
operator|*
operator|)
name|ls
index|[
name|i
index|]
operator|.
name|sockaddr
expr_stmt|;
if|if
condition|(
name|addr_in
operator|->
name|sin_family
operator|!=
name|AF_INET
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"the inherited socket #%d has "
literal|"unsupported family"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|fd
argument_list|)
expr_stmt|;
name|ls
index|[
name|i
index|]
operator|.
name|ignore
operator|=
literal|1
expr_stmt|;
continue|continue;
block|}
name|ls
index|[
name|i
index|]
operator|.
name|addr_text_max_len
operator|=
name|INET_ADDRSTRLEN
expr_stmt|;
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
operator|=
name|ngx_palloc
argument_list|(
name|cycle
operator|->
name|pool
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text_max_len
argument_list|)
expr_stmt|;
if|if
condition|(
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ls
index|[
name|i
index|]
operator|.
name|family
operator|=
name|addr_in
operator|->
name|sin_family
expr_stmt|;
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|len
operator|=
name|ngx_sock_ntop
argument_list|(
name|ls
index|[
name|i
index|]
operator|.
name|family
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|sockaddr
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text_max_len
argument_list|)
expr_stmt|;
if|if
condition|(
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|len
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_open_listening_sockets (ngx_cycle_t * cycle)
name|ngx_int_t
name|ngx_open_listening_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_int_t
name|tries
decl_stmt|,
name|failed
decl_stmt|,
name|reuseaddr
decl_stmt|,
name|i
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
name|ngx_socket_t
name|s
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
name|reuseaddr
operator|=
literal|1
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_SUPPRESS_WARN
operator|)
name|failed
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
name|log
operator|=
name|cycle
operator|->
name|log
expr_stmt|;
comment|/* TODO: tries configurable */
for|for
control|(
name|tries
operator|=
literal|10
init|;
name|tries
condition|;
name|tries
operator|--
control|)
block|{
name|failed
operator|=
literal|0
expr_stmt|;
comment|/* for each listening socket */
name|ls
operator|=
name|cycle
operator|->
name|listening
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cycle
operator|->
name|listening
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ls
index|[
name|i
index|]
operator|.
name|ignore
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|ls
index|[
name|i
index|]
operator|.
name|fd
operator|!=
operator|-
literal|1
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|ls
index|[
name|i
index|]
operator|.
name|inherited
condition|)
block|{
comment|/* TODO: close on exit */
comment|/* TODO: nonblocking */
comment|/* TODO: deferred accept */
continue|continue;
block|}
name|s
operator|=
name|ngx_socket
argument_list|(
name|ls
index|[
name|i
index|]
operator|.
name|family
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|type
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|protocol
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_socket_n
literal|" %s failed"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|#
directive|if
operator|(
name|WIN32
operator|)
comment|/*              * Winsock assignes a socket number divisible by 4              * so to find a connection we divide a socket number by 4.              */
if|if
condition|(
name|s
operator|%
literal|4
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|ls
operator|->
name|log
argument_list|,
literal|0
argument_list|,
name|ngx_socket_n
literal|" created socket %d"
argument_list|,
name|s
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
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
name|reuseaddr
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
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"setsockopt(SO_REUSEADDR) %s failed"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
comment|/* TODO: close on exit */
if|if
condition|(
operator|!
operator|(
name|ngx_event_flags
operator|&
name|NGX_USE_AIO_EVENT
operator|)
condition|)
block|{
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
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_nonblocking_n
literal|" %s failed"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
if|#
directive|if
literal|0
block_content|if (ls[i].nonblocking) {                 if (ngx_nonblocking(s) == -1) {                     ngx_log_error(NGX_LOG_EMERG, log, ngx_socket_errno,                                   ngx_nonblocking_n " %s failed",                                   ls[i].addr_text.data);                     return NGX_ERROR;                 }             }
endif|#
directive|endif
if|if
condition|(
name|bind
argument_list|(
name|s
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|sockaddr
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|socklen
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
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
literal|"bind() to %s failed"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
name|NGX_EADDRINUSE
condition|)
return|return
name|NGX_ERROR
return|;
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
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_close_socket_n
literal|" %s failed"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|)
expr_stmt|;
name|failed
operator|=
literal|1
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|listen
argument_list|(
name|s
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|backlog
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"listen() to %s failed"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
comment|/* TODO: deferred accept */
name|ls
index|[
name|i
index|]
operator|.
name|fd
operator|=
name|s
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|failed
condition|)
break|break;
comment|/* TODO: delay configurable */
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"try again to bind() after 500ms"
argument_list|)
expr_stmt|;
name|ngx_msleep
argument_list|(
literal|500
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|failed
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"still can not bind()"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_close_listening_sockets (ngx_cycle_t * cycle)
name|void
name|ngx_close_listening_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_int_t
name|i
decl_stmt|;
name|ngx_socket_t
name|fd
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_IOCP_EVENT
condition|)
block|{
return|return;
block|}
name|ls
operator|=
name|cycle
operator|->
name|listening
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cycle
operator|->
name|listening
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|fd
operator|=
name|ls
index|[
name|i
index|]
operator|.
name|fd
expr_stmt|;
if|#
directive|if
operator|(
name|WIN32
operator|)
comment|/*          * Winsock assignes a socket number divisible by 4          * so to find a connection we divide a socket number by 4.          */
name|fd
operator|/=
literal|4
expr_stmt|;
endif|#
directive|endif
name|ngx_del_event
argument_list|(
operator|&
name|cycle
operator|->
name|read_events
index|[
name|fd
index|]
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_CLOSE_EVENT
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_close_socket
argument_list|(
name|ls
index|[
name|i
index|]
operator|.
name|fd
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_close_socket_n
literal|" %s failed"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|addr_text
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
name|cycle
operator|->
name|connections
index|[
name|fd
index|]
operator|.
name|fd
operator|=
operator|-
literal|1
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_connection_error (ngx_connection_t * c,ngx_err_t err,char * text)
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
block|{
name|ngx_int_t
name|level
decl_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_ECONNRESET
operator|&&
name|c
operator|->
name|read
operator|->
name|log_error
operator|==
name|NGX_ERROR_IGNORE_ECONNRESET
condition|)
block|{
return|return
literal|0
return|;
block|}
if|if
condition|(
name|err
operator|==
name|NGX_ECONNRESET
operator|||
name|err
operator|==
name|NGX_EPIPE
operator|||
name|err
operator|==
name|NGX_ENOTCONN
condition|)
block|{
switch|switch
condition|(
name|c
operator|->
name|read
operator|->
name|log_error
condition|)
block|{
case|case
name|NGX_ERROR_INFO
case|:
name|level
operator|=
name|NGX_LOG_INFO
expr_stmt|;
break|break;
case|case
name|NGX_ERROR_ERR
case|:
name|level
operator|=
name|NGX_LOG_ERR
expr_stmt|;
break|break;
default|default:
name|level
operator|=
name|NGX_LOG_CRIT
expr_stmt|;
block|}
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
name|text
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
end_function

end_unit

