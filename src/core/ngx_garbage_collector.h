begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_GARBAGE_COLLECTOR_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_GARBAGE_COLLECTOR_H_INCLUDED_
define|#
directive|define
name|_NGX_GARBAGE_COLLECTOR_H_INCLUDED_
end_define

begin_typedef
DECL|typedef|ngx_gc_t
typedef|typedef
name|struct
name|ngx_gc_s
name|ngx_gc_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_gc_handler_pt
typedef|typedef
name|int
function_decl|(
modifier|*
name|ngx_gc_handler_pt
function_decl|)
parameter_list|(
name|ngx_gc_t
modifier|*
name|ctx
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|ngx_dir_t
modifier|*
name|dir
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_gc_s
struct|struct
name|ngx_gc_s
block|{
DECL|member|path
name|ngx_path_t
modifier|*
name|path
decl_stmt|;
DECL|member|deleted
name|u_int
name|deleted
decl_stmt|;
DECL|member|freed
name|off_t
name|freed
decl_stmt|;
DECL|member|handler
name|ngx_gc_handler_pt
name|handler
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|int
name|ngx_garbage_collector_temp_handler
parameter_list|(
name|ngx_gc_t
modifier|*
name|ctx
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|ngx_dir_t
modifier|*
name|dir
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_GARBAGE_COLLECTOR_H_INCLUDED_ */
end_comment

end_unit

