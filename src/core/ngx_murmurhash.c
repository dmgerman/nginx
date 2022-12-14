begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Austin Appleby  */
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
name|uint32_t
DECL|function|ngx_murmur_hash2 (u_char * data,size_t len)
name|ngx_murmur_hash2
parameter_list|(
name|u_char
modifier|*
name|data
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|uint32_t
name|h
decl_stmt|,
name|k
decl_stmt|;
name|h
operator|=
literal|0
operator|^
name|len
expr_stmt|;
while|while
condition|(
name|len
operator|>=
literal|4
condition|)
block|{
name|k
operator|=
name|data
index|[
literal|0
index|]
expr_stmt|;
name|k
operator||=
name|data
index|[
literal|1
index|]
operator|<<
literal|8
expr_stmt|;
name|k
operator||=
name|data
index|[
literal|2
index|]
operator|<<
literal|16
expr_stmt|;
name|k
operator||=
name|data
index|[
literal|3
index|]
operator|<<
literal|24
expr_stmt|;
name|k
operator|*=
literal|0x5bd1e995
expr_stmt|;
name|k
operator|^=
name|k
operator|>>
literal|24
expr_stmt|;
name|k
operator|*=
literal|0x5bd1e995
expr_stmt|;
name|h
operator|*=
literal|0x5bd1e995
expr_stmt|;
name|h
operator|^=
name|k
expr_stmt|;
name|data
operator|+=
literal|4
expr_stmt|;
name|len
operator|-=
literal|4
expr_stmt|;
block|}
switch|switch
condition|(
name|len
condition|)
block|{
case|case
literal|3
case|:
name|h
operator|^=
name|data
index|[
literal|2
index|]
operator|<<
literal|16
expr_stmt|;
comment|/* fall through */
case|case
literal|2
case|:
name|h
operator|^=
name|data
index|[
literal|1
index|]
operator|<<
literal|8
expr_stmt|;
comment|/* fall through */
case|case
literal|1
case|:
name|h
operator|^=
name|data
index|[
literal|0
index|]
expr_stmt|;
name|h
operator|*=
literal|0x5bd1e995
expr_stmt|;
block|}
name|h
operator|^=
name|h
operator|>>
literal|13
expr_stmt|;
name|h
operator|*=
literal|0x5bd1e995
expr_stmt|;
name|h
operator|^=
name|h
operator|>>
literal|15
expr_stmt|;
return|return
name|h
return|;
block|}
end_function

end_unit

