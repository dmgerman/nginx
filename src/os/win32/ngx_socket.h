begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SOCKET_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SOCKET_H_INCLUDED_
define|#
directive|define
name|_NGX_SOCKET_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_typedef
DECL|typedef|ngx_socket_t
typedef|typedef
name|SOCKET
name|ngx_socket_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_init_sockets
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_nonblocking_n
parameter_list|(
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_nonblocking_n
define|#
directive|define
name|ngx_nonblocking_n
value|"ioctlsocket (FIONBIO)"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SOCKET_H_INCLUDED_ */
end_comment

end_unit

