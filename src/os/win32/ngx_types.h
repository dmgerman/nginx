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

begin_typedef
DECL|typedef|ngx_file_t
typedef|typedef
name|HANDLE
name|ngx_file_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_socket_t
typedef|typedef
name|SOCKET
name|ngx_socket_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|time_t
typedef|typedef
name|long
name|time_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|off_t
typedef|typedef
name|unsigned
name|__int64
name|off_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_TYPES_H_INCLUDED_ */
end_comment

end_unit

