begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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

begin_if
if|#
directive|if
operator|(
name|NGX_PCRE2
operator|)
end_if

begin_define
DECL|macro|PCRE2_CODE_UNIT_WIDTH
define|#
directive|define
name|PCRE2_CODE_UNIT_WIDTH
value|8
end_define

begin_include
include|#
directive|include
file|<pcre2.h>
end_include

begin_define
DECL|macro|NGX_REGEX_NO_MATCHED
define|#
directive|define
name|NGX_REGEX_NO_MATCHED
value|PCRE2_ERROR_NOMATCH
end_define

begin_comment
DECL|macro|NGX_REGEX_NO_MATCHED
comment|/* -1 */
end_comment

begin_typedef
DECL|typedef|ngx_regex_t
typedef|typedef
name|pcre2_code
name|ngx_regex_t
typedef|;
end_typedef

begin_else
else|#
directive|else
end_else

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

begin_typedef
DECL|struct|__anon2c7dda150108
typedef|typedef
struct|struct
block|{
DECL|member|code
name|pcre
modifier|*
name|code
decl_stmt|;
DECL|member|extra
name|pcre_extra
modifier|*
name|extra
decl_stmt|;
DECL|typedef|ngx_regex_t
block|}
name|ngx_regex_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_REGEX_CASELESS
define|#
directive|define
name|NGX_REGEX_CASELESS
value|0x00000001
end_define

begin_define
DECL|macro|NGX_REGEX_MULTILINE
define|#
directive|define
name|NGX_REGEX_MULTILINE
value|0x00000002
end_define

begin_typedef
DECL|struct|__anon2c7dda150208
typedef|typedef
struct|struct
block|{
DECL|member|pattern
name|ngx_str_t
name|pattern
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|options
name|ngx_uint_t
name|options
decl_stmt|;
DECL|member|regex
name|ngx_regex_t
modifier|*
name|regex
decl_stmt|;
DECL|member|captures
name|int
name|captures
decl_stmt|;
DECL|member|named_captures
name|int
name|named_captures
decl_stmt|;
DECL|member|name_size
name|int
name|name_size
decl_stmt|;
DECL|member|names
name|u_char
modifier|*
name|names
decl_stmt|;
DECL|member|err
name|ngx_str_t
name|err
decl_stmt|;
DECL|typedef|ngx_regex_compile_t
block|}
name|ngx_regex_compile_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c7dda150308
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
name|ngx_int_t
name|ngx_regex_compile
parameter_list|(
name|ngx_regex_compile_t
modifier|*
name|rc
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
name|ngx_uint_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_PCRE2
operator|)
end_if

begin_define
DECL|macro|ngx_regex_exec_n
define|#
directive|define
name|ngx_regex_exec_n
value|"pcre2_match()"
end_define

begin_else
else|#
directive|else
end_else

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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_REGEX_H_INCLUDED_ */
end_comment

end_unit

