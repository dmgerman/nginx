begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

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
DECL|struct|__anon2c7202890108
typedef|typedef
struct|struct
block|{
DECL|member|lengths
name|ngx_array_t
modifier|*
name|lengths
decl_stmt|;
DECL|member|values
name|ngx_array_t
modifier|*
name|values
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|code
name|unsigned
name|code
range|:
literal|10
decl_stmt|;
DECL|member|test_dir
name|unsigned
name|test_dir
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_http_try_file_t
block|}
name|ngx_http_try_file_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c7202890208
typedef|typedef
struct|struct
block|{
DECL|member|try_files
name|ngx_http_try_file_t
modifier|*
name|try_files
decl_stmt|;
DECL|typedef|ngx_http_try_files_loc_conf_t
block|}
name|ngx_http_try_files_loc_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_try_files_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_try_files
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
specifier|static
name|void
modifier|*
name|ngx_http_try_files_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_try_files_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_try_files_commands
specifier|static
name|ngx_command_t
name|ngx_http_try_files_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"try_files"
argument_list|)
block|,
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_2MORE
block|,
name|ngx_http_try_files
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_try_files_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_try_files_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_try_files_init
block|,
comment|/* postconfiguration */
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|NULL
block|,
comment|/* create server configuration */
name|NULL
block|,
comment|/* merge server configuration */
name|ngx_http_try_files_create_loc_conf
block|,
comment|/* create location configuration */
name|NULL
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_try_files_module
name|ngx_module_t
name|ngx_http_try_files_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_try_files_module_ctx
block|,
comment|/* module context */
name|ngx_http_try_files_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|NULL
block|,
comment|/* init module */
name|NULL
block|,
comment|/* init process */
name|NULL
block|,
comment|/* init thread */
name|NULL
block|,
comment|/* exit thread */
name|NULL
block|,
comment|/* exit process */
name|NULL
block|,
comment|/* exit master */
name|NGX_MODULE_V1_PADDING
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_try_files_handler (ngx_http_request_t * r)
name|ngx_http_try_files_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|size_t
name|len
decl_stmt|,
name|root
decl_stmt|,
name|alias
decl_stmt|,
name|reserve
decl_stmt|,
name|allocated
decl_stmt|;
name|u_char
modifier|*
name|p
decl_stmt|,
modifier|*
name|name
decl_stmt|;
name|ngx_str_t
name|path
decl_stmt|,
name|args
decl_stmt|;
name|ngx_uint_t
name|test_dir
decl_stmt|;
name|ngx_http_try_file_t
modifier|*
name|tf
decl_stmt|;
name|ngx_open_file_info_t
name|of
decl_stmt|;
name|ngx_http_script_code_pt
name|code
decl_stmt|;
name|ngx_http_script_engine_t
name|e
decl_stmt|;
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
name|ngx_http_script_len_code_pt
name|lcode
decl_stmt|;
name|ngx_http_try_files_loc_conf_t
modifier|*
name|tlcf
decl_stmt|;
name|tlcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_try_files_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|tlcf
operator|->
name|try_files
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"try files handler"
argument_list|)
expr_stmt|;
name|allocated
operator|=
literal|0
expr_stmt|;
name|root
operator|=
literal|0
expr_stmt|;
name|name
operator|=
name|NULL
expr_stmt|;
comment|/* suppress MSVC warning */
name|path
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
name|tf
operator|=
name|tlcf
operator|->
name|try_files
expr_stmt|;
name|clcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
name|alias
operator|=
name|clcf
operator|->
name|alias
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|tf
operator|->
name|lengths
condition|)
block|{
name|ngx_memzero
argument_list|(
operator|&
name|e
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_script_engine_t
argument_list|)
argument_list|)
expr_stmt|;
name|e
operator|.
name|ip
operator|=
name|tf
operator|->
name|lengths
operator|->
name|elts
expr_stmt|;
name|e
operator|.
name|request
operator|=
name|r
expr_stmt|;
comment|/* 1 is for terminating '\0' as in static names */
name|len
operator|=
literal|1
expr_stmt|;
while|while
condition|(
operator|*
operator|(
name|uintptr_t
operator|*
operator|)
name|e
operator|.
name|ip
condition|)
block|{
name|lcode
operator|=
operator|*
operator|(
name|ngx_http_script_len_code_pt
operator|*
operator|)
name|e
operator|.
name|ip
expr_stmt|;
name|len
operator|+=
name|lcode
argument_list|(
operator|&
name|e
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|len
operator|=
name|tf
operator|->
name|name
operator|.
name|len
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|alias
condition|)
block|{
name|reserve
operator|=
name|len
operator|>
name|r
operator|->
name|uri
operator|.
name|len
condition|?
name|len
operator|-
name|r
operator|->
name|uri
operator|.
name|len
else|:
literal|0
expr_stmt|;
block|}
if|else if
condition|(
name|alias
operator|==
name|NGX_MAX_SIZE_T_VALUE
condition|)
block|{
name|reserve
operator|=
name|len
expr_stmt|;
block|}
else|else
block|{
name|reserve
operator|=
name|len
operator|>
name|r
operator|->
name|uri
operator|.
name|len
operator|-
name|alias
condition|?
name|len
operator|-
operator|(
name|r
operator|->
name|uri
operator|.
name|len
operator|-
name|alias
operator|)
else|:
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|reserve
operator|>
name|allocated
operator|||
operator|!
name|allocated
condition|)
block|{
comment|/* 16 bytes are preallocation */
name|allocated
operator|=
name|reserve
operator|+
literal|16
expr_stmt|;
if|if
condition|(
name|ngx_http_map_uri_to_path
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|,
operator|&
name|root
argument_list|,
name|allocated
argument_list|)
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|name
operator|=
name|path
operator|.
name|data
operator|+
name|root
expr_stmt|;
block|}
if|if
condition|(
name|tf
operator|->
name|values
operator|==
name|NULL
condition|)
block|{
comment|/* tf->name.len includes the terminating '\0' */
name|ngx_memcpy
argument_list|(
name|name
argument_list|,
name|tf
operator|->
name|name
operator|.
name|data
argument_list|,
name|tf
operator|->
name|name
operator|.
name|len
argument_list|)
expr_stmt|;
name|path
operator|.
name|len
operator|=
operator|(
name|name
operator|+
name|tf
operator|->
name|name
operator|.
name|len
operator|-
literal|1
operator|)
operator|-
name|path
operator|.
name|data
expr_stmt|;
block|}
else|else
block|{
name|e
operator|.
name|ip
operator|=
name|tf
operator|->
name|values
operator|->
name|elts
expr_stmt|;
name|e
operator|.
name|pos
operator|=
name|name
expr_stmt|;
name|e
operator|.
name|flushed
operator|=
literal|1
expr_stmt|;
while|while
condition|(
operator|*
operator|(
name|uintptr_t
operator|*
operator|)
name|e
operator|.
name|ip
condition|)
block|{
name|code
operator|=
operator|*
operator|(
name|ngx_http_script_code_pt
operator|*
operator|)
name|e
operator|.
name|ip
expr_stmt|;
name|code
argument_list|(
operator|(
name|ngx_http_script_engine_t
operator|*
operator|)
operator|&
name|e
argument_list|)
expr_stmt|;
block|}
name|path
operator|.
name|len
operator|=
name|e
operator|.
name|pos
operator|-
name|path
operator|.
name|data
expr_stmt|;
operator|*
name|e
operator|.
name|pos
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|alias
operator|&&
name|alias
operator|!=
name|NGX_MAX_SIZE_T_VALUE
operator|&&
name|ngx_strncmp
argument_list|(
name|name
argument_list|,
name|r
operator|->
name|uri
operator|.
name|data
argument_list|,
name|alias
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_memmove
argument_list|(
name|name
argument_list|,
name|name
operator|+
name|alias
argument_list|,
name|len
operator|-
name|alias
argument_list|)
expr_stmt|;
name|path
operator|.
name|len
operator|-=
name|alias
expr_stmt|;
block|}
block|}
name|test_dir
operator|=
name|tf
operator|->
name|test_dir
expr_stmt|;
name|tf
operator|++
expr_stmt|;
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"trying to use %s: \"%s\" \"%s\""
argument_list|,
name|test_dir
condition|?
literal|"dir"
else|:
literal|"file"
argument_list|,
name|name
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|tf
operator|->
name|lengths
operator|==
name|NULL
operator|&&
name|tf
operator|->
name|name
operator|.
name|len
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|tf
operator|->
name|code
condition|)
block|{
return|return
name|tf
operator|->
name|code
return|;
block|}
name|path
operator|.
name|len
operator|-=
name|root
expr_stmt|;
name|path
operator|.
name|data
operator|+=
name|root
expr_stmt|;
if|if
condition|(
name|path
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'@'
condition|)
block|{
operator|(
name|void
operator|)
name|ngx_http_named_location
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|ngx_http_split_args
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|,
operator|&
name|args
argument_list|)
expr_stmt|;
operator|(
name|void
operator|)
name|ngx_http_internal_redirect
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|,
operator|&
name|args
argument_list|)
expr_stmt|;
block|}
name|ngx_http_finalize_request
argument_list|(
name|r
argument_list|,
name|NGX_DONE
argument_list|)
expr_stmt|;
return|return
name|NGX_DONE
return|;
block|}
name|ngx_memzero
argument_list|(
operator|&
name|of
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_open_file_info_t
argument_list|)
argument_list|)
expr_stmt|;
name|of
operator|.
name|read_ahead
operator|=
name|clcf
operator|->
name|read_ahead
expr_stmt|;
name|of
operator|.
name|directio
operator|=
name|clcf
operator|->
name|directio
expr_stmt|;
name|of
operator|.
name|valid
operator|=
name|clcf
operator|->
name|open_file_cache_valid
expr_stmt|;
name|of
operator|.
name|min_uses
operator|=
name|clcf
operator|->
name|open_file_cache_min_uses
expr_stmt|;
name|of
operator|.
name|test_only
operator|=
literal|1
expr_stmt|;
name|of
operator|.
name|errors
operator|=
name|clcf
operator|->
name|open_file_cache_errors
expr_stmt|;
name|of
operator|.
name|events
operator|=
name|clcf
operator|->
name|open_file_cache_events
expr_stmt|;
if|if
condition|(
name|ngx_http_set_disable_symlinks
argument_list|(
name|r
argument_list|,
name|clcf
argument_list|,
operator|&
name|path
argument_list|,
operator|&
name|of
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
if|if
condition|(
name|ngx_open_cached_file
argument_list|(
name|clcf
operator|->
name|open_file_cache
argument_list|,
operator|&
name|path
argument_list|,
operator|&
name|of
argument_list|,
name|r
operator|->
name|pool
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
if|if
condition|(
name|of
operator|.
name|err
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
if|if
condition|(
name|of
operator|.
name|err
operator|!=
name|NGX_ENOENT
operator|&&
name|of
operator|.
name|err
operator|!=
name|NGX_ENOTDIR
operator|&&
name|of
operator|.
name|err
operator|!=
name|NGX_ENAMETOOLONG
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
name|of
operator|.
name|err
argument_list|,
literal|"%s \"%s\" failed"
argument_list|,
name|of
operator|.
name|failed
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
continue|continue;
block|}
if|if
condition|(
name|of
operator|.
name|is_dir
operator|!=
name|test_dir
condition|)
block|{
continue|continue;
block|}
name|path
operator|.
name|len
operator|-=
name|root
expr_stmt|;
name|path
operator|.
name|data
operator|+=
name|root
expr_stmt|;
if|if
condition|(
operator|!
name|alias
condition|)
block|{
name|r
operator|->
name|uri
operator|=
name|path
expr_stmt|;
block|}
if|else if
condition|(
name|alias
operator|==
name|NGX_MAX_SIZE_T_VALUE
condition|)
block|{
if|if
condition|(
operator|!
name|test_dir
condition|)
block|{
name|r
operator|->
name|uri
operator|=
name|path
expr_stmt|;
name|r
operator|->
name|add_uri_to_alias
operator|=
literal|1
expr_stmt|;
block|}
block|}
else|else
block|{
name|name
operator|=
name|r
operator|->
name|uri
operator|.
name|data
expr_stmt|;
name|r
operator|->
name|uri
operator|.
name|len
operator|=
name|alias
operator|+
name|path
operator|.
name|len
expr_stmt|;
name|r
operator|->
name|uri
operator|.
name|data
operator|=
name|ngx_pnalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|r
operator|->
name|uri
operator|.
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|uri
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|r
operator|->
name|uri
operator|.
name|len
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|p
operator|=
name|ngx_copy
argument_list|(
name|r
operator|->
name|uri
operator|.
name|data
argument_list|,
name|name
argument_list|,
name|alias
argument_list|)
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|p
argument_list|,
name|path
operator|.
name|data
argument_list|,
name|path
operator|.
name|len
argument_list|)
expr_stmt|;
block|}
name|ngx_http_set_exten
argument_list|(
name|r
argument_list|)
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"try file uri: \"%V\""
argument_list|,
operator|&
name|r
operator|->
name|uri
argument_list|)
expr_stmt|;
return|return
name|NGX_DECLINED
return|;
block|}
comment|/* not reached */
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_try_files (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_try_files
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
block|{
name|ngx_http_try_files_loc_conf_t
modifier|*
name|tlcf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_int_t
name|code
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_http_try_file_t
modifier|*
name|tf
decl_stmt|;
name|ngx_http_script_compile_t
name|sc
decl_stmt|;
if|if
condition|(
name|tlcf
operator|->
name|try_files
condition|)
block|{
return|return
literal|"is duplicate"
return|;
block|}
name|tf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|cf
operator|->
name|args
operator|->
name|nelts
operator|*
sizeof|sizeof
argument_list|(
name|ngx_http_try_file_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|tlcf
operator|->
name|try_files
operator|=
name|tf
expr_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cf
operator|->
name|args
operator|->
name|nelts
operator|-
literal|1
condition|;
name|i
operator|++
control|)
block|{
name|tf
index|[
name|i
index|]
operator|.
name|name
operator|=
name|value
index|[
name|i
operator|+
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|tf
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|>
literal|0
operator|&&
name|tf
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
index|[
name|tf
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|-
literal|1
index|]
operator|==
literal|'/'
operator|&&
name|i
operator|+
literal|2
operator|<
name|cf
operator|->
name|args
operator|->
name|nelts
condition|)
block|{
name|tf
index|[
name|i
index|]
operator|.
name|test_dir
operator|=
literal|1
expr_stmt|;
name|tf
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|--
expr_stmt|;
name|tf
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
index|[
name|tf
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
name|n
operator|=
name|ngx_http_script_variables_count
argument_list|(
operator|&
name|tf
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
condition|)
block|{
name|ngx_memzero
argument_list|(
operator|&
name|sc
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_script_compile_t
argument_list|)
argument_list|)
expr_stmt|;
name|sc
operator|.
name|cf
operator|=
name|cf
expr_stmt|;
name|sc
operator|.
name|source
operator|=
operator|&
name|tf
index|[
name|i
index|]
operator|.
name|name
expr_stmt|;
name|sc
operator|.
name|lengths
operator|=
operator|&
name|tf
index|[
name|i
index|]
operator|.
name|lengths
expr_stmt|;
name|sc
operator|.
name|values
operator|=
operator|&
name|tf
index|[
name|i
index|]
operator|.
name|values
expr_stmt|;
name|sc
operator|.
name|variables
operator|=
name|n
expr_stmt|;
name|sc
operator|.
name|complete_lengths
operator|=
literal|1
expr_stmt|;
name|sc
operator|.
name|complete_values
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ngx_http_script_compile
argument_list|(
operator|&
name|sc
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
else|else
block|{
comment|/* add trailing '\0' to length */
name|tf
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
name|tf
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|name
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'='
condition|)
block|{
name|code
operator|=
name|ngx_atoi
argument_list|(
name|tf
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|name
operator|.
name|data
operator|+
literal|1
argument_list|,
name|tf
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|name
operator|.
name|len
operator|-
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
name|code
operator|==
name|NGX_ERROR
operator|||
name|code
operator|>
literal|999
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid code \"%*s\""
argument_list|,
name|tf
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|name
operator|.
name|len
operator|-
literal|1
argument_list|,
name|tf
index|[
name|i
operator|-
literal|1
index|]
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|tf
index|[
name|i
index|]
operator|.
name|code
operator|=
name|code
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_try_files_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_try_files_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_try_files_loc_conf_t
modifier|*
name|tlcf
decl_stmt|;
name|tlcf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_try_files_loc_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tlcf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
comment|/*      * set by ngx_pcalloc():      *      *     tlcf->try_files = NULL;      */
return|return
name|tlcf
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_try_files_init (ngx_conf_t * cf)
name|ngx_http_try_files_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_handler_pt
modifier|*
name|h
decl_stmt|;
name|ngx_http_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
name|cmcf
operator|=
name|ngx_http_conf_get_module_main_conf
argument_list|(
name|cf
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
name|h
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|cmcf
operator|->
name|phases
index|[
name|NGX_HTTP_PRECONTENT_PHASE
index|]
operator|.
name|handlers
argument_list|)
expr_stmt|;
if|if
condition|(
name|h
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
operator|*
name|h
operator|=
name|ngx_http_try_files_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit
