begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_RBTREE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_RBTREE_H_INCLUDED_
define|#
directive|define
name|_NGX_RBTREE_H_INCLUDED_
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

begin_typedef
DECL|typedef|ngx_rbtree_key_t
typedef|typedef
name|ngx_uint_t
name|ngx_rbtree_key_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_rbtree_key_int_t
typedef|typedef
name|ngx_int_t
name|ngx_rbtree_key_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_rbtree_node_t
typedef|typedef
name|struct
name|ngx_rbtree_node_s
name|ngx_rbtree_node_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_rbtree_node_s
struct|struct
name|ngx_rbtree_node_s
block|{
DECL|member|key
name|ngx_rbtree_key_t
name|key
decl_stmt|;
DECL|member|left
name|ngx_rbtree_node_t
modifier|*
name|left
decl_stmt|;
DECL|member|right
name|ngx_rbtree_node_t
modifier|*
name|right
decl_stmt|;
DECL|member|parent
name|ngx_rbtree_node_t
modifier|*
name|parent
decl_stmt|;
DECL|member|color
name|u_char
name|color
decl_stmt|;
DECL|member|data
name|u_char
name|data
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|ngx_rbtree_t
typedef|typedef
name|struct
name|ngx_rbtree_s
name|ngx_rbtree_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_rbtree_insert_pt
typedef|typedef
name|void
function_decl|(
modifier|*
name|ngx_rbtree_insert_pt
function_decl|)
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
name|root
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
end_typedef

begin_struct
DECL|struct|ngx_rbtree_s
struct|struct
name|ngx_rbtree_s
block|{
DECL|member|root
name|ngx_rbtree_node_t
modifier|*
name|root
decl_stmt|;
DECL|member|sentinel
name|ngx_rbtree_node_t
modifier|*
name|sentinel
decl_stmt|;
DECL|member|insert
name|ngx_rbtree_insert_pt
name|insert
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|ngx_rbtree_init (tree,s,i)
define|#
directive|define
name|ngx_rbtree_init
parameter_list|(
name|tree
parameter_list|,
name|s
parameter_list|,
name|i
parameter_list|)
define|\
value|ngx_rbtree_sentinel_init(s);                                              \     (tree)->root = s;                                                         \     (tree)->sentinel = s;                                                     \     (tree)->insert = i
end_define

begin_function_decl
name|void
name|ngx_rbtree_insert
parameter_list|(
name|ngx_thread_volatile
name|ngx_rbtree_t
modifier|*
name|tree
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_rbtree_delete
parameter_list|(
name|ngx_thread_volatile
name|ngx_rbtree_t
modifier|*
name|tree
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_rbtree_insert_value
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
name|root
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

begin_function_decl
name|void
name|ngx_rbtree_insert_timer_value
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
name|root
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

begin_define
DECL|macro|ngx_rbt_red (node)
define|#
directive|define
name|ngx_rbt_red
parameter_list|(
name|node
parameter_list|)
value|((node)->color = 1)
end_define

begin_define
DECL|macro|ngx_rbt_black (node)
define|#
directive|define
name|ngx_rbt_black
parameter_list|(
name|node
parameter_list|)
value|((node)->color = 0)
end_define

begin_define
DECL|macro|ngx_rbt_is_red (node)
define|#
directive|define
name|ngx_rbt_is_red
parameter_list|(
name|node
parameter_list|)
value|((node)->color)
end_define

begin_define
DECL|macro|ngx_rbt_is_black (node)
define|#
directive|define
name|ngx_rbt_is_black
parameter_list|(
name|node
parameter_list|)
value|(!ngx_rbt_is_red(node))
end_define

begin_define
DECL|macro|ngx_rbt_copy_color (n1,n2)
define|#
directive|define
name|ngx_rbt_copy_color
parameter_list|(
name|n1
parameter_list|,
name|n2
parameter_list|)
value|(n1->color = n2->color)
end_define

begin_comment
comment|/* a sentinel must be black */
end_comment

begin_define
DECL|macro|ngx_rbtree_sentinel_init (node)
define|#
directive|define
name|ngx_rbtree_sentinel_init
parameter_list|(
name|node
parameter_list|)
value|ngx_rbt_black(node)
end_define

begin_function
specifier|static
name|ngx_inline
name|ngx_rbtree_node_t
modifier|*
DECL|function|ngx_rbtree_min (ngx_rbtree_node_t * node,ngx_rbtree_node_t * sentinel)
name|ngx_rbtree_min
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|)
block|{
while|while
condition|(
name|node
operator|->
name|left
operator|!=
name|sentinel
condition|)
block|{
name|node
operator|=
name|node
operator|->
name|left
expr_stmt|;
block|}
return|return
name|node
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_RBTREE_H_INCLUDED_ */
end_comment

end_unit

