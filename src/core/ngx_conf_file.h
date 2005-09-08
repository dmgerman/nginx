begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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
DECL|macro|NGX_CONF_TAKE3
define|#
directive|define
name|NGX_CONF_TAKE3
value|0x00000008
end_define

begin_define
DECL|macro|NGX_CONF_TAKE4
define|#
directive|define
name|NGX_CONF_TAKE4
value|0x00000010
end_define

begin_define
DECL|macro|NGX_CONF_TAKE5
define|#
directive|define
name|NGX_CONF_TAKE5
value|0x00000020
end_define

begin_define
DECL|macro|NGX_CONF_TAKE6
define|#
directive|define
name|NGX_CONF_TAKE6
value|0x00000040
end_define

begin_define
DECL|macro|NGX_CONF_TAKE7
define|#
directive|define
name|NGX_CONF_TAKE7
value|0x00000080
end_define

begin_define
DECL|macro|NGX_CONF_MAX_ARGS
define|#
directive|define
name|NGX_CONF_MAX_ARGS
value|8
end_define

begin_define
DECL|macro|NGX_CONF_TAKE12
define|#
directive|define
name|NGX_CONF_TAKE12
value|(NGX_CONF_TAKE1|NGX_CONF_TAKE2)
end_define

begin_define
DECL|macro|NGX_CONF_TAKE13
define|#
directive|define
name|NGX_CONF_TAKE13
value|(NGX_CONF_TAKE1|NGX_CONF_TAKE3)
end_define

begin_define
DECL|macro|NGX_CONF_TAKE23
define|#
directive|define
name|NGX_CONF_TAKE23
value|(NGX_CONF_TAKE2|NGX_CONF_TAKE3)
end_define

begin_define
DECL|macro|NGX_CONF_TAKE1234
define|#
directive|define
name|NGX_CONF_TAKE1234
value|(NGX_CONF_TAKE1|NGX_CONF_TAKE2|NGX_CONF_TAKE3   \                               |NGX_CONF_TAKE4)
end_define

begin_define
DECL|macro|NGX_CONF_ARGS_NUMBER
define|#
directive|define
name|NGX_CONF_ARGS_NUMBER
value|0x000000ff
end_define

begin_define
DECL|macro|NGX_CONF_BLOCK
define|#
directive|define
name|NGX_CONF_BLOCK
value|0x00000100
end_define

begin_define
DECL|macro|NGX_CONF_FLAG
define|#
directive|define
name|NGX_CONF_FLAG
value|0x00000200
end_define

begin_define
DECL|macro|NGX_CONF_ANY
define|#
directive|define
name|NGX_CONF_ANY
value|0x00000400
end_define

begin_define
DECL|macro|NGX_CONF_1MORE
define|#
directive|define
name|NGX_CONF_1MORE
value|0x00000800
end_define

begin_define
DECL|macro|NGX_CONF_2MORE
define|#
directive|define
name|NGX_CONF_2MORE
value|0x00001000
end_define

begin_define
DECL|macro|NGX_DIRECT_CONF
define|#
directive|define
name|NGX_DIRECT_CONF
value|0x00010000
end_define

begin_define
DECL|macro|NGX_MAIN_CONF
define|#
directive|define
name|NGX_MAIN_CONF
value|0x01000000
end_define

begin_define
DECL|macro|NGX_ANY_CONF
define|#
directive|define
name|NGX_ANY_CONF
value|0x0F000000
end_define

begin_define
DECL|macro|NGX_CONF_UNSET
define|#
directive|define
name|NGX_CONF_UNSET
value|-1
end_define

begin_define
DECL|macro|NGX_CONF_UNSET_UINT
define|#
directive|define
name|NGX_CONF_UNSET_UINT
value|(ngx_uint_t) -1
end_define

begin_define
DECL|macro|NGX_CONF_UNSET_PTR
define|#
directive|define
name|NGX_CONF_UNSET_PTR
value|(void *) -1
end_define

begin_define
DECL|macro|NGX_CONF_UNSET_SIZE
define|#
directive|define
name|NGX_CONF_UNSET_SIZE
value|(size_t) -1
end_define

begin_define
DECL|macro|NGX_CONF_UNSET_MSEC
define|#
directive|define
name|NGX_CONF_UNSET_MSEC
value|(ngx_msec_t) -1
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
value|(char *) -1
end_define

begin_define
DECL|macro|NGX_CONF_BLOCK_START
define|#
directive|define
name|NGX_CONF_BLOCK_START
value|1
end_define

begin_define
DECL|macro|NGX_CONF_BLOCK_DONE
define|#
directive|define
name|NGX_CONF_BLOCK_DONE
value|2
end_define

