begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_typedef
DECL|typedef|ngx_err_t
typedef|typedef
name|int
name|ngx_err_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_ENOENT
define|#
directive|define
name|NGX_ENOENT
value|ENOENT
end_define

begin_define
DECL|macro|NGX_EINTR
define|#
directive|define
name|NGX_EINTR
value|EINTR
end_define

begin_define
DECL|macro|NGX_EAGAIN
define|#
directive|define
name|NGX_EAGAIN
value|EWOULDBLOCK
end_define

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
value|ngx_cpystrn(errstr, strerror(err), size) - (errstr)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ERRNO_H_INCLUDED_ */
end_comment

end_unit

