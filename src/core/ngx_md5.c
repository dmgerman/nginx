begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * An internal implementation, based on Alexander Peslyak's  * public domain implementation:  * http://openwall.info/wiki/people/solar/software/public-domain-source-code/md5  * It is not expected to be optimal and is used only  * if no MD5 implementation was found in system.  */
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
file|<ngx_md5.h>
end_include

begin_if
if|#
directive|if
operator|!
operator|(
name|NGX_HAVE_MD5
operator|)
end_if

begin_function_decl
specifier|static
specifier|const
name|u_char
modifier|*
name|ngx_md5_body
parameter_list|(
name|ngx_md5_t
modifier|*
name|ctx
parameter_list|,
specifier|const
name|u_char
modifier|*
name|data
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|ngx_md5_init (ngx_md5_t * ctx)
name|ngx_md5_init
parameter_list|(
name|ngx_md5_t
modifier|*
name|ctx
parameter_list|)
block|{
name|ctx
operator|->
name|a
operator|=
literal|0x67452301
expr_stmt|;
name|ctx
operator|->
name|b
operator|=
literal|0xefcdab89
expr_stmt|;
name|ctx
operator|->
name|c
operator|=
literal|0x98badcfe
expr_stmt|;
name|ctx
operator|->
name|d
operator|=
literal|0x10325476
expr_stmt|;
name|ctx
operator|->
name|bytes
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_md5_update (ngx_md5_t * ctx,const void * data,size_t size)
name|ngx_md5_update
parameter_list|(
name|ngx_md5_t
modifier|*
name|ctx
parameter_list|,
specifier|const
name|void
modifier|*
name|data
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|size_t
name|used
decl_stmt|,
name|free
decl_stmt|;
name|used
operator|=
name|ctx
operator|->
name|bytes
operator|&
literal|0x3f
expr_stmt|;
name|ctx
operator|->
name|bytes
operator|+=
name|size
expr_stmt|;
if|if
condition|(
name|used
condition|)
block|{
name|free
operator|=
literal|64
operator|-
name|used
expr_stmt|;
if|if
condition|(
name|size
operator|<
name|free
condition|)
block|{
name|ngx_memcpy
argument_list|(
operator|&
name|ctx
operator|->
name|buffer
index|[
name|used
index|]
argument_list|,
name|data
argument_list|,
name|size
argument_list|)
expr_stmt|;
return|return;
block|}
name|data
operator|=
name|ngx_cpymem
argument_list|(
operator|&
name|ctx
operator|->
name|buffer
index|[
name|used
index|]
argument_list|,
name|data
argument_list|,
name|free
argument_list|)
expr_stmt|;
name|size
operator|-=
name|free
expr_stmt|;
operator|(
name|void
operator|)
name|ngx_md5_body
argument_list|(
name|ctx
argument_list|,
name|ctx
operator|->
name|buffer
argument_list|,
literal|64
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|size
operator|>=
literal|64
condition|)
block|{
name|data
operator|=
name|ngx_md5_body
argument_list|(
name|ctx
argument_list|,
name|data
argument_list|,
name|size
operator|&
operator|~
operator|(
name|size_t
operator|)
literal|0x3f
argument_list|)
expr_stmt|;
name|size
operator|&=
literal|0x3f
expr_stmt|;
block|}
name|ngx_memcpy
argument_list|(
name|ctx
operator|->
name|buffer
argument_list|,
name|data
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_md5_final (u_char result[16],ngx_md5_t * ctx)
name|ngx_md5_final
parameter_list|(
name|u_char
name|result
index|[
literal|16
index|]
parameter_list|,
name|ngx_md5_t
modifier|*
name|ctx
parameter_list|)
block|{
name|size_t
name|used
decl_stmt|,
name|free
decl_stmt|;
name|used
operator|=
name|ctx
operator|->
name|bytes
operator|&
literal|0x3f
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
name|used
operator|++
index|]
operator|=
literal|0x80
expr_stmt|;
name|free
operator|=
literal|64
operator|-
name|used
expr_stmt|;
if|if
condition|(
name|free
operator|<
literal|8
condition|)
block|{
name|ngx_memzero
argument_list|(
operator|&
name|ctx
operator|->
name|buffer
index|[
name|used
index|]
argument_list|,
name|free
argument_list|)
expr_stmt|;
operator|(
name|void
operator|)
name|ngx_md5_body
argument_list|(
name|ctx
argument_list|,
name|ctx
operator|->
name|buffer
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|used
operator|=
literal|0
expr_stmt|;
name|free
operator|=
literal|64
expr_stmt|;
block|}
name|ngx_memzero
argument_list|(
operator|&
name|ctx
operator|->
name|buffer
index|[
name|used
index|]
argument_list|,
name|free
operator|-
literal|8
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|bytes
operator|<<=
literal|3
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
literal|56
index|]
operator|=
name|ctx
operator|->
name|bytes
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
literal|57
index|]
operator|=
name|ctx
operator|->
name|bytes
operator|>>
literal|8
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
literal|58
index|]
operator|=
name|ctx
operator|->
name|bytes
operator|>>
literal|16
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
literal|59
index|]
operator|=
name|ctx
operator|->
name|bytes
operator|>>
literal|24
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
literal|60
index|]
operator|=
name|ctx
operator|->
name|bytes
operator|>>
literal|32
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
literal|61
index|]
operator|=
name|ctx
operator|->
name|bytes
operator|>>
literal|40
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
literal|62
index|]
operator|=
name|ctx
operator|->
name|bytes
operator|>>
literal|48
expr_stmt|;
name|ctx
operator|->
name|buffer
index|[
literal|63
index|]
operator|=
name|ctx
operator|->
name|bytes
operator|>>
literal|56
expr_stmt|;
operator|(
name|void
operator|)
name|ngx_md5_body
argument_list|(
name|ctx
argument_list|,
name|ctx
operator|->
name|buffer
argument_list|,
literal|64
argument_list|)
expr_stmt|;
name|result
index|[
literal|0
index|]
operator|=
name|ctx
operator|->
name|a
expr_stmt|;
name|result
index|[
literal|1
index|]
operator|=
name|ctx
operator|->
name|a
operator|>>
literal|8
expr_stmt|;
name|result
index|[
literal|2
index|]
operator|=
name|ctx
operator|->
name|a
operator|>>
literal|16
expr_stmt|;
name|result
index|[
literal|3
index|]
operator|=
name|ctx
operator|->
name|a
operator|>>
literal|24
expr_stmt|;
name|result
index|[
literal|4
index|]
operator|=
name|ctx
operator|->
name|b
expr_stmt|;
name|result
index|[
literal|5
index|]
operator|=
name|ctx
operator|->
name|b
operator|>>
literal|8
expr_stmt|;
name|result
index|[
literal|6
index|]
operator|=
name|ctx
operator|->
name|b
operator|>>
literal|16
expr_stmt|;
name|result
index|[
literal|7
index|]
operator|=
name|ctx
operator|->
name|b
operator|>>
literal|24
expr_stmt|;
name|result
index|[
literal|8
index|]
operator|=
name|ctx
operator|->
name|c
expr_stmt|;
name|result
index|[
literal|9
index|]
operator|=
name|ctx
operator|->
name|c
operator|>>
literal|8
expr_stmt|;
name|result
index|[
literal|10
index|]
operator|=
name|ctx
operator|->
name|c
operator|>>
literal|16
expr_stmt|;
name|result
index|[
literal|11
index|]
operator|=
name|ctx
operator|->
name|c
operator|>>
literal|24
expr_stmt|;
name|result
index|[
literal|12
index|]
operator|=
name|ctx
operator|->
name|d
expr_stmt|;
name|result
index|[
literal|13
index|]
operator|=
name|ctx
operator|->
name|d
operator|>>
literal|8
expr_stmt|;
name|result
index|[
literal|14
index|]
operator|=
name|ctx
operator|->
name|d
operator|>>
literal|16
expr_stmt|;
name|result
index|[
literal|15
index|]
operator|=
name|ctx
operator|->
name|d
operator|>>
literal|24
expr_stmt|;
name|ngx_memzero
argument_list|(
name|ctx
argument_list|,
sizeof|sizeof
argument_list|(
operator|*
name|ctx
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * The basic MD5 functions.  *  * F and G are optimized compared to their RFC 1321 definitions for  * architectures that lack an AND-NOT instruction, just like in  * Colin Plumb's implementation.  */
end_comment

begin_define
DECL|macro|F (x,y,z)
define|#
directive|define
name|F
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|((z) ^ ((x)& ((y) ^ (z))))
end_define

begin_define
DECL|macro|G (x,y,z)
define|#
directive|define
name|G
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|((y) ^ ((z)& ((x) ^ (y))))
end_define

begin_define
DECL|macro|H (x,y,z)
define|#
directive|define
name|H
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|((x) ^ (y) ^ (z))
end_define

begin_define
DECL|macro|I (x,y,z)
define|#
directive|define
name|I
parameter_list|(
name|x
parameter_list|,
name|y
parameter_list|,
name|z
parameter_list|)
value|((y) ^ ((x) | ~(z)))
end_define

begin_comment
comment|/*  * The MD5 transformation for all four rounds.  */
end_comment

begin_define
DECL|macro|STEP (f,a,b,c,d,x,t,s)
define|#
directive|define
name|STEP
parameter_list|(
name|f
parameter_list|,
name|a
parameter_list|,
name|b
parameter_list|,
name|c
parameter_list|,
name|d
parameter_list|,
name|x
parameter_list|,
name|t
parameter_list|,
name|s
parameter_list|)
define|\
value|(a) += f((b), (c), (d)) + (x) + (t);                                      \     (a) = (((a)<< (s)) | (((a)& 0xffffffff)>> (32 - (s))));                \     (a) += (b)
end_define

begin_comment
comment|/*  * SET() reads 4 input bytes in little-endian byte order and stores them  * in a properly aligned word in host byte order.  *  * The check for little-endian architectures that tolerate unaligned  * memory accesses is just an optimization.  Nothing will break if it  * does not work.  */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_LITTLE_ENDIAN
operator|&&
name|NGX_HAVE_NONALIGNED
operator|)
end_if

begin_define
DECL|macro|SET (n)
define|#
directive|define
name|SET
parameter_list|(
name|n
parameter_list|)
value|(*(uint32_t *)&p[n * 4])
end_define

begin_define
DECL|macro|GET (n)
define|#
directive|define
name|GET
parameter_list|(
name|n
parameter_list|)
value|(*(uint32_t *)&p[n * 4])
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|SET (n)
define|#
directive|define
name|SET
parameter_list|(
name|n
parameter_list|)
define|\
value|(block[n] =                                                               \     (uint32_t) p[n * 4] |                                                     \     ((uint32_t) p[n * 4 + 1]<< 8) |                                          \     ((uint32_t) p[n * 4 + 2]<< 16) |                                         \     ((uint32_t) p[n * 4 + 3]<< 24))
end_define

begin_define
DECL|macro|GET (n)
define|#
directive|define
name|GET
parameter_list|(
name|n
parameter_list|)
value|block[n]
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  * This processes one or more 64-byte data blocks, but does not update  * the bit counters.  There are no alignment requirements.  */
end_comment

begin_function
specifier|static
specifier|const
name|u_char
modifier|*
DECL|function|ngx_md5_body (ngx_md5_t * ctx,const u_char * data,size_t size)
name|ngx_md5_body
parameter_list|(
name|ngx_md5_t
modifier|*
name|ctx
parameter_list|,
specifier|const
name|u_char
modifier|*
name|data
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|uint32_t
name|a
decl_stmt|,
name|b
decl_stmt|,
name|c
decl_stmt|,
name|d
decl_stmt|;
name|uint32_t
name|saved_a
decl_stmt|,
name|saved_b
decl_stmt|,
name|saved_c
decl_stmt|,
name|saved_d
decl_stmt|;
specifier|const
name|u_char
modifier|*
name|p
decl_stmt|;
if|#
directive|if
operator|!
operator|(
name|NGX_HAVE_LITTLE_ENDIAN
operator|&&
name|NGX_HAVE_NONALIGNED
operator|)
name|uint32_t
name|block
index|[
literal|16
index|]
decl_stmt|;
endif|#
directive|endif
name|p
operator|=
name|data
expr_stmt|;
name|a
operator|=
name|ctx
operator|->
name|a
expr_stmt|;
name|b
operator|=
name|ctx
operator|->
name|b
expr_stmt|;
name|c
operator|=
name|ctx
operator|->
name|c
expr_stmt|;
name|d
operator|=
name|ctx
operator|->
name|d
expr_stmt|;
do|do
block|{
name|saved_a
operator|=
name|a
expr_stmt|;
name|saved_b
operator|=
name|b
expr_stmt|;
name|saved_c
operator|=
name|c
expr_stmt|;
name|saved_d
operator|=
name|d
expr_stmt|;
comment|/* Round 1 */
name|STEP
argument_list|(
name|F
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|SET
argument_list|(
literal|0
argument_list|)
argument_list|,
literal|0xd76aa478
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|SET
argument_list|(
literal|1
argument_list|)
argument_list|,
literal|0xe8c7b756
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|SET
argument_list|(
literal|2
argument_list|)
argument_list|,
literal|0x242070db
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|SET
argument_list|(
literal|3
argument_list|)
argument_list|,
literal|0xc1bdceee
argument_list|,
literal|22
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|SET
argument_list|(
literal|4
argument_list|)
argument_list|,
literal|0xf57c0faf
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|SET
argument_list|(
literal|5
argument_list|)
argument_list|,
literal|0x4787c62a
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|SET
argument_list|(
literal|6
argument_list|)
argument_list|,
literal|0xa8304613
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|SET
argument_list|(
literal|7
argument_list|)
argument_list|,
literal|0xfd469501
argument_list|,
literal|22
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|SET
argument_list|(
literal|8
argument_list|)
argument_list|,
literal|0x698098d8
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|SET
argument_list|(
literal|9
argument_list|)
argument_list|,
literal|0x8b44f7af
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|SET
argument_list|(
literal|10
argument_list|)
argument_list|,
literal|0xffff5bb1
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|SET
argument_list|(
literal|11
argument_list|)
argument_list|,
literal|0x895cd7be
argument_list|,
literal|22
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|SET
argument_list|(
literal|12
argument_list|)
argument_list|,
literal|0x6b901122
argument_list|,
literal|7
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|SET
argument_list|(
literal|13
argument_list|)
argument_list|,
literal|0xfd987193
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|SET
argument_list|(
literal|14
argument_list|)
argument_list|,
literal|0xa679438e
argument_list|,
literal|17
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|F
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|SET
argument_list|(
literal|15
argument_list|)
argument_list|,
literal|0x49b40821
argument_list|,
literal|22
argument_list|)
expr_stmt|;
comment|/* Round 2 */
name|STEP
argument_list|(
name|G
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|1
argument_list|)
argument_list|,
literal|0xf61e2562
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|6
argument_list|)
argument_list|,
literal|0xc040b340
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|11
argument_list|)
argument_list|,
literal|0x265e5a51
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|0
argument_list|)
argument_list|,
literal|0xe9b6c7aa
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|5
argument_list|)
argument_list|,
literal|0xd62f105d
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|10
argument_list|)
argument_list|,
literal|0x02441453
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|15
argument_list|)
argument_list|,
literal|0xd8a1e681
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|4
argument_list|)
argument_list|,
literal|0xe7d3fbc8
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|9
argument_list|)
argument_list|,
literal|0x21e1cde6
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|14
argument_list|)
argument_list|,
literal|0xc33707d6
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|3
argument_list|)
argument_list|,
literal|0xf4d50d87
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|8
argument_list|)
argument_list|,
literal|0x455a14ed
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|13
argument_list|)
argument_list|,
literal|0xa9e3e905
argument_list|,
literal|5
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|2
argument_list|)
argument_list|,
literal|0xfcefa3f8
argument_list|,
literal|9
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|7
argument_list|)
argument_list|,
literal|0x676f02d9
argument_list|,
literal|14
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|G
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|12
argument_list|)
argument_list|,
literal|0x8d2a4c8a
argument_list|,
literal|20
argument_list|)
expr_stmt|;
comment|/* Round 3 */
name|STEP
argument_list|(
name|H
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|5
argument_list|)
argument_list|,
literal|0xfffa3942
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|8
argument_list|)
argument_list|,
literal|0x8771f681
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|11
argument_list|)
argument_list|,
literal|0x6d9d6122
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|14
argument_list|)
argument_list|,
literal|0xfde5380c
argument_list|,
literal|23
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|1
argument_list|)
argument_list|,
literal|0xa4beea44
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|4
argument_list|)
argument_list|,
literal|0x4bdecfa9
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|7
argument_list|)
argument_list|,
literal|0xf6bb4b60
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|10
argument_list|)
argument_list|,
literal|0xbebfbc70
argument_list|,
literal|23
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|13
argument_list|)
argument_list|,
literal|0x289b7ec6
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|0
argument_list|)
argument_list|,
literal|0xeaa127fa
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|3
argument_list|)
argument_list|,
literal|0xd4ef3085
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|6
argument_list|)
argument_list|,
literal|0x04881d05
argument_list|,
literal|23
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|9
argument_list|)
argument_list|,
literal|0xd9d4d039
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|12
argument_list|)
argument_list|,
literal|0xe6db99e5
argument_list|,
literal|11
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|15
argument_list|)
argument_list|,
literal|0x1fa27cf8
argument_list|,
literal|16
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|H
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|2
argument_list|)
argument_list|,
literal|0xc4ac5665
argument_list|,
literal|23
argument_list|)
expr_stmt|;
comment|/* Round 4 */
name|STEP
argument_list|(
name|I
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|0
argument_list|)
argument_list|,
literal|0xf4292244
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|7
argument_list|)
argument_list|,
literal|0x432aff97
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|14
argument_list|)
argument_list|,
literal|0xab9423a7
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|5
argument_list|)
argument_list|,
literal|0xfc93a039
argument_list|,
literal|21
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|12
argument_list|)
argument_list|,
literal|0x655b59c3
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|3
argument_list|)
argument_list|,
literal|0x8f0ccc92
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|10
argument_list|)
argument_list|,
literal|0xffeff47d
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|1
argument_list|)
argument_list|,
literal|0x85845dd1
argument_list|,
literal|21
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|8
argument_list|)
argument_list|,
literal|0x6fa87e4f
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|15
argument_list|)
argument_list|,
literal|0xfe2ce6e0
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|6
argument_list|)
argument_list|,
literal|0xa3014314
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|13
argument_list|)
argument_list|,
literal|0x4e0811a1
argument_list|,
literal|21
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|GET
argument_list|(
literal|4
argument_list|)
argument_list|,
literal|0xf7537e82
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|GET
argument_list|(
literal|11
argument_list|)
argument_list|,
literal|0xbd3af235
argument_list|,
literal|10
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|b
argument_list|,
name|GET
argument_list|(
literal|2
argument_list|)
argument_list|,
literal|0x2ad7d2bb
argument_list|,
literal|15
argument_list|)
expr_stmt|;
name|STEP
argument_list|(
name|I
argument_list|,
name|b
argument_list|,
name|c
argument_list|,
name|d
argument_list|,
name|a
argument_list|,
name|GET
argument_list|(
literal|9
argument_list|)
argument_list|,
literal|0xeb86d391
argument_list|,
literal|21
argument_list|)
expr_stmt|;
name|a
operator|+=
name|saved_a
expr_stmt|;
name|b
operator|+=
name|saved_b
expr_stmt|;
name|c
operator|+=
name|saved_c
expr_stmt|;
name|d
operator|+=
name|saved_d
expr_stmt|;
name|p
operator|+=
literal|64
expr_stmt|;
block|}
do|while
condition|(
name|size
operator|-=
literal|64
condition|)
do|;
name|ctx
operator|->
name|a
operator|=
name|a
expr_stmt|;
name|ctx
operator|->
name|b
operator|=
name|b
expr_stmt|;
name|ctx
operator|->
name|c
operator|=
name|c
expr_stmt|;
name|ctx
operator|->
name|d
operator|=
name|d
expr_stmt|;
return|return
name|p
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

