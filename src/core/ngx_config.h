begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_CONFIG_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_auto_headers.h>
end_include

begin_if
if|#
directive|if
name|defined
name|__DragonFly__
operator|&&
operator|!
name|defined
name|__FreeBSD__
end_if

begin_define
DECL|macro|__FreeBSD__
define|#
directive|define
name|__FreeBSD__
value|4
end_define

begin_define
DECL|macro|__FreeBSD_version
define|#
directive|define
name|__FreeBSD_version
value|480101
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_FREEBSD
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_freebsd_config.h>
end_include

begin_elif
elif|#
directive|elif
operator|(
name|NGX_LINUX
operator|)
end_elif

begin_include
include|#
directive|include
file|<ngx_linux_config.h>
end_include

begin_elif
elif|#
directive|elif
operator|(
name|NGX_SOLARIS
operator|)
end_elif

begin_include
include|#
directive|include
file|<ngx_solaris_config.h>
end_include

begin_elif
elif|#
directive|elif
operator|(
name|NGX_WIN32
operator|)
end_elif

begin_include
include|#
directive|include
file|<ngx_win32_config.h>
end_include

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* POSIX */
end_comment

begin_include
include|#
directive|include
file|<ngx_posix_config.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|!
operator|(
name|NGX_WIN32
operator|)
end_if

begin_define
DECL|macro|ngx_signal_helper (n)
define|#
directive|define
name|ngx_signal_helper
parameter_list|(
name|n
parameter_list|)
value|SIG##n
end_define

begin_define
DECL|macro|ngx_signal_value (n)
define|#
directive|define
name|ngx_signal_value
parameter_list|(
name|n
parameter_list|)
value|ngx_signal_helper(n)
end_define

begin_comment
comment|/* TODO: #ifndef */
end_comment

begin_define
DECL|macro|NGX_SHUTDOWN_SIGNAL
define|#
directive|define
name|NGX_SHUTDOWN_SIGNAL
value|QUIT
end_define

begin_define
DECL|macro|NGX_TERMINATE_SIGNAL
define|#
directive|define
name|NGX_TERMINATE_SIGNAL
value|TERM
end_define

begin_define
DECL|macro|NGX_NOACCEPT_SIGNAL
define|#
directive|define
name|NGX_NOACCEPT_SIGNAL
value|WINCH
end_define

begin_define
DECL|macro|NGX_RECONFIGURE_SIGNAL
define|#
directive|define
name|NGX_RECONFIGURE_SIGNAL
value|HUP
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_LINUXTHREADS
operator|)
end_if

begin_define
DECL|macro|NGX_REOPEN_SIGNAL
define|#
directive|define
name|NGX_REOPEN_SIGNAL
value|INFO
end_define

begin_define
DECL|macro|NGX_CHANGEBIN_SIGNAL
define|#
directive|define
name|NGX_CHANGEBIN_SIGNAL
value|XCPU
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_REOPEN_SIGNAL
define|#
directive|define
name|NGX_REOPEN_SIGNAL
value|USR1
end_define

begin_define
DECL|macro|NGX_CHANGEBIN_SIGNAL
define|#
directive|define
name|NGX_CHANGEBIN_SIGNAL
value|USR2
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
comment|/* TODO: platform specific: array[NGX_INVALID_ARRAY_INDEX] must cause SIGSEGV */
end_comment

begin_define
DECL|macro|NGX_INVALID_ARRAY_INDEX
define|#
directive|define
name|NGX_INVALID_ARRAY_INDEX
value|0x80000000
end_define

begin_if
if|#
directive|if
literal|1
end_if

begin_comment
comment|/* STUB: autoconf */
end_comment

begin_typedef
DECL|typedef|ngx_int_t
typedef|typedef
name|int
name|ngx_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_uint_t
typedef|typedef
name|u_int
name|ngx_uint_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_flag_t
typedef|typedef
name|int
name|ngx_flag_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_INT_T_LEN
define|#
directive|define
name|NGX_INT_T_LEN
value|sizeof("-2147483648") - 1
end_define

begin_else
else|#
directive|else
end_else

