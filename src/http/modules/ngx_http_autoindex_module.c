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

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|typedef struct {     ngx_buf_t     *buf;     size_t         size;     ngx_pool_t    *pool;     size_t         alloc_size;     ngx_chain_t  **last_out; } ngx_http_autoindex_ctx_t;
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2a4555a50108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|utf_len
name|size_t
name|utf_len
decl_stmt|;
DECL|member|escape
name|ngx_uint_t
name|escape
decl_stmt|;
DECL|member|dir
name|ngx_uint_t
name|dir
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|size
name|off_t
name|size
decl_stmt|;
DECL|typedef|ngx_http_autoindex_entry_t
block|}
name|ngx_http_autoindex_entry_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a4555a50208
typedef|typedef
struct|struct
block|{
DECL|member|enable
name|ngx_flag_t
name|enable
decl_stmt|;
DECL|member|localtime
name|ngx_flag_t
name|localtime
decl_stmt|;
DECL|member|exact_size
name|ngx_flag_t
name|exact_size
decl_stmt|;
DECL|typedef|ngx_http_autoindex_loc_conf_t
block|}
name|ngx_http_autoindex_loc_conf_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_AUTOINDEX_PREALLOCATE
define|#
directive|define
name|NGX_HTTP_AUTOINDEX_PREALLOCATE
value|50
end_define

begin_define
DECL|macro|NGX_HTTP_AUTOINDEX_NAME_LEN
define|#
directive|define
name|NGX_HTTP_AUTOINDEX_NAME_LEN
value|50
end_define

