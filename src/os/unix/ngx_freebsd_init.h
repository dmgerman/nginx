begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_FREEBSD_INIT_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_FREEBSD_INIT_H_INCLUDED_
define|#
directive|define
name|_NGX_FREEBSD_INIT_H_INCLUDED_
end_define

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
file|<ngx_os_init.h>
end_include

begin_include
include|#
directive|include
file|<sys/sysctl.h>
end_include

begin_function_decl
name|int
name|ngx_unix_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

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

begin_decl_stmt
specifier|extern
name|int
name|ngx_freebsd_kern_osreldate
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_freebsd_hw_ncpu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_freebsd_net_inet_tcp_sendspace
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_freebsd_sendfile_nbytes_bug
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FREEBSD_INIT_H_INCLUDED_ */
end_comment

end_unit

