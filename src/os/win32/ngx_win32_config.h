begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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
value|0x0400
end_define

begin_define
DECL|macro|_WIN32_WINNT
define|#
directive|define
name|_WIN32_WINNT
value|0x0501
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
comment|/* enable getenv() and gmtime() in msvc8 */
end_comment

begin_define
DECL|macro|_CRT_SECURE_NO_WARNINGS
define|#
directive|define
name|_CRT_SECURE_NO_WARNINGS
end_define

begin_comment
comment|/*  * we need to include<windows.h> explicity before<winsock2.h> because  * the warning 4201 is enabled in<windows.h>  */
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
file|<ws2tcpip.h>
end_include

begin_comment
comment|/* ipv6 */
end_comment

begin_include
include|#
directive|include
file|<mswsock.h>
end_include

begin_include
include|#
directive|include
file|<shellapi.h>
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

begin_include
include|#
directive|include
file|<locale.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__WATCOMC__
end_ifdef

begin_define
DECL|macro|_TIME_T_DEFINED
define|#
directive|define
name|_TIME_T_DEFINED
end_define

begin_typedef
DECL|typedef|time_t
typedef|typedef
name|long
name|time_t
typedef|;
end_typedef

begin_comment
comment|/* OpenWatcom defines time_t as "unsigned long" */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_comment
comment|/* localtime(), strftime() */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|_MSC_VER
end_ifdef

begin_comment
comment|/* the end of the precompiled headers */
end_comment

begin_pragma
pragma|#
directive|pragma
name|hdrstop
end_pragma

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
comment|/* disable some "-W4" level warnings */
end_comment

begin_comment
comment|/* 'type cast': from function pointer to data pointer */
end_comment

begin_pragma
pragma|#
directive|pragma
name|warning
name|(
name|disable
name|:
name|4054
name|)
end_pragma

begin_comment
comment|/* 'type cast': from data pointer to function pointer */
end_comment

