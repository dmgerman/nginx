begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  * Copyright (C) Valentin V. Bartenev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_SPDY_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_SPDY_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_SPDY_MODULE_H_INCLUDED_
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
DECL|struct|__anon27b735b30108
typedef|typedef
struct|struct
block|{
DECL|member|recv_buffer_size
name|size_t
name|recv_buffer_size
decl_stmt|;
DECL|member|recv_buffer
name|u_char
modifier|*
name|recv_buffer
decl_stmt|;
DECL|typedef|ngx_http_spdy_main_conf_t
block|}
name|ngx_http_spdy_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27b735b30208
typedef|typedef
struct|struct
block|{
DECL|member|pool_size
name|size_t
name|pool_size
decl_stmt|;
DECL|member|concurrent_streams
name|ngx_uint_t
name|concurrent_streams
decl_stmt|;
DECL|member|streams_index_mask
name|ngx_uint_t
name|streams_index_mask
decl_stmt|;
DECL|member|recv_timeout
name|ngx_msec_t
name|recv_timeout
decl_stmt|;
DECL|member|keepalive_timeout
name|ngx_msec_t
name|keepalive_timeout
decl_stmt|;
DECL|member|headers_comp
name|ngx_int_t
name|headers_comp
decl_stmt|;
DECL|typedef|ngx_http_spdy_srv_conf_t
block|}
name|ngx_http_spdy_srv_conf_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_spdy_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_SPDY_MODULE_H_INCLUDED_ */
end_comment

end_unit

