begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev  */
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

begin_typedef
DECL|struct|__anon28c219d40108
typedef|typedef
struct|struct
block|{
name|handler
expr_stmt|;
name|offset
operator|/
name|data
expr_stmt|;
name|size
expr_stmt|;
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

