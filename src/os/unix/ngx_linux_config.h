begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_define
DECL|macro|_FILE_OFFSET_BITS
define|#
directive|define
name|_FILE_OFFSET_BITS
value|64
end_define

begin_define
DECL|macro|_LARGEFILE_SOURCE
define|#
directive|define
name|_LARGEFILE_SOURCE
end_define

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
comment|/* offsetof() */
end_comment

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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_include
include|#
directive|include
file|<fcntl.h>
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
file|<limits.h>
end_include

begin_include
include|#
directive|include
file|<time.h>
end_include

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
file|<sys/select.h>
end_include

begin_include
include|#
directive|include
file|<sys/uio.h>
end_include

begin_include
include|#
directive|include
file|<sys/ioctl.h>
end_include

begin_include
include|#
directive|include
file|<sys/resource.h>
end_include

begin_include
include|#
directive|include
file|<sys/sysctl.h>
end_include

begin_include
include|#
directive|include
file|<sys/wait.h>
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
comment|/* TCP_CORK */
end_comment

begin_include
include|#
directive|include
file|<arpa/inet.h>
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
file|<netdb.h>
end_include

begin_include
include|#
directive|include
file|<dirent.h>
end_include

begin_include
include|#
directive|include
file|<ngx_auto_config.h>
end_include

begin_if
if|#
directive|if
operator|(
name|HAVE_PRCTL
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
name|HAVE_SENDFILE64
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

begin_if
if|#
directive|if
operator|(
name|HAVE_EPOLL
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

begin_comment
comment|/* HAVE_EPOLL */
end_comment

begin_if
if|#
directive|if
name|defined
name|TCP_DEFER_ACCEPT
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
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_FIONBIO
end_ifndef

begin_define
DECL|macro|HAVE_FIONBIO
define|#
directive|define
name|HAVE_FIONBIO
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_SELECT_CHANGE_TIMEOUT
end_ifndef

begin_define
DECL|macro|HAVE_SELECT_CHANGE_TIMEOUT
define|#
directive|define
name|HAVE_SELECT_CHANGE_TIMEOUT
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_setproctitle (title)
define|#
directive|define
name|ngx_setproctitle
parameter_list|(
name|title
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_LINUX_CONFIG_H_INCLUDED_ */
end_comment

end_unit

