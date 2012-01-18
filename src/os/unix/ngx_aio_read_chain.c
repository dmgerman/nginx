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

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_function
name|ssize_t
DECL|function|ngx_aio_read_chain (ngx_connection_t * c,ngx_chain_t * cl)
name|ngx_aio_read_chain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|cl
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
name|u_char
modifier|*
name|buf
decl_stmt|,
modifier|*
name|prev
decl_stmt|;
name|size_t
name|size
decl_stmt|;
name|ssize_t
name|total
decl_stmt|;
if|if
condition|(
name|c
operator|->
name|read
operator|->
name|pending_eof
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|ready
operator|=
literal|0
expr_stmt|;
return|return
literal|0
return|;
block|}
name|total
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|cl
condition|)
block|{
comment|/* we can post the single aio operation only */
if|if
condition|(
operator|!
name|c
operator|->
name|read
operator|->
name|ready
condition|)
block|{
return|return
name|total
condition|?
name|total
else|:
name|NGX_AGAIN
return|;
block|}
name|buf
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|prev
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|size
operator|=
literal|0
expr_stmt|;
comment|/* coalesce the neighbouring bufs */
while|while
condition|(
name|cl
operator|&&
name|prev
operator|==
name|cl
operator|->
name|buf
operator|->
name|last
condition|)
block|{
name|size
operator|+=
name|cl
operator|->
name|buf
operator|->
name|end
operator|-
name|cl
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|prev
operator|=
name|cl
operator|->
name|buf
operator|->
name|end
expr_stmt|;
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
block|}
name|n
operator|=
name|ngx_aio_read
argument_list|(
name|c
argument_list|,
name|buf
argument_list|,
name|size
argument_list|)
expr_stmt|;
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
literal|"aio_read: %d"
argument_list|,
name|n
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return
name|total
condition|?
name|total
else|:
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|n
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
name|n
operator|==
literal|0
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|pending_eof
operator|=
literal|1
expr_stmt|;
if|if
condition|(
name|total
condition|)
block|{
name|c
operator|->
name|read
operator|->
name|eof
operator|=
literal|0
expr_stmt|;
name|c
operator|->
name|read
operator|->
name|ready
operator|=
literal|1
expr_stmt|;
block|}
return|return
name|total
return|;
block|}
if|if
condition|(
name|n
operator|>
literal|0
condition|)
block|{
name|total
operator|+=
name|n
expr_stmt|;
block|}
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
literal|"aio_read total: %d"
argument_list|,
name|total
argument_list|)
expr_stmt|;
block|}
return|return
name|total
condition|?
name|total
else|:
name|NGX_AGAIN
return|;
block|}
end_function

end_unit

