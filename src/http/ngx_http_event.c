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

begin_function_decl
specifier|static
name|size_t
name|ngx_http_log_error
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* STUB */
end_comment

begin_function_decl
specifier|static
name|int
name|ngx_http_writer
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

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
name|struct
name|sockaddr
modifier|*
name|addr
decl_stmt|;
name|ngx_http_log_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ev
operator|=
name|c
operator|->
name|read
expr_stmt|;
name|ev
operator|->
name|event_handler
operator|=
name|ngx_http_init_request
expr_stmt|;
comment|/* TODO: connection's pool size */
name|ngx_test_null
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|ngx_create_pool
argument_list|(
literal|1024
argument_list|,
name|ev
operator|->
name|log
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|addr
argument_list|,
name|ngx_palloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|c
operator|->
name|socklen
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|addr
argument_list|,
name|c
operator|->
name|sockaddr
argument_list|,
name|c
operator|->
name|socklen
argument_list|)
expr_stmt|;
name|c
operator|->
name|sockaddr
operator|=
name|addr
expr_stmt|;
name|ngx_test_null
argument_list|(
name|c
operator|->
name|addr_text
argument_list|,
name|ngx_palloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|c
operator|->
name|addr_textlen
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|inet_ntop
argument_list|(
name|c
operator|->
name|family
argument_list|,
operator|(
name|char
operator|*
operator|)
name|c
operator|->
name|sockaddr
operator|+
name|c
operator|->
name|addr
argument_list|,
name|c
operator|->
name|addr_text
argument_list|,
name|c
operator|->
name|addr_textlen
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|ctx
argument_list|,
name|ngx_pcalloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_log_ctx_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ctx
operator|->
name|client
operator|=
name|c
operator|->
name|addr_text
expr_stmt|;
name|ctx
operator|->
name|action
operator|=
literal|"reading client request line"
expr_stmt|;
name|c
operator|->
name|log
operator|->
name|data
operator|=
name|ctx
expr_stmt|;
name|c
operator|->
name|log
operator|->
name|handler
operator|=
name|ngx_http_log_error
expr_stmt|;
name|ngx_add_timer
argument_list|(
name|ev
argument_list|,
name|c
operator|->
name|post_accept_timeout
argument_list|)
expr_stmt|;
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
name|USE_KQUEUE
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
if|#
directive|if
operator|(
name|HAVE_AIO_EVENT
operator|)
if|if
condition|(
name|ngx_event_type
operator|==
name|NGX_AIO_EVENT
condition|)
return|return
name|ngx_http_init_request
argument_list|(
name|ev
argument_list|)
return|;
if|else
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_CLEAR_EVENT
operator|)
if|if
condition|(
name|ngx_event_type
operator|==
name|NGX_KQUEUE_EVENT
condition|)
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
else|else
else|#
directive|else
return|return
name|ngx_add_event
argument_list|(
name|ev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_LEVEL_EVENT
argument_list|)
return|;
endif|#
directive|endif
endif|#
directive|endif
block|}
end_function

