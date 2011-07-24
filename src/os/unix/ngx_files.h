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

begin_typedef
DECL|typedef|ngx_file_uniq_t
typedef|typedef
name|ino_t
name|ngx_file_uniq_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2ae02ae50108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|u_char
modifier|*
name|name
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|addr
name|void
modifier|*
name|addr
decl_stmt|;
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_file_mapping_t
block|}
name|ngx_file_mapping_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2ae02ae50208
typedef|typedef
struct|struct
block|{
DECL|member|dir
name|DIR
modifier|*
name|dir
decl_stmt|;
DECL|member|de
name|struct
name|dirent
modifier|*
name|de
decl_stmt|;
DECL|member|info
name|struct
name|stat
name|info
decl_stmt|;
DECL|member|type
name|unsigned
name|type
range|:
literal|8
decl_stmt|;
DECL|member|valid_info
name|unsigned
name|valid_info
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_dir_t
block|}
name|ngx_dir_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2ae02ae50308
typedef|typedef
struct|struct
block|{
DECL|member|n
name|size_t
name|n
decl_stmt|;
DECL|member|pglob
name|glob_t
name|pglob
decl_stmt|;
DECL|member|pattern
name|u_char
modifier|*
name|pattern
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|test
name|ngx_uint_t
name|test
decl_stmt|;
DECL|typedef|ngx_glob_t
block|}
name|ngx_glob_t
typedef|;
end_typedef

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

begin_ifdef
ifdef|#
directive|ifdef
name|__CYGWIN__
end_ifdef

begin_define
DECL|macro|NGX_HAVE_CASELESS_FILESYSTEM
define|#
directive|define
name|NGX_HAVE_CASELESS_FILESYSTEM
value|1
end_define

begin_define
DECL|macro|ngx_open_file (name,mode,create,access)
define|#
directive|define
name|ngx_open_file
parameter_list|(
name|name
parameter_list|,
name|mode
parameter_list|,
name|create
parameter_list|,
name|access
parameter_list|)
define|\
value|open((const char *) name, mode|create|O_BINARY, access)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_open_file (name,mode,create,access)
define|#
directive|define
name|ngx_open_file
parameter_list|(
name|name
parameter_list|,
name|mode
parameter_list|,
name|create
parameter_list|,
name|access
parameter_list|)
define|\
value|open((const char *) name, mode|create, access)
end_define

begin_endif
endif|#
directive|endif
end_endif

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
DECL|macro|NGX_FILE_WRONLY
define|#
directive|define
name|NGX_FILE_WRONLY
value|O_WRONLY
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
value|O_CREAT|O_TRUNC
end_define

begin_define
DECL|macro|NGX_FILE_APPEND
define|#
directive|define
name|NGX_FILE_APPEND
value|O_WRONLY|O_APPEND
end_define

begin_define
DECL|macro|NGX_FILE_NONBLOCK
define|#
directive|define
name|NGX_FILE_NONBLOCK
value|O_NONBLOCK
end_define

begin_define
DECL|macro|NGX_FILE_DEFAULT_ACCESS
define|#
directive|define
name|NGX_FILE_DEFAULT_ACCESS
value|0644
end_define

begin_define
DECL|macro|NGX_FILE_OWNER_ACCESS
define|#
directive|define
name|NGX_FILE_OWNER_ACCESS
value|0600
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
parameter_list|,
name|ngx_uint_t
name|access
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_PREAD
operator|)
end_if

begin_define
DECL|macro|ngx_read_file_n
define|#
directive|define
name|ngx_read_file_n
value|"pread()"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_read_file_n
define|#
directive|define
name|ngx_read_file_n
value|"read()"
end_define

begin_endif
endif|#
directive|endif
end_endif

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
DECL|macro|ngx_read_fd
define|#
directive|define
name|ngx_read_fd
value|read
end_define

begin_define
DECL|macro|ngx_read_fd_n
define|#
directive|define
name|ngx_read_fd_n
value|"read()"
end_define

begin_comment
comment|/*  * we use inlined function instead of simple #define  * because glibc 2.3 sets warn_unused_result attribute for write()  * and in this case gcc 4.3 ignores (void) cast  */
end_comment

begin_function
specifier|static
name|ngx_inline
name|ssize_t
DECL|function|ngx_write_fd (ngx_fd_t fd,void * buf,size_t n)
name|ngx_write_fd
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|,
name|void
modifier|*
name|buf
parameter_list|,
name|size_t
name|n
parameter_list|)
block|{
return|return
name|write
argument_list|(
name|fd
argument_list|,
name|buf
argument_list|,
name|n
argument_list|)
return|;
block|}
end_function

