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

begin_define
DECL|macro|NGX_MAX_THREADS
define|#
directive|define
name|NGX_MAX_THREADS
value|128
end_define

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
file|<ngx_freebsd_rfork_thread.h>
end_include

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

begin_include
include|#
directive|include
file|<pthread_np.h>
end_include

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|pthread_t
name|ngx_tid_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_thread_self ()
define|#
directive|define
name|ngx_thread_self
parameter_list|()
value|pthread_self()
end_define

begin_define
DECL|macro|ngx_log_tid
define|#
directive|define
name|ngx_log_tid
value|(int) ngx_thread_self()
end_define

begin_define
DECL|macro|TID_T_FMT
define|#
directive|define
name|TID_T_FMT
value|PTR_FMT
end_define

begin_define
DECL|macro|ngx_thread_create_tls ()
define|#
directive|define
name|ngx_thread_create_tls
parameter_list|()
value|pthread_key_create(0, NULL)
end_define

begin_define
DECL|macro|ngx_thread_create_tls_n
define|#
directive|define
name|ngx_thread_create_tls_n
value|"pthread_key_create(0, NULL)"
end_define

begin_define
DECL|macro|ngx_thread_get_tls ()
define|#
directive|define
name|ngx_thread_get_tls
parameter_list|()
value|pthread_getspecific(0)
end_define

begin_define
DECL|macro|ngx_thread_set_tls (v)
define|#
directive|define
name|ngx_thread_set_tls
parameter_list|(
name|v
parameter_list|)
value|pthread_setspecific(0, v)
end_define

begin_define
DECL|macro|NGX_MUTEX_LIGHT
define|#
directive|define
name|NGX_MUTEX_LIGHT
value|0
end_define

begin_typedef
DECL|struct|__anon2c8f79680108
typedef|typedef
struct|struct
block|{
DECL|member|mutex
name|pthread_mutex_t
name|mutex
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_mutex_t
block|}
name|ngx_mutex_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c8f79680208
typedef|typedef
struct|struct
block|{
DECL|member|cond
name|pthread_cond_t
name|cond
decl_stmt|;
DECL|member|tid
name|ngx_tid_t
name|tid
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_cond_t
block|}
name|ngx_cond_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_thread_sigmask
define|#
directive|define
name|ngx_thread_sigmask
value|pthread_sigmask
end_define

begin_define
DECL|macro|ngx_thread_sigmask_n
define|#
directive|define
name|ngx_thread_sigmask_n
value|"pthread_sigmask()"
end_define

begin_define
DECL|macro|ngx_thread_join (t,p)
define|#
directive|define
name|ngx_thread_join
parameter_list|(
name|t
parameter_list|,
name|p
parameter_list|)
value|pthread_join(t, p)
end_define

begin_define
DECL|macro|ngx_setthrtitle (n)
define|#
directive|define
name|ngx_setthrtitle
parameter_list|(
name|n
parameter_list|)
end_define

begin_function_decl
name|ngx_int_t
name|ngx_mutex_trylock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_mutex_lock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
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

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_thread_volatile
define|#
directive|define
name|ngx_thread_volatile
value|volatile
end_define

begin_typedef
DECL|struct|__anon2c8f79680308
typedef|typedef
struct|struct
block|{
DECL|member|tid
name|ngx_tid_t
name|tid
decl_stmt|;
DECL|member|cv
name|ngx_cond_t
modifier|*
name|cv
decl_stmt|;
DECL|member|state
name|ngx_uint_t
name|state
decl_stmt|;
DECL|typedef|ngx_thread_t
block|}
name|ngx_thread_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_THREAD_FREE
define|#
directive|define
name|NGX_THREAD_FREE
value|1
end_define

begin_define
DECL|macro|NGX_THREAD_BUSY
define|#
directive|define
name|NGX_THREAD_BUSY
value|2
end_define

begin_define
DECL|macro|NGX_THREAD_EXIT
define|#
directive|define
name|NGX_THREAD_EXIT
value|3
end_define

begin_define
DECL|macro|NGX_THREAD_DONE
define|#
directive|define
name|NGX_THREAD_DONE
value|4
end_define

begin_decl_stmt
specifier|extern
name|ngx_int_t
name|ngx_threads_n
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|volatile
name|ngx_thread_t
name|ngx_threads
index|[
name|NGX_MAX_THREADS
index|]
decl_stmt|;
end_decl_stmt

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
name|void
modifier|*
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
name|ngx_mutex_destroy
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_cond_t
modifier|*
name|ngx_cond_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_cond_destroy
parameter_list|(
name|ngx_cond_t
modifier|*
name|cv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_cond_wait
parameter_list|(
name|ngx_cond_t
modifier|*
name|cv
parameter_list|,
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_cond_signal
parameter_list|(
name|ngx_cond_t
modifier|*
name|cv
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !NGX_THREADS */
end_comment

begin_define
DECL|macro|ngx_thread_volatile
define|#
directive|define
name|ngx_thread_volatile
end_define

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
value|NGX_OK
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

begin_define
DECL|macro|ngx_cond_signal (cv)
define|#
directive|define
name|ngx_cond_signal
parameter_list|(
name|cv
parameter_list|)
end_define

begin_define
DECL|macro|ngx_thread_main ()
define|#
directive|define
name|ngx_thread_main
parameter_list|()
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon2c8f79680408
typedef|typedef
struct|struct
block|{
DECL|member|event
name|ngx_event_t
modifier|*
name|event
decl_stmt|;
DECL|typedef|ngx_tls_t
block|}
name|ngx_tls_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_THREAD_H_INCLUDED_ */
end_comment

end_unit

