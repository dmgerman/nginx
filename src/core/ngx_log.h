begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_LOG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_LOG_H_INCLUDED_
define|#
directive|define
name|_NGX_LOG_H_INCLUDED_
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

begin_define
DECL|macro|NGX_LOG_STDERR
define|#
directive|define
name|NGX_LOG_STDERR
value|0
end_define

begin_define
DECL|macro|NGX_LOG_EMERG
define|#
directive|define
name|NGX_LOG_EMERG
value|1
end_define

begin_define
DECL|macro|NGX_LOG_ALERT
define|#
directive|define
name|NGX_LOG_ALERT
value|2
end_define

begin_define
DECL|macro|NGX_LOG_CRIT
define|#
directive|define
name|NGX_LOG_CRIT
value|3
end_define

begin_define
DECL|macro|NGX_LOG_ERR
define|#
directive|define
name|NGX_LOG_ERR
value|4
end_define

begin_define
DECL|macro|NGX_LOG_WARN
define|#
directive|define
name|NGX_LOG_WARN
value|5
end_define

begin_define
DECL|macro|NGX_LOG_NOTICE
define|#
directive|define
name|NGX_LOG_NOTICE
value|6
end_define

begin_define
DECL|macro|NGX_LOG_INFO
define|#
directive|define
name|NGX_LOG_INFO
value|7
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG
define|#
directive|define
name|NGX_LOG_DEBUG
value|8
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_CORE
define|#
directive|define
name|NGX_LOG_DEBUG_CORE
value|0x010
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_ALLOC
define|#
directive|define
name|NGX_LOG_DEBUG_ALLOC
value|0x020
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_MUTEX
define|#
directive|define
name|NGX_LOG_DEBUG_MUTEX
value|0x040
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_EVENT
define|#
directive|define
name|NGX_LOG_DEBUG_EVENT
value|0x080
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_HTTP
define|#
directive|define
name|NGX_LOG_DEBUG_HTTP
value|0x100
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_MAIL
define|#
directive|define
name|NGX_LOG_DEBUG_MAIL
value|0x200
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_MYSQL
define|#
directive|define
name|NGX_LOG_DEBUG_MYSQL
value|0x400
end_define

begin_comment
comment|/*  * do not forget to update debug_levels[] in src/core/ngx_log.c  * after the adding a new debug level  */
end_comment

begin_define
DECL|macro|NGX_LOG_DEBUG_FIRST
define|#
directive|define
name|NGX_LOG_DEBUG_FIRST
value|NGX_LOG_DEBUG_CORE
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_LAST
define|#
directive|define
name|NGX_LOG_DEBUG_LAST
value|NGX_LOG_DEBUG_MYSQL
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_CONNECTION
define|#
directive|define
name|NGX_LOG_DEBUG_CONNECTION
value|0x80000000
end_define

begin_define
DECL|macro|NGX_LOG_DEBUG_ALL
define|#
directive|define
name|NGX_LOG_DEBUG_ALL
value|0x7ffffff0
end_define

begin_typedef
DECL|typedef|ngx_log_handler_pt
typedef|typedef
name|u_char
modifier|*
function_decl|(
modifier|*
name|ngx_log_handler_pt
function_decl|)
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_log_s
struct|struct
name|ngx_log_s
block|{
DECL|member|log_level
name|ngx_uint_t
name|log_level
decl_stmt|;
DECL|member|file
name|ngx_open_file_t
modifier|*
name|file
decl_stmt|;
DECL|member|connection
name|ngx_atomic_uint_t
name|connection
decl_stmt|;
DECL|member|handler
name|ngx_log_handler_pt
name|handler
decl_stmt|;
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
comment|/*      * we declare "action" as "char *" because the actions are usually      * the static strings and in the "u_char *" case we have to override      * their types all the time      */
DECL|member|action
name|char
modifier|*
name|action
decl_stmt|;
DECL|member|next
name|ngx_log_t
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|NGX_MAX_ERROR_STR
define|#
directive|define
name|NGX_MAX_ERROR_STR
value|2048
end_define

begin_comment
comment|/*********************************/
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_C99_VARIADIC_MACROS
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_VARIADIC_MACROS
define|#
directive|define
name|NGX_HAVE_VARIADIC_MACROS
value|1
end_define

begin_define
DECL|macro|ngx_log_error (level,log,...)
define|#
directive|define
name|ngx_log_error
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
modifier|...
parameter_list|)
define|\
value|if ((log)->log_level>= level) ngx_log_error_core(level, log, __VA_ARGS__)
end_define

