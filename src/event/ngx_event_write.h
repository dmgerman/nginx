begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_WRITE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_WRITE_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_WRITE_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_function_decl
name|ngx_chain_t
modifier|*
name|ngx_event_write
parameter_list|(
name|ngx_connection_t
modifier|*
name|cn
parameter_list|,
name|ngx_chain_t
modifier|*
name|in
parameter_list|,
name|off_t
name|flush
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_WRITE_H_INCLUDED_ */
end_comment

end_unit

