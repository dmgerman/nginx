begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_function_decl
specifier|static
name|int
name|ngx_http_header_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_http_header_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_header_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_header_filter_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* pre conf */
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
name|NULL
block|,
comment|/* create location configuration */
name|NULL
block|,
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_header_filter_module
name|ngx_module_t
name|ngx_http_header_filter_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_header_filter_module_ctx
block|,
comment|/* module context */
name|NULL
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|ngx_http_header_filter_init
block|,
comment|/* init module */
name|NULL
comment|/* init child */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|server_string
specifier|static
name|char
name|server_string
index|[]
init|=
literal|"Server: "
name|NGINX_VER
name|CRLF
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|http_codes
specifier|static
name|ngx_str_t
name|http_codes
index|[]
init|=
block|{
name|ngx_string
argument_list|(
literal|"200 OK"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* "201 Created" */
name|ngx_null_string
block|,
comment|/* "202 Accepted" */
name|ngx_null_string
block|,
comment|/* "203 Non-Authoritative Information" */
name|ngx_null_string
block|,
comment|/* "204 No Content" */
name|ngx_null_string
block|,
comment|/* "205 Reset Content" */
name|ngx_string
argument_list|(
literal|"206 Partial Content"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* "207 Multi-Status" */
if|#
directive|if
literal|0
block|ngx_null_string,
comment|/* "300 Multiple Choices" */
endif|#
directive|endif
name|ngx_string
argument_list|(
literal|"301 Moved Permanently"
argument_list|)
block|,
if|#
directive|if
literal|0
block|ngx_string("302 Moved Temporarily"),
else|#
directive|else
name|ngx_string
argument_list|(
literal|"302 Found"
argument_list|)
block|,
endif|#
directive|endif
name|ngx_null_string
block|,
comment|/* "303 See Other" */
name|ngx_string
argument_list|(
literal|"304 Not Modified"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"400 Bad Request"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"401 Unauthorized"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* "402 Payment Required" */
name|ngx_string
argument_list|(
literal|"403 Forbidden"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"404 Not Found"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"405 Not Allowed"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* "406 Not Acceptable" */
name|ngx_null_string
block|,
comment|/* "407 Proxy Authentication Required" */
name|ngx_string
argument_list|(
literal|"408 Request Time-out"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* "409 Conflict" */
name|ngx_null_string
block|,
comment|/* "410 Gone" */
name|ngx_string
argument_list|(
literal|"411 Length Required"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* "412 Precondition Failed" */
name|ngx_string
argument_list|(
literal|"413 Request Entity Too Large"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* "414 Request-URI Too Large" but we never send it                        * because we treat such requests as the HTTP/0.9                        * requests and send only a body without a header                        */
name|ngx_null_string
block|,
comment|/* "415 Unsupported Media Type" */
name|ngx_string
argument_list|(
literal|"416 Requested Range Not Satisfiable"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"500 Internal Server Error"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"501 Method Not Implemented"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"502 Bad Gateway"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"503 Service Temporarily Unavailable"
argument_list|)
block|,
name|ngx_string
argument_list|(
literal|"504 Gateway Time-out"
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_header_filter (ngx_http_request_t * r)
specifier|static
name|int
name|ngx_http_header_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_uint_t
name|status
decl_stmt|,
name|i
decl_stmt|;
name|ngx_buf_t
modifier|*
name|b
decl_stmt|;
name|ngx_chain_t
modifier|*
name|ln
decl_stmt|;
name|ngx_table_elt_t
modifier|*
name|header
decl_stmt|;
if|if
condition|(
name|r
operator|->
name|http_version
operator|<
name|NGX_HTTP_VERSION_10
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|r
operator|->
name|method
operator|==
name|NGX_HTTP_HEAD
condition|)
block|{
name|r
operator|->
name|header_only
operator|=
literal|1
expr_stmt|;
block|}
comment|/* 2 is for trailing "\r\n" and 2 is for "\r\n" in the end of header */
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"HTTP/1.x "
argument_list|)
operator|-
literal|1
operator|+
literal|2
operator|+
literal|2
expr_stmt|;
comment|/* status line */
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|status_line
operator|.
name|len
condition|)
block|{
name|len
operator|+=
name|r
operator|->
name|headers_out
operator|.
name|status_line
operator|.
name|len
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_SUPPRESS_WARN
operator|)
name|status
operator|=
name|NGX_INVALID_ARRAY_INDEX
expr_stmt|;
endif|#
directive|endif
block|}
else|else
block|{
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|status
operator|<
name|NGX_HTTP_MOVED_PERMANENTLY
condition|)
block|{
comment|/* 2XX */
name|status
operator|=
name|r
operator|->
name|headers_out
operator|.
name|status
operator|-
name|NGX_HTTP_OK
expr_stmt|;
block|}
if|else if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|status
operator|<
name|NGX_HTTP_BAD_REQUEST
condition|)
block|{
comment|/* 3XX */
name|status
operator|=
name|r
operator|->
name|headers_out
operator|.
name|status
operator|-
name|NGX_HTTP_MOVED_PERMANENTLY
operator|+
literal|8
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|status
operator|==
name|NGX_HTTP_NOT_MODIFIED
condition|)
block|{
name|r
operator|->
name|header_only
operator|=
literal|1
expr_stmt|;
block|}
block|}
if|else if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|status
operator|<
name|NGX_HTTP_INTERNAL_SERVER_ERROR
condition|)
block|{
comment|/* 4XX */
name|status
operator|=
name|r
operator|->
name|headers_out
operator|.
name|status
operator|-
name|NGX_HTTP_BAD_REQUEST
operator|+
literal|8
operator|+
literal|4
expr_stmt|;
block|}
else|else
block|{
comment|/* 5XX */
name|status
operator|=
name|r
operator|->
name|headers_out
operator|.
name|status
operator|-
name|NGX_HTTP_INTERNAL_SERVER_ERROR
operator|+
literal|8
operator|+
literal|4
operator|+
literal|17
expr_stmt|;
block|}
name|len
operator|+=
name|http_codes
index|[
name|status
index|]
operator|.
name|len
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|server
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|server
operator|->
name|key
operator|.
name|len
condition|)
block|{
name|len
operator|+=
name|r
operator|->
name|headers_out
operator|.
name|server
operator|->
name|key
operator|.
name|len
operator|+
name|r
operator|->
name|headers_out
operator|.
name|server
operator|->
name|value
operator|.
name|len
operator|+
literal|2
expr_stmt|;
block|}
else|else
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
name|server_string
argument_list|)
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
name|date
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|date
operator|->
name|key
operator|.
name|len
condition|)
block|{
name|len
operator|+=
name|r
operator|->
name|headers_out
operator|.
name|date
operator|->
name|key
operator|.
name|len
operator|+
name|r
operator|->
name|headers_out
operator|.
name|date
operator|->
name|value
operator|.
name|len
operator|+
literal|2
expr_stmt|;
block|}
else|else
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"Date: Mon, 28 Sep 1970 06:00:00 GMT"
name|CRLF
argument_list|)
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
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|>=
literal|0
condition|)
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"Content-Length: "
argument_list|)
operator|-
literal|1
operator|+
name|NGX_OFF_T_LEN
operator|+
literal|2
expr_stmt|;
block|}
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|key
operator|.
name|len
operator|=
literal|0
expr_stmt|;
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"Content-Type: "
argument_list|)
operator|-
literal|1
operator|+
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
operator|+
literal|2
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|charset
operator|.
name|len
condition|)
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"; charset="
argument_list|)
operator|-
literal|1
operator|+
name|r
operator|->
name|headers_out
operator|.
name|charset
operator|.
name|len
expr_stmt|;
block|}
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|location
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|len
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'/'
condition|)
block|{
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|key
operator|.
name|len
operator|=
literal|0
expr_stmt|;
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"Location: http://"
argument_list|)
operator|-
literal|1
operator|+
name|r
operator|->
name|server_name
operator|->
name|len
operator|+
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|len
operator|+
literal|2
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|port
operator|!=
literal|80
condition|)
block|{
name|len
operator|+=
name|r
operator|->
name|port_name
operator|->
name|len
expr_stmt|;
block|}
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|last_modified
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|last_modified
operator|->
name|key
operator|.
name|len
condition|)
block|{
name|len
operator|+=
name|r
operator|->
name|headers_out
operator|.
name|last_modified
operator|->
name|key
operator|.
name|len
operator|+
name|r
operator|->
name|headers_out
operator|.
name|last_modified
operator|->
name|value
operator|.
name|len
operator|+
literal|2
expr_stmt|;
block|}
if|else if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
operator|!=
operator|-
literal|1
condition|)
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"Last-Modified: Mon, 28 Sep 1970 06:00:00 GMT"
name|CRLF
argument_list|)
operator|-
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|chunked
condition|)
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"Transfer-Encoding: chunked"
name|CRLF
argument_list|)
operator|-
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|keepalive
condition|)
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"Connection: keep-alive"
name|CRLF
argument_list|)
operator|-
literal|1
expr_stmt|;
block|}
else|else
block|{
name|len
operator|+=
sizeof|sizeof
argument_list|(
literal|"Connection: closed"
name|CRLF
argument_list|)
operator|-
literal|1
expr_stmt|;
block|}
name|header
operator|=
name|r
operator|->
name|headers_out
operator|.
name|headers
operator|.
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
name|r
operator|->
name|headers_out
operator|.
name|headers
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|header
index|[
name|i
index|]
operator|.
name|key
operator|.
name|len
operator|==
literal|0
condition|)
block|{
continue|continue;
block|}
comment|/* 2 is for ": " and 2 is for "\r\n" */
name|len
operator|+=
name|header
index|[
name|i
index|]
operator|.
name|key
operator|.
name|len
operator|+
literal|2
operator|+
name|header
index|[
name|i
index|]
operator|.
name|value
operator|.
name|len
operator|+
literal|2
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|b
operator|=
name|ngx_create_temp_buf
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|len
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
comment|/* "HTTP/1.x " */
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"HTTP/1.1 "
argument_list|,
sizeof|sizeof
argument_list|(
literal|"HTTP/1.x "
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* status line */
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|status_line
operator|.
name|len
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|status_line
operator|.
name|data
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|status_line
operator|.
name|len
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|http_codes
index|[
name|status
index|]
operator|.
name|data
argument_list|,
name|http_codes
index|[
name|status
index|]
operator|.
name|len
argument_list|)
expr_stmt|;
block|}
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|headers_out
operator|.
name|server
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|server
operator|->
name|key
operator|.
name|len
operator|)
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|server_string
argument_list|,
sizeof|sizeof
argument_list|(
name|server_string
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|headers_out
operator|.
name|date
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|date
operator|->
name|key
operator|.
name|len
operator|)
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"Date: "
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Date: "
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|ngx_cached_http_time
operator|.
name|data
argument_list|,
name|ngx_cached_http_time
operator|.
name|len
argument_list|)
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|content_length
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|>=
literal|0
condition|)
block|{
name|b
operator|->
name|last
operator|+=
name|ngx_snprintf
argument_list|(
argument|(char *) b->last
argument_list|,
argument|sizeof(
literal|"Content-Length: "
argument|) + NGX_OFF_T_LEN +
literal|2
argument_list|,
literal|"Content-Length: "
argument|OFF_T_FMT CRLF
argument_list|,
argument|r->headers_out.content_length_n
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"Content-Type: "
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Content-Type: "
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|p
operator|=
name|b
operator|->
name|last
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|data
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|charset
operator|.
name|len
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"; charset="
argument_list|,
sizeof|sizeof
argument_list|(
literal|"; charset="
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|charset
operator|.
name|data
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|charset
operator|.
name|len
argument_list|)
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|len
operator|=
name|b
operator|->
name|last
operator|-
name|p
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_type
operator|->
name|value
operator|.
name|data
operator|=
name|p
expr_stmt|;
block|}
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|headers_out
operator|.
name|location
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|len
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'/'
condition|)
block|{
name|p
operator|=
name|b
operator|->
name|last
operator|+
sizeof|sizeof
argument_list|(
literal|"Location: "
argument_list|)
operator|-
literal|1
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"Location: http://"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Location: http://"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|server_name
operator|->
name|data
argument_list|,
name|r
operator|->
name|server_name
operator|->
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|port
operator|!=
literal|80
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|port_name
operator|->
name|data
argument_list|,
name|r
operator|->
name|port_name
operator|->
name|len
argument_list|)
expr_stmt|;
block|}
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|data
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|len
argument_list|)
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|len
operator|=
name|b
operator|->
name|last
operator|-
name|p
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|location
operator|->
name|value
operator|.
name|data
operator|=
name|p
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|headers_out
operator|.
name|last_modified
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|last_modified
operator|->
name|key
operator|.
name|len
operator|)
operator|&&
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
operator|!=
operator|-
literal|1
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"Last-Modified: "
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Last-Modified: "
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|b
operator|->
name|last
operator|+=
name|ngx_http_time
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
argument_list|)
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|chunked
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"Transfer-Encoding: chunked"
name|CRLF
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Transfer-Encoding: chunked"
name|CRLF
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|r
operator|->
name|keepalive
condition|)
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"Connection: keep-alive"
name|CRLF
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Connection: keep-alive"
name|CRLF
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
literal|"Connection: close"
name|CRLF
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Connection: close"
name|CRLF
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|r
operator|->
name|headers_out
operator|.
name|headers
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|header
index|[
name|i
index|]
operator|.
name|key
operator|.
name|len
operator|==
literal|0
condition|)
block|{
continue|continue;
block|}
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|header
index|[
name|i
index|]
operator|.
name|key
operator|.
name|data
argument_list|,
name|header
index|[
name|i
index|]
operator|.
name|key
operator|.
name|len
argument_list|)
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|':'
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
literal|' '
expr_stmt|;
name|b
operator|->
name|last
operator|=
name|ngx_cpymem
argument_list|(
name|b
operator|->
name|last
argument_list|,
name|header
index|[
name|i
index|]
operator|.
name|value
operator|.
name|data
argument_list|,
name|header
index|[
name|i
index|]
operator|.
name|value
operator|.
name|len
argument_list|)
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
block|}
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
operator|*
operator|(
name|b
operator|->
name|last
operator|)
operator|=
literal|'\0'
expr_stmt|;
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
literal|"%s\n"
argument_list|,
name|b
operator|->
name|pos
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* the end of HTTP header */
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|CR
expr_stmt|;
operator|*
operator|(
name|b
operator|->
name|last
operator|++
operator|)
operator|=
name|LF
expr_stmt|;
name|r
operator|->
name|header_size
operator|=
name|b
operator|->
name|last
operator|-
name|b
operator|->
name|pos
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|header_only
condition|)
block|{
name|b
operator|->
name|last_buf
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|ln
operator|=
name|ngx_alloc_chain_link
argument_list|(
name|r
operator|->
name|pool
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ln
operator|->
name|buf
operator|=
name|b
expr_stmt|;
name|ln
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
return|return
name|ngx_http_write_filter
argument_list|(
name|r
argument_list|,
name|ln
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_header_filter_init (ngx_cycle_t * cycle)
specifier|static
name|int
name|ngx_http_header_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_http_top_header_filter
operator|=
name|ngx_http_header_filter
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

