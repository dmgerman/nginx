begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_decl_stmt
specifier|extern
name|ngx_http_module_t
name|ngx_http_write_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_http_module_t
name|ngx_http_output_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_http_module_t
name|ngx_http_core_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_http_module_t
name|ngx_http_index_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_modules
name|ngx_http_module_t
modifier|*
name|ngx_http_modules
index|[]
init|=
block|{
operator|&
name|ngx_http_write_filter_module
block|,
operator|&
name|ngx_http_output_filter_module
block|,
operator|&
name|ngx_http_index_module
block|,
operator|&
name|ngx_http_core_module
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

end_unit

