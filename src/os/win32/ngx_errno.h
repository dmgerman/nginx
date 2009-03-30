begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_ERRNO_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_ERRNO_H_INCLUDED_
define|#
directive|define
name|_NGX_ERRNO_H_INCLUDED_
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

begin_typedef
DECL|typedef|ngx_err_t
typedef|typedef
name|DWORD
name|ngx_err_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_errno
define|#
directive|define
name|ngx_errno
value|GetLastError()
end_define

begin_define
DECL|macro|ngx_set_errno (err)
define|#
directive|define
name|ngx_set_errno
parameter_list|(
name|err
parameter_list|)
value|SetLastError(err)
end_define

begin_define
DECL|macro|ngx_socket_errno
define|#
directive|define
name|ngx_socket_errno
value|WSAGetLastError()
end_define

begin_define
DECL|macro|ngx_set_socket_errno (err)
define|#
directive|define
name|ngx_set_socket_errno
parameter_list|(
name|err
parameter_list|)
value|WSASetLastError(err)
end_define

begin_define
DECL|macro|NGX_EPERM
define|#
directive|define
name|NGX_EPERM
value|ERROR_ACCESS_DENIED
end_define

begin_define
DECL|macro|NGX_ENOENT
define|#
directive|define
name|NGX_ENOENT
value|ERROR_FILE_NOT_FOUND
end_define

begin_define
DECL|macro|NGX_ENOMEM
define|#
directive|define
name|NGX_ENOMEM
value|ERROR_NOT_ENOUGH_MEMORY
end_define

begin_define
DECL|macro|NGX_EACCES
define|#
directive|define
name|NGX_EACCES
value|ERROR_ACCESS_DENIED
end_define

begin_comment
comment|/* it's seems that ERROR_FILE_EXISTS is not appropriate error code */
end_comment

begin_define
DECL|macro|NGX_EEXIST
define|#
directive|define
name|NGX_EEXIST
value|ERROR_ALREADY_EXISTS
end_define

begin_comment
comment|/*  * could not found cross volume directory move error code,  * so use ERROR_WRONG_DISK as stub one  */
end_comment

begin_define
DECL|macro|NGX_EXDEV
define|#
directive|define
name|NGX_EXDEV
value|ERROR_WRONG_DISK
end_define

begin_define
DECL|macro|NGX_ENOTDIR
define|#
directive|define
name|NGX_ENOTDIR
value|ERROR_PATH_NOT_FOUND
end_define

begin_define
DECL|macro|NGX_EISDIR
define|#
directive|define
name|NGX_EISDIR
value|ERROR_CANNOT_MAKE
end_define

begin_define
DECL|macro|NGX_ENOSPC
define|#
directive|define
name|NGX_ENOSPC
value|ERROR_DISK_FULL
end_define

begin_define
DECL|macro|NGX_EPIPE
define|#
directive|define
name|NGX_EPIPE
value|EPIPE
end_define

begin_define
DECL|macro|NGX_EAGAIN
define|#
directive|define
name|NGX_EAGAIN
value|WSAEWOULDBLOCK
end_define

begin_define
DECL|macro|NGX_EINPROGRESS
define|#
directive|define
name|NGX_EINPROGRESS
value|WSAEINPROGRESS
end_define

begin_define
DECL|macro|NGX_EADDRINUSE
define|#
directive|define
name|NGX_EADDRINUSE
value|WSAEADDRINUSE
end_define

begin_define
DECL|macro|NGX_ECONNABORTED
define|#
directive|define
name|NGX_ECONNABORTED
value|WSAECONNABORTED
end_define

begin_define
DECL|macro|NGX_ECONNRESET
define|#
directive|define
name|NGX_ECONNRESET
value|WSAECONNRESET
end_define

begin_define
DECL|macro|NGX_ENOTCONN
define|#
directive|define
name|NGX_ENOTCONN
value|WSAENOTCONN
end_define

begin_define
DECL|macro|NGX_ETIMEDOUT
define|#
directive|define
name|NGX_ETIMEDOUT
value|WSAETIMEDOUT
end_define

begin_define
DECL|macro|NGX_ECONNREFUSED
define|#
directive|define
name|NGX_ECONNREFUSED
value|WSAECONNREFUSED
end_define

begin_define
DECL|macro|NGX_ENAMETOOLONG
define|#
directive|define
name|NGX_ENAMETOOLONG
value|ERROR_BAD_PATHNAME
end_define

begin_define
DECL|macro|NGX_ENETDOWN
define|#
directive|define
name|NGX_ENETDOWN
value|WSAENETDOWN
end_define

begin_define
DECL|macro|NGX_ENETUNREACH
define|#
directive|define
name|NGX_ENETUNREACH
value|WSAENETUNREACH
end_define

begin_define
DECL|macro|NGX_EHOSTDOWN
define|#
directive|define
name|NGX_EHOSTDOWN
value|WSAEHOSTDOWN
end_define

begin_define
DECL|macro|NGX_EHOSTUNREACH
define|#
directive|define
name|NGX_EHOSTUNREACH
value|WSAEHOSTUNREACH
end_define

begin_define
DECL|macro|NGX_ENOMOREFILES
define|#
directive|define
name|NGX_ENOMOREFILES
value|ERROR_NO_MORE_FILES
end_define

begin_define
DECL|macro|NGX_EILSEQ
define|#
directive|define
name|NGX_EILSEQ
value|ERROR_NO_UNICODE_TRANSLATION
end_define

begin_define
DECL|macro|NGX_EALREADY
define|#
directive|define
name|NGX_EALREADY
value|WSAEALREADY
end_define

begin_define
DECL|macro|NGX_EINVAL
define|#
directive|define
name|NGX_EINVAL
value|WSAEINVAL
end_define

begin_function_decl
name|u_char
modifier|*
name|ngx_strerror_r
parameter_list|(
name|ngx_err_t
name|err
parameter_list|,
name|u_char
modifier|*
name|errstr
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ERRNO_H_INCLUDED_ */
end_comment

end_unit

