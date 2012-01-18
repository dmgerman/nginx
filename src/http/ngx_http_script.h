begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_SCRIPT_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_SCRIPT_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_SCRIPT_H_INCLUDED_
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
DECL|struct|__anon2baa37ed0108
typedef|typedef
struct|struct
block|{
DECL|member|ip
name|u_char
modifier|*
name|ip
decl_stmt|;
DECL|member|pos
name|u_char
modifier|*
name|pos
decl_stmt|;
DECL|member|sp
name|ngx_http_variable_value_t
modifier|*
name|sp
decl_stmt|;
DECL|member|buf
name|ngx_str_t
name|buf
decl_stmt|;
DECL|member|line
name|ngx_str_t
name|line
decl_stmt|;
comment|/* the start of the rewritten arguments */
DECL|member|args
name|u_char
modifier|*
name|args
decl_stmt|;
DECL|member|flushed
name|unsigned
name|flushed
range|:
literal|1
decl_stmt|;
DECL|member|skip
name|unsigned
name|skip
range|:
literal|1
decl_stmt|;
DECL|member|quote
name|unsigned
name|quote
range|:
literal|1
decl_stmt|;
DECL|member|is_args
name|unsigned
name|is_args
range|:
literal|1
decl_stmt|;
DECL|member|log
name|unsigned
name|log
range|:
literal|1
decl_stmt|;
DECL|member|status
name|ngx_int_t
name|status
decl_stmt|;
DECL|member|request
name|ngx_http_request_t
modifier|*
name|request
decl_stmt|;
DECL|typedef|ngx_http_script_engine_t
block|}
name|ngx_http_script_engine_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0208
typedef|typedef
struct|struct
block|{
DECL|member|cf
name|ngx_conf_t
modifier|*
name|cf
decl_stmt|;
DECL|member|source
name|ngx_str_t
modifier|*
name|source
decl_stmt|;
DECL|member|flushes
name|ngx_array_t
modifier|*
modifier|*
name|flushes
decl_stmt|;
DECL|member|lengths
name|ngx_array_t
modifier|*
modifier|*
name|lengths
decl_stmt|;
DECL|member|values
name|ngx_array_t
modifier|*
modifier|*
name|values
decl_stmt|;
DECL|member|variables
name|ngx_uint_t
name|variables
decl_stmt|;
DECL|member|ncaptures
name|ngx_uint_t
name|ncaptures
decl_stmt|;
DECL|member|captures_mask
name|ngx_uint_t
name|captures_mask
decl_stmt|;
DECL|member|size
name|ngx_uint_t
name|size
decl_stmt|;
DECL|member|main
name|void
modifier|*
decl|main
decl_stmt|;
DECL|member|compile_args
name|unsigned
name|compile_args
range|:
literal|1
decl_stmt|;
DECL|member|complete_lengths
name|unsigned
name|complete_lengths
range|:
literal|1
decl_stmt|;
DECL|member|complete_values
name|unsigned
name|complete_values
range|:
literal|1
decl_stmt|;
DECL|member|zero
name|unsigned
name|zero
range|:
literal|1
decl_stmt|;
DECL|member|conf_prefix
name|unsigned
name|conf_prefix
range|:
literal|1
decl_stmt|;
DECL|member|root_prefix
name|unsigned
name|root_prefix
range|:
literal|1
decl_stmt|;
DECL|member|dup_capture
name|unsigned
name|dup_capture
range|:
literal|1
decl_stmt|;
DECL|member|args
name|unsigned
name|args
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_script_compile_t
block|}
name|ngx_http_script_compile_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0308
typedef|typedef
struct|struct
block|{
DECL|member|value
name|ngx_str_t
name|value
decl_stmt|;
DECL|member|flushes
name|ngx_uint_t
modifier|*
name|flushes
decl_stmt|;
DECL|member|lengths
name|void
modifier|*
name|lengths
decl_stmt|;
DECL|member|values
name|void
modifier|*
name|values
decl_stmt|;
DECL|typedef|ngx_http_complex_value_t
block|}
name|ngx_http_complex_value_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0408
typedef|typedef
struct|struct
block|{
DECL|member|cf
name|ngx_conf_t
modifier|*
name|cf
decl_stmt|;
DECL|member|value
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
DECL|member|complex_value
name|ngx_http_complex_value_t
modifier|*
name|complex_value
decl_stmt|;
DECL|member|zero
name|unsigned
name|zero
range|:
literal|1
decl_stmt|;
DECL|member|conf_prefix
name|unsigned
name|conf_prefix
range|:
literal|1
decl_stmt|;
DECL|member|root_prefix
name|unsigned
name|root_prefix
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_compile_complex_value_t
block|}
name|ngx_http_compile_complex_value_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_script_code_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_http_script_code_pt
function_decl|)
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_script_len_code_pt
typedef|typedef
name|size_t
function_decl|(
modifier|*
name|ngx_http_script_len_code_pt
function_decl|)
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0508
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|len
name|uintptr_t
name|len
decl_stmt|;
DECL|typedef|ngx_http_script_copy_code_t
block|}
name|ngx_http_script_copy_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0608
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|index
name|uintptr_t
name|index
decl_stmt|;
DECL|typedef|ngx_http_script_var_code_t
block|}
name|ngx_http_script_var_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0708
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|handler
name|ngx_http_set_variable_pt
name|handler
decl_stmt|;
DECL|member|data
name|uintptr_t
name|data
decl_stmt|;
DECL|typedef|ngx_http_script_var_handler_code_t
block|}
name|ngx_http_script_var_handler_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0808
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|n
name|uintptr_t
name|n
decl_stmt|;
DECL|typedef|ngx_http_script_copy_capture_code_t
block|}
name|ngx_http_script_copy_capture_code_t
typedef|;
end_typedef

