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

begin_comment
comment|/*  * Solaris has thread-safe crypt()  * Linux has crypt_r(); "struct crypt_data" is more than 128K  * FreeBSD needs the mutex to protect crypt()  *  * TODO:  *     ngx_crypt_init() to init mutex  */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_CRYPT
operator|)
end_if

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_GNU_CRYPT_R
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
name|char
modifier|*
name|value
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|struct
name|crypt_data
name|cd
decl_stmt|;
name|cd
operator|.
name|initialized
operator|=
literal|0
expr_stmt|;
comment|/* work around the glibc bug */
name|cd
operator|.
name|current_salt
index|[
literal|0
index|]
operator|=
operator|~
name|salt
index|[
literal|0
index|]
expr_stmt|;
name|value
operator|=
name|crypt_r
argument_list|(
operator|(
name|char
operator|*
operator|)
name|key
argument_list|,
operator|(
name|char
operator|*
operator|)
name|salt
argument_list|,
operator|&
name|cd
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
name|len
operator|=
name|ngx_strlen
argument_list|(
name|value
argument_list|)
operator|+
literal|1
expr_stmt|;
operator|*
name|encrypted
operator|=
name|ngx_pnalloc
argument_list|(
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|encrypted
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_memcpy
argument_list|(
operator|*
name|encrypted
argument_list|,
name|value
argument_list|,
name|len
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|pool
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"crypt_r() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_else
else|#
directive|else
end_else

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
name|char
modifier|*
name|value
decl_stmt|;
name|size_t
name|len
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|&&
name|NGX_NONREENTRANT_CRYPT
operator|)
comment|/* crypt() is a time consuming function, so we only try to lock */
if|if
condition|(
name|ngx_mutex_trylock
argument_list|(
name|ngx_crypt_mutex
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_AGAIN
return|;
block|}
endif|#
directive|endif
name|value
operator|=
name|crypt
argument_list|(
operator|(
name|char
operator|*
operator|)
name|key
argument_list|,
operator|(
name|char
operator|*
operator|)
name|salt
argument_list|)
expr_stmt|;
if|if
condition|(
name|value
condition|)
block|{
name|len
operator|=
name|ngx_strlen
argument_list|(
name|value
argument_list|)
operator|+
literal|1
expr_stmt|;
operator|*
name|encrypted
operator|=
name|ngx_pnalloc
argument_list|(
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
name|encrypted
operator|==
name|NULL
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_THREADS
operator|&&
name|NGX_NONREENTRANT_CRYPT
operator|)
name|ngx_mutex_unlock
argument_list|(
name|ngx_crypt_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_memcpy
argument_list|(
operator|*
name|encrypted
argument_list|,
name|value
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|&&
name|NGX_NONREENTRANT_CRYPT
operator|)
name|ngx_mutex_unlock
argument_list|(
name|ngx_crypt_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|NGX_OK
return|;
block|}
name|err
operator|=
name|ngx_errno
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|&&
name|NGX_NONREENTRANT_CRYPT
operator|)
name|ngx_mutex_unlock
argument_list|(
name|ngx_crypt_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|pool
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"crypt() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* NGX_CRYPT */
end_comment

end_unit

