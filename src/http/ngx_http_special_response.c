begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<nginx.h>
end_include

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
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_output_filter.h>
end_include

begin_decl_stmt
DECL|variable|error_tail
specifier|static
name|char
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
name|ngx_null_string
block|,
comment|/* 301 */
name|ngx_null_string
block|,
comment|/* 302 */
name|ngx_null_string
block|,
comment|/* 303 */
name|ngx_string
argument_list|(
name|error_400_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 401 */
name|ngx_null_string
block|,
comment|/* 402 */
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
name|ngx_null_string
block|,
comment|/* 405 */
name|ngx_null_string
block|,
comment|/* 406 */
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
name|ngx_null_string
block|,
comment|/* 410 */
name|ngx_null_string
block|,
comment|/* 411 */
name|ngx_null_string
block|,
comment|/* 412 */
name|ngx_null_string
block|,
comment|/* 413 */
name|ngx_string
argument_list|(
name|error_414_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 415 */
name|ngx_null_string
block|,
comment|/* 416 */
name|ngx_string
argument_list|(
name|error_500_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 501 */
name|ngx_string
argument_list|(
name|error_502_page
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 503 */
name|ngx_string
argument_list|(
argument|error_504_page
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_special_response_handler (ngx_http_request_t * r,int error)
name|int
name|ngx_http_special_response_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|int
name|error
parameter_list|)
block|{
name|int
name|err
decl_stmt|,
name|len
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|message
decl_stmt|,
modifier|*
name|tail
decl_stmt|;
name|len
operator|=
literal|0
expr_stmt|;
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
name|error
operator|<
name|NGX_HTTP_BAD_REQUEST
condition|)
block|{
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
name|NGX_HTTP_INTERNAL_SERVER_ERROR
condition|)
block|{
name|err
operator|=
name|error
operator|-
name|NGX_HTTP_BAD_REQUEST
operator|+
literal|3
expr_stmt|;
block|}
else|else
block|{
name|err
operator|=
name|error
operator|-
name|NGX_HTTP_INTERNAL_SERVER_ERROR
operator|+
literal|3
operator|+
literal|17
expr_stmt|;
block|}
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
name|NGX_HTTP_REQUEST_URI_TOO_LARGE
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
name|r
operator|->
name|headers_out
operator|.
name|content_length
operator|=
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
name|r
operator|->
name|headers_out
operator|.
name|content_length
operator|=
name|error_pages
index|[
name|err
index|]
operator|.
name|len
operator|+
name|len
operator|+
sizeof|sizeof
argument_list|(
name|error_tail
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ngx_http_send_header
argument_list|(
name|r
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
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
name|ngx_test_null
argument_list|(
name|message
argument_list|,
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_hunk_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|message
operator|->
name|type
operator|=
name|NGX_HUNK_MEMORY
operator||
name|NGX_HUNK_IN_MEMORY
expr_stmt|;
name|message
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
name|message
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
if|if
condition|(
name|ngx_http_output_filter
argument_list|(
name|r
argument_list|,
name|message
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_test_null
argument_list|(
name|tail
argument_list|,
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_hunk_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|tail
operator|->
name|type
operator|=
name|NGX_HUNK_MEMORY
operator||
name|NGX_HUNK_LAST
operator||
name|NGX_HUNK_IN_MEMORY
expr_stmt|;
name|tail
operator|->
name|pos
operator|=
name|error_tail
expr_stmt|;
name|tail
operator|->
name|last
operator|=
name|error_tail
operator|+
sizeof|sizeof
argument_list|(
name|error_tail
argument_list|)
expr_stmt|;
return|return
name|ngx_http_output_filter
argument_list|(
name|r
argument_list|,
name|tail
argument_list|)
return|;
block|}
end_function

end_unit

