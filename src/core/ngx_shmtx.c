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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_ATOMIC_OPS
operator|)
end_if

begin_function_decl
specifier|static
name|void
name|ngx_shmtx_wakeup
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|ngx_int_t
DECL|function|ngx_shmtx_create (ngx_shmtx_t * mtx,ngx_shmtx_sh_t * addr,u_char * name)
name|ngx_shmtx_create
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|,
name|ngx_shmtx_sh_t
modifier|*
name|addr
parameter_list|,
name|u_char
modifier|*
name|name
parameter_list|)
block|{
name|mtx
operator|->
name|lock
operator|=
operator|&
name|addr
operator|->
name|lock
expr_stmt|;
if|if
condition|(
name|mtx
operator|->
name|spin
operator|==
operator|(
name|ngx_uint_t
operator|)
operator|-
literal|1
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|mtx
operator|->
name|spin
operator|=
literal|2048
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_POSIX_SEM
operator|)
name|mtx
operator|->
name|wait
operator|=
operator|&
name|addr
operator|->
name|wait
expr_stmt|;
if|if
condition|(
name|sem_init
argument_list|(
operator|&
name|mtx
operator|->
name|sem
argument_list|,
literal|1
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
name|ngx_cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"sem_init() failed"
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|mtx
operator|->
name|semaphore
operator|=
literal|1
expr_stmt|;
block|}
endif|#
directive|endif
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_shmtx_destory (ngx_shmtx_t * mtx)
name|ngx_shmtx_destory
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_POSIX_SEM
operator|)
if|if
condition|(
name|mtx
operator|->
name|semaphore
condition|)
block|{
if|if
condition|(
name|sem_destroy
argument_list|(
operator|&
name|mtx
operator|->
name|sem
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
name|ngx_cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"sem_destroy() failed"
argument_list|)
expr_stmt|;
block|}
block|}
endif|#
directive|endif
block|}
end_function

