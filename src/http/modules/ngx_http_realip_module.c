begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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

begin_comment
comment|/* AF_INET only */
end_comment

begin_typedef
DECL|struct|__anon28c482c90108
typedef|typedef
struct|struct
block|{
DECL|member|mask
name|in_addr_t
name|mask
decl_stmt|;
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|typedef|ngx_http_realip_from_t
block|}
name|ngx_http_realip_from_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c482c90208
typedef|typedef
struct|struct
block|{
DECL|member|from
name|ngx_array_t
modifier|*
name|from
decl_stmt|;
comment|/* array of ngx_http_realip_from_t */
DECL|member|xfwd
name|ngx_uint_t
name|xfwd
decl_stmt|;
DECL|typedef|ngx_http_realip_loc_conf_t
block|}
name|ngx_http_realip_loc_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_realip_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_realip_from
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

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_realip_create_loc_conf
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
name|ngx_http_realip_merge_loc_conf
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
name|ngx_http_realip_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_realip_header
specifier|static
name|ngx_conf_enum_t
name|ngx_http_realip_header
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"X-Forwarded-For"
argument_list|)
block|,
literal|1
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"X-Real-IP"
argument_list|)
block|,
literal|0
block|}
block|,
block|{
name|ngx_null_string
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_realip_commands
specifier|static
name|ngx_command_t
name|ngx_http_realip_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"set_real_ip_from"
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
name|ngx_http_realip_from
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"real_ip_header"
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
name|ngx_conf_set_enum_slot
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_realip_loc_conf_t
argument_list|,
name|xfwd
argument_list|)
block|,
operator|&
name|ngx_http_realip_header
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_realip_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_realip_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_realip_init
block|,
comment|/* postconfiguration */
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
name|ngx_http_realip_create_loc_conf
block|,
comment|/* create location configuration */
name|ngx_http_realip_merge_loc_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_realip_module
name|ngx_module_t
name|ngx_http_realip_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_realip_module_ctx
block|,
comment|/* module context */
name|ngx_http_realip_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|NULL
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

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_realip_handler (ngx_http_request_t * r)
name|ngx_http_realip_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|u_char
modifier|*
name|ip
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|in_addr_t
name|addr
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
name|ngx_http_realip_from_t
modifier|*
name|from
decl_stmt|;
name|ngx_http_realip_loc_conf_t
modifier|*
name|rlcf
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|realip_set
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|rlcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_realip_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|rlcf
operator|->
name|from
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
if|if
condition|(
name|rlcf
operator|->
name|xfwd
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
operator|->
name|headers_in
operator|.
name|x_real_ip
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|len
operator|=
name|r
operator|->
name|headers_in
operator|.
name|x_real_ip
operator|->
name|value
operator|.
name|len
expr_stmt|;
name|ip
operator|=
name|r
operator|->
name|headers_in
operator|.
name|x_real_ip
operator|->
name|value
operator|.
name|data
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|r
operator|->
name|headers_in
operator|.
name|x_forwarded_for
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|len
operator|=
name|r
operator|->
name|headers_in
operator|.
name|x_forwarded_for
operator|->
name|value
operator|.
name|len
expr_stmt|;
name|ip
operator|=
name|r
operator|->
name|headers_in
operator|.
name|x_forwarded_for
operator|->
name|value
operator|.
name|data
expr_stmt|;
for|for
control|(
name|p
operator|=
name|ip
operator|+
name|len
operator|-
literal|1
init|;
name|p
operator|>
name|ip
condition|;
name|p
operator|--
control|)
block|{
if|if
condition|(
operator|*
name|p
operator|==
literal|' '
operator|||
operator|*
name|p
operator|==
literal|','
condition|)
block|{
name|p
operator|++
expr_stmt|;
name|len
operator|-=
name|p
operator|-
name|ip
expr_stmt|;
name|ip
operator|=
name|p
expr_stmt|;
break|break;
block|}
block|}
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"realip: \"%s\""
argument_list|,
name|ip
argument_list|)
expr_stmt|;
comment|/* AF_INET only */
name|sin
operator|=
operator|(
expr|struct
name|sockaddr_in
operator|*
operator|)
name|r
operator|->
name|connection
operator|->
name|sockaddr
expr_stmt|;
name|from
operator|=
name|rlcf
operator|->
name|from
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|rlcf
operator|->
name|from
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|ngx_log_debug3
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"realip: %08XD %08XD %08XD"
argument_list|,
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
argument_list|,
name|from
index|[
name|i
index|]
operator|.
name|mask
argument_list|,
name|from
index|[
name|i
index|]
operator|.
name|addr
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
operator|&
name|from
index|[
name|i
index|]
operator|.
name|mask
operator|)
operator|==
name|from
index|[
name|i
index|]
operator|.
name|addr
condition|)
block|{
name|r
operator|->
name|realip_set
operator|=
literal|1
expr_stmt|;
name|addr
operator|=
name|inet_addr
argument_list|(
operator|(
name|char
operator|*
operator|)
name|ip
argument_list|)
expr_stmt|;
if|if
condition|(
name|addr
operator|==
name|INADDR_NONE
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|p
operator|=
name|ngx_palloc
argument_list|(
name|r
operator|->
name|connection
operator|->
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|ngx_memcpy
argument_list|(
name|p
argument_list|,
name|ip
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
operator|=
name|addr
expr_stmt|;
name|r
operator|->
name|connection
operator|->
name|addr_text
operator|.
name|len
operator|=
name|len
expr_stmt|;
name|r
operator|->
name|connection
operator|->
name|addr_text
operator|.
name|data
operator|=
name|p
expr_stmt|;
return|return
name|NGX_DECLINED
return|;
block|}
block|}
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_realip_from (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_realip_from
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
name|ngx_http_realip_loc_conf_t
modifier|*
name|rlcf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_inet_cidr_t
name|in_cidr
decl_stmt|;
name|ngx_http_realip_from_t
modifier|*
name|from
decl_stmt|;
if|if
condition|(
name|rlcf
operator|->
name|from
operator|==
name|NULL
condition|)
block|{
name|rlcf
operator|->
name|from
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|2
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_realip_from_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|rlcf
operator|->
name|from
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
name|from
operator|=
name|ngx_array_push
argument_list|(
name|rlcf
operator|->
name|from
argument_list|)
expr_stmt|;
if|if
condition|(
name|from
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|from
operator|->
name|addr
operator|=
name|inet_addr
argument_list|(
operator|(
name|char
operator|*
operator|)
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|from
operator|->
name|addr
operator|!=
name|INADDR_NONE
condition|)
block|{
name|from
operator|->
name|mask
operator|=
literal|0xffffffff
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
if|if
condition|(
name|ngx_ptocidr
argument_list|(
operator|&
name|value
index|[
literal|1
index|]
argument_list|,
operator|&
name|in_cidr
argument_list|)
operator|==
name|NGX_ERROR
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
literal|"invalid parameter \"%V\""
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|from
operator|->
name|mask
operator|=
name|in_cidr
operator|.
name|mask
expr_stmt|;
name|from
operator|->
name|addr
operator|=
name|in_cidr
operator|.
name|addr
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
DECL|function|ngx_http_realip_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_realip_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_realip_loc_conf_t
modifier|*
name|conf
decl_stmt|;
name|conf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_realip_loc_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
comment|/*      * set by ngx_pcalloc():      *      *     conf->from = NULL;      */
name|conf
operator|->
name|xfwd
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_realip_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_realip_merge_loc_conf
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
name|ngx_http_realip_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_realip_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
if|if
condition|(
name|conf
operator|->
name|from
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|from
operator|=
name|prev
operator|->
name|from
expr_stmt|;
block|}
name|ngx_conf_merge_uint_value
argument_list|(
name|conf
operator|->
name|xfwd
argument_list|,
name|prev
operator|->
name|xfwd
argument_list|,
literal|0
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_realip_init (ngx_conf_t * cf)
name|ngx_http_realip_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_handler_pt
modifier|*
name|h
decl_stmt|;
name|ngx_http_core_main_conf_t
modifier|*
name|cmcf
decl_stmt|;
name|cmcf
operator|=
name|ngx_http_conf_get_module_main_conf
argument_list|(
name|cf
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
name|h
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|cmcf
operator|->
name|phases
index|[
name|NGX_HTTP_POST_READ_PHASE
index|]
operator|.
name|handlers
argument_list|)
expr_stmt|;
if|if
condition|(
name|h
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
operator|*
name|h
operator|=
name|ngx_http_realip_handler
expr_stmt|;
name|h
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|cmcf
operator|->
name|phases
index|[
name|NGX_HTTP_PREACCESS_PHASE
index|]
operator|.
name|handlers
argument_list|)
expr_stmt|;
if|if
condition|(
name|h
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
operator|*
name|h
operator|=
name|ngx_http_realip_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

