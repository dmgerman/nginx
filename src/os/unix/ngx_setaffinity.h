begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SETAFFINITY_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SETAFFINITY_H_INCLUDED_
define|#
directive|define
name|_NGX_SETAFFINITY_H_INCLUDED_
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SCHED_SETAFFINITY
operator|||
name|NGX_HAVE_CPUSET_SETAFFINITY
operator|)
end_if

begin_define
DECL|macro|NGX_HAVE_CPU_AFFINITY
define|#
directive|define
name|NGX_HAVE_CPU_AFFINITY
value|1
end_define

begin_function_decl
name|void
name|ngx_setaffinity
parameter_list|(
name|uint64_t
name|cpu_affinity
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_setaffinity (cpu_affinity,log)
define|#
directive|define
name|ngx_setaffinity
parameter_list|(
name|cpu_affinity
parameter_list|,
name|log
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
comment|/* _NGX_SETAFFINITY_H_INCLUDED_ */
end_comment

end_unit

