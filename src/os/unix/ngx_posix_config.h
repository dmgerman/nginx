begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_define
DECL|macro|ngx_setproctitle (title)
define|#
directive|define
name|ngx_setproctitle
parameter_list|(
name|title
parameter_list|)
end_define

begin_define
DECL|macro|NGX_POSIX_IO
define|#
directive|define
name|NGX_POSIX_IO
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_POSIX_CONFIG_H_INCLUDED_ */
end_comment

end_unit

