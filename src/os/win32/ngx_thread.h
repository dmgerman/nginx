begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_THREAD_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_THREAD_H_INCLUDED_
define|#
directive|define
name|_NGX_THREAD_H_INCLUDED_
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

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_define
DECL|macro|ngx_thread_volatile
define|#
directive|define
name|ngx_thread_volatile
value|volatile
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !NGX_THREADS */
end_comment

begin_define
DECL|macro|ngx_thread_volatile
define|#
directive|define
name|ngx_thread_volatile
end_define

begin_define
DECL|macro|ngx_log_tid
define|#
directive|define
name|ngx_log_tid
value|0
end_define

begin_define
DECL|macro|TID_T_FMT
define|#
directive|define
name|TID_T_FMT
value|"%d"
end_define

begin_define
DECL|macro|ngx_mutex_lock (m)
define|#
directive|define
name|ngx_mutex_lock
parameter_list|(
name|m
parameter_list|)
value|NGX_OK
end_define

begin_define
DECL|macro|ngx_mutex_unlock (m)
define|#
directive|define
name|ngx_mutex_unlock
parameter_list|(
name|m
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_THREAD_H_INCLUDED_ */
end_comment

end_unit

