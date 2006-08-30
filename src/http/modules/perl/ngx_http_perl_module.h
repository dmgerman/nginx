begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_PERL_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_PERL_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_PERL_MODULE_H_INCLUDED_
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
file|<ngx_http.h>
end_include

begin_include
include|#
directive|include
file|<EXTERN.h>
end_include

begin_include
include|#
directive|include
file|<perl.h>
end_include

begin_typedef
DECL|typedef|nginx
typedef|typedef
name|ngx_http_request_t
modifier|*
name|nginx
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c4b6a8e0108
typedef|typedef
struct|struct
block|{
DECL|member|perl
name|PerlInterpreter
modifier|*
name|perl
decl_stmt|;
DECL|member|filename
name|ngx_str_t
name|filename
decl_stmt|;
DECL|member|redirect_uri
name|ngx_str_t
name|redirect_uri
decl_stmt|;
DECL|member|redirect_args
name|ngx_str_t
name|redirect_args
decl_stmt|;
DECL|member|next
name|SV
modifier|*
name|next
decl_stmt|;
DECL|member|done
name|ngx_uint_t
name|done
decl_stmt|;
comment|/* unsigned  done:1; */
if|#
directive|if
operator|(
name|NGX_HTTP_SSI
operator|)
DECL|member|ssi
name|ngx_http_ssi_ctx_t
modifier|*
name|ssi
decl_stmt|;
endif|#
directive|endif
DECL|typedef|ngx_http_perl_ctx_t
block|}
name|ngx_http_perl_ctx_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_perl_module
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * workaround for "unused variable `Perl___notused'" warning  * when building with perl 5.6.1  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|PERL_IMPLICIT_CONTEXT
end_ifndef

begin_undef
undef|#
directive|undef
name|dTHXa
end_undef

begin_define
DECL|macro|dTHXa (a)
define|#
directive|define
name|dTHXa
parameter_list|(
name|a
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|extern
name|void
name|boot_DynaLoader
parameter_list|(
name|pTHX_
name|CV
modifier|*
name|cv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_perl_handle_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_PERL_MODULE_H_INCLUDED_ */
end_comment

end_unit

