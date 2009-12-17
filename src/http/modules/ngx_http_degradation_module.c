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

begin_typedef
DECL|struct|__anon278ec5460108
typedef|typedef
struct|struct
block|{
DECL|member|sbrk_size
name|size_t
name|sbrk_size
decl_stmt|;
DECL|typedef|ngx_http_degradation_main_conf_t
block|}
name|ngx_http_degradation_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon278ec5460208
typedef|typedef
struct|struct
block|{
DECL|member|degrade
name|ngx_uint_t
name|degrade
decl_stmt|;
DECL|typedef|ngx_http_degradation_loc_conf_t
block|}
name|ngx_http_degradation_loc_conf_t
typedef|;
end_typedef

begin_decl_stmt
DECL|variable|ngx_http_degrade
specifier|static
name|ngx_conf_enum_t
name|ngx_http_degrade
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"204"
argument_list|)
block|,
literal|204
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"444"
argument_list|)
block|,
literal|444
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

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_degradation_create_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_degradation_create_loc_conf
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
name|ngx_http_degradation_merge_loc_conf
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
name|ngx_http_degradation
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
name|ngx_int_t
name|ngx_http_degradation_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_degradation_commands
specifier|static
name|ngx_command_t
name|ngx_http_degradation_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"degradation"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_degradation
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
literal|"degrade"
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
name|ngx_http_degradation_loc_conf_t
argument_list|,
name|degrade
argument_list|)
block|,
operator|&
name|ngx_http_degrade
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_degradation_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_degradation_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_degradation_init
block|,
comment|/* postconfiguration */
name|ngx_http_degradation_create_main_conf
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
name|ngx_http_degradation_create_loc_conf
block|,
comment|/* create location configuration */
name|ngx_http_degradation_merge_loc_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_degradation_module
name|ngx_module_t
name|ngx_http_degradation_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_degradation_module_ctx
block|,
comment|/* module context */
name|ngx_http_degradation_commands
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
DECL|function|ngx_http_degradation_handler (ngx_http_request_t * r)
name|ngx_http_degradation_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|time_t
name|now
decl_stmt|;
specifier|static
name|size_t
name|sbrk_size
decl_stmt|;
specifier|static
name|time_t
name|sbrk_time
decl_stmt|;
name|ngx_http_degradation_loc_conf_t
modifier|*
name|dlcf
decl_stmt|;
name|ngx_http_degradation_main_conf_t
modifier|*
name|dmcf
decl_stmt|;
name|dlcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_degradation_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|dlcf
operator|->
name|degrade
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_DECLINED
return|;
block|}
name|dmcf
operator|=
name|ngx_http_get_module_main_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_degradation_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|dmcf
operator|->
name|sbrk_size
condition|)
block|{
name|now
operator|=
name|ngx_time
argument_list|()
expr_stmt|;
comment|/* lock mutex */
if|if
condition|(
name|now
operator|!=
name|sbrk_time
condition|)
block|{
comment|/*              * ELF/i386 is loaded at 0x08000000, 128M              * ELF/amd64 is loaded at 0x00400000, 4M              *              * use a function address to substract the loading address              */
name|sbrk_size
operator|=
operator|(
name|size_t
operator|)
name|sbrk
argument_list|(
literal|0
argument_list|)
operator|-
operator|(
operator|(
name|uintptr_t
operator|)
name|ngx_palloc
operator|&
operator|~
literal|0x3FFFFF
operator|)
expr_stmt|;
name|sbrk_time
operator|=
name|now
expr_stmt|;
block|}
comment|/* unlock mutex */
if|if
condition|(
name|sbrk_size
operator|>=
name|dmcf
operator|->
name|sbrk_size
condition|)
block|{
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
literal|"degradation sbrk: %uz"
argument_list|,
name|sbrk_size
argument_list|)
expr_stmt|;
return|return
name|dlcf
operator|->
name|degrade
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
name|void
modifier|*
DECL|function|ngx_http_degradation_create_main_conf (ngx_conf_t * cf)
name|ngx_http_degradation_create_main_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_degradation_main_conf_t
modifier|*
name|dmcf
decl_stmt|;
name|dmcf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_degradation_main_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dmcf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
return|return
name|dmcf
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_degradation_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_degradation_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_degradation_loc_conf_t
modifier|*
name|conf
decl_stmt|;
name|conf
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_degradation_loc_conf_t
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
name|NULL
return|;
block|}
name|conf
operator|->
name|degrade
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
DECL|function|ngx_http_degradation_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_degradation_merge_loc_conf
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
name|ngx_http_degradation_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_degradation_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_conf_merge_uint_value
argument_list|(
name|conf
operator|->
name|degrade
argument_list|,
name|prev
operator|->
name|degrade
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
name|char
modifier|*
DECL|function|ngx_http_degradation (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_degradation
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
name|ngx_http_degradation_main_conf_t
modifier|*
name|dmcf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
name|s
decl_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
if|if
condition|(
name|ngx_strncmp
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
literal|"sbrk="
argument_list|,
literal|5
argument_list|)
operator|==
literal|0
condition|)
block|{
name|s
operator|.
name|len
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|len
operator|-
literal|5
expr_stmt|;
name|s
operator|.
name|data
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|data
operator|+
literal|5
expr_stmt|;
name|dmcf
operator|->
name|sbrk_size
operator|=
name|ngx_parse_size
argument_list|(
operator|&
name|s
argument_list|)
expr_stmt|;
if|if
condition|(
name|dmcf
operator|->
name|sbrk_size
operator|==
operator|(
name|size_t
operator|)
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
literal|"invalid sbrk size \"%V\""
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
return|return
name|NGX_CONF_OK
return|;
block|}
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
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_degradation_init (ngx_conf_t * cf)
name|ngx_http_degradation_init
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
name|ngx_http_degradation_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

