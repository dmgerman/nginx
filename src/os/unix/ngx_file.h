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
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_typedef
DECL|typedef|ngx_file_t
typedef|typedef
name|int
name|ngx_file_t
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

begin_define
DECL|macro|ngx_open_file
define|#
directive|define
name|ngx_open_file
value|open
end_define

begin_define
DECL|macro|ngx_open_file_n
define|#
directive|define
name|ngx_open_file_n
value|"open()"
end_define

begin_define
DECL|macro|ngx_read_file
define|#
directive|define
name|ngx_read_file
value|read
end_define

begin_define
DECL|macro|ngx_read_file_n
define|#
directive|define
name|ngx_read_file_n
value|"read()"
end_define

begin_define
DECL|macro|NGX_FILE_RDONLY
define|#
directive|define
name|NGX_FILE_RDONLY
value|O_RDONLY
end_define

begin_define
DECL|macro|ngx_file_type (file,sb)
define|#
directive|define
name|ngx_file_type
parameter_list|(
name|file
parameter_list|,
name|sb
parameter_list|)
value|stat(file, sb)
end_define

begin_define
DECL|macro|ngx_file_type_n
define|#
directive|define
name|ngx_file_type_n
value|"stat()"
end_define

begin_define
DECL|macro|ngx_stat_fd (fd,sb)
define|#
directive|define
name|ngx_stat_fd
parameter_list|(
name|fd
parameter_list|,
name|sb
parameter_list|)
value|fstat(fd, sb)
end_define

begin_define
DECL|macro|ngx_stat_fd_n
define|#
directive|define
name|ngx_stat_fd_n
value|"fstat()"
end_define

begin_define
DECL|macro|ngx_is_dir (sb)
define|#
directive|define
name|ngx_is_dir
parameter_list|(
name|sb
parameter_list|)
value|(S_ISDIR(sb.st_mode))
end_define

begin_define
DECL|macro|ngx_file_size (sb)
define|#
directive|define
name|ngx_file_size
parameter_list|(
name|sb
parameter_list|)
value|sb.st_size
end_define

begin_define
DECL|macro|ngx_file_mtime (sb)
define|#
directive|define
name|ngx_file_mtime
parameter_list|(
name|sb
parameter_list|)
value|sb.st_mtime
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FILE_H_INCLUDED_ */
end_comment

end_unit

