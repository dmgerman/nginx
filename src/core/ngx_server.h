begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SERVER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SERVER_H_INCLUDED_
define|#
directive|define
name|_NGX_SERVER_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_typedef
DECL|struct|__anon2bc823fd0108
typedef|typedef
struct|struct
block|{
DECL|member|log_level
name|int
name|log_level
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|handler
name|int
function_decl|(
modifier|*
name|handler
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
DECL|member|buff_size
name|int
name|buff_size
decl_stmt|;
DECL|typedef|ngx_server_t
block|}
name|ngx_server_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SERVER_H_INCLUDED_ */
end_comment

end_unit

