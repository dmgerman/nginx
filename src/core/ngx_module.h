begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Maxim Dounin  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_MODULE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_MODULE_H_INCLUDED_
define|#
directive|define
name|_NGX_MODULE_H_INCLUDED_
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
file|<nginx.h>
end_include

begin_define
DECL|macro|NGX_MODULE_UNSET_INDEX
define|#
directive|define
name|NGX_MODULE_UNSET_INDEX
value|(ngx_uint_t) -1
end_define

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_0
define|#
directive|define
name|NGX_MODULE_SIGNATURE_0
define|\
value|ngx_value(NGX_PTR_SIZE) ","                                               \     ngx_value(NGX_SIG_ATOMIC_T_SIZE) ","                                      \     ngx_value(NGX_TIME_T_SIZE) ","
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_1
define|#
directive|define
name|NGX_MODULE_SIGNATURE_1
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_1
define|#
directive|define
name|NGX_MODULE_SIGNATURE_1
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_IOCP
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_2
define|#
directive|define
name|NGX_MODULE_SIGNATURE_2
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_2
define|#
directive|define
name|NGX_MODULE_SIGNATURE_2
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|||
name|NGX_COMPAT
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_3
define|#
directive|define
name|NGX_MODULE_SIGNATURE_3
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_3
define|#
directive|define
name|NGX_MODULE_SIGNATURE_3
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_AIO_SENDFILE
operator|||
name|NGX_COMPAT
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_4
define|#
directive|define
name|NGX_MODULE_SIGNATURE_4
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_4
define|#
directive|define
name|NGX_MODULE_SIGNATURE_4
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_EVENTFD
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_5
define|#
directive|define
name|NGX_MODULE_SIGNATURE_5
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_5
define|#
directive|define
name|NGX_MODULE_SIGNATURE_5
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_EPOLL
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_6
define|#
directive|define
name|NGX_MODULE_SIGNATURE_6
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_6
define|#
directive|define
name|NGX_MODULE_SIGNATURE_6
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_KEEPALIVE_TUNABLE
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_7
define|#
directive|define
name|NGX_MODULE_SIGNATURE_7
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_7
define|#
directive|define
name|NGX_MODULE_SIGNATURE_7
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_INET6
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_8
define|#
directive|define
name|NGX_MODULE_SIGNATURE_8
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_8
define|#
directive|define
name|NGX_MODULE_SIGNATURE_8
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_9
define|#
directive|define
name|NGX_MODULE_SIGNATURE_9
value|"1"
end_define

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_10
define|#
directive|define
name|NGX_MODULE_SIGNATURE_10
value|"1"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_DEFERRED_ACCEPT
operator|&&
name|defined
name|SO_ACCEPTFILTER
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_11
define|#
directive|define
name|NGX_MODULE_SIGNATURE_11
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_11
define|#
directive|define
name|NGX_MODULE_SIGNATURE_11
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_12
define|#
directive|define
name|NGX_MODULE_SIGNATURE_12
value|"1"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SETFIB
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_13
define|#
directive|define
name|NGX_MODULE_SIGNATURE_13
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_13
define|#
directive|define
name|NGX_MODULE_SIGNATURE_13
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_TCP_FASTOPEN
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_14
define|#
directive|define
name|NGX_MODULE_SIGNATURE_14
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_14
define|#
directive|define
name|NGX_MODULE_SIGNATURE_14
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_UNIX_DOMAIN
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_15
define|#
directive|define
name|NGX_MODULE_SIGNATURE_15
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_15
define|#
directive|define
name|NGX_MODULE_SIGNATURE_15
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_VARIADIC_MACROS
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_16
define|#
directive|define
name|NGX_MODULE_SIGNATURE_16
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_16
define|#
directive|define
name|NGX_MODULE_SIGNATURE_16
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_17
define|#
directive|define
name|NGX_MODULE_SIGNATURE_17
value|"0"
end_define

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_18
define|#
directive|define
name|NGX_MODULE_SIGNATURE_18
value|"0"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_OPENAT
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_19
define|#
directive|define
name|NGX_MODULE_SIGNATURE_19
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_19
define|#
directive|define
name|NGX_MODULE_SIGNATURE_19
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_ATOMIC_OPS
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_20
define|#
directive|define
name|NGX_MODULE_SIGNATURE_20
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_20
define|#
directive|define
name|NGX_MODULE_SIGNATURE_20
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_POSIX_SEM
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_21
define|#
directive|define
name|NGX_MODULE_SIGNATURE_21
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_21
define|#
directive|define
name|NGX_MODULE_SIGNATURE_21
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_THREADS
operator|||
name|NGX_COMPAT
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_22
define|#
directive|define
name|NGX_MODULE_SIGNATURE_22
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_22
define|#
directive|define
name|NGX_MODULE_SIGNATURE_22
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_PCRE
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_23
define|#
directive|define
name|NGX_MODULE_SIGNATURE_23
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_23
define|#
directive|define
name|NGX_MODULE_SIGNATURE_23
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_SSL
operator|||
name|NGX_COMPAT
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_24
define|#
directive|define
name|NGX_MODULE_SIGNATURE_24
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_24
define|#
directive|define
name|NGX_MODULE_SIGNATURE_24
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_25
define|#
directive|define
name|NGX_MODULE_SIGNATURE_25
value|"1"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_GZIP
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_26
define|#
directive|define
name|NGX_MODULE_SIGNATURE_26
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_26
define|#
directive|define
name|NGX_MODULE_SIGNATURE_26
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_27
define|#
directive|define
name|NGX_MODULE_SIGNATURE_27
value|"1"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_X_FORWARDED_FOR
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_28
define|#
directive|define
name|NGX_MODULE_SIGNATURE_28
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_28
define|#
directive|define
name|NGX_MODULE_SIGNATURE_28
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_REALIP
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_29
define|#
directive|define
name|NGX_MODULE_SIGNATURE_29
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_29
define|#
directive|define
name|NGX_MODULE_SIGNATURE_29
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_HEADERS
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_30
define|#
directive|define
name|NGX_MODULE_SIGNATURE_30
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_30
define|#
directive|define
name|NGX_MODULE_SIGNATURE_30
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_DAV
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_31
define|#
directive|define
name|NGX_MODULE_SIGNATURE_31
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_31
define|#
directive|define
name|NGX_MODULE_SIGNATURE_31
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_CACHE
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_32
define|#
directive|define
name|NGX_MODULE_SIGNATURE_32
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_32
define|#
directive|define
name|NGX_MODULE_SIGNATURE_32
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_HTTP_UPSTREAM_ZONE
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_33
define|#
directive|define
name|NGX_MODULE_SIGNATURE_33
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_33
define|#
directive|define
name|NGX_MODULE_SIGNATURE_33
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|NGX_COMPAT
operator|)
end_if

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_34
define|#
directive|define
name|NGX_MODULE_SIGNATURE_34
value|"1"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_MODULE_SIGNATURE_34
define|#
directive|define
name|NGX_MODULE_SIGNATURE_34
value|"0"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_MODULE_SIGNATURE
define|#
directive|define
name|NGX_MODULE_SIGNATURE
define|\
value|NGX_MODULE_SIGNATURE_0 NGX_MODULE_SIGNATURE_1 NGX_MODULE_SIGNATURE_2      \     NGX_MODULE_SIGNATURE_3 NGX_MODULE_SIGNATURE_4 NGX_MODULE_SIGNATURE_5      \     NGX_MODULE_SIGNATURE_6 NGX_MODULE_SIGNATURE_7 NGX_MODULE_SIGNATURE_8      \     NGX_MODULE_SIGNATURE_9 NGX_MODULE_SIGNATURE_10 NGX_MODULE_SIGNATURE_11    \     NGX_MODULE_SIGNATURE_12 NGX_MODULE_SIGNATURE_13 NGX_MODULE_SIGNATURE_14   \     NGX_MODULE_SIGNATURE_15 NGX_MODULE_SIGNATURE_16 NGX_MODULE_SIGNATURE_17   \     NGX_MODULE_SIGNATURE_18 NGX_MODULE_SIGNATURE_19 NGX_MODULE_SIGNATURE_20   \     NGX_MODULE_SIGNATURE_21 NGX_MODULE_SIGNATURE_22 NGX_MODULE_SIGNATURE_23   \     NGX_MODULE_SIGNATURE_24 NGX_MODULE_SIGNATURE_25 NGX_MODULE_SIGNATURE_26   \     NGX_MODULE_SIGNATURE_27 NGX_MODULE_SIGNATURE_28 NGX_MODULE_SIGNATURE_29   \     NGX_MODULE_SIGNATURE_30 NGX_MODULE_SIGNATURE_31 NGX_MODULE_SIGNATURE_32   \     NGX_MODULE_SIGNATURE_33 NGX_MODULE_SIGNATURE_34
end_define

