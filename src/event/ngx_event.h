begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_EVENT_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_EVENT_H_INCLUDED_
define|#
directive|define
name|_NGX_EVENT_H_INCLUDED_
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

begin_define
DECL|macro|NGX_INVALID_INDEX
define|#
directive|define
name|NGX_INVALID_INDEX
value|0xd0d0d0d0
end_define

begin_if
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
end_if

begin_typedef
DECL|struct|__anon2c5b19a90108
typedef|typedef
struct|struct
block|{
DECL|member|ovlp
name|WSAOVERLAPPED
name|ovlp
decl_stmt|;
DECL|member|event
name|ngx_event_t
modifier|*
name|event
decl_stmt|;
DECL|member|error
name|int
name|error
decl_stmt|;
DECL|typedef|ngx_event_ovlp_t
block|}
name|ngx_event_ovlp_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_struct
DECL|struct|ngx_event_s
struct|struct
name|ngx_event_s
block|{
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
comment|/* TODO rename to handler, move flags to struct start */
DECL|member|event_handler
name|void
function_decl|(
modifier|*
name|event_handler
function_decl|)
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
DECL|member|index
name|u_int
name|index
decl_stmt|;
comment|/* queue in mutex(), aio_read(), aio_write()  */
DECL|member|prev
name|ngx_event_t
modifier|*
name|prev
decl_stmt|;
DECL|member|next
name|ngx_event_t
modifier|*
name|next
decl_stmt|;
if|#
directive|if
literal|0
block|ngx_event_t     *timer_prev;     ngx_event_t     *timer_next;      ngx_msec_t       timer_delta;
endif|#
directive|endif
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
comment|/*      * ngx_rbtree_t     rbtree;      */
DECL|member|rbtree_key
name|ngx_int_t
name|rbtree_key
decl_stmt|;
DECL|member|rbtree_left
name|void
modifier|*
name|rbtree_left
decl_stmt|;
DECL|member|rbtree_right
name|void
modifier|*
name|rbtree_right
decl_stmt|;
DECL|member|rbtree_parent
name|void
modifier|*
name|rbtree_parent
decl_stmt|;
DECL|member|rbtree_color
name|char
name|rbtree_color
decl_stmt|;
DECL|member|oneshot
name|unsigned
name|char
name|oneshot
range|:
literal|1
decl_stmt|;
DECL|member|write
name|unsigned
name|char
name|write
range|:
literal|1
decl_stmt|;
comment|/* used to detect the stale events in kqueue, rt signals and epoll */
DECL|member|instance
name|unsigned
name|char
name|instance
range|:
literal|1
decl_stmt|;
comment|/*      * the event was passed or would be passed to a kernel;      * in aio mode - operation was posted.      */
DECL|member|active
name|unsigned
name|char
name|active
range|:
literal|1
decl_stmt|;
comment|/* the ready event; in aio mode 0 means that no operation can be posted */
DECL|member|ready
name|unsigned
name|char
name|ready
range|:
literal|1
decl_stmt|;
comment|/* aio operation is complete */
DECL|member|complete
name|unsigned
name|char
name|complete
range|:
literal|1
decl_stmt|;
DECL|member|eof
name|unsigned
name|char
name|eof
range|:
literal|1
decl_stmt|;
DECL|member|error
name|unsigned
name|char
name|error
range|:
literal|1
decl_stmt|;
DECL|member|timedout
name|unsigned
name|short
name|timedout
range|:
literal|1
decl_stmt|;
DECL|member|timer_set
name|unsigned
name|short
name|timer_set
range|:
literal|1
decl_stmt|;
DECL|member|delayed
name|unsigned
name|short
name|delayed
range|:
literal|1
decl_stmt|;
DECL|member|read_discarded
name|unsigned
name|short
name|read_discarded
range|:
literal|1
decl_stmt|;
DECL|member|ignore_econnreset
name|unsigned
name|short
name|ignore_econnreset
range|:
literal|1
decl_stmt|;
DECL|member|unexpected_eof
name|unsigned
name|short
name|unexpected_eof
range|:
literal|1
decl_stmt|;
DECL|member|deferred_accept
name|unsigned
name|short
name|deferred_accept
range|:
literal|1
decl_stmt|;
comment|/* TODO: aio_eof and kq_eof can be the single pending_eof */
comment|/* the pending eof in aio chain operation */
DECL|member|aio_eof
name|unsigned
name|short
name|aio_eof
range|:
literal|1
decl_stmt|;
comment|/* the pending eof reported by kqueue */
DECL|member|kq_eof
name|unsigned
name|short
name|kq_eof
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|WIN32
operator|)
comment|/* setsockopt(SO_UPDATE_ACCEPT_CONTEXT) was succesfull */
DECL|member|accept_context_updated
name|unsigned
name|short
name|accept_context_updated
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
DECL|member|kq_vnode
name|unsigned
name|short
name|kq_vnode
range|:
literal|1
decl_stmt|;
comment|/* the pending errno reported by kqueue */
DECL|member|kq_errno
name|int
name|kq_errno
decl_stmt|;
endif|#
directive|endif
comment|/*      * kqueue only:      *   accept:     number of sockets that wait to be accepted      *   read:       bytes to read when event is ready      *               or lowat when event is set with NGX_LOWAT_EVENT flag      *   write:      available space in buffer when event is ready      *               or lowat when event is set with NGX_LOWAT_EVENT flag      *      * otherwise:      *   accept:     1 if accept many, 0 otherwise      */
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
DECL|member|available
name|int
name|available
decl_stmt|;
else|#
directive|else
DECL|member|available
name|unsigned
name|short
name|available
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_AIO
operator|)
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
DECL|member|ovlp
name|ngx_event_ovlp_t
name|ovlp
decl_stmt|;
else|#
directive|else
DECL|member|aiocb
name|struct
name|aiocb
name|aiocb
decl_stmt|;
endif|#
directive|endif
endif|#
directive|endif
if|#
directive|if
literal|0
comment|/* the threads support */
comment|/*      * the event thread context, we store it here      * if $(CC) does not understand __thread declaration      * and pthread_getspecific() is too costly      */
block|void            *thr_ctx;
if|#
directive|if
operator|(
name|NGX_EVENT_T_PADDING
operator|)
comment|/* event should not cross cache line in SMP */
block|int              padding[NGX_EVENT_T_PADDING];
endif|#
directive|endif
endif|#
directive|endif
block|}
struct|;
end_struct

