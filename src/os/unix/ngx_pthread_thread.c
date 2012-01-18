begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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

begin_decl_stmt
DECL|variable|nthreads
specifier|static
name|ngx_uint_t
name|nthreads
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|max_threads
specifier|static
name|ngx_uint_t
name|max_threads
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|thr_attr
specifier|static
name|pthread_attr_t
name|thr_attr
decl_stmt|;
end_decl_stmt

begin_function
name|ngx_err_t
DECL|function|ngx_create_thread (ngx_tid_t * tid,ngx_thread_value_t (* func)(void * arg),void * arg,ngx_log_t * log)
name|ngx_create_thread
parameter_list|(
name|ngx_tid_t
modifier|*
name|tid
parameter_list|,
name|ngx_thread_value_t
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
block|{
name|int
name|err
decl_stmt|;
if|if
condition|(
name|nthreads
operator|>=
name|max_threads
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"no more than %ui threads can be created"
argument_list|,
name|max_threads
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|err
operator|=
name|pthread_create
argument_list|(
name|tid
argument_list|,
operator|&
name|thr_attr
argument_list|,
name|func
argument_list|,
name|arg
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_create() failed"
argument_list|)
expr_stmt|;
return|return
name|err
return|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"thread is created: "
name|NGX_TID_T_FMT
argument_list|,
operator|*
name|tid
argument_list|)
expr_stmt|;
name|nthreads
operator|++
expr_stmt|;
return|return
name|err
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_init_threads (int n,size_t size,ngx_cycle_t * cycle)
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
block|{
name|int
name|err
decl_stmt|;
name|max_threads
operator|=
name|n
expr_stmt|;
name|err
operator|=
name|pthread_attr_init
argument_list|(
operator|&
name|thr_attr
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
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
name|err
argument_list|,
literal|"pthread_attr_init() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|err
operator|=
name|pthread_attr_setstacksize
argument_list|(
operator|&
name|thr_attr
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
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
name|err
argument_list|,
literal|"pthread_attr_setstacksize() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_threaded
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_mutex_t
modifier|*
DECL|function|ngx_mutex_init (ngx_log_t * log,ngx_uint_t flags)
name|ngx_mutex_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|ngx_uint_t
name|flags
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
name|ngx_mutex_t
modifier|*
name|m
decl_stmt|;
name|m
operator|=
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_mutex_t
argument_list|)
argument_list|,
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|m
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|m
operator|->
name|log
operator|=
name|log
expr_stmt|;
name|err
operator|=
name|pthread_mutex_init
argument_list|(
operator|&
name|m
operator|->
name|mutex
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|m
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_mutex_init() failed"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|m
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_mutex_destroy (ngx_mutex_t * m)
name|ngx_mutex_destroy
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
name|err
operator|=
name|pthread_mutex_destroy
argument_list|(
operator|&
name|m
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|m
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_mutex_destroy(%p) failed"
argument_list|,
name|m
argument_list|)
expr_stmt|;
block|}
name|ngx_free
argument_list|(
name|m
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_mutex_lock (ngx_mutex_t * m)
name|ngx_mutex_lock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
if|if
condition|(
operator|!
name|ngx_threaded
condition|)
block|{
return|return;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_MUTEX
argument_list|,
name|m
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"lock mutex %p"
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|err
operator|=
name|pthread_mutex_lock
argument_list|(
operator|&
name|m
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|m
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_mutex_lock(%p) failed"
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|ngx_abort
argument_list|()
expr_stmt|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_MUTEX
argument_list|,
name|m
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mutex %p is locked"
argument_list|,
name|m
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_mutex_trylock (ngx_mutex_t * m)
name|ngx_mutex_trylock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
if|if
condition|(
operator|!
name|ngx_threaded
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_MUTEX
argument_list|,
name|m
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"try lock mutex %p"
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|err
operator|=
name|pthread_mutex_trylock
argument_list|(
operator|&
name|m
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_EBUSY
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|m
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_mutex_trylock(%p) failed"
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|ngx_abort
argument_list|()
expr_stmt|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_MUTEX
argument_list|,
name|m
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mutex %p is locked"
argument_list|,
name|m
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_mutex_unlock (ngx_mutex_t * m)
name|ngx_mutex_unlock
parameter_list|(
name|ngx_mutex_t
modifier|*
name|m
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
if|if
condition|(
operator|!
name|ngx_threaded
condition|)
block|{
return|return;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_MUTEX
argument_list|,
name|m
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"unlock mutex %p"
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|err
operator|=
name|pthread_mutex_unlock
argument_list|(
operator|&
name|m
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|m
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_mutex_unlock(%p) failed"
argument_list|,
name|m
argument_list|)
expr_stmt|;
name|ngx_abort
argument_list|()
expr_stmt|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_MUTEX
argument_list|,
name|m
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mutex %p is unlocked"
argument_list|,
name|m
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

begin_function
name|ngx_cond_t
modifier|*
DECL|function|ngx_cond_init (ngx_log_t * log)
name|ngx_cond_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
name|ngx_cond_t
modifier|*
name|cv
decl_stmt|;
name|cv
operator|=
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_cond_t
argument_list|)
argument_list|,
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|cv
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|cv
operator|->
name|log
operator|=
name|log
expr_stmt|;
name|err
operator|=
name|pthread_cond_init
argument_list|(
operator|&
name|cv
operator|->
name|cond
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cv
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_cond_init() failed"
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
return|return
name|cv
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_cond_destroy (ngx_cond_t * cv)
name|ngx_cond_destroy
parameter_list|(
name|ngx_cond_t
modifier|*
name|cv
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
name|err
operator|=
name|pthread_cond_destroy
argument_list|(
operator|&
name|cv
operator|->
name|cond
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cv
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_cond_destroy(%p) failed"
argument_list|,
name|cv
argument_list|)
expr_stmt|;
block|}
name|ngx_free
argument_list|(
name|cv
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_cond_wait (ngx_cond_t * cv,ngx_mutex_t * m)
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
block|{
name|int
name|err
decl_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|cv
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"cv %p wait"
argument_list|,
name|cv
argument_list|)
expr_stmt|;
name|err
operator|=
name|pthread_cond_wait
argument_list|(
operator|&
name|cv
operator|->
name|cond
argument_list|,
operator|&
name|m
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cv
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_cond_wait(%p) failed"
argument_list|,
name|cv
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|cv
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"cv %p is waked up"
argument_list|,
name|cv
argument_list|)
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_MUTEX
argument_list|,
name|m
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mutex %p is locked"
argument_list|,
name|m
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_cond_signal (ngx_cond_t * cv)
name|ngx_cond_signal
parameter_list|(
name|ngx_cond_t
modifier|*
name|cv
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|cv
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"cv %p to signal"
argument_list|,
name|cv
argument_list|)
expr_stmt|;
name|err
operator|=
name|pthread_cond_signal
argument_list|(
operator|&
name|cv
operator|->
name|cond
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|!=
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cv
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_cond_signal(%p) failed"
argument_list|,
name|cv
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|cv
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"cv %p is signaled"
argument_list|,
name|cv
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

