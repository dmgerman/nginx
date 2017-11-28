begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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

begin_define
DECL|macro|_HPUX_ALT_XOPEN_SOCKET_API
define|#
directive|define
name|_HPUX_ALT_XOPEN_SOCKET_API
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

begin_if
if|#
directive|if
operator|(
name|NGX_GNU_HURD
operator|)
end_if

begin_ifndef
ifndef|#
directive|ifndef
name|_GNU_SOURCE
end_ifndef

begin_define
DECL|macro|_GNU_SOURCE
define|#
directive|define
name|_GNU_SOURCE
end_define

begin_comment
DECL|macro|_GNU_SOURCE
comment|/* accept4() */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|_FILE_OFFSET_BITS
define|#
directive|define
name|_FILE_OFFSET_BITS
value|64
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
file|<ctype.h>
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

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SYS_PARAM_H
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/param.h>
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
name|NGX_HAVE_DLOPEN
operator|)
end_if

begin_include
include|#
directive|include
file|<dlfcn.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_POSIX_SEM
operator|)
end_if

begin_include
include|#
directive|include
file|<semaphore.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
operator|&&
operator|!
operator|(
name|NGX_TEST_BUILD_DEVPOLL
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|)
end_if

begin_include
include|#
directive|include
file|<aio.h>
end_include

begin_typedef
DECL|typedef|ngx_aiocb_t
typedef|typedef
name|struct
name|aiocb
name|ngx_aiocb_t
typedef|;
end_typedef

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

begin_define
DECL|macro|ngx_debug_init ()
define|#
directive|define
name|ngx_debug_init
parameter_list|()
end_define

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

