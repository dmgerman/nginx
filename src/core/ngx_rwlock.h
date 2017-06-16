begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Ruslan Ermilov  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_RWLOCK_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_RWLOCK_H_INCLUDED_
define|#
directive|define
name|_NGX_RWLOCK_H_INCLUDED_
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
name|ngx_rwlock_wlock
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_rwlock_rlock
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_rwlock_unlock
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_rwlock_downgrade
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_RWLOCK_H_INCLUDED_ */
end_comment

end_unit

