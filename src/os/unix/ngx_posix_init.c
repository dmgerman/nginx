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

begin_include
include|#
directive|include
file|<nginx.h>
end_include

begin_decl_stmt
DECL|variable|ngx_ncpu
name|ngx_int_t
name|ngx_ncpu
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_max_sockets
name|ngx_int_t
name|ngx_max_sockets
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_inherited_nonblocking
name|ngx_uint_t
name|ngx_inherited_nonblocking
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_tcp_nodelay_and_tcp_nopush
name|ngx_uint_t
name|ngx_tcp_nodelay_and_tcp_nopush
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|rlmt
name|struct
name|rlimit
name|rlmt
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_os_io
name|ngx_os_io_t
name|ngx_os_io
init|=
block|{
name|ngx_unix_recv
block|,
name|ngx_readv_chain
block|,
name|ngx_udp_unix_recv
block|,
name|ngx_unix_send
block|,
name|ngx_writev_chain
block|,
literal|0
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|ngx_int_t
DECL|function|ngx_os_init (ngx_log_t * log)
name|ngx_os_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_uint_t
name|n
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_OS_SPECIFIC_INIT
operator|)
if|if
condition|(
name|ngx_os_specific_init
argument_list|(
name|log
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
endif|#
directive|endif
if|if
condition|(
name|ngx_init_setproctitle
argument_list|(
name|log
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_pagesize
operator|=
name|getpagesize
argument_list|()
expr_stmt|;
name|ngx_cacheline_size
operator|=
name|NGX_CPU_CACHE_LINE
expr_stmt|;
for|for
control|(
name|n
operator|=
name|ngx_pagesize
init|;
name|n
operator|>>=
literal|1
condition|;
name|ngx_pagesize_shift
operator|++
control|)
block|{
comment|/* void */
block|}
if|#
directive|if
operator|(
name|NGX_HAVE_SC_NPROCESSORS_ONLN
operator|)
if|if
condition|(
name|ngx_ncpu
operator|==
literal|0
condition|)
block|{
name|ngx_ncpu
operator|=
name|sysconf
argument_list|(
name|_SC_NPROCESSORS_ONLN
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
if|if
condition|(
name|ngx_ncpu
operator|<
literal|1
condition|)
block|{
name|ngx_ncpu
operator|=
literal|1
expr_stmt|;
block|}
name|ngx_cpuinfo
argument_list|()
expr_stmt|;
if|if
condition|(
name|getrlimit
argument_list|(
name|RLIMIT_NOFILE
argument_list|,
operator|&
name|rlmt
argument_list|)
operator|==
operator|-
literal|1
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
name|errno
argument_list|,
literal|"getrlimit(RLIMIT_NOFILE) failed)"
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_max_sockets
operator|=
operator|(
name|ngx_int_t
operator|)
name|rlmt
operator|.
name|rlim_cur
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_INHERITED_NONBLOCK
operator|||
name|NGX_HAVE_ACCEPT4
operator|)
name|ngx_inherited_nonblocking
operator|=
literal|1
expr_stmt|;
else|#
directive|else
name|ngx_inherited_nonblocking
operator|=
literal|0
expr_stmt|;
endif|#
directive|endif
name|srandom
argument_list|(
name|ngx_time
argument_list|()
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_os_status (ngx_log_t * log)
name|ngx_os_status
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
name|NGINX_VER_BUILD
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|NGX_COMPILER
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"built by "
name|NGX_COMPILER
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_OS_SPECIFIC_INIT
operator|)
name|ngx_os_specific_status
argument_list|(
name|log
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|ngx_log_error
argument_list|(
name|NGX_LOG_NOTICE
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
literal|"getrlimit(RLIMIT_NOFILE): %r:%r"
argument_list|,
name|rlmt
operator|.
name|rlim_cur
argument_list|,
name|rlmt
operator|.
name|rlim_max
argument_list|)
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|ngx_int_t ngx_posix_post_conf_init(ngx_log_t *log) {     ngx_fd_t  pp[2];      if (pipe(pp) == -1) {         ngx_log_error(NGX_LOG_EMERG, log, ngx_errno, "pipe() failed");         return NGX_ERROR;     }      if (dup2(pp[1], STDERR_FILENO) == -1) {         ngx_log_error(NGX_LOG_EMERG, log, errno, "dup2(STDERR) failed");         return NGX_ERROR;     }      if (pp[1]> STDERR_FILENO) {         if (close(pp[1]) == -1) {             ngx_log_error(NGX_LOG_EMERG, log, errno, "close() failed");             return NGX_ERROR;         }     }      return NGX_OK; }
endif|#
directive|endif
end_endif

end_unit

