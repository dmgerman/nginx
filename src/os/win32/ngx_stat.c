begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev  */
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

begin_function
DECL|function|ngx_file_type (char * file,ngx_file_info_t * sb)
name|int
name|ngx_file_type
parameter_list|(
name|char
modifier|*
name|file
parameter_list|,
name|ngx_file_info_t
modifier|*
name|sb
parameter_list|)
block|{
name|sb
operator|->
name|dwFileAttributes
operator|=
name|GetFileAttributes
argument_list|(
name|file
argument_list|)
expr_stmt|;
if|if
condition|(
name|sb
operator|->
name|dwFileAttributes
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

begin_comment
comment|/* int ngx_stat(char *file, ngx_stat_t *sb) {     *sb = GetFileAttributes(file);      if (*sb == INVALID_FILE_ATTRIBUTES) {         return -1;     }      return 0; } */
end_comment

end_unit

