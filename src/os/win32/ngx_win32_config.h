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

begin_define
DECL|macro|NGX_WIN_NT
define|#
directive|define
name|NGX_WIN_NT
value|200000
end_define

begin_define
DECL|macro|STRICT
define|#
directive|define
name|STRICT
end_define

begin_define
DECL|macro|WIN32_LEAN_AND_MEAN
define|#
directive|define
name|WIN32_LEAN_AND_MEAN
end_define

begin_comment
comment|/*  * we need to include windows.h explicity before winsock2.h because  * warning 4201 is enabled in windows.h  */
end_comment

begin_include
include|#
directive|include
file|<windows.h>
end_include

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

begin_endif
endif|#
directive|endif
end_endif

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
comment|/* offsetof() */
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

begin_comment
comment|/* unreferenced formal parameter */
end_comment

begin_pragma
pragma|#
directive|pragma
name|warning
name|(
name|disable
name|:
name|4100
name|)
end_pragma

begin_comment
comment|/* STUB */
end_comment

begin_pragma
pragma|#
directive|pragma
name|warning
name|(
name|disable
name|:
name|4127
name|)
end_pragma

begin_endif
endif|#
directive|endif
end_endif

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

begin_comment
comment|/* owc have not __int32 */
end_comment

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
name|__int64
name|off_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|in_addr_t
typedef|typedef
name|uint32_t
name|in_addr_t
typedef|;
end_typedef

begin_define
DECL|macro|OFF_T_FMT
define|#
directive|define
name|OFF_T_FMT
value|"%I64d"
end_define

begin_define
DECL|macro|SIZE_T_FMT
define|#
directive|define
name|SIZE_T_FMT
value|"%d"
end_define

begin_define
DECL|macro|SIZE_T_X_FMT
define|#
directive|define
name|SIZE_T_X_FMT
value|"%x"
end_define

begin_define
DECL|macro|PID_T_FMT
define|#
directive|define
name|PID_T_FMT
value|"%d"
end_define

begin_define
DECL|macro|TIME_T_FMT
define|#
directive|define
name|TIME_T_FMT
value|"%lu"
end_define

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

