begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_typedef
DECL|struct|__anon2b53d5600108
typedef|typedef
struct|struct
block|{
DECL|member|changes
name|int
name|changes
decl_stmt|;
DECL|member|events
name|int
name|events
decl_stmt|;
DECL|typedef|ngx_kqueue_conf_t
block|}
name|ngx_kqueue_conf_t
typedef|;
end_typedef

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

