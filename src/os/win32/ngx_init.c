begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_os_init.h>
end_include

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
operator|&
name|ngx_log
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

