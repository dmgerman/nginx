begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_decl_stmt
DECL|variable|ngx_http_static_module
name|ngx_http_module_t
name|ngx_http_static_module
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
comment|/* STUB */
end_comment

begin_comment
unit|static ngx_http_static_ctx_t module_ctx;  void ngx_http_static_init() {      module_ctx.out = NULL;       ngx_http_static_module.ctx =&module_ctx; }
comment|/* */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_http_static_handler (ngx_http_request_t * r)
name|int
name|ngx_http_static_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
modifier|*
name|ch
decl_stmt|;
comment|/*     ngx_http_event_static_handler_loc_conf_t  *cf;      cf = (ngx_http_event_static_handler_loc_conf_t *)              ngx_get_module_loc_conf(r,&ngx_http_event_static_handler_module);  */
name|r
operator|->
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|r
operator|->
name|filename
argument_list|,
name|NGX_FILE_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|fd
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"ngx_http_static_handler: "
name|ngx_open_file_n
literal|" %s failed"
argument_list|,
name|r
operator|->
name|filename
argument_list|)
expr_stmt|;
comment|/* STUB */
return|return
operator|-
literal|1
return|;
block|}
if|if
condition|(
name|ngx_stat_fd
argument_list|(
name|r
operator|->
name|fd
argument_list|,
operator|&
name|r
operator|->
name|file_info
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"ngx_http_static_handler: "
name|ngx_stat_fd_n
literal|" %s failed"
argument_list|,
name|r
operator|->
name|filename
argument_list|)
expr_stmt|;
comment|/* STUB */
return|return
operator|-
literal|1
return|;
block|}
name|r
operator|->
name|headers_out
operator|->
name|status
operator|=
name|NGX_HTTP_OK
expr_stmt|;
name|r
operator|->
name|headers_out
operator|->
name|content_length
operator|=
name|ngx_file_size
argument_list|(
name|r
operator|->
name|file_info
argument_list|)
expr_stmt|;
comment|/*     r->headers_out->last_modified = ngx_file_mtime(r->file_info); */
comment|/* STUB */
name|r
operator|->
name|headers_out
operator|->
name|content_type
operator|=
literal|"text/html"
expr_stmt|;
comment|/* STUB */
name|rc
operator|=
name|ngx_http_header_filter
argument_list|(
name|r
argument_list|)
expr_stmt|;
comment|/*     rc = ngx_send_http_header(r->headers_out); */
if|if
condition|(
name|r
operator|->
name|header_only
condition|)
return|return
name|rc
return|;
comment|/* TODO: NGX_HTTP_INTERNAL_SERVER_ERROR is too late */
comment|/* STUB */
name|ngx_test_null
argument_list|(
name|h
argument_list|,
name|ngx_get_hunk
argument_list|(
name|r
operator|->
name|pool
argument_list|,
literal|1024
argument_list|,
literal|0
argument_list|,
literal|64
argument_list|)
argument_list|,
comment|/* STUB */
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*     ngx_test_null(h, ngx_create_hunk(r->pool), NGX_HTTP_INTERNAL_SERVER_ERROR); */
name|h
operator|->
name|type
operator|=
name|NGX_HUNK_FILE
operator||
name|NGX_HUNK_LAST
expr_stmt|;
name|h
operator|->
name|fd
operator|=
name|r
operator|->
name|fd
expr_stmt|;
name|h
operator|->
name|pos
operator|.
name|file
operator|=
literal|0
expr_stmt|;
name|h
operator|->
name|last
operator|.
name|file
operator|=
name|ngx_file_size
argument_list|(
name|r
operator|->
name|file_info
argument_list|)
expr_stmt|;
comment|/* STUB */
name|ngx_test_null
argument_list|(
name|ch
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_chain_t
argument_list|)
argument_list|)
argument_list|,
comment|/* STUB */
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/*                   NGX_HTTP_FILTER_ERROR); */
comment|/*     ngx_test_null(ch, ngx_create_chain(r->pool),                   NGX_HTTP_INTERNAL_SERVER_ERROR); */
name|ch
operator|->
name|hunk
operator|=
name|h
expr_stmt|;
name|ch
operator|->
name|next
operator|=
name|NULL
expr_stmt|;
comment|/* STUB */
name|rc
operator|=
name|ngx_http_write_filter
argument_list|(
name|r
argument_list|,
name|ch
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"write_filter: %d"
argument|_ rc
argument_list|)
empty_stmt|;
return|return
name|rc
return|;
comment|/*     return ngx_http_filter(r, ch); */
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static void *ngx_create_index_config() {     ngx_http_index_handler_loc_conf_t  *cf;      ngx_check_null(cf, ngx_alloc(p, sizeof(ngx_http_index_handler_loc_conf)),                    NULL);      cf->indices = ngx_create_array(p, sizeof(ngx_http_index_t), 5);     if (cf->indices == NULL)         return NULL;      cf->max_index_len = 0;      return cf; }  static void *ngx_merge_index_config() {     if (p->indices->nelts> 0) {          copy and check dups          if (c->max_index_len< c->max_index_len)             c->max_index_len< c->max_index_len);     } }  static void *ngx_set_index() {     if (*conf == NULL) {         cf = ngx_create_index_conf();         if (cf == NULL)             return "can not create config";     }      while (args) {        index = ngx_push_array(cf->indices);        index->name = arg;        index->len = ngx_strlen(arg) + 1;         if (cf->max_index_len< index->len)            cf->max_index_len = index->len;     }      *conf = cf; }
endif|#
directive|endif
end_endif

end_unit

