begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_include
include|#
directive|include
file|<ngx_listen.h>
end_include

begin_include
include|#
directive|include
file|<ngx_inet.h>
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
file|<ngx_http_core_module.h>
end_include

begin_function_decl
specifier|static
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
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
DECL|variable|ngx_http_max_module
name|int
name|ngx_http_max_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_servers
name|ngx_array_t
name|ngx_http_servers
decl_stmt|;
end_decl_stmt

begin_comment
DECL|variable|ngx_http_servers
comment|/* array of ngx_http_core_srv_conf_t */
end_comment

begin_decl_stmt
DECL|variable|ngx_http_post_accept_timeout
name|int
name|ngx_http_post_accept_timeout
init|=
literal|30000
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_connection_pool_size
name|int
name|ngx_http_connection_pool_size
init|=
literal|16384
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_request_pool_size
name|int
name|ngx_http_request_pool_size
init|=
literal|16384
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_client_header_timeout
name|int
name|ngx_http_client_header_timeout
init|=
literal|60000
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_client_header_buffer_size
name|int
name|ngx_http_client_header_buffer_size
init|=
literal|1024
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_large_client_header
name|int
name|ngx_http_large_client_header
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_url_in_error_log
name|int
name|ngx_http_url_in_error_log
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_translate_handlers
name|ngx_array_t
name|ngx_http_translate_handlers
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_index_handlers
name|ngx_array_t
name|ngx_http_index_handlers
decl_stmt|;
end_decl_stmt

