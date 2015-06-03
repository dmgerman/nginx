begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Roman Arutyunyan  * Copyright (C) Nginx, Inc.  */
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

begin_typedef
DECL|struct|__anon2bb0515d0108
typedef|typedef
struct|struct
block|{
DECL|member|hash
name|uint32_t
name|hash
decl_stmt|;
DECL|member|server
name|ngx_str_t
modifier|*
name|server
decl_stmt|;
DECL|typedef|ngx_stream_upstream_chash_point_t
block|}
name|ngx_stream_upstream_chash_point_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2bb0515d0208
typedef|typedef
struct|struct
block|{
DECL|member|number
name|ngx_uint_t
name|number
decl_stmt|;
DECL|member|point
name|ngx_stream_upstream_chash_point_t
name|point
index|[
literal|1
index|]
decl_stmt|;
DECL|typedef|ngx_stream_upstream_chash_points_t
block|}
name|ngx_stream_upstream_chash_points_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2bb0515d0308
typedef|typedef
struct|struct
block|{
DECL|member|points
name|ngx_stream_upstream_chash_points_t
modifier|*
name|points
decl_stmt|;
DECL|typedef|ngx_stream_upstream_hash_srv_conf_t
block|}
name|ngx_stream_upstream_hash_srv_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2bb0515d0408
typedef|typedef
struct|struct
block|{
comment|/* the round robin data must be first */
DECL|member|rrp
name|ngx_stream_upstream_rr_peer_data_t
name|rrp
decl_stmt|;
DECL|member|conf
name|ngx_stream_upstream_hash_srv_conf_t
modifier|*
name|conf
decl_stmt|;
DECL|member|key
name|ngx_str_t
name|key
decl_stmt|;
DECL|member|tries
name|ngx_uint_t
name|tries
decl_stmt|;
DECL|member|rehash
name|ngx_uint_t
name|rehash
decl_stmt|;
DECL|member|hash
name|uint32_t
name|hash
decl_stmt|;
DECL|member|get_rr_peer
name|ngx_event_get_peer_pt
name|get_rr_peer
decl_stmt|;
DECL|typedef|ngx_stream_upstream_hash_peer_data_t
block|}
name|ngx_stream_upstream_hash_peer_data_t
typedef|;
end_typedef

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_upstream_init_hash
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_upstream_init_hash_peer
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_upstream_get_hash_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_upstream_init_chash
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|int
name|ngx_libc_cdecl
name|ngx_stream_upstream_chash_cmp_points
parameter_list|(
specifier|const
name|void
modifier|*
name|one
parameter_list|,
specifier|const
name|void
modifier|*
name|two
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_uint_t
name|ngx_stream_upstream_find_chash_point
parameter_list|(
name|ngx_stream_upstream_chash_points_t
modifier|*
name|points
parameter_list|,
name|uint32_t
name|hash
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_upstream_init_chash_peer
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|ngx_int_t
name|ngx_stream_upstream_get_chash_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_stream_upstream_hash_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_stream_upstream_hash
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
DECL|variable|ngx_stream_upstream_hash_commands
specifier|static
name|ngx_command_t
name|ngx_stream_upstream_hash_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"hash"
argument_list|)
block|,
name|NGX_STREAM_UPS_CONF
operator||
name|NGX_CONF_TAKE12
block|,
name|ngx_stream_upstream_hash
block|,
name|NGX_STREAM_SRV_CONF_OFFSET
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
DECL|variable|ngx_stream_upstream_hash_module_ctx
specifier|static
name|ngx_stream_module_t
name|ngx_stream_upstream_hash_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|ngx_stream_upstream_hash_create_conf
block|,
comment|/* create server configuration */
name|NULL
block|,
comment|/* merge server configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_stream_upstream_hash_module
name|ngx_module_t
name|ngx_stream_upstream_hash_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_stream_upstream_hash_module_ctx
block|,
comment|/* module context */
name|ngx_stream_upstream_hash_commands
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
name|ngx_int_t
DECL|function|ngx_stream_upstream_init_hash (ngx_conf_t * cf,ngx_stream_upstream_srv_conf_t * us)
name|ngx_stream_upstream_init_hash
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
block|{
if|if
condition|(
name|ngx_stream_upstream_init_round_robin
argument_list|(
name|cf
argument_list|,
name|us
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|us
operator|->
name|peer
operator|.
name|init
operator|=
name|ngx_stream_upstream_init_hash_peer
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_upstream_init_hash_peer (ngx_stream_session_t * s,ngx_stream_upstream_srv_conf_t * us)
name|ngx_stream_upstream_init_hash_peer
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
block|{
name|ngx_stream_upstream_hash_srv_conf_t
modifier|*
name|hcf
decl_stmt|;
name|ngx_stream_upstream_hash_peer_data_t
modifier|*
name|hp
decl_stmt|;
name|hp
operator|=
name|ngx_palloc
argument_list|(
name|s
operator|->
name|connection
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_hash_peer_data_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|hp
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|s
operator|->
name|upstream
operator|->
name|peer
operator|.
name|data
operator|=
operator|&
name|hp
operator|->
name|rrp
expr_stmt|;
if|if
condition|(
name|ngx_stream_upstream_init_round_robin_peer
argument_list|(
name|s
argument_list|,
name|us
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|s
operator|->
name|upstream
operator|->
name|peer
operator|.
name|get
operator|=
name|ngx_stream_upstream_get_hash_peer
expr_stmt|;
name|hcf
operator|=
name|ngx_stream_conf_upstream_srv_conf
argument_list|(
name|us
argument_list|,
name|ngx_stream_upstream_hash_module
argument_list|)
expr_stmt|;
name|hp
operator|->
name|key
operator|=
name|s
operator|->
name|connection
operator|->
name|addr_text
expr_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_STREAM
argument_list|,
name|s
operator|->
name|connection
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"upstream hash key:\"%V\""
argument_list|,
operator|&
name|hp
operator|->
name|key
argument_list|)
expr_stmt|;
name|hp
operator|->
name|conf
operator|=
name|hcf
expr_stmt|;
name|hp
operator|->
name|tries
operator|=
literal|0
expr_stmt|;
name|hp
operator|->
name|rehash
operator|=
literal|0
expr_stmt|;
name|hp
operator|->
name|hash
operator|=
literal|0
expr_stmt|;
name|hp
operator|->
name|get_rr_peer
operator|=
name|ngx_stream_upstream_get_round_robin_peer
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_upstream_get_hash_peer (ngx_peer_connection_t * pc,void * data)
name|ngx_stream_upstream_get_hash_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|ngx_stream_upstream_hash_peer_data_t
modifier|*
name|hp
init|=
name|data
decl_stmt|;
name|time_t
name|now
decl_stmt|;
name|u_char
name|buf
index|[
name|NGX_INT_T_LEN
index|]
decl_stmt|;
name|size_t
name|size
decl_stmt|;
name|uint32_t
name|hash
decl_stmt|;
name|ngx_int_t
name|w
decl_stmt|;
name|uintptr_t
name|m
decl_stmt|;
name|ngx_uint_t
name|n
decl_stmt|,
name|p
decl_stmt|;
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_STREAM
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"get hash peer, try: %ui"
argument_list|,
name|pc
operator|->
name|tries
argument_list|)
expr_stmt|;
name|ngx_stream_upstream_rr_peers_wlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
if|if
condition|(
name|hp
operator|->
name|tries
operator|>
literal|20
operator|||
name|hp
operator|->
name|rrp
operator|.
name|peers
operator|->
name|single
condition|)
block|{
name|ngx_stream_upstream_rr_peers_unlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
return|return
name|hp
operator|->
name|get_rr_peer
argument_list|(
name|pc
argument_list|,
operator|&
name|hp
operator|->
name|rrp
argument_list|)
return|;
block|}
name|now
operator|=
name|ngx_time
argument_list|()
expr_stmt|;
name|pc
operator|->
name|connection
operator|=
name|NULL
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
comment|/*          * Hash expression is compatible with Cache::Memcached:          * ((crc32([REHASH] KEY)>> 16)& 0x7fff) + PREV_HASH          * with REHASH omitted at the first iteration.          */
name|ngx_crc32_init
argument_list|(
name|hash
argument_list|)
expr_stmt|;
if|if
condition|(
name|hp
operator|->
name|rehash
operator|>
literal|0
condition|)
block|{
name|size
operator|=
name|ngx_sprintf
argument_list|(
name|buf
argument_list|,
literal|"%ui"
argument_list|,
name|hp
operator|->
name|rehash
argument_list|)
operator|-
name|buf
expr_stmt|;
name|ngx_crc32_update
argument_list|(
operator|&
name|hash
argument_list|,
name|buf
argument_list|,
name|size
argument_list|)
expr_stmt|;
block|}
name|ngx_crc32_update
argument_list|(
operator|&
name|hash
argument_list|,
name|hp
operator|->
name|key
operator|.
name|data
argument_list|,
name|hp
operator|->
name|key
operator|.
name|len
argument_list|)
expr_stmt|;
name|ngx_crc32_final
argument_list|(
name|hash
argument_list|)
expr_stmt|;
name|hash
operator|=
operator|(
name|hash
operator|>>
literal|16
operator|)
operator|&
literal|0x7fff
expr_stmt|;
name|hp
operator|->
name|hash
operator|+=
name|hash
expr_stmt|;
name|hp
operator|->
name|rehash
operator|++
expr_stmt|;
name|w
operator|=
name|hp
operator|->
name|hash
operator|%
name|hp
operator|->
name|rrp
operator|.
name|peers
operator|->
name|total_weight
expr_stmt|;
name|peer
operator|=
name|hp
operator|->
name|rrp
operator|.
name|peers
operator|->
name|peer
expr_stmt|;
name|p
operator|=
literal|0
expr_stmt|;
while|while
condition|(
name|w
operator|>=
name|peer
operator|->
name|weight
condition|)
block|{
name|w
operator|-=
name|peer
operator|->
name|weight
expr_stmt|;
name|peer
operator|=
name|peer
operator|->
name|next
expr_stmt|;
name|p
operator|++
expr_stmt|;
block|}
name|n
operator|=
name|p
operator|/
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
name|m
operator|=
operator|(
name|uintptr_t
operator|)
literal|1
operator|<<
name|p
operator|%
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|hp
operator|->
name|rrp
operator|.
name|tried
index|[
name|n
index|]
operator|&
name|m
condition|)
block|{
goto|goto
name|next
goto|;
block|}
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_STREAM
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"get hash peer, value:%uD, peer:%ui"
argument_list|,
name|hp
operator|->
name|hash
argument_list|,
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|peer
operator|->
name|down
condition|)
block|{
goto|goto
name|next
goto|;
block|}
if|if
condition|(
name|peer
operator|->
name|max_fails
operator|&&
name|peer
operator|->
name|fails
operator|>=
name|peer
operator|->
name|max_fails
operator|&&
name|now
operator|-
name|peer
operator|->
name|checked
operator|<=
name|peer
operator|->
name|fail_timeout
condition|)
block|{
goto|goto
name|next
goto|;
block|}
break|break;
name|next
label|:
if|if
condition|(
operator|++
name|hp
operator|->
name|tries
operator|>
literal|20
condition|)
block|{
name|ngx_stream_upstream_rr_peers_unlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
return|return
name|hp
operator|->
name|get_rr_peer
argument_list|(
name|pc
argument_list|,
operator|&
name|hp
operator|->
name|rrp
argument_list|)
return|;
block|}
block|}
name|hp
operator|->
name|rrp
operator|.
name|current
operator|=
name|peer
expr_stmt|;
name|pc
operator|->
name|sockaddr
operator|=
name|peer
operator|->
name|sockaddr
expr_stmt|;
name|pc
operator|->
name|socklen
operator|=
name|peer
operator|->
name|socklen
expr_stmt|;
name|pc
operator|->
name|name
operator|=
operator|&
name|peer
operator|->
name|name
expr_stmt|;
name|peer
operator|->
name|conns
operator|++
expr_stmt|;
if|if
condition|(
name|now
operator|-
name|peer
operator|->
name|checked
operator|>
name|peer
operator|->
name|fail_timeout
condition|)
block|{
name|peer
operator|->
name|checked
operator|=
name|now
expr_stmt|;
block|}
name|ngx_stream_upstream_rr_peers_unlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
name|hp
operator|->
name|rrp
operator|.
name|tried
index|[
name|n
index|]
operator||=
name|m
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_upstream_init_chash (ngx_conf_t * cf,ngx_stream_upstream_srv_conf_t * us)
name|ngx_stream_upstream_init_chash
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
block|{
name|u_char
modifier|*
name|host
decl_stmt|,
modifier|*
name|port
decl_stmt|,
name|c
decl_stmt|;
name|size_t
name|host_len
decl_stmt|,
name|port_len
decl_stmt|,
name|size
decl_stmt|;
name|uint32_t
name|hash
decl_stmt|,
name|base_hash
decl_stmt|;
name|ngx_str_t
modifier|*
name|server
decl_stmt|;
name|ngx_uint_t
name|npoints
decl_stmt|,
name|i
decl_stmt|,
name|j
decl_stmt|;
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|;
name|ngx_stream_upstream_rr_peers_t
modifier|*
name|peers
decl_stmt|;
name|ngx_stream_upstream_chash_points_t
modifier|*
name|points
decl_stmt|;
name|ngx_stream_upstream_hash_srv_conf_t
modifier|*
name|hcf
decl_stmt|;
DECL|union|__anon2bb0515d050a
union|union
block|{
DECL|member|value
name|uint32_t
name|value
decl_stmt|;
DECL|member|byte
name|u_char
name|byte
index|[
literal|4
index|]
decl_stmt|;
block|}
name|prev_hash
union|;
if|if
condition|(
name|ngx_stream_upstream_init_round_robin
argument_list|(
name|cf
argument_list|,
name|us
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|us
operator|->
name|peer
operator|.
name|init
operator|=
name|ngx_stream_upstream_init_chash_peer
expr_stmt|;
name|peers
operator|=
name|us
operator|->
name|peer
operator|.
name|data
expr_stmt|;
name|npoints
operator|=
name|peers
operator|->
name|total_weight
operator|*
literal|160
expr_stmt|;
name|size
operator|=
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_chash_points_t
argument_list|)
operator|+
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_chash_point_t
argument_list|)
operator|*
operator|(
name|npoints
operator|-
literal|1
operator|)
expr_stmt|;
name|points
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|points
operator|==
name|NULL
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|points
operator|->
name|number
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|peer
operator|=
name|peers
operator|->
name|peer
init|;
name|peer
condition|;
name|peer
operator|=
name|peer
operator|->
name|next
control|)
block|{
name|server
operator|=
operator|&
name|peer
operator|->
name|server
expr_stmt|;
comment|/*          * Hash expression is compatible with Cache::Memcached::Fast:          * crc32(HOST \0 PORT PREV_HASH).          */
if|if
condition|(
name|server
operator|->
name|len
operator|>=
literal|5
operator|&&
name|ngx_strncasecmp
argument_list|(
name|server
operator|->
name|data
argument_list|,
operator|(
name|u_char
operator|*
operator|)
literal|"unix:"
argument_list|,
literal|5
argument_list|)
operator|==
literal|0
condition|)
block|{
name|host
operator|=
name|server
operator|->
name|data
operator|+
literal|5
expr_stmt|;
name|host_len
operator|=
name|server
operator|->
name|len
operator|-
literal|5
expr_stmt|;
name|port
operator|=
name|NULL
expr_stmt|;
name|port_len
operator|=
literal|0
expr_stmt|;
goto|goto
name|done
goto|;
block|}
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|server
operator|->
name|len
condition|;
name|j
operator|++
control|)
block|{
name|c
operator|=
name|server
operator|->
name|data
index|[
name|server
operator|->
name|len
operator|-
name|j
operator|-
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|c
operator|==
literal|':'
condition|)
block|{
name|host
operator|=
name|server
operator|->
name|data
expr_stmt|;
name|host_len
operator|=
name|server
operator|->
name|len
operator|-
name|j
operator|-
literal|1
expr_stmt|;
name|port
operator|=
name|server
operator|->
name|data
operator|+
name|server
operator|->
name|len
operator|-
name|j
expr_stmt|;
name|port_len
operator|=
name|j
expr_stmt|;
goto|goto
name|done
goto|;
block|}
if|if
condition|(
name|c
argument_list|<
literal|'0'
operator|||
name|c
argument_list|>
literal|'9'
condition|)
block|{
break|break;
block|}
block|}
name|host
operator|=
name|server
operator|->
name|data
expr_stmt|;
name|host_len
operator|=
name|server
operator|->
name|len
expr_stmt|;
name|port
operator|=
name|NULL
expr_stmt|;
name|port_len
operator|=
literal|0
expr_stmt|;
name|done
label|:
name|ngx_crc32_init
argument_list|(
name|base_hash
argument_list|)
expr_stmt|;
name|ngx_crc32_update
argument_list|(
operator|&
name|base_hash
argument_list|,
name|host
argument_list|,
name|host_len
argument_list|)
expr_stmt|;
name|ngx_crc32_update
argument_list|(
operator|&
name|base_hash
argument_list|,
operator|(
name|u_char
operator|*
operator|)
literal|""
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|ngx_crc32_update
argument_list|(
operator|&
name|base_hash
argument_list|,
name|port
argument_list|,
name|port_len
argument_list|)
expr_stmt|;
name|prev_hash
operator|.
name|value
operator|=
literal|0
expr_stmt|;
name|npoints
operator|=
name|peer
operator|->
name|weight
operator|*
literal|160
expr_stmt|;
for|for
control|(
name|j
operator|=
literal|0
init|;
name|j
operator|<
name|npoints
condition|;
name|j
operator|++
control|)
block|{
name|hash
operator|=
name|base_hash
expr_stmt|;
name|ngx_crc32_update
argument_list|(
operator|&
name|hash
argument_list|,
name|prev_hash
operator|.
name|byte
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|ngx_crc32_final
argument_list|(
name|hash
argument_list|)
expr_stmt|;
name|points
operator|->
name|point
index|[
name|points
operator|->
name|number
index|]
operator|.
name|hash
operator|=
name|hash
expr_stmt|;
name|points
operator|->
name|point
index|[
name|points
operator|->
name|number
index|]
operator|.
name|server
operator|=
name|server
expr_stmt|;
name|points
operator|->
name|number
operator|++
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_LITTLE_ENDIAN
operator|)
name|prev_hash
operator|.
name|value
operator|=
name|hash
expr_stmt|;
else|#
directive|else
name|prev_hash
operator|.
name|byte
index|[
literal|0
index|]
operator|=
operator|(
name|u_char
operator|)
operator|(
name|hash
operator|&
literal|0xff
operator|)
expr_stmt|;
name|prev_hash
operator|.
name|byte
index|[
literal|1
index|]
operator|=
operator|(
name|u_char
operator|)
operator|(
operator|(
name|hash
operator|>>
literal|8
operator|)
operator|&
literal|0xff
operator|)
expr_stmt|;
name|prev_hash
operator|.
name|byte
index|[
literal|2
index|]
operator|=
operator|(
name|u_char
operator|)
operator|(
operator|(
name|hash
operator|>>
literal|16
operator|)
operator|&
literal|0xff
operator|)
expr_stmt|;
name|prev_hash
operator|.
name|byte
index|[
literal|3
index|]
operator|=
operator|(
name|u_char
operator|)
operator|(
operator|(
name|hash
operator|>>
literal|24
operator|)
operator|&
literal|0xff
operator|)
expr_stmt|;
endif|#
directive|endif
block|}
block|}
name|ngx_qsort
argument_list|(
name|points
operator|->
name|point
argument_list|,
name|points
operator|->
name|number
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_chash_point_t
argument_list|)
argument_list|,
name|ngx_stream_upstream_chash_cmp_points
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
operator|,
name|j
operator|=
literal|1
init|;
name|j
operator|<
name|points
operator|->
name|number
condition|;
name|j
operator|++
control|)
block|{
if|if
condition|(
name|points
operator|->
name|point
index|[
name|i
index|]
operator|.
name|hash
operator|!=
name|points
operator|->
name|point
index|[
name|j
index|]
operator|.
name|hash
condition|)
block|{
name|points
operator|->
name|point
index|[
operator|++
name|i
index|]
operator|=
name|points
operator|->
name|point
index|[
name|j
index|]
expr_stmt|;
block|}
block|}
name|points
operator|->
name|number
operator|=
name|i
operator|+
literal|1
expr_stmt|;
name|hcf
operator|=
name|ngx_stream_conf_upstream_srv_conf
argument_list|(
name|us
argument_list|,
name|ngx_stream_upstream_hash_module
argument_list|)
expr_stmt|;
name|hcf
operator|->
name|points
operator|=
name|points
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|int
name|ngx_libc_cdecl
DECL|function|ngx_stream_upstream_chash_cmp_points (const void * one,const void * two)
name|ngx_stream_upstream_chash_cmp_points
parameter_list|(
specifier|const
name|void
modifier|*
name|one
parameter_list|,
specifier|const
name|void
modifier|*
name|two
parameter_list|)
block|{
name|ngx_stream_upstream_chash_point_t
modifier|*
name|first
init|=
operator|(
name|ngx_stream_upstream_chash_point_t
operator|*
operator|)
name|one
decl_stmt|;
name|ngx_stream_upstream_chash_point_t
modifier|*
name|second
init|=
operator|(
name|ngx_stream_upstream_chash_point_t
operator|*
operator|)
name|two
decl_stmt|;
if|if
condition|(
name|first
operator|->
name|hash
operator|<
name|second
operator|->
name|hash
condition|)
block|{
return|return
operator|-
literal|1
return|;
block|}
if|else if
condition|(
name|first
operator|->
name|hash
operator|>
name|second
operator|->
name|hash
condition|)
block|{
return|return
literal|1
return|;
block|}
else|else
block|{
return|return
literal|0
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|ngx_uint_t
DECL|function|ngx_stream_upstream_find_chash_point (ngx_stream_upstream_chash_points_t * points,uint32_t hash)
name|ngx_stream_upstream_find_chash_point
parameter_list|(
name|ngx_stream_upstream_chash_points_t
modifier|*
name|points
parameter_list|,
name|uint32_t
name|hash
parameter_list|)
block|{
name|ngx_uint_t
name|i
decl_stmt|,
name|j
decl_stmt|,
name|k
decl_stmt|;
name|ngx_stream_upstream_chash_point_t
modifier|*
name|point
decl_stmt|;
comment|/* find first point>= hash */
name|point
operator|=
operator|&
name|points
operator|->
name|point
index|[
literal|0
index|]
expr_stmt|;
name|i
operator|=
literal|0
expr_stmt|;
name|j
operator|=
name|points
operator|->
name|number
expr_stmt|;
while|while
condition|(
name|i
operator|<
name|j
condition|)
block|{
name|k
operator|=
operator|(
name|i
operator|+
name|j
operator|)
operator|/
literal|2
expr_stmt|;
if|if
condition|(
name|hash
operator|>
name|point
index|[
name|k
index|]
operator|.
name|hash
condition|)
block|{
name|i
operator|=
name|k
operator|+
literal|1
expr_stmt|;
block|}
if|else if
condition|(
name|hash
operator|<
name|point
index|[
name|k
index|]
operator|.
name|hash
condition|)
block|{
name|j
operator|=
name|k
expr_stmt|;
block|}
else|else
block|{
return|return
name|k
return|;
block|}
block|}
return|return
name|i
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_upstream_init_chash_peer (ngx_stream_session_t * s,ngx_stream_upstream_srv_conf_t * us)
name|ngx_stream_upstream_init_chash_peer
parameter_list|(
name|ngx_stream_session_t
modifier|*
name|s
parameter_list|,
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|us
parameter_list|)
block|{
name|uint32_t
name|hash
decl_stmt|;
name|ngx_stream_upstream_hash_srv_conf_t
modifier|*
name|hcf
decl_stmt|;
name|ngx_stream_upstream_hash_peer_data_t
modifier|*
name|hp
decl_stmt|;
if|if
condition|(
name|ngx_stream_upstream_init_hash_peer
argument_list|(
name|s
argument_list|,
name|us
argument_list|)
operator|!=
name|NGX_OK
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|s
operator|->
name|upstream
operator|->
name|peer
operator|.
name|get
operator|=
name|ngx_stream_upstream_get_chash_peer
expr_stmt|;
name|hp
operator|=
name|s
operator|->
name|upstream
operator|->
name|peer
operator|.
name|data
expr_stmt|;
name|hcf
operator|=
name|ngx_stream_conf_upstream_srv_conf
argument_list|(
name|us
argument_list|,
name|ngx_stream_upstream_hash_module
argument_list|)
expr_stmt|;
name|hash
operator|=
name|ngx_crc32_long
argument_list|(
name|hp
operator|->
name|key
operator|.
name|data
argument_list|,
name|hp
operator|->
name|key
operator|.
name|len
argument_list|)
expr_stmt|;
name|ngx_stream_upstream_rr_peers_rlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
name|hp
operator|->
name|hash
operator|=
name|ngx_stream_upstream_find_chash_point
argument_list|(
name|hcf
operator|->
name|points
argument_list|,
name|hash
argument_list|)
expr_stmt|;
name|ngx_stream_upstream_rr_peers_unlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_stream_upstream_get_chash_peer (ngx_peer_connection_t * pc,void * data)
name|ngx_stream_upstream_get_chash_peer
parameter_list|(
name|ngx_peer_connection_t
modifier|*
name|pc
parameter_list|,
name|void
modifier|*
name|data
parameter_list|)
block|{
name|ngx_stream_upstream_hash_peer_data_t
modifier|*
name|hp
init|=
name|data
decl_stmt|;
name|time_t
name|now
decl_stmt|;
name|intptr_t
name|m
decl_stmt|;
name|ngx_str_t
modifier|*
name|server
decl_stmt|;
name|ngx_int_t
name|total
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|,
name|n
decl_stmt|,
name|best_i
decl_stmt|;
name|ngx_stream_upstream_rr_peer_t
modifier|*
name|peer
decl_stmt|,
modifier|*
name|best
decl_stmt|;
name|ngx_stream_upstream_chash_point_t
modifier|*
name|point
decl_stmt|;
name|ngx_stream_upstream_chash_points_t
modifier|*
name|points
decl_stmt|;
name|ngx_stream_upstream_hash_srv_conf_t
modifier|*
name|hcf
decl_stmt|;
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_STREAM
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"get consistent hash peer, try: %ui"
argument_list|,
name|pc
operator|->
name|tries
argument_list|)
expr_stmt|;
name|ngx_stream_upstream_rr_peers_wlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
name|pc
operator|->
name|connection
operator|=
name|NULL
expr_stmt|;
name|now
operator|=
name|ngx_time
argument_list|()
expr_stmt|;
name|hcf
operator|=
name|hp
operator|->
name|conf
expr_stmt|;
name|points
operator|=
name|hcf
operator|->
name|points
expr_stmt|;
name|point
operator|=
operator|&
name|points
operator|->
name|point
index|[
literal|0
index|]
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|server
operator|=
name|point
index|[
name|hp
operator|->
name|hash
operator|%
name|points
operator|->
name|number
index|]
operator|.
name|server
expr_stmt|;
name|ngx_log_debug2
argument_list|(
name|NGX_LOG_DEBUG_STREAM
argument_list|,
name|pc
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"consistent hash peer:%uD, server:\"%V\""
argument_list|,
name|hp
operator|->
name|hash
argument_list|,
name|server
argument_list|)
expr_stmt|;
name|best
operator|=
name|NULL
expr_stmt|;
name|best_i
operator|=
literal|0
expr_stmt|;
name|total
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|peer
operator|=
name|hp
operator|->
name|rrp
operator|.
name|peers
operator|->
name|peer
operator|,
name|i
operator|=
literal|0
init|;
name|peer
condition|;
name|peer
operator|=
name|peer
operator|->
name|next
operator|,
name|i
operator|++
control|)
block|{
name|n
operator|=
name|i
operator|/
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
name|m
operator|=
operator|(
name|uintptr_t
operator|)
literal|1
operator|<<
name|i
operator|%
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
if|if
condition|(
name|hp
operator|->
name|rrp
operator|.
name|tried
index|[
name|n
index|]
operator|&
name|m
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|peer
operator|->
name|down
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|peer
operator|->
name|server
operator|.
name|len
operator|!=
name|server
operator|->
name|len
operator|||
name|ngx_strncmp
argument_list|(
name|peer
operator|->
name|server
operator|.
name|data
argument_list|,
name|server
operator|->
name|data
argument_list|,
name|server
operator|->
name|len
argument_list|)
operator|!=
literal|0
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|peer
operator|->
name|max_fails
operator|&&
name|peer
operator|->
name|fails
operator|>=
name|peer
operator|->
name|max_fails
operator|&&
name|now
operator|-
name|peer
operator|->
name|checked
operator|<=
name|peer
operator|->
name|fail_timeout
condition|)
block|{
continue|continue;
block|}
name|peer
operator|->
name|current_weight
operator|+=
name|peer
operator|->
name|effective_weight
expr_stmt|;
name|total
operator|+=
name|peer
operator|->
name|effective_weight
expr_stmt|;
if|if
condition|(
name|peer
operator|->
name|effective_weight
operator|<
name|peer
operator|->
name|weight
condition|)
block|{
name|peer
operator|->
name|effective_weight
operator|++
expr_stmt|;
block|}
if|if
condition|(
name|best
operator|==
name|NULL
operator|||
name|peer
operator|->
name|current_weight
operator|>
name|best
operator|->
name|current_weight
condition|)
block|{
name|best
operator|=
name|peer
expr_stmt|;
name|best_i
operator|=
name|i
expr_stmt|;
block|}
block|}
if|if
condition|(
name|best
condition|)
block|{
name|best
operator|->
name|current_weight
operator|-=
name|total
expr_stmt|;
break|break;
block|}
name|hp
operator|->
name|hash
operator|++
expr_stmt|;
name|hp
operator|->
name|tries
operator|++
expr_stmt|;
if|if
condition|(
name|hp
operator|->
name|tries
operator|>=
name|points
operator|->
name|number
condition|)
block|{
name|ngx_stream_upstream_rr_peers_unlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
return|return
name|NGX_BUSY
return|;
block|}
block|}
name|hp
operator|->
name|rrp
operator|.
name|current
operator|=
name|best
expr_stmt|;
name|pc
operator|->
name|sockaddr
operator|=
name|best
operator|->
name|sockaddr
expr_stmt|;
name|pc
operator|->
name|socklen
operator|=
name|best
operator|->
name|socklen
expr_stmt|;
name|pc
operator|->
name|name
operator|=
operator|&
name|best
operator|->
name|name
expr_stmt|;
name|best
operator|->
name|conns
operator|++
expr_stmt|;
if|if
condition|(
name|now
operator|-
name|best
operator|->
name|checked
operator|>
name|best
operator|->
name|fail_timeout
condition|)
block|{
name|best
operator|->
name|checked
operator|=
name|now
expr_stmt|;
block|}
name|ngx_stream_upstream_rr_peers_unlock
argument_list|(
name|hp
operator|->
name|rrp
operator|.
name|peers
argument_list|)
expr_stmt|;
name|n
operator|=
name|best_i
operator|/
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
name|m
operator|=
operator|(
name|uintptr_t
operator|)
literal|1
operator|<<
name|best_i
operator|%
operator|(
literal|8
operator|*
sizeof|sizeof
argument_list|(
name|uintptr_t
argument_list|)
operator|)
expr_stmt|;
name|hp
operator|->
name|rrp
operator|.
name|tried
index|[
name|n
index|]
operator||=
name|m
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|ngx_stream_upstream_hash_create_conf (ngx_conf_t * cf)
name|ngx_stream_upstream_hash_create_conf
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
block|{
name|ngx_stream_upstream_hash_srv_conf_t
modifier|*
name|conf
decl_stmt|;
name|conf
operator|=
name|ngx_palloc
argument_list|(
name|cf
operator|->
name|pool
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_stream_upstream_hash_srv_conf_t
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|conf
operator|==
name|NULL
condition|)
block|{
return|return
name|NULL
return|;
block|}
name|conf
operator|->
name|points
operator|=
name|NULL
expr_stmt|;
return|return
name|conf
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_stream_upstream_hash (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_stream_upstream_hash
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
name|ngx_str_t
modifier|*
name|value
decl_stmt|;
name|ngx_stream_upstream_srv_conf_t
modifier|*
name|uscf
decl_stmt|;
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
name|ngx_strcmp
argument_list|(
name|value
index|[
literal|1
index|]
operator|.
name|data
argument_list|,
literal|"$remote_addr"
argument_list|)
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
literal|"unsupported hash key \"%V\", use $remote_addr"
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
name|uscf
operator|=
name|ngx_stream_conf_get_module_srv_conf
argument_list|(
name|cf
argument_list|,
name|ngx_stream_upstream_module
argument_list|)
expr_stmt|;
if|if
condition|(
name|uscf
operator|->
name|peer
operator|.
name|init_upstream
condition|)
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_WARN
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"load balancing method redefined"
argument_list|)
expr_stmt|;
block|}
name|uscf
operator|->
name|flags
operator|=
name|NGX_STREAM_UPSTREAM_CREATE
operator||
name|NGX_STREAM_UPSTREAM_WEIGHT
operator||
name|NGX_STREAM_UPSTREAM_MAX_FAILS
operator||
name|NGX_STREAM_UPSTREAM_FAIL_TIMEOUT
operator||
name|NGX_STREAM_UPSTREAM_DOWN
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
name|uscf
operator|->
name|peer
operator|.
name|init_upstream
operator|=
name|ngx_stream_upstream_init_hash
expr_stmt|;
block|}
if|else if
condition|(
name|ngx_strcmp
argument_list|(
name|value
index|[
literal|2
index|]
operator|.
name|data
argument_list|,
literal|"consistent"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|uscf
operator|->
name|peer
operator|.
name|init_upstream
operator|=
name|ngx_stream_upstream_init_chash
expr_stmt|;
block|}
else|else
block|{
name|ngx_conf_log_error
argument_list|(
name|NGX_LOG_EMERG
argument_list|,
name|cf
argument_list|,
literal|0
argument_list|,
literal|"invalid parameter \"%V\""
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
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit
