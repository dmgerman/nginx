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
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_files.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_include
include|#
directive|include
file|<ngx_errno.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_include
include|#
directive|include
file|<ngx_sendv.h>
end_include

begin_include
include|#
directive|include
file|<ngx_sendfile.h>
end_include

begin_comment
comment|/*   TODO:        various flags        TransmitPackets */
end_comment

begin_if
if|#
directive|if
operator|(
name|HAVE_WIN32_TRANSMITFILE
operator|)
end_if

begin_function
DECL|function|ngx_sendfile (ngx_connection_t * c,ngx_iovec_t * headers,int hdr_cnt,ngx_fd_t fd,off_t offset,size_t nbytes,ngx_iovec_t * trailers,int trl_cnt,off_t * sent,u_int flags)
name|int
name|ngx_sendfile
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_iovec_t
modifier|*
name|headers
parameter_list|,
name|int
name|hdr_cnt
parameter_list|,
name|ngx_fd_t
name|fd
parameter_list|,
name|off_t
name|offset
parameter_list|,
name|size_t
name|nbytes
parameter_list|,
name|ngx_iovec_t
modifier|*
name|trailers
parameter_list|,
name|int
name|trl_cnt
parameter_list|,
name|off_t
modifier|*
name|sent
parameter_list|,
name|u_int
name|flags
parameter_list|)
block|{
name|int
name|tfrc
decl_stmt|,
name|rc
decl_stmt|;
name|ngx_err_t
name|tf_err
decl_stmt|,
name|err
decl_stmt|;
name|OVERLAPPED
name|olp
decl_stmt|;
name|TRANSMIT_FILE_BUFFERS
name|tfb
decl_stmt|,
modifier|*
name|ptfb
decl_stmt|;
if|#
directive|if
literal|0
block_content|ev = c->write;      if (ev->timedout) {         ngx_set_socket_errno(NGX_ETIMEDOUT);         ngx_log_error(NGX_LOG_ERR, ev->log, 0, "TransmitFile() timed out");          return NGX_ERROR;     }      if (ev->ready) {         ev->ready = 0;
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
comment|/* iocp */
block_content|if (ngx_event_flags& NGX_HAVE_IOCP_EVENT) {             if (ev->ovlp.error) {                 ngx_log_error(NGX_LOG_ERR, ev->log, 0, "TransmitFile() failed");                 return NGX_ERROR;             }              return ev->available;             }         }
endif|#
directive|endif
comment|/* TODO: WSAGetOverlappedResult stuff */
block_content|}
endif|#
directive|endif
name|tf_err
operator|=
literal|0
expr_stmt|;
name|err
operator|=
literal|0
expr_stmt|;
name|olp
operator|.
name|Internal
operator|=
literal|0
expr_stmt|;
name|olp
operator|.
name|InternalHigh
operator|=
literal|0
expr_stmt|;
name|olp
operator|.
name|Offset
operator|=
operator|(
name|DWORD
operator|)
name|offset
expr_stmt|;
name|olp
operator|.
name|OffsetHigh
operator|=
operator|(
name|DWORD
operator|)
operator|(
name|offset
operator|>>
literal|32
operator|)
expr_stmt|;
name|olp
operator|.
name|hEvent
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|headers
operator|||
name|trailers
condition|)
block|{
name|tfb
operator|.
name|Head
operator|=
name|headers
operator|->
name|ngx_iov_base
expr_stmt|;
name|tfb
operator|.
name|HeadLength
operator|=
name|headers
operator|->
name|ngx_iov_len
expr_stmt|;
name|tfb
operator|.
name|Tail
operator|=
name|trailers
operator|->
name|ngx_iov_base
expr_stmt|;
name|tfb
operator|.
name|TailLength
operator|=
name|trailers
operator|->
name|ngx_iov_len
expr_stmt|;
name|ptfb
operator|=
operator|&
name|tfb
expr_stmt|;
block|}
else|else
block|{
name|ptfb
operator|=
name|NULL
expr_stmt|;
block|}
if|#
directive|if
literal|1
name|flags
operator|=
name|TF_DISCONNECT
operator||
name|TF_REUSE_SOCKET
expr_stmt|;
name|tfrc
operator|=
name|transmitfile
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
operator|&
name|olp
argument_list|,
name|NULL
argument_list|,
name|flags
argument_list|)
expr_stmt|;
else|#
directive|else
name|tfrc
operator|=
name|TransmitFile
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|fd
argument_list|,
name|nbytes
argument_list|,
literal|0
argument_list|,
operator|&
name|olp
argument_list|,
name|ptfb
argument_list|,
name|flags
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
literal|0
if|#
directive|if
literal|1
block_content|tfrc = TransmitFile(c->fd, fd, nbytes, 0,&olp, ptfb, 0);
else|#
directive|else
block_content|tfrc = TransmitFile(c->fd, fd, nbytes, 0, NULL, ptfb, 0);
endif|#
directive|endif
endif|#
directive|endif
if|if
condition|(
name|tfrc
operator|==
literal|0
condition|)
block|{
name|tf_err
operator|=
name|ngx_socket_errno
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|tf_err
argument_list|,
literal|"ngx_sendfile: TransmitFile failed"
argument_list|)
expr_stmt|;
if|if
condition|(
name|tf_err
operator|==
name|WSA_IO_PENDING
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
block|}
comment|/* set sent */
if|#
directive|if
literal|0
block_content|rc = WSAGetOverlappedResult(c->fd,&olp, (unsigned long *) sent, 0, NULL);
else|#
directive|else
operator|*
name|sent
operator|=
name|olp
operator|.
name|InternalHigh
expr_stmt|;
name|rc
operator|=
literal|1
expr_stmt|;
endif|#
directive|endif
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"TransmitFile: %d, @%I64d %I64d:%d"
argument|_                   tfrc _ offset _ *sent _ nbytes
argument_list|)
empty_stmt|;
if|if
condition|(
name|rc
operator|==
literal|0
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"ngx_sendfile: WSAGetOverlappedResult failed"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|tfrc
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|tf_err
operator|!=
name|NGX_EAGAIN
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
name|tf_err
argument_list|,
literal|"ngx_sendfile: TransmitFile failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|tf_err
argument_list|,
literal|"ngx_sendfile: TransmitFile sent only %I64d bytes"
argument_list|,
operator|*
name|sent
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|rc
operator|==
literal|0
condition|)
return|return
name|NGX_ERROR
return|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

