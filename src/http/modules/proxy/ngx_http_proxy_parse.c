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
file|<ngx_http_proxy_handler.h>
end_include

begin_function
DECL|function|ngx_http_proxy_parse_status_line (ngx_http_proxy_ctx_t * p)
name|int
name|ngx_http_proxy_parse_status_line
parameter_list|(
name|ngx_http_proxy_ctx_t
modifier|*
name|p
parameter_list|)
block|{
name|char
name|ch
decl_stmt|;
name|char
modifier|*
name|pos
decl_stmt|;
DECL|enum|__anon2b2ecb780103
enum|enum
block|{
DECL|enumerator|sw_start
name|sw_start
init|=
literal|0
block|,
DECL|enumerator|sw_H
name|sw_H
block|,
DECL|enumerator|sw_HT
name|sw_HT
block|,
DECL|enumerator|sw_HTT
name|sw_HTT
block|,
DECL|enumerator|sw_HTTP
name|sw_HTTP
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
DECL|enumerator|sw_status
name|sw_status
block|,
DECL|enumerator|sw_space_after_status
name|sw_space_after_status
block|,
DECL|enumerator|sw_status_text
name|sw_status_text
block|,
DECL|enumerator|sw_almost_done
name|sw_almost_done
block|,
DECL|enumerator|sw_done
name|sw_done
block|}
name|state
enum|;
name|state
operator|=
name|p
operator|->
name|state
expr_stmt|;
name|pos
operator|=
name|p
operator|->
name|header_in
operator|->
name|pos
expr_stmt|;
while|while
condition|(
name|pos
operator|<
name|p
operator|->
name|header_in
operator|->
name|last
operator|&&
name|state
operator|<
name|sw_done
condition|)
block|{
name|ch
operator|=
operator|*
name|pos
operator|++
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
comment|/* "HTTP/" */
case|case
name|sw_start
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|'H'
case|:
name|state
operator|=
name|sw_H
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
case|case
name|sw_H
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|'T'
case|:
name|state
operator|=
name|sw_HT
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
case|case
name|sw_HT
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|'T'
case|:
name|state
operator|=
name|sw_HTT
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
case|case
name|sw_HTT
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|'P'
case|:
name|state
operator|=
name|sw_HTTP
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
case|case
name|sw_HTTP
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|'/'
case|:
name|state
operator|=
name|sw_first_major_digit
expr_stmt|;
break|break;
default|default:
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
comment|/* the first digit of major HTTP version */
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
block|{
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
name|state
operator|=
name|sw_major_digit
expr_stmt|;
break|break;
comment|/* the major HTTP version or dot */
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
block|{
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
comment|/* the first digit of minor HTTP version */
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
block|{
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
name|state
operator|=
name|sw_minor_digit
expr_stmt|;
break|break;
comment|/* the minor HTTP version or the end of the request line */
case|case
name|sw_minor_digit
case|:
if|if
condition|(
name|ch
operator|==
literal|' '
condition|)
block|{
name|state
operator|=
name|sw_status
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
block|{
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
comment|/* HTTP status code */
case|case
name|sw_status
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
block|{
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
name|p
operator|->
name|status
operator|=
name|p
operator|->
name|status
operator|*
literal|10
operator|+
name|ch
operator|-
literal|'0'
expr_stmt|;
if|if
condition|(
operator|++
name|p
operator|->
name|status_count
operator|==
literal|3
condition|)
block|{
name|state
operator|=
name|sw_space_after_status
expr_stmt|;
name|p
operator|->
name|status_start
operator|=
name|pos
operator|-
literal|3
expr_stmt|;
block|}
break|break;
comment|/* space or end of line */
case|case
name|sw_space_after_status
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
name|sw_status_text
expr_stmt|;
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
return|return
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
comment|/* any text until end of line */
case|case
name|sw_status_text
case|:
switch|switch
condition|(
name|ch
condition|)
block|{
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
block|}
break|break;
comment|/* end of request line */
case|case
name|sw_almost_done
case|:
name|p
operator|->
name|status_end
operator|=
name|pos
operator|-
literal|2
expr_stmt|;
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
name|NGX_HTTP_PROXY_PARSE_NO_HEADER
return|;
block|}
break|break;
block|}
block|}
name|p
operator|->
name|header_in
operator|->
name|pos
operator|=
name|pos
expr_stmt|;
if|if
condition|(
name|state
operator|==
name|sw_done
condition|)
block|{
if|if
condition|(
name|p
operator|->
name|status_end
operator|==
name|NULL
condition|)
block|{
name|p
operator|->
name|status_end
operator|=
name|pos
operator|-
literal|1
expr_stmt|;
block|}
name|p
operator|->
name|state
operator|=
name|sw_start
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|p
operator|->
name|state
operator|=
name|state
expr_stmt|;
return|return
name|NGX_AGAIN
return|;
block|}
end_function

end_unit

