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

begin_decl_stmt
DECL|variable|ngx_max_sockets
name|int
name|ngx_max_sockets
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_os_io
name|ngx_os_io_t
name|ngx_os_io
init|=
block|{
if|#
directive|if
literal|0
block|ngx_unix_recv,     NULL,     NULL,     ngx_freebsd_write_chain
else|#
directive|else
name|NULL
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
endif|#
directive|endif
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_os_init (ngx_log_t * log)
name|int
name|ngx_os_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
if|if
condition|(
name|ngx_init_sockets
argument_list|(
name|log
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

