begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_RADIX_TREE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_RADIX_TREE_H_INCLUDED_
define|#
directive|define
name|_NGX_RADIX_TREE_H_INCLUDED_
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

begin_define
DECL|macro|NGX_RADIX_NO_VALUE
define|#
directive|define
name|NGX_RADIX_NO_VALUE
value|(uintptr_t) -1
end_define

begin_typedef
DECL|typedef|ngx_radix_node_t
typedef|typedef
name|struct
name|ngx_radix_node_s
name|ngx_radix_node_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_radix_node_s
struct|struct
name|ngx_radix_node_s
block|{
DECL|member|right
name|ngx_radix_node_t
modifier|*
name|right
decl_stmt|;
DECL|member|left
name|ngx_radix_node_t
modifier|*
name|left
decl_stmt|;
DECL|member|parent
name|ngx_radix_node_t
modifier|*
name|parent
decl_stmt|;
DECL|member|value
name|uintptr_t
name|value
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon29a2fde00108
typedef|typedef
struct|struct
block|{
DECL|member|root
name|ngx_radix_node_t
modifier|*
name|root
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|free
name|ngx_radix_node_t
modifier|*
name|free
decl_stmt|;
DECL|member|start
name|char
modifier|*
name|start
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|typedef|ngx_radix_tree_t
block|}
name|ngx_radix_tree_t
typedef|;
end_typedef

begin_function_decl
name|ngx_radix_tree_t
modifier|*
name|ngx_radix_tree_create
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_uint_t
name|preallocate
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_radix32tree_insert
parameter_list|(
name|ngx_radix_tree_t
modifier|*
name|tree
parameter_list|,
name|uint32_t
name|key
parameter_list|,
name|uint32_t
name|mask
parameter_list|,
name|uintptr_t
name|value
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_radix32tree_delete
parameter_list|(
name|ngx_radix_tree_t
modifier|*
name|tree
parameter_list|,
name|uint32_t
name|key
parameter_list|,
name|uint32_t
name|mask
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|uintptr_t
name|ngx_radix32tree_find
parameter_list|(
name|ngx_radix_tree_t
modifier|*
name|tree
parameter_list|,
name|uint32_t
name|key
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_RADIX_TREE_H_INCLUDED_ */
end_comment

end_unit

