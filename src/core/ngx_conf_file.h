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
file|<ngx_files.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_file.h>
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
file|<ngx_hunk.h>
end_include

begin_include
include|#
directive|include
file|<ngx_array.h>
end_include

begin_define
DECL|macro|NGX_CONF_NOARGS
define|#
directive|define
name|NGX_CONF_NOARGS
value|1
end_define

begin_define
DECL|macro|NGX_CONF_TAKE1
define|#
directive|define
name|NGX_CONF_TAKE1
value|2
end_define

begin_define
DECL|macro|NGX_CONF_TAKE2
define|#
directive|define
name|NGX_CONF_TAKE2
value|4
end_define

begin_define
DECL|macro|NGX_CONF_ARGS_NUMBER
define|#
directive|define
name|NGX_CONF_ARGS_NUMBER
value|0x00ffff
end_define

begin_define
DECL|macro|NGX_CONF_ANY
define|#
directive|define
name|NGX_CONF_ANY
value|0x010000
end_define

begin_define
DECL|macro|NGX_CONF_BLOCK
define|#
directive|define
name|NGX_CONF_BLOCK
value|0x020000
end_define

begin_define
DECL|macro|NGX_CONF_FLAG
define|#
directive|define
name|NGX_CONF_FLAG
value|0x040000
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
DECL|macro|NGX_CORE_MODULE_TYPE
define|#
directive|define
name|NGX_CORE_MODULE_TYPE
value|0x45524F43
end_define

begin_comment
DECL|macro|NGX_CORE_MODULE_TYPE
comment|/* "CORE" */
end_comment

begin_define
DECL|macro|NGX_CONF_MODULE_TYPE
define|#
directive|define
name|NGX_CONF_MODULE_TYPE
value|0x464E4F43
end_define

begin_comment
DECL|macro|NGX_CONF_MODULE_TYPE
comment|/* "CONF" */
end_comment

begin_typedef
DECL|typedef|ngx_conf_t
typedef|typedef
name|struct
name|ngx_conf_s
name|ngx_conf_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_command_t
typedef|typedef
name|struct
name|ngx_command_s
name|ngx_command_t
typedef|;
end_typedef

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
name|char
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

begin_typedef
DECL|struct|__anon2a8f12e30108
typedef|typedef
struct|struct
block|{
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
DECL|typedef|ngx_module_t
block|}
name|ngx_module_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2a8f12e30208
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
DECL|member|type
name|int
name|type
decl_stmt|;
DECL|member|handler
name|char
modifier|*
function_decl|(
modifier|*
name|handler
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_define
DECL|macro|ngx_conf_merge (conf,prev,default)
define|#
directive|define
name|ngx_conf_merge
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                                  \     if (conf == NGX_CONF_UNSET) {                                            \         conf = (prev == NGX_CONF_UNSET) ? default : prev;                    \     }
end_define

begin_define
DECL|macro|ngx_conf_size_merge (conf,prev,default)
define|#
directive|define
name|ngx_conf_size_merge
parameter_list|(
name|conf
parameter_list|,
name|prev
parameter_list|,
define|default)                             \     if (conf == (size_t) NGX_CONF_UNSET) {                                   \         conf = (prev == (size_t) NGX_CONF_UNSET) ? default : prev;           \     }
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
name|char
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
name|char
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
name|char
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
name|char
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CONF_FILE_H_INCLUDED_ */
end_comment

end_unit

