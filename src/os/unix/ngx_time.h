begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_TIME_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_TIME_H_INCLUDED_
define|#
directive|define
name|_NGX_TIME_H_INCLUDED_
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
DECL|typedef|ngx_msec_t
typedef|typedef
name|ngx_rbtree_key_t
name|ngx_msec_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_msec_int_t
typedef|typedef
name|ngx_rbtree_key_int_t
name|ngx_msec_int_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_tm_t
typedef|typedef
name|struct
name|tm
name|ngx_tm_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_tm_sec
define|#
directive|define
name|ngx_tm_sec
value|tm_sec
end_define

begin_define
DECL|macro|ngx_tm_min
define|#
directive|define
name|ngx_tm_min
value|tm_min
end_define

begin_define
DECL|macro|ngx_tm_hour
define|#
directive|define
name|ngx_tm_hour
value|tm_hour
end_define

begin_define
DECL|macro|ngx_tm_mday
define|#
directive|define
name|ngx_tm_mday
value|tm_mday
end_define

begin_define
DECL|macro|ngx_tm_mon
define|#
directive|define
name|ngx_tm_mon
value|tm_mon
end_define

begin_define
DECL|macro|ngx_tm_year
define|#
directive|define
name|ngx_tm_year
value|tm_year
end_define

begin_define
DECL|macro|ngx_tm_wday
define|#
directive|define
name|ngx_tm_wday
value|tm_wday
end_define

begin_define
DECL|macro|ngx_tm_isdst
define|#
directive|define
name|ngx_tm_isdst
value|tm_isdst
end_define

begin_define
DECL|macro|ngx_tm_sec_t
define|#
directive|define
name|ngx_tm_sec_t
value|int
end_define

begin_define
DECL|macro|ngx_tm_min_t
define|#
directive|define
name|ngx_tm_min_t
value|int
end_define

begin_define
DECL|macro|ngx_tm_hour_t
define|#
directive|define
name|ngx_tm_hour_t
value|int
end_define

begin_define
DECL|macro|ngx_tm_mday_t
define|#
directive|define
name|ngx_tm_mday_t
value|int
end_define

begin_define
DECL|macro|ngx_tm_mon_t
define|#
directive|define
name|ngx_tm_mon_t
value|int
end_define

begin_define
DECL|macro|ngx_tm_year_t
define|#
directive|define
name|ngx_tm_year_t
value|int
end_define

begin_define
DECL|macro|ngx_tm_wday_t
define|#
directive|define
name|ngx_tm_wday_t
value|int
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_GMTOFF
operator|)
end_if

begin_define
DECL|macro|ngx_tm_gmtoff
define|#
directive|define
name|ngx_tm_gmtoff
value|tm_gmtoff
end_define

begin_define
DECL|macro|ngx_tm_zone
define|#
directive|define
name|ngx_tm_zone
value|tm_zone
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_SOLARIS
operator|)
end_if

begin_define
DECL|macro|ngx_timezone (isdst)
define|#
directive|define
name|ngx_timezone
parameter_list|(
name|isdst
parameter_list|)
value|(- (isdst ? altzone : timezone) / 60)
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_timezone (isdst)
define|#
directive|define
name|ngx_timezone
parameter_list|(
name|isdst
parameter_list|)
value|(- (isdst ? timezone + 3600 : timezone) / 60)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_timezone_update
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_localtime
parameter_list|(
name|time_t
name|s
parameter_list|,
name|ngx_tm_t
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_libc_localtime
parameter_list|(
name|time_t
name|s
parameter_list|,
name|struct
name|tm
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_libc_gmtime
parameter_list|(
name|time_t
name|s
parameter_list|,
name|struct
name|tm
modifier|*
name|tm
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_gettimeofday (tp)
define|#
directive|define
name|ngx_gettimeofday
parameter_list|(
name|tp
parameter_list|)
value|(void) gettimeofday(tp, NULL);
end_define

begin_define
DECL|macro|ngx_msleep (ms)
define|#
directive|define
name|ngx_msleep
parameter_list|(
name|ms
parameter_list|)
value|(void) usleep(ms * 1000)
end_define

begin_define
DECL|macro|ngx_sleep (s)
define|#
directive|define
name|ngx_sleep
parameter_list|(
name|s
parameter_list|)
value|(void) sleep(s)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_TIME_H_INCLUDED_ */
end_comment

end_unit

