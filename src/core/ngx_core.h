begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_CORE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_CORE_H_INCLUDED_
define|#
directive|define
name|_NGX_CORE_H_INCLUDED_
end_define

begin_typedef
DECL|typedef|ngx_module_t
typedef|typedef
name|struct
name|ngx_module_s
name|ngx_module_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_conf_t
typedef|typedef
name|struct
name|ngx_conf_s
name|ngx_conf_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_cycle_t
typedef|typedef
name|struct
name|ngx_cycle_s
name|ngx_cycle_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_pool_t
typedef|typedef
name|struct
name|ngx_pool_s
name|ngx_pool_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_log_t
typedef|typedef
name|struct
name|ngx_log_s
name|ngx_log_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_array_t
typedef|typedef
name|struct
name|ngx_array_s
name|ngx_array_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_open_file_t
typedef|typedef
name|struct
name|ngx_open_file_s
name|ngx_open_file_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_command_t
typedef|typedef
name|struct
name|ngx_command_s
name|ngx_command_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_file_t
typedef|typedef
name|struct
name|ngx_file_s
name|ngx_file_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_event_t
typedef|typedef
name|struct
name|ngx_event_s
name|ngx_event_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_connection_t
typedef|typedef
name|struct
name|ngx_connection_s
name|ngx_connection_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_OK
define|#
directive|define
name|NGX_OK
value|0
end_define

begin_define
DECL|macro|NGX_ERROR
define|#
directive|define
name|NGX_ERROR
value|-1
end_define

begin_define
DECL|macro|NGX_AGAIN
define|#
directive|define
name|NGX_AGAIN
value|-2
end_define

begin_define
DECL|macro|NGX_BUSY
define|#
directive|define
name|NGX_BUSY
value|-3
end_define

begin_define
DECL|macro|NGX_DONE
define|#
directive|define
name|NGX_DONE
value|-4
end_define

begin_define
DECL|macro|NGX_DECLINED
define|#
directive|define
name|NGX_DECLINED
value|-5
end_define

begin_define
DECL|macro|NGX_ABORT
define|#
directive|define
name|NGX_ABORT
value|-6
end_define

begin_include
include|#
directive|include
file|<ngx_atomic.h>
end_include

begin_include
include|#
directive|include
file|<ngx_time.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_include
include|#
directive|include
file|<ngx_errno.h>
end_include

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_shared.h>
end_include

begin_include
include|#
directive|include
file|<ngx_process.h>
end_include

begin_include
include|#
directive|include
file|<ngx_thread.h>
end_include

begin_include
include|#
directive|include
file|<ngx_user.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_parse.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_palloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_buf.h>
end_include

begin_include
include|#
directive|include
file|<ngx_array.h>
end_include

begin_include
include|#
directive|include
file|<ngx_table.h>
end_include

begin_include
include|#
directive|include
file|<ngx_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_files.h>
end_include

begin_include
include|#
directive|include
file|<ngx_crc.h>
end_include

begin_if
if|#
directive|if
operator|(
name|HAVE_PCRE
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_regex.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<ngx_rbtree.h>
end_include

begin_include
include|#
directive|include
file|<ngx_radix_tree.h>
end_include

begin_include
include|#
directive|include
file|<ngx_times.h>
end_include

begin_include
include|#
directive|include
file|<ngx_inet.h>
end_include

begin_include
include|#
directive|include
file|<ngx_cycle.h>
end_include

begin_include
include|#
directive|include
file|<ngx_process_cycle.h>
end_include

begin_include
include|#
directive|include
file|<ngx_conf_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_os.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_define
DECL|macro|LF
define|#
directive|define
name|LF
value|(u_char) 10
end_define

begin_define
DECL|macro|CR
define|#
directive|define
name|CR
value|(u_char) 13
end_define

begin_define
DECL|macro|CRLF
define|#
directive|define
name|CRLF
value|"\x0d\x0a"
end_define

begin_define
DECL|macro|NGX_MAXHOSTNAMELEN
define|#
directive|define
name|NGX_MAXHOSTNAMELEN
value|64
end_define

begin_comment
comment|/* #define NGX_MAXHOSTNAMELEN MAXHOSTNAMELEN */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_CORE_H_INCLUDED_ */
end_comment

end_unit

