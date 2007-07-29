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

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_set_error_log
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
DECL|variable|ngx_errlog_commands
specifier|static
name|ngx_command_t
name|ngx_errlog_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"error_log"
argument_list|)
block|,
name|NGX_MAIN_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_set_error_log
block|,
literal|0
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
DECL|variable|ngx_errlog_module_ctx
specifier|static
name|ngx_core_module_t
name|ngx_errlog_module_ctx
init|=
block|{
name|ngx_string
argument_list|(
literal|"errlog"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_errlog_module
name|ngx_module_t
name|ngx_errlog_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_errlog_module_ctx
block|,
comment|/* module context */
name|ngx_errlog_commands
block|,
comment|/* module directives */
name|NGX_CORE_MODULE
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

begin_decl_stmt
DECL|variable|ngx_log
specifier|static
name|ngx_log_t
name|ngx_log
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_stderr
specifier|static
name|ngx_open_file_t
name|ngx_stderr
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|err_levels
specifier|static
specifier|const
name|char
modifier|*
name|err_levels
index|[]
init|=
block|{
literal|"stderr"
block|,
literal|"emerg"
block|,
literal|"alert"
block|,
literal|"crit"
block|,
literal|"error"
block|,
literal|"warn"
block|,
literal|"notice"
block|,
literal|"info"
block|,
literal|"debug"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|debug_levels
specifier|static
specifier|const
name|char
modifier|*
name|debug_levels
index|[]
init|=
block|{
literal|"debug_core"
block|,
literal|"debug_alloc"
block|,
literal|"debug_mutex"
block|,
literal|"debug_event"
block|,
literal|"debug_http"
block|,
literal|"debug_mail"
block|,
literal|"debug_mysql"
block|}
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_VARIADIC_MACROS
operator|)
end_if

begin_decl_stmt
name|void
DECL|function|ngx_log_error_core (ngx_uint_t level,ngx_log_t * log,ngx_err_t err,const char * fmt,...)
name|ngx_log_error_core
argument_list|(
name|ngx_uint_t
name|level
argument_list|,
name|ngx_log_t
operator|*
name|log
argument_list|,
name|ngx_err_t
name|err
argument_list|,
specifier|const
name|char
operator|*
name|fmt
argument_list|,
operator|...
argument_list|)
else|#
directive|else
name|void
name|ngx_log_error_core
argument_list|(
name|ngx_uint_t
name|level
argument_list|,
name|ngx_log_t
operator|*
name|log
argument_list|,
name|ngx_err_t
name|err
argument_list|,
specifier|const
name|char
operator|*
name|fmt
argument_list|,
name|va_list
name|args
argument_list|)
endif|#
directive|endif
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_VARIADIC_MACROS
operator|)
name|va_list
name|args
decl_stmt|;
endif|#
directive|endif
name|u_char
name|errstr
index|[
name|NGX_MAX_ERROR_STR
index|]
decl_stmt|,
modifier|*
name|p
decl_stmt|,
modifier|*
name|last
decl_stmt|;
if|if
condition|(
name|log
operator|->
name|file
operator|->
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
return|return;
block|}
name|last
operator|=
name|errstr
operator|+
name|NGX_MAX_ERROR_STR
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|errstr
argument_list|,
name|ngx_cached_err_log_time
operator|.
name|data
argument_list|,
name|ngx_cached_err_log_time
operator|.
name|len
argument_list|)
expr_stmt|;
name|p
operator|=
name|errstr
operator|+
name|ngx_cached_err_log_time
operator|.
name|len
expr_stmt|;
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
literal|" [%s] "
argument_list|,
name|err_levels
index|[
name|level
index|]
argument_list|)
expr_stmt|;
comment|/* pid#tid */
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
literal|"%P#"
name|NGX_TID_T_FMT
literal|": "
argument_list|,
name|ngx_log_pid
argument_list|,
name|ngx_log_tid
argument_list|)
expr_stmt|;
if|if
condition|(
name|log
operator|->
name|connection
condition|)
block|{
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
literal|"*%uA "
argument_list|,
name|log
operator|->
name|connection
argument_list|)
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_VARIADIC_MACROS
operator|)
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_vsnprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
else|#
directive|else
name|p
operator|=
name|ngx_vsnprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|err
condition|)
block|{
if|if
condition|(
name|p
operator|>
name|last
operator|-
literal|50
condition|)
block|{
comment|/* leave a space for an error code */
name|p
operator|=
name|last
operator|-
literal|50
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'.'
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'.'
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'.'
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_WIN32
operator|)
if|if
condition|(
operator|(
name|unsigned
operator|)
name|err
operator|>=
literal|0x80000000
condition|)
block|{
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
literal|" (%Xd: "
argument_list|,
name|err
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
literal|" (%d: "
argument_list|,
name|err
argument_list|)
expr_stmt|;
block|}
else|#
directive|else
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
literal|" (%d: "
argument_list|,
name|err
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|p
operator|=
name|ngx_strerror_r
argument_list|(
name|err
argument_list|,
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|<
name|last
condition|)
block|{
operator|*
name|p
operator|++
operator|=
literal|')'
expr_stmt|;
block|}
block|}
if|if
condition|(
name|level
operator|!=
name|NGX_LOG_DEBUG
operator|&&
name|log
operator|->
name|handler
condition|)
block|{
name|p
operator|=
name|log
operator|->
name|handler
argument_list|(
name|log
argument_list|,
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|p
operator|>
name|last
operator|-
name|NGX_LINEFEED_SIZE
condition|)
block|{
name|p
operator|=
name|last
operator|-
name|NGX_LINEFEED_SIZE
expr_stmt|;
block|}
name|ngx_linefeed
argument_list|(
name|p
argument_list|)
expr_stmt|;
name|ngx_write_fd
argument_list|(
name|log
operator|->
name|file
operator|->
name|fd
argument_list|,
name|errstr
argument_list|,
name|p
operator|-
name|errstr
argument_list|)
expr_stmt|;
block|}
end_decl_stmt

