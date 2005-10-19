begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_TIMES_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_TIMES_H_INCLUDED_
define|#
directive|define
name|_NGX_TIMES_H_INCLUDED_
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

begin_typedef
DECL|struct|__anon293199660108
typedef|typedef
struct|struct
block|{
DECL|member|sec
name|time_t
name|sec
decl_stmt|;
DECL|member|msec
name|ngx_uint_t
name|msec
decl_stmt|;
DECL|member|gmtoff
name|ngx_int_t
name|gmtoff
decl_stmt|;
DECL|typedef|ngx_time_t
block|}
name|ngx_time_t
typedef|;
end_typedef

begin_function_decl
name|void
name|ngx_time_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_time_update
parameter_list|(
name|time_t
name|sec
parameter_list|,
name|ngx_uint_t
name|msec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_http_time
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|time_t
name|t
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_http_cookie_time
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|time_t
name|t
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_gmtime
parameter_list|(
name|time_t
name|t
parameter_list|,
name|ngx_tm_t
modifier|*
name|tp
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
specifier|volatile
name|ngx_time_t
modifier|*
name|ngx_cached_time
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|ngx_time ()
define|#
directive|define
name|ngx_time
parameter_list|()
value|ngx_cached_time->sec
end_define

begin_define
DECL|macro|ngx_timeofday ()
define|#
directive|define
name|ngx_timeofday
parameter_list|()
value|(ngx_time_t *) ngx_cached_time
end_define

begin_decl_stmt
specifier|extern
specifier|volatile
name|ngx_str_t
name|ngx_cached_err_log_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|volatile
name|ngx_str_t
name|ngx_cached_http_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
specifier|volatile
name|ngx_str_t
name|ngx_cached_http_log_time
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * milliseconds elapsed since epoch and truncated to ngx_msec_t,  * used in event timers  */
end_comment

begin_decl_stmt
specifier|extern
specifier|volatile
name|ngx_msec_t
name|ngx_current_msec
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_TIMES_H_INCLUDED_ */
end_comment

end_unit

