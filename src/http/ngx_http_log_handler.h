begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_LOG_HANDLER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_LOG_HANDLER_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_LOG_HANDLER_H_INCLUDED_
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
DECL|typedef|ngx_http_log_op_pt
typedef|typedef
name|char
modifier|*
function_decl|(
modifier|*
name|ngx_http_log_op_pt
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|uintptr_t
name|data
parameter_list|)
function_decl|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_LOG_COPY_SHORT
define|#
directive|define
name|NGX_HTTP_LOG_COPY_SHORT
value|(ngx_http_log_op_pt) 0
end_define

begin_define
DECL|macro|NGX_HTTP_LOG_COPY_LONG
define|#
directive|define
name|NGX_HTTP_LOG_COPY_LONG
value|(ngx_http_log_op_pt) -1
end_define

begin_define
DECL|macro|NGX_HTTP_LOG_ARG
define|#
directive|define
name|NGX_HTTP_LOG_ARG
value|(u_int) -1
end_define

begin_comment
comment|/* STUB */
end_comment

begin_define
DECL|macro|NGX_INT32_LEN
define|#
directive|define
name|NGX_INT32_LEN
value|sizeof("-2147483648") - 1
end_define

begin_define
DECL|macro|NGX_TIME_LEN
define|#
directive|define
name|NGX_TIME_LEN
value|sizeof("-2147483648") - 1
end_define

begin_define
DECL|macro|NGX_OFF_LEN
define|#
directive|define
name|NGX_OFF_LEN
value|sizeof("-9223372036854775808") - 1
end_define

begin_typedef
DECL|struct|__anon2b43fcf60108
typedef|typedef
struct|struct
block|{
DECL|member|len
name|size_t
name|len
decl_stmt|;
DECL|member|op
name|ngx_http_log_op_pt
name|op
decl_stmt|;
DECL|member|data
name|uintptr_t
name|data
decl_stmt|;
DECL|typedef|ngx_http_log_op_t
block|}
name|ngx_http_log_op_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b43fcf60208
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|ops
name|ngx_array_t
modifier|*
name|ops
decl_stmt|;
comment|/* array of ngx_http_log_op_t */
DECL|typedef|ngx_http_log_fmt_t
block|}
name|ngx_http_log_fmt_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b43fcf60308
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|len
name|size_t
name|len
decl_stmt|;
DECL|member|op
name|ngx_http_log_op_pt
name|op
decl_stmt|;
DECL|typedef|ngx_http_log_op_name_t
block|}
name|ngx_http_log_op_name_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b43fcf60408
typedef|typedef
struct|struct
block|{
DECL|member|formats
name|ngx_array_t
name|formats
decl_stmt|;
comment|/* array of ngx_http_log_fmt_t */
DECL|typedef|ngx_http_log_main_conf_t
block|}
name|ngx_http_log_main_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b43fcf60508
typedef|typedef
struct|struct
block|{
DECL|member|file
name|ngx_open_file_t
modifier|*
name|file
decl_stmt|;
DECL|member|ops
name|ngx_array_t
modifier|*
name|ops
decl_stmt|;
comment|/* array of ngx_http_log_op_t */
DECL|typedef|ngx_http_log_t
block|}
name|ngx_http_log_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2b43fcf60608
typedef|typedef
struct|struct
block|{
DECL|member|logs
name|ngx_array_t
modifier|*
name|logs
decl_stmt|;
comment|/* array of ngx_http_log_t */
DECL|typedef|ngx_http_log_loc_conf_t
block|}
name|ngx_http_log_loc_conf_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_http_log_op_name_t
name|ngx_http_log_fmt_ops
index|[]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_LOG_HANDLER_H_INCLUDED_ */
end_comment

end_unit

