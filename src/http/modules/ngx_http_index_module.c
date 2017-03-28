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
DECL|struct|__anon29ea84f60108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
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
DECL|typedef|ngx_http_index_t
block|}
name|ngx_http_index_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29ea84f60208
typedef|typedef
struct|struct
block|{
DECL|member|indices
name|ngx_array_t
modifier|*
name|indices
decl_stmt|;
comment|/* array of ngx_http_index_t */
DECL|member|max_index_len
name|size_t
name|max_index_len
decl_stmt|;
DECL|typedef|ngx_http_index_loc_conf_t
block|}
name|ngx_http_index_loc_conf_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_DEFAULT_INDEX
define|#
directive|define
name|NGX_HTTP_DEFAULT_INDEX
value|"index.html"
end_define

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_index_test_dir
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
parameter_list|,
name|u_char
modifier|*
name|path
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_index_error
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
parameter_list|,
name|u_char
modifier|*
name|file
parameter_list|,
name|ngx_err_t
name|err
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_index_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_index_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_index_merge_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|parent
parameter_list|,
name|void
modifier|*
name|child
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_index_set_index
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

begin_decl_stmt
DECL|variable|ngx_http_index_commands
specifier|static
name|ngx_command_t
name|ngx_http_index_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"index"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_http_index_set_index
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
DECL|variable|ngx_http_index_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_index_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_index_init
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
name|ngx_http_index_create_loc_conf
block|,
comment|/* create location configuration */
name|ngx_http_index_merge_loc_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_index_module
name|ngx_module_t
name|ngx_http_index_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_index_module_ctx
block|,
comment|/* module context */
name|ngx_http_index_commands
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

