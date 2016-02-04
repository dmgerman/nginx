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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_DLOPEN
operator|)
end_if

begin_function
name|char
modifier|*
DECL|function|ngx_dlerror (void)
name|ngx_dlerror
parameter_list|(
name|void
parameter_list|)
block|{
name|char
modifier|*
name|err
decl_stmt|;
name|err
operator|=
operator|(
name|char
operator|*
operator|)
name|dlerror
argument_list|()
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NULL
condition|)
block|{
return|return
literal|""
return|;
block|}
return|return
name|err
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

