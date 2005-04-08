begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HASH_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HASH_H_INCLUDED_
define|#
directive|define
name|_NGX_HASH_H_INCLUDED_
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
DECL|struct|__anon28a17a430108
typedef|typedef
struct|struct
block|{
DECL|member|buckets
name|void
modifier|*
modifier|*
name|buckets
decl_stmt|;
DECL|member|hash_size
name|ngx_uint_t
name|hash_size
decl_stmt|;
DECL|member|max_size
name|ngx_uint_t
name|max_size
decl_stmt|;
DECL|member|bucket_limit
name|ngx_uint_t
name|bucket_limit
decl_stmt|;
DECL|member|bucket_size
name|size_t
name|bucket_size
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|min_buckets
name|ngx_uint_t
name|min_buckets
decl_stmt|;
DECL|typedef|ngx_hash_t
block|}
name|ngx_hash_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon28a17a430208
typedef|typedef
struct|struct
block|{
DECL|member|hash
name|ngx_uint_t
name|hash
decl_stmt|;
DECL|member|key
name|ngx_str_t
name|key
decl_stmt|;
DECL|member|value
name|ngx_str_t
name|value
decl_stmt|;
DECL|typedef|ngx_table_elt_t
block|}
name|ngx_table_elt_t
typedef|;
end_typedef

begin_function_decl
name|ngx_int_t
name|ngx_hash_init
parameter_list|(
name|ngx_hash_t
modifier|*
name|hash
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|void
modifier|*
name|names
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HASH_H_INCLUDED_ */
end_comment

end_unit