begin_define
DECL|macro|NGX_CONF_FILE_DONE
define|#
directive|define
name|NGX_CONF_FILE_DONE
value|3
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
DECL|macro|NGX_MAX_CONF_ERRSTR
define|#
directive|define
name|NGX_MAX_CONF_ERRSTR
value|256
end_define

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
name|ngx_uint_t
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
name|ngx_uint_t
name|conf
decl_stmt|;
DECL|member|offset
name|ngx_uint_t
name|offset
decl_stmt|;
DECL|member|post
name|void
modifier|*
name|post
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|ngx_null_command
define|#
directive|define
name|ngx_null_command
value|{ ngx_null_string, 0, NULL, 0, 0, NULL }
end_define

begin_struct
DECL|struct|ngx_open_file_s
struct|struct
name|ngx_open_file_s
block|{
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
if|#
directive|if
literal|0
comment|/* e.g. append mode, error_log */
block|ngx_uint_t            flags;
comment|/* e.g. reopen db file */
block|ngx_uint_t          (*handler)(void *data, ngx_open_file_t *file);     void                 *data;
endif|#
directive|endif
block|}
struct|;
end_struct

begin_define
DECL|macro|NGX_MODULE_V1
define|#
directive|define
name|NGX_MODULE_V1
value|0, 0, 1, 0, 0, 0, 0
end_define

begin_define
DECL|macro|NGX_MODULE_V1_PADDING
define|#
directive|define
name|NGX_MODULE_V1_PADDING
value|0, 0, 0, 0, 0, 0, 0, 0
end_define

