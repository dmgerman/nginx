begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_INET_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_INET_H_INCLUDED_
define|#
directive|define
name|_NGX_INET_H_INCLUDED_
end_define

begin_function_decl
name|size_t
name|ngx_sock_ntop
parameter_list|(
name|int
name|family
parameter_list|,
name|struct
name|sockaddr
modifier|*
name|addr
parameter_list|,
name|u_char
modifier|*
name|text
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_inet_ntop
parameter_list|(
name|int
name|family
parameter_list|,
name|u_char
modifier|*
name|addr
parameter_list|,
name|u_char
modifier|*
name|text
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_INET_H_INCLUDED_ */
end_comment

end_unit

