begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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
name|NGX_HAVE_IOCP
operator|)
end_if

begin_typedef
DECL|struct|__anon2ac19d000108
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

begin_typedef
DECL|struct|__anon2ac19d000208
typedef|typedef
struct|struct
block|{
DECL|member|lock
name|ngx_uint_t
name|lock
decl_stmt|;
DECL|member|events
name|ngx_event_t
modifier|*
name|events
decl_stmt|;
DECL|member|last
name|ngx_event_t
modifier|*
name|last
decl_stmt|;
DECL|typedef|ngx_event_mutex_t
block|}
name|ngx_event_mutex_t
typedef|;
end_typedef

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
DECL|member|write
name|unsigned
name|write
range|:
literal|1
decl_stmt|;
DECL|member|accept
name|unsigned
name|accept
range|:
literal|1
decl_stmt|;
DECL|member|oneshot
name|unsigned
name|oneshot
range|:
literal|1
decl_stmt|;
comment|/* used to detect the stale events in kqueue, rt signals and epoll */
DECL|member|instance
name|unsigned
name|instance
range|:
literal|1
decl_stmt|;
comment|/*      * the event was passed or would be passed to a kernel;      * in aio mode - operation was posted.      */
DECL|member|active
name|unsigned
name|active
range|:
literal|1
decl_stmt|;
DECL|member|disabled
name|unsigned
name|disabled
range|:
literal|1
decl_stmt|;
comment|/* the ready event; in aio mode 0 means that no operation can be posted */
DECL|member|ready
name|unsigned
name|ready
range|:
literal|1
decl_stmt|;
comment|/* aio operation is complete */
DECL|member|complete
name|unsigned
name|complete
range|:
literal|1
decl_stmt|;
DECL|member|eof
name|unsigned
name|eof
range|:
literal|1
decl_stmt|;
DECL|member|error
name|unsigned
name|error
range|:
literal|1
decl_stmt|;
DECL|member|timedout
name|unsigned
name|timedout
range|:
literal|1
decl_stmt|;
DECL|member|timer_set
name|unsigned
name|timer_set
range|:
literal|1
decl_stmt|;
DECL|member|delayed
name|unsigned
name|delayed
range|:
literal|1
decl_stmt|;
DECL|member|read_discarded
name|unsigned
name|read_discarded
range|:
literal|1
decl_stmt|;
DECL|member|unexpected_eof
name|unsigned
name|unexpected_eof
range|:
literal|1
decl_stmt|;
DECL|member|deferred_accept
name|unsigned
name|deferred_accept
range|:
literal|1
decl_stmt|;
comment|/* the pending eof reported by kqueue or in aio chain operation */
DECL|member|pending_eof
name|unsigned
name|pending_eof
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|!
operator|(
name|NGX_THREADS
operator|)
DECL|member|posted_ready
name|unsigned
name|posted_ready
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_WIN32
operator|)
comment|/* setsockopt(SO_UPDATE_ACCEPT_CONTEXT) was succesfull */
DECL|member|accept_context_updated
name|unsigned
name|accept_context_updated
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
DECL|member|kq_vnode
name|unsigned
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
comment|/*      * kqueue only:      *   accept:     number of sockets that wait to be accepted      *   read:       bytes to read when event is ready      *               or lowat when event is set with NGX_LOWAT_EVENT flag      *   write:      available space in buffer when event is ready      *               or lowat when event is set with NGX_LOWAT_EVENT flag      *      * iocp: TODO      *      * otherwise:      *   accept:     1 if accept many, 0 otherwise      */
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
operator|||
operator|(
name|NGX_HAVE_IOCP
operator|)
DECL|member|available
name|int
name|available
decl_stmt|;
else|#
directive|else
DECL|member|available
name|unsigned
name|available
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
DECL|member|handler
name|ngx_event_handler_pt
name|handler
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_AIO
operator|)
if|#
directive|if
operator|(
name|NGX_HAVE_IOCP
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
DECL|member|index
name|u_int
name|index
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|timer
name|ngx_rbtree_node_t
name|timer
decl_stmt|;
DECL|member|closed
name|unsigned
name|closed
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
DECL|member|locked
name|unsigned
name|locked
range|:
literal|1
decl_stmt|;
DECL|member|posted_ready
name|unsigned
name|posted_ready
range|:
literal|1
decl_stmt|;
DECL|member|posted_timedout
name|unsigned
name|posted_timedout
range|:
literal|1
decl_stmt|;
DECL|member|posted_eof
name|unsigned
name|posted_eof
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
comment|/* the pending errno reported by kqueue */
DECL|member|posted_errno
name|int
name|posted_errno
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_KQUEUE
operator|)
operator|||
operator|(
name|NGX_HAVE_IOCP
operator|)
DECL|member|posted_available
name|int
name|posted_available
decl_stmt|;
else|#
directive|else
DECL|member|posted_available
name|unsigned
name|posted_available
range|:
literal|1
decl_stmt|;
endif|#
directive|endif
DECL|member|lock
name|ngx_atomic_t
modifier|*
name|lock
decl_stmt|;
DECL|member|own_lock
name|ngx_atomic_t
modifier|*
name|own_lock
decl_stmt|;
endif|#
directive|endif
comment|/* the links of the posted queue */
DECL|member|next
name|ngx_event_t
modifier|*
name|next
decl_stmt|;
DECL|member|prev
name|ngx_event_t
modifier|*
modifier|*
name|prev
decl_stmt|;
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
DECL|struct|__anon2ac19d000308
typedef|typedef
struct|struct
block|{
DECL|member|add
name|ngx_int_t
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
name|ngx_int_t
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
name|ngx_int_t
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
name|ngx_int_t
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
name|ngx_int_t
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
name|ngx_int_t
function_decl|(
modifier|*
name|del_conn
function_decl|)
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
DECL|member|process_changes
name|ngx_int_t
function_decl|(
modifier|*
name|process_changes
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|,
name|ngx_uint_t
name|nowait
parameter_list|)
function_decl|;
DECL|member|process_events
name|ngx_int_t
function_decl|(
modifier|*
name|process_events
function_decl|)
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
DECL|member|init
name|ngx_int_t
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
comment|/*  * The event filter requires to read/write the whole data:  * select, poll, /dev/poll, kqueue, epoll.  */
end_comment

begin_define
DECL|macro|NGX_USE_LEVEL_EVENT
define|#
directive|define
name|NGX_USE_LEVEL_EVENT
value|0x00000001
end_define

begin_comment
comment|/*  * The event filter is deleted after a notification without an additional  * syscall: select, poll, kqueue, epoll, Solaris 10's event ports.  */
end_comment

begin_define
DECL|macro|NGX_USE_ONESHOT_EVENT
define|#
directive|define
name|NGX_USE_ONESHOT_EVENT
value|0x00000002
end_define

begin_comment
comment|/*  * The event filter notifies only the changes and an initial level:  * kqueue, epoll.  */
end_comment

begin_define
DECL|macro|NGX_USE_CLEAR_EVENT
define|#
directive|define
name|NGX_USE_CLEAR_EVENT
value|0x00000004
end_define

begin_comment
comment|/*  * The event filter has kqueue features: the eof flag, errno,  * available data, etc.  */
end_comment

begin_define
DECL|macro|NGX_USE_KQUEUE_EVENT
define|#
directive|define
name|NGX_USE_KQUEUE_EVENT
value|0x00000008
end_define

begin_comment
comment|/*  * The event filter supports low water mark: kqueue's NOTE_LOWAT.  * kqueue in FreeBSD 4.1-4.2 has no NOTE_LOWAT so we need a separate flag.  */
end_comment

begin_define
DECL|macro|NGX_USE_LOWAT_EVENT
define|#
directive|define
name|NGX_USE_LOWAT_EVENT
value|0x00000010
end_define

begin_comment
comment|/*  * The event filter requires to do i/o operation until EAGAIN:  * epoll, rt signals.  */
end_comment

begin_define
DECL|macro|NGX_USE_GREEDY_EVENT
define|#
directive|define
name|NGX_USE_GREEDY_EVENT
value|0x00000020
end_define

begin_comment
comment|/*  * The event filter is epoll.  */
end_comment

begin_define
DECL|macro|NGX_USE_EPOLL_EVENT
define|#
directive|define
name|NGX_USE_EPOLL_EVENT
value|0x00000040
end_define

begin_comment
comment|/*  * No need to add or delete the event filters: rt signals.  */
end_comment

begin_define
DECL|macro|NGX_USE_RTSIG_EVENT
define|#
directive|define
name|NGX_USE_RTSIG_EVENT
value|0x00000080
end_define

begin_comment
comment|/*  * No need to add or delete the event filters: overlapped, aio_read,  * aioread, io_submit.  */
end_comment

begin_define
DECL|macro|NGX_USE_AIO_EVENT
define|#
directive|define
name|NGX_USE_AIO_EVENT
value|0x00000100
end_define

begin_comment
comment|/*  * Need to add socket or handle only once: i/o completion port.  * It also requires NGX_HAVE_AIO and NGX_USE_AIO_EVENT to be set.  */
end_comment

begin_define
DECL|macro|NGX_USE_IOCP_EVENT
define|#
directive|define
name|NGX_USE_IOCP_EVENT
value|0x00000200
end_define

begin_comment
comment|/*  * The event filter has no opaque data and requires file descriptors table:  * poll, /dev/poll, rt signals.  */
end_comment

begin_define
DECL|macro|NGX_USE_FD_EVENT
define|#
directive|define
name|NGX_USE_FD_EVENT
value|0x00000400
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

begin_define
DECL|macro|NGX_DISABLE_EVENT
define|#
directive|define
name|NGX_DISABLE_EVENT
value|2
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
name|NGX_HAVE_KQUEUE
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
name|NGX_HAVE_DEVPOLL
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
name|NGX_HAVE_EPOLL
operator|)
end_elif