begin_function
name|ngx_uint_t
DECL|function|ngx_shmtx_trylock (ngx_shmtx_t * mtx)
name|ngx_shmtx_trylock
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
return|return
operator|(
operator|*
name|mtx
operator|->
name|lock
operator|==
literal|0
operator|&&
name|ngx_atomic_cmp_set
argument_list|(
name|mtx
operator|->
name|lock
argument_list|,
literal|0
argument_list|,
name|ngx_pid
argument_list|)
operator|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_shmtx_lock (ngx_shmtx_t * mtx)
name|ngx_shmtx_lock
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"shmtx lock"
argument_list|)
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
operator|*
name|mtx
operator|->
name|lock
operator|==
literal|0
operator|&&
name|ngx_atomic_cmp_set
argument_list|(
name|mtx
operator|->
name|lock
argument_list|,
literal|0
argument_list|,
name|ngx_pid
argument_list|)
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|ngx_ncpu
operator|>
literal|1
condition|)
block|{
for|for
control|(
name|n
operator|=
literal|1
init|;
name|n
operator|<
name|mtx
operator|->
name|spin
condition|;
name|n
operator|<<=
literal|1
control|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n
condition|;
name|i
operator|++
control|)
block|{
name|ngx_cpu_pause
argument_list|()
expr_stmt|;
block|}
if|if
condition|(
operator|*
name|mtx
operator|->
name|lock
operator|==
literal|0
operator|&&
name|ngx_atomic_cmp_set
argument_list|(
name|mtx
operator|->
name|lock
argument_list|,
literal|0
argument_list|,
name|ngx_pid
argument_list|)
condition|)
block|{
return|return;
block|}
block|}
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_POSIX_SEM
operator|)
if|if
condition|(
name|mtx
operator|->
name|semaphore
condition|)
block|{
operator|(
name|void
operator|)
name|ngx_atomic_fetch_add
argument_list|(
name|mtx
operator|->
name|wait
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|mtx
operator|->
name|lock
operator|==
literal|0
operator|&&
name|ngx_atomic_cmp_set
argument_list|(
name|mtx
operator|->
name|lock
argument_list|,
literal|0
argument_list|,
name|ngx_pid
argument_list|)
condition|)
block|{
return|return;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"shmtx wait %uA"
argument_list|,
operator|*
name|mtx
operator|->
name|wait
argument_list|)
expr_stmt|;
while|while
condition|(
name|sem_wait
argument_list|(
operator|&
name|mtx
operator|->
name|sem
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_err_t
name|err
decl_stmt|;
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|err
operator|!=
name|NGX_EINTR
condition|)
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
literal|"sem_wait() failed while waiting on shmtx"
argument_list|)
expr_stmt|;
break|break;
block|}
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"shmtx awoke"
argument_list|)
expr_stmt|;
block|}
continue|continue;
block|}
endif|#
directive|endif
name|ngx_sched_yield
argument_list|()
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|ngx_shmtx_unlock (ngx_shmtx_t * mtx)
name|ngx_shmtx_unlock
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
if|if
condition|(
name|mtx
operator|->
name|spin
operator|!=
operator|(
name|ngx_uint_t
operator|)
operator|-
literal|1
condition|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"shmtx unlock"
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ngx_atomic_cmp_set
argument_list|(
name|mtx
operator|->
name|lock
argument_list|,
name|ngx_pid
argument_list|,
literal|0
argument_list|)
condition|)
block|{
name|ngx_shmtx_wakeup
argument_list|(
name|mtx
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|ngx_uint_t
DECL|function|ngx_shmtx_force_unlock (ngx_shmtx_t * mtx,ngx_pid_t pid)
name|ngx_shmtx_force_unlock
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|,
name|ngx_pid_t
name|pid
parameter_list|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"shmtx forced unlock"
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_atomic_cmp_set
argument_list|(
name|mtx
operator|->
name|lock
argument_list|,
name|pid
argument_list|,
literal|0
argument_list|)
condition|)
block|{
name|ngx_shmtx_wakeup
argument_list|(
name|mtx
argument_list|)
expr_stmt|;
return|return
literal|1
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_shmtx_wakeup (ngx_shmtx_t * mtx)
name|ngx_shmtx_wakeup
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_POSIX_SEM
operator|)
name|ngx_atomic_uint_t
name|wait
decl_stmt|;
if|if
condition|(
operator|!
name|mtx
operator|->
name|semaphore
condition|)
block|{
return|return;
block|}
for|for
control|(
init|;
condition|;
control|)
block|{
name|wait
operator|=
operator|*
name|mtx
operator|->
name|wait
expr_stmt|;
if|if
condition|(
name|wait
operator|==
literal|0
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|ngx_atomic_cmp_set
argument_list|(
name|mtx
operator|->
name|wait
argument_list|,
name|wait
argument_list|,
name|wait
operator|-
literal|1
argument_list|)
condition|)
block|{
break|break;
block|}
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"shmtx wake %uA"
argument_list|,
name|wait
argument_list|)
expr_stmt|;
if|if
condition|(
name|sem_post
argument_list|(
operator|&
name|mtx
operator|->
name|sem
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
name|ngx_cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"sem_post() failed while wake shmtx"
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_function
name|ngx_int_t
DECL|function|ngx_shmtx_create (ngx_shmtx_t * mtx,ngx_shmtx_sh_t * addr,u_char * name)
name|ngx_shmtx_create
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|,
name|ngx_shmtx_sh_t
modifier|*
name|addr
parameter_list|,
name|u_char
modifier|*
name|name
parameter_list|)
block|{
if|if
condition|(
name|mtx
operator|->
name|name
condition|)
block|{
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|name
argument_list|,
name|mtx
operator|->
name|name
argument_list|)
operator|==
literal|0
condition|)
block|{
name|mtx
operator|->
name|name
operator|=
name|name
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|ngx_shmtx_destory
argument_list|(
name|mtx
argument_list|)
expr_stmt|;
block|}
name|mtx
operator|->
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|name
argument_list|,
name|NGX_FILE_RDWR
argument_list|,
name|NGX_FILE_CREATE_OR_OPEN
argument_list|,
name|NGX_FILE_DEFAULT_ACCESS
argument_list|)
expr_stmt|;
if|if
condition|(
name|mtx
operator|->
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_open_file_n
literal|" \"%s\" failed"
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|ngx_delete_file
argument_list|(
name|name
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_delete_file_n
literal|" \"%s\" failed"
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
name|mtx
operator|->
name|name
operator|=
name|name
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_shmtx_destory (ngx_shmtx_t * mtx)
name|ngx_shmtx_destory
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
if|if
condition|(
name|ngx_close_file
argument_list|(
name|mtx
operator|->
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|mtx
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|ngx_uint_t
DECL|function|ngx_shmtx_trylock (ngx_shmtx_t * mtx)
name|ngx_shmtx_trylock
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
name|ngx_err_t
name|err
decl_stmt|;
name|err
operator|=
name|ngx_trylock_fd
argument_list|(
name|mtx
operator|->
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
literal|0
condition|)
block|{
return|return
literal|1
return|;
block|}
if|if
condition|(
name|err
operator|==
name|NGX_EAGAIN
condition|)
block|{
return|return
literal|0
return|;
block|}
if|#
directive|if
name|__osf__
comment|/* Tru64 UNIX */
if|if
condition|(
name|err
operator|==
name|NGX_EACCESS
condition|)
block|{
return|return
literal|0
return|;
block|}
endif|#
directive|endif
name|ngx_log_abort
argument_list|(
name|err
argument_list|,
name|ngx_trylock_fd_n
literal|" %s failed"
argument_list|,
name|mtx
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_shmtx_lock (ngx_shmtx_t * mtx)
name|ngx_shmtx_lock
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
name|ngx_err_t
name|err
decl_stmt|;
name|err
operator|=
name|ngx_lock_fd
argument_list|(
name|mtx
operator|->
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
literal|0
condition|)
block|{
return|return;
block|}
name|ngx_log_abort
argument_list|(
name|err
argument_list|,
name|ngx_lock_fd_n
literal|" %s failed"
argument_list|,
name|mtx
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_shmtx_unlock (ngx_shmtx_t * mtx)
name|ngx_shmtx_unlock
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|)
block|{
name|ngx_err_t
name|err
decl_stmt|;
name|err
operator|=
name|ngx_unlock_fd
argument_list|(
name|mtx
operator|->
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
literal|0
condition|)
block|{
return|return;
block|}
name|ngx_log_abort
argument_list|(
name|err
argument_list|,
name|ngx_unlock_fd_n
literal|" %s failed"
argument_list|,
name|mtx
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ngx_uint_t
DECL|function|ngx_shmtx_force_unlock (ngx_shmtx_t * mtx,ngx_pid_t pid)
name|ngx_shmtx_force_unlock
parameter_list|(
name|ngx_shmtx_t
modifier|*
name|mtx
parameter_list|,
name|ngx_pid_t
name|pid
parameter_list|)
block|{
return|return
literal|0
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

