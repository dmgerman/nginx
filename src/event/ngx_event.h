begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
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
DECL|struct|__anon28e954d80108
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
comment|/* used to detect the stale events in kqueue and epoll */
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
DECL|member|oneshot
name|unsigned
name|oneshot
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
DECL|member|deferred_accept
name|unsigned
name|deferred_accept
range|:
literal|1
decl_stmt|;
comment|/* the pending eof reported by kqueue, epoll or in aio chain operation */
DECL|member|pending_eof
name|unsigned
name|pending_eof
range|:
literal|1
decl_stmt|;
DECL|member|posted
name|unsigned
name|posted
range|:
literal|1
decl_stmt|;
DECL|member|closed
name|unsigned
name|closed
range|:
literal|1
decl_stmt|;
comment|/* to test on worker exit */
DECL|member|channel
name|unsigned
name|channel
range|:
literal|1
decl_stmt|;
DECL|member|resolver
name|unsigned
name|resolver
range|:
literal|1
decl_stmt|;
DECL|member|cancelable
name|unsigned
name|cancelable
range|:
literal|1
decl_stmt|;
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
comment|/*      * kqueue only:      *   accept:     number of sockets that wait to be accepted      *   read:       bytes to read when event is ready      *               or lowat when event is set with NGX_LOWAT_EVENT flag      *   write:      available space in buffer when event is ready      *               or lowat when event is set with NGX_LOWAT_EVENT flag      *      * epoll with EPOLLRDHUP:      *   accept:     1 if accept many, 0 otherwise      *   read:       1 if there can be data to read, 0 otherwise      *      * iocp: TODO      *      * otherwise:      *   accept:     1 if accept many, 0 otherwise      */
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
name|NGX_HAVE_IOCP
operator|)
DECL|member|ovlp
name|ngx_event_ovlp_t
name|ovlp
decl_stmt|;
endif|#
directive|endif
DECL|member|index
name|ngx_uint_t
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
comment|/* the posted queue */
DECL|member|queue
name|ngx_queue_t
name|queue
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
block|uint32_t         padding[NGX_EVENT_T_PADDING];
endif|#
directive|endif
endif|#
directive|endif
block|}
struct|;
end_struct

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_FILE_AIO
operator|)
end_if

begin_struct
DECL|struct|ngx_event_aio_s
struct|struct
name|ngx_event_aio_s
block|{
DECL|member|data
name|void
modifier|*
name|data
decl_stmt|;
DECL|member|handler
name|ngx_event_handler_pt
name|handler
decl_stmt|;
DECL|member|file
name|ngx_file_t
modifier|*
name|file
decl_stmt|;
DECL|member|fd
name|ngx_fd_t
name|fd
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_HAVE_AIO_SENDFILE
operator|||
name|NGX_COMPAT
operator|)
DECL|member|preload_handler
name|ssize_t
function_decl|(
modifier|*
name|preload_handler
function_decl|)
parameter_list|(
name|ngx_buf_t
modifier|*
name|file
parameter_list|)
function_decl|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|NGX_HAVE_EVENTFD
operator|)
DECL|member|res
name|int64_t
name|res
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|!
operator|(
name|NGX_HAVE_EVENTFD
operator|)
operator|||
operator|(
name|NGX_TEST_BUILD_EPOLL
operator|)
DECL|member|err
name|ngx_err_t
name|err
decl_stmt|;
DECL|member|nbytes
name|size_t
name|nbytes
decl_stmt|;
endif|#
directive|endif
DECL|member|aiocb
name|ngx_aiocb_t
name|aiocb
decl_stmt|;
DECL|member|event
name|ngx_event_t
name|event
decl_stmt|;
block|}
struct|;
end_struct

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon28e954d80208
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
name|ngx_int_t
name|event
parameter_list|,
name|ngx_uint_t
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
name|ngx_int_t
name|event
parameter_list|,
name|ngx_uint_t
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
name|ngx_int_t
name|event
parameter_list|,
name|ngx_uint_t
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
name|ngx_int_t
name|event
parameter_list|,
name|ngx_uint_t
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
name|ngx_uint_t
name|flags
parameter_list|)
function_decl|;
DECL|member|notify
name|ngx_int_t
function_decl|(
modifier|*
name|notify
function_decl|)
parameter_list|(
name|ngx_event_handler_pt
name|handler
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
parameter_list|,
name|ngx_msec_t
name|timer
parameter_list|,
name|ngx_uint_t
name|flags
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
parameter_list|,
name|ngx_msec_t
name|timer
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_EPOLLRDHUP
operator|)
end_if

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_use_epoll_rdhup
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

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
comment|/*  * The event filter is deleted after a notification without an additional  * syscall: kqueue, epoll.  */
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
comment|/*  * The event filter requires to do i/o operation until EAGAIN: epoll.  */
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
comment|/*  * Obsolete.  */
end_comment

