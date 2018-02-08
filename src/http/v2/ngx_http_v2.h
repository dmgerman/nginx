begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  * Copyright (C) Valentin V. Bartenev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_V2_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_V2_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_V2_H_INCLUDED_
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
file|<ngx_http.h>
end_include

begin_define
DECL|macro|NGX_HTTP_V2_ALPN_ADVERTISE
define|#
directive|define
name|NGX_HTTP_V2_ALPN_ADVERTISE
value|"\x02h2"
end_define

begin_define
DECL|macro|NGX_HTTP_V2_NPN_ADVERTISE
define|#
directive|define
name|NGX_HTTP_V2_NPN_ADVERTISE
value|NGX_HTTP_V2_ALPN_ADVERTISE
end_define

begin_define
DECL|macro|NGX_HTTP_V2_STATE_BUFFER_SIZE
define|#
directive|define
name|NGX_HTTP_V2_STATE_BUFFER_SIZE
value|16
end_define

begin_define
DECL|macro|NGX_HTTP_V2_MAX_FRAME_SIZE
define|#
directive|define
name|NGX_HTTP_V2_MAX_FRAME_SIZE
value|((1<< 24) - 1)
end_define

begin_define
DECL|macro|NGX_HTTP_V2_INT_OCTETS
define|#
directive|define
name|NGX_HTTP_V2_INT_OCTETS
value|4
end_define

begin_define
DECL|macro|NGX_HTTP_V2_MAX_FIELD
define|#
directive|define
name|NGX_HTTP_V2_MAX_FIELD
define|\
value|(127 + (1<< (NGX_HTTP_V2_INT_OCTETS - 1) * 7) - 1)
end_define

begin_define
DECL|macro|NGX_HTTP_V2_STREAM_ID_SIZE
define|#
directive|define
name|NGX_HTTP_V2_STREAM_ID_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_HTTP_V2_FRAME_HEADER_SIZE
define|#
directive|define
name|NGX_HTTP_V2_FRAME_HEADER_SIZE
value|9
end_define

begin_comment
comment|/* frame types */
end_comment

begin_define
DECL|macro|NGX_HTTP_V2_DATA_FRAME
define|#
directive|define
name|NGX_HTTP_V2_DATA_FRAME
value|0x0
end_define

begin_define
DECL|macro|NGX_HTTP_V2_HEADERS_FRAME
define|#
directive|define
name|NGX_HTTP_V2_HEADERS_FRAME
value|0x1
end_define

begin_define
DECL|macro|NGX_HTTP_V2_PRIORITY_FRAME
define|#
directive|define
name|NGX_HTTP_V2_PRIORITY_FRAME
value|0x2
end_define

begin_define
DECL|macro|NGX_HTTP_V2_RST_STREAM_FRAME
define|#
directive|define
name|NGX_HTTP_V2_RST_STREAM_FRAME
value|0x3
end_define

begin_define
DECL|macro|NGX_HTTP_V2_SETTINGS_FRAME
define|#
directive|define
name|NGX_HTTP_V2_SETTINGS_FRAME
value|0x4
end_define

begin_define
DECL|macro|NGX_HTTP_V2_PUSH_PROMISE_FRAME
define|#
directive|define
name|NGX_HTTP_V2_PUSH_PROMISE_FRAME
value|0x5
end_define

begin_define
DECL|macro|NGX_HTTP_V2_PING_FRAME
define|#
directive|define
name|NGX_HTTP_V2_PING_FRAME
value|0x6
end_define

begin_define
DECL|macro|NGX_HTTP_V2_GOAWAY_FRAME
define|#
directive|define
name|NGX_HTTP_V2_GOAWAY_FRAME
value|0x7
end_define

begin_define
DECL|macro|NGX_HTTP_V2_WINDOW_UPDATE_FRAME
define|#
directive|define
name|NGX_HTTP_V2_WINDOW_UPDATE_FRAME
value|0x8
end_define

begin_define
DECL|macro|NGX_HTTP_V2_CONTINUATION_FRAME
define|#
directive|define
name|NGX_HTTP_V2_CONTINUATION_FRAME
value|0x9
end_define

begin_comment
comment|/* frame flags */
end_comment

begin_define
DECL|macro|NGX_HTTP_V2_NO_FLAG
define|#
directive|define
name|NGX_HTTP_V2_NO_FLAG
value|0x00
end_define