begin_if
if|#
directive|if
operator|!
operator|(
name|NGX_HAVE_VARIADIC_MACROS
operator|)
end_if

begin_function
name|void
name|ngx_cdecl
DECL|function|ngx_log_error (ngx_uint_t level,ngx_log_t * log,ngx_err_t err,const char * fmt,...)
name|ngx_log_error
parameter_list|(
name|ngx_uint_t
name|level
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|ngx_err_t
name|err
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
if|if
condition|(
name|log
operator|->
name|log_level
operator|>=
name|level
condition|)
block|{
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|ngx_log_error_core
argument_list|(
name|level
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
name|ngx_cdecl
DECL|function|ngx_log_debug_core (ngx_log_t * log,ngx_err_t err,const char * fmt,...)
name|ngx_log_debug_core
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|ngx_err_t
name|err
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
block|{
name|va_list
name|args
decl_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|ngx_log_error_core
argument_list|(
name|NGX_LOG_DEBUG
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
DECL|function|ngx_log_abort (ngx_err_t err,const char * text)
name|ngx_log_abort
parameter_list|(
name|ngx_err_t
name|err
parameter_list|,
specifier|const
name|char
modifier|*
name|text
parameter_list|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
name|err
argument_list|,
name|text
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ngx_log_t
modifier|*
DECL|function|ngx_log_init (void)
name|ngx_log_init
parameter_list|(
name|void
parameter_list|)
block|{
name|ngx_log
operator|.
name|file
operator|=
operator|&
name|ngx_stderr
expr_stmt|;
name|ngx_log
operator|.
name|log_level
operator|=
name|NGX_LOG_NOTICE
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_WIN32
operator|)
name|ngx_stderr_fileno
operator|=
name|GetStdHandle
argument_list|(
name|STD_ERROR_HANDLE
argument_list|)
expr_stmt|;
name|ngx_stderr
operator|.
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|NGX_ERROR_LOG_PATH
argument_list|,
name|NGX_FILE_RDWR
argument_list|,
name|NGX_FILE_CREATE_OR_OPEN
operator||
name|NGX_FILE_APPEND
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_stderr
operator|.
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|ngx_message_box
argument_list|(
literal|"nginx"
argument_list|,
name|MB_OK
argument_list|,
name|ngx_errno
argument_list|,
literal|"Could not open error log file: "
name|ngx_open_file_n
literal|" \""
name|NGX_ERROR_LOG_PATH
literal|"\" failed"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|ngx_file_append_mode
argument_list|(
name|ngx_stderr
operator|.
name|fd
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_message_box
argument_list|(
literal|"nginx"
argument_list|,
name|MB_OK
argument_list|,
name|ngx_errno
argument_list|,
literal|"Could not open error log file: "
name|ngx_file_append_mode_n
literal|" \""
name|NGX_ERROR_LOG_PATH
literal|"\" failed"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
else|#
directive|else
name|ngx_stderr
operator|.
name|fd
operator|=
name|STDERR_FILENO
expr_stmt|;
endif|#
directive|endif
return|return
operator|&
name|ngx_log
return|;
block|}
end_function

begin_function
name|ngx_log_t
modifier|*
DECL|function|ngx_log_create_errlog (ngx_cycle_t * cycle,ngx_array_t * args)
name|ngx_log_create_errlog
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_array_t
modifier|*
name|args
parameter_list|)
block|{
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
modifier|*
name|name
decl_stmt|;
if|if
condition|(
name|args
condition|)
block|{
name|value
operator|=
name|args
operator|->
name|elts
expr_stmt|;
name|name
operator|=
operator|&
name|value
index|[
literal|1
index|]
expr_stmt|;
block|}
else|else
block|{
name|name
operator|=
name|NULL
expr_stmt|;
block|}
name|log
operator|=
name|ngx_pcalloc
argument_list|(
name|cycle
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_log_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|log
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|log
operator|->
name|file
operator|=
name|ngx_conf_open_file
argument_list|(
name|cycle
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|log
operator|->
name|file
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
return|return
name|log
return|;
block|}
end_function

begin_function
name|char
modifier|*
DECL|function|ngx_set_error_log_levels (ngx_conf_t * cf,ngx_log_t * log)
name|ngx_set_error_log_levels
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|,
name|d
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
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
literal|2
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
for|for
control|(
name|n
operator|=
literal|1
init|;
name|n
operator|<=
name|NGX_LOG_DEBUG
condition|;
name|n
operator|++
control|)
block|{
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
name|err_levels
index|[
name|n
index|]
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|log
operator|->
name|log_level
operator|!=
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
literal|"duplicate log level \"%s\""
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|log
operator|->
name|log_level
operator|=
name|n
expr_stmt|;
continue|continue;
block|}
block|}
for|for
control|(
name|n
operator|=
literal|0
operator|,
name|d
operator|=
name|NGX_LOG_DEBUG_FIRST
init|;
name|d
operator|<=
name|NGX_LOG_DEBUG_LAST
condition|;
name|d
operator|<<=
literal|1
control|)
block|{
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
name|debug_levels
index|[
name|n
operator|++
index|]
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|log
operator|->
name|log_level
operator|&
operator|~
name|NGX_LOG_DEBUG_ALL
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
literal|"invalid log level \"%s\""
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|log
operator|->
name|log_level
operator||=
name|d
expr_stmt|;
block|}
block|}
if|if
condition|(
name|log
operator|->
name|log_level
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
literal|"invalid log level \"%s\""
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
if|if
condition|(
name|log
operator|->
name|log_level
operator|==
name|NGX_LOG_DEBUG
condition|)
block|{
name|log
operator|->
name|log_level
operator|=
name|NGX_LOG_DEBUG_ALL
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_set_error_log (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_set_error_log
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
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
if|if
condition|(
name|value
index|[
literal|1
index|]
operator|.
name|len
operator|==
literal|6
operator|&&
name|ngx_strcmp
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
literal|"stderr"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|cf
operator|->
name|cycle
operator|->
name|new_log
operator|->
name|file
operator|->
name|fd
operator|=
name|ngx_stderr
operator|.
name|fd
expr_stmt|;
name|cf
operator|->
name|cycle
operator|->
name|new_log
operator|->
name|file
operator|->
name|name
operator|.
name|len
operator|=
literal|0
expr_stmt|;
name|cf
operator|->
name|cycle
operator|->
name|new_log
operator|->
name|file
operator|->
name|name
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
block|}
else|else
block|{
name|cf
operator|->
name|cycle
operator|->
name|new_log
operator|->
name|file
operator|->
name|name
operator|=
name|value
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|ngx_conf_full_name
argument_list|(
name|cf
operator|->
name|cycle
argument_list|,
operator|&
name|cf
operator|->
name|cycle
operator|->
name|new_log
operator|->
name|file
operator|->
name|name
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
return|return
name|ngx_set_error_log_levels
argument_list|(
name|cf
argument_list|,
name|cf
operator|->
name|cycle
operator|->
name|new_log
argument_list|)
return|;
block|}
end_function

end_unit

