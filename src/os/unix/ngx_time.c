begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_time.h>
end_include

begin_function
DECL|function|ngx_localtime (ngx_tm_t * tm)
name|void
name|ngx_localtime
parameter_list|(
name|ngx_tm_t
modifier|*
name|tm
parameter_list|)
block|{
name|time_t
name|clock
init|=
name|time
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|localtime_r
argument_list|(
operator|&
name|clock
argument_list|,
name|tm
argument_list|)
expr_stmt|;
name|tm
operator|->
name|ngx_tm_mon
operator|++
expr_stmt|;
name|tm
operator|->
name|ngx_tm_year
operator|+=
literal|1900
expr_stmt|;
block|}
end_function

begin_function
DECL|function|ngx_msec (void)
name|u_int
name|ngx_msec
parameter_list|(
name|void
parameter_list|)
block|{
name|struct
name|timeval
name|tv
decl_stmt|;
name|gettimeofday
argument_list|(
operator|&
name|tv
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
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
return|;
block|}
end_function

begin_if
if|#
directive|if
literal|0
end_if

begin_comment
unit|typedef struct {     int busy;     u_int_64 msec;     time_t sec;     tm;     http_time_len;     http_time[n]; };  volatile *ngx_time_p;  ngx_time() {     p = ngx_time_p; }  ngx_update_time() {     u_int64   msec;     struct timeval  tv;      gettimeofday(&tv, NULL);      msec = (unsigned long) tv.tv_sec * 1000 + tv.tv_usec / 1000;     p = ngx_time_p;
comment|/* minimum can be for example 0, 10, 50 or 100 ms */
end_comment

begin_comment
unit|if (tv_sec> p->sec || msec - p->msec>= minimum) {         old_p = p;
comment|/* max_tries< max_slots - 10,            max_slots should be more than max of threads */
end_comment

begin_comment
unit|for (
comment|/* void */
end_comment

begin_comment
unit|; i< max_tries; i++) {             if (++p>= last_slot)                 p = first_slot;              if (!test_and_set(p->busy)                 break;         }          if (i == max_tries) {             ngx_log_error();             return;         }          if (tv_sec> p->sec) {             p->sec = tv.tv.sec;             p->msec = msec;             localtime_r(&tv.tv_sec, tm);             make http stirng;          } else {             ngx_memcpy(p->sec, old_p->sec, sizeof() - offset_of(, sec));             p->msec = msec;         }
comment|/* here can be too seldom and non-critical race condition */
end_comment

begin_endif
unit|if (ngx_time_p == old_p)             ngx_time_p = p;          unlock(p->busy);     } }
endif|#
directive|endif
end_endif

end_unit