begin_define
DECL|macro|NGX_HTTP_V2_ACK_FLAG
define|#
directive|define
name|NGX_HTTP_V2_ACK_FLAG
value|0x01
end_define

begin_define
DECL|macro|NGX_HTTP_V2_END_STREAM_FLAG
define|#
directive|define
name|NGX_HTTP_V2_END_STREAM_FLAG
value|0x01
end_define

begin_define
DECL|macro|NGX_HTTP_V2_END_HEADERS_FLAG
define|#
directive|define
name|NGX_HTTP_V2_END_HEADERS_FLAG
value|0x04
end_define

begin_define
DECL|macro|NGX_HTTP_V2_PADDED_FLAG
define|#
directive|define
name|NGX_HTTP_V2_PADDED_FLAG
value|0x08
end_define

begin_define
DECL|macro|NGX_HTTP_V2_PRIORITY_FLAG
define|#
directive|define
name|NGX_HTTP_V2_PRIORITY_FLAG
value|0x20
end_define

begin_define
DECL|macro|NGX_HTTP_V2_MAX_WINDOW
define|#
directive|define
name|NGX_HTTP_V2_MAX_WINDOW
value|((1U<< 31) - 1)
end_define

begin_define
DECL|macro|NGX_HTTP_V2_DEFAULT_WINDOW
define|#
directive|define
name|NGX_HTTP_V2_DEFAULT_WINDOW
value|65535
end_define

begin_define
DECL|macro|NGX_HTTP_V2_DEFAULT_WEIGHT
define|#
directive|define
name|NGX_HTTP_V2_DEFAULT_WEIGHT
value|16
end_define

begin_typedef
DECL|typedef|ngx_http_v2_connection_t
typedef|typedef
name|struct
name|ngx_http_v2_connection_s
name|ngx_http_v2_connection_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_v2_node_t
typedef|typedef
name|struct
name|ngx_http_v2_node_s
name|ngx_http_v2_node_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_v2_out_frame_t
typedef|typedef
name|struct
name|ngx_http_v2_out_frame_s
name|ngx_http_v2_out_frame_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_v2_handler_pt
typedef|typedef
name|u_char
modifier|*
function_decl|(
modifier|*
name|ngx_http_v2_handler_pt
function_decl|)
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|u_char
modifier|*
name|pos
parameter_list|,
name|u_char
modifier|*
name|end
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|__anon2ab03ac30108
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
name|name
decl_stmt|;
DECL|member|value
name|ngx_str_t
name|value
decl_stmt|;
DECL|typedef|ngx_http_v2_header_t
block|}
name|ngx_http_v2_header_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2ab03ac30208
typedef|typedef
struct|struct
block|{
DECL|member|sid
name|ngx_uint_t
name|sid
decl_stmt|;
DECL|member|length
name|size_t
name|length
decl_stmt|;
DECL|member|padding
name|size_t
name|padding
decl_stmt|;
DECL|member|flags
name|unsigned
name|flags
range|:
literal|8
decl_stmt|;
DECL|member|incomplete
name|unsigned
name|incomplete
range|:
literal|1
decl_stmt|;
DECL|member|keep_pool
name|unsigned
name|keep_pool
range|:
literal|1
decl_stmt|;
comment|/* HPACK */
DECL|member|parse_name
name|unsigned
name|parse_name
range|:
literal|1
decl_stmt|;
DECL|member|parse_value
name|unsigned
name|parse_value
range|:
literal|1
decl_stmt|;
DECL|member|index
name|unsigned
name|index
range|:
literal|1
decl_stmt|;
DECL|member|header
name|ngx_http_v2_header_t
name|header
decl_stmt|;
DECL|member|header_limit
name|size_t
name|header_limit
decl_stmt|;
DECL|member|field_state
name|u_char
name|field_state
decl_stmt|;
DECL|member|field_start
name|u_char
modifier|*
name|field_start
decl_stmt|;
DECL|member|field_end
name|u_char
modifier|*
name|field_end
decl_stmt|;
DECL|member|field_rest
name|size_t
name|field_rest
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|stream
name|ngx_http_v2_stream_t
modifier|*
name|stream
decl_stmt|;
DECL|member|buffer
name|u_char
name|buffer
index|[
name|NGX_HTTP_V2_STATE_BUFFER_SIZE
index|]
decl_stmt|;
DECL|member|buffer_used
name|size_t
name|buffer_used
decl_stmt|;
DECL|member|handler
name|ngx_http_v2_handler_pt
name|handler
decl_stmt|;
DECL|typedef|ngx_http_v2_state_t
block|}
name|ngx_http_v2_state_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2ab03ac30308
typedef|typedef
struct|struct
block|{
DECL|member|entries
name|ngx_http_v2_header_t
modifier|*
modifier|*
name|entries
decl_stmt|;
DECL|member|added
name|ngx_uint_t
name|added
decl_stmt|;
DECL|member|deleted
name|ngx_uint_t
name|deleted
decl_stmt|;
DECL|member|reused
name|ngx_uint_t
name|reused
decl_stmt|;
DECL|member|allocated
name|ngx_uint_t
name|allocated
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|free
name|size_t
name|free
decl_stmt|;
DECL|member|storage
name|u_char
modifier|*
name|storage
decl_stmt|;
DECL|member|pos
name|u_char
modifier|*
name|pos
decl_stmt|;
DECL|typedef|ngx_http_v2_hpack_t
block|}
name|ngx_http_v2_hpack_t
typedef|;
end_typedef

