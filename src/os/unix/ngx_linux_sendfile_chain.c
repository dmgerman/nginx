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
DECL|function|ngx_linux_sendfile_chain (ngx_connection_t * c,ngx_chain_t * in)
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
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|char
modifier|*
name|prev
decl_stmt|;
name|off_t
name|fprev
decl_stmt|;
name|size_t
name|size
decl_stmt|,
name|fsize
decl_stmt|,
name|sent
decl_stmt|;
name|ngx_int_t
name|use_cork
decl_stmt|,
name|eintr
decl_stmt|;
name|struct
name|iovec
modifier|*
name|iov
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_hunk_t
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
decl_stmt|,
modifier|*
name|tail
decl_stmt|;
if|#
directive|if
operator|(
name|HAVE_SENDFILE64
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
do|do
block|{
name|file
operator|=
name|NULL
expr_stmt|;
name|fsize
operator|=
literal|0
expr_stmt|;
name|eintr
operator|=
literal|0
expr_stmt|;
name|ngx_init_array
argument_list|(
name|header
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
name|NGX_CHAIN_ERROR
argument_list|)
expr_stmt|;
name|prev
operator|=
name|NULL
expr_stmt|;
name|iov
operator|=
name|NULL
expr_stmt|;
comment|/* create the iovec and coalesce the neighbouring hunks */
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
name|ngx_hunk_special
argument_list|(
name|cl
operator|->
name|hunk
argument_list|)
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
operator|!
name|ngx_hunk_in_memory_only
argument_list|(
name|cl
operator|->
name|hunk
argument_list|)
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|prev
operator|==
name|cl
operator|->
name|hunk
operator|->
name|pos
condition|)
block|{
name|iov
operator|->
name|iov_len
operator|+=
name|cl
operator|->
name|hunk
operator|->
name|last
operator|-
name|cl
operator|->
name|hunk
operator|->
name|pos
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
name|header
argument_list|)
argument_list|,
name|NGX_CHAIN_ERROR
argument_list|)
expr_stmt|;
name|iov
operator|->
name|iov_base
operator|=
name|cl
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
name|iov
operator|->
name|iov_len
operator|=
name|cl
operator|->
name|hunk
operator|->
name|last
operator|-
name|cl
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
block|}
name|prev
operator|=
name|cl
operator|->
name|hunk
operator|->
name|last
expr_stmt|;
block|}
comment|/* set TCP_CORK if there is a header before a file */
if|if
condition|(
operator|!
name|c
operator|->
name|tcp_nopush
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
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
condition|)
block|{
name|c
operator|->
name|tcp_nopush
operator|=
literal|1
expr_stmt|;
name|ngx_log_debug
argument_list|(
name|c
operator|->
name|log
argument_list|,
literal|"CORK"
argument_list|)
expr_stmt|;
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
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
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
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
condition|)
block|{
comment|/* get the file hunk */
name|file
operator|=
name|cl
operator|->
name|hunk
expr_stmt|;
name|fsize
operator|=
operator|(
name|size_t
operator|)
operator|(
name|file
operator|->
name|file_last
operator|-
name|file
operator|->
name|file_pos
operator|)
expr_stmt|;
name|fprev
operator|=
name|file
operator|->
name|file_last
expr_stmt|;
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
comment|/* coalesce the neighbouring file hunks */
while|while
condition|(
name|cl
operator|&&
operator|(
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
operator|)
condition|)
block|{
if|if
condition|(
name|file
operator|->
name|file
operator|->
name|fd
operator|!=
name|cl
operator|->
name|hunk
operator|->
name|file
operator|->
name|fd
operator|||
name|fprev
operator|!=
name|cl
operator|->
name|hunk
operator|->
name|file_pos
condition|)
block|{
break|break;
block|}
name|fsize
operator|+=
operator|(
name|size_t
operator|)
operator|(
name|cl
operator|->
name|hunk
operator|->
name|file_last
operator|-
name|cl
operator|->
name|hunk
operator|->
name|file_pos
operator|)
expr_stmt|;
name|fprev
operator|=
name|cl
operator|->
name|hunk
operator|->
name|file_last
expr_stmt|;
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
block|}
block|}
comment|/*           * the tail is the rest of the chain that exceeded          * a single sendfile() capability          */
name|tail
operator|=
name|cl
expr_stmt|;
if|if
condition|(
name|fsize
condition|)
block|{
if|#
directive|if
operator|(
name|HAVE_SENDFILE64
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
name|fsize
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
literal|"sendfile() EAGAIN"
argument_list|)
expr_stmt|;
block|}
if|else if
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
literal|"sendfile() EINTR"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
if|#
directive|if
operator|(
name|NGX_DEBUG_WRITE_CHAIN
operator|)
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"sendfile: %d, @"
argument|OFF_T_FMT
literal|" %d:%d"
argument|_                           rc _ file->file_pos _ sent _ fsize
argument_list|)
empty_stmt|;
endif|#
directive|endif
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
literal|"writev() EAGAIN"
argument_list|)
expr_stmt|;
block|}
if|else if
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
literal|"writev() EINTR"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
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
if|#
directive|if
operator|(
name|NGX_DEBUG_WRITE_CHAIN
operator|)
name|ngx_log_debug
argument_list|(
argument|c->log
argument_list|,
literal|"writev: %d"
argument|_ sent
argument_list|)
empty_stmt|;
endif|#
directive|endif
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
name|ngx_hunk_special
argument_list|(
name|cl
operator|->
name|hunk
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
name|ngx_hunk_size
argument_list|(
name|cl
operator|->
name|hunk
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
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_IN_MEMORY
condition|)
block|{
name|cl
operator|->
name|hunk
operator|->
name|pos
operator|=
name|cl
operator|->
name|hunk
operator|->
name|last
expr_stmt|;
block|}
if|if
condition|(
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
condition|)
block|{
name|cl
operator|->
name|hunk
operator|->
name|file_pos
operator|=
name|cl
operator|->
name|hunk
operator|->
name|file_last
expr_stmt|;
block|}
continue|continue;
block|}
if|if
condition|(
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_IN_MEMORY
condition|)
block|{
name|cl
operator|->
name|hunk
operator|->
name|pos
operator|+=
name|sent
expr_stmt|;
block|}
if|if
condition|(
name|cl
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
condition|)
block|{
name|cl
operator|->
name|hunk
operator|->
name|file_pos
operator|+=
name|sent
expr_stmt|;
block|}
break|break;
block|}
name|in
operator|=
name|cl
expr_stmt|;
comment|/* "tail == in" means that a single sendfile() is complete */
block|}
do|while
condition|(
operator|(
name|tail
operator|&&
name|tail
operator|==
name|in
operator|)
operator|||
name|eintr
condition|)
do|;
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
return|return
name|in
return|;
block|}
end_function

end_unit

