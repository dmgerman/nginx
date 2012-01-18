begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_LINUX_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_LINUX_H_INCLUDED_
define|#
directive|define
name|_NGX_LINUX_H_INCLUDED_
end_define

begin_function_decl
name|ngx_chain_t
modifier|*
name|ngx_linux_sendfile_chain
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|,
name|off_t
name|limit
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|int
name|ngx_linux_rtsig_max
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_LINUX_H_INCLUDED_ */
end_comment

end_unit

