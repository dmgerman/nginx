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

begin_decl_stmt
DECL|variable|ngx_cached_time
name|time_t
name|ngx_cached_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|cached_http_time
specifier|static
name|char
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
name|char
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

begin_function
DECL|function|ngx_time ()
name|time_t
name|ngx_time
parameter_list|()
block|{
return|return
name|ngx_cached_time
return|;
block|}
end_function

begin_comment
comment|/* TODO:  *   cache ngx_tm_t  *   write own gmtime()  *   remove strftime()  *   we can remove localtime_r  */
end_comment

begin_function
DECL|function|ngx_time_update ()
name|void
name|ngx_time_update
parameter_list|()
block|{
name|ngx_tm_t
modifier|*
name|tp
decl_stmt|,
name|tm
decl_stmt|;
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
comment|/* STUB: need to move to ngx_init_time() */
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
if|#
directive|if
literal|0
block_content|days = sec / 86400;     days = days - 31 - 28 + 719527;      year = days * 400 / (365 * 400 + 100 - 4 + 1);     yday = days - (365 * year + year / 4 - year / 100 + year / 400);      month = (yday + 30) * 12 / 367;     mday = yday - (month * 367 / 12 - 31);      if (++month> 11) {         month -= 12;         year++;     }
endif|#
directive|endif
name|tp
operator|=
name|gmtime
argument_list|(
operator|&
name|ngx_cached_time
argument_list|)
expr_stmt|;
name|ngx_cached_http_time
operator|.
name|len
operator|=
name|strftime
argument_list|(
name|ngx_cached_http_time
operator|.
name|data
argument_list|,
sizeof|sizeof
argument_list|(
literal|"Mon, 28 Sep 1970 06:00:00 GMT"
argument_list|)
argument_list|,
literal|"%a, %d %b %Y %H:%M:%S GMT"
argument_list|,
name|tp
argument_list|)
expr_stmt|;
name|ngx_localtime
argument_list|(
operator|&
name|tm
argument_list|)
expr_stmt|;
name|ngx_cached_http_log_time
operator|.
name|len
operator|=
name|ngx_snprintf
argument_list|(
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
block|}
end_function

end_unit

