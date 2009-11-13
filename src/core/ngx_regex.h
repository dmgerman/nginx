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
value|PCRE_ERROR_NOMATCH
end_define

begin_comment
DECL|macro|NGX_REGEX_NO_MATCHED
comment|/* -1 */
end_comment

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

begin_typedef
DECL|struct|__anon2a1f187f0108
typedef|typedef
struct|struct
block|{
DECL|member|regex
name|ngx_regex_t
modifier|*
name|regex
decl_stmt|;
DECL|member|name
name|u_char
modifier|*
name|name
decl_stmt|;
DECL|typedef|ngx_regex_elt_t
block|}
name|ngx_regex_elt_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_regex_init
parameter_list|(
name|void
parameter_list|)
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
name|ngx_int_t
name|ngx_regex_capture_count
parameter_list|(
name|ngx_regex_t
modifier|*
name|re
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_regex_exec (re,s,captures,size)
define|#
directive|define
name|ngx_regex_exec
parameter_list|(
name|re
parameter_list|,
name|s
parameter_list|,
name|captures
parameter_list|,
name|size
parameter_list|)
define|\
value|pcre_exec(re, NULL, (const char *) (s)->data, (s)->len, 0, 0,            \               captures, size)
end_define

begin_function_decl
name|ngx_int_t
name|ngx_regex_exec_array
parameter_list|(
name|ngx_array_t
modifier|*
name|a
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|,
name|ngx_log_t
modifier|*
name|log
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

begin_define
DECL|macro|ngx_regex_capture_count_n
define|#
directive|define
name|ngx_regex_capture_count_n
value|"pcre_fullinfo()"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_REGEX_H_INCLUDED_ */
end_comment

end_unit

