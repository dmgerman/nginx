begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_GUI_RESOURCES_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_GUI_RESOURCES_H_INCLUDED_
define|#
directive|define
name|_NGX_GUI_RESOURCES_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<winuser.h>
end_include

begin_define
DECL|macro|NGX_WM_TRAY
define|#
directive|define
name|NGX_WM_TRAY
value|WM_USER
end_define

begin_define
DECL|macro|NGX_WM_EXIT
define|#
directive|define
name|NGX_WM_EXIT
value|WM_USER + 1
end_define

begin_define
DECL|macro|NGX_WM_ABOUT
define|#
directive|define
name|NGX_WM_ABOUT
value|WM_USER + 2
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_GUI_RESOURCES_H_INCLUDED_ */
end_comment

end_unit

