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

begin_if
if|#
directive|if
literal|0
end_if

begin_include
include|#
directive|include
file|<ngx_types.h>
end_include

begin_include
include|#
directive|include
file|<ngx_time.h>
end_include

begin_include
include|#
directive|include
file|<ngx_socket.h>
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
file|<ngx_array.h>
end_include

begin_include
include|#
directive|include
file|<ngx_conf_file.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* STUB */
end_comment

begin_define
DECL|macro|NGX_LOWAT
define|#
directive|define
name|NGX_LOWAT
value|10000
end_define

begin_define
DECL|macro|NGX_INVALID_INDEX
define|#
directive|define
name|NGX_INVALID_INDEX
value|0x80000000
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_endif
unit|typedef struct ngx_event_s       ngx_event_t;
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
end_if

begin_typedef
DECL|struct|__anon278453f40108
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
if|#
directive|if
literal|0
block|int            (*close_handler)(ngx_event_t *ev);
endif|#
directive|endif
DECL|member|context
name|void
modifier|*
name|context
decl_stmt|;
DECL|member|action
name|char
modifier|*
name|action
decl_stmt|;
DECL|member|index
name|unsigned
name|int
name|index
decl_stmt|;
DECL|member|prev
name|ngx_event_t
modifier|*
name|prev
decl_stmt|;
comment|/* queue in mutex(), aio_read(), aio_write()  */
DECL|member|next
name|ngx_event_t
modifier|*
name|next
decl_stmt|;
comment|/*                                            */
if|#
directive|if
literal|0
block|int            (*timer_handler)(ngx_event_t *ev);
endif|#
directive|endif
DECL|member|timer_prev
name|ngx_event_t
modifier|*
name|timer_prev
decl_stmt|;
DECL|member|timer_next
name|ngx_event_t
modifier|*
name|timer_next
decl_stmt|;
DECL|member|timer_delta
name|ngx_msec_t
name|timer_delta
decl_stmt|;
DECL|member|timer
name|ngx_msec_t
name|timer
decl_stmt|;
DECL|member|log
name|ngx_log_t
modifier|*
name|log
decl_stmt|;
DECL|member|available
name|int
name|available
decl_stmt|;
comment|/* kqueue only:                              */
comment|/*   accept: number of sockets that wait     */
comment|/*           to be accepted                  */
comment|/*   read:   bytes to read                   */
comment|/*   write:  available space in buffer       */
comment|/* otherwise:                                */
comment|/*   accept: 1 if accept many, 0 otherwise   */
DECL|member|oneshot
name|unsigned
name|oneshot
range|:
literal|1
decl_stmt|;
if|#
directive|if
literal|0
block|unsigned         listening:1;
endif|#
directive|endif
DECL|member|write
name|unsigned
name|write
range|:
literal|1
decl_stmt|;
DECL|member|instance
name|unsigned
name|instance
range|:
literal|1
decl_stmt|;
comment|/* used to detect stale events in kqueue,                                      rt signals and epoll */
DECL|member|active
name|unsigned
name|active
range|:
literal|1
decl_stmt|;
DECL|member|ready
name|unsigned
name|ready
range|:
literal|1
decl_stmt|;
DECL|member|timedout
name|unsigned
name|timedout
range|:
literal|1
decl_stmt|;
DECL|member|blocked
name|unsigned
name|blocked
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
DECL|member|process
name|unsigned
name|process
range|:
literal|1
decl_stmt|;
DECL|member|read_discarded
name|unsigned
name|read_discarded
range|:
literal|1
decl_stmt|;
DECL|member|ignore_econnreset
name|unsigned
name|ignore_econnreset
range|:
literal|1
decl_stmt|;
DECL|member|unexpected_eof
name|unsigned
name|unexpected_eof
range|:
literal|1
decl_stmt|;
if|#
directive|if
operator|(
name|HAVE_DEFERRED_ACCEPT
operator|)
DECL|member|deferred_accept
name|unsigned
name|deferred_accept
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
DECL|member|eof
name|unsigned
name|eof
range|:
literal|1
decl_stmt|;
DECL|member|error
name|int
name|error
decl_stmt|;
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_LOWAT_EVENT
operator|)
comment|/* kqueue's NOTE_LOWAT */
DECL|member|lowat
name|int
name|lowat
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
block|void            *thr_ctx;
comment|/* event thread context if $(CC) doesn't                                    understand __thread declaration                                    and pthread_getspecific() is too costly */
if|#
directive|if
operator|(
name|NGX_EVENT_T_PADDING
operator|)
block|int              padding[NGX_EVENT_T_PADDING];
comment|/* event should not cross                                                        cache line in SMP */
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
literal|1
end_if

