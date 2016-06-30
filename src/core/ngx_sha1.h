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

begin_typedef
DECL|struct|__anon2888aeba0108
typedef|typedef
struct|struct
block|{
DECL|member|bytes
name|uint64_t
name|bytes
decl_stmt|;
DECL|member|a
DECL|member|b
DECL|member|c
DECL|member|d
DECL|member|e
DECL|member|f
name|uint32_t
name|a
decl_stmt|,
name|b
decl_stmt|,
name|c
decl_stmt|,
name|d
decl_stmt|,
name|e
decl_stmt|,
name|f
decl_stmt|;
DECL|member|buffer
name|u_char
name|buffer
index|[
literal|64
index|]
decl_stmt|;
DECL|typedef|ngx_sha1_t
block|}
name|ngx_sha1_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_sha1_init
parameter_list|(
name|ngx_sha1_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_sha1_update
parameter_list|(
name|ngx_sha1_t
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_sha1_final
parameter_list|(
name|u_char
name|result
index|[
literal|20
index|]
parameter_list|,
name|ngx_sha1_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SHA1_H_INCLUDED_ */
end_comment

end_unit