begin_function
DECL|function|ngx_http_init_request (ngx_event_t * ev)
name|int
name|ngx_http_init_request
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_http_server_t
modifier|*
name|srv
decl_stmt|;
name|ngx_http_request_t
modifier|*
name|r
decl_stmt|;
name|c
operator|=
operator|(
name|ngx_connection_t
operator|*
operator|)
name|ev
operator|->
name|data
expr_stmt|;
name|srv
operator|=
operator|(
name|ngx_http_server_t
operator|*
operator|)
name|c
operator|->
name|server
expr_stmt|;
name|ngx_test_null
argument_list|(
name|r
argument_list|,
name|ngx_pcalloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_request_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|c
operator|->
name|data
operator|=
name|r
expr_stmt|;
name|r
operator|->
name|connection
operator|=
name|c
expr_stmt|;
name|r
operator|->
name|server
operator|=
name|srv
expr_stmt|;
name|ngx_test_null
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|ngx_create_pool
argument_list|(
literal|16384
argument_list|,
name|ev
operator|->
name|log
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
comment|/* TODO: buff -> hunk */
name|ngx_test_null
argument_list|(
name|r
operator|->
name|buff
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_buff_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|r
operator|->
name|buff
operator|->
name|buff
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|srv
operator|->
name|buff_size
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|r
operator|->
name|buff
operator|->
name|pos
operator|=
name|r
operator|->
name|buff
operator|->
name|last
operator|=
name|r
operator|->
name|buff
operator|->
name|buff
expr_stmt|;
name|r
operator|->
name|buff
operator|->
name|end
operator|=
name|r
operator|->
name|buff
operator|->
name|buff
operator|+
name|srv
operator|->
name|buff_size
expr_stmt|;
name|r
operator|->
name|state_handler
operator|=
name|ngx_process_http_request_line
expr_stmt|;
name|ev
operator|->
name|event_handler
operator|=
name|ngx_http_process_request
expr_stmt|;
name|ev
operator|->
name|close_handler
operator|=
name|ngx_http_close_request
expr_stmt|;
name|c
operator|->
name|write
operator|->
name|close_handler
operator|=
name|ngx_http_close_request
expr_stmt|;
return|return
name|ngx_http_process_request
argument_list|(
name|ev
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_process_request (ngx_event_t * ev)
name|int
name|ngx_http_process_request
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_http_request_t
modifier|*
name|r
decl_stmt|;
name|c
operator|=
operator|(
name|ngx_connection_t
operator|*
operator|)
name|ev
operator|->
name|data
expr_stmt|;
name|r
operator|=
operator|(
name|ngx_http_request_t
operator|*
operator|)
name|c
operator|->
name|data
expr_stmt|;
name|ngx_log_debug
argument_list|(
name|ev
operator|->
name|log
argument_list|,
literal|"http process request"
argument_list|)
expr_stmt|;
name|n
operator|=
name|ngx_event_recv
argument_list|(
name|ev
argument_list|,
name|r
operator|->
name|buff
operator|->
name|last
argument_list|,
name|r
operator|->
name|buff
operator|->
name|end
operator|-
name|r
operator|->
name|buff
operator|->
name|last
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
return|return
name|NGX_AGAIN
return|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
comment|/* close request */
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_debug
argument_list|(
argument|ev->log
argument_list|,
literal|"http read %d"
argument|_ n
argument_list|)
empty_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|ev
operator|->
name|unexpected_eof
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|ev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"connection is closed"
argument_list|)
expr_stmt|;
comment|/* close request */
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|ngx_http_close_request
argument_list|(
name|ev
argument_list|)
return|;
block|}
if|if
condition|(
operator|!
name|ev
operator|->
name|read_discarded
condition|)
block|{
name|r
operator|->
name|buff
operator|->
name|last
operator|+=
name|n
expr_stmt|;
comment|/* state_handlers are called in following order:             ngx_process_http_request_line()             ngx_process_http_request_header() */
do|do
block|{
if|if
condition|(
operator|(
name|r
operator|->
name|state_handler
operator|)
operator|(
name|r
operator|)
operator|<
literal|0
condition|)
return|return
operator|-
literal|1
return|;
block|}
do|while
condition|(
name|r
operator|->
name|buff
operator|->
name|pos
operator|<
name|r
operator|->
name|buff
operator|->
name|last
condition|)
do|;
block|}
if|if
condition|(
name|ngx_del_event
argument_list|(
name|ev
argument_list|,
name|NGX_TIMER_EVENT
argument_list|)
operator|==
operator|-
literal|1
condition|)
return|return
operator|-
literal|1
return|;
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
return|return
literal|0
return|;
block|}
end_function

begin_function
DECL|function|ngx_process_http_request_line (ngx_http_request_t * r)
specifier|static
name|int
name|ngx_process_http_request_line
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
if|if
condition|(
operator|(
name|n
operator|=
name|ngx_read_http_request_line
argument_list|(
name|r
argument_list|)
operator|)
operator|==
literal|1
condition|)
block|{
operator|*
name|r
operator|->
name|uri_end
operator|=
literal|'\0'
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"HTTP: %d, %d, %s"
argument|_                      r->method _ r->http_version _ r->uri_start
argument_list|)
empty_stmt|;
name|r
operator|->
name|state_handler
operator|=
name|ngx_process_http_request_header
expr_stmt|;
name|r
operator|->
name|connection
operator|->
name|read
operator|->
name|action
operator|=
literal|"reading client request headers"
expr_stmt|;
block|}
return|return
name|n
return|;
block|}
end_function

