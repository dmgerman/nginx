begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_IOCP_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_IOCP_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_IOCP_MODULE_H_INCLUDED_
end_define

begin_typedef
DECL|struct|__anon28f2e2940108
typedef|typedef
struct|struct
block|{
DECL|member|threads
name|int
name|threads
decl_stmt|;
DECL|member|post_acceptex
name|int
name|post_acceptex
decl_stmt|;
DECL|member|acceptex_read
name|int
name|acceptex_read
decl_stmt|;
DECL|typedef|ngx_iocp_conf_t
block|}
name|ngx_iocp_conf_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_iocp_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_IOCP_MODULE_H_INCLUDED_ */
end_comment

end_unit

