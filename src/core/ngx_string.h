begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
DECL|struct|__anon2b13c1360108
typedef|typedef
struct|struct
block|{
DECL|member|len
name|size_t
name|len
decl_stmt|;
DECL|member|data
name|char
modifier|*
name|data
decl_stmt|;
DECL|typedef|ngx_str_t
block|}
name|ngx_str_t
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
value|{ sizeof(str) - 1, str }
end_define

begin_define
DECL|macro|ngx_null_string
define|#
directive|define
name|ngx_null_string
value|{ 0, NULL }
end_define

begin_if
if|#
directive|if
operator|(
name|WIN32
operator|)
end_if

begin_define
DECL|macro|ngx_strncasecmp
define|#
directive|define
name|ngx_strncasecmp
value|strnicmp
end_define

begin_define
DECL|macro|ngx_strcasecmp
define|#
directive|define
name|ngx_strcasecmp
value|stricmp
end_define

begin_define
DECL|macro|ngx_snprintf
define|#
directive|define
name|ngx_snprintf
value|_snprintf
end_define

begin_define
DECL|macro|ngx_vsnprintf
define|#
directive|define
name|ngx_vsnprintf
value|_vsnprintf
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_strncasecmp
define|#
directive|define
name|ngx_strncasecmp
value|strncasecmp
end_define

begin_define
DECL|macro|ngx_strcasecmp
define|#
directive|define
name|ngx_strcasecmp
value|strcasecmp
end_define

begin_define
DECL|macro|ngx_snprintf
define|#
directive|define
name|ngx_snprintf
value|snprintf
end_define

begin_define
DECL|macro|ngx_vsnprintf
define|#
directive|define
name|ngx_vsnprintf
value|vsnprintf
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_strncmp
define|#
directive|define
name|ngx_strncmp
value|strncmp
end_define

begin_comment
comment|/* msvc and icc compile strcmp() to inline loop */
end_comment

begin_define
DECL|macro|ngx_strcmp
define|#
directive|define
name|ngx_strcmp
value|strcmp
end_define

begin_define
DECL|macro|ngx_strstr
define|#
directive|define
name|ngx_strstr
value|strstr
end_define

begin_define
DECL|macro|ngx_strlen
define|#
directive|define
name|ngx_strlen
value|strlen
end_define

begin_comment
comment|/*  * msvc and icc compile memset() to inline "rep stos"  * while ZeroMemory and bzero are calls.  *  * icc can also inline mov's of a zeroed register for small blocks.  */
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
value|memset(buf, 0, n)
end_define

begin_comment
comment|/* msvc and icc compile memcpy() to inline "rep movs" */
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
value|memcpy(dst, src, n)
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
value|((char *) memcpy(dst, src, n)) + n
end_define

begin_comment
comment|/* msvc and icc compile memcmp() to inline loop */
end_comment

begin_define
DECL|macro|ngx_memcmp
define|#
directive|define
name|ngx_memcmp
value|memcmp
end_define

begin_function_decl
name|char
modifier|*
name|ngx_cpystrn
parameter_list|(
name|char
modifier|*
name|dst
parameter_list|,
name|char
modifier|*
name|src
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_rstrncmp
parameter_list|(
name|char
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
name|int
name|ngx_atoi
parameter_list|(
name|char
modifier|*
name|line
parameter_list|,
name|size_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_md5_text
parameter_list|(
name|char
modifier|*
name|text
parameter_list|,
name|u_char
modifier|*
name|md5
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

