begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
DECL|struct|__anon2b3fe4890208
typedef|typedef
struct|struct
block|{ }
DECL|typedef|ngx_http_ssi_filter_ctx_t
name|ngx_http_ssi_filter_ctx_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|int
name|ngx_http_ssi_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_ssi_filter_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_ssi_filter_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|NULL
block|,
comment|/* create server configuration */
name|NULL
block|,
comment|/* merge server configuration */
name|NULL
block|,
comment|/* create location configuration */
name|NULL
block|,
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_ssi_filter_module
name|ngx_module_t
name|ngx_http_ssi_filter_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_ssi_filter_module_ctx
block|,
comment|/* module context */
name|NULL
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|ngx_http_ssi_filter_init
block|,
comment|/* init module */
name|NULL
comment|/* init child */
block|}
decl_stmt|;
end_decl_stmt

begin_function_decl
DECL|variable|next_header_filter
specifier|static
name|int
function_decl|(
modifier|*
name|next_header_filter
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
DECL|variable|next_body_filter
specifier|static
name|int
function_decl|(
modifier|*
name|next_body_filter
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

begin_function
DECL|function|ngx_http_ssi_body_filter (ngx_http_request_t * r,ngx_chain_t * in)
specifier|static
name|int
name|ngx_http_ssi_body_filter
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|)
block|{
block|}
end_function

begin_function
DECL|function|ngx_http_ssi_parse ()
specifier|static
name|void
name|ngx_http_ssi_parse
parameter_list|()
block|{
for|for
control|(
control|)
block|{
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|ssi_start_state
case|:
comment|/* tight loop */
while|while
condition|(
name|p
operator|<
name|h
operator|->
name|last
condition|)
block|{
if|if
condition|(
operator|*
name|p
operator|++
operator|==
literal|'<'
condition|)
block|{
name|state
operator|=
name|ssi_comment_state
expr_stmt|;
name|length
operator|=
literal|1
expr_stmt|;
break|break;
block|}
block|}
comment|/* fall through */
case|case
name|ssi_comment_state
case|:
break|break;
block|}
block|}
specifier|static
name|int
name|ngx_http_ssi_filter_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|next_header_filter
operator|=
name|ngx_http_top_header_filter
expr_stmt|;
name|ngx_http_top_header_filter
operator|=
name|ngx_http_ssi_header_filter
expr_stmt|;
name|next_body_filter
operator|=
name|ngx_http_top_body_filter
expr_stmt|;
name|ngx_http_top_body_filter
operator|=
name|ngx_http_ssi_body_filter
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

