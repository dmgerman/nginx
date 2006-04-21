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

begin_define
DECL|macro|NGX_HTTP_DAV_OFF
define|#
directive|define
name|NGX_HTTP_DAV_OFF
value|2
end_define

begin_typedef
DECL|struct|__anon292b05600108
typedef|typedef
struct|struct
block|{
DECL|member|methods
name|ngx_uint_t
name|methods
decl_stmt|;
DECL|member|create_full_put_path
name|ngx_flag_t
name|create_full_put_path
decl_stmt|;
DECL|typedef|ngx_http_dav_loc_conf_t
block|}
name|ngx_http_dav_loc_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_dav_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_http_dav_put_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_dav_error
parameter_list|(
name|ngx_http_request_t
modifier|*
parameter_list|,
name|ngx_err_t
name|err
parameter_list|,
name|ngx_int_t
name|not_found
parameter_list|,
name|char
modifier|*
name|failed
parameter_list|,
name|u_char
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_dav_location
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|u_char
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_dav_create_loc_conf
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
name|ngx_http_dav_merge_loc_conf
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
name|ngx_int_t
name|ngx_http_dav_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_dav_methods_mask
specifier|static
name|ngx_conf_bitmask_t
name|ngx_http_dav_methods_mask
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"off"
argument_list|)
block|,
name|NGX_HTTP_DAV_OFF
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"put"
argument_list|)
block|,
name|NGX_HTTP_PUT
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"delete"
argument_list|)
block|,
name|NGX_HTTP_DELETE
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"mkcol"
argument_list|)
block|,
name|NGX_HTTP_MKCOL
block|}
block|,
block|{
name|ngx_null_string
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_dav_commands
specifier|static
name|ngx_command_t
name|ngx_http_dav_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"dav_methods"
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
name|ngx_conf_set_bitmask_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_dav_loc_conf_t
argument_list|,
name|methods
argument_list|)
block|,
operator|&
name|ngx_http_dav_methods_mask
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"create_full_put_path"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
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
name|ngx_http_dav_loc_conf_t
argument_list|,
name|create_full_put_path
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
DECL|variable|ngx_http_dav_module_ctx
name|ngx_http_module_t
name|ngx_http_dav_module_ctx
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
name|ngx_http_dav_create_loc_conf
block|,
comment|/* create location configuration */
name|ngx_http_dav_merge_loc_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_dav_module
name|ngx_module_t
name|ngx_http_dav_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_dav_module_ctx
block|,
comment|/* module context */
name|ngx_http_dav_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|ngx_http_dav_init
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
DECL|function|ngx_http_dav_handler (ngx_http_request_t * r)
name|ngx_http_dav_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|char
modifier|*
name|failed
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_str_t
name|path
decl_stmt|;
name|ngx_file_info_t
name|fi
decl_stmt|;
name|ngx_http_dav_loc_conf_t
modifier|*
name|dlcf
decl_stmt|;
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
name|dlcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_dav_module
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|method
operator|&
name|dlcf
operator|->
name|methods
operator|)
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
switch|switch
condition|(
name|r
operator|->
name|method
condition|)
block|{
case|case
name|NGX_HTTP_PUT
case|:
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
operator|==
literal|'/'
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|r
operator|->
name|request_body_in_file_only
operator|=
literal|1
expr_stmt|;
name|r
operator|->
name|request_body_in_persistent_file
operator|=
literal|1
expr_stmt|;
name|r
operator|->
name|request_body_delete_incomplete_file
operator|=
literal|1
expr_stmt|;
name|r
operator|->
name|request_body_file_group_access
operator|=
literal|1
expr_stmt|;
name|r
operator|->
name|request_body_file_log_level
operator|=
literal|0
expr_stmt|;
name|rc
operator|=
name|ngx_http_read_client_request_body
argument_list|(
name|r
argument_list|,
name|ngx_http_dav_put_handler
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|>=
name|NGX_HTTP_SPECIAL_RESPONSE
condition|)
block|{
return|return
name|rc
return|;
block|}
return|return
name|NGX_DONE
return|;
case|case
name|NGX_HTTP_DELETE
case|:
if|if
condition|(
name|r
operator|->
name|headers_in
operator|.
name|content_length_n
operator|>
literal|0
condition|)
block|{
return|return
name|NGX_HTTP_UNSUPPORTED_MEDIA_TYPE
return|;
block|}
name|rc
operator|=
name|ngx_http_discard_body
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
operator|&&
name|rc
operator|!=
name|NGX_AGAIN
condition|)
block|{
return|return
name|rc
return|;
block|}
name|ngx_http_map_uri_to_path
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|,
literal|0
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
literal|"http delete filename: \"%s\""
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_file_info
argument_list|(
name|path
operator|.
name|data
argument_list|,
operator|&
name|fi
argument_list|)
operator|!=
operator|-
literal|1
condition|)
block|{
if|if
condition|(
name|ngx_is_dir
argument_list|(
operator|&
name|fi
argument_list|)
condition|)
block|{
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
operator|||
name|r
operator|->
name|headers_in
operator|.
name|depth
operator|==
name|NULL
operator|||
name|r
operator|->
name|headers_in
operator|.
name|depth
operator|->
name|value
operator|.
name|len
operator|!=
sizeof|sizeof
argument_list|(
literal|"infinity"
argument_list|)
operator|-
literal|1
operator|||
name|ngx_strcmp
argument_list|(
name|r
operator|->
name|headers_in
operator|.
name|depth
operator|->
name|value
operator|.
name|data
argument_list|,
literal|"infinity"
argument_list|)
operator|!=
literal|0
condition|)
block|{
return|return
name|NGX_HTTP_BAD_REQUEST
return|;
block|}
if|if
condition|(
name|ngx_delete_dir
argument_list|(
name|path
operator|.
name|data
argument_list|)
operator|!=
name|NGX_FILE_ERROR
condition|)
block|{
return|return
name|NGX_HTTP_NO_CONTENT
return|;
block|}
name|failed
operator|=
name|ngx_delete_dir_n
expr_stmt|;
block|}
else|else
block|{
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
operator|==
literal|'/'
condition|)
block|{
return|return
name|NGX_HTTP_BAD_REQUEST
return|;
block|}
if|if
condition|(
name|r
operator|->
name|headers_in
operator|.
name|depth
operator|&&
name|r
operator|->
name|headers_in
operator|.
name|depth
operator|->
name|value
operator|.
name|len
operator|==
literal|1
operator|&&
name|r
operator|->
name|headers_in
operator|.
name|depth
operator|->
name|value
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'1'
condition|)
block|{
return|return
name|NGX_HTTP_BAD_REQUEST
return|;
block|}
if|if
condition|(
name|ngx_delete_file
argument_list|(
name|path
operator|.
name|data
argument_list|)
operator|!=
name|NGX_FILE_ERROR
condition|)
block|{
return|return
name|NGX_HTTP_NO_CONTENT
return|;
block|}
name|failed
operator|=
name|ngx_delete_file_n
expr_stmt|;
block|}
block|}
else|else
block|{
name|failed
operator|=
name|ngx_file_info_n
expr_stmt|;
block|}
return|return
name|ngx_http_dav_error
argument_list|(
name|r
argument_list|,
name|ngx_errno
argument_list|,
name|NGX_HTTP_NOT_FOUND
argument_list|,
name|failed
argument_list|,
name|path
operator|.
name|data
argument_list|)
return|;
case|case
name|NGX_HTTP_MKCOL
case|:
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
name|r
operator|->
name|headers_in
operator|.
name|content_length_n
operator|>
literal|0
condition|)
block|{
return|return
name|NGX_HTTP_UNSUPPORTED_MEDIA_TYPE
return|;
block|}
name|rc
operator|=
name|ngx_http_discard_body
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
operator|&&
name|rc
operator|!=
name|NGX_AGAIN
condition|)
block|{
return|return
name|rc
return|;
block|}
name|ngx_http_map_uri_to_path
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|,
literal|0
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
literal|"http mkcol path: \"%s\""
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_create_dir
argument_list|(
name|path
operator|.
name|data
argument_list|)
operator|!=
name|NGX_FILE_ERROR
condition|)
block|{
if|if
condition|(
name|ngx_http_dav_location
argument_list|(
name|r
argument_list|,
name|path
operator|.
name|data
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
return|return
name|NGX_HTTP_CREATED
return|;
block|}
return|return
name|ngx_http_dav_error
argument_list|(
name|r
argument_list|,
name|ngx_errno
argument_list|,
name|NGX_HTTP_CONFLICT
argument_list|,
name|ngx_create_dir_n
argument_list|,
name|path
operator|.
name|data
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
name|void
DECL|function|ngx_http_dav_put_handler (ngx_http_request_t * r)
name|ngx_http_dav_put_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_str_t
modifier|*
name|temp
decl_stmt|,
name|path
decl_stmt|;
name|ngx_uint_t
name|status
decl_stmt|;
name|ngx_file_info_t
name|fi
decl_stmt|;
name|ngx_http_dav_loc_conf_t
modifier|*
name|dlcf
decl_stmt|;
name|ngx_http_map_uri_to_path
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|,
literal|0
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
literal|"http put filename: \"%s\""
argument_list|,
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
name|temp
operator|=
operator|&
name|r
operator|->
name|request_body
operator|->
name|temp_file
operator|->
name|file
operator|.
name|name
expr_stmt|;
if|if
condition|(
name|ngx_file_info
argument_list|(
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
name|status
operator|=
name|NGX_HTTP_CREATED
expr_stmt|;
block|}
else|else
block|{
name|status
operator|=
name|NGX_HTTP_NO_CONTENT
expr_stmt|;
block|}
if|if
condition|(
name|ngx_is_dir
argument_list|(
operator|&
name|fi
argument_list|)
condition|)
block|{
name|ngx_http_finalize_request
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_CONFLICT
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|ngx_rename_file
argument_list|(
name|temp
operator|->
name|data
argument_list|,
name|path
operator|.
name|data
argument_list|)
operator|!=
name|NGX_FILE_ERROR
condition|)
block|{
goto|goto
name|ok
goto|;
block|}
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
name|dlcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_dav_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|dlcf
operator|->
name|create_full_put_path
condition|)
block|{
name|err
operator|=
name|ngx_create_full_path
argument_list|(
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|ngx_rename_file
argument_list|(
name|temp
operator|->
name|data
argument_list|,
name|path
operator|.
name|data
argument_list|)
operator|!=
name|NGX_FILE_ERROR
condition|)
block|{
goto|goto
name|ok
goto|;
block|}
name|err
operator|=
name|ngx_errno
expr_stmt|;
block|}
block|}
block|}
if|#
directive|if
operator|(
name|NGX_WIN32
operator|)
if|if
condition|(
name|err
operator|==
name|NGX_EEXIST
condition|)
block|{
if|if
condition|(
name|ngx_win32_rename_file
argument_list|(
name|temp
argument_list|,
operator|&
name|path
argument_list|,
name|r
operator|->
name|pool
argument_list|)
operator|!=
name|NGX_ERROR
condition|)
block|{
if|if
condition|(
name|ngx_rename_file
argument_list|(
name|temp
operator|->
name|data
argument_list|,
name|path
operator|.
name|data
argument_list|)
operator|!=
name|NGX_FILE_ERROR
condition|)
block|{
goto|goto
name|ok
goto|;
block|}
block|}
name|err
operator|=
name|ngx_errno
expr_stmt|;
block|}
endif|#
directive|endif
name|ngx_http_finalize_request
argument_list|(
name|r
argument_list|,
name|ngx_http_dav_error
argument_list|(
name|r
argument_list|,
name|err
argument_list|,
name|NGX_HTTP_CONFLICT
argument_list|,
name|ngx_rename_file_n
argument_list|,
name|path
operator|.
name|data
argument_list|)
argument_list|)
expr_stmt|;
return|return;
name|ok
label|:
if|if
condition|(
name|status
operator|==
name|NGX_HTTP_CREATED
condition|)
block|{
if|if
condition|(
name|ngx_http_dav_location
argument_list|(
name|r
argument_list|,
name|path
operator|.
name|data
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
name|ngx_http_finalize_request
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|=
literal|0
expr_stmt|;
block|}
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|status
expr_stmt|;
name|r
operator|->
name|header_only
operator|=
literal|1
expr_stmt|;
name|ngx_http_finalize_request
argument_list|(
name|r
argument_list|,
name|ngx_http_send_header
argument_list|(
name|r
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_dav_error (ngx_http_request_t * r,ngx_err_t err,ngx_int_t not_found,char * failed,u_char * path)
name|ngx_http_dav_error
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_err_t
name|err
parameter_list|,
name|ngx_int_t
name|not_found
parameter_list|,
name|char
modifier|*
name|failed
parameter_list|,
name|u_char
modifier|*
name|path
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_uint_t
name|level
decl_stmt|;
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
name|not_found
expr_stmt|;
block|}
if|else if
condition|(
name|err
operator|==
name|NGX_EACCES
operator|||
name|err
operator|==
name|NGX_EPERM
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
if|else if
condition|(
name|err
operator|==
name|NGX_EEXIST
condition|)
block|{
name|level
operator|=
name|NGX_LOG_ERR
expr_stmt|;
name|rc
operator|=
name|NGX_HTTP_NOT_ALLOWED
expr_stmt|;
block|}
if|else if
condition|(
name|err
operator|==
name|NGX_ENOSPC
condition|)
block|{
name|level
operator|=
name|NGX_LOG_CRIT
expr_stmt|;
name|rc
operator|=
name|NGX_HTTP_INSUFFICIENT_STORAGE
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
literal|"%s \"%s\" failed"
argument_list|,
name|failed
argument_list|,
name|path
argument_list|)
expr_stmt|;
return|return
name|rc
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_dav_location (ngx_http_request_t * r,u_char * path)
name|ngx_http_dav_location
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|u_char
modifier|*
name|path
parameter_list|)
block|{
name|u_char
modifier|*
name|location
decl_stmt|;
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|location
operator|=
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_table_elt_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|location
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|clcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|clcf
operator|->
name|alias
operator|&&
name|clcf
operator|->
name|root_lengths
operator|==
name|NULL
condition|)
block|{
name|location
operator|=
name|path
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
name|location
operator|=
name|ngx_palloc
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
name|location
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_memcpy
argument_list|(
name|location
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
block|}
comment|/*      * we do not need to set the r->headers_out.location->hash and      * r->headers_out.location->key fields      */
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|len
operator|=
name|r
operator|->
name|uri
operator|.
name|len
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|data
operator|=
name|location
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_dav_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_dav_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_dav_loc_conf_t
modifier|*
name|conf
decl_stmt|;
name|conf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_dav_loc_conf_t
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
comment|/*      * set by ngx_pcalloc():      *      *     conf->methods = 0;      */
name|conf
operator|->
name|create_full_put_path
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
DECL|function|ngx_http_dav_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_dav_merge_loc_conf
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
name|ngx_http_dav_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_dav_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_bitmask_value
argument_list|(
name|conf
operator|->
name|methods
argument_list|,
name|prev
operator|->
name|methods
argument_list|,
operator|(
name|NGX_CONF_BITMASK_SET
operator||
name|NGX_HTTP_DAV_OFF
operator|)
argument_list|)
expr_stmt|;
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|create_full_put_path
argument_list|,
name|prev
operator|->
name|create_full_put_path
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
DECL|function|ngx_http_dav_init (ngx_cycle_t * cycle)
name|ngx_http_dav_init
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
name|ngx_http_dav_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