begin_define
DECL|macro|NGX_USE_RTSIG_EVENT
define|#
directive|define
name|NGX_USE_RTSIG_EVENT
value|0x00000080
end_define

begin_comment
comment|/*  * Obsolete.  */
end_comment

begin_define
DECL|macro|NGX_USE_AIO_EVENT
define|#
directive|define
name|NGX_USE_AIO_EVENT
value|0x00000100
end_define

begin_comment
comment|/*  * Need to add socket or handle only once: i/o completion port.  */
end_comment

begin_define
DECL|macro|NGX_USE_IOCP_EVENT
define|#
directive|define
name|NGX_USE_IOCP_EVENT
value|0x00000200
end_define

begin_comment
comment|/*  * The event filter has no opaque data and requires file descriptors table:  * poll, /dev/poll.  */
end_comment

begin_define
DECL|macro|NGX_USE_FD_EVENT
define|#
directive|define
name|NGX_USE_FD_EVENT
value|0x00000400
end_define

begin_comment
comment|/*  * The event module handles periodic or absolute timer event by itself:  * kqueue in FreeBSD 4.4, NetBSD 2.0, and MacOSX 10.4, Solaris 10's event ports.  */
end_comment

begin_define
DECL|macro|NGX_USE_TIMER_EVENT
define|#
directive|define
name|NGX_USE_TIMER_EVENT
value|0x00000800
end_define

begin_comment
comment|/*  * All event filters on file descriptor are deleted after a notification:  * Solaris 10's event ports.  */
end_comment

begin_define
DECL|macro|NGX_USE_EVENTPORT_EVENT
define|#
directive|define
name|NGX_USE_EVENTPORT_EVENT
value|0x00001000
end_define

begin_comment
comment|/*  * The event filter support vnode notifications: kqueue.  */
end_comment

begin_define
DECL|macro|NGX_USE_VNODE_EVENT
define|#
directive|define
name|NGX_USE_VNODE_EVENT
value|0x00002000
end_define

begin_comment
comment|/*  * The event filter is deleted just before the closing file.  * Has no meaning for select and poll.  * kqueue, epoll, eventport:         allows to avoid explicit delete,  *                                   because filter automatically is deleted  *                                   on file close,  *  * /dev/poll:                        we need to flush POLLREMOVE event  *                                   before closing file.  */
end_comment

begin_define
DECL|macro|NGX_CLOSE_EVENT
define|#
directive|define
name|NGX_CLOSE_EVENT
value|1
end_define

begin_comment
comment|/*  * disable temporarily event filter, this may avoid locks  * in kernel malloc()/free(): kqueue.  */
end_comment

begin_define
DECL|macro|NGX_DISABLE_EVENT
define|#
directive|define
name|NGX_DISABLE_EVENT
value|2
end_define

begin_comment
comment|/*  * event must be passed to kernel right now, do not wait until batch processing.  */
end_comment

begin_define
DECL|macro|NGX_FLUSH_EVENT
define|#
directive|define
name|NGX_FLUSH_EVENT
value|4
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
name|NGX_HAVE_EPOLL
operator|)
operator|&&
operator|!
operator|(
name|NGX_HAVE_EPOLLRDHUP
operator|)
end_if

begin_define
DECL|macro|EPOLLRDHUP
define|#
directive|define
name|EPOLLRDHUP
value|0
end_define

