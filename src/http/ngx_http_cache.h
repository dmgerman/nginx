begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_CACHE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_CACHE_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_CACHE_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_CACHE_MISS
define|#
directive|define
name|NGX_HTTP_CACHE_MISS
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_BYPASS
define|#
directive|define
name|NGX_HTTP_CACHE_BYPASS
value|2
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_EXPIRED
define|#
directive|define
name|NGX_HTTP_CACHE_EXPIRED
value|3
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_STALE
define|#
directive|define
name|NGX_HTTP_CACHE_STALE
value|4
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_UPDATING
define|#
directive|define
name|NGX_HTTP_CACHE_UPDATING
value|5
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_REVALIDATED
define|#
directive|define
name|NGX_HTTP_CACHE_REVALIDATED
value|6
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_HIT
define|#
directive|define
name|NGX_HTTP_CACHE_HIT
value|7
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_SCARCE
define|#
directive|define
name|NGX_HTTP_CACHE_SCARCE
value|8
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_KEY_LEN
define|#
directive|define
name|NGX_HTTP_CACHE_KEY_LEN
value|16
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_ETAG_LEN
define|#
directive|define
name|NGX_HTTP_CACHE_ETAG_LEN
value|128
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_VARY_LEN
define|#
directive|define
name|NGX_HTTP_CACHE_VARY_LEN
value|128
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_VERSION
define|#
directive|define
name|NGX_HTTP_CACHE_VERSION
value|5
end_define

