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

begin_decl_stmt
DECL|variable|ngx_http_status_commands
specifier|static
name|ngx_command_t
name|ngx_http_status_commands
index|[]
init|=
block|{
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_status_module_ctx
name|ngx_http_module_t
name|ngx_http_status_module_ctx
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
name|ngx_http_status_create_loc_conf
block|,
comment|/* create location configration */
name|ngx_http_status_merge_loc_conf
comment|/* merge location configration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_status_module
name|ngx_module_t
name|ngx_http_status_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_status_module_ctx
block|,
comment|/* module context */
name|ngx_http_status_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|ngx_http_status_init
block|,
comment|/* init module */
name|NULL
comment|/* init child */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|http_states
specifier|static
name|char
name|http_states
init|=
literal|"IRPCUWLK"
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_status_handler (ngx_http_request_t * r)
name|int
name|ngx_http_status_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_int_t
name|i
decl_stmt|,
name|http
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_http_request_t
modifier|*
name|sr
decl_stmt|;
name|c
operator|=
name|ngx_cycle
operator|->
name|connections
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ngx_cycle
operator|->
name|connection_n
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|module
operator|!=
name|http
operator|||
name|c
index|[
name|i
index|]
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|data
operator|==
name|NULL
operator|&&
name|c
index|[
name|i
index|]
operator|.
name|fd
operator|!=
operator|-
literal|1
condition|)
block|{
literal|'A'
block|}
name|sr
operator|=
name|c
index|[
name|i
index|]
operator|.
name|data
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