begin_endif
endif|#
directive|endif
end_endif

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
comment|/*  * NGX_CLOSE_EVENT, NGX_LOWAT_EVENT, and NGX_FLUSH_EVENT are the module flags  * and they must not go into a kernel so we need to choose the value  * that must not interfere with any existent and future kqueue flags.  * kqueue has such values - EV_FLAG1, EV_EOF, and EV_ERROR:  * they are reserved and cleared on a kernel entrance.  */
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

begin_undef
undef|#
directive|undef
name|NGX_FLUSH_EVENT
end_undef

begin_define
DECL|macro|NGX_FLUSH_EVENT
define|#
directive|define
name|NGX_FLUSH_EVENT
value|EV_ERROR
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
operator|&&
operator|!
operator|(
name|NGX_TEST_BUILD_DEVPOLL
operator|)
operator|)
expr|\
operator|||
operator|(
name|NGX_HAVE_EVENTPORT
operator|&&
operator|!
operator|(
name|NGX_TEST_BUILD_EVENTPORT
operator|)
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
operator|&&
operator|!
operator|(
name|NGX_TEST_BUILD_EPOLL
operator|)
end_elif

begin_define
DECL|macro|NGX_READ_EVENT
define|#
directive|define
name|NGX_READ_EVENT
value|(EPOLLIN|EPOLLRDHUP)
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

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_EPOLLEXCLUSIVE
operator|)
end_if

begin_define
DECL|macro|NGX_EXCLUSIVE_EVENT
define|#
directive|define
name|NGX_EXCLUSIVE_EVENT
value|EPOLLEXCLUSIVE
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

begin_if
if|#
directive|if
operator|(
name|NGX_TEST_BUILD_EPOLL
operator|)
end_if

begin_define
DECL|macro|NGX_EXCLUSIVE_EVENT
define|#
directive|define
name|NGX_EXCLUSIVE_EVENT
value|0
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
DECL|macro|ngx_notify
define|#
directive|define
name|ngx_notify
value|ngx_event_actions.notify
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
DECL|macro|ngx_udp_recv
define|#
directive|define
name|ngx_udp_recv
value|ngx_io.udp_recv
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
DECL|macro|ngx_udp_send
define|#
directive|define
name|ngx_udp_send
value|ngx_io.udp_send
end_define

begin_define
DECL|macro|ngx_udp_send_chain
define|#
directive|define
name|ngx_udp_send_chain
value|ngx_io.udp_send_chain
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
DECL|struct|__anon28e954d80308
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
DECL|struct|__anon28e954d80408
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
name|ngx_shmtx_t
name|ngx_accept_mutex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_use_accept_mutex
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_uint_t
name|ngx_accept_events
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

begin_decl_stmt
specifier|extern
name|ngx_atomic_t
modifier|*
name|ngx_stat_waiting
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_UPDATE_TIME
define|#
directive|define
name|NGX_UPDATE_TIME
value|1
end_define

begin_define
DECL|macro|NGX_POST_EVENTS
define|#
directive|define
name|NGX_POST_EVENTS
value|2
end_define

begin_decl_stmt
specifier|extern
name|sig_atomic_t
name|ngx_event_timer_alarm
decl_stmt|;
end_decl_stmt

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
value|(*(ngx_get_conf(conf_ctx, ngx_events_module))) [module.ctx_index]
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
operator|!
operator|(
name|NGX_WIN32
operator|)
end_if

begin_function_decl
name|void
name|ngx_event_recvmsg
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_udp_rbtree_insert_value
parameter_list|(
name|ngx_rbtree_node_t
modifier|*
name|temp
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|node
parameter_list|,
name|ngx_rbtree_node_t
modifier|*
name|sentinel
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_delete_udp_connection
parameter_list|(
name|void
modifier|*
name|data
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

begin_if
if|#
directive|if
operator|(
name|NGX_DEBUG
operator|)
end_if

begin_function_decl
name|void
name|ngx_debug_accepted_connection
parameter_list|(
name|ngx_event_conf_t
modifier|*
name|ecf
parameter_list|,
name|ngx_connection_t
modifier|*
name|c
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|void
name|ngx_process_events_and_timers
parameter_list|(
name|ngx_cycle_t
modifier|*
name|cycle
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
name|ngx_uint_t
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

