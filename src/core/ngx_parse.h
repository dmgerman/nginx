begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_PARSE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_PARSE_H_INCLUDED_
define|#
directive|define
name|_NGX_PARSE_H_INCLUDED_
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
name|ssize_t
name|ngx_parse_size
parameter_list|(
name|ngx_str_t
modifier|*
name|line
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|off_t
name|ngx_parse_offset
parameter_list|(
name|ngx_str_t
modifier|*
name|line
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_parse_time
parameter_list|(
name|ngx_str_t
modifier|*
name|line
parameter_list|,
name|ngx_uint_t
name|is_sec
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PARSE_H_INCLUDED_ */
end_comment

end_unit

