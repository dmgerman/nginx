begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

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

begin_comment
comment|/*  * The red-black tree code is based on the algorithm described in  * the "Introduction to Algorithms" by Cormen, Leiserson and Rivest.  */
end_comment

begin_function_decl
specifier|static
name|ngx_inline
name|void
name|ngx_rbtree_left_rotate
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
modifier|*
name|root
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_inline
name|void
name|ngx_rbtree_right_rotate
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
modifier|*
name|root
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|ngx_rbtree_insert (ngx_rbtree_t * tree,ngx_rbtree_node_t * node)
name|ngx_rbtree_insert
parameter_list|(
name|ngx_rbtree_t
modifier|*
name|tree
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|)
block|{
name|ngx_rbtree_node_t
modifier|*
modifier|*
name|root
decl_stmt|,
modifier|*
name|temp
decl_stmt|,
modifier|*
name|sentinel
decl_stmt|;
comment|/* a binary tree insert */
name|root
operator|=
operator|(
name|ngx_rbtree_node_t
operator|*
operator|*
operator|)
operator|&
name|tree
operator|->
name|root
expr_stmt|;
name|sentinel
operator|=
name|tree
operator|->
name|sentinel
expr_stmt|;
if|if
condition|(
operator|*
name|root
operator|==
name|sentinel
condition|)
block|{
name|node
operator|->
name|parent
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|left
operator|=
name|sentinel
expr_stmt|;
name|node
operator|->
name|right
operator|=
name|sentinel
expr_stmt|;
name|ngx_rbt_black
argument_list|(
name|node
argument_list|)
expr_stmt|;
operator|*
name|root
operator|=
name|node
expr_stmt|;
return|return;
block|}
name|tree
operator|->
name|insert
argument_list|(
operator|*
name|root
argument_list|,
name|node
argument_list|,
name|sentinel
argument_list|)
expr_stmt|;
comment|/* re-balance tree */
while|while
condition|(
name|node
operator|!=
operator|*
name|root
operator|&&
name|ngx_rbt_is_red
argument_list|(
name|node
operator|->
name|parent
argument_list|)
condition|)
block|{
if|if
condition|(
name|node
operator|->
name|parent
operator|==
name|node
operator|->
name|parent
operator|->
name|parent
operator|->
name|left
condition|)
block|{
name|temp
operator|=
name|node
operator|->
name|parent
operator|->
name|parent
operator|->
name|right
expr_stmt|;
if|if
condition|(
name|ngx_rbt_is_red
argument_list|(
name|temp
argument_list|)
condition|)
block|{
name|ngx_rbt_black
argument_list|(
name|node
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbt_black
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|node
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
name|node
operator|=
name|node
operator|->
name|parent
operator|->
name|parent
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|node
operator|==
name|node
operator|->
name|parent
operator|->
name|right
condition|)
block|{
name|node
operator|=
name|node
operator|->
name|parent
expr_stmt|;
name|ngx_rbtree_left_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|node
argument_list|)
expr_stmt|;
block|}
name|ngx_rbt_black
argument_list|(
name|node
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|node
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbtree_right_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|node
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|temp
operator|=
name|node
operator|->
name|parent
operator|->
name|parent
operator|->
name|left
expr_stmt|;
if|if
condition|(
name|ngx_rbt_is_red
argument_list|(
name|temp
argument_list|)
condition|)
block|{
name|ngx_rbt_black
argument_list|(
name|node
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbt_black
argument_list|(
name|temp
argument_list|)
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|node
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
name|node
operator|=
name|node
operator|->
name|parent
operator|->
name|parent
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|node
operator|==
name|node
operator|->
name|parent
operator|->
name|left
condition|)
block|{
name|node
operator|=
name|node
operator|->
name|parent
expr_stmt|;
name|ngx_rbtree_right_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|node
argument_list|)
expr_stmt|;
block|}
name|ngx_rbt_black
argument_list|(
name|node
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|node
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbtree_left_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|node
operator|->
name|parent
operator|->
name|parent
argument_list|)
expr_stmt|;
block|}
block|}
block|}
name|ngx_rbt_black
argument_list|(
operator|*
name|root
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_rbtree_insert_value (ngx_rbtree_node_t * temp,ngx_rbtree_node_t * node,ngx_rbtree_node_t * sentinel)
name|ngx_rbtree_insert_value
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
block|{
name|ngx_rbtree_node_t
modifier|*
modifier|*
name|p
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|p
operator|=
operator|(
name|node
operator|->
name|key
operator|<
name|temp
operator|->
name|key
operator|)
condition|?
operator|&
name|temp
operator|->
name|left
else|:
operator|&
name|temp
operator|->
name|right
expr_stmt|;
if|if
condition|(
operator|*
name|p
operator|==
name|sentinel
condition|)
block|{
break|break;
block|}
name|temp
operator|=
operator|*
name|p
expr_stmt|;
block|}
operator|*
name|p
operator|=
name|node
expr_stmt|;
name|node
operator|->
name|parent
operator|=
name|temp
expr_stmt|;
name|node
operator|->
name|left
operator|=
name|sentinel
expr_stmt|;
name|node
operator|->
name|right
operator|=
name|sentinel
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|node
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_rbtree_insert_timer_value (ngx_rbtree_node_t * temp,ngx_rbtree_node_t * node,ngx_rbtree_node_t * sentinel)
name|ngx_rbtree_insert_timer_value
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
block|{
name|ngx_rbtree_node_t
modifier|*
modifier|*
name|p
decl_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
comment|/*          * Timer values          * 1) are spread in small range, usually several minutes,          * 2) and overflow each 49 days, if milliseconds are stored in 32 bits.          * The comparison takes into account that overflow.          */
comment|/*  node->key< temp->key */
name|p
operator|=
operator|(
operator|(
name|ngx_rbtree_key_int_t
operator|)
operator|(
name|node
operator|->
name|key
operator|-
name|temp
operator|->
name|key
operator|)
operator|<
literal|0
operator|)
condition|?
operator|&
name|temp
operator|->
name|left
else|:
operator|&
name|temp
operator|->
name|right
expr_stmt|;
if|if
condition|(
operator|*
name|p
operator|==
name|sentinel
condition|)
block|{
break|break;
block|}
name|temp
operator|=
operator|*
name|p
expr_stmt|;
block|}
operator|*
name|p
operator|=
name|node
expr_stmt|;
name|node
operator|->
name|parent
operator|=
name|temp
expr_stmt|;
name|node
operator|->
name|left
operator|=
name|sentinel
expr_stmt|;
name|node
operator|->
name|right
operator|=
name|sentinel
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|node
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_rbtree_delete (ngx_rbtree_t * tree,ngx_rbtree_node_t * node)
name|ngx_rbtree_delete
parameter_list|(
name|ngx_rbtree_t
modifier|*
name|tree
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|)
block|{
name|ngx_uint_t
name|red
decl_stmt|;
name|ngx_rbtree_node_t
modifier|*
modifier|*
name|root
decl_stmt|,
modifier|*
name|sentinel
decl_stmt|,
modifier|*
name|subst
decl_stmt|,
modifier|*
name|temp
decl_stmt|,
modifier|*
name|w
decl_stmt|;
comment|/* a binary tree delete */
name|root
operator|=
operator|(
name|ngx_rbtree_node_t
operator|*
operator|*
operator|)
operator|&
name|tree
operator|->
name|root
expr_stmt|;
name|sentinel
operator|=
name|tree
operator|->
name|sentinel
expr_stmt|;
if|if
condition|(
name|node
operator|->
name|left
operator|==
name|sentinel
condition|)
block|{
name|temp
operator|=
name|node
operator|->
name|right
expr_stmt|;
name|subst
operator|=
name|node
expr_stmt|;
block|}
if|else if
condition|(
name|node
operator|->
name|right
operator|==
name|sentinel
condition|)
block|{
name|temp
operator|=
name|node
operator|->
name|left
expr_stmt|;
name|subst
operator|=
name|node
expr_stmt|;
block|}
else|else
block|{
name|subst
operator|=
name|ngx_rbtree_min
argument_list|(
name|node
operator|->
name|right
argument_list|,
name|sentinel
argument_list|)
expr_stmt|;
if|if
condition|(
name|subst
operator|->
name|left
operator|!=
name|sentinel
condition|)
block|{
name|temp
operator|=
name|subst
operator|->
name|left
expr_stmt|;
block|}
else|else
block|{
name|temp
operator|=
name|subst
operator|->
name|right
expr_stmt|;
block|}
block|}
if|if
condition|(
name|subst
operator|==
operator|*
name|root
condition|)
block|{
operator|*
name|root
operator|=
name|temp
expr_stmt|;
name|ngx_rbt_black
argument_list|(
name|temp
argument_list|)
expr_stmt|;
comment|/* DEBUG stuff */
name|node
operator|->
name|left
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|right
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|parent
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|key
operator|=
literal|0
expr_stmt|;
return|return;
block|}
name|red
operator|=
name|ngx_rbt_is_red
argument_list|(
name|subst
argument_list|)
expr_stmt|;
if|if
condition|(
name|subst
operator|==
name|subst
operator|->
name|parent
operator|->
name|left
condition|)
block|{
name|subst
operator|->
name|parent
operator|->
name|left
operator|=
name|temp
expr_stmt|;
block|}
else|else
block|{
name|subst
operator|->
name|parent
operator|->
name|right
operator|=
name|temp
expr_stmt|;
block|}
if|if
condition|(
name|subst
operator|==
name|node
condition|)
block|{
name|temp
operator|->
name|parent
operator|=
name|subst
operator|->
name|parent
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|subst
operator|->
name|parent
operator|==
name|node
condition|)
block|{
name|temp
operator|->
name|parent
operator|=
name|subst
expr_stmt|;
block|}
else|else
block|{
name|temp
operator|->
name|parent
operator|=
name|subst
operator|->
name|parent
expr_stmt|;
block|}
name|subst
operator|->
name|left
operator|=
name|node
operator|->
name|left
expr_stmt|;
name|subst
operator|->
name|right
operator|=
name|node
operator|->
name|right
expr_stmt|;
name|subst
operator|->
name|parent
operator|=
name|node
operator|->
name|parent
expr_stmt|;
name|ngx_rbt_copy_color
argument_list|(
name|subst
argument_list|,
name|node
argument_list|)
expr_stmt|;
if|if
condition|(
name|node
operator|==
operator|*
name|root
condition|)
block|{
operator|*
name|root
operator|=
name|subst
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|node
operator|==
name|node
operator|->
name|parent
operator|->
name|left
condition|)
block|{
name|node
operator|->
name|parent
operator|->
name|left
operator|=
name|subst
expr_stmt|;
block|}
else|else
block|{
name|node
operator|->
name|parent
operator|->
name|right
operator|=
name|subst
expr_stmt|;
block|}
block|}
if|if
condition|(
name|subst
operator|->
name|left
operator|!=
name|sentinel
condition|)
block|{
name|subst
operator|->
name|left
operator|->
name|parent
operator|=
name|subst
expr_stmt|;
block|}
if|if
condition|(
name|subst
operator|->
name|right
operator|!=
name|sentinel
condition|)
block|{
name|subst
operator|->
name|right
operator|->
name|parent
operator|=
name|subst
expr_stmt|;
block|}
block|}
comment|/* DEBUG stuff */
name|node
operator|->
name|left
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|right
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|parent
operator|=
name|NULL
expr_stmt|;
name|node
operator|->
name|key
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|red
condition|)
block|{
return|return;
block|}
comment|/* a delete fixup */
while|while
condition|(
name|temp
operator|!=
operator|*
name|root
operator|&&
name|ngx_rbt_is_black
argument_list|(
name|temp
argument_list|)
condition|)
block|{
if|if
condition|(
name|temp
operator|==
name|temp
operator|->
name|parent
operator|->
name|left
condition|)
block|{
name|w
operator|=
name|temp
operator|->
name|parent
operator|->
name|right
expr_stmt|;
if|if
condition|(
name|ngx_rbt_is_red
argument_list|(
name|w
argument_list|)
condition|)
block|{
name|ngx_rbt_black
argument_list|(
name|w
argument_list|)
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbtree_left_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|w
operator|=
name|temp
operator|->
name|parent
operator|->
name|right
expr_stmt|;
block|}
if|if
condition|(
name|ngx_rbt_is_black
argument_list|(
name|w
operator|->
name|left
argument_list|)
operator|&&
name|ngx_rbt_is_black
argument_list|(
name|w
operator|->
name|right
argument_list|)
condition|)
block|{
name|ngx_rbt_red
argument_list|(
name|w
argument_list|)
expr_stmt|;
name|temp
operator|=
name|temp
operator|->
name|parent
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|ngx_rbt_is_black
argument_list|(
name|w
operator|->
name|right
argument_list|)
condition|)
block|{
name|ngx_rbt_black
argument_list|(
name|w
operator|->
name|left
argument_list|)
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|w
argument_list|)
expr_stmt|;
name|ngx_rbtree_right_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|w
argument_list|)
expr_stmt|;
name|w
operator|=
name|temp
operator|->
name|parent
operator|->
name|right
expr_stmt|;
block|}
name|ngx_rbt_copy_color
argument_list|(
name|w
argument_list|,
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbt_black
argument_list|(
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbt_black
argument_list|(
name|w
operator|->
name|right
argument_list|)
expr_stmt|;
name|ngx_rbtree_left_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|temp
operator|=
operator|*
name|root
expr_stmt|;
block|}
block|}
else|else
block|{
name|w
operator|=
name|temp
operator|->
name|parent
operator|->
name|left
expr_stmt|;
if|if
condition|(
name|ngx_rbt_is_red
argument_list|(
name|w
argument_list|)
condition|)
block|{
name|ngx_rbt_black
argument_list|(
name|w
argument_list|)
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbtree_right_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|w
operator|=
name|temp
operator|->
name|parent
operator|->
name|left
expr_stmt|;
block|}
if|if
condition|(
name|ngx_rbt_is_black
argument_list|(
name|w
operator|->
name|left
argument_list|)
operator|&&
name|ngx_rbt_is_black
argument_list|(
name|w
operator|->
name|right
argument_list|)
condition|)
block|{
name|ngx_rbt_red
argument_list|(
name|w
argument_list|)
expr_stmt|;
name|temp
operator|=
name|temp
operator|->
name|parent
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|ngx_rbt_is_black
argument_list|(
name|w
operator|->
name|left
argument_list|)
condition|)
block|{
name|ngx_rbt_black
argument_list|(
name|w
operator|->
name|right
argument_list|)
expr_stmt|;
name|ngx_rbt_red
argument_list|(
name|w
argument_list|)
expr_stmt|;
name|ngx_rbtree_left_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|w
argument_list|)
expr_stmt|;
name|w
operator|=
name|temp
operator|->
name|parent
operator|->
name|left
expr_stmt|;
block|}
name|ngx_rbt_copy_color
argument_list|(
name|w
argument_list|,
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbt_black
argument_list|(
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|ngx_rbt_black
argument_list|(
name|w
operator|->
name|left
argument_list|)
expr_stmt|;
name|ngx_rbtree_right_rotate
argument_list|(
name|root
argument_list|,
name|sentinel
argument_list|,
name|temp
operator|->
name|parent
argument_list|)
expr_stmt|;
name|temp
operator|=
operator|*
name|root
expr_stmt|;
block|}
block|}
block|}
name|ngx_rbt_black
argument_list|(
name|temp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_rbtree_left_rotate (ngx_rbtree_node_t ** root,ngx_rbtree_node_t * sentinel,ngx_rbtree_node_t * node)
name|ngx_rbtree_left_rotate
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
modifier|*
name|root
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|)
block|{
name|ngx_rbtree_node_t
modifier|*
name|temp
decl_stmt|;
name|temp
operator|=
name|node
operator|->
name|right
expr_stmt|;
name|node
operator|->
name|right
operator|=
name|temp
operator|->
name|left
expr_stmt|;
if|if
condition|(
name|temp
operator|->
name|left
operator|!=
name|sentinel
condition|)
block|{
name|temp
operator|->
name|left
operator|->
name|parent
operator|=
name|node
expr_stmt|;
block|}
name|temp
operator|->
name|parent
operator|=
name|node
operator|->
name|parent
expr_stmt|;
if|if
condition|(
name|node
operator|==
operator|*
name|root
condition|)
block|{
operator|*
name|root
operator|=
name|temp
expr_stmt|;
block|}
if|else if
condition|(
name|node
operator|==
name|node
operator|->
name|parent
operator|->
name|left
condition|)
block|{
name|node
operator|->
name|parent
operator|->
name|left
operator|=
name|temp
expr_stmt|;
block|}
else|else
block|{
name|node
operator|->
name|parent
operator|->
name|right
operator|=
name|temp
expr_stmt|;
block|}
name|temp
operator|->
name|left
operator|=
name|node
expr_stmt|;
name|node
operator|->
name|parent
operator|=
name|temp
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_rbtree_right_rotate (ngx_rbtree_node_t ** root,ngx_rbtree_node_t * sentinel,ngx_rbtree_node_t * node)
name|ngx_rbtree_right_rotate
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
modifier|*
name|root
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|)
block|{
name|ngx_rbtree_node_t
modifier|*
name|temp
decl_stmt|;
name|temp
operator|=
name|node
operator|->
name|left
expr_stmt|;
name|node
operator|->
name|left
operator|=
name|temp
operator|->
name|right
expr_stmt|;
if|if
condition|(
name|temp
operator|->
name|right
operator|!=
name|sentinel
condition|)
block|{
name|temp
operator|->
name|right
operator|->
name|parent
operator|=
name|node
expr_stmt|;
block|}
name|temp
operator|->
name|parent
operator|=
name|node
operator|->
name|parent
expr_stmt|;
if|if
condition|(
name|node
operator|==
operator|*
name|root
condition|)
block|{
operator|*
name|root
operator|=
name|temp
expr_stmt|;
block|}
if|else if
condition|(
name|node
operator|==
name|node
operator|->
name|parent
operator|->
name|right
condition|)
block|{
name|node
operator|->
name|parent
operator|->
name|right
operator|=
name|temp
expr_stmt|;
block|}
else|else
block|{
name|node
operator|->
name|parent
operator|->
name|left
operator|=
name|temp
expr_stmt|;
block|}
name|temp
operator|->
name|right
operator|=
name|node
expr_stmt|;
name|node
operator|->
name|parent
operator|=
name|temp
expr_stmt|;
block|}
end_function

end_unit