begin_comment
comment|/*  * Try to open/test the first index file before the test of directory  * existence because valid requests should prevail over invalid ones.  * If open()/stat() of a file will fail then stat() of a directory  * should be faster because kernel may have already cached some data.  * Besides, Win32 may return ERROR_PATH_NOT_FOUND (NGX_ENOTDIR) at once.  * Unix has ENOTDIR error; however, it's less helpful than Win32's one:  * it only indicates that path points to a regular file, not a directory.  */
end_comment

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_index_handler (ngx_http_request_t * r)
name|ngx_http_index_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|,
modifier|*
name|name
decl_stmt|;
name|size_t
name|len
decl_stmt|,
name|root
decl_stmt|,
name|reserve
decl_stmt|,
name|allocated
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_str_t
name|path
decl_stmt|,
name|uri
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|dir_tested
decl_stmt|;
name|ngx_http_index_t
modifier|*
name|index
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
name|ngx_http_index_loc_conf_t
modifier|*
name|ilcf
decl_stmt|;
name|ngx_http_script_len_code_pt
name|lcode
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|uri
operator|.
name|data
index|[
name|r
operator|->
name|uri
operator|.
name|len
operator|-
literal|1
index|]
operator|!=
literal|'/'
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|method
operator|&
operator|(
name|NGX_HTTP_GET
operator||
name|NGX_HTTP_HEAD
operator||
name|NGX_HTTP_POST
operator|)
operator|)
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|ilcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_index_module
argument_list|)
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
name|allocated
operator|=
literal|0
expr_stmt|;
name|root
operator|=
literal|0
expr_stmt|;
name|dir_tested
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
name|index
operator|=
name|ilcf
operator|->
name|indices
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
name|ilcf
operator|->
name|indices
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|index
index|[
name|i
index|]
operator|.
name|lengths
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|index
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'/'
condition|)
block|{
return|return
name|ngx_http_internal_redirect
argument_list|(
name|r
argument_list|,
operator|&
name|index
index|[
name|i
index|]
operator|.
name|name
argument_list|,
operator|&
name|r
operator|->
name|args
argument_list|)
return|;
block|}
name|reserve
operator|=
name|ilcf
operator|->
name|max_index_len
expr_stmt|;
name|len
operator|=
name|index
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
expr_stmt|;
block|}
else|else
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
name|index
index|[
name|i
index|]
operator|.
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
name|e
operator|.
name|flushed
operator|=
literal|1
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
comment|/* 16 bytes are preallocation */
name|reserve
operator|=
name|len
operator|+
literal|16
expr_stmt|;
block|}
if|if
condition|(
name|reserve
operator|>
name|allocated
condition|)
block|{
name|name
operator|=
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
name|reserve
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|allocated
operator|=
name|path
operator|.
name|data
operator|+
name|path
operator|.
name|len
operator|-
name|name
expr_stmt|;
block|}
if|if
condition|(
name|index
index|[
name|i
index|]
operator|.
name|values
operator|==
name|NULL
condition|)
block|{
comment|/* index[i].name.len includes the terminating '\0' */
name|ngx_memcpy
argument_list|(
name|name
argument_list|,
name|index
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
argument_list|,
name|index
index|[
name|i
index|]
operator|.
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
name|index
index|[
name|i
index|]
operator|.
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
name|index
index|[
name|i
index|]
operator|.
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
if|if
condition|(
operator|*
name|name
operator|==
literal|'/'
condition|)
block|{
name|uri
operator|.
name|len
operator|=
name|len
operator|-
literal|1
expr_stmt|;
name|uri
operator|.
name|data
operator|=
name|name
expr_stmt|;
return|return
name|ngx_http_internal_redirect
argument_list|(
name|r
argument_list|,
operator|&
name|uri
argument_list|,
operator|&
name|r
operator|->
name|args
argument_list|)
return|;
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
block|}
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
literal|"open index \"%V\""
argument_list|,
operator|&
name|path
argument_list|)
expr_stmt|;
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
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_HTTP
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
if|#
directive|if
operator|(
name|NGX_HAVE_OPENAT
operator|)
if|if
condition|(
name|of
operator|.
name|err
operator|==
name|NGX_EMLINK
operator|||
name|of
operator|.
name|err
operator|==
name|NGX_ELOOP
condition|)
block|{
return|return
name|NGX_HTTP_FORBIDDEN
return|;
block|}
endif|#
directive|endif
if|if
condition|(
name|of
operator|.
name|err
operator|==
name|NGX_ENOTDIR
operator|||
name|of
operator|.
name|err
operator|==
name|NGX_ENAMETOOLONG
operator|||
name|of
operator|.
name|err
operator|==
name|NGX_EACCES
condition|)
block|{
return|return
name|ngx_http_index_error
argument_list|(
name|r
argument_list|,
name|clcf
argument_list|,
name|path
operator|.
name|data
argument_list|,
name|of
operator|.
name|err
argument_list|)
return|;
block|}
if|if
condition|(
operator|!
name|dir_tested
condition|)
block|{
name|rc
operator|=
name|ngx_http_index_test_dir
argument_list|(
name|r
argument_list|,
name|clcf
argument_list|,
name|path
operator|.
name|data
argument_list|,
name|name
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|rc
return|;
block|}
name|dir_tested
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|of
operator|.
name|err
operator|==
name|NGX_ENOENT
condition|)
block|{
continue|continue;
block|}
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
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|uri
operator|.
name|len
operator|=
name|r
operator|->
name|uri
operator|.
name|len
operator|+
name|len
operator|-
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|clcf
operator|->
name|alias
condition|)
block|{
name|uri
operator|.
name|data
operator|=
name|path
operator|.
name|data
operator|+
name|root
expr_stmt|;
block|}
else|else
block|{
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
name|uri
operator|.
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|uri
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|p
operator|=
name|ngx_copy
argument_list|(
name|uri
operator|.
name|data
argument_list|,
name|r
operator|->
name|uri
operator|.
name|data
argument_list|,
name|r
operator|->
name|uri
operator|.
name|len
argument_list|)
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|p
argument_list|,
name|name
argument_list|,
name|len
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
return|return
name|ngx_http_internal_redirect
argument_list|(
name|r
argument_list|,
operator|&
name|uri
argument_list|,
operator|&
name|r
operator|->
name|args
argument_list|)
return|;
block|}
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_index_test_dir (ngx_http_request_t * r,ngx_http_core_loc_conf_t * clcf,u_char * path,u_char * last)
name|ngx_http_index_test_dir
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
parameter_list|,
name|u_char
modifier|*
name|path
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|)
block|{
name|u_char
name|c
decl_stmt|;
name|ngx_str_t
name|dir
decl_stmt|;
name|ngx_open_file_info_t
name|of
decl_stmt|;
name|c
operator|=
operator|*
name|last
expr_stmt|;
if|if
condition|(
name|c
operator|!=
literal|'/'
operator|||
name|path
operator|==
name|last
condition|)
block|{
comment|/* "alias" without trailing slash */
name|c
operator|=
operator|*
operator|(
operator|++
name|last
operator|)
expr_stmt|;
block|}
operator|*
name|last
operator|=
literal|'\0'
expr_stmt|;
name|dir
operator|.
name|len
operator|=
name|last
operator|-
name|path
expr_stmt|;
name|dir
operator|.
name|data
operator|=
name|path
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
literal|"http index check dir: \"%V\""
argument_list|,
operator|&
name|dir
argument_list|)
expr_stmt|;
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
name|test_dir
operator|=
literal|1
expr_stmt|;
name|of
operator|.
name|test_only
operator|=
literal|1
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
name|errors
operator|=
name|clcf
operator|->
name|open_file_cache_errors
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
name|dir
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
name|dir
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
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_OPENAT
operator|)
if|if
condition|(
name|of
operator|.
name|err
operator|==
name|NGX_EMLINK
operator|||
name|of
operator|.
name|err
operator|==
name|NGX_ELOOP
condition|)
block|{
return|return
name|NGX_HTTP_FORBIDDEN
return|;
block|}
endif|#
directive|endif
if|if
condition|(
name|of
operator|.
name|err
operator|==
name|NGX_ENOENT
condition|)
block|{
operator|*
name|last
operator|=
name|c
expr_stmt|;
return|return
name|ngx_http_index_error
argument_list|(
name|r
argument_list|,
name|clcf
argument_list|,
name|dir
operator|.
name|data
argument_list|,
name|NGX_ENOENT
argument_list|)
return|;
block|}
if|if
condition|(
name|of
operator|.
name|err
operator|==
name|NGX_EACCES
condition|)
block|{
operator|*
name|last
operator|=
name|c
expr_stmt|;
comment|/*                  * ngx_http_index_test_dir() is called after the first index                  * file testing has returned an error distinct from NGX_EACCES.                  * This means that directory searching is allowed.                  */
return|return
name|NGX_OK
return|;
block|}
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
name|dir
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
operator|*
name|last
operator|=
name|c
expr_stmt|;
if|if
condition|(
name|of
operator|.
name|is_dir
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"\"%s\" is not a directory"
argument_list|,
name|dir
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_index_error (ngx_http_request_t * r,ngx_http_core_loc_conf_t * clcf,u_char * file,ngx_err_t err)
name|ngx_http_index_error
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
parameter_list|,
name|u_char
modifier|*
name|file
parameter_list|,
name|ngx_err_t
name|err
parameter_list|)
block|{
if|if
condition|(
name|err
operator|==
name|NGX_EACCES
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"\"%s\" is forbidden"
argument_list|,
name|file
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_FORBIDDEN
return|;
block|}
if|if
condition|(
name|clcf
operator|->
name|log_not_found
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"\"%s\" is not found"
argument_list|,
name|file
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_HTTP_NOT_FOUND
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_index_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_index_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_index_loc_conf_t
modifier|*
name|conf
decl_stmt|;
name|conf
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_index_loc_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|conf
operator|->
name|indices
operator|=
name|NULL
expr_stmt|;
name|conf
operator|->
name|max_index_len
operator|=
literal|0
expr_stmt|;
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_index_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_index_merge_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|parent
parameter_list|,
name|void
modifier|*
name|child
parameter_list|)
block|{
name|ngx_http_index_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_index_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_http_index_t
modifier|*
name|index
decl_stmt|;
if|if
condition|(
name|conf
operator|->
name|indices
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|indices
operator|=
name|prev
operator|->
name|indices
expr_stmt|;
name|conf
operator|->
name|max_index_len
operator|=
name|prev
operator|->
name|max_index_len
expr_stmt|;
block|}
if|if
condition|(
name|conf
operator|->
name|indices
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|indices
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|1
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_index_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|->
name|indices
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|index
operator|=
name|ngx_array_push
argument_list|(
name|conf
operator|->
name|indices
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|index
operator|->
name|name
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
name|NGX_HTTP_DEFAULT_INDEX
argument_list|)
expr_stmt|;
name|index
operator|->
name|name
operator|.
name|data
operator|=
operator|(
name|u_char
operator|*
operator|)
name|NGX_HTTP_DEFAULT_INDEX
expr_stmt|;
name|index
operator|->
name|lengths
operator|=
name|NULL
expr_stmt|;
name|index
operator|->
name|values
operator|=
name|NULL
expr_stmt|;
name|conf
operator|->
name|max_index_len
operator|=
sizeof|sizeof
argument_list|(
name|NGX_HTTP_DEFAULT_INDEX
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_index_init (ngx_conf_t * cf)
name|ngx_http_index_init
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
name|NGX_HTTP_CONTENT_PHASE
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
name|ngx_http_index_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_comment
comment|/* TODO: warn about duplicate indices */
end_comment

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_index_set_index (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_index_set_index
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
name|ngx_http_index_loc_conf_t
modifier|*
name|ilcf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_http_index_t
modifier|*
name|index
decl_stmt|;
name|ngx_http_script_compile_t
name|sc
decl_stmt|;
if|if
condition|(
name|ilcf
operator|->
name|indices
operator|==
name|NULL
condition|)
block|{
name|ilcf
operator|->
name|indices
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|2
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_index_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ilcf
operator|->
name|indices
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
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
literal|1
init|;
name|i
operator|<
name|cf
operator|->
name|args
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'/'
operator|&&
name|i
operator|!=
name|cf
operator|->
name|args
operator|->
name|nelts
operator|-
literal|1
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"only the last index in \"index\" directive "
literal|"should be absolute"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|value
index|[
name|i
index|]
operator|.
name|len
operator|==
literal|0
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
literal|"index \"%V\" in \"index\" directive is invalid"
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|index
operator|=
name|ngx_array_push
argument_list|(
name|ilcf
operator|->
name|indices
argument_list|)
expr_stmt|;
if|if
condition|(
name|index
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|index
operator|->
name|name
operator|.
name|len
operator|=
name|value
index|[
name|i
index|]
operator|.
name|len
expr_stmt|;
name|index
operator|->
name|name
operator|.
name|data
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
expr_stmt|;
name|index
operator|->
name|lengths
operator|=
name|NULL
expr_stmt|;
name|index
operator|->
name|values
operator|=
name|NULL
expr_stmt|;
name|n
operator|=
name|ngx_http_script_variables_count
argument_list|(
operator|&
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|ilcf
operator|->
name|max_index_len
operator|<
name|index
operator|->
name|name
operator|.
name|len
condition|)
block|{
name|ilcf
operator|->
name|max_index_len
operator|=
name|index
operator|->
name|name
operator|.
name|len
expr_stmt|;
block|}
if|if
condition|(
name|index
operator|->
name|name
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'/'
condition|)
block|{
continue|continue;
block|}
comment|/* include the terminating '\0' to the length to use ngx_memcpy() */
name|index
operator|->
name|name
operator|.
name|len
operator|++
expr_stmt|;
continue|continue;
block|}
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
name|value
index|[
name|i
index|]
expr_stmt|;
name|sc
operator|.
name|lengths
operator|=
operator|&
name|index
operator|->
name|lengths
expr_stmt|;
name|sc
operator|.
name|values
operator|=
operator|&
name|index
operator|->
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
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