begin_typedef
DECL|enum|__anon278453f40203
typedef|typedef
enum|enum
block|{
DECL|enumerator|NGX_SELECT_EVENT_N
name|NGX_SELECT_EVENT_N
init|=
literal|0
block|,
if|#
directive|if
operator|(
name|HAVE_POLL
operator|)
DECL|enumerator|NGX_POLL_EVENT_N
name|NGX_POLL_EVENT_N
block|,
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_DEVPOLL
operator|)
DECL|enumerator|NGX_DEVPOLL_EVENT_N
name|NGX_DEVPOLL_EVENT_N
block|,
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
DECL|enumerator|NGX_KQUEUE_EVENT_N
name|NGX_KQUEUE_EVENT_N
block|,
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_AIO
operator|)
DECL|enumerator|NGX_AIO_EVENT_N
name|NGX_AIO_EVENT_N
block|,
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
DECL|enumerator|NGX_IOCP_EVENT_N
name|NGX_IOCP_EVENT_N
block|,
endif|#
directive|endif
DECL|enumerator|NGX_DUMMY_EVENT_N
name|NGX_DUMMY_EVENT_N
comment|/* avoid comma at end of enumerator list */
DECL|typedef|ngx_event_type_e
block|}
name|ngx_event_type_e
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|struct|__anon278453f40308
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
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
DECL|member|done
name|void
function_decl|(
modifier|*
name|done
function_decl|)
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
DECL|typedef|ngx_event_actions_t
block|}
name|ngx_event_actions_t
typedef|;
end_typedef

begin_comment
comment|/* The event filter requires to read/write the whole data -    select, poll, /dev/poll, kqueue. */
end_comment

begin_define
DECL|macro|NGX_HAVE_LEVEL_EVENT
define|#
directive|define
name|NGX_HAVE_LEVEL_EVENT
value|0x00000001
end_define

begin_comment
comment|/* The event filter is deleted after a notification without an additional    syscall - select, poll, kqueue.  */
end_comment

begin_define
DECL|macro|NGX_HAVE_ONESHOT_EVENT
define|#
directive|define
name|NGX_HAVE_ONESHOT_EVENT
value|0x00000002
end_define

begin_comment
comment|/* The event filter notifies only the changes and an initial level - kqueue */
end_comment

begin_define
DECL|macro|NGX_HAVE_CLEAR_EVENT
define|#
directive|define
name|NGX_HAVE_CLEAR_EVENT
value|0x00000004
end_define

begin_comment
comment|/* The event filter has kqueue features - the eof flag, errno,    available data, etc */
end_comment

begin_define
DECL|macro|NGX_HAVE_KQUEUE_EVENT
define|#
directive|define
name|NGX_HAVE_KQUEUE_EVENT
value|0x00000008
end_define

begin_comment
comment|/* The event filter supports low water mark - kqueue's NOTE_LOWAT.    kqueue in FreeBSD 4.1-4.2 has no NOTE_LOWAT so we need a separate flag */
end_comment

begin_define
DECL|macro|NGX_HAVE_LOWAT_EVENT
define|#
directive|define
name|NGX_HAVE_LOWAT_EVENT
value|0x00000010
end_define

begin_comment
comment|/* The event filter notifies only the changes (the edges)    but not an initial level - epoll */
end_comment

begin_define
DECL|macro|NGX_HAVE_EDGE_EVENT
define|#
directive|define
name|NGX_HAVE_EDGE_EVENT
value|0x00000020
end_define

begin_comment
comment|/* No need to add or delete the event filters - rt signals */
end_comment

begin_define
DECL|macro|NGX_HAVE_SIGIO_EVENT
define|#
directive|define
name|NGX_HAVE_SIGIO_EVENT
value|0x00000040
end_define

begin_comment
comment|/* No need to add or delete the event filters - overlapped, aio_read, aioread */
end_comment

begin_define
DECL|macro|NGX_HAVE_AIO_EVENT
define|#
directive|define
name|NGX_HAVE_AIO_EVENT
value|0x00000080
end_define

begin_comment
comment|/* Need to add socket or handle only once - i/o completion port.    It also requires HAVE_AIO_EVENT and NGX_HAVE_AIO_EVENT to be set */
end_comment

begin_define
DECL|macro|NGX_HAVE_IOCP_EVENT
define|#
directive|define
name|NGX_HAVE_IOCP_EVENT
value|0x00000100
end_define

begin_define
DECL|macro|NGX_USE_LEVEL_EVENT
define|#
directive|define
name|NGX_USE_LEVEL_EVENT
value|0x00010000
end_define

begin_define
DECL|macro|NGX_USE_AIO_EVENT
define|#
directive|define
name|NGX_USE_AIO_EVENT
value|0x00020000
end_define

begin_comment
comment|/* Event filter is deleted before closing file.    Has no meaning for select, poll, epoll.     kqueue:     kqueue deletes event filters for file that closed                so we need only to delete filters in user-level batch array    /dev/poll:  we need to flush POLLREMOVE event before closing file */
end_comment

begin_define
DECL|macro|NGX_CLOSE_EVENT
define|#
directive|define
name|NGX_CLOSE_EVENT
value|1
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

begin_comment
comment|/* NGX_CLOSE_EVENT is the module flag and it would not go into a kernel    so we need to choose the value that would not interfere with any existent    and future flags. kqueue has such values - EV_FLAG1, EV_EOF and EV_ERROR.    They are reserved and cleared on a kernel entrance */
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

