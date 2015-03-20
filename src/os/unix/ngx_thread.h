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

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_include
include|#
directive|include
file|<pthread.h>
end_include

begin_typedef
DECL|typedef|ngx_thread_mutex_t
typedef|typedef
name|pthread_mutex_t
name|ngx_thread_mutex_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_thread_mutex_create
parameter_list|(
name|ngx_thread_mutex_t
modifier|*
name|mtx
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_thread_mutex_destroy
parameter_list|(
name|ngx_thread_mutex_t
modifier|*
name|mtx
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_thread_mutex_lock
parameter_list|(
name|ngx_thread_mutex_t
modifier|*
name|mtx
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_thread_mutex_unlock
parameter_list|(
name|ngx_thread_mutex_t
modifier|*
name|mtx
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|typedef|ngx_thread_cond_t
typedef|typedef
name|pthread_cond_t
name|ngx_thread_cond_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_thread_cond_create
parameter_list|(
name|ngx_thread_cond_t
modifier|*
name|cond
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_thread_cond_destroy
parameter_list|(
name|ngx_thread_cond_t
modifier|*
name|cond
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_thread_cond_signal
parameter_list|(
name|ngx_thread_cond_t
modifier|*
name|cond
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_thread_cond_wait
parameter_list|(
name|ngx_thread_cond_t
modifier|*
name|cond
parameter_list|,
name|ngx_thread_mutex_t
modifier|*
name|mtx
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_LINUX
operator|)
end_if

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|pid_t
name|ngx_tid_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_TID_T_FMT
define|#
directive|define
name|NGX_TID_T_FMT
value|"%P"
end_define

begin_elif
elif|#
directive|elif
operator|(
name|NGX_FREEBSD
operator|)
end_elif

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|uint32_t
name|ngx_tid_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_TID_T_FMT
define|#
directive|define
name|NGX_TID_T_FMT
value|"%uD"
end_define

begin_elif
elif|#
directive|elif
operator|(
name|NGX_DARWIN
operator|)
end_elif

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|uint64_t
name|ngx_tid_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_TID_T_FMT
define|#
directive|define
name|NGX_TID_T_FMT
value|"%uA"
end_define

begin_else
else|#
directive|else
end_else

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|uint64_t
name|ngx_tid_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_TID_T_FMT
define|#
directive|define
name|NGX_TID_T_FMT
value|"%uA"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|ngx_tid_t
name|ngx_thread_tid
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_log_tid
define|#
directive|define
name|ngx_log_tid
value|ngx_thread_tid()
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_log_tid
define|#
directive|define
name|ngx_log_tid
value|0
end_define

begin_define
DECL|macro|NGX_TID_T_FMT
define|#
directive|define
name|NGX_TID_T_FMT
value|"%d"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_THREAD_H_INCLUDED_ */
end_comment

end_unit

