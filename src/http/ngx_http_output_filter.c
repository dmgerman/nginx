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
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon2b3149f50108
typedef|typedef
struct|struct
block|{
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
DECL|typedef|ngx_http_output_filter_conf_t
block|}
name|ngx_http_output_filter_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b3149f50208
typedef|typedef
struct|struct
block|{
comment|/*      * NOTE: we do not need now to store hunk in ctx,      * it's needed for the future NGX_FILE_AIO_READ support only      */
DECL|member|hunk
name|ngx_hunk_t
modifier|*
name|hunk
decl_stmt|;
DECL|member|in
name|ngx_chain_t
modifier|*
name|in
decl_stmt|;
DECL|member|out
name|ngx_chain_t
modifier|*
name|out
decl_stmt|;
DECL|member|last_out
name|ngx_chain_t
modifier|*
modifier|*
name|last_out
decl_stmt|;
DECL|member|free
name|ngx_chain_t
modifier|*
name|free
decl_stmt|;
DECL|member|busy
name|ngx_chain_t
modifier|*
name|busy
decl_stmt|;
DECL|member|hunks
name|int
name|hunks
decl_stmt|;
DECL|typedef|ngx_http_output_filter_ctx_t
block|}
name|ngx_http_output_filter_ctx_t
typedef|;
end_typedef

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
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_output_filter_merge_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
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
literal|"output_buffers"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_TAKE2
block|,
name|ngx_conf_set_bufs_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_output_filter_conf_t
argument_list|,
name|bufs
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
DECL|variable|ngx_http_output_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_output_filter_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|NULL
block|,
comment|/* create server configuration */
name|NULL
block|,
comment|/* merge server configuration */
name|ngx_http_output_filter_create_conf
block|,
comment|/* create location configuration */
name|ngx_http_output_filter_merge_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_output_filter_module
name|ngx_module_t
name|ngx_http_output_filter_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_output_filter_module_ctx
block|,
comment|/* module context */
name|ngx_http_output_filter_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
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

