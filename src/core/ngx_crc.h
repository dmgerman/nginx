begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_CRC_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_CRC_H_INCLUDED_
define|#
directive|define
name|_NGX_CRC_H_INCLUDED_
end_define

begin_comment
comment|/* 32-bit crc16 */
end_comment

begin_function
DECL|function|ngx_crc (char * data,size_t len)
name|ngx_inline
specifier|static
name|uint32_t
name|ngx_crc
parameter_list|(
name|char
modifier|*
name|data
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|uint32_t
name|sum
decl_stmt|;
for|for
control|(
name|sum
operator|=
literal|0
init|;
name|len
condition|;
name|len
operator|--
control|)
block|{
comment|/*          * gcc 2.95.2 x86 and icc 7.1.006 compile that operator          *                                into the single "rol" opcode.          * msvc 6.0sp2 compiles it into four opcodes.          */
name|sum
operator|=
name|sum
operator|>>
literal|1
operator||
name|sum
operator|<<
literal|31
expr_stmt|;
name|sum
operator|+=
operator|*
name|data
operator|++
expr_stmt|;
block|}
return|return
name|sum
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_CRC_H_INCLUDED_ */
end_comment

end_unit

