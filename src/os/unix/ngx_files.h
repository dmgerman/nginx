begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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
file|<ngx_core.h>
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
value|open((const char *) name, access|create, 0644)
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
DECL|macro|NGX_FILE_TRUNCATE
define|#
directive|define
name|NGX_FILE_TRUNCATE
value|O_TRUNC
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
DECL|macro|ngx_delete_file (name)
define|#
directive|define
name|ngx_delete_file
parameter_list|(
name|name
parameter_list|)
value|unlink((const char *) name)
end_define

begin_define
DECL|macro|ngx_delete_file_n
define|#
directive|define
name|ngx_delete_file_n
value|"unlink()"
end_define

begin_function_decl
name|ngx_fd_t
name|ngx_open_tempfile
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|,
name|ngx_uint_t
name|persistent
parameter_list|)
function_decl|;
end_function_decl

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
name|u_char
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
name|u_char
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
DECL|macro|ngx_file_info (file,sb)
define|#
directive|define
name|ngx_file_info
parameter_list|(
name|file
parameter_list|,
name|sb
parameter_list|)
value|stat((const char *) file, sb)
end_define

begin_define
DECL|macro|ngx_file_info_n
define|#
directive|define
name|ngx_file_info_n
value|"stat()"
end_define

begin_define
DECL|macro|ngx_fd_info (fd,sb)
define|#
directive|define
name|ngx_fd_info
parameter_list|(
name|fd
parameter_list|,
name|sb
parameter_list|)
value|fstat(fd, sb)
end_define

begin_define
DECL|macro|ngx_fd_info_n
define|#
directive|define
name|ngx_fd_info_n
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
value|(S_ISDIR((sb)->st_mode))
end_define

begin_define
DECL|macro|ngx_is_file (sb)
define|#
directive|define
name|ngx_is_file
parameter_list|(
name|sb
parameter_list|)
value|(S_ISREG((sb)->st_mode))
end_define

begin_define
DECL|macro|ngx_file_size (sb)
define|#
directive|define
name|ngx_file_size
parameter_list|(
name|sb
parameter_list|)
value|(sb)->st_size
end_define

begin_define
DECL|macro|ngx_file_mtime (sb)
define|#
directive|define
name|ngx_file_mtime
parameter_list|(
name|sb
parameter_list|)
value|(sb)->st_mtime
end_define

begin_define
DECL|macro|ngx_file_uniq (sb)
define|#
directive|define
name|ngx_file_uniq
parameter_list|(
name|sb
parameter_list|)
value|(sb)->st_ino
end_define

begin_define
DECL|macro|ngx_getcwd (buf,size)
define|#
directive|define
name|ngx_getcwd
parameter_list|(
name|buf
parameter_list|,
name|size
parameter_list|)
value|(getcwd(buf, size) != NULL)
end_define

begin_define
DECL|macro|ngx_getcwd_n
define|#
directive|define
name|ngx_getcwd_n
value|"getcwd()"
end_define

begin_define
DECL|macro|NGX_MAX_PATH
define|#
directive|define
name|NGX_MAX_PATH
value|PATH_MAX
end_define

begin_define
DECL|macro|NGX_DIR_MASK_LEN
define|#
directive|define
name|NGX_DIR_MASK_LEN
value|0
end_define

begin_function_decl
name|ngx_int_t
name|ngx_open_dir
parameter_list|(
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|ngx_dir_t
modifier|*
name|dir
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_open_dir_n
define|#
directive|define
name|ngx_open_dir_n
value|"opendir()"
end_define

begin_define
DECL|macro|ngx_close_dir (d)
define|#
directive|define
name|ngx_close_dir
parameter_list|(
name|d
parameter_list|)
value|closedir((d)->dir)
end_define

begin_define
DECL|macro|ngx_close_dir_n
define|#
directive|define
name|ngx_close_dir_n
value|"closedir()"
end_define

begin_define
DECL|macro|ngx_read_dir (d)
define|#
directive|define
name|ngx_read_dir
parameter_list|(
name|d
parameter_list|)
define|\
value|(((d)->de = readdir((d)->dir)) ? NGX_OK : NGX_ERROR)
end_define

begin_define
DECL|macro|ngx_read_dir_n
define|#
directive|define
name|ngx_read_dir_n
value|"readdir()"
end_define

begin_define
DECL|macro|ngx_create_dir (name)
define|#
directive|define
name|ngx_create_dir
parameter_list|(
name|name
parameter_list|)
value|mkdir((const char *) name, 0700)
end_define

begin_define
DECL|macro|ngx_create_dir_n
define|#
directive|define
name|ngx_create_dir_n
value|"mkdir()"
end_define

begin_define
DECL|macro|ngx_delete_dir (name)
define|#
directive|define
name|ngx_delete_dir
parameter_list|(
name|name
parameter_list|)
value|rmdir((const char *) name)
end_define

begin_define
DECL|macro|ngx_delete_dir_n
define|#
directive|define
name|ngx_delete_dir_n
value|"rmdir()"
end_define

begin_define
DECL|macro|ngx_de_name (dir)
define|#
directive|define
name|ngx_de_name
parameter_list|(
name|dir
parameter_list|)
value|((u_char *) (dir)->de->d_name)
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_FREEBSD
operator|)
end_if

begin_define
DECL|macro|ngx_de_namelen (dir)
define|#
directive|define
name|ngx_de_namelen
parameter_list|(
name|dir
parameter_list|)
value|(dir)->de->d_namlen
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_de_namelen (dir)
define|#
directive|define
name|ngx_de_namelen
parameter_list|(
name|dir
parameter_list|)
value|ngx_strlen((dir)->de->d_name)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_de_info (name,dir)
define|#
directive|define
name|ngx_de_info
parameter_list|(
name|name
parameter_list|,
name|dir
parameter_list|)
value|lstat((const char *) name,&(dir)->info)
end_define

begin_define
DECL|macro|ngx_de_info_n
define|#
directive|define
name|ngx_de_info_n
value|"stat()"
end_define

begin_define
DECL|macro|ngx_de_is_dir (dir)
define|#
directive|define
name|ngx_de_is_dir
parameter_list|(
name|dir
parameter_list|)
value|(S_ISDIR((dir)->info.st_mode))
end_define

begin_define
DECL|macro|ngx_de_is_file (dir)
define|#
directive|define
name|ngx_de_is_file
parameter_list|(
name|dir
parameter_list|)
value|(S_ISREG((dir)->info.st_mode))
end_define

begin_define
DECL|macro|ngx_de_size (dir)
define|#
directive|define
name|ngx_de_size
parameter_list|(
name|dir
parameter_list|)
value|(dir)->info.st_size
end_define

begin_define
DECL|macro|ngx_de_mtime (dir)
define|#
directive|define
name|ngx_de_mtime
parameter_list|(
name|dir
parameter_list|)
value|(dir)->info.st_mtime
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FILES_H_INCLUDED_ */
end_comment

end_unit