begin_typedef
DECL|typedef|ngx_int_t
typedef|typedef
name|long
name|ngx_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_uint_t
typedef|typedef
name|u_long
name|ngx_uint_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_flag_t
typedef|typedef
name|long
name|ngx_flag_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_INT_T_LEN
define|#
directive|define
name|NGX_INT_T_LEN
value|sizeof("-9223372036854775808") - 1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* TODO: auto */
end_comment

begin_define
DECL|macro|NGX_INT32_LEN
define|#
directive|define
name|NGX_INT32_LEN
value|sizeof("-2147483648") - 1
end_define

begin_define
DECL|macro|NGX_INT64_LEN
define|#
directive|define
name|NGX_INT64_LEN
value|sizeof("-9223372036854775808") - 1
end_define

begin_define
DECL|macro|NGX_OFF_T_LEN
define|#
directive|define
name|NGX_OFF_T_LEN
value|sizeof("-9223372036854775808") - 1
end_define

begin_define
DECL|macro|NGX_MAX_INT_LEN
define|#
directive|define
name|NGX_MAX_INT_LEN
value|(sizeof("-9223372036854775808") - 1)
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_SOLARIS
operator|)
end_if

begin_comment
comment|/* TODO: auto_conf */
end_comment

begin_define
DECL|macro|NGX_ALIGN
define|#
directive|define
name|NGX_ALIGN
value|(_MAX_ALIGNMENT - 1)
end_define

begin_comment
DECL|macro|NGX_ALIGN
comment|/* platform word */
end_comment

begin_define
DECL|macro|NGX_ALIGN_CAST
define|#
directive|define
name|NGX_ALIGN_CAST
value|(unsigned long)
end_define

begin_comment
DECL|macro|NGX_ALIGN_CAST
comment|/* size of the pointer */
end_comment

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* TODO: auto_conf */
end_comment

begin_define
DECL|macro|NGX_ALIGN
define|#
directive|define
name|NGX_ALIGN
value|(sizeof(unsigned long) - 1)
end_define

begin_comment
DECL|macro|NGX_ALIGN
comment|/* platform word */
end_comment

begin_define
DECL|macro|NGX_ALIGN_CAST
define|#
directive|define
name|NGX_ALIGN_CAST
value|(unsigned long)
end_define

begin_comment
DECL|macro|NGX_ALIGN_CAST
comment|/* size of the pointer */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_align (p)
define|#
directive|define
name|ngx_align
parameter_list|(
name|p
parameter_list|)
value|(char *) ((NGX_ALIGN_CAST p + NGX_ALIGN)& ~NGX_ALIGN)
end_define

begin_comment
comment|/* TODO: auto_conf: ngx_inline   inline __inline __inline__ */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|ngx_inline
end_ifndef

begin_define
DECL|macro|ngx_inline
define|#
directive|define
name|ngx_inline
value|inline
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_ACCEPT_THRESHOLD
define|#
directive|define
name|NGX_ACCEPT_THRESHOLD
value|100
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|INADDR_NONE
end_ifndef

begin_comment
comment|/* Solaris */
end_comment

begin_define
DECL|macro|INADDR_NONE
define|#
directive|define
name|INADDR_NONE
value|((unsigned int) -1)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|INET_ADDRSTRLEN
end_ifndef

begin_comment
comment|/* Win32 */
end_comment

begin_define
DECL|macro|INET_ADDRSTRLEN
define|#
directive|define
name|INET_ADDRSTRLEN
value|16
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_MAXHOSTNAMELEN
define|#
directive|define
name|NGX_MAXHOSTNAMELEN
value|64
end_define

begin_comment
comment|/* #define NGX_MAXHOSTNAMELEN MAXHOSTNAMELEN */
end_comment

begin_if
if|#
directive|if
operator|(
operator|(
name|__GNU__
operator|==
literal|2
operator|)
operator|&&
operator|(
name|__GNUC_MINOR__
operator|<
literal|8
operator|)
operator|)
end_if

begin_define
DECL|macro|NGX_MAX_UINT32_VALUE
define|#
directive|define
name|NGX_MAX_UINT32_VALUE
value|0xffffffffLL
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MAX_UINT32_VALUE
define|#
directive|define
name|NGX_MAX_UINT32_VALUE
value|0xffffffff
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
comment|/* _NGX_CONFIG_H_INCLUDED_ */
end_comment

end_unit

