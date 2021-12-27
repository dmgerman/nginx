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
comment|/*  * Although FreeBSD sendfile() allows to pass a header and a trailer,  * it cannot send a header with a part of the file in one packet until  * FreeBSD 5.3.  Besides, over the fast ethernet connection sendfile()  * may send the partially filled packets, i.e. the 8 file pages may be sent  * as the 11 full 1460-bytes packets, then one incomplete 324-bytes packet,  * and then again the 11 full 1460-bytes packets.  *  * Therefore we use the TCP_NOPUSH option (similar to Linux's TCP_CORK)  * to postpone the sending - it not only sends a header and the first part of  * the file in one packet, but also sends the file pages in the full packets.  *  * But until FreeBSD 4.5 turning TCP_NOPUSH off does not flush a pending  * data that less than MSS, so that data may be sent with 5 second delay.  * So we do not use TCP_NOPUSH on FreeBSD prior to 4.5, although it can be used  * for non-keepalive HTTP connections.  */
end_comment

begin_function
name|ngx_chain_t
modifier|*
DECL|function|ngx_freebsd_sendfile_chain (ngx_connection_t * c,ngx_chain_t * in,off_t limit)
name|ngx_freebsd_sendfile_chain
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
name|flags
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
decl_stmt|,
name|eagain
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE_NODISKIO
operator|)
name|ngx_uint_t
name|ebusy
decl_stmt|;
endif|#
directive|endif
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
decl_stmt|,
name|trailer
decl_stmt|;
name|struct
name|sf_hdtr
name|hdtr
decl_stmt|;
name|struct
name|iovec
name|headers
index|[
name|NGX_IOVS_PREALLOCATE
index|]
decl_stmt|;
name|struct
name|iovec
name|trailers
index|[
name|NGX_IOVS_PREALLOCATE
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
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
if|if
condition|(
operator|(
name|ngx_event_flags
operator|&
name|NGX_USE_KQUEUE_EVENT
operator|)
operator|&&
name|wev
operator|->
name|pending_eof
condition|)
block|{
operator|(
name|void
operator|)
name|ngx_connection_error
argument_list|(
name|c
argument_list|,
name|wev
operator|->
name|kq_errno
argument_list|,
literal|"kevent() reported about an closed connection"
argument_list|)
expr_stmt|;
name|wev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
endif|#
directive|endif
comment|/* the maximum limit size is the maximum size_t value - the page size */
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
name|NGX_MAX_SIZE_T_VALUE
operator|-
name|ngx_pagesize
operator|)
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
name|eagain
operator|=
literal|0
expr_stmt|;
name|flags
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
name|trailer
operator|.
name|iovs
operator|=
name|trailers
expr_stmt|;
name|trailer
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
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE_NODISKIO
operator|)
name|ebusy
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
name|prev_send
operator|=
name|send
expr_stmt|;
comment|/* create the header iovec and coalesce the neighbouring bufs */
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
if|if
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
if|if
condition|(
name|send
operator|<
name|limit
condition|)
block|{
comment|/*                  * create the trailer iovec and coalesce the neighbouring bufs                  */
name|cl
operator|=
name|ngx_output_chain_to_iovec
argument_list|(
operator|&
name|trailer
argument_list|,
name|cl
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
name|trailer
operator|.
name|size
expr_stmt|;
block|}
else|else
block|{
name|trailer
operator|.
name|count
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|ngx_freebsd_use_tcp_nopush
operator|&&
name|c
operator|->
name|tcp_nopush
operator|==
name|NGX_TCP_NOPUSH_UNSET
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
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_socket_errno
expr_stmt|;
comment|/*                      * there is a tiny chance to be interrupted, however,                      * we continue a processing without the TCP_NOPUSH                      */
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
operator|(
name|void
operator|)
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
comment|/*              * sendfile() does unneeded work if sf_hdtr's count is 0,              * but corresponding pointer is not NULL              */
name|hdtr
operator|.
name|headers
operator|=
name|header
operator|.
name|count
condition|?
name|header
operator|.
name|iovs
else|:
name|NULL
expr_stmt|;
name|hdtr
operator|.
name|hdr_cnt
operator|=
name|header
operator|.
name|count
expr_stmt|;
name|hdtr
operator|.
name|trailers
operator|=
name|trailer
operator|.
name|count
condition|?
name|trailer
operator|.
name|iovs
else|:
name|NULL
expr_stmt|;
name|hdtr
operator|.
name|trl_cnt
operator|=
name|trailer
operator|.
name|count
expr_stmt|;
comment|/*              * the "nbytes bug" of the old sendfile() syscall:              * http://bugs.freebsd.org/33771              */
if|if
condition|(
operator|!
name|ngx_freebsd_sendfile_nbytes_bug
condition|)
block|{
name|header
operator|.
name|size
operator|=
literal|0
expr_stmt|;
block|}
name|sent
operator|=
literal|0
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE_NODISKIO
operator|)
name|flags
operator|=
operator|(
name|c
operator|->
name|busy_count
operator|<=
literal|2
operator|)
condition|?
name|SF_NODISKIO
else|:
literal|0
expr_stmt|;
if|if
condition|(
name|file
operator|->
name|file
operator|->
name|directio
condition|)
block|{
name|flags
operator||=
name|SF_NOCACHE
expr_stmt|;
block|}
endif|#
directive|endif
name|rc
operator|=
name|sendfile
argument_list|(
name|file
operator|->
name|file
operator|->
name|fd
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|file
operator|->
name|file_pos
argument_list|,
name|file_size
operator|+
name|header
operator|.
name|size
argument_list|,
operator|&
name|hdtr
argument_list|,
operator|&
name|sent
argument_list|,
name|flags
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
name|eagain
operator|=
literal|1
expr_stmt|;
break|break;
case|case
name|NGX_EINTR
case|:
name|eintr
operator|=
literal|1
expr_stmt|;
break|break;
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE_NODISKIO
operator|)
case|case
name|NGX_EBUSY
case|:
name|ebusy
operator|=
literal|1
expr_stmt|;
break|break;
endif|#
directive|endif
default|default:
name|wev
operator|->
name|error
operator|=
literal|1
expr_stmt|;
operator|(
name|void
operator|)
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
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"sendfile() sent only %O bytes"
argument_list|,
name|sent
argument_list|)
expr_stmt|;
comment|/*              * sendfile() in FreeBSD 3.x-4.x may return value>= 0              * on success, although only 0 is documented              */
block|}
if|else if
condition|(
name|rc
operator|>=
literal|0
operator|&&
name|sent
operator|==
literal|0
condition|)
block|{
comment|/*                  * if rc is OK and sent equal to zero, then someone                  * has truncated the file, so the offset became beyond                  * the end of the file                  */
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
literal|"sendfile() reported that \"%s\" was truncated at %O"
argument_list|,
name|file
operator|->
name|file
operator|->
name|name
operator|.
name|data
argument_list|,
name|file
operator|->
name|file_pos
argument_list|)
expr_stmt|;
return|return
name|NGX_CHAIN_ERROR
return|;
block|}
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
operator|+
name|header
operator|.
name|size
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
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE_NODISKIO
operator|)
if|if
condition|(
name|ebusy
condition|)
block|{
if|if
condition|(
name|sent
operator|==
literal|0
condition|)
block|{
name|c
operator|->
name|busy_count
operator|++
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
literal|"sendfile() busy, count:%d"
argument_list|,
name|c
operator|->
name|busy_count
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|c
operator|->
name|busy_count
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|wev
operator|->
name|posted
condition|)
block|{
name|ngx_delete_posted_event
argument_list|(
name|wev
argument_list|)
expr_stmt|;
block|}
name|ngx_post_event
argument_list|(
name|wev
argument_list|,
operator|&
name|ngx_posted_next_events
argument_list|)
expr_stmt|;
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
name|c
operator|->
name|busy_count
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|eagain
condition|)
block|{
comment|/*              * sendfile() may return EAGAIN, even if it has sent a whole file              * part, it indicates that the successive sendfile() call would              * return EAGAIN right away and would not send anything.              * We use it as a hint.              */
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
name|eintr
condition|)
block|{
name|send
operator|=
name|prev_send
operator|+
name|sent
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

