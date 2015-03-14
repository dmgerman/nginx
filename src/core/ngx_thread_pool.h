begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  * Copyright (C) Valentin V. Bartenev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_THREAD_POOL_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_THREAD_POOL_H_INCLUDED_
define|#
directive|define
name|_NGX_THREAD_POOL_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_struct
DECL|struct|ngx_thread_task_s
struct|struct
name|ngx_thread_task_s
block|{
DECL|member|next
name|ngx_thread_task_t
modifier|*
name|next
decl_stmt|;
DECL|member|id
name|ngx_uint_t
name|id
decl_stmt|;
DECL|member|ctx
name|void
modifier|*
name|ctx
decl_stmt|;
DECL|member|handler
name|void
function_decl|(
modifier|*
name|handler
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
DECL|member|event
name|ngx_event_t
name|event
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|ngx_thread_pool_t
typedef|typedef
name|struct
name|ngx_thread_pool_s
name|ngx_thread_pool_t
typedef|;
end_typedef

begin_function_decl
name|ngx_thread_pool_t
modifier|*
name|ngx_thread_pool_add
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_thread_pool_t
modifier|*
name|ngx_thread_pool_get
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_thread_task_t
modifier|*
name|ngx_thread_task_alloc
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_thread_task_post
parameter_list|(
name|ngx_thread_pool_t
modifier|*
name|tp
parameter_list|,
name|ngx_thread_task_t
modifier|*
name|task
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_THREAD_POOL_H_INCLUDED_ */
end_comment

end_unit

