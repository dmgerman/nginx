begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_typedef
DECL|struct|__anon2c6e28c50108
typedef|typedef
struct|struct
block|{
DECL|member|crc
name|uint32_t
name|crc
decl_stmt|;
DECL|member|key
name|ngx_str_t
name|key
decl_stmt|;
DECL|member|accessed
name|time_t
name|accessed
decl_stmt|;
DECL|member|refs
name|unsigned
name|refs
range|:
literal|20
decl_stmt|;
comment|/* 1048576 references */
DECL|member|count
name|unsigned
name|count
range|:
literal|2
decl_stmt|;
comment|/* lazy allocation: the 4 uses */
DECL|member|deleted
name|unsigned
name|deleted
range|:
literal|1
decl_stmt|;
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|member|last_modified
name|time_t
name|last_modified
decl_stmt|;
DECL|member|updated
name|time_t
name|updated
decl_stmt|;
DECL|union|__anon2c6e28c5020a
union|union
block|{
DECL|member|size
name|off_t
name|size
decl_stmt|;
DECL|member|value
name|ngx_str_t
name|value
decl_stmt|;
DECL|member|data
block|}
name|data
union|;
DECL|typedef|ngx_http_cache_t
block|}
name|ngx_http_cache_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c6e28c50308
typedef|typedef
struct|struct
block|{
DECL|member|expires
name|time_t
name|expires
decl_stmt|;
DECL|member|last_modified
name|time_t
name|last_modified
decl_stmt|;
DECL|member|date
name|time_t
name|date
decl_stmt|;
DECL|member|length
name|off_t
name|length
decl_stmt|;
DECL|member|key_len
name|size_t
name|key_len
decl_stmt|;
DECL|member|key
name|char
name|key
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|ngx_http_cache_header_t
block|}
name|ngx_http_cache_header_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_CACHE_HASH
define|#
directive|define
name|NGX_HTTP_CACHE_HASH
value|7
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_NELTS
define|#
directive|define
name|NGX_HTTP_CACHE_NELTS
value|4
end_define

begin_typedef
DECL|struct|__anon2c6e28c50408
typedef|typedef
struct|struct
block|{
DECL|member|elts
name|ngx_http_cache_t
modifier|*
name|elts
decl_stmt|;
DECL|member|hash
name|size_t
name|hash
decl_stmt|;
DECL|member|nelts
name|size_t
name|nelts
decl_stmt|;
DECL|member|life
name|time_t
name|life
decl_stmt|;
DECL|member|update
name|time_t
name|update
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|typedef|ngx_http_cache_hash_t
block|}
name|ngx_http_cache_hash_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c6e28c50508
typedef|typedef
struct|struct
block|{
DECL|member|hash
name|ngx_http_cache_hash_t
modifier|*
name|hash
decl_stmt|;
DECL|member|cache
name|ngx_http_cache_t
modifier|*
name|cache
decl_stmt|;
DECL|member|file
name|ngx_file_t
name|file
decl_stmt|;
DECL|member|key
name|ngx_str_t
name|key
decl_stmt|;
DECL|member|crc
name|uint32_t
name|crc
decl_stmt|;
DECL|member|md5
name|u_char
name|md5
index|[
literal|16
index|]
decl_stmt|;
DECL|member|path
name|ngx_path_t
modifier|*
name|path
decl_stmt|;
DECL|member|buf
name|ngx_hunk_t
modifier|*
name|buf
decl_stmt|;
DECL|member|expires
name|time_t
name|expires
decl_stmt|;
DECL|member|last_modified
name|time_t
name|last_modified
decl_stmt|;
DECL|member|date
name|time_t
name|date
decl_stmt|;
DECL|member|length
name|off_t
name|length
decl_stmt|;
DECL|member|header_size
name|ssize_t
name|header_size
decl_stmt|;
DECL|member|file_start
name|size_t
name|file_start
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_http_cache_ctx_t
block|}
name|ngx_http_cache_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c6e28c50608
typedef|typedef
struct|struct
block|{
DECL|member|open_files
name|ngx_http_cache_hash_t
modifier|*
name|open_files
decl_stmt|;
DECL|typedef|ngx_http_cache_conf_t
block|}
name|ngx_http_cache_conf_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_http_cache_unlock (ch,ce)
define|#
directive|define
name|ngx_http_cache_unlock
parameter_list|(
name|ch
parameter_list|,
name|ce
parameter_list|)
define|\
value|ngx_mutex_lock(&ch->mutex);                                      \             ce->refs--;                                                      \             ngx_mutex_unlock(&ch->mutex);
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_STALE
define|#
directive|define
name|NGX_HTTP_CACHE_STALE
value|1
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_AGED
define|#
directive|define
name|NGX_HTTP_CACHE_AGED
value|2
end_define

begin_define
DECL|macro|NGX_HTTP_CACHE_THE_SAME
define|#
directive|define
name|NGX_HTTP_CACHE_THE_SAME
value|3
end_define

begin_function_decl
name|int
name|ngx_http_cache_get_file
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_cache_ctx_t
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_cache_open_file
parameter_list|(
name|ngx_http_cache_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_file_uniq_t
name|uniq
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_http_cache_update_file
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_cache_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_str_t
modifier|*
name|temp_file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_http_cache_t
modifier|*
name|ngx_http_cache_get
parameter_list|(
name|ngx_http_cache_hash_t
modifier|*
name|cache
parameter_list|,
name|ngx_str_t
modifier|*
name|key
parameter_list|,
name|uint32_t
modifier|*
name|crc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_http_cache_t
modifier|*
name|ngx_http_cache_alloc
parameter_list|(
name|ngx_http_cache_hash_t
modifier|*
name|cache
parameter_list|,
name|ngx_str_t
modifier|*
name|key
parameter_list|,
name|uint32_t
name|crc
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_garbage_collector_http_cache_handler
parameter_list|(
name|ngx_gc_t
modifier|*
name|gc
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|ngx_dir_t
modifier|*
name|dir
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_http_set_cache_slot
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
name|ngx_module_t
name|ngx_http_cache_module
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

