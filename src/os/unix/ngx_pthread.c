begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_pthread.h>
end_include

begin_function
DECL|function|ngx_create_os_thread (ngx_os_tid_t * tid,void * stack,ngx_thread_start_routine_t func,void * arg,ngx_log_t log)
name|int
name|ngx_create_os_thread
parameter_list|(
name|ngx_os_tid_t
modifier|*
name|tid
parameter_list|,
name|void
modifier|*
name|stack
parameter_list|,
name|ngx_thread_start_routine_t
name|func
parameter_list|,
name|void
modifier|*
name|arg
parameter_list|,
name|ngx_log_t
name|log
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
name|pthread_attr_t
modifier|*
name|attr
decl_stmt|;
name|attr
operator|=
name|NULL
expr_stmt|;
name|err
operator|=
name|pthread_create
argument_list|(
name|tid
argument_list|,
name|attr
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
name|NGX_LOG_ERR
argument_list|,
name|log
argument_list|,
name|err
argument_list|,
literal|"pthread_create() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

