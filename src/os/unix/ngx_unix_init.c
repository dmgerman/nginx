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

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* STUB */
end_comment

begin_comment
unit|ssize_t ngx_unix_recv(ngx_connection_t *c, char *buf, size_t size); ngx_chain_t *ngx_writev_chain(ngx_connection_t *c, ngx_chain_t *in); int ngx_posix_init(ngx_log_t *log); int ngx_posix_post_conf_init(ngx_log_t *log);
comment|/* */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|ngx_os_io
name|ngx_os_io_t
name|ngx_os_io
init|=
block|{
name|ngx_unix_recv
block|,
name|ngx_readv_chain
block|,
name|NULL
block|,
name|ngx_writev_chain
block|,
name|NGX_HAVE_ZEROCOPY
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
return|return
name|ngx_posix_init
argument_list|(
name|log
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_os_post_conf_init (ngx_log_t * log)
name|int
name|ngx_os_post_conf_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
return|return
name|ngx_posix_post_conf_init
argument_list|(
name|log
argument_list|)
return|;
block|}
end_function

end_unit