begin_function_decl
DECL|variable|ngx_http_top_header_filter
name|int
function_decl|(
modifier|*
name|ngx_http_top_header_filter
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
DECL|variable|ngx_http_top_body_filter
name|int
function_decl|(
modifier|*
name|ngx_http_top_body_filter
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
end_function_decl

begin_decl_stmt
DECL|variable|http_name
specifier|static
name|ngx_str_t
name|http_name
init|=
name|ngx_string
argument_list|(
literal|"http"
argument_list|)
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
DECL|variable|ngx_http_module
name|ngx_module_t
name|ngx_http_module
init|=
block|{
literal|0
block|,
comment|/* module index */
operator|&
name|http_name
block|,
comment|/* module context */
name|ngx_http_commands
block|,
comment|/* module directives */
name|NGX_CORE_MODULE_TYPE
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
name|char
modifier|*
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
name|s
decl_stmt|,
name|l
decl_stmt|,
name|p
decl_stmt|,
name|a
decl_stmt|,
name|n
decl_stmt|,
name|start
decl_stmt|;
name|int
name|port_found
decl_stmt|,
name|addr_found
decl_stmt|,
name|virtual_names
decl_stmt|;
name|char
modifier|*
name|rv
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|addr_in
decl_stmt|;
name|ngx_array_t
name|in_ports
decl_stmt|;
name|ngx_listen_t
modifier|*
name|ls
decl_stmt|;
name|ngx_http_module_t
modifier|*
name|module
decl_stmt|;
name|ngx_http_conf_ctx_t
modifier|*
name|ctx
decl_stmt|,
modifier|*
name|prev
decl_stmt|;
name|ngx_http_in_port_t
modifier|*
name|in_port
decl_stmt|;
name|ngx_http_in_addr_t
modifier|*
name|in_addr
decl_stmt|,
modifier|*
name|inaddr
decl_stmt|;
name|ngx_http_core_srv_conf_t
modifier|*
modifier|*
name|cscf
decl_stmt|;
name|ngx_http_listen_t
modifier|*
name|lscf
decl_stmt|;
name|ngx_http_server_name_t
modifier|*
name|s_name
decl_stmt|,
modifier|*
name|name
decl_stmt|;
empty_stmt|;
name|ngx_init_array
argument_list|(
name|ngx_http_servers
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_core_srv_conf_t
operator|*
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|ctx
argument_list|,
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_conf_ctx_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ngx_http_max_module
operator|=
literal|0
expr_stmt|;
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
name|ngx_http_max_module
operator|++
expr_stmt|;
block|}
comment|/* null loc_conf */
name|ngx_test_null
argument_list|(
name|ctx
operator|->
name|loc_conf
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
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
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
if|if
condition|(
name|module
operator|->
name|create_loc_conf
condition|)
block|{
name|ngx_test_null
argument_list|(
name|ctx
operator|->
name|loc_conf
index|[
name|module
operator|->
name|index
index|]
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
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
block|}
block|}
name|prev
operator|=
name|cf
operator|->
name|ctx
expr_stmt|;
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
name|rv
operator|=
name|ngx_conf_parse
argument_list|(
name|cf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|cf
operator|->
name|ctx
operator|=
name|prev
expr_stmt|;
if|if
condition|(
name|rv
operator|!=
name|NGX_CONF_OK
condition|)
return|return
name|rv
return|;
if|#
directive|if
literal|0
comment|/* DEBUG STUFF */
block_content|cscf = (ngx_http_core_srv_conf_t **) ngx_http_servers.elts;     for (s = 0; s< ngx_http_servers.nelts; s++) {         ngx_http_core_loc_conf_t **loc;          ngx_log_debug(cf->log, "srv: %08x" _ cscf[s]);         loc = (ngx_http_core_loc_conf_t **) cscf[s]->locations.elts;         for (l = 0; l< cscf[s]->locations.nelts; l++) {             ngx_log_debug(cf->log, "loc: %08x:%s, %08x:%s" _                           loc[l] _ loc[l]->name.data _&loc[l]->doc_root _ loc[l]->doc_root.data);         }     }
comment|/**/
endif|#
directive|endif
name|ngx_init_array
argument_list|(
name|ngx_http_translate_handlers
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_handler_pt
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ngx_init_array
argument_list|(
name|ngx_http_index_handlers
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|3
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_handler_pt
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
comment|/* create lists of ports, addresses and server names */
name|ngx_init_array
argument_list|(
name|in_ports
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_in_port_t
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|cscf
operator|=
operator|(
name|ngx_http_core_srv_conf_t
operator|*
operator|*
operator|)
name|ngx_http_servers
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|s
operator|=
literal|0
init|;
name|s
operator|<
name|ngx_http_servers
operator|.
name|nelts
condition|;
name|s
operator|++
control|)
block|{
name|lscf
operator|=
operator|(
name|ngx_http_listen_t
operator|*
operator|)
name|cscf
index|[
name|s
index|]
operator|->
name|listen
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|l
operator|=
literal|0
init|;
name|l
operator|<
name|cscf
index|[
name|s
index|]
operator|->
name|listen
operator|.
name|nelts
condition|;
name|l
operator|++
control|)
block|{
name|port_found
operator|=
literal|0
expr_stmt|;
comment|/* AF_INET only */
name|in_port
operator|=
operator|(
name|ngx_http_in_port_t
operator|*
operator|)
name|in_ports
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|p
operator|=
literal|0
init|;
name|p
operator|<
name|in_ports
operator|.
name|nelts
condition|;
name|p
operator|++
control|)
block|{
if|if
condition|(
name|lscf
index|[
name|l
index|]
operator|.
name|port
operator|==
name|in_port
index|[
name|p
index|]
operator|.
name|port
condition|)
block|{
name|port_found
operator|=
literal|1
expr_stmt|;
name|addr_found
operator|=
literal|0
expr_stmt|;
name|in_addr
operator|=
operator|(
name|ngx_http_in_addr_t
operator|*
operator|)
name|in_port
index|[
name|p
index|]
operator|.
name|addr
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|a
operator|=
literal|0
init|;
name|a
operator|<
name|in_port
index|[
name|p
index|]
operator|.
name|addr
operator|.
name|nelts
condition|;
name|a
operator|++
control|)
block|{
if|if
condition|(
name|lscf
index|[
name|l
index|]
operator|.
name|addr
operator|==
name|in_addr
index|[
name|a
index|]
operator|.
name|addr
condition|)
block|{
name|s_name
operator|=
operator|(
name|ngx_http_server_name_t
operator|*
operator|)
name|cscf
index|[
name|s
index|]
operator|->
name|server_names
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|n
operator|=
literal|0
init|;
name|n
operator|<
name|cscf
index|[
name|s
index|]
operator|->
name|server_names
operator|.
name|nelts
condition|;
name|n
operator|++
control|)
block|{
name|ngx_test_null
argument_list|(
name|name
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|in_addr
index|[
name|a
index|]
operator|.
name|names
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|name
operator|->
name|name
operator|=
name|s_name
index|[
name|n
index|]
operator|.
name|name
expr_stmt|;
name|name
operator|->
name|core_srv_conf
operator|=
name|s_name
index|[
name|n
index|]
operator|.
name|core_srv_conf
expr_stmt|;
block|}
if|if
condition|(
name|lscf
index|[
name|l
index|]
operator|.
name|flags
operator|&
name|NGX_HTTP_DEFAULT_SERVER
condition|)
block|{
if|if
condition|(
name|in_addr
index|[
name|a
index|]
operator|.
name|flags
operator|&
name|NGX_HTTP_DEFAULT_SERVER
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"duplicate default server in %s:%d"
argument_list|,
name|lscf
index|[
name|l
index|]
operator|.
name|file_name
operator|.
name|data
argument_list|,
name|lscf
index|[
name|l
index|]
operator|.
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|in_addr
index|[
name|a
index|]
operator|.
name|flags
operator||=
name|NGX_HTTP_DEFAULT_SERVER
expr_stmt|;
name|in_addr
index|[
name|a
index|]
operator|.
name|core_srv_conf
operator|=
name|cscf
index|[
name|s
index|]
expr_stmt|;
block|}
name|addr_found
operator|=
literal|1
expr_stmt|;
break|break;
comment|/* "*:XX" is the last resort */
block|}
if|else if
condition|(
name|in_addr
index|[
name|p
index|]
operator|.
name|addr
operator|==
name|INADDR_ANY
condition|)
block|{
name|ngx_test_null
argument_list|(
name|inaddr
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|in_port
index|[
name|p
index|]
operator|.
name|addr
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|inaddr
argument_list|,
operator|&
name|in_addr
index|[
name|a
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_in_addr_t
argument_list|)
argument_list|)
expr_stmt|;
name|inaddr
operator|->
name|addr
operator|=
name|lscf
index|[
name|l
index|]
operator|.
name|addr
expr_stmt|;
name|inaddr
operator|->
name|flags
operator|=
name|lscf
index|[
name|l
index|]
operator|.
name|flags
expr_stmt|;
name|inaddr
operator|->
name|core_srv_conf
operator|=
name|cscf
index|[
name|s
index|]
expr_stmt|;
name|ngx_init_array
argument_list|(
name|inaddr
operator|->
name|names
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_server_name_t
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|addr_found
operator|=
literal|1
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
operator|!
name|addr_found
condition|)
block|{
name|ngx_test_null
argument_list|(
name|inaddr
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|in_port
index|[
name|p
index|]
operator|.
name|addr
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|inaddr
operator|->
name|addr
operator|=
name|lscf
index|[
name|l
index|]
operator|.
name|addr
expr_stmt|;
name|inaddr
operator|->
name|flags
operator|=
name|lscf
index|[
name|l
index|]
operator|.
name|flags
expr_stmt|;
name|inaddr
operator|->
name|core_srv_conf
operator|=
name|cscf
index|[
name|s
index|]
expr_stmt|;
name|ngx_init_array
argument_list|(
name|inaddr
operator|->
name|names
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_server_name_t
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
operator|!
name|port_found
condition|)
block|{
name|ngx_test_null
argument_list|(
name|in_port
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|in_ports
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|in_port
operator|->
name|port
operator|=
name|lscf
index|[
name|l
index|]
operator|.
name|port
expr_stmt|;
name|ngx_init_array
argument_list|(
name|in_port
operator|->
name|addr
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_in_addr_t
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|inaddr
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|in_port
operator|->
name|addr
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|inaddr
operator|->
name|addr
operator|=
name|lscf
index|[
name|l
index|]
operator|.
name|addr
expr_stmt|;
name|inaddr
operator|->
name|flags
operator|=
name|lscf
index|[
name|l
index|]
operator|.
name|flags
expr_stmt|;
name|inaddr
operator|->
name|core_srv_conf
operator|=
name|cscf
index|[
name|s
index|]
expr_stmt|;
name|ngx_init_array
argument_list|(
name|inaddr
operator|->
name|names
argument_list|,
name|cf
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_server_name_t
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
block|}
block|}
block|}
comment|/* optimzie lists of ports, addresses and server names */
comment|/* AF_INET only */
name|in_port
operator|=
operator|(
name|ngx_http_in_port_t
operator|*
operator|)
name|in_ports
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|p
operator|=
literal|0
init|;
name|p
operator|<
name|in_ports
operator|.
name|nelts
condition|;
name|p
operator|++
control|)
block|{
name|in_addr
operator|=
operator|(
name|ngx_http_in_addr_t
operator|*
operator|)
name|in_port
index|[
name|p
index|]
operator|.
name|addr
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|a
operator|=
literal|0
init|;
name|a
operator|<
name|in_port
index|[
name|p
index|]
operator|.
name|addr
operator|.
name|nelts
condition|;
name|a
operator|++
control|)
block|{
name|virtual_names
operator|=
literal|0
expr_stmt|;
name|name
operator|=
operator|(
name|ngx_http_server_name_t
operator|*
operator|)
name|in_addr
index|[
name|a
index|]
operator|.
name|names
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|n
operator|=
literal|0
init|;
name|n
operator|<
name|in_addr
index|[
name|a
index|]
operator|.
name|names
operator|.
name|nelts
condition|;
name|n
operator|++
control|)
block|{
if|if
condition|(
name|in_addr
index|[
name|a
index|]
operator|.
name|core_srv_conf
operator|!=
name|name
index|[
name|n
index|]
operator|.
name|core_srv_conf
condition|)
block|{
name|virtual_names
operator|=
literal|1
expr_stmt|;
break|break;
block|}
block|}
comment|/* if all server names point to the same server                then we do not need to check them at run time */
if|if
condition|(
operator|!
name|virtual_names
condition|)
block|{
name|in_addr
index|[
name|a
index|]
operator|.
name|names
operator|.
name|nelts
operator|=
literal|0
expr_stmt|;
block|}
block|}
comment|/* if there is binding to "*:XX" then we need to bind to "*:XX" only            and ignore other binding */
if|if
condition|(
name|in_addr
index|[
name|a
operator|-
literal|1
index|]
operator|.
name|addr
operator|==
name|INADDR_ANY
condition|)
block|{
name|start
operator|=
name|a
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
name|start
operator|=
literal|0
expr_stmt|;
block|}
name|in_addr
operator|=
operator|(
name|ngx_http_in_addr_t
operator|*
operator|)
name|in_port
index|[
name|p
index|]
operator|.
name|addr
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|a
operator|=
name|start
init|;
name|a
operator|<
name|in_port
index|[
name|p
index|]
operator|.
name|addr
operator|.
name|nelts
condition|;
name|a
operator|++
control|)
block|{
name|ngx_test_null
argument_list|(
name|ls
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|ngx_listening_sockets
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
name|ls
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_listen_t
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|addr_in
argument_list|,
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|addr_in
operator|->
name|sin_family
operator|=
name|AF_INET
expr_stmt|;
name|addr_in
operator|->
name|sin_addr
operator|.
name|s_addr
operator|=
name|in_addr
index|[
name|a
index|]
operator|.
name|addr
expr_stmt|;
name|addr_in
operator|->
name|sin_port
operator|=
name|htons
argument_list|(
name|in_port
index|[
name|p
index|]
operator|.
name|port
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|ls
operator|->
name|addr_text
operator|.
name|data
argument_list|,
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|INET_ADDRSTRLEN
operator|+
literal|6
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ls
operator|->
name|addr_text
operator|.
name|len
operator|=
name|ngx_snprintf
argument_list|(
name|ls
operator|->
name|addr_text
operator|.
name|data
operator|+
name|ngx_inet_ntop
argument_list|(
name|AF_INET
argument_list|,
operator|(
name|char
operator|*
operator|)
operator|&
name|in_addr
index|[
name|a
index|]
operator|.
name|addr
argument_list|,
name|ls
operator|->
name|addr_text
operator|.
name|data
argument_list|,
name|INET_ADDRSTRLEN
argument_list|)
argument_list|,
literal|6
argument_list|,
literal|":%d"
argument_list|,
name|in_port
index|[
name|p
index|]
operator|.
name|port
argument_list|)
expr_stmt|;
name|ls
operator|->
name|family
operator|=
name|AF_INET
expr_stmt|;
name|ls
operator|->
name|type
operator|=
name|SOCK_STREAM
expr_stmt|;
name|ls
operator|->
name|protocol
operator|=
name|IPPROTO_IP
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_OVERLAPPED
operator|)
name|ls
operator|->
name|flags
operator|=
name|WSA_FLAG_OVERLAPPED
expr_stmt|;
endif|#
directive|endif
name|ls
operator|->
name|sockaddr
operator|=
operator|(
expr|struct
name|sockaddr
operator|*
operator|)
name|addr_in
expr_stmt|;
name|ls
operator|->
name|socklen
operator|=
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|)
expr_stmt|;
name|ls
operator|->
name|addr
operator|=
name|offsetof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|,
name|sin_addr
argument_list|)
expr_stmt|;
name|ls
operator|->
name|addr_text_max_len
operator|=
name|INET_ADDRSTRLEN
expr_stmt|;
name|ls
operator|->
name|backlog
operator|=
operator|-
literal|1
expr_stmt|;
name|ls
operator|->
name|post_accept_timeout
operator|=
name|ngx_http_post_accept_timeout
expr_stmt|;
name|ls
operator|->
name|nonblocking
operator|=
literal|1
expr_stmt|;
name|ls
operator|->
name|handler
operator|=
name|ngx_http_init_connection
expr_stmt|;
name|ls
operator|->
name|log
operator|=
name|cf
operator|->
name|log
expr_stmt|;
name|ls
operator|->
name|pool_size
operator|=
name|ngx_http_connection_pool_size
expr_stmt|;
name|ls
operator|->
name|ctx
operator|=
name|ctx
expr_stmt|;
name|ls
operator|->
name|servers
operator|=
operator|&
name|in_port
index|[
name|p
index|]
expr_stmt|;
if|#
directive|if
literal|0
block_content|if (in_port[p].addr.nelts == 1) {                 in_addr = (ngx_http_in_addr_t *) in_port[p].addr.elts;
comment|/* if there is the single address for this port and no virtual                    name servers so we do not need to check addresses                    at run time */
block_content|if (in_addr[a].names.nelts == 0) {                     ls->ctx = in_addr->core_srv_conf->ctx;                     ls->servers = NULL;                 }             }
endif|#
directive|endif
name|ngx_log_debug
argument_list|(
argument|cf->log
argument_list|,
literal|"ls ctx: %d:%08x"
argument|_ in_port[p].port _ ls->ctx
argument_list|)
empty_stmt|;
block|}
block|}
comment|/* DEBUG STUFF */
name|in_port
operator|=
operator|(
name|ngx_http_in_port_t
operator|*
operator|)
name|in_ports
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|p
operator|=
literal|0
init|;
name|p
operator|<
name|in_ports
operator|.
name|nelts
condition|;
name|p
operator|++
control|)
block|{
name|ngx_log_debug
argument_list|(
argument|cf->log
argument_list|,
literal|"port: %d"
argument|_ in_port[p].port
argument_list|)
empty_stmt|;
name|in_addr
operator|=
operator|(
name|ngx_http_in_addr_t
operator|*
operator|)
name|in_port
index|[
name|p
index|]
operator|.
name|addr
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|a
operator|=
literal|0
init|;
name|a
operator|<
name|in_port
index|[
name|p
index|]
operator|.
name|addr
operator|.
name|nelts
condition|;
name|a
operator|++
control|)
block|{
name|char
name|ip
index|[
literal|20
index|]
decl_stmt|;
name|ngx_inet_ntop
argument_list|(
name|AF_INET
argument_list|,
operator|(
name|char
operator|*
operator|)
operator|&
name|in_addr
index|[
name|a
index|]
operator|.
name|addr
argument_list|,
name|ip
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|cf->log
argument_list|,
literal|"%s %08x"
argument|_ ip _ in_addr[a].core_srv_conf
argument_list|)
empty_stmt|;
block|}
block|}
comment|/**/
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* STUB */
end_comment

begin_if
unit|static struct sockaddr_in  addr; static char addr_text[22];   int ngx_http_init(ngx_pool_t *pool, ngx_log_t *log) {     ngx_listen_t  *ls;      ngx_http_server.connection_pool_size = 16384;     ngx_http_server.request_pool_size = 16384;     ngx_http_server.header_timeout = 20000;     ngx_http_server.header_buffer_size = 1024;     ngx_http_server.discarded_buffer_size = 1500;      ngx_http_server.lingering_timeout = 5000;     ngx_http_server.lingering_time = 30;
if|#
directive|if
operator|(
name|WIN32
operator|)
end_if

begin_else
unit|ngx_http_server.doc_root = "html";
else|#
directive|else
end_else

begin_endif
unit|ngx_http_server.doc_root = "/home/is/dox/";     ngx_http_server.doc_root = "/home/is/work/xml/site-1.0.0/html";     ngx_http_server.doc_root = "/spool/test/lperltk";     ngx_http_server.doc_root = "/home/is/dox/ora/lperltk";
endif|#
directive|endif
end_endif

begin_if
unit|ngx_http_server.doc_root_len = strlen(ngx_http_server.doc_root) + 1;       ngx_http_config_modules(pool, ngx_modules);
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* STUB */
end_comment

begin_endif
unit|ngx_http_output_filter_set_stub(pool, ngx_http_modules);     ngx_http_write_filter_set_stub(pool, ngx_http_modules);     ngx_http_index_set_stub(pool, ngx_http_modules);      ngx_http_init_modules(pool, ngx_http_modules);
endif|#
directive|endif
end_endif

begin_if
unit|ngx_http_init_filters(pool, ngx_modules);      ls = ngx_push_array(&ngx_listening_sockets);     ngx_memzero(ls, sizeof(ngx_listen_t));      addr.sin_family = AF_INET;     addr.sin_addr.s_addr = inet_addr("0.0.0.0");     addr.sin_port = htons(8000);      ngx_snprintf(ngx_cpystrn(addr_text, inet_ntoa(addr.sin_addr), 16),                  7, ":%d", ntohs(addr.sin_port));      ls->family = AF_INET;     ls->type = SOCK_STREAM;     ls->protocol = IPPROTO_IP;
if|#
directive|if
operator|(
name|NGX_OVERLAPPED
operator|)
end_if

begin_else
unit|ls->flags = WSA_FLAG_OVERLAPPED;
else|#
directive|else
end_else

begin_endif
unit|ls->nonblocking = 1;
endif|#
directive|endif
end_endif

begin_comment
unit|ls->sockaddr = (struct sockaddr *)&addr;     ls->socklen = sizeof(struct sockaddr_in);     ls->addr = offsetof(struct sockaddr_in, sin_addr);     ls->addr_text.len = INET_ADDRSTRLEN;     ls->addr_text.data = addr_text;     ls->backlog = -1;     ls->post_accept_timeout = 10000;      ls->handler = ngx_http_init_connection;     ls->server =&ngx_http_server;     ls->log = log;       return 1; }
comment|/**/
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

