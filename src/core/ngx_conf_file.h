begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_CONF_FILE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_CONF_FILE_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_CONF_FILE_H_INCLUDED_
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

begin_comment
comment|/*  *        AAAA  number of agruments  *      FF      command flags  *    TT        command type, i.e. HTTP "location" or "server" command  */
end_comment

begin_define
DECL|macro|NGX_CONF_NOARGS
define|#
directive|define
name|NGX_CONF_NOARGS
value|0x00000001
end_define

begin_define
DECL|macro|NGX_CONF_TAKE1
define|#
directive|define
name|NGX_CONF_TAKE1
value|0x00000002
end_define

begin_define
DECL|macro|NGX_CONF_TAKE2
define|#
directive|define
name|NGX_CONF_TAKE2
value|0x00000004
end_define

begin_define
DECL|macro|NGX_CONF_ARGS_NUMBER
define|#
directive|define
name|NGX_CONF_ARGS_NUMBER
value|0x0000ffff
end_define

begin_define
DECL|macro|NGX_CONF_ANY
define|#
directive|define
name|NGX_CONF_ANY
value|0x00010000
end_define

begin_define
DECL|macro|NGX_CONF_1MORE
define|#
directive|define
name|NGX_CONF_1MORE
value|0x00020000
end_define

begin_define
DECL|macro|NGX_CONF_BLOCK
define|#
directive|define
name|NGX_CONF_BLOCK
value|0x00040000
end_define

begin_define
DECL|macro|NGX_CONF_FLAG
define|#
directive|define
name|NGX_CONF_FLAG
value|0x00080000
end_define

begin_define
DECL|macro|NGX_MAIN_CONF
define|#
directive|define
name|NGX_MAIN_CONF
value|0x01000000
end_define

begin_define
DECL|macro|NGX_CONF_UNSET
define|#
directive|define
name|NGX_CONF_UNSET
value|-1
end_define

begin_define
DECL|macro|NGX_CONF_OK
define|#
directive|define
name|NGX_CONF_OK
value|NULL
end_define

begin_define
DECL|macro|NGX_CONF_ERROR
define|#
directive|define
name|NGX_CONF_ERROR
value|(void *) -1
end_define

begin_define
DECL|macro|NGX_CONF_BLOCK_DONE
define|#
directive|define
name|NGX_CONF_BLOCK_DONE
value|1
end_define

begin_define
DECL|macro|NGX_CONF_FILE_DONE
define|#
directive|define
name|NGX_CONF_FILE_DONE
value|2
end_define

begin_define
DECL|macro|NGX_MODULE
define|#
directive|define
name|NGX_MODULE
value|0, 0
end_define

begin_define
DECL|macro|NGX_CORE_MODULE
define|#
directive|define
name|NGX_CORE_MODULE
value|0x45524F43
end_define

begin_comment
DECL|macro|NGX_CORE_MODULE
comment|/* "CORE" */
end_comment

begin_define
DECL|macro|NGX_CONF_MODULE
define|#
directive|define
name|NGX_CONF_MODULE
value|0x464E4F43
end_define

begin_comment
DECL|macro|NGX_CONF_MODULE
comment|/* "CONF" */
end_comment

begin_define
DECL|macro|MAX_CONF_ERRSTR
define|#
directive|define
name|MAX_CONF_ERRSTR
value|256
end_define

begin_decl_stmt
specifier|extern
name|char
name|ngx_conf_errstr
index|[
name|MAX_CONF_ERRSTR
index|]
decl_stmt|;
end_decl_stmt

begin_struct
DECL|struct|ngx_command_s
struct|struct
name|ngx_command_s
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|member|set
name|char
modifier|*
function_decl|(
modifier|*
name|set
function_decl|)
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
DECL|member|conf
name|int
name|conf
decl_stmt|;
DECL|member|offset
name|int
name|offset
decl_stmt|;
DECL|member|bounds
name|void
modifier|*
name|bounds
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|ngx_null_command
define|#
directive|define
name|ngx_null_command
value|{ngx_null_string, 0, NULL, 0, 0, NULL}
end_define

