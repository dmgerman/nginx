begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SOCKET_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SOCKET_H_INCLUDED_
define|#
directive|define
name|_NGX_SOCKET_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_define
DECL|macro|NGX_WRITE_SHUTDOWN
define|#
directive|define
name|NGX_WRITE_SHUTDOWN
value|SHUT_WR
end_define

begin_typedef
DECL|typedef|ngx_socket_t
typedef|typedef
name|int
name|ngx_socket_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_socket
define|#
directive|define
name|ngx_socket
value|socket
end_define

begin_define
DECL|macro|ngx_socket_n
define|#
directive|define
name|ngx_socket_n
value|"socket()"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_FIONBIO
operator|)
end_if

begin_function_decl
name|int
name|ngx_nonblocking
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_blocking
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_nonblocking_n
define|#
directive|define
name|ngx_nonblocking_n
value|"ioctl(FIONBIO)"
end_define

begin_define
DECL|macro|ngx_blocking_n
define|#
directive|define
name|ngx_blocking_n
value|"ioctl(!FIONBIO)"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_nonblocking (s)
define|#
directive|define
name|ngx_nonblocking
parameter_list|(
name|s
parameter_list|)
value|fcntl(s, F_SETFL, O_NONBLOCK)
end_define

begin_define
DECL|macro|ngx_nonblocking_n
define|#
directive|define
name|ngx_nonblocking_n
value|"fcntl(O_NONBLOCK)"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|int
name|ngx_tcp_nopush
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_tcp_push
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_LINUX
operator|)
end_if

begin_define
DECL|macro|ngx_tcp_nopush_n
define|#
directive|define
name|ngx_tcp_nopush_n
value|"setsockopt(TCP_CORK)"
end_define

begin_define
DECL|macro|ngx_tcp_push_n
define|#
directive|define
name|ngx_tcp_push_n
value|"setsockopt(!TCP_CORK)"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_tcp_nopush_n
define|#
directive|define
name|ngx_tcp_nopush_n
value|"setsockopt(TCP_NOPUSH)"
end_define

begin_define
DECL|macro|ngx_tcp_push_n
define|#
directive|define
name|ngx_tcp_push_n
value|"setsockopt(!TCP_NOPUSH)"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_shutdown_socket
define|#
directive|define
name|ngx_shutdown_socket
value|shutdown
end_define

begin_define
DECL|macro|ngx_shutdown_socket_n
define|#
directive|define
name|ngx_shutdown_socket_n
value|"shutdown()"
end_define

begin_define
DECL|macro|ngx_close_socket
define|#
directive|define
name|ngx_close_socket
value|close
end_define

begin_define
DECL|macro|ngx_close_socket_n
define|#
directive|define
name|ngx_close_socket_n
value|"close() socket"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SOCKET_H_INCLUDED_ */
end_comment

end_unit

