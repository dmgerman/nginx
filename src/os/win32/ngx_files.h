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
DECL|struct|__anon28c2cc010108
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
DECL|member|handle
name|HANDLE
name|handle
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
DECL|struct|__anon28c2cc010208
typedef|typedef
struct|struct
block|{
DECL|member|dir
name|HANDLE
name|dir
decl_stmt|;
DECL|member|finddata
name|WIN32_FIND_DATA
name|finddata
decl_stmt|;
DECL|member|valid_info
name|unsigned
name|valid_info
range|:
literal|1
decl_stmt|;
DECL|member|type
name|unsigned
name|type
range|:
literal|1
decl_stmt|;
DECL|member|ready
name|unsigned
name|ready
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_dir_t
block|}
name|ngx_dir_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c2cc010308
typedef|typedef
struct|struct
block|{
DECL|member|dir
name|HANDLE
name|dir
decl_stmt|;
DECL|member|finddata
name|WIN32_FIND_DATA
name|finddata
decl_stmt|;
DECL|member|ready
name|unsigned
name|ready
range|:
literal|1
decl_stmt|;
DECL|member|test
name|unsigned
name|test
range|:
literal|1
decl_stmt|;
DECL|member|no_match
name|unsigned
name|no_match
range|:
literal|1
decl_stmt|;
DECL|member|pattern
name|u_char
modifier|*
name|pattern
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|last
name|size_t
name|last
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_glob_t
block|}
name|ngx_glob_t
typedef|;
end_typedef

begin_comment
comment|/* INVALID_FILE_ATTRIBUTES is specified but not defined at least in MSVC6SP2 */
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
value|0xffffffff
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* INVALID_SET_FILE_POINTER is not defined at least in MSVC6SP2 */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|INVALID_SET_FILE_POINTER
end_ifndef

begin_define
DECL|macro|INVALID_SET_FILE_POINTER
define|#
directive|define
name|INVALID_SET_FILE_POINTER
value|0xffffffff
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_INVALID_FILE
define|#
directive|define
name|NGX_INVALID_FILE
value|INVALID_HANDLE_VALUE
end_define

begin_define
DECL|macro|NGX_FILE_ERROR
define|#
directive|define
name|NGX_FILE_ERROR
value|0
end_define

begin_function_decl
name|ngx_fd_t
name|ngx_open_file
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|,
name|u_long
name|mode
parameter_list|,
name|u_long
name|create
parameter_list|,
name|u_long
name|access
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_open_file_n
define|#
directive|define
name|ngx_open_file_n
value|"CreateFile()"
end_define

begin_define
DECL|macro|NGX_FILE_RDONLY
define|#
directive|define
name|NGX_FILE_RDONLY
value|GENERIC_READ
end_define

begin_define
DECL|macro|NGX_FILE_WRONLY
define|#
directive|define
name|NGX_FILE_WRONLY
value|GENERIC_WRITE
end_define

begin_define
DECL|macro|NGX_FILE_RDWR
define|#
directive|define
name|NGX_FILE_RDWR
value|GENERIC_READ|GENERIC_WRITE
end_define

begin_define
DECL|macro|NGX_FILE_APPEND
define|#
directive|define
name|NGX_FILE_APPEND
value|FILE_APPEND_DATA|SYNCHRONIZE
end_define

begin_define
DECL|macro|NGX_FILE_NONBLOCK
define|#
directive|define
name|NGX_FILE_NONBLOCK
value|0
end_define

begin_define
DECL|macro|NGX_FILE_CREATE_OR_OPEN
define|#
directive|define
name|NGX_FILE_CREATE_OR_OPEN
value|OPEN_ALWAYS
end_define

begin_define
DECL|macro|NGX_FILE_OPEN
define|#
directive|define
name|NGX_FILE_OPEN
value|OPEN_EXISTING
end_define

begin_define
DECL|macro|NGX_FILE_TRUNCATE
define|#
directive|define
name|NGX_FILE_TRUNCATE
value|CREATE_ALWAYS
end_define

begin_define
DECL|macro|NGX_FILE_DEFAULT_ACCESS
define|#
directive|define
name|NGX_FILE_DEFAULT_ACCESS
value|0
end_define

