begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_SCRIPT_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_SCRIPT_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_SCRIPT_H_INCLUDED_
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

begin_typedef
DECL|typedef|ngx_http_script_code_pt
typedef|typedef
name|u_char
modifier|*
function_decl|(
modifier|*
name|ngx_http_script_code_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|ngx_http_script_code_s
typedef|typedef
struct|struct
name|ngx_http_script_code_s
block|{
DECL|member|data_len
name|size_t
name|data_len
decl_stmt|;
DECL|member|code_len
name|size_t
name|code_len
decl_stmt|;
DECL|member|code
name|ngx_http_script_code_pt
name|code
decl_stmt|;
DECL|typedef|ngx_http_script_code_t
block|}
name|ngx_http_script_code_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_SCRIPT_H_INCLUDED_ */
end_comment

end_unit

