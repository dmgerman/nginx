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

begin_function
DECL|function|ngx_cpystrn (char * dst,char * src,size_t n)
name|char
modifier|*
name|ngx_cpystrn
parameter_list|(
name|char
modifier|*
name|dst
parameter_list|,
name|char
modifier|*
name|src
parameter_list|,
name|size_t
name|n
parameter_list|)
block|{
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
name|dst
return|;
block|}
for|for
control|(
comment|/* void */
init|;
operator|--
name|n
condition|;
name|dst
operator|++
operator|,
name|src
operator|++
control|)
block|{
operator|*
name|dst
operator|=
operator|*
name|src
expr_stmt|;
if|if
condition|(
operator|*
name|dst
operator|==
literal|'\0'
condition|)
block|{
return|return
name|dst
return|;
block|}
block|}
operator|*
name|dst
operator|=
literal|'\0'
expr_stmt|;
return|return
name|dst
return|;
block|}
end_function

begin_function
DECL|function|ngx_rstrncmp (char * s1,char * s2,size_t n)
name|int
name|ngx_rstrncmp
parameter_list|(
name|char
modifier|*
name|s1
parameter_list|,
name|char
modifier|*
name|s2
parameter_list|,
name|size_t
name|n
parameter_list|)
block|{
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
literal|0
return|;
block|}
name|n
operator|--
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|s1
index|[
name|n
index|]
operator|!=
name|s2
index|[
name|n
index|]
condition|)
block|{
return|return
operator|(
name|u_char
operator|)
name|s1
index|[
name|n
index|]
operator|-
operator|(
name|u_char
operator|)
name|s2
index|[
name|n
index|]
return|;
block|}
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
literal|0
return|;
block|}
name|n
operator|--
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_atoi (char * line,size_t n)
name|int
name|ngx_atoi
parameter_list|(
name|char
modifier|*
name|line
parameter_list|,
name|size_t
name|n
parameter_list|)
block|{
name|int
name|value
decl_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
for|for
control|(
name|value
operator|=
literal|0
init|;
name|n
operator|--
condition|;
name|line
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|line
argument_list|<
literal|'0'
operator|||
operator|*
name|line
argument_list|>
literal|'9'
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|value
operator|=
name|value
operator|*
literal|10
operator|+
operator|(
operator|*
name|line
operator|-
literal|'0'
operator|)
expr_stmt|;
block|}
if|if
condition|(
name|value
operator|<
literal|0
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
else|else
block|{
return|return
name|value
return|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_print_md5 (char * text,u_char * md5)
name|void
name|ngx_print_md5
parameter_list|(
name|char
modifier|*
name|text
parameter_list|,
name|u_char
modifier|*
name|md5
parameter_list|)
block|{
name|ngx_snprintf
argument_list|(
name|text
argument_list|,
literal|33
argument_list|,
literal|"%0x%0x%0x%0x%0x%0x%0x%0x%0x%0x%0x%0x%0x%0x%0x%0x"
argument_list|,
name|md5
index|[
literal|0
index|]
argument_list|,
name|md5
index|[
literal|1
index|]
argument_list|,
name|md5
index|[
literal|2
index|]
argument_list|,
name|md5
index|[
literal|3
index|]
argument_list|,
name|md5
index|[
literal|4
index|]
argument_list|,
name|md5
index|[
literal|5
index|]
argument_list|,
name|md5
index|[
literal|6
index|]
argument_list|,
name|md5
index|[
literal|7
index|]
argument_list|,
name|md5
index|[
literal|8
index|]
argument_list|,
name|md5
index|[
literal|9
index|]
argument_list|,
name|md5
index|[
literal|10
index|]
argument_list|,
name|md5
index|[
literal|11
index|]
argument_list|,
name|md5
index|[
literal|12
index|]
argument_list|,
name|md5
index|[
literal|13
index|]
argument_list|,
name|md5
index|[
literal|14
index|]
argument_list|,
name|md5
index|[
literal|15
index|]
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
unit|char *ngx_psprintf(ngx_pool_t *p, const char *fmt, ...) {     va_list    args;      va_start(args, fmt);      while (*fmt) {          switch(*fmt++) {          case '%':              switch(*fmt++) {              case 's':                  s = va_arg(args, char *);                  n += ngx_strlen(s);                  break;               default:                  n++;          }          default:              n++;          }     }      str = ngx_palloc(p, n);      va_start(args, fmt);      for (i = 0; i< n; i++) {          switch(*fmt++) {          case '%':              switch(*fmt++) {              case 's':                  s = va_arg(args, char *);                  while (str[i++] = s);                  break;               default:                  n++;          }          default:              str[i] = *fmt;          }     }      len += ngx_vsnprintf(errstr + len, sizeof(errstr) - len - 1, fmt, args);      va_end(args);  }
endif|#
directive|endif
end_endif

end_unit

