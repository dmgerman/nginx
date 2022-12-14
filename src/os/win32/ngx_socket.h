begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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
DECL|macro|ngx_socket (af,type,proto)
define|#
directive|define
name|ngx_socket
parameter_list|(
name|af
parameter_list|,
name|type
parameter_list|,
name|proto
parameter_list|)
define|\
value|WSASocketW(af, type, proto, NULL, 0, WSA_FLAG_OVERLAPPED)
end_define

begin_define
DECL|macro|ngx_socket_n
define|#
directive|define
name|ngx_socket_n
value|"WSASocketW()"
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

begin_function_decl
name|int
name|ngx_socket_nread
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|,
name|int
modifier|*
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_socket_nread_n
define|#
directive|define
name|ngx_socket_nread_n
value|"ioctlsocket(FIONREAD)"
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
name|WSAID_TRANSMITFILE
end_ifndef

begin_ifndef
ifndef|#
directive|ifndef
name|TF_DISCONNECT
end_ifndef

begin_define
DECL|macro|TF_DISCONNECT
define|#
directive|define
name|TF_DISCONNECT
value|1
end_define

begin_define
DECL|macro|TF_REUSE_SOCKET
define|#
directive|define
name|TF_REUSE_SOCKET
value|2
end_define

begin_define
DECL|macro|TF_WRITE_BEHIND
define|#
directive|define
name|TF_WRITE_BEHIND
value|4
end_define

begin_define
DECL|macro|TF_USE_DEFAULT_WORKER
define|#
directive|define
name|TF_USE_DEFAULT_WORKER
value|0
end_define

begin_define
DECL|macro|TF_USE_SYSTEM_THREAD
define|#
directive|define
name|TF_USE_SYSTEM_THREAD
value|16
end_define

begin_define
DECL|macro|TF_USE_KERNEL_APC
define|#
directive|define
name|TF_USE_KERNEL_APC
value|32
end_define

begin_typedef
DECL|struct|_TRANSMIT_FILE_BUFFERS
typedef|typedef
struct|struct
name|_TRANSMIT_FILE_BUFFERS
block|{
DECL|member|Head
name|LPVOID
name|Head
decl_stmt|;
DECL|member|HeadLength
name|DWORD
name|HeadLength
decl_stmt|;
DECL|member|Tail
name|LPVOID
name|Tail
decl_stmt|;
DECL|member|TailLength
name|DWORD
name|TailLength
decl_stmt|;
DECL|typedef|TRANSMIT_FILE_BUFFERS
DECL|typedef|PTRANSMIT_FILE_BUFFERS
DECL|typedef|LPTRANSMIT_FILE_BUFFERS
block|}
name|TRANSMIT_FILE_BUFFERS
operator|,
typedef|*
name|PTRANSMIT_FILE_BUFFERS
operator|,
name|FAR
modifier|*
name|LPTRANSMIT_FILE_BUFFERS
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

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

begin_ifndef
ifndef|#
directive|ifndef
name|WSAID_TRANSMITPACKETS
end_ifndef

begin_comment
comment|/* OpenWatcom has a swapped TP_ELEMENT_FILE and TP_ELEMENT_MEMORY definition */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|TP_ELEMENT_FILE
end_ifndef

begin_ifdef
ifdef|#
directive|ifdef
name|_MSC_VER
end_ifdef

begin_pragma
pragma|#
directive|pragma
name|warning
name|(
name|disable
name|:
name|4201
name|)
end_pragma

