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
file|<osreldate.h>
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

begin_endif
endif|#
directive|endif
end_endif

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

begin_comment
comment|/* _NGX_FREEBSD_CONFIG_H_INCLUDED_ */
end_comment

end_unit