begin_struct
DECL|struct|ngx_module_s
struct|struct
name|ngx_module_s
block|{
DECL|member|ctx_index
name|ngx_uint_t
name|ctx_index
decl_stmt|;
DECL|member|index
name|ngx_uint_t
name|index
decl_stmt|;
DECL|member|version
name|ngx_uint_t
name|version
decl_stmt|;
DECL|member|spare0
name|ngx_uint_t
name|spare0
decl_stmt|;
DECL|member|spare1
name|ngx_uint_t
name|spare1
decl_stmt|;
DECL|member|spare2
name|ngx_uint_t
name|spare2
decl_stmt|;
DECL|member|spare3
name|ngx_uint_t
name|spare3
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
name|ngx_uint_t
name|type
decl_stmt|;
DECL|member|init_master
name|ngx_int_t
function_decl|(
modifier|*
name|init_master
function_decl|)
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
DECL|member|init_module
name|ngx_int_t
function_decl|(
modifier|*
name|init_module
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|init_process
name|ngx_int_t
function_decl|(
modifier|*
name|init_process
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|init_thread
name|ngx_int_t
function_decl|(
modifier|*
name|init_thread
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|exit_thread
name|ngx_int_t
function_decl|(
modifier|*
name|exit_thread
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|exit_process
name|ngx_int_t
function_decl|(
modifier|*
name|exit_process
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|exit_master
name|ngx_int_t
function_decl|(
modifier|*
name|exit_master
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|spare_hook0
name|uintptr_t
name|spare_hook0
decl_stmt|;
DECL|member|spare_hook1
name|uintptr_t
name|spare_hook1
decl_stmt|;
DECL|member|spare_hook2
name|uintptr_t
name|spare_hook2
decl_stmt|;
DECL|member|spare_hook3
name|uintptr_t
name|spare_hook3
decl_stmt|;
DECL|member|spare_hook4
name|uintptr_t
name|spare_hook4
decl_stmt|;
DECL|member|spare_hook5
name|uintptr_t
name|spare_hook5
decl_stmt|;
DECL|member|spare_hook6
name|uintptr_t
name|spare_hook6
decl_stmt|;
DECL|member|spare_hook7
name|uintptr_t
name|spare_hook7
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2911b9ea0108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|create_conf
name|void
modifier|*
function_decl|(
modifier|*
name|create_conf
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|init_conf
name|char
modifier|*
function_decl|(
modifier|*
name|init_conf
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
DECL|typedef|ngx_core_module_t
block|}
name|ngx_core_module_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2911b9ea0208
typedef|typedef
struct|struct
block|{
DECL|member|file
name|ngx_file_t
name|file
decl_stmt|;
DECL|member|buffer
name|ngx_buf_t
modifier|*
name|buffer
decl_stmt|;
DECL|member|line
name|ngx_uint_t
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
DECL|member|cycle
name|ngx_cycle_t
modifier|*
name|cycle
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
name|ngx_uint_t
name|module_type
decl_stmt|;
DECL|member|cmd_type
name|ngx_uint_t
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

begin_typedef
DECL|typedef|ngx_conf_post_handler_pt
typedef|typedef
name|char
modifier|*
function_decl|(
modifier|*
name|ngx_conf_post_handler_pt
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|data
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2911b9ea0308
typedef|typedef
struct|struct
block|{
DECL|member|post_handler
name|ngx_conf_post_handler_pt
name|post_handler
decl_stmt|;
DECL|typedef|ngx_conf_post_t
block|}
name|ngx_conf_post_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2911b9ea0408
typedef|typedef
struct|struct
block|{
DECL|member|post_handler
name|ngx_conf_post_handler_pt
name|post_handler
decl_stmt|;
DECL|member|low
name|ngx_int_t
name|low
decl_stmt|;
DECL|member|high
name|ngx_int_t
name|high
decl_stmt|;
DECL|typedef|ngx_conf_num_bounds_t
block|}
name|ngx_conf_num_bounds_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2911b9ea0508
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|value
name|ngx_uint_t
name|value
decl_stmt|;
DECL|typedef|ngx_conf_enum_t
block|}
name|ngx_conf_enum_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_CONF_BITMASK_SET
define|#
directive|define
name|NGX_CONF_BITMASK_SET
value|1
end_define

begin_typedef
DECL|struct|__anon2911b9ea0608
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|mask
name|ngx_uint_t
name|mask
decl_stmt|;
DECL|typedef|ngx_conf_bitmask_t
block|}
name|ngx_conf_bitmask_t
typedef|;
end_typedef

begin_function_decl
name|char
modifier|*
name|ngx_conf_check_num_bounds
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|post
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_get_conf (conf_ctx,module)
define|#
directive|define
name|ngx_get_conf
parameter_list|(
name|conf_ctx
parameter_list|,
name|module
parameter_list|)
value|conf_ctx[module.index]
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
DECL|macro|ngx_conf_init_ptr_value (conf,default)
define|#
directive|define
name|ngx_conf_init_ptr_value
parameter_list|(
name|conf
parameter_list|,
define|default)                               \     if (conf == NGX_CONF_UNSET_PTR) {                                        \         conf = default;                                                      \     }
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
define|default)                              \     if (conf == NGX_CONF_UNSET_SIZE) {                                       \         conf = default;                                                      \     }
end_define

begin_define
DECL|macro|ngx_conf_init_msec_value (conf,default)
define|#
directive|define
name|ngx_conf_init_msec_value
parameter_list|(
name|conf
parameter_list|,
define|default)                              \     if (conf == NGX_CONF_UNSET_MSEC) {                                       \         conf = default;                                                      \     }
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
DECL|macro|ngx_conf_merge_ptr_value (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge_ptr_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                        \     if (conf == NULL) {                                                      \         conf = (prev == NULL) ? default : prev;                              \     }
end_define

begin_define
DECL|macro|ngx_conf_merge_unsigned_value (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge_unsigned_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                   \     if (conf == NGX_CONF_UNSET_UINT) {                                       \         conf = (prev == NGX_CONF_UNSET_UINT) ? default : prev;               \     }
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
define|default)                       \     if (conf == NGX_CONF_UNSET_MSEC) {                                       \         conf = (prev == NGX_CONF_UNSET_MSEC) ? default : prev;               \     }
end_define

begin_define
DECL|macro|ngx_conf_merge_sec_value (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge_sec_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                        \     if (conf == NGX_CONF_UNSET) {                                            \         conf = (prev == NGX_CONF_UNSET) ? default : prev;                    \     }
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
define|default)                       \     if (conf == NGX_CONF_UNSET_SIZE) {                                       \         conf = (prev == NGX_CONF_UNSET_SIZE) ? default : prev;               \     }
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
define|default)                        \     if (conf.data == NULL) {                                                 \         if (prev.data) {                                                      \             conf.len = prev.len;                                             \             conf.data = prev.data;                                           \         } else {                                                             \             conf.len = sizeof(default) - 1;                                  \             conf.data = (u_char *) default;                                  \         }                                                                    \     }
end_define

begin_define
DECL|macro|ngx_conf_merge_bufs_value (conf,prev,default_num,default_size)
define|#
directive|define
name|ngx_conf_merge_bufs_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
name|default_num
parameter_list|,
name|default_size
parameter_list|)
define|\
value|if (conf.num == 0) {                                                     \         if (prev.num) {                                                      \             conf.num = prev.num;                                             \             conf.size = prev.size;                                           \         } else {                                                             \             conf.num = default_num;                                          \             conf.size = default_size;                                        \         }                                                                    \     }
end_define

begin_define
DECL|macro|ngx_conf_merge_bitmask_value (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge_bitmask_value
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                    \     if (conf == 0) {                                                         \         conf = (prev == 0) ? default : prev;                                 \     }
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
name|ngx_int_t
name|ngx_conf_full_name
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_open_file_t
modifier|*
name|ngx_conf_open_file
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_str_t
modifier|*
name|name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_cdecl
name|ngx_conf_log_error
parameter_list|(
name|ngx_uint_t
name|level
parameter_list|,
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_err_t
name|err
parameter_list|,
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
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
name|ngx_conf_set_table_elt_slot
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
name|ngx_conf_set_sec_slot
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
name|ngx_conf_set_bufs_slot
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
name|ngx_conf_set_enum_slot
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
name|ngx_conf_set_bitmask_slot
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
name|ngx_uint_t
name|ngx_max_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
modifier|*
name|ngx_modules
index|[]
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

