begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_UNIX_DOMAIN_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_UNIX_DOMAIN_H_INCLUDED_
define|#
directive|define
name|_NGX_UNIX_DOMAIN_H_INCLUDED_
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
DECL|struct|__anon296ba6880108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
comment|/* "schema:unix:path:/uri" */
DECL|member|url
name|ngx_str_t
name|url
decl_stmt|;
comment|/* "unix:path:/uri" */
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|uri_part
name|ngx_uint_t
name|uri_part
decl_stmt|;
comment|/* unsigned  uri_part:1; */
DECL|typedef|ngx_unix_domain_upstream_t
block|}
name|ngx_unix_domain_upstream_t
typedef|;
end_typedef

begin_function_decl
name|ngx_peers_t
modifier|*
name|ngx_unix_upstream_parse
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_unix_domain_upstream_t
modifier|*
name|u
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_UNIX_DOMAIN_H_INCLUDED_ */
end_comment

end_unit