begin_function_decl
name|void
name|ngx_log_error_core
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
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_log_debug (level,log,...)
define|#
directive|define
name|ngx_log_debug
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
modifier|...
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_error_core(NGX_LOG_DEBUG, log, __VA_ARGS__)
end_define

begin_comment
comment|/*********************************/
end_comment

begin_elif
elif|#
directive|elif
operator|(
name|NGX_HAVE_GCC_VARIADIC_MACROS
operator|)
end_elif

begin_define
DECL|macro|NGX_HAVE_VARIADIC_MACROS
define|#
directive|define
name|NGX_HAVE_VARIADIC_MACROS
value|1
end_define

begin_define
DECL|macro|ngx_log_error (level,log,args...)
define|#
directive|define
name|ngx_log_error
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|args
modifier|...
parameter_list|)
define|\
value|if ((log)->log_level>= level) ngx_log_error_core(level, log, args)
end_define

begin_function_decl
name|void
name|ngx_log_error_core
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
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_log_debug (level,log,args...)
define|#
directive|define
name|ngx_log_debug
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|args
modifier|...
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_error_core(NGX_LOG_DEBUG, log, args)
end_define

begin_comment
comment|/*********************************/
end_comment

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* NO VARIADIC MACROS */
end_comment

begin_define
DECL|macro|NGX_HAVE_VARIADIC_MACROS
define|#
directive|define
name|NGX_HAVE_VARIADIC_MACROS
value|0
end_define

begin_function_decl
name|void
name|ngx_cdecl
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_log_error_core
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
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_cdecl
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* VARIADIC MACROS */
end_comment

begin_comment
comment|/*********************************/
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
end_if

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_VARIADIC_MACROS
operator|)
end_if

begin_define
DECL|macro|ngx_log_debug0 (level,log,err,fmt)
define|#
directive|define
name|ngx_log_debug0
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt)
end_define

begin_define
DECL|macro|ngx_log_debug1 (level,log,err,fmt,arg1)
define|#
directive|define
name|ngx_log_debug1
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt, arg1)
end_define

begin_define
DECL|macro|ngx_log_debug2 (level,log,err,fmt,arg1,arg2)
define|#
directive|define
name|ngx_log_debug2
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt, arg1, arg2)
end_define

begin_define
DECL|macro|ngx_log_debug3 (level,log,err,fmt,arg1,arg2,arg3)
define|#
directive|define
name|ngx_log_debug3
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3)
end_define

begin_define
DECL|macro|ngx_log_debug4 (level,log,err,fmt,arg1,arg2,arg3,arg4)
define|#
directive|define
name|ngx_log_debug4
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4)
end_define

begin_define
DECL|macro|ngx_log_debug5 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5)
define|#
directive|define
name|ngx_log_debug5
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)
end_define

begin_define
DECL|macro|ngx_log_debug6 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6)
define|#
directive|define
name|ngx_log_debug6
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,                                  \
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,
name|arg6
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt,                                   \                        arg1, arg2, arg3, arg4, arg5, arg6)
end_define

begin_define
DECL|macro|ngx_log_debug7 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
define|#
directive|define
name|ngx_log_debug7
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,                                  \
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,
name|arg6
parameter_list|,
name|arg7
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt,                                   \                        arg1, arg2, arg3, arg4, arg5, arg6, arg7)
end_define

begin_define
DECL|macro|ngx_log_debug8 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
define|#
directive|define
name|ngx_log_debug8
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,                                  \
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,
name|arg6
parameter_list|,
name|arg7
parameter_list|,
name|arg8
parameter_list|)
define|\
value|ngx_log_debug(level, log, err, fmt,                                   \                        arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* NO VARIADIC MACROS */
end_comment

begin_define
DECL|macro|ngx_log_debug0 (level,log,err,fmt)
define|#
directive|define
name|ngx_log_debug0
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt)
end_define

begin_define
DECL|macro|ngx_log_debug1 (level,log,err,fmt,arg1)
define|#
directive|define
name|ngx_log_debug1
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt, arg1)
end_define

begin_define
DECL|macro|ngx_log_debug2 (level,log,err,fmt,arg1,arg2)
define|#
directive|define
name|ngx_log_debug2
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt, arg1, arg2)
end_define

begin_define
DECL|macro|ngx_log_debug3 (level,log,err,fmt,arg1,arg2,arg3)
define|#
directive|define
name|ngx_log_debug3
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt, arg1, arg2, arg3)
end_define

