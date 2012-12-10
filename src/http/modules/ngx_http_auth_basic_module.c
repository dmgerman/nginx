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

begin_include
include|#
directive|include
file|<ngx_crypt.h>
end_include

begin_define
DECL|macro|NGX_HTTP_AUTH_BUF_SIZE
define|#
directive|define
name|NGX_HTTP_AUTH_BUF_SIZE
value|2048
end_define

begin_typedef
DECL|struct|__anon292ca8c30108
typedef|typedef
struct|struct
block|{
DECL|member|passwd
name|ngx_str_t
name|passwd
decl_stmt|;
DECL|typedef|ngx_http_auth_basic_ctx_t
block|}
name|ngx_http_auth_basic_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon292ca8c30208
typedef|typedef
struct|struct
block|{
DECL|member|realm
name|ngx_http_complex_value_t
modifier|*
name|realm
decl_stmt|;
DECL|member|user_file
name|ngx_http_complex_value_t
name|user_file
decl_stmt|;
DECL|typedef|ngx_http_auth_basic_loc_conf_t
block|}
name|ngx_http_auth_basic_loc_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_auth_basic_handler
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
name|ngx_http_auth_basic_crypt_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_auth_basic_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_str_t
modifier|*
name|passwd
parameter_list|,
name|ngx_str_t
modifier|*
name|realm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_auth_basic_set_realm
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_str_t
modifier|*
name|realm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_http_auth_basic_close
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_auth_basic_create_loc_conf
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
name|ngx_http_auth_basic_merge_loc_conf
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
name|ngx_http_auth_basic_init
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
name|ngx_http_auth_basic_user_file
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
DECL|variable|ngx_http_auth_basic_commands
specifier|static
name|ngx_command_t
name|ngx_http_auth_basic_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"auth_basic"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_HTTP_LMT_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_set_complex_value_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_auth_basic_loc_conf_t
argument_list|,
name|realm
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"auth_basic_user_file"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_HTTP_LMT_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_auth_basic_user_file
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_auth_basic_loc_conf_t
argument_list|,
name|user_file
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
DECL|variable|ngx_http_auth_basic_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_auth_basic_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_auth_basic_init
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
name|ngx_http_auth_basic_create_loc_conf
block|,
comment|/* create location configuration */
name|ngx_http_auth_basic_merge_loc_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_auth_basic_module
name|ngx_module_t
name|ngx_http_auth_basic_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_auth_basic_module_ctx
block|,
comment|/* module context */
name|ngx_http_auth_basic_commands
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
DECL|function|ngx_http_auth_basic_handler (ngx_http_request_t * r)
name|ngx_http_auth_basic_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|off_t
name|offset
decl_stmt|;
name|ssize_t
name|n
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
name|pwd
decl_stmt|,
name|realm
decl_stmt|,
name|user_file
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|level
decl_stmt|,
name|login
decl_stmt|,
name|left
decl_stmt|,
name|passwd
decl_stmt|;
name|ngx_file_t
name|file
decl_stmt|;
name|ngx_http_auth_basic_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_auth_basic_loc_conf_t
modifier|*
name|alcf
decl_stmt|;
name|u_char
name|buf
index|[
name|NGX_HTTP_AUTH_BUF_SIZE
index|]
decl_stmt|;
DECL|enum|__anon292ca8c30303
enum|enum
block|{
DECL|enumerator|sw_login
name|sw_login
block|,
DECL|enumerator|sw_passwd
name|sw_passwd
block|,
DECL|enumerator|sw_skip
name|sw_skip
block|}
name|state
enum|;
name|alcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_auth_basic_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|alcf
operator|->
name|realm
operator|==
name|NULL
operator|||
name|alcf
operator|->
name|user_file
operator|.
name|value
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
if|if
condition|(
name|ngx_http_complex_value
argument_list|(
name|r
argument_list|,
name|alcf
operator|->
name|realm
argument_list|,
operator|&
name|realm
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|realm
operator|.
name|len
operator|==
literal|3
operator|&&
name|ngx_strncmp
argument_list|(
name|realm
operator|.
name|data
argument_list|,
literal|"off"
argument_list|,
literal|3
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|ctx
operator|=
name|ngx_http_get_module_ctx
argument_list|(
name|r
argument_list|,
name|ngx_http_auth_basic_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
condition|)
block|{
return|return
name|ngx_http_auth_basic_crypt_handler
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|,
operator|&
name|ctx
operator|->
name|passwd
argument_list|,
operator|&
name|realm
argument_list|)
return|;
block|}
name|rc
operator|=
name|ngx_http_auth_basic_user
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_DECLINED
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
literal|0
argument_list|,
literal|"no user/password was provided for basic authentication"
argument_list|)
expr_stmt|;
return|return
name|ngx_http_auth_basic_set_realm
argument_list|(
name|r
argument_list|,
operator|&
name|realm
argument_list|)
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
if|if
condition|(
name|ngx_http_complex_value
argument_list|(
name|r
argument_list|,
operator|&
name|alcf
operator|->
name|user_file
argument_list|,
operator|&
name|user_file
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|user_file
operator|.
name|data
argument_list|,
name|NGX_FILE_RDONLY
argument_list|,
name|NGX_FILE_OPEN
argument_list|,
literal|0
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|err
operator|==
name|NGX_ENOENT
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
name|ngx_open_file_n
literal|" \"%s\" failed"
argument_list|,
name|user_file
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|rc
return|;
block|}
name|ngx_memzero
argument_list|(
operator|&
name|file
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_file_t
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|.
name|fd
operator|=
name|fd
expr_stmt|;
name|file
operator|.
name|name
operator|=
name|user_file
expr_stmt|;
name|file
operator|.
name|log
operator|=
name|r
operator|->
name|connection
operator|->
name|log
expr_stmt|;
name|state
operator|=
name|sw_login
expr_stmt|;
name|passwd
operator|=
literal|0
expr_stmt|;
name|login
operator|=
literal|0
expr_stmt|;
name|left
operator|=
literal|0
expr_stmt|;
name|offset
operator|=
literal|0
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|i
operator|=
name|left
expr_stmt|;
name|n
operator|=
name|ngx_read_file
argument_list|(
operator|&
name|file
argument_list|,
name|buf
operator|+
name|left
argument_list|,
name|NGX_HTTP_AUTH_BUF_SIZE
operator|-
name|left
argument_list|,
name|offset
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_http_auth_basic_close
argument_list|(
operator|&
name|file
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
break|break;
block|}
for|for
control|(
name|i
operator|=
name|left
init|;
name|i
operator|<
name|left
operator|+
name|n
condition|;
name|i
operator|++
control|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|sw_login
case|:
if|if
condition|(
name|login
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|buf
index|[
name|i
index|]
operator|==
literal|'#'
operator|||
name|buf
index|[
name|i
index|]
operator|==
name|CR
condition|)
block|{
name|state
operator|=
name|sw_skip
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|buf
index|[
name|i
index|]
operator|==
name|LF
condition|)
block|{
break|break;
block|}
block|}
if|if
condition|(
name|buf
index|[
name|i
index|]
operator|!=
name|r
operator|->
name|headers_in
operator|.
name|user
operator|.
name|data
index|[
name|login
index|]
condition|)
block|{
name|state
operator|=
name|sw_skip
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|login
operator|==
name|r
operator|->
name|headers_in
operator|.
name|user
operator|.
name|len
condition|)
block|{
name|state
operator|=
name|sw_passwd
expr_stmt|;
name|passwd
operator|=
name|i
operator|+
literal|1
expr_stmt|;
block|}
name|login
operator|++
expr_stmt|;
break|break;
case|case
name|sw_passwd
case|:
if|if
condition|(
name|buf
index|[
name|i
index|]
operator|==
name|LF
operator|||
name|buf
index|[
name|i
index|]
operator|==
name|CR
operator|||
name|buf
index|[
name|i
index|]
operator|==
literal|':'
condition|)
block|{
name|buf
index|[
name|i
index|]
operator|=
literal|'\0'
expr_stmt|;
name|ngx_http_auth_basic_close
argument_list|(
operator|&
name|file
argument_list|)
expr_stmt|;
name|pwd
operator|.
name|len
operator|=
name|i
operator|-
name|passwd
expr_stmt|;
name|pwd
operator|.
name|data
operator|=
operator|&
name|buf
index|[
name|passwd
index|]
expr_stmt|;
return|return
name|ngx_http_auth_basic_crypt_handler
argument_list|(
name|r
argument_list|,
name|NULL
argument_list|,
operator|&
name|pwd
argument_list|,
operator|&
name|realm
argument_list|)
return|;
block|}
break|break;
case|case
name|sw_skip
case|:
if|if
condition|(
name|buf
index|[
name|i
index|]
operator|==
name|LF
condition|)
block|{
name|state
operator|=
name|sw_login
expr_stmt|;
name|login
operator|=
literal|0
expr_stmt|;
block|}
break|break;
block|}
block|}
if|if
condition|(
name|state
operator|==
name|sw_passwd
condition|)
block|{
name|left
operator|=
name|left
operator|+
name|n
operator|-
name|passwd
expr_stmt|;
name|ngx_memmove
argument_list|(
name|buf
argument_list|,
operator|&
name|buf
index|[
name|passwd
index|]
argument_list|,
name|left
argument_list|)
expr_stmt|;
name|passwd
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|left
operator|=
literal|0
expr_stmt|;
block|}
name|offset
operator|+=
name|n
expr_stmt|;
block|}
name|ngx_http_auth_basic_close
argument_list|(
operator|&
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|state
operator|==
name|sw_passwd
condition|)
block|{
name|pwd
operator|.
name|len
operator|=
name|i
operator|-
name|passwd
expr_stmt|;
name|pwd
operator|.
name|data
operator|=
name|ngx_pnalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|pwd
operator|.
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|pwd
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
name|ngx_cpystrn
argument_list|(
name|pwd
operator|.
name|data
argument_list|,
operator|&
name|buf
index|[
name|passwd
index|]
argument_list|,
name|pwd
operator|.
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
return|return
name|ngx_http_auth_basic_crypt_handler
argument_list|(
name|r
argument_list|,
name|NULL
argument_list|,
operator|&
name|pwd
argument_list|,
operator|&
name|realm
argument_list|)
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
literal|0
argument_list|,
literal|"user \"%V\" was not found in \"%V\""
argument_list|,
operator|&
name|r
operator|->
name|headers_in
operator|.
name|user
argument_list|,
operator|&
name|user_file
argument_list|)
expr_stmt|;
return|return
name|ngx_http_auth_basic_set_realm
argument_list|(
name|r
argument_list|,
operator|&
name|realm
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_auth_basic_crypt_handler (ngx_http_request_t * r,ngx_http_auth_basic_ctx_t * ctx,ngx_str_t * passwd,ngx_str_t * realm)
name|ngx_http_auth_basic_crypt_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_auth_basic_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_str_t
modifier|*
name|passwd
parameter_list|,
name|ngx_str_t
modifier|*
name|realm
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
name|u_char
modifier|*
name|encrypted
decl_stmt|;
name|rc
operator|=
name|ngx_crypt
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|r
operator|->
name|headers_in
operator|.
name|passwd
operator|.
name|data
argument_list|,
name|passwd
operator|->
name|data
argument_list|,
operator|&
name|encrypted
argument_list|)
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
literal|"rc: %d user: \"%V\" salt: \"%s\""
argument_list|,
name|rc
argument_list|,
operator|&
name|r
operator|->
name|headers_in
operator|.
name|user
argument_list|,
name|passwd
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_OK
condition|)
block|{
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|encrypted
argument_list|,
name|passwd
operator|->
name|data
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_OK
return|;
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
literal|"encrypted: \"%s\""
argument_list|,
name|encrypted
argument_list|)
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
literal|0
argument_list|,
literal|"user \"%V\": password mismatch"
argument_list|,
operator|&
name|r
operator|->
name|headers_in
operator|.
name|user
argument_list|)
expr_stmt|;
return|return
name|ngx_http_auth_basic_set_realm
argument_list|(
name|r
argument_list|,
name|realm
argument_list|)
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
comment|/* rc == NGX_AGAIN */
if|if
condition|(
name|ctx
operator|==
name|NULL
condition|)
block|{
name|ctx
operator|=
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_auth_basic_ctx_t
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
name|ngx_http_auth_basic_module
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|passwd
operator|.
name|len
operator|=
name|passwd
operator|->
name|len
expr_stmt|;
name|passwd
operator|->
name|len
operator|++
expr_stmt|;
name|ctx
operator|->
name|passwd
operator|.
name|data
operator|=
name|ngx_pstrdup
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|passwd
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|->
name|passwd
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
block|}
comment|/* TODO: add mutex event */
return|return
name|rc
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_auth_basic_set_realm (ngx_http_request_t * r,ngx_str_t * realm)
name|ngx_http_auth_basic_set_realm
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_str_t
modifier|*
name|realm
parameter_list|)
block|{
name|size_t
name|len
decl_stmt|;
name|u_char
modifier|*
name|basic
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|www_authenticate
operator|=
name|ngx_list_push
argument_list|(
operator|&
name|r
operator|->
name|headers_out
operator|.
name|headers
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|www_authenticate
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"Basic realm=\"\""
argument_list|)
operator|-
literal|1
operator|+
name|realm
operator|->
name|len
expr_stmt|;
name|basic
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
name|basic
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
name|ngx_cpymem
argument_list|(
name|basic
argument_list|,
literal|"Basic realm=\""
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Basic realm=\""
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_cpymem
argument_list|(
name|p
argument_list|,
name|realm
operator|->
name|data
argument_list|,
name|realm
operator|->
name|len
argument_list|)
expr_stmt|;
operator|*
name|p
operator|=
literal|'"'
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|www_authenticate
operator|->
name|hash
operator|=
literal|1
expr_stmt|;
name|ngx_str_set
argument_list|(
operator|&
name|r
operator|->
name|headers_out
operator|.
name|www_authenticate
operator|->
name|key
argument_list|,
literal|"WWW-Authenticate"
argument_list|)
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|www_authenticate
operator|->
name|value
operator|.
name|data
operator|=
name|basic
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|www_authenticate
operator|->
name|value
operator|.
name|len
operator|=
name|len
expr_stmt|;
return|return
name|NGX_HTTP_UNAUTHORIZED
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_http_auth_basic_close (ngx_file_t * file)
name|ngx_http_auth_basic_close
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|)
block|{
if|if
condition|(
name|ngx_close_file
argument_list|(
name|file
operator|->
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
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_auth_basic_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_auth_basic_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_auth_basic_loc_conf_t
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
name|ngx_http_auth_basic_loc_conf_t
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
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_auth_basic_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_auth_basic_merge_loc_conf
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
name|ngx_http_auth_basic_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_auth_basic_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
if|if
condition|(
name|conf
operator|->
name|realm
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|realm
operator|=
name|prev
operator|->
name|realm
expr_stmt|;
block|}
if|if
condition|(
name|conf
operator|->
name|user_file
operator|.
name|value
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|user_file
operator|=
name|prev
operator|->
name|user_file
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
DECL|function|ngx_http_auth_basic_init (ngx_conf_t * cf)
name|ngx_http_auth_basic_init
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
name|NGX_HTTP_ACCESS_PHASE
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
name|ngx_http_auth_basic_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_auth_basic_user_file (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_auth_basic_user_file
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
name|ngx_http_auth_basic_loc_conf_t
modifier|*
name|alcf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_http_compile_complex_value_t
name|ccv
decl_stmt|;
if|if
condition|(
name|alcf
operator|->
name|user_file
operator|.
name|value
operator|.
name|data
condition|)
block|{
return|return
literal|"is duplicate"
return|;
block|}
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|ccv
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_compile_complex_value_t
argument_list|)
argument_list|)
expr_stmt|;
name|ccv
operator|.
name|cf
operator|=
name|cf
expr_stmt|;
name|ccv
operator|.
name|value
operator|=
operator|&
name|value
index|[
literal|1
index|]
expr_stmt|;
name|ccv
operator|.
name|complex_value
operator|=
operator|&
name|alcf
operator|->
name|user_file
expr_stmt|;
name|ccv
operator|.
name|zero
operator|=
literal|1
expr_stmt|;
name|ccv
operator|.
name|conf_prefix
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ngx_http_compile_complex_value
argument_list|(
operator|&
name|ccv
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

