begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SENDV_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SENDV_H_INCLUDED_
define|#
directive|define
name|_NGX_SENDV_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
end_include

begin_typedef
DECL|typedef|ngx_iovec_t
typedef|typedef
name|struct
name|iovec
name|ngx_iovec_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_iov_base
define|#
directive|define
name|ngx_iov_base
value|iov_base
end_define

begin_define
DECL|macro|ngx_iov_len
define|#
directive|define
name|ngx_iov_len
value|iov_len
end_define

begin_function_decl
name|ssize_t
name|ngx_sendv
parameter_list|(
name|ngx_socket_t
name|s
parameter_list|,
name|ngx_iovec_t
modifier|*
name|iovec
parameter_list|,
name|int
name|n
parameter_list|,
name|size_t
modifier|*
name|sent
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SENDV_H_INCLUDED_ */
end_comment

end_unit

