begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_CHANNEL_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_CHANNEL_H_INCLUDED_
define|#
directive|define
name|_NGX_CHANNEL_H_INCLUDED_
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

begin_typedef
DECL|struct|__anon27a59db90108
typedef|typedef
struct|struct
block|{
DECL|member|command
name|ngx_uint_t
name|command
decl_stmt|;
DECL|member|pid
name|ngx_pid_t
name|pid
decl_stmt|;
DECL|member|slot
name|ngx_int_t
name|slot
decl_stmt|;
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|typedef|ngx_channel_t
block|}
name|ngx_channel_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_write_channel
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|,
name|ngx_channel_t
modifier|*
name|ch
parameter_list|,
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
name|ngx_int_t
name|ngx_read_channel
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|,
name|ngx_channel_t
modifier|*
name|ch
parameter_list|,
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
name|ngx_int_t
name|ngx_add_channel_event
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_fd_t
name|fd
parameter_list|,
name|ngx_int_t
name|event
parameter_list|,
name|ngx_event_handler_pt
name|handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_close_channel
parameter_list|(
name|ngx_fd_t
modifier|*
name|fd
parameter_list|,
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
comment|/* _NGX_CHANNEL_H_INCLUDED_ */
end_comment

end_unit

