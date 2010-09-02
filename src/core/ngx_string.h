begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_STRING_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_STRING_H_INCLUDED_
define|#
directive|define
name|_NGX_STRING_H_INCLUDED_
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

begin_typedef
DECL|struct|__anon28c306b30108
typedef|typedef
struct|struct
block|{
DECL|member|len
name|size_t
name|len
decl_stmt|;
DECL|member|data
name|u_char
modifier|*
name|data
decl_stmt|;
DECL|typedef|ngx_str_t
block|}
name|ngx_str_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c306b30208
typedef|typedef
struct|struct
block|{
DECL|member|key
name|ngx_str_t
name|key
decl_stmt|;
DECL|member|value
name|ngx_str_t
name|value
decl_stmt|;
DECL|typedef|ngx_keyval_t
block|}
name|ngx_keyval_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28c306b30308
typedef|typedef
struct|struct
block|{
DECL|member|len
name|unsigned
name|len
range|:
literal|28
decl_stmt|;
DECL|member|valid
name|unsigned
name|valid
range|:
literal|1
decl_stmt|;
DECL|member|no_cacheable
name|unsigned
name|no_cacheable
range|:
literal|1
decl_stmt|;
DECL|member|not_found
name|unsigned
name|not_found
range|:
literal|1
decl_stmt|;
DECL|member|escape
name|unsigned
name|escape
range|:
literal|1
decl_stmt|;
DECL|member|data
name|u_char
modifier|*
name|data
decl_stmt|;
DECL|typedef|ngx_variable_value_t
block|}
name|ngx_variable_value_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_string (str)
define|#
directive|define
name|ngx_string
parameter_list|(
name|str
parameter_list|)
value|{ sizeof(str) - 1, (u_char *) str }
end_define

begin_define
DECL|macro|ngx_null_string
define|#
directive|define
name|ngx_null_string
value|{ 0, NULL }
end_define

begin_define
DECL|macro|ngx_str_set (str,text)
define|#
directive|define
name|ngx_str_set
parameter_list|(
name|str
parameter_list|,
name|text
parameter_list|)
define|\
value|(str)->len = sizeof(text) - 1; (str)->data = (u_char *) text
end_define

begin_define
DECL|macro|ngx_str_null (str)
define|#
directive|define
name|ngx_str_null
parameter_list|(
name|str
parameter_list|)
value|(str)->len = 0; (str)->data = NULL
end_define

begin_define
DECL|macro|ngx_tolower (c)
define|#
directive|define
name|ngx_tolower
parameter_list|(
name|c
parameter_list|)
value|(u_char) ((c>= 'A'&& c<= 'Z') ? (c | 0x20) : c)
end_define

begin_define
DECL|macro|ngx_toupper (c)
define|#
directive|define
name|ngx_toupper
parameter_list|(
name|c
parameter_list|)
value|(u_char) ((c>= 'a'&& c<= 'z') ? (c& ~0x20) : c)
end_define

