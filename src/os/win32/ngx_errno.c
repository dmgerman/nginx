begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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
name|u_char
modifier|*
DECL|function|ngx_strerror (ngx_err_t err,u_char * errstr,size_t size)
name|ngx_strerror
parameter_list|(
name|ngx_err_t
name|err
parameter_list|,
name|u_char
modifier|*
name|errstr
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|u_int
name|len
decl_stmt|;
specifier|static
name|u_long
name|lang
init|=
name|MAKELANGID
argument_list|(
name|LANG_ENGLISH
argument_list|,
name|SUBLANG_ENGLISH_US
argument_list|)
decl_stmt|;
if|if
condition|(
name|size
operator|==
literal|0
condition|)
block|{
return|return
name|errstr
return|;
block|}
name|len
operator|=
name|FormatMessage
argument_list|(
name|FORMAT_MESSAGE_FROM_SYSTEM
argument_list|,
name|NULL
argument_list|,
name|err
argument_list|,
name|lang
argument_list|,
operator|(
name|char
operator|*
operator|)
name|errstr
argument_list|,
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|==
literal|0
operator|&&
name|lang
operator|&&
name|GetLastError
argument_list|()
operator|==
name|ERROR_RESOURCE_LANG_NOT_FOUND
condition|)
block|{
comment|/*          * Try to use English messages first and fallback to a language,          * based on locale: non-English Windows have no English messages          * at all.  This way allows to use English messages at least on          * Windows with MUI.          */
name|lang
operator|=
literal|0
expr_stmt|;
name|len
operator|=
name|FormatMessage
argument_list|(
name|FORMAT_MESSAGE_FROM_SYSTEM
argument_list|,
name|NULL
argument_list|,
name|err
argument_list|,
name|lang
argument_list|,
operator|(
name|char
operator|*
operator|)
name|errstr
argument_list|,
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|len
operator|==
literal|0
condition|)
block|{
return|return
name|ngx_snprintf
argument_list|(
name|errstr
argument_list|,
name|size
argument_list|,
literal|"FormatMessage() error:(%d)"
argument_list|,
name|GetLastError
argument_list|()
argument_list|)
return|;
block|}
comment|/* remove ".\r\n\0" */
while|while
condition|(
name|errstr
index|[
name|len
index|]
operator|==
literal|'\0'
operator|||
name|errstr
index|[
name|len
index|]
operator|==
name|CR
operator|||
name|errstr
index|[
name|len
index|]
operator|==
name|LF
operator|||
name|errstr
index|[
name|len
index|]
operator|==
literal|'.'
condition|)
block|{
operator|--
name|len
expr_stmt|;
block|}
return|return
operator|&
name|errstr
index|[
operator|++
name|len
index|]
return|;
block|}
end_function

begin_function
name|ngx_uint_t
DECL|function|ngx_strerror_init (void)
name|ngx_strerror_init
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

