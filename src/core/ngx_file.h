begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_FILE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_FILE_H_INCLUDED_
define|#
directive|define
name|_NGX_FILE_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_files.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_typedef
DECL|typedef|ngx_file_t
typedef|typedef
name|struct
name|ngx_file_s
name|ngx_file_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_file_s
struct|struct
name|ngx_file_s
block|{
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|info
name|ngx_file_info_t
name|info
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|info_valid
name|unsigned
name|info_valid
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
endif|_NGX_FILE_H_INCLUDED_
end_endif

end_unit

