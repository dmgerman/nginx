begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_WRITE_FILTER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_WRITE_FILTER_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_WRITE_FILTER_H_INCLUDED_
end_define

begin_typedef
DECL|struct|__anon2790daec0108
typedef|typedef
struct|struct
block|{
DECL|member|out
name|ngx_chain_t
modifier|*
name|out
decl_stmt|;
DECL|member|buffer_output
name|size_t
name|buffer_output
decl_stmt|;
DECL|typedef|ngx_http_write_filter_ctx_t
block|}
name|ngx_http_write_filter_ctx_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_WRITE_FILTER_H_INCLUDED_ */
end_comment

end_unit

