begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_comment
comment|/*    ioctl(FIONBIO) set blocking mode with one syscall only while    fcntl(F_SETFL, ~O_NONBLOCK) need to know previous state    using fcntl(F_GETFL).     ioctl() and fcntl() are syscalls on FreeBSD, Solaris 7/8 and Linux */
end_comment

begin_if
if|#
directive|if
literal|1
end_if

begin_function
DECL|function|ngx_nonblocking (ngx_socket_t s)
name|int
name|ngx_nonblocking
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|unsigned
name|long
name|nb
init|=
literal|1
decl_stmt|;
return|return
name|ioctl
argument_list|(
name|s
argument_list|,
name|FIONBIO
argument_list|,
operator|&
name|nb
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_blocking (ngx_socket_t s)
name|int
name|ngx_blocking
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|unsigned
name|long
name|nb
init|=
literal|0
decl_stmt|;
return|return
name|ioctl
argument_list|(
name|s
argument_list|,
name|FIONBIO
argument_list|,
operator|&
name|nb
argument_list|)
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

