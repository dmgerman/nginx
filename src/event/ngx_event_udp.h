begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_UDP_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_UDP_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_UDP_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_core.h>
end_include

begin_if
if|#
directive|if
operator|!
operator|(
name|NGX_WIN32
operator|)
end_if

begin_function_decl
name|void
name|ngx_event_recvmsg
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_udp_rbtree_insert_value
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
name|temp
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_delete_udp_connection
parameter_list|(
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_UDP_H_INCLUDED_ */
end_comment

end_unit

