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
DECL|typedef|ngx_fd_t
typedef|typedef
name|HANDLE
name|ngx_fd_t
typedef|;
end_typedef

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

begin_typedef
DECL|typedef|off_t
typedef|typedef
name|unsigned
name|__int64
name|off_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_file_info_t
typedef|typedef
name|BY_HANDLE_FILE_INFORMATION
name|ngx_file_info_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_open_file (name,flags)
define|#
directive|define
name|ngx_open_file
parameter_list|(
name|name
parameter_list|,
name|flags
parameter_list|)
define|\
value|CreateFile(name, flags,                                         \                        FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,  \                        NULL, OPEN_EXISTING, 0, NULL)
end_define

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
name|int
name|ngx_file_type
parameter_list|(
name|char
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
DECL|macro|ngx_file_type_n
define|#
directive|define
name|ngx_file_type_n
value|"GetFileAttributes"
end_define

begin_define
DECL|macro|ngx_stat_fd (fd,fi)
define|#
directive|define
name|ngx_stat_fd
parameter_list|(
name|fd
parameter_list|,
name|fi
parameter_list|)
value|GetFileInformationByHandle(fd, fi)
end_define

begin_define
DECL|macro|ngx_stat_fd_n
define|#
directive|define
name|ngx_stat_fd_n
value|"GetFileInformationByHandle"
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
DECL|macro|ngx_is_file (fi)
define|#
directive|define
name|ngx_is_file
parameter_list|(
name|fi
parameter_list|)
value|!(fi.dwFileAttributes& FILE_ATTRIBUTE_DIRECTORY)
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
value|(((off_t) fi.nFileSizeHigh<< 32) | fi.nFileSizeLow)
end_define

begin_comment
comment|/* There are 134774 days between 1 Jan 1970 and 1 Jan 1601,    11644473600 seconds or 11644473600,000,000,0 100-nanosecond intervals */
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
value|(time_t) (((((unsigned __int64) fi.ftLastWriteTime.dwHighDateTime<< 32) \                                  | fi.ftLastWriteTime.dwLowDateTime)        \                                           - 116444736000000000) / 10000000)
end_define

begin_define
DECL|macro|ngx_read_file_n
define|#
directive|define
name|ngx_read_file_n
value|"ReadFile()"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FILES_H_INCLUDED_ */
end_comment

end_unit

