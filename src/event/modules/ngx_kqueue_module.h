begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_KQUEUE_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_KQUEUE_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_KQUEUE_MODULE_H_INCLUDED_
end_define

begin_decl_stmt
specifier|extern
name|int
name|ngx_kqueue
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_kqueue_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_event_module_t
name|ngx_kqueue_module_ctx
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_KQUEUE_MODULE_H_INCLUDED_ */
end_comment

end_unit

