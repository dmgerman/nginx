begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
file|<nginx.h>
end_include

begin_if
if|#
directive|if
literal|0
end_if

begin_if
unit|typedef struct {      ngx_flag_t  daemon;      ngx_flag_t  master;      ngx_flag_t  worker_reopen;      uid_t       user;      gid_t       group;      ngx_str_t   pid;      ngx_str_t   newpid; } ngx_core_conf_t;   typedef struct {      ngx_file_t    pid;      char         *name;      int           argc;      char *const  *argv; } ngx_master_ctx_t;   static void ngx_master_process_cycle(ngx_cycle_t *cycle, ngx_master_ctx_t *ctx); static void ngx_master_exit(ngx_cycle_t *cycle, ngx_master_ctx_t *ctx); static void ngx_worker_process_cycle(ngx_cycle_t *cycle, void *data);
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
end_if

begin_endif
unit|static int ngx_worker_thread_cycle(void *data);
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_add_inherited_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|char
modifier|*
modifier|*
name|envp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_getopt
parameter_list|(
name|ngx_master_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_core_module_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_set_user
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
DECL|variable|core_name
specifier|static
name|ngx_str_t
name|core_name
init|=
name|ngx_string
argument_list|(
literal|"core"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_core_commands
specifier|static
name|ngx_command_t
name|ngx_core_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"user"
argument_list|)
block|,
name|NGX_MAIN_CONF
operator||
name|NGX_CONF_TAKE12
block|,
name|ngx_set_user
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"daemon"
argument_list|)
block|,
name|NGX_MAIN_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_core_flag_slot
block|,
literal|0
block|,
name|offsetof
argument_list|(
name|ngx_core_conf_t
argument_list|,
name|daemon
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"master_process"
argument_list|)
block|,
name|NGX_MAIN_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_core_flag_slot
block|,
literal|0
block|,
name|offsetof
argument_list|(
name|ngx_core_conf_t
argument_list|,
name|master
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"pid"
argument_list|)
block|,
name|NGX_MAIN_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_core_str_slot
block|,
literal|0
block|,
name|offsetof
argument_list|(
name|ngx_core_conf_t
argument_list|,
name|pid
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|ngx_string
argument_list|(
literal|"worker_reopen"
argument_list|)
block|,
name|NGX_MAIN_CONF
operator||
name|NGX_CONF_TAKE1
block|,
name|ngx_conf_set_core_flag_slot
block|,
literal|0
block|,
name|offsetof
argument_list|(
name|ngx_core_conf_t
argument_list|,
name|worker_reopen
argument_list|)
block|,
name|NULL
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_core_module
name|ngx_module_t
name|ngx_core_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|core_name
block|,
comment|/* module context */
name|ngx_core_commands
block|,
comment|/* module directives */
name|NGX_CORE_MODULE
block|,
comment|/* module type */
name|ngx_core_module_init
block|,
comment|/* init module */
name|NULL
comment|/* init child */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_max_module
name|ngx_int_t
name|ngx_max_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_connection_counter
name|ngx_atomic_t
name|ngx_connection_counter
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_process
name|ngx_int_t
name|ngx_process
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_pid
name|ngx_pid_t
name|ngx_pid
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_new_binary
name|ngx_pid_t
name|ngx_new_binary
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_inherited
name|ngx_int_t
name|ngx_inherited
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_reap
name|ngx_int_t
name|ngx_reap
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_timer
name|ngx_int_t
name|ngx_timer
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_terminate
name|ngx_int_t
name|ngx_terminate
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_quit
name|ngx_int_t
name|ngx_quit
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_noaccept
name|ngx_int_t
name|ngx_noaccept
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_reconfigure
name|ngx_int_t
name|ngx_reconfigure
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_reopen
name|ngx_int_t
name|ngx_reopen
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_change_binary
name|ngx_int_t
name|ngx_change_binary
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|main (int argc,char * const * argv,char ** envp)
name|int
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
specifier|const
modifier|*
name|argv
parameter_list|,
name|char
modifier|*
modifier|*
name|envp
parameter_list|)
block|{
name|ngx_int_t
name|i
decl_stmt|;
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
name|ngx_cycle_t
modifier|*
name|cycle
decl_stmt|,
name|init_cycle
decl_stmt|;
name|ngx_core_conf_t
modifier|*
name|ccf
decl_stmt|;
name|ngx_master_ctx_t
name|ctx
decl_stmt|;
if|#
directive|if
operator|!
operator|(
name|WIN32
operator|)
name|size_t
name|len
decl_stmt|;
name|char
name|pid
index|[
comment|/* STUB */
literal|10
index|]
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
name|__FreeBSD__
name|ngx_debug_init
argument_list|()
expr_stmt|;
endif|#
directive|endif
comment|/* TODO */
name|ngx_max_sockets
operator|=
operator|-
literal|1
expr_stmt|;
name|ngx_time_init
argument_list|()
expr_stmt|;
if|#
directive|if
operator|(
name|HAVE_PCRE
operator|)
name|ngx_regex_init
argument_list|()
expr_stmt|;
endif|#
directive|endif
name|log
operator|=
name|ngx_log_init_errlog
argument_list|()
expr_stmt|;
name|ngx_pid
operator|=
name|ngx_getpid
argument_list|()
expr_stmt|;
comment|/* init_cycle->log is required for signal handlers and ngx_getopt() */
name|ngx_memzero
argument_list|(
operator|&
name|init_cycle
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_cycle_t
argument_list|)
argument_list|)
expr_stmt|;
name|init_cycle
operator|.
name|log
operator|=
name|log
expr_stmt|;
name|ngx_cycle
operator|=
operator|&
name|init_cycle
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|ctx
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_master_ctx_t
argument_list|)
argument_list|)
expr_stmt|;
name|ctx
operator|.
name|argc
operator|=
name|argc
expr_stmt|;
name|ctx
operator|.
name|argv
operator|=
name|argv
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
if|if
condition|(
name|ngx_time_mutex_init
argument_list|(
name|log
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
literal|1
return|;
block|}
endif|#
directive|endif
if|if
condition|(
name|ngx_getopt
argument_list|(
operator|&
name|ctx
argument_list|,
operator|&
name|init_cycle
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
literal|1
return|;
block|}
if|if
condition|(
name|ngx_os_init
argument_list|(
name|log
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
literal|1
return|;
block|}
name|ngx_max_module
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|ngx_modules
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
name|ngx_modules
index|[
name|i
index|]
operator|->
name|index
operator|=
name|ngx_max_module
operator|++
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|init_cycle
operator|.
name|pool
operator|=
name|ngx_create_pool
argument_list|(
literal|1024
argument_list|,
name|log
argument_list|)
operator|)
condition|)
block|{
return|return
literal|1
return|;
block|}
if|if
condition|(
name|ngx_add_inherited_sockets
argument_list|(
operator|&
name|init_cycle
argument_list|,
name|envp
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
literal|1
return|;
block|}
name|cycle
operator|=
name|ngx_init_cycle
argument_list|(
operator|&
name|init_cycle
argument_list|)
expr_stmt|;
if|if
condition|(
name|cycle
operator|==
name|NULL
condition|)
block|{
return|return
literal|1
return|;
block|}
name|ngx_cycle
operator|=
name|cycle
expr_stmt|;
name|ccf
operator|=
operator|(
name|ngx_core_conf_t
operator|*
operator|)
name|ngx_get_conf
argument_list|(
name|cycle
operator|->
name|conf_ctx
argument_list|,
name|ngx_core_module
argument_list|)
expr_stmt|;
name|ngx_process
operator|=
operator|(
name|ccf
operator|->
name|master
operator|!=
literal|0
operator|)
condition|?
name|NGX_PROCESS_MASTER
else|:
name|NGX_PROCESS_SINGLE
expr_stmt|;
if|#
directive|if
operator|(
name|WIN32
operator|)
if|#
directive|if
literal|0
block_content|if (run_as_service) {         if (ngx_servie(cycle->log) == NGX_ERROR) {             return 1;         }          return 0;     }
endif|#
directive|endif
else|#
directive|else
if|if
condition|(
operator|!
name|ngx_inherited
operator|&&
name|ccf
operator|->
name|daemon
operator|!=
literal|0
condition|)
block|{
if|if
condition|(
name|ngx_daemon
argument_list|(
name|cycle
operator|->
name|log
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
literal|1
return|;
block|}
block|}
if|if
condition|(
name|ccf
operator|->
name|pid
operator|.
name|len
operator|==
literal|0
condition|)
block|{
name|ccf
operator|->
name|pid
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
name|NGINX_PID
argument_list|)
operator|-
literal|1
expr_stmt|;
name|ccf
operator|->
name|pid
operator|.
name|data
operator|=
name|NGINX_PID
expr_stmt|;
name|ccf
operator|->
name|newpid
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
name|NGINX_NEW_PID
argument_list|)
operator|-
literal|1
expr_stmt|;
name|ccf
operator|->
name|newpid
operator|.
name|data
operator|=
name|NGINX_NEW_PID
expr_stmt|;
block|}
else|else
block|{
name|ccf
operator|->
name|newpid
operator|.
name|len
operator|=
name|ccf
operator|->
name|pid
operator|.
name|len
operator|+
sizeof|sizeof
argument_list|(
name|NGINX_NEW_PID_EXT
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|ccf
operator|->
name|newpid
operator|.
name|data
operator|=
name|ngx_alloc
argument_list|(
name|ccf
operator|->
name|newpid
operator|.
name|len
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
operator|)
condition|)
block|{
return|return
literal|1
return|;
block|}
name|ngx_memcpy
argument_list|(
name|ngx_cpymem
argument_list|(
name|ccf
operator|->
name|newpid
operator|.
name|data
argument_list|,
name|ccf
operator|->
name|pid
operator|.
name|data
argument_list|,
name|ccf
operator|->
name|pid
operator|.
name|len
argument_list|)
argument_list|,
name|NGINX_NEW_PID_EXT
argument_list|,
sizeof|sizeof
argument_list|(
name|NGINX_NEW_PID_EXT
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|len
operator|=
name|ngx_snprintf
argument_list|(
name|pid
argument_list|,
comment|/* STUB */
literal|10
argument_list|,
name|PID_T_FMT
argument_list|,
name|ngx_getpid
argument_list|()
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|ctx
operator|.
name|pid
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_file_t
argument_list|)
argument_list|)
expr_stmt|;
name|ctx
operator|.
name|pid
operator|.
name|name
operator|=
name|ngx_inherited
condition|?
name|ccf
operator|->
name|newpid
else|:
name|ccf
operator|->
name|pid
expr_stmt|;
name|ctx
operator|.
name|name
operator|=
name|ccf
operator|->
name|pid
operator|.
name|data
expr_stmt|;
name|ctx
operator|.
name|pid
operator|.
name|fd
operator|=
name|ngx_open_file
argument_list|(
name|ctx
operator|.
name|pid
operator|.
name|name
operator|.
name|data
argument_list|,
name|NGX_FILE_RDWR
argument_list|,
name|NGX_FILE_CREATE_OR_OPEN
argument_list|)
expr_stmt|;
if|if
condition|(
name|ctx
operator|.
name|pid
operator|.
name|fd
operator|==
name|NGX_INVALID_FILE
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_open_file_n
literal|" \"%s\" failed"
argument_list|,
name|ctx
operator|.
name|pid
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
literal|1
return|;
block|}
if|if
condition|(
name|ngx_write_file
argument_list|(
operator|&
name|ctx
operator|.
name|pid
argument_list|,
name|pid
argument_list|,
name|len
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
literal|1
return|;
block|}
if|if
condition|(
name|ngx_close_file
argument_list|(
name|ctx
operator|.
name|pid
operator|.
name|fd
argument_list|)
operator|==
name|NGX_FILE_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
name|ngx_errno
argument_list|,
name|ngx_close_file_n
literal|" \"%s\" failed"
argument_list|,
name|ctx
operator|.
name|pid
operator|.
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
endif|#
directive|endif
name|ngx_master_process_cycle
argument_list|(
name|cycle
argument_list|,
operator|&
name|ctx
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

begin_function
DECL|function|ngx_add_inherited_sockets (ngx_cycle_t * cycle,char ** envp)
specifier|static
name|ngx_int_t
name|ngx_add_inherited_sockets
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|char
modifier|*
modifier|*
name|envp
parameter_list|)
block|{
name|char
modifier|*
name|p
decl_stmt|,
modifier|*
name|v
decl_stmt|;
name|ngx_socket_t
name|s
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
for|for
control|(
comment|/* void */
init|;
operator|*
name|envp
condition|;
name|envp
operator|++
control|)
block|{
if|if
condition|(
name|ngx_strncmp
argument_list|(
operator|*
name|envp
argument_list|,
name|NGINX_VAR
argument_list|,
name|NGINX_VAR_LEN
argument_list|)
operator|!=
literal|0
condition|)
block|{
continue|continue;
block|}
name|ngx_log_error
argument_list|(
name|NGX_LOG_INFO
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"using inherited sockets from \"%s\""
argument_list|,
operator|*
name|envp
argument_list|)
expr_stmt|;
name|ngx_init_array
argument_list|(
name|cycle
operator|->
name|listening
argument_list|,
name|cycle
operator|->
name|pool
argument_list|,
literal|10
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_listening_t
argument_list|)
argument_list|,
name|NGX_ERROR
argument_list|)
expr_stmt|;
for|for
control|(
name|p
operator|=
operator|*
name|envp
operator|+
name|NGINX_VAR_LEN
operator|,
name|v
operator|=
name|p
init|;
operator|*
name|p
condition|;
name|p
operator|++
control|)
block|{
if|if
condition|(
operator|*
name|p
operator|==
literal|':'
operator|||
operator|*
name|p
operator|==
literal|';'
condition|)
block|{
name|s
operator|=
name|ngx_atoi
argument_list|(
name|v
argument_list|,
name|p
operator|-
name|v
argument_list|)
expr_stmt|;
if|if
condition|(
name|s
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"invalid socket number \"%s\" "
literal|"in NGINX enviroment variable, "
literal|"ignoring the rest of the variable"
argument_list|,
name|v
argument_list|)
expr_stmt|;
break|break;
block|}
name|v
operator|=
name|p
operator|+
literal|1
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|ls
operator|=
name|ngx_push_array
argument_list|(
operator|&
name|cycle
operator|->
name|listening
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ls
operator|->
name|fd
operator|=
name|s
expr_stmt|;
block|}
block|}
name|ngx_inherited
operator|=
literal|1
expr_stmt|;
return|return
name|ngx_set_inherited_sockets
argument_list|(
name|cycle
argument_list|)
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_exec_new_binary (ngx_cycle_t * cycle,char * const * argv)
name|ngx_pid_t
name|ngx_exec_new_binary
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|char
modifier|*
specifier|const
modifier|*
name|argv
parameter_list|)
block|{
name|char
modifier|*
name|env
index|[
literal|2
index|]
decl_stmt|,
modifier|*
name|var
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|ngx_int_t
name|i
decl_stmt|;
name|ngx_pid_t
name|pid
decl_stmt|;
name|ngx_exec_ctx_t
name|ctx
decl_stmt|;
name|ngx_listening_t
modifier|*
name|ls
decl_stmt|;
name|ctx
operator|.
name|path
operator|=
name|argv
index|[
literal|0
index|]
expr_stmt|;
name|ctx
operator|.
name|name
operator|=
literal|"new binary process"
expr_stmt|;
name|ctx
operator|.
name|argv
operator|=
name|argv
expr_stmt|;
name|var
operator|=
name|ngx_alloc
argument_list|(
name|NGINX_VAR_LEN
operator|+
name|cycle
operator|->
name|listening
operator|.
name|nelts
operator|*
operator|(
name|NGX_INT32_LEN
operator|+
literal|1
operator|)
operator|+
literal|1
argument_list|,
name|cycle
operator|->
name|log
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_cpymem
argument_list|(
name|var
argument_list|,
name|NGINX_VAR
argument_list|,
name|NGINX_VAR_LEN
argument_list|)
expr_stmt|;
name|ls
operator|=
name|cycle
operator|->
name|listening
operator|.
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|cycle
operator|->
name|listening
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|+=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|NGX_INT32_LEN
operator|+
literal|2
argument_list|,
literal|"%u;"
argument_list|,
name|ls
index|[
name|i
index|]
operator|.
name|fd
argument_list|)
expr_stmt|;
block|}
name|env
index|[
literal|0
index|]
operator|=
name|var
expr_stmt|;
name|env
index|[
literal|1
index|]
operator|=
name|NULL
expr_stmt|;
name|ctx
operator|.
name|envp
operator|=
operator|(
name|char
operator|*
specifier|const
operator|*
operator|)
operator|&
name|env
expr_stmt|;
name|pid
operator|=
name|ngx_execute
argument_list|(
name|cycle
argument_list|,
operator|&
name|ctx
argument_list|)
expr_stmt|;
name|ngx_free
argument_list|(
name|var
argument_list|)
expr_stmt|;
return|return
name|pid
return|;
block|}
end_function

begin_function
DECL|function|ngx_getopt (ngx_master_ctx_t * ctx,ngx_cycle_t * cycle)
specifier|static
name|ngx_int_t
name|ngx_getopt
parameter_list|(
name|ngx_master_ctx_t
modifier|*
name|ctx
parameter_list|,
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_int_t
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|ctx
operator|->
name|argc
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ctx
operator|->
name|argv
index|[
name|i
index|]
index|[
literal|0
index|]
operator|!=
literal|'-'
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"invalid option: \"%s\""
argument_list|,
name|ctx
operator|->
name|argv
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
switch|switch
condition|(
name|ctx
operator|->
name|argv
index|[
name|i
index|]
index|[
literal|1
index|]
condition|)
block|{
case|case
literal|'c'
case|:
name|cycle
operator|->
name|conf_file
operator|.
name|data
operator|=
name|ctx
operator|->
name|argv
index|[
operator|++
name|i
index|]
expr_stmt|;
name|cycle
operator|->
name|conf_file
operator|.
name|len
operator|=
name|ngx_strlen
argument_list|(
name|cycle
operator|->
name|conf_file
operator|.
name|data
argument_list|)
expr_stmt|;
break|break;
default|default:
name|ngx_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"invalid option: \"%s\""
argument_list|,
name|ctx
operator|->
name|argv
index|[
name|i
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
block|}
if|if
condition|(
name|cycle
operator|->
name|conf_file
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
name|cycle
operator|->
name|conf_file
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
name|NGINX_CONF
argument_list|)
operator|-
literal|1
expr_stmt|;
name|cycle
operator|->
name|conf_file
operator|.
name|data
operator|=
name|NGINX_CONF
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_core_module_init (ngx_cycle_t * cycle)
specifier|static
name|ngx_int_t
name|ngx_core_module_init
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
block|{
name|ngx_core_conf_t
modifier|*
name|ccf
decl_stmt|;
comment|/*      * ngx_core_module has a special init procedure: it is called by      * ngx_init_cycle() before the configuration file parsing to create      * ngx_core_module configuration and to set its default parameters      */
if|if
condition|(
operator|(
operator|(
name|void
operator|*
operator|*
operator|)
operator|(
name|cycle
operator|->
name|conf_ctx
operator|)
operator|)
index|[
name|ngx_core_module
operator|.
name|index
index|]
operator|!=
name|NULL
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
operator|!
operator|(
name|ccf
operator|=
name|ngx_pcalloc
argument_list|(
name|cycle
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_core_conf_t
argument_list|)
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
comment|/* set by pcalloc()      *      * ccf->pid = NULL;      * ccf->newpid = NULL;      */
name|ccf
operator|->
name|daemon
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|ccf
operator|->
name|master
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|ccf
operator|->
name|worker_reopen
operator|=
name|NGX_CONF_UNSET
expr_stmt|;
name|ccf
operator|->
name|user
operator|=
operator|(
name|ngx_uid_t
operator|)
name|NGX_CONF_UNSET
expr_stmt|;
name|ccf
operator|->
name|group
operator|=
operator|(
name|ngx_gid_t
operator|)
name|NGX_CONF_UNSET
expr_stmt|;
operator|(
operator|(
name|void
operator|*
operator|*
operator|)
operator|(
name|cycle
operator|->
name|conf_ctx
operator|)
operator|)
index|[
name|ngx_core_module
operator|.
name|index
index|]
operator|=
name|ccf
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_set_user (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
specifier|static
name|char
modifier|*
name|ngx_set_user
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
block|{
if|#
directive|if
operator|(
name|WIN32
operator|)
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"\"user\" is not supported, ignored"
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
else|#
directive|else
name|struct
name|passwd
modifier|*
name|pwd
decl_stmt|;
name|struct
name|group
modifier|*
name|grp
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_core_conf_t
modifier|*
name|ccf
decl_stmt|;
name|ccf
operator|=
operator|*
operator|(
name|void
operator|*
operator|*
operator|)
name|conf
expr_stmt|;
if|if
condition|(
name|ccf
operator|->
name|user
operator|!=
operator|(
name|uid_t
operator|)
name|NGX_CONF_UNSET
condition|)
block|{
return|return
literal|"is duplicate"
return|;
block|}
name|value
operator|=
operator|(
name|ngx_str_t
operator|*
operator|)
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
name|pwd
operator|=
name|getpwnam
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|pwd
operator|==
name|NULL
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
name|ngx_errno
argument_list|,
literal|"getpwnam(%s) failed"
argument_list|,
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|ccf
operator|->
name|user
operator|=
name|pwd
operator|->
name|pw_uid
expr_stmt|;
if|if
condition|(
name|cf
operator|->
name|args
operator|->
name|nelts
operator|==
literal|2
condition|)
block|{
return|return
name|NGX_CONF_OK
return|;
block|}
name|grp
operator|=
name|getgrnam
argument_list|(
name|value
index|[
literal|2
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|grp
operator|==
name|NULL
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
name|ngx_errno
argument_list|,
literal|"getgrnam(%s) failed"
argument_list|,
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|ccf
operator|->
name|group
operator|=
name|grp
operator|->
name|gr_gid
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
endif|#
directive|endif
block|}
end_function

end_unit