begin_define
DECL|macro|NGX_MODULE_V1
define|#
directive|define
name|NGX_MODULE_V1
define|\
value|NGX_MODULE_UNSET_INDEX, NGX_MODULE_UNSET_INDEX,                           \     NULL, 0, 0, nginx_version, NGX_MODULE_SIGNATURE
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
DECL|member|name
name|char
modifier|*
name|name
decl_stmt|;
DECL|member|spare0
name|ngx_uint_t
name|spare0
decl_stmt|;
DECL|member|spare1
name|ngx_uint_t
name|spare1
decl_stmt|;
DECL|member|version
name|ngx_uint_t
name|version
decl_stmt|;
DECL|member|signature
specifier|const
name|char
modifier|*
name|signature
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
name|void
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
name|void
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
name|void
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
DECL|struct|__anon28b8eaf90108
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

begin_function_decl
name|ngx_int_t
name|ngx_preinit_modules
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_cycle_modules
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_init_modules
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_count_modules
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_uint_t
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_add_module
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_str_t
modifier|*
name|file
parameter_list|,
name|ngx_module_t
modifier|*
name|module
parameter_list|,
name|char
modifier|*
modifier|*
name|order
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
name|ngx_uint_t
name|ngx_max_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|ngx_module_names
index|[]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_MODULE_H_INCLUDED_ */
end_comment

end_unit

