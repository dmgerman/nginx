begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_decl_stmt
specifier|extern
name|ngx_http_module_t
name|ngx_http_output_filter_module
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
name|ngx_http_output_filter_module
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

end_unit

