begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_WIN32_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_WIN32_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_WIN32_CONFIG_H_INCLUDED_
end_define

begin_define
DECL|macro|WIN32
define|#
directive|define
name|WIN32
value|1
end_define

begin_comment
comment|/* STUB */
end_comment

begin_define
DECL|macro|NGX_WIN_NT
define|#
directive|define
name|NGX_WIN_NT
value|200000
end_define

begin_decl_stmt
specifier|extern
name|int
name|ngx_win32_version
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**/
end_comment

begin_include
include|#
directive|include
file|<winsock2.h>
end_include

begin_include
include|#
directive|include
file|<mswsock.h>
end_include

begin_include
include|#
directive|include
file|<stddef.h>
end_include

begin_comment
comment|/* offsetof */
end_comment

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_define
DECL|macro|ngx_inline
define|#
directive|define
name|ngx_inline
value|__inline
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_else
unit|typedef unsigned __int32  uint32_t;
else|#
directive|else
end_else

begin_typedef
DECL|typedef|uint32_t
typedef|typedef
name|unsigned
name|int
name|uint32_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|int64_t
typedef|typedef
name|__int64
name|int64_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|uint64_t
typedef|typedef
name|unsigned
name|__int64
name|uint64_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|uintptr_t
typedef|typedef
name|u_int
name|uintptr_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ssize_t
typedef|typedef
name|int
name|ssize_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|time_t
typedef|typedef
name|long
name|time_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|off_t
typedef|typedef
name|unsigned
name|__int64
name|off_t
typedef|;
end_typedef

begin_define
DECL|macro|OFF_FMT
define|#
directive|define
name|OFF_FMT
value|"%I64d"
end_define

begin_define
DECL|macro|SIZE_FMT
define|#
directive|define
name|SIZE_FMT
value|"%d"
end_define

begin_define
DECL|macro|SIZEX_FMT
define|#
directive|define
name|SIZEX_FMT
value|"%x"
end_define

begin_define
DECL|macro|PID_FMT
define|#
directive|define
name|PID_FMT
value|"%d"
end_define

begin_define
DECL|macro|TIME_FMT
define|#
directive|define
name|TIME_FMT
value|"%lu"
end_define

begin_comment
comment|/* STUB */
end_comment

begin_typedef
DECL|typedef|u_int32_t
typedef|typedef
name|uint32_t
name|u_int32_t
typedef|;
end_typedef

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_INHERITED_NONBLOCK
end_ifndef

begin_define
DECL|macro|HAVE_INHERITED_NONBLOCK
define|#
directive|define
name|HAVE_INHERITED_NONBLOCK
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_WIN32_TRANSMITPACKETS
end_ifndef

begin_define
DECL|macro|HAVE_WIN32_TRANSMITPACKETS
define|#
directive|define
name|HAVE_WIN32_TRANSMITPACKETS
value|1
end_define

begin_define
DECL|macro|HAVE_WIN32_TRANSMITFILE
define|#
directive|define
name|HAVE_WIN32_TRANSMITFILE
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_WIN32_TRANSMITFILE
end_ifndef

begin_define
DECL|macro|HAVE_WIN32_TRANSMITFILE
define|#
directive|define
name|HAVE_WIN32_TRANSMITFILE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_WIN32_TRANSMITPACKETS
operator|)
operator|||
operator|(
name|HAVE_WIN32_TRANSMITFILE
operator|)
end_if

begin_define
DECL|macro|HAVE_SENDFILE
define|#
directive|define
name|HAVE_SENDFILE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* STUB */
end_comment

begin_define
DECL|macro|HAVE_LITTLE_ENDIAN
define|#
directive|define
name|HAVE_LITTLE_ENDIAN
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_WIN32_CONFIG_H_INCLUDED_ */
end_comment

end_unit

