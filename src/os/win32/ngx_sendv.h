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
file|<ngx_config.h>
end_include

begin_typedef
DECL|typedef|ngx_iovec_t
typedef|typedef
name|WSABUF
name|ngx_iovec_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_iov_base
define|#
directive|define
name|ngx_iov_base
value|buf
end_define

begin_define
DECL|macro|ngx_iov_len
define|#
directive|define
name|ngx_iov_len
value|len
end_define

begin_define
DECL|macro|ngx_sendv (s,iovec,n,sent)
define|#
directive|define
name|ngx_sendv
parameter_list|(
name|s
parameter_list|,
name|iovec
parameter_list|,
name|n
parameter_list|,
name|sent
parameter_list|)
value|WSASend(s, iovec, n, sent, 0, NULL, NULL)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SENDV_H_INCLUDED_ */
end_comment

end_unit

