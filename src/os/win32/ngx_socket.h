begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_define
DECL|macro|NGX_WRITE_SHUTDOWN
define|#
directive|define
name|NGX_WRITE_SHUTDOWN
value|SD_SEND
end_define

begin_define
DECL|macro|INET_ADDRSTRLEN
define|#
directive|define
name|INET_ADDRSTRLEN
value|16
end_define

begin_typedef
DECL|typedef|ngx_socket_t
typedef|typedef
name|SOCKET
name|ngx_socket_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|socklen_t
typedef|typedef
name|int
name|socklen_t
typedef|;
end_typedef

begin_function_decl
name|int
name|ngx_init_sockets
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_socket (af,type,proto,flags)
define|#
directive|define
name|ngx_socket
parameter_list|(
name|af
parameter_list|,
name|type
parameter_list|,
name|proto
parameter_list|,
name|flags
parameter_list|)
define|\
value|WSASocket(af, type, proto, NULL, 0, flags)
end_define

begin_define
DECL|macro|ngx_socket_n
define|#
directive|define
name|ngx_socket_n
value|"WSASocket()"
end_define

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
value|"ioctlsocket(FIONBIO)"
end_define

begin_define
DECL|macro|ngx_blocking_n
define|#
directive|define
name|ngx_blocking_n
value|"ioctlsocket(!FIONBIO)"
end_define

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
value|closesocket
end_define

begin_define
DECL|macro|ngx_close_socket_n
define|#
directive|define
name|ngx_close_socket_n
value|"closesocket()"
end_define

begin_decl_stmt
specifier|extern
name|LPFN_ACCEPTEX
name|acceptex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|LPFN_GETACCEPTEXSOCKADDRS
name|getacceptexsockaddrs
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|LPFN_TRANSMITFILE
name|transmitfile
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SOCKET_H_INCLUDED_ */
end_comment

end_unit

