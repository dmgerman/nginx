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

begin_comment
comment|/* the buffer size is enough to hold "struct sockaddr_un" */
end_comment

begin_define
DECL|macro|NGX_SOCKLEN
define|#
directive|define
name|NGX_SOCKLEN
value|512
end_define

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_enable_accept_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_disable_accept_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_close_accepted_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|ngx_event_accept (ngx_event_t * ev)
name|ngx_event_accept
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|socklen_t
name|socklen
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
name|ngx_event_t
modifier|*
name|rev
decl_stmt|,
modifier|*
name|wev
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|,
modifier|*
name|lc
decl_stmt|;
name|ngx_event_conf_t
modifier|*
name|ecf
decl_stmt|;
name|char
name|sa
index|[
name|NGX_SOCKLEN
index|]
decl_stmt|;
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
name|ngx_event_flags
operator|&
name|NGX_USE_RTSIG_EVENT
condition|)
block|{
name|ev
operator|->
name|available
operator|=
literal|1
expr_stmt|;
block|}
if|else if
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
literal|"accept on %V, ready: %d"
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
name|socklen
operator|=
name|NGX_SOCKLEN
expr_stmt|;
name|s
operator|=
name|accept
argument_list|(
name|lc
operator|->
name|fd
argument_list|,
operator|(
expr|struct
name|sockaddr
operator|*
operator|)
name|sa
argument_list|,
operator|&
name|socklen
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
literal|"accept() not ready"
argument_list|)
expr_stmt|;
return|return;
block|}
name|ngx_log_error
argument_list|(
operator|(
name|err
operator|==
name|NGX_ECONNABORTED
operator|)
condition|?
name|NGX_LOG_ERR
else|:
name|NGX_LOG_ALERT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"accept() failed"
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_ECONNABORTED
condition|)
block|{
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
operator|--
expr_stmt|;
block|}
if|if
condition|(
name|ev
operator|->
name|available
condition|)
block|{
continue|continue;
block|}
block|}
return|return;
block|}
if|#
directive|if
operator|(
name|NGX_STAT_STUB
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
name|s
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
name|ev
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
return|return;
block|}
if|#
directive|if
operator|(
name|NGX_STAT_STUB
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
name|ngx_close_accepted_connection
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
name|ngx_close_accepted_connection
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
name|sa
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
name|ngx_close_accepted_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
comment|/* set a blocking mode for aio and non-blocking mode for others */
if|if
condition|(
name|ngx_inherited_nonblocking
condition|)
block|{
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_AIO_EVENT
condition|)
block|{
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
name|ev
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_blocking_n
literal|" failed"
argument_list|)
expr_stmt|;
name|ngx_close_accepted_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
block|}
else|else
block|{
if|if
condition|(
operator|!
operator|(
name|ngx_event_flags
operator|&
operator|(
name|NGX_USE_AIO_EVENT
operator||
name|NGX_USE_RTSIG_EVENT
operator|)
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
name|NGX_LOG_ALERT
argument_list|,
name|ev
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_nonblocking_n
literal|" failed"
argument_list|)
expr_stmt|;
name|ngx_close_accepted_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
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
name|c
operator|->
name|socklen
operator|=
name|socklen
expr_stmt|;
name|c
operator|->
name|unexpected_eof
operator|=
literal|1
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
if|if
condition|(
name|ngx_event_flags
operator|&
operator|(
name|NGX_USE_AIO_EVENT
operator||
name|NGX_USE_RTSIG_EVENT
operator|)
condition|)
block|{
comment|/* rtsig, aio, iocp */
name|rev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|ev
operator|->
name|deferred_accept
condition|)
block|{
name|rev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
name|rev
operator|->
name|available
operator|=
literal|1
expr_stmt|;
endif|#
directive|endif
block|}
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
name|ngx_atomic_fetch_add
argument_list|(
name|ngx_stat_handled
argument_list|,
literal|1
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
name|rev
operator|->
name|lock
operator|=
operator|&
name|c
operator|->
name|lock
expr_stmt|;
name|wev
operator|->
name|lock
operator|=
operator|&
name|c
operator|->
name|lock
expr_stmt|;
name|rev
operator|->
name|own_lock
operator|=
operator|&
name|c
operator|->
name|lock
expr_stmt|;
name|wev
operator|->
name|own_lock
operator|=
operator|&
name|c
operator|->
name|lock
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
name|ngx_close_accepted_connection
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
name|addr_text
operator|.
name|data
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
name|len
operator|==
literal|0
condition|)
block|{
name|ngx_close_accepted_connection
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
name|in_addr_t
name|i
decl_stmt|;
name|ngx_event_debug_t
modifier|*
name|dc
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
name|sin
operator|=
operator|(
expr|struct
name|sockaddr_in
operator|*
operator|)
name|sa
expr_stmt|;
name|dc
operator|=
name|ecf
operator|->
name|debug_connection
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
name|ecf
operator|->
name|debug_connection
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
operator|&
name|dc
index|[
name|i
index|]
operator|.
name|mask
operator|)
operator|==
name|dc
index|[
name|i
index|]
operator|.
name|addr
condition|)
block|{
name|log
operator|->
name|log_level
operator|=
name|NGX_LOG_DEBUG_CONNECTION
operator||
name|NGX_LOG_DEBUG_ALL
expr_stmt|;
break|break;
block|}
block|}
block|}
endif|#
directive|endif
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"*%d accept: %V fd:%d"
argument_list|,
name|c
operator|->
name|number
argument_list|,
operator|&
name|c
operator|->
name|addr_text
argument_list|,
name|s
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_add_conn
operator|&&
operator|(
name|ngx_event_flags
operator|&
name|NGX_USE_EPOLL_EVENT
operator|)
operator|==
literal|0
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
name|ngx_close_accepted_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
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
operator|--
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
name|ngx_int_t
DECL|function|ngx_trylock_accept_mutex (ngx_cycle_t * cycle)
name|ngx_trylock_accept_mutex
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
if|if
condition|(
name|ngx_shmtx_trylock
argument_list|(
operator|&
name|ngx_accept_mutex
argument_list|)
condition|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"accept mutex locked"
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_accept_mutex_held
operator|&&
name|ngx_accept_events
operator|==
literal|0
operator|&&
operator|!
operator|(
name|ngx_event_flags
operator|&
name|NGX_USE_RTSIG_EVENT
operator|)
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|ngx_enable_accept_events
argument_list|(
name|cycle
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_shmtx_unlock
argument_list|(
operator|&
name|ngx_accept_mutex
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_accept_events
operator|=
literal|0
expr_stmt|;
name|ngx_accept_mutex_held
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"accept mutex lock failed: %ui"
argument_list|,
name|ngx_accept_mutex_held
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_accept_mutex_held
condition|)
block|{
if|if
condition|(
name|ngx_disable_accept_events
argument_list|(
name|cycle
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_accept_mutex_held
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_enable_accept_events (ngx_cycle_t * cycle)
name|ngx_enable_accept_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
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
name|c
operator|=
name|ls
index|[
name|i
index|]
operator|.
name|connection
expr_stmt|;
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_RTSIG_EVENT
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
return|return
name|NGX_ERROR
return|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|ngx_add_event
argument_list|(
name|c
operator|->
name|read
argument_list|,
name|NGX_READ_EVENT
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_disable_accept_events (ngx_cycle_t * cycle)
name|ngx_disable_accept_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
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
name|c
operator|=
name|ls
index|[
name|i
index|]
operator|.
name|connection
expr_stmt|;
if|if
condition|(
operator|!
name|c
operator|->
name|read
operator|->
name|active
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_RTSIG_EVENT
condition|)
block|{
if|if
condition|(
name|ngx_del_conn
argument_list|(
name|c
argument_list|,
name|NGX_DISABLE_EVENT
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|ngx_del_event
argument_list|(
name|c
operator|->
name|read
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_DISABLE_EVENT
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_close_accepted_connection (ngx_connection_t * c)
name|ngx_close_accepted_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
name|ngx_socket_t
name|fd
decl_stmt|;
name|ngx_free_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
name|fd
operator|=
name|c
operator|->
name|fd
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
name|ngx_close_socket
argument_list|(
name|fd
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
name|c
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

begin_function
name|u_char
modifier|*
DECL|function|ngx_accept_log_error (ngx_log_t * log,u_char * buf,size_t len)
name|ngx_accept_log_error
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
return|return
name|ngx_snprintf
argument_list|(
name|buf
argument_list|,
name|len
argument_list|,
literal|" while accepting new connection on %V"
argument_list|,
name|log
operator|->
name|data
argument_list|)
return|;
block|}
end_function

end_unit

