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

begin_comment
comment|/*  * find the middle queue element if the queue has odd number of elements  * or the first element of the queue's second part otherwise  */
end_comment

begin_function
name|ngx_queue_t
modifier|*
DECL|function|ngx_queue_middle (ngx_queue_t * queue)
name|ngx_queue_middle
parameter_list|(
name|ngx_queue_t
modifier|*
name|queue
parameter_list|)
block|{
name|ngx_queue_t
modifier|*
name|middle
decl_stmt|,
modifier|*
name|next
decl_stmt|;
name|middle
operator|=
name|ngx_queue_head
argument_list|(
name|queue
argument_list|)
expr_stmt|;
if|if
condition|(
name|middle
operator|==
name|ngx_queue_last
argument_list|(
name|queue
argument_list|)
condition|)
block|{
return|return
name|middle
return|;
block|}
name|next
operator|=
name|ngx_queue_head
argument_list|(
name|queue
argument_list|)
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|middle
operator|=
name|ngx_queue_next
argument_list|(
name|middle
argument_list|)
expr_stmt|;
name|next
operator|=
name|ngx_queue_next
argument_list|(
name|next
argument_list|)
expr_stmt|;
if|if
condition|(
name|next
operator|==
name|ngx_queue_last
argument_list|(
name|queue
argument_list|)
condition|)
block|{
return|return
name|middle
return|;
block|}
name|next
operator|=
name|ngx_queue_next
argument_list|(
name|next
argument_list|)
expr_stmt|;
if|if
condition|(
name|next
operator|==
name|ngx_queue_last
argument_list|(
name|queue
argument_list|)
condition|)
block|{
return|return
name|middle
return|;
block|}
block|}
block|}
end_function

begin_comment
comment|/* the stable insertion sort */
end_comment

begin_function
name|void
DECL|function|ngx_queue_sort (ngx_queue_t * queue,ngx_int_t (* cmp)(const ngx_queue_t *,const ngx_queue_t *))
name|ngx_queue_sort
parameter_list|(
name|ngx_queue_t
modifier|*
name|queue
parameter_list|,
name|ngx_int_t
function_decl|(
modifier|*
name|cmp
function_decl|)
parameter_list|(
specifier|const
name|ngx_queue_t
modifier|*
parameter_list|,
specifier|const
name|ngx_queue_t
modifier|*
parameter_list|)
parameter_list|)
block|{
name|ngx_queue_t
modifier|*
name|q
decl_stmt|,
modifier|*
name|prev
decl_stmt|,
modifier|*
name|next
decl_stmt|;
name|q
operator|=
name|ngx_queue_head
argument_list|(
name|queue
argument_list|)
expr_stmt|;
if|if
condition|(
name|q
operator|==
name|ngx_queue_last
argument_list|(
name|queue
argument_list|)
condition|)
block|{
return|return;
block|}
for|for
control|(
name|q
operator|=
name|ngx_queue_next
argument_list|(
name|q
argument_list|)
init|;
name|q
operator|!=
name|ngx_queue_sentinel
argument_list|(
name|queue
argument_list|)
condition|;
name|q
operator|=
name|next
control|)
block|{
name|prev
operator|=
name|ngx_queue_prev
argument_list|(
name|q
argument_list|)
expr_stmt|;
name|next
operator|=
name|ngx_queue_next
argument_list|(
name|q
argument_list|)
expr_stmt|;
name|ngx_queue_remove
argument_list|(
name|q
argument_list|)
expr_stmt|;
do|do
block|{
if|if
condition|(
name|cmp
argument_list|(
name|prev
argument_list|,
name|q
argument_list|)
operator|<=
literal|0
condition|)
block|{
break|break;
block|}
name|prev
operator|=
name|ngx_queue_prev
argument_list|(
name|prev
argument_list|)
expr_stmt|;
block|}
do|while
condition|(
name|prev
operator|!=
name|ngx_queue_sentinel
argument_list|(
name|queue
argument_list|)
condition|)
do|;
name|ngx_queue_insert_after
argument_list|(
name|prev
argument_list|,
name|q
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

