begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Ruslan Ermilov  * Copyright (C) Nginx, Inc.  */
end_comment

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
file|<ngx_stream.h>
end_include

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_stream_upstream_zone
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
specifier|static
name|ngx_int_t
name|ngx_stream_upstream_init_zone
parameter_list|(
name|ngx_shm_zone_t
modifier|*
name|shm_zone
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|ngx_stream_upstream_zone_copy_peers
parameter_list|(
name|ngx_slab_pool_t
modifier|*
name|shpool
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|uscf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|ngx_stream_upstream_zone_copy_peer
parameter_list|(
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|peers
parameter_list|,
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|src
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_stream_upstream_zone_commands
specifier|static
name|ngx_command_t
name|ngx_stream_upstream_zone_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"zone"
argument_list|)
block|,
name|NGX_STREAM_UPS_CONF
operator||
name|NGX_CONF_TAKE12
block|,
name|ngx_stream_upstream_zone
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_stream_upstream_zone_module_ctx
specifier|static
name|ngx_stream_module_t
name|ngx_stream_upstream_zone_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|NULL
block|,
comment|/* postconfiguration */
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|NULL
block|,
comment|/* create server configuration */
name|NULL
comment|/* merge server configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_stream_upstream_zone_module
name|ngx_module_t
name|ngx_stream_upstream_zone_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_stream_upstream_zone_module_ctx
block|,
comment|/* module context */
name|ngx_stream_upstream_zone_commands
block|,
comment|/* module directives */
name|NGX_STREAM_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|NULL
block|,
comment|/* init module */
name|NULL
block|,
comment|/* init process */
name|NULL
block|,
comment|/* init thread */
name|NULL
block|,
comment|/* exit thread */
name|NULL
block|,
comment|/* exit process */
name|NULL
block|,
comment|/* exit master */
name|NGX_MODULE_V1_PADDING
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_stream_upstream_zone (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_stream_upstream_zone
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
name|ssize_t
name|size
decl_stmt|;
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|uscf
decl_stmt|;
name|ngx_stream_upstream_main_conf_t
modifier|*
name|umcf
decl_stmt|;
name|uscf
operator|=
name|ngx_stream_conf_get_module_srv_conf
argument_list|(
name|cf
argument_list|,
name|ngx_stream_upstream_module
argument_list|)
expr_stmt|;
name|umcf
operator|=
name|ngx_stream_conf_get_module_main_conf
argument_list|(
name|cf
argument_list|,
name|ngx_stream_upstream_module
argument_list|)
expr_stmt|;
name|value
operator|=
name|cf
operator|->
name|args
operator|->
name|elts
expr_stmt|;
if|if
condition|(
operator|!
name|value
index|[
literal|1
index|]
operator|.
name|len
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid zone name \"%V\""
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|cf
operator|->
name|args
operator|->
name|nelts
operator|==
literal|3
condition|)
block|{
name|size
operator|=
name|ngx_parse_size
argument_list|(
operator|&
name|value
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
if|if
condition|(
name|size
operator|==
name|NGX_ERROR
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid zone size \"%V\""
argument_list|,
operator|&
name|value
index|[
literal|2
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
if|if
condition|(
name|size
operator|<
operator|(
name|ssize_t
operator|)
operator|(
literal|8
operator|*
name|ngx_pagesize
operator|)
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"zone \"%V\" is too small"
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|)
expr_stmt|;
return|return
name|NGX_CONF_ERROR
return|;
block|}
block|}
else|else
block|{
name|size
operator|=
literal|0
expr_stmt|;
block|}
name|uscf
operator|->
name|shm_zone
operator|=
name|ngx_shared_memory_add
argument_list|(
name|cf
argument_list|,
operator|&
name|value
index|[
literal|1
index|]
argument_list|,
name|size
argument_list|,
operator|&
name|ngx_stream_upstream_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|uscf
operator|->
name|shm_zone
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_CONF_ERROR
return|;
block|}
name|uscf
operator|->
name|shm_zone
operator|->
name|init
operator|=
name|ngx_stream_upstream_init_zone
expr_stmt|;
name|uscf
operator|->
name|shm_zone
operator|->
name|data
operator|=
name|umcf
expr_stmt|;
name|uscf
operator|->
name|shm_zone
operator|->
name|noreuse
operator|=
literal|1
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_upstream_init_zone (ngx_shm_zone_t * shm_zone,void * data)
name|ngx_stream_upstream_init_zone
parameter_list|(
name|ngx_shm_zone_t
modifier|*
name|shm_zone
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|size_t
name|len
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_slab_pool_t
modifier|*
name|shpool
decl_stmt|;
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|peers
decl_stmt|,
modifier|*
modifier|*
name|peersp
decl_stmt|;
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|uscf
decl_stmt|,
modifier|*
modifier|*
name|uscfp
decl_stmt|;
name|ngx_stream_upstream_main_conf_t
modifier|*
name|umcf
decl_stmt|;
name|shpool
operator|=
operator|(
name|ngx_slab_pool_t
operator|*
operator|)
name|shm_zone
operator|->
name|shm
operator|.
name|addr
expr_stmt|;
name|umcf
operator|=
name|shm_zone
operator|->
name|data
expr_stmt|;
name|uscfp
operator|=
name|umcf
operator|->
name|upstreams
operator|.
name|elts
expr_stmt|;
if|if
condition|(
name|shm_zone
operator|->
name|shm
operator|.
name|exists
condition|)
block|{
name|peers
operator|=
name|shpool
operator|->
name|data
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|umcf
operator|->
name|upstreams
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|uscf
operator|=
name|uscfp
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|uscf
operator|->
name|shm_zone
operator|!=
name|shm_zone
condition|)
block|{
continue|continue;
block|}
name|uscf
operator|->
name|peer
operator|.
name|data
operator|=
name|peers
expr_stmt|;
name|peers
operator|=
name|peers
operator|->
name|zone_next
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
name|len
operator|=
sizeof|sizeof
argument_list|(
literal|" in upstream zone \"\""
argument_list|)
operator|+
name|shm_zone
operator|->
name|shm
operator|.
name|name
operator|.
name|len
expr_stmt|;
name|shpool
operator|->
name|log_ctx
operator|=
name|ngx_slab_alloc
argument_list|(
name|shpool
argument_list|,
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|shpool
operator|->
name|log_ctx
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_sprintf
argument_list|(
name|shpool
operator|->
name|log_ctx
argument_list|,
literal|" in upstream zone \"%V\"%Z"
argument_list|,
operator|&
name|shm_zone
operator|->
name|shm
operator|.
name|name
argument_list|)
expr_stmt|;
comment|/* copy peers to shared memory */
name|peersp
operator|=
operator|(
name|ngx_stream_upstream_rr_peers_t
operator|*
operator|*
operator|)
operator|(
name|void
operator|*
operator|)
operator|&
name|shpool
operator|->
name|data
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|umcf
operator|->
name|upstreams
operator|.
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|uscf
operator|=
name|uscfp
index|[
name|i
index|]
expr_stmt|;
if|if
condition|(
name|uscf
operator|->
name|shm_zone
operator|!=
name|shm_zone
condition|)
block|{
continue|continue;
block|}
name|peers
operator|=
name|ngx_stream_upstream_zone_copy_peers
argument_list|(
name|shpool
argument_list|,
name|uscf
argument_list|)
expr_stmt|;
if|if
condition|(
name|peers
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
operator|*
name|peersp
operator|=
name|peers
expr_stmt|;
name|peersp
operator|=
operator|&
name|peers
operator|->
name|zone_next
expr_stmt|;
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_stream_upstream_rr_peers_t
modifier|*
DECL|function|ngx_stream_upstream_zone_copy_peers (ngx_slab_pool_t * shpool,ngx_stream_upstream_srv_conf_t * uscf)
name|ngx_stream_upstream_zone_copy_peers
parameter_list|(
name|ngx_slab_pool_t
modifier|*
name|shpool
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|uscf
parameter_list|)
block|{
name|ngx_str_t
modifier|*
name|name
decl_stmt|;
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|,
modifier|*
modifier|*
name|peerp
decl_stmt|;
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|peers
decl_stmt|,
modifier|*
name|backup
decl_stmt|;
name|peers
operator|=
name|ngx_slab_alloc
argument_list|(
name|shpool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_rr_peers_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|peers
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|ngx_memcpy
argument_list|(
name|peers
argument_list|,
name|uscf
operator|->
name|peer
operator|.
name|data
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_rr_peers_t
argument_list|)
argument_list|)
expr_stmt|;
name|name
operator|=
name|ngx_slab_alloc
argument_list|(
name|shpool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_str_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|name
operator|->
name|data
operator|=
name|ngx_slab_alloc
argument_list|(
name|shpool
argument_list|,
name|peers
operator|->
name|name
operator|->
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
operator|->
name|data
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|ngx_memcpy
argument_list|(
name|name
operator|->
name|data
argument_list|,
name|peers
operator|->
name|name
operator|->
name|data
argument_list|,
name|peers
operator|->
name|name
operator|->
name|len
argument_list|)
expr_stmt|;
name|name
operator|->
name|len
operator|=
name|peers
operator|->
name|name
operator|->
name|len
expr_stmt|;
name|peers
operator|->
name|name
operator|=
name|name
expr_stmt|;
name|peers
operator|->
name|shpool
operator|=
name|shpool
expr_stmt|;
for|for
control|(
name|peerp
operator|=
operator|&
name|peers
operator|->
name|peer
init|;
operator|*
name|peerp
condition|;
name|peerp
operator|=
operator|&
name|peer
operator|->
name|next
control|)
block|{
comment|/* pool is unlocked */
name|peer
operator|=
name|ngx_stream_upstream_zone_copy_peer
argument_list|(
name|peers
argument_list|,
operator|*
name|peerp
argument_list|)
expr_stmt|;
if|if
condition|(
name|peer
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
operator|*
name|peerp
operator|=
name|peer
expr_stmt|;
block|}
if|if
condition|(
name|peers
operator|->
name|next
operator|==
name|NULL
condition|)
block|{
goto|goto
name|done
goto|;
block|}
name|backup
operator|=
name|ngx_slab_alloc
argument_list|(
name|shpool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_rr_peers_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|backup
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|ngx_memcpy
argument_list|(
name|backup
argument_list|,
name|peers
operator|->
name|next
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_rr_peers_t
argument_list|)
argument_list|)
expr_stmt|;
name|backup
operator|->
name|name
operator|=
name|name
expr_stmt|;
name|backup
operator|->
name|shpool
operator|=
name|shpool
expr_stmt|;
for|for
control|(
name|peerp
operator|=
operator|&
name|backup
operator|->
name|peer
init|;
operator|*
name|peerp
condition|;
name|peerp
operator|=
operator|&
name|peer
operator|->
name|next
control|)
block|{
comment|/* pool is unlocked */
name|peer
operator|=
name|ngx_stream_upstream_zone_copy_peer
argument_list|(
name|backup
argument_list|,
operator|*
name|peerp
argument_list|)
expr_stmt|;
if|if
condition|(
name|peer
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
operator|*
name|peerp
operator|=
name|peer
expr_stmt|;
block|}
name|peers
operator|->
name|next
operator|=
name|backup
expr_stmt|;
name|done
label|:
name|uscf
operator|->
name|peer
operator|.
name|data
operator|=
name|peers
expr_stmt|;
return|return
name|peers
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_stream_upstream_rr_peer_t
modifier|*
DECL|function|ngx_stream_upstream_zone_copy_peer (ngx_stream_upstream_rr_peers_t * peers,ngx_stream_upstream_rr_peer_t * src)
name|ngx_stream_upstream_zone_copy_peer
parameter_list|(
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|peers
parameter_list|,
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|src
parameter_list|)
block|{
name|ngx_slab_pool_t
modifier|*
name|pool
decl_stmt|;
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|dst
decl_stmt|;
name|pool
operator|=
name|peers
operator|->
name|shpool
expr_stmt|;
name|dst
operator|=
name|ngx_slab_calloc_locked
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_rr_peer_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dst
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
if|if
condition|(
name|src
condition|)
block|{
name|ngx_memcpy
argument_list|(
name|dst
argument_list|,
name|src
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_rr_peer_t
argument_list|)
argument_list|)
expr_stmt|;
name|dst
operator|->
name|sockaddr
operator|=
name|NULL
expr_stmt|;
name|dst
operator|->
name|name
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
name|dst
operator|->
name|server
operator|.
name|data
operator|=
name|NULL
expr_stmt|;
block|}
name|dst
operator|->
name|sockaddr
operator|=
name|ngx_slab_calloc_locked
argument_list|(
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_sockaddr_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|dst
operator|->
name|sockaddr
operator|==
name|NULL
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
name|dst
operator|->
name|name
operator|.
name|data
operator|=
name|ngx_slab_calloc_locked
argument_list|(
name|pool
argument_list|,
name|NGX_SOCKADDR_STRLEN
argument_list|)
expr_stmt|;
if|if
condition|(
name|dst
operator|->
name|name
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
if|if
condition|(
name|src
condition|)
block|{
name|ngx_memcpy
argument_list|(
name|dst
operator|->
name|sockaddr
argument_list|,
name|src
operator|->
name|sockaddr
argument_list|,
name|src
operator|->
name|socklen
argument_list|)
expr_stmt|;
name|ngx_memcpy
argument_list|(
name|dst
operator|->
name|name
operator|.
name|data
argument_list|,
name|src
operator|->
name|name
operator|.
name|data
argument_list|,
name|src
operator|->
name|name
operator|.
name|len
argument_list|)
expr_stmt|;
name|dst
operator|->
name|server
operator|.
name|data
operator|=
name|ngx_slab_alloc_locked
argument_list|(
name|pool
argument_list|,
name|src
operator|->
name|server
operator|.
name|len
argument_list|)
expr_stmt|;
if|if
condition|(
name|dst
operator|->
name|server
operator|.
name|data
operator|==
name|NULL
condition|)
block|{
goto|goto
name|failed
goto|;
block|}
name|ngx_memcpy
argument_list|(
name|dst
operator|->
name|server
operator|.
name|data
argument_list|,
name|src
operator|->
name|server
operator|.
name|data
argument_list|,
name|src
operator|->
name|server
operator|.
name|len
argument_list|)
expr_stmt|;
block|}
return|return
name|dst
return|;
name|failed
label|:
if|if
condition|(
name|dst
operator|->
name|server
operator|.
name|data
condition|)
block|{
name|ngx_slab_free_locked
argument_list|(
name|pool
argument_list|,
name|dst
operator|->
name|server
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dst
operator|->
name|name
operator|.
name|data
condition|)
block|{
name|ngx_slab_free_locked
argument_list|(
name|pool
argument_list|,
name|dst
operator|->
name|name
operator|.
name|data
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|dst
operator|->
name|sockaddr
condition|)
block|{
name|ngx_slab_free_locked
argument_list|(
name|pool
argument_list|,
name|dst
operator|->
name|sockaddr
argument_list|)
expr_stmt|;
block|}
name|ngx_slab_free_locked
argument_list|(
name|pool
argument_list|,
name|dst
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

end_unit

