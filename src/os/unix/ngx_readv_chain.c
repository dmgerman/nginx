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
DECL|function|ngx_readv_chain (ngx_connection_t * c,ngx_chain_t * chain)
name|ssize_t
name|ngx_readv_chain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|chain
parameter_list|)
block|{
name|char
modifier|*
name|prev
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|struct
name|iovec
modifier|*
name|iov
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_array_t
name|io
decl_stmt|;
name|prev
operator|=
name|NULL
expr_stmt|;
name|iov
operator|=
name|NULL
expr_stmt|;
name|ngx_init_array
argument_list|(
name|io
argument_list|,
name|c
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|iovec
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
comment|/* coalesce the neighbouring hunks */
while|while
condition|(
name|chain
condition|)
block|{
if|if
condition|(
name|prev
operator|==
name|chain
operator|->
name|hunk
operator|->
name|last
condition|)
block|{
name|iov
operator|->
name|iov_len
operator|+=
name|chain
operator|->
name|hunk
operator|->
name|end
operator|-
name|chain
operator|->
name|hunk
operator|->
name|last
expr_stmt|;
block|}
else|else
block|{
name|ngx_test_null
argument_list|(
name|iov
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|io
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|iov
operator|->
name|iov_base
operator|=
name|chain
operator|->
name|hunk
operator|->
name|last
expr_stmt|;
name|iov
operator|->
name|iov_len
operator|=
name|chain
operator|->
name|hunk
operator|->
name|end
operator|-
name|chain
operator|->
name|hunk
operator|->
name|last
expr_stmt|;
block|}
name|prev
operator|=
name|chain
operator|->
name|hunk
operator|->
name|end
expr_stmt|;
name|chain
operator|=
name|chain
operator|->
name|next
expr_stmt|;
block|}
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"recv: %d:%d"
argument|_ io.nelts _ iov->iov_len
argument_list|)
empty_stmt|;
name|n
operator|=
name|readv
argument_list|(
name|c
operator|->
name|fd
argument_list|,
operator|(
expr|struct
name|iovec
operator|*
operator|)
name|io
operator|.
name|elts
argument_list|,
name|io
operator|.
name|nelts
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|eof
operator|=
literal|1
expr_stmt|;
block|}
if|else if
condition|(
name|n
operator|==
operator|-
literal|1
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
name|c
operator|->
name|read
operator|->
name|error
operator|=
literal|1
expr_stmt|;
name|err
operator|=
name|ngx_errno
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
literal|"readv() returned EAGAIN"
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
literal|"readv() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|n
return|;
block|}
end_function

end_unit