begin_typedef
DECL|struct|__anon2b95979d0108
typedef|typedef
struct|struct
block|{
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|valid
name|time_t
name|valid
decl_stmt|;
DECL|typedef|ngx_http_cache_valid_t
block|}
name|ngx_http_cache_valid_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b95979d0208
typedef|typedef
struct|struct
block|{
DECL|member|node
name|ngx_rbtree_node_t
name|node
decl_stmt|;
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
DECL|member|key
name|u_char
name|key
index|[
name|NGX_HTTP_CACHE_KEY_LEN
operator|-
sizeof|sizeof
argument_list|(
name|ngx_rbtree_key_t
argument_list|)
index|]
decl_stmt|;
DECL|member|count
name|unsigned
name|count
range|:
literal|20
decl_stmt|;
DECL|member|uses
name|unsigned
name|uses
range|:
literal|10
decl_stmt|;
DECL|member|valid_msec
name|unsigned
name|valid_msec
range|:
literal|10
decl_stmt|;
DECL|member|error
name|unsigned
name|error
range|:
literal|10
decl_stmt|;
DECL|member|exists
name|unsigned
name|exists
range|:
literal|1
decl_stmt|;
DECL|member|updating
name|unsigned
name|updating
range|:
literal|1
decl_stmt|;
DECL|member|deleting
name|unsigned
name|deleting
range|:
literal|1
decl_stmt|;
DECL|member|purged
name|unsigned
name|purged
range|:
literal|1
decl_stmt|;
comment|/* 10 unused bits */
DECL|member|uniq
name|ngx_file_uniq_t
name|uniq
decl_stmt|;
DECL|member|expire
name|time_t
name|expire
decl_stmt|;
DECL|member|valid_sec
name|time_t
name|valid_sec
decl_stmt|;
DECL|member|body_start
name|size_t
name|body_start
decl_stmt|;
DECL|member|fs_size
name|off_t
name|fs_size
decl_stmt|;
DECL|member|lock_time
name|ngx_msec_t
name|lock_time
decl_stmt|;
DECL|typedef|ngx_http_file_cache_node_t
block|}
name|ngx_http_file_cache_node_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_cache_s
struct|struct
name|ngx_http_cache_s
block|{
DECL|member|file
name|ngx_file_t
name|file
decl_stmt|;
DECL|member|keys
name|ngx_array_t
name|keys
decl_stmt|;
DECL|member|crc32
name|uint32_t
name|crc32
decl_stmt|;
DECL|member|key
name|u_char
name|key
index|[
name|NGX_HTTP_CACHE_KEY_LEN
index|]
decl_stmt|;
DECL|member|main
name|u_char
decl|main[
name|NGX_HTTP_CACHE_KEY_LEN
decl|]
decl_stmt|;
DECL|member|uniq
name|ngx_file_uniq_t
name|uniq
decl_stmt|;
DECL|member|valid_sec
name|time_t
name|valid_sec
decl_stmt|;
DECL|member|updating_sec
name|time_t
name|updating_sec
decl_stmt|;
DECL|member|error_sec
name|time_t
name|error_sec
decl_stmt|;
DECL|member|last_modified
name|time_t
name|last_modified
decl_stmt|;
DECL|member|date
name|time_t
name|date
decl_stmt|;
DECL|member|etag
name|ngx_str_t
name|etag
decl_stmt|;
DECL|member|vary
name|ngx_str_t
name|vary
decl_stmt|;
DECL|member|variant
name|u_char
name|variant
index|[
name|NGX_HTTP_CACHE_KEY_LEN
index|]
decl_stmt|;
DECL|member|buffer_size
name|size_t
name|buffer_size
decl_stmt|;
DECL|member|header_start
name|size_t
name|header_start
decl_stmt|;
DECL|member|body_start
name|size_t
name|body_start
decl_stmt|;
DECL|member|length
name|off_t
name|length
decl_stmt|;
DECL|member|fs_size
name|off_t
name|fs_size
decl_stmt|;
DECL|member|min_uses
name|ngx_uint_t
name|min_uses
decl_stmt|;
DECL|member|error
name|ngx_uint_t
name|error
decl_stmt|;
DECL|member|valid_msec
name|ngx_uint_t
name|valid_msec
decl_stmt|;
DECL|member|vary_tag
name|ngx_uint_t
name|vary_tag
decl_stmt|;
DECL|member|buf
name|ngx_buf_t
modifier|*
name|buf
decl_stmt|;
DECL|member|file_cache
name|ngx_http_file_cache_t
modifier|*
name|file_cache
decl_stmt|;
DECL|member|node
name|ngx_http_file_cache_node_t
modifier|*
name|node
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|||
name|NGX_COMPAT
operator|)
DECL|member|thread_task
name|ngx_thread_task_t
modifier|*
name|thread_task
decl_stmt|;
endif|#
directive|endif
DECL|member|lock_timeout
name|ngx_msec_t
name|lock_timeout
decl_stmt|;
DECL|member|lock_age
name|ngx_msec_t
name|lock_age
decl_stmt|;
DECL|member|lock_time
name|ngx_msec_t
name|lock_time
decl_stmt|;
DECL|member|wait_time
name|ngx_msec_t
name|wait_time
decl_stmt|;
DECL|member|wait_event
name|ngx_event_t
name|wait_event
decl_stmt|;
DECL|member|lock
name|unsigned
name|lock
range|:
literal|1
decl_stmt|;
DECL|member|waiting
name|unsigned
name|waiting
range|:
literal|1
decl_stmt|;
DECL|member|updated
name|unsigned
name|updated
range|:
literal|1
decl_stmt|;
DECL|member|updating
name|unsigned
name|updating
range|:
literal|1
decl_stmt|;
DECL|member|exists
name|unsigned
name|exists
range|:
literal|1
decl_stmt|;
DECL|member|temp_file
name|unsigned
name|temp_file
range|:
literal|1
decl_stmt|;
DECL|member|purged
name|unsigned
name|purged
range|:
literal|1
decl_stmt|;
DECL|member|reading
name|unsigned
name|reading
range|:
literal|1
decl_stmt|;
DECL|member|secondary
name|unsigned
name|secondary
range|:
literal|1
decl_stmt|;
DECL|member|update_variant
name|unsigned
name|update_variant
range|:
literal|1
decl_stmt|;
DECL|member|background
name|unsigned
name|background
range|:
literal|1
decl_stmt|;
DECL|member|stale_updating
name|unsigned
name|stale_updating
range|:
literal|1
decl_stmt|;
DECL|member|stale_error
name|unsigned
name|stale_error
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2b95979d0308
typedef|typedef
struct|struct
block|{
DECL|member|version
name|ngx_uint_t
name|version
decl_stmt|;
DECL|member|valid_sec
name|time_t
name|valid_sec
decl_stmt|;
DECL|member|updating_sec
name|time_t
name|updating_sec
decl_stmt|;
DECL|member|error_sec
name|time_t
name|error_sec
decl_stmt|;
DECL|member|last_modified
name|time_t
name|last_modified
decl_stmt|;
DECL|member|date
name|time_t
name|date
decl_stmt|;
DECL|member|crc32
name|uint32_t
name|crc32
decl_stmt|;
DECL|member|valid_msec
name|u_short
name|valid_msec
decl_stmt|;
DECL|member|header_start
name|u_short
name|header_start
decl_stmt|;
DECL|member|body_start
name|u_short
name|body_start
decl_stmt|;
DECL|member|etag_len
name|u_char
name|etag_len
decl_stmt|;
DECL|member|etag
name|u_char
name|etag
index|[
name|NGX_HTTP_CACHE_ETAG_LEN
index|]
decl_stmt|;
DECL|member|vary_len
name|u_char
name|vary_len
decl_stmt|;
DECL|member|vary
name|u_char
name|vary
index|[
name|NGX_HTTP_CACHE_VARY_LEN
index|]
decl_stmt|;
DECL|member|variant
name|u_char
name|variant
index|[
name|NGX_HTTP_CACHE_KEY_LEN
index|]
decl_stmt|;
DECL|typedef|ngx_http_file_cache_header_t
block|}
name|ngx_http_file_cache_header_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b95979d0408
typedef|typedef
struct|struct
block|{
DECL|member|rbtree
name|ngx_rbtree_t
name|rbtree
decl_stmt|;
DECL|member|sentinel
name|ngx_rbtree_node_t
name|sentinel
decl_stmt|;
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
DECL|member|cold
name|ngx_atomic_t
name|cold
decl_stmt|;
DECL|member|loading
name|ngx_atomic_t
name|loading
decl_stmt|;
DECL|member|size
name|off_t
name|size
decl_stmt|;
DECL|member|count
name|ngx_uint_t
name|count
decl_stmt|;
DECL|member|watermark
name|ngx_uint_t
name|watermark
decl_stmt|;
DECL|typedef|ngx_http_file_cache_sh_t
block|}
name|ngx_http_file_cache_sh_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_file_cache_s
struct|struct
name|ngx_http_file_cache_s
block|{
DECL|member|sh
name|ngx_http_file_cache_sh_t
modifier|*
name|sh
decl_stmt|;
DECL|member|shpool
name|ngx_slab_pool_t
modifier|*
name|shpool
decl_stmt|;
DECL|member|path
name|ngx_path_t
modifier|*
name|path
decl_stmt|;
DECL|member|min_free
name|off_t
name|min_free
decl_stmt|;
DECL|member|max_size
name|off_t
name|max_size
decl_stmt|;
DECL|member|bsize
name|size_t
name|bsize
decl_stmt|;
DECL|member|inactive
name|time_t
name|inactive
decl_stmt|;
DECL|member|fail_time
name|time_t
name|fail_time
decl_stmt|;
DECL|member|files
name|ngx_uint_t
name|files
decl_stmt|;
DECL|member|loader_files
name|ngx_uint_t
name|loader_files
decl_stmt|;
DECL|member|last
name|ngx_msec_t
name|last
decl_stmt|;
DECL|member|loader_sleep
name|ngx_msec_t
name|loader_sleep
decl_stmt|;
DECL|member|loader_threshold
name|ngx_msec_t
name|loader_threshold
decl_stmt|;
DECL|member|manager_files
name|ngx_uint_t
name|manager_files
decl_stmt|;
DECL|member|manager_sleep
name|ngx_msec_t
name|manager_sleep
decl_stmt|;
DECL|member|manager_threshold
name|ngx_msec_t
name|manager_threshold
decl_stmt|;
DECL|member|shm_zone
name|ngx_shm_zone_t
modifier|*
name|shm_zone
decl_stmt|;
DECL|member|use_temp_path
name|ngx_uint_t
name|use_temp_path
decl_stmt|;
comment|/* unsigned use_temp_path:1 */
block|}
struct|;
end_struct

begin_function_decl
name|ngx_int_t
name|ngx_http_file_cache_new
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_file_cache_create
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_file_cache_create_key
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_file_cache_open
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_file_cache_set_header
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_file_cache_update
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_temp_file_t
modifier|*
name|tf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_file_cache_update_header
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_cache_send
parameter_list|(
name|ngx_http_request_t
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_file_cache_free
parameter_list|(
name|ngx_http_cache_t
modifier|*
name|c
parameter_list|,
name|ngx_temp_file_t
modifier|*
name|tf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|time_t
name|ngx_http_file_cache_valid
parameter_list|(
name|ngx_array_t
modifier|*
name|cache_valid
parameter_list|,
name|ngx_uint_t
name|status
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_http_file_cache_set_slot
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_http_file_cache_valid_set_slot
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|ngx_str_t
name|ngx_http_cache_status
index|[]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CACHE_H_INCLUDED_ */
end_comment

end_unit

