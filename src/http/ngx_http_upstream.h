begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_UPSTREAM_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_UPSTREAM_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_UPSTREAM_H_INCLUDED_
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
file|<ngx_event.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_connect.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_pipe.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_ERROR
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_ERROR
value|0x02
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_TIMEOUT
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_TIMEOUT
value|0x04
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_INVALID_HEADER
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_INVALID_HEADER
value|0x08
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_500
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_500
value|0x10
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_HTTP_404
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_HTTP_404
value|0x20
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_BUSY_LOCK
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_BUSY_LOCK
value|0x40
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_FT_MAX_WAITING
define|#
directive|define
name|NGX_HTTP_UPSTREAM_FT_MAX_WAITING
value|0x80
end_define

begin_define
DECL|macro|NGX_HTTP_UPSTREAM_INVALID_HEADER
define|#
directive|define
name|NGX_HTTP_UPSTREAM_INVALID_HEADER
value|40
end_define

begin_typedef
DECL|struct|__anon2a0d85400108
typedef|typedef
struct|struct
block|{
DECL|member|bl_time
name|time_t
name|bl_time
decl_stmt|;
DECL|member|bl_state
name|ngx_uint_t
name|bl_state
decl_stmt|;
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|time
name|time_t
name|time
decl_stmt|;
DECL|member|peer
name|ngx_str_t
modifier|*
name|peer
decl_stmt|;
DECL|typedef|ngx_http_upstream_state_t
block|}
name|ngx_http_upstream_state_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a0d85400208
typedef|typedef
struct|struct
block|{
DECL|member|connect_timeout
name|ngx_msec_t
name|connect_timeout
decl_stmt|;
DECL|member|send_timeout
name|ngx_msec_t
name|send_timeout
decl_stmt|;
DECL|member|read_timeout
name|ngx_msec_t
name|read_timeout
decl_stmt|;
DECL|member|send_lowat
name|size_t
name|send_lowat
decl_stmt|;
DECL|member|header_buffer_size
name|size_t
name|header_buffer_size
decl_stmt|;
DECL|member|busy_buffers_size
name|size_t
name|busy_buffers_size
decl_stmt|;
DECL|member|max_temp_file_size
name|size_t
name|max_temp_file_size
decl_stmt|;
DECL|member|temp_file_write_size
name|size_t
name|temp_file_write_size
decl_stmt|;
DECL|member|next_upstream
name|ngx_uint_t
name|next_upstream
decl_stmt|;
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
DECL|member|x_powered_by
name|ngx_flag_t
name|x_powered_by
decl_stmt|;
DECL|member|cyclic_temp_file
name|ngx_flag_t
name|cyclic_temp_file
decl_stmt|;
DECL|member|temp_path
name|ngx_path_t
modifier|*
name|temp_path
decl_stmt|;
DECL|typedef|ngx_http_upstream_conf_t
block|}
name|ngx_http_upstream_conf_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_upstream_t
typedef|typedef
name|struct
name|ngx_http_upstream_s
name|ngx_http_upstream_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_upstream_s
struct|struct
name|ngx_http_upstream_s
block|{
DECL|member|request
name|ngx_http_request_t
modifier|*
name|request
decl_stmt|;
DECL|member|peer
name|ngx_peer_connection_t
name|peer
decl_stmt|;
DECL|member|pipe
name|ngx_event_pipe_t
name|pipe
decl_stmt|;
DECL|member|output
name|ngx_output_chain_ctx_t
name|output
decl_stmt|;
DECL|member|writer
name|ngx_chain_writer_ctx_t
name|writer
decl_stmt|;
DECL|member|conf
name|ngx_http_upstream_conf_t
modifier|*
name|conf
decl_stmt|;
DECL|member|header_in
name|ngx_buf_t
name|header_in
decl_stmt|;
DECL|member|create_request
name|ngx_int_t
function_decl|(
modifier|*
name|create_request
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|reinit_request
name|ngx_int_t
function_decl|(
modifier|*
name|reinit_request
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|process_header
name|ngx_int_t
function_decl|(
modifier|*
name|process_header
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|send_header
name|ngx_int_t
function_decl|(
modifier|*
name|send_header
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|abort_request
name|void
function_decl|(
modifier|*
name|abort_request
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
DECL|member|finalize_request
name|void
function_decl|(
modifier|*
name|finalize_request
function_decl|)
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_int_t
name|rc
parameter_list|)
function_decl|;
DECL|member|method
name|ngx_uint_t
name|method
decl_stmt|;
DECL|member|schema
name|ngx_str_t
name|schema
decl_stmt|;
DECL|member|uri
name|ngx_str_t
name|uri
decl_stmt|;
DECL|member|location
name|ngx_str_t
modifier|*
name|location
decl_stmt|;
DECL|member|log_ctx
name|ngx_http_log_ctx_t
modifier|*
name|log_ctx
decl_stmt|;
DECL|member|log_handler
name|ngx_log_handler_pt
name|log_handler
decl_stmt|;
DECL|member|saved_ctx
name|ngx_http_log_ctx_t
modifier|*
name|saved_ctx
decl_stmt|;
DECL|member|saved_handler
name|ngx_log_handler_pt
name|saved_handler
decl_stmt|;
comment|/* used to parse an upstream HTTP header */
DECL|member|status
name|ngx_uint_t
name|status
decl_stmt|;
DECL|member|status_start
name|u_char
modifier|*
name|status_start
decl_stmt|;
DECL|member|status_end
name|u_char
modifier|*
name|status_end
decl_stmt|;
DECL|member|status_count
name|ngx_uint_t
name|status_count
decl_stmt|;
DECL|member|parse_state
name|ngx_uint_t
name|parse_state
decl_stmt|;
DECL|member|state
name|ngx_http_upstream_state_t
modifier|*
name|state
decl_stmt|;
DECL|member|states
name|ngx_array_t
name|states
decl_stmt|;
comment|/* of ngx_http_upstream_state_t */
DECL|member|cachable
name|unsigned
name|cachable
range|:
literal|1
decl_stmt|;
DECL|member|request_sent
name|unsigned
name|request_sent
range|:
literal|1
decl_stmt|;
DECL|member|header_sent
name|unsigned
name|header_sent
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|ngx_http_upstream_init
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_http_upstream_log_error
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|ngx_http_upstream_header_errors
index|[]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_UPSTREAM_H_INCLUDED_ */
end_comment

end_unit

