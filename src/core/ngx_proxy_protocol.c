begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Roman Arutyunyan  * Copyright (C) Nginx, Inc.  */
end_comment

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
name|u_char
modifier|*
DECL|function|ngx_proxy_protocol_parse (ngx_connection_t * c,u_char * buf,u_char * last)
name|ngx_proxy_protocol_parse
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|u_char
modifier|*
name|last
parameter_list|)
block|{
name|size_t
name|len
decl_stmt|;
name|u_char
name|ch
decl_stmt|,
modifier|*
name|p
decl_stmt|,
modifier|*
name|addr
decl_stmt|;
name|p
operator|=
name|buf
expr_stmt|;
name|len
operator|=
name|last
operator|-
name|buf
expr_stmt|;
if|if
condition|(
name|len
operator|<
literal|8
operator|||
name|ngx_strncmp
argument_list|(
name|p
argument_list|,
literal|"PROXY "
argument_list|,
literal|6
argument_list|)
operator|!=
literal|0
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
name|p
operator|+=
literal|6
expr_stmt|;
name|len
operator|-=
literal|6
expr_stmt|;
if|if
condition|(
name|len
operator|>=
literal|7
operator|&&
name|ngx_strncmp
argument_list|(
name|p
argument_list|,
literal|"UNKNOWN"
argument_list|,
literal|7
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"PROXY protocol unknown protocol"
argument_list|)
expr_stmt|;
name|p
operator|+=
literal|7
expr_stmt|;
goto|goto
name|skip
goto|;
block|}
if|if
condition|(
name|len
operator|<
literal|5
operator|||
name|ngx_strncmp
argument_list|(
name|p
argument_list|,
literal|"TCP"
argument_list|,
literal|3
argument_list|)
operator|!=
literal|0
operator|||
operator|(
name|p
index|[
literal|3
index|]
operator|!=
literal|'4'
operator|&&
name|p
index|[
literal|3
index|]
operator|!=
literal|'6'
operator|)
operator|||
name|p
index|[
literal|4
index|]
operator|!=
literal|' '
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
name|p
operator|+=
literal|5
expr_stmt|;
name|addr
operator|=
name|p
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
if|if
condition|(
name|p
operator|==
name|last
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
name|ch
operator|=
operator|*
name|p
operator|++
expr_stmt|;
if|if
condition|(
name|ch
operator|==
literal|' '
condition|)
block|{
break|break;
block|}
if|if
condition|(
name|ch
operator|!=
literal|':'
operator|&&
name|ch
operator|!=
literal|'.'
operator|&&
operator|(
name|ch
argument_list|<
literal|'a'
operator|||
name|ch
argument_list|>
literal|'f'
operator|)
operator|&&
operator|(
name|ch
argument_list|<
literal|'A'
operator|||
name|ch
argument_list|>
literal|'F'
operator|)
operator|&&
operator|(
name|ch
argument_list|<
literal|'0'
operator|||
name|ch
argument_list|>
literal|'9'
operator|)
condition|)
block|{
goto|goto
name|invalid
goto|;
block|}
block|}
name|len
operator|=
name|p
operator|-
name|addr
operator|-
literal|1
expr_stmt|;
name|c
operator|->
name|proxy_protocol_addr
operator|.
name|data
operator|=
name|ngx_pnalloc
argument_list|(
name|c
operator|->
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|c
operator|->
name|proxy_protocol_addr
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|ngx_memcpy
argument_list|(
name|c
operator|->
name|proxy_protocol_addr
operator|.
name|data
argument_list|,
name|addr
argument_list|,
name|len
argument_list|)
expr_stmt|;
name|c
operator|->
name|proxy_protocol_addr
operator|.
name|len
operator|=
name|len
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"PROXY protocol address: \"%V\""
argument_list|,
operator|&
name|c
operator|->
name|proxy_protocol_addr
argument_list|)
expr_stmt|;
name|skip
label|:
for|for
control|(
comment|/* void */
init|;
name|p
operator|<
name|last
operator|-
literal|1
condition|;
name|p
operator|++
control|)
block|{
if|if
condition|(
name|p
index|[
literal|0
index|]
operator|==
name|CR
operator|&&
name|p
index|[
literal|1
index|]
operator|==
name|LF
condition|)
block|{
return|return
name|p
operator|+
literal|2
return|;
block|}
block|}
name|invalid
label|:
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|c
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"broken header: \"%*s\""
argument_list|,
operator|(
name|size_t
operator|)
operator|(
name|last
operator|-
name|buf
operator|)
argument_list|,
name|buf
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

