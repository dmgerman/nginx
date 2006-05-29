begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_MYSQL_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_MYSQL_H_INCLUDED_
define|#
directive|define
name|_NGX_MYSQL_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_connect.h>
end_include

begin_typedef
DECL|typedef|ngx_mysql_t
typedef|typedef
name|struct
name|ngx_mysql_s
name|ngx_mysql_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_mysql_handler_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_mysql_handler_pt
function_decl|)
parameter_list|(
name|ngx_mysql_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_mysql_s
struct|struct
name|ngx_mysql_s
block|{
DECL|member|peer
name|ngx_peer_connection_t
name|peer
decl_stmt|;
DECL|member|buf
name|ngx_buf_t
modifier|*
name|buf
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|login
name|ngx_str_t
modifier|*
name|login
decl_stmt|;
DECL|member|passwd
name|ngx_str_t
modifier|*
name|passwd
decl_stmt|;
DECL|member|database
name|ngx_str_t
modifier|*
name|database
decl_stmt|;
DECL|member|query
name|ngx_str_t
name|query
decl_stmt|;
DECL|member|pktn
name|ngx_uint_t
name|pktn
decl_stmt|;
DECL|member|handler
name|ngx_mysql_handler_pt
name|handler
decl_stmt|;
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|state
name|ngx_int_t
name|state
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|NGX_MYSQL_CMDPKT_LEN
define|#
directive|define
name|NGX_MYSQL_CMDPKT_LEN
value|5
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_LITTLE_ENDIAN
operator|&&
name|NGX_HAVE_NONALIGNED
operator|&&
literal|0
operator|)
end_if

begin_define
DECL|macro|ngx_m16toh (n)
define|#
directive|define
name|ngx_m16toh
parameter_list|(
name|n
parameter_list|)
value|(*(uint32_t *) n& 0x0000ffff)
end_define

begin_define
DECL|macro|ngx_m24toh (n)
define|#
directive|define
name|ngx_m24toh
parameter_list|(
name|n
parameter_list|)
value|(*(uint32_t *) n& 0x00ffffff)
end_define

begin_define
DECL|macro|ngx_m32toh (n)
define|#
directive|define
name|ngx_m32toh
parameter_list|(
name|n
parameter_list|)
value|*(uint32_t *) n
end_define

begin_define
DECL|macro|ngx_htom16 (n,m)
define|#
directive|define
name|ngx_htom16
parameter_list|(
name|n
parameter_list|,
name|m
parameter_list|)
value|*(uint16_t *) n = (uint16_t) ((m)& 0xffff)
end_define

begin_define
DECL|macro|ngx_htom24 (n,m)
define|#
directive|define
name|ngx_htom24
parameter_list|(
name|n
parameter_list|,
name|m
parameter_list|)
value|(n)[0] = (u_char) ((m)& 0xff);                   \                            (n)[1] = (u_char) (((m)>> 8)& 0xff);            \                            (n)[2] = (u_char) (((m)>> 16)& 0xff)
end_define

begin_define
DECL|macro|ngx_htom32 (n,m)
define|#
directive|define
name|ngx_htom32
parameter_list|(
name|n
parameter_list|,
name|m
parameter_list|)
value|*(uint32_t *) (n) = (m)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_m16toh (n)
define|#
directive|define
name|ngx_m16toh
parameter_list|(
name|n
parameter_list|)
value|(n[0] | n[1]<< 8)
end_define

begin_define
DECL|macro|ngx_m24toh (n)
define|#
directive|define
name|ngx_m24toh
parameter_list|(
name|n
parameter_list|)
value|(n[0] | n[1]<< 8 | n[2]<< 16)
end_define

begin_define
DECL|macro|ngx_m32toh (n)
define|#
directive|define
name|ngx_m32toh
parameter_list|(
name|n
parameter_list|)
value|(n[0] | n[1]<< 8 | n[2]<< 16 | n[3]<< 24)
end_define

begin_define
DECL|macro|ngx_htom16 (n,m)
define|#
directive|define
name|ngx_htom16
parameter_list|(
name|n
parameter_list|,
name|m
parameter_list|)
value|(n)[0] = (u_char) (m); (n)[1] = (u_char) ((m)>> 8)
end_define

begin_define
DECL|macro|ngx_htom24 (n,m)
define|#
directive|define
name|ngx_htom24
parameter_list|(
name|n
parameter_list|,
name|m
parameter_list|)
value|(n)[0] = (u_char) ((m)& 0xff);                   \                            (n)[1] = (u_char) (((m)>> 8)& 0xff);            \                            (n)[2] = (u_char) (((m)>> 16)& 0xff)
end_define

begin_define
DECL|macro|ngx_htom32 (n,m)
define|#
directive|define
name|ngx_htom32
parameter_list|(
name|n
parameter_list|,
name|m
parameter_list|)
value|(n)[0] = (u_char) ((m)& 0xff);                   \                            (n)[1] = (u_char) (((m)>> 8)& 0xff);            \                            (n)[2] = (u_char) (((m)>> 16)& 0xff);           \                            (n)[3] = (u_char) (((m)>> 24)& 0xff)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|ngx_int_t
name|ngx_mysql_connect
parameter_list|(
name|ngx_mysql_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_mysql_query
parameter_list|(
name|ngx_mysql_t
modifier|*
name|m
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_MYSQL_H_INCLUDED_ */
end_comment

end_unit

