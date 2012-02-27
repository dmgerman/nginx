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
name|_NGX_OPEN_FILE_CACHE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_OPEN_FILE_CACHE_H_INCLUDED_
define|#
directive|define
name|_NGX_OPEN_FILE_CACHE_H_INCLUDED_
end_define

begin_define
DECL|macro|NGX_OPEN_FILE_DIRECTIO_OFF
define|#
directive|define
name|NGX_OPEN_FILE_DIRECTIO_OFF
value|NGX_MAX_OFF_T_VALUE
end_define

begin_typedef
DECL|struct|__anon2c3961950108
typedef|typedef
struct|struct
block|{
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|member|uniq
name|ngx_file_uniq_t
name|uniq
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|size
name|off_t
name|size
decl_stmt|;
DECL|member|fs_size
name|off_t
name|fs_size
decl_stmt|;
DECL|member|directio
name|off_t
name|directio
decl_stmt|;
DECL|member|read_ahead
name|size_t
name|read_ahead
decl_stmt|;
DECL|member|err
name|ngx_err_t
name|err
decl_stmt|;
DECL|member|failed
name|char
modifier|*
name|failed
decl_stmt|;
DECL|member|valid
name|time_t
name|valid
decl_stmt|;
DECL|member|min_uses
name|ngx_uint_t
name|min_uses
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_OPENAT
operator|)
DECL|member|disable_symlinks_from
name|size_t
name|disable_symlinks_from
decl_stmt|;
DECL|member|disable_symlinks
name|unsigned
name|disable_symlinks
range|:
literal|2
decl_stmt|;
endif|#
directive|endif
DECL|member|test_dir
name|unsigned
name|test_dir
range|:
literal|1
decl_stmt|;
DECL|member|test_only
name|unsigned
name|test_only
range|:
literal|1
decl_stmt|;
DECL|member|log
name|unsigned
name|log
range|:
literal|1
decl_stmt|;
DECL|member|errors
name|unsigned
name|errors
range|:
literal|1
decl_stmt|;
DECL|member|events
name|unsigned
name|events
range|:
literal|1
decl_stmt|;
DECL|member|is_dir
name|unsigned
name|is_dir
range|:
literal|1
decl_stmt|;
DECL|member|is_file
name|unsigned
name|is_file
range|:
literal|1
decl_stmt|;
DECL|member|is_link
name|unsigned
name|is_link
range|:
literal|1
decl_stmt|;
DECL|member|is_exec
name|unsigned
name|is_exec
range|:
literal|1
decl_stmt|;
DECL|member|is_directio
name|unsigned
name|is_directio
range|:
literal|1
decl_stmt|;
DECL|typedef|ngx_open_file_info_t
block|}
name|ngx_open_file_info_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_cached_open_file_t
typedef|typedef
name|struct
name|ngx_cached_open_file_s
name|ngx_cached_open_file_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_cached_open_file_s
struct|struct
name|ngx_cached_open_file_s
block|{
DECL|member|node
name|ngx_rbtree_node_t
name|node
decl_stmt|;
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
DECL|member|name
name|u_char
modifier|*
name|name
decl_stmt|;
DECL|member|created
name|time_t
name|created
decl_stmt|;
DECL|member|accessed
name|time_t
name|accessed
decl_stmt|;
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|member|uniq
name|ngx_file_uniq_t
name|uniq
decl_stmt|;
DECL|member|mtime
name|time_t
name|mtime
decl_stmt|;
DECL|member|size
name|off_t
name|size
decl_stmt|;
DECL|member|err
name|ngx_err_t
name|err
decl_stmt|;
DECL|member|uses
name|uint32_t
name|uses
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_OPENAT
operator|)
DECL|member|disable_symlinks_from
name|size_t
name|disable_symlinks_from
decl_stmt|;
DECL|member|disable_symlinks
name|unsigned
name|disable_symlinks
range|:
literal|2
decl_stmt|;
endif|#
directive|endif
DECL|member|count
name|unsigned
name|count
range|:
literal|24
decl_stmt|;
DECL|member|close
name|unsigned
name|close
range|:
literal|1
decl_stmt|;
DECL|member|use_event
name|unsigned
name|use_event
range|:
literal|1
decl_stmt|;
DECL|member|is_dir
name|unsigned
name|is_dir
range|:
literal|1
decl_stmt|;
DECL|member|is_file
name|unsigned
name|is_file
range|:
literal|1
decl_stmt|;
DECL|member|is_link
name|unsigned
name|is_link
range|:
literal|1
decl_stmt|;
DECL|member|is_exec
name|unsigned
name|is_exec
range|:
literal|1
decl_stmt|;
DECL|member|is_directio
name|unsigned
name|is_directio
range|:
literal|1
decl_stmt|;
DECL|member|event
name|ngx_event_t
modifier|*
name|event
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2c3961950208
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
DECL|member|expire_queue
name|ngx_queue_t
name|expire_queue
decl_stmt|;
DECL|member|current
name|ngx_uint_t
name|current
decl_stmt|;
DECL|member|max
name|ngx_uint_t
name|max
decl_stmt|;
DECL|member|inactive
name|time_t
name|inactive
decl_stmt|;
DECL|typedef|ngx_open_file_cache_t
block|}
name|ngx_open_file_cache_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c3961950308
typedef|typedef
struct|struct
block|{
DECL|member|cache
name|ngx_open_file_cache_t
modifier|*
name|cache
decl_stmt|;
DECL|member|file
name|ngx_cached_open_file_t
modifier|*
name|file
decl_stmt|;
DECL|member|min_uses
name|ngx_uint_t
name|min_uses
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|typedef|ngx_open_file_cache_cleanup_t
block|}
name|ngx_open_file_cache_cleanup_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c3961950408
typedef|typedef
struct|struct
block|{
comment|/* ngx_connection_t stub to allow use c->fd as event ident */
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|read
name|ngx_event_t
modifier|*
name|read
decl_stmt|;
DECL|member|write
name|ngx_event_t
modifier|*
name|write
decl_stmt|;
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|member|file
name|ngx_cached_open_file_t
modifier|*
name|file
decl_stmt|;
DECL|member|cache
name|ngx_open_file_cache_t
modifier|*
name|cache
decl_stmt|;
DECL|typedef|ngx_open_file_cache_event_t
block|}
name|ngx_open_file_cache_event_t
typedef|;
end_typedef

begin_function_decl
name|ngx_open_file_cache_t
modifier|*
name|ngx_open_file_cache_init
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_uint_t
name|max
parameter_list|,
name|time_t
name|inactive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_open_cached_file
parameter_list|(
name|ngx_open_file_cache_t
modifier|*
name|cache
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|ngx_open_file_info_t
modifier|*
name|of
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_OPEN_FILE_CACHE_H_INCLUDED_ */
end_comment

end_unit

