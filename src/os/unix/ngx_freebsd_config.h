begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_FREEBSD_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_FREEBSD_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_FREEBSD_CONFIG_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/time.h>
end_include

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_include
include|#
directive|include
file|<stdarg.h>
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
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<signal.h>
end_include

begin_include
include|#
directive|include
file|<pwd.h>
end_include

begin_include
include|#
directive|include
file|<grp.h>
end_include

begin_include
include|#
directive|include
file|<dirent.h>
end_include

begin_include
include|#
directive|include
file|<sys/uio.h>
end_include

begin_include
include|#
directive|include
file|<sys/filio.h>
end_include

begin_comment
comment|/* FIONBIO */
end_comment

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
end_include

begin_include
include|#
directive|include
file|<sys/wait.h>
end_include

begin_include
include|#
directive|include
file|<sys/mman.h>
end_include

begin_include
include|#
directive|include
file|<sys/resource.h>
end_include

begin_include
include|#
directive|include
file|<sys/socket.h>
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

begin_include
include|#
directive|include
file|<libutil.h>
end_include

begin_comment
comment|/* setproctitle() before 4.1 */
end_comment

begin_include
include|#
directive|include
file|<osreldate.h>
end_include

begin_include
include|#
directive|include
file|<sys/sysctl.h>
end_include

begin_include
include|#
directive|include
file|<netinet/tcp.h>
end_include

begin_comment
comment|/* TCP_NOPUSH */
end_comment

begin_if
if|#
directive|if
name|__FreeBSD_version
operator|<
literal|400017
end_if

begin_include
include|#
directive|include
file|<sys/param.h>
end_include

begin_comment
comment|/* ALIGN() */
end_comment

begin_comment
comment|/* FreeBSD 3.x has no CMSG_SPACE() at all and has the broken CMSG_DATA() */
end_comment

begin_undef
undef|#
directive|undef
name|CMSG_SPACE
end_undef

begin_define
DECL|macro|CMSG_SPACE (l)
define|#
directive|define
name|CMSG_SPACE
parameter_list|(
name|l
parameter_list|)
value|(ALIGN(sizeof(struct cmsghdr)) + ALIGN(l))
end_define

begin_undef
undef|#
directive|undef
name|CMSG_DATA
end_undef

begin_define
DECL|macro|CMSG_DATA (cmsg)
define|#
directive|define
name|CMSG_DATA
parameter_list|(
name|cmsg
parameter_list|)
value|((u_char *)(cmsg) + ALIGN(sizeof(struct cmsghdr)))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<ngx_auto_config.h>
end_include

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

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_POLL
operator|)
end_if

begin_include
include|#
directive|include
file|<poll.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* FreeBSD aio supported via kqueue */
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
literal|500014
end_if

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_AIO
end_ifndef

begin_define
DECL|macro|HAVE_AIO
define|#
directive|define
name|HAVE_AIO
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

begin_if
if|#
directive|if
name|defined
name|SO_ACCEPTFILTER
operator|&&
operator|!
name|defined
name|HAVE_DEFERRED_ACCEPT
end_if

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

begin_if
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/event.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|__FreeBSD_version
operator|<
literal|430000
operator|||
name|__FreeBSD_version
operator|<
literal|500012
operator|)
end_if

begin_function_decl
name|pid_t
name|rfork_thread
parameter_list|(
name|int
name|flags
parameter_list|,
name|void
modifier|*
name|stack
parameter_list|,
name|int
function_decl|(
modifier|*
name|func
function_decl|)
parameter_list|(
name|void
modifier|*
name|arg
parameter_list|)
parameter_list|,
name|void
modifier|*
name|arg
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|IOV_MAX
end_ifndef

begin_define
DECL|macro|IOV_MAX
define|#
directive|define
name|IOV_MAX
value|1024
end_define

begin_endif
endif|#
directive|endif
end_endif

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

begin_define
DECL|macro|ngx_setproctitle
define|#
directive|define
name|ngx_setproctitle
value|setproctitle
end_define

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|malloc_options
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FREEBSD_CONFIG_H_INCLUDED_ */
end_comment

end_unit

