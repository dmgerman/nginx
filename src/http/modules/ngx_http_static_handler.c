begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_function_decl
specifier|static
name|int
name|ngx_http_static_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_http_static_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_static_commands
specifier|static
name|ngx_command_t
name|ngx_http_static_commands
index|[]
init|=
block|{
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_static_module_ctx
name|ngx_http_module_t
name|ngx_http_static_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* pre conf */
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
name|NULL
block|,
comment|/* create location configuration */
name|NULL
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_static_module
name|ngx_module_t
name|ngx_http_static_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_static_module_ctx
block|,
comment|/* module context */
name|ngx_http_static_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|ngx_http_static_init
block|,
comment|/* init module */
name|NULL
comment|/* init child */
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_static_translate_handler (ngx_http_request_t * r)
name|int
name|ngx_http_static_translate_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|int
name|rc
decl_stmt|,
name|level
decl_stmt|;
name|char
modifier|*
name|location
decl_stmt|,
modifier|*
name|last
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|method
operator|!=
name|NGX_HTTP_GET
operator|&&
name|r
operator|->
name|method
operator|!=
name|NGX_HTTP_HEAD
condition|)
block|{
return|return
name|NGX_HTTP_NOT_ALLOWED
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
if|if
condition|(
name|r
operator|->
name|path
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|ngx_test_null
argument_list|(
name|r
operator|->
name|path
operator|.
name|data
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|clcf
operator|->
name|doc_root
operator|.
name|len
operator|+
name|r
operator|->
name|uri
operator|.
name|len
argument_list|)
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
expr_stmt|;
name|ngx_cpystrn
argument_list|(
name|ngx_cpymem
argument_list|(
name|r
operator|->
name|path
operator|.
name|data
argument_list|,
name|clcf
operator|->
name|doc_root
operator|.
name|data
argument_list|,
name|clcf
operator|->
name|doc_root
operator|.
name|len
argument_list|)
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
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|r
operator|->
name|path
operator|.
name|data
index|[
name|r
operator|->
name|path
operator|.
name|len
index|]
operator|=
literal|'\0'
expr_stmt|;
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
literal|0
argument_list|,
literal|"directory index of \"%s\" is forbidden"
argument_list|,
name|r
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
comment|/* "+ 2" is for trailing '/' in redirect and '\0' */
name|ngx_test_null
argument_list|(
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|clcf
operator|->
name|doc_root
operator|.
name|len
operator|+
name|r
operator|->
name|uri
operator|.
name|len
operator|+
literal|2
argument_list|)
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
expr_stmt|;
name|location
operator|=
name|ngx_cpymem
argument_list|(
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|,
name|clcf
operator|->
name|doc_root
operator|.
name|data
argument_list|,
name|clcf
operator|->
name|doc_root
operator|.
name|len
argument_list|)
operator|,
name|last
operator|=
name|ngx_cpystrn
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
operator|+
literal|1
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"HTTP filename: '%s'"
argument|_ r->file.name.data
argument_list|)
empty_stmt|;
if|#
directive|if
operator|(
name|WIN9X
operator|)
if|if
condition|(
name|ngx_win32_version
operator|<
name|NGX_WIN_NT
condition|)
block|{
comment|/*          * there is no way to open a file or a directory in Win9X with          * one syscall because Win9X has no FILE_FLAG_BACKUP_SEMANTICS flag          * so we need to check its type before the opening          */
if|if
condition|(
name|ngx_file_info
argument_list|(
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|,
operator|&
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|err
operator|=
name|ngx_errno
expr_stmt|;
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
name|ngx_file_info_n
literal|" \"%s\" failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
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
condition|)
block|{
return|return
name|NGX_HTTP_NOT_FOUND
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
name|NGX_HTTP_FORBIDDEN
return|;
block|}
else|else
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
block|}
if|if
condition|(
name|ngx_is_dir
argument_list|(
operator|&
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
condition|)
block|{
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"HTTP DIR: '%s'"
argument|_ r->file.name.data
argument_list|)
empty_stmt|;
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|headers_out
operator|.
name|location
operator|=
name|ngx_http_add_header
argument_list|(
operator|&
name|r
operator|->
name|headers_out
argument_list|,
name|ngx_http_headers_out
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
operator|*
name|last
operator|++
operator|=
literal|'/'
expr_stmt|;
operator|*
name|last
operator|=
literal|'\0'
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|key
operator|.
name|len
operator|=
literal|8
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|key
operator|.
name|data
operator|=
literal|"Location"
expr_stmt|;
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
name|last
operator|-
name|location
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
name|NGX_HTTP_MOVED_PERMANENTLY
return|;
block|}
block|}
endif|#
directive|endif
if|if
condition|(
name|r
operator|->
name|file
operator|.
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|r
operator|->
name|file
operator|.
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|,
name|NGX_FILE_RDONLY
argument_list|,
name|NGX_FILE_OPEN
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|file
operator|.
name|fd
operator|==
name|NGX_INVALID_FILE
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
name|ngx_errno
argument_list|,
name|ngx_open_file_n
literal|" \"%s\" failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|rc
return|;
block|}
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"FILE: %d"
argument|_ r->file.fd
argument_list|)
empty_stmt|;
if|if
condition|(
operator|!
name|r
operator|->
name|file
operator|.
name|info_valid
condition|)
block|{
if|if
condition|(
name|ngx_fd_info
argument_list|(
name|r
operator|->
name|file
operator|.
name|fd
argument_list|,
operator|&
name|r
operator|->
name|file
operator|.
name|info
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
name|ngx_fd_info_n
literal|" \"%s\" failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_close_file
argument_list|(
name|r
operator|->
name|file
operator|.
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
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
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
name|r
operator|->
name|file
operator|.
name|fd
operator|=
name|NGX_INVALID_FILE
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|r
operator|->
name|file
operator|.
name|info_valid
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|ngx_is_dir
argument_list|(
operator|&
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
condition|)
block|{
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"HTTP DIR: '%s'"
argument|_ r->file.name.data
argument_list|)
empty_stmt|;
if|if
condition|(
name|ngx_close_file
argument_list|(
name|r
operator|->
name|file
operator|.
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
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
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
name|r
operator|->
name|file
operator|.
name|fd
operator|=
name|NGX_INVALID_FILE
expr_stmt|;
name|r
operator|->
name|file
operator|.
name|info_valid
operator|=
literal|0
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|headers_out
operator|.
name|location
operator|=
name|ngx_http_add_header
argument_list|(
operator|&
name|r
operator|->
name|headers_out
argument_list|,
name|ngx_http_headers_out
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
operator|*
name|last
operator|++
operator|=
literal|'/'
expr_stmt|;
operator|*
name|last
operator|=
literal|'\0'
expr_stmt|;
if|#
directive|if
literal|0
block_content|r->headers_out.location->key.len = 8;         r->headers_out.location->key.data = "Location" ;
endif|#
directive|endif
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
name|last
operator|-
name|location
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
name|NGX_HTTP_MOVED_PERMANENTLY
return|;
block|}
if|#
directive|if
operator|!
operator|(
name|WIN32
operator|)
comment|/* the not regular files are probably Unix specific */
if|if
condition|(
operator|!
name|ngx_is_file
argument_list|(
operator|&
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
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
literal|"%s is not a regular file"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_close_file
argument_list|(
name|r
operator|->
name|file
operator|.
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
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
name|ngx_close_file_n
literal|" %s failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_NOT_FOUND
return|;
block|}
endif|#
directive|endif
name|r
operator|->
name|content_handler
operator|=
name|ngx_http_static_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_static_handler (ngx_http_request_t * r)
specifier|static
name|int
name|ngx_http_static_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|int
name|rc
decl_stmt|,
name|key
decl_stmt|,
name|i
decl_stmt|;
name|ngx_log_e
name|level
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
name|out
decl_stmt|;
name|ngx_http_type_t
modifier|*
name|type
decl_stmt|;
name|ngx_http_log_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
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
condition|)
block|{
return|return
name|rc
return|;
block|}
name|ctx
operator|=
name|r
operator|->
name|connection
operator|->
name|log
operator|->
name|data
expr_stmt|;
name|ctx
operator|->
name|action
operator|=
literal|"sending response to client"
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|file
operator|.
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|r
operator|->
name|file
operator|.
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|r
operator|->
name|file
operator|.
name|name
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
name|r
operator|->
name|file
operator|.
name|fd
operator|==
name|NGX_INVALID_FILE
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
name|ngx_errno
argument_list|,
name|ngx_open_file_n
literal|" %s failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|rc
return|;
block|}
block|}
if|if
condition|(
operator|!
name|r
operator|->
name|file
operator|.
name|info_valid
condition|)
block|{
if|if
condition|(
name|ngx_fd_info
argument_list|(
name|r
operator|->
name|file
operator|.
name|fd
argument_list|,
operator|&
name|r
operator|->
name|file
operator|.
name|info
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
name|ngx_fd_info_n
literal|" %s failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_close_file
argument_list|(
name|r
operator|->
name|file
operator|.
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
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
name|ngx_close_file_n
literal|" %s failed"
argument_list|,
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|r
operator|->
name|file
operator|.
name|info_valid
operator|=
literal|1
expr_stmt|;
block|}
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|NGX_HTTP_OK
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|=
name|ngx_file_size
argument_list|(
operator|&
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
operator|=
name|ngx_file_mtime
argument_list|(
operator|&
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|=
name|ngx_http_add_header
argument_list|(
operator|&
name|r
operator|->
name|headers_out
argument_list|,
name|ngx_http_headers_out
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|key
operator|.
name|len
operator|=
literal|0
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|key
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
operator|=
literal|0
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|data
operator|=
name|NULL
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
if|if
condition|(
name|r
operator|->
name|exten
operator|.
name|len
condition|)
block|{
name|ngx_http_types_hash_key
argument_list|(
name|key
argument_list|,
name|r
operator|->
name|exten
argument_list|)
expr_stmt|;
name|type
operator|=
operator|(
name|ngx_http_type_t
operator|*
operator|)
name|clcf
operator|->
name|types
index|[
name|key
index|]
operator|.
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
name|clcf
operator|->
name|types
index|[
name|key
index|]
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|r
operator|->
name|exten
operator|.
name|len
operator|!=
name|type
index|[
name|i
index|]
operator|.
name|exten
operator|.
name|len
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|ngx_strcasecmp
argument_list|(
name|r
operator|->
name|exten
operator|.
name|data
argument_list|,
name|type
index|[
name|i
index|]
operator|.
name|exten
operator|.
name|data
argument_list|)
operator|==
literal|0
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
operator|=
name|type
index|[
name|i
index|]
operator|.
name|type
operator|.
name|len
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|data
operator|=
name|type
index|[
name|i
index|]
operator|.
name|type
operator|.
name|data
expr_stmt|;
break|break;
block|}
block|}
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
operator|=
name|clcf
operator|->
name|default_type
operator|.
name|len
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|data
operator|=
name|clcf
operator|->
name|default_type
operator|.
name|data
expr_stmt|;
block|}
comment|/* we need to allocate all before the header would be sent */
name|ngx_test_null
argument_list|(
name|h
argument_list|,
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_hunk_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|h
operator|->
name|file
argument_list|,
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_file_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
expr_stmt|;
name|rc
operator|=
name|ngx_http_send_header
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|rc
operator|>
name|NGX_OK
operator|||
name|r
operator|->
name|header_only
condition|)
block|{
return|return
name|rc
return|;
block|}
name|h
operator|->
name|type
operator|=
name|r
operator|->
expr|main
operator|?
name|NGX_HUNK_FILE
operator|:
name|NGX_HUNK_FILE
operator||
name|NGX_HUNK_LAST
expr_stmt|;
name|h
operator|->
name|file_pos
operator|=
literal|0
expr_stmt|;
name|h
operator|->
name|file_last
operator|=
name|ngx_file_size
argument_list|(
operator|&
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
expr_stmt|;
name|h
operator|->
name|file
operator|->
name|fd
operator|=
name|r
operator|->
name|file
operator|.
name|fd
expr_stmt|;
name|h
operator|->
name|file
operator|->
name|log
operator|=
name|r
operator|->
name|connection
operator|->
name|log
expr_stmt|;
name|out
operator|.
name|hunk
operator|=
name|h
expr_stmt|;
name|out
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
return|return
name|ngx_http_output_filter
argument_list|(
name|r
argument_list|,
operator|&
name|out
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_static_init (ngx_cycle_t * cycle)
specifier|static
name|int
name|ngx_http_static_init
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
name|ngx_http_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
name|ctx
operator|=
operator|(
name|ngx_http_conf_ctx_t
operator|*
operator|)
name|cycle
operator|->
name|conf_ctx
index|[
name|ngx_http_module
operator|.
name|index
index|]
expr_stmt|;
name|cmcf
operator|=
name|ctx
operator|->
name|main_conf
index|[
name|ngx_http_core_module
operator|.
name|ctx_index
index|]
expr_stmt|;
name|ngx_test_null
argument_list|(
name|h
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|cmcf
operator|->
name|phases
index|[
name|NGX_HTTP_TRANSLATE_PHASE
index|]
operator|.
name|handlers
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
operator|*
name|h
operator|=
name|ngx_http_static_translate_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

