begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_POSIX_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_POSIX_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_POSIX_CONFIG_H_INCLUDED_
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HPUX
operator|)
end_if

begin_define
DECL|macro|_XOPEN_SOURCE
define|#
directive|define
name|_XOPEN_SOURCE
end_define

begin_define
DECL|macro|_XOPEN_SOURCE_EXTENDED
define|#
directive|define
name|_XOPEN_SOURCE_EXTENDED
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
name|NGX_TRU64
operator|)
end_if

begin_define
DECL|macro|_REENTRANT
define|#
directive|define
name|_REENTRANT
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__CYGWIN__
end_ifdef

begin_define
DECL|macro|timezonevar
define|#
directive|define
name|timezonevar
end_define

begin_comment
DECL|macro|timezonevar
comment|/* timezone is variable */
end_comment

begin_define
DECL|macro|NGX_BROKEN_SCM_RIGHTS
define|#
directive|define
name|NGX_BROKEN_SCM_RIGHTS
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_UNISTD_H
operator|)
end_if

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_INTTYPES_H
operator|)
end_if

begin_include
include|#
directive|include
file|<inttypes.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|<glob.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SYS_MOUNT_H
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/mount.h>
end_include

begin_comment
comment|/* statfs() */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SYS_STATVFS_H
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/statvfs.h>
end_include

begin_comment
comment|/* statvfs() */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SYS_FILIO_H
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/filio.h>
end_include

begin_comment
comment|/* FIONBIO */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<sys/ioctl.h>
end_include

begin_comment
comment|/* FIONBIO */
end_comment

begin_include
include|#
directive|include
file|<sys/uio.h>
end_include

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
file|<sched.h>
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
file|<netinet/tcp.h>
end_include

begin_comment
comment|/* TCP_NODELAY */
end_comment

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
file|<sys/un.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_LIMITS_H
operator|)
end_if

begin_include
include|#
directive|include
file|<limits.h>
end_include

begin_comment
comment|/* IOV_MAX */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|__CYGWIN__
end_ifdef

begin_include
include|#
directive|include
file|<malloc.h>
end_include

begin_comment
comment|/* memalign() */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_CRYPT_H
operator|)
end_if

begin_include
include|#
directive|include
file|<crypt.h>
end_include

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
value|16
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_POLL
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
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
name|NGX_HAVE_DEVPOLL
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

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_LISTEN_BACKLOG
define|#
directive|define
name|NGX_LISTEN_BACKLOG
value|511
end_define

begin_if
if|#
directive|if
operator|(
name|__FreeBSD__
operator|)
operator|&&
operator|(
name|__FreeBSD_version
operator|<
literal|400017
operator|)
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
comment|/*  * FreeBSD 3.x has no CMSG_SPACE() and CMSG_LEN() and has the broken CMSG_DATA()  */
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
name|CMSG_LEN
end_undef

begin_define
DECL|macro|CMSG_LEN (l)
define|#
directive|define
name|CMSG_LEN
parameter_list|(
name|l
parameter_list|)
value|(ALIGN(sizeof(struct cmsghdr)) + (l))
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

begin_decl_stmt
specifier|extern
name|char
modifier|*
modifier|*
name|environ
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_POSIX_CONFIG_H_INCLUDED_ */
end_comment

end_unit

