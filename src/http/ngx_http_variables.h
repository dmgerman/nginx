begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_VARIABLES_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_VARIABLES_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_VARIABLES_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_VAR_NOT_FOUND
define|#
directive|define
name|NGX_HTTP_VAR_NOT_FOUND
value|(ngx_http_variable_value_t *) -1
end_define

begin_typedef
DECL|struct|__anon27549b4b0108
typedef|typedef
struct|struct
block|{
DECL|member|value
name|ngx_uint_t
name|value
decl_stmt|;
DECL|member|text
name|ngx_str_t
name|text
decl_stmt|;
DECL|typedef|ngx_http_variable_value_t
block|}
name|ngx_http_variable_value_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_variable_t
typedef|typedef
name|struct
name|ngx_http_variable_s
name|ngx_http_variable_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
name|ngx_http_variable_value_t
modifier|*
DECL|typedef|ngx_http_get_variable_pt
function_decl|(
modifier|*
name|ngx_http_get_variable_pt
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

begin_define
DECL|macro|NGX_HTTP_VAR_CHANGABLE
define|#
directive|define
name|NGX_HTTP_VAR_CHANGABLE
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_VAR_NOCACHABLE
define|#
directive|define
name|NGX_HTTP_VAR_NOCACHABLE
value|2
end_define

begin_define
DECL|macro|NGX_HTTP_VAR_INDEXED
define|#
directive|define
name|NGX_HTTP_VAR_INDEXED
value|4
end_define

begin_struct
DECL|struct|ngx_http_variable_s
struct|struct
name|ngx_http_variable_s
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
comment|/* must be first to build the hash */
DECL|member|handler
name|ngx_http_get_variable_pt
name|handler
decl_stmt|;
DECL|member|data
name|uintptr_t
name|data
decl_stmt|;
DECL|member|flags
name|ngx_uint_t
name|flags
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|ngx_http_variable_t
modifier|*
name|ngx_http_add_variable
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_get_variable_index
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
name|ngx_http_variable_value_t
modifier|*
name|ngx_http_get_indexed_variable
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_uint_t
name|index
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_http_variable_value_t
modifier|*
name|ngx_http_get_variable
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_variables_add_core_vars
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_variables_init_vars
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_VARIABLES_H_INCLUDED_ */
end_comment

end_unit

