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
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_core.h>
end_include

begin_typedef
DECL|enum|__anon2a9e25b60103
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_LOG_STDERR
name|NGX_LOG_STDERR
init|=
literal|0
block|,
DECL|enumerator|NGX_LOG_EMERG
name|NGX_LOG_EMERG
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
comment|/*     "[%time] [%level] %pid#%tid: %message:(%errno)%errstr, while %action"         " %peer and while processing %context"      ----     message = "recv() failed";     errno = 32;     action = "reading request headers from client";     peer = "192.168.1.1";     context = "URL /"      "[2002/08/20 12:00:00] [error] 412#3: recv() failed (32: Broken pipe)"     " while reading request headers from client 192.168.1.1"     " and while processing URL /"      ----     message = "recv() failed";     errno = 32;     ngx_http_proxy_error_context_t:         action = "reading headers from server %s for client %s and "                  "while processing %s"         backend = "127.0.0.1";         peer = "192.168.1.1";         context = "URL /"      "[2002/08/20 12:00:00] [error] 412#3: recv() failed (32: Broken pipe)"     " while reading headers from backend 127.0.0.1"     " for client 192.168.1.1 and while processing URL /"      ----     "[alert] 412#3: ngx_alloc: malloc() 102400 bytes failed (12: Cannot "     "allocate memory) while reading request headers from client 192.168.1.1"     " and while processing URL /"       OLD:     "... while ", action = "reading client request headers"     "... while reading client request headers"     "... while ", action = "reading client request headers"                   context: pop3 user account     "... while reading client command for 'john_doe'" */
end_comment

begin_typedef
DECL|typedef|ngx_log_handler_pt
typedef|typedef
name|size_t
function_decl|(
modifier|*
name|ngx_log_handler_pt
function_decl|)
parameter_list|(
name|void
modifier|*
name|ctx
parameter_list|,
name|char
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
name|int
name|log_level
decl_stmt|;
DECL|member|file
name|ngx_open_file_t
modifier|*
name|file
decl_stmt|;
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|handler
name|ngx_log_handler_pt
name|handler
decl_stmt|;
if|#
directive|if
literal|0
comment|/* STUB */
block|char     *action;     char     *context;
comment|/* */
endif|#
directive|endif
block|}
struct|;
end_struct

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

begin_if
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
end_if

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

begin_if
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
end_if

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

begin_if
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
end_if

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

begin_define
DECL|macro|ngx_log_alloc_log (pool,log)
define|#
directive|define
name|ngx_log_alloc_log
parameter_list|(
name|pool
parameter_list|,
name|log
parameter_list|)
value|ngx_palloc(pool, log, sizeof(ngx_log_t))
end_define

begin_define
DECL|macro|ngx_log_copy_log (new,old)
define|#
directive|define
name|ngx_log_copy_log
parameter_list|(
name|new
parameter_list|,
name|old
parameter_list|)
value|ngx_memcpy(new, old, sizeof(ngx_log_t))
end_define

begin_function_decl
name|ngx_log_t
modifier|*
name|ngx_log_init_errlog
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|ngx_log_t
modifier|*
name|ngx_log_create_errlog
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_errlog_module
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

