begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
DECL|struct|__anon2a1f0f130108
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
DECL|enum|__anon2a1f0f130203
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
DECL|struct|__anon2a1f0f130308
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
DECL|member|imap_state
name|ngx_imap_state_e
name|imap_state
decl_stmt|;
DECL|member|proxy
name|ngx_imap_proxy_ctx_t
modifier|*
name|proxy
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
DECL|macro|NGX_IMAP_CONF
define|#
directive|define
name|NGX_IMAP_CONF
value|0x02000000
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
name|void
name|ngx_imap_proxy_init
parameter_list|(
name|ngx_imap_session_t
modifier|*
name|s
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_IMAP_H_INCLUDED_ */
end_comment

end_unit

