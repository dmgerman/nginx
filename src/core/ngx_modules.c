begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_core_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_errlog_module
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

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_select_module
decl_stmt|;
end_decl_stmt

begin_if
if|#
directive|if
operator|(
name|HAVE_POLL
operator|)
end_if

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_poll_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
end_if

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_kqueue_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_if
if|#
directive|if
operator|(
name|HAVE_DEVPOLL
operator|)
end_if

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_devpoll_module
decl_stmt|;
end_decl_stmt

begin_endif
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

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_iocp_module
decl_stmt|;
end_decl_stmt

begin_elif
elif|#
directive|elif
operator|(
name|HAVE_AIO
operator|)
end_elif

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_aio_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_core_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_write_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_output_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_header_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_chunked_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_gzip_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_not_modified_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_range_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_charset_filter_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_index_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_static_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_proxy_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_http_log_module
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_modules
name|ngx_module_t
modifier|*
name|ngx_modules
index|[]
init|=
block|{
comment|/* core */
operator|&
name|ngx_core_module
block|,
operator|&
name|ngx_errlog_module
block|,
comment|/* events */
operator|&
name|ngx_events_module
block|,
operator|&
name|ngx_event_core_module
block|,
operator|&
name|ngx_select_module
block|,
if|#
directive|if
operator|(
name|HAVE_POLL
operator|)
operator|&
name|ngx_poll_module
block|,
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_KQUEUE
operator|)
operator|&
name|ngx_kqueue_module
block|,
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_DEVPOLL
operator|)
operator|&
name|ngx_devpoll_module
block|,
endif|#
directive|endif
if|#
directive|if
operator|(
name|HAVE_IOCP
operator|)
operator|&
name|ngx_iocp_module
block|,
elif|#
directive|elif
operator|(
name|HAVE_AIO
operator|)
operator|&
name|ngx_aio_module
block|,
endif|#
directive|endif
comment|/* http */
operator|&
name|ngx_http_module
block|,
operator|&
name|ngx_http_core_module
block|,
operator|&
name|ngx_http_write_filter_module
block|,
operator|&
name|ngx_http_output_filter_module
block|,
operator|&
name|ngx_http_header_filter_module
block|,
operator|&
name|ngx_http_chunked_filter_module
block|,
operator|&
name|ngx_http_gzip_filter_module
block|,
operator|&
name|ngx_http_not_modified_filter_module
block|,
operator|&
name|ngx_http_range_filter_module
block|,
comment|/*&ngx_http_ssi_filter_module, */
operator|&
name|ngx_http_charset_filter_module
block|,
operator|&
name|ngx_http_index_module
block|,
comment|/*&ngx_http_static_module, */
comment|/*&ngx_http_proxy_module, */
operator|&
name|ngx_http_log_module
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

end_unit

