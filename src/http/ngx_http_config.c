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
file|<ngx_config_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_core.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_write_filter.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_output_filter.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_index_handler.h>
end_include

begin_comment
comment|/* STUB */
end_comment

begin_decl_stmt
DECL|variable|ngx_srv_conf
name|void
modifier|*
modifier|*
name|ngx_srv_conf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_loc_conf
name|void
modifier|*
modifier|*
name|ngx_loc_conf
decl_stmt|;
end_decl_stmt

begin_comment
comment|/**/
end_comment

begin_function_decl
specifier|static
name|int
name|ngx_http_block
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|char
modifier|*
name|dummy
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|null_loc_conf
name|void
modifier|*
name|null_loc_conf
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_commands
specifier|static
name|ngx_command_t
name|ngx_http_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"http"
argument_list|)
block|,
name|NGX_CONF_BLOCK
operator||
name|NGX_CONF_NOARGS
block|,
name|ngx_http_block
block|,
literal|0
block|,
literal|0
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
DECL|variable|ngx_http_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_module_ctx
init|=
block|{
name|NGX_HTTP_MODULE
block|,
name|NULL
block|,
comment|/* create server config */
name|NULL
block|,
comment|/* create location config */
name|NULL
block|,
comment|/* translate handler */
name|NULL
block|,
comment|/* output header filter */
name|NULL
block|,
comment|/* next output header filter */
name|NULL
block|,
comment|/* output body filter */
name|NULL
comment|/* next output body filter */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_module
name|ngx_module_t
name|ngx_http_module
init|=
block|{
operator|&
name|ngx_http_module_ctx
block|,
comment|/* module context */
name|ngx_http_commands
block|,
comment|/* module directives */
literal|0
block|,
comment|/* module type */
name|NULL
comment|/* init module */
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_block (ngx_conf_t * cf,ngx_command_t * cmd,char * dummy)
specifier|static
name|int
name|ngx_http_block
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|char
modifier|*
name|dummy
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|j
decl_stmt|;
name|ngx_http_module_t
modifier|*
name|module
decl_stmt|;
name|ngx_http_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|i
index|]
operator|->
name|type
operator|!=
name|NGX_HTTP_MODULE_TYPE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
operator|(
name|ngx_http_module_t
operator|*
operator|)
name|ngx_modules
index|[
name|i
index|]
operator|->
name|ctx
expr_stmt|;
name|module
operator|->
name|index
operator|=
name|i
expr_stmt|;
block|}
name|ngx_http_max_module
operator|=
name|i
expr_stmt|;
name|ngx_test_null
argument_list|(
name|null_loc_conf
argument_list|,
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|void
operator|*
argument_list|)
operator|*
name|ngx_http_max_module
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|srv_conf
operator|=
name|NULL
expr_stmt|;
name|ctx
operator|->
name|loc_conf
operator|=
name|null_loc_conf
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|j
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|i
index|]
operator|->
name|type
operator|!=
name|NGX_HTTP_MODULE_TYPE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
operator|(
name|ngx_http_module_t
operator|*
operator|)
name|ngx_modules
index|[
name|i
index|]
operator|->
name|ctx
expr_stmt|;
name|module
operator|->
name|index
operator|=
name|i
expr_stmt|;
if|if
condition|(
name|module
operator|->
name|create_loc_conf
condition|)
block|{
name|ngx_test_null
argument_list|(
name|null_loc_conf
argument_list|,
name|module
operator|->
name|create_loc_conf
argument_list|(
name|cf
operator|->
name|pool
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|j
operator|++
expr_stmt|;
block|}
block|}
name|cf
operator|->
name|ctx
operator|=
name|ctx
expr_stmt|;
name|cf
operator|->
name|type
operator|=
name|NGX_HTTP_MODULE_TYPE
expr_stmt|;
return|return
name|ngx_conf_parse
argument_list|(
name|cf
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|int ngx_server_block(ngx_conf_t *cf) {     ngx_http_conf_ctx_t  *ctx, *prev;      ngx_test_null(ctx,                   ngx_pcalloc(cf->pool, sizeof(ngx_http_conf_ctx_t)),                   NGX_ERROR);
comment|/* server config */
end_comment

begin_comment
unit|ngx_test_null(ctx->srv_conf,                   ngx_pcalloc(cf->pool, sizeof(void *) * ngx_max_module),                   NGX_ERROR);
comment|/* server location config */
end_comment

begin_if
unit|ngx_test_null(ctx->loc_conf,                   ngx_pcalloc(cf->pool, sizeof(void *) * ngx_max_module),                   NGX_ERROR);       for (i = 0; modules[i]; i++) {         if (modules[i]->create_srv_conf)             ngx_test_null(ctx->srv_conf[i],                           modules[i]->create_srv_conf(cf->pool),                           NGX_ERROR);          if (modules[i]->create_loc_conf)             ngx_test_null(ctx->loc_conf[i],                           modules[i]->create_loc_conf(cf->pool),                           NGX_ERROR);     }      prev = cf->ctx;     cf->ctx = ctx;     rc = ngx_conf_parse(cf);     cf->ctx = prev;      if (loc == NGX_ERROR)         return NGX_ERROR;      for (i = 0; modules[i]; i++) {
if|#
directive|if
literal|0
end_if

begin_endif
unit|if (modules[i]->merge_srv_conf)             if (modules[i]->merge_srv_conf(cf->pool,                                            prev->srv_conf, ctx->srv_conf)                                                                   == NGX_ERROR)                 return NGX_ERROR;
endif|#
directive|endif
end_endif

begin_endif
unit|if (modules[i]->init_srv_conf)             if (modules[i]->init_srv_conf(cf->pool, ctx->srv_conf) == NGX_ERROR)                 return NGX_ERROR;          if (modules[i]->merge_loc_conf)             if (modules[i]->merge_loc_conf(cf->pool,                                            prev->loc_conf, ctx->loc_conf)                                                                   == NGX_ERROR)                 return NGX_ERROR;              for (array) {                 if (modules[i]->merge_loc_conf(cf->pool,                                                ctx->loc_conf, loc->loc_conf)                                                                   == NGX_ERROR)                 return NGX_ERROR;             }         }     }      return NGX_OK; }  int ngx_location_block(ngx_conf_t *cf) {     ngx_http_conf_ctx_t  *ctx, *prev;      ngx_test_null(ctx, ngx_pcalloc(cf->pool, sizeof(ngx_http_conf_ctx_t)),                   NGX_ERROR);      ctx->srv_conf = cf->ctx->srv_conf;      ngx_test_null(ctx->loc_conf,                   ngx_pcalloc(cf->pool, sizeof(void *) * ngx_max_module),                   NGX_ERROR);      for (i = 0; modules[i]; i++) {         if (modules[i]->create_loc_conf)             ngx_test_null(ctx->loc_conf[i],                           modules[i]->create_loc_conf(cf->pool),                           NGX_ERROR);          if (ngx_http_core_module.index == i)             ctx->loc_conf[i].location = cf->args[0];     }      push      return ngx_conf_parse(cf); }
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_http_config_modules (ngx_pool_t * pool,ngx_module_t ** modules)
name|int
name|ngx_http_config_modules
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_module_t
modifier|*
modifier|*
name|modules
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
name|ngx_http_module_t
modifier|*
name|module
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|modules
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|modules
index|[
name|i
index|]
operator|->
name|type
operator|!=
name|NGX_HTTP_MODULE_TYPE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
operator|(
name|ngx_http_module_t
operator|*
operator|)
name|modules
index|[
name|i
index|]
operator|->
name|ctx
expr_stmt|;
name|module
operator|->
name|index
operator|=
name|i
expr_stmt|;
block|}
name|ngx_http_max_module
operator|=
name|i
expr_stmt|;
if|#
directive|if
literal|0
block_content|ngx_test_null(ngx_srv_conf,                   ngx_pcalloc(pool, sizeof(void *) * ngx_http_max_module),                   NGX_ERROR);     ngx_test_null(ngx_loc_conf,                   ngx_pcalloc(pool, sizeof(void *) * ngx_http_max_module),                   NGX_ERROR);      for (i = 0; modules[i]; i++) {         if (modules[i]->create_srv_conf)             ngx_srv_conf[i] = modules[i]->create_srv_conf(pool);          if (modules[i]->create_loc_conf)             ngx_loc_conf[i] = modules[i]->create_loc_conf(pool);     }
endif|#
directive|endif
block|}
end_function

