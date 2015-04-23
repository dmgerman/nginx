begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_LINUX_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_LINUX_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_LINUX_CONFIG_H_INCLUDED_
end_define

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
comment|/* pread(), pwrite(), gethostname() */
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
file|<sys/vfs.h>
end_include

begin_comment
comment|/* statfs() */
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
comment|/* TCP_NODELAY, TCP_CORK */
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

begin_include
include|#
directive|include
file|<time.h>
end_include

begin_comment
comment|/* tzset() */
end_comment

begin_include
include|#
directive|include
file|<malloc.h>
end_include

begin_comment
comment|/* memalign() */
end_comment

begin_include
include|#
directive|include
file|<limits.h>
end_include

begin_comment
comment|/* IOV_MAX */
end_comment

begin_include
include|#
directive|include
file|<sys/ioctl.h>
end_include

begin_include
include|#
directive|include
file|<crypt.h>
end_include

begin_include
include|#
directive|include
file|<sys/utsname.h>
end_include

begin_comment
comment|/* uname() */
end_comment

begin_include
include|#
directive|include
file|<ngx_auto_config.h>
end_include

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
name|NGX_HAVE_SYS_PRCTL_H
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/prctl.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SENDFILE64
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/sendfile.h>
end_include

begin_else
else|#
directive|else
end_else

begin_function_decl
specifier|extern
name|ssize_t
name|sendfile
parameter_list|(
name|int
name|s
parameter_list|,
name|int
name|fd
parameter_list|,
name|int32_t
modifier|*
name|offset
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|NGX_SENDFILE_LIMIT
define|#
directive|define
name|NGX_SENDFILE_LIMIT
value|0x80000000
end_define

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
name|NGX_HAVE_EPOLL
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/epoll.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SYS_EVENTFD_H
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/eventfd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<sys/syscall.h>
end_include

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
file|<linux/aio_abi.h>
end_include

begin_typedef
DECL|typedef|ngx_aiocb_t
typedef|typedef
name|struct
name|iocb
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

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_HAVE_SO_SNDLOWAT
end_ifndef

begin_comment
comment|/* setsockopt(SO_SNDLOWAT) returns ENOPROTOOPT */
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
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_HAVE_OS_SPECIFIC_INIT
define|#
directive|define
name|NGX_HAVE_OS_SPECIFIC_INIT
value|1
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
comment|/* _NGX_LINUX_CONFIG_H_INCLUDED_ */
end_comment

end_unit

