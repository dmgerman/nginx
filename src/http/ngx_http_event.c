begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_comment
comment|/* ngx_read should check errors (if we ask) and return    -2 EAGAIN    -1 error     0 EOF>0 number of bytes */
end_comment

begin_function_decl
name|int
name|ngx_http_init_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_http_init_request
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_http_process_request
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_process_http_request_line
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_process_http_request_header
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_process_http_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_http_close_request
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*     returns     -1 if error      0 need more data or EOF (filter is deleted)      1 there is unread data */
end_comment

begin_function
DECL|function|ngx_http_init_connection (ngx_connection_t * c)
name|int
name|ngx_http_init_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
block|{
name|ngx_event_t
modifier|*
name|ev
decl_stmt|;
name|ev
operator|=
name|c
operator|->
name|read
expr_stmt|;
comment|/*     ev->event_handler = ngx_http_init_request; */
name|ev
operator|->
name|event_handler
operator|=
name|NULL
expr_stmt|;
name|ev
operator|->
name|log
operator|->
name|action
operator|=
literal|"reading client request line"
expr_stmt|;
name|ngx_log_debug
argument_list|(
name|ev
operator|->
name|log
argument_list|,
literal|"ngx_http_init_connection: entered"
argument_list|)
expr_stmt|;
comment|/* XXX: ev->timer ? */
if|if
condition|(
name|ngx_add_event
argument_list|(
name|ev
argument_list|,
name|NGX_TIMER_EVENT
argument_list|,
name|ev
operator|->
name|timer
argument_list|)
operator|==
operator|-
literal|1
condition|)
return|return
operator|-
literal|1
return|;
if|#
directive|if
operator|(
name|HAVE_DEFERRED_ACCEPT
operator|)
if|if
condition|(
name|ev
operator|->
name|ready
condition|)
return|return
name|ngx_http_init_request
argument_list|(
name|ev
argument_list|)
return|;
else|else
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_CLEAR_EVENT
operator|)
return|return
name|ngx_add_event
argument_list|(
name|ev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_CLEAR_EVENT
argument_list|)
return|;
else|#
directive|else
return|return
name|ngx_add_event
argument_list|(
name|ev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_ONESHOT_EVENT
argument_list|)
return|;
endif|#
directive|endif
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|int ngx_http_init_request(ngx_event_t *ev) {     ngx_connection_t   *c = (ngx_connection_t *) ev->data;     ngx_http_request_t *r;      ngx_log_debug(ev->log, "ngx_http_init_request: entered");      ngx_test_null(r, ngx_pcalloc(c->pool, sizeof(ngx_http_request_t)), -1);      c->data = r;     r->connection = c;      ngx_test_null(r->buff, ngx_palloc(r->pool, sizeof(ngx_buff_t)), -1);     ngx_test_null(r->buff->buff,                   ngx_pcalloc(r->pool, sizeof(c->server->buff_size)), -1);      r->buff->pos = r->buff->last = r->buff->buff;     r->buff->end = r->buff->buff + c->server->buff_size;      r->state_handler = ngx_process_http_request_line;      ev->event_handler = ngx_http_process_request;     ev->close_handler = ngx_http_close_request;     c->write->close_handler = ngx_http_close_request;     return ngx_http_process_request(ev); }  int ngx_http_process_request(ngx_event_t *ev) {     int n;     ngx_connection_t *c = (ngx_connection_t *) ev->data;     ngx_http_request_t *r = (ngx_http_request_t *) c->data;      ngx_log_debug(ev->log, "http process request");      ngx_log_debug(ev->log, "http: eof:%d, avail:%d", ev->eof, ev->available);      if (ev->eof&& ev->available == 0) {         if (ev->err_no)             ngx_log_error(NGX_LOG_ERR, ev->log, ev->err_no,                          "ngx_http_process_request: "                          "read failed while %s", ev->action);          return -1;     }      if ((n = read(c->fd, r->buff->last, r->buff->end - r->buff->last)) == -1) {          if (errno == NGX_EWOULDBLOCK) {             ngx_log_error(NGX_LOG_INFO, ev->log, errno,                          "ngx_http_process_request: "                          "EAGAIN while %s", ev->action);             return 0;         }          ngx_log_error(NGX_LOG_ERR, ev->log, errno,                      "ngx_http_process_request: "                      "read failed while %s", ev->action);         return -1;     }      ngx_log_debug(ev->log, "http read %d", n);      if (n == 0) {         if (ev->unexpected_eof) {             ngx_log_error(NGX_LOG_INFO, ev->log, 0,                          "ngx_http_process_request: "                          "connection is closed while %s", ev->action);             return -1;         }          return ngx_http_close_request(ev);     }      n == r->buff->end - r->buff->last;      if (!ev->read_discarded) {         r->buff->last += n;
comment|/* state_handlers are called in following order:             ngx_process_http_request_line()             ngx_process_http_request_header() */
end_comment

begin_comment
unit|do {             if ((r->state_handler)(r)< 0)                 return -1;         } while (r->buff->pos< r->buff->last);     }      if (ngx_del_event(ev, NGX_TIMER_EVENT) == -1)         return -1;      if (ngx_add_event(ev, NGX_TIMER_EVENT, ev->timer) == -1)         return -1;      return 0; }  static int ngx_process_http_request_line(ngx_http_request_t *r) {     int n;      if ((n = ngx_read_http_request_line(r)) == 1) {         *r->uri_end = '\0';         ngx_log_debug(r->connection->log, "HTTP: %d, %d, %s",                      r->method, r->http_version, r->uri_start);         r->state_handler = ngx_process_http_request_header;         r->connection->read->action = "reading client request headers";     }      return n; }  static int ngx_process_http_request_header(ngx_http_request_t *r) {     int n;      while ((n = ngx_read_http_header_line(r)) == 1) {         *r->header_name_end = '\0';         *r->header_end = '\0';         ngx_log_debug(r->connection->log, "HTTP header: '%s: %s'",                      r->header_name_start, r->header_start);     }      if (n != 2)         return n;      r->state_handler = NULL;     r->connection->read->action = "reading client request body";      r->connection->read->read_discarded = 1;     r->connection->read->unexpected_eof = 0;     ngx_log_debug(r->connection->log, "HTTP header done");      return ngx_process_http_request(r); }  static int ngx_process_http_request(ngx_http_request_t *r) {     int fd;     struct stat sb;     ngx_http_header_out_t  *header_out;     ngx_chunk_t            *header, *ch;      int index = (*(r->uri_end - 1) == '/') ? sizeof(NGX_INDEX) : 1;     char *name = ngx_palloc(r->pool,                            r->uri_end - r->uri_start + strlen(ngx_root) + index);     strcpy(name, ngx_root);     strcat(name, r->uri_start);     if (*(r->uri_end - 1) == '/')         strcat(name, NGX_INDEX);      ngx_log_debug(r->connection->log, "HTTP URI: '%s'", name);      if ((fd = open(name, O_RDONLY)) == -1) {         ngx_log_error(NGX_LOG_ERR, r->connection->log, errno,                      "open %s failed", name);         return -1;     }      if (fstat(fd,&sb) == -1) {         ngx_log_error(NGX_LOG_ERR, r->connection->log, errno,                      "fstat %s failed", name);         return -1;     }      header_out = ngx_palloc(r->pool, sizeof(ngx_http_header_out_t));      header_out->status = NGX_HTTP_OK;     header_out->content_length = sb.st_size;     header_out->last_modified = sb.st_mtime;     header_out->content_type = "text/html";     header_out->charset = "koi8-r";     header_out->date = time(NULL);     header_out->connection = NGX_HTTP_CONN_CLOSE;
comment|/*     header_out->connection = NGX_HTTP_CONN_KEEP_ALIVE;     r->connection->read->event_handler = ngx_http_init_request; */
end_comment

begin_endif
unit|header = ngx_http_header(r, header_out);     ch = ngx_palloc(r->pool, sizeof(ngx_chunk_t));     ch->ident = fd;     ch->offset = 0;     ch->size = sb.st_size;     ch->next = NULL;     header->next = ch;      ngx_event_write(r->connection, header);      return 0; }  static int ngx_http_close_request(ngx_event_t *ev) {     ngx_connection_t *c = (ngx_connection_t *) ev->data;      ngx_log_debug(ev->log, "http close");      ngx_del_event(c->read, NGX_TIMER_EVENT);     ngx_del_event(c->write, NGX_TIMER_EVENT);      return ngx_event_close(ev); }
endif|#
directive|endif
end_endif

end_unit

