begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev, http://sysoev.ru/en/  */
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
file|<ngx_event.h>
end_include

begin_if
if|#
directive|if
operator|(
name|TEST_BUILD_RTSIG
operator|)
end_if

begin_define
DECL|macro|F_SETSIG
define|#
directive|define
name|F_SETSIG
value|10
end_define

begin_define
DECL|macro|SIGRTMIN
define|#
directive|define
name|SIGRTMIN
value|33
end_define

begin_define
DECL|macro|si_fd
define|#
directive|define
name|si_fd
value|__spare__[0]
end_define

begin_define
DECL|macro|KERN_RTSIGNR
define|#
directive|define
name|KERN_RTSIGNR
value|30
end_define

begin_define
DECL|macro|KERN_RTSIGMAX
define|#
directive|define
name|KERN_RTSIGMAX
value|31
end_define

begin_function
DECL|function|sigtimedwait (const sigset_t * set,siginfo_t * info,const struct timespec * timeout)
name|int
name|sigtimedwait
parameter_list|(
specifier|const
name|sigset_t
modifier|*
name|set
parameter_list|,
name|siginfo_t
modifier|*
name|info
parameter_list|,
specifier|const
name|struct
name|timespec
modifier|*
name|timeout
parameter_list|)
block|{
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon28c38ba90108
typedef|typedef
struct|struct
block|{
DECL|member|signo
name|int
name|signo
decl_stmt|;
DECL|typedef|ngx_rtsig_conf_t
block|}
name|ngx_rtsig_conf_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_event_module_t
name|ngx_poll_module_ctx
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_rtsig_init
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
name|ngx_rtsig_done
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_rtsig_add_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_rtsig_del_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_rtsig_process_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_rtsig_process_overflow
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
name|ngx_rtsig_create_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_rtsig_init_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|set
specifier|static
name|sigset_t
name|set
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|overflow
DECL|variable|current
specifier|static
name|ngx_uint_t
name|overflow
decl_stmt|,
name|current
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rtsig_name
specifier|static
name|ngx_str_t
name|rtsig_name
init|=
name|ngx_string
argument_list|(
literal|"rtsig"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_rtsig_commands
specifier|static
name|ngx_command_t
name|ngx_rtsig_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"rtsig_signo"
argument_list|)
block|,
name|NGX_EVENT_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_num_slot
block|,
literal|0
block|,
name|offsetof
argument_list|(
name|ngx_rtsig_conf_t
argument_list|,
name|signo
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
DECL|variable|ngx_rtsig_module_ctx
name|ngx_event_module_t
name|ngx_rtsig_module_ctx
init|=
block|{
operator|&
name|rtsig_name
block|,
name|ngx_rtsig_create_conf
block|,
comment|/* create configuration */
name|ngx_rtsig_init_conf
block|,
comment|/* init configuration */
block|{
name|NULL
block|,
comment|/* add an event */
name|NULL
block|,
comment|/* delete an event */
name|NULL
block|,
comment|/* enable an event */
name|NULL
block|,
comment|/* disable an event */
name|ngx_rtsig_add_connection
block|,
comment|/* add an connection */
name|ngx_rtsig_del_connection
block|,
comment|/* delete an connection */
name|ngx_rtsig_process_events
block|,
comment|/* process the events */
name|ngx_rtsig_init
block|,
comment|/* init the events */
name|ngx_rtsig_done
block|,
comment|/* done the events */
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_rtsig_module
name|ngx_module_t
name|ngx_rtsig_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_rtsig_module_ctx
block|,
comment|/* module context */
name|ngx_rtsig_commands
block|,
comment|/* module directives */
name|NGX_EVENT_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init module */
name|NULL
comment|/* init child */
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_rtsig_init (ngx_cycle_t * cycle)
specifier|static
name|ngx_int_t
name|ngx_rtsig_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_rtsig_conf_t
modifier|*
name|rtscf
decl_stmt|;
if|if
condition|(
name|ngx_poll_module_ctx
operator|.
name|actions
operator|.
name|init
argument_list|(
name|cycle
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|rtscf
operator|=
name|ngx_event_get_conf
argument_list|(
name|cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_rtsig_module
argument_list|)
expr_stmt|;
name|sigemptyset
argument_list|(
operator|&
name|set
argument_list|)
expr_stmt|;
name|sigaddset
argument_list|(
operator|&
name|set
argument_list|,
name|rtscf
operator|->
name|signo
argument_list|)
expr_stmt|;
name|sigaddset
argument_list|(
operator|&
name|set
argument_list|,
name|rtscf
operator|->
name|signo
operator|+
literal|1
argument_list|)
expr_stmt|;
name|sigaddset
argument_list|(
operator|&
name|set
argument_list|,
name|SIGIO
argument_list|)
expr_stmt|;
if|if
condition|(
name|sigprocmask
argument_list|(
name|SIG_BLOCK
argument_list|,
operator|&
name|set
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"sigprocmask() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_io
operator|=
name|ngx_os_io
expr_stmt|;
name|ngx_event_actions
operator|=
name|ngx_rtsig_module_ctx
operator|.
name|actions
expr_stmt|;
name|ngx_event_flags
operator|=
name|NGX_USE_RTSIG_EVENT
operator||
name|NGX_HAVE_GREEDY_EVENT
operator||
name|NGX_HAVE_INSTANCE_EVENT
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_rtsig_done (ngx_cycle_t * cycle)
specifier|static
name|void
name|ngx_rtsig_done
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_poll_module_ctx
operator|.
name|actions
operator|.
name|done
argument_list|(
name|cycle
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_rtsig_add_connection (ngx_connection_t * c)
specifier|static
name|ngx_int_t
name|ngx_rtsig_add_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
name|int
name|signo
decl_stmt|;
name|ngx_rtsig_conf_t
modifier|*
name|rtscf
decl_stmt|;
if|if
condition|(
name|c
operator|->
name|read
operator|->
name|accept
operator|&&
name|c
operator|->
name|read
operator|->
name|disabled
condition|)
block|{
if|if
condition|(
name|fcntl
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|F_SETOWN
argument_list|,
name|ngx_pid
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(F_SETOWN) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|c
operator|->
name|read
operator|->
name|active
operator|=
literal|1
expr_stmt|;
name|c
operator|->
name|read
operator|->
name|disabled
operator|=
literal|0
expr_stmt|;
block|}
name|rtscf
operator|=
name|ngx_event_get_conf
argument_list|(
name|ngx_cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_rtsig_module
argument_list|)
expr_stmt|;
name|signo
operator|=
name|rtscf
operator|->
name|signo
operator|+
name|c
operator|->
name|read
operator|->
name|instance
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rtsig add connection: fd:%d signo:%d"
argument_list|,
name|c
operator|->
name|fd
argument_list|,
name|signo
argument_list|)
expr_stmt|;
if|if
condition|(
name|fcntl
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|F_SETFL
argument_list|,
name|O_RDWR
operator||
name|O_NONBLOCK
operator||
name|O_ASYNC
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(O_RDWR|O_NONBLOCK|O_ASYNC) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|fcntl
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|F_SETSIG
argument_list|,
name|signo
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(F_SETSIG) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|fcntl
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|F_SETOWN
argument_list|,
name|ngx_pid
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(F_SETOWN) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|#
directive|if
operator|(
name|HAVE_ONESIGFD
operator|)
if|if
condition|(
name|fcntl
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|F_SETAUXFL
argument_list|,
name|O_ONESIGFD
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(F_SETAUXFL) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
name|c
operator|->
name|read
operator|->
name|active
operator|=
literal|1
expr_stmt|;
name|c
operator|->
name|write
operator|->
name|active
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_rtsig_del_connection (ngx_connection_t * c,u_int flags)
specifier|static
name|ngx_int_t
name|ngx_rtsig_del_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_int
name|flags
parameter_list|)
block|{
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rtsig del connection: fd:%d"
argument_list|,
name|c
operator|->
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|flags
operator|&
name|NGX_DISABLE_EVENT
operator|)
operator|&&
name|c
operator|->
name|read
operator|->
name|accept
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|active
operator|=
literal|0
expr_stmt|;
name|c
operator|->
name|read
operator|->
name|disabled
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|flags
operator|&
name|NGX_CLOSE_EVENT
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|active
operator|=
literal|0
expr_stmt|;
name|c
operator|->
name|write
operator|->
name|active
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|fcntl
argument_list|(
name|c
operator|->
name|fd
argument_list|,
name|F_SETFL
argument_list|,
name|O_RDWR
operator||
name|O_NONBLOCK
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|c
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"fcntl(O_RDWR|O_NONBLOCK) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|c
operator|->
name|read
operator|->
name|active
operator|=
literal|0
expr_stmt|;
name|c
operator|->
name|write
operator|->
name|active
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_rtsig_process_events (ngx_cycle_t * cycle)
name|ngx_int_t
name|ngx_rtsig_process_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|int
name|signo
decl_stmt|;
name|ngx_int_t
name|instance
decl_stmt|,
name|i
decl_stmt|;
name|ngx_uint_t
name|expire
decl_stmt|;
name|size_t
name|n
decl_stmt|;
name|ngx_msec_t
name|timer
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|siginfo_t
name|si
decl_stmt|;
name|struct
name|timeval
name|tv
decl_stmt|;
name|struct
name|timespec
name|ts
decl_stmt|,
modifier|*
name|tp
decl_stmt|;
name|struct
name|sigaction
name|sa
decl_stmt|;
name|ngx_epoch_msec_t
name|delta
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_rtsig_conf_t
modifier|*
name|rtscf
decl_stmt|;
if|if
condition|(
name|overflow
condition|)
block|{
name|timer
operator|=
literal|0
expr_stmt|;
name|expire
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
init|;
condition|;
control|)
block|{
name|timer
operator|=
name|ngx_event_find_timer
argument_list|()
expr_stmt|;
if|if
condition|(
name|timer
operator|!=
literal|0
condition|)
block|{
break|break;
block|}
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rtsig expired timer"
argument_list|)
expr_stmt|;
name|ngx_event_expire_timers
argument_list|(
operator|(
name|ngx_msec_t
operator|)
operator|(
name|ngx_elapsed_msec
operator|-
name|ngx_old_elapsed_msec
operator|)
argument_list|)
expr_stmt|;
block|}
name|expire
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|ngx_accept_mutex
condition|)
block|{
if|if
condition|(
name|ngx_accept_disabled
operator|>
literal|0
condition|)
block|{
name|ngx_accept_disabled
operator|--
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|ngx_trylock_accept_mutex
argument_list|(
name|cycle
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|ngx_accept_mutex_held
operator|==
literal|0
operator|&&
operator|(
name|timer
operator|==
name|NGX_TIMER_INFINITE
operator|||
name|timer
operator|>
name|ngx_accept_mutex_delay
operator|)
condition|)
block|{
name|timer
operator|=
name|ngx_accept_mutex_delay
expr_stmt|;
name|expire
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
block|}
if|if
condition|(
name|timer
operator|==
name|NGX_TIMER_INFINITE
condition|)
block|{
name|tp
operator|=
name|NULL
expr_stmt|;
name|expire
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|ts
operator|.
name|tv_sec
operator|=
name|timer
operator|/
literal|1000
expr_stmt|;
name|ts
operator|.
name|tv_nsec
operator|=
operator|(
name|timer
operator|%
literal|1000
operator|)
operator|*
literal|1000000
expr_stmt|;
name|tp
operator|=
operator|&
name|ts
expr_stmt|;
block|}
name|ngx_old_elapsed_msec
operator|=
name|ngx_elapsed_msec
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rtsig timer: %d"
argument_list|,
name|timer
argument_list|)
expr_stmt|;
comment|/* Linux sigwaitinfo() is sigtimedwait() with the NULL timeout pointer */
name|signo
operator|=
name|sigtimedwait
argument_list|(
operator|&
name|set
argument_list|,
operator|&
name|si
argument_list|,
name|tp
argument_list|)
expr_stmt|;
if|if
condition|(
name|signo
operator|==
operator|-
literal|1
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
name|NGX_EAGAIN
condition|)
block|{
if|if
condition|(
name|timer
operator|==
name|NGX_TIMER_INFINITE
condition|)
block|{
name|ngx_accept_mutex_unlock
argument_list|()
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"sigtimedwait() returned EAGAIN without timeout"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|err
operator|=
literal|0
expr_stmt|;
block|}
block|}
else|else
block|{
name|err
operator|=
literal|0
expr_stmt|;
block|}
name|ngx_gettimeofday
argument_list|(
operator|&
name|tv
argument_list|)
expr_stmt|;
name|ngx_time_update
argument_list|(
name|tv
operator|.
name|tv_sec
argument_list|)
expr_stmt|;
name|delta
operator|=
name|ngx_elapsed_msec
expr_stmt|;
name|ngx_elapsed_msec
operator|=
name|tv
operator|.
name|tv_sec
operator|*
literal|1000
operator|+
name|tv
operator|.
name|tv_usec
operator|/
literal|1000
operator|-
name|ngx_start_msec
expr_stmt|;
if|if
condition|(
name|err
condition|)
block|{
name|ngx_accept_mutex_unlock
argument_list|()
expr_stmt|;
name|ngx_log_error
argument_list|(
operator|(
name|err
operator|==
name|NGX_EINTR
operator|)
condition|?
name|NGX_LOG_INFO
else|:
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"sigtimedwait() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|timer
operator|!=
name|NGX_TIMER_INFINITE
condition|)
block|{
name|delta
operator|=
name|ngx_elapsed_msec
operator|-
name|delta
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rtsig timer: %d, delta: %d"
argument_list|,
name|timer
argument_list|,
operator|(
name|int
operator|)
name|delta
argument_list|)
expr_stmt|;
block|}
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rtsig signo:%d fd:%d band:%X"
argument_list|,
name|signo
argument_list|,
name|si
operator|.
name|si_fd
argument_list|,
name|si
operator|.
name|si_band
argument_list|)
expr_stmt|;
name|rtscf
operator|=
name|ngx_event_get_conf
argument_list|(
name|ngx_cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_rtsig_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|signo
operator|==
name|rtscf
operator|->
name|signo
operator|||
name|signo
operator|==
name|rtscf
operator|->
name|signo
operator|+
literal|1
condition|)
block|{
if|if
condition|(
name|overflow
operator|&&
operator|(
name|ngx_uint_t
operator|)
name|si
operator|.
name|si_fd
operator|>
name|current
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
comment|/* TODO: old_cycles */
name|c
operator|=
operator|&
name|ngx_cycle
operator|->
name|connections
index|[
name|si
operator|.
name|si_fd
index|]
expr_stmt|;
name|instance
operator|=
name|signo
operator|-
name|rtscf
operator|->
name|signo
expr_stmt|;
if|if
condition|(
name|si
operator|.
name|si_band
operator|&
name|POLLIN
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|returned_instance
operator|=
name|instance
expr_stmt|;
block|}
if|if
condition|(
name|si
operator|.
name|si_band
operator|&
name|POLLOUT
condition|)
block|{
name|c
operator|->
name|write
operator|->
name|returned_instance
operator|=
name|instance
expr_stmt|;
block|}
if|if
condition|(
name|c
operator|->
name|read
operator|->
name|instance
operator|!=
name|instance
condition|)
block|{
comment|/*              * the stale event from a file descriptor              * that was just closed in this iteration              */
name|ngx_accept_mutex_unlock
argument_list|()
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rtsig: stale event "
name|PTR_FMT
argument_list|,
name|c
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|si
operator|.
name|si_band
operator|&
operator|(
name|POLLIN
operator||
name|POLLHUP
operator||
name|POLLERR
operator|)
condition|)
block|{
if|if
condition|(
name|c
operator|->
name|read
operator|->
name|active
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|ngx_threaded
operator|&&
operator|!
name|ngx_accept_mutex_held
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|event_handler
argument_list|(
name|c
operator|->
name|read
argument_list|)
expr_stmt|;
block|}
if|else if
condition|(
name|c
operator|->
name|read
operator|->
name|accept
condition|)
block|{
if|if
condition|(
name|ngx_accept_disabled
operator|<=
literal|0
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|event_handler
argument_list|(
name|c
operator|->
name|read
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|ngx_mutex_lock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_accept_mutex_unlock
argument_list|()
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_post_event
argument_list|(
name|c
operator|->
name|read
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|si
operator|.
name|si_band
operator|&
operator|(
name|POLLOUT
operator||
name|POLLHUP
operator||
name|POLLERR
operator|)
condition|)
block|{
if|if
condition|(
name|c
operator|->
name|write
operator|->
name|active
condition|)
block|{
name|c
operator|->
name|write
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|ngx_threaded
operator|&&
operator|!
name|ngx_accept_mutex_held
condition|)
block|{
name|c
operator|->
name|write
operator|->
name|event_handler
argument_list|(
name|c
operator|->
name|write
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|ngx_mutex_lock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_accept_mutex_unlock
argument_list|()
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_post_event
argument_list|(
name|c
operator|->
name|write
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
expr_stmt|;
block|}
block|}
block|}
block|}
if|else if
condition|(
name|signo
operator|==
name|SIGIO
condition|)
block|{
name|ngx_accept_mutex_unlock
argument_list|()
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rt signal queue overflowed"
argument_list|)
expr_stmt|;
comment|/* flush the RT signal queue */
name|ngx_memzero
argument_list|(
operator|&
name|sa
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|sigaction
argument_list|)
argument_list|)
expr_stmt|;
name|sa
operator|.
name|sa_handler
operator|=
name|SIG_DFL
expr_stmt|;
name|sigemptyset
argument_list|(
operator|&
name|sa
operator|.
name|sa_mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|sigaction
argument_list|(
name|rtscf
operator|->
name|signo
argument_list|,
operator|&
name|sa
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"sigaction(%d, SIG_DFL) failed"
argument_list|,
name|rtscf
operator|->
name|signo
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|sigaction
argument_list|(
name|rtscf
operator|->
name|signo
operator|+
literal|1
argument_list|,
operator|&
name|sa
argument_list|,
name|NULL
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"sigaction(%d, SIG_DFL) failed"
argument_list|,
name|rtscf
operator|->
name|signo
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
name|overflow
operator|=
literal|1
expr_stmt|;
name|current
operator|=
literal|0
expr_stmt|;
name|ngx_event_actions
operator|.
name|process
operator|=
name|ngx_rtsig_process_overflow
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|else if
condition|(
name|signo
operator|!=
operator|-
literal|1
condition|)
block|{
name|ngx_accept_mutex_unlock
argument_list|()
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"sigtimedwait() returned unexpected signal: %d"
argument_list|,
name|signo
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_accept_mutex_unlock
argument_list|()
expr_stmt|;
if|if
condition|(
name|expire
operator|&&
name|delta
condition|)
block|{
name|ngx_event_expire_timers
argument_list|(
operator|(
name|ngx_msec_t
operator|)
name|delta
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|ngx_threaded
condition|)
block|{
name|ngx_event_process_posted
argument_list|(
name|cycle
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|signo
operator|==
operator|-
literal|1
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
else|else
block|{
return|return
name|NGX_OK
return|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_rtsig_process_overflow (ngx_cycle_t * cycle)
specifier|static
name|ngx_int_t
name|ngx_rtsig_process_overflow
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|int
name|name
index|[
literal|2
index|]
decl_stmt|,
name|len
decl_stmt|,
name|rtsig_max
decl_stmt|,
name|rtsig_nr
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
comment|/* TODO: old cylces */
name|n
operator|=
literal|0
expr_stmt|;
name|c
operator|=
name|cycle
operator|->
name|connections
expr_stmt|;
for|for
control|(
name|current
operator|=
literal|0
init|;
name|current
operator|<
name|cycle
operator|->
name|connection_n
condition|;
name|current
operator|++
control|)
block|{
name|i
operator|=
name|current
expr_stmt|;
if|if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|read
operator|->
name|active
operator|&&
name|c
index|[
name|i
index|]
operator|.
name|read
operator|->
name|event_handler
condition|)
block|{
name|n
operator|++
expr_stmt|;
name|c
index|[
name|i
index|]
operator|.
name|read
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|ngx_threaded
condition|)
block|{
name|c
index|[
name|i
index|]
operator|.
name|read
operator|->
name|event_handler
argument_list|(
name|c
index|[
name|i
index|]
operator|.
name|read
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|ngx_mutex_lock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_post_event
argument_list|(
name|c
index|[
name|i
index|]
operator|.
name|read
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|write
operator|->
name|active
operator|&&
name|c
index|[
name|i
index|]
operator|.
name|write
operator|->
name|event_handler
condition|)
block|{
name|n
operator|++
expr_stmt|;
name|c
index|[
name|i
index|]
operator|.
name|write
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
if|if
condition|(
operator|!
name|ngx_threaded
condition|)
block|{
name|c
index|[
name|i
index|]
operator|.
name|write
operator|->
name|event_handler
argument_list|(
name|c
index|[
name|i
index|]
operator|.
name|write
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|ngx_mutex_lock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_post_event
argument_list|(
name|c
index|[
name|i
index|]
operator|.
name|write
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
name|ngx_posted_events_mutex
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|n
operator|&&
operator|(
name|n
operator|%
literal|100
operator|==
literal|0
operator|)
condition|)
block|{
comment|/*              * Check the current rt queue length to prevent the new overflow.              *              * Learn the /proc/sys/kernel/rtsig-max value because              * it can be changed sisnce the last checking.              */
name|name
index|[
literal|0
index|]
operator|=
name|CTL_KERN
expr_stmt|;
name|name
index|[
literal|1
index|]
operator|=
name|KERN_RTSIGMAX
expr_stmt|;
name|len
operator|=
sizeof|sizeof
argument_list|(
name|rtsig_max
argument_list|)
expr_stmt|;
if|if
condition|(
name|sysctl
argument_list|(
name|name
argument_list|,
sizeof|sizeof
argument_list|(
name|name
argument_list|)
argument_list|,
operator|&
name|rtsig_max
argument_list|,
operator|&
name|len
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|errno
argument_list|,
literal|"sysctl(KERN_RTSIGMAX) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|name
index|[
literal|0
index|]
operator|=
name|CTL_KERN
expr_stmt|;
name|name
index|[
literal|1
index|]
operator|=
name|KERN_RTSIGNR
expr_stmt|;
name|len
operator|=
sizeof|sizeof
argument_list|(
name|rtsig_nr
argument_list|)
expr_stmt|;
if|if
condition|(
name|sysctl
argument_list|(
name|name
argument_list|,
sizeof|sizeof
argument_list|(
name|name
argument_list|)
argument_list|,
operator|&
name|rtsig_nr
argument_list|,
operator|&
name|len
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|errno
argument_list|,
literal|"sysctl(KERN_RTSIGNR) failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
comment|/*              * drain rt signal queue if the /proc/sys/kernel/rtsig-nr              * is bigger than "/proc/sys/kernel/rtsig-max / 4"              */
if|if
condition|(
name|rtsig_max
operator|/
literal|4
operator|<
name|rtsig_nr
condition|)
block|{
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_EVENT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rtsig queue state: %d/%d"
argument_list|,
name|rtsig_nr
argument_list|,
name|rtsig_max
argument_list|)
expr_stmt|;
while|while
condition|(
name|ngx_rtsig_process_events
argument_list|(
name|cycle
argument_list|)
operator|==
name|NGX_OK
condition|)
block|{
comment|/* void */
block|}
block|}
block|}
block|}
if|if
condition|(
operator|!
name|ngx_threaded
condition|)
block|{
name|ngx_event_process_posted
argument_list|(
name|cycle
argument_list|)
expr_stmt|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"rt signal queue overflow recovered"
argument_list|)
expr_stmt|;
name|overflow
operator|=
literal|0
expr_stmt|;
name|ngx_event_actions
operator|.
name|process
operator|=
name|ngx_rtsig_process_events
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_rtsig_create_conf (ngx_cycle_t * cycle)
specifier|static
name|void
modifier|*
name|ngx_rtsig_create_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_rtsig_conf_t
modifier|*
name|rtscf
decl_stmt|;
name|ngx_test_null
argument_list|(
name|rtscf
argument_list|,
name|ngx_palloc
argument_list|(
name|cycle
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_rtsig_conf_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|rtscf
operator|->
name|signo
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|rtscf
return|;
block|}
end_function

begin_function
DECL|function|ngx_rtsig_init_conf (ngx_cycle_t * cycle,void * conf)
specifier|static
name|char
modifier|*
name|ngx_rtsig_init_conf
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_rtsig_conf_t
modifier|*
name|rtscf
init|=
name|conf
decl_stmt|;
comment|/* LinuxThreads use the first 3 RT signals */
name|ngx_conf_init_value
argument_list|(
name|rtscf
operator|->
name|signo
argument_list|,
name|SIGRTMIN
operator|+
literal|10
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

