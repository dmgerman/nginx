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
file|<ngx_errno.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_sendv.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_function
DECL|function|ngx_sendv (ngx_connection_t * c,ngx_iovec_t * iovec,int n)
name|ssize_t
name|ngx_sendv
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_iovec_t
modifier|*
name|iovec
parameter_list|,
name|int
name|n
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|size_t
name|sent
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
if|#
directive|if
literal|0
comment|/* STUB: WSABUF must be 4-byte aligned. Undocumented WSAEINVAL error */
block_content|ngx_iovec_t iov[10];     ngx_memcpy(iov, iovec, n * sizeof(ngx_iovec_t));
endif|#
directive|endif
name|sent
operator|=
literal|0
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"WSASend: %d, %d, %08x"
argument|_ c->fd _ n _ iovec
argument_list|)
empty_stmt|;
name|rc
operator|=
name|WSASend
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|iovec
argument_list|,
name|n
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
name|ngx_log_debug
argument_list|(
name|c
operator|->
name|log
argument_list|,
literal|"WSASend() done"
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|SOCKET_ERROR
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
literal|"WSASend() eagain"
argument_list|)
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
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
literal|"WSASend() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|sent
return|;
block|}
end_function

end_unit

