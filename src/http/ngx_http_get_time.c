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

begin_macro
DECL|function|ngx_http_get_time (char * buf,time_t t)
name|ngx_http_get_time
argument_list|(
argument|char *buf
argument_list|,
argument|time_t t
argument_list|)
end_macro

begin_block
block|{
name|struct
name|tm
modifier|*
name|tp
decl_stmt|;
name|tp
operator|=
name|gmtime
argument_list|(
operator|&
name|t
argument_list|)
expr_stmt|;
return|return
name|strftime
argument_list|(
name|buf
argument_list|,
literal|31
argument_list|,
literal|"%a, %d %b %Y %H:%M:%S GMT"
argument_list|,
name|tp
argument_list|)
return|;
block|}
end_block

end_unit

