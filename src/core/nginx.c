begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<nginx.h>
end_include

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_errno.h>
end_include

begin_include
include|#
directive|include
file|<ngx_time.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_array.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_include
include|#
directive|include
file|<ngx_server.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_include
include|#
directive|include
file|<ngx_listen.h>
end_include

begin_comment
comment|/* STUB */
end_comment

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_comment
comment|/* */
end_comment

begin_function_decl
specifier|static
name|void
name|ngx_set_signals
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_open_listening_sockets
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* STUB */
end_comment

begin_decl_stmt
DECL|variable|ngx_max_conn
name|int
name|ngx_max_conn
init|=
literal|512
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_server
name|ngx_server_t
name|ngx_server
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* */
end_comment

begin_decl_stmt
DECL|variable|ngx_log
name|ngx_log_t
name|ngx_log
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_pool
name|ngx_pool_t
modifier|*
name|ngx_pool
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_connection_counter
name|int
name|ngx_connection_counter
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_listening_sockets
name|ngx_array_t
modifier|*
name|ngx_listening_sockets
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|main (int argc,char * const * argv)
name|int
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
specifier|const
modifier|*
name|argv
parameter_list|)
block|{
name|ngx_str_t
name|conf_file
decl_stmt|;
name|ngx_conf_t
name|conf
decl_stmt|;
comment|/* STUB */
name|ngx_log
operator|.
name|log_level
operator|=
name|NGX_LOG_DEBUG
expr_stmt|;
name|ngx_pool
operator|=
name|ngx_create_pool
argument_list|(
literal|16
operator|*
literal|1024
argument_list|,
operator|&
name|ngx_log
argument_list|)
expr_stmt|;
comment|/* */
if|#
directive|if
operator|!
operator|(
name|WIN32
operator|)
name|ngx_set_signals
argument_list|(
operator|&
name|ngx_log
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|ngx_init_sockets
argument_list|(
operator|&
name|ngx_log
argument_list|)
expr_stmt|;
comment|/* TODO: read config */
if|#
directive|if
literal|1
name|ngx_memzero
argument_list|(
operator|&
name|conf
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_conf_t
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|conf
operator|.
name|args
argument_list|,
name|ngx_create_array
argument_list|(
name|ngx_pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_str_t
argument_list|)
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|conf
operator|.
name|pool
operator|=
name|ngx_pool
expr_stmt|;
name|conf
operator|.
name|log
operator|=
operator|&
name|ngx_log
expr_stmt|;
name|conf_file
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"nginx.conf"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|conf_file
operator|.
name|data
operator|=
literal|"nginx.conf"
expr_stmt|;
name|ngx_conf_parse
argument_list|(
operator|&
name|conf
argument_list|,
operator|&
name|conf_file
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|ngx_test_null
argument_list|(
name|ngx_listening_sockets
argument_list|,
name|ngx_create_array
argument_list|(
name|ngx_pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_listen_t
argument_list|)
argument_list|)
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/* STUB */
comment|/* TODO: init chain of global modules (like ngx_http.c),        they would init its modules and ngx_listening_sockets */
name|ngx_http_init
argument_list|(
name|ngx_pool
argument_list|,
operator|&
name|ngx_log
argument_list|)
expr_stmt|;
name|ngx_open_listening_sockets
argument_list|(
operator|&
name|ngx_log
argument_list|)
expr_stmt|;
comment|/* TODO: daemon */
comment|/* TODO: fork */
name|ngx_pre_thread
argument_list|(
name|ngx_listening_sockets
argument_list|,
name|ngx_pool
argument_list|,
operator|&
name|ngx_log
argument_list|)
expr_stmt|;
comment|/* TODO: threads */
comment|/* STUB */
name|ngx_worker
argument_list|(
operator|&
name|ngx_log
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_if
if|#
directive|if
operator|!
operator|(
name|WIN32
operator|)
end_if

begin_function
DECL|function|ngx_set_signals (ngx_log_t * log)
specifier|static
name|void
name|ngx_set_signals
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|struct
name|sigaction
name|sa
decl_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|sa
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|sigaction
argument_list|)
argument_list|)
expr_stmt|;
name|sa
operator|.
name|sa_handler
operator|=
name|SIG_IGN
expr_stmt|;
name|sigemptyset
argument_list|(
operator|&
name|sa
operator|.
name|sa_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|sigaction
argument_list|(
name|SIGPIPE
argument_list|,
operator|&
name|sa
argument_list|,
name|NULL
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
name|ngx_errno
argument_list|,
literal|"sigaction(SIGPIPE, SIG_IGN) failed"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_open_listening_sockets (ngx_log_t * log)
specifier|static
name|void
name|ngx_open_listening_sockets
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|int
name|times
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
name|ngx_socket_t
name|s
decl_stmt|;
name|ngx_listen_t
modifier|*
name|ls
decl_stmt|;
name|reuseaddr
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|times
operator|=
literal|10
init|;
name|times
condition|;
name|times
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
operator|(
name|ngx_listen_t
operator|*
operator|)
name|ngx_listening_sockets
operator|->
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
name|ngx_listening_sockets
operator|->
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
name|done
condition|)
continue|continue;
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
name|ls
index|[
name|i
index|]
operator|.
name|done
operator|=
literal|1
expr_stmt|;
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
literal|" %s falied"
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
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
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
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
comment|/* TODO: close on exit */
if|if
condition|(
name|ls
index|[
name|i
index|]
operator|.
name|nonblocking
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
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
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
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
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
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
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
name|ls
index|[
name|i
index|]
operator|.
name|done
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|failed
condition|)
break|break;
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
literal|"can not bind(), exiting"
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

