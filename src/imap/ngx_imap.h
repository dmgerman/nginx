begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_IMAP_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_IMAP_H_INCLUDED_
define|#
directive|define
name|_NGX_IMAP_H_INCLUDED_
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

begin_typedef
DECL|struct|__anon27c48f880108
typedef|typedef
struct|struct
block|{
DECL|member|main_conf
name|void
modifier|*
modifier|*
name|main_conf
decl_stmt|;
DECL|member|srv_conf
name|void
modifier|*
modifier|*
name|srv_conf
decl_stmt|;
DECL|typedef|ngx_imap_conf_ctx_t
block|}
name|ngx_imap_conf_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27c48f880208
typedef|typedef
struct|struct
block|{
DECL|member|servers
name|ngx_array_t
name|servers
decl_stmt|;
comment|/* ngx_imap_core_srv_conf_t */
DECL|typedef|ngx_imap_core_main_conf_t
block|}
name|ngx_imap_core_main_conf_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_IMAP_POP3_PROTOCOL
define|#
directive|define
name|NGX_IMAP_POP3_PROTOCOL
value|0
end_define

begin_define
DECL|macro|NGX_IMAP_IMAP_PROTOCOL
define|#
directive|define
name|NGX_IMAP_IMAP_PROTOCOL
value|1
end_define

