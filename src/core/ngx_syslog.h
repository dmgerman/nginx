begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SYSLOG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SYSLOG_H_INCLUDED_
define|#
directive|define
name|_NGX_SYSLOG_H_INCLUDED_
end_define

begin_typedef
DECL|struct|__anon2c8733120108
typedef|typedef
struct|struct
block|{
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|facility
name|ngx_uint_t
name|facility
decl_stmt|;
DECL|member|severity
name|ngx_uint_t
name|severity
decl_stmt|;
DECL|member|tag
name|ngx_str_t
name|tag
decl_stmt|;
DECL|member|server
name|ngx_addr_t
name|server
decl_stmt|;
DECL|member|conn
name|ngx_connection_t
name|conn
decl_stmt|;
DECL|member|processing
name|ngx_uint_t
name|processing
decl_stmt|;
comment|/* unsigned processing:1; */
DECL|typedef|ngx_syslog_peer_t
block|}
name|ngx_syslog_peer_t
typedef|;
end_typedef

begin_function_decl
name|char
modifier|*
name|ngx_syslog_process_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_syslog_peer_t
modifier|*
name|peer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_syslog_add_header
parameter_list|(
name|ngx_syslog_peer_t
modifier|*
name|peer
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_syslog_writer
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|ngx_uint_t
name|level
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

begin_function_decl
name|ssize_t
name|ngx_syslog_send
parameter_list|(
name|ngx_syslog_peer_t
modifier|*
name|peer
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SYSLOG_H_INCLUDED_ */
end_comment

end_unit