begin_function_decl
name|void
name|ngx_strlow
parameter_list|(
name|u_char
modifier|*
name|dst
parameter_list|,
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_strncmp (s1,s2,n)
define|#
directive|define
name|ngx_strncmp
parameter_list|(
name|s1
parameter_list|,
name|s2
parameter_list|,
name|n
parameter_list|)
value|strncmp((const char *) s1, (const char *) s2, n)
end_define

begin_comment
comment|/* msvc and icc7 compile strcmp() to inline loop */
end_comment

begin_define
DECL|macro|ngx_strcmp (s1,s2)
define|#
directive|define
name|ngx_strcmp
parameter_list|(
name|s1
parameter_list|,
name|s2
parameter_list|)
value|strcmp((const char *) s1, (const char *) s2)
end_define

begin_define
DECL|macro|ngx_strstr (s1,s2)
define|#
directive|define
name|ngx_strstr
parameter_list|(
name|s1
parameter_list|,
name|s2
parameter_list|)
value|strstr((const char *) s1, (const char *) s2)
end_define

begin_define
DECL|macro|ngx_strlen (s)
define|#
directive|define
name|ngx_strlen
parameter_list|(
name|s
parameter_list|)
value|strlen((const char *) s)
end_define

begin_define
DECL|macro|ngx_strchr (s1,c)
define|#
directive|define
name|ngx_strchr
parameter_list|(
name|s1
parameter_list|,
name|c
parameter_list|)
value|strchr((const char *) s1, (int) c)
end_define

begin_function
specifier|static
name|ngx_inline
name|u_char
modifier|*
DECL|function|ngx_strlchr (u_char * p,u_char * last,u_char c)
name|ngx_strlchr
parameter_list|(
name|u_char
modifier|*
name|p
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|,
name|u_char
name|c
parameter_list|)
block|{
while|while
condition|(
name|p
operator|<
name|last
condition|)
block|{
if|if
condition|(
operator|*
name|p
operator|==
name|c
condition|)
block|{
return|return
name|p
return|;
block|}
name|p
operator|++
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  * msvc and icc7 compile memset() to the inline "rep stos"  * while ZeroMemory() and bzero() are the calls.  * icc7 may also inline several mov's of a zeroed register for small blocks.  */
end_comment

begin_define
DECL|macro|ngx_memzero (buf,n)
define|#
directive|define
name|ngx_memzero
parameter_list|(
name|buf
parameter_list|,
name|n
parameter_list|)
value|(void) memset(buf, 0, n)
end_define

begin_define
DECL|macro|ngx_memset (buf,c,n)
define|#
directive|define
name|ngx_memset
parameter_list|(
name|buf
parameter_list|,
name|c
parameter_list|,
name|n
parameter_list|)
value|(void) memset(buf, c, n)
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_MEMCPY_LIMIT
operator|)
end_if

begin_function_decl
name|void
modifier|*
name|ngx_memcpy
parameter_list|(
name|void
modifier|*
name|dst
parameter_list|,
name|void
modifier|*
name|src
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_cpymem (dst,src,n)
define|#
directive|define
name|ngx_cpymem
parameter_list|(
name|dst
parameter_list|,
name|src
parameter_list|,
name|n
parameter_list|)
value|(((u_char *) ngx_memcpy(dst, src, n)) + (n))
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/*  * gcc3, msvc, and icc7 compile memcpy() to the inline "rep movs".  * gcc3 compiles memcpy(d, s, 4) to the inline "mov"es.  * icc8 compile memcpy(d, s, 4) to the inline "mov"es or XMM moves.  */
end_comment

begin_define
DECL|macro|ngx_memcpy (dst,src,n)
define|#
directive|define
name|ngx_memcpy
parameter_list|(
name|dst
parameter_list|,
name|src
parameter_list|,
name|n
parameter_list|)
value|(void) memcpy(dst, src, n)
end_define

begin_define
DECL|macro|ngx_cpymem (dst,src,n)
define|#
directive|define
name|ngx_cpymem
parameter_list|(
name|dst
parameter_list|,
name|src
parameter_list|,
name|n
parameter_list|)
value|(((u_char *) memcpy(dst, src, n)) + (n))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|__INTEL_COMPILER
operator|>=
literal|800
operator|)
end_if

begin_comment
comment|/*  * the simple inline cycle copies the variable length strings up to 16  * bytes faster than icc8 autodetecting _intel_fast_memcpy()  */
end_comment

begin_function
specifier|static
name|ngx_inline
name|u_char
modifier|*
DECL|function|ngx_copy (u_char * dst,u_char * src,size_t len)
name|ngx_copy
parameter_list|(
name|u_char
modifier|*
name|dst
parameter_list|,
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
if|if
condition|(
name|len
operator|<
literal|17
condition|)
block|{
while|while
condition|(
name|len
condition|)
block|{
operator|*
name|dst
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
name|len
operator|--
expr_stmt|;
block|}
return|return
name|dst
return|;
block|}
else|else
block|{
return|return
name|ngx_cpymem
argument_list|(
name|dst
argument_list|,
name|src
argument_list|,
name|len
argument_list|)
return|;
block|}
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_copy
define|#
directive|define
name|ngx_copy
value|ngx_cpymem
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* msvc and icc7 compile memcmp() to the inline loop */
end_comment

begin_define
DECL|macro|ngx_memcmp (s1,s2,n)
define|#
directive|define
name|ngx_memcmp
parameter_list|(
name|s1
parameter_list|,
name|s2
parameter_list|,
name|n
parameter_list|)
value|memcmp((const char *) s1, (const char *) s2, n)
end_define

begin_function_decl
name|u_char
modifier|*
name|ngx_cpystrn
parameter_list|(
name|u_char
modifier|*
name|dst
parameter_list|,
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_pstrdup
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_str_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_cdecl
name|ngx_sprintf
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_cdecl
name|ngx_snprintf
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|max
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_cdecl
name|ngx_slprintf
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_vslprintf
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_vsnprintf (buf,max,fmt,args)
define|#
directive|define
name|ngx_vsnprintf
parameter_list|(
name|buf
parameter_list|,
name|max
parameter_list|,
name|fmt
parameter_list|,
name|args
parameter_list|)
define|\
value|ngx_vslprintf(buf, buf + (max), fmt, args)
end_define

begin_function_decl
name|ngx_int_t
name|ngx_strcasecmp
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|u_char
modifier|*
name|s2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_strncasecmp
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|u_char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_strnstr
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_strstrn
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_strcasestrn
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_strlcasestrn
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|,
name|u_char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_rstrncmp
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|u_char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_rstrncasecmp
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|u_char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_memn2cmp
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|u_char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n1
parameter_list|,
name|size_t
name|n2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_dns_strcmp
parameter_list|(
name|u_char
modifier|*
name|s1
parameter_list|,
name|u_char
modifier|*
name|s2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_atoi
parameter_list|(
name|u_char
modifier|*
name|line
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_atofp
parameter_list|(
name|u_char
modifier|*
name|line
parameter_list|,
name|size_t
name|n
parameter_list|,
name|size_t
name|point
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ssize_t
name|ngx_atosz
parameter_list|(
name|u_char
modifier|*
name|line
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|off_t
name|ngx_atoof
parameter_list|(
name|u_char
modifier|*
name|line
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|time_t
name|ngx_atotm
parameter_list|(
name|u_char
modifier|*
name|line
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_hextoi
parameter_list|(
name|u_char
modifier|*
name|line
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_hex_dump
parameter_list|(
name|u_char
modifier|*
name|dst
parameter_list|,
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_base64_encoded_length (len)
define|#
directive|define
name|ngx_base64_encoded_length
parameter_list|(
name|len
parameter_list|)
value|(((len + 2) / 3) * 4)
end_define

begin_define
DECL|macro|ngx_base64_decoded_length (len)
define|#
directive|define
name|ngx_base64_decoded_length
parameter_list|(
name|len
parameter_list|)
value|(((len + 3) / 4) * 3)
end_define

begin_function_decl
name|void
name|ngx_encode_base64
parameter_list|(
name|ngx_str_t
modifier|*
name|dst
parameter_list|,
name|ngx_str_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_decode_base64
parameter_list|(
name|ngx_str_t
modifier|*
name|dst
parameter_list|,
name|ngx_str_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_decode_base64url
parameter_list|(
name|ngx_str_t
modifier|*
name|dst
parameter_list|,
name|ngx_str_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|uint32_t
name|ngx_utf8_decode
parameter_list|(
name|u_char
modifier|*
modifier|*
name|p
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_utf8_length
parameter_list|(
name|u_char
modifier|*
name|p
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_utf8_cpystrn
parameter_list|(
name|u_char
modifier|*
name|dst
parameter_list|,
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|n
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|NGX_ESCAPE_URI
define|#
directive|define
name|NGX_ESCAPE_URI
value|0
end_define

begin_define
DECL|macro|NGX_ESCAPE_ARGS
define|#
directive|define
name|NGX_ESCAPE_ARGS
value|1
end_define

begin_define
DECL|macro|NGX_ESCAPE_HTML
define|#
directive|define
name|NGX_ESCAPE_HTML
value|2
end_define

begin_define
DECL|macro|NGX_ESCAPE_REFRESH
define|#
directive|define
name|NGX_ESCAPE_REFRESH
value|3
end_define

begin_define
DECL|macro|NGX_ESCAPE_MEMCACHED
define|#
directive|define
name|NGX_ESCAPE_MEMCACHED
value|4
end_define

begin_define
DECL|macro|NGX_ESCAPE_MAIL_AUTH
define|#
directive|define
name|NGX_ESCAPE_MAIL_AUTH
value|5
end_define

begin_define
DECL|macro|NGX_UNESCAPE_URI
define|#
directive|define
name|NGX_UNESCAPE_URI
value|1
end_define

begin_define
DECL|macro|NGX_UNESCAPE_REDIRECT
define|#
directive|define
name|NGX_UNESCAPE_REDIRECT
value|2
end_define

begin_function_decl
name|uintptr_t
name|ngx_escape_uri
parameter_list|(
name|u_char
modifier|*
name|dst
parameter_list|,
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|size
parameter_list|,
name|ngx_uint_t
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_unescape_uri
parameter_list|(
name|u_char
modifier|*
modifier|*
name|dst
parameter_list|,
name|u_char
modifier|*
modifier|*
name|src
parameter_list|,
name|size_t
name|size
parameter_list|,
name|ngx_uint_t
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|uintptr_t
name|ngx_escape_html
parameter_list|(
name|u_char
modifier|*
name|dst
parameter_list|,
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_typedef
DECL|struct|__anon28c306b30408
typedef|typedef
struct|struct
block|{
DECL|member|node
name|ngx_rbtree_node_t
name|node
decl_stmt|;
DECL|member|str
name|ngx_str_t
name|str
decl_stmt|;
DECL|typedef|ngx_str_node_t
block|}
name|ngx_str_node_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_str_rbtree_insert_value
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
name|temp
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_str_node_t
modifier|*
name|ngx_str_rbtree_lookup
parameter_list|(
name|ngx_rbtree_t
modifier|*
name|rbtree
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|uint32_t
name|hash
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_sort
parameter_list|(
name|void
modifier|*
name|base
parameter_list|,
name|size_t
name|n
parameter_list|,
name|size_t
name|size
parameter_list|,
name|ngx_int_t
function_decl|(
modifier|*
name|cmp
function_decl|)
parameter_list|(
specifier|const
name|void
modifier|*
parameter_list|,
specifier|const
name|void
modifier|*
parameter_list|)
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_qsort
define|#
directive|define
name|ngx_qsort
value|qsort
end_define

begin_define
DECL|macro|ngx_value_helper (n)
define|#
directive|define
name|ngx_value_helper
parameter_list|(
name|n
parameter_list|)
value|#n
end_define

begin_define
DECL|macro|ngx_value (n)
define|#
directive|define
name|ngx_value
parameter_list|(
name|n
parameter_list|)
value|ngx_value_helper(n)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_STRING_H_INCLUDED_ */
end_comment

end_unit

