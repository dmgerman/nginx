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

begin_define
DECL|macro|NGX_WSABUFS
define|#
directive|define
name|NGX_WSABUFS
value|8
end_define

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_wsasend_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_wsasend_chain
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
decl_stmt|;
name|u_char
modifier|*
name|prev
decl_stmt|;
name|u_long
name|size
decl_stmt|,
name|sent
decl_stmt|,
name|send
decl_stmt|,
name|prev_send
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|ngx_array_t
name|vec
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|LPWSABUF
name|wsabuf
decl_stmt|;
name|WSABUF
name|wsabufs
index|[
name|NGX_WSABUFS
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
comment|/* the maximum limit size is the maximum u_long value - the page size */
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
name|NGX_MAX_UINT32_VALUE
operator|-
name|ngx_pagesize
operator|)
condition|)
block|{
name|limit
operator|=
name|NGX_MAX_UINT32_VALUE
operator|-
name|ngx_pagesize
expr_stmt|;
block|}
name|send
operator|=
literal|0
expr_stmt|;
comment|/*      * WSABUFs must be 4-byte aligned otherwise      * WSASend() will return undocumented WSAEINVAL error.      */
name|vec
operator|.
name|elts
operator|=
name|wsabufs
expr_stmt|;
name|vec
operator|.
name|size
operator|=
sizeof|sizeof
argument_list|(
name|WSABUF
argument_list|)
expr_stmt|;
name|vec
operator|.
name|nalloc
operator|=
name|NGX_WSABUFS
expr_stmt|;
name|vec
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
name|prev
operator|=
name|NULL
expr_stmt|;
name|wsabuf
operator|=
name|NULL
expr_stmt|;
name|prev_send
operator|=
name|send
expr_stmt|;
name|vec
operator|.
name|nelts
operator|=
literal|0
expr_stmt|;
comment|/* create the WSABUF and coalesce the neighbouring bufs */
for|for
control|(
name|cl
operator|=
name|in
init|;
name|cl
operator|&&
name|vec
operator|.
name|nelts
operator|<
name|ngx_max_wsabufs
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
operator|(
name|u_long
operator|)
operator|(
name|limit
operator|-
name|send
operator|)
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
name|wsabuf
operator|->
name|len
operator|+=
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
block|}
else|else
block|{
name|wsabuf
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|vec
argument_list|)
expr_stmt|;
if|if
condition|(
name|wsabuf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|wsabuf
operator|->
name|buf
operator|=
operator|(
name|char
operator|*
operator|)
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|wsabuf
operator|->
name|len
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
block|}
name|prev
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|send
operator|+=
name|size
expr_stmt|;
block|}
name|sent
operator|=
literal|0
expr_stmt|;
name|rc
operator|=
name|WSASend
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|vec
operator|.
name|elts
argument_list|,
name|vec
operator|.
name|nelts
argument_list|,
operator|&
name|sent
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
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
name|WSAEWOULDBLOCK
condition|)
block|{
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
literal|"WSASend() not ready"
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
literal|"WSASend() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
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
literal|"WSASend: fd:%d, s:%ul"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|sent
argument_list|)
expr_stmt|;
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

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_overlapped_wsasend_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_overlapped_wsasend_chain
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
decl_stmt|;
name|u_char
modifier|*
name|prev
decl_stmt|;
name|u_long
name|size
decl_stmt|,
name|send
decl_stmt|,
name|sent
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_event_t
modifier|*
name|wev
decl_stmt|;
name|ngx_array_t
name|vec
decl_stmt|;
name|ngx_chain_t
modifier|*
name|cl
decl_stmt|;
name|LPWSAOVERLAPPED
name|ovlp
decl_stmt|;
name|LPWSABUF
name|wsabuf
decl_stmt|;
name|WSABUF
name|wsabufs
index|[
name|NGX_WSABUFS
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
literal|"wev->complete: %d"
argument_list|,
name|wev
operator|->
name|complete
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|wev
operator|->
name|complete
condition|)
block|{
comment|/* post the overlapped WSASend() */
comment|/* the maximum limit size is the maximum u_long value - the page size */
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
name|NGX_MAX_UINT32_VALUE
operator|-
name|ngx_pagesize
operator|)
condition|)
block|{
name|limit
operator|=
name|NGX_MAX_UINT32_VALUE
operator|-
name|ngx_pagesize
expr_stmt|;
block|}
comment|/*          * WSABUFs must be 4-byte aligned otherwise          * WSASend() will return undocumented WSAEINVAL error.          */
name|vec
operator|.
name|elts
operator|=
name|wsabufs
expr_stmt|;
name|vec
operator|.
name|nelts
operator|=
literal|0
expr_stmt|;
name|vec
operator|.
name|size
operator|=
sizeof|sizeof
argument_list|(
name|WSABUF
argument_list|)
expr_stmt|;
name|vec
operator|.
name|nalloc
operator|=
name|NGX_WSABUFS
expr_stmt|;
name|vec
operator|.
name|pool
operator|=
name|c
operator|->
name|pool
expr_stmt|;
name|send
operator|=
literal|0
expr_stmt|;
name|prev
operator|=
name|NULL
expr_stmt|;
name|wsabuf
operator|=
name|NULL
expr_stmt|;
comment|/* create the WSABUF and coalesce the neighbouring bufs */
for|for
control|(
name|cl
operator|=
name|in
init|;
name|cl
operator|&&
name|vec
operator|.
name|nelts
operator|<
name|ngx_max_wsabufs
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
operator|(
name|u_long
operator|)
operator|(
name|limit
operator|-
name|send
operator|)
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
name|wsabuf
operator|->
name|len
operator|+=
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
block|}
else|else
block|{
name|wsabuf
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|vec
argument_list|)
expr_stmt|;
if|if
condition|(
name|wsabuf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|wsabuf
operator|->
name|buf
operator|=
operator|(
name|char
operator|*
operator|)
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|wsabuf
operator|->
name|len
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
block|}
name|prev
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|send
operator|+=
name|size
expr_stmt|;
block|}
name|ovlp
operator|=
operator|(
name|LPWSAOVERLAPPED
operator|)
operator|&
name|c
operator|->
name|write
operator|->
name|ovlp
expr_stmt|;
name|ngx_memzero
argument_list|(
name|ovlp
argument_list|,
sizeof|sizeof
argument_list|(
name|WSAOVERLAPPED
argument_list|)
argument_list|)
expr_stmt|;
name|rc
operator|=
name|WSASend
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|vec
operator|.
name|elts
argument_list|,
name|vec
operator|.
name|nelts
argument_list|,
operator|&
name|sent
argument_list|,
literal|0
argument_list|,
name|ovlp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|wev
operator|->
name|complete
operator|=
literal|0
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
name|WSA_IO_PENDING
condition|)
block|{
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
literal|"WSASend() posted"
argument_list|)
expr_stmt|;
name|wev
operator|->
name|active
operator|=
literal|1
expr_stmt|;
return|return
name|in
return|;
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
literal|"WSASend() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
block|}
if|else if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_IOCP_EVENT
condition|)
block|{
comment|/*               * if a socket was bound with I/O completion port then               * GetQueuedCompletionStatus() would anyway return its status               * despite that WSASend() was already complete               */
name|wev
operator|->
name|active
operator|=
literal|1
expr_stmt|;
return|return
name|in
return|;
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
literal|"WSASend: fd:%d, s:%ul"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|sent
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/* the overlapped WSASend() complete */
name|wev
operator|->
name|complete
operator|=
literal|0
expr_stmt|;
name|wev
operator|->
name|active
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_IOCP_EVENT
condition|)
block|{
if|if
condition|(
name|wev
operator|->
name|ovlp
operator|.
name|error
condition|)
block|{
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|wev
operator|->
name|ovlp
operator|.
name|error
argument_list|,
literal|"WSASend() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
name|sent
operator|=
name|wev
operator|->
name|available
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|WSAGetOverlappedResult
argument_list|(
name|c
operator|->
name|fd
argument_list|,
operator|(
name|LPWSAOVERLAPPED
operator|)
operator|&
name|wev
operator|->
name|ovlp
argument_list|,
operator|&
name|sent
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSASend() or WSAGetOverlappedResult() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
block|}
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
literal|"WSASend ovlp: fd:%d, s:%ul"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|sent
argument_list|)
expr_stmt|;
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
name|in
condition|)
block|{
name|wev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|wev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
block|}
return|return
name|in
return|;
block|}
end_function

end_unit

