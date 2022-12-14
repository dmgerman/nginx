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
DECL|struct|__anon29d409920108
typedef|typedef
struct|struct
block|{
DECL|member|enable
name|ngx_flag_t
name|enable
decl_stmt|;
DECL|typedef|ngx_http_random_index_loc_conf_t
block|}
name|ngx_http_random_index_loc_conf_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_RANDOM_INDEX_PREALLOCATE
define|#
directive|define
name|NGX_HTTP_RANDOM_INDEX_PREALLOCATE
value|50
end_define

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_random_index_error
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_dir_t
modifier|*
name|dir
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_random_index_init
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
name|ngx_http_random_index_create_loc_conf
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
name|ngx_http_random_index_merge_loc_conf
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

begin_decl_stmt
DECL|variable|ngx_http_random_index_commands
specifier|static
name|ngx_command_t
name|ngx_http_random_index_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"random_index"
argument_list|)
block|,
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_conf_set_flag_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_random_index_loc_conf_t
argument_list|,
name|enable
argument_list|)
block|,
name|NULL
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_random_index_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_random_index_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_random_index_init
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
name|ngx_http_random_index_create_loc_conf
block|,
comment|/* create location configuration */
name|ngx_http_random_index_merge_loc_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_random_index_module
name|ngx_module_t
name|ngx_http_random_index_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_random_index_module_ctx
block|,
comment|/* module context */
name|ngx_http_random_index_commands
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
DECL|function|ngx_http_random_index_handler (ngx_http_request_t * r)
name|ngx_http_random_index_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|u_char
modifier|*
name|last
decl_stmt|,
modifier|*
name|filename
decl_stmt|;
name|size_t
name|len
decl_stmt|,
name|allocated
decl_stmt|,
name|root
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_str_t
name|path
decl_stmt|,
name|uri
decl_stmt|,
modifier|*
name|name
decl_stmt|;
name|ngx_dir_t
name|dir
decl_stmt|;
name|ngx_uint_t
name|n
decl_stmt|,
name|level
decl_stmt|;
name|ngx_array_t
name|names
decl_stmt|;
name|ngx_http_random_index_loc_conf_t
modifier|*
name|rlcf
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
name|rlcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_random_index_module
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|rlcf
operator|->
name|enable
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_D_TYPE
operator|)
name|len
operator|=
literal|0
expr_stmt|;
else|#
directive|else
name|len
operator|=
name|NGX_HTTP_RANDOM_INDEX_PREALLOCATE
expr_stmt|;
endif|#
directive|endif
name|last
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
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|allocated
operator|=
name|path
operator|.
name|len
expr_stmt|;
name|path
operator|.
name|len
operator|=
name|last
operator|-
name|path
operator|.
name|data
operator|-
literal|1
expr_stmt|;
name|path
operator|.
name|data
index|[
name|path
operator|.
name|len
index|]
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
literal|"http random index: \"%s\""
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_open_dir
argument_list|(
operator|&
name|path
argument_list|,
operator|&
name|dir
argument_list|)
operator|==
name|NGX_ERROR
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
operator|||
name|err
operator|==
name|NGX_ENOTDIR
operator|||
name|err
operator|==
name|NGX_ENAMETOOLONG
condition|)
block|{
name|level
operator|=
name|NGX_LOG_ERR
expr_stmt|;
name|rc
operator|=
name|NGX_HTTP_NOT_FOUND
expr_stmt|;
block|}
if|else if
condition|(
name|err
operator|==
name|NGX_EACCES
condition|)
block|{
name|level
operator|=
name|NGX_LOG_ERR
expr_stmt|;
name|rc
operator|=
name|NGX_HTTP_FORBIDDEN
expr_stmt|;
block|}
else|else
block|{
name|level
operator|=
name|NGX_LOG_CRIT
expr_stmt|;
name|rc
operator|=
name|NGX_HTTP_INTERNAL_SERVER_ERROR
expr_stmt|;
block|}
name|ngx_log_error
argument_list|(
name|level
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
name|err
argument_list|,
name|ngx_open_dir_n
literal|" \"%s\" failed"
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|rc
return|;
block|}
if|if
condition|(
name|ngx_array_init
argument_list|(
operator|&
name|names
argument_list|,
name|r
operator|->
name|pool
argument_list|,
literal|32
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_str_t
argument_list|)
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|ngx_http_random_index_error
argument_list|(
name|r
argument_list|,
operator|&
name|dir
argument_list|,
operator|&
name|path
argument_list|)
return|;
block|}
name|filename
operator|=
name|path
operator|.
name|data
expr_stmt|;
name|filename
index|[
name|path
operator|.
name|len
index|]
operator|=
literal|'/'
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|ngx_set_errno
argument_list|(
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_read_dir
argument_list|(
operator|&
name|dir
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|err
operator|!=
name|NGX_ENOMOREFILES
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
name|err
argument_list|,
name|ngx_read_dir_n
literal|" \"%V\" failed"
argument_list|,
operator|&
name|path
argument_list|)
expr_stmt|;
return|return
name|ngx_http_random_index_error
argument_list|(
name|r
argument_list|,
operator|&
name|dir
argument_list|,
operator|&
name|path
argument_list|)
return|;
block|}
break|break;
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
literal|"http random index file: \"%s\""
argument_list|,
name|ngx_de_name
argument_list|(
operator|&
name|dir
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_de_name
argument_list|(
operator|&
name|dir
argument_list|)
index|[
literal|0
index|]
operator|==
literal|'.'
condition|)
block|{
continue|continue;
block|}
name|len
operator|=
name|ngx_de_namelen
argument_list|(
operator|&
name|dir
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|.
name|type
operator|==
literal|0
operator|||
name|ngx_de_is_link
argument_list|(
operator|&
name|dir
argument_list|)
condition|)
block|{
comment|/* 1 byte for '/' and 1 byte for terminating '\0' */
if|if
condition|(
name|path
operator|.
name|len
operator|+
literal|1
operator|+
name|len
operator|+
literal|1
operator|>
name|allocated
condition|)
block|{
name|allocated
operator|=
name|path
operator|.
name|len
operator|+
literal|1
operator|+
name|len
operator|+
literal|1
operator|+
name|NGX_HTTP_RANDOM_INDEX_PREALLOCATE
expr_stmt|;
name|filename
operator|=
name|ngx_pnalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|allocated
argument_list|)
expr_stmt|;
if|if
condition|(
name|filename
operator|==
name|NULL
condition|)
block|{
return|return
name|ngx_http_random_index_error
argument_list|(
name|r
argument_list|,
operator|&
name|dir
argument_list|,
operator|&
name|path
argument_list|)
return|;
block|}
name|last
operator|=
name|ngx_cpystrn
argument_list|(
name|filename
argument_list|,
name|path
operator|.
name|data
argument_list|,
name|path
operator|.
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
operator|*
name|last
operator|++
operator|=
literal|'/'
expr_stmt|;
block|}
name|ngx_cpystrn
argument_list|(
name|last
argument_list|,
name|ngx_de_name
argument_list|(
operator|&
name|dir
argument_list|)
argument_list|,
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_de_info
argument_list|(
name|filename
argument_list|,
operator|&
name|dir
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|err
operator|!=
name|NGX_ENOENT
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
name|err
argument_list|,
name|ngx_de_info_n
literal|" \"%s\" failed"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|ngx_http_random_index_error
argument_list|(
name|r
argument_list|,
operator|&
name|dir
argument_list|,
operator|&
name|path
argument_list|)
return|;
block|}
if|if
condition|(
name|ngx_de_link_info
argument_list|(
name|filename
argument_list|,
operator|&
name|dir
argument_list|)
operator|==
name|NGX_FILE_ERROR
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
name|ngx_errno
argument_list|,
name|ngx_de_link_info_n
literal|" \"%s\" failed"
argument_list|,
name|filename
argument_list|)
expr_stmt|;
return|return
name|ngx_http_random_index_error
argument_list|(
name|r
argument_list|,
operator|&
name|dir
argument_list|,
operator|&
name|path
argument_list|)
return|;
block|}
block|}
block|}
if|if
condition|(
operator|!
name|ngx_de_is_file
argument_list|(
operator|&
name|dir
argument_list|)
condition|)
block|{
continue|continue;
block|}
name|name
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|names
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
name|ngx_http_random_index_error
argument_list|(
name|r
argument_list|,
operator|&
name|dir
argument_list|,
operator|&
name|path
argument_list|)
return|;
block|}
name|name
operator|->
name|len
operator|=
name|len
expr_stmt|;
name|name
operator|->
name|data
operator|=
name|ngx_pnalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
operator|->
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|ngx_http_random_index_error
argument_list|(
name|r
argument_list|,
operator|&
name|dir
argument_list|,
operator|&
name|path
argument_list|)
return|;
block|}
name|ngx_memcpy
argument_list|(
name|name
operator|->
name|data
argument_list|,
name|ngx_de_name
argument_list|(
operator|&
name|dir
argument_list|)
argument_list|,
name|len
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ngx_close_dir
argument_list|(
operator|&
name|dir
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
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
name|ngx_errno
argument_list|,
name|ngx_close_dir_n
literal|" \"%V\" failed"
argument_list|,
operator|&
name|path
argument_list|)
expr_stmt|;
block|}
name|n
operator|=
name|names
operator|.
name|nelts
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|name
operator|=
name|names
operator|.
name|elts
expr_stmt|;
name|n
operator|=
operator|(
name|ngx_uint_t
operator|)
operator|(
operator|(
operator|(
name|uint64_t
operator|)
name|ngx_random
argument_list|()
operator|*
name|n
operator|)
operator|/
literal|0x80000000
operator|)
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
name|name
index|[
name|n
index|]
operator|.
name|len
expr_stmt|;
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
name|name
index|[
name|n
index|]
operator|.
name|data
argument_list|,
name|name
index|[
name|n
index|]
operator|.
name|len
argument_list|)
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
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_random_index_error (ngx_http_request_t * r,ngx_dir_t * dir,ngx_str_t * name)
name|ngx_http_random_index_error
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_dir_t
modifier|*
name|dir
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
block|{
if|if
condition|(
name|ngx_close_dir
argument_list|(
name|dir
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
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
name|ngx_errno
argument_list|,
name|ngx_close_dir_n
literal|" \"%V\" failed"
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_random_index_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_random_index_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_random_index_loc_conf_t
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
name|ngx_http_random_index_loc_conf_t
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
name|enable
operator|=
name|NGX_CONF_UNSET
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
DECL|function|ngx_http_random_index_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_random_index_merge_loc_conf
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
name|ngx_http_random_index_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_random_index_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|enable
argument_list|,
name|prev
operator|->
name|enable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_random_index_init (ngx_conf_t * cf)
name|ngx_http_random_index_init
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
name|ngx_http_random_index_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

