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

begin_include
include|#
directive|include
file|<ngx_core.h>
end_include

begin_define
DECL|macro|NGX_WRITE_SHUTDOWN
define|#
directive|define
name|NGX_WRITE_SHUTDOWN
value|SD_SEND
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
value|socket(af, type, proto)
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_define
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

begin_endif
endif|#
directive|endif
end_endif

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

begin_ifndef
ifndef|#
directive|ifndef
name|WSAID_ACCEPTEX
end_ifndef

begin_typedef
DECL|typedef|LPFN_ACCEPTEX
typedef|typedef
name|BOOL
function_decl|(
name|PASCAL
name|FAR
modifier|*
name|LPFN_ACCEPTEX
function_decl|)
parameter_list|(
name|IN
name|SOCKET
name|sListenSocket
parameter_list|,
name|IN
name|SOCKET
name|sAcceptSocket
parameter_list|,
name|IN
name|PVOID
name|lpOutputBuffer
parameter_list|,
name|IN
name|DWORD
name|dwReceiveDataLength
parameter_list|,
name|IN
name|DWORD
name|dwLocalAddressLength
parameter_list|,
name|IN
name|DWORD
name|dwRemoteAddressLength
parameter_list|,
name|OUT
name|LPDWORD
name|lpdwBytesReceived
parameter_list|,
name|IN
name|LPOVERLAPPED
name|lpOverlapped
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|WSAID_ACCEPTEX
define|#
directive|define
name|WSAID_ACCEPTEX
define|\
value|{0xb5367df1,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|WSAID_GETACCEPTEXSOCKADDRS
end_ifndef

begin_typedef
DECL|typedef|LPFN_GETACCEPTEXSOCKADDRS
typedef|typedef
name|VOID
function_decl|(
name|PASCAL
name|FAR
modifier|*
name|LPFN_GETACCEPTEXSOCKADDRS
function_decl|)
parameter_list|(
name|IN
name|PVOID
name|lpOutputBuffer
parameter_list|,
name|IN
name|DWORD
name|dwReceiveDataLength
parameter_list|,
name|IN
name|DWORD
name|dwLocalAddressLength
parameter_list|,
name|IN
name|DWORD
name|dwRemoteAddressLength
parameter_list|,
name|OUT
name|struct
name|sockaddr
modifier|*
modifier|*
name|LocalSockaddr
parameter_list|,
name|OUT
name|LPINT
name|LocalSockaddrLength
parameter_list|,
name|OUT
name|struct
name|sockaddr
modifier|*
modifier|*
name|RemoteSockaddr
parameter_list|,
name|OUT
name|LPINT
name|RemoteSockaddrLength
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|WSAID_GETACCEPTEXSOCKADDRS
define|#
directive|define
name|WSAID_GETACCEPTEXSOCKADDRS
define|\
value|{0xb5367df2,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|LPFN_TRANSMITFILE
end_ifndef

begin_typedef
DECL|typedef|LPFN_TRANSMITFILE
typedef|typedef
name|BOOL
function_decl|(
name|PASCAL
name|FAR
modifier|*
name|LPFN_TRANSMITFILE
function_decl|)
parameter_list|(
name|IN
name|SOCKET
name|hSocket
parameter_list|,
name|IN
name|HANDLE
name|hFile
parameter_list|,
name|IN
name|DWORD
name|nNumberOfBytesToWrite
parameter_list|,
name|IN
name|DWORD
name|nNumberOfBytesPerSend
parameter_list|,
name|IN
name|LPOVERLAPPED
name|lpOverlapped
parameter_list|,
name|IN
name|LPTRANSMIT_FILE_BUFFERS
name|lpTransmitBuffers
parameter_list|,
name|IN
name|DWORD
name|dwReserved
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|WSAID_TRANSMITFILE
define|#
directive|define
name|WSAID_TRANSMITFILE
define|\
value|{0xb5367df0,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}
end_define

begin_endif
endif|#
directive|endif
end_endif

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

begin_function
DECL|function|ngx_tcp_push (ngx_socket_t s)
name|ngx_inline
specifier|static
name|int
name|ngx_tcp_push
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
block|{
return|return
literal|0
return|;
block|}
end_function

begin_define
DECL|macro|ngx_tcp_push_n
define|#
directive|define
name|ngx_tcp_push_n
value|"tcp_push()"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SOCKET_H_INCLUDED_ */
end_comment

end_unit