begin_define
DECL|macro|NGX_FILE_OWNER_ACCESS
define|#
directive|define
name|NGX_FILE_OWNER_ACCESS
value|0
end_define

begin_define
DECL|macro|ngx_open_tempfile (name,persistent,access)
define|#
directive|define
name|ngx_open_tempfile
parameter_list|(
name|name
parameter_list|,
name|persistent
parameter_list|,
name|access
parameter_list|)
define|\
value|CreateFile((const char *) name,                                          \                GENERIC_READ|GENERIC_WRITE,                                   \                FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,           \                NULL,                                                         \                CREATE_NEW,                                                   \                persistent ? 0:                                               \                    FILE_ATTRIBUTE_TEMPORARY|FILE_FLAG_DELETE_ON_CLOSE,       \                NULL);
end_define

begin_define
DECL|macro|ngx_open_tempfile_n
define|#
directive|define
name|ngx_open_tempfile_n
value|"CreateFile()"
end_define

begin_define
DECL|macro|ngx_close_file
define|#
directive|define
name|ngx_close_file
value|CloseHandle
end_define

begin_define
DECL|macro|ngx_close_file_n
define|#
directive|define
name|ngx_close_file_n
value|"CloseHandle()"
end_define

begin_function_decl
name|ssize_t
name|ngx_read_fd
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|,
name|void
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_read_fd_n
define|#
directive|define
name|ngx_read_fd_n
value|"ReadFile()"
end_define

begin_function_decl
name|ssize_t
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
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_write_fd_n
define|#
directive|define
name|ngx_write_fd_n
value|"WriteFile()"
end_define

begin_function_decl
name|ssize_t
name|ngx_write_console
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|,
name|void
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_linefeed (p)
define|#
directive|define
name|ngx_linefeed
parameter_list|(
name|p
parameter_list|)
value|*p++ = CR; *p++ = LF;
end_define

begin_define
DECL|macro|NGX_LINEFEED_SIZE
define|#
directive|define
name|NGX_LINEFEED_SIZE
value|2
end_define

begin_define
DECL|macro|NGX_LINEFEED
define|#
directive|define
name|NGX_LINEFEED
value|CRLF
end_define

begin_define
DECL|macro|ngx_delete_file (name)
define|#
directive|define
name|ngx_delete_file
parameter_list|(
name|name
parameter_list|)
value|DeleteFile((const char *) name)
end_define

begin_define
DECL|macro|ngx_delete_file_n
define|#
directive|define
name|ngx_delete_file_n
value|"DeleteFile()"
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
value|MoveFile((const char *) o, (const char *) n)
end_define

begin_define
DECL|macro|ngx_rename_file_n
define|#
directive|define
name|ngx_rename_file_n
value|"MoveFile()"
end_define

