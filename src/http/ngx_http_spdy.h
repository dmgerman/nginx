begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Nginx, Inc.  * Copyright (C) Valentin V. Bartenev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_SPDY_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_SPDY_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_SPDY_H_INCLUDED_
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

begin_include
include|#
directive|include
file|<zlib.h>
end_include

begin_define
DECL|macro|NGX_SPDY_VERSION
define|#
directive|define
name|NGX_SPDY_VERSION
value|2
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|TLSEXT_TYPE_next_proto_neg
end_ifdef

begin_define
DECL|macro|NGX_SPDY_NPN_ADVERTISE
define|#
directive|define
name|NGX_SPDY_NPN_ADVERTISE
value|"\x06spdy/2"
end_define

begin_define
DECL|macro|NGX_SPDY_NPN_NEGOTIATED
define|#
directive|define
name|NGX_SPDY_NPN_NEGOTIATED
value|"spdy/2"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_SPDY_STATE_BUFFER_SIZE
define|#
directive|define
name|NGX_SPDY_STATE_BUFFER_SIZE
value|16
end_define

begin_define
DECL|macro|NGX_SPDY_CTL_BIT
define|#
directive|define
name|NGX_SPDY_CTL_BIT
value|1
end_define

begin_define
DECL|macro|NGX_SPDY_SYN_STREAM
define|#
directive|define
name|NGX_SPDY_SYN_STREAM
value|1
end_define

begin_define
DECL|macro|NGX_SPDY_SYN_REPLY
define|#
directive|define
name|NGX_SPDY_SYN_REPLY
value|2
end_define

begin_define
DECL|macro|NGX_SPDY_RST_STREAM
define|#
directive|define
name|NGX_SPDY_RST_STREAM
value|3
end_define

begin_define
DECL|macro|NGX_SPDY_SETTINGS
define|#
directive|define
name|NGX_SPDY_SETTINGS
value|4
end_define

begin_define
DECL|macro|NGX_SPDY_NOOP
define|#
directive|define
name|NGX_SPDY_NOOP
value|5
end_define

begin_define
DECL|macro|NGX_SPDY_PING
define|#
directive|define
name|NGX_SPDY_PING
value|6
end_define

begin_define
DECL|macro|NGX_SPDY_GOAWAY
define|#
directive|define
name|NGX_SPDY_GOAWAY
value|7
end_define

begin_define
DECL|macro|NGX_SPDY_HEADERS
define|#
directive|define
name|NGX_SPDY_HEADERS
value|8
end_define

begin_define
DECL|macro|NGX_SPDY_FRAME_HEADER_SIZE
define|#
directive|define
name|NGX_SPDY_FRAME_HEADER_SIZE
value|8
end_define

begin_define
DECL|macro|NGX_SPDY_SID_SIZE
define|#
directive|define
name|NGX_SPDY_SID_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_SPDY_SYN_STREAM_SIZE
define|#
directive|define
name|NGX_SPDY_SYN_STREAM_SIZE
value|10
end_define

begin_define
DECL|macro|NGX_SPDY_SYN_REPLY_SIZE
define|#
directive|define
name|NGX_SPDY_SYN_REPLY_SIZE
value|6
end_define

begin_define
DECL|macro|NGX_SPDY_RST_STREAM_SIZE
define|#
directive|define
name|NGX_SPDY_RST_STREAM_SIZE
value|8
end_define

begin_define
DECL|macro|NGX_SPDY_PING_SIZE
define|#
directive|define
name|NGX_SPDY_PING_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_SPDY_GOAWAY_SIZE
define|#
directive|define
name|NGX_SPDY_GOAWAY_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_SPDY_NV_NUM_SIZE
define|#
directive|define
name|NGX_SPDY_NV_NUM_SIZE
value|2
end_define

begin_define
DECL|macro|NGX_SPDY_NV_NLEN_SIZE
define|#
directive|define
name|NGX_SPDY_NV_NLEN_SIZE
value|2
end_define

begin_define
DECL|macro|NGX_SPDY_NV_VLEN_SIZE
define|#
directive|define
name|NGX_SPDY_NV_VLEN_SIZE
value|2
end_define

