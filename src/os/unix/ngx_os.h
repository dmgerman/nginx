begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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

begin_typedef
DECL|typedef|ngx_recv_pt
typedef|typedef
name|ssize_t
function_decl|(
modifier|*
name|ngx_recv_pt
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_recv_chain_pt
typedef|typedef
name|ssize_t
function_decl|(
modifier|*
name|ngx_recv_chain_pt
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
end_typedef

begin_typedef
DECL|typedef|ngx_send_pt
typedef|typedef
name|ssize_t
function_decl|(
modifier|*
name|ngx_send_pt
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_send_chain_pt
typedef|typedef
name|ngx_chain_t
modifier|*
function_decl|(
modifier|*
name|ngx_send_chain_pt
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|,
name|off_t
name|limit
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon28f6ce450108
typedef|typedef
struct|struct
block|{
DECL|member|recv
name|ngx_recv_pt
name|recv
decl_stmt|;
DECL|member|recv_chain
name|ngx_recv_chain_pt
name|recv_chain
decl_stmt|;
DECL|member|send
name|ngx_send_pt
name|send
decl_stmt|;
DECL|member|send_chain
name|ngx_send_chain_pt
name|send_chain
decl_stmt|;
DECL|member|flags
name|ngx_uint_t
name|flags
decl_stmt|;
DECL|typedef|ngx_os_io_t
block|}
name|ngx_os_io_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_debug_init
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_os_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_os_status
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_daemon
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_posix_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_posix_status
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
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
name|u_char
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
name|ssize_t
name|ngx_unix_send
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_char
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
parameter_list|,
name|off_t
name|limit
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
name|ngx_int_t
name|ngx_ncpu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_int_t
name|ngx_max_sockets
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_inherited_nonblocking
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_tcp_nodelay_and_tcp_nopush
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|ngx_stderr_fileno
define|#
directive|define
name|ngx_stderr_fileno
value|STDERR_FILENO
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_FREEBSD
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_freebsd.h>
end_include

begin_elif
elif|#
directive|elif
operator|(
name|NGX_LINUX
operator|)
end_elif

begin_include
include|#
directive|include
file|<ngx_linux.h>
end_include

begin_elif
elif|#
directive|elif
operator|(
name|NGX_SOLARIS
operator|)
end_elif

begin_include
include|#
directive|include
file|<ngx_solaris.h>
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

