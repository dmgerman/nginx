begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
file|<ngx_errno.h>
end_include

begin_typedef
DECL|enum|__anon275655d50103
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_LOG_EMERG
name|NGX_LOG_EMERG
init|=
literal|0
block|,
DECL|enumerator|NGX_LOG_ALERT
name|NGX_LOG_ALERT
block|,
DECL|enumerator|NGX_LOG_CRIT
name|NGX_LOG_CRIT
block|,
DECL|enumerator|NGX_LOG_ERR
name|NGX_LOG_ERR
block|,
DECL|enumerator|NGX_LOG_WARN
name|NGX_LOG_WARN
block|,
DECL|enumerator|NGX_LOG_NOTICE
name|NGX_LOG_NOTICE
block|,
DECL|enumerator|NGX_LOG_INFO
name|NGX_LOG_INFO
block|,
DECL|enumerator|NGX_LOG_DEBUG
name|NGX_LOG_DEBUG
DECL|typedef|ngx_log_e
block|}
name|ngx_log_e
typedef|;
end_typedef

begin_comment
comment|/*     "[%time] [%level] %pid#%tid: %message:(%errno)%errstr, while %action"         " %peer and processing %context"      message = "recv() failed";     errno = 32;     action = "reading request headers from client";     peer = "192.168.1.1";     context = "URL /"      "[2002/08/20 12:00:00] [error] 412#3: recv() failed:(32)Broken pipe,"     " while reading request headers from client 192.168.1.1"     " and processing URL /"       OLD:     "... while ", action = "reading client request headers"     "... while reading client request headers"     "... while ", action = "reading client request headers"                   context: pop3 user account     "... while reading client command for 'john_doe'" */
end_comment

begin_typedef
DECL|struct|__anon275655d50208
typedef|typedef
struct|struct
block|{
DECL|member|log_level
name|int
name|log_level
decl_stmt|;
DECL|member|action
name|char
modifier|*
name|action
decl_stmt|;
DECL|member|context
name|char
modifier|*
name|context
decl_stmt|;
comment|/*  char  *func(ngx_log_t *log); */
DECL|typedef|ngx_log_t
block|}
name|ngx_log_t
typedef|;
end_typedef

begin_define
DECL|macro|MAX_ERROR_STR
define|#
directive|define
name|MAX_ERROR_STR
value|2048
end_define

begin_define
DECL|macro|_
define|#
directive|define
name|_
value|,
end_define

begin_if
if|#
directive|if
operator|(
name|HAVE_GCC_VARIADIC_MACROS
operator|)
end_if

begin_define
DECL|macro|HAVE_VARIADIC_MACROS
define|#
directive|define
name|HAVE_VARIADIC_MACROS
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
value|if (log->log_level>= level) ngx_log_error_core(level, log, args)
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|NGX_DEBUG
end_ifdef

begin_define
DECL|macro|ngx_log_debug (log,args...)
define|#
directive|define
name|ngx_log_debug
parameter_list|(
name|log
parameter_list|,
name|args
modifier|...
parameter_list|)
define|\
value|if (log->log_level == NGX_LOG_DEBUG) \         ngx_log_error_core(NGX_LOG_DEBUG, log, 0, args)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_log_debug (log,args...)
define|#
directive|define
name|ngx_log_debug
parameter_list|(
name|log
parameter_list|,
name|args
modifier|...
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_assert (assert,fallback,log,args...)
define|#
directive|define
name|ngx_assert
parameter_list|(
name|assert
parameter_list|,
name|fallback
parameter_list|,
name|log
parameter_list|,
name|args
modifier|...
parameter_list|)
define|\
value|if (!(assert)) { \             if (log->log_level>= NGX_LOG_ALERT) \                 ngx_log_error_core(NGX_LOG_ALERT, log, 0, args); \             fallback; \         }
end_define

begin_function_decl
name|void
name|ngx_log_error_core
parameter_list|(
name|int
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

begin_elif
elif|#
directive|elif
operator|(
name|HAVE_C99_VARIADIC_MACROS
operator|)
end_elif

begin_define
DECL|macro|HAVE_VARIADIC_MACROS
define|#
directive|define
name|HAVE_VARIADIC_MACROS
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
value|if (log->log_level>= level) ngx_log_error_core(level, log, __VA_ARGS__)
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|NGX_DEBUG
end_ifdef

begin_define
DECL|macro|ngx_log_debug (log,...)
define|#
directive|define
name|ngx_log_debug
parameter_list|(
name|log
parameter_list|,
modifier|...
parameter_list|)
define|\
value|if (log->log_level == NGX_LOG_DEBUG) \         ngx_log_error_core(NGX_LOG_DEBUG, log, 0, __VA_ARGS__)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_log_debug (log,...)
define|#
directive|define
name|ngx_log_debug
parameter_list|(
name|log
parameter_list|,
modifier|...
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_assert (assert,fallback,log,...)
define|#
directive|define
name|ngx_assert
parameter_list|(
name|assert
parameter_list|,
name|fallback
parameter_list|,
name|log
parameter_list|,
modifier|...
parameter_list|)
define|\
value|if (!(assert)) { \             if (log->log_level>= NGX_LOG_ALERT) \                 ngx_log_error_core(NGX_LOG_ALERT, log, 0, __VA_ARGS__); \             fallback; \         }
end_define

begin_function_decl
name|void
name|ngx_log_error_core
parameter_list|(
name|int
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

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* NO VARIADIC MACROS */
end_comment

begin_include
include|#
directive|include
file|<stdarg.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|NGX_DEBUG
end_ifdef

begin_define
DECL|macro|ngx_log_debug (log,text)
define|#
directive|define
name|ngx_log_debug
parameter_list|(
name|log
parameter_list|,
name|text
parameter_list|)
define|\
value|if (log->log_level == NGX_LOG_DEBUG) \         ngx_log_debug_core(log, text)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_log_debug (log,text)
define|#
directive|define
name|ngx_log_debug
parameter_list|(
name|log
parameter_list|,
name|text
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_assert (assert,fallback,log,text)
define|#
directive|define
name|ngx_assert
parameter_list|(
name|assert
parameter_list|,
name|fallback
parameter_list|,
name|log
parameter_list|,
name|text
parameter_list|)
define|\
value|if (!(assert)) { \             if (log->log_level>= NGX_LOG_ALERT) \                 ngx_assert_core(log, text); \             fallback; \         }
end_define

begin_function_decl
name|void
name|ngx_log_error
parameter_list|(
name|int
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
name|int
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
name|ngx_log_debug_core
parameter_list|(
name|ngx_log_t
modifier|*
name|log
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
name|ngx_assert_core
parameter_list|(
name|ngx_log_t
modifier|*
name|log
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_LOG_H_INCLUDED_ */
end_comment

end_unit

