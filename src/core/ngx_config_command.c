begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|typedef struct ngx_conf_file_t {     ngx_fd_t  fd;     char     *name;     int       line;     char     *pos; };  typedef struct ngx_conf_t {     char             *name;     ngx_array_t      *args;      ngx_conf_file_t  *file;     ngx_log_t        *log;      void *context;             # ngx_http_conf_t };  static int argument_number[] = {     NGX_CONF_NOARGS,     NGX_CONF_TAKE1,     NGX_CONF_TAKE2,     NGX_CONF_TAKE3 };   ngx_conf_parse(cf, container, filename) {     create cf;      *conatiner(cf);      if (filename) {         open;     }      for ( ;; ) {         rc = ngx_conf_read_token(cf);  NGX_OK, NGX_ERROR, NGX_CONF_FILE_DONE, NGX_CONF_BLOCK_DONE          if (rc != NGX_OK)             return rc;  "listen address:port;" "location /images/ {"          cmd = ngx_conf_find_token(cf);         if (cmd == NULL) {             ngx_log_error(NGX_LOG_EMERG, cf->log, 0,                           "unknown directive \"%s\" in %s:%d",                           cf->name, cf->file->name, cf->file->line);             return NGX_ERROR;         }          if (cmd->type == NGX_CONF_CONTAINER) {             ngx_conf_parse(cf, cmd->container, NULL);          } else if (cmd->type == NGX_CONF_FLAG) {              if (cf->args->nelts != 1) {                 ngx_log_error(NGX_LOG_EMERG, cf->log, 0,                               "invalid number of arguments "                               "in directive \"%s\" in %s:%d",                               cf->name, cf->file->name, cf->file->line);                 return NGX_ERROR;             }              if (ngx_strcasecmp(cf->args->elts[0], "on") == 0) {                 flag = 1;              } else if (ngx_strcasecmp(cf->args->elts[0], "off") == 0) {                 flag = 0;              } else {                 ngx_log_error(NGX_LOG_EMERG, cf->log, 0,                               "invalid flag in directive \"%s\" in %s:%d",                               cf->name, cf->file->name, cf->file->line);                 return NGX_ERROR;             }              rv = cmd->set(cf, cmd->offset, flag);             if (rv) {                  ngx_log_error(NGX_LOG_EMERG, cf->log, 0,                                "%s in directive \"%s\" in %s:%d",                                rv, cf->name, cf->file->name, cf->file->line);                 return NGX_ERROR;             }          } else if (cmd->type& argument_number[args->nelts]) {             rv = cmd->set(cf, cmd->offset, cf->args);             if (rv) {                  ngx_log_error(NGX_LOG_EMERG, cf->log, 0,                                "%s in directive \"%s\" in %s:%d",                                rv, cf->name, cf->file->name, cf->file->line);                 return NGX_ERROR;             }          } else {             ngx_log_error(NGX_LOG_EMERG, cf->log, 0,                           "invalid number of arguments "                           "in directive \"%s\" in %s:%d",                           cf->name, cf->file->name, cf->file->line);             return NGX_ERROR;         }     }      if (filename) {         close;     } }      int ngx_conf_read_token(ngx_conf_t *cf) {      need_space = 0;     last_space = 1;     len = 0;     quoted = s_quoted = d_quoted = 0;      cf->args->nelts = 0;      for (
comment|/* void */
end_comment

begin_comment
unit|; cf->pos< cf->end; cf->pos++) {          ch = *cf->pos;          if (ch == LF)             cf->line++;          if (quoted) {             quoted = 0;             continue;         }          len++;          if (ch = '\\') {             quoted = 1;             continue;         }          if (d_quoted) {              if (ch == '"') {                 d_qouted = 0;                 need_space = 1;                 last_space = 1;                 continue;             }          } else if (s_quoted) {              if (ch == '\'') {                 s_qouted = 0;                 need_space = 1;                 last_space = 1;                 continue;             }          } else {              if (ch == ' ' || ch == '\t' || ch == CR || ch == LF) {                 ngx_test_null(word, ngx_push_array(cf->args), NGX_ERRROR);                 ngx_test_null(*word, ngx_palloc(cf->temp_pool, len + 1),                               NGX_ERROR);                  for (dst = *word, src = cf->start; src< cf->pos;
comment|/* void */
end_comment

begin_endif
unit|) {                     if (*src == '\\')                         src++;                     *dst++ = *src++;                 }                 *dst = '\0';                  need_space = 0;                 last_space = 1;                 continue;             }              if (need_space) {                 return NGX_ERROR;             }              if (ch == ';')                 return NGX_OK;              if (ch == '{')                 return NGX_OK;              if (ch == '}')                 return NGX_BLOCK_DONE;              if (last_space) {                 if (ch == '"') {                     d_qouted = 1;                     continue;                 }                  if (ch == '\'') {                     s_qouted = 1;                     continue;                 }             }              last_space = 0;         }     } }  container     server     location     module     if  http_conf current server           current location   ngx_conf_t *ngx_conf_open(char *filename, ngx_log_t *log) {     ngx_cf->fd = ngx_open_file(config, NGX_FILE_RDONLY);     if (ngx_conf->fd == -1) {         ngx_log_error(NGX_LOG_EMERG, log, ngx_errno,                       "ngx_conf_open: "                       ngx_open_file_n " %s failed", filename);          return NULL;     }      ngx_conf->name = filename;     ngx_conf->log = log;     return ngx_conf; }  void ngx_conf_close(ngx_conf_t *cf) {     if (ngx_close_file(cf->fd) == -1) {         ngx_log_error(NGX_LOG_ERR, cf->log, ngx_errno,                       ngx_close_file_n " %s failed", cf->name);     }      cf->fd = -1; }
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_conf_set_size_slot (char * conf,int offset,char * value)
name|char
modifier|*
name|ngx_conf_set_size_slot
parameter_list|(
name|char
modifier|*
name|conf
parameter_list|,
name|int
name|offset
parameter_list|,
name|char
modifier|*
name|value
parameter_list|)
block|{
name|int
name|size
decl_stmt|;
name|size
operator|=
name|atoi
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|<
literal|0
condition|)
return|return
literal|"value must be greater or equal to zero"
return|;
operator|*
operator|(
name|int
operator|*
operator|)
operator|(
name|conf
operator|+
name|offset
operator|)
operator|=
name|size
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
DECL|function|ngx_conf_set_time_slot (char * conf,int offset,char * value)
name|char
modifier|*
name|ngx_conf_set_time_slot
parameter_list|(
name|char
modifier|*
name|conf
parameter_list|,
name|int
name|offset
parameter_list|,
name|char
modifier|*
name|value
parameter_list|)
block|{
name|int
name|size
decl_stmt|;
name|size
operator|=
name|atoi
argument_list|(
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|<
literal|0
condition|)
return|return
literal|"value must be greater or equal to zero"
return|;
operator|*
operator|(
name|int
operator|*
operator|)
operator|(
name|conf
operator|+
name|offset
operator|)
operator|=
name|size
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