begin_define
DECL|macro|ngx_write_fd_n
define|#
directive|define
name|ngx_write_fd_n
value|"write()"
end_define

begin_define
DECL|macro|ngx_write_console
define|#
directive|define
name|ngx_write_console
value|ngx_write_fd
end_define

begin_define
DECL|macro|ngx_linefeed (p)
define|#
directive|define
name|ngx_linefeed
parameter_list|(
name|p
parameter_list|)
value|*p++ = LF;
end_define

begin_define
DECL|macro|NGX_LINEFEED_SIZE
define|#
directive|define
name|NGX_LINEFEED_SIZE
value|1
end_define

begin_define
DECL|macro|ngx_rename_file (o,n)
define|#
directive|define
name|ngx_rename_file
parameter_list|(
name|o
parameter_list|,
name|n
parameter_list|)
value|rename((const char *) o, (const char *) n)
end_define

begin_define
DECL|macro|ngx_rename_file_n
define|#
directive|define
name|ngx_rename_file_n
value|"rename()"
end_define

begin_define
DECL|macro|ngx_change_file_access (n,a)
define|#
directive|define
name|ngx_change_file_access
parameter_list|(
name|n
parameter_list|,
name|a
parameter_list|)
value|chmod((const char *) n, a)
end_define

begin_define
DECL|macro|ngx_change_file_access_n
define|#
directive|define
name|ngx_change_file_access_n
value|"chmod()"
end_define

begin_function_decl
name|ngx_int_t
name|ngx_set_file_time
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|,
name|ngx_fd_t
name|fd
parameter_list|,
name|time_t
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_set_file_time_n
define|#
directive|define
name|ngx_set_file_time_n
value|"utimes()"
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
DECL|macro|ngx_link_info (file,sb)
define|#
directive|define
name|ngx_link_info
parameter_list|(
name|file
parameter_list|,
name|sb
parameter_list|)
value|lstat((const char *) file, sb)
end_define

begin_define
DECL|macro|ngx_link_info_n
define|#
directive|define
name|ngx_link_info_n
value|"lstat()"
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
DECL|macro|ngx_is_link (sb)
define|#
directive|define
name|ngx_is_link
parameter_list|(
name|sb
parameter_list|)
value|(S_ISLNK((sb)->st_mode))
end_define

begin_define
DECL|macro|ngx_is_exec (sb)
define|#
directive|define
name|ngx_is_exec
parameter_list|(
name|sb
parameter_list|)
value|(((sb)->st_mode& S_IXUSR) == S_IXUSR)
end_define

begin_define
DECL|macro|ngx_file_access (sb)
define|#
directive|define
name|ngx_file_access
parameter_list|(
name|sb
parameter_list|)
value|((sb)->st_mode& 0777)
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
DECL|macro|ngx_file_fs_size (sb)
define|#
directive|define
name|ngx_file_fs_size
parameter_list|(
name|sb
parameter_list|)
value|((sb)->st_blocks * 512)
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

