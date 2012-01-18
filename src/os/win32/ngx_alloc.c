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
DECL|variable|ngx_pagesize
name|ngx_uint_t
name|ngx_pagesize
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_pagesize_shift
name|ngx_uint_t
name|ngx_pagesize_shift
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_cacheline_size
name|ngx_uint_t
name|ngx_cacheline_size
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_alloc (size_t size,ngx_log_t * log)
name|void
modifier|*
name|ngx_alloc
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|void
modifier|*
name|p
decl_stmt|;
name|p
operator|=
name|malloc
argument_list|(
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"malloc(%uz) failed"
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_ALLOC
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"malloc: %p:%uz"
argument_list|,
name|p
argument_list|,
name|size
argument_list|)
expr_stmt|;
return|return
name|p
return|;
block|}
end_function

begin_function
DECL|function|ngx_calloc (size_t size,ngx_log_t * log)
name|void
modifier|*
name|ngx_calloc
parameter_list|(
name|size_t
name|size
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|void
modifier|*
name|p
decl_stmt|;
name|p
operator|=
name|ngx_alloc
argument_list|(
name|size
argument_list|,
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
condition|)
block|{
name|ngx_memzero
argument_list|(
name|p
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
return|return
name|p
return|;
block|}
end_function

end_unit

