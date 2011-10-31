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
DECL|typedef|ngx_ssl_variable_handler_pt
typedef|typedef
name|ngx_int_t
function_decl|(
modifier|*
name|ngx_ssl_variable_handler_pt
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|NGX_DEFAULT_CIPHERS
define|#
directive|define
name|NGX_DEFAULT_CIPHERS
value|"HIGH:!aNULL:!MD5"
end_define

begin_define
DECL|macro|NGX_DEFAULT_ECDH_CURVE
define|#
directive|define
name|NGX_DEFAULT_ECDH_CURVE
value|"prime256v1"
end_define

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_ssl_static_variable
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
name|ngx_http_ssl_variable
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
name|ngx_http_ssl_add_variables
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
name|ngx_http_ssl_create_srv_conf
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
name|ngx_http_ssl_merge_srv_conf
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
name|ngx_http_ssl_enable
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
name|char
modifier|*
name|ngx_http_ssl_session_cache
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
DECL|variable|ngx_http_ssl_protocols
specifier|static
name|ngx_conf_bitmask_t
name|ngx_http_ssl_protocols
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"SSLv2"
argument_list|)
block|,
name|NGX_SSL_SSLv2
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"SSLv3"
argument_list|)
block|,
name|NGX_SSL_SSLv3
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"TLSv1"
argument_list|)
block|,
name|NGX_SSL_TLSv1
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
DECL|variable|ngx_http_ssl_verify
specifier|static
name|ngx_conf_enum_t
name|ngx_http_ssl_verify
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"off"
argument_list|)
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"on"
argument_list|)
block|,
literal|1
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"optional"
argument_list|)
block|,
literal|2
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
DECL|variable|ngx_http_ssl_commands
specifier|static
name|ngx_command_t
name|ngx_http_ssl_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"ssl"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_http_ssl_enable
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|enable
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_certificate"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|certificate
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_certificate_key"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|certificate_key
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_dhparam"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|dhparam
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_ecdh_curve"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|ecdh_curve
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_protocols"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_conf_set_bitmask_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|protocols
argument_list|)
block|,
operator|&
name|ngx_http_ssl_protocols
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_ciphers"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|ciphers
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_verify_client"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_conf_set_enum_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|verify
argument_list|)
block|,
operator|&
name|ngx_http_ssl_verify
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_verify_depth"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_conf_set_num_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|verify_depth
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_client_certificate"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|client_certificate
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_prefer_server_ciphers"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_conf_set_flag_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|prefer_server_ciphers
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_session_cache"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE12
block|,
name|ngx_http_ssl_session_cache
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
literal|"ssl_session_timeout"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_sec_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|session_timeout
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_crl"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_HTTP_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|,
name|crl
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
DECL|variable|ngx_http_ssl_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_ssl_module_ctx
init|=
block|{
name|ngx_http_ssl_add_variables
block|,
comment|/* preconfiguration */
name|NULL
block|,
comment|/* postconfiguration */
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|ngx_http_ssl_create_srv_conf
block|,
comment|/* create server configuration */
name|ngx_http_ssl_merge_srv_conf
block|,
comment|/* merge server configuration */
name|NULL
block|,
comment|/* create location configuration */
name|NULL
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_ssl_module
name|ngx_module_t
name|ngx_http_ssl_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_ssl_module_ctx
block|,
comment|/* module context */
name|ngx_http_ssl_commands
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

begin_decl_stmt
DECL|variable|ngx_http_ssl_vars
specifier|static
name|ngx_http_variable_t
name|ngx_http_ssl_vars
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"ssl_protocol"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_static_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_protocol
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_cipher"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_static_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_cipher_name
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_session_id"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_session_id
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_client_cert"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_certificate
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_client_raw_cert"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_raw_certificate
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_client_s_dn"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_subject_dn
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_client_i_dn"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_issuer_dn
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_client_serial"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_serial_number
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_client_verify"
argument_list|)
block|,
name|NULL
block|,
name|ngx_http_ssl_variable
block|,
operator|(
name|uintptr_t
operator|)
name|ngx_ssl_get_client_verify
block|,
name|NGX_HTTP_VAR_CHANGEABLE
block|,
literal|0
block|}
block|,
block|{
name|ngx_null_string
block|,
name|NULL
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_ssl_sess_id_ctx
specifier|static
name|ngx_str_t
name|ngx_http_ssl_sess_id_ctx
init|=
name|ngx_string
argument_list|(
literal|"HTTP"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_ssl_static_variable (ngx_http_request_t * r,ngx_http_variable_value_t * v,uintptr_t data)
name|ngx_http_ssl_static_variable
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
name|ngx_ssl_variable_handler_pt
name|handler
init|=
operator|(
name|ngx_ssl_variable_handler_pt
operator|)
name|data
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_str_t
name|s
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|connection
operator|->
name|ssl
condition|)
block|{
operator|(
name|void
operator|)
name|handler
argument_list|(
name|r
operator|->
name|connection
argument_list|,
name|NULL
argument_list|,
operator|&
name|s
argument_list|)
expr_stmt|;
name|v
operator|->
name|data
operator|=
name|s
operator|.
name|data
expr_stmt|;
for|for
control|(
name|len
operator|=
literal|0
init|;
name|v
operator|->
name|data
index|[
name|len
index|]
condition|;
name|len
operator|++
control|)
block|{
comment|/* void */
block|}
name|v
operator|->
name|len
operator|=
name|len
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
return|return
name|NGX_OK
return|;
block|}
name|v
operator|->
name|not_found
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_ssl_variable (ngx_http_request_t * r,ngx_http_variable_value_t * v,uintptr_t data)
name|ngx_http_ssl_variable
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
name|ngx_ssl_variable_handler_pt
name|handler
init|=
operator|(
name|ngx_ssl_variable_handler_pt
operator|)
name|data
decl_stmt|;
name|ngx_str_t
name|s
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|connection
operator|->
name|ssl
condition|)
block|{
if|if
condition|(
name|handler
argument_list|(
name|r
operator|->
name|connection
argument_list|,
name|r
operator|->
name|pool
argument_list|,
operator|&
name|s
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|v
operator|->
name|len
operator|=
name|s
operator|.
name|len
expr_stmt|;
name|v
operator|->
name|data
operator|=
name|s
operator|.
name|data
expr_stmt|;
if|if
condition|(
name|v
operator|->
name|len
condition|)
block|{
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
return|return
name|NGX_OK
return|;
block|}
block|}
name|v
operator|->
name|not_found
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_ssl_add_variables (ngx_conf_t * cf)
name|ngx_http_ssl_add_variables
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
name|ngx_http_ssl_vars
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
name|void
modifier|*
DECL|function|ngx_http_ssl_create_srv_conf (ngx_conf_t * cf)
name|ngx_http_ssl_create_srv_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_ssl_srv_conf_t
modifier|*
name|sscf
decl_stmt|;
name|sscf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_ssl_srv_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|sscf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
comment|/*      * set by ngx_pcalloc():      *      *     sscf->protocols = 0;      *     sscf->certificate = { 0, NULL };      *     sscf->certificate_key = { 0, NULL };      *     sscf->dhparam = { 0, NULL };      *     sscf->ecdh_curve = { 0, NULL };      *     sscf->client_certificate = { 0, NULL };      *     sscf->crl = { 0, NULL };      *     sscf->ciphers = { 0, NULL };      *     sscf->shm_zone = NULL;      */
name|sscf
operator|->
name|enable
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|sscf
operator|->
name|prefer_server_ciphers
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|sscf
operator|->
name|verify
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
name|sscf
operator|->
name|verify_depth
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
name|sscf
operator|->
name|builtin_session_cache
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|sscf
operator|->
name|session_timeout
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
return|return
name|sscf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_ssl_merge_srv_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_ssl_merge_srv_conf
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
name|ngx_http_ssl_srv_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_ssl_srv_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_pool_cleanup_t
modifier|*
name|cln
decl_stmt|;
if|if
condition|(
name|conf
operator|->
name|enable
operator|==
name|NGX_CONF_UNSET
condition|)
block|{
if|if
condition|(
name|prev
operator|->
name|enable
operator|==
name|NGX_CONF_UNSET
condition|)
block|{
name|conf
operator|->
name|enable
operator|=
literal|0
expr_stmt|;
block|}
else|else
block|{
name|conf
operator|->
name|enable
operator|=
name|prev
operator|->
name|enable
expr_stmt|;
name|conf
operator|->
name|file
operator|=
name|prev
operator|->
name|file
expr_stmt|;
name|conf
operator|->
name|line
operator|=
name|prev
operator|->
name|line
expr_stmt|;
block|}
block|}
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|session_timeout
argument_list|,
name|prev
operator|->
name|session_timeout
argument_list|,
literal|300
argument_list|)
expr_stmt|;
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|prefer_server_ciphers
argument_list|,
name|prev
operator|->
name|prefer_server_ciphers
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|ngx_conf_merge_bitmask_value
argument_list|(
name|conf
operator|->
name|protocols
argument_list|,
name|prev
operator|->
name|protocols
argument_list|,
operator|(
name|NGX_CONF_BITMASK_SET
operator||
name|NGX_SSL_SSLv3
operator||
name|NGX_SSL_TLSv1
operator|)
argument_list|)
expr_stmt|;
name|ngx_conf_merge_uint_value
argument_list|(
name|conf
operator|->
name|verify
argument_list|,
name|prev
operator|->
name|verify
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|ngx_conf_merge_uint_value
argument_list|(
name|conf
operator|->
name|verify_depth
argument_list|,
name|prev
operator|->
name|verify_depth
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|certificate
argument_list|,
name|prev
operator|->
name|certificate
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|certificate_key
argument_list|,
name|prev
operator|->
name|certificate_key
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|dhparam
argument_list|,
name|prev
operator|->
name|dhparam
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|client_certificate
argument_list|,
name|prev
operator|->
name|client_certificate
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|crl
argument_list|,
name|prev
operator|->
name|crl
argument_list|,
literal|""
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|ecdh_curve
argument_list|,
name|prev
operator|->
name|ecdh_curve
argument_list|,
name|NGX_DEFAULT_ECDH_CURVE
argument_list|)
expr_stmt|;
name|ngx_conf_merge_str_value
argument_list|(
name|conf
operator|->
name|ciphers
argument_list|,
name|prev
operator|->
name|ciphers
argument_list|,
name|NGX_DEFAULT_CIPHERS
argument_list|)
expr_stmt|;
name|conf
operator|->
name|ssl
operator|.
name|log
operator|=
name|cf
operator|->
name|log
expr_stmt|;
if|if
condition|(
name|conf
operator|->
name|enable
condition|)
block|{
if|if
condition|(
name|conf
operator|->
name|certificate
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no \"ssl_certificate\" is defined for "
literal|"the \"ssl\" directive in %s:%ui"
argument_list|,
name|conf
operator|->
name|file
argument_list|,
name|conf
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|conf
operator|->
name|certificate_key
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no \"ssl_certificate_key\" is defined for "
literal|"the \"ssl\" directive in %s:%ui"
argument_list|,
name|conf
operator|->
name|file
argument_list|,
name|conf
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|conf
operator|->
name|certificate
operator|.
name|len
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_CONF_OK
return|;
block|}
if|if
condition|(
name|conf
operator|->
name|certificate_key
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no \"ssl_certificate_key\" is defined "
literal|"for certificate \"%V\""
argument_list|,
operator|&
name|conf
operator|->
name|certificate
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
if|if
condition|(
name|ngx_ssl_create
argument_list|(
operator|&
name|conf
operator|->
name|ssl
argument_list|,
name|conf
operator|->
name|protocols
argument_list|,
name|conf
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
ifdef|#
directive|ifdef
name|SSL_CTRL_SET_TLSEXT_HOSTNAME
if|if
condition|(
name|SSL_CTX_set_tlsext_servername_callback
argument_list|(
name|conf
operator|->
name|ssl
operator|.
name|ctx
argument_list|,
name|ngx_http_ssl_servername
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"nginx was built with SNI support, however, now it is linked "
literal|"dynamically to an OpenSSL library which has no tlsext support, "
literal|"therefore SNI is not available"
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|cln
operator|=
name|ngx_pool_cleanup_add
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|cln
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|cln
operator|->
name|handler
operator|=
name|ngx_ssl_cleanup_ctx
expr_stmt|;
name|cln
operator|->
name|data
operator|=
operator|&
name|conf
operator|->
name|ssl
expr_stmt|;
if|if
condition|(
name|ngx_ssl_certificate
argument_list|(
name|cf
argument_list|,
operator|&
name|conf
operator|->
name|ssl
argument_list|,
operator|&
name|conf
operator|->
name|certificate
argument_list|,
operator|&
name|conf
operator|->
name|certificate_key
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|SSL_CTX_set_cipher_list
argument_list|(
name|conf
operator|->
name|ssl
operator|.
name|ctx
argument_list|,
operator|(
specifier|const
name|char
operator|*
operator|)
name|conf
operator|->
name|ciphers
operator|.
name|data
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_ssl_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"SSL_CTX_set_cipher_list(\"%V\") failed"
argument_list|,
operator|&
name|conf
operator|->
name|ciphers
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|conf
operator|->
name|verify
condition|)
block|{
if|if
condition|(
name|conf
operator|->
name|client_certificate
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"no ssl_client_certificate for ssl_client_verify"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|ngx_ssl_client_certificate
argument_list|(
name|cf
argument_list|,
operator|&
name|conf
operator|->
name|ssl
argument_list|,
operator|&
name|conf
operator|->
name|client_certificate
argument_list|,
name|conf
operator|->
name|verify_depth
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|ngx_ssl_crl
argument_list|(
name|cf
argument_list|,
operator|&
name|conf
operator|->
name|ssl
argument_list|,
operator|&
name|conf
operator|->
name|crl
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
if|if
condition|(
name|conf
operator|->
name|prefer_server_ciphers
condition|)
block|{
name|SSL_CTX_set_options
argument_list|(
name|conf
operator|->
name|ssl
operator|.
name|ctx
argument_list|,
name|SSL_OP_CIPHER_SERVER_PREFERENCE
argument_list|)
expr_stmt|;
block|}
comment|/* a temporary 512-bit RSA key is required for export versions of MSIE */
name|SSL_CTX_set_tmp_rsa_callback
argument_list|(
name|conf
operator|->
name|ssl
operator|.
name|ctx
argument_list|,
name|ngx_ssl_rsa512_key_callback
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_ssl_dhparam
argument_list|(
name|cf
argument_list|,
operator|&
name|conf
operator|->
name|ssl
argument_list|,
operator|&
name|conf
operator|->
name|dhparam
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|ngx_ssl_ecdh_curve
argument_list|(
name|cf
argument_list|,
operator|&
name|conf
operator|->
name|ssl
argument_list|,
operator|&
name|conf
operator|->
name|ecdh_curve
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|builtin_session_cache
argument_list|,
name|prev
operator|->
name|builtin_session_cache
argument_list|,
name|NGX_SSL_NONE_SCACHE
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|->
name|shm_zone
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|shm_zone
operator|=
name|prev
operator|->
name|shm_zone
expr_stmt|;
block|}
if|if
condition|(
name|ngx_ssl_session_cache
argument_list|(
operator|&
name|conf
operator|->
name|ssl
argument_list|,
operator|&
name|ngx_http_ssl_sess_id_ctx
argument_list|,
name|conf
operator|->
name|builtin_session_cache
argument_list|,
name|conf
operator|->
name|shm_zone
argument_list|,
name|conf
operator|->
name|session_timeout
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
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
DECL|function|ngx_http_ssl_enable (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_ssl_enable
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
name|ngx_http_ssl_srv_conf_t
modifier|*
name|sscf
init|=
name|conf
decl_stmt|;
name|char
modifier|*
name|rv
decl_stmt|;
name|rv
operator|=
name|ngx_conf_set_flag_slot
argument_list|(
name|cf
argument_list|,
name|cmd
argument_list|,
name|conf
argument_list|)
expr_stmt|;
if|if
condition|(
name|rv
operator|!=
name|NGX_CONF_OK
condition|)
block|{
return|return
name|rv
return|;
block|}
name|sscf
operator|->
name|file
operator|=
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
expr_stmt|;
name|sscf
operator|->
name|line
operator|=
name|cf
operator|->
name|conf_file
operator|->
name|line
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
DECL|function|ngx_http_ssl_session_cache (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_ssl_session_cache
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
name|ngx_http_ssl_srv_conf_t
modifier|*
name|sscf
init|=
name|conf
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
name|name
decl_stmt|,
name|size
decl_stmt|;
name|ngx_int_t
name|n
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|j
decl_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|cf
operator|->
name|args
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"off"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|sscf
operator|->
name|builtin_session_cache
operator|=
name|NGX_SSL_NO_SCACHE
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"none"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|sscf
operator|->
name|builtin_session_cache
operator|=
name|NGX_SSL_NONE_SCACHE
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"builtin"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|sscf
operator|->
name|builtin_session_cache
operator|=
name|NGX_SSL_DFLT_BUILTIN_SCACHE
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|value
index|[
name|i
index|]
operator|.
name|len
operator|>
sizeof|sizeof
argument_list|(
literal|"builtin:"
argument_list|)
operator|-
literal|1
operator|&&
name|ngx_strncmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"builtin:"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"builtin:"
argument_list|)
operator|-
literal|1
argument_list|)
operator|==
literal|0
condition|)
block|{
name|n
operator|=
name|ngx_atoi
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
sizeof|sizeof
argument_list|(
literal|"builtin:"
argument_list|)
operator|-
literal|1
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
operator|(
sizeof|sizeof
argument_list|(
literal|"builtin:"
argument_list|)
operator|-
literal|1
operator|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
name|sscf
operator|->
name|builtin_session_cache
operator|=
name|n
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|value
index|[
name|i
index|]
operator|.
name|len
operator|>
sizeof|sizeof
argument_list|(
literal|"shared:"
argument_list|)
operator|-
literal|1
operator|&&
name|ngx_strncmp
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|,
literal|"shared:"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"shared:"
argument_list|)
operator|-
literal|1
argument_list|)
operator|==
literal|0
condition|)
block|{
name|len
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|j
operator|=
sizeof|sizeof
argument_list|(
literal|"shared:"
argument_list|)
operator|-
literal|1
init|;
name|j
operator|<
name|value
index|[
name|i
index|]
operator|.
name|len
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
name|j
index|]
operator|==
literal|':'
condition|)
block|{
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
name|j
index|]
operator|=
literal|'\0'
expr_stmt|;
break|break;
block|}
name|len
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|len
operator|==
literal|0
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
name|name
operator|.
name|len
operator|=
name|len
expr_stmt|;
name|name
operator|.
name|data
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
sizeof|sizeof
argument_list|(
literal|"shared:"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|size
operator|.
name|len
operator|=
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
name|j
operator|-
literal|1
expr_stmt|;
name|size
operator|.
name|data
operator|=
name|name
operator|.
name|data
operator|+
name|len
operator|+
literal|1
expr_stmt|;
name|n
operator|=
name|ngx_parse_size
argument_list|(
operator|&
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
if|if
condition|(
name|n
operator|<
operator|(
name|ngx_int_t
operator|)
operator|(
literal|8
operator|*
name|ngx_pagesize
operator|)
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
literal|"session cache \"%V\" is too small"
argument_list|,
operator|&
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|sscf
operator|->
name|shm_zone
operator|=
name|ngx_shared_memory_add
argument_list|(
name|cf
argument_list|,
operator|&
name|name
argument_list|,
name|n
argument_list|,
operator|&
name|ngx_http_ssl_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|sscf
operator|->
name|shm_zone
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|sscf
operator|->
name|shm_zone
operator|->
name|init
operator|=
name|ngx_ssl_session_cache_init
expr_stmt|;
continue|continue;
block|}
goto|goto
name|invalid
goto|;
block|}
if|if
condition|(
name|sscf
operator|->
name|shm_zone
operator|&&
name|sscf
operator|->
name|builtin_session_cache
operator|==
name|NGX_CONF_UNSET
condition|)
block|{
name|sscf
operator|->
name|builtin_session_cache
operator|=
name|NGX_SSL_NO_BUILTIN_SCACHE
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
name|invalid
label|:
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid session cache \"%V\""
argument_list|,
operator|&
name|value
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
end_function

end_unit

