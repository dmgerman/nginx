begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_FREEBSD_RFORK_THREAD_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_FREEBSD_RFORK_THREAD_H_INCLUDED_
define|#
directive|define
name|_NGX_FREEBSD_RFORK_THREAD_H_INCLUDED_
end_define

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
value|PID_T_FMT
end_define

begin_define
DECL|macro|NGX_MUTEX_LIGHT
define|#
directive|define
name|NGX_MUTEX_LIGHT
value|1
end_define

begin_define
DECL|macro|NGX_MUTEX_LOCK_BUSY
define|#
directive|define
name|NGX_MUTEX_LOCK_BUSY
value|0x80000000
end_define

begin_typedef
DECL|struct|__anon2aac6b0b0108
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

begin_define
DECL|macro|NGX_CV_SIGNAL
define|#
directive|define
name|NGX_CV_SIGNAL
value|64
end_define

begin_typedef
DECL|struct|__anon2aac6b0b0208
typedef|typedef
struct|struct
block|{
DECL|member|signo
name|int
name|signo
decl_stmt|;
DECL|member|kq
name|int
name|kq
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
DECL|macro|ngx_thread_sigmask (how,set,oset)
define|#
directive|define
name|ngx_thread_sigmask
parameter_list|(
name|how
parameter_list|,
name|set
parameter_list|,
name|oset
parameter_list|)
define|\
value|(sigprocmask(how, set, oset) == -1) ? ngx_errno : 0
end_define

begin_define
DECL|macro|ngx_thread_sigmask_n
define|#
directive|define
name|ngx_thread_sigmask_n
value|"sigprocmask()"
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
end_define

begin_define
DECL|macro|ngx_setthrtitle (n)
define|#
directive|define
name|ngx_setthrtitle
parameter_list|(
name|n
parameter_list|)
value|setproctitle(n)
end_define

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|ngx_freebsd_kern_usrstack
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|size_t
name|ngx_thread_stack_size
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_gettid ()
specifier|static
specifier|inline
name|int
name|ngx_gettid
parameter_list|()
block|{
name|char
modifier|*
name|sp
decl_stmt|;
if|if
condition|(
name|ngx_thread_stack_size
operator|==
literal|0
condition|)
block|{
return|return
literal|0
return|;
block|}
if|#
directive|if
operator|(
name|__i386__
operator|)
asm|__asm__
specifier|volatile
asm|("mov %%esp, %0" : "=q" (sp));
elif|#
directive|elif
operator|(
name|__amd64__
operator|)
asm|__asm__
specifier|volatile
asm|("mov %%rsp, %0" : "=q" (sp));
else|#
directive|else
error|#
directive|error
literal|"rfork()ed threads are not supported on this platform"
endif|#
directive|endif
return|return
operator|(
name|ngx_freebsd_kern_usrstack
operator|-
name|sp
operator|)
operator|/
name|ngx_thread_stack_size
return|;
block|}
end_function

begin_function_decl
name|ngx_tid_t
name|ngx_thread_self
parameter_list|()
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_thread_main ()
define|#
directive|define
name|ngx_thread_main
parameter_list|()
value|(ngx_gettid() == 0)
end_define

begin_define
DECL|macro|ngx_mutex_trylock (m)
define|#
directive|define
name|ngx_mutex_trylock
parameter_list|(
name|m
parameter_list|)
value|ngx_mutex_dolock(m, 1)
end_define

begin_define
DECL|macro|ngx_mutex_lock (m)
define|#
directive|define
name|ngx_mutex_lock
parameter_list|(
name|m
parameter_list|)
value|ngx_mutex_dolock(m, 0)
end_define

begin_function_decl
name|ngx_int_t
name|ngx_mutex_dolock
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

begin_typedef
DECL|typedef|ngx_rfork_thread_func_pt
typedef|typedef
name|int
function_decl|(
modifier|*
name|ngx_rfork_thread_func_pt
function_decl|)
parameter_list|(
name|void
modifier|*
name|arg
parameter_list|)
function_decl|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_FREEBSD_RFORK_THREAD_H_INCLUDED_ */
end_comment

end_unit

