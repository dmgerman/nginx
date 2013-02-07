begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Maxim Dounin  */
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

begin_include
include|#
directive|include
file|<ngx_crypt.h>
end_include

begin_include
include|#
directive|include
file|<ngx_md5.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SHA1
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_sha1.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_CRYPT
operator|)
end_if

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_crypt_apr1
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_crypt_plain
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
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SHA1
operator|)
end_if

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_crypt_ssha
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
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_crypt_sha
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
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|u_char
modifier|*
name|ngx_crypt_to64
parameter_list|(
name|u_char
modifier|*
name|p
parameter_list|,
name|uint32_t
name|v
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|ngx_int_t
DECL|function|ngx_crypt (ngx_pool_t * pool,u_char * key,u_char * salt,u_char ** encrypted)
name|ngx_crypt
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
if|if
condition|(
name|ngx_strncmp
argument_list|(
name|salt
argument_list|,
literal|"$apr1$"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"$apr1$"
argument_list|)
operator|-
literal|1
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|ngx_crypt_apr1
argument_list|(
name|pool
argument_list|,
name|key
argument_list|,
name|salt
argument_list|,
name|encrypted
argument_list|)
return|;
block|}
if|else if
condition|(
name|ngx_strncmp
argument_list|(
name|salt
argument_list|,
literal|"{PLAIN}"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"{PLAIN}"
argument_list|)
operator|-
literal|1
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|ngx_crypt_plain
argument_list|(
name|pool
argument_list|,
name|key
argument_list|,
name|salt
argument_list|,
name|encrypted
argument_list|)
return|;
if|#
directive|if
operator|(
name|NGX_HAVE_SHA1
operator|)
block|}
if|else if
condition|(
name|ngx_strncmp
argument_list|(
name|salt
argument_list|,
literal|"{SSHA}"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"{SSHA}"
argument_list|)
operator|-
literal|1
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|ngx_crypt_ssha
argument_list|(
name|pool
argument_list|,
name|key
argument_list|,
name|salt
argument_list|,
name|encrypted
argument_list|)
return|;
block|}
if|else if
condition|(
name|ngx_strncmp
argument_list|(
name|salt
argument_list|,
literal|"{SHA}"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"{SHA}"
argument_list|)
operator|-
literal|1
argument_list|)
operator|==
literal|0
condition|)
block|{
return|return
name|ngx_crypt_sha
argument_list|(
name|pool
argument_list|,
name|key
argument_list|,
name|salt
argument_list|,
name|encrypted
argument_list|)
return|;
endif|#
directive|endif
block|}
comment|/* fallback to libc crypt() */
return|return
name|ngx_libc_crypt
argument_list|(
name|pool
argument_list|,
name|key
argument_list|,
name|salt
argument_list|,
name|encrypted
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_crypt_apr1 (ngx_pool_t * pool,u_char * key,u_char * salt,u_char ** encrypted)
name|ngx_crypt_apr1
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
name|ngx_int_t
name|n
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|u_char
modifier|*
name|p
decl_stmt|,
modifier|*
name|last
decl_stmt|,
name|final
index|[
literal|16
index|]
decl_stmt|;
name|size_t
name|saltlen
decl_stmt|,
name|keylen
decl_stmt|;
name|ngx_md5_t
name|md5
decl_stmt|,
name|ctx1
decl_stmt|;
comment|/* Apache's apr1 crypt is Paul-Henning Kamp's md5 crypt with $apr1$ magic */
name|keylen
operator|=
name|ngx_strlen
argument_list|(
name|key
argument_list|)
expr_stmt|;
comment|/* true salt: no magic, max 8 chars, stop at first $ */
name|salt
operator|+=
sizeof|sizeof
argument_list|(
literal|"$apr1$"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|last
operator|=
name|salt
operator|+
literal|8
expr_stmt|;
for|for
control|(
name|p
operator|=
name|salt
init|;
operator|*
name|p
operator|&&
operator|*
name|p
operator|!=
literal|'$'
operator|&&
name|p
operator|<
name|last
condition|;
name|p
operator|++
control|)
block|{
comment|/* void */
block|}
name|saltlen
operator|=
name|p
operator|-
name|salt
expr_stmt|;
comment|/* hash key and salt */
name|ngx_md5_init
argument_list|(
operator|&
name|md5
argument_list|)
expr_stmt|;
name|ngx_md5_update
argument_list|(
operator|&
name|md5
argument_list|,
name|key
argument_list|,
name|keylen
argument_list|)
expr_stmt|;
name|ngx_md5_update
argument_list|(
operator|&
name|md5
argument_list|,
operator|(
name|u_char
operator|*
operator|)
literal|"$apr1$"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"$apr1$"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ngx_md5_update
argument_list|(
operator|&
name|md5
argument_list|,
name|salt
argument_list|,
name|saltlen
argument_list|)
expr_stmt|;
name|ngx_md5_init
argument_list|(
operator|&
name|ctx1
argument_list|)
expr_stmt|;
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|key
argument_list|,
name|keylen
argument_list|)
expr_stmt|;
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|salt
argument_list|,
name|saltlen
argument_list|)
expr_stmt|;
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|key
argument_list|,
name|keylen
argument_list|)
expr_stmt|;
name|ngx_md5_final
argument_list|(
name|final
argument_list|,
operator|&
name|ctx1
argument_list|)
expr_stmt|;
for|for
control|(
name|n
operator|=
name|keylen
init|;
name|n
operator|>
literal|0
condition|;
name|n
operator|-=
literal|16
control|)
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|md5
argument_list|,
name|final
argument_list|,
name|n
operator|>
literal|16
condition|?
literal|16
else|:
name|n
argument_list|)
expr_stmt|;
block|}
name|ngx_memzero
argument_list|(
name|final
argument_list|,
sizeof|sizeof
argument_list|(
name|final
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
name|keylen
init|;
name|i
condition|;
name|i
operator|>>=
literal|1
control|)
block|{
if|if
condition|(
name|i
operator|&
literal|1
condition|)
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|md5
argument_list|,
name|final
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|md5
argument_list|,
name|key
argument_list|,
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
name|ngx_md5_final
argument_list|(
name|final
argument_list|,
operator|&
name|md5
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|1000
condition|;
name|i
operator|++
control|)
block|{
name|ngx_md5_init
argument_list|(
operator|&
name|ctx1
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|&
literal|1
condition|)
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|key
argument_list|,
name|keylen
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|final
argument_list|,
literal|16
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|%
literal|3
condition|)
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|salt
argument_list|,
name|saltlen
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|%
literal|7
condition|)
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|key
argument_list|,
name|keylen
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|i
operator|&
literal|1
condition|)
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|final
argument_list|,
literal|16
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|ngx_md5_update
argument_list|(
operator|&
name|ctx1
argument_list|,
name|key
argument_list|,
name|keylen
argument_list|)
expr_stmt|;
block|}
name|ngx_md5_final
argument_list|(
name|final
argument_list|,
operator|&
name|ctx1
argument_list|)
expr_stmt|;
block|}
comment|/* output */
operator|*
name|encrypted
operator|=
name|ngx_pnalloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
literal|"$apr1$"
argument_list|)
operator|-
literal|1
operator|+
name|saltlen
operator|+
literal|16
operator|+
literal|1
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
name|p
operator|=
name|ngx_cpymem
argument_list|(
operator|*
name|encrypted
argument_list|,
literal|"$apr1$"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"$apr1$"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_copy
argument_list|(
name|p
argument_list|,
name|salt
argument_list|,
name|saltlen
argument_list|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'$'
expr_stmt|;
name|p
operator|=
name|ngx_crypt_to64
argument_list|(
name|p
argument_list|,
operator|(
name|final
index|[
literal|0
index|]
operator|<<
literal|16
operator|)
operator||
operator|(
name|final
index|[
literal|6
index|]
operator|<<
literal|8
operator|)
operator||
name|final
index|[
literal|12
index|]
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_crypt_to64
argument_list|(
name|p
argument_list|,
operator|(
name|final
index|[
literal|1
index|]
operator|<<
literal|16
operator|)
operator||
operator|(
name|final
index|[
literal|7
index|]
operator|<<
literal|8
operator|)
operator||
name|final
index|[
literal|13
index|]
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_crypt_to64
argument_list|(
name|p
argument_list|,
operator|(
name|final
index|[
literal|2
index|]
operator|<<
literal|16
operator|)
operator||
operator|(
name|final
index|[
literal|8
index|]
operator|<<
literal|8
operator|)
operator||
name|final
index|[
literal|14
index|]
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_crypt_to64
argument_list|(
name|p
argument_list|,
operator|(
name|final
index|[
literal|3
index|]
operator|<<
literal|16
operator|)
operator||
operator|(
name|final
index|[
literal|9
index|]
operator|<<
literal|8
operator|)
operator||
name|final
index|[
literal|15
index|]
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_crypt_to64
argument_list|(
name|p
argument_list|,
operator|(
name|final
index|[
literal|4
index|]
operator|<<
literal|16
operator|)
operator||
operator|(
name|final
index|[
literal|10
index|]
operator|<<
literal|8
operator|)
operator||
name|final
index|[
literal|5
index|]
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_crypt_to64
argument_list|(
name|p
argument_list|,
name|final
index|[
literal|11
index|]
argument_list|,
literal|2
argument_list|)
expr_stmt|;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|u_char
modifier|*
DECL|function|ngx_crypt_to64 (u_char * p,uint32_t v,size_t n)
name|ngx_crypt_to64
parameter_list|(
name|u_char
modifier|*
name|p
parameter_list|,
name|uint32_t
name|v
parameter_list|,
name|size_t
name|n
parameter_list|)
block|{
specifier|static
name|u_char
name|itoa64
index|[]
init|=
literal|"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
decl_stmt|;
while|while
condition|(
name|n
operator|--
condition|)
block|{
operator|*
name|p
operator|++
operator|=
name|itoa64
index|[
name|v
operator|&
literal|0x3f
index|]
expr_stmt|;
name|v
operator|>>=
literal|6
expr_stmt|;
block|}
return|return
name|p
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_crypt_plain (ngx_pool_t * pool,u_char * key,u_char * salt,u_char ** encrypted)
name|ngx_crypt_plain
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
name|size_t
name|len
decl_stmt|;
name|u_char
modifier|*
name|p
decl_stmt|;
name|len
operator|=
name|ngx_strlen
argument_list|(
name|key
argument_list|)
expr_stmt|;
operator|*
name|encrypted
operator|=
name|ngx_pnalloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
literal|"{PLAIN}"
argument_list|)
operator|-
literal|1
operator|+
name|len
operator|+
literal|1
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
name|p
operator|=
name|ngx_cpymem
argument_list|(
operator|*
name|encrypted
argument_list|,
literal|"{PLAIN}"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"{PLAIN}"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|p
argument_list|,
name|key
argument_list|,
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SHA1
operator|)
end_if

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_crypt_ssha (ngx_pool_t * pool,u_char * key,u_char * salt,u_char ** encrypted)
name|ngx_crypt_ssha
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
name|size_t
name|len
decl_stmt|;
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_str_t
name|encoded
decl_stmt|,
name|decoded
decl_stmt|;
name|ngx_sha1_t
name|sha1
decl_stmt|;
comment|/* "{SSHA}" base64(SHA1(key salt) salt) */
comment|/* decode base64 salt to find out true salt */
name|encoded
operator|.
name|data
operator|=
name|salt
operator|+
sizeof|sizeof
argument_list|(
literal|"{SSHA}"
argument_list|)
operator|-
literal|1
expr_stmt|;
name|encoded
operator|.
name|len
operator|=
name|ngx_strlen
argument_list|(
name|encoded
operator|.
name|data
argument_list|)
expr_stmt|;
name|len
operator|=
name|ngx_max
argument_list|(
name|ngx_base64_decoded_length
argument_list|(
name|encoded
operator|.
name|len
argument_list|)
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|decoded
operator|.
name|data
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
name|decoded
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|rc
operator|=
name|ngx_decode_base64
argument_list|(
operator|&
name|decoded
argument_list|,
operator|&
name|encoded
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
operator|||
name|decoded
operator|.
name|len
operator|<
literal|20
condition|)
block|{
name|decoded
operator|.
name|len
operator|=
literal|20
expr_stmt|;
block|}
comment|/* update SHA1 from key and salt */
name|ngx_sha1_init
argument_list|(
operator|&
name|sha1
argument_list|)
expr_stmt|;
name|ngx_sha1_update
argument_list|(
operator|&
name|sha1
argument_list|,
name|key
argument_list|,
name|ngx_strlen
argument_list|(
name|key
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_sha1_update
argument_list|(
operator|&
name|sha1
argument_list|,
name|decoded
operator|.
name|data
operator|+
literal|20
argument_list|,
name|decoded
operator|.
name|len
operator|-
literal|20
argument_list|)
expr_stmt|;
name|ngx_sha1_final
argument_list|(
name|decoded
operator|.
name|data
argument_list|,
operator|&
name|sha1
argument_list|)
expr_stmt|;
comment|/* encode it back to base64 */
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"{SSHA}"
argument_list|)
operator|-
literal|1
operator|+
name|ngx_base64_encoded_length
argument_list|(
name|decoded
operator|.
name|len
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
name|encoded
operator|.
name|data
operator|=
name|ngx_cpymem
argument_list|(
operator|*
name|encrypted
argument_list|,
literal|"{SSHA}"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"{SSHA}"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ngx_encode_base64
argument_list|(
operator|&
name|encoded
argument_list|,
operator|&
name|decoded
argument_list|)
expr_stmt|;
name|encoded
operator|.
name|data
index|[
name|encoded
operator|.
name|len
index|]
operator|=
literal|'\0'
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_crypt_sha (ngx_pool_t * pool,u_char * key,u_char * salt,u_char ** encrypted)
name|ngx_crypt_sha
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
name|size_t
name|len
decl_stmt|;
name|ngx_str_t
name|encoded
decl_stmt|,
name|decoded
decl_stmt|;
name|ngx_sha1_t
name|sha1
decl_stmt|;
name|u_char
name|digest
index|[
literal|20
index|]
decl_stmt|;
comment|/* "{SHA}" base64(SHA1(key)) */
name|decoded
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
name|digest
argument_list|)
expr_stmt|;
name|decoded
operator|.
name|data
operator|=
name|digest
expr_stmt|;
name|ngx_sha1_init
argument_list|(
operator|&
name|sha1
argument_list|)
expr_stmt|;
name|ngx_sha1_update
argument_list|(
operator|&
name|sha1
argument_list|,
name|key
argument_list|,
name|ngx_strlen
argument_list|(
name|key
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_sha1_final
argument_list|(
name|digest
argument_list|,
operator|&
name|sha1
argument_list|)
expr_stmt|;
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|"{SHA}"
argument_list|)
operator|-
literal|1
operator|+
name|ngx_base64_encoded_length
argument_list|(
name|decoded
operator|.
name|len
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
name|encoded
operator|.
name|data
operator|=
name|ngx_cpymem
argument_list|(
operator|*
name|encrypted
argument_list|,
literal|"{SHA}"
argument_list|,
sizeof|sizeof
argument_list|(
literal|"{SHA}"
argument_list|)
operator|-
literal|1
argument_list|)
expr_stmt|;
name|ngx_encode_base64
argument_list|(
operator|&
name|encoded
argument_list|,
operator|&
name|decoded
argument_list|)
expr_stmt|;
name|encoded
operator|.
name|data
index|[
name|encoded
operator|.
name|len
index|]
operator|=
literal|'\0'
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
comment|/* NGX_HAVE_SHA1 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* NGX_CRYPT */
end_comment

end_unit

