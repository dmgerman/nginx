begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_LISTEN_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_LISTEN_H_INCLUDED_
define|#
directive|define
name|_NGX_LISTEN_H_INCLUDED_
end_define

begin_function_decl
name|ngx_socket_t
name|ngx_listen
parameter_list|(
name|struct
name|sockaddr
modifier|*
name|addr
parameter_list|,
name|int
name|backlog
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|char
modifier|*
name|addr_text
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_LISTEN_H_INCLUDED_ */
end_comment

end_unit

