begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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
file|<ngx_mail.h>
end_include

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
value|"auto"
end_define

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_mail_ssl_create_conf
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
name|ngx_mail_ssl_merge_conf
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
name|ngx_mail_ssl_enable
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
name|ngx_mail_ssl_starttls
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
name|ngx_mail_ssl_password_file
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
name|ngx_mail_ssl_session_cache
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
DECL|variable|ngx_mail_starttls_state
specifier|static
name|ngx_conf_enum_t
name|ngx_mail_starttls_state
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"off"
argument_list|)
block|,
name|NGX_MAIL_STARTTLS_OFF
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"on"
argument_list|)
block|,
name|NGX_MAIL_STARTTLS_ON
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"only"
argument_list|)
block|,
name|NGX_MAIL_STARTTLS_ONLY
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
DECL|variable|ngx_mail_ssl_protocols
specifier|static
name|ngx_conf_bitmask_t
name|ngx_mail_ssl_protocols
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
name|ngx_string
argument_list|(
literal|"TLSv1.1"
argument_list|)
block|,
name|NGX_SSL_TLSv1_1
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"TLSv1.2"
argument_list|)
block|,
name|NGX_SSL_TLSv1_2
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"TLSv1.3"
argument_list|)
block|,
name|NGX_SSL_TLSv1_3
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
DECL|variable|ngx_mail_ssl_verify
specifier|static
name|ngx_conf_enum_t
name|ngx_mail_ssl_verify
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
name|ngx_string
argument_list|(
literal|"optional_no_ca"
argument_list|)
block|,
literal|3
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
DECL|variable|ngx_mail_ssl_commands
specifier|static
name|ngx_command_t
name|ngx_mail_ssl_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"ssl"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_mail_ssl_enable
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
literal|"starttls"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_mail_ssl_starttls
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|,
name|starttls
argument_list|)
block|,
name|ngx_mail_starttls_state
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_certificate"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_array_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|,
name|certificates
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
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_array_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|,
name|certificate_keys
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_password_file"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_mail_ssl_password_file
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
literal|0
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
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_1MORE
block|,
name|ngx_conf_set_bitmask_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|,
name|protocols
argument_list|)
block|,
operator|&
name|ngx_mail_ssl_protocols
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_ciphers"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
literal|"ssl_prefer_server_ciphers"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_conf_set_flag_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE12
block|,
name|ngx_mail_ssl_session_cache
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_session_tickets"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_FLAG
block|,
name|ngx_conf_set_flag_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|,
name|session_tickets
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_session_ticket_key"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_array_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|,
name|session_ticket_keys
argument_list|)
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
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_sec_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
literal|"ssl_verify_client"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_enum_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|,
name|verify
argument_list|)
block|,
operator|&
name|ngx_mail_ssl_verify
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"ssl_verify_depth"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_num_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
literal|"ssl_trusted_certificate"
argument_list|)
block|,
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|,
name|trusted_certificate
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
name|NGX_MAIL_MAIN_CONF
operator||
name|NGX_MAIL_SRV_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_str_slot
block|,
name|NGX_MAIL_SRV_CONF_OFFSET
block|,
name|offsetof
argument_list|(
name|ngx_mail_ssl_conf_t
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
DECL|variable|ngx_mail_ssl_module_ctx
specifier|static
name|ngx_mail_module_t
name|ngx_mail_ssl_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* protocol */
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|ngx_mail_ssl_create_conf
block|,
comment|/* create server configuration */
name|ngx_mail_ssl_merge_conf
comment|/* merge server configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_mail_ssl_module
name|ngx_module_t
name|ngx_mail_ssl_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_mail_ssl_module_ctx
block|,
comment|/* module context */
name|ngx_mail_ssl_commands
block|,
comment|/* module directives */
name|NGX_MAIL_MODULE
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
DECL|variable|ngx_mail_ssl_sess_id_ctx
specifier|static
name|ngx_str_t
name|ngx_mail_ssl_sess_id_ctx
init|=
name|ngx_string
argument_list|(
literal|"MAIL"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_mail_ssl_create_conf (ngx_conf_t * cf)
name|ngx_mail_ssl_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_mail_ssl_conf_t
modifier|*
name|scf
decl_stmt|;
name|scf
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_mail_ssl_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|scf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
comment|/*      * set by ngx_pcalloc():      *      *     scf->protocols = 0;      *     scf->dhparam = { 0, NULL };      *     scf->ecdh_curve = { 0, NULL };      *     scf->client_certificate = { 0, NULL };      *     scf->trusted_certificate = { 0, NULL };      *     scf->crl = { 0, NULL };      *     scf->ciphers = { 0, NULL };      *     scf->shm_zone = NULL;      */
name|scf
operator|->
name|enable
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|scf
operator|->
name|starttls
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
name|scf
operator|->
name|certificates
operator|=
name|NGX_CONF_UNSET_PTR
expr_stmt|;
name|scf
operator|->
name|certificate_keys
operator|=
name|NGX_CONF_UNSET_PTR
expr_stmt|;
name|scf
operator|->
name|passwords
operator|=
name|NGX_CONF_UNSET_PTR
expr_stmt|;
name|scf
operator|->
name|prefer_server_ciphers
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|scf
operator|->
name|verify
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
name|scf
operator|->
name|verify_depth
operator|=
name|NGX_CONF_UNSET_UINT
expr_stmt|;
name|scf
operator|->
name|builtin_session_cache
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|scf
operator|->
name|session_timeout
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|scf
operator|->
name|session_tickets
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|scf
operator|->
name|session_ticket_keys
operator|=
name|NGX_CONF_UNSET_PTR
expr_stmt|;
return|return
name|scf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_mail_ssl_merge_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_mail_ssl_merge_conf
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
name|ngx_mail_ssl_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_mail_ssl_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|char
modifier|*
name|mode
decl_stmt|;
name|ngx_pool_cleanup_t
modifier|*
name|cln
decl_stmt|;
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|enable
argument_list|,
name|prev
operator|->
name|enable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|ngx_conf_merge_uint_value
argument_list|(
name|conf
operator|->
name|starttls
argument_list|,
name|prev
operator|->
name|starttls
argument_list|,
name|NGX_MAIL_STARTTLS_OFF
argument_list|)
expr_stmt|;
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
name|NGX_SSL_TLSv1
operator||
name|NGX_SSL_TLSv1_1
operator||
name|NGX_SSL_TLSv1_2
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
name|ngx_conf_merge_ptr_value
argument_list|(
name|conf
operator|->
name|certificates
argument_list|,
name|prev
operator|->
name|certificates
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ngx_conf_merge_ptr_value
argument_list|(
name|conf
operator|->
name|certificate_keys
argument_list|,
name|prev
operator|->
name|certificate_keys
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ngx_conf_merge_ptr_value
argument_list|(
name|conf
operator|->
name|passwords
argument_list|,
name|prev
operator|->
name|passwords
argument_list|,
name|NULL
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
name|trusted_certificate
argument_list|,
name|prev
operator|->
name|trusted_certificate
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
name|mode
operator|=
literal|"ssl"
expr_stmt|;
block|}
if|else if
condition|(
name|conf
operator|->
name|starttls
operator|!=
name|NGX_MAIL_STARTTLS_OFF
condition|)
block|{
name|mode
operator|=
literal|"starttls"
expr_stmt|;
block|}
else|else
block|{
name|mode
operator|=
literal|""
expr_stmt|;
block|}
if|if
condition|(
name|conf
operator|->
name|file
operator|==
name|NULL
condition|)
block|{
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
if|if
condition|(
operator|*
name|mode
condition|)
block|{
if|if
condition|(
name|conf
operator|->
name|certificates
operator|==
name|NULL
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
literal|"the \"%s\" directive in %s:%ui"
argument_list|,
name|mode
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
name|certificate_keys
operator|==
name|NULL
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
literal|"the \"%s\" directive in %s:%ui"
argument_list|,
name|mode
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
name|certificate_keys
operator|->
name|nelts
operator|<
name|conf
operator|->
name|certificates
operator|->
name|nelts
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
literal|"for certificate \"%V\" and "
literal|"the \"%s\" directive in %s:%ui"
argument_list|,
operator|(
operator|(
name|ngx_str_t
operator|*
operator|)
name|conf
operator|->
name|certificates
operator|->
name|elts
operator|)
operator|+
name|conf
operator|->
name|certificates
operator|->
name|nelts
operator|-
literal|1
argument_list|,
name|mode
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
name|certificates
operator|==
name|NULL
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
name|certificate_keys
operator|==
name|NULL
operator|||
name|conf
operator|->
name|certificate_keys
operator|->
name|nelts
operator|<
name|conf
operator|->
name|certificates
operator|->
name|nelts
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
operator|(
operator|(
name|ngx_str_t
operator|*
operator|)
name|conf
operator|->
name|certificates
operator|->
name|elts
operator|)
operator|+
name|conf
operator|->
name|certificates
operator|->
name|nelts
operator|-
literal|1
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
name|NULL
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
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
name|ngx_ssl_certificates
argument_list|(
name|cf
argument_list|,
operator|&
name|conf
operator|->
name|ssl
argument_list|,
name|conf
operator|->
name|certificates
argument_list|,
name|conf
operator|->
name|certificate_keys
argument_list|,
name|conf
operator|->
name|passwords
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
operator|&&
name|conf
operator|->
name|verify
operator|!=
literal|3
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
name|ngx_ssl_trusted_certificate
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
name|trusted_certificate
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
name|ngx_ssl_ciphers
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
name|ciphers
argument_list|,
name|conf
operator|->
name|prefer_server_ciphers
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
name|ngx_mail_ssl_sess_id_ctx
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
name|ngx_conf_merge_value
argument_list|(
name|conf
operator|->
name|session_tickets
argument_list|,
name|prev
operator|->
name|session_tickets
argument_list|,
literal|1
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|SSL_OP_NO_TICKET
if|if
condition|(
operator|!
name|conf
operator|->
name|session_tickets
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
name|SSL_OP_NO_TICKET
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|ngx_conf_merge_ptr_value
argument_list|(
name|conf
operator|->
name|session_ticket_keys
argument_list|,
name|prev
operator|->
name|session_ticket_keys
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_ssl_session_ticket_keys
argument_list|(
name|cf
argument_list|,
operator|&
name|conf
operator|->
name|ssl
argument_list|,
name|conf
operator|->
name|session_ticket_keys
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
DECL|function|ngx_mail_ssl_enable (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_ssl_enable
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
name|ngx_mail_ssl_conf_t
modifier|*
name|scf
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
if|if
condition|(
name|scf
operator|->
name|enable
operator|&&
operator|(
name|ngx_int_t
operator|)
name|scf
operator|->
name|starttls
operator|>
name|NGX_MAIL_STARTTLS_OFF
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
literal|"\"starttls\" directive conflicts with \"ssl on\""
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|scf
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
name|scf
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
DECL|function|ngx_mail_ssl_starttls (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_ssl_starttls
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
name|ngx_mail_ssl_conf_t
modifier|*
name|scf
init|=
name|conf
decl_stmt|;
name|char
modifier|*
name|rv
decl_stmt|;
name|rv
operator|=
name|ngx_conf_set_enum_slot
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
if|if
condition|(
name|scf
operator|->
name|enable
operator|==
literal|1
operator|&&
operator|(
name|ngx_int_t
operator|)
name|scf
operator|->
name|starttls
operator|>
name|NGX_MAIL_STARTTLS_OFF
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
literal|"\"ssl\" directive conflicts with \"starttls\""
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|scf
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
name|scf
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
DECL|function|ngx_mail_ssl_password_file (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_ssl_password_file
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
name|ngx_mail_ssl_conf_t
modifier|*
name|scf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
if|if
condition|(
name|scf
operator|->
name|passwords
operator|!=
name|NGX_CONF_UNSET_PTR
condition|)
block|{
return|return
literal|"is duplicate"
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
name|scf
operator|->
name|passwords
operator|=
name|ngx_ssl_read_password_file
argument_list|(
name|cf
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|scf
operator|->
name|passwords
operator|==
name|NULL
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
DECL|function|ngx_mail_ssl_session_cache (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_mail_ssl_session_cache
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
name|ngx_mail_ssl_conf_t
modifier|*
name|scf
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
name|scf
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
name|scf
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
name|scf
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
name|scf
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
name|scf
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
name|ngx_mail_ssl_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|scf
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
name|scf
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
name|scf
operator|->
name|shm_zone
operator|&&
name|scf
operator|->
name|builtin_session_cache
operator|==
name|NGX_CONF_UNSET
condition|)
block|{
name|scf
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

