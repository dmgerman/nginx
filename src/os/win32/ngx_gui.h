begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_GUI_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_GUI_H_INCLUDED_
define|#
directive|define
name|_NGX_GUI_H_INCLUDED_
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
file|<ngx_gui_resources.h>
end_include

begin_function_decl
name|void
name|ngx_message_box
parameter_list|(
name|char
modifier|*
name|title
parameter_list|,
name|ngx_uint_t
name|type
parameter_list|,
name|ngx_err_t
name|err
parameter_list|,
specifier|const
name|char
modifier|*
name|fmt
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_int_t
name|ngx_system_tray_icon
parameter_list|(
name|HWND
name|window
parameter_list|,
name|u_long
name|action
parameter_list|,
name|HICON
name|icon
parameter_list|,
name|u_char
modifier|*
name|tip
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_GUI_H_INCLUDED_ */
end_comment

end_unit

