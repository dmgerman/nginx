begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_FILES_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_FILES_H_INCLUDED_
define|#
directive|define
name|_NGX_FILES_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_file.h>
end_include

begin_define
DECL|macro|NGX_INVALID_FILE
define|#
directive|define
name|NGX_INVALID_FILE
value|-1
end_define

begin_define
DECL|macro|NGX_FILE_ERROR
define|#
directive|define
name|NGX_FILE_ERROR
value|-1
end_define

begin_define
DECL|macro|ngx_open_file (name,access,create)
define|#
directive|define
name|ngx_open_file
parameter_list|(
name|name
parameter_list|,
name|access
parameter_list|,
name|create
parameter_list|)
define|\
value|open(name, access|create, 0644)
end_define

begin_define
DECL|macro|ngx_open_file_n
define|#
directive|define
name|ngx_open_file_n
value|"open()"
end_define

begin_define
DECL|macro|NGX_FILE_RDONLY
define|#
directive|define
name|NGX_FILE_RDONLY
value|O_RDONLY
end_define

begin_define
DECL|macro|NGX_FILE_RDWR
define|#
directive|define
name|NGX_FILE_RDWR
value|O_RDWR
end_define

begin_define
DECL|macro|NGX_FILE_CREATE_OR_OPEN
define|#
directive|define
name|NGX_FILE_CREATE_OR_OPEN
value|O_CREAT
end_define

begin_define
DECL|macro|NGX_FILE_OPEN
define|#
directive|define
name|NGX_FILE_OPEN
value|0
end_define

begin_define
DECL|macro|NGX_FILE_APPEND
define|#
directive|define
name|NGX_FILE_APPEND
value|O_APPEND
end_define

begin_define
DECL|macro|ngx_close_file
define|#
directive|define
name|ngx_close_file
value|close
end_define

begin_define
DECL|macro|ngx_close_file_n
define|#
directive|define
name|ngx_close_file_n
value|"close()"
end_define

begin_define
DECL|macro|ngx_open_tempfile (name,persistent)
define|#
directive|define
name|ngx_open_tempfile
parameter_list|(
name|name
parameter_list|,
name|persistent
parameter_list|)
define|\
value|open(name, O_CREAT|O_EXCL|O_RDWR, 0600)
end_define

begin_define
DECL|macro|ngx_open_tempfile_n
define|#
directive|define
name|ngx_open_tempfile_n
value|"open()"
end_define

begin_function_decl
name|ssize_t
name|ngx_read_file
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|,
name|off_t
name|offset
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_read_file_n
define|#
directive|define
name|ngx_read_file_n
value|"read()"
end_define

begin_function_decl
name|ssize_t
name|ngx_write_file
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|,
name|off_t
name|offset
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ssize_t
name|ngx_write_chain_to_file
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|ngx_chain_t
modifier|*
name|ce
parameter_list|,
name|off_t
name|offset
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_rename_file
define|#
directive|define
name|ngx_rename_file
value|rename
end_define

begin_define
DECL|macro|ngx_rename_file_n
define|#
directive|define
name|ngx_rename_file_n
value|"rename"
end_define

begin_define
DECL|macro|ngx_mkdir (name)
define|#
directive|define
name|ngx_mkdir
parameter_list|(
name|name
parameter_list|)
value|mkdir(name, 0700)
end_define

begin_define
DECL|macro|ngx_mkdir_n
define|#
directive|define
name|ngx_mkdir_n
value|"mkdir()"
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
DECL|macro|ngx_is_file (sb)
define|#
directive|define
name|ngx_is_file
parameter_list|(
name|sb
parameter_list|)
value|(S_ISREG(sb.st_mode))
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

begin_define
DECL|macro|ngx_file_uniq (sb)
define|#
directive|define
name|ngx_file_uniq
parameter_list|(
name|sb
parameter_list|)
value|sb.st_ino
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FILES_H_INCLUDED_ */
end_comment

end_unit

