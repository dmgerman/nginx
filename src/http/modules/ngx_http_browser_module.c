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
comment|/*  * The module can check browser versions conforming to the following formats:  * X, X.X, X.X.X, and X.X.X.X.  The maximum values of each format may be  * 4000, 4000.99, 4000.99.99, and 4000.99.99.99.  */
end_comment

begin_typedef
DECL|struct|__anon2795ddfd0108
typedef|typedef
struct|struct
block|{
DECL|member|browser
name|u_char
name|browser
index|[
literal|12
index|]
decl_stmt|;
DECL|member|skip
name|size_t
name|skip
decl_stmt|;
DECL|member|add
name|size_t
name|add
decl_stmt|;
DECL|member|name
name|u_char
name|name
index|[
literal|12
index|]
decl_stmt|;
DECL|typedef|ngx_http_modern_browser_mask_t
block|}
name|ngx_http_modern_browser_mask_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2795ddfd0208
typedef|typedef
struct|struct
block|{
DECL|member|version
name|ngx_uint_t
name|version
decl_stmt|;
DECL|member|skip
name|size_t
name|skip
decl_stmt|;
DECL|member|add
name|size_t
name|add
decl_stmt|;
DECL|member|name
name|u_char
name|name
index|[
literal|12
index|]
decl_stmt|;
DECL|typedef|ngx_http_modern_browser_t
block|}
name|ngx_http_modern_browser_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2795ddfd0308
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|handler
name|ngx_http_get_variable_pt
name|handler
decl_stmt|;
DECL|typedef|ngx_http_browser_t
block|}
name|ngx_http_browser_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2795ddfd0408
typedef|typedef
struct|struct
block|{
DECL|member|modern_browsers
name|ngx_array_t
modifier|*
name|modern_browsers
decl_stmt|;
DECL|member|value
name|ngx_http_variable_value_t
modifier|*
name|value
decl_stmt|;
DECL|typedef|ngx_http_browser_conf_t
block|}
name|ngx_http_browser_conf_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_http_msie_variable
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
name|ngx_http_browser_add_variable
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
name|ngx_http_browser_create_conf
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
name|ngx_http_browser_merge_conf
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
name|int
name|ngx_libc_cdecl
name|ngx_http_modern_browser_sort
parameter_list|(
specifier|const
name|void
modifier|*
name|one
parameter_list|,
specifier|const
name|void
modifier|*
name|two
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_modern_browser
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
name|ngx_http_modern_browser_value
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
DECL|variable|ngx_http_browser_commands
specifier|static
name|ngx_command_t
name|ngx_http_browser_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"modern_browser"
argument_list|)
block|,
name|NGX_HTTP_MAIN_CONF
operator||
name|NGX_HTTP_SRV_CONF
operator||
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_TAKE2
block|,
name|ngx_http_modern_browser
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
literal|"modern_browser_value"
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
name|ngx_http_modern_browser_value
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
DECL|variable|ngx_http_browser_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_browser_module_ctx
init|=
block|{
name|ngx_http_browser_add_variable
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
name|NULL
block|,
comment|/* create server configuration */
name|NULL
block|,
comment|/* merge server configuration */
name|ngx_http_browser_create_conf
block|,
comment|/* create location configuration */
name|ngx_http_browser_merge_conf
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_browser_module
name|ngx_module_t
name|ngx_http_browser_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_browser_module_ctx
block|,
comment|/* module context */
name|ngx_http_browser_commands
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
DECL|variable|ngx_http_modern_browser_masks
specifier|static
name|ngx_http_modern_browser_mask_t
name|ngx_http_modern_browser_masks
index|[]
init|=
block|{
comment|/* Opera must be the first browser to check */
comment|/*      * "Opera/7.50 (X11; FreeBSD i386; U)  [en]"      * "Mozilla/5.0 (X11; FreeBSD i386; U) Opera 7.50  [en]"      * "Mozilla/4.0 (compatible; MSIE 6.0; X11; FreeBSD i386) Opera 7.50  [en]"      * "Opera/8.0 (Windows NT 5.1; U; ru)"      * "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0; en) Opera 8.0"      * "Opera/9.01 (X11; FreeBSD 6 i386; U; en)"      */
block|{
literal|"opera"
block|,
literal|0
block|,
sizeof|sizeof
argument_list|(
literal|"Opera "
argument_list|)
operator|-
literal|1
block|,
literal|"Opera"
block|}
block|,
comment|/* "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)" */
block|{
literal|"msie"
block|,
sizeof|sizeof
argument_list|(
literal|"Mozilla/4.0 (compatible; "
argument_list|)
operator|-
literal|1
block|,
sizeof|sizeof
argument_list|(
literal|"MSIE "
argument_list|)
operator|-
literal|1
block|,
literal|"MSIE "
block|}
block|,
comment|/*      * "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.0.0) Gecko/20020610"      * "Mozilla/5.0 (Windows; U; Windows NT 5.1; ru-RU; rv:1.5) Gecko/20031006"      * "Mozilla/5.0 (Windows; U; Windows NT 5.1; ru-RU; rv:1.6) Gecko/20040206      *              Firefox/0.8"      * "Mozilla/5.0 (Windows; U; Windows NT 5.1; ru-RU; rv:1.7.8)      *              Gecko/20050511 Firefox/1.0.4"      * "Mozilla/5.0 (X11; U; FreeBSD i386; en-US; rv:1.8.0.5) Gecko/20060729      *              Firefox/1.5.0.5"      */
block|{
literal|"gecko"
block|,
sizeof|sizeof
argument_list|(
literal|"Mozilla/5.0 ("
argument_list|)
operator|-
literal|1
block|,
sizeof|sizeof
argument_list|(
literal|"rv:"
argument_list|)
operator|-
literal|1
block|,
literal|"rv:"
block|}
block|,
comment|/*      * "Mozilla/5.0 (Macintosh; U; PPC Mac OS X; ru-ru) AppleWebKit/125.2      *              (KHTML, like Gecko) Safari/125.7"      * "Mozilla/5.0 (SymbianOS/9.1; U; en-us) AppleWebKit/413      *              (KHTML, like Gecko) Safari/413"      * "Mozilla/5.0 (Macintosh; U; PPC Mac OS X; en) AppleWebKit/418      *              (KHTML, like Gecko) Safari/417.9.3"      * "Mozilla/5.0 (Macintosh; U; PPC Mac OS X; ru-ru) AppleWebKit/418.8      *              (KHTML, like Gecko) Safari/419.3"      */
block|{
literal|"safari"
block|,
sizeof|sizeof
argument_list|(
literal|"Mozilla/5.0 ("
argument_list|)
operator|-
literal|1
block|,
sizeof|sizeof
argument_list|(
literal|"Safari/"
argument_list|)
operator|-
literal|1
block|,
literal|"Safari/"
block|}
block|,
comment|/*      * "Mozilla/5.0 (compatible; Konqueror/3.1; Linux)"      * "Mozilla/5.0 (compatible; Konqueror/3.4; Linux) KHTML/3.4.2 (like Gecko)"      * "Mozilla/5.0 (compatible; Konqueror/3.5; FreeBSD) KHTML/3.5.1      *              (like Gecko)"      */
block|{
literal|"konqueror"
block|,
sizeof|sizeof
argument_list|(
literal|"Mozilla/5.0 (compatible; "
argument_list|)
operator|-
literal|1
block|,
sizeof|sizeof
argument_list|(
literal|"Konqueror/"
argument_list|)
operator|-
literal|1
block|,
literal|"Konqueror/"
block|}
block|,
block|{
literal|""
block|,
literal|0
block|,
literal|0
block|,
literal|""
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_browsers
specifier|static
name|ngx_http_browser_t
name|ngx_http_browsers
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"msie"
argument_list|)
block|,
name|ngx_http_msie_variable
block|}
block|,
block|{
name|ngx_null_string
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_browser_variable (ngx_http_request_t * r,ngx_http_variable_value_t * v,uintptr_t data)
name|ngx_http_browser_variable
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
name|u_char
modifier|*
name|name
decl_stmt|,
modifier|*
name|ua
decl_stmt|,
modifier|*
name|last
decl_stmt|,
name|c
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|version
decl_stmt|,
name|ver
decl_stmt|,
name|scale
decl_stmt|;
name|ngx_http_browser_conf_t
modifier|*
name|cf
decl_stmt|;
name|ngx_http_modern_browser_t
modifier|*
name|browsers
decl_stmt|;
name|cf
operator|=
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_browser_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|cf
operator|->
name|modern_browsers
operator|==
name|NULL
operator|||
name|cf
operator|->
name|value
operator|==
name|NULL
condition|)
block|{
operator|*
name|v
operator|=
name|ngx_http_variable_null_value
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|#
directive|if
literal|0
block_content|if (!r->headers_in.msie&& !r->headers_in.opera&& !r->headers_in.gecko&& !r->headers_in.konqueror)     {         *v = ngx_http_variable_null_value;         return NGX_OK;     }
endif|#
directive|endif
if|if
condition|(
name|r
operator|->
name|headers_in
operator|.
name|user_agent
operator|==
name|NULL
condition|)
block|{
operator|*
name|v
operator|=
name|ngx_http_variable_null_value
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|ua
operator|=
name|r
operator|->
name|headers_in
operator|.
name|user_agent
operator|->
name|value
operator|.
name|data
expr_stmt|;
name|last
operator|=
name|ua
operator|+
name|r
operator|->
name|headers_in
operator|.
name|user_agent
operator|->
name|value
operator|.
name|len
expr_stmt|;
name|browsers
operator|=
name|cf
operator|->
name|modern_browsers
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
name|cf
operator|->
name|modern_browsers
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|name
operator|=
name|ua
operator|+
name|browsers
index|[
name|i
index|]
operator|.
name|skip
expr_stmt|;
if|if
condition|(
name|name
operator|>=
name|last
condition|)
block|{
continue|continue;
block|}
name|name
operator|=
operator|(
name|u_char
operator|*
operator|)
name|ngx_strstr
argument_list|(
name|name
argument_list|,
name|browsers
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
operator|==
name|NULL
condition|)
block|{
continue|continue;
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
literal|"browser: \"%s\""
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|name
operator|+=
name|browsers
index|[
name|i
index|]
operator|.
name|add
expr_stmt|;
if|if
condition|(
name|name
operator|>=
name|last
condition|)
block|{
continue|continue;
block|}
name|ngx_log_debug2
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
literal|"version: \"%ui\" \"%s\""
argument_list|,
name|browsers
index|[
name|i
index|]
operator|.
name|version
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|version
operator|=
literal|0
expr_stmt|;
name|ver
operator|=
literal|0
expr_stmt|;
name|scale
operator|=
literal|1000000
expr_stmt|;
while|while
condition|(
name|name
operator|<
name|last
condition|)
block|{
name|c
operator|=
operator|*
name|name
operator|++
expr_stmt|;
if|if
condition|(
name|c
operator|>=
literal|'0'
operator|&&
name|c
operator|<=
literal|'9'
condition|)
block|{
name|ver
operator|=
name|ver
operator|*
literal|10
operator|+
operator|(
name|c
operator|-
literal|'0'
operator|)
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|c
operator|==
literal|'.'
condition|)
block|{
name|version
operator|+=
name|ver
operator|*
name|scale
expr_stmt|;
if|if
condition|(
name|version
operator|>
name|browsers
index|[
name|i
index|]
operator|.
name|version
condition|)
block|{
operator|*
name|v
operator|=
operator|*
name|cf
operator|->
name|value
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|ver
operator|=
literal|0
expr_stmt|;
name|scale
operator|/=
literal|100
expr_stmt|;
continue|continue;
block|}
break|break;
block|}
name|version
operator|+=
name|ver
operator|*
name|scale
expr_stmt|;
name|ngx_log_debug2
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
literal|"version: \"%ui\" \"%ui\""
argument_list|,
name|browsers
index|[
name|i
index|]
operator|.
name|version
argument_list|,
name|version
argument_list|)
expr_stmt|;
if|if
condition|(
name|version
operator|>=
name|browsers
index|[
name|i
index|]
operator|.
name|version
condition|)
block|{
operator|*
name|v
operator|=
operator|*
name|cf
operator|->
name|value
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
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
DECL|function|ngx_http_msie_variable (ngx_http_request_t * r,ngx_http_variable_value_t * v,uintptr_t data)
name|ngx_http_msie_variable
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
name|headers_in
operator|.
name|msie
condition|)
block|{
operator|*
name|v
operator|=
name|ngx_http_variable_true_value
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
DECL|function|ngx_http_browser_add_variable (ngx_conf_t * cf)
name|ngx_http_browser_add_variable
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_browser_t
modifier|*
name|browser
decl_stmt|;
name|ngx_http_variable_t
modifier|*
name|var
decl_stmt|;
for|for
control|(
name|browser
operator|=
name|ngx_http_browsers
init|;
name|browser
operator|->
name|name
operator|.
name|len
condition|;
name|browser
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
name|browser
operator|->
name|name
argument_list|,
name|NGX_HTTP_VAR_CHANGABLE
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
name|browser
operator|->
name|handler
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
DECL|function|ngx_http_browser_create_conf (ngx_conf_t * cf)
name|ngx_http_browser_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_http_browser_conf_t
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
name|ngx_http_browser_conf_t
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
comment|/*      * set by ngx_pcalloc():      *      *     conf->browsers = NULL;      *     conf->value = NULL;      */
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_browser_merge_conf (ngx_conf_t * cf,void * parent,void * child)
name|ngx_http_browser_merge_conf
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
name|ngx_http_browser_conf_t
modifier|*
name|prev
init|=
name|parent
decl_stmt|;
name|ngx_http_browser_conf_t
modifier|*
name|conf
init|=
name|child
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|;
name|ngx_http_modern_browser_t
modifier|*
name|browsers
decl_stmt|,
modifier|*
name|opera
decl_stmt|;
comment|/*      * At the merge the skip field is used to store the browser slot,      * it will be used in sorting and then will overwritten      * with a real skip value.  The zero value means Opera.      */
if|if
condition|(
name|conf
operator|->
name|modern_browsers
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|modern_browsers
operator|=
name|prev
operator|->
name|modern_browsers
expr_stmt|;
block|}
else|else
block|{
name|browsers
operator|=
name|conf
operator|->
name|modern_browsers
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
name|conf
operator|->
name|modern_browsers
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|browsers
index|[
name|i
index|]
operator|.
name|skip
operator|==
literal|0
condition|)
block|{
goto|goto
name|found
goto|;
block|}
block|}
comment|/*          * Opera may contain MSIE string, so if Opera was not enumerated          * as modern browsers, then add it and set a unreachable version          */
name|opera
operator|=
name|ngx_array_push
argument_list|(
name|conf
operator|->
name|modern_browsers
argument_list|)
expr_stmt|;
if|if
condition|(
name|opera
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|opera
operator|->
name|skip
operator|=
literal|0
expr_stmt|;
name|opera
operator|->
name|version
operator|=
literal|4001000000U
expr_stmt|;
name|browsers
operator|=
name|conf
operator|->
name|modern_browsers
operator|->
name|elts
expr_stmt|;
name|found
label|:
name|ngx_qsort
argument_list|(
name|browsers
argument_list|,
operator|(
name|size_t
operator|)
name|conf
operator|->
name|modern_browsers
operator|->
name|nelts
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_modern_browser_t
argument_list|)
argument_list|,
name|ngx_http_modern_browser_sort
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|conf
operator|->
name|modern_browsers
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|n
operator|=
name|browsers
index|[
name|i
index|]
operator|.
name|skip
expr_stmt|;
name|browsers
index|[
name|i
index|]
operator|.
name|skip
operator|=
name|ngx_http_modern_browser_masks
index|[
name|n
index|]
operator|.
name|skip
expr_stmt|;
name|browsers
index|[
name|i
index|]
operator|.
name|add
operator|=
name|ngx_http_modern_browser_masks
index|[
name|n
index|]
operator|.
name|add
expr_stmt|;
operator|(
name|void
operator|)
name|ngx_cpystrn
argument_list|(
name|browsers
index|[
name|i
index|]
operator|.
name|name
argument_list|,
name|ngx_http_modern_browser_masks
index|[
name|n
index|]
operator|.
name|name
argument_list|,
literal|12
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|conf
operator|->
name|value
operator|==
name|NULL
condition|)
block|{
name|conf
operator|->
name|value
operator|=
name|prev
operator|->
name|value
expr_stmt|;
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|int
name|ngx_libc_cdecl
DECL|function|ngx_http_modern_browser_sort (const void * one,const void * two)
name|ngx_http_modern_browser_sort
parameter_list|(
specifier|const
name|void
modifier|*
name|one
parameter_list|,
specifier|const
name|void
modifier|*
name|two
parameter_list|)
block|{
name|ngx_http_modern_browser_t
modifier|*
name|first
init|=
operator|(
name|ngx_http_modern_browser_t
operator|*
operator|)
name|one
decl_stmt|;
name|ngx_http_modern_browser_t
modifier|*
name|second
init|=
operator|(
name|ngx_http_modern_browser_t
operator|*
operator|)
name|two
decl_stmt|;
return|return
operator|(
name|first
operator|->
name|skip
operator|-
name|second
operator|->
name|skip
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_modern_browser (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_modern_browser
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
name|ngx_http_browser_conf_t
modifier|*
name|bcf
init|=
name|conf
decl_stmt|;
name|u_char
name|c
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|,
name|version
decl_stmt|,
name|ver
decl_stmt|,
name|scale
decl_stmt|;
name|ngx_http_modern_browser_t
modifier|*
name|browser
decl_stmt|;
name|ngx_http_modern_browser_mask_t
modifier|*
name|mask
decl_stmt|;
if|if
condition|(
name|bcf
operator|->
name|modern_browsers
operator|==
name|NULL
condition|)
block|{
name|bcf
operator|->
name|modern_browsers
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
name|ngx_http_modern_browser_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|bcf
operator|->
name|modern_browsers
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
name|browser
operator|=
name|ngx_array_push
argument_list|(
name|bcf
operator|->
name|modern_browsers
argument_list|)
expr_stmt|;
if|if
condition|(
name|browser
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
name|mask
operator|=
name|ngx_http_modern_browser_masks
expr_stmt|;
for|for
control|(
name|n
operator|=
literal|0
init|;
name|mask
index|[
name|n
index|]
operator|.
name|browser
index|[
literal|0
index|]
operator|!=
literal|'\0'
condition|;
name|n
operator|++
control|)
block|{
if|if
condition|(
name|ngx_strcasecmp
argument_list|(
name|mask
index|[
name|n
index|]
operator|.
name|browser
argument_list|,
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|)
operator|==
literal|0
condition|)
block|{
goto|goto
name|found
goto|;
block|}
block|}
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"unknown browser name \"%V\""
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
name|found
label|:
comment|/*      * at this stage the skip field is used to store the browser slot,      * it will be used in sorting in merge stage and then will overwritten      * with a real value      */
name|browser
operator|->
name|skip
operator|=
name|n
expr_stmt|;
name|version
operator|=
literal|0
expr_stmt|;
name|ver
operator|=
literal|0
expr_stmt|;
name|scale
operator|=
literal|1000000
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|value
index|[
literal|2
index|]
operator|.
name|len
condition|;
name|i
operator|++
control|)
block|{
name|c
operator|=
name|value
index|[
literal|2
index|]
operator|.
name|data
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|c
operator|>=
literal|'0'
operator|&&
name|c
operator|<=
literal|'9'
condition|)
block|{
name|ver
operator|=
name|ver
operator|*
literal|10
operator|+
operator|(
name|c
operator|-
literal|'0'
operator|)
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|c
operator|==
literal|'.'
condition|)
block|{
name|version
operator|+=
name|ver
operator|*
name|scale
expr_stmt|;
name|ver
operator|=
literal|0
expr_stmt|;
name|scale
operator|/=
literal|100
expr_stmt|;
continue|continue;
block|}
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid browser version \"%V\""
argument_list|,
operator|&
name|value
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|version
operator|+=
name|ver
operator|*
name|scale
expr_stmt|;
name|browser
operator|->
name|version
operator|=
name|version
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
DECL|function|ngx_http_modern_browser_value (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_modern_browser_value
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
name|ngx_http_browser_conf_t
modifier|*
name|bcf
init|=
name|conf
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
name|name
decl_stmt|;
name|ngx_http_variable_t
modifier|*
name|var
decl_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|name
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"browser"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|name
operator|.
name|data
operator|=
operator|(
name|u_char
operator|*
operator|)
literal|"browser"
expr_stmt|;
name|var
operator|=
name|ngx_http_add_variable
argument_list|(
name|cf
argument_list|,
operator|&
name|name
argument_list|,
name|NGX_HTTP_VAR_CHANGABLE
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
name|NGX_CONF_ERROR
return|;
block|}
name|var
operator|->
name|get_handler
operator|=
name|ngx_http_browser_variable
expr_stmt|;
name|bcf
operator|->
name|value
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_variable_value_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|bcf
operator|->
name|value
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|bcf
operator|->
name|value
operator|->
name|len
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|len
expr_stmt|;
name|bcf
operator|->
name|value
operator|->
name|valid
operator|=
literal|1
expr_stmt|;
name|bcf
operator|->
name|value
operator|->
name|no_cachable
operator|=
literal|0
expr_stmt|;
name|bcf
operator|->
name|value
operator|->
name|not_found
operator|=
literal|0
expr_stmt|;
name|bcf
operator|->
name|value
operator|->
name|data
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|data
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