begin_define
DECL|macro|ngx_next_filter
define|#
directive|define
name|ngx_next_filter
value|(*ngx_http_top_body_filter)
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
value|(!ngx_hunk_special(hunk)                                      \&& (((r->filter& NGX_HTTP_FILTER_NEED_IN_MEMORY)            \&& (hunk->type& NGX_HUNK_IN_MEMORY) == 0)             \                  || ((r->filter& NGX_HTTP_FILTER_NEED_TEMP)              \&& (hunk->type& (NGX_HUNK_MEMORY|NGX_HUNK_MMAP)))))
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
decl_stmt|,
name|last
decl_stmt|;
name|ssize_t
name|size
decl_stmt|;
name|ngx_chain_t
name|out
decl_stmt|,
modifier|*
name|ce
decl_stmt|,
modifier|*
modifier|*
name|le
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
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|ctx
operator|->
name|out
expr_stmt|;
block|}
comment|/*      * the short path for the case when the chain ctx->in is empty      * and there's no hunk or the hunk does not require the copy      */
if|if
condition|(
name|ctx
operator|->
name|in
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
name|ngx_next_filter
argument_list|(
name|r
argument_list|,
name|NULL
argument_list|)
return|;
block|}
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
name|out
operator|.
name|hunk
operator|=
name|hunk
expr_stmt|;
name|out
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
return|return
name|ngx_next_filter
argument_list|(
name|r
argument_list|,
operator|&
name|out
argument_list|)
return|;
block|}
block|}
comment|/* add the incoming hunk to the chain ctx->in */
if|if
condition|(
name|hunk
condition|)
block|{
name|le
operator|=
operator|&
name|ctx
operator|->
name|in
expr_stmt|;
for|for
control|(
name|ce
operator|=
name|ctx
operator|->
name|in
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
name|le
operator|=
operator|&
name|ce
operator|->
name|next
expr_stmt|;
block|}
name|ngx_add_hunk_to_chain
argument_list|(
name|ce
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
operator|*
name|le
operator|=
name|ce
expr_stmt|;
block|}
name|conf
operator|=
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
name|last
operator|=
name|NGX_NONE
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
while|while
condition|(
name|ctx
operator|->
name|in
condition|)
block|{
if|if
condition|(
operator|!
name|need_to_copy
argument_list|(
name|r
argument_list|,
name|ctx
operator|->
name|in
operator|->
name|hunk
argument_list|)
condition|)
block|{
comment|/* move the chain entry to the chain ctx->out */
name|ce
operator|=
name|ctx
operator|->
name|in
expr_stmt|;
name|ctx
operator|->
name|in
operator|=
name|ce
operator|->
name|next
expr_stmt|;
operator|*
name|ctx
operator|->
name|last_out
operator|=
name|ce
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|ce
operator|->
name|next
expr_stmt|;
name|ce
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|ctx
operator|->
name|hunk
operator|==
name|NULL
condition|)
block|{
comment|/* get the free hunk */
if|if
condition|(
name|ctx
operator|->
name|free
condition|)
block|{
name|ctx
operator|->
name|hunk
operator|=
name|ctx
operator|->
name|free
operator|->
name|hunk
expr_stmt|;
name|ctx
operator|->
name|free
operator|=
name|ctx
operator|->
name|free
operator|->
name|next
expr_stmt|;
block|}
if|else if
condition|(
name|ctx
operator|->
name|hunks
operator|<
name|conf
operator|->
name|bufs
operator|.
name|num
condition|)
block|{
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
name|conf
operator|->
name|bufs
operator|.
name|size
argument_list|,
literal|0
argument_list|,
literal|0
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
name|ctx
operator|->
name|hunks
operator|++
expr_stmt|;
block|}
else|else
block|{
break|break;
block|}
block|}
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
name|in
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
if|if
condition|(
name|ctx
operator|->
name|in
operator|->
name|hunk
operator|->
name|type
operator|&
name|NGX_HUNK_IN_MEMORY
condition|)
block|{
name|size
operator|=
name|ctx
operator|->
name|in
operator|->
name|hunk
operator|->
name|last
operator|-
name|ctx
operator|->
name|in
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
block|}
else|else
block|{
name|size
operator|=
operator|(
name|size_t
operator|)
operator|(
name|ctx
operator|->
name|in
operator|->
name|hunk
operator|->
name|file_last
operator|-
name|ctx
operator|->
name|in
operator|->
name|hunk
operator|->
name|file_pos
operator|)
expr_stmt|;
block|}
comment|/* delete the completed hunk from the chain ctx->in */
if|if
condition|(
name|size
operator|==
literal|0
condition|)
block|{
name|ctx
operator|->
name|in
operator|=
name|ctx
operator|->
name|in
operator|->
name|next
expr_stmt|;
block|}
name|ngx_add_hunk_to_chain
argument_list|(
name|ce
argument_list|,
name|ctx
operator|->
name|hunk
argument_list|,
name|r
operator|->
name|pool
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
operator|*
name|ctx
operator|->
name|last_out
operator|=
name|ce
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|ce
operator|->
name|next
expr_stmt|;
name|ctx
operator|->
name|hunk
operator|=
name|NULL
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|ctx
operator|->
name|out
operator|==
name|NULL
operator|&&
name|last
operator|!=
name|NGX_NONE
condition|)
block|{
return|return
name|last
return|;
block|}
name|last
operator|=
name|ngx_next_filter
argument_list|(
name|r
argument_list|,
name|ctx
operator|->
name|out
argument_list|)
expr_stmt|;
name|ngx_chain_update_chains
argument_list|(
operator|&
name|ctx
operator|->
name|free
argument_list|,
operator|&
name|ctx
operator|->
name|busy
argument_list|,
operator|&
name|ctx
operator|->
name|out
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|last_out
operator|=
operator|&
name|ctx
operator|->
name|out
expr_stmt|;
block|}
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
if|if
condition|(
name|src
operator|->
name|type
operator|&
name|NGX_HUNK_IN_MEMORY
condition|)
block|{
name|size
operator|=
name|src
operator|->
name|last
operator|-
name|src
operator|->
name|pos
expr_stmt|;
block|}
else|else
block|{
name|size
operator|=
operator|(
name|size_t
operator|)
operator|(
name|src
operator|->
name|file_last
operator|-
name|src
operator|->
name|file_pos
operator|)
expr_stmt|;
block|}
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
expr_stmt|;
block|}
if|if
condition|(
name|src
operator|->
name|type
operator|&
name|NGX_HUNK_IN_MEMORY
condition|)
block|{
name|ngx_memcpy
argument_list|(
name|dst
operator|->
name|pos
argument_list|,
name|src
operator|->
name|pos
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|src
operator|->
name|pos
operator|+=
name|size
expr_stmt|;
name|dst
operator|->
name|last
operator|+=
name|size
expr_stmt|;
if|if
condition|(
name|src
operator|->
name|type
operator|&
name|NGX_HUNK_FILE
condition|)
block|{
name|src
operator|->
name|file_pos
operator|+=
name|size
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|src
operator|->
name|type
operator|&
name|NGX_HUNK_LAST
operator|)
operator|&&
name|src
operator|->
name|pos
operator|==
name|src
operator|->
name|last
condition|)
block|{
name|dst
operator|->
name|type
operator||=
name|NGX_HUNK_LAST
expr_stmt|;
block|}
block|}
else|else
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
argument_list|,
name|size
argument_list|,
name|src
operator|->
name|file_pos
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
name|ngx_log_debug
argument_list|(
argument|src->file->log
argument_list|,
literal|"READ: %qd:%qd %X:%X %X:%X"
argument|_               src->file_pos _ src->file_last _               dst->pos _ dst->last _ dst->start _ dst->end
argument_list|)
empty_stmt|;
block|}
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
name|file_pos
operator|+=
name|n
expr_stmt|;
name|dst
operator|->
name|last
operator|+=
name|n
expr_stmt|;
if|if
condition|(
operator|(
name|src
operator|->
name|type
operator|&
name|NGX_HUNK_LAST
operator|)
operator|&&
name|src
operator|->
name|file_pos
operator|==
name|src
operator|->
name|file_last
condition|)
block|{
name|dst
operator|->
name|type
operator||=
name|NGX_HUNK_LAST
expr_stmt|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_output_filter_create_conf (ngx_conf_t * cf)
specifier|static
name|void
modifier|*
name|ngx_http_output_filter_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
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
name|ngx_palloc
argument_list|(
name|cf
operator|->
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
name|bufs
operator|.
name|num
operator|=
literal|0
expr_stmt|;
return|return
name|conf
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_output_filter_merge_conf (ngx_conf_t * cf,void * parent,void * child)
specifier|static
name|char
modifier|*
name|ngx_http_output_filter_merge_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
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
name|parent
decl_stmt|;
name|ngx_http_output_filter_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_bufs_value
argument_list|(
name|conf
operator|->
name|bufs
argument_list|,
name|prev
operator|->
name|bufs
argument_list|,
literal|2
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

