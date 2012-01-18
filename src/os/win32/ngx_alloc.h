begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_ALLOC_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_ALLOC_H_INCLUDED_
define|#
directive|define
name|_NGX_ALLOC_H_INCLUDED_
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

begin_function_decl
name|void
modifier|*
name|ngx_alloc
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_calloc
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_free
define|#
directive|define
name|ngx_free
value|free
end_define

begin_define
DECL|macro|ngx_memalign (alignment,size,log)
define|#
directive|define
name|ngx_memalign
parameter_list|(
name|alignment
parameter_list|,
name|size
parameter_list|,
name|log
parameter_list|)
value|ngx_alloc(size, log)
end_define

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_pagesize
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_pagesize_shift
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_cacheline_size
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ALLOC_H_INCLUDED_ */
end_comment

end_unit

