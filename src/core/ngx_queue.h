begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_QUEUE_H_INCLUDED_ */
end_comment

end_unit

