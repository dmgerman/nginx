begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_CRC32_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_CRC32_H_INCLUDED_
define|#
directive|define
name|_NGX_CRC32_H_INCLUDED_
end_define

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

begin_decl_stmt
specifier|extern
name|uint32_t
name|ngx_crc32_table
index|[]
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_inline
name|uint32_t
DECL|function|ngx_crc32 (u_char * p,size_t len)
name|ngx_crc32
parameter_list|(
name|u_char
modifier|*
name|p
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|uint32_t
name|crc
decl_stmt|;
name|crc
operator|=
literal|0xffffffff
expr_stmt|;
while|while
condition|(
name|len
operator|--
condition|)
block|{
name|crc
operator|=
name|ngx_crc32_table
index|[
operator|(
name|crc
operator|^
operator|*
name|p
operator|++
operator|)
operator|&
literal|0xff
index|]
operator|^
operator|(
name|crc
operator|>>
literal|8
operator|)
expr_stmt|;
block|}
return|return
name|crc
operator|^
literal|0xffffffff
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_CRC32_H_INCLUDED_ */
end_comment

end_unit

