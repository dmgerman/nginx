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

begin_comment
comment|/* STUB */
end_comment

begin_function_decl
name|ssize_t
name|ngx_unix_recv
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_chain_t
modifier|*
name|ngx_writev_chain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_posix_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_posix_post_conf_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* */
end_comment

begin_decl_stmt
DECL|variable|ngx_os_io
name|ngx_os_io_t
name|ngx_os_io
init|=
block|{
name|ngx_unix_recv
block|,
name|NULL
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

