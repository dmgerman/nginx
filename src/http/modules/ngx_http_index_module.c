begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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
DECL|struct|__anon2b079d460108
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
DECL|struct|__anon2b079d460208
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

begin_typedef
DECL|struct|__anon2b079d460308
typedef|typedef
struct|struct
block|{
DECL|member|current
name|ngx_uint_t
name|current
decl_stmt|;
DECL|member|path
name|ngx_str_t
name|path
decl_stmt|;
DECL|member|index
name|ngx_str_t
name|index
decl_stmt|;
DECL|member|tested
name|ngx_uint_t
name|tested
decl_stmt|;
comment|/* unsigned  tested:1 */
DECL|typedef|ngx_http_index_ctx_t
block|}
name|ngx_http_index_ctx_t
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
name|ngx_http_index_ctx_t
modifier|*
name|ctx
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
name|ngx_http_index_ctx_t
modifier|*
name|ctx
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
name|ngx_cycle_t
modifier|*
name|cycle
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
if|#
directive|if
operator|(
name|NGX_HTTP_CACHE
operator|)
block|{
name|ngx_string
argument_list|(
literal|"index_cache"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_TAKE3
block|,
name|ngx_http_set_cache_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_index_loc_conf_t
argument_list|,
name|index_cache
argument_list|)
block|,
name|NULL
block|}
block|,
endif|#
directive|endif
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_index_module_ctx
name|ngx_http_module_t
name|ngx_http_index_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|NULL
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
comment|/* create location configration */
name|ngx_http_index_merge_loc_conf
comment|/* merge location configration */
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
name|ngx_http_index_init
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
comment|/*  * Try to open the first index file before the test of the directory existence  * because the valid requests should be many more than invalid ones.  * If open() would fail, then stat() should be more quickly because some data  * is already cached in the kernel.  * Besides, Win32 has ERROR_PATH_NOT_FOUND (NGX_ENOTDIR).  * Unix has ENOTDIR error, although it less helpfull - it points only  * that path contains the usual file in place of the directory.  */
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
name|last
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_fd_t
name|fd
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_str_t
name|uri
decl_stmt|;
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_http_index_t
modifier|*
name|index
decl_stmt|;
name|ngx_http_index_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_pool_cleanup_t
modifier|*
name|cln
decl_stmt|;
name|ngx_pool_cleanup_file_t
modifier|*
name|clnf
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
comment|/* TODO: Win32 */
if|if
condition|(
name|r
operator|->
name|zero_in_uri
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|log
operator|=
name|r
operator|->
name|connection
operator|->
name|log
expr_stmt|;
comment|/*      * we use context because the handler supports an async file opening,      * and may be called several times      */
name|ilcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_index_module
argument_list|)
expr_stmt|;
name|ctx
operator|=
name|ngx_http_get_module_ctx
argument_list|(
name|r
argument_list|,
name|ngx_http_index_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|==
name|NULL
condition|)
block|{
name|ctx
operator|=
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_index_ctx_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|ngx_http_set_ctx
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|,
name|ngx_http_index_module
argument_list|)
expr_stmt|;
block|}
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
name|ctx
operator|->
name|current
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
name|len
operator|=
name|ilcf
operator|->
name|max_index_len
expr_stmt|;
name|ctx
operator|->
name|index
operator|.
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
comment|/* 1 byte for terminating '\0' */
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
name|ctx
operator|->
name|index
operator|.
name|len
operator|=
name|len
expr_stmt|;
comment|/* 16 bytes are preallocation */
name|len
operator|+=
literal|16
expr_stmt|;
block|}
if|if
condition|(
name|len
operator|>
name|ctx
operator|->
name|path
operator|.
name|len
condition|)
block|{
name|last
operator|=
name|ngx_http_map_uri_to_path
argument_list|(
name|r
argument_list|,
operator|&
name|ctx
operator|->
name|path
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|last
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ctx
operator|->
name|index
operator|.
name|data
operator|=
name|last
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
name|ctx
operator|->
name|index
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
name|ctx
operator|->
name|index
operator|.
name|data
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
name|ctx
operator|->
name|index
operator|.
name|data
operator|==
literal|'/'
condition|)
block|{
name|ctx
operator|->
name|index
operator|.
name|len
operator|--
expr_stmt|;
return|return
name|ngx_http_internal_redirect
argument_list|(
name|r
argument_list|,
operator|&
name|ctx
operator|->
name|index
argument_list|,
operator|&
name|r
operator|->
name|args
argument_list|)
return|;
block|}
operator|*
name|e
operator|.
name|pos
operator|++
operator|=
literal|'\0'
expr_stmt|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"open index \"%s\""
argument_list|,
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
name|cln
operator|=
name|ngx_pool_cleanup_add
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_pool_cleanup_file_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|cln
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|,
name|NGX_FILE_RDONLY
argument_list|,
name|NGX_FILE_OPEN
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
operator|(
name|ngx_fd_t
operator|)
name|NGX_AGAIN
condition|)
block|{
name|ctx
operator|->
name|current
operator|=
name|i
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|err
operator|=
name|ngx_errno
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
name|ngx_open_file_n
literal|" \"%s\" failed"
argument_list|,
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_ENOTDIR
condition|)
block|{
return|return
name|ngx_http_index_error
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|,
name|err
argument_list|)
return|;
block|}
if|else if
condition|(
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
name|ctx
argument_list|,
name|err
argument_list|)
return|;
block|}
if|if
condition|(
operator|!
name|ctx
operator|->
name|tested
condition|)
block|{
name|rc
operator|=
name|ngx_http_index_test_dir
argument_list|(
name|r
argument_list|,
name|ctx
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
name|ctx
operator|->
name|tested
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|err
operator|==
name|NGX_ENOENT
condition|)
block|{
continue|continue;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
name|ngx_open_file_n
literal|" \"%s\" failed"
argument_list|,
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|cln
operator|->
name|handler
operator|=
name|ngx_pool_cleanup_file
expr_stmt|;
name|clnf
operator|=
name|cln
operator|->
name|data
expr_stmt|;
name|clnf
operator|->
name|fd
operator|=
name|fd
expr_stmt|;
name|clnf
operator|->
name|name
operator|=
name|ctx
operator|->
name|path
operator|.
name|data
expr_stmt|;
name|clnf
operator|->
name|log
operator|=
name|r
operator|->
name|pool
operator|->
name|log
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
name|ctx
operator|->
name|index
operator|.
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
name|ctx
operator|->
name|path
operator|.
name|data
operator|+
name|clcf
operator|->
name|root
operator|.
name|len
expr_stmt|;
block|}
else|else
block|{
name|uri
operator|.
name|data
operator|=
name|ngx_palloc
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
name|last
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
name|last
argument_list|,
name|ctx
operator|->
name|index
operator|.
name|data
argument_list|,
name|ctx
operator|->
name|index
operator|.
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
DECL|function|ngx_http_index_test_dir (ngx_http_request_t * r,ngx_http_index_ctx_t * ctx)
name|ngx_http_index_test_dir
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_index_ctx_t
modifier|*
name|ctx
parameter_list|)
block|{
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_file_info_t
name|fi
decl_stmt|;
operator|*
operator|(
name|ctx
operator|->
name|index
operator|.
name|data
operator|-
literal|1
operator|)
operator|=
literal|'\0'
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
literal|"http index check dir: \"%s\""
argument_list|,
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_file_info
argument_list|(
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|,
operator|&
name|fi
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_ENOENT
condition|)
block|{
operator|*
operator|(
name|ctx
operator|->
name|index
operator|.
name|data
operator|-
literal|1
operator|)
operator|=
literal|'/'
expr_stmt|;
return|return
name|ngx_http_index_error
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|,
name|err
argument_list|)
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
name|err
argument_list|,
name|ngx_file_info_n
literal|" \"%s\" failed"
argument_list|,
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
operator|*
operator|(
name|ctx
operator|->
name|index
operator|.
name|data
operator|-
literal|1
operator|)
operator|=
literal|'/'
expr_stmt|;
if|if
condition|(
name|ngx_is_dir
argument_list|(
operator|&
name|fi
argument_list|)
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
name|ctx
operator|->
name|path
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
DECL|function|ngx_http_index_error (ngx_http_request_t * r,ngx_http_index_ctx_t * ctx,ngx_err_t err)
name|ngx_http_index_error
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_index_ctx_t
modifier|*
name|ctx
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
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_FORBIDDEN
return|;
block|}
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
name|ctx
operator|->
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
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
name|NGX_CONF_ERROR
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
literal|1
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
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
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
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"only the last index in \"index\" directive "
literal|"may be absolute"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
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
operator|!=
literal|0
operator|&&
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
comment|/* include the terminating '\0' to the length to use ngx_copy() */
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
name|ilcf
operator|->
name|max_index_len
operator|=
literal|0
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_index_init (ngx_cycle_t * cycle)
name|ngx_http_index_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
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
name|ngx_http_cycle_get_module_main_conf
argument_list|(
name|cycle
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

end_unit

