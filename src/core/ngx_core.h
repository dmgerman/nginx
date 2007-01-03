begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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
DECL|typedef|ngx_chain_t
typedef|typedef
name|struct
name|ngx_chain_s
name|ngx_chain_t
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

begin_typedef
DECL|typedef|ngx_event_handler_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_event_handler_pt
function_decl|)
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_connection_handler_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_connection_handler_pt
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
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
file|<ngx_errno.h>
end_include

begin_include
include|#
directive|include
file|<ngx_atomic.h>
end_include

begin_include
include|#
directive|include
file|<ngx_thread.h>
end_include

begin_include
include|#
directive|include
file|<ngx_rbtree.h>
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
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_shmem.h>
end_include

begin_include
include|#
directive|include
file|<ngx_process.h>
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
file|<ngx_list.h>
end_include

begin_include
include|#
directive|include
file|<ngx_hash.h>
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

begin_include
include|#
directive|include
file|<ngx_crc32.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_PCRE
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
file|<ngx_shmtx.h>
end_include

begin_include
include|#
directive|include
file|<ngx_slab.h>
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

begin_if
if|#
directive|if
operator|(
name|NGX_OPENSSL
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_event_openssl.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
DECL|macro|ngx_abs (value)
define|#
directive|define
name|ngx_abs
parameter_list|(
name|value
parameter_list|)
value|(((value)>= 0) ? (value) : - (value))
end_define

begin_function_decl
name|void
name|ngx_cpuinfo
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_CORE_H_INCLUDED_ */
end_comment

end_unit

