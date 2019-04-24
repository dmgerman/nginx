begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_STREAM_SCRIPT_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_STREAM_SCRIPT_H_INCLUDED_
define|#
directive|define
name|_NGX_STREAM_SCRIPT_H_INCLUDED_
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
file|<ngx_stream.h>
end_include

begin_typedef
DECL|struct|__anon28b1fad50108
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
name|ngx_stream_variable_value_t
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
DECL|member|session
name|ngx_stream_session_t
modifier|*
name|session
decl_stmt|;
DECL|typedef|ngx_stream_script_engine_t
block|}
name|ngx_stream_script_engine_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28b1fad50208
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
DECL|member|size
name|ngx_uint_t
name|size
decl_stmt|;
DECL|member|main
name|void
modifier|*
decl|main
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
DECL|typedef|ngx_stream_script_compile_t
block|}
name|ngx_stream_script_compile_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28b1fad50308
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
DECL|union|__anon28b1fad5040a
union|union
block|{
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|u
block|}
name|u
union|;
DECL|typedef|ngx_stream_complex_value_t
block|}
name|ngx_stream_complex_value_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28b1fad50508
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
name|ngx_stream_complex_value_t
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
DECL|typedef|ngx_stream_compile_complex_value_t
block|}
name|ngx_stream_compile_complex_value_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_script_code_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_stream_script_code_pt
function_decl|)
parameter_list|(
name|ngx_stream_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_stream_script_len_code_pt
typedef|typedef
name|size_t
function_decl|(
modifier|*
name|ngx_stream_script_len_code_pt
function_decl|)
parameter_list|(
name|ngx_stream_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon28b1fad50608
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_stream_script_code_pt
name|code
decl_stmt|;
DECL|member|len
name|uintptr_t
name|len
decl_stmt|;
DECL|typedef|ngx_stream_script_copy_code_t
block|}
name|ngx_stream_script_copy_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28b1fad50708
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_stream_script_code_pt
name|code
decl_stmt|;
DECL|member|index
name|uintptr_t
name|index
decl_stmt|;
DECL|typedef|ngx_stream_script_var_code_t
block|}
name|ngx_stream_script_var_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28b1fad50808
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_stream_script_code_pt
name|code
decl_stmt|;
DECL|member|n
name|uintptr_t
name|n
decl_stmt|;
DECL|typedef|ngx_stream_script_copy_capture_code_t
block|}
name|ngx_stream_script_copy_capture_code_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28b1fad50908
typedef|typedef
struct|struct
block|{
DECL|member|code
name|ngx_stream_script_code_pt
name|code
decl_stmt|;
DECL|member|conf_prefix
name|uintptr_t
name|conf_prefix
decl_stmt|;
DECL|typedef|ngx_stream_script_full_name_code_t
block|}
name|ngx_stream_script_full_name_code_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_stream_script_flush_complex_value
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_complex_value_t
modifier|*
name|val
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_complex_value
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_complex_value_t
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
name|size_t
name|ngx_stream_complex_value_size
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_complex_value_t
modifier|*
name|val
parameter_list|,
name|size_t
name|default_value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_compile_complex_value
parameter_list|(
name|ngx_stream_compile_complex_value_t
modifier|*
name|ccv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_stream_set_complex_value_slot
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
name|char
modifier|*
name|ngx_stream_set_complex_value_size_slot
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
name|ngx_stream_script_variables_count
parameter_list|(
name|ngx_str_t
modifier|*
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_stream_script_compile
parameter_list|(
name|ngx_stream_script_compile_t
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_stream_script_run
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
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
name|ngx_stream_script_flush_no_cacheable_variables
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
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
name|ngx_stream_script_add_code
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
name|ngx_stream_script_copy_len_code
parameter_list|(
name|ngx_stream_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_stream_script_copy_code
parameter_list|(
name|ngx_stream_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_stream_script_copy_var_len_code
parameter_list|(
name|ngx_stream_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_stream_script_copy_var_code
parameter_list|(
name|ngx_stream_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_stream_script_copy_capture_len_code
parameter_list|(
name|ngx_stream_script_engine_t
modifier|*
name|e
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_stream_script_copy_capture_code
parameter_list|(
name|ngx_stream_script_engine_t
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
comment|/* _NGX_STREAM_SCRIPT_H_INCLUDED_ */
end_comment

end_unit