begin_comment
comment|/* Nonstandard extension, nameless struct/union */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|_TRANSMIT_PACKETS_ELEMENT
typedef|typedef
struct|struct
name|_TRANSMIT_PACKETS_ELEMENT
block|{
DECL|member|dwElFlags
name|ULONG
name|dwElFlags
decl_stmt|;
DECL|macro|TP_ELEMENT_MEMORY
define|#
directive|define
name|TP_ELEMENT_MEMORY
value|1
DECL|macro|TP_ELEMENT_FILE
define|#
directive|define
name|TP_ELEMENT_FILE
value|2
DECL|macro|TP_ELEMENT_EOP
define|#
directive|define
name|TP_ELEMENT_EOP
value|4
DECL|member|cLength
name|ULONG
name|cLength
decl_stmt|;
DECL|union|__anon29a27c8e010a
union|union
block|{
DECL|struct|__anon29a27c8e0208
struct|struct
block|{
DECL|member|nFileOffset
name|LARGE_INTEGER
name|nFileOffset
decl_stmt|;
DECL|member|hFile
name|HANDLE
name|hFile
decl_stmt|;
block|}
struct|;
DECL|member|pBuffer
name|PVOID
name|pBuffer
decl_stmt|;
block|}
union|;
DECL|typedef|TRANSMIT_PACKETS_ELEMENT
DECL|typedef|PTRANSMIT_PACKETS_ELEMENT
block|}
name|TRANSMIT_PACKETS_ELEMENT
operator|,
typedef|*
name|PTRANSMIT_PACKETS_ELEMENT
operator|,
DECL|typedef|LPTRANSMIT_PACKETS_ELEMENT
name|FAR
modifier|*
name|LPTRANSMIT_PACKETS_ELEMENT
typedef|;
end_typedef

begin_ifdef
ifdef|#
directive|ifdef
name|_MSC_VER
end_ifdef

