begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_STAT_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_STAT_H_INCLUDED_
define|#
directive|define
name|_NGX_STAT_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_comment
comment|/* INVALID_FILE_ATTRIBUTES specified but never defined at least in VC6SP2 */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|INVALID_FILE_ATTRIBUTES
end_ifndef

begin_define
DECL|macro|INVALID_FILE_ATTRIBUTES
define|#
directive|define
name|INVALID_FILE_ATTRIBUTES
value|0xFFFFFFFF
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_file_info_t
typedef|typedef
name|BY_HANDLE_FILE_INFORMATION
name|ngx_file_info_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_file_type_n
define|#
directive|define
name|ngx_file_type_n
value|"GetFileAttributes"
end_define

begin_define
DECL|macro|ngx_is_dir (fi)
define|#
directive|define
name|ngx_is_dir
parameter_list|(
name|fi
parameter_list|)
value|(fi.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)
end_define

begin_define
DECL|macro|ngx_stat_n
define|#
directive|define
name|ngx_stat_n
value|"GetFileAttributes"
end_define

begin_define
DECL|macro|ngx_fstat (file,fd,sb)
define|#
directive|define
name|ngx_fstat
parameter_list|(
name|file
parameter_list|,
name|fd
parameter_list|,
name|sb
parameter_list|)
value|ngx_stat(file, sb)
end_define

begin_define
DECL|macro|ngx_fstat_n
define|#
directive|define
name|ngx_fstat_n
value|"GetFileAttributes"
end_define

begin_comment
comment|/* int ngx_stat(char *file, ngx_stat_t *sb); */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_STAT_H_INCLUDED_ */
end_comment

end_unit