begin_pragma
pragma|#
directive|pragma
name|warning
name|(
name|disable
name|:
name|4055
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
comment|/* FD_SET() and FD_CLR(): conditional expression is constant */
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

begin_ifdef
ifdef|#
directive|ifdef
name|__WATCOMC__
end_ifdef

begin_comment
comment|/* symbol 'ngx_rbtree_min' has been defined, but not referenced */
end_comment

begin_pragma
pragma|#
directive|pragma
name|disable_message
name|(
name|202
name|)
end_pragma

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__BORLANDC__
end_ifdef

begin_comment
comment|/* the end of the precompiled headers */
end_comment

begin_pragma
pragma|#
directive|pragma
name|hdrstop
end_pragma

begin_comment
comment|/* functions containing (for|while|some if) are not expanded inline */
end_comment

begin_pragma
pragma|#
directive|pragma
name|warn
name|-
name|8027
end_pragma

begin_comment
comment|/* unreferenced formal parameter */
end_comment

begin_pragma
pragma|#
directive|pragma
name|warn
name|-
name|8057
end_pragma

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<ngx_auto_config.h>
end_include

begin_define
DECL|macro|ngx_inline
define|#
directive|define
name|ngx_inline
value|__inline
end_define

begin_define
DECL|macro|ngx_cdecl
define|#
directive|define
name|ngx_cdecl
value|__cdecl
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|_MSC_VER
end_ifdef

begin_typedef
DECL|typedef|uint32_t
typedef|typedef
name|unsigned
name|__int32
name|uint32_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|int32_t
typedef|typedef
name|__int32
name|int32_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|uint16_t
typedef|typedef
name|unsigned
name|__int16
name|uint16_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_libc_cdecl
define|#
directive|define
name|ngx_libc_cdecl
value|__cdecl
end_define

begin_elif
elif|#
directive|elif
name|defined
name|__BORLANDC__
end_elif

begin_typedef
DECL|typedef|uint32_t
typedef|typedef
name|unsigned
name|__int32
name|uint32_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|int32_t
typedef|typedef
name|__int32
name|int32_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|uint16_t
typedef|typedef
name|unsigned
name|__int16
name|uint16_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_libc_cdecl
define|#
directive|define
name|ngx_libc_cdecl
value|__cdecl
end_define

begin_define
DECL|macro|_strnicmp
define|#
directive|define
name|_strnicmp
value|strnicmp
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* __WATCOMC__ */
end_comment

begin_typedef
DECL|typedef|uint32_t
typedef|typedef
name|unsigned
name|int
name|uint32_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|int32_t
typedef|typedef
name|int
name|int32_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|uint16_t
typedef|typedef
name|unsigned
name|short
name|int
name|uint16_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_libc_cdecl
define|#
directive|define
name|ngx_libc_cdecl
end_define

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
DECL|typedef|intptr_t
typedef|typedef
name|int
name|intptr_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|uintptr_t
typedef|typedef
name|u_int
name|uintptr_t
typedef|;
end_typedef

begin_comment
comment|/* Windows defines off_t as long, which is 32-bit */
end_comment

begin_typedef
DECL|typedef|off_t
typedef|typedef
name|__int64
name|off_t
typedef|;
end_typedef

begin_define
DECL|macro|_OFF_T_DEFINED
define|#
directive|define
name|_OFF_T_DEFINED
end_define

begin_typedef
DECL|typedef|ssize_t
typedef|typedef
name|int
name|ssize_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|in_addr_t
typedef|typedef
name|uint32_t
name|in_addr_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|in_port_t
typedef|typedef
name|u_short
name|in_port_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|sig_atomic_t
typedef|typedef
name|int
name|sig_atomic_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_PTR_SIZE
define|#
directive|define
name|NGX_PTR_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_SIZE_T_LEN
define|#
directive|define
name|NGX_SIZE_T_LEN
value|sizeof("-2147483648") - 1
end_define

begin_define
DECL|macro|NGX_MAX_SIZE_T_VALUE
define|#
directive|define
name|NGX_MAX_SIZE_T_VALUE
value|2147483647
end_define

begin_define
DECL|macro|NGX_TIME_T_LEN
define|#
directive|define
name|NGX_TIME_T_LEN
value|sizeof("-2147483648") - 1
end_define

begin_define
DECL|macro|NGX_TIME_T_SIZE
define|#
directive|define
name|NGX_TIME_T_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_OFF_T_LEN
define|#
directive|define
name|NGX_OFF_T_LEN
value|sizeof("-9223372036854775807") - 1
end_define

begin_define
DECL|macro|NGX_MAX_OFF_T_VALUE
define|#
directive|define
name|NGX_MAX_OFF_T_VALUE
value|9223372036854775807
end_define

begin_define
DECL|macro|NGX_SIG_ATOMIC_T_SIZE
define|#
directive|define
name|NGX_SIG_ATOMIC_T_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_HAVE_LITTLE_ENDIAN
define|#
directive|define
name|NGX_HAVE_LITTLE_ENDIAN
value|1
end_define

begin_define
DECL|macro|NGX_HAVE_NONALIGNED
define|#
directive|define
name|NGX_HAVE_NONALIGNED
value|1
end_define

begin_define
DECL|macro|NGX_THREADS
define|#
directive|define
name|NGX_THREADS
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
DECL|macro|NGX_LISTEN_BACKLOG
define|#
directive|define
name|NGX_LISTEN_BACKLOG
value|511
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_HAVE_INHERITED_NONBLOCK
end_ifndef

begin_define
DECL|macro|NGX_HAVE_INHERITED_NONBLOCK
define|#
directive|define
name|NGX_HAVE_INHERITED_NONBLOCK
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_HAVE_WIN32_TRANSMITPACKETS
end_ifndef

begin_define
DECL|macro|NGX_HAVE_WIN32_TRANSMITPACKETS
define|#
directive|define
name|NGX_HAVE_WIN32_TRANSMITPACKETS
value|1
end_define

begin_define
DECL|macro|NGX_HAVE_WIN32_TRANSMITFILE
define|#
directive|define
name|NGX_HAVE_WIN32_TRANSMITFILE
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_HAVE_WIN32_TRANSMITFILE
end_ifndef

begin_define
DECL|macro|NGX_HAVE_WIN32_TRANSMITFILE
define|#
directive|define
name|NGX_HAVE_WIN32_TRANSMITFILE
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
name|NGX_HAVE_WIN32_TRANSMITPACKETS
operator|)
operator|||
operator|(
name|NGX_HAVE_WIN32_TRANSMITFILE
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_SENDFILE
define|#
directive|define
name|NGX_HAVE_SENDFILE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_HAVE_SO_SNDLOWAT
end_ifndef

begin_comment
comment|/* setsockopt(SO_SNDLOWAT) returns error WSAENOPROTOOPT */
end_comment

begin_define
DECL|macro|NGX_HAVE_SO_SNDLOWAT
define|#
directive|define
name|NGX_HAVE_SO_SNDLOWAT
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_random
define|#
directive|define
name|ngx_random
value|rand
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_WIN32_CONFIG_H_INCLUDED_ */
end_comment

end_unit

