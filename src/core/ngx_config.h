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

begin_include
include|#
directive|include
file|<ngx_auto_config.h>
end_include

begin_comment
comment|/*    auto_conf    ngx_inline inline __inline __inline__ */
end_comment

begin_comment
comment|/* STUB */
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

begin_comment
comment|/* auto_conf */
end_comment

begin_define
DECL|macro|NGX_ALIGN
define|#
directive|define
name|NGX_ALIGN
value|(4 - 1)
end_define

begin_define
DECL|macro|NGX_ALIGN_TYPE
define|#
directive|define
name|NGX_ALIGN_TYPE
value|unsigned
end_define

begin_define
DECL|macro|ngx_align (p)
define|#
directive|define
name|ngx_align
parameter_list|(
name|p
parameter_list|)
value|(char *) (((NGX_ALIGN_TYPE) p + NGX_ALIGN)& ~NGX_ALIGN)
end_define

begin_comment
comment|/* Platform specific: array[NGX_INVALID_ARRAY_INDEX] should cause SIGSEGV */
end_comment

begin_define
DECL|macro|NGX_INVALID_ARRAY_INDEX
define|#
directive|define
name|NGX_INVALID_ARRAY_INDEX
value|0x80000000
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|_WIN32
end_ifdef

begin_define
DECL|macro|WIN32
define|#
directive|define
name|WIN32
value|1
end_define

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
file|<stdarg.h>
end_include

begin_define
DECL|macro|ngx_inline
define|#
directive|define
name|ngx_inline
value|__inline
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

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* POSIX */
end_comment

begin_comment
comment|/* Solaris */
end_comment

begin_if
if|#
directive|if
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
end_if

begin_define
DECL|macro|SOLARIS
define|#
directive|define
name|SOLARIS
value|1
end_define

begin_define
DECL|macro|_FILE_OFFSET_BITS
define|#
directive|define
name|_FILE_OFFSET_BITS
value|64
end_define

begin_comment
DECL|macro|_FILE_OFFSET_BITS
comment|/* should be before sys/types.h */
end_comment

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

begin_include
include|#
directive|include
file|<sys/stropts.h>
end_include

begin_comment
comment|/* INFTIM */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* Solaris */
end_comment

begin_include
include|#
directive|include
file|<unistd.h>
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
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/mman.h>
end_include

begin_include
include|#
directive|include
file|<sys/wait.h>
end_include

begin_include
include|#
directive|include
file|<sys/time.h>
end_include

begin_include
include|#
directive|include
file|<sys/socket.h>
end_include

begin_include
include|#
directive|include
file|<sys/uio.h>
end_include

begin_include
include|#
directive|include
file|<netinet/in.h>
end_include

begin_include
include|#
directive|include
file|<arpa/inet.h>
end_include

begin_include
include|#
directive|include
file|<netdb.h>
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_POLL
end_ifndef

begin_define
DECL|macro|HAVE_POLL
define|#
directive|define
name|HAVE_POLL
value|1
end_define

begin_include
include|#
directive|include
file|<poll.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_DEVPOLL
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/ioctl.h>
end_include

begin_include
include|#
directive|include
file|<sys/devpoll.h>
end_include

begin_comment
comment|/* Solaris, HP/UX */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_AIO
operator|)
end_if

begin_include
include|#
directive|include
file|<aio.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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

begin_comment
comment|/* POSIX */
end_comment

begin_define
DECL|macro|LF
define|#
directive|define
name|LF
value|10
end_define

begin_define
DECL|macro|CR
define|#
directive|define
name|CR
value|13
end_define

begin_define
DECL|macro|CRLF
define|#
directive|define
name|CRLF
value|"\x0d\x0a"
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|INET_ADDRSTRLEN
end_ifndef

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

begin_if
if|#
directive|if
name|defined
name|SO_ACCEPTFILTER
operator|||
name|defined
name|TCP_DEFER_ACCEPT
end_if

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_DEFERRED_ACCEPT
end_ifndef

begin_define
DECL|macro|HAVE_DEFERRED_ACCEPT
define|#
directive|define
name|HAVE_DEFERRED_ACCEPT
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_SELECT
end_ifndef

begin_define
DECL|macro|HAVE_SELECT
define|#
directive|define
name|HAVE_SELECT
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__FreeBSD__
end_ifdef

begin_include
include|#
directive|include
file|<osreldate.h>
end_include

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

begin_comment
comment|/* FreeBSD sendfile */
end_comment

begin_if
if|#
directive|if
name|__FreeBSD_version
operator|>=
literal|300007
end_if

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_FREEBSD_SENDFILE
end_ifndef

begin_define
DECL|macro|HAVE_FREEBSD_SENDFILE
define|#
directive|define
name|HAVE_FREEBSD_SENDFILE
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_FREEBSD_SENDFILE_NBYTES_BUG
end_ifndef

begin_define
DECL|macro|HAVE_FREEBSD_SENDFILE_NBYTES_BUG
define|#
directive|define
name|HAVE_FREEBSD_SENDFILE_NBYTES_BUG
value|2
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
comment|/* FreeBSD sendfile */
end_comment

begin_comment
comment|/* FreeBSD sendfile nbytes bug */
end_comment

begin_if
if|#
directive|if
operator|(
name|__FreeBSD__
operator|==
literal|4
operator|&&
name|__FreeBSD_version
operator|>=
literal|460100
operator|)
expr|\
operator|||
name|__FreeBSD_version
operator|==
literal|460001
expr|\
operator|||
name|__FreeBSD_version
operator|>=
literal|500029
end_if

begin_if
if|#
directive|if
operator|(
name|HAVE_FREEBSD_SENDFILE_NBYTES_BUG
operator|==
literal|2
operator|)
end_if

begin_undef
undef|#
directive|undef
name|HAVE_FREEBSD_SENDFILE_NBYTES_BUG
end_undef

begin_define
DECL|macro|HAVE_FREEBSD_SENDFILE_NBYTES_BUG
define|#
directive|define
name|HAVE_FREEBSD_SENDFILE_NBYTES_BUG
value|0
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
comment|/* FreeBSD sendfile nbytes bug */
end_comment

begin_if
if|#
directive|if
operator|(
name|HAVE_FREEBSD_SENDFILE
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
comment|/* FreeBSD kqueue */
end_comment

begin_if
if|#
directive|if
operator|(
name|__FreeBSD__
operator|==
literal|4
operator|&&
name|__FreeBSD_version
operator|>=
literal|410000
operator|)
expr|\
operator|||
name|__FreeBSD_version
operator|>=
literal|500011
end_if

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_KQUEUE
end_ifndef

begin_define
DECL|macro|HAVE_KQUEUE
define|#
directive|define
name|HAVE_KQUEUE
value|1
end_define

begin_include
include|#
directive|include
file|<sys/event.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* kqueue's NOTE_LOWAT */
end_comment

begin_if
if|#
directive|if
operator|(
name|__FreeBSD__
operator|==
literal|4
operator|&&
name|__FreeBSD_version
operator|>=
literal|430000
operator|)
expr|\
operator|||
name|__FreeBSD_version
operator|>=
literal|500018
end_if

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_LOWAT_EVENT
end_ifndef

begin_define
DECL|macro|HAVE_LOWAT_EVENT
define|#
directive|define
name|HAVE_LOWAT_EVENT
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* FreeBSD kqueue */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __FreeBSD__ */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|__SOME_OS_TEMPLATE__
end_ifdef

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

