begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_ARRAY_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_ARRAY_H_INCLUDED_
define|#
directive|define
name|_NGX_ARRAY_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_typedef
DECL|struct|__anon2b56a0020108
typedef|typedef
struct|struct
block|{
DECL|member|elts
name|char
modifier|*
name|elts
decl_stmt|;
DECL|member|nelts
name|int
name|nelts
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|nalloc
name|int
name|nalloc
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|typedef|ngx_array_t
block|}
name|ngx_array_t
typedef|;
end_typedef

begin_function_decl
name|ngx_array_t
modifier|*
name|ngx_create_array
parameter_list|(
name|ngx_pool_t
modifier|*
name|p
parameter_list|,
name|int
name|n
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_destroy_array
parameter_list|(
name|ngx_array_t
modifier|*
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_push_array
parameter_list|(
name|ngx_array_t
modifier|*
name|a
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_init_array (a,p,n,s,rc)
define|#
directive|define
name|ngx_init_array
parameter_list|(
name|a
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
value|ngx_test_null(a.elts, ngx_palloc(p, n * s), rc);                         \     a.nelts = 0; a.size = s; a.nalloc = n; a.pool = p;
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_ARRAY_H_INCLUDED_ */
end_comment

end_unit

