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
DECL|typedef|ngx_thread_value_t
typedef|typedef
name|DWORD
name|ngx_thread_value_t
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_THREAD_H_INCLUDED_ */
end_comment

end_unit

