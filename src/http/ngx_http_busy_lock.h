begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_BUSY_LOCK_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_BUSY_LOCK_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_BUSY_LOCK_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon2b0d190c0108
typedef|typedef
struct|struct
block|{
DECL|member|busy
name|char
modifier|*
name|busy
decl_stmt|;
DECL|member|busy_n
name|int
name|busy_n
decl_stmt|;
DECL|member|waiting_n
name|int
name|waiting_n
decl_stmt|;
DECL|member|max_waiting
name|int
name|max_waiting
decl_stmt|;
DECL|member|conn_n
name|int
name|conn_n
decl_stmt|;
DECL|member|max_conn
name|int
name|max_conn
decl_stmt|;
DECL|member|timeout
name|int
name|timeout
decl_stmt|;
comment|/* ngx_mutex_t  mutex; */
DECL|typedef|ngx_http_busy_lock_t
block|}
name|ngx_http_busy_lock_t
typedef|;
end_typedef

begin_function_decl
name|char
modifier|*
name|ngx_http_set_busy_lock_slot
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_BUSY_LOCK_H_INCLUDED_ */
end_comment

end_unit

