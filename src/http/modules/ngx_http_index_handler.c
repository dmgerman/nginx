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
file|<ngx_errno.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_files.h>
end_include

begin_include
include|#
directive|include
file|<ngx_conf_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_core_module.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http_index_handler.h>
end_include

begin_function_decl
specifier|static
name|int
name|ngx_http_index_test_dir
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
name|ngx_http_index_init
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_http_index_create_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_index_merge_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|p
parameter_list|,
name|void
modifier|*
name|parent
parameter_list|,
name|void
modifier|*
name|child
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_index_set_index
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|char
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_index_commands
specifier|static
name|ngx_command_t
name|ngx_http_index_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"index"
argument_list|)
block|,
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_BLOCK
operator||
name|NGX_CONF_ANY
block|,
name|ngx_http_index_set_index
block|,
name|NGX_HTTP_LOC_CONF_OFFSET
block|,
literal|0
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|""
argument_list|)
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
literal|0
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_index_module_ctx
name|ngx_http_module_t
name|ngx_http_index_module_ctx
init|=
block|{
name|NGX_HTTP_MODULE
block|,
name|NULL
block|,
comment|/* create server config */
name|NULL
block|,
comment|/* init server config */
name|ngx_http_index_create_conf
block|,
comment|/* create location config */
name|ngx_http_index_merge_conf
block|,
comment|/* merge location config */
name|NULL
block|,
comment|/* translate handler */
name|NULL
block|,
comment|/* output header filter */
name|NULL
block|,
comment|/* next output header filter */
name|NULL
block|,
comment|/* output body filter */
name|NULL
block|,
comment|/* next output body filter */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_index_module
name|ngx_module_t
name|ngx_http_index_module
init|=
block|{
literal|0
block|,
comment|/* module index */
operator|&
name|ngx_http_index_module_ctx
block|,
comment|/* module context */
name|ngx_http_index_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE_TYPE
block|,
comment|/* module type */
name|ngx_http_index_init
comment|/* init module */
block|}
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*    Try to open first index file before the test of the directory existence    because the valid requests should be many more then invalid ones.    If open() failed then stat() should be more quickly because some data    is already cached in the kernel.  Besides Win32 has ERROR_PATH_NOT_FOUND    and Unix has ENOTDIR error (although it less helpfull). */
end_comment

begin_function
DECL|function|ngx_http_index_handler (ngx_http_request_t * r)
name|int
name|ngx_http_index_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|rc
decl_stmt|,
name|test_dir
decl_stmt|;
name|char
modifier|*
name|name
decl_stmt|,
modifier|*
name|file
decl_stmt|;
name|ngx_str_t
name|loc
decl_stmt|,
modifier|*
name|index
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_fd_t
name|fd
decl_stmt|;
name|ngx_http_index_conf_t
modifier|*
name|cf
decl_stmt|;
name|ngx_http_core_loc_conf_t
modifier|*
name|core_cf
decl_stmt|;
name|cf
operator|=
operator|(
name|ngx_http_index_conf_t
operator|*
operator|)
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_index_module
argument_list|)
expr_stmt|;
name|core_cf
operator|=
operator|(
name|ngx_http_core_loc_conf_t
operator|*
operator|)
name|ngx_http_get_module_loc_conf
argument_list|(
name|r
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|r
operator|->
name|path
operator|.
name|data
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|core_cf
operator|->
name|doc_root
operator|.
name|len
operator|+
name|r
operator|->
name|uri
operator|.
name|len
operator|+
name|cf
operator|->
name|max_index_len
argument_list|)
argument_list|,
name|NGX_HTTP_INTERNAL_SERVER_ERROR
argument_list|)
expr_stmt|;
name|loc
operator|.
name|data
operator|=
name|ngx_cpystrn
argument_list|(
name|r
operator|->
name|path
operator|.
name|data
argument_list|,
name|core_cf
operator|->
name|doc_root
operator|.
name|data
argument_list|,
name|core_cf
operator|->
name|doc_root
operator|.
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
name|file
operator|=
name|ngx_cpystrn
argument_list|(
name|loc
operator|.
name|data
argument_list|,
name|r
operator|->
name|uri
operator|.
name|data
argument_list|,
name|r
operator|->
name|uri
operator|.
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
name|r
operator|->
name|path
operator|.
name|len
operator|=
name|file
operator|-
name|r
operator|->
name|path
operator|.
name|data
expr_stmt|;
name|test_dir
operator|=
literal|1
expr_stmt|;
name|index
operator|=
operator|(
name|ngx_str_t
operator|*
operator|)
name|cf
operator|->
name|indices
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cf
operator|->
name|indices
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|index
index|[
name|i
index|]
operator|.
name|data
index|[
literal|0
index|]
operator|!=
literal|'/'
condition|)
block|{
name|ngx_memcpy
argument_list|(
name|file
argument_list|,
name|index
index|[
name|i
index|]
operator|.
name|data
argument_list|,
name|index
index|[
name|i
index|]
operator|.
name|len
operator|+
literal|1
argument_list|)
expr_stmt|;
name|name
operator|=
name|r
operator|->
name|path
operator|.
name|data
expr_stmt|;
block|}
else|else
block|{
name|name
operator|=
name|index
index|[
name|i
index|]
operator|.
name|data
expr_stmt|;
block|}
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|name
argument_list|,
name|NGX_FILE_RDONLY
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|err
operator|=
name|ngx_errno
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_DEBUG
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
name|err
argument_list|,
literal|"DEBUG: "
name|ngx_open_file_n
literal|" %s failed"
argument_list|,
name|name
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|WIN32
operator|)
if|if
condition|(
name|err
operator|==
name|ERROR_PATH_NOT_FOUND
condition|)
block|{
else|#
directive|else
if|if
condition|(
name|err
operator|==
name|NGX_ENOTDIR
condition|)
block|{
endif|#
directive|endif
name|r
operator|->
name|path_not_found
operator|=
literal|1
expr_stmt|;
block|}
if|else if
condition|(
name|err
operator|==
name|NGX_EACCES
condition|)
block|{
name|r
operator|->
name|path_err
operator|=
name|err
expr_stmt|;
return|return
name|NGX_HTTP_FORBIDDEN
return|;
block|}
if|if
condition|(
name|test_dir
condition|)
block|{
if|if
condition|(
name|r
operator|->
name|path_not_found
condition|)
block|{
name|r
operator|->
name|path_err
operator|=
name|err
expr_stmt|;
return|return
name|NGX_HTTP_NOT_FOUND
return|;
block|}
name|rc
operator|=
name|ngx_http_index_test_dir
argument_list|(
name|r
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|rc
return|;
block|}
name|test_dir
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|err
operator|==
name|NGX_ENOENT
condition|)
block|{
continue|continue;
block|}
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
name|ngx_open_file_n
literal|" %s failed"
argument_list|,
name|name
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|data
operator|=
name|name
expr_stmt|;
name|r
operator|->
name|file
operator|.
name|fd
operator|=
name|fd
expr_stmt|;
if|if
condition|(
name|index
index|[
name|i
index|]
operator|.
name|data
index|[
literal|0
index|]
operator|==
literal|'/'
condition|)
block|{
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|len
operator|=
name|index
index|[
name|i
index|]
operator|.
name|len
expr_stmt|;
name|loc
operator|.
name|len
operator|=
name|index
index|[
name|i
index|]
operator|.
name|len
expr_stmt|;
name|loc
operator|.
name|data
operator|=
name|index
index|[
name|i
index|]
operator|.
name|data
expr_stmt|;
block|}
else|else
block|{
name|loc
operator|.
name|len
operator|=
name|r
operator|->
name|uri
operator|.
name|len
operator|+
name|index
index|[
name|i
index|]
operator|.
name|len
expr_stmt|;
name|r
operator|->
name|file
operator|.
name|name
operator|.
name|len
operator|=
name|core_cf
operator|->
name|doc_root
operator|.
name|len
operator|+
name|r
operator|->
name|uri
operator|.
name|len
operator|+
name|index
index|[
name|i
index|]
operator|.
name|len
expr_stmt|;
block|}
return|return
name|ngx_http_internal_redirect
argument_list|(
name|r
argument_list|,
name|loc
argument_list|)
return|;
block|}
return|return
name|NGX_DECLINED
return|;
block|}
DECL|function|ngx_http_index_test_dir (ngx_http_request_t * r)
specifier|static
name|int
name|ngx_http_index_test_dir
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|r
operator|->
name|path
operator|.
name|data
index|[
name|r
operator|->
name|path
operator|.
name|len
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
name|r
operator|->
name|path
operator|.
name|data
index|[
name|r
operator|->
name|path
operator|.
name|len
index|]
operator|=
literal|'\0'
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"IS_DIR: %s"
argument|_ r->path.data
argument_list|)
empty_stmt|;
if|#
directive|if
literal|0
block_content|if (r->path_err == NGX_EACCES) {             return NGX_HTTP_FORBIDDEN;         }
endif|#
directive|endif
if|if
condition|(
name|ngx_file_type
argument_list|(
name|r
operator|->
name|path
operator|.
name|data
argument_list|,
operator|&
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|r
operator|->
name|path_err
operator|=
name|ngx_errno
expr_stmt|;
if|if
condition|(
name|r
operator|->
name|path_err
operator|==
name|NGX_ENOENT
condition|)
block|{
name|r
operator|->
name|path
operator|.
name|data
index|[
name|r
operator|->
name|path
operator|.
name|len
operator|-
literal|1
index|]
operator|=
literal|'/'
expr_stmt|;
return|return
name|NGX_HTTP_NOT_FOUND
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
name|r
operator|->
name|path_err
argument_list|,
literal|"ngx_http_index_test_dir: "
name|ngx_file_type_n
literal|" %s failed"
argument_list|,
name|r
operator|->
name|path
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_HTTP_INTERNAL_SERVER_ERROR
return|;
block|}
name|r
operator|->
name|path
operator|.
name|data
index|[
name|r
operator|->
name|path
operator|.
name|len
operator|-
literal|1
index|]
operator|=
literal|'/'
expr_stmt|;
if|if
condition|(
name|ngx_is_dir
argument_list|(
name|r
operator|->
name|file
operator|.
name|info
argument_list|)
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
else|else
block|{
return|return
name|NGX_HTTP_NOT_FOUND
return|;
block|}
block|}
DECL|function|ngx_http_index_init (ngx_pool_t * pool)
specifier|static
name|int
name|ngx_http_index_init
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_http_handler_pt
modifier|*
name|h
decl_stmt|;
name|ngx_test_null
argument_list|(
name|h
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|ngx_http_index_handlers
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
operator|*
name|h
operator|=
name|ngx_http_index_handler
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
DECL|function|ngx_http_index_create_conf (ngx_pool_t * pool)
specifier|static
name|void
modifier|*
name|ngx_http_index_create_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|ngx_http_index_conf_t
modifier|*
name|conf
decl_stmt|;
name|ngx_test_null
argument_list|(
name|conf
argument_list|,
name|ngx_pcalloc
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_index_conf_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|conf
operator|->
name|indices
argument_list|,
name|ngx_create_array
argument_list|(
name|pool
argument_list|,
literal|3
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_str_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
return|return
name|conf
return|;
block|}
comment|/* STUB */
DECL|function|ngx_http_index_merge_conf (ngx_pool_t * p,void * parent,void * child)
specifier|static
name|char
modifier|*
name|ngx_http_index_merge_conf
parameter_list|(
name|ngx_pool_t
modifier|*
name|p
parameter_list|,
name|void
modifier|*
name|parent
parameter_list|,
name|void
modifier|*
name|child
parameter_list|)
block|{
name|ngx_http_index_conf_t
modifier|*
name|prev
init|=
operator|(
name|ngx_http_index_conf_t
operator|*
operator|)
name|parent
decl_stmt|;
name|ngx_http_index_conf_t
modifier|*
name|conf
init|=
operator|(
name|ngx_http_index_conf_t
operator|*
operator|)
name|child
decl_stmt|;
name|ngx_str_t
modifier|*
name|index
decl_stmt|;
if|if
condition|(
name|conf
operator|->
name|max_index_len
operator|==
literal|0
condition|)
block|{
name|ngx_test_null
argument_list|(
name|index
argument_list|,
name|ngx_push_array
argument_list|(
name|conf
operator|->
name|indices
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|index
operator|->
name|len
operator|=
sizeof|sizeof
argument_list|(
name|NGX_HTTP_INDEX
argument_list|)
operator|-
literal|1
expr_stmt|;
name|index
operator|->
name|data
operator|=
name|NGX_HTTP_INDEX
expr_stmt|;
name|conf
operator|->
name|max_index_len
operator|=
sizeof|sizeof
argument_list|(
name|NGX_HTTP_INDEX
argument_list|)
expr_stmt|;
block|}
comment|/* FAIL: if first index is started with '/' */
return|return
name|NULL
return|;
block|}
if|#
directive|if
literal|0
block_content|static char *ngx_http_index_merge_conf(ngx_pool_t *p, void *parent, void *child) {     ngx_http_index_conf_t *prev = (ngx_http_index_conf_t *) parent;     ngx_http_index_conf_t *conf = (ngx_http_index_conf_t *) child;     ngx_str_t  *index;      if (conf->max_index_len == 0) {         if (prev->max_index_len != 0) {             return prev;         }          ngx_test_null(index, ngx_push_array(conf->indices), NULL);         index->len = sizeof(NGX_HTTP_INDEX) - 1;         index->data = NGX_HTTP_INDEX;         conf->max_index_len = sizeof(NGX_HTTP_INDEX);     }      return conf; }
endif|#
directive|endif
DECL|function|ngx_http_index_set_index (ngx_conf_t * cf,ngx_command_t * cmd,char * conf)
specifier|static
name|char
modifier|*
name|ngx_http_index_set_index
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|char
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_http_index_conf_t
modifier|*
name|icf
init|=
operator|(
name|ngx_http_index_conf_t
operator|*
operator|)
name|conf
decl_stmt|;
name|int
name|i
decl_stmt|;
name|ngx_str_t
modifier|*
name|index
decl_stmt|,
modifier|*
name|value
decl_stmt|;
name|value
operator|=
operator|(
name|ngx_str_t
operator|*
operator|)
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
name|ngx_test_null
argument_list|(
name|index
argument_list|,
name|ngx_push_array
argument_list|(
name|icf
operator|->
name|indices
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|index
operator|->
name|len
operator|=
name|value
index|[
name|i
index|]
operator|.
name|len
expr_stmt|;
name|index
operator|->
name|data
operator|=
name|value
index|[
name|i
index|]
operator|.
name|data
expr_stmt|;
if|if
condition|(
name|icf
operator|->
name|max_index_len
operator|<
name|index
operator|->
name|len
condition|)
block|{
name|icf
operator|->
name|max_index_len
operator|=
name|index
operator|->
name|len
expr_stmt|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

end_unit

