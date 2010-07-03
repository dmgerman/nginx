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
name|int
name|ngx_err_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_EPERM
define|#
directive|define
name|NGX_EPERM
value|EPERM
end_define

begin_define
DECL|macro|NGX_ENOENT
define|#
directive|define
name|NGX_ENOENT
value|ENOENT
end_define

begin_define
DECL|macro|NGX_ENOPATH
define|#
directive|define
name|NGX_ENOPATH
value|ENOENT
end_define

begin_define
DECL|macro|NGX_ESRCH
define|#
directive|define
name|NGX_ESRCH
value|ESRCH
end_define

begin_define
DECL|macro|NGX_EINTR
define|#
directive|define
name|NGX_EINTR
value|EINTR
end_define

begin_define
DECL|macro|NGX_ECHILD
define|#
directive|define
name|NGX_ECHILD
value|ECHILD
end_define

begin_define
DECL|macro|NGX_ENOMEM
define|#
directive|define
name|NGX_ENOMEM
value|ENOMEM
end_define

begin_define
DECL|macro|NGX_EACCES
define|#
directive|define
name|NGX_EACCES
value|EACCES
end_define

begin_define
DECL|macro|NGX_EBUSY
define|#
directive|define
name|NGX_EBUSY
value|EBUSY
end_define

begin_define
DECL|macro|NGX_EEXIST
define|#
directive|define
name|NGX_EEXIST
value|EEXIST
end_define

begin_define
DECL|macro|NGX_EXDEV
define|#
directive|define
name|NGX_EXDEV
value|EXDEV
end_define

begin_define
DECL|macro|NGX_ENOTDIR
define|#
directive|define
name|NGX_ENOTDIR
value|ENOTDIR
end_define

begin_define
DECL|macro|NGX_EISDIR
define|#
directive|define
name|NGX_EISDIR
value|EISDIR
end_define

begin_define
DECL|macro|NGX_EINVAL
define|#
directive|define
name|NGX_EINVAL
value|EINVAL
end_define

begin_define
DECL|macro|NGX_ENOSPC
define|#
directive|define
name|NGX_ENOSPC
value|ENOSPC
end_define

begin_define
DECL|macro|NGX_EPIPE
define|#
directive|define
name|NGX_EPIPE
value|EPIPE
end_define

begin_define
DECL|macro|NGX_EINPROGRESS
define|#
directive|define
name|NGX_EINPROGRESS
value|EINPROGRESS
end_define

begin_define
DECL|macro|NGX_EADDRINUSE
define|#
directive|define
name|NGX_EADDRINUSE
value|EADDRINUSE
end_define

begin_define
DECL|macro|NGX_ECONNABORTED
define|#
directive|define
name|NGX_ECONNABORTED
value|ECONNABORTED
end_define

begin_define
DECL|macro|NGX_ECONNRESET
define|#
directive|define
name|NGX_ECONNRESET
value|ECONNRESET
end_define

begin_define
DECL|macro|NGX_ENOTCONN
define|#
directive|define
name|NGX_ENOTCONN
value|ENOTCONN
end_define

begin_define
DECL|macro|NGX_ETIMEDOUT
define|#
directive|define
name|NGX_ETIMEDOUT
value|ETIMEDOUT
end_define

begin_define
DECL|macro|NGX_ECONNREFUSED
define|#
directive|define
name|NGX_ECONNREFUSED
value|ECONNREFUSED
end_define

begin_define
DECL|macro|NGX_ENAMETOOLONG
define|#
directive|define
name|NGX_ENAMETOOLONG
value|ENAMETOOLONG
end_define

begin_define
DECL|macro|NGX_ENETDOWN
define|#
directive|define
name|NGX_ENETDOWN
value|ENETDOWN
end_define

begin_define
DECL|macro|NGX_ENETUNREACH
define|#
directive|define
name|NGX_ENETUNREACH
value|ENETUNREACH
end_define

begin_define
DECL|macro|NGX_EHOSTDOWN
define|#
directive|define
name|NGX_EHOSTDOWN
value|EHOSTDOWN
end_define

begin_define
DECL|macro|NGX_EHOSTUNREACH
define|#
directive|define
name|NGX_EHOSTUNREACH
value|EHOSTUNREACH
end_define

begin_define
DECL|macro|NGX_ENOSYS
define|#
directive|define
name|NGX_ENOSYS
value|ENOSYS
end_define

begin_define
DECL|macro|NGX_ECANCELED
define|#
directive|define
name|NGX_ECANCELED
value|ECANCELED
end_define

begin_define
DECL|macro|NGX_EILSEQ
define|#
directive|define
name|NGX_EILSEQ
value|EILSEQ
end_define

begin_define
DECL|macro|NGX_ENOMOREFILES
define|#
directive|define
name|NGX_ENOMOREFILES
value|0
end_define

begin_if
if|#
directive|if
operator|(
name|__hpux__
operator|)
end_if

begin_define
DECL|macro|NGX_EAGAIN
define|#
directive|define
name|NGX_EAGAIN
value|EWOULDBLOCK
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_EAGAIN
define|#
directive|define
name|NGX_EAGAIN
value|EAGAIN
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_errno
define|#
directive|define
name|ngx_errno
value|errno
end_define

begin_define
DECL|macro|ngx_socket_errno
define|#
directive|define
name|ngx_socket_errno
value|errno
end_define

begin_define
DECL|macro|ngx_set_errno (err)
define|#
directive|define
name|ngx_set_errno
parameter_list|(
name|err
parameter_list|)
value|errno = err
end_define

begin_define
DECL|macro|ngx_set_socket_errno (err)
define|#
directive|define
name|ngx_set_socket_errno
parameter_list|(
name|err
parameter_list|)
value|errno = err
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_STRERROR_R
operator|||
name|NGX_HAVE_GNU_STRERROR_R
operator|)
end_if

begin_function_decl
name|u_char
modifier|*
name|ngx_strerror_r
parameter_list|(
name|int
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

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* Solaris and Tru64 UNIX have thread-safe strerror() */
end_comment

begin_define
DECL|macro|ngx_strerror_r (err,errstr,size)
define|#
directive|define
name|ngx_strerror_r
parameter_list|(
name|err
parameter_list|,
name|errstr
parameter_list|,
name|size
parameter_list|)
define|\
value|ngx_cpystrn(errstr, (u_char *) strerror(err), size)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SYS_ERRLIST
operator|)
end_if

begin_define
DECL|macro|ngx_sigsafe_strerror (err)
define|#
directive|define
name|ngx_sigsafe_strerror
parameter_list|(
name|err
parameter_list|)
define|\
value|(err> 0&& err< sys_nerr) ? sys_errlist[err] : "Unknown error"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_sigsafe_strerror (err)
define|#
directive|define
name|ngx_sigsafe_strerror
parameter_list|(
name|err
parameter_list|)
value|""
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ERRNO_H_INCLUDED_ */
end_comment

end_unit

