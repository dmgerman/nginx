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
DECL|struct|__anon29541c6b0108
typedef|typedef
struct|struct
block|{
DECL|member|value
name|void
modifier|*
name|value
decl_stmt|;
DECL|member|len
name|u_char
name|len
decl_stmt|;
DECL|member|name
name|u_char
name|name
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|ngx_hash_elt_t
block|}
name|ngx_hash_elt_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29541c6b0208
typedef|typedef
struct|struct
block|{
DECL|member|buckets
name|ngx_hash_elt_t
modifier|*
modifier|*
name|buckets
decl_stmt|;
DECL|member|size
name|ngx_uint_t
name|size
decl_stmt|;
DECL|typedef|ngx_hash_t
block|}
name|ngx_hash_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29541c6b0308
typedef|typedef
struct|struct
block|{
DECL|member|hash
name|ngx_hash_t
name|hash
decl_stmt|;
DECL|member|value
name|void
modifier|*
name|value
decl_stmt|;
DECL|typedef|ngx_hash_wildcard_t
block|}
name|ngx_hash_wildcard_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29541c6b0408
typedef|typedef
struct|struct
block|{
DECL|member|key
name|ngx_str_t
name|key
decl_stmt|;
DECL|member|key_hash
name|ngx_uint_t
name|key_hash
decl_stmt|;
DECL|member|value
name|void
modifier|*
name|value
decl_stmt|;
DECL|typedef|ngx_hash_key_t
block|}
name|ngx_hash_key_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_hash_key_pt
typedef|typedef
name|ngx_uint_t
function_decl|(
modifier|*
name|ngx_hash_key_pt
function_decl|)
parameter_list|(
name|u_char
modifier|*
name|data
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon29541c6b0508
typedef|typedef
struct|struct
block|{
DECL|member|hash
name|ngx_hash_t
modifier|*
name|hash
decl_stmt|;
DECL|member|key
name|ngx_hash_key_pt
name|key
decl_stmt|;
DECL|member|max_size
name|ngx_uint_t
name|max_size
decl_stmt|;
DECL|member|bucket_size
name|ngx_uint_t
name|bucket_size
decl_stmt|;
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|temp_pool
name|ngx_pool_t
modifier|*
name|temp_pool
decl_stmt|;
DECL|typedef|ngx_hash_init_t
block|}
name|ngx_hash_init_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HASH_SMALL
define|#
directive|define
name|NGX_HASH_SMALL
value|1
end_define

begin_define
DECL|macro|NGX_HASH_LARGE
define|#
directive|define
name|NGX_HASH_LARGE
value|2
end_define

begin_define
DECL|macro|NGX_HASH_LARGE_ASIZE
define|#
directive|define
name|NGX_HASH_LARGE_ASIZE
value|16384
end_define

begin_define
DECL|macro|NGX_HASH_LARGE_HSIZE
define|#
directive|define
name|NGX_HASH_LARGE_HSIZE
value|10007
end_define

begin_define
DECL|macro|NGX_HASH_WILDCARD_KEY
define|#
directive|define
name|NGX_HASH_WILDCARD_KEY
value|1
end_define

begin_define
DECL|macro|NGX_HASH_READONLY_KEY
define|#
directive|define
name|NGX_HASH_READONLY_KEY
value|2
end_define

begin_typedef
DECL|struct|__anon29541c6b0608
typedef|typedef
struct|struct
block|{
DECL|member|hsize
name|ngx_uint_t
name|hsize
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|temp_pool
name|ngx_pool_t
modifier|*
name|temp_pool
decl_stmt|;
DECL|member|keys
name|ngx_array_t
name|keys
decl_stmt|;
DECL|member|keys_hash
name|ngx_array_t
modifier|*
name|keys_hash
decl_stmt|;
DECL|member|dns_wildcards
name|ngx_array_t
name|dns_wildcards
decl_stmt|;
DECL|member|dns_wildcards_hash
name|ngx_array_t
modifier|*
name|dns_wildcards_hash
decl_stmt|;
DECL|typedef|ngx_hash_keys_arrays_t
block|}
name|ngx_hash_keys_arrays_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29541c6b0708
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
DECL|typedef|ngx_hash0_t
block|}
name|ngx_hash0_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon29541c6b0808
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
DECL|member|lowcase_key
name|u_char
modifier|*
name|lowcase_key
decl_stmt|;
DECL|typedef|ngx_table_elt_t
block|}
name|ngx_table_elt_t
typedef|;
end_typedef

begin_function_decl
name|void
modifier|*
name|ngx_hash_find
parameter_list|(
name|ngx_hash_t
modifier|*
name|hash
parameter_list|,
name|ngx_uint_t
name|key
parameter_list|,
name|u_char
modifier|*
name|name
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
modifier|*
name|ngx_hash_find_wildcard
parameter_list|(
name|ngx_hash_wildcard_t
modifier|*
name|hwc
parameter_list|,
name|u_char
modifier|*
name|name
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_hash_init
parameter_list|(
name|ngx_hash_init_t
modifier|*
name|hinit
parameter_list|,
name|ngx_hash_key_t
modifier|*
name|names
parameter_list|,
name|ngx_uint_t
name|nelts
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_hash_wildcard_init
parameter_list|(
name|ngx_hash_init_t
modifier|*
name|hinit
parameter_list|,
name|ngx_hash_key_t
modifier|*
name|names
parameter_list|,
name|ngx_uint_t
name|nelts
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_hash (key,c)
define|#
directive|define
name|ngx_hash
parameter_list|(
name|key
parameter_list|,
name|c
parameter_list|)
value|((ngx_uint_t) key * 31 + c)
end_define

begin_function_decl
name|ngx_uint_t
name|ngx_hash_key
parameter_list|(
name|u_char
modifier|*
name|data
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_uint_t
name|ngx_hash_key_lc
parameter_list|(
name|u_char
modifier|*
name|data
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_hash_keys_array_init
parameter_list|(
name|ngx_hash_keys_arrays_t
modifier|*
name|ha
parameter_list|,
name|ngx_uint_t
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_hash_add_key
parameter_list|(
name|ngx_hash_keys_arrays_t
modifier|*
name|ha
parameter_list|,
name|ngx_str_t
modifier|*
name|key
parameter_list|,
name|void
modifier|*
name|value
parameter_list|,
name|ngx_uint_t
name|flags
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

