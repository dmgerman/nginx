begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SHMEM_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SHMEM_H_INCLUDED_
define|#
directive|define
name|_NGX_SHMEM_H_INCLUDED_
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
DECL|struct|__anon27f88d740108
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|u_char
modifier|*
name|addr
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
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
DECL|typedef|ngx_shm_t
block|}
name|ngx_shm_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_shm_alloc
parameter_list|(
name|ngx_shm_t
modifier|*
name|shm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_shm_free
parameter_list|(
name|ngx_shm_t
modifier|*
name|shm
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SHMEM_H_INCLUDED_ */
end_comment

end_unit

