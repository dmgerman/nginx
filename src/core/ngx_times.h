begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_TIMES_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_TIMES_H_INCLUDED_
define|#
directive|define
name|_NGX_TIMES_H_INCLUDED_
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

begin_function_decl
name|void
name|ngx_time_init
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_time_update
parameter_list|(
name|time_t
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_time
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|time_t
name|t
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_cookie_time
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|time_t
name|t
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_gmtime
parameter_list|(
name|time_t
name|t
parameter_list|,
name|ngx_tm_t
modifier|*
name|tp
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_function_decl
name|ngx_int_t
name|ngx_time_mutex_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|&&
operator|(
name|TIME_T_SIZE
operator|>
name|SIG_ATOMIC_T_SIZE
operator|)
operator|)
end_if

begin_define
DECL|macro|ngx_time ()
define|#
directive|define
name|ngx_time
parameter_list|()
value|*ngx_cached_time
end_define

begin_decl_stmt
specifier|extern
specifier|volatile
name|time_t
modifier|*
name|ngx_cached_time
decl_stmt|;
end_decl_stmt

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_time ()
define|#
directive|define
name|ngx_time
parameter_list|()
value|ngx_cached_time
end_define

begin_decl_stmt
specifier|extern
specifier|volatile
name|time_t
name|ngx_cached_time
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|ngx_thread_volatile
name|ngx_str_t
name|ngx_cached_err_log_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_thread_volatile
name|ngx_str_t
name|ngx_cached_http_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_thread_volatile
name|ngx_str_t
name|ngx_cached_http_log_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_epoch_msec_t
name|ngx_start_msec
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * msecs elapsed since ngx_start_msec in the current event cycle,  * used in ngx_event_add_timer() and ngx_event_find_timer()  */
end_comment

begin_decl_stmt
specifier|extern
name|ngx_epoch_msec_t
name|ngx_elapsed_msec
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * msecs elapsed since ngx_start_msec in the previous event cycle,  * used in ngx_event_expire_timers()  */
end_comment

begin_decl_stmt
specifier|extern
name|ngx_epoch_msec_t
name|ngx_old_elapsed_msec
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_TIMES_H_INCLUDED_ */
end_comment

end_unit

