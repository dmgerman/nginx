begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_PIPE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_PIPE_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_PIPE_H_INCLUDED_
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

begin_typedef
DECL|typedef|ngx_event_pipe_t
typedef|typedef
name|struct
name|ngx_event_pipe_s
name|ngx_event_pipe_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_event_pipe_input_filter_pt
typedef|typedef
name|int
function_decl|(
modifier|*
name|ngx_event_pipe_input_filter_pt
function_decl|)
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|,
name|ngx_hunk_t
modifier|*
name|hunk
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|ngx_event_pipe_output_filter_pt
typedef|typedef
name|int
function_decl|(
modifier|*
name|ngx_event_pipe_output_filter_pt
function_decl|)
parameter_list|(
name|void
modifier|*
name|data
parameter_list|,
name|ngx_chain_t
modifier|*
name|chain
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|ngx_event_pipe_s
struct|struct
name|ngx_event_pipe_s
block|{
DECL|member|free_raw_hunks
name|ngx_chain_t
modifier|*
name|free_raw_hunks
decl_stmt|;
DECL|member|in
name|ngx_chain_t
modifier|*
name|in
decl_stmt|;
DECL|member|last_in
name|ngx_chain_t
modifier|*
modifier|*
name|last_in
decl_stmt|;
DECL|member|out
name|ngx_chain_t
modifier|*
name|out
decl_stmt|;
DECL|member|last_out
name|ngx_chain_t
modifier|*
modifier|*
name|last_out
decl_stmt|;
DECL|member|free
name|ngx_chain_t
modifier|*
name|free
decl_stmt|;
DECL|member|busy
name|ngx_chain_t
modifier|*
name|busy
decl_stmt|;
comment|/*      * the input filter i.e. that moves HTTP/1.1 chunks      * from the raw hunks to an incoming chain      */
DECL|member|input_filter
name|ngx_event_pipe_input_filter_pt
name|input_filter
decl_stmt|;
DECL|member|input_ctx
name|void
modifier|*
name|input_ctx
decl_stmt|;
DECL|member|output_filter
name|ngx_event_pipe_output_filter_pt
name|output_filter
decl_stmt|;
DECL|member|output_ctx
name|void
modifier|*
name|output_ctx
decl_stmt|;
DECL|member|read
name|unsigned
name|read
range|:
literal|1
decl_stmt|;
DECL|member|cachable
name|unsigned
name|cachable
range|:
literal|1
decl_stmt|;
DECL|member|single_buf
name|unsigned
name|single_buf
range|:
literal|1
decl_stmt|;
DECL|member|free_bufs
name|unsigned
name|free_bufs
range|:
literal|1
decl_stmt|;
DECL|member|upstream_done
name|unsigned
name|upstream_done
range|:
literal|1
decl_stmt|;
DECL|member|upstream_error
name|unsigned
name|upstream_error
range|:
literal|1
decl_stmt|;
DECL|member|upstream_eof
name|unsigned
name|upstream_eof
range|:
literal|1
decl_stmt|;
DECL|member|upstream_blocked
name|unsigned
name|upstream_blocked
range|:
literal|1
decl_stmt|;
DECL|member|downstream_done
name|unsigned
name|downstream_done
range|:
literal|1
decl_stmt|;
DECL|member|downstream_error
name|unsigned
name|downstream_error
range|:
literal|1
decl_stmt|;
DECL|member|cyclic_temp_file
name|unsigned
name|cyclic_temp_file
range|:
literal|1
decl_stmt|;
DECL|member|hunks
name|int
name|hunks
decl_stmt|;
DECL|member|bufs
name|ngx_bufs_t
name|bufs
decl_stmt|;
DECL|member|tag
name|ngx_hunk_tag_t
name|tag
decl_stmt|;
DECL|member|busy_size
name|size_t
name|busy_size
decl_stmt|;
DECL|member|max_temp_file_size
name|off_t
name|max_temp_file_size
decl_stmt|;
DECL|member|temp_file_write_size
name|int
name|temp_file_write_size
decl_stmt|;
DECL|member|upstream
name|ngx_connection_t
modifier|*
name|upstream
decl_stmt|;
DECL|member|downstream
name|ngx_connection_t
modifier|*
name|downstream
decl_stmt|;
DECL|member|read_timeout
name|ngx_msec_t
name|read_timeout
decl_stmt|;
DECL|member|send_timeout
name|ngx_msec_t
name|send_timeout
decl_stmt|;
DECL|member|send_lowat
name|ssize_t
name|send_lowat
decl_stmt|;
DECL|member|pool
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|preread_hunks
name|ngx_chain_t
modifier|*
name|preread_hunks
decl_stmt|;
DECL|member|preread_size
name|int
name|preread_size
decl_stmt|;
DECL|member|temp_file
name|ngx_temp_file_t
modifier|*
name|temp_file
decl_stmt|;
DECL|member|num
comment|/* STUB */
name|int
name|num
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|int
name|ngx_event_pipe
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|,
name|int
name|do_write
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_event_pipe_copy_input_filter
parameter_list|(
name|ngx_event_pipe_t
modifier|*
name|p
parameter_list|,
name|ngx_hunk_t
modifier|*
name|hunk
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_PIPE_H_INCLUDED_ */
end_comment

end_unit