begin_ifndef
ifndef|#
directive|ifndef
name|HAVE_CLEAR_EVENT
end_ifndef

begin_define
DECL|macro|HAVE_CLEAR_EVENT
define|#
directive|define
name|HAVE_CLEAR_EVENT
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_elif
elif|#
directive|elif
operator|(
name|HAVE_POLL
operator|)
operator|||
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
comment|/* dummy */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|USE_KQUEUE
operator|)
end_if

begin_define
DECL|macro|ngx_init_events
define|#
directive|define
name|ngx_init_events
value|ngx_kqueue_init
end_define

begin_define
DECL|macro|ngx_process_events
define|#
directive|define
name|ngx_process_events
value|ngx_kqueue_process_events
end_define

begin_define
DECL|macro|ngx_add_event
define|#
directive|define
name|ngx_add_event
value|ngx_kqueue_add_event
end_define

begin_define
DECL|macro|ngx_del_event
define|#
directive|define
name|ngx_del_event
value|ngx_kqueue_del_event
end_define

begin_if
if|#
directive|if
literal|0
end_if

begin_define
define|#
directive|define
name|ngx_add_timer
value|ngx_kqueue_add_timer
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_add_timer
define|#
directive|define
name|ngx_add_timer
value|ngx_event_add_timer
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_event_recv
define|#
directive|define
name|ngx_event_recv
value|ngx_event_recv_core
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_init_events
define|#
directive|define
name|ngx_init_events
value|(ngx_event_init[ngx_event_type])
end_define

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

begin_if
if|#
directive|if
literal|0
end_if

begin_define
define|#
directive|define
name|ngx_add_timer
value|ngx_event_actions.timer
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_add_timer
define|#
directive|define
name|ngx_add_timer
value|ngx_event_add_timer
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_IOCP_EVENT
operator|)
end_if

begin_define
DECL|macro|ngx_event_recv
define|#
directive|define
name|ngx_event_recv
value|ngx_event_wsarecv
end_define

begin_elif
elif|#
directive|elif
operator|(
name|HAVE_AIO_EVENT
operator|)
end_elif

begin_define
DECL|macro|ngx_event_recv
define|#
directive|define
name|ngx_event_recv
value|ngx_event_aio_read
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_event_recv
define|#
directive|define
name|ngx_event_recv
value|ngx_io.recv
end_define

begin_define
DECL|macro|ngx_write_chain
define|#
directive|define
name|ngx_write_chain
value|ngx_io.send_chain
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|ngx_del_timer
define|#
directive|define
name|ngx_del_timer
value|ngx_event_del_timer
end_define

begin_decl_stmt
specifier|extern
name|ngx_event_t
modifier|*
name|ngx_read_events
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_event_t
modifier|*
name|ngx_write_events
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_connection_t
modifier|*
name|ngx_connections
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

begin_decl_stmt
specifier|extern
name|ngx_event_actions_t
name|ngx_event_actions
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_event_type_e
name|ngx_event_type
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|int
name|ngx_event_flags
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|!
operator|(
name|HAVE_EPOLL
operator|)
end_if

begin_define
DECL|macro|ngx_edge_add_event (ev)
define|#
directive|define
name|ngx_edge_add_event
parameter_list|(
name|ev
parameter_list|)
value|NGX_ERROR
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGX_EVENT_MODULE_TYPE
define|#
directive|define
name|NGX_EVENT_MODULE_TYPE
value|0x544E5645
end_define

begin_comment
DECL|macro|NGX_EVENT_MODULE_TYPE
comment|/* "EVNT" */
end_comment

begin_define
DECL|macro|NGX_EVENT_CONF
define|#
directive|define
name|NGX_EVENT_CONF
value|0x00200000
end_define

begin_define
DECL|macro|NGX_EVENT_MODULE
define|#
directive|define
name|NGX_EVENT_MODULE
value|0
end_define

begin_typedef
DECL|struct|__anon278453f40408
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
DECL|struct|__anon278453f40508
typedef|typedef
struct|struct
block|{
DECL|member|index
name|int
name|index
decl_stmt|;
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
name|ngx_pool_t
modifier|*
name|p
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
name|ngx_pool_t
modifier|*
name|p
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
name|ngx_module_t
name|ngx_events_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_event_module_t
name|ngx_event_module_ctx
decl_stmt|;
end_decl_stmt

begin_define
DECL|macro|ngx_event_get_conf (module)
define|#
directive|define
name|ngx_event_get_conf
parameter_list|(
name|module
parameter_list|)
define|\
value|(*(ngx_get_conf(ngx_events_module))) [module.index];
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
name|ssize_t
name|ngx_event_recv_core
parameter_list|(
name|ngx_connection_t
modifier|*
name|c
parameter_list|,
name|char
modifier|*
name|buf
parameter_list|,
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_event_close_connection
parameter_list|(
name|ngx_event_t
modifier|*
name|ev
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
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
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_worker
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_include
include|#
directive|include
file|<ngx_event_timer.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_EVENT_H_INCLUDED_ */
end_comment

end_unit

