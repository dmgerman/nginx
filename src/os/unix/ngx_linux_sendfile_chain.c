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

begin_comment
comment|/*  * On Linux up to 2.4.21 sendfile() (syscall #187) works with 32-bit  * offsets only, and the including<sys/sendfile.h> breaks the compiling,  * if off_t is 64 bit wide.  So we use own sendfile() definition, where offset  * parameter is int32_t, and use sendfile() for the file parts below 2G only,  * see src/os/unix/ngx_linux_config.h  *  * Linux 2.4.21 has the new sendfile64() syscall #239.  *  * On Linux up to 2.6.16 sendfile() does not allow to pass the count parameter  * more than 2G-1 bytes even on 64-bit platforms: it returns EINVAL,  * so we limit it to 2G-1 bytes.  */
end_comment

begin_define
DECL|macro|NGX_SENDFILE_MAXSIZE
define|#
directive|define
name|NGX_SENDFILE_MAXSIZE
value|2147483647L
end_define

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_linux_sendfile_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_linux_sendfile_chain
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
name|int
name|rc
decl_stmt|,
name|tcp_nodelay
decl_stmt|;
name|off_t
name|send
decl_stmt|,
name|prev_send
decl_stmt|,
name|sent
decl_stmt|;
name|size_t
name|file_size
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_buf_t
modifier|*
name|file
decl_stmt|;
name|ngx_uint_t
name|eintr
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|ngx_iovec_t
name|header
decl_stmt|;
name|struct
name|iovec
name|headers
index|[
name|NGX_IOVS_PREALLOCATE
index|]
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE64
operator|)
name|off_t
name|offset
decl_stmt|;
else|#
directive|else
name|int32_t
name|offset
decl_stmt|;
endif|#
directive|endif
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
comment|/* the maximum limit size is 2G-1 - the page size */
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
name|NGX_SENDFILE_MAXSIZE
operator|-
name|ngx_pagesize
operator|)
condition|)
block|{
name|limit
operator|=
name|NGX_SENDFILE_MAXSIZE
operator|-
name|ngx_pagesize
expr_stmt|;
block|}
name|send
operator|=
literal|0
expr_stmt|;
name|header
operator|.
name|iovs
operator|=
name|headers
expr_stmt|;
name|header
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
name|eintr
operator|=
literal|0
expr_stmt|;
name|prev_send
operator|=
name|send
expr_stmt|;
comment|/* create the iovec and coalesce the neighbouring bufs */
name|cl
operator|=
name|ngx_output_chain_to_iovec
argument_list|(
operator|&
name|header
argument_list|,
name|in
argument_list|,
name|limit
operator|-
name|send
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
name|send
operator|+=
name|header
operator|.
name|size
expr_stmt|;
comment|/* set TCP_CORK if there is a header before a file */
if|if
condition|(
name|c
operator|->
name|tcp_nopush
operator|==
name|NGX_TCP_NOPUSH_UNSET
operator|&&
name|header
operator|.
name|count
operator|!=
literal|0
operator|&&
name|cl
operator|&&
name|cl
operator|->
name|buf
operator|->
name|in_file
condition|)
block|{
comment|/* the TCP_CORK and TCP_NODELAY are mutually exclusive */
if|if
condition|(
name|c
operator|->
name|tcp_nodelay
operator|==
name|NGX_TCP_NODELAY_SET
condition|)
block|{
name|tcp_nodelay
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|setsockopt
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|IPPROTO_TCP
argument_list|,
name|TCP_NODELAY
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|tcp_nodelay
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
comment|/*                      * there is a tiny chance to be interrupted, however,                      * we continue a processing with the TCP_NODELAY                      * and without the TCP_CORK                      */
if|if
condition|(
name|err
operator|!=
name|NGX_EINTR
condition|)
block|{
name|wev
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
literal|"setsockopt(TCP_NODELAY) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
block|}
else|else
block|{
name|c
operator|->
name|tcp_nodelay
operator|=
name|NGX_TCP_NODELAY_UNSET
expr_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no tcp_nodelay"
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|c
operator|->
name|tcp_nodelay
operator|==
name|NGX_TCP_NODELAY_UNSET
condition|)
block|{
if|if
condition|(
name|ngx_tcp_nopush
argument_list|(
name|c
operator|->
name|fd
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
comment|/*                      * there is a tiny chance to be interrupted, however,                      * we continue a processing without the TCP_CORK                      */
if|if
condition|(
name|err
operator|!=
name|NGX_EINTR
condition|)
block|{
name|wev
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
name|ngx_tcp_nopush_n
literal|" failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
block|}
else|else
block|{
name|c
operator|->
name|tcp_nopush
operator|=
name|NGX_TCP_NOPUSH_SET
expr_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"tcp_nopush"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/* get the file buf */
if|if
condition|(
name|header
operator|.
name|count
operator|==
literal|0
operator|&&
name|cl
operator|&&
name|cl
operator|->
name|buf
operator|->
name|in_file
operator|&&
name|send
operator|<
name|limit
condition|)
block|{
name|file
operator|=
name|cl
operator|->
name|buf
expr_stmt|;
comment|/* coalesce the neighbouring file bufs */
name|file_size
operator|=
operator|(
name|size_t
operator|)
name|ngx_chain_coalesce_file
argument_list|(
operator|&
name|cl
argument_list|,
name|limit
operator|-
name|send
argument_list|)
expr_stmt|;
name|send
operator|+=
name|file_size
expr_stmt|;
if|#
directive|if
literal|1
if|if
condition|(
name|file_size
operator|==
literal|0
condition|)
block|{
name|ngx_debug_point
argument_list|()
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE64
operator|)
name|offset
operator|=
name|file
operator|->
name|file_pos
expr_stmt|;
else|#
directive|else
name|offset
operator|=
operator|(
name|int32_t
operator|)
name|file
operator|->
name|file_pos
expr_stmt|;
endif|#
directive|endif
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
literal|"sendfile: @%O %uz"
argument_list|,
name|file
operator|->
name|file_pos
argument_list|,
name|file_size
argument_list|)
expr_stmt|;
name|rc
operator|=
name|sendfile
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|file
operator|->
name|file
operator|->
name|fd
argument_list|,
operator|&
name|offset
argument_list|,
name|file_size
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
break|break;
case|case
name|NGX_EINTR
case|:
name|eintr
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
name|wev
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
literal|"sendfile() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
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
literal|"sendfile() is not ready"
argument_list|)
expr_stmt|;
block|}
name|sent
operator|=
name|rc
operator|>
literal|0
condition|?
name|rc
else|:
literal|0
expr_stmt|;
name|ngx_log_debug4
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"sendfile: %d, @%O %O:%uz"
argument_list|,
name|rc
argument_list|,
name|file
operator|->
name|file_pos
argument_list|,
name|sent
argument_list|,
name|file_size
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|n
operator|=
name|ngx_writev
argument_list|(
name|c
argument_list|,
operator|&
name|header
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
name|sent
operator|=
operator|(
name|n
operator|==
name|NGX_AGAIN
operator|)
condition|?
literal|0
else|:
name|n
expr_stmt|;
block|}
name|c
operator|->
name|sent
operator|+=
name|sent
expr_stmt|;
name|in
operator|=
name|ngx_chain_update_sent
argument_list|(
name|in
argument_list|,
name|sent
argument_list|)
expr_stmt|;
if|if
condition|(
name|eintr
condition|)
block|{
name|send
operator|=
name|prev_send
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|send
operator|-
name|prev_send
operator|!=
name|sent
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

end_unit

