begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

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
file|<nginx.h>
end_include

begin_decl_stmt
DECL|variable|ngx_win32_version
name|ngx_uint_t
name|ngx_win32_version
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_ncpu
name|ngx_uint_t
name|ngx_ncpu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_max_wsabufs
name|ngx_uint_t
name|ngx_max_wsabufs
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_max_sockets
name|ngx_int_t
name|ngx_max_sockets
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_inherited_nonblocking
name|ngx_uint_t
name|ngx_inherited_nonblocking
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_tcp_nodelay_and_tcp_nopush
name|ngx_uint_t
name|ngx_tcp_nodelay_and_tcp_nopush
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_unique
name|char
name|ngx_unique
index|[
name|NGX_INT32_LEN
operator|+
literal|1
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_os_io
name|ngx_os_io_t
name|ngx_os_io
init|=
block|{
name|ngx_wsarecv
block|,
name|ngx_wsarecv_chain
block|,
name|ngx_udp_wsarecv
block|,
name|ngx_wsasend
block|,
name|NULL
block|,
name|NULL
block|,
name|ngx_wsasend_chain
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_typedef
DECL|struct|__anon2c2d8dfe0108
typedef|typedef
struct|struct
block|{
DECL|member|wServicePackMinor
name|WORD
name|wServicePackMinor
decl_stmt|;
DECL|member|wSuiteMask
name|WORD
name|wSuiteMask
decl_stmt|;
DECL|member|wProductType
name|BYTE
name|wProductType
decl_stmt|;
DECL|typedef|ngx_osviex_stub_t
block|}
name|ngx_osviex_stub_t
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|osviex
specifier|static
name|u_int
name|osviex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|osvi
specifier|static
name|OSVERSIONINFOEX
name|osvi
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* Should these pointers be per protocol ? */
end_comment

begin_decl_stmt
DECL|variable|ngx_acceptex
name|LPFN_ACCEPTEX
name|ngx_acceptex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_getacceptexsockaddrs
name|LPFN_GETACCEPTEXSOCKADDRS
name|ngx_getacceptexsockaddrs
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_transmitfile
name|LPFN_TRANSMITFILE
name|ngx_transmitfile
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_transmitpackets
name|LPFN_TRANSMITPACKETS
name|ngx_transmitpackets
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_connectex
name|LPFN_CONNECTEX
name|ngx_connectex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_disconnectex
name|LPFN_DISCONNECTEX
name|ngx_disconnectex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ax_guid
specifier|static
name|GUID
name|ax_guid
init|=
name|WSAID_ACCEPTEX
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|as_guid
specifier|static
name|GUID
name|as_guid
init|=
name|WSAID_GETACCEPTEXSOCKADDRS
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tf_guid
specifier|static
name|GUID
name|tf_guid
init|=
name|WSAID_TRANSMITFILE
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tp_guid
specifier|static
name|GUID
name|tp_guid
init|=
name|WSAID_TRANSMITPACKETS
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cx_guid
specifier|static
name|GUID
name|cx_guid
init|=
name|WSAID_CONNECTEX
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|dx_guid
specifier|static
name|GUID
name|dx_guid
init|=
name|WSAID_DISCONNECTEX
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|(
name|NGX_LOAD_WSAPOLL
operator|)
end_if

begin_decl_stmt
DECL|variable|WSAPoll
name|ngx_wsapoll_pt
name|WSAPoll
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_have_wsapoll
name|ngx_uint_t
name|ngx_have_wsapoll
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|ngx_int_t
DECL|function|ngx_os_init (ngx_log_t * log)
name|ngx_os_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|DWORD
name|bytes
decl_stmt|;
name|SOCKET
name|s
decl_stmt|;
name|WSADATA
name|wsd
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_time_t
modifier|*
name|tp
decl_stmt|;
name|ngx_uint_t
name|n
decl_stmt|;
name|SYSTEM_INFO
name|si
decl_stmt|;
comment|/* get Windows version */
name|ngx_memzero
argument_list|(
operator|&
name|osvi
argument_list|,
sizeof|sizeof
argument_list|(
name|OSVERSIONINFOEX
argument_list|)
argument_list|)
expr_stmt|;
name|osvi
operator|.
name|dwOSVersionInfoSize
operator|=
sizeof|sizeof
argument_list|(
name|OSVERSIONINFOEX
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|_MSC_VER
pragma|#
directive|pragma
name|warning
name|(
name|disable
name|:
name|4996
name|)
endif|#
directive|endif
name|osviex
operator|=
name|GetVersionEx
argument_list|(
operator|(
name|OSVERSIONINFO
operator|*
operator|)
operator|&
name|osvi
argument_list|)
expr_stmt|;
if|if
condition|(
name|osviex
operator|==
literal|0
condition|)
block|{
name|osvi
operator|.
name|dwOSVersionInfoSize
operator|=
sizeof|sizeof
argument_list|(
name|OSVERSIONINFOEX
argument_list|)
expr_stmt|;
if|if
condition|(
name|GetVersionEx
argument_list|(
operator|(
name|OSVERSIONINFO
operator|*
operator|)
operator|&
name|osvi
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"GetVersionEx() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
ifdef|#
directive|ifdef
name|_MSC_VER
pragma|#
directive|pragma
name|warning
name|(
name|default
name|:
name|4996
name|)
endif|#
directive|endif
comment|/*      *  Windows 3.1 Win32s   0xxxxx      *      *  Windows 95           140000      *  Windows 98           141000      *  Windows ME           149000      *  Windows NT 3.51      235100      *  Windows NT 4.0       240000      *  Windows NT 4.0 SP5   240050      *  Windows 2000         250000      *  Windows XP           250100      *  Windows 2003         250200      *  Windows Vista/2008   260000      *      *  Windows CE x.x       3xxxxx      */
name|ngx_win32_version
operator|=
name|osvi
operator|.
name|dwPlatformId
operator|*
literal|100000
operator|+
name|osvi
operator|.
name|dwMajorVersion
operator|*
literal|10000
operator|+
name|osvi
operator|.
name|dwMinorVersion
operator|*
literal|100
expr_stmt|;
if|if
condition|(
name|osviex
condition|)
block|{
name|ngx_win32_version
operator|+=
name|osvi
operator|.
name|wServicePackMajor
operator|*
literal|10
operator|+
name|osvi
operator|.
name|wServicePackMinor
expr_stmt|;
block|}
name|GetSystemInfo
argument_list|(
operator|&
name|si
argument_list|)
expr_stmt|;
name|ngx_pagesize
operator|=
name|si
operator|.
name|dwPageSize
expr_stmt|;
name|ngx_allocation_granularity
operator|=
name|si
operator|.
name|dwAllocationGranularity
expr_stmt|;
name|ngx_ncpu
operator|=
name|si
operator|.
name|dwNumberOfProcessors
expr_stmt|;
name|ngx_cacheline_size
operator|=
name|NGX_CPU_CACHE_LINE
expr_stmt|;
for|for
control|(
name|n
operator|=
name|ngx_pagesize
init|;
name|n
operator|>>=
literal|1
condition|;
name|ngx_pagesize_shift
operator|++
control|)
block|{
comment|/* void */
block|}
comment|/* delete default "C" locale for _wcsicmp() */
name|setlocale
argument_list|(
name|LC_ALL
argument_list|,
literal|""
argument_list|)
expr_stmt|;
comment|/* init Winsock */
if|if
condition|(
name|WSAStartup
argument_list|(
name|MAKEWORD
argument_list|(
literal|2
argument_list|,
literal|2
argument_list|)
argument_list|,
operator|&
name|wsd
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSAStartup() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|ngx_win32_version
operator|<
name|NGX_WIN_NT
condition|)
block|{
name|ngx_max_wsabufs
operator|=
literal|16
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
comment|/* STUB: ngx_uint_t max */
name|ngx_max_wsabufs
operator|=
literal|1024
operator|*
literal|1024
expr_stmt|;
comment|/*      * get AcceptEx(), GetAcceptExSockAddrs(), TransmitFile(),      * TransmitPackets(), ConnectEx(), and DisconnectEx() addresses      */
name|s
operator|=
name|ngx_socket
argument_list|(
name|AF_INET
argument_list|,
name|SOCK_STREAM
argument_list|,
name|IPPROTO_IP
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|==
operator|(
name|ngx_socket_t
operator|)
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_socket_n
literal|" failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|WSAIoctl
argument_list|(
name|s
argument_list|,
name|SIO_GET_EXTENSION_FUNCTION_POINTER
argument_list|,
operator|&
name|ax_guid
argument_list|,
sizeof|sizeof
argument_list|(
name|GUID
argument_list|)
argument_list|,
operator|&
name|ngx_acceptex
argument_list|,
sizeof|sizeof
argument_list|(
name|LPFN_ACCEPTEX
argument_list|)
argument_list|,
operator|&
name|bytes
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER, "
literal|"WSAID_ACCEPTEX) failed"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|WSAIoctl
argument_list|(
name|s
argument_list|,
name|SIO_GET_EXTENSION_FUNCTION_POINTER
argument_list|,
operator|&
name|as_guid
argument_list|,
sizeof|sizeof
argument_list|(
name|GUID
argument_list|)
argument_list|,
operator|&
name|ngx_getacceptexsockaddrs
argument_list|,
sizeof|sizeof
argument_list|(
name|LPFN_GETACCEPTEXSOCKADDRS
argument_list|)
argument_list|,
operator|&
name|bytes
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER, "
literal|"WSAID_GETACCEPTEXSOCKADDRS) failed"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|WSAIoctl
argument_list|(
name|s
argument_list|,
name|SIO_GET_EXTENSION_FUNCTION_POINTER
argument_list|,
operator|&
name|tf_guid
argument_list|,
sizeof|sizeof
argument_list|(
name|GUID
argument_list|)
argument_list|,
operator|&
name|ngx_transmitfile
argument_list|,
sizeof|sizeof
argument_list|(
name|LPFN_TRANSMITFILE
argument_list|)
argument_list|,
operator|&
name|bytes
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER, "
literal|"WSAID_TRANSMITFILE) failed"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|WSAIoctl
argument_list|(
name|s
argument_list|,
name|SIO_GET_EXTENSION_FUNCTION_POINTER
argument_list|,
operator|&
name|tp_guid
argument_list|,
sizeof|sizeof
argument_list|(
name|GUID
argument_list|)
argument_list|,
operator|&
name|ngx_transmitpackets
argument_list|,
sizeof|sizeof
argument_list|(
name|LPFN_TRANSMITPACKETS
argument_list|)
argument_list|,
operator|&
name|bytes
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER, "
literal|"WSAID_TRANSMITPACKETS) failed"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|WSAIoctl
argument_list|(
name|s
argument_list|,
name|SIO_GET_EXTENSION_FUNCTION_POINTER
argument_list|,
operator|&
name|cx_guid
argument_list|,
sizeof|sizeof
argument_list|(
name|GUID
argument_list|)
argument_list|,
operator|&
name|ngx_connectex
argument_list|,
sizeof|sizeof
argument_list|(
name|LPFN_CONNECTEX
argument_list|)
argument_list|,
operator|&
name|bytes
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER, "
literal|"WSAID_CONNECTEX) failed"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|WSAIoctl
argument_list|(
name|s
argument_list|,
name|SIO_GET_EXTENSION_FUNCTION_POINTER
argument_list|,
operator|&
name|dx_guid
argument_list|,
sizeof|sizeof
argument_list|(
name|GUID
argument_list|)
argument_list|,
operator|&
name|ngx_disconnectex
argument_list|,
sizeof|sizeof
argument_list|(
name|LPFN_DISCONNECTEX
argument_list|)
argument_list|,
operator|&
name|bytes
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
literal|"WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER, "
literal|"WSAID_DISCONNECTEX) failed"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ngx_close_socket
argument_list|(
name|s
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|ngx_socket_errno
argument_list|,
name|ngx_close_socket_n
literal|" failed"
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_LOAD_WSAPOLL
operator|)
block|{
name|HMODULE
name|hmod
decl_stmt|;
name|hmod
operator|=
name|GetModuleHandle
argument_list|(
literal|"ws2_32.dll"
argument_list|)
expr_stmt|;
if|if
condition|(
name|hmod
operator|==
name|NULL
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"GetModuleHandle(\"ws2_32.dll\") failed"
argument_list|)
expr_stmt|;
goto|goto
name|nopoll
goto|;
block|}
name|WSAPoll
operator|=
operator|(
name|ngx_wsapoll_pt
operator|)
operator|(
name|void
operator|*
operator|)
name|GetProcAddress
argument_list|(
name|hmod
argument_list|,
literal|"WSAPoll"
argument_list|)
expr_stmt|;
if|if
condition|(
name|WSAPoll
operator|==
name|NULL
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"GetProcAddress(\"WSAPoll\") failed"
argument_list|)
expr_stmt|;
goto|goto
name|nopoll
goto|;
block|}
name|ngx_have_wsapoll
operator|=
literal|1
expr_stmt|;
block|}
name|nopoll
label|:
endif|#
directive|endif
if|if
condition|(
name|GetEnvironmentVariable
argument_list|(
literal|"ngx_unique"
argument_list|,
name|ngx_unique
argument_list|,
name|NGX_INT32_LEN
operator|+
literal|1
argument_list|)
operator|!=
literal|0
condition|)
block|{
name|ngx_process
operator|=
name|NGX_PROCESS_WORKER
expr_stmt|;
block|}
else|else
block|{
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|err
operator|!=
name|ERROR_ENVVAR_NOT_FOUND
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
literal|"GetEnvironmentVariable(\"ngx_unique\") failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_sprintf
argument_list|(
operator|(
name|u_char
operator|*
operator|)
name|ngx_unique
argument_list|,
literal|"%P%Z"
argument_list|,
name|ngx_pid
argument_list|)
expr_stmt|;
block|}
name|tp
operator|=
name|ngx_timeofday
argument_list|()
expr_stmt|;
name|srand
argument_list|(
operator|(
name|ngx_pid
operator|<<
literal|16
operator|)
operator|^
operator|(
name|unsigned
operator|)
name|tp
operator|->
name|sec
operator|^
name|tp
operator|->
name|msec
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_os_status (ngx_log_t * log)
name|ngx_os_status
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_osviex_stub_t
modifier|*
name|osviex_stub
decl_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
name|NGINX_VER_BUILD
argument_list|)
expr_stmt|;
if|if
condition|(
name|osviex
condition|)
block|{
comment|/*          * the MSVC 6.0 SP2 defines wSuiteMask and wProductType          * as WORD wReserved[2]          */
name|osviex_stub
operator|=
operator|(
name|ngx_osviex_stub_t
operator|*
operator|)
operator|&
name|osvi
operator|.
name|wServicePackMinor
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"OS: %ud build:%ud, \"%s\", suite:%Xd, type:%ud"
argument_list|,
name|ngx_win32_version
argument_list|,
name|osvi
operator|.
name|dwBuildNumber
argument_list|,
name|osvi
operator|.
name|szCSDVersion
argument_list|,
name|osviex_stub
operator|->
name|wSuiteMask
argument_list|,
name|osviex_stub
operator|->
name|wProductType
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|osvi
operator|.
name|dwPlatformId
operator|==
name|VER_PLATFORM_WIN32_WINDOWS
condition|)
block|{
comment|/* Win9x build */
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"OS: %u build:%ud.%ud.%ud, \"%s\""
argument_list|,
name|ngx_win32_version
argument_list|,
name|osvi
operator|.
name|dwBuildNumber
operator|>>
literal|24
argument_list|,
operator|(
name|osvi
operator|.
name|dwBuildNumber
operator|>>
literal|16
operator|)
operator|&
literal|0xff
argument_list|,
name|osvi
operator|.
name|dwBuildNumber
operator|&
literal|0xffff
argument_list|,
name|osvi
operator|.
name|szCSDVersion
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*              * VER_PLATFORM_WIN32_NT              *              * we do not currently support VER_PLATFORM_WIN32_CE              * and we do not support VER_PLATFORM_WIN32s at all              */
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"OS: %ud build:%ud, \"%s\""
argument_list|,
name|ngx_win32_version
argument_list|,
name|osvi
operator|.
name|dwBuildNumber
argument_list|,
name|osvi
operator|.
name|szCSDVersion
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

