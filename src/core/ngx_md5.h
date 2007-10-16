begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_MD5_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_MD5_H_INCLUDED_
define|#
directive|define
name|_NGX_MD5_H_INCLUDED_
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_OPENSSL_MD5_H
operator|)
end_if

begin_include
include|#
directive|include
file|<openssl/md5.h>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|<md5.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_md5_t
typedef|typedef
name|MD5_CTX
name|ngx_md5_t
typedef|;
end_typedef

begin_if
if|#
directive|if
operator|(
name|NGX_OPENSSL_MD5
operator|)
end_if

begin_define
DECL|macro|ngx_md5_init
define|#
directive|define
name|ngx_md5_init
value|MD5_Init
end_define

begin_define
DECL|macro|ngx_md5_update
define|#
directive|define
name|ngx_md5_update
value|MD5_Update
end_define

begin_define
DECL|macro|ngx_md5_final
define|#
directive|define
name|ngx_md5_final
value|MD5_Final
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_md5_init
define|#
directive|define
name|ngx_md5_init
value|MD5Init
end_define

begin_define
DECL|macro|ngx_md5_update
define|#
directive|define
name|ngx_md5_update
value|MD5Update
end_define

begin_define
DECL|macro|ngx_md5_final
define|#
directive|define
name|ngx_md5_final
value|MD5Final
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
comment|/* _NGX_MD5_H_INCLUDED_ */
end_comment

end_unit

