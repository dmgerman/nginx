begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_AIO_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_AIO_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_AIO_MODULE_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_function_decl
name|int
name|ngx_aio_init
parameter_list|(
name|int
name|max_connections
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_aio_process_events
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_AIO_MODULE_H_INCLUDED_ */
end_comment

end_unit

