begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_if
if|#
directive|if
literal|0
end_if

begin_include
include|#
directive|include
file|<ngx_core.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_function
DECL|function|ngx_http_special_response (ngx_http_request_t * r,int error)
name|int
name|ngx_http_special_response
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|int
name|error
parameter_list|)
block|{
switch|switch
condition|(
name|error
condition|)
block|{
default|default:
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|error
expr_stmt|;
return|return
name|ngx_http_header_filter
argument_list|(
name|r
argument_list|)
return|;
block|}
return|return
name|ngx_http_error
argument_list|(
name|r
argument_list|,
name|error
argument_list|)
return|;
block|}
end_function

end_unit

