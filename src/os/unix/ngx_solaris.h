begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SOLARIS_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SOLARIS_H_INCLUDED_
define|#
directive|define
name|_NGX_SOLARIS_H_INCLUDED_
end_define

begin_function_decl
name|ngx_int_t
name|ngx_init_setproctitle
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_setproctitle
parameter_list|(
name|char
modifier|*
name|title
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_chain_t
modifier|*
name|ngx_solaris_sendfilev_chain
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SOLARIS_H_INCLUDED_ */
end_comment

end_unit

