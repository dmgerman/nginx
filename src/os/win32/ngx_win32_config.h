begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_WIN32_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_WIN32_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_WIN32_CONFIG_H_INCLUDED_
end_define

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_WIN32_CONFIG_H_INCLUDED_ */
end_comment

end_unit

