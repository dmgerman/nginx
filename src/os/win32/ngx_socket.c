begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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
name|ioctlsocket
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
name|ioctlsocket
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

end_unit