begin_typedef
DECL|struct|__anon27c48f880308
typedef|typedef
struct|struct
block|{
DECL|member|timeout
name|ngx_msec_t
name|timeout
decl_stmt|;
DECL|member|imap_client_buffer_size
name|size_t
name|imap_client_buffer_size
decl_stmt|;
DECL|member|proxy_buffer_size
name|size_t
name|proxy_buffer_size
decl_stmt|;
DECL|member|protocol
name|ngx_uint_t
name|protocol
decl_stmt|;
comment|/* server ctx */
DECL|member|ctx
name|ngx_imap_conf_ctx_t
modifier|*
name|ctx
decl_stmt|;
DECL|typedef|ngx_imap_core_srv_conf_t
block|}
name|ngx_imap_core_srv_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27c48f880408
typedef|typedef
struct|struct
block|{
DECL|member|create_main_conf
name|void
modifier|*
function_decl|(
modifier|*
name|create_main_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|init_main_conf
name|char
modifier|*
function_decl|(
modifier|*
name|init_main_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
DECL|member|create_srv_conf
name|void
modifier|*
function_decl|(
modifier|*
name|create_srv_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|merge_srv_conf
name|char
modifier|*
function_decl|(
modifier|*
name|merge_srv_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|prev
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
DECL|typedef|ngx_imap_module_t
block|}
name|ngx_imap_module_t
typedef|;
end_typedef

begin_typedef
DECL|enum|__anon27c48f880503
typedef|typedef
enum|enum
block|{
DECL|enumerator|ngx_pop3_start
name|ngx_pop3_start
init|=
literal|0
block|,
DECL|enumerator|ngx_pop3_user
name|ngx_pop3_user
DECL|typedef|ngx_imap_state_e
block|}
name|ngx_imap_state_e
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27c48f880608
typedef|typedef
struct|struct
block|{
DECL|member|upstream
name|ngx_peer_connection_t
name|upstream
decl_stmt|;
DECL|member|buffer
name|ngx_buf_t
modifier|*
name|buffer
decl_stmt|;
DECL|typedef|ngx_imap_proxy_ctx_t
block|}
name|ngx_imap_proxy_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon27c48f880708
typedef|typedef
struct|struct
block|{
DECL|member|signature
name|uint32_t
name|signature
decl_stmt|;
comment|/* "IMAP" */
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
decl_stmt|;
DECL|member|buffer
name|ngx_buf_t
modifier|*
name|buffer
decl_stmt|;
DECL|member|ctx
name|void
modifier|*
modifier|*
name|ctx
decl_stmt|;
DECL|member|main_conf
name|void
modifier|*
modifier|*
name|main_conf
decl_stmt|;
DECL|member|srv_conf
name|void
modifier|*
modifier|*
name|srv_conf
decl_stmt|;
DECL|member|proxy
name|ngx_imap_proxy_ctx_t
modifier|*
name|proxy
decl_stmt|;
DECL|member|imap_state
name|ngx_imap_state_e
name|imap_state
decl_stmt|;
DECL|member|protocol
name|unsigned
name|protocol
range|:
literal|1
decl_stmt|;
DECL|member|login
name|ngx_str_t
name|login
decl_stmt|;
DECL|member|passwd
name|ngx_str_t
name|passwd
decl_stmt|;
DECL|member|command
name|ngx_uint_t
name|command
decl_stmt|;
DECL|member|args
name|ngx_array_t
name|args
decl_stmt|;
comment|/* used to parse IMAP/POP3 command */
DECL|member|state
name|ngx_uint_t
name|state
decl_stmt|;
DECL|member|arg_start
name|u_char
modifier|*
name|arg_start
decl_stmt|;
DECL|member|arg_end
name|u_char
modifier|*
name|arg_end
decl_stmt|;
DECL|typedef|ngx_imap_session_t
block|}
name|ngx_imap_session_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_POP3_USER
define|#
directive|define
name|NGX_POP3_USER
value|1
end_define

begin_define
DECL|macro|NGX_POP3_PASS
define|#
directive|define
name|NGX_POP3_PASS
value|2
end_define

begin_define
DECL|macro|NGX_POP3_APOP
define|#
directive|define
name|NGX_POP3_APOP
value|3
end_define

begin_define
DECL|macro|NGX_POP3_STAT
define|#
directive|define
name|NGX_POP3_STAT
value|4
end_define

begin_define
DECL|macro|NGX_POP3_LIST
define|#
directive|define
name|NGX_POP3_LIST
value|5
end_define

begin_define
DECL|macro|NGX_POP3_RETR
define|#
directive|define
name|NGX_POP3_RETR
value|6
end_define

begin_define
DECL|macro|NGX_POP3_DELE
define|#
directive|define
name|NGX_POP3_DELE
value|7
end_define

begin_define
DECL|macro|NGX_POP3_NOOP
define|#
directive|define
name|NGX_POP3_NOOP
value|8
end_define

begin_define
DECL|macro|NGX_POP3_RSET
define|#
directive|define
name|NGX_POP3_RSET
value|9
end_define

begin_define
DECL|macro|NGX_POP3_TOP
define|#
directive|define
name|NGX_POP3_TOP
value|10
end_define

begin_define
DECL|macro|NGX_POP3_UIDL
define|#
directive|define
name|NGX_POP3_UIDL
value|11
end_define

begin_define
DECL|macro|NGX_POP3_QUIT
define|#
directive|define
name|NGX_POP3_QUIT
value|12
end_define

begin_define
DECL|macro|NGX_IMAP_PARSE_INVALID_COMMAND
define|#
directive|define
name|NGX_IMAP_PARSE_INVALID_COMMAND
value|10
end_define

begin_define
DECL|macro|NGX_IMAP_PROXY_INVALID
define|#
directive|define
name|NGX_IMAP_PROXY_INVALID
value|10
end_define

begin_define
DECL|macro|NGX_IMAP_PROXY_ERROR
define|#
directive|define
name|NGX_IMAP_PROXY_ERROR
value|11
end_define

begin_define
DECL|macro|NGX_IMAP_MODULE
define|#
directive|define
name|NGX_IMAP_MODULE
value|0x50414D49
end_define

begin_comment
DECL|macro|NGX_IMAP_MODULE
comment|/* "IMAP" */
end_comment

begin_define
DECL|macro|NGX_IMAP_MAIN_CONF
define|#
directive|define
name|NGX_IMAP_MAIN_CONF
value|0x02000000
end_define

begin_define
DECL|macro|NGX_IMAP_SRV_CONF
define|#
directive|define
name|NGX_IMAP_SRV_CONF
value|0x04000000
end_define

begin_define
DECL|macro|NGX_IMAP_MAIN_CONF_OFFSET
define|#
directive|define
name|NGX_IMAP_MAIN_CONF_OFFSET
value|offsetof(ngx_imap_conf_ctx_t, main_conf)
end_define

begin_define
DECL|macro|NGX_IMAP_SRV_CONF_OFFSET
define|#
directive|define
name|NGX_IMAP_SRV_CONF_OFFSET
value|offsetof(ngx_imap_conf_ctx_t, srv_conf)
end_define

begin_define
DECL|macro|ngx_imap_get_module_ctx (s,module)
define|#
directive|define
name|ngx_imap_get_module_ctx
parameter_list|(
name|s
parameter_list|,
name|module
parameter_list|)
value|(s)->ctx[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_imap_set_ctx (s,c,module)
define|#
directive|define
name|ngx_imap_set_ctx
parameter_list|(
name|s
parameter_list|,
name|c
parameter_list|,
name|module
parameter_list|)
value|s->ctx[module.ctx_index] = c;
end_define

begin_define
DECL|macro|ngx_imap_delete_ctx (s,module)
define|#
directive|define
name|ngx_imap_delete_ctx
parameter_list|(
name|s
parameter_list|,
name|module
parameter_list|)
value|s->ctx[module.ctx_index] = NULL;
end_define

begin_define
DECL|macro|ngx_imap_get_module_main_conf (s,module)
define|#
directive|define
name|ngx_imap_get_module_main_conf
parameter_list|(
name|s
parameter_list|,
name|module
parameter_list|)
define|\
value|(s)->main_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_imap_get_module_srv_conf (s,module)
define|#
directive|define
name|ngx_imap_get_module_srv_conf
parameter_list|(
name|s
parameter_list|,
name|module
parameter_list|)
value|(s)->srv_conf[module.ctx_index]
end_define

begin_function_decl
name|void
name|ngx_imap_init_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_imap_close_connection
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_pop3_parse_command
parameter_list|(
name|ngx_imap_session_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* STUB */
end_comment

begin_function_decl
name|void
name|ngx_imap_proxy_init
parameter_list|(
name|ngx_imap_session_t
modifier|*
name|s
parameter_list|,
name|ngx_peers_t
modifier|*
name|peers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_imap_auth_http_init
parameter_list|(
name|ngx_imap_session_t
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**/
end_comment

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_imap_max_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_imap_core_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_IMAP_H_INCLUDED_ */
end_comment

end_unit

