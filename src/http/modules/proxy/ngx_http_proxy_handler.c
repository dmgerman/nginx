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
file|<ngx_event.h>
end_include

begin_comment
comment|/* STUB */
end_comment

begin_include
include|#
directive|include
file|<ngx_event_connect.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_proxy_handler.h>
end_include

begin_decl_stmt
DECL|variable|ngx_http_proxy_commands
specifier|static
name|ngx_command_t
name|ngx_http_proxy_commands
index|[]
init|=
block|{
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_proxy_module_ctx
name|ngx_http_module_t
name|ngx_http_proxy_module_ctx
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
if|#
directive|if
literal|0
block|ngx_http_proxy_create_conf,
comment|/* create location configration */
block|ngx_http_proxy_merge_conf
comment|/* merge location configration */
endif|#
directive|endif
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_proxy_module
name|ngx_module_t
name|ngx_http_proxy_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_proxy_module_ctx
block|,
comment|/* module context */
name|ngx_http_proxy_commands
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

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_http_proxy_handler (ngx_http_request_t * r)
name|int
name|ngx_http_proxy_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|ngx_http_proxy_ctx_t
modifier|*
name|p
decl_stmt|;
name|ngx_peer_connection_t
modifier|*
name|pc
decl_stmt|;
name|ngx_http_create_ctx
argument_list|(
name|r
argument_list|,
name|p
argument_list|,
name|ngx_http_proxy_module
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_proxy_ctx_t
argument_list|)
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
expr_stmt|;
name|p
operator|->
name|action
operator|=
literal|"connecting to upstream"
expr_stmt|;
name|p
operator|->
name|request
operator|=
name|r
expr_stmt|;
if|#
directive|if
literal|0
block_content|pc->peers = lcf->peers;
endif|#
directive|endif
name|p
operator|->
name|upstream
operator|.
name|log
operator|=
name|r
operator|->
name|connection
operator|->
name|log
expr_stmt|;
do|do
block|{
name|rc
operator|=
name|ngx_event_connect_peer
argument_list|(
operator|&
name|p
operator|->
name|upstream
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
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_OK
condition|)
block|{
name|send_proxy_request
argument_list|(
name|p
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|rc
operator|==
name|NGX_AGAIN
operator|&&
name|p
operator|->
name|upstream
operator|.
name|connection
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
block|}
do|while
condition|(
name|p
operator|->
name|upstream
operator|.
name|tries
condition|)
do|;
return|return
name|NGX_HTTP_BAD_GATEWAY
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|ngx_http_proxy_connect()     do {         ngx_event_connect_peer()         if error             return error         if ok             return ok         if again             return again
comment|/* next */
end_comment

begin_endif
unit|while (tries) }   ngx_http_proxy_send_request(ngx_event_t *wev)     for ( ;; ) {        send        if ok           ???        if again           return        if error           close           ngx_http_proxy_connect()           if ok               continue           if error               return           if again               return     }
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_http_proxy_log_error (void * data,char * buf,size_t len)
specifier|static
name|size_t
name|ngx_http_proxy_log_error
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|ngx_http_proxy_ctx_t
modifier|*
name|p
init|=
name|data
decl_stmt|;
return|return
name|ngx_snprintf
argument_list|(
name|buf
argument_list|,
name|len
argument_list|,
literal|" while %s, upstream: %s, client: %s, URL: %s"
argument_list|,
name|p
operator|->
name|action
argument_list|,
name|p
operator|->
name|upstream
operator|.
name|peers
operator|->
name|peers
index|[
name|p
operator|->
name|upstream
operator|.
name|cur_peer
index|]
operator|.
name|addr_port_text
operator|.
name|data
argument_list|,
name|p
operator|->
name|request
operator|->
name|connection
operator|->
name|addr_text
operator|.
name|data
argument_list|,
name|p
operator|->
name|request
operator|->
name|unparsed_uri
operator|.
name|data
argument_list|)
return|;
block|}
end_function

end_unit

