begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  * Copyright (C) Valentin V. Bartenev  */
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
file|<ngx_http.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_v2_module.h>
end_include

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_v2_add_variables
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_v2_variable
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_variable_value_t
modifier|*
name|v
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_v2_module_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_v2_create_main_conf
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
name|ngx_http_v2_init_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_v2_create_srv_conf
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
name|ngx_http_v2_merge_srv_conf
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
name|void
modifier|*
name|ngx_http_v2_create_loc_conf
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
name|ngx_http_v2_merge_loc_conf
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
name|char
modifier|*
name|ngx_http_v2_recv_buffer_size
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_v2_pool_size
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_v2_preread_size
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_v2_streams_index_mask
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_v2_chunk_size
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_v2_spdy_deprecated
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_v2_recv_buffer_size_post
specifier|static
name|ngx_conf_post_t
name|ngx_http_v2_recv_buffer_size_post
init|=
block|{
name|ngx_http_v2_recv_buffer_size
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_v2_pool_size_post
specifier|static
name|ngx_conf_post_t
name|ngx_http_v2_pool_size_post
init|=
block|{
name|ngx_http_v2_pool_size
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_v2_preread_size_post
specifier|static
name|ngx_conf_post_t
name|ngx_http_v2_preread_size_post
init|=
block|{
name|ngx_http_v2_preread_size
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_v2_streams_index_mask_post
specifier|static
name|ngx_conf_post_t
name|ngx_http_v2_streams_index_mask_post
init|=
block|{
name|ngx_http_v2_streams_index_mask
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_v2_chunk_size_post
specifier|static
name|ngx_conf_post_t
name|ngx_http_v2_chunk_size_post
init|=
block|{
name|ngx_http_v2_chunk_size
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_v2_commands
specifier|static
name|ngx_command_t
name|ngx_http_v2_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"http2_recv_buffer_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_size_slot
block|,
name|NGX_HTTP_MAIN_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_main_conf_t
argument_list|,
name|recv_buffer_size
argument_list|)
block|,
operator|&
name|ngx_http_v2_recv_buffer_size_post
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_pool_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_size_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|pool_size
argument_list|)
block|,
operator|&
name|ngx_http_v2_pool_size_post
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_max_concurrent_streams"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_num_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|concurrent_streams
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_max_requests"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_num_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|max_requests
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_max_field_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_size_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|max_field_size
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_max_header_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_size_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|max_header_size
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_body_preread_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_size_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|preread_size
argument_list|)
block|,
operator|&
name|ngx_http_v2_preread_size_post
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_streams_index_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_num_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|streams_index_mask
argument_list|)
block|,
operator|&
name|ngx_http_v2_streams_index_mask_post
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_recv_timeout"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_msec_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|recv_timeout
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_idle_timeout"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_msec_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|,
name|idle_timeout
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"http2_chunk_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
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
name|ngx_http_v2_loc_conf_t
argument_list|,
name|chunk_size
argument_list|)
block|,
operator|&
name|ngx_http_v2_chunk_size_post
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"spdy_recv_buffer_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_v2_spdy_deprecated
block|,
name|NGX_HTTP_MAIN_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"spdy_pool_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_v2_spdy_deprecated
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"spdy_max_concurrent_streams"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_v2_spdy_deprecated
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"spdy_streams_index_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_v2_spdy_deprecated
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"spdy_recv_timeout"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_v2_spdy_deprecated
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"spdy_keepalive_timeout"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_v2_spdy_deprecated
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"spdy_headers_comp"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_v2_spdy_deprecated
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"spdy_chunk_size"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_v2_spdy_deprecated
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_v2_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_v2_module_ctx
init|=
block|{
name|ngx_http_v2_add_variables
block|,
comment|/* preconfiguration */
name|NULL
block|,
comment|/* postconfiguration */
name|ngx_http_v2_create_main_conf
block|,
comment|/* create main configuration */
name|ngx_http_v2_init_main_conf
block|,
comment|/* init main configuration */
name|ngx_http_v2_create_srv_conf
block|,
comment|/* create server configuration */
name|ngx_http_v2_merge_srv_conf
block|,
comment|/* merge server configuration */
name|ngx_http_v2_create_loc_conf
block|,
comment|/* create location configuration */
name|ngx_http_v2_merge_loc_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_v2_module
name|ngx_module_t
name|ngx_http_v2_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_v2_module_ctx
block|,
comment|/* module context */
name|ngx_http_v2_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|ngx_http_v2_module_init
block|,
comment|/* init module */
name|NULL
block|,
comment|/* init process */
name|NULL
block|,
comment|/* init thread */
name|NULL
block|,
comment|/* exit thread */
name|NULL
block|,
comment|/* exit process */
name|NULL
block|,
comment|/* exit master */
name|NGX_MODULE_V1_PADDING
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_v2_vars
specifier|static
name|ngx_http_variable_t
name|ngx_http_v2_vars
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"http2"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_v2_variable
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|,
name|ngx_http_null_variable
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_v2_add_variables (ngx_conf_t * cf)
name|ngx_http_v2_add_variables
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_variable_t
modifier|*
name|var
decl_stmt|,
modifier|*
name|v
decl_stmt|;
for|for
control|(
name|v
operator|=
name|ngx_http_v2_vars
init|;
name|v
operator|->
name|name
operator|.
name|len
condition|;
name|v
operator|++
control|)
block|{
name|var
operator|=
name|ngx_http_add_variable
argument_list|(
name|cf
argument_list|,
operator|&
name|v
operator|->
name|name
argument_list|,
name|v
operator|->
name|flags
argument_list|)
expr_stmt|;
if|if
condition|(
name|var
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|var
operator|->
name|get_handler
operator|=
name|v
operator|->
name|get_handler
expr_stmt|;
name|var
operator|->
name|data
operator|=
name|v
operator|->
name|data
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_v2_variable (ngx_http_request_t * r,ngx_http_variable_value_t * v,uintptr_t data)
name|ngx_http_v2_variable
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_variable_value_t
modifier|*
name|v
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
block|{
if|if
condition|(
name|r
operator|->
name|stream
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
operator|)
if|if
condition|(
name|r
operator|->
name|connection
operator|->
name|ssl
condition|)
block|{
name|v
operator|->
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"h2"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|v
operator|->
name|valid
operator|=
literal|1
expr_stmt|;
name|v
operator|->
name|no_cacheable
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|not_found
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|data
operator|=
operator|(
name|u_char
operator|*
operator|)
literal|"h2"
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
endif|#
directive|endif
name|v
operator|->
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"h2c"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|v
operator|->
name|valid
operator|=
literal|1
expr_stmt|;
name|v
operator|->
name|no_cacheable
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|not_found
operator|=
literal|0
expr_stmt|;
name|v
operator|->
name|data
operator|=
operator|(
name|u_char
operator|*
operator|)
literal|"h2c"
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
operator|*
name|v
operator|=
name|ngx_http_variable_null_value
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_v2_module_init (ngx_cycle_t * cycle)
name|ngx_http_v2_module_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_v2_create_main_conf (ngx_conf_t * cf)
name|ngx_http_v2_create_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_v2_main_conf_t
modifier|*
name|h2mcf
decl_stmt|;
name|h2mcf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_v2_main_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|h2mcf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|h2mcf
operator|->
name|recv_buffer_size
operator|=
name|NGX_CONF_UNSET_SIZE
expr_stmt|;
return|return
name|h2mcf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_init_main_conf (ngx_conf_t * cf,void * conf)
name|ngx_http_v2_init_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_http_v2_main_conf_t
modifier|*
name|h2mcf
init|=
name|conf
decl_stmt|;
name|ngx_conf_init_size_value
argument_list|(
name|h2mcf
operator|->
name|recv_buffer_size
argument_list|,
literal|256
operator|*
literal|1024
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_v2_create_srv_conf (ngx_conf_t * cf)
name|ngx_http_v2_create_srv_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_v2_srv_conf_t
modifier|*
name|h2scf
decl_stmt|;
name|h2scf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_v2_srv_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|h2scf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|h2scf
operator|->
name|pool_size
operator|=
name|NGX_CONF_UNSET_SIZE
expr_stmt|;
name|h2scf
operator|->
name|concurrent_streams
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
name|h2scf
operator|->
name|max_requests
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
name|h2scf
operator|->
name|max_field_size
operator|=
name|NGX_CONF_UNSET_SIZE
expr_stmt|;
name|h2scf
operator|->
name|max_header_size
operator|=
name|NGX_CONF_UNSET_SIZE
expr_stmt|;
name|h2scf
operator|->
name|preread_size
operator|=
name|NGX_CONF_UNSET_SIZE
expr_stmt|;
name|h2scf
operator|->
name|streams_index_mask
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
name|h2scf
operator|->
name|recv_timeout
operator|=
name|NGX_CONF_UNSET_MSEC
expr_stmt|;
name|h2scf
operator|->
name|idle_timeout
operator|=
name|NGX_CONF_UNSET_MSEC
expr_stmt|;
return|return
name|h2scf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_merge_srv_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_v2_merge_srv_conf
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
name|ngx_http_v2_srv_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_v2_srv_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_size_value
argument_list|(
name|conf
operator|->
name|pool_size
argument_list|,
name|prev
operator|->
name|pool_size
argument_list|,
literal|4096
argument_list|)
expr_stmt|;
name|ngx_conf_merge_uint_value
argument_list|(
name|conf
operator|->
name|concurrent_streams
argument_list|,
name|prev
operator|->
name|concurrent_streams
argument_list|,
literal|128
argument_list|)
expr_stmt|;
name|ngx_conf_merge_uint_value
argument_list|(
name|conf
operator|->
name|max_requests
argument_list|,
name|prev
operator|->
name|max_requests
argument_list|,
literal|1000
argument_list|)
expr_stmt|;
name|ngx_conf_merge_size_value
argument_list|(
name|conf
operator|->
name|max_field_size
argument_list|,
name|prev
operator|->
name|max_field_size
argument_list|,
literal|4096
argument_list|)
expr_stmt|;
name|ngx_conf_merge_size_value
argument_list|(
name|conf
operator|->
name|max_header_size
argument_list|,
name|prev
operator|->
name|max_header_size
argument_list|,
literal|16384
argument_list|)
expr_stmt|;
name|ngx_conf_merge_size_value
argument_list|(
name|conf
operator|->
name|preread_size
argument_list|,
name|prev
operator|->
name|preread_size
argument_list|,
literal|65536
argument_list|)
expr_stmt|;
name|ngx_conf_merge_uint_value
argument_list|(
name|conf
operator|->
name|streams_index_mask
argument_list|,
name|prev
operator|->
name|streams_index_mask
argument_list|,
literal|32
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ngx_conf_merge_msec_value
argument_list|(
name|conf
operator|->
name|recv_timeout
argument_list|,
name|prev
operator|->
name|recv_timeout
argument_list|,
literal|30000
argument_list|)
expr_stmt|;
name|ngx_conf_merge_msec_value
argument_list|(
name|conf
operator|->
name|idle_timeout
argument_list|,
name|prev
operator|->
name|idle_timeout
argument_list|,
literal|180000
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_v2_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_v2_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_v2_loc_conf_t
modifier|*
name|h2lcf
decl_stmt|;
name|h2lcf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_v2_loc_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|h2lcf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|h2lcf
operator|->
name|chunk_size
operator|=
name|NGX_CONF_UNSET_SIZE
expr_stmt|;
return|return
name|h2lcf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_v2_merge_loc_conf
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
name|ngx_http_v2_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_v2_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_size_value
argument_list|(
name|conf
operator|->
name|chunk_size
argument_list|,
name|prev
operator|->
name|chunk_size
argument_list|,
literal|8
operator|*
literal|1024
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_recv_buffer_size (ngx_conf_t * cf,void * post,void * data)
name|ngx_http_v2_recv_buffer_size
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|size_t
modifier|*
name|sp
init|=
name|data
decl_stmt|;
if|if
condition|(
operator|*
name|sp
operator|<=
literal|2
operator|*
name|NGX_HTTP_V2_STATE_BUFFER_SIZE
condition|)
block|{
return|return
literal|"value is too small"
return|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_pool_size (ngx_conf_t * cf,void * post,void * data)
name|ngx_http_v2_pool_size
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|size_t
modifier|*
name|sp
init|=
name|data
decl_stmt|;
if|if
condition|(
operator|*
name|sp
operator|<
name|NGX_MIN_POOL_SIZE
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"the pool size must be no less than %uz"
argument_list|,
name|NGX_MIN_POOL_SIZE
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
operator|*
name|sp
operator|%
name|NGX_POOL_ALIGNMENT
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"the pool size must be a multiple of %uz"
argument_list|,
name|NGX_POOL_ALIGNMENT
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_preread_size (ngx_conf_t * cf,void * post,void * data)
name|ngx_http_v2_preread_size
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|size_t
modifier|*
name|sp
init|=
name|data
decl_stmt|;
if|if
condition|(
operator|*
name|sp
operator|>
name|NGX_HTTP_V2_MAX_WINDOW
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"the maximum body preread buffer size is %uz"
argument_list|,
name|NGX_HTTP_V2_MAX_WINDOW
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_streams_index_mask (ngx_conf_t * cf,void * post,void * data)
name|ngx_http_v2_streams_index_mask
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|ngx_uint_t
modifier|*
name|np
init|=
name|data
decl_stmt|;
name|ngx_uint_t
name|mask
decl_stmt|;
name|mask
operator|=
operator|*
name|np
operator|-
literal|1
expr_stmt|;
if|if
condition|(
operator|*
name|np
operator|==
literal|0
operator|||
operator|(
operator|*
name|np
operator|&
name|mask
operator|)
condition|)
block|{
return|return
literal|"must be a power of two"
return|;
block|}
operator|*
name|np
operator|=
name|mask
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_chunk_size (ngx_conf_t * cf,void * post,void * data)
name|ngx_http_v2_chunk_size
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|size_t
modifier|*
name|sp
init|=
name|data
decl_stmt|;
if|if
condition|(
operator|*
name|sp
operator|==
literal|0
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"the http2 chunk size cannot be zero"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
operator|*
name|sp
operator|>
name|NGX_HTTP_V2_MAX_FRAME_SIZE
condition|)
block|{
operator|*
name|sp
operator|=
name|NGX_HTTP_V2_MAX_FRAME_SIZE
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_v2_spdy_deprecated (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_v2_spdy_deprecated
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid directive \"%V\": ngx_http_spdy_module "
literal|"was superseded by ngx_http_v2_module"
argument_list|,
operator|&
name|cmd
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

