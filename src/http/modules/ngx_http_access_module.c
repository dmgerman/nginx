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
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon29b420610108
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
DECL|member|deny
name|ngx_uint_t
name|deny
decl_stmt|;
comment|/* unsigned  deny:1; */
DECL|typedef|ngx_http_access_rule_t
block|}
name|ngx_http_access_rule_t
typedef|;
end_typedef

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
end_if

begin_typedef
DECL|struct|__anon29b420610208
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|struct
name|in6_addr
name|addr
decl_stmt|;
DECL|member|mask
name|struct
name|in6_addr
name|mask
decl_stmt|;
DECL|member|deny
name|ngx_uint_t
name|deny
decl_stmt|;
comment|/* unsigned  deny:1; */
DECL|typedef|ngx_http_access_rule6_t
block|}
name|ngx_http_access_rule6_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
end_if

begin_typedef
DECL|struct|__anon29b420610308
typedef|typedef
struct|struct
block|{
DECL|member|deny
name|ngx_uint_t
name|deny
decl_stmt|;
comment|/* unsigned  deny:1; */
DECL|typedef|ngx_http_access_rule_un_t
block|}
name|ngx_http_access_rule_un_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon29b420610408
typedef|typedef
struct|struct
block|{
DECL|member|rules
name|ngx_array_t
modifier|*
name|rules
decl_stmt|;
comment|/* array of ngx_http_access_rule_t */
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
DECL|member|rules6
name|ngx_array_t
modifier|*
name|rules6
decl_stmt|;
comment|/* array of ngx_http_access_rule6_t */
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
DECL|member|rules_un
name|ngx_array_t
modifier|*
name|rules_un
decl_stmt|;
comment|/* array of ngx_http_access_rule_un_t */
endif|#
directive|endif
DECL|typedef|ngx_http_access_loc_conf_t
block|}
name|ngx_http_access_loc_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_access_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_access_inet
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_access_loc_conf_t
modifier|*
name|alcf
parameter_list|,
name|in_addr_t
name|addr
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
end_if

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_access_inet6
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_access_loc_conf_t
modifier|*
name|alcf
parameter_list|,
name|u_char
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
end_if

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_access_unix
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_access_loc_conf_t
modifier|*
name|alcf
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_access_found
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_uint_t
name|deny
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_access_rule
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
name|ngx_http_access_create_loc_conf
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
name|ngx_http_access_merge_loc_conf
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
name|ngx_http_access_init
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_access_commands
specifier|static
name|ngx_command_t
name|ngx_http_access_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"allow"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_HTTP_LMT_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_access_rule
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
literal|"deny"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_HTTP_LMT_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_http_access_rule
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
DECL|variable|ngx_http_access_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_access_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|ngx_http_access_init
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
name|ngx_http_access_create_loc_conf
block|,
comment|/* create location configuration */
name|ngx_http_access_merge_loc_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_access_module
name|ngx_module_t
name|ngx_http_access_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_access_module_ctx
block|,
comment|/* module context */
name|ngx_http_access_commands
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
DECL|function|ngx_http_access_handler (ngx_http_request_t * r)
name|ngx_http_access_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|struct
name|sockaddr_in
modifier|*
name|sin
decl_stmt|;
name|ngx_http_access_loc_conf_t
modifier|*
name|alcf
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
name|u_char
modifier|*
name|p
decl_stmt|;
name|in_addr_t
name|addr
decl_stmt|;
name|struct
name|sockaddr_in6
modifier|*
name|sin6
decl_stmt|;
endif|#
directive|endif
name|alcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_access_module
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|r
operator|->
name|connection
operator|->
name|sockaddr
operator|->
name|sa_family
condition|)
block|{
case|case
name|AF_INET
case|:
if|if
condition|(
name|alcf
operator|->
name|rules
condition|)
block|{
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
return|return
name|ngx_http_access_inet
argument_list|(
name|r
argument_list|,
name|alcf
argument_list|,
name|sin
operator|->
name|sin_addr
operator|.
name|s_addr
argument_list|)
return|;
block|}
break|break;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
case|case
name|AF_INET6
case|:
name|sin6
operator|=
operator|(
expr|struct
name|sockaddr_in6
operator|*
operator|)
name|r
operator|->
name|connection
operator|->
name|sockaddr
expr_stmt|;
name|p
operator|=
name|sin6
operator|->
name|sin6_addr
operator|.
name|s6_addr
expr_stmt|;
if|if
condition|(
name|alcf
operator|->
name|rules
operator|&&
name|IN6_IS_ADDR_V4MAPPED
argument_list|(
operator|&
name|sin6
operator|->
name|sin6_addr
argument_list|)
condition|)
block|{
name|addr
operator|=
name|p
index|[
literal|12
index|]
operator|<<
literal|24
expr_stmt|;
name|addr
operator|+=
name|p
index|[
literal|13
index|]
operator|<<
literal|16
expr_stmt|;
name|addr
operator|+=
name|p
index|[
literal|14
index|]
operator|<<
literal|8
expr_stmt|;
name|addr
operator|+=
name|p
index|[
literal|15
index|]
expr_stmt|;
return|return
name|ngx_http_access_inet
argument_list|(
name|r
argument_list|,
name|alcf
argument_list|,
name|htonl
argument_list|(
name|addr
argument_list|)
argument_list|)
return|;
block|}
if|if
condition|(
name|alcf
operator|->
name|rules6
condition|)
block|{
return|return
name|ngx_http_access_inet6
argument_list|(
name|r
argument_list|,
name|alcf
argument_list|,
name|p
argument_list|)
return|;
block|}
break|break;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
case|case
name|AF_UNIX
case|:
if|if
condition|(
name|alcf
operator|->
name|rules_un
condition|)
block|{
return|return
name|ngx_http_access_unix
argument_list|(
name|r
argument_list|,
name|alcf
argument_list|)
return|;
block|}
break|break;
endif|#
directive|endif
block|}
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_access_inet (ngx_http_request_t * r,ngx_http_access_loc_conf_t * alcf,in_addr_t addr)
name|ngx_http_access_inet
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_access_loc_conf_t
modifier|*
name|alcf
parameter_list|,
name|in_addr_t
name|addr
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_http_access_rule_t
modifier|*
name|rule
decl_stmt|;
name|rule
operator|=
name|alcf
operator|->
name|rules
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
name|alcf
operator|->
name|rules
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
literal|"access: %08XD %08XD %08XD"
argument_list|,
name|addr
argument_list|,
name|rule
index|[
name|i
index|]
operator|.
name|mask
argument_list|,
name|rule
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
name|addr
operator|&
name|rule
index|[
name|i
index|]
operator|.
name|mask
operator|)
operator|==
name|rule
index|[
name|i
index|]
operator|.
name|addr
condition|)
block|{
return|return
name|ngx_http_access_found
argument_list|(
name|r
argument_list|,
name|rule
index|[
name|i
index|]
operator|.
name|deny
argument_list|)
return|;
block|}
block|}
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
end_if

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_access_inet6 (ngx_http_request_t * r,ngx_http_access_loc_conf_t * alcf,u_char * p)
name|ngx_http_access_inet6
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_access_loc_conf_t
modifier|*
name|alcf
parameter_list|,
name|u_char
modifier|*
name|p
parameter_list|)
block|{
name|ngx_uint_t
name|n
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_http_access_rule6_t
modifier|*
name|rule6
decl_stmt|;
name|rule6
operator|=
name|alcf
operator|->
name|rules6
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
name|alcf
operator|->
name|rules6
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
block|{
name|size_t
name|cl
decl_stmt|,
name|ml
decl_stmt|,
name|al
decl_stmt|;
name|u_char
name|ct
index|[
name|NGX_INET6_ADDRSTRLEN
index|]
decl_stmt|;
name|u_char
name|mt
index|[
name|NGX_INET6_ADDRSTRLEN
index|]
decl_stmt|;
name|u_char
name|at
index|[
name|NGX_INET6_ADDRSTRLEN
index|]
decl_stmt|;
name|cl
operator|=
name|ngx_inet6_ntop
argument_list|(
name|p
argument_list|,
name|ct
argument_list|,
name|NGX_INET6_ADDRSTRLEN
argument_list|)
expr_stmt|;
name|ml
operator|=
name|ngx_inet6_ntop
argument_list|(
name|rule6
index|[
name|i
index|]
operator|.
name|mask
operator|.
name|s6_addr
argument_list|,
name|mt
argument_list|,
name|NGX_INET6_ADDRSTRLEN
argument_list|)
expr_stmt|;
name|al
operator|=
name|ngx_inet6_ntop
argument_list|(
name|rule6
index|[
name|i
index|]
operator|.
name|addr
operator|.
name|s6_addr
argument_list|,
name|at
argument_list|,
name|NGX_INET6_ADDRSTRLEN
argument_list|)
expr_stmt|;
name|ngx_log_debug6
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
literal|"access: %*s %*s %*s"
argument_list|,
name|cl
argument_list|,
name|ct
argument_list|,
name|ml
argument_list|,
name|mt
argument_list|,
name|al
argument_list|,
name|at
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
for|for
control|(
name|n
operator|=
literal|0
init|;
name|n
operator|<
literal|16
condition|;
name|n
operator|++
control|)
block|{
if|if
condition|(
operator|(
name|p
index|[
name|n
index|]
operator|&
name|rule6
index|[
name|i
index|]
operator|.
name|mask
operator|.
name|s6_addr
index|[
name|n
index|]
operator|)
operator|!=
name|rule6
index|[
name|i
index|]
operator|.
name|addr
operator|.
name|s6_addr
index|[
name|n
index|]
condition|)
block|{
goto|goto
name|next
goto|;
block|}
block|}
return|return
name|ngx_http_access_found
argument_list|(
name|r
argument_list|,
name|rule6
index|[
name|i
index|]
operator|.
name|deny
argument_list|)
return|;
name|next
label|:
continue|continue;
block|}
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
end_if

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_access_unix (ngx_http_request_t * r,ngx_http_access_loc_conf_t * alcf)
name|ngx_http_access_unix
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_access_loc_conf_t
modifier|*
name|alcf
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_http_access_rule_un_t
modifier|*
name|rule_un
decl_stmt|;
name|rule_un
operator|=
name|alcf
operator|->
name|rules_un
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
name|alcf
operator|->
name|rules_un
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
return|return
name|ngx_http_access_found
argument_list|(
name|r
argument_list|,
name|rule_un
index|[
name|i
index|]
operator|.
name|deny
argument_list|)
return|;
block|}
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_access_found (ngx_http_request_t * r,ngx_uint_t deny)
name|ngx_http_access_found
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_uint_t
name|deny
parameter_list|)
block|{
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
if|if
condition|(
name|deny
condition|)
block|{
name|clcf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|clcf
operator|->
name|satisfy
operator|==
name|NGX_HTTP_SATISFY_ALL
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"access forbidden by rule"
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_HTTP_FORBIDDEN
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_access_rule (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_access_rule
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
name|ngx_http_access_loc_conf_t
modifier|*
name|alcf
init|=
name|conf
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_uint_t
name|all
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_cidr_t
name|cidr
decl_stmt|;
name|ngx_http_access_rule_t
modifier|*
name|rule
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
name|ngx_http_access_rule6_t
modifier|*
name|rule6
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
name|ngx_http_access_rule_un_t
modifier|*
name|rule_un
decl_stmt|;
endif|#
directive|endif
name|ngx_memzero
argument_list|(
operator|&
name|cidr
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_cidr_t
argument_list|)
argument_list|)
expr_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|all
operator|=
operator|(
name|value
index|[
literal|1
index|]
operator|.
name|len
operator|==
literal|3
operator|&&
name|ngx_strcmp
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
literal|"all"
argument_list|)
operator|==
literal|0
operator|)
expr_stmt|;
if|if
condition|(
operator|!
name|all
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
if|if
condition|(
name|value
index|[
literal|1
index|]
operator|.
name|len
operator|==
literal|5
operator|&&
name|ngx_strcmp
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
literal|"unix:"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|cidr
operator|.
name|family
operator|=
name|AF_UNIX
expr_stmt|;
name|rc
operator|=
name|NGX_OK
expr_stmt|;
block|}
else|else
block|{
name|rc
operator|=
name|ngx_ptocidr
argument_list|(
operator|&
name|value
index|[
literal|1
index|]
argument_list|,
operator|&
name|cidr
argument_list|)
expr_stmt|;
block|}
else|#
directive|else
name|rc
operator|=
name|ngx_ptocidr
argument_list|(
operator|&
name|value
index|[
literal|1
index|]
argument_list|,
operator|&
name|cidr
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|rc
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
if|if
condition|(
name|rc
operator|==
name|NGX_DONE
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"low address bits of %V are meaningless"
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|cidr
operator|.
name|family
operator|==
name|AF_INET
operator|||
name|all
condition|)
block|{
if|if
condition|(
name|alcf
operator|->
name|rules
operator|==
name|NULL
condition|)
block|{
name|alcf
operator|->
name|rules
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|4
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_access_rule_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|alcf
operator|->
name|rules
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
name|rule
operator|=
name|ngx_array_push
argument_list|(
name|alcf
operator|->
name|rules
argument_list|)
expr_stmt|;
if|if
condition|(
name|rule
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|rule
operator|->
name|mask
operator|=
name|cidr
operator|.
name|u
operator|.
name|in
operator|.
name|mask
expr_stmt|;
name|rule
operator|->
name|addr
operator|=
name|cidr
operator|.
name|u
operator|.
name|in
operator|.
name|addr
expr_stmt|;
name|rule
operator|->
name|deny
operator|=
operator|(
name|value
index|[
literal|0
index|]
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'d'
operator|)
condition|?
literal|1
else|:
literal|0
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
if|if
condition|(
name|cidr
operator|.
name|family
operator|==
name|AF_INET6
operator|||
name|all
condition|)
block|{
if|if
condition|(
name|alcf
operator|->
name|rules6
operator|==
name|NULL
condition|)
block|{
name|alcf
operator|->
name|rules6
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|4
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_access_rule6_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|alcf
operator|->
name|rules6
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
name|rule6
operator|=
name|ngx_array_push
argument_list|(
name|alcf
operator|->
name|rules6
argument_list|)
expr_stmt|;
if|if
condition|(
name|rule6
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|rule6
operator|->
name|mask
operator|=
name|cidr
operator|.
name|u
operator|.
name|in6
operator|.
name|mask
expr_stmt|;
name|rule6
operator|->
name|addr
operator|=
name|cidr
operator|.
name|u
operator|.
name|in6
operator|.
name|addr
expr_stmt|;
name|rule6
operator|->
name|deny
operator|=
operator|(
name|value
index|[
literal|0
index|]
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'d'
operator|)
condition|?
literal|1
else|:
literal|0
expr_stmt|;
block|}
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
if|if
condition|(
name|cidr
operator|.
name|family
operator|==
name|AF_UNIX
operator|||
name|all
condition|)
block|{
if|if
condition|(
name|alcf
operator|->
name|rules_un
operator|==
name|NULL
condition|)
block|{
name|alcf
operator|->
name|rules_un
operator|=
name|ngx_array_create
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|1
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_access_rule_un_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|alcf
operator|->
name|rules_un
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
name|rule_un
operator|=
name|ngx_array_push
argument_list|(
name|alcf
operator|->
name|rules_un
argument_list|)
expr_stmt|;
if|if
condition|(
name|rule_un
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|rule_un
operator|->
name|deny
operator|=
operator|(
name|value
index|[
literal|0
index|]
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'d'
operator|)
condition|?
literal|1
else|:
literal|0
expr_stmt|;
block|}
endif|#
directive|endif
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_http_access_create_loc_conf (ngx_conf_t * cf)
name|ngx_http_access_create_loc_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_access_loc_conf_t
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
name|ngx_http_access_loc_conf_t
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
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_access_merge_loc_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_access_merge_loc_conf
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
name|ngx_http_access_loc_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_access_loc_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
if|if
condition|(
name|conf
operator|->
name|rules
operator|==
name|NULL
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
operator|&&
name|conf
operator|->
name|rules6
operator|==
name|NULL
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
operator|&&
name|conf
operator|->
name|rules_un
operator|==
name|NULL
endif|#
directive|endif
condition|)
block|{
name|conf
operator|->
name|rules
operator|=
name|prev
operator|->
name|rules
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
name|conf
operator|->
name|rules6
operator|=
name|prev
operator|->
name|rules6
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
name|conf
operator|->
name|rules_un
operator|=
name|prev
operator|->
name|rules_un
expr_stmt|;
endif|#
directive|endif
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_access_init (ngx_conf_t * cf)
name|ngx_http_access_init
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
name|NGX_HTTP_ACCESS_PHASE
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
name|ngx_http_access_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