begin_define
DECL|macro|NGX_READ_EVENT
define|#
directive|define
name|NGX_READ_EVENT
value|EPOLLIN
end_define

begin_define
DECL|macro|NGX_WRITE_EVENT
define|#
directive|define
name|NGX_WRITE_EVENT
value|EPOLLOUT
end_define

begin_define
DECL|macro|NGX_LEVEL_EVENT
define|#
directive|define
name|NGX_LEVEL_EVENT
value|0
end_define

begin_define
DECL|macro|NGX_CLEAR_EVENT
define|#
directive|define
name|NGX_CLEAR_EVENT
value|EPOLLET
end_define

begin_define
DECL|macro|NGX_ONESHOT_EVENT
define|#
directive|define
name|NGX_ONESHOT_EVENT
value|0x70000000
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_define
define|#
directive|define
name|NGX_ONESHOT_EVENT
value|EPOLLONESHOT
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_elif
elif|#
directive|elif
operator|(
name|NGX_HAVE_POLL
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
comment|/* NGX_HAVE_KQUEUE */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_IOCP
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
DECL|macro|ngx_process_changes
define|#
directive|define
name|ngx_process_changes
value|ngx_event_actions.process_changes
end_define

begin_define
DECL|macro|ngx_process_events
define|#
directive|define
name|ngx_process_events
value|ngx_event_actions.process_events
end_define

begin_define
DECL|macro|ngx_done_events
define|#
directive|define
name|ngx_done_events
value|ngx_event_actions.done
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

begin_decl_stmt
specifier|extern
name|ngx_os_io_t
name|ngx_io
decl_stmt|;
end_decl_stmt

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
DECL|macro|ngx_send
define|#
directive|define
name|ngx_send
value|ngx_io.send
end_define

begin_define
DECL|macro|ngx_send_chain
define|#
directive|define
name|ngx_send_chain
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
value|0x02000000
end_define

begin_typedef
DECL|struct|__anon2ac19d000408
typedef|typedef
struct|struct
block|{
DECL|member|connections
name|ngx_uint_t
name|connections
decl_stmt|;
DECL|member|use
name|ngx_uint_t
name|use
decl_stmt|;
DECL|member|multi_accept
name|ngx_flag_t
name|multi_accept
decl_stmt|;
DECL|member|accept_mutex
name|ngx_flag_t
name|accept_mutex
decl_stmt|;
DECL|member|accept_mutex_delay
name|ngx_msec_t
name|accept_mutex_delay
decl_stmt|;
DECL|member|name
name|u_char
modifier|*
name|name
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
DECL|member|debug_connection
name|ngx_array_t
name|debug_connection
decl_stmt|;
endif|#
directive|endif
DECL|typedef|ngx_event_conf_t
block|}
name|ngx_event_conf_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2ac19d000508
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
name|ngx_atomic_t
modifier|*
name|ngx_connection_counter
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_accept_mutex_ptr
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_accept_mutex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_accept_mutex_held
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_msec_t
name|ngx_accept_mutex_delay
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_int_t
name|ngx_accept_disabled
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|(
name|NGX_STAT_STUB
operator|)
end_if

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_stat_accepted
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_stat_handled
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_stat_requests
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_stat_active
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_stat_reading
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_stat_writing
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_accept_mutex_unlock ()
define|#
directive|define
name|ngx_accept_mutex_unlock
parameter_list|()
define|\
value|if (ngx_accept_mutex_held) {                                       \                *ngx_accept_mutex = 0;                                         \            }
end_define

begin_decl_stmt
specifier|extern
name|ngx_uint_t
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

begin_function_decl
name|ngx_int_t
name|ngx_trylock_accept_mutex
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_disable_accept_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_enable_accept_events
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_accept_log_error
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_handle_read_event
parameter_list|(
name|ngx_event_t
modifier|*
name|rev
parameter_list|,
name|u_int
name|flags
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_handle_write_event
parameter_list|(
name|ngx_event_t
modifier|*
name|wev
parameter_list|,
name|size_t
name|lowat
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|NGX_WIN32
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
name|ngx_int_t
name|ngx_event_post_acceptex
parameter_list|(
name|ngx_listening_t
modifier|*
name|ls
parameter_list|,
name|ngx_uint_t
name|n
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|u_char
modifier|*
name|ngx_acceptex_log_error
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|,
name|u_char
modifier|*
name|buf
parameter_list|,
name|size_t
name|len
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|ngx_int_t
name|ngx_send_lowat
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|size_t
name|lowat
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* used in ngx_log_debugX() */
end_comment

begin_define
DECL|macro|ngx_event_ident (p)
define|#
directive|define
name|ngx_event_ident
parameter_list|(
name|p
parameter_list|)
value|((ngx_connection_t *) (p))->fd
end_define

begin_include
include|#
directive|include
file|<ngx_event_timer.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_posted.h>
end_include

begin_include
include|#
directive|include
file|<ngx_event_busy_lock.h>
end_include

begin_if
if|#
directive|if
operator|(
name|NGX_WIN32
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_H_INCLUDED_ */
end_comment

end_unit

