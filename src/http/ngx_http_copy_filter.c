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
DECL|struct|__anon2c5c1cd40108
typedef|typedef
struct|struct
block|{
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
DECL|typedef|ngx_http_copy_filter_conf_t
block|}
name|ngx_http_copy_filter_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_copy_filter_create_conf
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
name|ngx_http_copy_filter_merge_conf
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

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_copy_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_copy_filter_commands
specifier|static
name|ngx_command_t
name|ngx_http_copy_filter_commands
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
name|ngx_http_copy_filter_conf_t
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
DECL|variable|ngx_http_copy_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_copy_filter_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* pre conf */
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
name|ngx_http_copy_filter_create_conf
block|,
comment|/* create location configuration */
name|ngx_http_copy_filter_merge_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_copy_filter_module
name|ngx_module_t
name|ngx_http_copy_filter_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_copy_filter_module_ctx
block|,
comment|/* module context */
name|ngx_http_copy_filter_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|ngx_http_copy_filter_init
block|,
comment|/* init module */
name|NULL
comment|/* init process */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_next_filter
specifier|static
name|ngx_http_output_body_filter_pt
name|ngx_http_next_filter
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_copy_filter (ngx_http_request_t * r,ngx_chain_t * in)
name|ngx_int_t
name|ngx_http_copy_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
block|{
name|ngx_output_chain_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ngx_http_copy_filter_conf_t
modifier|*
name|conf
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|connection
operator|->
name|write
operator|->
name|error
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
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
name|ngx_http_copy_filter_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|==
name|NULL
condition|)
block|{
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
name|ngx_http_copy_filter_module
argument_list|)
expr_stmt|;
name|ngx_http_create_ctx
argument_list|(
name|r
argument_list|,
name|ctx
argument_list|,
name|ngx_http_copy_filter_module
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_output_chain_ctx_t
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|sendfile
operator|=
name|r
operator|->
name|sendfile
expr_stmt|;
name|ctx
operator|->
name|need_in_memory
operator|=
name|r
operator|->
name|filter_need_in_memory
expr_stmt|;
name|ctx
operator|->
name|need_in_temp
operator|=
name|r
operator|->
name|filter_need_temporary
expr_stmt|;
name|ctx
operator|->
name|pool
operator|=
name|r
operator|->
name|pool
expr_stmt|;
name|ctx
operator|->
name|bufs
operator|=
name|conf
operator|->
name|bufs
expr_stmt|;
name|ctx
operator|->
name|tag
operator|=
operator|(
name|ngx_buf_tag_t
operator|)
operator|&
name|ngx_http_copy_filter_module
expr_stmt|;
name|ctx
operator|->
name|output_filter
operator|=
operator|(
name|ngx_output_chain_filter_pt
operator|)
name|ngx_http_next_filter
expr_stmt|;
name|ctx
operator|->
name|filter_ctx
operator|=
name|r
expr_stmt|;
block|}
return|return
name|ngx_output_chain
argument_list|(
name|ctx
argument_list|,
name|in
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_copy_filter_create_conf (ngx_conf_t * cf)
specifier|static
name|void
modifier|*
name|ngx_http_copy_filter_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_copy_filter_conf_t
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
name|ngx_http_copy_filter_conf_t
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
DECL|function|ngx_http_copy_filter_merge_conf (ngx_conf_t * cf,void * parent,void * child)
specifier|static
name|char
modifier|*
name|ngx_http_copy_filter_merge_conf
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
name|ngx_http_copy_filter_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_copy_filter_conf_t
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
literal|1
argument_list|,
literal|32768
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_copy_filter_init (ngx_cycle_t * cycle)
specifier|static
name|ngx_int_t
name|ngx_http_copy_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_http_next_filter
operator|=
name|ngx_http_top_body_filter
expr_stmt|;
name|ngx_http_top_body_filter
operator|=
name|ngx_http_copy_filter
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