begin_define
DECL|macro|NGX_SPDY_SETTINGS_NUM_SIZE
define|#
directive|define
name|NGX_SPDY_SETTINGS_NUM_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_SPDY_SETTINGS_IDF_SIZE
define|#
directive|define
name|NGX_SPDY_SETTINGS_IDF_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_SPDY_SETTINGS_VAL_SIZE
define|#
directive|define
name|NGX_SPDY_SETTINGS_VAL_SIZE
value|4
end_define

begin_define
DECL|macro|NGX_SPDY_SETTINGS_PAIR_SIZE
define|#
directive|define
name|NGX_SPDY_SETTINGS_PAIR_SIZE
define|\
value|(NGX_SPDY_SETTINGS_IDF_SIZE + NGX_SPDY_SETTINGS_VAL_SIZE)
end_define

begin_define
DECL|macro|NGX_SPDY_HIGHEST_PRIORITY
define|#
directive|define
name|NGX_SPDY_HIGHEST_PRIORITY
value|0
end_define

begin_define
DECL|macro|NGX_SPDY_LOWEST_PRIORITY
define|#
directive|define
name|NGX_SPDY_LOWEST_PRIORITY
value|3
end_define

begin_define
DECL|macro|NGX_SPDY_FLAG_FIN
define|#
directive|define
name|NGX_SPDY_FLAG_FIN
value|0x01
end_define

begin_define
DECL|macro|NGX_SPDY_FLAG_UNIDIRECTIONAL
define|#
directive|define
name|NGX_SPDY_FLAG_UNIDIRECTIONAL
value|0x02
end_define

begin_define
DECL|macro|NGX_SPDY_FLAG_CLEAR_SETTINGS
define|#
directive|define
name|NGX_SPDY_FLAG_CLEAR_SETTINGS
value|0x01
end_define

begin_define
DECL|macro|NGX_SPDY_MAX_FRAME_SIZE
define|#
directive|define
name|NGX_SPDY_MAX_FRAME_SIZE
value|((1<< 24) - 1)
end_define

begin_define
DECL|macro|NGX_SPDY_DATA_DISCARD
define|#
directive|define
name|NGX_SPDY_DATA_DISCARD
value|1
end_define

begin_define
DECL|macro|NGX_SPDY_DATA_ERROR
define|#
directive|define
name|NGX_SPDY_DATA_ERROR
value|2
end_define

begin_define
DECL|macro|NGX_SPDY_DATA_INTERNAL_ERROR
define|#
directive|define
name|NGX_SPDY_DATA_INTERNAL_ERROR
value|3
end_define

