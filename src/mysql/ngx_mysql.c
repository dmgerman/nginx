begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_comment
comment|/* the library supports the subset of the MySQL 4.1+ protocol (version 10) */
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

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_connect.h>
end_include

begin_include
include|#
directive|include
file|<ngx_mysql.h>
end_include

begin_include
include|#
directive|include
file|<ngx_sha1.h>
end_include

begin_define
DECL|macro|NGX_MYSQL_LONG_PASSWORD
define|#
directive|define
name|NGX_MYSQL_LONG_PASSWORD
value|0x0001
end_define

begin_define
DECL|macro|NGX_MYSQL_CONNECT_WITH_DB
define|#
directive|define
name|NGX_MYSQL_CONNECT_WITH_DB
value|0x0008
end_define

begin_define
DECL|macro|NGX_MYSQL_PROTOCOL_41
define|#
directive|define
name|NGX_MYSQL_PROTOCOL_41
value|0x0200
end_define

begin_define
DECL|macro|NGX_MYSQL_SECURE_CONNECTION
define|#
directive|define
name|NGX_MYSQL_SECURE_CONNECTION
value|0x8000
end_define

begin_define
DECL|macro|NGX_MYSQL_CMD_QUERY
define|#
directive|define
name|NGX_MYSQL_CMD_QUERY
value|3
end_define

