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
file|<ngx_files.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
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
name|ngx_connection_t
modifier|*
name|c
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
name|u_int
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|u_int
name|ngx_sendfile_flags
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SENDFILE_H_INCLUDED_ */
end_comment

end_unit

