begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SENDFILE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SENDFILE_H_INCLUDED_
define|#
directive|define
name|_NGX_SENDFILE_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_sendv.h>
end_include

begin_function_decl
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
name|ngx_file_t
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SENDFILE_H_INCLUDED_ */
end_comment

end_unit

