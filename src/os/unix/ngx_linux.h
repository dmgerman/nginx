begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_decl
name|ngx_chain_t
modifier|*
name|ngx_linux_sendfile_chain
argument_list|(
name|ngx_connection_t
operator|*
name|c
argument_list|,
name|ngx_chain_t
operator|*
name|in
argument_list|)
end_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_LINUX_H_INCLUDED_ */
end_comment

end_unit