begin_function_decl
specifier|static
name|int
name|ngx_libc_cdecl
name|ngx_http_autoindex_cmp_entries
parameter_list|(
specifier|const
name|void
modifier|*
name|one
parameter_list|,
specifier|const
name|void
modifier|*
name|two
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_autoindex_error
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
name|ngx_http_autoindex_init
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
name|ngx_http_autoindex_create_loc_conf
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
name|ngx_http_autoindex_merge_loc_conf
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
DECL|variable|ngx_http_autoindex_commands
specifier|static
name|ngx_command_t
name|ngx_http_autoindex_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"autoindex"
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
name|ngx_http_autoindex_loc_conf_t
argument_list|,
name|enable
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"autoindex_localtime"
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
name|ngx_http_autoindex_loc_conf_t
argument_list|,
name|localtime
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"autoindex_exact_size"
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
name|ngx_http_autoindex_loc_conf_t
argument_list|,
name|exact_size
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
DECL|variable|ngx_http_autoindex_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_autoindex_module_ctx
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
name|ngx_http_autoindex_create_loc_conf
block|,
comment|/* create location configration */
name|ngx_http_autoindex_merge_loc_conf
comment|/* merge location configration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_autoindex_module
name|ngx_module_t
name|ngx_http_autoindex_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_autoindex_module_ctx
block|,
comment|/* module context */
name|ngx_http_autoindex_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|ngx_http_autoindex_init
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

begin_decl_stmt
DECL|variable|title
specifier|static
name|u_char
name|title
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>Index of "
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|header
specifier|static
name|u_char
name|header
index|[]
init|=
literal|"</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<h1>Index of "
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|tail
specifier|static
name|u_char
name|tail
index|[]
init|=
literal|"</body>"
name|CRLF
literal|"</html>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_autoindex_handler (ngx_http_request_t * r)
name|ngx_http_autoindex_handler
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
decl_stmt|,
name|scale
decl_stmt|;
name|off_t
name|length
decl_stmt|;
name|size_t
name|len
decl_stmt|,
name|copy
decl_stmt|,
name|allocated
decl_stmt|;
name|ngx_tm_t
name|tm
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|,
name|size
decl_stmt|;
name|ngx_str_t
name|path
decl_stmt|;
name|ngx_dir_t
name|dir
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|level
decl_stmt|;
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
name|ngx_time_t
modifier|*
name|tp
decl_stmt|;
name|ngx_chain_t
name|out
decl_stmt|;
name|ngx_array_t
name|entries
decl_stmt|;
name|ngx_http_autoindex_entry_t
modifier|*
name|entry
decl_stmt|;
name|ngx_http_autoindex_loc_conf_t
modifier|*
name|alcf
decl_stmt|;
specifier|static
name|char
modifier|*
name|months
index|[]
init|=
block|{
literal|"Jan"
block|,
literal|"Feb"
block|,
literal|"Mar"
block|,
literal|"Apr"
block|,
literal|"May"
block|,
literal|"Jun"
block|,
literal|"Jul"
block|,
literal|"Aug"
block|,
literal|"Sep"
block|,
literal|"Oct"
block|,
literal|"Nov"
block|,
literal|"Dec"
block|}
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
operator|)
operator|)
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|alcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_autoindex_module
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|alcf
operator|->
name|enable
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
comment|/* NGX_DIR_MASK_LEN is lesser than NGX_HTTP_AUTOINDEX_PREALLOCATE */
name|last
operator|=
name|ngx_http_map_uri_to_path
argument_list|(
name|r
argument_list|,
operator|&
name|path
argument_list|,
name|NGX_HTTP_AUTOINDEX_PREALLOCATE
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
literal|"http autoindex: \"%s\""
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
if|#
directive|if
operator|(
name|NGX_SUPPRESS_WARN
operator|)
comment|/* MSVC thinks 'entries' may be used without having been initialized */
name|ngx_memzero
argument_list|(
operator|&
name|entries
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_array_t
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* TODO: pool should be temporary pool */
name|pool
operator|=
name|r
operator|->
name|pool
expr_stmt|;
if|if
condition|(
name|ngx_array_init
argument_list|(
operator|&
name|entries
argument_list|,
name|pool
argument_list|,
literal|40
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_autoindex_entry_t
argument_list|)
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|ngx_http_autoindex_error
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
name|content_type
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"text/html"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|.
name|data
operator|=
operator|(
name|u_char
operator|*
operator|)
literal|"text/html"
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
name|ngx_http_autoindex_error
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
literal|"http autoindex file: \"%s\""
argument_list|,
name|ngx_de_name
argument_list|(
operator|&
name|dir
argument_list|)
argument_list|)
expr_stmt|;
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
if|if
condition|(
operator|!
name|dir
operator|.
name|valid_info
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
name|NGX_HTTP_AUTOINDEX_PREALLOCATE
expr_stmt|;
name|filename
operator|=
name|ngx_palloc
argument_list|(
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
name|ngx_http_autoindex_error
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
name|ngx_http_autoindex_error
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
name|ngx_http_autoindex_error
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
name|entry
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|entries
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|==
name|NULL
condition|)
block|{
return|return
name|ngx_http_autoindex_error
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
name|entry
operator|->
name|name
operator|.
name|len
operator|=
name|len
expr_stmt|;
name|entry
operator|->
name|name
operator|.
name|data
operator|=
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
operator|->
name|name
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|ngx_http_autoindex_error
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
name|ngx_cpystrn
argument_list|(
name|entry
operator|->
name|name
operator|.
name|data
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
name|entry
operator|->
name|escape
operator|=
literal|2
operator|*
name|ngx_escape_uri
argument_list|(
name|NULL
argument_list|,
name|ngx_de_name
argument_list|(
operator|&
name|dir
argument_list|)
argument_list|,
name|len
argument_list|,
name|NGX_ESCAPE_HTML
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|utf8
condition|)
block|{
name|entry
operator|->
name|utf_len
operator|=
name|ngx_utf_length
argument_list|(
name|entry
operator|->
name|name
operator|.
name|data
argument_list|,
name|entry
operator|->
name|name
operator|.
name|len
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|entry
operator|->
name|utf_len
operator|=
name|len
expr_stmt|;
block|}
name|entry
operator|->
name|dir
operator|=
name|ngx_de_is_dir
argument_list|(
operator|&
name|dir
argument_list|)
expr_stmt|;
name|entry
operator|->
name|mtime
operator|=
name|ngx_de_mtime
argument_list|(
operator|&
name|dir
argument_list|)
expr_stmt|;
name|entry
operator|->
name|size
operator|=
name|ngx_de_size
argument_list|(
operator|&
name|dir
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
literal|" \"%s\" failed"
argument_list|,
operator|&
name|path
argument_list|)
expr_stmt|;
block|}
name|len
operator|=
sizeof|sizeof
argument_list|(
name|title
argument_list|)
operator|-
literal|1
operator|+
name|r
operator|->
name|uri
operator|.
name|len
operator|+
sizeof|sizeof
argument_list|(
name|header
argument_list|)
operator|-
literal|1
operator|+
name|r
operator|->
name|uri
operator|.
name|len
operator|+
sizeof|sizeof
argument_list|(
literal|"</h1>"
argument_list|)
operator|-
literal|1
operator|+
sizeof|sizeof
argument_list|(
literal|"<hr><pre><a href=\"../\">../</a>"
name|CRLF
argument_list|)
operator|-
literal|1
operator|+
sizeof|sizeof
argument_list|(
literal|"</pre><hr>"
argument_list|)
operator|-
literal|1
operator|+
sizeof|sizeof
argument_list|(
name|tail
argument_list|)
operator|-
literal|1
expr_stmt|;
name|entry
operator|=
name|entries
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
name|entries
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"<a href=\""
argument_list|)
operator|-
literal|1
operator|+
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|+
name|entry
index|[
name|i
index|]
operator|.
name|escape
operator|+
literal|1
comment|/* 1 is for "/" */
operator|+
sizeof|sizeof
argument_list|(
literal|"\">"
argument_list|)
operator|-
literal|1
operator|+
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|-
name|entry
index|[
name|i
index|]
operator|.
name|utf_len
operator|+
name|NGX_HTTP_AUTOINDEX_NAME_LEN
operator|+
sizeof|sizeof
argument_list|(
literal|"&gt;"
argument_list|)
operator|-
literal|2
operator|+
sizeof|sizeof
argument_list|(
literal|"</a>"
argument_list|)
operator|-
literal|1
operator|+
sizeof|sizeof
argument_list|(
literal|" 28-Sep-1970 12:00 "
argument_list|)
operator|-
literal|1
operator|+
literal|20
comment|/* the file size */
operator|+
literal|2
expr_stmt|;
block|}
name|b
operator|=
name|ngx_create_temp_buf
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
name|b
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
if|if
condition|(
name|entries
operator|.
name|nelts
operator|>
literal|1
condition|)
block|{
name|ngx_qsort
argument_list|(
name|entry
argument_list|,
operator|(
name|size_t
operator|)
name|entries
operator|.
name|nelts
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_autoindex_entry_t
argument_list|)
argument_list|,
name|ngx_http_autoindex_cmp_entries
argument_list|)
expr_stmt|;
block|}
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|title
argument_list|,
sizeof|sizeof
argument_list|(
name|title
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
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
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|header
argument_list|,
sizeof|sizeof
argument_list|(
name|header
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
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
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"</h1>"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"</h1>"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"<hr><pre><a href=\"../\">../</a>"
name|CRLF
argument_list|,
sizeof|sizeof
argument_list|(
literal|"<hr><pre><a href=\"../\">../</a>"
name|CRLF
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|tp
operator|=
name|ngx_timeofday
argument_list|()
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|entries
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"<a href=\""
argument_list|,
sizeof|sizeof
argument_list|(
literal|"<a href=\""
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|entry
index|[
name|i
index|]
operator|.
name|escape
condition|)
block|{
name|ngx_escape_uri
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
argument_list|,
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
argument_list|,
name|NGX_ESCAPE_HTML
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|+=
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|+
name|entry
index|[
name|i
index|]
operator|.
name|escape
expr_stmt|;
block|}
else|else
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
argument_list|,
name|entry
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
if|if
condition|(
name|entry
index|[
name|i
index|]
operator|.
name|dir
condition|)
block|{
operator|*
name|b
operator|->
name|last
operator|++
operator|=
literal|'/'
expr_stmt|;
block|}
operator|*
name|b
operator|->
name|last
operator|++
operator|=
literal|'"'
expr_stmt|;
operator|*
name|b
operator|->
name|last
operator|++
operator|=
literal|'>'
expr_stmt|;
name|len
operator|=
name|entry
index|[
name|i
index|]
operator|.
name|utf_len
expr_stmt|;
if|if
condition|(
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|len
operator|-
name|len
condition|)
block|{
if|if
condition|(
name|len
operator|>
name|NGX_HTTP_AUTOINDEX_NAME_LEN
condition|)
block|{
name|copy
operator|=
name|NGX_HTTP_AUTOINDEX_NAME_LEN
operator|-
literal|3
operator|+
literal|1
expr_stmt|;
block|}
else|else
block|{
name|copy
operator|=
name|NGX_HTTP_AUTOINDEX_NAME_LEN
operator|+
literal|1
expr_stmt|;
block|}
name|b
operator|->
name|last
operator|=
name|ngx_utf_cpystrn
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
argument_list|,
name|copy
argument_list|)
expr_stmt|;
name|last
operator|=
name|b
operator|->
name|last
expr_stmt|;
block|}
else|else
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpystrn
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|entry
index|[
name|i
index|]
operator|.
name|name
operator|.
name|data
argument_list|,
name|NGX_HTTP_AUTOINDEX_NAME_LEN
operator|+
literal|1
argument_list|)
expr_stmt|;
name|last
operator|=
name|b
operator|->
name|last
operator|-
literal|3
expr_stmt|;
block|}
if|if
condition|(
name|len
operator|>
name|NGX_HTTP_AUTOINDEX_NAME_LEN
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|last
argument_list|,
literal|"..&gt;</a>"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"..&gt;</a>"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|entry
index|[
name|i
index|]
operator|.
name|dir
operator|&&
name|NGX_HTTP_AUTOINDEX_NAME_LEN
operator|-
name|len
operator|>
literal|0
condition|)
block|{
operator|*
name|b
operator|->
name|last
operator|++
operator|=
literal|'/'
expr_stmt|;
name|len
operator|++
expr_stmt|;
block|}
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"</a>"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"</a>"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ngx_memset
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|' '
argument_list|,
name|NGX_HTTP_AUTOINDEX_NAME_LEN
operator|-
name|len
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|+=
name|NGX_HTTP_AUTOINDEX_NAME_LEN
operator|-
name|len
expr_stmt|;
block|}
operator|*
name|b
operator|->
name|last
operator|++
operator|=
literal|' '
expr_stmt|;
name|ngx_gmtime
argument_list|(
name|entry
index|[
name|i
index|]
operator|.
name|mtime
operator|+
name|tp
operator|->
name|gmtoff
operator|*
literal|60
operator|*
name|alcf
operator|->
name|localtime
argument_list|,
operator|&
name|tm
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_sprintf
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"%02d-%s-%d %02d:%02d "
argument_list|,
name|tm
operator|.
name|ngx_tm_mday
argument_list|,
name|months
index|[
name|tm
operator|.
name|ngx_tm_mon
operator|-
literal|1
index|]
argument_list|,
name|tm
operator|.
name|ngx_tm_year
argument_list|,
name|tm
operator|.
name|ngx_tm_hour
argument_list|,
name|tm
operator|.
name|ngx_tm_min
argument_list|)
expr_stmt|;
if|if
condition|(
name|alcf
operator|->
name|exact_size
condition|)
block|{
if|if
condition|(
name|entry
index|[
name|i
index|]
operator|.
name|dir
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"                  -"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"                  -"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|b
operator|->
name|last
operator|=
name|ngx_sprintf
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"%19O"
argument_list|,
name|entry
index|[
name|i
index|]
operator|.
name|size
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|entry
index|[
name|i
index|]
operator|.
name|dir
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"      -"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"      -"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|length
operator|=
name|entry
index|[
name|i
index|]
operator|.
name|size
expr_stmt|;
if|if
condition|(
name|length
operator|>
literal|1024
operator|*
literal|1024
operator|*
literal|1024
operator|-
literal|1
condition|)
block|{
name|size
operator|=
operator|(
name|ngx_int_t
operator|)
operator|(
name|length
operator|/
operator|(
literal|1024
operator|*
literal|1024
operator|*
literal|1024
operator|)
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|length
operator|%
operator|(
literal|1024
operator|*
literal|1024
operator|*
literal|1024
operator|)
operator|)
operator|>
operator|(
literal|1024
operator|*
literal|1024
operator|*
literal|1024
operator|/
literal|2
operator|-
literal|1
operator|)
condition|)
block|{
name|size
operator|++
expr_stmt|;
block|}
name|scale
operator|=
literal|'G'
expr_stmt|;
block|}
if|else if
condition|(
name|length
operator|>
literal|1024
operator|*
literal|1024
operator|-
literal|1
condition|)
block|{
name|size
operator|=
operator|(
name|ngx_int_t
operator|)
operator|(
name|length
operator|/
operator|(
literal|1024
operator|*
literal|1024
operator|)
operator|)
expr_stmt|;
if|if
condition|(
operator|(
name|length
operator|%
operator|(
literal|1024
operator|*
literal|1024
operator|)
operator|)
operator|>
operator|(
literal|1024
operator|*
literal|1024
operator|/
literal|2
operator|-
literal|1
operator|)
condition|)
block|{
name|size
operator|++
expr_stmt|;
block|}
name|scale
operator|=
literal|'M'
expr_stmt|;
block|}
if|else if
condition|(
name|length
operator|>
literal|9999
condition|)
block|{
name|size
operator|=
operator|(
name|ngx_int_t
operator|)
operator|(
name|length
operator|/
literal|1024
operator|)
expr_stmt|;
if|if
condition|(
name|length
operator|%
literal|1024
operator|>
literal|511
condition|)
block|{
name|size
operator|++
expr_stmt|;
block|}
name|scale
operator|=
literal|'K'
expr_stmt|;
block|}
else|else
block|{
name|size
operator|=
operator|(
name|ngx_int_t
operator|)
name|length
expr_stmt|;
name|scale
operator|=
literal|'\0'
expr_stmt|;
block|}
if|if
condition|(
name|scale
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_sprintf
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"%6i%c"
argument_list|,
name|size
argument_list|,
name|scale
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|b
operator|->
name|last
operator|=
name|ngx_sprintf
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|" %6i"
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
block|}
block|}
operator|*
name|b
operator|->
name|last
operator|++
operator|=
name|CR
expr_stmt|;
operator|*
name|b
operator|->
name|last
operator|++
operator|=
name|LF
expr_stmt|;
block|}
comment|/* TODO: free temporary pool */
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"</pre><hr>"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"</pre><hr>"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|tail
argument_list|,
sizeof|sizeof
argument_list|(
name|tail
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|==
name|r
operator|->
expr|main
condition|)
block|{
name|b
operator|->
name|last_buf
operator|=
literal|1
expr_stmt|;
block|}
name|b
operator|->
name|last_in_chain
operator|=
literal|1
expr_stmt|;
name|out
operator|.
name|buf
operator|=
name|b
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
specifier|static
name|int
name|ngx_libc_cdecl
DECL|function|ngx_http_autoindex_cmp_entries (const void * one,const void * two)
name|ngx_http_autoindex_cmp_entries
parameter_list|(
specifier|const
name|void
modifier|*
name|one
parameter_list|,
specifier|const
name|void
modifier|*
name|two
parameter_list|)
block|{
name|ngx_http_autoindex_entry_t
modifier|*
name|first
init|=
operator|(
name|ngx_http_autoindex_entry_t
operator|*
operator|)
name|one
decl_stmt|;
name|ngx_http_autoindex_entry_t
modifier|*
name|second
init|=
operator|(
name|ngx_http_autoindex_entry_t
operator|*
operator|)
name|two
decl_stmt|;
if|if
condition|(
name|first
operator|->
name|dir
operator|&&
operator|!
name|second
operator|->
name|dir
condition|)
block|{
comment|/* move the directories to the start */
return|return
operator|-
literal|1
return|;
block|}
if|if
condition|(
operator|!
name|first
operator|->
name|dir
operator|&&
name|second
operator|->
name|dir
condition|)
block|{
comment|/* move the directories to the start */
return|return
literal|1
return|;
block|}
return|return
operator|(
name|int
operator|)
name|ngx_strcmp
argument_list|(
name|first
operator|->
name|name
operator|.
name|data
argument_list|,
name|second
operator|->
name|name
operator|.
name|data
argument_list|)
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static ngx_buf_t * ngx_http_autoindex_alloc(ngx_http_autoindex_ctx_t *ctx, size_t size) {     ngx_chain_t  *cl;      if (ctx->buf) {          if ((size_t) (ctx->buf->end - ctx->buf->last)>= size) {             return ctx->buf;         }          ctx->size += ctx->buf->last - ctx->buf->pos;     }      ctx->buf = ngx_create_temp_buf(ctx->pool, ctx->alloc_size);     if (ctx->buf == NULL) {         return NULL;     }      cl = ngx_alloc_chain_link(ctx->pool);     if (cl == NULL) {         return NULL;     }      cl->buf = ctx->buf;     cl->next = NULL;      *ctx->last_out = cl;     ctx->last_out =&cl->next;      return ctx->buf; }
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_autoindex_error (ngx_http_request_t * r,ngx_dir_t * dir,ngx_str_t * name)
name|ngx_http_autoindex_error
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
name|ngx_int_t
DECL|function|ngx_http_autoindex_init (ngx_cycle_t * cycle)
name|ngx_http_autoindex_init
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
name|ngx_http_autoindex_handler
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
DECL|function|ngx_http_autoindex_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_autoindex_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_autoindex_loc_conf_t
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
name|ngx_http_autoindex_loc_conf_t
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
name|enable
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|conf
operator|->
name|localtime
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|conf
operator|->
name|exact_size
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
DECL|function|ngx_http_autoindex_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_autoindex_merge_loc_conf
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
name|ngx_http_autoindex_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_autoindex_loc_conf_t
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
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|localtime
argument_list|,
name|prev
operator|->
name|localtime
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|exact_size
argument_list|,
name|prev
operator|->
name|exact_size
argument_list|,
literal|1
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

