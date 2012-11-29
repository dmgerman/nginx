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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|)
end_if

begin_decl_stmt
DECL|variable|ngx_file_aio
name|ngx_uint_t
name|ngx_file_aio
init|=
literal|1
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|ssize_t
DECL|function|ngx_read_file (ngx_file_t * file,u_char * buf,size_t size,off_t offset)
name|ngx_read_file
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|,
name|off_t
name|offset
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|;
name|ngx_log_debug4
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|file
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"read: %d, %p, %uz, %O"
argument_list|,
name|file
operator|->
name|fd
argument_list|,
name|buf
argument_list|,
name|size
argument_list|,
name|offset
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_PREAD
operator|)
name|n
operator|=
name|pread
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|buf
argument_list|,
name|size
argument_list|,
name|offset
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"pread() \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
else|#
directive|else
if|if
condition|(
name|file
operator|->
name|sys_offset
operator|!=
name|offset
condition|)
block|{
if|if
condition|(
name|lseek
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|offset
argument_list|,
name|SEEK_SET
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"lseek() \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|file
operator|->
name|sys_offset
operator|=
name|offset
expr_stmt|;
block|}
name|n
operator|=
name|read
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|buf
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"read() \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|file
operator|->
name|sys_offset
operator|+=
name|n
expr_stmt|;
endif|#
directive|endif
name|file
operator|->
name|offset
operator|+=
name|n
expr_stmt|;
return|return
name|n
return|;
block|}
end_function

begin_function
name|ssize_t
DECL|function|ngx_write_file (ngx_file_t * file,u_char * buf,size_t size,off_t offset)
name|ngx_write_file
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|,
name|off_t
name|offset
parameter_list|)
block|{
name|ssize_t
name|n
decl_stmt|,
name|written
decl_stmt|;
name|ngx_log_debug4
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|file
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"write: %d, %p, %uz, %O"
argument_list|,
name|file
operator|->
name|fd
argument_list|,
name|buf
argument_list|,
name|size
argument_list|,
name|offset
argument_list|)
expr_stmt|;
name|written
operator|=
literal|0
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_PWRITE
operator|)
for|for
control|(
init|;
condition|;
control|)
block|{
name|n
operator|=
name|pwrite
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|buf
operator|+
name|written
argument_list|,
name|size
argument_list|,
name|offset
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"pwrite() \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|file
operator|->
name|offset
operator|+=
name|n
expr_stmt|;
name|written
operator|+=
name|n
expr_stmt|;
if|if
condition|(
operator|(
name|size_t
operator|)
name|n
operator|==
name|size
condition|)
block|{
return|return
name|written
return|;
block|}
name|offset
operator|+=
name|n
expr_stmt|;
name|size
operator|-=
name|n
expr_stmt|;
block|}
else|#
directive|else
if|if
condition|(
name|file
operator|->
name|sys_offset
operator|!=
name|offset
condition|)
block|{
if|if
condition|(
name|lseek
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|offset
argument_list|,
name|SEEK_SET
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"lseek() \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|file
operator|->
name|sys_offset
operator|=
name|offset
expr_stmt|;
block|}
for|for
control|(
init|;
condition|;
control|)
block|{
name|n
operator|=
name|write
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|buf
operator|+
name|written
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"write() \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|file
operator|->
name|offset
operator|+=
name|n
expr_stmt|;
name|written
operator|+=
name|n
expr_stmt|;
if|if
condition|(
operator|(
name|size_t
operator|)
name|n
operator|==
name|size
condition|)
block|{
return|return
name|written
return|;
block|}
name|size
operator|-=
name|n
expr_stmt|;
block|}
endif|#
directive|endif
block|}
end_function