begin_typedef
DECL|typedef|ngx_http_spdy_connection_t
typedef|typedef
name|struct
name|ngx_http_spdy_connection_s
name|ngx_http_spdy_connection_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_spdy_out_frame_t
typedef|typedef
name|struct
name|ngx_http_spdy_out_frame_s
name|ngx_http_spdy_out_frame_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_http_spdy_handler_pt
typedef|typedef
name|u_char
modifier|*
function_decl|(
modifier|*
name|ngx_http_spdy_handler_pt
function_decl|)
parameter_list|(
name|ngx_http_spdy_connection_t
modifier|*
name|sc
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

begin_struct
DECL|struct|ngx_http_spdy_connection_s
struct|struct
name|ngx_http_spdy_connection_s
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
DECL|member|buffer
name|u_char
name|buffer
index|[
name|NGX_SPDY_STATE_BUFFER_SIZE
index|]
decl_stmt|;
DECL|member|buffer_used
name|size_t
name|buffer_used
decl_stmt|;
DECL|member|handler
name|ngx_http_spdy_handler_pt
name|handler
decl_stmt|;
DECL|member|zstream_in
name|z_stream
name|zstream_in
decl_stmt|;
DECL|member|zstream_out
name|z_stream
name|zstream_out
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|free_ctl_frames
name|ngx_http_spdy_out_frame_t
modifier|*
name|free_ctl_frames
decl_stmt|;
DECL|member|free_fake_connections
name|ngx_connection_t
modifier|*
name|free_fake_connections
decl_stmt|;
DECL|member|streams_index
name|ngx_http_spdy_stream_t
modifier|*
modifier|*
name|streams_index
decl_stmt|;
DECL|member|last_out
name|ngx_http_spdy_out_frame_t
modifier|*
name|last_out
decl_stmt|;
DECL|member|last_stream
name|ngx_http_spdy_stream_t
modifier|*
name|last_stream
decl_stmt|;
DECL|member|stream
name|ngx_http_spdy_stream_t
modifier|*
name|stream
decl_stmt|;
DECL|member|headers
name|ngx_uint_t
name|headers
decl_stmt|;
DECL|member|length
name|size_t
name|length
decl_stmt|;
DECL|member|flags
name|u_char
name|flags
decl_stmt|;
DECL|member|last_sid
name|ngx_uint_t
name|last_sid
decl_stmt|;
DECL|member|blocked
name|unsigned
name|blocked
range|:
literal|1
decl_stmt|;
DECL|member|incomplete
name|unsigned
name|incomplete
range|:
literal|1
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|ngx_http_spdy_stream_s
struct|struct
name|ngx_http_spdy_stream_s
block|{
DECL|member|id
name|ngx_uint_t
name|id
decl_stmt|;
DECL|member|request
name|ngx_http_request_t
modifier|*
name|request
decl_stmt|;
DECL|member|connection
name|ngx_http_spdy_connection_t
modifier|*
name|connection
decl_stmt|;
DECL|member|index
name|ngx_http_spdy_stream_t
modifier|*
name|index
decl_stmt|;
DECL|member|next
name|ngx_http_spdy_stream_t
modifier|*
name|next
decl_stmt|;
DECL|member|header_buffers
name|ngx_uint_t
name|header_buffers
decl_stmt|;
DECL|member|queued
name|ngx_uint_t
name|queued
decl_stmt|;
DECL|member|free_frames
name|ngx_http_spdy_out_frame_t
modifier|*
name|free_frames
decl_stmt|;
DECL|member|free_data_headers
name|ngx_chain_t
modifier|*
name|free_data_headers
decl_stmt|;
DECL|member|priority
name|unsigned
name|priority
range|:
literal|2
decl_stmt|;
DECL|member|handled
name|unsigned
name|handled
range|:
literal|1
decl_stmt|;
DECL|member|blocked
name|unsigned
name|blocked
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
DECL|member|skip_data
name|unsigned
name|skip_data
range|:
literal|2
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|ngx_http_spdy_out_frame_s
struct|struct
name|ngx_http_spdy_out_frame_s
block|{
DECL|member|next
name|ngx_http_spdy_out_frame_t
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
name|ngx_http_spdy_connection_t
modifier|*
name|sc
parameter_list|,
name|ngx_http_spdy_out_frame_t
modifier|*
name|frame
parameter_list|)
function_decl|;
DECL|member|free
name|ngx_http_spdy_out_frame_t
modifier|*
name|free
decl_stmt|;
DECL|member|stream
name|ngx_http_spdy_stream_t
modifier|*
name|stream
decl_stmt|;
DECL|member|size
name|size_t
name|size
decl_stmt|;
DECL|member|priority
name|ngx_uint_t
name|priority
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
DECL|function|ngx_http_spdy_queue_frame (ngx_http_spdy_connection_t * sc,ngx_http_spdy_out_frame_t * frame)
name|ngx_http_spdy_queue_frame
parameter_list|(
name|ngx_http_spdy_connection_t
modifier|*
name|sc
parameter_list|,
name|ngx_http_spdy_out_frame_t
modifier|*
name|frame
parameter_list|)
block|{
name|ngx_http_spdy_out_frame_t
modifier|*
modifier|*
name|out
decl_stmt|;
for|for
control|(
name|out
operator|=
operator|&
name|sc
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
name|frame
operator|->
name|priority
operator|>=
operator|(
operator|*
name|out
operator|)
operator|->
name|priority
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
DECL|function|ngx_http_spdy_queue_blocked_frame (ngx_http_spdy_connection_t * sc,ngx_http_spdy_out_frame_t * frame)
name|ngx_http_spdy_queue_blocked_frame
parameter_list|(
name|ngx_http_spdy_connection_t
modifier|*
name|sc
parameter_list|,
name|ngx_http_spdy_out_frame_t
modifier|*
name|frame
parameter_list|)
block|{
name|ngx_http_spdy_out_frame_t
modifier|*
modifier|*
name|out
decl_stmt|;
for|for
control|(
name|out
operator|=
operator|&
name|sc
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

begin_function_decl
name|void
name|ngx_http_spdy_init
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_spdy_request_headers_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_http_spdy_read_request_body
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|,
name|ngx_http_client_body_handler_pt
name|post_handler
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_http_spdy_close_stream
parameter_list|(
name|ngx_http_spdy_stream_t
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
name|ngx_http_spdy_send_output_queue
parameter_list|(
name|ngx_http_spdy_connection_t
modifier|*
name|sc
parameter_list|)
function_decl|;
end_function_decl

begin_define
DECL|macro|ngx_spdy_frame_aligned_write_uint16 (p,s)
define|#
directive|define
name|ngx_spdy_frame_aligned_write_uint16
parameter_list|(
name|p
parameter_list|,
name|s
parameter_list|)
define|\
value|(*(uint16_t *) (p) = htons((uint16_t) (s)), (p) + sizeof(uint16_t))
end_define

begin_define
DECL|macro|ngx_spdy_frame_aligned_write_uint32 (p,s)
define|#
directive|define
name|ngx_spdy_frame_aligned_write_uint32
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
DECL|macro|ngx_spdy_frame_write_uint16
define|#
directive|define
name|ngx_spdy_frame_write_uint16
value|ngx_spdy_frame_aligned_write_uint16
end_define

begin_define
DECL|macro|ngx_spdy_frame_write_uint32
define|#
directive|define
name|ngx_spdy_frame_write_uint32
value|ngx_spdy_frame_aligned_write_uint32
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_spdy_frame_write_uint16 (p,s)
define|#
directive|define
name|ngx_spdy_frame_write_uint16
parameter_list|(
name|p
parameter_list|,
name|s
parameter_list|)
define|\
value|((p)[0] = (u_char) (s)>> 8, (p)[1] = (u_char) (s), (p) + sizeof(uint16_t))
end_define

begin_define
DECL|macro|ngx_spdy_frame_write_uint32 (p,s)
define|#
directive|define
name|ngx_spdy_frame_write_uint32
parameter_list|(
name|p
parameter_list|,
name|s
parameter_list|)
define|\
value|((p)[0] = (u_char) (s)>> 24,                                             \     (p)[1] = (u_char) (s)>> 16,                                              \     (p)[2] = (u_char) (s)>> 8,                                               \     (p)[3] = (u_char) (s), (p) + sizeof(uint32_t))
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_spdy_ctl_frame_head (t)
define|#
directive|define
name|ngx_spdy_ctl_frame_head
parameter_list|(
name|t
parameter_list|)
define|\
value|((uint32_t) NGX_SPDY_CTL_BIT<< 31 | NGX_SPDY_VERSION<< 16 | (t))
end_define

begin_define
DECL|macro|ngx_spdy_frame_write_head (p,t)
define|#
directive|define
name|ngx_spdy_frame_write_head
parameter_list|(
name|p
parameter_list|,
name|t
parameter_list|)
define|\
value|ngx_spdy_frame_aligned_write_uint32(p, ngx_spdy_ctl_frame_head(t))
end_define

begin_define
DECL|macro|ngx_spdy_frame_write_flags_and_len (p,f,l)
define|#
directive|define
name|ngx_spdy_frame_write_flags_and_len
parameter_list|(
name|p
parameter_list|,
name|f
parameter_list|,
name|l
parameter_list|)
define|\
value|ngx_spdy_frame_aligned_write_uint32(p, (f)<< 24 | (l))
end_define

begin_define
DECL|macro|ngx_spdy_frame_write_sid
define|#
directive|define
name|ngx_spdy_frame_write_sid
value|ngx_spdy_frame_aligned_write_uint32
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_SPDY_H_INCLUDED_ */
end_comment

end_unit

