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
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_include
include|#
directive|include
file|<ngx_sendv.h>
end_include

begin_function
DECL|function|ngx_sendfile (ngx_socket_t s,ngx_iovec_t * headers,int hdr_cnt,ngx_fd_t fd,off_t offset,size_t nbytes,ngx_iovec_t * trailers,int trl_cnt,off_t * sent,ngx_log_t * log)
name|int
name|ngx_sendfile
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|,
name|ngx_iovec_t
modifier|*
name|headers
parameter_list|,
name|int
name|hdr_cnt
parameter_list|,
name|ngx_fd_t
name|fd
parameter_list|,
name|off_t
name|offset
parameter_list|,
name|size_t
name|nbytes
parameter_list|,
name|ngx_iovec_t
modifier|*
name|trailers
parameter_list|,
name|int
name|trl_cnt
parameter_list|,
name|off_t
modifier|*
name|sent
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"ngx_sendfile: sendfile is not implemented"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
end_function

end_unit

