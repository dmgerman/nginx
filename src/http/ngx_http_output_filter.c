begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
file|<ngx_files.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_conf_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_output_filter.h>
end_include

begin_function_decl
specifier|static
name|int
name|ngx_http_output_filter_copy_hunk
parameter_list|(
name|ngx_hunk_t
modifier|*
name|dst
parameter_list|,
name|ngx_hunk_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_output_filter_create_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_output_filter_merge_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|void
modifier|*
name|parent
parameter_list|,
name|void
modifier|*
name|child
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_output_filter_commands
specifier|static
name|ngx_command_t
name|ngx_http_output_filter_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"output_buffer"
argument_list|)
block|,
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_size_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
argument|ngx_http_output_filter_conf_t
argument_list|,
argument|hunk_size
argument_list|)
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|""
argument_list|)
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_output_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_output_filter_module_ctx
init|=
block|{
name|NGX_HTTP_MODULE
block|,
name|NULL
block|,
comment|/* create server config */
name|NULL
block|,
comment|/* init server config */
name|ngx_http_output_filter_create_conf
block|,
comment|/* create location config */
name|ngx_http_output_filter_merge_conf
block|,
comment|/* merge location config */
name|NULL
block|,
comment|/* translate handler */
name|NULL
block|,
comment|/* output header filter */
name|NULL
block|,
comment|/* next output header filter */
operator|(
name|int
argument_list|(
operator|*
argument_list|)
argument_list|(
name|ngx_http_request_t
operator|*
argument_list|,
name|ngx_chain_t
operator|*
argument_list|)
operator|)
name|ngx_http_output_filter
block|,
comment|/* output body filter */
name|NULL
comment|/* next output body filter */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_output_filter_module
name|ngx_module_t
name|ngx_http_output_filter_module
init|=
block|{
literal|0
block|,
comment|/* module index */
operator|&
name|ngx_http_output_filter_module_ctx
block|,
comment|/* module context */
name|ngx_http_output_filter_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE_TYPE
block|,
comment|/* module type */
name|NULL
comment|/* init module */
block|}
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|next_filter
define|#
directive|define
name|next_filter
value|ngx_http_output_filter_module_ctx.next_output_body_filter
end_define

begin_define
DECL|macro|need_to_copy (r,hunk)
define|#
directive|define
name|need_to_copy
parameter_list|(
name|r
parameter_list|,
name|hunk
parameter_list|)
define|\
value|(((r->filter& NGX_HTTP_FILTER_NEED_IN_MEMORY)                \&& (hunk->type& NGX_HUNK_FILE))                           \             || ((r->filter& NGX_HTTP_FILTER_NEED_TEMP)                   \&& (hunk->type& (NGX_HUNK_MEMORY|NGX_HUNK_MMAP))))
end_define

begin_function
DECL|function|ngx_http_output_filter (ngx_http_request_t * r,ngx_hunk_t * hunk)
name|int
name|ngx_http_output_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_hunk_t
modifier|*
name|hunk
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|size_t
name|size
decl_stmt|;
name|ngx_chain_t
modifier|*
name|ce
decl_stmt|,
modifier|*
name|pe
decl_stmt|;
name|ngx_http_output_filter_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_output_filter_conf_t
modifier|*
name|conf
decl_stmt|;
name|ctx
operator|=
operator|(
name|ngx_http_output_filter_ctx_t
operator|*
operator|)
name|ngx_http_get_module_ctx
argument_list|(
name|r
operator|->
expr|main
operator|?
name|r
operator|->
expr|main
operator|:
name|r
argument_list|,
name|ngx_http_output_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|==
name|NULL
condition|)
block|{
name|ngx_http_create_ctx
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|,
name|ngx_http_output_filter_module
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_output_filter_ctx_t
argument_list|)
argument_list|)
expr_stmt|;
block|}
comment|/* the short path for the case when the chain ctx->incoming is empty        and there is no hunk or the hunk does not require the copy */
if|if
condition|(
name|ctx
operator|->
name|incoming
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|hunk
operator|==
name|NULL
condition|)
block|{
return|return
name|next_filter
argument_list|(
name|r
argument_list|,
name|NULL
argument_list|)
return|;
block|}
comment|/* we do not need to copy the incoming hunk to our hunk */
if|if
condition|(
operator|!
name|need_to_copy
argument_list|(
name|r
argument_list|,
name|hunk
argument_list|)
condition|)
block|{
name|ctx
operator|->
name|out
operator|.
name|hunk
operator|=
name|hunk
expr_stmt|;
name|ctx
operator|->
name|out
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
return|return
name|next_filter
argument_list|(
name|r
argument_list|,
operator|&
name|ctx
operator|->
name|out
argument_list|)
return|;
block|}
block|}
comment|/* add the incoming hunk to the chain ctx->incoming */
if|if
condition|(
name|hunk
condition|)
block|{
comment|/* the output of the only hunk is common case so we have            special chain entry ctx->in for it */
if|if
condition|(
name|ctx
operator|->
name|incoming
operator|==
name|NULL
condition|)
block|{
name|ctx
operator|->
name|in
operator|.
name|hunk
operator|=
name|hunk
expr_stmt|;
name|ctx
operator|->
name|in
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
name|ctx
operator|->
name|incoming
operator|=
operator|&
name|ctx
operator|->
name|in
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|ce
operator|=
name|ctx
operator|->
name|incoming
init|;
name|ce
operator|->
name|next
condition|;
name|ce
operator|=
name|ce
operator|->
name|next
control|)
block|{
comment|/* void */
empty_stmt|;
block|}
name|ngx_add_hunk_to_chain
argument_list|(
name|ce
operator|->
name|next
argument_list|,
name|hunk
argument_list|,
name|r
operator|->
name|pool
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
block|}
block|}
comment|/* allocate our hunk if it's needed */
if|if
condition|(
name|ctx
operator|->
name|hunk
operator|==
name|NULL
condition|)
block|{
name|conf
operator|=
operator|(
name|ngx_http_output_filter_conf_t
operator|*
operator|)
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
operator|->
expr|main
operator|?
name|r
operator|->
expr|main
operator|:
name|r
argument_list|,
name|ngx_http_output_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_LAST
condition|)
block|{
name|size
operator|=
name|hunk
operator|->
name|last
operator|.
name|mem
operator|-
name|hunk
operator|->
name|pos
operator|.
name|mem
expr_stmt|;
if|if
condition|(
name|size
operator|>
name|conf
operator|->
name|hunk_size
condition|)
block|{
name|size
operator|=
name|conf
operator|->
name|hunk_size
expr_stmt|;
block|}
block|}
else|else
block|{
name|size
operator|=
name|conf
operator|->
name|hunk_size
expr_stmt|;
block|}
name|ngx_test_null
argument_list|(
name|ctx
operator|->
name|hunk
argument_list|,
name|ngx_create_temp_hunk
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|size
argument_list|,
literal|50
argument_list|,
literal|50
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|hunk
operator|->
name|type
operator||=
name|NGX_HUNK_RECYCLED
expr_stmt|;
comment|/* our hunk is still busy */
block|}
if|else if
condition|(
name|ctx
operator|->
name|hunk
operator|->
name|pos
operator|.
name|mem
operator|<
name|ctx
operator|->
name|hunk
operator|->
name|last
operator|.
name|mem
condition|)
block|{
name|rc
operator|=
name|next_filter
argument_list|(
name|r
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|rc
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return
name|rc
return|;
block|}
comment|/* NGX_OK */
comment|/* set our hunk free */
name|ctx
operator|->
name|hunk
operator|->
name|pos
operator|.
name|mem
operator|=
name|ctx
operator|->
name|hunk
operator|->
name|last
operator|.
name|mem
operator|=
name|ctx
operator|->
name|hunk
operator|->
name|start
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_SUPPRESS_WARN
operator|)
name|pe
operator|=
name|NULL
expr_stmt|;
endif|#
directive|endif
comment|/* process the chain ctx->incoming */
do|do
block|{
comment|/* find the hunks that do not need to be copied ... */
for|for
control|(
name|ce
operator|=
name|ctx
operator|->
name|incoming
init|;
name|ce
condition|;
name|ce
operator|=
name|ce
operator|->
name|next
control|)
block|{
if|if
condition|(
name|need_to_copy
argument_list|(
name|r
argument_list|,
name|ce
operator|->
name|hunk
argument_list|)
condition|)
block|{
break|break;
block|}
name|pe
operator|=
name|ce
expr_stmt|;
block|}
comment|/* ... and pass them to the next filter */
if|if
condition|(
name|ctx
operator|->
name|incoming
operator|!=
name|ce
condition|)
block|{
name|ctx
operator|->
name|out
operator|.
name|hunk
operator|=
name|ctx
operator|->
name|incoming
operator|->
name|hunk
expr_stmt|;
name|ctx
operator|->
name|out
operator|.
name|next
operator|=
name|ctx
operator|->
name|incoming
operator|->
name|next
expr_stmt|;
name|ctx
operator|->
name|incoming
operator|=
name|ce
expr_stmt|;
name|pe
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
name|rc
operator|=
name|next_filter
argument_list|(
name|r
argument_list|,
operator|&
name|ctx
operator|->
name|out
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|rc
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return
name|rc
return|;
block|}
comment|/* NGX_OK */
if|if
condition|(
name|ctx
operator|->
name|incoming
operator|==
name|NULL
condition|)
block|{
return|return
name|rc
return|;
block|}
block|}
comment|/* copy the first hunk or its part from the chain ctx->incoming            to our hunk and pass it to the next filter */
do|do
block|{
name|rc
operator|=
name|ngx_http_output_filter_copy_hunk
argument_list|(
name|ctx
operator|->
name|hunk
argument_list|,
name|ctx
operator|->
name|incoming
operator|->
name|hunk
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|rc
return|;
block|}
if|#
directive|if
operator|(
name|NGX_FILE_AIO_READ
operator|)
if|if
condition|(
name|rc
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return
name|rc
return|;
block|}
endif|#
directive|endif
name|ctx
operator|->
name|out
operator|.
name|hunk
operator|=
name|ctx
operator|->
name|hunk
expr_stmt|;
name|ctx
operator|->
name|out
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
name|rc
operator|=
name|next_filter
argument_list|(
name|r
argument_list|,
operator|&
name|ctx
operator|->
name|out
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|rc
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return
name|rc
return|;
block|}
comment|/* NGX_OK */
comment|/* set our hunk free */
name|ctx
operator|->
name|hunk
operator|->
name|pos
operator|.
name|mem
operator|=
name|ctx
operator|->
name|hunk
operator|->
name|last
operator|.
name|mem
operator|=
name|ctx
operator|->
name|hunk
operator|->
name|start
expr_stmt|;
comment|/* repeat until we will have copied the whole first hunk from            the chain ctx->incoming */
block|}
do|while
condition|(
name|ctx
operator|->
name|incoming
operator|->
name|hunk
operator|->
name|pos
operator|.
name|mem
operator|<
name|ctx
operator|->
name|incoming
operator|->
name|hunk
operator|->
name|last
operator|.
name|mem
condition|)
do|;
comment|/* delete the completed hunk from the incoming chain */
name|ctx
operator|->
name|incoming
operator|=
name|ctx
operator|->
name|incoming
operator|->
name|next
expr_stmt|;
comment|/* repeat until we will have processed the whole chain ctx->incoming */
block|}
do|while
condition|(
name|ctx
operator|->
name|incoming
condition|)
do|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_output_filter_copy_hunk (ngx_hunk_t * dst,ngx_hunk_t * src)
specifier|static
name|int
name|ngx_http_output_filter_copy_hunk
parameter_list|(
name|ngx_hunk_t
modifier|*
name|dst
parameter_list|,
name|ngx_hunk_t
modifier|*
name|src
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|,
name|size
decl_stmt|;
name|size
operator|=
name|src
operator|->
name|last
operator|.
name|mem
operator|-
name|src
operator|->
name|pos
operator|.
name|mem
expr_stmt|;
if|if
condition|(
name|size
operator|>
operator|(
name|dst
operator|->
name|end
operator|-
name|dst
operator|->
name|pos
operator|.
name|mem
operator|)
condition|)
block|{
name|size
operator|=
name|dst
operator|->
name|end
operator|-
name|dst
operator|->
name|pos
operator|.
name|mem
expr_stmt|;
block|}
if|if
condition|(
name|src
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
condition|)
block|{
name|n
operator|=
name|ngx_read_file
argument_list|(
name|src
operator|->
name|file
argument_list|,
name|dst
operator|->
name|pos
operator|.
name|mem
argument_list|,
name|size
argument_list|,
name|src
operator|->
name|pos
operator|.
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|n
return|;
block|}
if|#
directive|if
operator|(
name|NGX_FILE_AIO_READ
operator|)
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return
name|n
return|;
block|}
endif|#
directive|endif
if|if
condition|(
name|n
operator|!=
name|size
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|src
operator|->
name|file
operator|->
name|log
argument_list|,
literal|0
argument_list|,
name|ngx_read_file_n
literal|" reads only %d of %d from file"
argument_list|,
name|n
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
name|src
operator|->
name|pos
operator|.
name|mem
operator|+=
name|n
expr_stmt|;
name|dst
operator|->
name|last
operator|.
name|mem
operator|+=
name|n
expr_stmt|;
block|}
else|else
block|{
name|ngx_memcpy
argument_list|(
name|src
operator|->
name|pos
operator|.
name|mem
argument_list|,
name|dst
operator|->
name|pos
operator|.
name|mem
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|src
operator|->
name|pos
operator|.
name|mem
operator|+=
name|size
expr_stmt|;
name|dst
operator|->
name|last
operator|.
name|mem
operator|+=
name|size
expr_stmt|;
block|}
if|if
condition|(
name|src
operator|->
name|type
operator|&
name|NGX_HUNK_LAST
operator|&&
name|src
operator|->
name|pos
operator|.
name|mem
operator|==
name|src
operator|->
name|last
operator|.
name|mem
condition|)
block|{
name|dst
operator|->
name|type
operator||=
name|NGX_HUNK_LAST
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_output_filter_create_conf (ngx_pool_t * pool)
specifier|static
name|void
modifier|*
name|ngx_http_output_filter_create_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_http_output_filter_conf_t
modifier|*
name|conf
decl_stmt|;
name|ngx_test_null
argument_list|(
name|conf
argument_list|,
name|ngx_pcalloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_output_filter_conf_t
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|conf
operator|->
name|hunk_size
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|conf
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_output_filter_merge_conf (ngx_pool_t * pool,void * parent,void * child)
specifier|static
name|char
modifier|*
name|ngx_http_output_filter_merge_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|void
modifier|*
name|parent
parameter_list|,
name|void
modifier|*
name|child
parameter_list|)
block|{
name|ngx_http_output_filter_conf_t
modifier|*
name|prev
init|=
operator|(
name|ngx_http_output_filter_conf_t
operator|*
operator|)
name|parent
decl_stmt|;
name|ngx_http_output_filter_conf_t
modifier|*
name|conf
init|=
operator|(
name|ngx_http_output_filter_conf_t
operator|*
operator|)
name|child
decl_stmt|;
name|ngx_conf_size_merge
argument_list|(
name|conf
operator|->
name|hunk_size
argument_list|,
name|prev
operator|->
name|hunk_size
argument_list|,
literal|32768
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

