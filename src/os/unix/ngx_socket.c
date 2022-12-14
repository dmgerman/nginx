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

begin_comment
comment|/*  * ioctl(FIONBIO) sets a non-blocking mode with the single syscall  * while fcntl(F_SETFL, O_NONBLOCK) needs to learn the current state  * using fcntl(F_GETFL).  *  * ioctl() and fcntl() are syscalls at least in FreeBSD 2.x, Linux 2.2  * and Solaris 7.  *  * ioctl() in Linux 2.4 and 2.6 uses BKL, however, fcntl(F_SETFL) uses it too.  */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_FIONBIO
operator|)
end_if

begin_function
name|int
DECL|function|ngx_nonblocking (ngx_socket_t s)
name|ngx_nonblocking
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|int
name|nb
decl_stmt|;
name|nb
operator|=
literal|1
expr_stmt|;
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
name|int
DECL|function|ngx_blocking (ngx_socket_t s)
name|ngx_blocking
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|int
name|nb
decl_stmt|;
name|nb
operator|=
literal|0
expr_stmt|;
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

begin_if
if|#
directive|if
operator|(
name|NGX_FREEBSD
operator|)
end_if

begin_function
name|int
DECL|function|ngx_tcp_nopush (ngx_socket_t s)
name|ngx_tcp_nopush
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|int
name|tcp_nopush
decl_stmt|;
name|tcp_nopush
operator|=
literal|1
expr_stmt|;
return|return
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_TCP
argument_list|,
name|TCP_NOPUSH
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|tcp_nopush
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|int
DECL|function|ngx_tcp_push (ngx_socket_t s)
name|ngx_tcp_push
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|int
name|tcp_nopush
decl_stmt|;
name|tcp_nopush
operator|=
literal|0
expr_stmt|;
return|return
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_TCP
argument_list|,
name|TCP_NOPUSH
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|tcp_nopush
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_elif
elif|#
directive|elif
operator|(
name|NGX_LINUX
operator|)
end_elif

begin_function
name|int
DECL|function|ngx_tcp_nopush (ngx_socket_t s)
name|ngx_tcp_nopush
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|int
name|cork
decl_stmt|;
name|cork
operator|=
literal|1
expr_stmt|;
return|return
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_TCP
argument_list|,
name|TCP_CORK
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|cork
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_function
name|int
DECL|function|ngx_tcp_push (ngx_socket_t s)
name|ngx_tcp_push
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
name|int
name|cork
decl_stmt|;
name|cork
operator|=
literal|0
expr_stmt|;
return|return
name|setsockopt
argument_list|(
name|s
argument_list|,
name|IPPROTO_TCP
argument_list|,
name|TCP_CORK
argument_list|,
operator|(
specifier|const
name|void
operator|*
operator|)
operator|&
name|cork
argument_list|,
sizeof|sizeof
argument_list|(
name|int
argument_list|)
argument_list|)
return|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_function
name|int
DECL|function|ngx_tcp_nopush (ngx_socket_t s)
name|ngx_tcp_nopush
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
return|return
literal|0
return|;
block|}
end_function

begin_function
name|int
DECL|function|ngx_tcp_push (ngx_socket_t s)
name|ngx_tcp_push
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
return|return
literal|0
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

