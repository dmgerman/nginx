begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<windows.h>
end_include

begin_include
include|#
directive|include
file|<ngx_stat.h>
end_include

begin_function
DECL|function|ngx_stat (char * file,ngx_stat_t * sb)
name|int
name|ngx_stat
parameter_list|(
name|char
modifier|*
name|file
parameter_list|,
name|ngx_stat_t
modifier|*
name|sb
parameter_list|)
block|{
operator|*
name|sb
operator|=
name|GetFileAttributes
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|sb
operator|==
name|INVALID_FILE_ATTRIBUTES
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

end_unit

