begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_OS_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_OS_H_INCLUDED_
define|#
directive|define
name|_NGX_OS_H_INCLUDED_
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

begin_define
DECL|macro|NGX_IO_SENDFILE
define|#
directive|define
name|NGX_IO_SENDFILE
value|1
end_define

begin_define
DECL|macro|NGX_IO_ZEROCOPY
define|#
directive|define
name|NGX_IO_ZEROCOPY
value|2
end_define

begin_if
if|#
directive|if
operator|(
name|HAVE_SENDFILE
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_SENDFILE
define|#
directive|define
name|NGX_HAVE_SENDFILE
value|NGX_IO_SENDFILE
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_HAVE_SENDFILE
define|#
directive|define
name|NGX_HAVE_SENDFILE
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_ZEROCOPY
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_ZEROCOPY
define|#
directive|define
name|NGX_HAVE_ZEROCOPY
value|NGX_IO_ZEROCOPY
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_HAVE_ZEROCOPY
define|#
directive|define
name|NGX_HAVE_ZEROCOPY
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon29d352ce0108
typedef|typedef
struct|struct
block|{
DECL|member|recv
name|ssize_t
function_decl|(
modifier|*
name|recv
function_decl|)
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
DECL|member|recv_chain
name|ssize_t
function_decl|(
modifier|*
name|recv_chain
function_decl|)
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
DECL|member|send
name|ssize_t
function_decl|(
modifier|*
name|send
function_decl|)
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
DECL|member|send_chain
name|ngx_chain_t
modifier|*
function_decl|(
modifier|*
name|send_chain
function_decl|)
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
DECL|member|flags
name|int
name|flags
decl_stmt|;
DECL|typedef|ngx_os_io_t
block|}
name|ngx_os_io_t
typedef|;
end_typedef

begin_function_decl
name|int
name|ngx_os_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_daemon
parameter_list|(
name|ngx_log_t
modifier|*
name|log
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
name|ssize_t
name|ngx_readv_chain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|entry
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

begin_decl_stmt
specifier|extern
name|ngx_os_io_t
name|ngx_os_io
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_max_sockets
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_inherited_nonblocking
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|restart
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|rotate
decl_stmt|;
end_decl_stmt

begin_ifdef
ifdef|#
directive|ifdef
name|__FreeBSD__
end_ifdef

begin_include
include|#
directive|include
file|<ngx_freebsd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__linux__
end_ifdef

begin_include
include|#
directive|include
file|<ngx_linux.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_OS_H_INCLUDED_ */
end_comment

end_unit