begin_function
DECL|function|ngx_process_http_request_header (ngx_http_request_t * r)
specifier|static
name|int
name|ngx_process_http_request_header
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
while|while
condition|(
operator|(
name|n
operator|=
name|ngx_read_http_header_line
argument_list|(
name|r
argument_list|)
operator|)
operator|==
literal|1
condition|)
block|{
operator|*
name|r
operator|->
name|header_name_end
operator|=
literal|'\0'
expr_stmt|;
operator|*
name|r
operator|->
name|header_end
operator|=
literal|'\0'
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"HTTP header: '%s: %s'"
argument|_                      r->header_name_start _ r->header_start
argument_list|)
empty_stmt|;
block|}
if|if
condition|(
name|n
operator|!=
literal|2
condition|)
return|return
name|n
return|;
name|r
operator|->
name|state_handler
operator|=
name|NULL
expr_stmt|;
name|r
operator|->
name|connection
operator|->
name|read
operator|->
name|action
operator|=
literal|"reading client request body"
expr_stmt|;
name|r
operator|->
name|connection
operator|->
name|read
operator|->
name|read_discarded
operator|=
literal|1
expr_stmt|;
name|r
operator|->
name|connection
operator|->
name|read
operator|->
name|unexpected_eof
operator|=
literal|0
expr_stmt|;
name|ngx_log_debug
argument_list|(
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|"HTTP header done"
argument_list|)
expr_stmt|;
return|return
name|ngx_process_http_request
argument_list|(
name|r
argument_list|)
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|static int ngx_http_lock_read(ngx_event_t *ev) {     ngx_del_event(ev, NGX_READ_EVENT);     ev->read_blocked = 1; }
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_process_http_request (ngx_http_request_t * r)
specifier|static
name|int
name|ngx_process_http_request
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|int
name|err
decl_stmt|,
name|rc
decl_stmt|;
name|char
modifier|*
name|name
decl_stmt|,
modifier|*
name|loc
decl_stmt|,
modifier|*
name|file
decl_stmt|;
name|ngx_log_debug
argument_list|(
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|"HTTP request"
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|r
operator|->
name|headers_out
argument_list|,
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_headers_out_t
argument_list|)
argument_list|)
argument_list|,
name|ngx_http_error
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|*
operator|(
name|r
operator|->
name|uri_end
operator|-
literal|1
operator|)
operator|==
literal|'/'
condition|)
block|{
name|r
operator|->
name|handler
operator|=
name|NGX_HTTP_DIRECTORY_HANDLER
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
comment|/* 20 bytes is spare space for some index name, i.e. index.html */
name|r
operator|->
name|filename_len
operator|=
name|r
operator|->
name|uri_end
operator|-
name|r
operator|->
name|uri_start
operator|+
name|r
operator|->
name|server
operator|->
name|doc_root_len
operator|+
literal|20
expr_stmt|;
name|ngx_test_null
argument_list|(
name|r
operator|->
name|filename
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|r
operator|->
name|filename_len
argument_list|)
argument_list|,
name|ngx_http_error
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
argument_list|)
expr_stmt|;
name|r
operator|->
name|location
operator|=
name|ngx_cpystrn
argument_list|(
name|r
operator|->
name|filename
argument_list|,
name|r
operator|->
name|server
operator|->
name|doc_root
argument_list|,
name|r
operator|->
name|server
operator|->
name|doc_root_len
argument_list|)
expr_stmt|;
name|file
operator|=
name|ngx_cpystrn
argument_list|(
name|r
operator|->
name|location
argument_list|,
name|r
operator|->
name|uri_start
argument_list|,
name|r
operator|->
name|uri_end
operator|-
name|r
operator|->
name|uri_start
operator|+
literal|1
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"HTTP filename: '%s'"
argument|_ r->filename
argument_list|)
empty_stmt|;
if|if
condition|(
name|ngx_file_type
argument_list|(
name|r
operator|->
name|filename
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
name|err
operator|=
name|ngx_errno
expr_stmt|;
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
name|err
argument_list|,
literal|"ngx_process_http_request: "
name|ngx_file_type_n
literal|" %s failed"
argument_list|,
name|r
operator|->
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
name|NGX_ENOENT
condition|)
return|return
name|ngx_http_error
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_NOT_FOUND
argument_list|)
return|;
else|else
return|return
name|ngx_http_error
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
return|;
block|}
if|if
condition|(
name|ngx_is_dir
argument_list|(
name|r
operator|->
name|file_info
argument_list|)
condition|)
block|{
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"HTTP DIR: '%s'"
argument|_ r->filename
argument_list|)
empty_stmt|;
operator|*
name|file
operator|++
operator|=
literal|'/'
expr_stmt|;
operator|*
name|file
operator|=
literal|'\0'
expr_stmt|;
name|r
operator|->
name|headers_out
operator|->
name|location
operator|=
name|r
operator|->
name|location
expr_stmt|;
return|return
name|ngx_http_redirect
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_MOVED_PERMANENTLY
argument_list|)
return|;
block|}
comment|/* STUB */
name|rc
operator|=
name|ngx_http_static_handler
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
literal|0
condition|)
block|{
name|r
operator|->
name|connection
operator|->
name|write
operator|->
name|event_handler
operator|=
name|ngx_http_writer
expr_stmt|;
name|ngx_add_event
argument_list|(
name|r
operator|->
name|connection
operator|->
name|write
argument_list|,
name|NGX_WRITE_EVENT
argument_list|,
name|NGX_CLEAR_EVENT
argument_list|)
expr_stmt|;
block|}
return|return
name|rc
return|;
name|r
operator|->
name|handler
operator|=
name|NGX_HTTP_STATIC_HANDLER
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|static int ngx_http_handler(ngx_http_request_t *r) {     find_http_handler();      if (r->discard_body&& r->connection->read->ready)         ngx_http_discarad_body();      rc = http_handler();
comment|/* transfer not completed */
end_comment

begin_comment
unit|if (rc == NGX_AGAIN)         return rc;      if (rc == NGX_ERROR) {         log http request         close http request         return rc;     }      if (rc> 300) {         send special response     }
comment|/* rc == NGX_OK */
end_comment

begin_comment
unit|if (!keepalive)         if (linger)             set linger timeout on read             shutdown socket         else             close socket      log http request     close http request     if (keepalive)         return NGX_OK;     else         close connection         return NGX_OK; }  static int ngx_http_writer(ngx_event_t *ev) {     int rc;      ngx_connection_t   *c = (ngx_connection_t *) ev->data;     ngx_http_request_t *r = (ngx_http_request_t *) c->data;      rc = ngx_http_filter(r, NULL);      if (rc == NGX_AGAIN)         return rc;      if (rc == NGX_ERROR)         return rc;
comment|/* rc == NGX_OK */
end_comment

begin_comment
unit|if (!keepalive)         if (linger)             shutdown socket         else             close socket      log http request     close http request     if (keepalive)         return NGX_OK;     else         close connection         return NGX_OK; }  static int ngx_http_discarded_read(ngx_event_t *ev) {     if (ev->timedout)         return NGX_ERROR;      while (full) {         recv();     }      return NGX_OK; }  static int ngx_http_keepalive_handler(ngx_event_t *ev) {     ngx_connection_t    *c;     ngx_http_log_ctx_t  *ctx;      if (closed)
comment|/* NGX_LOG_INFO or even silent */
end_comment

begin_endif
unit|return NGX_ERROR;      c = (ngx_connection_t *) ev->data;      ctx = (ngx_http_log_ctx_t *) c->log->data;     ctx->action = "reading client request line";     c->log->handler = ngx_http_log_error;      return ngx_http_init_request(ev); }
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_http_writer (ngx_event_t * ev)
specifier|static
name|int
name|ngx_http_writer
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|int
name|rc
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
init|=
operator|(
name|ngx_connection_t
operator|*
operator|)
name|ev
operator|->
name|data
decl_stmt|;
name|ngx_http_request_t
modifier|*
name|r
init|=
operator|(
name|ngx_http_request_t
operator|*
operator|)
name|c
operator|->
name|data
decl_stmt|;
name|rc
operator|=
name|ngx_http_write_filter
argument_list|(
name|r
argument_list|,
name|NULL
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
block|}
end_function

