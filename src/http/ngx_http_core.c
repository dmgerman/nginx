begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_config_command.h>
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

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_core_create_srv_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_core_create_loc_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_core_commands
specifier|static
name|ngx_command_t
name|ngx_http_core_commands
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_core_module
name|ngx_http_module_t
name|ngx_http_core_module
init|=
block|{
name|NGX_HTTP_MODULE
block|,
name|ngx_http_core_create_srv_conf
block|,
comment|/* create server config */
name|ngx_http_core_create_loc_conf
block|,
comment|/* create location config */
name|ngx_http_core_commands
block|,
comment|/* module directives */
name|NULL
block|,
comment|/* init module */
name|NULL
comment|/* init output body filter */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_core_commands
specifier|static
name|ngx_command_t
name|ngx_http_core_commands
index|[]
init|=
block|{
block|{
literal|"send_timeout"
block|,
name|ngx_conf_set_time_slot
block|,
name|offsetof
argument_list|(
name|ngx_http_core_loc_conf_t
argument_list|,
name|send_timeout
argument_list|)
block|,
name|NGX_HTTP_LOC_CONF
block|,
name|NGX_CONF_TAKE1
block|,
literal|"set timeout for sending response"
block|}
block|,
block|{
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_core_create_srv_conf (ngx_pool_t * pool)
specifier|static
name|void
modifier|*
name|ngx_http_core_create_srv_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_http_core_srv_conf_t
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
name|ngx_http_core_srv_conf_t
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|conf
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_core_create_loc_conf (ngx_pool_t * pool)
specifier|static
name|void
modifier|*
name|ngx_http_core_create_loc_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_http_core_loc_conf_t
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
name|ngx_http_core_loc_conf_t
argument_list|)
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|conf
operator|->
name|send_timeout
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|conf
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static void *ngx_http_core_create_conf(ngx_pool_t *pool) {      ngx_test_null(conf, ngx_palloc(pool, sizeof(ngx_http_core_conf_t)), NULL);      ngx_test_null(conf->srv, ngx_http_core_create_srv_conf_t(pool), NULL);     ngx_test_null(conf->loc, ngx_http_core_create_loc_conf_t(pool), NULL);     conf->parent =      conf->next = NULL; }
endif|#
directive|endif
end_endif

end_unit

