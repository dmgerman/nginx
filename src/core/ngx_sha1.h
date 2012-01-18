begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SHA1_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SHA1_H_INCLUDED_
define|#
directive|define
name|_NGX_SHA1_H_INCLUDED_
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
name|NGX_HAVE_OPENSSL_SHA1_H
operator|)
end_if

begin_include
include|#
directive|include
file|<openssl/sha.h>
end_include

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|<sha.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|ngx_sha1_t
typedef|typedef
name|SHA_CTX
name|ngx_sha1_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_sha1_init
define|#
directive|define
name|ngx_sha1_init
value|SHA1_Init
end_define

begin_define
DECL|macro|ngx_sha1_update
define|#
directive|define
name|ngx_sha1_update
value|SHA1_Update
end_define

begin_define
DECL|macro|ngx_sha1_final
define|#
directive|define
name|ngx_sha1_final
value|SHA1_Final
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SHA1_H_INCLUDED_ */
end_comment

end_unit

