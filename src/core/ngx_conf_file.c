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
file|<ngx_files.h>
end_include

begin_include
include|#
directive|include
file|<ngx_conf_file.h>
end_include

begin_decl_stmt
DECL|variable|argument_number
specifier|static
name|int
name|argument_number
index|[]
init|=
block|{
name|NGX_CONF_NOARGS
block|,
name|NGX_CONF_TAKE1
block|,
name|NGX_CONF_TAKE2
block|}
decl_stmt|;
end_decl_stmt

begin_function_decl
specifier|static
name|int
name|ngx_conf_read_token
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function
DECL|function|ngx_conf_parse (ngx_conf_t * cf,ngx_str_t * filename)
name|char
modifier|*
name|ngx_conf_parse
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_str_t
modifier|*
name|filename
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|rc
decl_stmt|,
name|found
decl_stmt|;
name|char
modifier|*
name|rv
decl_stmt|;
name|void
modifier|*
name|conf
decl_stmt|,
modifier|*
modifier|*
name|pconf
decl_stmt|;
name|ngx_str_t
modifier|*
name|name
decl_stmt|;
name|ngx_fd_t
name|fd
decl_stmt|;
name|ngx_conf_file_t
modifier|*
name|prev
decl_stmt|;
name|ngx_command_t
modifier|*
name|cmd
decl_stmt|;
if|if
condition|(
name|filename
condition|)
block|{
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|filename
operator|->
name|data
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
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"ngx_conf_file: "
name|ngx_open_file_n
literal|" %s failed"
argument_list|,
name|filename
operator|->
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|prev
operator|=
name|cf
operator|->
name|conf_file
expr_stmt|;
name|ngx_test_null
argument_list|(
name|cf
operator|->
name|conf_file
argument_list|,
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_conf_file_t
argument_list|)
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_stat_fd
argument_list|(
name|fd
argument_list|,
operator|&
name|cf
operator|->
name|conf_file
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
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"ngx_conf_file: "
name|ngx_stat_fd_n
literal|" %s failed"
argument_list|,
name|filename
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
name|ngx_test_null
argument_list|(
name|cf
operator|->
name|conf_file
operator|->
name|hunk
argument_list|,
name|ngx_create_temp_hunk
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
literal|1024
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
argument_list|,
name|NGX_CONF_ERROR
argument_list|)
expr_stmt|;
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|fd
operator|=
name|fd
expr_stmt|;
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|len
operator|=
name|filename
operator|->
name|len
expr_stmt|;
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
operator|=
name|filename
operator|->
name|data
expr_stmt|;
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|log
operator|=
name|cf
operator|->
name|log
expr_stmt|;
empty_stmt|;
name|cf
operator|->
name|conf_file
operator|->
name|line
operator|=
literal|1
expr_stmt|;
block|}
for|for
control|(
init|;
condition|;
control|)
block|{
name|rc
operator|=
name|ngx_conf_read_token
argument_list|(
name|cf
argument_list|)
expr_stmt|;
comment|/* NGX_OK, NGX_ERROR, NGX_CONF_FILE_DONE, NGX_CONF_BLOCK_DONE */
if|#
directive|if
literal|0
block_content|ngx_log_debug(cf->log, "token %d" _ rc);
endif|#
directive|endif
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|rc
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_CONF_OK
return|;
block|}
if|if
condition|(
name|cf
operator|->
name|handler
condition|)
block|{
if|if
condition|(
call|(
modifier|*
name|cf
operator|->
name|handler
call|)
argument_list|(
name|cf
argument_list|)
operator|==
name|NGX_CONF_ERROR
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
continue|continue;
block|}
name|name
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
name|found
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
operator|!
name|found
operator|&&
name|ngx_modules
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_modules
index|[
name|i
index|]
operator|->
name|type
operator|!=
name|NGX_CONF_MODULE_TYPE
operator|&&
name|ngx_modules
index|[
name|i
index|]
operator|->
name|type
operator|!=
name|cf
operator|->
name|type
condition|)
block|{
continue|continue;
block|}
name|cmd
operator|=
name|ngx_modules
index|[
name|i
index|]
operator|->
name|commands
expr_stmt|;
if|if
condition|(
name|cmd
operator|==
name|NULL
condition|)
block|{
continue|continue;
block|}
while|while
condition|(
name|cmd
operator|->
name|name
operator|.
name|len
condition|)
block|{
if|if
condition|(
name|name
operator|->
name|len
operator|==
name|cmd
operator|->
name|name
operator|.
name|len
operator|&&
name|ngx_strcmp
argument_list|(
name|name
operator|->
name|data
argument_list|,
name|cmd
operator|->
name|name
operator|.
name|data
argument_list|)
operator|==
literal|0
condition|)
block|{
if|#
directive|if
literal|0
block_content|ngx_log_debug(cf->log, "command '%s'" _ cmd->name.data);
endif|#
directive|endif
if|if
condition|(
operator|!
operator|(
name|cmd
operator|->
name|type
operator|&
name|NGX_CONF_ANY
operator|)
operator|&&
operator|!
operator|(
name|cmd
operator|->
name|type
operator|&
name|argument_number
index|[
name|cf
operator|->
name|args
operator|->
name|nelts
operator|-
literal|1
index|]
operator|)
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"invalid number arguments in "
literal|"directive \"%s\" in %s:%d"
argument_list|,
name|name
operator|->
name|data
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|conf
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
name|cf
operator|->
name|ctx
condition|)
block|{
name|pconf
operator|=
operator|*
operator|(
name|void
operator|*
operator|*
operator|)
operator|(
operator|(
name|char
operator|*
operator|)
name|cf
operator|->
name|ctx
operator|+
name|cmd
operator|->
name|conf
operator|)
expr_stmt|;
if|if
condition|(
name|pconf
condition|)
block|{
name|conf
operator|=
name|pconf
index|[
name|ngx_modules
index|[
name|i
index|]
operator|->
name|index
index|]
expr_stmt|;
block|}
block|}
name|rv
operator|=
name|cmd
operator|->
name|set
argument_list|(
name|cf
argument_list|,
name|cmd
argument_list|,
name|conf
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block_content|ngx_log_debug(cf->log, "rv: %d" _ rv);
endif|#
directive|endif
if|if
condition|(
name|rv
operator|==
name|NGX_CONF_OK
condition|)
block|{
name|found
operator|=
literal|1
expr_stmt|;
break|break;
block|}
if|else if
condition|(
name|rv
operator|==
name|NGX_CONF_ERROR
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
else|else
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"%s"
argument_list|,
name|rv
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
name|cmd
operator|++
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|found
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"unknown directive \"%s\" in %s:%d"
argument_list|,
name|name
operator|->
name|data
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
if|if
condition|(
name|filename
condition|)
block|{
name|cf
operator|->
name|conf_file
operator|=
name|prev
expr_stmt|;
if|if
condition|(
name|ngx_close_file
argument_list|(
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|cf
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" %s failed"
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_conf_read_token (ngx_conf_t * cf)
specifier|static
name|int
name|ngx_conf_read_token
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|char
modifier|*
name|start
decl_stmt|,
name|ch
decl_stmt|,
modifier|*
name|src
decl_stmt|,
modifier|*
name|dst
decl_stmt|;
name|int
name|len
decl_stmt|;
name|int
name|found
decl_stmt|,
name|need_space
decl_stmt|,
name|last_space
decl_stmt|,
name|sharp_comment
decl_stmt|;
name|int
name|quoted
decl_stmt|,
name|s_quoted
decl_stmt|,
name|d_quoted
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|ngx_str_t
modifier|*
name|word
decl_stmt|;
name|ngx_hunk_t
modifier|*
name|h
decl_stmt|;
name|found
operator|=
literal|0
expr_stmt|;
name|need_space
operator|=
literal|0
expr_stmt|;
name|last_space
operator|=
literal|1
expr_stmt|;
name|sharp_comment
operator|=
literal|0
expr_stmt|;
name|quoted
operator|=
name|s_quoted
operator|=
name|d_quoted
operator|=
literal|0
expr_stmt|;
name|cf
operator|->
name|args
operator|->
name|nelts
operator|=
literal|0
expr_stmt|;
name|h
operator|=
name|cf
operator|->
name|conf_file
operator|->
name|hunk
expr_stmt|;
name|start
operator|=
name|h
operator|->
name|pos
operator|.
name|mem
expr_stmt|;
if|#
directive|if
literal|0
block_content|ngx_log_debug(cf->log, "TOKEN START");
endif|#
directive|endif
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|h
operator|->
name|pos
operator|.
name|mem
operator|>=
name|h
operator|->
name|last
operator|.
name|mem
condition|)
block|{
if|if
condition|(
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|offset
operator|>=
name|ngx_file_size
argument_list|(
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|info
argument_list|)
condition|)
block|{
return|return
name|NGX_CONF_FILE_DONE
return|;
block|}
if|if
condition|(
name|h
operator|->
name|pos
operator|.
name|mem
operator|-
name|start
condition|)
block|{
name|ngx_memcpy
argument_list|(
name|h
operator|->
name|start
argument_list|,
name|start
argument_list|,
name|h
operator|->
name|pos
operator|.
name|mem
operator|-
name|start
argument_list|)
expr_stmt|;
block|}
name|n
operator|=
name|ngx_read_file
argument_list|(
operator|&
name|cf
operator|->
name|conf_file
operator|->
name|file
argument_list|,
name|h
operator|->
name|start
operator|+
operator|(
name|h
operator|->
name|pos
operator|.
name|mem
operator|-
name|start
operator|)
argument_list|,
name|h
operator|->
name|end
operator|-
operator|(
name|h
operator|->
name|start
operator|+
operator|(
name|h
operator|->
name|pos
operator|.
name|mem
operator|-
name|start
operator|)
operator|)
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|offset
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|h
operator|->
name|pos
operator|.
name|mem
operator|=
name|h
operator|->
name|start
operator|+
operator|(
name|h
operator|->
name|pos
operator|.
name|mem
operator|-
name|start
operator|)
expr_stmt|;
name|start
operator|=
name|h
operator|->
name|start
expr_stmt|;
name|h
operator|->
name|last
operator|.
name|mem
operator|=
name|h
operator|->
name|pos
operator|.
name|mem
operator|+
name|n
expr_stmt|;
block|}
name|ch
operator|=
operator|*
name|h
operator|->
name|pos
operator|.
name|mem
operator|++
expr_stmt|;
if|#
directive|if
literal|0
block_content|ngx_log_debug(cf->log, "%d:%d:%d:%d:%d '%c'" _               last_space _ need_space _               quoted _ s_quoted _ d_quoted _ ch);
endif|#
directive|endif
if|if
condition|(
name|ch
operator|==
name|LF
condition|)
block|{
name|cf
operator|->
name|conf_file
operator|->
name|line
operator|++
expr_stmt|;
if|if
condition|(
name|sharp_comment
condition|)
block|{
name|sharp_comment
operator|=
literal|0
expr_stmt|;
block|}
block|}
if|if
condition|(
name|sharp_comment
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|quoted
condition|)
block|{
name|quoted
operator|=
literal|0
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|need_space
condition|)
block|{
if|if
condition|(
name|ch
operator|==
literal|' '
operator|||
name|ch
operator|==
literal|'\t'
operator|||
name|ch
operator|==
name|CR
operator|||
name|ch
operator|==
name|LF
condition|)
block|{
name|last_space
operator|=
literal|1
expr_stmt|;
name|need_space
operator|=
literal|0
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|ch
operator|==
literal|';'
operator|||
name|ch
operator|==
literal|'{'
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|last_space
condition|)
block|{
if|if
condition|(
name|ch
operator|==
literal|' '
operator|||
name|ch
operator|==
literal|'\t'
operator|||
name|ch
operator|==
name|CR
operator|||
name|ch
operator|==
name|LF
condition|)
block|{
continue|continue;
block|}
name|start
operator|=
name|h
operator|->
name|pos
operator|.
name|mem
operator|-
literal|1
expr_stmt|;
switch|switch
condition|(
name|ch
condition|)
block|{
case|case
literal|';'
case|:
case|case
literal|'{'
case|:
if|if
condition|(
name|cf
operator|->
name|args
operator|->
name|nelts
operator|==
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"unexpected '%c' in %s:%d"
argument_list|,
name|ch
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
case|case
literal|'}'
case|:
if|if
condition|(
name|cf
operator|->
name|args
operator|->
name|nelts
operator|>
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"unexpected '}' in %s:%d"
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|file
operator|.
name|name
operator|.
name|data
argument_list|,
name|cf
operator|->
name|conf_file
operator|->
name|line
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_CONF_BLOCK_DONE
return|;
case|case
literal|'#'
case|:
name|sharp_comment
operator|=
literal|1
expr_stmt|;
continue|continue;
case|case
literal|'\\'
case|:
name|quoted
operator|=
literal|1
expr_stmt|;
name|last_space
operator|=
literal|0
expr_stmt|;
continue|continue;
case|case
literal|'"'
case|:
name|start
operator|++
expr_stmt|;
name|d_quoted
operator|=
literal|1
expr_stmt|;
name|last_space
operator|=
literal|0
expr_stmt|;
continue|continue;
case|case
literal|'\''
case|:
name|start
operator|++
expr_stmt|;
name|s_quoted
operator|=
literal|1
expr_stmt|;
name|last_space
operator|=
literal|0
expr_stmt|;
continue|continue;
default|default:
name|last_space
operator|=
literal|0
expr_stmt|;
block|}
block|}
else|else
block|{
if|if
condition|(
name|ch
operator|==
literal|'\\'
condition|)
block|{
name|quoted
operator|=
literal|1
expr_stmt|;
continue|continue;
block|}
if|if
condition|(
name|d_quoted
condition|)
block|{
if|if
condition|(
name|ch
operator|==
literal|'"'
condition|)
block|{
name|d_quoted
operator|=
literal|0
expr_stmt|;
name|need_space
operator|=
literal|1
expr_stmt|;
name|found
operator|=
literal|1
expr_stmt|;
block|}
block|}
if|else if
condition|(
name|s_quoted
condition|)
block|{
if|if
condition|(
name|ch
operator|==
literal|'\''
condition|)
block|{
name|s_quoted
operator|=
literal|0
expr_stmt|;
name|need_space
operator|=
literal|1
expr_stmt|;
name|found
operator|=
literal|1
expr_stmt|;
block|}
block|}
if|else if
condition|(
name|ch
operator|==
literal|' '
operator|||
name|ch
operator|==
literal|'\t'
operator|||
name|ch
operator|==
name|CR
operator|||
name|ch
operator|==
name|LF
operator|||
name|ch
operator|==
literal|';'
operator|||
name|ch
operator|==
literal|'{'
condition|)
block|{
name|last_space
operator|=
literal|1
expr_stmt|;
name|found
operator|=
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|found
condition|)
block|{
name|ngx_test_null
argument_list|(
name|word
argument_list|,
name|ngx_push_array
argument_list|(
name|cf
operator|->
name|args
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|ngx_test_null
argument_list|(
name|word
operator|->
name|data
argument_list|,
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|h
operator|->
name|pos
operator|.
name|mem
operator|-
name|start
operator|+
literal|1
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
for|for
control|(
name|dst
operator|=
name|word
operator|->
name|data
operator|,
name|src
operator|=
name|start
operator|,
name|len
operator|=
literal|0
init|;
name|src
operator|<
name|h
operator|->
name|pos
operator|.
name|mem
operator|-
literal|1
condition|;
name|len
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|src
operator|==
literal|'\\'
condition|)
block|{
name|src
operator|++
expr_stmt|;
block|}
operator|*
name|dst
operator|++
operator|=
operator|*
name|src
operator|++
expr_stmt|;
block|}
operator|*
name|dst
operator|=
literal|'\0'
expr_stmt|;
name|word
operator|->
name|len
operator|=
name|len
expr_stmt|;
if|#
directive|if
literal|0
block_content|ngx_log_debug(cf->log, "FOUND %d:'%s'" _ word->len _ word->data);
endif|#
directive|endif
if|if
condition|(
name|ch
operator|==
literal|';'
operator|||
name|ch
operator|==
literal|'{'
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|found
operator|=
literal|0
expr_stmt|;
block|}
block|}
block|}
block|}
end_function

begin_function
DECL|function|ngx_conf_set_str_slot (ngx_conf_t * cf,ngx_command_t * cmd,char * conf)
name|char
modifier|*
name|ngx_conf_set_str_slot
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
name|ngx_str_t
modifier|*
name|field
decl_stmt|,
modifier|*
name|value
decl_stmt|;
name|field
operator|=
operator|(
name|ngx_str_t
operator|*
operator|)
operator|(
name|conf
operator|+
name|cmd
operator|->
name|offset
operator|)
expr_stmt|;
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
name|field
operator|->
name|len
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|len
expr_stmt|;
name|field
operator|->
name|data
operator|=
name|value
index|[
literal|1
index|]
operator|.
name|data
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_conf_set_size_slot (ngx_conf_t * cf,ngx_command_t * cmd,char * conf)
name|char
modifier|*
name|ngx_conf_set_size_slot
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
name|int
name|size
decl_stmt|;
name|ngx_str_t
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
name|size
operator|=
name|atoi
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|<
literal|0
condition|)
block|{
return|return
literal|"value must be greater or equal to zero"
return|;
block|}
operator|*
operator|(
name|int
operator|*
operator|)
operator|(
name|conf
operator|+
name|cmd
operator|->
name|offset
operator|)
operator|=
name|size
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_conf_set_time_slot (ngx_conf_t * cf,ngx_command_t * cmd,char * conf)
name|char
modifier|*
name|ngx_conf_set_time_slot
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
name|int
name|size
decl_stmt|;
name|ngx_str_t
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
name|size
operator|=
name|atoi
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|<
literal|0
condition|)
block|{
return|return
literal|"value must be greater or equal to zero"
return|;
block|}
operator|*
operator|(
name|int
operator|*
operator|)
operator|(
name|conf
operator|+
name|cmd
operator|->
name|offset
operator|)
operator|=
name|size
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

