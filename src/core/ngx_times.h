begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_function_decl
name|void
name|ngx_init_time
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|time_t
name|ngx_time
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_time_update
parameter_list|()
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_time
parameter_list|(
name|char
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
name|time_t
name|ngx_cached_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_str_t
name|ngx_cached_err_log_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_str_t
name|ngx_cached_http_time
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_str_t
name|ngx_cached_http_log_time
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

