begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_OS_THREAD_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_OS_THREAD_H_INCLUDED_
define|#
directive|define
name|_NGX_OS_THREAD_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_typedef
DECL|typedef|ngx_os_tid_t
typedef|typedef
name|HANDLE
name|ngx_os_tid_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|int
name|ngx_tid_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
name|LPTHREAD_START_ROUTINE
name|ngx_thread_start_routine_t
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_OS_THREAD_H_INCLUDED_ */
end_comment

end_unit

