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

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_decl_stmt
DECL|variable|ngx_time_mutex
specifier|static
name|ngx_mutex_t
modifier|*
name|ngx_time_mutex
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|ngx_cached_time
name|time_t
name|ngx_cached_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_elapsed_msec
name|ngx_epoch_msec_t
name|ngx_elapsed_msec
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_old_elapsed_msec
name|ngx_epoch_msec_t
name|ngx_old_elapsed_msec
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_start_msec
name|ngx_epoch_msec_t
name|ngx_start_msec
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_cached_gmtime
name|ngx_tm_t
name|ngx_cached_gmtime
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cached_err_log_time
specifier|static
name|u_char
name|cached_err_log_time
index|[]
init|=
literal|"1970/09/28 12:00:00"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_cached_err_log_time
name|ngx_str_t
name|ngx_cached_err_log_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cached_http_time
specifier|static
name|u_char
name|cached_http_time
index|[]
init|=
literal|"Mon, 28 Sep 1970 06:00:00 GMT"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_cached_http_time
name|ngx_str_t
name|ngx_cached_http_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cached_http_log_time
specifier|static
name|u_char
name|cached_http_log_time
index|[]
init|=
literal|"28/Sep/1970:12:00:00"
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_cached_http_log_time
name|ngx_str_t
name|ngx_cached_http_log_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|week
specifier|static
name|char
modifier|*
name|week
index|[]
init|=
block|{
literal|"Sun"
block|,
literal|"Mon"
block|,
literal|"Tue"
block|,
literal|"Wed"
block|,
literal|"Thu"
block|,
literal|"Fir"
block|,
literal|"Sat"
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|months
specifier|static
name|char
modifier|*
name|months
index|[]
init|=
block|{
literal|"Jan"
block|,
literal|"Feb"
block|,
literal|"Mar"
block|,
literal|"Apr"
block|,
literal|"May"
block|,
literal|"Jun"
block|,
literal|"Jul"
block|,
literal|"Aug"
block|,
literal|"Sep"
block|,
literal|"Oct"
block|,
literal|"Nov"
block|,
literal|"Dec"
block|}
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_time_init ()
name|void
name|ngx_time_init
parameter_list|()
block|{
name|struct
name|timeval
name|tv
decl_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|ngx_cached_gmtime
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_tm_t
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|ngx_tm_zone
name|ngx_cached_gmtime
operator|.
name|ngx_tm_zone
operator|=
literal|"GMT"
expr_stmt|;
endif|#
directive|endif
name|ngx_cached_err_log_time
operator|.
name|data
operator|=
name|cached_err_log_time
expr_stmt|;
name|ngx_cached_http_time
operator|.
name|data
operator|=
name|cached_http_time
expr_stmt|;
name|ngx_cached_http_log_time
operator|.
name|data
operator|=
name|cached_http_log_time
expr_stmt|;
name|ngx_cached_time
operator|=
literal|0
expr_stmt|;
name|ngx_gettimeofday
argument_list|(
operator|&
name|tv
argument_list|)
expr_stmt|;
name|ngx_start_msec
operator|=
name|tv
operator|.
name|tv_sec
operator|*
literal|1000
operator|+
name|tv
operator|.
name|tv_usec
operator|/
literal|1000
expr_stmt|;
name|ngx_old_elapsed_msec
operator|=
literal|0
expr_stmt|;
name|ngx_elapsed_msec
operator|=
literal|0
expr_stmt|;
name|ngx_time_update
argument_list|(
name|tv
operator|.
name|tv_sec
argument_list|)
expr_stmt|;
block|}
end_function

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_function
DECL|function|ngx_time_mutex_init (ngx_log_t * log)
name|ngx_int_t
name|ngx_time_mutex_init
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
if|if
condition|(
operator|!
operator|(
name|ngx_time_mutex
operator|=
name|ngx_mutex_init
argument_list|(
name|log
argument_list|,
name|NGX_MUTEX_LIGHT
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_time_update (time_t s)
name|void
name|ngx_time_update
parameter_list|(
name|time_t
name|s
parameter_list|)
block|{
name|ngx_tm_t
name|tm
decl_stmt|;
if|if
condition|(
name|ngx_cached_time
operator|==
name|s
condition|)
block|{
return|return;
block|}
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
if|if
condition|(
name|ngx_mutex_trylock
argument_list|(
name|ngx_time_mutex
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return;
block|}
endif|#
directive|endif
name|ngx_cached_time
operator|=
name|s
expr_stmt|;
name|ngx_gmtime
argument_list|(
name|ngx_cached_time
argument_list|,
operator|&
name|ngx_cached_gmtime
argument_list|)
expr_stmt|;
name|ngx_cached_http_time
operator|.
name|len
operator|=
name|ngx_snprintf
argument_list|(
operator|(
name|char
operator|*
operator|)
name|ngx_cached_http_time
operator|.
name|data
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Mon, 28 Sep 1970 06:00:00 GMT"
argument_list|)
argument_list|,
literal|"%s, %02d %s %4d %02d:%02d:%02d GMT"
argument_list|,
name|week
index|[
name|ngx_cached_gmtime
operator|.
name|ngx_tm_wday
index|]
argument_list|,
name|ngx_cached_gmtime
operator|.
name|ngx_tm_mday
argument_list|,
name|months
index|[
name|ngx_cached_gmtime
operator|.
name|ngx_tm_mon
operator|-
literal|1
index|]
argument_list|,
name|ngx_cached_gmtime
operator|.
name|ngx_tm_year
argument_list|,
name|ngx_cached_gmtime
operator|.
name|ngx_tm_hour
argument_list|,
name|ngx_cached_gmtime
operator|.
name|ngx_tm_min
argument_list|,
name|ngx_cached_gmtime
operator|.
name|ngx_tm_sec
argument_list|)
expr_stmt|;
name|ngx_localtime
argument_list|(
operator|&
name|tm
argument_list|)
expr_stmt|;
name|ngx_cached_err_log_time
operator|.
name|len
operator|=
name|ngx_snprintf
argument_list|(
operator|(
name|char
operator|*
operator|)
name|ngx_cached_err_log_time
operator|.
name|data
argument_list|,
sizeof|sizeof
argument_list|(
literal|"1970/09/28 12:00:00"
argument_list|)
argument_list|,
literal|"%4d/%02d/%02d %02d:%02d:%02d"
argument_list|,
name|tm
operator|.
name|ngx_tm_year
argument_list|,
name|tm
operator|.
name|ngx_tm_mon
argument_list|,
name|tm
operator|.
name|ngx_tm_mday
argument_list|,
name|tm
operator|.
name|ngx_tm_hour
argument_list|,
name|tm
operator|.
name|ngx_tm_min
argument_list|,
name|tm
operator|.
name|ngx_tm_sec
argument_list|)
expr_stmt|;
name|ngx_cached_http_log_time
operator|.
name|len
operator|=
name|ngx_snprintf
argument_list|(
operator|(
name|char
operator|*
operator|)
name|ngx_cached_http_log_time
operator|.
name|data
argument_list|,
sizeof|sizeof
argument_list|(
literal|"28/Sep/1970:12:00:00"
argument_list|)
argument_list|,
literal|"%02d/%s/%d:%02d:%02d:%02d"
argument_list|,
name|tm
operator|.
name|ngx_tm_mday
argument_list|,
name|months
index|[
name|tm
operator|.
name|ngx_tm_mon
operator|-
literal|1
index|]
argument_list|,
name|tm
operator|.
name|ngx_tm_year
argument_list|,
name|tm
operator|.
name|ngx_tm_hour
argument_list|,
name|tm
operator|.
name|ngx_tm_min
argument_list|,
name|tm
operator|.
name|ngx_tm_sec
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
name|ngx_mutex_unlock
argument_list|(
name|ngx_time_mutex
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
DECL|function|ngx_http_time (u_char * buf,time_t t)
name|size_t
name|ngx_http_time
parameter_list|(
name|u_char
modifier|*
name|buf
parameter_list|,
name|time_t
name|t
parameter_list|)
block|{
name|ngx_tm_t
name|tm
decl_stmt|;
name|ngx_gmtime
argument_list|(
name|t
argument_list|,
operator|&
name|tm
argument_list|)
expr_stmt|;
return|return
name|ngx_snprintf
argument_list|(
operator|(
name|char
operator|*
operator|)
name|buf
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Mon, 28 Sep 1970 06:00:00 GMT"
argument_list|)
argument_list|,
literal|"%s, %02d %s %4d %02d:%02d:%02d GMT"
argument_list|,
name|week
index|[
name|tm
operator|.
name|ngx_tm_wday
index|]
argument_list|,
name|tm
operator|.
name|ngx_tm_mday
argument_list|,
name|months
index|[
name|tm
operator|.
name|ngx_tm_mon
operator|-
literal|1
index|]
argument_list|,
name|tm
operator|.
name|ngx_tm_year
argument_list|,
name|tm
operator|.
name|ngx_tm_hour
argument_list|,
name|tm
operator|.
name|ngx_tm_min
argument_list|,
name|tm
operator|.
name|ngx_tm_sec
argument_list|)
return|;
block|}
end_function

begin_function
DECL|function|ngx_gmtime (time_t t,ngx_tm_t * tp)
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
block|{
name|ngx_int_t
name|sec
decl_stmt|,
name|min
decl_stmt|,
name|hour
decl_stmt|,
name|mday
decl_stmt|,
name|mon
decl_stmt|,
name|year
decl_stmt|,
name|wday
decl_stmt|,
name|yday
decl_stmt|,
name|days
decl_stmt|;
name|days
operator|=
name|t
operator|/
literal|86400
expr_stmt|;
comment|/* Jaunary 1, 1970 was Thursday */
name|wday
operator|=
operator|(
literal|4
operator|+
name|days
operator|)
operator|%
literal|7
expr_stmt|;
name|t
operator|%=
literal|86400
expr_stmt|;
name|hour
operator|=
name|t
operator|/
literal|3600
expr_stmt|;
name|t
operator|%=
literal|3600
expr_stmt|;
name|min
operator|=
name|t
operator|/
literal|60
expr_stmt|;
name|sec
operator|=
name|t
operator|%
literal|60
expr_stmt|;
comment|/* the algorithm based on Gauss's formula */
name|days
operator|=
name|days
operator|-
operator|(
literal|31
operator|+
literal|28
operator|)
operator|+
literal|719527
expr_stmt|;
name|year
operator|=
name|days
operator|*
literal|400
operator|/
operator|(
literal|365
operator|*
literal|400
operator|+
literal|100
operator|-
literal|4
operator|+
literal|1
operator|)
expr_stmt|;
name|yday
operator|=
name|days
operator|-
operator|(
literal|365
operator|*
name|year
operator|+
name|year
operator|/
literal|4
operator|-
name|year
operator|/
literal|100
operator|+
name|year
operator|/
literal|400
operator|)
expr_stmt|;
name|mon
operator|=
operator|(
name|yday
operator|+
literal|31
operator|)
operator|*
literal|12
operator|/
literal|367
expr_stmt|;
name|mday
operator|=
name|yday
operator|-
operator|(
name|mon
operator|*
literal|367
operator|/
literal|12
operator|-
literal|31
operator|)
expr_stmt|;
name|mon
operator|+=
literal|2
expr_stmt|;
if|if
condition|(
name|yday
operator|>=
literal|306
condition|)
block|{
name|yday
operator|-=
literal|306
expr_stmt|;
name|year
operator|++
expr_stmt|;
name|mon
operator|-=
literal|12
expr_stmt|;
if|if
condition|(
name|mday
operator|==
literal|0
condition|)
block|{
comment|/* Jaunary 31 */
name|mon
operator|=
literal|1
expr_stmt|;
name|mday
operator|=
literal|31
expr_stmt|;
block|}
if|else if
condition|(
name|mon
operator|==
literal|2
condition|)
block|{
if|if
condition|(
operator|(
name|year
operator|%
literal|4
operator|==
literal|0
operator|)
operator|&&
operator|(
name|year
operator|%
literal|100
operator|||
operator|(
name|year
operator|%
literal|400
operator|==
literal|0
operator|)
operator|)
condition|)
block|{
if|if
condition|(
name|mday
operator|>
literal|29
condition|)
block|{
name|mon
operator|=
literal|3
expr_stmt|;
name|mday
operator|-=
literal|29
expr_stmt|;
block|}
block|}
if|else if
condition|(
name|mday
operator|>
literal|28
condition|)
block|{
name|mon
operator|=
literal|3
expr_stmt|;
name|mday
operator|-=
literal|28
expr_stmt|;
block|}
block|}
block|}
else|else
block|{
name|yday
operator|+=
literal|31
operator|+
literal|28
expr_stmt|;
if|if
condition|(
operator|(
name|year
operator|%
literal|4
operator|==
literal|0
operator|)
operator|&&
operator|(
name|year
operator|%
literal|100
operator|||
operator|(
name|year
operator|%
literal|400
operator|==
literal|0
operator|)
operator|)
condition|)
block|{
name|yday
operator|++
expr_stmt|;
block|}
block|}
name|tp
operator|->
name|ngx_tm_sec
operator|=
operator|(
name|ngx_tm_sec_t
operator|)
name|sec
expr_stmt|;
name|tp
operator|->
name|ngx_tm_min
operator|=
operator|(
name|ngx_tm_min_t
operator|)
name|min
expr_stmt|;
name|tp
operator|->
name|ngx_tm_hour
operator|=
operator|(
name|ngx_tm_hour_t
operator|)
name|hour
expr_stmt|;
name|tp
operator|->
name|ngx_tm_mday
operator|=
operator|(
name|ngx_tm_mday_t
operator|)
name|mday
expr_stmt|;
name|tp
operator|->
name|ngx_tm_mon
operator|=
operator|(
name|ngx_tm_mon_t
operator|)
name|mon
expr_stmt|;
name|tp
operator|->
name|ngx_tm_year
operator|=
operator|(
name|ngx_tm_year_t
operator|)
name|year
expr_stmt|;
name|tp
operator|->
name|ngx_tm_wday
operator|=
operator|(
name|ngx_tm_wday_t
operator|)
name|wday
expr_stmt|;
block|}
end_function

end_unit

