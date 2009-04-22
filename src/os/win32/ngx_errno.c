begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_comment
comment|/*  * TODO:  *   add WSA error messages for NT and 98  */
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

begin_decl_stmt
DECL|variable|wsa_errors
specifier|static
name|ngx_str_t
name|wsa_errors
index|[]
init|=
block|{
name|ngx_string
argument_list|(
literal|"An invalid argument was supplied"
argument_list|)
block|,
comment|/* WSAEINVAL 10022 */
name|ngx_string
argument_list|(
literal|"Too many open sockets"
argument_list|)
block|,
comment|/* WSAEMFILE 10023 */
name|ngx_null_string
block|,
comment|/* 10024 */
name|ngx_null_string
block|,
comment|/* 10025 */
name|ngx_null_string
block|,
comment|/* 10026 */
name|ngx_null_string
block|,
comment|/* 10027 */
name|ngx_null_string
block|,
comment|/* 10028 */
name|ngx_null_string
block|,
comment|/* 10029 */
name|ngx_null_string
block|,
comment|/* 10030 */
name|ngx_null_string
block|,
comment|/* 10031 */
name|ngx_null_string
block|,
comment|/* 10032 */
name|ngx_null_string
block|,
comment|/* 10033 */
name|ngx_null_string
block|,
comment|/* 10034 */
comment|/* WSAEWOULDBLOCK 10035 */
name|ngx_string
argument_list|(
literal|"A non-blocking socket operation could not be completed "
literal|"immediately"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 10036 */
name|ngx_null_string
block|,
comment|/* 10037 */
comment|/* WSAENOTSOCK 10038 */
name|ngx_string
argument_list|(
literal|"An operation was attempted on something that is not a socket"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 10039 */
name|ngx_null_string
block|,
comment|/* 10040 */
name|ngx_null_string
block|,
comment|/* 10041 */
comment|/* WSAENOPROTOOPT 10042 */
name|ngx_string
argument_list|(
literal|"An unknown, invalid, or unsupported option or level was "
literal|"specified in a getsockopt or setsockopt call"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 10043 */
name|ngx_null_string
block|,
comment|/* 10044 */
name|ngx_null_string
block|,
comment|/* 10045 */
name|ngx_null_string
block|,
comment|/* 10046 */
name|ngx_null_string
block|,
comment|/* 10047 */
name|ngx_null_string
block|,
comment|/* 10048 */
name|ngx_null_string
block|,
comment|/* 10049 */
name|ngx_null_string
block|,
comment|/* 10050 */
name|ngx_null_string
block|,
comment|/* 10051 */
name|ngx_null_string
block|,
comment|/* 10052 */
name|ngx_null_string
block|,
comment|/* 10053 */
comment|/* WSAECONNRESET 10054 */
name|ngx_string
argument_list|(
literal|"An existing connection was forcibly closed by the remote host"
argument_list|)
block|,
comment|/* WSAENOBUFS 10055 */
name|ngx_string
argument_list|(
literal|"An operation on a socket could not be performed because "
literal|"the system lacked sufficient buffer space or "
literal|"because a queue was full"
argument_list|)
block|,
comment|/* WSAEISCONN 10056 */
name|ngx_string
argument_list|(
literal|"A connect request was made on an already connected socket"
argument_list|)
block|,
comment|/* WSAENOTCONN 10057 */
name|ngx_string
argument_list|(
literal|"A request to send or receive data was disallowed because"
literal|"the socket is not connected and (when sending on a datagram "
literal|"socket using a sendto call) no address was supplied"
argument_list|)
block|,
name|ngx_null_string
block|,
comment|/* 10058 */
name|ngx_null_string
block|,
comment|/* 10059 */
comment|/* WSAETIMEDOUT 10060 */
name|ngx_string
argument_list|(
literal|"A connection attempt failed because the connected party "
literal|"did not properly respond after a period of time, "
literal|"or established connection failed because connected host "
literal|"has failed to respond"
argument_list|)
block|,
comment|/* WSAECONNREFUSED 10061 */
name|ngx_string
argument_list|(
literal|"No connection could be made because the target machine "
literal|"actively refused it"
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|u_char
modifier|*
DECL|function|ngx_strerror_r (ngx_err_t err,u_char * errstr,size_t size)
name|ngx_strerror_r
parameter_list|(
name|ngx_err_t
name|err
parameter_list|,
name|u_char
modifier|*
name|errstr
parameter_list|,
name|size_t
name|size
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
name|u_int
name|len
decl_stmt|;
name|ngx_err_t
name|format_error
decl_stmt|;
if|if
condition|(
name|size
operator|==
literal|0
condition|)
block|{
return|return
name|errstr
return|;
block|}
name|len
operator|=
name|FormatMessage
argument_list|(
name|FORMAT_MESSAGE_FROM_SYSTEM
operator||
name|FORMAT_MESSAGE_IGNORE_INSERTS
argument_list|,
name|NULL
argument_list|,
name|err
argument_list|,
name|MAKELANGID
argument_list|(
name|LANG_ENGLISH
argument_list|,
name|SUBLANG_DEFAULT
argument_list|)
argument_list|,
operator|(
name|char
operator|*
operator|)
name|errstr
argument_list|,
name|size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|==
literal|0
condition|)
block|{
name|format_error
operator|=
name|GetLastError
argument_list|()
expr_stmt|;
if|if
condition|(
name|format_error
operator|==
name|ERROR_MR_MID_NOT_FOUND
condition|)
block|{
name|n
operator|=
name|err
operator|-
name|WSAEINVAL
expr_stmt|;
if|if
condition|(
name|n
operator|>=
literal|0
operator|&&
name|n
operator|<=
name|WSAECONNREFUSED
operator|-
name|WSAEINVAL
condition|)
block|{
name|len
operator|=
name|wsa_errors
index|[
name|n
index|]
operator|.
name|len
expr_stmt|;
if|if
condition|(
name|len
condition|)
block|{
if|if
condition|(
name|len
operator|>
name|size
condition|)
block|{
name|len
operator|=
name|size
expr_stmt|;
block|}
name|ngx_memcpy
argument_list|(
name|errstr
argument_list|,
name|wsa_errors
index|[
name|n
index|]
operator|.
name|data
argument_list|,
name|len
argument_list|)
expr_stmt|;
return|return
name|errstr
operator|+
name|len
return|;
block|}
block|}
block|}
return|return
name|ngx_snprintf
argument_list|(
name|errstr
argument_list|,
name|size
argument_list|,
literal|"FormatMessage() error:(%d)"
argument_list|,
name|format_error
argument_list|)
return|;
block|}
comment|/* remove ".\r\n\0" */
while|while
condition|(
name|errstr
index|[
name|len
index|]
operator|==
literal|'\0'
operator|||
name|errstr
index|[
name|len
index|]
operator|==
name|CR
operator|||
name|errstr
index|[
name|len
index|]
operator|==
name|LF
operator|||
name|errstr
index|[
name|len
index|]
operator|==
literal|'.'
condition|)
block|{
operator|--
name|len
expr_stmt|;
block|}
return|return
operator|&
name|errstr
index|[
operator|++
name|len
index|]
return|;
block|}
end_function

end_unit