begin_struct
DECL|struct|ngx_module_s
struct|struct
name|ngx_module_s
block|{
DECL|member|ctx_index
name|int
name|ctx_index
decl_stmt|;
DECL|member|index
name|int
name|index
decl_stmt|;
DECL|member|ctx
name|void
modifier|*
name|ctx
decl_stmt|;
DECL|member|commands
name|ngx_command_t
modifier|*
name|commands
decl_stmt|;
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|member|init_module
name|int
function_decl|(
modifier|*
name|init_module
function_decl|)
parameter_list|(
name|ngx_pool_t
modifier|*
name|p
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2953bcf20108
typedef|typedef
struct|struct
block|{
DECL|member|file
name|ngx_file_t
name|file
decl_stmt|;
DECL|member|hunk
name|ngx_hunk_t
modifier|*
name|hunk
decl_stmt|;
DECL|member|line
name|int
name|line
decl_stmt|;
DECL|typedef|ngx_conf_file_t
block|}
name|ngx_conf_file_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_conf_handler_pt
typedef|typedef
name|char
modifier|*
function_decl|(
modifier|*
name|ngx_conf_handler_pt
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|dummy
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_conf_s
struct|struct
name|ngx_conf_s
block|{
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|args
name|ngx_array_t
modifier|*
name|args
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|conf_file
name|ngx_conf_file_t
modifier|*
name|conf_file
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|ctx
name|void
modifier|*
name|ctx
decl_stmt|;
DECL|member|module_type
name|int
name|module_type
decl_stmt|;
DECL|member|cmd_type
name|int
name|cmd_type
decl_stmt|;
DECL|member|handler
name|ngx_conf_handler_pt
name|handler
decl_stmt|;
DECL|member|handler_conf
name|char
modifier|*
name|handler_conf
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|ngx_get_conf (module)
define|#
directive|define
name|ngx_get_conf
parameter_list|(
name|module
parameter_list|)
value|ngx_conf_ctx[module.index]
end_define

begin_define
DECL|macro|ngx_conf_init_value (conf,default)
define|#
directive|define
name|ngx_conf_init_value
parameter_list|(
name|conf
parameter_list|,
define|default)                                   \     if (conf == NGX_CONF_UNSET) {                                            \         conf = default;                                                      \     }
end_define

begin_define
DECL|macro|ngx_conf_init_unsigned_value (conf,default)
define|#
directive|define
name|ngx_conf_init_unsigned_value
parameter_list|(
name|conf
parameter_list|,
define|default)                          \     if (conf == (unsigned) NGX_CONF_UNSET) {                                 \         conf = default;                                                      \     }
end_define

begin_define
DECL|macro|ngx_conf_init_size_value (conf,default)
define|#
directive|define
name|ngx_conf_init_size_value
parameter_list|(
name|conf
parameter_list|,
define|default)                              \     if (conf == NGX_CONF_UNSET) {                                            \         conf = default;                                                      \     }
end_define

begin_define
DECL|macro|ngx_conf_init_msec_value (conf,default)
define|#
directive|define
name|ngx_conf_init_msec_value
parameter_list|(
name|conf
parameter_list|,
define|default)                              \     if (conf == NGX_CONF_UNSET) {                                            \         conf = default;                                                      \     }
end_define

begin_define
DECL|macro|ngx_conf_merge_value (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                            \     if (conf == NGX_CONF_UNSET) {                                            \         conf = (prev == NGX_CONF_UNSET) ? default : prev;                    \     }
end_define

begin_define
DECL|macro|ngx_conf_merge_msec_value (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge_msec_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                       \     if (conf == (ngx_msec_t) NGX_CONF_UNSET) {                               \         conf = (prev == (ngx_msec_t) NGX_CONF_UNSET) ? default : prev;       \     }
end_define

begin_define
DECL|macro|ngx_conf_merge_size_value (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge_size_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                       \     if (conf == (ssize_t) NGX_CONF_UNSET) {                                   \         conf = (prev == (ssize_t) NGX_CONF_UNSET) ? default : prev;           \     }
end_define

begin_define
DECL|macro|ngx_conf_merge_str_value (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge_str_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                        \     if (conf.len == 0) {                                                     \         if (prev.len) {                                                      \             conf.len = prev.len;                                             \             conf.data = prev.data;                                           \         } else {                                                             \             conf.len = sizeof(default) - 1;                                  \             conf.data = default;                                             \         }                                                                    \     }
end_define

begin_define
DECL|macro|addressof (addr)
define|#
directive|define
name|addressof
parameter_list|(
name|addr
parameter_list|)
value|((int)&addr)
end_define

begin_function_decl
name|char
modifier|*
name|ngx_conf_parse
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_str_t
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|char
modifier|*
name|ngx_conf_set_flag_slot
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

begin_function_decl
name|char
modifier|*
name|ngx_conf_set_str_slot
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

begin_function_decl
name|char
modifier|*
name|ngx_conf_set_num_slot
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

begin_function_decl
name|char
modifier|*
name|ngx_conf_set_size_slot
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

begin_function_decl
name|char
modifier|*
name|ngx_conf_set_msec_slot
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

begin_function_decl
name|char
modifier|*
name|ngx_conf_set_time_slot
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

begin_decl_stmt
specifier|extern
name|ngx_module_t
modifier|*
name|ngx_modules
index|[]
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|void
modifier|*
modifier|*
modifier|*
modifier|*
name|ngx_conf_ctx
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CONF_FILE_H_INCLUDED_ */
end_comment

end_unit