begin_pragma
pragma|#
directive|pragma
name|warning
name|(
name|default
name|:
name|4201
name|)
end_pragma

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|LPFN_TRANSMITPACKETS
typedef|typedef
name|BOOL
function_decl|(
name|PASCAL
name|FAR
modifier|*
name|LPFN_TRANSMITPACKETS
function_decl|)
parameter_list|(
name|SOCKET
name|hSocket
parameter_list|,
name|TRANSMIT_PACKETS_ELEMENT
modifier|*
name|lpPacketArray
parameter_list|,
name|DWORD
name|nElementCount
parameter_list|,
name|DWORD
name|nSendSize
parameter_list|,
name|LPOVERLAPPED
name|lpOverlapped
parameter_list|,
name|DWORD
name|dwFlags
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|WSAID_TRANSMITPACKETS
define|#
directive|define
name|WSAID_TRANSMITPACKETS
define|\
value|{0xd9689da0,0x1f90,0x11d3,{0x99,0x71,0x00,0xc0,0x4f,0x68,0xc8,0x76}}
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|WSAID_CONNECTEX
end_ifndef

begin_typedef
DECL|typedef|LPFN_CONNECTEX
typedef|typedef
name|BOOL
argument_list|(
argument|PASCAL FAR * LPFN_CONNECTEX
argument_list|)
operator|(
name|IN
name|SOCKET
name|s
operator|,
name|IN
specifier|const
expr|struct
name|sockaddr
name|FAR
operator|*
name|name
operator|,
name|IN
name|int
name|namelen
operator|,
name|IN
name|PVOID
name|lpSendBuffer
name|OPTIONAL
operator|,
name|IN
name|DWORD
name|dwSendDataLength
operator|,
name|OUT
name|LPDWORD
name|lpdwBytesSent
operator|,
name|IN
name|LPOVERLAPPED
name|lpOverlapped
operator|)
expr_stmt|;
end_typedef

begin_define
DECL|macro|WSAID_CONNECTEX
define|#
directive|define
name|WSAID_CONNECTEX
define|\
value|{0x25a207b9,0xddf3,0x4660,{0x8e,0xe9,0x76,0xe5,0x8c,0x74,0x06,0x3e}}
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|WSAID_DISCONNECTEX
end_ifndef

begin_typedef
DECL|typedef|LPFN_DISCONNECTEX
typedef|typedef
name|BOOL
function_decl|(
name|PASCAL
name|FAR
modifier|*
name|LPFN_DISCONNECTEX
function_decl|)
parameter_list|(
name|IN
name|SOCKET
name|s
parameter_list|,
name|IN
name|LPOVERLAPPED
name|lpOverlapped
parameter_list|,
name|IN
name|DWORD
name|dwFlags
parameter_list|,
name|IN
name|DWORD
name|dwReserved
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|WSAID_DISCONNECTEX
define|#
directive|define
name|WSAID_DISCONNECTEX
define|\
value|{0x7fda2e11,0x8630,0x436f,{0xa0,0x31,0xf5,0x36,0xa6,0xee,0xc1,0x57}}
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|LPFN_ACCEPTEX
name|ngx_acceptex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|LPFN_GETACCEPTEXSOCKADDRS
name|ngx_getacceptexsockaddrs
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|LPFN_TRANSMITFILE
name|ngx_transmitfile
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|LPFN_TRANSMITPACKETS
name|ngx_transmitpackets
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|LPFN_CONNECTEX
name|ngx_connectex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|LPFN_DISCONNECTEX
name|ngx_disconnectex
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_POLL
operator|&&
operator|!
name|defined
name|POLLIN
operator|)
end_if

begin_comment
comment|/*  * WSAPoll() is only available if _WIN32_WINNT>= 0x0600.  * If it is not available during compilation, we try to  * load it dynamically at runtime.  */
end_comment

begin_define
DECL|macro|NGX_LOAD_WSAPOLL
define|#
directive|define
name|NGX_LOAD_WSAPOLL
value|1
end_define

begin_define
DECL|macro|POLLRDNORM
define|#
directive|define
name|POLLRDNORM
value|0x0100
end_define

begin_define
DECL|macro|POLLRDBAND
define|#
directive|define
name|POLLRDBAND
value|0x0200
end_define

begin_define
DECL|macro|POLLIN
define|#
directive|define
name|POLLIN
value|(POLLRDNORM | POLLRDBAND)
end_define

begin_define
DECL|macro|POLLPRI
define|#
directive|define
name|POLLPRI
value|0x0400
end_define

begin_define
DECL|macro|POLLWRNORM
define|#
directive|define
name|POLLWRNORM
value|0x0010
end_define

begin_define
DECL|macro|POLLOUT
define|#
directive|define
name|POLLOUT
value|(POLLWRNORM)
end_define

begin_define
DECL|macro|POLLWRBAND
define|#
directive|define
name|POLLWRBAND
value|0x0020
end_define

begin_define
DECL|macro|POLLERR
define|#
directive|define
name|POLLERR
value|0x0001
end_define

begin_define
DECL|macro|POLLHUP
define|#
directive|define
name|POLLHUP
value|0x0002
end_define

begin_define
DECL|macro|POLLNVAL
define|#
directive|define
name|POLLNVAL
value|0x0004
end_define

begin_typedef
DECL|struct|pollfd
typedef|typedef
struct|struct
name|pollfd
block|{
DECL|member|fd
name|SOCKET
name|fd
decl_stmt|;
DECL|member|events
name|SHORT
name|events
decl_stmt|;
DECL|member|revents
name|SHORT
name|revents
decl_stmt|;
DECL|typedef|WSAPOLLFD
DECL|typedef|PWSAPOLLFD
DECL|typedef|LPWSAPOLLFD
block|}
name|WSAPOLLFD
operator|,
typedef|*
name|PWSAPOLLFD
operator|,
name|FAR
modifier|*
name|LPWSAPOLLFD
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_wsapoll_pt
typedef|typedef
name|int
function_decl|(
name|WSAAPI
modifier|*
name|ngx_wsapoll_pt
function_decl|)
parameter_list|(
name|LPWSAPOLLFD
name|fdArray
parameter_list|,
name|ULONG
name|fds
parameter_list|,
name|INT
name|timeout
parameter_list|)
function_decl|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_wsapoll_pt
name|WSAPoll
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_have_wsapoll
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|int
name|ngx_tcp_push
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|)
function_decl|;
end_function_decl

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

