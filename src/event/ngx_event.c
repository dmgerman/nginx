begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|<ngx_config.h>
end_include

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_log.h>
end_include

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_listen.h>
end_include

begin_include
include|#
directive|include
file|<ngx_connection.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_accept.h>
end_include

begin_include
include|#
directive|include
file|<ngx_select_module.h>
end_include

begin_if
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_kqueue_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|ngx_connections
name|ngx_connection_t
modifier|*
name|ngx_connections
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_read_events
DECL|variable|ngx_write_events
name|ngx_event_t
modifier|*
name|ngx_read_events
decl_stmt|,
modifier|*
name|ngx_write_events
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|!
operator|(
name|USE_KQUEUE
operator|)
end_if

begin_if
if|#
directive|if
literal|1
end_if

begin_decl_stmt
DECL|variable|ngx_event_type
name|ngx_event_type_e
name|ngx_event_type
init|=
name|NGX_SELECT_EVENT
decl_stmt|;
end_decl_stmt

begin_else
else|#
directive|else
end_else

begin_decl_stmt
DECL|variable|ngx_event_type
name|ngx_event_type_e
name|ngx_event_type
init|=
name|NGX_KQUEUE_EVENT
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
DECL|variable|ngx_event_actions
name|ngx_event_actions_t
name|ngx_event_actions
decl_stmt|;
end_decl_stmt

begin_comment
comment|/* ngx_event_type_e order */
end_comment

begin_function_decl
DECL|variable|ngx_event_init
specifier|static
name|void
function_decl|(
modifier|*
name|ngx_event_init
index|[]
function_decl|)
parameter_list|(
name|int
name|max_connections
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
init|=
block|{
name|ngx_select_init
operator|,
if|#
directive|if
operator|(
name|HAVE_POLL
operator|)
function_decl|ngx_poll_init
operator|,
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
function_decl|ngx_kqueue_init
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_endif
unit|};
endif|#
directive|endif
end_endif

begin_comment
comment|/* USE_KQUEUE */
end_comment

begin_function
DECL|function|ngx_pre_thread (ngx_array_t * ls,ngx_pool_t * pool,ngx_log_t * log)
name|void
name|ngx_pre_thread
parameter_list|(
name|ngx_array_t
modifier|*
name|ls
parameter_list|,
name|ngx_pool_t
modifier|*
name|pool
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|int
name|i
decl_stmt|,
name|fd
decl_stmt|;
name|ngx_listen_t
modifier|*
name|s
decl_stmt|;
comment|/* per group */
name|int
name|max_connections
init|=
literal|512
decl_stmt|;
name|ngx_init_events
argument_list|(
name|max_connections
argument_list|,
name|log
argument_list|)
expr_stmt|;
name|ngx_read_events
operator|=
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_event_t
argument_list|)
operator|*
name|max_connections
argument_list|,
name|log
argument_list|)
expr_stmt|;
name|ngx_write_events
operator|=
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_event_t
argument_list|)
operator|*
name|max_connections
argument_list|,
name|log
argument_list|)
expr_stmt|;
name|ngx_connections
operator|=
name|ngx_alloc
argument_list|(
sizeof|sizeof
argument_list|(
name|ngx_connection_t
argument_list|)
operator|*
name|max_connections
argument_list|,
name|log
argument_list|)
expr_stmt|;
comment|/* for each listening socket */
name|s
operator|=
operator|(
name|ngx_listen_t
operator|*
operator|)
name|ls
operator|->
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
name|ls
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|fd
operator|=
name|s
index|[
name|i
index|]
operator|.
name|fd
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|ngx_read_events
index|[
name|fd
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_event_t
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|ngx_write_events
index|[
name|fd
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_event_t
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_memzero
argument_list|(
operator|&
name|ngx_connections
index|[
name|fd
index|]
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_connection_t
argument_list|)
argument_list|)
expr_stmt|;
name|ngx_connections
index|[
name|fd
index|]
operator|.
name|fd
operator|=
name|fd
expr_stmt|;
name|ngx_connections
index|[
name|fd
index|]
operator|.
name|server
operator|=
name|s
index|[
name|i
index|]
operator|.
name|server
expr_stmt|;
name|ngx_connections
index|[
name|fd
index|]
operator|.
name|read
operator|=
operator|(
name|void
operator|*
operator|)
operator|&
name|ngx_read_events
index|[
name|fd
index|]
operator|.
name|data
expr_stmt|;
name|ngx_connections
index|[
name|fd
index|]
operator|.
name|handler
operator|=
name|s
index|[
name|i
index|]
operator|.
name|handler
expr_stmt|;
name|ngx_read_events
index|[
name|fd
index|]
operator|.
name|data
operator|=
operator|&
name|ngx_connections
index|[
name|fd
index|]
expr_stmt|;
name|ngx_read_events
index|[
name|fd
index|]
operator|.
name|log
operator|=
name|ngx_connections
index|[
name|fd
index|]
operator|.
name|log
operator|=
name|s
index|[
name|i
index|]
operator|.
name|log
expr_stmt|;
name|ngx_read_events
index|[
name|fd
index|]
operator|.
name|data
operator|=
operator|&
name|ngx_connections
index|[
name|fd
index|]
expr_stmt|;
name|ngx_read_events
index|[
name|fd
index|]
operator|.
name|event_handler
operator|=
operator|&
name|ngx_event_accept
expr_stmt|;
name|ngx_read_events
index|[
name|fd
index|]
operator|.
name|listening
operator|=
literal|1
expr_stmt|;
name|ngx_read_events
index|[
name|fd
index|]
operator|.
name|available
operator|=
literal|0
expr_stmt|;
if|#
directive|if
operator|(
name|HAVE_DEFERRED_ACCEPT
operator|)
name|ngx_read_events
index|[
name|fd
index|]
operator|.
name|accept_filter
operator|=
name|s
index|[
name|i
index|]
operator|.
name|accept_filter
expr_stmt|;
endif|#
directive|endif
name|ngx_add_event
argument_list|(
operator|&
name|ngx_read_events
index|[
name|fd
index|]
argument_list|,
name|NGX_READ_EVENT
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
DECL|function|ngx_worker (ngx_log_t * log)
name|void
name|ngx_worker
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
while|while
condition|(
literal|1
condition|)
block|{
name|ngx_log_debug
argument_list|(
name|log
argument_list|,
literal|"ngx_worker cycle"
argument_list|)
expr_stmt|;
name|ngx_process_events
argument_list|(
name|log
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

