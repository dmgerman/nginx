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
file|<ngx_thread_pool.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_LINUX
operator|)
end_if

begin_comment
comment|/*  * Linux thread id is a pid of thread created by clone(2),  * glibc does not provide a wrapper for gettid().  */
end_comment

begin_function
name|ngx_tid_t
DECL|function|ngx_thread_tid (void)
name|ngx_thread_tid
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|syscall
argument_list|(
name|SYS_gettid
argument_list|)
return|;
block|}
end_function

begin_elif
elif|#
directive|elif
operator|(
name|NGX_FREEBSD
operator|)
operator|&&
operator|(
name|__FreeBSD_version
operator|>=
literal|900031
operator|)
end_elif

begin_include
include|#
directive|include
file|<pthread_np.h>
end_include

begin_function
name|ngx_tid_t
DECL|function|ngx_thread_tid (void)
name|ngx_thread_tid
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|pthread_getthreadid_np
argument_list|()
return|;
block|}
end_function

begin_elif
elif|#
directive|elif
operator|(
name|NGX_DARWIN
operator|)
end_elif

begin_comment
comment|/*  * MacOSX thread has two thread ids:  *  * 1) MacOSX 10.6 (Snow Leoprad) has pthread_threadid_np() returning  *    an uint64_t value, which is obtained using the __thread_selfid()  *    syscall.  It is a number above 300,000.  */
end_comment

begin_function
name|ngx_tid_t
DECL|function|ngx_thread_tid (void)
name|ngx_thread_tid
parameter_list|(
name|void
parameter_list|)
block|{
name|uint64_t
name|tid
decl_stmt|;
operator|(
name|void
operator|)
name|pthread_threadid_np
argument_list|(
name|NULL
argument_list|,
operator|&
name|tid
argument_list|)
expr_stmt|;
return|return
name|tid
return|;
block|}
end_function

begin_comment
comment|/*  * 2) Kernel thread mach_port_t returned by pthread_mach_thread_np().  *    It is a number in range 100-100,000.  *  * return pthread_mach_thread_np(pthread_self());  */
end_comment

begin_else
else|#
directive|else
end_else

begin_function
name|ngx_tid_t
DECL|function|ngx_thread_tid (void)
name|ngx_thread_tid
parameter_list|(
name|void
parameter_list|)
block|{
return|return
operator|(
name|uint64_t
operator|)
operator|(
name|uintptr_t
operator|)
name|pthread_self
argument_list|()
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

