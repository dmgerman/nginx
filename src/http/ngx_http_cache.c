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

begin_decl_stmt
DECL|variable|ngx_http_cache_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_cache_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* pre conf */
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
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_cache_module
name|ngx_module_t
name|ngx_http_cache_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_http_cache_module_ctx
block|,
comment|/* module context */
name|NULL
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init module */
name|NULL
comment|/* init child */
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_cache_get (ngx_http_cache_hash_t * hash,ngx_http_cleanup_t * cleanup,ngx_str_t * key,uint32_t * crc)
name|ngx_http_cache_t
modifier|*
name|ngx_http_cache_get
parameter_list|(
name|ngx_http_cache_hash_t
modifier|*
name|hash
parameter_list|,
name|ngx_http_cleanup_t
modifier|*
name|cleanup
parameter_list|,
name|ngx_str_t
modifier|*
name|key
parameter_list|,
name|uint32_t
modifier|*
name|crc
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_http_cache_t
modifier|*
name|c
decl_stmt|;
operator|*
name|crc
operator|=
name|ngx_crc
argument_list|(
name|key
operator|->
name|data
argument_list|,
name|key
operator|->
name|len
argument_list|)
expr_stmt|;
name|c
operator|=
name|hash
operator|->
name|elts
operator|+
operator|*
name|crc
operator|%
name|hash
operator|->
name|hash
operator|*
name|hash
operator|->
name|nelts
expr_stmt|;
name|ngx_mutex_lock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|hash
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|crc
operator|==
operator|*
name|crc
operator|&&
name|c
index|[
name|i
index|]
operator|.
name|key
operator|.
name|len
operator|==
name|key
operator|->
name|len
operator|&&
name|ngx_rstrncmp
argument_list|(
name|c
index|[
name|i
index|]
operator|.
name|key
operator|.
name|data
argument_list|,
name|key
operator|->
name|data
argument_list|,
name|key
operator|->
name|len
argument_list|)
operator|==
literal|0
condition|)
block|{
name|c
index|[
name|i
index|]
operator|.
name|refs
operator|++
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
operator|(
operator|!
operator|(
name|c
index|[
name|i
index|]
operator|.
name|notify
operator|&&
operator|(
name|ngx_event_flags
operator|&
name|NGX_HAVE_KQUEUE_EVENT
operator|)
operator|)
operator|)
operator|&&
operator|(
name|ngx_cached_time
operator|-
name|c
index|[
name|i
index|]
operator|.
name|updated
operator|>=
name|hash
operator|->
name|update
operator|)
condition|)
block|{
name|c
index|[
name|i
index|]
operator|.
name|expired
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|cleanup
condition|)
block|{
name|cleanup
operator|->
name|data
operator|.
name|cache
operator|.
name|hash
operator|=
name|hash
expr_stmt|;
name|cleanup
operator|->
name|data
operator|.
name|cache
operator|.
name|cache
operator|=
operator|&
name|c
index|[
name|i
index|]
expr_stmt|;
name|cleanup
operator|->
name|valid
operator|=
literal|1
expr_stmt|;
name|cleanup
operator|->
name|cache
operator|=
literal|1
expr_stmt|;
block|}
return|return
operator|&
name|c
index|[
name|i
index|]
return|;
block|}
block|}
name|ngx_mutex_unlock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_cache_alloc (ngx_http_cache_hash_t * hash,ngx_http_cache_t * cache,ngx_http_cleanup_t * cleanup,ngx_str_t * key,uint32_t crc,ngx_str_t * value,ngx_log_t * log)
name|ngx_http_cache_t
modifier|*
name|ngx_http_cache_alloc
parameter_list|(
name|ngx_http_cache_hash_t
modifier|*
name|hash
parameter_list|,
name|ngx_http_cache_t
modifier|*
name|cache
parameter_list|,
name|ngx_http_cleanup_t
modifier|*
name|cleanup
parameter_list|,
name|ngx_str_t
modifier|*
name|key
parameter_list|,
name|uint32_t
name|crc
parameter_list|,
name|ngx_str_t
modifier|*
name|value
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|time_t
name|old
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_http_cache_t
modifier|*
name|c
decl_stmt|;
name|old
operator|=
name|ngx_cached_time
operator|+
literal|1
expr_stmt|;
name|c
operator|=
name|hash
operator|->
name|elts
operator|+
name|crc
operator|%
name|hash
operator|->
name|hash
operator|*
name|hash
operator|->
name|nelts
expr_stmt|;
name|ngx_mutex_lock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
operator|==
name|NULL
condition|)
block|{
comment|/* allocate a new entry */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|hash
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|refs
operator|>
literal|0
condition|)
block|{
comment|/* a busy entry */
continue|continue;
block|}
if|if
condition|(
name|c
index|[
name|i
index|]
operator|.
name|key
operator|.
name|len
operator|==
literal|0
condition|)
block|{
comment|/* a free entry is found */
name|cache
operator|=
operator|&
name|c
index|[
name|i
index|]
expr_stmt|;
break|break;
block|}
comment|/* looking for the oldest cache entry */
if|if
condition|(
name|old
operator|>
name|c
index|[
name|i
index|]
operator|.
name|accessed
condition|)
block|{
name|old
operator|=
name|c
index|[
name|i
index|]
operator|.
name|accessed
expr_stmt|;
name|cache
operator|=
operator|&
name|c
index|[
name|i
index|]
expr_stmt|;
block|}
block|}
if|if
condition|(
name|cache
operator|==
name|NULL
condition|)
block|{
name|ngx_mutex_unlock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|ngx_http_cache_free
argument_list|(
name|cache
argument_list|,
name|key
argument_list|,
name|value
argument_list|,
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
operator|->
name|key
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|cache
operator|->
name|key
operator|.
name|data
operator|=
name|ngx_alloc
argument_list|(
name|key
operator|->
name|len
argument_list|,
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
operator|->
name|key
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|ngx_http_cache_free
argument_list|(
name|cache
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|log
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
name|cache
operator|->
name|key
operator|.
name|len
operator|=
name|key
operator|->
name|len
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|cache
operator|->
name|key
operator|.
name|data
argument_list|,
name|key
operator|->
name|data
argument_list|,
name|key
operator|->
name|len
argument_list|)
expr_stmt|;
block|}
if|else if
condition|(
name|value
condition|)
block|{
name|ngx_http_cache_free
argument_list|(
name|cache
argument_list|,
name|key
argument_list|,
name|value
argument_list|,
name|log
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|value
condition|)
block|{
if|if
condition|(
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|data
operator|=
name|ngx_alloc
argument_list|(
name|value
operator|->
name|len
argument_list|,
name|log
argument_list|)
expr_stmt|;
if|if
condition|(
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|ngx_http_cache_free
argument_list|(
name|cache
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|log
argument_list|)
expr_stmt|;
name|ngx_mutex_unlock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|len
operator|=
name|value
operator|->
name|len
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|data
argument_list|,
name|value
operator|->
name|data
argument_list|,
name|value
operator|->
name|len
argument_list|)
expr_stmt|;
block|}
name|cache
operator|->
name|crc
operator|=
name|crc
expr_stmt|;
name|cache
operator|->
name|key
operator|.
name|len
operator|=
name|key
operator|->
name|len
expr_stmt|;
name|cache
operator|->
name|refs
operator|=
literal|1
expr_stmt|;
name|cache
operator|->
name|count
operator|=
literal|0
expr_stmt|;
name|cache
operator|->
name|deleted
operator|=
literal|0
expr_stmt|;
name|cache
operator|->
name|expired
operator|=
literal|0
expr_stmt|;
name|cache
operator|->
name|memory
operator|=
literal|0
expr_stmt|;
name|cache
operator|->
name|mmap
operator|=
literal|0
expr_stmt|;
name|cache
operator|->
name|notify
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|cleanup
condition|)
block|{
name|cleanup
operator|->
name|data
operator|.
name|cache
operator|.
name|hash
operator|=
name|hash
expr_stmt|;
name|cleanup
operator|->
name|data
operator|.
name|cache
operator|.
name|cache
operator|=
name|cache
expr_stmt|;
name|cleanup
operator|->
name|valid
operator|=
literal|1
expr_stmt|;
name|cleanup
operator|->
name|cache
operator|=
literal|1
expr_stmt|;
block|}
name|ngx_mutex_unlock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
return|return
name|cache
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_cache_free (ngx_http_cache_t * cache,ngx_str_t * key,ngx_str_t * value,ngx_log_t * log)
name|void
name|ngx_http_cache_free
parameter_list|(
name|ngx_http_cache_t
modifier|*
name|cache
parameter_list|,
name|ngx_str_t
modifier|*
name|key
parameter_list|,
name|ngx_str_t
modifier|*
name|value
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
if|if
condition|(
name|cache
operator|->
name|memory
condition|)
block|{
if|if
condition|(
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|data
operator|&&
operator|(
name|value
operator|==
name|NULL
operator|||
name|value
operator|->
name|len
operator|>
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|len
operator|)
condition|)
block|{
name|ngx_free
argument_list|(
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|data
argument_list|)
expr_stmt|;
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
block|}
block|}
comment|/* TODO: mmap */
name|cache
operator|->
name|data
operator|.
name|value
operator|.
name|len
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|cache
operator|->
name|fd
operator|!=
name|NGX_INVALID_FILE
condition|)
block|{
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"http cache close fd: %d"
argument_list|,
name|cache
operator|->
name|fd
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_close_file
argument_list|(
name|cache
operator|->
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|cache
operator|->
name|key
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
name|cache
operator|->
name|fd
operator|=
name|NGX_INVALID_FILE
expr_stmt|;
block|}
if|if
condition|(
name|cache
operator|->
name|key
operator|.
name|data
operator|&&
operator|(
name|key
operator|==
name|NULL
operator|||
name|key
operator|->
name|len
operator|>
name|cache
operator|->
name|key
operator|.
name|len
operator|)
condition|)
block|{
name|ngx_free
argument_list|(
name|cache
operator|->
name|key
operator|.
name|data
argument_list|)
expr_stmt|;
name|cache
operator|->
name|key
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
block|}
name|cache
operator|->
name|key
operator|.
name|len
operator|=
literal|0
expr_stmt|;
name|cache
operator|->
name|refs
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_http_cache_unlock (ngx_http_cache_hash_t * hash,ngx_http_cache_t * cache,ngx_log_t * log)
name|void
name|ngx_http_cache_unlock
parameter_list|(
name|ngx_http_cache_hash_t
modifier|*
name|hash
parameter_list|,
name|ngx_http_cache_t
modifier|*
name|cache
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_mutex_lock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
name|cache
operator|->
name|refs
operator|--
expr_stmt|;
if|if
condition|(
name|cache
operator|->
name|refs
operator|==
literal|0
operator|&&
name|cache
operator|->
name|deleted
condition|)
block|{
name|ngx_http_cache_free
argument_list|(
name|cache
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|log
argument_list|)
expr_stmt|;
block|}
name|ngx_mutex_unlock
argument_list|(
operator|&
name|hash
operator|->
name|mutex
argument_list|)
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|ngx_add_file_event(ngx_fd_t, ngx_event_handler_pt *handler, void *data) {     ngx_event_t  *ev;      ev =&ngx_cycle->read_events[fd];     ngx_memzero(ev, sizeof(ngx_event_t);      ev->data = data;     ev->event_handler = ngx_http_cache_invalidate;      return ngx_add_event(ev, NGX_VNODE_EVENT, 0); }   void ngx_http_cache_invalidate(ngx_event_t *ev) {     ngx_http_cache_ctx_t  *ctx;      ctx = ev->data;      ngx_http_cache_lock(&ctx->hash->mutex);      if (ctx->cache->refs == 0)         ngx_http_cache_free(ctx->cache, NULL, NULL, ctx->log);      } else {         ctx->cache->deleted = 1;     }      ngx_http_cache_unlock(&ctx->hash->mutex); }
endif|#
directive|endif
end_endif

begin_comment
comment|/* TODO: currently fd only */
end_comment

begin_function
DECL|function|ngx_http_send_cached (ngx_http_request_t * r)
name|ngx_int_t
name|ngx_http_send_cached
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|ngx_chain_t
name|out
decl_stmt|;
name|ngx_http_log_ctx_t
modifier|*
name|ctx
decl_stmt|;
name|ctx
operator|=
name|r
operator|->
name|connection
operator|->
name|log
operator|->
name|data
expr_stmt|;
name|ctx
operator|->
name|action
operator|=
literal|"sending response to client"
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|status
operator|=
name|NGX_HTTP_OK
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|content_length_n
operator|=
name|r
operator|->
name|cache
operator|->
name|data
operator|.
name|size
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
operator|=
name|r
operator|->
name|cache
operator|->
name|last_modified
expr_stmt|;
if|if
condition|(
name|ngx_http_set_content_type
argument_list|(
name|r
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
comment|/* we need to allocate all before the header would be sent */
if|if
condition|(
operator|!
operator|(
name|h
operator|=
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_hunk_t
argument_list|)
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
if|if
condition|(
operator|!
operator|(
name|h
operator|->
name|file
operator|=
name|ngx_pcalloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_file_t
argument_list|)
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|rc
operator|=
name|ngx_http_send_header
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|rc
operator|>
name|NGX_OK
operator|||
name|r
operator|->
name|header_only
condition|)
block|{
return|return
name|rc
return|;
block|}
name|h
operator|->
name|type
operator|=
name|r
operator|->
expr|main
operator|?
name|NGX_HUNK_FILE
operator|:
name|NGX_HUNK_FILE
operator||
name|NGX_HUNK_LAST
expr_stmt|;
name|h
operator|->
name|file_pos
operator|=
literal|0
expr_stmt|;
name|h
operator|->
name|file_last
operator|=
name|r
operator|->
name|cache
operator|->
name|data
operator|.
name|size
expr_stmt|;
name|h
operator|->
name|file
operator|->
name|fd
operator|=
name|r
operator|->
name|cache
operator|->
name|fd
expr_stmt|;
name|h
operator|->
name|file
operator|->
name|log
operator|=
name|r
operator|->
name|connection
operator|->
name|log
expr_stmt|;
name|out
operator|.
name|hunk
operator|=
name|h
expr_stmt|;
name|out
operator|.
name|next
operator|=
name|NULL
expr_stmt|;
return|return
name|ngx_http_output_filter
argument_list|(
name|r
argument_list|,
operator|&
name|out
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_http_set_cache_slot (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|char
modifier|*
name|ngx_http_set_cache_slot
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|char
modifier|*
name|p
init|=
name|conf
decl_stmt|;
name|ngx_int_t
name|i
decl_stmt|,
name|j
decl_stmt|,
name|dup
decl_stmt|,
name|invalid
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|,
name|line
decl_stmt|;
name|ngx_http_cache_t
modifier|*
name|c
decl_stmt|;
name|ngx_http_cache_hash_t
modifier|*
name|ch
decl_stmt|,
modifier|*
modifier|*
name|chp
decl_stmt|;
name|chp
operator|=
operator|(
name|ngx_http_cache_hash_t
operator|*
operator|*
operator|)
operator|(
name|p
operator|+
name|cmd
operator|->
name|offset
operator|)
expr_stmt|;
if|if
condition|(
operator|*
name|chp
condition|)
block|{
return|return
literal|"is duplicate"
return|;
block|}
if|if
condition|(
operator|!
operator|(
name|ch
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_cache_hash_t
argument_list|)
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
operator|*
name|chp
operator|=
name|ch
expr_stmt|;
name|dup
operator|=
literal|0
expr_stmt|;
name|invalid
operator|=
literal|0
expr_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|cf
operator|->
name|args
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|1
index|]
operator|!=
literal|'='
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid value \"%s\""
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
switch|switch
condition|(
name|value
index|[
name|i
index|]
operator|.
name|data
index|[
literal|0
index|]
condition|)
block|{
case|case
literal|'h'
case|:
if|if
condition|(
name|ch
operator|->
name|hash
condition|)
block|{
name|dup
operator|=
literal|1
expr_stmt|;
break|break;
block|}
name|ch
operator|->
name|hash
operator|=
name|ngx_atoi
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
literal|2
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
name|ch
operator|->
name|hash
operator|==
operator|(
name|size_t
operator|)
name|NGX_ERROR
operator|||
name|ch
operator|->
name|hash
operator|==
literal|0
condition|)
block|{
name|invalid
operator|=
literal|1
expr_stmt|;
break|break;
block|}
continue|continue;
case|case
literal|'n'
case|:
if|if
condition|(
name|ch
operator|->
name|nelts
condition|)
block|{
name|dup
operator|=
literal|1
expr_stmt|;
break|break;
block|}
name|ch
operator|->
name|nelts
operator|=
name|ngx_atoi
argument_list|(
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
literal|2
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|2
argument_list|)
expr_stmt|;
if|if
condition|(
name|ch
operator|->
name|nelts
operator|==
operator|(
name|size_t
operator|)
name|NGX_ERROR
operator|||
name|ch
operator|->
name|nelts
operator|==
literal|0
condition|)
block|{
name|invalid
operator|=
literal|1
expr_stmt|;
break|break;
block|}
continue|continue;
case|case
literal|'l'
case|:
if|if
condition|(
name|ch
operator|->
name|life
condition|)
block|{
name|dup
operator|=
literal|1
expr_stmt|;
break|break;
block|}
name|line
operator|.
name|len
operator|=
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|2
expr_stmt|;
name|line
operator|.
name|data
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
literal|2
expr_stmt|;
name|ch
operator|->
name|life
operator|=
name|ngx_parse_time
argument_list|(
operator|&
name|line
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|ch
operator|->
name|life
operator|==
name|NGX_ERROR
operator|||
name|ch
operator|->
name|life
operator|==
literal|0
condition|)
block|{
name|invalid
operator|=
literal|1
expr_stmt|;
break|break;
block|}
continue|continue;
case|case
literal|'u'
case|:
if|if
condition|(
name|ch
operator|->
name|update
condition|)
block|{
name|dup
operator|=
literal|1
expr_stmt|;
break|break;
block|}
name|line
operator|.
name|len
operator|=
name|value
index|[
name|i
index|]
operator|.
name|len
operator|-
literal|2
expr_stmt|;
name|line
operator|.
name|data
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
operator|+
literal|2
expr_stmt|;
name|ch
operator|->
name|update
operator|=
name|ngx_parse_time
argument_list|(
operator|&
name|line
argument_list|,
literal|1
argument_list|)
expr_stmt|;
if|if
condition|(
name|ch
operator|->
name|update
operator|==
name|NGX_ERROR
operator|||
name|ch
operator|->
name|update
operator|==
literal|0
condition|)
block|{
name|invalid
operator|=
literal|1
expr_stmt|;
break|break;
block|}
continue|continue;
default|default:
name|invalid
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|dup
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"duplicate value \"%s\""
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|invalid
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid value \"%s\""
argument_list|,
name|value
index|[
name|i
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
name|ch
operator|->
name|elts
operator|=
name|ngx_pcalloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|ch
operator|->
name|hash
operator|*
name|ch
operator|->
name|nelts
operator|*
sizeof|sizeof
argument_list|(
name|ngx_http_cache_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ch
operator|->
name|elts
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
operator|(
name|ngx_int_t
operator|)
name|ch
operator|->
name|hash
condition|;
name|i
operator|++
control|)
block|{
name|c
operator|=
name|ch
operator|->
name|elts
operator|+
name|i
operator|*
name|ch
operator|->
name|nelts
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
operator|(
name|ngx_int_t
operator|)
name|ch
operator|->
name|nelts
condition|;
name|j
operator|++
control|)
block|{
name|c
index|[
name|j
index|]
operator|.
name|fd
operator|=
name|NGX_INVALID_FILE
expr_stmt|;
block|}
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

