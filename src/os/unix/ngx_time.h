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

begin_ifndef
ifndef|#
directive|ifndef
name|SOLARIS
end_ifndef

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

begin_function_decl
name|void
name|ngx_localtime
parameter_list|(
name|ngx_tm_t
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
value|gettimeofday(tp, NULL);
end_define

begin_define
DECL|macro|ngx_msleep (ms)
define|#
directive|define
name|ngx_msleep
parameter_list|(
name|ms
parameter_list|)
value|usleep(ms * 1000)
end_define

begin_decl_stmt
specifier|extern
name|time_t
name|ngx_cached_time
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_TIME_H_INCLUDED_ */
end_comment

end_unit

