begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_include
include|#
directive|include
file|<ngx_listen.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_decl_stmt
specifier|extern
name|ngx_array_t
modifier|*
name|ngx_listening_sockets
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* STUB */
end_comment

begin_decl_stmt
DECL|variable|addr
specifier|static
name|struct
name|sockaddr_in
name|addr
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|addr_text
specifier|static
name|char
name|addr_text
index|[
literal|22
index|]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_server
specifier|static
name|ngx_http_server_t
name|ngx_http_server
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_http_init (ngx_pool_t * pool,ngx_log_t * log)
name|int
name|ngx_http_init
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_listen_t
modifier|*
name|ls
decl_stmt|;
name|ngx_http_server
operator|.
name|request_pool_size
operator|=
literal|16384
expr_stmt|;
name|ngx_http_server
operator|.
name|header_timeout
operator|=
literal|20000
expr_stmt|;
name|ngx_http_server
operator|.
name|header_buffer_size
operator|=
literal|1024
expr_stmt|;
name|ngx_http_server
operator|.
name|discarded_buffer_size
operator|=
literal|1500
expr_stmt|;
if|#
directive|if
operator|(
name|WIN32
operator|)
name|ngx_http_server
operator|.
name|doc_root
operator|=
literal|"html"
expr_stmt|;
else|#
directive|else
name|ngx_http_server
operator|.
name|doc_root
operator|=
literal|"/home/is/work/xml/site-1.0.0/html"
expr_stmt|;
endif|#
directive|endif
name|ngx_http_server
operator|.
name|doc_root
operator|=
literal|"html"
expr_stmt|;
name|ngx_http_server
operator|.
name|doc_root_len
operator|=
name|strlen
argument_list|(
name|ngx_http_server
operator|.
name|doc_root
argument_list|)
operator|+
literal|1
expr_stmt|;
name|ngx_http_output_filter_init
argument_list|()
expr_stmt|;
name|ngx_http_write_filter_init
argument_list|()
expr_stmt|;
name|ls
operator|=
name|ngx_push_array
argument_list|(
name|ngx_listening_sockets
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
name|ls
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_listen_t
argument_list|)
argument_list|)
expr_stmt|;
name|addr
operator|.
name|sin_family
operator|=
name|AF_INET
expr_stmt|;
name|addr
operator|.
name|sin_addr
operator|.
name|s_addr
operator|=
name|inet_addr
argument_list|(
literal|"0.0.0.0"
argument_list|)
expr_stmt|;
name|addr
operator|.
name|sin_port
operator|=
name|htons
argument_list|(
literal|8000
argument_list|)
expr_stmt|;
name|ngx_snprintf
argument_list|(
name|ngx_cpystrn
argument_list|(
name|addr_text
argument_list|,
name|inet_ntoa
argument_list|(
name|addr
operator|.
name|sin_addr
argument_list|)
argument_list|,
literal|16
argument_list|)
argument_list|,
literal|7
argument_list|,
literal|":%d"
argument_list|,
name|ntohs
argument_list|(
name|addr
operator|.
name|sin_port
argument_list|)
argument_list|)
expr_stmt|;
name|ls
operator|->
name|family
operator|=
name|AF_INET
expr_stmt|;
name|ls
operator|->
name|type
operator|=
name|SOCK_STREAM
expr_stmt|;
name|ls
operator|->
name|protocol
operator|=
name|IPPROTO_IP
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_OVERLAPPED
operator|)
name|ls
operator|->
name|flags
operator|=
name|WSA_FLAG_OVERLAPPED
expr_stmt|;
endif|#
directive|endif
name|ls
operator|->
name|sockaddr
operator|=
operator|(
expr|struct
name|sockaddr
operator|*
operator|)
operator|&
name|addr
expr_stmt|;
name|ls
operator|->
name|socklen
operator|=
sizeof|sizeof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|)
expr_stmt|;
name|ls
operator|->
name|addr
operator|=
name|offsetof
argument_list|(
expr|struct
name|sockaddr_in
argument_list|,
name|sin_addr
argument_list|)
expr_stmt|;
name|ls
operator|->
name|addr_text
operator|=
name|addr_text
expr_stmt|;
name|ls
operator|->
name|addr_textlen
operator|=
name|INET_ADDRSTRLEN
expr_stmt|;
name|ls
operator|->
name|backlog
operator|=
operator|-
literal|1
expr_stmt|;
name|ls
operator|->
name|post_accept_timeout
operator|=
literal|10000
expr_stmt|;
name|ls
operator|->
name|nonblocking
operator|=
literal|1
expr_stmt|;
name|ls
operator|->
name|handler
operator|=
name|ngx_http_init_connection
expr_stmt|;
name|ls
operator|->
name|server
operator|=
operator|&
name|ngx_http_server
expr_stmt|;
name|ls
operator|->
name|log
operator|=
name|log
expr_stmt|;
return|return
literal|1
return|;
block|}
end_function

begin_comment
comment|/* */
end_comment

end_unit

