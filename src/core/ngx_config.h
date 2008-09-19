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
name|NGX_DARWIN
operator|)
end_elif

begin_include
include|#
directive|include
file|<ngx_darwin_config.h>
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

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_HAVE_SO_SNDLOWAT
end_ifndef

begin_define
DECL|macro|NGX_HAVE_SO_SNDLOWAT
define|#
directive|define
name|NGX_HAVE_SO_SNDLOWAT
value|1
end_define

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

begin_define
DECL|macro|ngx_random
define|#
directive|define
name|ngx_random
value|random
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

begin_define
DECL|macro|ngx_cdecl
define|#
directive|define
name|ngx_cdecl
end_define

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
DECL|typedef|ngx_int_t
typedef|typedef
name|intptr_t
name|ngx_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_uint_t
typedef|typedef
name|uintptr_t
name|ngx_uint_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_flag_t
typedef|typedef
name|intptr_t
name|ngx_flag_t
typedef|;
end_typedef

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

begin_if
if|#
directive|if
operator|(
name|NGX_PTR_SIZE
operator|==
literal|4
operator|)
end_if

begin_define
DECL|macro|NGX_INT_T_LEN
define|#
directive|define
name|NGX_INT_T_LEN
value|NGX_INT32_LEN
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_INT_T_LEN
define|#
directive|define
name|NGX_INT_T_LEN
value|NGX_INT64_LEN
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_ALIGNMENT
end_ifndef

begin_define
DECL|macro|NGX_ALIGNMENT
define|#
directive|define
name|NGX_ALIGNMENT
value|sizeof(unsigned long)
end_define

begin_comment
DECL|macro|NGX_ALIGNMENT
comment|/* platform word */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_align (d,a)
define|#
directive|define
name|ngx_align
parameter_list|(
name|d
parameter_list|,
name|a
parameter_list|)
value|(((d) + (a - 1))& ~(a - 1))
end_define

begin_define
DECL|macro|ngx_align_ptr (p,a)
define|#
directive|define
name|ngx_align_ptr
parameter_list|(
name|p
parameter_list|,
name|a
parameter_list|)
define|\
value|(u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1))& ~((uintptr_t) a - 1))
end_define

begin_define
DECL|macro|ngx_abort
define|#
directive|define
name|ngx_abort
value|abort
end_define

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

begin_ifdef
ifdef|#
directive|ifdef
name|MAXHOSTNAMELEN
end_ifdef

begin_define
DECL|macro|NGX_MAXHOSTNAMELEN
define|#
directive|define
name|NGX_MAXHOSTNAMELEN
value|MAXHOSTNAMELEN
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MAXHOSTNAMELEN
define|#
directive|define
name|NGX_MAXHOSTNAMELEN
value|256
end_define

begin_endif
endif|#
directive|endif
end_endif

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
value|(uint32_t) 0xffffffffLL
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
value|(uint32_t) 0xffffffff
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

