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
file|<ngx_file.h>
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
literal|"read: %x, %d, %qd"
argument|_ buf _ size _ offset
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
name|NGX_LOG_ERR
argument_list|,
name|file
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
literal|"read() failed"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
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

