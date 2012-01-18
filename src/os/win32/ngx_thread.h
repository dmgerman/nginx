begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_THREAD_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_THREAD_H_INCLUDED_
define|#
directive|define
name|_NGX_THREAD_H_INCLUDED_
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
DECL|typedef|ngx_tid_t
typedef|typedef
name|HANDLE
name|ngx_tid_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_tls_key_t
typedef|typedef
name|DWORD
name|ngx_tls_key_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_thread_value_t
typedef|typedef
name|DWORD
name|ngx_thread_value_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a0c93980108
typedef|typedef
struct|struct
block|{
DECL|member|mutex
name|HANDLE
name|mutex
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_mutex_t
block|}
name|ngx_mutex_t
typedef|;
end_typedef

begin_function_decl
name|ngx_err_t
name|ngx_create_thread
parameter_list|(
name|ngx_tid_t
modifier|*
name|tid
parameter_list|,
name|ngx_thread_value_t
function_decl|(
name|__stdcall
modifier|*
name|func
function_decl|)
parameter_list|(
name|void
modifier|*
name|arg
parameter_list|)
parameter_list|,
name|void
modifier|*
name|arg
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_init_threads
parameter_list|(
name|int
name|n
parameter_list|,
name|size_t
name|size
parameter_list|,
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_err_t
name|ngx_thread_key_create
parameter_list|(
name|ngx_tls_key_t
modifier|*
name|key
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_thread_key_create_n
define|#
directive|define
name|ngx_thread_key_create_n
value|"TlsAlloc()"
end_define

begin_function_decl
name|ngx_err_t
name|ngx_thread_set_tls
parameter_list|(
name|ngx_tls_key_t
modifier|*
name|key
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_thread_set_tls_n
define|#
directive|define
name|ngx_thread_set_tls_n
value|"TlsSetValue()"
end_define

begin_define
DECL|macro|ngx_thread_get_tls
define|#
directive|define
name|ngx_thread_get_tls
value|TlsGetValue
end_define

begin_define
DECL|macro|ngx_thread_volatile
define|#
directive|define
name|ngx_thread_volatile
value|volatile
end_define

begin_define
DECL|macro|ngx_log_tid
define|#
directive|define
name|ngx_log_tid
value|GetCurrentThreadId()
end_define

begin_define
DECL|macro|NGX_TID_T_FMT
define|#
directive|define
name|NGX_TID_T_FMT
value|"%ud"
end_define

begin_function_decl
name|ngx_mutex_t
modifier|*
name|ngx_mutex_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_mutex_lock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_mutex_trylock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_mutex_unlock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* STUB */
end_comment

begin_define
DECL|macro|NGX_MUTEX_LIGHT
define|#
directive|define
name|NGX_MUTEX_LIGHT
value|0
end_define

begin_comment
comment|/**/
end_comment

begin_decl_stmt
specifier|extern
name|ngx_int_t
name|ngx_threads_n
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_THREAD_H_INCLUDED_ */
end_comment

end_unit

