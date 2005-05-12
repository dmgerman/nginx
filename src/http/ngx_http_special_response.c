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

begin_include
include|#
directive|include
file|<nginx.h>
end_include

begin_decl_stmt
DECL|variable|error_tail
specifier|static
name|u_char
name|error_tail
index|[]
init|=
literal|"<hr><center>"
name|NGINX_VER
literal|"</center>"
name|CRLF
literal|"</body>"
name|CRLF
literal|"</html>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_msie_stub
specifier|static
name|u_char
name|ngx_http_msie_stub
index|[]
init|=
literal|"<!-- The padding to disable MSIE's friendly error page -->"
name|CRLF
literal|"<!-- The padding to disable MSIE's friendly error page -->"
name|CRLF
literal|"<!-- The padding to disable MSIE's friendly error page -->"
name|CRLF
literal|"<!-- The padding to disable MSIE's friendly error page -->"
name|CRLF
literal|"<!-- The padding to disable MSIE's friendly error page -->"
name|CRLF
literal|"<!-- The padding to disable MSIE's friendly error page -->"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_301_page
specifier|static
name|char
name|error_301_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>301 Moved Permanently</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>301 Moved Permanently</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_302_page
specifier|static
name|char
name|error_302_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>302 Found</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>302 Found</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_400_page
specifier|static
name|char
name|error_400_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>400 Bad Request</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>400 Bad Request</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_401_page
specifier|static
name|char
name|error_401_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>401 Authorization Required</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>401 Authorization Required</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_402_page
specifier|static
name|char
name|error_402_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>402 Payment Required</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>402 Payment Required</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_403_page
specifier|static
name|char
name|error_403_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>403 Forbidden</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>403 Forbidden</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_404_page
specifier|static
name|char
name|error_404_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>404 Not Found</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>404 Not Found</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_405_page
specifier|static
name|char
name|error_405_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>405 Not Allowed</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>405 Not Allowed</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_406_page
specifier|static
name|char
name|error_406_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>406 Not Acceptable</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>406 Not Acceptable</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_408_page
specifier|static
name|char
name|error_408_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>408 Request Time-out</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>408 Request Time-out</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_410_page
specifier|static
name|char
name|error_410_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>410 Gone</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>410 Gone</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_413_page
specifier|static
name|char
name|error_413_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>413 Request Entity Too Large</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>413 Request Entity Too Large</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_414_page
specifier|static
name|char
name|error_414_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>414 Request-URI Too Large</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>414 Request-URI Too Large</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_416_page
specifier|static
name|char
name|error_416_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>416 Requested Range Not Satisfiable</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>416 Requested Range Not Satisfiable</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_497_page
specifier|static
name|char
name|error_497_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>400 The plain HTTP request was sent to HTTPS port</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>400 Bad Request</h1></center>"
name|CRLF
literal|"<center>The plain HTTP request was sent to HTTPS port</center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_500_page
specifier|static
name|char
name|error_500_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>500 Internal Server Error</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>500 Internal Server Error</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_501_page
specifier|static
name|char
name|error_501_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>501 Method Not Implemented</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>500 Method Not Implemented</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_502_page
specifier|static
name|char
name|error_502_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>502 Bad Gateway</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>502 Bad Gateway</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_503_page
specifier|static
name|char
name|error_503_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>503 Service Temporarily Unavailable</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>503 Service Temporarily Unavailable</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_504_page
specifier|static
name|char
name|error_504_page
index|[]
init|=
literal|"<html>"
name|CRLF
literal|"<head><title>504 Gateway Time-out</title></head>"
name|CRLF
literal|"<body bgcolor=\"white\">"
name|CRLF
literal|"<center><h1>504 Gateway Time-out</h1></center>"
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|error_pages
specifier|static
name|ngx_str_t
name|error_pages
index|[]
init|=
block|{
comment|/* ngx_null_string, */
comment|/* 300 */
name|ngx_string
argument_list|(
name|error_301_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_302_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 303 */
DECL|macro|NGX_HTTP_LEVEL_300
define|#
directive|define
name|NGX_HTTP_LEVEL_300
value|3
name|ngx_string
argument_list|(
name|error_400_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_401_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_402_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_403_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_404_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_405_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_406_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 407 */
name|ngx_string
argument_list|(
name|error_408_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 409 */
name|ngx_string
argument_list|(
name|error_410_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 411 */
name|ngx_null_string
block|,
comment|/* 412 */
name|ngx_string
argument_list|(
name|error_413_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_414_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 415 */
name|ngx_string
argument_list|(
name|error_416_page
argument_list|)
block|,
DECL|macro|NGX_HTTP_LEVEL_400
define|#
directive|define
name|NGX_HTTP_LEVEL_400
value|17
name|ngx_string
argument_list|(
name|error_497_page
argument_list|)
block|,
comment|/* 497, http to https */
name|ngx_string
argument_list|(
name|error_404_page
argument_list|)
block|,
comment|/* 498, invalid host name */
name|ngx_null_string
block|,
comment|/* 499, client had closed connection */
name|ngx_string
argument_list|(
name|error_500_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_501_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_502_page
argument_list|)
block|,
name|ngx_string
argument_list|(
name|error_503_page
argument_list|)
block|,
name|ngx_string
argument_list|(
argument|error_504_page
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|ngx_int_t
DECL|function|ngx_http_special_response_handler (ngx_http_request_t * r,ngx_int_t error)
name|ngx_http_special_response_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_int_t
name|error
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|err
decl_stmt|,
name|msie_padding
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
name|ngx_chain_t
modifier|*
name|out
decl_stmt|,
modifier|*
name|cl
decl_stmt|;
name|ngx_http_err_page_t
modifier|*
name|err_page
decl_stmt|;
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
name|rc
operator|=
name|ngx_http_discard_body
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_HTTP_INTERNAL_SERVER_ERROR
condition|)
block|{
name|error
operator|=
name|NGX_HTTP_INTERNAL_SERVER_ERROR
expr_stmt|;
block|}
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|error
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|keepalive
operator|!=
literal|0
condition|)
block|{
switch|switch
condition|(
name|error
condition|)
block|{
case|case
name|NGX_HTTP_BAD_REQUEST
case|:
case|case
name|NGX_HTTP_REQUEST_ENTITY_TOO_LARGE
case|:
case|case
name|NGX_HTTP_REQUEST_URI_TOO_LARGE
case|:
case|case
name|NGX_HTTP_TO_HTTPS
case|:
case|case
name|NGX_HTTP_INTERNAL_SERVER_ERROR
case|:
name|r
operator|->
name|keepalive
operator|=
literal|0
expr_stmt|;
block|}
block|}
if|if
condition|(
name|r
operator|->
name|lingering_close
operator|==
literal|1
condition|)
block|{
switch|switch
condition|(
name|error
condition|)
block|{
case|case
name|NGX_HTTP_BAD_REQUEST
case|:
case|case
name|NGX_HTTP_TO_HTTPS
case|:
name|r
operator|->
name|lingering_close
operator|=
literal|0
expr_stmt|;
block|}
block|}
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
name|r
operator|->
name|err_ctx
operator|==
name|NULL
operator|&&
name|clcf
operator|->
name|error_pages
condition|)
block|{
name|err_page
operator|=
name|clcf
operator|->
name|error_pages
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
name|clcf
operator|->
name|error_pages
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|err_page
index|[
name|i
index|]
operator|.
name|status
operator|==
name|error
condition|)
block|{
if|if
condition|(
name|err_page
index|[
name|i
index|]
operator|.
name|overwrite
condition|)
block|{
name|r
operator|->
name|err_status
operator|=
name|err_page
index|[
name|i
index|]
operator|.
name|overwrite
expr_stmt|;
block|}
else|else
block|{
name|r
operator|->
name|err_status
operator|=
name|error
expr_stmt|;
block|}
name|r
operator|->
name|err_ctx
operator|=
name|r
operator|->
name|ctx
expr_stmt|;
return|return
name|ngx_http_internal_redirect
argument_list|(
name|r
argument_list|,
operator|&
name|err_page
index|[
name|i
index|]
operator|.
name|uri
argument_list|,
name|NULL
argument_list|)
return|;
block|}
block|}
block|}
if|if
condition|(
name|error
operator|<
name|NGX_HTTP_BAD_REQUEST
condition|)
block|{
comment|/* 3XX */
name|err
operator|=
name|error
operator|-
name|NGX_HTTP_MOVED_PERMANENTLY
expr_stmt|;
block|}
if|else if
condition|(
name|error
operator|<
name|NGX_HTTP_NGX_CODES
condition|)
block|{
comment|/* 4XX */
name|err
operator|=
name|error
operator|-
name|NGX_HTTP_BAD_REQUEST
operator|+
name|NGX_HTTP_LEVEL_300
expr_stmt|;
block|}
else|else
block|{
comment|/* 49X, 5XX */
name|err
operator|=
name|error
operator|-
name|NGX_HTTP_NGX_CODES
operator|+
name|NGX_HTTP_LEVEL_300
operator|+
name|NGX_HTTP_LEVEL_400
expr_stmt|;
switch|switch
condition|(
name|error
condition|)
block|{
case|case
name|NGX_HTTP_TO_HTTPS
case|:
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|NGX_HTTP_BAD_REQUEST
expr_stmt|;
name|error
operator|=
name|NGX_HTTP_BAD_REQUEST
expr_stmt|;
break|break;
case|case
name|NGX_HTTP_INVALID_HOST
case|:
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|NGX_HTTP_NOT_FOUND
expr_stmt|;
name|error
operator|=
name|NGX_HTTP_NOT_FOUND
expr_stmt|;
break|break;
block|}
block|}
name|msie_padding
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|error_pages
index|[
name|err
index|]
operator|.
name|len
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|=
name|error_pages
index|[
name|err
index|]
operator|.
name|len
operator|+
sizeof|sizeof
argument_list|(
name|error_tail
argument_list|)
operator|-
literal|1
expr_stmt|;
if|if
condition|(
name|clcf
operator|->
name|msie_padding
operator|&&
name|r
operator|->
name|headers_in
operator|.
name|msie
operator|&&
name|r
operator|->
name|http_version
operator|>=
name|NGX_HTTP_VERSION_10
operator|&&
name|error
operator|>=
name|NGX_HTTP_BAD_REQUEST
operator|&&
name|error
operator|!=
name|NGX_HTTP_REQUEST_URI_TOO_LARGE
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|+=
sizeof|sizeof
argument_list|(
name|ngx_http_msie_stub
argument_list|)
operator|-
literal|1
expr_stmt|;
name|msie_padding
operator|=
literal|1
expr_stmt|;
block|}
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"text/html"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|.
name|data
operator|=
operator|(
name|u_char
operator|*
operator|)
literal|"text/html"
expr_stmt|;
block|}
else|else
block|{
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|=
operator|-
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|content_length
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|content_length
operator|->
name|hash
operator|=
literal|0
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_length
operator|=
name|NULL
expr_stmt|;
block|}
name|rc
operator|=
name|ngx_http_send_header
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|r
operator|->
name|header_only
condition|)
block|{
return|return
name|rc
return|;
block|}
if|if
condition|(
name|error_pages
index|[
name|err
index|]
operator|.
name|len
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|b
operator|->
name|memory
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|pos
operator|=
name|error_pages
index|[
name|err
index|]
operator|.
name|data
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|error_pages
index|[
name|err
index|]
operator|.
name|data
operator|+
name|error_pages
index|[
name|err
index|]
operator|.
name|len
expr_stmt|;
name|cl
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|cl
operator|->
name|buf
operator|=
name|b
expr_stmt|;
name|out
operator|=
name|cl
expr_stmt|;
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|b
operator|->
name|memory
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|pos
operator|=
name|error_tail
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|error_tail
operator|+
sizeof|sizeof
argument_list|(
name|error_tail
argument_list|)
operator|-
literal|1
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
name|cl
operator|->
name|buf
operator|=
name|b
expr_stmt|;
if|if
condition|(
name|msie_padding
condition|)
block|{
name|b
operator|=
name|ngx_calloc_buf
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|b
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|b
operator|->
name|memory
operator|=
literal|1
expr_stmt|;
name|b
operator|->
name|pos
operator|=
name|ngx_http_msie_stub
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_http_msie_stub
operator|+
sizeof|sizeof
argument_list|(
name|ngx_http_msie_stub
argument_list|)
operator|-
literal|1
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|r
operator|->
name|pool
argument_list|)
expr_stmt|;
if|if
condition|(
name|cl
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
name|cl
operator|->
name|buf
operator|=
name|b
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
expr|main
operator|==
name|NULL
condition|)
block|{
name|b
operator|->
name|last_buf
operator|=
literal|1
expr_stmt|;
block|}
name|b
operator|->
name|last_in_chain
operator|=
literal|1
expr_stmt|;
name|cl
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
return|return
name|ngx_http_output_filter
argument_list|(
name|r
argument_list|,
name|out
argument_list|)
return|;
block|}
end_function

end_unit

