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

begin_function
DECL|function|ngx_read_http_request_line (ngx_http_request_t * r)
name|int
name|ngx_read_http_request_line
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|char
name|ch
decl_stmt|;
name|char
modifier|*
name|p
init|=
name|r
operator|->
name|header_in
operator|->
name|pos
operator|.
name|mem
decl_stmt|;
DECL|enum|__anon27ce31850103
enum|enum
block|{
DECL|enumerator|sw_start
name|sw_start
init|=
literal|0
block|,
DECL|enumerator|sw_space_after_method
name|sw_space_after_method
block|,
DECL|enumerator|sw_spaces_before_uri
name|sw_spaces_before_uri
block|,
DECL|enumerator|sw_after_slash_in_uri
name|sw_after_slash_in_uri
block|,
DECL|enumerator|sw_check_uri
name|sw_check_uri
block|,
DECL|enumerator|sw_uri
name|sw_uri
block|,
DECL|enumerator|sw_http_09
name|sw_http_09
block|,
DECL|enumerator|sw_http_version
name|sw_http_version
block|,
DECL|enumerator|sw_first_major_digit
name|sw_first_major_digit
block|,
DECL|enumerator|sw_major_digit
name|sw_major_digit
block|,
DECL|enumerator|sw_first_minor_digit
name|sw_first_minor_digit
block|,
DECL|enumerator|sw_minor_digit
name|sw_minor_digit
block|,
DECL|enumerator|sw_almost_done
name|sw_almost_done
block|,
DECL|enumerator|sw_done
name|sw_done
block|}
name|state
init|=
name|r
operator|->
name|state
enum|;
while|while
condition|(
name|p
operator|<
name|r
operator|->
name|header_in
operator|->
name|last
operator|.
name|mem
operator|&&
name|state
operator|<
name|sw_done
condition|)
block|{
name|ch
operator|=
operator|*
name|p
operator|++
expr_stmt|;
comment|/* printf("\nstate: %d, pos: %x, end: %x, char: '%c' buf: %s",        state, p, r->header_in->last, ch, p); */
comment|/* GCC compiles switch as jump table */
switch|switch
condition|(
name|state
condition|)
block|{
comment|/* HTTP methods: GET, HEAD, POST */
case|case
name|sw_start
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|'G'
case|:
if|if
condition|(
name|p
operator|+
literal|1
operator|>=
name|r
operator|->
name|header_in
operator|->
name|last
operator|.
name|mem
condition|)
return|return
name|NGX_AGAIN
return|;
if|if
condition|(
operator|*
name|p
operator|!=
literal|'E'
operator|||
operator|*
operator|(
name|p
operator|+
literal|1
operator|)
operator|!=
literal|'T'
condition|)
return|return
name|NGX_HTTP_INVALID_METHOD
return|;
name|r
operator|->
name|method
operator|=
name|NGX_HTTP_GET
expr_stmt|;
name|p
operator|+=
literal|2
expr_stmt|;
break|break;
case|case
literal|'H'
case|:
if|if
condition|(
name|p
operator|+
literal|2
operator|>=
name|r
operator|->
name|header_in
operator|->
name|last
operator|.
name|mem
condition|)
return|return
name|NGX_AGAIN
return|;
if|if
condition|(
operator|*
name|p
operator|!=
literal|'E'
operator|||
operator|*
operator|(
name|p
operator|+
literal|1
operator|)
operator|!=
literal|'A'
operator|||
operator|*
operator|(
name|p
operator|+
literal|2
operator|)
operator|!=
literal|'D'
condition|)
return|return
name|NGX_HTTP_INVALID_METHOD
return|;
name|r
operator|->
name|method
operator|=
name|NGX_HTTP_HEAD
expr_stmt|;
name|p
operator|+=
literal|3
expr_stmt|;
break|break;
case|case
literal|'P'
case|:
if|if
condition|(
name|p
operator|+
literal|2
operator|>=
name|r
operator|->
name|header_in
operator|->
name|last
operator|.
name|mem
condition|)
return|return
name|NGX_AGAIN
return|;
if|if
condition|(
operator|*
name|p
operator|!=
literal|'O'
operator|||
operator|*
operator|(
name|p
operator|+
literal|1
operator|)
operator|!=
literal|'S'
operator|||
operator|*
operator|(
name|p
operator|+
literal|2
operator|)
operator|!=
literal|'T'
condition|)
return|return
name|NGX_HTTP_INVALID_METHOD
return|;
name|r
operator|->
name|method
operator|=
name|NGX_HTTP_POST
expr_stmt|;
name|p
operator|+=
literal|3
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_INVALID_METHOD
return|;
block|}
name|state
operator|=
name|sw_space_after_method
expr_stmt|;
break|break;
comment|/* single space after method */
case|case
name|sw_space_after_method
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|' '
case|:
name|state
operator|=
name|sw_spaces_before_uri
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_INVALID_METHOD
return|;
block|}
break|break;
comment|/* space* before URI */
case|case
name|sw_spaces_before_uri
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|'/'
case|:
name|r
operator|->
name|uri_start
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_after_slash_in_uri
expr_stmt|;
break|break;
case|case
literal|' '
case|:
break|break;
default|default:
name|r
operator|->
name|unusual_uri
operator|=
literal|1
expr_stmt|;
name|r
operator|->
name|uri_start
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_uri
expr_stmt|;
break|break;
block|}
break|break;
comment|/* check dot after slash */
case|case
name|sw_after_slash_in_uri
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
name|CR
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|http_minor
operator|=
literal|9
expr_stmt|;
name|state
operator|=
name|sw_almost_done
expr_stmt|;
break|break;
case|case
name|LF
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|http_minor
operator|=
literal|9
expr_stmt|;
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
case|case
literal|' '
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_http_09
expr_stmt|;
break|break;
case|case
literal|'.'
case|:
name|r
operator|->
name|complex_uri
operator|=
literal|1
expr_stmt|;
name|state
operator|=
name|sw_uri
expr_stmt|;
break|break;
case|case
literal|'/'
case|:
name|r
operator|->
name|complex_uri
operator|=
literal|1
expr_stmt|;
name|state
operator|=
name|sw_uri
expr_stmt|;
break|break;
case|case
literal|'?'
case|:
name|r
operator|->
name|args_start
operator|=
name|p
expr_stmt|;
name|state
operator|=
name|sw_uri
expr_stmt|;
break|break;
default|default:
name|state
operator|=
name|sw_check_uri
expr_stmt|;
break|break;
block|}
break|break;
comment|/* check slash in URI */
case|case
name|sw_check_uri
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
name|CR
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|http_minor
operator|=
literal|9
expr_stmt|;
name|state
operator|=
name|sw_almost_done
expr_stmt|;
break|break;
case|case
name|LF
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|http_minor
operator|=
literal|9
expr_stmt|;
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
case|case
literal|' '
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_http_09
expr_stmt|;
break|break;
case|case
literal|'.'
case|:
name|r
operator|->
name|uri_ext
operator|=
name|p
expr_stmt|;
break|break;
case|case
literal|'/'
case|:
name|r
operator|->
name|uri_ext
operator|=
name|NULL
expr_stmt|;
name|state
operator|=
name|sw_after_slash_in_uri
expr_stmt|;
break|break;
case|case
literal|'?'
case|:
name|r
operator|->
name|args_start
operator|=
name|p
expr_stmt|;
name|state
operator|=
name|sw_uri
expr_stmt|;
break|break;
block|}
break|break;
comment|/* URI */
case|case
name|sw_uri
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
name|CR
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|http_minor
operator|=
literal|9
expr_stmt|;
name|state
operator|=
name|sw_almost_done
expr_stmt|;
break|break;
case|case
name|LF
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|r
operator|->
name|http_minor
operator|=
literal|9
expr_stmt|;
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
case|case
literal|' '
case|:
name|r
operator|->
name|uri_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_http_09
expr_stmt|;
break|break;
block|}
break|break;
comment|/* space+ after URI */
case|case
name|sw_http_09
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|' '
case|:
break|break;
case|case
name|CR
case|:
name|r
operator|->
name|http_minor
operator|=
literal|9
expr_stmt|;
name|state
operator|=
name|sw_almost_done
expr_stmt|;
break|break;
case|case
name|LF
case|:
name|r
operator|->
name|http_minor
operator|=
literal|9
expr_stmt|;
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
case|case
literal|'H'
case|:
name|state
operator|=
name|sw_http_version
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_INVALID_REQUEST
return|;
block|}
break|break;
comment|/* TTP/ */
case|case
name|sw_http_version
case|:
if|if
condition|(
name|p
operator|+
literal|2
operator|>=
name|r
operator|->
name|header_in
operator|->
name|last
operator|.
name|mem
condition|)
block|{
name|r
operator|->
name|state
operator|=
name|sw_http_version
expr_stmt|;
name|r
operator|->
name|header_in
operator|->
name|pos
operator|.
name|mem
operator|=
name|p
operator|-
literal|1
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
if|if
condition|(
name|ch
operator|!=
literal|'T'
operator|||
operator|*
name|p
operator|!=
literal|'T'
operator|||
operator|*
operator|(
name|p
operator|+
literal|1
operator|)
operator|!=
literal|'P'
operator|||
operator|*
operator|(
name|p
operator|+
literal|2
operator|)
operator|!=
literal|'/'
condition|)
return|return
name|NGX_HTTP_INVALID_REQUEST
return|;
name|p
operator|+=
literal|3
expr_stmt|;
name|state
operator|=
name|sw_first_major_digit
expr_stmt|;
break|break;
comment|/* first digit of major HTTP version */
case|case
name|sw_first_major_digit
case|:
if|if
condition|(
name|ch
argument_list|<
literal|'1'
operator|||
name|ch
argument_list|>
literal|'9'
condition|)
return|return
name|NGX_HTTP_INVALID_REQUEST
return|;
name|r
operator|->
name|http_major
operator|=
name|ch
operator|-
literal|'0'
expr_stmt|;
name|state
operator|=
name|sw_major_digit
expr_stmt|;
break|break;
comment|/* major HTTP version or dot */
case|case
name|sw_major_digit
case|:
if|if
condition|(
name|ch
operator|==
literal|'.'
condition|)
block|{
name|state
operator|=
name|sw_first_minor_digit
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|ch
argument_list|<
literal|'0'
operator|||
name|ch
argument_list|>
literal|'9'
condition|)
return|return
name|NGX_HTTP_INVALID_REQUEST
return|;
name|r
operator|->
name|http_major
operator|=
name|r
operator|->
name|http_major
operator|*
literal|10
operator|+
name|ch
operator|-
literal|'0'
expr_stmt|;
break|break;
comment|/* first digit of minor HTTP version */
case|case
name|sw_first_minor_digit
case|:
if|if
condition|(
name|ch
argument_list|<
literal|'0'
operator|||
name|ch
argument_list|>
literal|'9'
condition|)
return|return
name|NGX_HTTP_INVALID_REQUEST
return|;
name|r
operator|->
name|http_minor
operator|=
name|ch
operator|-
literal|'0'
expr_stmt|;
name|state
operator|=
name|sw_minor_digit
expr_stmt|;
break|break;
comment|/* minor HTTP version or end of request line */
case|case
name|sw_minor_digit
case|:
if|if
condition|(
name|ch
operator|==
name|CR
condition|)
block|{
name|state
operator|=
name|sw_almost_done
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|ch
operator|==
name|LF
condition|)
block|{
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|ch
argument_list|<
literal|'0'
operator|||
name|ch
argument_list|>
literal|'9'
condition|)
return|return
name|NGX_HTTP_INVALID_REQUEST
return|;
name|r
operator|->
name|http_minor
operator|=
name|r
operator|->
name|http_minor
operator|*
literal|10
operator|+
name|ch
operator|-
literal|'0'
expr_stmt|;
break|break;
comment|/* end of request line */
case|case
name|sw_almost_done
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
name|LF
case|:
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_INVALID_REQUEST
return|;
block|}
break|break;
block|}
block|}
name|r
operator|->
name|header_in
operator|->
name|pos
operator|.
name|mem
operator|=
name|p
expr_stmt|;
if|if
condition|(
name|state
operator|==
name|sw_done
condition|)
block|{
name|r
operator|->
name|http_version
operator|=
name|r
operator|->
name|http_major
operator|*
literal|1000
operator|+
name|r
operator|->
name|http_minor
expr_stmt|;
name|r
operator|->
name|state
operator|=
name|sw_start
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|http_version
operator|==
literal|9
operator|&&
name|r
operator|->
name|method
operator|==
name|NGX_HTTP_HEAD
condition|)
return|return
name|NGX_HTTP_INVALID_HEAD
return|;
else|else
return|return
name|NGX_OK
return|;
block|}
else|else
block|{
name|r
operator|->
name|state
operator|=
name|state
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_read_http_header_line (ngx_http_request_t * r)
name|int
name|ngx_read_http_header_line
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|char
name|c
decl_stmt|,
name|ch
decl_stmt|;
name|char
modifier|*
name|p
init|=
name|r
operator|->
name|header_in
operator|->
name|pos
operator|.
name|mem
decl_stmt|;
DECL|enum|__anon27ce31850203
enum|enum
block|{
DECL|enumerator|sw_start
name|sw_start
init|=
literal|0
block|,
DECL|enumerator|sw_name
name|sw_name
block|,
DECL|enumerator|sw_space_before_value
name|sw_space_before_value
block|,
DECL|enumerator|sw_value
name|sw_value
block|,
DECL|enumerator|sw_space_after_value
name|sw_space_after_value
block|,
DECL|enumerator|sw_almost_done
name|sw_almost_done
block|,
DECL|enumerator|sw_header_almost_done
name|sw_header_almost_done
block|,
DECL|enumerator|sw_done
name|sw_done
block|,
DECL|enumerator|sw_header_done
name|sw_header_done
block|}
name|state
init|=
name|r
operator|->
name|state
enum|;
while|while
condition|(
name|p
operator|<
name|r
operator|->
name|header_in
operator|->
name|last
operator|.
name|mem
operator|&&
name|state
operator|<
name|sw_done
condition|)
block|{
name|ch
operator|=
operator|*
name|p
operator|++
expr_stmt|;
comment|/* printf("\nstate: %d, pos: %x, end: %x, char: '%c' buf: %s",        state, p, r->header_in->last.mem, ch, p); */
switch|switch
condition|(
name|state
condition|)
block|{
comment|/* first char */
case|case
name|sw_start
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
name|CR
case|:
name|r
operator|->
name|header_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_header_almost_done
expr_stmt|;
break|break;
case|case
name|LF
case|:
name|r
operator|->
name|header_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_header_done
expr_stmt|;
break|break;
default|default:
name|state
operator|=
name|sw_name
expr_stmt|;
name|r
operator|->
name|header_name_start
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|c
operator|=
name|ch
operator||
literal|0x20
expr_stmt|;
if|if
condition|(
name|c
operator|>=
literal|'a'
operator|&&
name|c
operator|<=
literal|'z'
condition|)
break|break;
if|if
condition|(
name|ch
operator|==
literal|'-'
condition|)
break|break;
if|if
condition|(
name|ch
operator|>=
literal|'0'
operator|&&
name|ch
operator|<=
literal|'9'
condition|)
break|break;
return|return
name|NGX_HTTP_INVALID_HEADER
return|;
block|}
break|break;
comment|/* header name */
case|case
name|sw_name
case|:
name|c
operator|=
name|ch
operator||
literal|0x20
expr_stmt|;
if|if
condition|(
name|c
operator|>=
literal|'a'
operator|&&
name|c
operator|<=
literal|'z'
condition|)
break|break;
if|if
condition|(
name|ch
operator|==
literal|':'
condition|)
block|{
name|r
operator|->
name|header_name_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_space_before_value
expr_stmt|;
break|break;
block|}
if|if
condition|(
name|ch
operator|==
literal|'-'
condition|)
break|break;
if|if
condition|(
name|ch
operator|>=
literal|'0'
operator|&&
name|ch
operator|<=
literal|'9'
condition|)
break|break;
return|return
name|NGX_HTTP_INVALID_HEADER
return|;
comment|/* space* before header value */
case|case
name|sw_space_before_value
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|' '
case|:
break|break;
case|case
name|CR
case|:
name|r
operator|->
name|header_start
operator|=
name|r
operator|->
name|header_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_almost_done
expr_stmt|;
break|break;
case|case
name|LF
case|:
name|r
operator|->
name|header_start
operator|=
name|r
operator|->
name|header_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
default|default:
name|r
operator|->
name|header_start
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_value
expr_stmt|;
break|break;
block|}
break|break;
comment|/* header value */
case|case
name|sw_value
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|' '
case|:
name|r
operator|->
name|header_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_space_after_value
expr_stmt|;
break|break;
case|case
name|CR
case|:
name|r
operator|->
name|header_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_almost_done
expr_stmt|;
break|break;
case|case
name|LF
case|:
name|r
operator|->
name|header_end
operator|=
name|p
operator|-
literal|1
expr_stmt|;
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
block|}
break|break;
comment|/* space* before end of header line */
case|case
name|sw_space_after_value
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|' '
case|:
break|break;
case|case
name|CR
case|:
name|state
operator|=
name|sw_almost_done
expr_stmt|;
break|break;
case|case
name|LF
case|:
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
default|default:
name|state
operator|=
name|sw_value
expr_stmt|;
break|break;
block|}
break|break;
comment|/* end of header line */
case|case
name|sw_almost_done
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
name|LF
case|:
name|state
operator|=
name|sw_done
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_INVALID_HEADER
return|;
block|}
break|break;
comment|/* end of header */
case|case
name|sw_header_almost_done
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
name|LF
case|:
name|state
operator|=
name|sw_header_done
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_INVALID_HEADER
return|;
block|}
break|break;
block|}
block|}
name|r
operator|->
name|header_in
operator|->
name|pos
operator|.
name|mem
operator|=
name|p
expr_stmt|;
if|if
condition|(
name|state
operator|==
name|sw_done
condition|)
block|{
name|r
operator|->
name|state
operator|=
name|sw_start
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
if|else if
condition|(
name|state
operator|==
name|sw_header_done
condition|)
block|{
name|r
operator|->
name|state
operator|=
name|sw_start
expr_stmt|;
return|return
name|NGX_HTTP_HEADER_DONE
return|;
block|}
else|else
block|{
name|r
operator|->
name|state
operator|=
name|state
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
block|}
end_function

end_unit

