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
file|<ngx_core.h>
end_include

begin_typedef
DECL|typedef|ngx_fd_t
typedef|typedef
name|HANDLE
name|ngx_fd_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_file_info_t
typedef|typedef
name|BY_HANDLE_FILE_INFORMATION
name|ngx_file_info_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_file_uniq_t
typedef|typedef
name|uint64_t
name|ngx_file_uniq_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28f6dbac0108
typedef|typedef
struct|struct
block|{
DECL|member|dir
name|HANDLE
name|dir
decl_stmt|;
DECL|member|de
name|WIN32_FIND_DATA
name|de
decl_stmt|;
DECL|typedef|ngx_dir_t
block|}
name|ngx_dir_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_dirent_t
typedef|typedef
name|WIN32_FIND_DATA
name|ngx_dirent_t
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