begin_function_decl
name|ngx_err_t
name|ngx_win32_rename_file
parameter_list|(
name|ngx_str_t
modifier|*
name|from
parameter_list|,
name|ngx_str_t
modifier|*
name|to
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

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
value|"SetFileTime()"
end_define

begin_function_decl
name|ngx_int_t
name|ngx_file_info
parameter_list|(
name|u_char
modifier|*
name|filename
parameter_list|,
name|ngx_file_info_t
modifier|*
name|fi
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_file_info_n
define|#
directive|define
name|ngx_file_info_n
value|"GetFileAttributesEx()"
end_define

begin_define
DECL|macro|ngx_fd_info (fd,fi)
define|#
directive|define
name|ngx_fd_info
parameter_list|(
name|fd
parameter_list|,
name|fi
parameter_list|)
value|GetFileInformationByHandle(fd, fi)
end_define

begin_define
DECL|macro|ngx_fd_info_n
define|#
directive|define
name|ngx_fd_info_n
value|"GetFileInformationByHandle()"
end_define

begin_define
DECL|macro|ngx_link_info (name,fi)
define|#
directive|define
name|ngx_link_info
parameter_list|(
name|name
parameter_list|,
name|fi
parameter_list|)
value|ngx_file_info(name, fi)
end_define

begin_define
DECL|macro|ngx_link_info_n
define|#
directive|define
name|ngx_link_info_n
value|"GetFileAttributesEx()"
end_define

begin_define
DECL|macro|ngx_is_dir (fi)
define|#
directive|define
name|ngx_is_dir
parameter_list|(
name|fi
parameter_list|)
define|\
value|(((fi)->dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) != 0)
end_define

begin_define
DECL|macro|ngx_is_file (fi)
define|#
directive|define
name|ngx_is_file
parameter_list|(
name|fi
parameter_list|)
define|\
value|(((fi)->dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) == 0)
end_define

begin_define
DECL|macro|ngx_is_link (fi)
define|#
directive|define
name|ngx_is_link
parameter_list|(
name|fi
parameter_list|)
value|0
end_define

begin_define
DECL|macro|ngx_is_exec (fi)
define|#
directive|define
name|ngx_is_exec
parameter_list|(
name|fi
parameter_list|)
value|0
end_define

begin_define
DECL|macro|ngx_file_access (fi)
define|#
directive|define
name|ngx_file_access
parameter_list|(
name|fi
parameter_list|)
value|0
end_define

begin_define
DECL|macro|ngx_file_size (fi)
define|#
directive|define
name|ngx_file_size
parameter_list|(
name|fi
parameter_list|)
define|\
value|(((off_t) (fi)->nFileSizeHigh<< 32) | (fi)->nFileSizeLow)
end_define

begin_define
DECL|macro|ngx_file_fs_size (fi)
define|#
directive|define
name|ngx_file_fs_size
parameter_list|(
name|fi
parameter_list|)
value|ngx_file_size(fi)
end_define

begin_define
DECL|macro|ngx_file_uniq (fi)
define|#
directive|define
name|ngx_file_uniq
parameter_list|(
name|fi
parameter_list|)
value|(*(ngx_file_uniq_t *)&(fi)->nFileIndexHigh)
end_define

begin_comment
comment|/* 116444736000000000 is commented in src/os/win32/ngx_time.c */
end_comment

begin_define
DECL|macro|ngx_file_mtime (fi)
define|#
directive|define
name|ngx_file_mtime
parameter_list|(
name|fi
parameter_list|)
define|\
value|(time_t) (((((unsigned __int64) (fi)->ftLastWriteTime.dwHighDateTime<< 32) \                                | (fi)->ftLastWriteTime.dwLowDateTime)        \                                           - 116444736000000000) / 10000000)
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

begin_define
DECL|macro|NGX_HAVE_CASELESS_FILESYSTEM
define|#
directive|define
name|NGX_HAVE_CASELESS_FILESYSTEM
value|1
end_define

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
value|_strnicmp((char *) s1, (char *) s2, n)
end_define

begin_function_decl
name|char
modifier|*
name|ngx_realpath
parameter_list|(
name|u_char
modifier|*
name|path
parameter_list|,
name|u_char
modifier|*
name|resolved
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_realpath_n
define|#
directive|define
name|ngx_realpath_n
value|""
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
value|GetCurrentDirectory(size, (char *) buf)
end_define

begin_define
DECL|macro|ngx_getcwd_n
define|#
directive|define
name|ngx_getcwd_n
value|"GetCurrentDirectory()"
end_define

begin_define
DECL|macro|ngx_path_separator (c)
define|#
directive|define
name|ngx_path_separator
parameter_list|(
name|c
parameter_list|)
value|((c) == '/' || (c) == '\\')
end_define

begin_define
DECL|macro|NGX_MAX_PATH
define|#
directive|define
name|NGX_MAX_PATH
value|MAX_PATH
end_define

begin_define
DECL|macro|NGX_DIR_MASK
define|#
directive|define
name|NGX_DIR_MASK
value|(u_char *) "/*"
end_define

begin_define
DECL|macro|NGX_DIR_MASK_LEN
define|#
directive|define
name|NGX_DIR_MASK_LEN
value|2
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
value|"FindFirstFile()"
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
value|"FindNextFile()"
end_define

begin_define
DECL|macro|ngx_close_dir (d)
define|#
directive|define
name|ngx_close_dir
parameter_list|(
name|d
parameter_list|)
value|FindClose((d)->dir)
end_define

begin_define
DECL|macro|ngx_close_dir_n
define|#
directive|define
name|ngx_close_dir_n
value|"FindClose()"
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
value|CreateDirectory((const char *) name, NULL)
end_define

begin_define
DECL|macro|ngx_create_dir_n
define|#
directive|define
name|ngx_create_dir_n
value|"CreateDirectory()"
end_define

begin_define
DECL|macro|ngx_delete_dir (name)
define|#
directive|define
name|ngx_delete_dir
parameter_list|(
name|name
parameter_list|)
value|RemoveDirectory((const char *) name)
end_define

begin_define
DECL|macro|ngx_delete_dir_n
define|#
directive|define
name|ngx_delete_dir_n
value|"RemoveDirectory()"
end_define

begin_define
DECL|macro|ngx_dir_access (a)
define|#
directive|define
name|ngx_dir_access
parameter_list|(
name|a
parameter_list|)
value|(a)
end_define

begin_define
DECL|macro|ngx_de_name (dir)
define|#
directive|define
name|ngx_de_name
parameter_list|(
name|dir
parameter_list|)
value|((u_char *) (dir)->finddata.cFileName)
end_define

begin_define
DECL|macro|ngx_de_namelen (dir)
define|#
directive|define
name|ngx_de_namelen
parameter_list|(
name|dir
parameter_list|)
value|ngx_strlen((dir)->finddata.cFileName)
end_define

begin_function_decl
name|ngx_int_t
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
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_de_info_n
define|#
directive|define
name|ngx_de_info_n
value|"dummy()"
end_define

begin_function_decl
name|ngx_int_t
name|ngx_de_link_info
parameter_list|(
name|u_char
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
DECL|macro|ngx_de_link_info_n
define|#
directive|define
name|ngx_de_link_info_n
value|"dummy()"
end_define

begin_define
DECL|macro|ngx_de_is_dir (dir)
define|#
directive|define
name|ngx_de_is_dir
parameter_list|(
name|dir
parameter_list|)
define|\
value|(((dir)->finddata.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) != 0)
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
value|(((dir)->finddata.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY) == 0)
end_define

begin_define
DECL|macro|ngx_de_is_link (dir)
define|#
directive|define
name|ngx_de_is_link
parameter_list|(
name|dir
parameter_list|)
value|0
end_define

begin_define
DECL|macro|ngx_de_access (dir)
define|#
directive|define
name|ngx_de_access
parameter_list|(
name|dir
parameter_list|)
value|0
end_define

begin_define
DECL|macro|ngx_de_size (dir)
define|#
directive|define
name|ngx_de_size
parameter_list|(
name|dir
parameter_list|)
define|\
value|(((off_t) (dir)->finddata.nFileSizeHigh<< 32) | (dir)->finddata.nFileSizeLow)
end_define

begin_define
DECL|macro|ngx_de_fs_size (dir)
define|#
directive|define
name|ngx_de_fs_size
parameter_list|(
name|dir
parameter_list|)
value|ngx_de_size(dir)
end_define

begin_comment
comment|/* 116444736000000000 is commented in src/os/win32/ngx_time.c */
end_comment

begin_define
DECL|macro|ngx_de_mtime (dir)
define|#
directive|define
name|ngx_de_mtime
parameter_list|(
name|dir
parameter_list|)
define|\
value|(time_t) (((((unsigned __int64)                                          \                      (dir)->finddata.ftLastWriteTime.dwHighDateTime<< 32)   \                       | (dir)->finddata.ftLastWriteTime.dwLowDateTime)       \                                           - 116444736000000000) / 10000000)
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
value|"FindFirstFile()"
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
value|"ReadFile()"
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
value|"ngx_read_ahead_n"
end_define

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
value|"ngx_directio_on_n"
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
value|"ngx_directio_off_n"
end_define

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
value|GetStdHandle(STD_ERROR_HANDLE)
end_define

begin_define
DECL|macro|ngx_set_stderr (fd)
define|#
directive|define
name|ngx_set_stderr
parameter_list|(
name|fd
parameter_list|)
value|SetStdHandle(STD_ERROR_HANDLE, fd)
end_define

begin_define
DECL|macro|ngx_set_stderr_n
define|#
directive|define
name|ngx_set_stderr_n
value|"SetStdHandle(STD_ERROR_HANDLE)"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FILES_H_INCLUDED_ */
end_comment

end_unit