begin_define
DECL|macro|ngx_log_debug4 (level,log,err,fmt,arg1,arg2,arg3,arg4)
define|#
directive|define
name|ngx_log_debug4
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt, arg1, arg2, arg3, arg4)
end_define

begin_define
DECL|macro|ngx_log_debug5 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5)
define|#
directive|define
name|ngx_log_debug5
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt, arg1, arg2, arg3, arg4, arg5)
end_define

begin_define
DECL|macro|ngx_log_debug6 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6)
define|#
directive|define
name|ngx_log_debug6
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,                                  \
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,
name|arg6
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
end_define

begin_define
DECL|macro|ngx_log_debug7 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
define|#
directive|define
name|ngx_log_debug7
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,                                  \
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,
name|arg6
parameter_list|,
name|arg7
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt,                                     \                        arg1, arg2, arg3, arg4, arg5, arg6, arg7)
end_define

begin_define
DECL|macro|ngx_log_debug8 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
define|#
directive|define
name|ngx_log_debug8
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,                                  \
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,
name|arg6
parameter_list|,
name|arg7
parameter_list|,
name|arg8
parameter_list|)
define|\
value|if ((log)->log_level& level)                                             \         ngx_log_debug_core(log, err, fmt,                                     \                        arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* NO NGX_DEBUG */
end_comment

begin_define
DECL|macro|ngx_log_debug0 (level,log,err,fmt)
define|#
directive|define
name|ngx_log_debug0
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|)
end_define

begin_define
DECL|macro|ngx_log_debug1 (level,log,err,fmt,arg1)
define|#
directive|define
name|ngx_log_debug1
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|)
end_define

begin_define
DECL|macro|ngx_log_debug2 (level,log,err,fmt,arg1,arg2)
define|#
directive|define
name|ngx_log_debug2
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|)
end_define

begin_define
DECL|macro|ngx_log_debug3 (level,log,err,fmt,arg1,arg2,arg3)
define|#
directive|define
name|ngx_log_debug3
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|)
end_define

begin_define
DECL|macro|ngx_log_debug4 (level,log,err,fmt,arg1,arg2,arg3,arg4)
define|#
directive|define
name|ngx_log_debug4
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|)
end_define

begin_define
DECL|macro|ngx_log_debug5 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5)
define|#
directive|define
name|ngx_log_debug5
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|)
end_define

begin_define
DECL|macro|ngx_log_debug6 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6)
define|#
directive|define
name|ngx_log_debug6
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,
name|arg6
parameter_list|)
end_define

begin_define
DECL|macro|ngx_log_debug7 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
define|#
directive|define
name|ngx_log_debug7
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,    \
name|arg6
parameter_list|,
name|arg7
parameter_list|)
end_define

begin_define
DECL|macro|ngx_log_debug8 (level,log,err,fmt,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8)
define|#
directive|define
name|ngx_log_debug8
parameter_list|(
name|level
parameter_list|,
name|log
parameter_list|,
name|err
parameter_list|,
name|fmt
parameter_list|,
name|arg1
parameter_list|,
name|arg2
parameter_list|,
name|arg3
parameter_list|,
name|arg4
parameter_list|,
name|arg5
parameter_list|,    \
name|arg6
parameter_list|,
name|arg7
parameter_list|,
name|arg8
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*********************************/
end_comment

begin_function_decl
name|ngx_log_t
modifier|*
name|ngx_log_init
parameter_list|(
name|u_char
modifier|*
name|prefix
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_cdecl
name|ngx_log_abort
parameter_list|(
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_cdecl
name|ngx_log_stderr
parameter_list|(
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
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_log_errno
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|,
name|ngx_err_t
name|err
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_log_set_log
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_log_t
modifier|*
modifier|*
name|head
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * ngx_write_stderr() cannot be implemented as macro, since  * MSVC does not allow to use #ifdef inside macro parameters.  *  * ngx_write_fd() is used instead of ngx_write_console(), since  * CharToOemBuff() inside ngx_write_console() cannot be used with  * read only buffer as destination and CharToOemBuff() is not needed  * for ngx_write_stderr() anyway.  */
end_comment

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_write_stderr (char * text)
name|ngx_write_stderr
parameter_list|(
name|char
modifier|*
name|text
parameter_list|)
block|{
operator|(
name|void
operator|)
name|ngx_write_fd
argument_list|(
name|ngx_stderr
argument_list|,
name|text
argument_list|,
name|strlen
argument_list|(
name|text
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_errlog_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_use_stderr
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_LOG_H_INCLUDED_ */
end_comment

end_unit

