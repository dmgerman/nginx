begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_TYPES_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_TYPES_H_INCLUDED_
define|#
directive|define
name|_NGX_TYPES_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_typedef
DECL|typedef|ngx_fd_t
typedef|typedef
name|int
name|ngx_fd_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_file_info_t
typedef|typedef
name|struct
name|stat
name|ngx_file_info_t
typedef|;
end_typedef

begin_ifdef
ifdef|#
directive|ifdef
name|SOLARIS
end_ifdef

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

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|QD_FMT
define|#
directive|define
name|QD_FMT
value|"%qd"
end_define

begin_define
DECL|macro|QX_FMT
define|#
directive|define
name|QX_FMT
value|"%qx"
end_define

begin_define
DECL|macro|OFF_FMT
define|#
directive|define
name|OFF_FMT
value|"%qd"
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
comment|/* _NGX_TYPES_H_INCLUDED_ */
end_comment

end_unit

