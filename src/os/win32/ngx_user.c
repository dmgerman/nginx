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

begin_if
if|#
directive|if
operator|(
name|NGX_CRYPT
operator|)
end_if

begin_function
name|ngx_int_t
DECL|function|ngx_libc_crypt (ngx_pool_t * pool,u_char * key,u_char * salt,u_char ** encrypted)
name|ngx_libc_crypt
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|u_char
modifier|*
name|key
parameter_list|,
name|u_char
modifier|*
name|salt
parameter_list|,
name|u_char
modifier|*
modifier|*
name|encrypted
parameter_list|)
block|{
comment|/* STUB: a plain text password */
operator|*
name|encrypted
operator|=
name|key
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* NGX_CRYPT */
end_comment

end_unit

