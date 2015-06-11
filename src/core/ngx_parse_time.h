begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_PARSE_TIME_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_PARSE_TIME_H_INCLUDED_
define|#
directive|define
name|_NGX_PARSE_TIME_H_INCLUDED_
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
name|time_t
name|ngx_parse_http_time
parameter_list|(
name|u_char
modifier|*
name|value
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* compatibility */
end_comment

begin_define
DECL|macro|ngx_http_parse_time (value,len)
define|#
directive|define
name|ngx_http_parse_time
parameter_list|(
name|value
parameter_list|,
name|len
parameter_list|)
value|ngx_parse_http_time(value, len)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PARSE_TIME_H_INCLUDED_ */
end_comment

end_unit

