begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* STUB to allocate a big ngx_connections */
end_comment

begin_undef
undef|#
directive|undef
name|FD_SETSIZE
end_undef

begin_define
define|#
directive|define
name|FD_SETSIZE
value|5000
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
name|defined
name|__FreeBSD__
end_if

begin_include
include|#
directive|include
file|<ngx_freebsd_config.h>
end_include

begin_elif
elif|#
directive|elif
name|defined
name|__linux__
end_elif

begin_include
include|#
directive|include
file|<ngx_linux_config.h>
end_include

begin_comment
comment|/* Solaris */
end_comment

begin_elif
elif|#
directive|elif
name|defined
argument_list|(
name|sun
argument_list|)
operator|&&
operator|(
name|defined
argument_list|(
name|__svr4__
argument_list|)
operator|||
name|defined
argument_list|(
name|__SVR4
argument_list|)
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
name|defined
name|_WIN32
end_elif

begin_comment
comment|/* STUB to allocate a big ngx_connections */
end_comment

begin_undef
undef|#
directive|undef
name|FD_SETSIZE
end_undef

begin_define
DECL|macro|FD_SETSIZE
define|#
directive|define
name|FD_SETSIZE
value|1024
end_define

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
comment|/* posix */
end_comment

begin_include
include|#
directive|include
file|<ngx_auto_config.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_SERVER_ROOT
end_ifndef

begin_define
DECL|macro|NGX_SERVER_ROOT
define|#
directive|define
name|NGX_SERVER_ROOT
value|"./"
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_define
define|#
directive|define
name|NGX_SERVER_ROOT
value|"/usr/local/nginx/"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|!
operator|(
name|WIN32
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
DECL|macro|NGX_TIME_T_LEN
define|#
directive|define
name|NGX_TIME_T_LEN
value|sizeof("-2147483648") - 1
end_define

begin_define
DECL|macro|NGX_OFF_T_LEN
define|#
directive|define
name|NGX_OFF_T_LEN
value|sizeof("-9223372036854775808") - 1
end_define

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

begin_ifndef
ifndef|#
directive|ifndef
name|INFTIM
end_ifndef

begin_comment
comment|/* Linux */
end_comment

begin_define
DECL|macro|INFTIM
define|#
directive|define
name|INFTIM
value|-1
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_CONFIG_H_INCLUDED_ */
end_comment

end_unit