begin_function_decl
name|ngx_int_t
name|ngx_create_file_mapping
parameter_list|(
name|ngx_file_mapping_t
modifier|*
name|fm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_close_file_mapping
parameter_list|(
name|ngx_file_mapping_t
modifier|*
name|fm
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_CASELESS_FILESYSTEM
operator|)
end_if

begin_define
DECL|macro|ngx_filename_cmp (s1,s2,n)
define|#
directive|define
name|ngx_filename_cmp
parameter_list|(
name|s1
parameter_list|,
name|s2
parameter_list|,
name|n
parameter_list|)
value|strncasecmp((char *) s1, (char *) s2, n)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_filename_cmp
define|#
directive|define
name|ngx_filename_cmp
value|ngx_memcmp
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_realpath (p,r)
define|#
directive|define
name|ngx_realpath
parameter_list|(
name|p
parameter_list|,
name|r
parameter_list|)
value|realpath((char *) p, (char *) r)
end_define

begin_define
DECL|macro|ngx_realpath_n
define|#
directive|define
name|ngx_realpath_n
value|"realpath()"
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
value|(getcwd((char *) buf, size) != NULL)
end_define

begin_define
DECL|macro|ngx_getcwd_n
define|#
directive|define
name|ngx_getcwd_n
value|"getcwd()"
end_define

begin_define
DECL|macro|ngx_path_separator (c)
define|#
directive|define
name|ngx_path_separator
parameter_list|(
name|c
parameter_list|)
value|((c) == '/')
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

begin_function_decl
name|ngx_int_t
name|ngx_read_dir
parameter_list|(
name|ngx_dir_t
modifier|*
name|dir
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_read_dir_n
define|#
directive|define
name|ngx_read_dir_n
value|"readdir()"
end_define

begin_define
DECL|macro|ngx_create_dir (name,access)
define|#
directive|define
name|ngx_create_dir
parameter_list|(
name|name
parameter_list|,
name|access
parameter_list|)
value|mkdir((const char *) name, access)
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
DECL|macro|ngx_dir_access (a)
define|#
directive|define
name|ngx_dir_access
parameter_list|(
name|a
parameter_list|)
value|(a | (a& 0444)>> 2)
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
name|NGX_HAVE_D_NAMLEN
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

begin_function
specifier|static
name|ngx_inline
name|ngx_int_t
DECL|function|ngx_de_info (u_char * name,ngx_dir_t * dir)
name|ngx_de_info
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|,
name|ngx_dir_t
modifier|*
name|dir
parameter_list|)
block|{
name|dir
operator|->
name|type
operator|=
literal|0
expr_stmt|;
return|return
name|stat
argument_list|(
operator|(
specifier|const
name|char
operator|*
operator|)
name|name
argument_list|,
operator|&
name|dir
operator|->
name|info
argument_list|)
return|;
block|}
end_function

begin_define
DECL|macro|ngx_de_info_n
define|#
directive|define
name|ngx_de_info_n
value|"stat()"
end_define

begin_define
DECL|macro|ngx_de_link_info (name,dir)
define|#
directive|define
name|ngx_de_link_info
parameter_list|(
name|name
parameter_list|,
name|dir
parameter_list|)
value|lstat((const char *) name,&(dir)->info)
end_define

begin_define
DECL|macro|ngx_de_link_info_n
define|#
directive|define
name|ngx_de_link_info_n
value|"lstat()"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_D_TYPE
operator|)
end_if

begin_comment
comment|/*  * some file systems (e.g. XFS on Linux and CD9660 on FreeBSD)  * do not set dirent.d_type  */
end_comment

begin_define
DECL|macro|ngx_de_is_dir (dir)
define|#
directive|define
name|ngx_de_is_dir
parameter_list|(
name|dir
parameter_list|)
define|\
value|(((dir)->type) ? ((dir)->type == DT_DIR) : (S_ISDIR((dir)->info.st_mode)))
end_define

begin_define
DECL|macro|ngx_de_is_file (dir)
define|#
directive|define
name|ngx_de_is_file
parameter_list|(
name|dir
parameter_list|)
define|\
value|(((dir)->type) ? ((dir)->type == DT_REG) : (S_ISREG((dir)->info.st_mode)))
end_define

begin_define
DECL|macro|ngx_de_is_link (dir)
define|#
directive|define
name|ngx_de_is_link
parameter_list|(
name|dir
parameter_list|)
define|\
value|(((dir)->type) ? ((dir)->type == DT_LNK) : (S_ISLNK((dir)->info.st_mode)))
end_define

begin_else
else|#
directive|else
end_else

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
DECL|macro|ngx_de_is_link (dir)
define|#
directive|define
name|ngx_de_is_link
parameter_list|(
name|dir
parameter_list|)
value|(S_ISLNK((dir)->info.st_mode))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_de_access (dir)
define|#
directive|define
name|ngx_de_access
parameter_list|(
name|dir
parameter_list|)
value|(((dir)->info.st_mode)& 0777)
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
DECL|macro|ngx_de_fs_size (dir)
define|#
directive|define
name|ngx_de_fs_size
parameter_list|(
name|dir
parameter_list|)
value|((dir)->info.st_blocks * 512)
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

