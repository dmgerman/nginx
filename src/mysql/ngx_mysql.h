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

begin_typedef
DECL|struct|__anon2c77a5a50108
typedef|typedef
struct|struct
block|{
DECL|member|peer
name|ngx_peer_connection_t
name|peer
decl_stmt|;
DECL|typedef|ngx_mysql_t
block|}
name|ngx_mysql_t
typedef|;
end_typedef

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

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_MYSQL_H_INCLUDED_ */
end_comment

end_unit

