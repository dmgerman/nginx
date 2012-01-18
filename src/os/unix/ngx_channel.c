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
file|<ngx_channel.h>
end_include

begin_function
name|ngx_int_t
DECL|function|ngx_write_channel (ngx_socket_t s,ngx_channel_t * ch,size_t size,ngx_log_t * log)
name|ngx_write_channel
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|,
name|ngx_channel_t
modifier|*
name|ch
parameter_list|,
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|struct
name|iovec
name|iov
index|[
literal|1
index|]
decl_stmt|;
name|struct
name|msghdr
name|msg
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
DECL|union|__anon2a313bb1010a
union|union
block|{
DECL|member|cm
name|struct
name|cmsghdr
name|cm
decl_stmt|;
DECL|member|space
name|char
name|space
index|[
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
index|]
decl_stmt|;
block|}
name|cmsg
union|;
if|if
condition|(
name|ch
operator|->
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|msg
operator|.
name|msg_control
operator|=
name|NULL
expr_stmt|;
name|msg
operator|.
name|msg_controllen
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|msg
operator|.
name|msg_control
operator|=
operator|(
name|caddr_t
operator|)
operator|&
name|cmsg
expr_stmt|;
name|msg
operator|.
name|msg_controllen
operator|=
sizeof|sizeof
argument_list|(
name|cmsg
argument_list|)
expr_stmt|;
name|cmsg
operator|.
name|cm
operator|.
name|cmsg_len
operator|=
name|CMSG_LEN
argument_list|(
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
expr_stmt|;
name|cmsg
operator|.
name|cm
operator|.
name|cmsg_level
operator|=
name|SOL_SOCKET
expr_stmt|;
name|cmsg
operator|.
name|cm
operator|.
name|cmsg_type
operator|=
name|SCM_RIGHTS
expr_stmt|;
comment|/*          * We have to use ngx_memcpy() instead of simple          *   *(int *) CMSG_DATA(&cmsg.cm) = ch->fd;          * because some gcc 4.4 with -O2/3/s optimization issues the warning:          *   dereferencing type-punned pointer will break strict-aliasing rules          *          * Fortunately, gcc with -O1 compiles this ngx_memcpy()          * in the same simple assignment as in the code above          */
name|ngx_memcpy
argument_list|(
name|CMSG_DATA
argument_list|(
operator|&
name|cmsg
operator|.
name|cm
argument_list|)
argument_list|,
operator|&
name|ch
operator|->
name|fd
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|msg
operator|.
name|msg_flags
operator|=
literal|0
expr_stmt|;
else|#
directive|else
if|if
condition|(
name|ch
operator|->
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|msg
operator|.
name|msg_accrights
operator|=
name|NULL
expr_stmt|;
name|msg
operator|.
name|msg_accrightslen
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|msg
operator|.
name|msg_accrights
operator|=
operator|(
name|caddr_t
operator|)
operator|&
name|ch
operator|->
name|fd
expr_stmt|;
name|msg
operator|.
name|msg_accrightslen
operator|=
sizeof|sizeof
argument_list|(
name|int
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|iov
index|[
literal|0
index|]
operator|.
name|iov_base
operator|=
operator|(
name|char
operator|*
operator|)
name|ch
expr_stmt|;
name|iov
index|[
literal|0
index|]
operator|.
name|iov_len
operator|=
name|size
expr_stmt|;
name|msg
operator|.
name|msg_name
operator|=
name|NULL
expr_stmt|;
name|msg
operator|.
name|msg_namelen
operator|=
literal|0
expr_stmt|;
name|msg
operator|.
name|msg_iov
operator|=
name|iov
expr_stmt|;
name|msg
operator|.
name|msg_iovlen
operator|=
literal|1
expr_stmt|;
name|n
operator|=
name|sendmsg
argument_list|(
name|s
argument_list|,
operator|&
name|msg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
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
return|return
name|NGX_AGAIN
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
literal|"sendmsg() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_read_channel (ngx_socket_t s,ngx_channel_t * ch,size_t size,ngx_log_t * log)
name|ngx_read_channel
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|,
name|ngx_channel_t
modifier|*
name|ch
parameter_list|,
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|struct
name|iovec
name|iov
index|[
literal|1
index|]
decl_stmt|;
name|struct
name|msghdr
name|msg
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
DECL|union|__anon2a313bb1020a
union|union
block|{
DECL|member|cm
name|struct
name|cmsghdr
name|cm
decl_stmt|;
DECL|member|space
name|char
name|space
index|[
name|CMSG_SPACE
argument_list|(
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
index|]
decl_stmt|;
block|}
name|cmsg
union|;
else|#
directive|else
name|int
name|fd
decl_stmt|;
endif|#
directive|endif
name|iov
index|[
literal|0
index|]
operator|.
name|iov_base
operator|=
operator|(
name|char
operator|*
operator|)
name|ch
expr_stmt|;
name|iov
index|[
literal|0
index|]
operator|.
name|iov_len
operator|=
name|size
expr_stmt|;
name|msg
operator|.
name|msg_name
operator|=
name|NULL
expr_stmt|;
name|msg
operator|.
name|msg_namelen
operator|=
literal|0
expr_stmt|;
name|msg
operator|.
name|msg_iov
operator|=
name|iov
expr_stmt|;
name|msg
operator|.
name|msg_iovlen
operator|=
literal|1
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
name|msg
operator|.
name|msg_control
operator|=
operator|(
name|caddr_t
operator|)
operator|&
name|cmsg
expr_stmt|;
name|msg
operator|.
name|msg_controllen
operator|=
sizeof|sizeof
argument_list|(
name|cmsg
argument_list|)
expr_stmt|;
else|#
directive|else
name|msg
operator|.
name|msg_accrights
operator|=
operator|(
name|caddr_t
operator|)
operator|&
name|fd
expr_stmt|;
name|msg
operator|.
name|msg_accrightslen
operator|=
sizeof|sizeof
argument_list|(
name|int
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|n
operator|=
name|recvmsg
argument_list|(
name|s
argument_list|,
operator|&
name|msg
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
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
return|return
name|NGX_AGAIN
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
literal|"recvmsg() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"recvmsg() returned zero"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
operator|(
name|size_t
operator|)
name|n
operator|<
sizeof|sizeof
argument_list|(
name|ngx_channel_t
argument_list|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"recvmsg() returned not enough data: %uz"
argument_list|,
name|n
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_MSGHDR_MSG_CONTROL
operator|)
if|if
condition|(
name|ch
operator|->
name|command
operator|==
name|NGX_CMD_OPEN_CHANNEL
condition|)
block|{
if|if
condition|(
name|cmsg
operator|.
name|cm
operator|.
name|cmsg_len
operator|<
operator|(
name|socklen_t
operator|)
name|CMSG_LEN
argument_list|(
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"recvmsg() returned too small ancillary data"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|cmsg
operator|.
name|cm
operator|.
name|cmsg_level
operator|!=
name|SOL_SOCKET
operator|||
name|cmsg
operator|.
name|cm
operator|.
name|cmsg_type
operator|!=
name|SCM_RIGHTS
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"recvmsg() returned invalid ancillary data "
literal|"level %d or type %d"
argument_list|,
name|cmsg
operator|.
name|cm
operator|.
name|cmsg_level
argument_list|,
name|cmsg
operator|.
name|cm
operator|.
name|cmsg_type
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
comment|/* ch->fd = *(int *) CMSG_DATA(&cmsg.cm); */
name|ngx_memcpy
argument_list|(
operator|&
name|ch
operator|->
name|fd
argument_list|,
name|CMSG_DATA
argument_list|(
operator|&
name|cmsg
operator|.
name|cm
argument_list|)
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|msg
operator|.
name|msg_flags
operator|&
operator|(
name|MSG_TRUNC
operator||
name|MSG_CTRUNC
operator|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"recvmsg() truncated data"
argument_list|)
expr_stmt|;
block|}
else|#
directive|else
if|if
condition|(
name|ch
operator|->
name|command
operator|==
name|NGX_CMD_OPEN_CHANNEL
condition|)
block|{
if|if
condition|(
name|msg
operator|.
name|msg_accrightslen
operator|!=
sizeof|sizeof
argument_list|(
name|int
argument_list|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"recvmsg() returned no ancillary data"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ch
operator|->
name|fd
operator|=
name|fd
expr_stmt|;
block|}
endif|#
directive|endif
return|return
name|n
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_add_channel_event (ngx_cycle_t * cycle,ngx_fd_t fd,ngx_int_t event,ngx_event_handler_pt handler)
name|ngx_add_channel_event
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_fd_t
name|fd
parameter_list|,
name|ngx_int_t
name|event
parameter_list|,
name|ngx_event_handler_pt
name|handler
parameter_list|)
block|{
name|ngx_event_t
modifier|*
name|ev
decl_stmt|,
modifier|*
name|rev
decl_stmt|,
modifier|*
name|wev
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|c
operator|=
name|ngx_get_connection
argument_list|(
name|fd
argument_list|,
name|cycle
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
return|return
name|NGX_ERROR
return|;
block|}
name|c
operator|->
name|pool
operator|=
name|cycle
operator|->
name|pool
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
name|rev
operator|->
name|log
operator|=
name|cycle
operator|->
name|log
expr_stmt|;
name|wev
operator|->
name|log
operator|=
name|cycle
operator|->
name|log
expr_stmt|;
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
name|rev
operator|->
name|channel
operator|=
literal|1
expr_stmt|;
name|wev
operator|->
name|channel
operator|=
literal|1
expr_stmt|;
name|ev
operator|=
operator|(
name|event
operator|==
name|NGX_READ_EVENT
operator|)
condition|?
name|rev
else|:
name|wev
expr_stmt|;
name|ev
operator|->
name|handler
operator|=
name|handler
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
name|ngx_free_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
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
name|ev
argument_list|,
name|event
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_free_connection
argument_list|(
name|c
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_close_channel (ngx_fd_t * fd,ngx_log_t * log)
name|ngx_close_channel
parameter_list|(
name|ngx_fd_t
modifier|*
name|fd
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
if|if
condition|(
name|close
argument_list|(
name|fd
index|[
literal|0
index|]
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
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"close() channel failed"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|close
argument_list|(
name|fd
index|[
literal|1
index|]
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
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"close() channel failed"
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