begin_function
DECL|function|ngx_http_init_filters (ngx_pool_t * pool,ngx_module_t ** modules)
name|void
name|ngx_http_init_filters
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_module_t
modifier|*
modifier|*
name|modules
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
name|ngx_http_module_t
modifier|*
name|module
decl_stmt|;
name|int
function_decl|(
modifier|*
name|ohf
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
name|int
function_decl|(
modifier|*
name|obf
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|ch
parameter_list|)
function_decl|;
name|ohf
operator|=
name|NULL
expr_stmt|;
name|obf
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|modules
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|modules
index|[
name|i
index|]
operator|->
name|type
operator|!=
name|NGX_HTTP_MODULE_TYPE
condition|)
block|{
continue|continue;
block|}
name|module
operator|=
operator|(
name|ngx_http_module_t
operator|*
operator|)
name|modules
index|[
name|i
index|]
operator|->
name|ctx
expr_stmt|;
if|if
condition|(
name|module
operator|->
name|output_header_filter
condition|)
block|{
name|module
operator|->
name|next_output_header_filter
operator|=
name|ohf
expr_stmt|;
name|ohf
operator|=
name|module
operator|->
name|output_header_filter
expr_stmt|;
block|}
if|if
condition|(
name|module
operator|->
name|output_body_filter
condition|)
block|{
name|module
operator|->
name|next_output_body_filter
operator|=
name|obf
expr_stmt|;
name|obf
operator|=
name|module
operator|->
name|output_body_filter
expr_stmt|;
block|}
block|}
name|ngx_http_top_header_filter
operator|=
name|ohf
expr_stmt|;
block|}
end_function

end_unit

