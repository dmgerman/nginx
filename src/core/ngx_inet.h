begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev  */
end_comment

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

begin_typedef
DECL|struct|__anon275ed88b0108
typedef|typedef
struct|struct
block|{
DECL|member|addr
name|in_addr_t
name|addr
decl_stmt|;
DECL|member|mask
name|in_addr_t
name|mask
decl_stmt|;
DECL|typedef|ngx_inet_cidr_t
block|}
name|ngx_inet_cidr_t
typedef|;
end_typedef

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
name|void
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
name|ngx_int_t
name|ngx_ptocidr
parameter_list|(
name|ngx_str_t
modifier|*
name|text
parameter_list|,
name|void
modifier|*
name|cidr
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