begin_function_decl
name|ngx_int_t
name|ngx_open_glob
parameter_list|(
name|ngx_glob_t
modifier|*
name|gl
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_open_glob_n
define|#
directive|define
name|ngx_open_glob_n
value|"glob()"
end_define

begin_function_decl
name|ngx_int_t
name|ngx_read_glob
parameter_list|(
name|ngx_glob_t
modifier|*
name|gl
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_close_glob
parameter_list|(
name|ngx_glob_t
modifier|*
name|gl
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_err_t
name|ngx_trylock_fd
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_err_t
name|ngx_lock_fd
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_err_t
name|ngx_unlock_fd
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_trylock_fd_n
define|#
directive|define
name|ngx_trylock_fd_n
value|"fcntl(F_SETLK, F_WRLCK)"
end_define

begin_define
DECL|macro|ngx_lock_fd_n
define|#
directive|define
name|ngx_lock_fd_n
value|"fcntl(F_SETLKW, F_WRLCK)"
end_define

begin_define
DECL|macro|ngx_unlock_fd_n
define|#
directive|define
name|ngx_unlock_fd_n
value|"fcntl(F_SETLK, F_UNLCK)"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_F_READAHEAD
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_READ_AHEAD
define|#
directive|define
name|NGX_HAVE_READ_AHEAD
value|1
end_define

begin_define
DECL|macro|ngx_read_ahead (fd,n)
define|#
directive|define
name|ngx_read_ahead
parameter_list|(
name|fd
parameter_list|,
name|n
parameter_list|)
value|fcntl(fd, F_READAHEAD, (int) n)
end_define

begin_define
DECL|macro|ngx_read_ahead_n
define|#
directive|define
name|ngx_read_ahead_n
value|"fcntl(fd, F_READAHEAD)"
end_define

begin_elif
elif|#
directive|elif
operator|(
name|NGX_HAVE_POSIX_FADVISE
operator|)
end_elif

begin_define
DECL|macro|NGX_HAVE_READ_AHEAD
define|#
directive|define
name|NGX_HAVE_READ_AHEAD
value|1
end_define

begin_function_decl
name|ngx_int_t
name|ngx_read_ahead
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_read_ahead_n
define|#
directive|define
name|ngx_read_ahead_n
value|"posix_fadvise(POSIX_FADV_SEQUENTIAL)"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_read_ahead (fd,n)
define|#
directive|define
name|ngx_read_ahead
parameter_list|(
name|fd
parameter_list|,
name|n
parameter_list|)
value|0
end_define

begin_define
DECL|macro|ngx_read_ahead_n
define|#
directive|define
name|ngx_read_ahead_n
value|"ngx_read_ahead_n"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_O_DIRECT
operator|)
end_if

begin_function_decl
name|ngx_int_t
name|ngx_directio_on
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_directio_on_n
define|#
directive|define
name|ngx_directio_on_n
value|"fcntl(O_DIRECT)"
end_define

begin_function_decl
name|ngx_int_t
name|ngx_directio_off
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_directio_off_n
define|#
directive|define
name|ngx_directio_off_n
value|"fcntl(!O_DIRECT)"
end_define

begin_elif
elif|#
directive|elif
operator|(
name|NGX_HAVE_F_NOCACHE
operator|)
end_elif

begin_define
DECL|macro|ngx_directio_on (fd)
define|#
directive|define
name|ngx_directio_on
parameter_list|(
name|fd
parameter_list|)
value|fcntl(fd, F_NOCACHE, 1)
end_define

begin_define
DECL|macro|ngx_directio_on_n
define|#
directive|define
name|ngx_directio_on_n
value|"fcntl(F_NOCACHE, 1)"
end_define

begin_elif
elif|#
directive|elif
operator|(
name|NGX_HAVE_DIRECTIO
operator|)
end_elif

begin_define
DECL|macro|ngx_directio_on (fd)
define|#
directive|define
name|ngx_directio_on
parameter_list|(
name|fd
parameter_list|)
value|directio(fd, DIRECTIO_ON)
end_define

begin_define
DECL|macro|ngx_directio_on_n
define|#
directive|define
name|ngx_directio_on_n
value|"directio(DIRECTIO_ON)"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_directio_on (fd)
define|#
directive|define
name|ngx_directio_on
parameter_list|(
name|fd
parameter_list|)
value|0
end_define

begin_define
DECL|macro|ngx_directio_on_n
define|#
directive|define
name|ngx_directio_on_n
value|"ngx_directio_on_n"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|size_t
name|ngx_fs_bsize
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_stderr
define|#
directive|define
name|ngx_stderr
value|STDERR_FILENO
end_define

begin_define
DECL|macro|ngx_set_stderr (fd)
define|#
directive|define
name|ngx_set_stderr
parameter_list|(
name|fd
parameter_list|)
value|dup2(fd, STDERR_FILENO)
end_define

begin_define
DECL|macro|ngx_set_stderr_n
define|#
directive|define
name|ngx_set_stderr_n
value|"dup2(STDERR_FILENO)"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|)
end_if

begin_function_decl
name|ssize_t
name|ngx_file_aio_read
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
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_file_aio
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FILES_H_INCLUDED_ */
end_comment

end_unit

