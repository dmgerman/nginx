begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_THREAD_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_THREAD_H_INCLUDED_
define|#
directive|define
name|_NGX_THREAD_H_INCLUDED_
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

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_if
if|#
directive|if
operator|(
name|NGX_USE_RFORK
operator|)
end_if

begin_include
include|#
directive|include
file|<sys/ipc.h>
end_include

begin_include
include|#
directive|include
file|<sys/sem.h>
end_include

begin_include
include|#
directive|include
file|<sched.h>
end_include

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|pid_t
name|ngx_tid_t
typedef|;
end_typedef

begin_define
DECL|macro|TID_T_FMT
define|#
directive|define
name|TID_T_FMT
value|PID_T_FMT
end_define

begin_define
DECL|macro|ngx_log_tid
define|#
directive|define
name|ngx_log_tid
value|0
end_define

begin_undef
undef|#
directive|undef
name|ngx_log_pid
end_undef

begin_define
DECL|macro|ngx_log_pid
define|#
directive|define
name|ngx_log_pid
value|ngx_thread_self()
end_define

begin_define
DECL|macro|NGX_MUTEX_LIGHT
define|#
directive|define
name|NGX_MUTEX_LIGHT
value|1
end_define

begin_define
DECL|macro|NGX_MUTEX_CV
define|#
directive|define
name|NGX_MUTEX_CV
value|2
end_define

begin_define
DECL|macro|NGX_MUTEX_LOCK_BUSY
define|#
directive|define
name|NGX_MUTEX_LOCK_BUSY
value|0x80000000
end_define

begin_typedef
DECL|struct|__anon2bff69350108
typedef|typedef
specifier|volatile
struct|struct
block|{
DECL|member|lock
name|ngx_atomic_t
name|lock
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|semid
name|int
name|semid
decl_stmt|;
DECL|typedef|ngx_mutex_t
block|}
name|ngx_mutex_t
typedef|;
end_typedef

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* use pthreads */
end_comment

begin_include
include|#
directive|include
file|<pthread.h>
end_include

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|pthread_t
name|ngx_tid_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_log_tid
define|#
directive|define
name|ngx_log_tid
value|ngx_thread_self()
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|ngx_int_t
name|ngx_init_threads
parameter_list|(
name|int
name|n
parameter_list|,
name|size_t
name|size
parameter_list|,
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_create_thread
parameter_list|(
name|ngx_tid_t
modifier|*
name|tid
parameter_list|,
name|int
function_decl|(
modifier|*
name|func
function_decl|)
parameter_list|(
name|void
modifier|*
name|arg
parameter_list|)
parameter_list|,
name|void
modifier|*
name|arg
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_tid_t
name|ngx_thread_self
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|ngx_mutex_t
modifier|*
name|ngx_mutex_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|uint
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_mutex_done
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_mutex_trylock (m)
define|#
directive|define
name|ngx_mutex_trylock
parameter_list|(
name|m
parameter_list|)
value|ngx_mutex_do_lock(m, 1)
end_define

begin_define
DECL|macro|ngx_mutex_lock (m)
define|#
directive|define
name|ngx_mutex_lock
parameter_list|(
name|m
parameter_list|)
value|ngx_mutex_do_lock(m, 0)
end_define

begin_function_decl
name|ngx_int_t
name|ngx_mutex_do_lock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|,
name|ngx_int_t
name|try
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_mutex_unlock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_int_t
name|ngx_threaded
decl_stmt|;
end_decl_stmt

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !NGX_THREADS */
end_comment

begin_define
DECL|macro|ngx_log_tid
define|#
directive|define
name|ngx_log_tid
value|0
end_define

begin_define
DECL|macro|TID_T_FMT
define|#
directive|define
name|TID_T_FMT
value|"%d"
end_define

begin_define
DECL|macro|ngx_mutex_lock (m)
define|#
directive|define
name|ngx_mutex_lock
parameter_list|(
name|m
parameter_list|)
end_define

begin_define
DECL|macro|ngx_mutex_unlock (m)
define|#
directive|define
name|ngx_mutex_unlock
parameter_list|(
name|m
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_THREAD_H_INCLUDED_ */
end_comment

end_unit

