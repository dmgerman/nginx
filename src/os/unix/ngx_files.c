begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_array.h>
end_include

begin_include
include|#
directive|include
file|<ngx_file.h>
end_include

begin_include
include|#
directive|include
file|<ngx_files.h>
end_include

begin_function
DECL|function|ngx_read_file (ngx_file_t * file,char * buf,size_t size,off_t offset)
name|ssize_t
name|ngx_read_file
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|char
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
name|ngx_log_debug
argument_list|(
argument|file->log
argument_list|,
literal|"read: %d, %x, %d, %qd"
argument|_                   file->fd _ buf _ size _ offset
argument_list|)
empty_stmt|;
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
literal|"pread() failed"
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
return|return
name|n
return|;
block|}
end_function

begin_function
DECL|function|ngx_write_file (ngx_file_t * file,char * buf,size_t size,off_t offset)
name|ssize_t
name|ngx_write_file
parameter_list|(
name|ngx_file_t
modifier|*
name|file
parameter_list|,
name|char
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
name|n
operator|=
name|pwrite
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
literal|"pwrite() failed"
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
literal|"pwrite() has written only %d of %d"
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
DECL|function|ngx_write_chain_to_file (ngx_file_t * file,ngx_chain_t * cl,off_t offset,ngx_pool_t * pool)
name|ssize_t
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
name|char
modifier|*
name|prev
decl_stmt|;
name|size_t
name|size
decl_stmt|;
name|ssize_t
name|n
decl_stmt|;
name|struct
name|iovec
modifier|*
name|iov
decl_stmt|;
name|ngx_err_t
name|err
decl_stmt|;
name|ngx_array_t
name|io
decl_stmt|;
comment|/* use pwrite() if there's the only hunk in a chain */
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
name|hunk
operator|->
name|pos
argument_list|,
name|cl
operator|->
name|hunk
operator|->
name|last
operator|-
name|cl
operator|->
name|hunk
operator|->
name|pos
argument_list|,
name|offset
argument_list|)
return|;
block|}
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
name|ngx_init_array
argument_list|(
name|io
argument_list|,
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
expr|struct
name|iovec
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
comment|/* create the iovec and coalesce the neighbouring hunks */
while|while
condition|(
name|cl
condition|)
block|{
if|if
condition|(
name|prev
operator|==
name|cl
operator|->
name|hunk
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
name|hunk
operator|->
name|last
operator|-
name|cl
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
block|}
else|else
block|{
name|ngx_test_null
argument_list|(
name|iov
argument_list|,
name|ngx_push_array
argument_list|(
operator|&
name|io
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|iov
operator|->
name|iov_base
operator|=
name|cl
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
name|iov
operator|->
name|iov_len
operator|=
name|cl
operator|->
name|hunk
operator|->
name|last
operator|-
name|cl
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
block|}
name|size
operator|+=
name|cl
operator|->
name|hunk
operator|->
name|last
operator|-
name|cl
operator|->
name|hunk
operator|->
name|pos
expr_stmt|;
name|prev
operator|=
name|cl
operator|->
name|hunk
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
comment|/* use pwrite() if there's the only iovec buffer */
if|if
condition|(
name|io
operator|.
name|nelts
operator|==
literal|1
condition|)
block|{
name|iov
operator|=
name|io
operator|.
name|elts
expr_stmt|;
return|return
name|ngx_write_file
argument_list|(
name|file
argument_list|,
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
return|;
block|}
if|if
condition|(
name|file
operator|->
name|offset
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
literal|"lseek() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
name|n
operator|=
name|writev
argument_list|(
name|file
operator|->
name|fd
argument_list|,
name|io
operator|.
name|elts
argument_list|,
name|io
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
literal|"writev() failed"
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
literal|"writev() has written only %d of %d"
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

begin_if
if|#
directive|if
literal|0
end_if

begin_if
unit|ssize_t ngx_read_file(ngx_file_t *file, char *buf, size_t size, off_t offset) {     if (!file->read->ready) {          ngx_memzero(&file->iocb, sizeof(iocb));         file->iocb.aio_fildes = file->fd;         file->iocb.aio_buf = buf;         file->iocb.aio_nbytes = size;         file->iocb.aio_offset = offset;
if|#
directive|if
operator|(
name|USE_AIO_KQUEUE
operator|)
end_if

begin_endif
unit|file->iocb.aio_sigevent.sigev_notify = SIGEV_KEVENT;         file->iocb.aio_sigevent.sigev_notify_kqueue = tid->kq;         file->iocb.aio_sigevent.sigev_value = (union sigval) file;
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|USE_AIO_SIGNAL
operator|)
end_if

begin_ifndef
unit|file->iocb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;         file->iocb.aio_sigevent.sigev_signo = NGX_SIGAIO;
ifndef|#
directive|ifndef
name|__FreeBSD__
end_ifndef

begin_endif
unit|file->iocb.aio_sigevent.sigev_value.sival_ptr = file;
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_endif
unit|if (aio_read(&file->iocb) == -1) {             ngx_log_error(NGX_LOG_ERR, file->log, ngx_errno,                           "aio_read() failed");             return NGX_ERROR;          n = aio_error(&file->iocb);         if (n == EINPROGRESS)             return NGX_AGAIN;          if (n == -1) {             ngx_log_error(NGX_LOG_ERR, file->log, ngx_errno,                           "aio_read() failed");             return NGX_ERROR;         }     }      ngx_assert(file->iocb.aio_buf == buf), return NGX_ERROR,                "ngx_aio_read_file: another buffer is passed");      n = aio_return(&file->iocb);     if (n == -1) {         ngx_log_error(NGX_LOG_ERR, file->log, ngx_errno,                       "aio_read() failed");         return NGX_ERROR;     }      return n; }
endif|#
directive|endif
end_endif

end_unit

