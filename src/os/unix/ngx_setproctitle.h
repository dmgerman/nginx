begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_SETPROCTITLE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_SETPROCTITLE_H_INCLUDED_
define|#
directive|define
name|_NGX_SETPROCTITLE_H_INCLUDED_
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_SETPROCTITLE
operator|)
end_if

begin_comment
comment|/* FreeBSD, NetBSD, OpenBSD */
end_comment

begin_define
DECL|macro|ngx_init_setproctitle (log)
define|#
directive|define
name|ngx_init_setproctitle
parameter_list|(
name|log
parameter_list|)
end_define

begin_define
DECL|macro|ngx_setproctitle (title)
define|#
directive|define
name|ngx_setproctitle
parameter_list|(
name|title
parameter_list|)
value|setproctitle("%s", title)
end_define

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* !NGX_HAVE_SETPROCTITLE */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
name|NGX_SETPROCTITLE_USES_ENV
end_if

begin_if
if|#
directive|if
operator|(
name|NGX_SOLARIS
operator|)
end_if

begin_define
DECL|macro|NGX_SETPROCTITLE_USES_ENV
define|#
directive|define
name|NGX_SETPROCTITLE_USES_ENV
value|1
end_define

begin_define
DECL|macro|NGX_SETPROCTITLE_PAD
define|#
directive|define
name|NGX_SETPROCTITLE_PAD
value|' '
end_define

begin_function_decl
name|ngx_int_t
name|ngx_init_setproctitle
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_setproctitle
parameter_list|(
name|char
modifier|*
name|title
parameter_list|)
function_decl|;
end_function_decl

begin_elif
elif|#
directive|elif
operator|(
name|NGX_LINUX
operator|)
operator|||
operator|(
name|NGX_DARWIN
operator|)
end_elif

begin_define
DECL|macro|NGX_SETPROCTITLE_USES_ENV
define|#
directive|define
name|NGX_SETPROCTITLE_USES_ENV
value|1
end_define

begin_define
DECL|macro|NGX_SETPROCTITLE_PAD
define|#
directive|define
name|NGX_SETPROCTITLE_PAD
value|'\0'
end_define

begin_function_decl
name|ngx_int_t
name|ngx_init_setproctitle
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|ngx_setproctitle
parameter_list|(
name|char
modifier|*
name|title
parameter_list|)
function_decl|;
end_function_decl

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|ngx_init_setproctitle (log)
define|#
directive|define
name|ngx_init_setproctitle
parameter_list|(
name|log
parameter_list|)
end_define

begin_define
DECL|macro|ngx_setproctitle (title)
define|#
directive|define
name|ngx_setproctitle
parameter_list|(
name|title
parameter_list|)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* OSes */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* NGX_SETPROCTITLE_USES_ENV */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* NGX_HAVE_SETPROCTITLE */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_SETPROCTITLE_H_INCLUDED_ */
end_comment

end_unit

