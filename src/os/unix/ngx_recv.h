begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_RECV_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_RECV_H_INCLUDED_
define|#
directive|define
name|_NGX_RECV_H_INCLUDED_
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_include
include|#
directive|include
file|<errno.h>
end_include

begin_define
define|#
directive|define
name|ngx_recv
parameter_list|(
name|fd
parameter_list|,
name|buf
parameter_list|,
name|size
parameter_list|,
name|flags
parameter_list|)
value|recv(fd, buf, size, flags)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_RECV_H_INCLUDED_ */
end_comment

end_unit

