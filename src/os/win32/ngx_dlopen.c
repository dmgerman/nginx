begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Maxim Dounin  * Copyright (C) Nginx, Inc.  */
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
name|char
modifier|*
DECL|function|ngx_dlerror (void)
name|ngx_dlerror
parameter_list|(
name|void
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
specifier|static
name|u_char
name|errstr
index|[
name|NGX_MAX_ERROR_STR
index|]
decl_stmt|;
name|p
operator|=
name|ngx_strerror
argument_list|(
name|ngx_errno
argument_list|,
name|errstr
argument_list|,
name|NGX_MAX_ERROR_STR
argument_list|)
expr_stmt|;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
return|return
operator|(
name|char
operator|*
operator|)
name|errstr
return|;
block|}
end_function

end_unit