begin_typedef
DECL|struct|__anon2747e6aa0108
typedef|typedef
struct|struct
block|{
DECL|member|pktlen
name|u_char
name|pktlen
index|[
literal|3
index|]
decl_stmt|;
DECL|member|pktn
name|u_char
name|pktn
decl_stmt|;
DECL|member|protocol
name|u_char
name|protocol
decl_stmt|;
DECL|member|version
name|u_char
name|version
index|[
literal|1
index|]
decl_stmt|;
comment|/* NULL-terminated string */
DECL|typedef|ngx_mysql_greeting1_pkt_t
block|}
name|ngx_mysql_greeting1_pkt_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2747e6aa0208
typedef|typedef
struct|struct
block|{
DECL|member|thread
name|u_char
name|thread
index|[
literal|4
index|]
decl_stmt|;
DECL|member|salt1
name|u_char
name|salt1
index|[
literal|9
index|]
decl_stmt|;
DECL|member|capacity
name|u_char
name|capacity
index|[
literal|2
index|]
decl_stmt|;
DECL|member|charset
name|u_char
name|charset
decl_stmt|;
DECL|member|status
name|u_char
name|status
index|[
literal|2
index|]
decl_stmt|;
DECL|member|zero
name|u_char
name|zero
index|[
literal|13
index|]
decl_stmt|;
DECL|member|salt2
name|u_char
name|salt2
index|[
literal|13
index|]
decl_stmt|;
DECL|typedef|ngx_mysql_greeting2_pkt_t
block|}
name|ngx_mysql_greeting2_pkt_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2747e6aa0308
typedef|typedef
struct|struct
block|{
DECL|member|pktlen
name|u_char
name|pktlen
index|[
literal|3
index|]
decl_stmt|;
DECL|member|pktn
name|u_char
name|pktn
decl_stmt|;
DECL|member|capacity
name|u_char
name|capacity
index|[
literal|4
index|]
decl_stmt|;
DECL|member|max_packet
name|u_char
name|max_packet
index|[
literal|4
index|]
decl_stmt|;
DECL|member|charset
name|u_char
name|charset
decl_stmt|;
DECL|member|zero
name|u_char
name|zero
index|[
literal|23
index|]
decl_stmt|;
DECL|member|login
name|u_char
name|login
index|[
literal|1
index|]
decl_stmt|;
comment|/* NULL-terminated string */
comment|/*   * u_char      passwd_len;         0 if no password   * u_char      passwd[20];   *   * u_char      database[1];        NULL-terminated string   */
DECL|typedef|ngx_mysql_auth_pkt_t
block|}
name|ngx_mysql_auth_pkt_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2747e6aa0408
typedef|typedef
struct|struct
block|{
DECL|member|pktlen
name|u_char
name|pktlen
index|[
literal|3
index|]
decl_stmt|;
DECL|member|pktn
name|u_char
name|pktn
decl_stmt|;
DECL|member|fields
name|u_char
name|fields
decl_stmt|;
DECL|typedef|ngx_mysql_response_pkt_t
block|}
name|ngx_mysql_response_pkt_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2747e6aa0508
typedef|typedef
struct|struct
block|{
DECL|member|pktlen
name|u_char
name|pktlen
index|[
literal|3
index|]
decl_stmt|;
DECL|member|pktn
name|u_char
name|pktn
decl_stmt|;
DECL|member|err
name|u_char
name|err
decl_stmt|;
DECL|member|code
name|u_char
name|code
index|[
literal|2
index|]
decl_stmt|;
DECL|member|message
name|u_char
name|message
index|[
literal|1
index|]
decl_stmt|;
comment|/* string */
DECL|typedef|ngx_mysql_error_pkt_t
block|}
name|ngx_mysql_error_pkt_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2747e6aa0608
typedef|typedef
struct|struct
block|{
DECL|member|pktlen
name|u_char
name|pktlen
index|[
literal|3
index|]
decl_stmt|;
DECL|member|pktn
name|u_char
name|pktn
decl_stmt|;
DECL|member|command
name|u_char
name|command
decl_stmt|;
DECL|member|arg
name|u_char
name|arg
index|[
literal|1
index|]
decl_stmt|;
comment|/* string */
DECL|typedef|ngx_mysql_command_pkt_t
block|}
name|ngx_mysql_command_pkt_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|void
name|ngx_mysql_read_server_greeting
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_mysql_empty_handler
parameter_list|(
name|ngx_event_t
modifier|*
name|wev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_mysql_read_auth_result
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_mysql_read_query_result
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_mysql_close
parameter_list|(
name|ngx_mysql_t
modifier|*
name|m
parameter_list|,
name|ngx_int_t
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|ngx_int_t
DECL|function|ngx_mysql_connect (ngx_mysql_t * m)
name|ngx_mysql_connect
parameter_list|(
name|ngx_mysql_t
modifier|*
name|m
parameter_list|)
block|{
name|ngx_int_t
name|rc
decl_stmt|;
if|#
directive|if
literal|0
block_content|if (cached) {         return NGX_OK;     }
endif|#
directive|endif
name|m
operator|->
name|peer
operator|.
name|log
operator|->
name|action
operator|=
literal|"connecting to mysql server"
expr_stmt|;
name|rc
operator|=
name|ngx_event_connect_peer
argument_list|(
operator|&
name|m
operator|->
name|peer
argument_list|)
expr_stmt|;
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
operator|||
name|rc
operator|==
name|NGX_BUSY
operator|||
name|rc
operator|==
name|NGX_DECLINED
condition|)
block|{
return|return
name|rc
return|;
block|}
name|m
operator|->
name|peer
operator|.
name|connection
operator|->
name|data
operator|=
name|m
expr_stmt|;
name|m
operator|->
name|peer
operator|.
name|connection
operator|->
name|read
operator|->
name|handler
operator|=
name|ngx_mysql_read_server_greeting
expr_stmt|;
name|m
operator|->
name|peer
operator|.
name|connection
operator|->
name|write
operator|->
name|handler
operator|=
name|ngx_mysql_empty_handler
expr_stmt|;
name|ngx_add_timer
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
operator|->
name|read
argument_list|,
comment|/* STUB */
literal|5000
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_mysql_read_server_greeting (ngx_event_t * rev)
name|ngx_mysql_read_server_greeting
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
block|{
name|size_t
name|len
decl_stmt|;
name|u_char
modifier|*
name|p
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|capacity
decl_stmt|;
name|ngx_mysql_t
modifier|*
name|m
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_mysql_greeting1_pkt_t
modifier|*
name|gr1
decl_stmt|;
name|ngx_mysql_greeting2_pkt_t
modifier|*
name|gr2
decl_stmt|;
name|ngx_mysql_auth_pkt_t
modifier|*
name|auth
decl_stmt|;
name|ngx_sha1_t
name|sha
decl_stmt|;
name|u_char
name|hash1
index|[
literal|20
index|]
decl_stmt|,
name|hash2
index|[
literal|20
index|]
decl_stmt|;
name|c
operator|=
name|rev
operator|->
name|data
expr_stmt|;
name|m
operator|=
name|c
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|rev
operator|->
name|timedout
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
name|NGX_ETIMEDOUT
argument_list|,
literal|"mysql server %V timed out"
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|m
operator|->
name|buf
operator|==
name|NULL
condition|)
block|{
name|m
operator|->
name|peer
operator|.
name|log
operator|->
name|action
operator|=
literal|"reading mysql server greeting"
expr_stmt|;
name|m
operator|->
name|buf
operator|=
name|ngx_create_temp_buf
argument_list|(
name|m
operator|->
name|pool
argument_list|,
comment|/* STUB */
literal|1024
argument_list|)
expr_stmt|;
if|if
condition|(
name|m
operator|->
name|buf
operator|==
name|NULL
condition|)
block|{
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
block|}
name|n
operator|=
name|ngx_recv
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
argument_list|,
name|m
operator|->
name|buf
operator|->
name|pos
argument_list|,
comment|/* STUB */
literal|1024
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|n
operator|<
literal|5
condition|)
block|{
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
name|gr1
operator|=
operator|(
name|ngx_mysql_greeting1_pkt_t
operator|*
operator|)
name|m
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
if|if
condition|(
name|ngx_m24toh
argument_list|(
name|gr1
operator|->
name|pktlen
argument_list|)
operator|>
name|n
operator|-
literal|4
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql server %V sent incomplete greeting packet"
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|gr1
operator|->
name|protocol
operator|<
literal|10
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql server %V sent unsupported protocol version %ud"
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|,
name|gr1
operator|->
name|protocol
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
name|gr2
operator|=
operator|(
name|ngx_mysql_greeting2_pkt_t
operator|*
operator|)
operator|(
name|gr1
operator|->
name|version
operator|+
name|ngx_strlen
argument_list|(
name|gr1
operator|->
name|version
argument_list|)
operator|+
literal|1
operator|)
expr_stmt|;
name|capacity
operator|=
name|ngx_m16toh
argument_list|(
name|gr2
operator|->
name|capacity
argument_list|)
expr_stmt|;
name|ngx_log_debug8
argument_list|(
name|NGX_LOG_DEBUG_MYSQL
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql version: %ud, \"%s\", thread: %ud, salt: \"%s\", "
literal|"capacity: %Xd, charset: %ud, status: %ud, salt rest \"%s\""
argument_list|,
name|gr1
operator|->
name|protocol
argument_list|,
name|gr1
operator|->
name|version
argument_list|,
name|ngx_m32toh
argument_list|(
name|gr2
operator|->
name|thread
argument_list|)
argument_list|,
name|gr2
operator|->
name|salt1
argument_list|,
name|capacity
argument_list|,
name|gr2
operator|->
name|charset
argument_list|,
name|ngx_m16toh
argument_list|(
name|gr2
operator|->
name|status
argument_list|)
argument_list|,
operator|&
name|gr2
operator|->
name|salt2
argument_list|)
expr_stmt|;
name|capacity
operator|=
name|NGX_MYSQL_LONG_PASSWORD
operator||
name|NGX_MYSQL_CONNECT_WITH_DB
operator||
name|NGX_MYSQL_PROTOCOL_41
operator||
name|NGX_MYSQL_SECURE_CONNECTION
expr_stmt|;
name|len
operator|=
literal|4
operator|+
literal|4
operator|+
literal|4
operator|+
literal|1
operator|+
literal|23
operator|+
name|m
operator|->
name|login
operator|->
name|len
operator|+
literal|1
operator|+
literal|1
operator|+
name|m
operator|->
name|database
operator|->
name|len
operator|+
literal|1
expr_stmt|;
if|if
condition|(
name|m
operator|->
name|passwd
operator|->
name|len
condition|)
block|{
name|len
operator|+=
literal|20
expr_stmt|;
block|}
name|auth
operator|=
name|ngx_pnalloc
argument_list|(
name|m
operator|->
name|pool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|auth
operator|==
name|NULL
condition|)
block|{
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
name|ngx_htom24
argument_list|(
name|auth
operator|->
name|pktlen
argument_list|,
name|len
operator|-
literal|4
argument_list|)
expr_stmt|;
name|auth
operator|->
name|pktn
operator|=
operator|(
name|u_char
operator|)
operator|(
name|gr1
operator|->
name|pktn
operator|+
literal|1
operator|)
expr_stmt|;
name|ngx_htom32
argument_list|(
name|auth
operator|->
name|capacity
argument_list|,
name|capacity
argument_list|)
expr_stmt|;
name|ngx_htom32
argument_list|(
name|auth
operator|->
name|max_packet
argument_list|,
literal|0x01000000
argument_list|)
expr_stmt|;
comment|/* max packet size 2^24 */
name|ngx_memzero
argument_list|(
name|auth
operator|->
name|zero
argument_list|,
literal|24
argument_list|)
expr_stmt|;
name|auth
operator|->
name|charset
operator|=
name|gr2
operator|->
name|charset
expr_stmt|;
name|p
operator|=
name|ngx_copy
argument_list|(
name|auth
operator|->
name|login
argument_list|,
name|m
operator|->
name|login
operator|->
name|data
argument_list|,
name|m
operator|->
name|login
operator|->
name|len
argument_list|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'\0'
expr_stmt|;
if|if
condition|(
name|m
operator|->
name|passwd
operator|->
name|len
condition|)
block|{
operator|*
name|p
operator|++
operator|=
operator|(
name|u_char
operator|)
literal|20
expr_stmt|;
name|ngx_sha1_init
argument_list|(
operator|&
name|sha
argument_list|)
expr_stmt|;
name|ngx_sha1_update
argument_list|(
operator|&
name|sha
argument_list|,
name|m
operator|->
name|passwd
operator|->
name|data
argument_list|,
name|m
operator|->
name|passwd
operator|->
name|len
argument_list|)
expr_stmt|;
name|ngx_sha1_final
argument_list|(
name|hash1
argument_list|,
operator|&
name|sha
argument_list|)
expr_stmt|;
name|ngx_sha1_init
argument_list|(
operator|&
name|sha
argument_list|)
expr_stmt|;
name|ngx_sha1_update
argument_list|(
operator|&
name|sha
argument_list|,
name|hash1
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|ngx_sha1_final
argument_list|(
name|hash2
argument_list|,
operator|&
name|sha
argument_list|)
expr_stmt|;
name|ngx_sha1_init
argument_list|(
operator|&
name|sha
argument_list|)
expr_stmt|;
name|ngx_sha1_update
argument_list|(
operator|&
name|sha
argument_list|,
name|gr2
operator|->
name|salt1
argument_list|,
literal|8
argument_list|)
expr_stmt|;
name|ngx_sha1_update
argument_list|(
operator|&
name|sha
argument_list|,
name|gr2
operator|->
name|salt2
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|ngx_sha1_update
argument_list|(
operator|&
name|sha
argument_list|,
name|hash2
argument_list|,
literal|20
argument_list|)
expr_stmt|;
name|ngx_sha1_final
argument_list|(
name|hash2
argument_list|,
operator|&
name|sha
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
literal|20
condition|;
name|i
operator|++
control|)
block|{
operator|*
name|p
operator|++
operator|=
operator|(
name|u_char
operator|)
operator|(
name|hash1
index|[
name|i
index|]
operator|^
name|hash2
index|[
name|i
index|]
operator|)
expr_stmt|;
block|}
block|}
else|else
block|{
operator|*
name|p
operator|++
operator|=
literal|'\0'
expr_stmt|;
block|}
name|p
operator|=
name|ngx_copy
argument_list|(
name|p
argument_list|,
name|m
operator|->
name|database
operator|->
name|data
argument_list|,
name|m
operator|->
name|database
operator|->
name|len
argument_list|)
expr_stmt|;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|n
operator|=
name|ngx_send
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
argument_list|,
operator|(
name|void
operator|*
operator|)
name|auth
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|<
operator|(
name|ssize_t
operator|)
name|len
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"the incomplete packet was sent to mysql server %V"
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
name|m
operator|->
name|peer
operator|.
name|connection
operator|->
name|read
operator|->
name|handler
operator|=
name|ngx_mysql_read_auth_result
expr_stmt|;
name|ngx_add_timer
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
operator|->
name|read
argument_list|,
comment|/* STUB */
literal|5000
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_mysql_empty_handler (ngx_event_t * wev)
name|ngx_mysql_empty_handler
parameter_list|(
name|ngx_event_t
modifier|*
name|wev
parameter_list|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|wev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql empty handler"
argument_list|)
expr_stmt|;
return|return;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_mysql_read_auth_result (ngx_event_t * rev)
name|ngx_mysql_read_auth_result
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|,
name|len
decl_stmt|;
name|ngx_str_t
name|msg
decl_stmt|;
name|ngx_mysql_t
modifier|*
name|m
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_mysql_error_pkt_t
modifier|*
name|epkt
decl_stmt|;
name|ngx_mysql_response_pkt_t
modifier|*
name|pkt
decl_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql read auth"
argument_list|)
expr_stmt|;
name|c
operator|=
name|rev
operator|->
name|data
expr_stmt|;
name|m
operator|=
name|c
operator|->
name|data
expr_stmt|;
name|m
operator|->
name|peer
operator|.
name|log
operator|->
name|action
operator|=
literal|"reading mysql auth result"
expr_stmt|;
name|n
operator|=
name|ngx_recv
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
argument_list|,
name|m
operator|->
name|buf
operator|->
name|pos
argument_list|,
comment|/* STUB */
literal|1024
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|n
operator|<
literal|5
condition|)
block|{
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
name|pkt
operator|=
operator|(
name|ngx_mysql_response_pkt_t
operator|*
operator|)
name|m
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|len
operator|=
name|ngx_m24toh
argument_list|(
name|pkt
operator|->
name|pktlen
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|>
name|n
operator|-
literal|4
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql server %V sent incomplete response packet"
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|pkt
operator|->
name|fields
operator|==
literal|0
condition|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql auth OK"
argument_list|)
expr_stmt|;
name|m
operator|->
name|state
operator|=
name|NGX_OK
expr_stmt|;
name|m
operator|->
name|pktn
operator|=
literal|0
expr_stmt|;
name|m
operator|->
name|handler
argument_list|(
name|m
argument_list|)
expr_stmt|;
return|return;
block|}
name|epkt
operator|=
operator|(
name|ngx_mysql_error_pkt_t
operator|*
operator|)
name|pkt
expr_stmt|;
name|msg
operator|.
name|len
operator|=
operator|(
name|u_char
operator|*
operator|)
name|epkt
operator|+
literal|4
operator|+
name|len
operator|-
name|epkt
operator|->
name|message
expr_stmt|;
name|msg
operator|.
name|data
operator|=
name|epkt
operator|->
name|message
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql server %V sent error (%ud): \"%V\""
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|,
name|ngx_m16toh
argument_list|(
name|epkt
operator|->
name|code
argument_list|)
argument_list|,
operator|&
name|msg
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_mysql_query (ngx_mysql_t * m)
name|ngx_mysql_query
parameter_list|(
name|ngx_mysql_t
modifier|*
name|m
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|;
name|ngx_mysql_command_pkt_t
modifier|*
name|pkt
decl_stmt|;
name|pkt
operator|=
operator|(
name|ngx_mysql_command_pkt_t
operator|*
operator|)
name|m
operator|->
name|query
operator|.
name|data
expr_stmt|;
name|ngx_htom24
argument_list|(
name|pkt
operator|->
name|pktlen
argument_list|,
name|m
operator|->
name|query
operator|.
name|len
operator|-
literal|4
argument_list|)
expr_stmt|;
name|pkt
operator|->
name|pktn
operator|=
operator|(
name|u_char
operator|)
name|m
operator|->
name|pktn
operator|++
expr_stmt|;
name|pkt
operator|->
name|command
operator|=
name|NGX_MYSQL_CMD_QUERY
expr_stmt|;
name|n
operator|=
name|ngx_send
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
argument_list|,
name|m
operator|->
name|query
operator|.
name|data
argument_list|,
name|m
operator|->
name|query
operator|.
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|<
operator|(
name|ssize_t
operator|)
name|m
operator|->
name|query
operator|.
name|len
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|m
operator|->
name|peer
operator|.
name|log
argument_list|,
literal|0
argument_list|,
literal|"the incomplete packet was sent to mysql server %V"
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
name|m
operator|->
name|peer
operator|.
name|connection
operator|->
name|read
operator|->
name|handler
operator|=
name|ngx_mysql_read_query_result
expr_stmt|;
name|ngx_add_timer
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
operator|->
name|read
argument_list|,
comment|/* STUB */
literal|5000
argument_list|)
expr_stmt|;
comment|/* STUB handle event */
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_mysql_read_query_result (ngx_event_t * rev)
name|ngx_mysql_read_query_result
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|,
name|len
decl_stmt|;
name|ngx_str_t
name|msg
decl_stmt|;
name|ngx_mysql_t
modifier|*
name|m
decl_stmt|;
name|ngx_connection_t
modifier|*
name|c
decl_stmt|;
name|ngx_mysql_error_pkt_t
modifier|*
name|epkt
decl_stmt|;
name|ngx_mysql_response_pkt_t
modifier|*
name|pkt
decl_stmt|;
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql read query result"
argument_list|)
expr_stmt|;
name|c
operator|=
name|rev
operator|->
name|data
expr_stmt|;
name|m
operator|=
name|c
operator|->
name|data
expr_stmt|;
name|m
operator|->
name|peer
operator|.
name|log
operator|->
name|action
operator|=
literal|"reading mysql read query result"
expr_stmt|;
name|n
operator|=
name|ngx_recv
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
argument_list|,
name|m
operator|->
name|buf
operator|->
name|pos
argument_list|,
comment|/* STUB */
literal|1024
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_AGAIN
condition|)
block|{
return|return;
block|}
if|if
condition|(
name|n
operator|<
literal|5
condition|)
block|{
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
name|pkt
operator|=
operator|(
name|ngx_mysql_response_pkt_t
operator|*
operator|)
name|m
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|len
operator|=
name|ngx_m24toh
argument_list|(
name|pkt
operator|->
name|pktlen
argument_list|)
expr_stmt|;
if|if
condition|(
name|len
operator|>
name|n
operator|-
literal|4
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql server %V sent incomplete response packet"
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
return|return;
block|}
if|if
condition|(
name|pkt
operator|->
name|fields
operator|!=
literal|0xff
condition|)
block|{
name|ngx_log_debug0
argument_list|(
name|NGX_LOG_DEBUG_HTTP
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql query OK"
argument_list|)
expr_stmt|;
name|m
operator|->
name|state
operator|=
name|NGX_OK
expr_stmt|;
name|m
operator|->
name|pktn
operator|=
name|pkt
operator|->
name|pktn
expr_stmt|;
name|m
operator|->
name|handler
argument_list|(
name|m
argument_list|)
expr_stmt|;
return|return;
block|}
name|epkt
operator|=
operator|(
name|ngx_mysql_error_pkt_t
operator|*
operator|)
name|pkt
expr_stmt|;
name|msg
operator|.
name|len
operator|=
operator|(
name|u_char
operator|*
operator|)
name|epkt
operator|+
literal|4
operator|+
name|len
operator|-
name|epkt
operator|->
name|message
expr_stmt|;
name|msg
operator|.
name|data
operator|=
name|epkt
operator|->
name|message
expr_stmt|;
name|ngx_log_error
argument_list|(
name|NGX_LOG_ERR
argument_list|,
name|rev
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"mysql server %V sent error (%ud): \"%V\""
argument_list|,
name|m
operator|->
name|peer
operator|.
name|name
argument_list|,
name|ngx_m16toh
argument_list|(
name|epkt
operator|->
name|code
argument_list|)
argument_list|,
operator|&
name|msg
argument_list|)
expr_stmt|;
name|ngx_mysql_close
argument_list|(
name|m
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|ngx_mysql_close (ngx_mysql_t * m,ngx_int_t rc)
name|ngx_mysql_close
parameter_list|(
name|ngx_mysql_t
modifier|*
name|m
parameter_list|,
name|ngx_int_t
name|rc
parameter_list|)
block|{
if|if
condition|(
name|rc
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_close_connection
argument_list|(
name|m
operator|->
name|peer
operator|.
name|connection
argument_list|)
expr_stmt|;
block|}
name|m
operator|->
name|state
operator|=
name|rc
expr_stmt|;
name|m
operator|->
name|handler
argument_list|(
name|m
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

