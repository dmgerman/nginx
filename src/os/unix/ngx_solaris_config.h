begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SOLARIS_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SOLARIS_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_SOLARIS_CONFIG_H_INCLUDED_
end_define

begin_define
DECL|macro|SOLARIS
define|#
directive|define
name|SOLARIS
value|1
end_define

begin_define
DECL|macro|_REENTRANT
define|#
directive|define
name|_REENTRANT
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
comment|/* must be before sys/types.h */
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
file|<strings.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
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
file|<sys/stropts.h>
end_include

begin_comment
comment|/* INFTIM */
end_comment

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

begin_typedef
DECL|typedef|u_int32_t
typedef|typedef
name|uint32_t
name|u_int32_t
typedef|;
end_typedef

begin_define
DECL|macro|QD_FMT
define|#
directive|define
name|QD_FMT
value|"%lld"
end_define

begin_define
DECL|macro|QX_FMT
define|#
directive|define
name|QX_FMT
value|"%llx"
end_define

begin_define
DECL|macro|OFF_FMT
define|#
directive|define
name|OFF_FMT
value|"%lld"
end_define

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SOLARIS_CONFIG_H_INCLUDED_ */
end_comment

end_unit

