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

begin_include
include|#
directive|include
file|<ngx_string.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_time.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_decl_stmt
DECL|variable|ngx_http_log_module
name|ngx_http_module_t
name|ngx_http_log_module
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
DECL|function|ngx_http_log_handler (ngx_http_request_t * r)
name|int
name|ngx_http_log_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|size_t
name|len
decl_stmt|;
name|char
modifier|*
name|line
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|ngx_tm_t
name|tm
decl_stmt|;
name|ngx_log_debug
argument_list|(
name|r
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|"log handler"
argument_list|)
expr_stmt|;
comment|/* %a, 20:%c, 22:%d, 3:%s, 20:%b, 5*" ", "2/1: "\r\n" */
if|#
directive|if
operator|(
name|WIN32
operator|)
name|len
operator|=
literal|2
operator|+
literal|20
operator|+
literal|22
operator|+
literal|3
operator|+
literal|20
operator|+
literal|5
operator|+
operator|+
literal|2
expr_stmt|;
else|#
directive|else
name|len
operator|=
literal|2
operator|+
literal|20
operator|+
literal|22
operator|+
literal|3
operator|+
literal|20
operator|+
literal|5
operator|+
operator|+
literal|1
expr_stmt|;
endif|#
directive|endif
name|len
operator|+=
name|r
operator|->
name|connection
operator|->
name|addr_text
operator|.
name|len
expr_stmt|;
name|len
operator|+=
name|r
operator|->
name|request_line
operator|.
name|len
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"log handler: %d"
argument|_ len
argument_list|)
empty_stmt|;
name|ngx_test_null
argument_list|(
name|line
argument_list|,
name|ngx_palloc
argument_list|(
name|r
operator|->
name|pool
argument_list|,
name|len
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
name|p
operator|=
name|line
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|p
argument_list|,
name|r
operator|->
name|connection
operator|->
name|addr_text
operator|.
name|data
argument_list|,
name|r
operator|->
name|connection
operator|->
name|addr_text
operator|.
name|len
argument_list|)
expr_stmt|;
name|p
operator|+=
name|r
operator|->
name|connection
operator|->
name|addr_text
operator|.
name|len
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|' '
expr_stmt|;
name|p
operator|+=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
literal|21
argument_list|,
literal|"%u"
argument_list|,
name|r
operator|->
name|connection
operator|->
name|number
argument_list|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|' '
expr_stmt|;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"log handler: %s"
argument|_ line
argument_list|)
empty_stmt|;
name|ngx_localtime
argument_list|(
operator|&
name|tm
argument_list|)
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"log handler: %s"
argument|_ line
argument_list|)
empty_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'['
expr_stmt|;
name|p
operator|+=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
literal|21
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
operator|*
name|p
operator|++
operator|=
literal|']'
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|' '
expr_stmt|;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"log handler: %s"
argument|_ line
argument_list|)
empty_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'"'
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|p
argument_list|,
name|r
operator|->
name|request_line
operator|.
name|data
argument_list|,
name|r
operator|->
name|request_line
operator|.
name|len
argument_list|)
expr_stmt|;
name|p
operator|+=
name|r
operator|->
name|request_line
operator|.
name|len
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'"'
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|' '
expr_stmt|;
name|p
operator|+=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
literal|4
argument_list|,
literal|"%d"
argument_list|,
name|r
operator|->
name|headers_out
operator|.
name|status
argument_list|)
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|' '
expr_stmt|;
name|p
operator|+=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
literal|21
argument_list|,
name|QD_FMT
argument_list|,
name|r
operator|->
name|connection
operator|->
name|sent
argument_list|)
expr_stmt|;
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"log handler: %s"
argument|_ line
argument_list|)
empty_stmt|;
if|#
directive|if
operator|(
name|WIN32
operator|)
operator|*
name|p
operator|++
operator|=
name|CR
expr_stmt|;
operator|*
name|p
operator|++
operator|=
name|LF
expr_stmt|;
else|#
directive|else
operator|*
name|p
operator|++
operator|=
name|LF
expr_stmt|;
endif|#
directive|endif
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|ngx_log_debug
argument_list|(
argument|r->connection->log
argument_list|,
literal|"log handler: %s"
argument|_ line
argument_list|)
empty_stmt|;
name|write
argument_list|(
literal|1
argument_list|,
name|line
argument_list|,
name|len
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

end_unit

