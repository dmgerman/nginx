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
comment|/*  * On Linux up to 2.4.21 sendfile() (syscall #187) works with 32-bit  * offsets only, and the including<sys/sendfile.h> breaks the compiling,  * if off_t is 64 bit wide.  So we use own sendfile() definition, where offset  * parameter is int32_t, and use sendfile() for the file parts below 2G only,  * see src/os/unix/ngx_linux_config.h  *  * Linux 2.4.21 has a new sendfile64() syscall #239.  */
end_comment

begin_define
DECL|macro|NGX_HEADERS
define|#
directive|define
name|NGX_HEADERS
value|8
end_define

begin_function
DECL|function|ngx_linux_sendfile_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_chain_t
modifier|*
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
name|u_char
modifier|*
name|prev
decl_stmt|;
name|off_t
name|size
decl_stmt|,
name|send
decl_stmt|,
name|prev_send
decl_stmt|,
name|aligned
decl_stmt|,
name|sent
decl_stmt|,
name|fprev
decl_stmt|;
name|size_t
name|file_size
decl_stmt|;
name|ngx_uint_t
name|eintr
decl_stmt|,
name|complete
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_buf_t
modifier|*
name|file
decl_stmt|;
name|ngx_array_t
name|header
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|struct
name|iovec
modifier|*
name|iov
decl_stmt|,
name|headers
index|[
name|NGX_HEADERS
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
comment|/* the maximum limit size is the maximum size_t value - the page size */
if|if
condition|(
name|limit
operator|==
literal|0
operator|||
name|limit
operator|>
name|NGX_MAX_SIZE_T_VALUE
operator|-
name|ngx_pagesize
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
name|header
operator|.
name|elts
operator|=
name|headers
expr_stmt|;
name|header
operator|.
name|size
operator|=
sizeof|sizeof
argument_list|(
expr|struct
name|iovec
argument_list|)
expr_stmt|;
name|header
operator|.
name|nalloc
operator|=
name|NGX_HEADERS
expr_stmt|;
name|header
operator|.
name|pool
operator|=
name|c
operator|->
name|pool
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|file
operator|=
name|NULL
expr_stmt|;
name|file_size
operator|=
literal|0
expr_stmt|;
name|eintr
operator|=
literal|0
expr_stmt|;
name|complete
operator|=
literal|0
expr_stmt|;
name|prev_send
operator|=
name|send
expr_stmt|;
name|header
operator|.
name|nelts
operator|=
literal|0
expr_stmt|;
name|prev
operator|=
name|NULL
expr_stmt|;
name|iov
operator|=
name|NULL
expr_stmt|;
comment|/* create the iovec and coalesce the neighbouring bufs */
for|for
control|(
name|cl
operator|=
name|in
init|;
name|cl
operator|&&
name|header
operator|.
name|nelts
operator|<
name|IOV_MAX
operator|&&
name|send
operator|<
name|limit
condition|;
name|cl
operator|=
name|cl
operator|->
name|next
control|)
block|{
if|if
condition|(
name|ngx_buf_special
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
continue|continue;
block|}
if|#
directive|if
literal|1
if|if
condition|(
operator|!
name|ngx_buf_in_memory
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
operator|&&
operator|!
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
literal|"zero size buf in sendfile"
argument_list|)
expr_stmt|;
name|ngx_debug_point
argument_list|()
expr_stmt|;
block|}
endif|#
directive|endif
if|if
condition|(
operator|!
name|ngx_buf_in_memory_only
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
break|break;
block|}
name|size
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
operator|-
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
if|if
condition|(
name|send
operator|+
name|size
operator|>
name|limit
condition|)
block|{
name|size
operator|=
name|limit
operator|-
name|send
expr_stmt|;
block|}
if|if
condition|(
name|prev
operator|==
name|cl
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
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
operator|(
name|iov
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|header
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|iov
operator|->
name|iov_base
operator|=
operator|(
name|void
operator|*
operator|)
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|iov
operator|->
name|iov_len
operator|=
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
block|}
name|prev
operator|=
name|cl
operator|->
name|buf
operator|->
name|pos
operator|+
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
name|send
operator|+=
name|size
expr_stmt|;
block|}
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
name|nelts
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
name|ngx_errno
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
name|ngx_socket_errno
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
literal|0
expr_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
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
operator|!
name|c
operator|->
name|tcp_nodelay
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
name|ngx_errno
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
name|nelts
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
do|do
block|{
name|size
operator|=
name|cl
operator|->
name|buf
operator|->
name|file_last
operator|-
name|cl
operator|->
name|buf
operator|->
name|file_pos
expr_stmt|;
if|if
condition|(
name|send
operator|+
name|size
operator|>
name|limit
condition|)
block|{
name|size
operator|=
name|limit
operator|-
name|send
expr_stmt|;
name|aligned
operator|=
operator|(
name|cl
operator|->
name|buf
operator|->
name|file_pos
operator|+
name|size
operator|+
name|ngx_pagesize
operator|-
literal|1
operator|)
operator|&
operator|~
operator|(
name|ngx_pagesize
operator|-
literal|1
operator|)
expr_stmt|;
if|if
condition|(
name|aligned
operator|<=
name|cl
operator|->
name|buf
operator|->
name|file_last
condition|)
block|{
name|size
operator|=
name|aligned
operator|-
name|cl
operator|->
name|buf
operator|->
name|file_pos
expr_stmt|;
block|}
block|}
name|file_size
operator|+=
operator|(
name|size_t
operator|)
name|size
expr_stmt|;
name|send
operator|+=
name|size
expr_stmt|;
name|fprev
operator|=
name|cl
operator|->
name|buf
operator|->
name|file_pos
operator|+
name|size
expr_stmt|;
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
block|}
do|while
condition|(
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
operator|&&
name|file
operator|->
name|file
operator|->
name|fd
operator|==
name|cl
operator|->
name|buf
operator|->
name|file
operator|->
name|fd
operator|&&
name|fprev
operator|==
name|cl
operator|->
name|buf
operator|->
name|file_pos
condition|)
do|;
block|}
if|if
condition|(
name|file
condition|)
block|{
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
if|if
condition|(
name|err
operator|==
name|NGX_EAGAIN
operator|||
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
if|if
condition|(
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
name|eintr
operator|=
literal|1
expr_stmt|;
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
else|else
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
literal|"sendfile() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
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
name|rc
operator|=
name|writev
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|header
operator|.
name|elts
argument_list|,
name|header
operator|.
name|nelts
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
if|if
condition|(
name|err
operator|==
name|NGX_EAGAIN
operator|||
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
if|if
condition|(
name|err
operator|==
name|NGX_EINTR
condition|)
block|{
name|eintr
operator|=
literal|1
expr_stmt|;
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
literal|"writev() not ready"
argument_list|)
expr_stmt|;
block|}
else|else
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
literal|"writev() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
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
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"writev: %O"
argument_list|,
name|sent
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|send
operator|-
name|prev_send
operator|==
name|sent
condition|)
block|{
name|complete
operator|=
literal|1
expr_stmt|;
block|}
name|c
operator|->
name|sent
operator|+=
name|sent
expr_stmt|;
for|for
control|(
name|cl
operator|=
name|in
init|;
name|cl
condition|;
name|cl
operator|=
name|cl
operator|->
name|next
control|)
block|{
if|if
condition|(
name|ngx_buf_special
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|sent
operator|==
literal|0
condition|)
block|{
break|break;
block|}
name|size
operator|=
name|ngx_buf_size
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
expr_stmt|;
if|if
condition|(
name|sent
operator|>=
name|size
condition|)
block|{
name|sent
operator|-=
name|size
expr_stmt|;
if|if
condition|(
name|ngx_buf_in_memory
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
name|cl
operator|->
name|buf
operator|->
name|pos
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
expr_stmt|;
block|}
if|if
condition|(
name|cl
operator|->
name|buf
operator|->
name|in_file
condition|)
block|{
name|cl
operator|->
name|buf
operator|->
name|file_pos
operator|=
name|cl
operator|->
name|buf
operator|->
name|file_last
expr_stmt|;
block|}
continue|continue;
block|}
if|if
condition|(
name|ngx_buf_in_memory
argument_list|(
name|cl
operator|->
name|buf
argument_list|)
condition|)
block|{
name|cl
operator|->
name|buf
operator|->
name|pos
operator|+=
operator|(
name|size_t
operator|)
name|sent
expr_stmt|;
block|}
if|if
condition|(
name|cl
operator|->
name|buf
operator|->
name|in_file
condition|)
block|{
name|cl
operator|->
name|buf
operator|->
name|file_pos
operator|+=
name|sent
expr_stmt|;
block|}
break|break;
block|}
if|if
condition|(
name|eintr
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
operator|!
name|complete
condition|)
block|{
name|wev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
return|return
name|cl
return|;
block|}
if|if
condition|(
name|send
operator|>=
name|limit
operator|||
name|cl
operator|==
name|NULL
condition|)
block|{
return|return
name|cl
return|;
block|}
name|in
operator|=
name|cl
expr_stmt|;
block|}
block|}
end_function

end_unit