begin_struct
DECL|struct|ngx_http_v2_connection_s
struct|struct
name|ngx_http_v2_connection_s
block|{
DECL|member|connection
name|ngx_connection_t
modifier|*
name|connection
decl_stmt|;
DECL|member|http_connection
name|ngx_http_connection_t
modifier|*
name|http_connection
decl_stmt|;
DECL|member|processing
name|ngx_uint_t
name|processing
decl_stmt|;
DECL|member|pushing
name|ngx_uint_t
name|pushing
decl_stmt|;
DECL|member|concurrent_pushes
name|ngx_uint_t
name|concurrent_pushes
decl_stmt|;
DECL|member|send_window
name|size_t
name|send_window
decl_stmt|;
DECL|member|recv_window
name|size_t
name|recv_window
decl_stmt|;
DECL|member|init_window
name|size_t
name|init_window
decl_stmt|;
DECL|member|frame_size
name|size_t
name|frame_size
decl_stmt|;
DECL|member|waiting
name|ngx_queue_t
name|waiting
decl_stmt|;
DECL|member|state
name|ngx_http_v2_state_t
name|state
decl_stmt|;
DECL|member|hpack
name|ngx_http_v2_hpack_t
name|hpack
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|free_frames
name|ngx_http_v2_out_frame_t
modifier|*
name|free_frames
decl_stmt|;
DECL|member|free_fake_connections
name|ngx_connection_t
modifier|*
name|free_fake_connections
decl_stmt|;
DECL|member|streams_index
name|ngx_http_v2_node_t
modifier|*
modifier|*
name|streams_index
decl_stmt|;
DECL|member|last_out
name|ngx_http_v2_out_frame_t
modifier|*
name|last_out
decl_stmt|;
DECL|member|dependencies
name|ngx_queue_t
name|dependencies
decl_stmt|;
DECL|member|closed
name|ngx_queue_t
name|closed
decl_stmt|;
DECL|member|last_sid
name|ngx_uint_t
name|last_sid
decl_stmt|;
DECL|member|last_push
name|ngx_uint_t
name|last_push
decl_stmt|;
DECL|member|closed_nodes
name|unsigned
name|closed_nodes
range|:
literal|8
decl_stmt|;
DECL|member|settings_ack
name|unsigned
name|settings_ack
range|:
literal|1
decl_stmt|;
DECL|member|table_update
name|unsigned
name|table_update
range|:
literal|1
decl_stmt|;
DECL|member|blocked
name|unsigned
name|blocked
range|:
literal|1
decl_stmt|;
DECL|member|goaway
name|unsigned
name|goaway
range|:
literal|1
decl_stmt|;
DECL|member|push_disabled
name|unsigned
name|push_disabled
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|ngx_http_v2_node_s
struct|struct
name|ngx_http_v2_node_s
block|{
DECL|member|id
name|ngx_uint_t
name|id
decl_stmt|;
DECL|member|index
name|ngx_http_v2_node_t
modifier|*
name|index
decl_stmt|;
DECL|member|parent
name|ngx_http_v2_node_t
modifier|*
name|parent
decl_stmt|;
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
DECL|member|children
name|ngx_queue_t
name|children
decl_stmt|;
DECL|member|reuse
name|ngx_queue_t
name|reuse
decl_stmt|;
DECL|member|rank
name|ngx_uint_t
name|rank
decl_stmt|;
DECL|member|weight
name|ngx_uint_t
name|weight
decl_stmt|;
DECL|member|rel_weight
name|double
name|rel_weight
decl_stmt|;
DECL|member|stream
name|ngx_http_v2_stream_t
modifier|*
name|stream
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|ngx_http_v2_stream_s
struct|struct
name|ngx_http_v2_stream_s
block|{
DECL|member|request
name|ngx_http_request_t
modifier|*
name|request
decl_stmt|;
DECL|member|connection
name|ngx_http_v2_connection_t
modifier|*
name|connection
decl_stmt|;
DECL|member|node
name|ngx_http_v2_node_t
modifier|*
name|node
decl_stmt|;
DECL|member|queued
name|ngx_uint_t
name|queued
decl_stmt|;
comment|/*      * A change to SETTINGS_INITIAL_WINDOW_SIZE could cause the      * send_window to become negative, hence it's signed.      */
DECL|member|send_window
name|ssize_t
name|send_window
decl_stmt|;
DECL|member|recv_window
name|size_t
name|recv_window
decl_stmt|;
DECL|member|preread
name|ngx_buf_t
modifier|*
name|preread
decl_stmt|;
DECL|member|free_frames
name|ngx_http_v2_out_frame_t
modifier|*
name|free_frames
decl_stmt|;
DECL|member|free_frame_headers
name|ngx_chain_t
modifier|*
name|free_frame_headers
decl_stmt|;
DECL|member|free_bufs
name|ngx_chain_t
modifier|*
name|free_bufs
decl_stmt|;
DECL|member|queue
name|ngx_queue_t
name|queue
decl_stmt|;
DECL|member|cookies
name|ngx_array_t
modifier|*
name|cookies
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|waiting
name|unsigned
name|waiting
range|:
literal|1
decl_stmt|;
DECL|member|blocked
name|unsigned
name|blocked
range|:
literal|1
decl_stmt|;
DECL|member|exhausted
name|unsigned
name|exhausted
range|:
literal|1
decl_stmt|;
DECL|member|in_closed
name|unsigned
name|in_closed
range|:
literal|1
decl_stmt|;
DECL|member|out_closed
name|unsigned
name|out_closed
range|:
literal|1
decl_stmt|;
DECL|member|rst_sent
name|unsigned
name|rst_sent
range|:
literal|1
decl_stmt|;
DECL|member|no_flow_control
name|unsigned
name|no_flow_control
range|:
literal|1
decl_stmt|;
DECL|member|skip_data
name|unsigned
name|skip_data
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|ngx_http_v2_out_frame_s
struct|struct
name|ngx_http_v2_out_frame_s
block|{
DECL|member|next
name|ngx_http_v2_out_frame_t
modifier|*
name|next
decl_stmt|;
DECL|member|first
name|ngx_chain_t
modifier|*
name|first
decl_stmt|;
DECL|member|last
name|ngx_chain_t
modifier|*
name|last
decl_stmt|;
DECL|member|handler
name|ngx_int_t
function_decl|(
modifier|*
name|handler
function_decl|)
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|ngx_http_v2_out_frame_t
modifier|*
name|frame
parameter_list|)
function_decl|;
DECL|member|stream
name|ngx_http_v2_stream_t
modifier|*
name|stream
decl_stmt|;
DECL|member|length
name|size_t
name|length
decl_stmt|;
DECL|member|blocked
name|unsigned
name|blocked
range|:
literal|1
decl_stmt|;
DECL|member|fin
name|unsigned
name|fin
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_http_v2_queue_frame (ngx_http_v2_connection_t * h2c,ngx_http_v2_out_frame_t * frame)
name|ngx_http_v2_queue_frame
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|ngx_http_v2_out_frame_t
modifier|*
name|frame
parameter_list|)
block|{
name|ngx_http_v2_out_frame_t
modifier|*
modifier|*
name|out
decl_stmt|;
for|for
control|(
name|out
operator|=
operator|&
name|h2c
operator|->
name|last_out
init|;
operator|*
name|out
condition|;
name|out
operator|=
operator|&
operator|(
operator|*
name|out
operator|)
operator|->
name|next
control|)
block|{
if|if
condition|(
operator|(
operator|*
name|out
operator|)
operator|->
name|blocked
operator|||
operator|(
operator|*
name|out
operator|)
operator|->
name|stream
operator|==
name|NULL
condition|)
block|{
break|break;
block|}
if|if
condition|(
operator|(
operator|*
name|out
operator|)
operator|->
name|stream
operator|->
name|node
operator|->
name|rank
operator|<
name|frame
operator|->
name|stream
operator|->
name|node
operator|->
name|rank
operator|||
operator|(
operator|(
operator|*
name|out
operator|)
operator|->
name|stream
operator|->
name|node
operator|->
name|rank
operator|==
name|frame
operator|->
name|stream
operator|->
name|node
operator|->
name|rank
operator|&&
operator|(
operator|*
name|out
operator|)
operator|->
name|stream
operator|->
name|node
operator|->
name|rel_weight
operator|>=
name|frame
operator|->
name|stream
operator|->
name|node
operator|->
name|rel_weight
operator|)
condition|)
block|{
break|break;
block|}
block|}
name|frame
operator|->
name|next
operator|=
operator|*
name|out
expr_stmt|;
operator|*
name|out
operator|=
name|frame
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_http_v2_queue_blocked_frame (ngx_http_v2_connection_t * h2c,ngx_http_v2_out_frame_t * frame)
name|ngx_http_v2_queue_blocked_frame
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|ngx_http_v2_out_frame_t
modifier|*
name|frame
parameter_list|)
block|{
name|ngx_http_v2_out_frame_t
modifier|*
modifier|*
name|out
decl_stmt|;
for|for
control|(
name|out
operator|=
operator|&
name|h2c
operator|->
name|last_out
init|;
operator|*
name|out
condition|;
name|out
operator|=
operator|&
operator|(
operator|*
name|out
operator|)
operator|->
name|next
control|)
block|{
if|if
condition|(
operator|(
operator|*
name|out
operator|)
operator|->
name|blocked
operator|||
operator|(
operator|*
name|out
operator|)
operator|->
name|stream
operator|==
name|NULL
condition|)
block|{
break|break;
block|}
block|}
name|frame
operator|->
name|next
operator|=
operator|*
name|out
expr_stmt|;
operator|*
name|out
operator|=
name|frame
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_http_v2_queue_ordered_frame (ngx_http_v2_connection_t * h2c,ngx_http_v2_out_frame_t * frame)
name|ngx_http_v2_queue_ordered_frame
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|ngx_http_v2_out_frame_t
modifier|*
name|frame
parameter_list|)
block|{
name|frame
operator|->
name|next
operator|=
name|h2c
operator|->
name|last_out
expr_stmt|;
name|h2c
operator|->
name|last_out
operator|=
name|frame
expr_stmt|;
block|}
end_function

begin_function_decl
name|void
name|ngx_http_v2_init
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_v2_read_request_body
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_v2_read_unbuffered_request_body
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_v2_push_stream
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|ngx_uint_t
name|depend
parameter_list|,
name|size_t
name|request_length
parameter_list|,
name|ngx_str_t
modifier|*
name|path
parameter_list|,
name|ngx_str_t
modifier|*
name|authority
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_v2_close_stream
parameter_list|(
name|ngx_http_v2_stream_t
modifier|*
name|stream
parameter_list|,
name|ngx_int_t
name|rc
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_v2_send_output_queue
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_v2_get_indexed_header
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|ngx_uint_t
name|index
parameter_list|,
name|ngx_uint_t
name|name_only
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_v2_add_header
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|ngx_http_v2_header_t
modifier|*
name|header
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_v2_table_size
parameter_list|(
name|ngx_http_v2_connection_t
modifier|*
name|h2c
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_v2_huff_decode
parameter_list|(
name|u_char
modifier|*
name|state
parameter_list|,
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|len
parameter_list|,
name|u_char
modifier|*
modifier|*
name|dst
parameter_list|,
name|ngx_uint_t
name|last
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|size_t
name|ngx_http_v2_huff_encode
parameter_list|(
name|u_char
modifier|*
name|src
parameter_list|,
name|size_t
name|len
parameter_list|,
name|u_char
modifier|*
name|dst
parameter_list|,
name|ngx_uint_t
name|lower
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_http_v2_prefix (bits)
define|#
directive|define
name|ngx_http_v2_prefix
parameter_list|(
name|bits
parameter_list|)
value|((1<< (bits)) - 1)
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_NONALIGNED
operator|)
end_if

begin_define
DECL|macro|ngx_http_v2_parse_uint16 (p)
define|#
directive|define
name|ngx_http_v2_parse_uint16
parameter_list|(
name|p
parameter_list|)
value|ntohs(*(uint16_t *) (p))
end_define

begin_define
DECL|macro|ngx_http_v2_parse_uint32 (p)
define|#
directive|define
name|ngx_http_v2_parse_uint32
parameter_list|(
name|p
parameter_list|)
value|ntohl(*(uint32_t *) (p))
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_http_v2_parse_uint16 (p)
define|#
directive|define
name|ngx_http_v2_parse_uint16
parameter_list|(
name|p
parameter_list|)
value|((p)[0]<< 8 | (p)[1])
end_define

begin_define
DECL|macro|ngx_http_v2_parse_uint32 (p)
define|#
directive|define
name|ngx_http_v2_parse_uint32
parameter_list|(
name|p
parameter_list|)
define|\
value|((uint32_t) (p)[0]<< 24 | (p)[1]<< 16 | (p)[2]<< 8 | (p)[3])
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_http_v2_parse_length (p)
define|#
directive|define
name|ngx_http_v2_parse_length
parameter_list|(
name|p
parameter_list|)
value|((p)>> 8)
end_define

begin_define
DECL|macro|ngx_http_v2_parse_type (p)
define|#
directive|define
name|ngx_http_v2_parse_type
parameter_list|(
name|p
parameter_list|)
value|((p)& 0xff)
end_define

begin_define
DECL|macro|ngx_http_v2_parse_sid (p)
define|#
directive|define
name|ngx_http_v2_parse_sid
parameter_list|(
name|p
parameter_list|)
value|(ngx_http_v2_parse_uint32(p)& 0x7fffffff)
end_define

begin_define
DECL|macro|ngx_http_v2_parse_window (p)
define|#
directive|define
name|ngx_http_v2_parse_window
parameter_list|(
name|p
parameter_list|)
value|(ngx_http_v2_parse_uint32(p)& 0x7fffffff)
end_define

begin_define
DECL|macro|ngx_http_v2_write_uint16_aligned (p,s)
define|#
directive|define
name|ngx_http_v2_write_uint16_aligned
parameter_list|(
name|p
parameter_list|,
name|s
parameter_list|)
define|\
value|(*(uint16_t *) (p) = htons((uint16_t) (s)), (p) + sizeof(uint16_t))
end_define

begin_define
DECL|macro|ngx_http_v2_write_uint32_aligned (p,s)
define|#
directive|define
name|ngx_http_v2_write_uint32_aligned
parameter_list|(
name|p
parameter_list|,
name|s
parameter_list|)
define|\
value|(*(uint32_t *) (p) = htonl((uint32_t) (s)), (p) + sizeof(uint32_t))
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_NONALIGNED
operator|)
end_if

begin_define
DECL|macro|ngx_http_v2_write_uint16
define|#
directive|define
name|ngx_http_v2_write_uint16
value|ngx_http_v2_write_uint16_aligned
end_define

begin_define
DECL|macro|ngx_http_v2_write_uint32
define|#
directive|define
name|ngx_http_v2_write_uint32
value|ngx_http_v2_write_uint32_aligned
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_http_v2_write_uint16 (p,s)
define|#
directive|define
name|ngx_http_v2_write_uint16
parameter_list|(
name|p
parameter_list|,
name|s
parameter_list|)
define|\
value|((p)[0] = (u_char) ((s)>> 8),                                            \      (p)[1] = (u_char)  (s),                                                  \      (p) + sizeof(uint16_t))
end_define

begin_define
DECL|macro|ngx_http_v2_write_uint32 (p,s)
define|#
directive|define
name|ngx_http_v2_write_uint32
parameter_list|(
name|p
parameter_list|,
name|s
parameter_list|)
define|\
value|((p)[0] = (u_char) ((s)>> 24),                                           \      (p)[1] = (u_char) ((s)>> 16),                                           \      (p)[2] = (u_char) ((s)>> 8),                                            \      (p)[3] = (u_char)  (s),                                                  \      (p) + sizeof(uint32_t))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_http_v2_write_len_and_type (p,l,t)
define|#
directive|define
name|ngx_http_v2_write_len_and_type
parameter_list|(
name|p
parameter_list|,
name|l
parameter_list|,
name|t
parameter_list|)
define|\
value|ngx_http_v2_write_uint32_aligned(p, (l)<< 8 | (t))
end_define

begin_define
DECL|macro|ngx_http_v2_write_sid
define|#
directive|define
name|ngx_http_v2_write_sid
value|ngx_http_v2_write_uint32
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_V2_H_INCLUDED_ */
end_comment

end_unit