begin_function
DECL|function|ngx_http_handler (ngx_http_request_t * r,int handler)
specifier|static
name|int
name|ngx_http_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|int
name|handler
parameter_list|)
block|{
if|if
condition|(
name|handler
operator|==
name|NGX_HTTP_STATIC_HANDLER
condition|)
return|return
name|ngx_http_static_handler
argument_list|(
name|r
argument_list|)
return|;
if|#
directive|if
literal|0
block_content|elsif (handler == NGX_HTTP_DIRECTORY_HANDLER)          return ngx_http_index_handler(r);
endif|#
directive|endif
return|return
name|ngx_http_error
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_redirect (ngx_http_request_t * r,int redirect)
specifier|static
name|int
name|ngx_http_redirect
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|int
name|redirect
parameter_list|)
block|{
comment|/* STUB */
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_error (ngx_http_request_t * r,int error)
specifier|static
name|int
name|ngx_http_error
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|int
name|error
parameter_list|)
block|{
comment|/* STUB */
return|return
operator|-
literal|1
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|static int ngx_process_http_request(ngx_http_request_t *r) {     int fd;     struct stat sb;     ngx_http_header_out_t  *header_out;     ngx_chunk_t            *header, *ch;      int index = (*(r->uri_end - 1) == '/') ? sizeof(NGX_INDEX) : 1;     char *name = ngx_palloc(r->pool,                            r->uri_end - r->uri_start + strlen(ngx_root) + index);     strcpy(name, ngx_root);     strcat(name, r->uri_start);     if (*(r->uri_end - 1) == '/')         strcat(name, NGX_INDEX);      ngx_log_debug(r->connection->log, "HTTP URI: '%s'", name);      if ((fd = open(name, O_RDONLY)) == -1) {         ngx_log_error(NGX_LOG_ERR, r->connection->log, errno,                      "open %s failed", name);         return -1;     }      if (fstat(fd,&sb) == -1) {         ngx_log_error(NGX_LOG_ERR, r->connection->log, errno,                      "fstat %s failed", name);         return -1;     }      header_out = ngx_palloc(r->pool, sizeof(ngx_http_header_out_t));      header_out->status = NGX_HTTP_OK;     header_out->content_length = sb.st_size;     header_out->last_modified = sb.st_mtime;     header_out->content_type = "text/html";     header_out->charset = "koi8-r";     header_out->date = time(NULL);     header_out->connection = NGX_HTTP_CONN_CLOSE;
comment|/*     header_out->connection = NGX_HTTP_CONN_KEEP_ALIVE;     r->connection->read->event_handler = ngx_http_init_request; */
end_comment

begin_endif
unit|header = ngx_http_header(r, header_out);     ch = ngx_palloc(r->pool, sizeof(ngx_chunk_t));     ch->ident = fd;     ch->offset = 0;     ch->size = sb.st_size;     ch->next = NULL;     header->next = ch;      ngx_event_write(r->connection, header);      return 0; }
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_http_close_request (ngx_event_t * ev)
specifier|static
name|int
name|ngx_http_close_request
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
block|{
name|ngx_connection_t
modifier|*
name|c
init|=
operator|(
name|ngx_connection_t
operator|*
operator|)
name|ev
operator|->
name|data
decl_stmt|;
name|ngx_log_debug
argument_list|(
name|ev
operator|->
name|log
argument_list|,
literal|"http close"
argument_list|)
expr_stmt|;
name|ngx_del_event
argument_list|(
name|c
operator|->
name|read
argument_list|,
name|NGX_TIMER_EVENT
argument_list|)
expr_stmt|;
name|ngx_del_event
argument_list|(
name|c
operator|->
name|write
argument_list|,
name|NGX_TIMER_EVENT
argument_list|)
expr_stmt|;
return|return
name|ngx_event_close_connection
argument_list|(
name|ev
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_log_error (void * data,char * buf,size_t len)
specifier|static
name|size_t
name|ngx_http_log_error
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
block|{
name|ngx_http_log_ctx_t
modifier|*
name|ctx
init|=
operator|(
name|ngx_http_log_ctx_t
operator|*
operator|)
name|data
decl_stmt|;
if|if
condition|(
name|ctx
operator|->
name|url
condition|)
return|return
name|ngx_snprintf
argument_list|(
name|buf
argument_list|,
name|len
argument_list|,
literal|" while %s, client: %s, URL: %s"
argument_list|,
name|ctx
operator|->
name|action
argument_list|,
name|ctx
operator|->
name|client
argument_list|,
name|ctx
operator|->
name|url
argument_list|)
return|;
else|else
return|return
name|ngx_snprintf
argument_list|(
name|buf
argument_list|,
name|len
argument_list|,
literal|" while %s, client: %s"
argument_list|,
name|ctx
operator|->
name|action
argument_list|,
name|ctx
operator|->
name|client
argument_list|)
return|;
block|}
end_function

end_unit