begin_if
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
end_if

begin_typedef
DECL|struct|__anon2baa37ed0908
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|regex
name|ngx_http_regex_t
modifier|*
name|regex
decl_stmt|;
DECL|member|lengths
name|ngx_array_t
modifier|*
name|lengths
decl_stmt|;
DECL|member|size
name|uintptr_t
name|size
decl_stmt|;
DECL|member|status
name|uintptr_t
name|status
decl_stmt|;
DECL|member|next
name|uintptr_t
name|next
decl_stmt|;
DECL|member|test
name|uintptr_t
name|test
range|:
literal|1
decl_stmt|;
DECL|member|negative_test
name|uintptr_t
name|negative_test
range|:
literal|1
decl_stmt|;
DECL|member|uri
name|uintptr_t
name|uri
range|:
literal|1
decl_stmt|;
DECL|member|args
name|uintptr_t
name|args
range|:
literal|1
decl_stmt|;
comment|/* add the r->args to the new arguments */
DECL|member|add_args
name|uintptr_t
name|add_args
range|:
literal|1
decl_stmt|;
DECL|member|redirect
name|uintptr_t
name|redirect
range|:
literal|1
decl_stmt|;
DECL|member|break_cycle
name|uintptr_t
name|break_cycle
range|:
literal|1
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|typedef|ngx_http_script_regex_code_t
block|}
name|ngx_http_script_regex_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0a08
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|uri
name|uintptr_t
name|uri
range|:
literal|1
decl_stmt|;
DECL|member|args
name|uintptr_t
name|args
range|:
literal|1
decl_stmt|;
comment|/* add the r->args to the new arguments */
DECL|member|add_args
name|uintptr_t
name|add_args
range|:
literal|1
decl_stmt|;
DECL|member|redirect
name|uintptr_t
name|redirect
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_script_regex_end_code_t
block|}
name|ngx_http_script_regex_end_code_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2baa37ed0b08
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|conf_prefix
name|uintptr_t
name|conf_prefix
decl_stmt|;
DECL|typedef|ngx_http_script_full_name_code_t
block|}
name|ngx_http_script_full_name_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0c08
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|status
name|uintptr_t
name|status
decl_stmt|;
DECL|member|text
name|ngx_http_complex_value_t
name|text
decl_stmt|;
DECL|typedef|ngx_http_script_return_code_t
block|}
name|ngx_http_script_return_code_t
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon2baa37ed0d03
typedef|typedef
enum|enum
block|{
DECL|enumerator|ngx_http_script_file_plain
name|ngx_http_script_file_plain
init|=
literal|0
block|,
DECL|enumerator|ngx_http_script_file_not_plain
name|ngx_http_script_file_not_plain
block|,
DECL|enumerator|ngx_http_script_file_dir
name|ngx_http_script_file_dir
block|,
DECL|enumerator|ngx_http_script_file_not_dir
name|ngx_http_script_file_not_dir
block|,
DECL|enumerator|ngx_http_script_file_exists
name|ngx_http_script_file_exists
block|,
DECL|enumerator|ngx_http_script_file_not_exists
name|ngx_http_script_file_not_exists
block|,
DECL|enumerator|ngx_http_script_file_exec
name|ngx_http_script_file_exec
block|,
DECL|enumerator|ngx_http_script_file_not_exec
name|ngx_http_script_file_not_exec
DECL|typedef|ngx_http_script_file_op_e
block|}
name|ngx_http_script_file_op_e
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0e08
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|op
name|uintptr_t
name|op
decl_stmt|;
DECL|typedef|ngx_http_script_file_code_t
block|}
name|ngx_http_script_file_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed0f08
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|next
name|uintptr_t
name|next
decl_stmt|;
DECL|member|loc_conf
name|void
modifier|*
modifier|*
name|loc_conf
decl_stmt|;
DECL|typedef|ngx_http_script_if_code_t
block|}
name|ngx_http_script_if_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed1008
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|lengths
name|ngx_array_t
modifier|*
name|lengths
decl_stmt|;
DECL|typedef|ngx_http_script_complex_value_code_t
block|}
name|ngx_http_script_complex_value_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2baa37ed1108
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|member|value
name|uintptr_t
name|value
decl_stmt|;
DECL|member|text_len
name|uintptr_t
name|text_len
decl_stmt|;
DECL|member|text_data
name|uintptr_t
name|text_data
decl_stmt|;
DECL|typedef|ngx_http_script_value_code_t
block|}
name|ngx_http_script_value_code_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_http_script_flush_complex_value
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_complex_value_t
modifier|*
name|val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_complex_value
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_complex_value_t
modifier|*
name|val
parameter_list|,
name|ngx_str_t
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_compile_complex_value
parameter_list|(
name|ngx_http_compile_complex_value_t
modifier|*
name|ccv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_http_set_complex_value_slot
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_test_predicates
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_array_t
modifier|*
name|predicates
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_http_set_predicate_slot
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_uint_t
name|ngx_http_script_variables_count
parameter_list|(
name|ngx_str_t
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_script_compile
parameter_list|(
name|ngx_http_script_compile_t
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_http_script_run
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_str_t
modifier|*
name|value
parameter_list|,
name|void
modifier|*
name|code_lengths
parameter_list|,
name|size_t
name|reserved
parameter_list|,
name|void
modifier|*
name|code_values
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_flush_no_cacheable_variables
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_array_t
modifier|*
name|indices
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_http_script_start_code
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_array_t
modifier|*
modifier|*
name|codes
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_http_script_add_code
parameter_list|(
name|ngx_array_t
modifier|*
name|codes
parameter_list|,
name|size_t
name|size
parameter_list|,
name|void
modifier|*
name|code
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_script_copy_len_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_copy_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_script_copy_var_len_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_copy_var_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_script_copy_capture_len_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_copy_capture_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_script_mark_args_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_start_args_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
end_if

begin_function_decl
name|void
name|ngx_http_script_regex_start_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_regex_end_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_http_script_return_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_break_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_if_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_equal_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_not_equal_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_file_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_complex_value_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_value_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_set_var_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_var_set_handler_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_var_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_script_nop_code
parameter_list|(
name|ngx_http_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_SCRIPT_H_INCLUDED_ */
end_comment

end_unit

