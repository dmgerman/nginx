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

begin_function
DECL|function|ngx_wsarecv (ngx_connection_t * c,char * buf,size_t size)
name|ssize_t
name|ngx_wsarecv
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|u_int
name|flags
decl_stmt|;
name|size_t
name|bytes
decl_stmt|;
name|WSABUF
name|wsabuf
index|[
literal|1
index|]
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_event_t
modifier|*
name|rev
decl_stmt|;
name|wsabuf
index|[
literal|0
index|]
operator|.
name|buf
operator|=
name|buf
expr_stmt|;
name|wsabuf
index|[
literal|0
index|]
operator|.
name|len
operator|=
name|size
expr_stmt|;
name|flags
operator|=
literal|0
expr_stmt|;
name|bytes
operator|=
literal|0
expr_stmt|;
name|rc
operator|=
name|WSARecv
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|wsabuf
argument_list|,
literal|1
argument_list|,
operator|&
name|bytes
argument_list|,
operator|&
name|flags
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"WSARecv: %d:%d"
argument|_ rc _ bytes
argument_list|)
empty_stmt|;
name|rev
operator|=
name|c
operator|->
name|read
expr_stmt|;
if|if
condition|(
name|rc
operator|==
operator|-
literal|1
condition|)
block|{
name|rev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|WSAEWOULDBLOCK
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"WSARecv() EAGAIN"
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|rev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"WSARecv() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|bytes
operator|<
name|size
condition|)
block|{
name|rev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|bytes
operator|==
literal|0
condition|)
block|{
name|rev
operator|->
name|eof
operator|=
literal|1
expr_stmt|;
block|}
return|return
name|bytes
return|;
block|}
end_function

begin_function
DECL|function|ngx_overlapped_wsarecv (ngx_connection_t * c,char * buf,size_t size)
name|ssize_t
name|ngx_overlapped_wsarecv
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|u_int
name|flags
decl_stmt|;
name|size_t
name|bytes
decl_stmt|;
name|WSABUF
name|wsabuf
index|[
literal|1
index|]
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_event_t
modifier|*
name|rev
decl_stmt|;
name|LPWSAOVERLAPPED
name|ovlp
decl_stmt|;
name|rev
operator|=
name|c
operator|->
name|read
expr_stmt|;
if|if
condition|(
operator|!
name|rev
operator|->
name|ready
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"SECOND WSA POST"
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"rev->complete: %d"
argument|_ rev->complete
argument_list|)
empty_stmt|;
if|if
condition|(
name|rev
operator|->
name|complete
condition|)
block|{
name|rev
operator|->
name|complete
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
name|rev
operator|->
name|ovlp
operator|.
name|error
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
name|rev
operator|->
name|ovlp
operator|.
name|error
argument_list|,
literal|"WSARecv() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|rev
operator|->
name|available
return|;
block|}
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
name|rev
operator|->
name|ovlp
argument_list|,
operator|&
name|bytes
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSARecv() or WSAGetOverlappedResult() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|bytes
return|;
block|}
name|ovlp
operator|=
operator|(
name|LPWSAOVERLAPPED
operator|)
operator|&
name|rev
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
name|wsabuf
index|[
literal|0
index|]
operator|.
name|buf
operator|=
name|buf
expr_stmt|;
name|wsabuf
index|[
literal|0
index|]
operator|.
name|len
operator|=
name|size
expr_stmt|;
name|flags
operator|=
literal|0
expr_stmt|;
name|bytes
operator|=
literal|0
expr_stmt|;
name|rc
operator|=
name|WSARecv
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|wsabuf
argument_list|,
literal|1
argument_list|,
operator|&
name|bytes
argument_list|,
operator|&
name|flags
argument_list|,
name|ovlp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|rev
operator|->
name|complete
operator|=
literal|0
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"WSARecv: %d:%d"
argument|_ rc _ bytes
argument_list|)
empty_stmt|;
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
name|ngx_socket_errno
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|WSA_IO_PENDING
condition|)
block|{
name|rev
operator|->
name|active
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
name|rev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"WSARecv() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_IOCP_EVENT
condition|)
block|{
comment|/*          * if a socket was bound with I/O completion port          * then GetQueuedCompletionStatus() would anyway return its status          * despite that WSARecv() was already complete          */
name|rev
operator|->
name|active
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|bytes
operator|==
literal|0
condition|)
block|{
name|rev
operator|->
name|eof
operator|=
literal|1
expr_stmt|;
name|rev
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|rev
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
block|}
name|rev
operator|->
name|active
operator|=
literal|0
expr_stmt|;
return|return
name|bytes
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* DELELTE IT WHEN ABOVE FUNC WOULD BE TESTED */
end_comment

begin_comment
unit|ssize_t ngx_wsarecv(ngx_connection_t *c, char *buf, size_t size) {     int               rc;     u_int             flags;     size_t            bytes;     WSABUF            wsabuf[1];     ngx_err_t         err;     ngx_event_t      *rev;     LPWSAOVERLAPPED   ovlp;      rev = c->read;     bytes = 0;      if ((ngx_event_flags& NGX_USE_AIO_EVENT)&& rev->ready) {         rev->ready = 0;
comment|/* the overlapped WSARecv() completed */
end_comment

begin_comment
unit|if (ngx_event_flags& NGX_USE_IOCP_EVENT) {             if (rev->ovlp.error) {                 ngx_log_error(NGX_LOG_ERR, c->log, rev->ovlp.error,                               "WSARecv() failed");                 return NGX_ERROR;             }              return rev->available;         }          if (WSAGetOverlappedResult(c->fd, (LPWSAOVERLAPPED)&rev->ovlp,&bytes, 0, NULL) == 0) {             err = ngx_socket_errno;             ngx_log_error(NGX_LOG_CRIT, c->log, err,                          "WSARecv() or WSAGetOverlappedResult() failed");              return NGX_ERROR;         }          return bytes;     }      if (ngx_event_flags& NGX_USE_AIO_EVENT) {         ovlp = (LPWSAOVERLAPPED)&c->read->ovlp;         ngx_memzero(ovlp, sizeof(WSAOVERLAPPED));      } else {         ovlp = NULL;     }      wsabuf[0].buf = buf;     wsabuf[0].len = size;     flags = 0;      rc = WSARecv(c->fd, wsabuf, 1,&bytes,&flags, ovlp, NULL);      ngx_log_debug(c->log, "WSARecv: %d:%d" _ rc _ bytes);      if (rc == -1) {         err = ngx_socket_errno;         if (err == WSA_IO_PENDING) {             return NGX_AGAIN;          } else if (err == WSAEWOULDBLOCK) {             ngx_log_error(NGX_LOG_INFO, c->log, err, "WSARecv() EAGAIN");             return NGX_AGAIN;          } else {             ngx_log_error(NGX_LOG_CRIT, c->log, err, "WSARecv() failed");             return NGX_ERROR;         }     }      if (ngx_event_flags& NGX_USE_IOCP_EVENT) {
comment|/*          * If a socket was bound with I/O completion port          * then GetQueuedCompletionStatus() would anyway return its status          * despite that WSARecv() was already completed.          */
end_comment

begin_endif
unit|return NGX_AGAIN;     }      return bytes; }
endif|#
directive|endif
end_endif

end_unit