begin_typedef
DECL|struct|__anon2c5b19a90208
typedef|typedef
struct|struct
block|{
DECL|member|add
name|int
function_decl|(
modifier|*
name|add
function_decl|)
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|int
name|event
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
DECL|member|del
name|int
function_decl|(
modifier|*
name|del
function_decl|)
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|int
name|event
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
DECL|member|enable
name|int
function_decl|(
modifier|*
name|enable
function_decl|)
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|int
name|event
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
DECL|member|disable
name|int
function_decl|(
modifier|*
name|disable
function_decl|)
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|,
name|int
name|event
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
DECL|member|add_conn
name|int
function_decl|(
modifier|*
name|add_conn
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
DECL|member|del_conn
name|int
function_decl|(
modifier|*
name|del_conn
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
DECL|member|process
name|int
function_decl|(
modifier|*
name|process
function_decl|)
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
DECL|member|init
name|int
function_decl|(
modifier|*
name|init
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|done
name|void
function_decl|(
modifier|*
name|done
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|typedef|ngx_event_actions_t
block|}
name|ngx_event_actions_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|ngx_event_actions_t
name|ngx_event_actions
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  * The event filter requires to read/write the whole data -  * select, poll, /dev/poll, kqueue.  */
end_comment

begin_define
DECL|macro|NGX_USE_LEVEL_EVENT
define|#
directive|define
name|NGX_USE_LEVEL_EVENT
value|0x00000001
end_define

begin_comment
comment|/*  * The event filter is deleted after a notification without an additional  * syscall - select, poll, kqueue.  */
end_comment

begin_define
DECL|macro|NGX_USE_ONESHOT_EVENT
define|#
directive|define
name|NGX_USE_ONESHOT_EVENT
value|0x00000002
end_define

begin_comment
comment|/*  *  The event filter notifies only the changes and an initial level - kqueue.  */
end_comment

begin_define
DECL|macro|NGX_USE_CLEAR_EVENT
define|#
directive|define
name|NGX_USE_CLEAR_EVENT
value|0x00000004
end_define

begin_comment
comment|/*  * The event filter has kqueue features - the eof flag, errno,  * available data, etc  */
end_comment

begin_define
DECL|macro|NGX_HAVE_KQUEUE_EVENT
define|#
directive|define
name|NGX_HAVE_KQUEUE_EVENT
value|0x00000008
end_define

begin_comment
comment|/*  * The event filter supports low water mark - kqueue's NOTE_LOWAT.  * kqueue in FreeBSD 4.1-4.2 has no NOTE_LOWAT so we need a separate flag.  */
end_comment

begin_define
DECL|macro|NGX_HAVE_LOWAT_EVENT
define|#
directive|define
name|NGX_HAVE_LOWAT_EVENT
value|0x00000010
end_define

begin_comment
comment|/*  * The event filter notifies only the changes (the edges)  * but not an initial level - epoll.  */
end_comment

begin_define
DECL|macro|NGX_USE_EDGE_EVENT
define|#
directive|define
name|NGX_USE_EDGE_EVENT
value|0x00000020
end_define

begin_comment
comment|/*  * No need to add or delete the event filters - rt signals.  */
end_comment

begin_define
DECL|macro|NGX_USE_SIGIO_EVENT
define|#
directive|define
name|NGX_USE_SIGIO_EVENT
value|0x00000040
end_define

begin_comment
comment|/*  * No need to add or delete the event filters - overlapped, aio_read,  * aioread, io_submit.  */
end_comment

begin_define
DECL|macro|NGX_USE_AIO_EVENT
define|#
directive|define
name|NGX_USE_AIO_EVENT
value|0x00000080
end_define

begin_comment
comment|/*  * Need to add socket or handle only once - i/o completion port.  * It also requires HAVE_AIO and NGX_USE_AIO_EVENT to be set.  */
end_comment

begin_define
DECL|macro|NGX_USE_IOCP_EVENT
define|#
directive|define
name|NGX_USE_IOCP_EVENT
value|0x00000100
end_define

begin_comment
comment|/*  * The event filter is deleted before the closing file.  * Has no meaning for select, poll, epoll.  *  * kqueue:     kqueue deletes event filters for file that closed  *             so we need only to delete filters in user-level batch array  * /dev/poll:  we need to flush POLLREMOVE event before closing file  */
end_comment

begin_define
DECL|macro|NGX_CLOSE_EVENT
define|#
directive|define
name|NGX_CLOSE_EVENT
value|1
end_define

begin_comment
comment|/* these flags have a meaning only for kqueue */
end_comment

begin_define
DECL|macro|NGX_LOWAT_EVENT
define|#
directive|define
name|NGX_LOWAT_EVENT
value|0
end_define

begin_define
DECL|macro|NGX_DISABLE_EVENT
define|#
directive|define
name|NGX_DISABLE_EVENT
value|0
end_define

begin_define
DECL|macro|NGX_VNODE_EVENT
define|#
directive|define
name|NGX_VNODE_EVENT
value|0
end_define

begin_if
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
end_if

begin_define
DECL|macro|NGX_READ_EVENT
define|#
directive|define
name|NGX_READ_EVENT
value|EVFILT_READ
end_define

begin_define
DECL|macro|NGX_WRITE_EVENT
define|#
directive|define
name|NGX_WRITE_EVENT
value|EVFILT_WRITE
end_define

begin_undef
undef|#
directive|undef
name|NGX_VNODE_EVENT
end_undef

begin_define
DECL|macro|NGX_VNODE_EVENT
define|#
directive|define
name|NGX_VNODE_EVENT
value|EVFILT_VNODE
end_define

begin_comment
comment|/*  * NGX_CLOSE_EVENT and NGX_LOWAT_EVENT are the module flags and they would  * not go into a kernel so we need to choose the value that would not interfere  * with any existent and future kqueue flags.  kqueue has such values -  * EV_FLAG1, EV_EOF and EV_ERROR.  They are reserved and cleared on a kernel  * entrance.  */
end_comment

begin_undef
undef|#
directive|undef
name|NGX_CLOSE_EVENT
end_undef

begin_define
DECL|macro|NGX_CLOSE_EVENT
define|#
directive|define
name|NGX_CLOSE_EVENT
value|EV_EOF
end_define

begin_undef
undef|#
directive|undef
name|NGX_LOWAT_EVENT
end_undef

begin_define
DECL|macro|NGX_LOWAT_EVENT
define|#
directive|define
name|NGX_LOWAT_EVENT
value|EV_FLAG1
end_define

begin_define
DECL|macro|NGX_LEVEL_EVENT
define|#
directive|define
name|NGX_LEVEL_EVENT
value|0
end_define

begin_define
DECL|macro|NGX_ONESHOT_EVENT
define|#
directive|define
name|NGX_ONESHOT_EVENT
value|EV_ONESHOT
end_define

begin_define
DECL|macro|NGX_CLEAR_EVENT
define|#
directive|define
name|NGX_CLEAR_EVENT
value|EV_CLEAR
end_define

begin_undef
undef|#
directive|undef
name|NGX_DISABLE_EVENT
end_undef

begin_define
DECL|macro|NGX_DISABLE_EVENT
define|#
directive|define
name|NGX_DISABLE_EVENT
value|EV_DISABLE
end_define

begin_elif
elif|#
directive|elif
operator|(
name|HAVE_POLL
operator|)
end_elif

begin_define
DECL|macro|NGX_READ_EVENT
define|#
directive|define
name|NGX_READ_EVENT
value|POLLIN
end_define

begin_define
DECL|macro|NGX_WRITE_EVENT
define|#
directive|define
name|NGX_WRITE_EVENT
value|POLLOUT
end_define

begin_define
DECL|macro|NGX_LEVEL_EVENT
define|#
directive|define
name|NGX_LEVEL_EVENT
value|0
end_define

begin_define
DECL|macro|NGX_ONESHOT_EVENT
define|#
directive|define
name|NGX_ONESHOT_EVENT
value|1
end_define

begin_elif
elif|#
directive|elif
operator|(
name|HAVE_DEVPOLL
operator|)
end_elif

begin_define
DECL|macro|NGX_READ_EVENT
define|#
directive|define
name|NGX_READ_EVENT
value|POLLIN
end_define

begin_define
DECL|macro|NGX_WRITE_EVENT
define|#
directive|define
name|NGX_WRITE_EVENT
value|POLLOUT
end_define

begin_define
DECL|macro|NGX_LEVEL_EVENT
define|#
directive|define
name|NGX_LEVEL_EVENT
value|0
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* select */
end_comment

begin_define
DECL|macro|NGX_READ_EVENT
define|#
directive|define
name|NGX_READ_EVENT
value|0
end_define

begin_define
DECL|macro|NGX_WRITE_EVENT
define|#
directive|define
name|NGX_WRITE_EVENT
value|1
end_define

begin_define
DECL|macro|NGX_LEVEL_EVENT
define|#
directive|define
name|NGX_LEVEL_EVENT
value|0
end_define

begin_define
DECL|macro|NGX_ONESHOT_EVENT
define|#
directive|define
name|NGX_ONESHOT_EVENT
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* HAVE_KQUEUE */
end_comment

begin_if
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
end_if

begin_define
DECL|macro|NGX_IOCP_ACCEPT
define|#
directive|define
name|NGX_IOCP_ACCEPT
value|0
end_define

begin_define
DECL|macro|NGX_IOCP_IO
define|#
directive|define
name|NGX_IOCP_IO
value|1
end_define

begin_define
DECL|macro|NGX_IOCP_CONNECT
define|#
directive|define
name|NGX_IOCP_CONNECT
value|2
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|NGX_CLEAR_EVENT
end_ifndef

begin_define
DECL|macro|NGX_CLEAR_EVENT
define|#
directive|define
name|NGX_CLEAR_EVENT
value|0
end_define

begin_comment
DECL|macro|NGX_CLEAR_EVENT
comment|/* dummy declaration */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_process_events
define|#
directive|define
name|ngx_process_events
value|ngx_event_actions.process
end_define

begin_define
DECL|macro|ngx_add_event
define|#
directive|define
name|ngx_add_event
value|ngx_event_actions.add
end_define

begin_define
DECL|macro|ngx_del_event
define|#
directive|define
name|ngx_del_event
value|ngx_event_actions.del
end_define

begin_define
DECL|macro|ngx_add_conn
define|#
directive|define
name|ngx_add_conn
value|ngx_event_actions.add_conn
end_define

begin_define
DECL|macro|ngx_del_conn
define|#
directive|define
name|ngx_del_conn
value|ngx_event_actions.del_conn
end_define

begin_define
DECL|macro|ngx_add_timer
define|#
directive|define
name|ngx_add_timer
value|ngx_event_add_timer
end_define

begin_define
DECL|macro|ngx_del_timer
define|#
directive|define
name|ngx_del_timer
value|ngx_event_del_timer
end_define

begin_define
DECL|macro|ngx_recv
define|#
directive|define
name|ngx_recv
value|ngx_io.recv
end_define

begin_define
DECL|macro|ngx_recv_chain
define|#
directive|define
name|ngx_recv_chain
value|ngx_io.recv_chain
end_define

begin_define
DECL|macro|ngx_write_chain
define|#
directive|define
name|ngx_write_chain
value|ngx_io.send_chain
end_define

begin_define
DECL|macro|NGX_EVENT_MODULE
define|#
directive|define
name|NGX_EVENT_MODULE
value|0x544E5645
end_define

begin_comment
DECL|macro|NGX_EVENT_MODULE
comment|/* "EVNT" */
end_comment

begin_define
DECL|macro|NGX_EVENT_CONF
define|#
directive|define
name|NGX_EVENT_CONF
value|0x00200000
end_define

begin_typedef
DECL|struct|__anon2c5b19a90308
typedef|typedef
struct|struct
block|{
DECL|member|connections
name|int
name|connections
decl_stmt|;
DECL|member|timer_queues
name|int
name|timer_queues
decl_stmt|;
DECL|member|use
name|int
name|use
decl_stmt|;
DECL|typedef|ngx_event_conf_t
block|}
name|ngx_event_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2c5b19a90408
typedef|typedef
struct|struct
block|{
DECL|member|name
name|ngx_str_t
modifier|*
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
DECL|member|actions
name|ngx_event_actions_t
name|actions
decl_stmt|;
DECL|typedef|ngx_event_module_t
block|}
name|ngx_event_module_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|int
name|ngx_event_flags
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_events_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_event_core_module
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|ngx_event_get_conf (conf_ctx,module)
define|#
directive|define
name|ngx_event_get_conf
parameter_list|(
name|conf_ctx
parameter_list|,
name|module
parameter_list|)
define|\
value|(*(ngx_get_conf(conf_ctx, ngx_events_module))) [module.ctx_index];
end_define

begin_function_decl
name|void
name|ngx_event_accept
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|WIN32
operator|)
end_if

begin_function_decl
name|void
name|ngx_event_acceptex
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_event_post_acceptex
parameter_list|(
name|ngx_listening_t
modifier|*
name|ls
parameter_list|,
name|int
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<ngx_event_timer.h>
end_include

begin_if
if|#
directive|if
operator|(
name|WIN32
operator|)
end_if

begin_include
include|#
directive|include
file|<ngx_iocp_module.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_function
DECL|function|ngx_handle_read_event (ngx_event_t * rev,u_int flags)
name|ngx_inline
specifier|static
name|int
name|ngx_handle_read_event
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|,
name|u_int
name|flags
parameter_list|)
block|{
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_CLEAR_EVENT
condition|)
block|{
comment|/* kqueue */
if|if
condition|(
operator|!
name|rev
operator|->
name|active
operator|&&
operator|!
name|rev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_add_event
argument_list|(
name|rev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_CLEAR_EVENT
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
if|else if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_LEVEL_EVENT
condition|)
block|{
comment|/* select, poll, /dev/poll */
if|if
condition|(
operator|!
name|rev
operator|->
name|active
operator|&&
operator|!
name|rev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_add_event
argument_list|(
name|rev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_LEVEL_EVENT
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|rev
operator|->
name|active
operator|&&
operator|(
name|rev
operator|->
name|ready
operator|||
operator|(
name|flags
operator|&
name|NGX_CLOSE_EVENT
operator|)
operator|)
condition|)
block|{
if|if
condition|(
name|ngx_del_event
argument_list|(
name|rev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|flags
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
block|}
comment|/* aio, iocp, epoll, rt signals */
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_handle_level_read_event (ngx_event_t * rev)
name|ngx_inline
specifier|static
name|int
name|ngx_handle_level_read_event
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|)
block|{
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_LEVEL_EVENT
condition|)
block|{
if|if
condition|(
operator|!
name|rev
operator|->
name|active
operator|&&
operator|!
name|rev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_add_event
argument_list|(
name|rev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
name|NGX_LEVEL_EVENT
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|rev
operator|->
name|active
operator|&&
name|rev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_del_event
argument_list|(
name|rev
argument_list|,
name|NGX_READ_EVENT
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_handle_write_event (ngx_event_t * wev,u_int flags)
name|ngx_inline
specifier|static
name|int
name|ngx_handle_write_event
parameter_list|(
name|ngx_event_t
modifier|*
name|wev
parameter_list|,
name|u_int
name|flags
parameter_list|)
block|{
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_CLEAR_EVENT
condition|)
block|{
comment|/* kqueue */
if|if
condition|(
operator|!
name|wev
operator|->
name|active
operator|&&
operator|!
name|wev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_add_event
argument_list|(
name|wev
argument_list|,
name|NGX_WRITE_EVENT
argument_list|,
name|NGX_CLEAR_EVENT
operator||
name|flags
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
if|else if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_LEVEL_EVENT
condition|)
block|{
comment|/* select, poll, /dev/poll */
if|if
condition|(
operator|!
name|wev
operator|->
name|active
operator|&&
operator|!
name|wev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_add_event
argument_list|(
name|wev
argument_list|,
name|NGX_WRITE_EVENT
argument_list|,
name|NGX_LEVEL_EVENT
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|wev
operator|->
name|active
operator|&&
name|wev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_del_event
argument_list|(
name|wev
argument_list|,
name|NGX_WRITE_EVENT
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
block|}
comment|/* aio, iocp, epoll, rt signals */
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
DECL|function|ngx_handle_level_write_event (ngx_event_t * wev)
name|ngx_inline
specifier|static
name|int
name|ngx_handle_level_write_event
parameter_list|(
name|ngx_event_t
modifier|*
name|wev
parameter_list|)
block|{
if|if
condition|(
name|ngx_event_flags
operator|&
name|NGX_USE_LEVEL_EVENT
condition|)
block|{
if|if
condition|(
operator|!
name|wev
operator|->
name|active
operator|&&
operator|!
name|wev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_add_event
argument_list|(
name|wev
argument_list|,
name|NGX_WRITE_EVENT
argument_list|,
name|NGX_LEVEL_EVENT
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
if|if
condition|(
name|wev
operator|->
name|active
operator|&&
name|wev
operator|->
name|ready
condition|)
block|{
if|if
condition|(
name|ngx_del_event
argument_list|(
name|wev
argument_list|,
name|NGX_WRITE_EVENT
argument_list|,
literal|0
argument_list|)
operator|==
name|NGX_ERROR
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
return|return
name|NGX_OK
return|;
block|}
block|}
return|return
name|NGX_OK
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_H_INCLUDED_ */
end_comment

end_unit

