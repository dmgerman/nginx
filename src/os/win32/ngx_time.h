begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
DECL|typedef|ngx_epoch_msec_t
typedef|typedef
name|uint64_t
name|ngx_epoch_msec_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_msec_t
typedef|typedef
name|u_int
name|ngx_msec_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_MAX_MSEC
define|#
directive|define
name|NGX_MAX_MSEC
value|(ngx_msec_t) -1
end_define

begin_typedef
DECL|typedef|ngx_tm_t
typedef|typedef
name|SYSTEMTIME
name|ngx_tm_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_mtime_t
typedef|typedef
name|FILETIME
name|ngx_mtime_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_tm_sec
define|#
directive|define
name|ngx_tm_sec
value|wSecond
end_define

begin_define
DECL|macro|ngx_tm_min
define|#
directive|define
name|ngx_tm_min
value|wMinute
end_define

begin_define
DECL|macro|ngx_tm_hour
define|#
directive|define
name|ngx_tm_hour
value|wHour
end_define

begin_define
DECL|macro|ngx_tm_mday
define|#
directive|define
name|ngx_tm_mday
value|wDay
end_define

begin_define
DECL|macro|ngx_tm_mon
define|#
directive|define
name|ngx_tm_mon
value|wMonth
end_define

begin_define
DECL|macro|ngx_tm_year
define|#
directive|define
name|ngx_tm_year
value|wYear
end_define

begin_define
DECL|macro|ngx_tm_wday
define|#
directive|define
name|ngx_tm_wday
value|wDayOfWeek
end_define

begin_define
DECL|macro|ngx_tm_sec_t
define|#
directive|define
name|ngx_tm_sec_t
value|u_short
end_define

begin_define
DECL|macro|ngx_tm_min_t
define|#
directive|define
name|ngx_tm_min_t
value|u_short
end_define

begin_define
DECL|macro|ngx_tm_hour_t
define|#
directive|define
name|ngx_tm_hour_t
value|u_short
end_define

begin_define
DECL|macro|ngx_tm_mday_t
define|#
directive|define
name|ngx_tm_mday_t
value|u_short
end_define

begin_define
DECL|macro|ngx_tm_mon_t
define|#
directive|define
name|ngx_tm_mon_t
value|u_short
end_define

begin_define
DECL|macro|ngx_tm_year_t
define|#
directive|define
name|ngx_tm_year_t
value|u_short
end_define

begin_define
DECL|macro|ngx_tm_wday_t
define|#
directive|define
name|ngx_tm_wday_t
value|u_short
end_define

begin_define
DECL|macro|ngx_msleep
define|#
directive|define
name|ngx_msleep
value|Sleep
end_define

begin_define
DECL|macro|ngx_localtime
define|#
directive|define
name|ngx_localtime
value|GetLocalTime
end_define

begin_function_decl
name|void
name|ngx_gettimeofday
parameter_list|(
name|struct
name|timeval
modifier|*
name|tp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_TIME_H_INCLUDED_ */
end_comment

end_unit

