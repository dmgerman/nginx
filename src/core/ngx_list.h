begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_LIST_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_LIST_H_INCLUDED_
define|#
directive|define
name|_NGX_LIST_H_INCLUDED_
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
DECL|typedef|ngx_list_part_t
typedef|typedef
name|struct
name|ngx_list_part_s
name|ngx_list_part_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_list_part_s
struct|struct
name|ngx_list_part_s
block|{
DECL|member|elts
name|void
modifier|*
name|elts
decl_stmt|;
DECL|member|nelts
name|ngx_uint_t
name|nelts
decl_stmt|;
DECL|member|next
name|ngx_list_part_t
modifier|*
name|next
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon27929fd70108
typedef|typedef
struct|struct
block|{
DECL|member|last
name|ngx_list_part_t
modifier|*
name|last
decl_stmt|;
DECL|member|part
name|ngx_list_part_t
name|part
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|nalloc
name|ngx_uint_t
name|nalloc
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|typedef|ngx_list_t
block|}
name|ngx_list_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_init_list (l,p,n,s,rc)
define|#
directive|define
name|ngx_init_list
parameter_list|(
name|l
parameter_list|,
name|p
parameter_list|,
name|n
parameter_list|,
name|s
parameter_list|,
name|rc
parameter_list|)
define|\
value|if (!(l.part.elts = ngx_palloc(p, n * s))) {                             \         return rc;                                                           \     }                                                                        \     l.part.nelts = 0; l.part.next = NULL;                                    \     l.last =&l.part; l.size = s; l.nalloc = n; l.pool = p;
end_define

begin_define
DECL|macro|ngx_iterate_list (p,i)
define|#
directive|define
name|ngx_iterate_list
parameter_list|(
name|p
parameter_list|,
name|i
parameter_list|)
define|\
value|for ( ;; i++) {                                                  \                 if (i>= p->nelts) {                                         \                     if (p->next == NULL) {                                   \                         break;                                               \                     }                                                        \                     p = p->next; i = 0;                                      \                 }
end_define

begin_function_decl
name|void
modifier|*
name|ngx_push_list
parameter_list|(
name|ngx_list_t
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_LIST_H_INCLUDED_ */
end_comment

end_unit