begin_function
name|ngx_fd_t
DECL|function|ngx_open_tempfile (u_char * name,ngx_uint_t persistent,ngx_uint_t access)
name|ngx_open_tempfile
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|,
name|ngx_uint_t
name|persistent
parameter_list|,
name|ngx_uint_t
name|access
parameter_list|)
block|{
name|ngx_fd_t
name|fd
decl_stmt|;
name|fd
operator|=
name|open
argument_list|(
operator|(
specifier|const
name|char
operator|*
operator|)
name|name
argument_list|,
name|O_CREAT
operator||
name|O_EXCL
operator||
name|O_RDWR
argument_list|,
name|access
condition|?
name|access
else|:
literal|0600
argument_list|)
expr_stmt|;
if|if
condition|(
name|fd
operator|!=
operator|-
literal|1
operator|&&
operator|!
name|persistent
condition|)
block|{
operator|(
name|void
operator|)
name|unlink
argument_list|(
operator|(
specifier|const
name|char
operator|*
operator|)
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|fd
return|;
block|}
end_function

begin_define
DECL|macro|NGX_IOVS
define|#
directive|define
name|NGX_IOVS
value|8
end_define

begin_function
name|ssize_t
DECL|function|ngx_write_chain_to_file (ngx_file_t * file,ngx_chain_t * cl,off_t offset,ngx_pool_t * pool)
name|ngx_write_chain_to_file
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|ngx_chain_t
modifier|*
name|cl
parameter_list|,
name|off_t
name|offset
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
name|u_char
modifier|*
name|prev
decl_stmt|;
name|size_t
name|size
decl_stmt|;
name|ssize_t
name|total
decl_stmt|,
name|n
decl_stmt|;
name|ngx_array_t
name|vec
decl_stmt|;
name|struct
name|iovec
modifier|*
name|iov
decl_stmt|,
name|iovs
index|[
name|NGX_IOVS
index|]
decl_stmt|;
comment|/* use pwrite() if there is the only buf in a chain */
if|if
condition|(
name|cl
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
return|return
name|ngx_write_file
argument_list|(
name|file
argument_list|,
name|cl
operator|->
name|buf
operator|->
name|pos
argument_list|,
operator|(
name|size_t
operator|)
operator|(
name|cl
operator|->
name|buf
operator|->
name|last
operator|-
name|cl
operator|->
name|buf
operator|->
name|pos
operator|)
argument_list|,
name|offset
argument_list|)
return|;
block|}
name|total
operator|=
literal|0
expr_stmt|;
name|vec
operator|.
name|elts
operator|=
name|iovs
expr_stmt|;
name|vec
operator|.
name|size
operator|=
sizeof|sizeof
argument_list|(
expr|struct
name|iovec
argument_list|)
expr_stmt|;
name|vec
operator|.
name|nalloc
operator|=
name|NGX_IOVS
expr_stmt|;
name|vec
operator|.
name|pool
operator|=
name|pool
expr_stmt|;
do|do
block|{
name|prev
operator|=
name|NULL
expr_stmt|;
name|iov
operator|=
name|NULL
expr_stmt|;
name|size
operator|=
literal|0
expr_stmt|;
name|vec
operator|.
name|nelts
operator|=
literal|0
expr_stmt|;
comment|/* create the iovec and coalesce the neighbouring bufs */
while|while
condition|(
name|cl
operator|&&
name|vec
operator|.
name|nelts
operator|<
name|IOV_MAX
condition|)
block|{
if|if
condition|(
name|prev
operator|==
name|cl
operator|->
name|buf
operator|->
name|pos
condition|)
block|{
name|iov
operator|->
name|iov_len
operator|+=
name|cl
operator|->
name|buf
operator|->
name|last
operator|-
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
block|}
else|else
block|{
name|iov
operator|=
name|ngx_array_push
argument_list|(
operator|&
name|vec
argument_list|)
expr_stmt|;
if|if
condition|(
name|iov
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|iov
operator|->
name|iov_base
operator|=
operator|(
name|void
operator|*
operator|)
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|iov
operator|->
name|iov_len
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
operator|-
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
block|}
name|size
operator|+=
name|cl
operator|->
name|buf
operator|->
name|last
operator|-
name|cl
operator|->
name|buf
operator|->
name|pos
expr_stmt|;
name|prev
operator|=
name|cl
operator|->
name|buf
operator|->
name|last
expr_stmt|;
name|cl
operator|=
name|cl
operator|->
name|next
expr_stmt|;
block|}
comment|/* use pwrite() if there is the only iovec buffer */
if|if
condition|(
name|vec
operator|.
name|nelts
operator|==
literal|1
condition|)
block|{
name|iov
operator|=
name|vec
operator|.
name|elts
expr_stmt|;
name|n
operator|=
name|ngx_write_file
argument_list|(
name|file
argument_list|,
operator|(
name|u_char
operator|*
operator|)
name|iov
index|[
literal|0
index|]
operator|.
name|iov_base
argument_list|,
name|iov
index|[
literal|0
index|]
operator|.
name|iov_len
argument_list|,
name|offset
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|n
return|;
block|}
return|return
name|total
operator|+
name|n
return|;
block|}
if|if
condition|(
name|file
operator|->
name|sys_offset
operator|!=
name|offset
condition|)
block|{
if|if
condition|(
name|lseek
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|offset
argument_list|,
name|SEEK_SET
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"lseek() \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|file
operator|->
name|sys_offset
operator|=
name|offset
expr_stmt|;
block|}
name|n
operator|=
name|writev
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|vec
operator|.
name|elts
argument_list|,
name|vec
operator|.
name|nelts
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"writev() \"%s\" failed"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
operator|(
name|size_t
operator|)
name|n
operator|!=
name|size
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|file
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"writev() \"%s\" has written only %z of %uz"
argument_list|,
name|file
operator|->
name|name
operator|.
name|data
argument_list|,
name|n
argument_list|,
name|size
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|file
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"writev: %d, %z"
argument_list|,
name|file
operator|->
name|fd
argument_list|,
name|n
argument_list|)
expr_stmt|;
name|file
operator|->
name|sys_offset
operator|+=
name|n
expr_stmt|;
name|file
operator|->
name|offset
operator|+=
name|n
expr_stmt|;
name|offset
operator|+=
name|n
expr_stmt|;
name|total
operator|+=
name|n
expr_stmt|;
block|}
do|while
condition|(
name|cl
condition|)
do|;
return|return
name|total
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_set_file_time (u_char * name,ngx_fd_t fd,time_t s)
name|ngx_set_file_time
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|,
name|ngx_fd_t
name|fd
parameter_list|,
name|time_t
name|s
parameter_list|)
block|{
name|struct
name|timeval
name|tv
index|[
literal|2
index|]
decl_stmt|;
name|tv
index|[
literal|0
index|]
operator|.
name|tv_sec
operator|=
name|ngx_time
argument_list|()
expr_stmt|;
name|tv
index|[
literal|0
index|]
operator|.
name|tv_usec
operator|=
literal|0
expr_stmt|;
name|tv
index|[
literal|1
index|]
operator|.
name|tv_sec
operator|=
name|s
expr_stmt|;
name|tv
index|[
literal|1
index|]
operator|.
name|tv_usec
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|utimes
argument_list|(
operator|(
name|char
operator|*
operator|)
name|name
argument_list|,
name|tv
argument_list|)
operator|!=
operator|-
literal|1
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_create_file_mapping (ngx_file_mapping_t * fm)
name|ngx_create_file_mapping
parameter_list|(
name|ngx_file_mapping_t
modifier|*
name|fm
parameter_list|)
block|{
name|fm
operator|->
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|fm
operator|->
name|name
argument_list|,
name|NGX_FILE_RDWR
argument_list|,
name|NGX_FILE_TRUNCATE
argument_list|,
name|NGX_FILE_DEFAULT_ACCESS
argument_list|)
expr_stmt|;
if|if
condition|(
name|fm
operator|->
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|fm
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_open_file_n
literal|" \"%s\" failed"
argument_list|,
name|fm
operator|->
name|name
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
if|if
condition|(
name|ftruncate
argument_list|(
name|fm
operator|->
name|fd
argument_list|,
name|fm
operator|->
name|size
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|fm
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"ftruncate() \"%s\" failed"
argument_list|,
name|fm
operator|->
name|name
argument_list|)
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
name|fm
operator|->
name|addr
operator|=
name|mmap
argument_list|(
name|NULL
argument_list|,
name|fm
operator|->
name|size
argument_list|,
name|PROT_READ
operator||
name|PROT_WRITE
argument_list|,
name|MAP_SHARED
argument_list|,
name|fm
operator|->
name|fd
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|fm
operator|->
name|addr
operator|!=
name|MAP_FAILED
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|fm
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"mmap(%uz) \"%s\" failed"
argument_list|,
name|fm
operator|->
name|size
argument_list|,
name|fm
operator|->
name|name
argument_list|)
expr_stmt|;
name|failed
label|:
if|if
condition|(
name|ngx_close_file
argument_list|(
name|fm
operator|->
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|fm
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|fm
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_close_file_mapping (ngx_file_mapping_t * fm)
name|ngx_close_file_mapping
parameter_list|(
name|ngx_file_mapping_t
modifier|*
name|fm
parameter_list|)
block|{
if|if
condition|(
name|munmap
argument_list|(
name|fm
operator|->
name|addr
argument_list|,
name|fm
operator|->
name|size
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_CRIT
argument_list|,
name|fm
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"munmap(%uz) \"%s\" failed"
argument_list|,
name|fm
operator|->
name|size
argument_list|,
name|fm
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|ngx_close_file
argument_list|(
name|fm
operator|->
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|fm
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|fm
operator|->
name|name
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_open_dir (ngx_str_t * name,ngx_dir_t * dir)
name|ngx_open_dir
parameter_list|(
name|ngx_str_t
modifier|*
name|name
parameter_list|,
name|ngx_dir_t
modifier|*
name|dir
parameter_list|)
block|{
name|dir
operator|->
name|dir
operator|=
name|opendir
argument_list|(
operator|(
specifier|const
name|char
operator|*
operator|)
name|name
operator|->
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|->
name|dir
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|dir
operator|->
name|valid_info
operator|=
literal|0
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_read_dir (ngx_dir_t * dir)
name|ngx_read_dir
parameter_list|(
name|ngx_dir_t
modifier|*
name|dir
parameter_list|)
block|{
name|dir
operator|->
name|de
operator|=
name|readdir
argument_list|(
name|dir
operator|->
name|dir
argument_list|)
expr_stmt|;
if|if
condition|(
name|dir
operator|->
name|de
condition|)
block|{
if|#
directive|if
operator|(
name|NGX_HAVE_D_TYPE
operator|)
name|dir
operator|->
name|type
operator|=
name|dir
operator|->
name|de
operator|->
name|d_type
expr_stmt|;
else|#
directive|else
name|dir
operator|->
name|type
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
return|return
name|NGX_OK
return|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_open_glob (ngx_glob_t * gl)
name|ngx_open_glob
parameter_list|(
name|ngx_glob_t
modifier|*
name|gl
parameter_list|)
block|{
name|int
name|n
decl_stmt|;
name|n
operator|=
name|glob
argument_list|(
operator|(
name|char
operator|*
operator|)
name|gl
operator|->
name|pattern
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
operator|&
name|gl
operator|->
name|pglob
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
ifdef|#
directive|ifdef
name|GLOB_NOMATCH
if|if
condition|(
name|n
operator|==
name|GLOB_NOMATCH
operator|&&
name|gl
operator|->
name|test
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
endif|#
directive|endif
return|return
name|NGX_ERROR
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_read_glob (ngx_glob_t * gl,ngx_str_t * name)
name|ngx_read_glob
parameter_list|(
name|ngx_glob_t
modifier|*
name|gl
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
block|{
name|size_t
name|count
decl_stmt|;
ifdef|#
directive|ifdef
name|GLOB_NOMATCH
name|count
operator|=
operator|(
name|size_t
operator|)
name|gl
operator|->
name|pglob
operator|.
name|gl_pathc
expr_stmt|;
else|#
directive|else
name|count
operator|=
operator|(
name|size_t
operator|)
name|gl
operator|->
name|pglob
operator|.
name|gl_matchc
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|gl
operator|->
name|n
operator|<
name|count
condition|)
block|{
name|name
operator|->
name|len
operator|=
operator|(
name|size_t
operator|)
name|ngx_strlen
argument_list|(
name|gl
operator|->
name|pglob
operator|.
name|gl_pathv
index|[
name|gl
operator|->
name|n
index|]
argument_list|)
expr_stmt|;
name|name
operator|->
name|data
operator|=
operator|(
name|u_char
operator|*
operator|)
name|gl
operator|->
name|pglob
operator|.
name|gl_pathv
index|[
name|gl
operator|->
name|n
index|]
expr_stmt|;
name|gl
operator|->
name|n
operator|++
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
return|return
name|NGX_DONE
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_close_glob (ngx_glob_t * gl)
name|ngx_close_glob
parameter_list|(
name|ngx_glob_t
modifier|*
name|gl
parameter_list|)
block|{
name|globfree
argument_list|(
operator|&
name|gl
operator|->
name|pglob
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ngx_err_t
DECL|function|ngx_trylock_fd (ngx_fd_t fd)
name|ngx_trylock_fd
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
block|{
name|struct
name|flock
name|fl
decl_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|fl
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|flock
argument_list|)
argument_list|)
expr_stmt|;
name|fl
operator|.
name|l_type
operator|=
name|F_WRLCK
expr_stmt|;
name|fl
operator|.
name|l_whence
operator|=
name|SEEK_SET
expr_stmt|;
if|if
condition|(
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_SETLK
argument_list|,
operator|&
name|fl
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
return|return
name|ngx_errno
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
name|ngx_err_t
DECL|function|ngx_lock_fd (ngx_fd_t fd)
name|ngx_lock_fd
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
block|{
name|struct
name|flock
name|fl
decl_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|fl
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|flock
argument_list|)
argument_list|)
expr_stmt|;
name|fl
operator|.
name|l_type
operator|=
name|F_WRLCK
expr_stmt|;
name|fl
operator|.
name|l_whence
operator|=
name|SEEK_SET
expr_stmt|;
if|if
condition|(
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_SETLKW
argument_list|,
operator|&
name|fl
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
return|return
name|ngx_errno
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_function
name|ngx_err_t
DECL|function|ngx_unlock_fd (ngx_fd_t fd)
name|ngx_unlock_fd
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
block|{
name|struct
name|flock
name|fl
decl_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|fl
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|flock
argument_list|)
argument_list|)
expr_stmt|;
name|fl
operator|.
name|l_type
operator|=
name|F_UNLCK
expr_stmt|;
name|fl
operator|.
name|l_whence
operator|=
name|SEEK_SET
expr_stmt|;
if|if
condition|(
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_SETLK
argument_list|,
operator|&
name|fl
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
return|return
name|ngx_errno
return|;
block|}
return|return
literal|0
return|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_POSIX_FADVISE
operator|)
operator|&&
operator|!
operator|(
name|NGX_HAVE_F_READAHEAD
operator|)
end_if

begin_function
name|ngx_int_t
DECL|function|ngx_read_ahead (ngx_fd_t fd,size_t n)
name|ngx_read_ahead
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|,
name|size_t
name|n
parameter_list|)
block|{
name|int
name|err
decl_stmt|;
name|err
operator|=
name|posix_fadvise
argument_list|(
name|fd
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|POSIX_FADV_SEQUENTIAL
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
operator|==
literal|0
condition|)
block|{
return|return
literal|0
return|;
block|}
name|ngx_set_errno
argument_list|(
name|err
argument_list|)
expr_stmt|;
return|return
name|NGX_FILE_ERROR
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_O_DIRECT
operator|)
end_if

begin_function
name|ngx_int_t
DECL|function|ngx_directio_on (ngx_fd_t fd)
name|ngx_directio_on
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
block|{
name|int
name|flags
decl_stmt|;
name|flags
operator|=
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_GETFL
argument_list|)
expr_stmt|;
if|if
condition|(
name|flags
operator|==
operator|-
literal|1
condition|)
block|{
return|return
name|NGX_FILE_ERROR
return|;
block|}
return|return
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_SETFL
argument_list|,
name|flags
operator||
name|O_DIRECT
argument_list|)
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_directio_off (ngx_fd_t fd)
name|ngx_directio_off
parameter_list|(
name|ngx_fd_t
name|fd
parameter_list|)
block|{
name|int
name|flags
decl_stmt|;
name|flags
operator|=
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_GETFL
argument_list|)
expr_stmt|;
if|if
condition|(
name|flags
operator|==
operator|-
literal|1
condition|)
block|{
return|return
name|NGX_FILE_ERROR
return|;
block|}
return|return
name|fcntl
argument_list|(
name|fd
argument_list|,
name|F_SETFL
argument_list|,
name|flags
operator|&
operator|~
name|O_DIRECT
argument_list|)
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_STATFS
operator|)
end_if

begin_function
name|size_t
DECL|function|ngx_fs_bsize (u_char * name)
name|ngx_fs_bsize
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|)
block|{
name|struct
name|statfs
name|fs
decl_stmt|;
if|if
condition|(
name|statfs
argument_list|(
operator|(
name|char
operator|*
operator|)
name|name
argument_list|,
operator|&
name|fs
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
return|return
literal|512
return|;
block|}
if|if
condition|(
operator|(
name|fs
operator|.
name|f_bsize
operator|%
literal|512
operator|)
operator|!=
literal|0
condition|)
block|{
return|return
literal|512
return|;
block|}
return|return
operator|(
name|size_t
operator|)
name|fs
operator|.
name|f_bsize
return|;
block|}
end_function

begin_elif
elif|#
directive|elif
operator|(
name|NGX_HAVE_STATVFS
operator|)
end_elif

begin_function
name|size_t
DECL|function|ngx_fs_bsize (u_char * name)
name|ngx_fs_bsize
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|)
block|{
name|struct
name|statvfs
name|fs
decl_stmt|;
if|if
condition|(
name|statvfs
argument_list|(
operator|(
name|char
operator|*
operator|)
name|name
argument_list|,
operator|&
name|fs
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
return|return
literal|512
return|;
block|}
if|if
condition|(
operator|(
name|fs
operator|.
name|f_frsize
operator|%
literal|512
operator|)
operator|!=
literal|0
condition|)
block|{
return|return
literal|512
return|;
block|}
return|return
operator|(
name|size_t
operator|)
name|fs
operator|.
name|f_frsize
return|;
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_function
name|size_t
DECL|function|ngx_fs_bsize (u_char * name)
name|ngx_fs_bsize
parameter_list|(
name|u_char
modifier|*
name|name
parameter_list|)
block|{
return|return
literal|512
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

