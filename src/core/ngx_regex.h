begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_REGEX_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_REGEX_H_INCLUDED_
define|#
directive|define
name|_NGX_REGEX_H_INCLUDED_
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
file|<pcre.h>
end_include

begin_define
DECL|macro|NGX_REGEX_NO_MATCHED
define|#
directive|define
name|NGX_REGEX_NO_MATCHED
value|-1000
end_define

begin_define
DECL|macro|NGX_REGEX_CASELESS
define|#
directive|define
name|NGX_REGEX_CASELESS
value|PCRE_CASELESS
end_define

begin_typedef
DECL|typedef|ngx_regex_t
typedef|typedef
name|pcre
name|ngx_regex_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_regex_init
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|ngx_regex_t
modifier|*
name|ngx_regex_compile
parameter_list|(
name|ngx_str_t
modifier|*
name|pattern
parameter_list|,
name|ngx_int_t
name|options
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|err
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_uint_t
name|ngx_regex_capture_count
parameter_list|(
name|ngx_regex_t
modifier|*
name|re
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_regex_exec
parameter_list|(
name|ngx_regex_t
modifier|*
name|re
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|,
name|int
modifier|*
name|captures
parameter_list|,
name|ngx_int_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_regex_exec_n
define|#
directive|define
name|ngx_regex_exec_n
value|"pcre_exec()"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_REGEX_H_INCLUDED_ */
end_comment

end_unit

