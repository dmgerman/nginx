begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_FILTER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_FILTER_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_FILTER_H_INCLUDED_
end_define

begin_define
DECL|macro|NGX_HTTP_FILTER_NEED_IN_MEMORY
define|#
directive|define
name|NGX_HTTP_FILTER_NEED_IN_MEMORY
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_FILTER_SSI_NEED_IN_MEMORY
define|#
directive|define
name|NGX_HTTP_FILTER_SSI_NEED_IN_MEMORY
value|2
end_define

begin_define
DECL|macro|NGX_HTTP_FILTER_NEED_TEMP
define|#
directive|define
name|NGX_HTTP_FILTER_NEED_TEMP
value|4
end_define

begin_function_decl
name|int
name|ngx_http_output_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_hunk_t
modifier|*
name|hunk
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_write_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
function_decl|(
modifier|*
name|ngx_http_top_header_filter
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
function_decl|(
modifier|*
name|ngx_http_top_body_filter
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|ch
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_FILTER_H_INCLUDED_ */
end_comment

end_unit

