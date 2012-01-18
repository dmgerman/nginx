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

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_QUEUE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_QUEUE_H_INCLUDED_
define|#
directive|define
name|_NGX_QUEUE_H_INCLUDED_
end_define

begin_typedef
DECL|typedef|ngx_queue_t
typedef|typedef
name|struct
name|ngx_queue_s
name|ngx_queue_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_queue_s
struct|struct
name|ngx_queue_s
block|{
DECL|member|prev
name|ngx_queue_t
modifier|*
name|prev
decl_stmt|;
DECL|member|next
name|ngx_queue_t
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|ngx_queue_init (q)
define|#
directive|define
name|ngx_queue_init
parameter_list|(
name|q
parameter_list|)
define|\
value|(q)->prev = q;                                                            \     (q)->next = q
end_define

begin_define
DECL|macro|ngx_queue_empty (h)
define|#
directive|define
name|ngx_queue_empty
parameter_list|(
name|h
parameter_list|)
define|\
value|(h == (h)->prev)
end_define

begin_define
DECL|macro|ngx_queue_insert_head (h,x)
define|#
directive|define
name|ngx_queue_insert_head
parameter_list|(
name|h
parameter_list|,
name|x
parameter_list|)
define|\
value|(x)->next = (h)->next;                                                    \     (x)->next->prev = x;                                                      \     (x)->prev = h;                                                            \     (h)->next = x
end_define

begin_define
DECL|macro|ngx_queue_insert_after
define|#
directive|define
name|ngx_queue_insert_after
value|ngx_queue_insert_head
end_define

begin_define
DECL|macro|ngx_queue_insert_tail (h,x)
define|#
directive|define
name|ngx_queue_insert_tail
parameter_list|(
name|h
parameter_list|,
name|x
parameter_list|)
define|\
value|(x)->prev = (h)->prev;                                                    \     (x)->prev->next = x;                                                      \     (x)->next = h;                                                            \     (h)->prev = x
end_define

begin_define
DECL|macro|ngx_queue_head (h)
define|#
directive|define
name|ngx_queue_head
parameter_list|(
name|h
parameter_list|)
define|\
value|(h)->next
end_define

begin_define
DECL|macro|ngx_queue_last (h)
define|#
directive|define
name|ngx_queue_last
parameter_list|(
name|h
parameter_list|)
define|\
value|(h)->prev
end_define

begin_define
DECL|macro|ngx_queue_sentinel (h)
define|#
directive|define
name|ngx_queue_sentinel
parameter_list|(
name|h
parameter_list|)
define|\
value|(h)
end_define

begin_define
DECL|macro|ngx_queue_next (q)
define|#
directive|define
name|ngx_queue_next
parameter_list|(
name|q
parameter_list|)
define|\
value|(q)->next
end_define

begin_define
DECL|macro|ngx_queue_prev (q)
define|#
directive|define
name|ngx_queue_prev
parameter_list|(
name|q
parameter_list|)
define|\
value|(q)->prev
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
end_if

begin_define
DECL|macro|ngx_queue_remove (x)
define|#
directive|define
name|ngx_queue_remove
parameter_list|(
name|x
parameter_list|)
define|\
value|(x)->next->prev = (x)->prev;                                              \     (x)->prev->next = (x)->next;                                              \     (x)->prev = NULL;                                                         \     (x)->next = NULL
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_queue_remove (x)
define|#
directive|define
name|ngx_queue_remove
parameter_list|(
name|x
parameter_list|)
define|\
value|(x)->next->prev = (x)->prev;                                              \     (x)->prev->next = (x)->next
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_queue_split (h,q,n)
define|#
directive|define
name|ngx_queue_split
parameter_list|(
name|h
parameter_list|,
name|q
parameter_list|,
name|n
parameter_list|)
define|\
value|(n)->prev = (h)->prev;                                                    \     (n)->prev->next = n;                                                      \     (n)->next = q;                                                            \     (h)->prev = (q)->prev;                                                    \     (h)->prev->next = h;                                                      \     (q)->prev = n;
end_define

begin_define
DECL|macro|ngx_queue_add (h,n)
define|#
directive|define
name|ngx_queue_add
parameter_list|(
name|h
parameter_list|,
name|n
parameter_list|)
define|\
value|(h)->prev->next = (n)->next;                                              \     (n)->next->prev = (h)->prev;                                              \     (h)->prev = (n)->prev;                                                    \     (h)->prev->next = h;
end_define

begin_define
DECL|macro|ngx_queue_data (q,type,link)
define|#
directive|define
name|ngx_queue_data
parameter_list|(
name|q
parameter_list|,
name|type
parameter_list|,
name|link
parameter_list|)
define|\
value|(type *) ((u_char *) q - offsetof(type, link))
end_define

begin_function_decl
name|ngx_queue_t
modifier|*
name|ngx_queue_middle
parameter_list|(
name|ngx_queue_t
modifier|*
name|queue
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_queue_sort
parameter_list|(
name|ngx_queue_t
modifier|*
name|queue
parameter_list|,
name|ngx_int_t
function_decl|(
modifier|*
name|cmp
function_decl|)
parameter_list|(
specifier|const
name|ngx_queue_t
modifier|*
parameter_list|,
specifier|const
name|ngx_queue_t
modifier|*
parameter_list|)
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_QUEUE_H_INCLUDED_ */
end_comment

end_unit

