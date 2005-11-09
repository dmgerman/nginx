begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_LOG_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_LOG_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_LOG_MODULE_H_INCLUDED_
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
file|<ngx_http.h>
end_include

begin_typedef
DECL|typedef|ngx_http_log_op_t
typedef|typedef
name|struct
name|ngx_http_log_op_s
name|ngx_http_log_op_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_log_op_run_pt
typedef|typedef
name|u_char
modifier|*
function_decl|(
modifier|*
name|ngx_http_log_op_run_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|ngx_http_log_op_t
modifier|*
name|op
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_log_op_getlen_pt
typedef|typedef
name|size_t
function_decl|(
modifier|*
name|ngx_http_log_op_getlen_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_log_op_compile_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_http_log_op_compile_pt
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_http_log_op_t
modifier|*
name|op
parameter_list|,
name|ngx_str_t
modifier|*
name|value
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_http_log_op_s
struct|struct
name|ngx_http_log_op_s
block|{
DECL|member|len
name|size_t
name|len
decl_stmt|;
DECL|member|getlen
name|ngx_http_log_op_getlen_pt
name|getlen
decl_stmt|;
DECL|member|run
name|ngx_http_log_op_run_pt
name|run
decl_stmt|;
DECL|member|data
name|uintptr_t
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon297d11240108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|len
name|size_t
name|len
decl_stmt|;
DECL|member|compile
name|ngx_http_log_op_compile_pt
name|compile
decl_stmt|;
DECL|member|getlen
name|ngx_http_log_op_getlen_pt
name|getlen
decl_stmt|;
DECL|member|run
name|ngx_http_log_op_run_pt
name|run
decl_stmt|;
DECL|typedef|ngx_http_log_op_name_t
block|}
name|ngx_http_log_op_name_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_http_log_op_name_t
name|ngx_http_log_fmt_ops
index|[]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_LOG_MODULE_H_INCLUDED_ */
end_comment

end_unit

