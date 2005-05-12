begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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
DECL|macro|NGX_MAX_TEXT
define|#
directive|define
name|NGX_MAX_TEXT
value|2048
end_define

begin_function
name|void
name|__cdecl
DECL|function|ngx_message_box (char * title,ngx_uint_t type,ngx_err_t err,const char * fmt,...)
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
block|{
name|va_list
name|args
decl_stmt|;
name|u_char
name|text
index|[
name|NGX_MAX_TEXT
index|]
decl_stmt|,
modifier|*
name|p
decl_stmt|,
modifier|*
name|last
decl_stmt|;
name|last
operator|=
name|text
operator|+
name|NGX_MAX_TEXT
expr_stmt|;
name|va_start
argument_list|(
name|args
argument_list|,
name|fmt
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_vsnprintf
argument_list|(
name|text
argument_list|,
name|NGX_MAX_TEXT
argument_list|,
name|fmt
argument_list|,
name|args
argument_list|)
expr_stmt|;
name|va_end
argument_list|(
name|args
argument_list|)
expr_stmt|;
if|if
condition|(
name|err
condition|)
block|{
if|if
condition|(
name|p
operator|>
name|last
operator|-
literal|50
condition|)
block|{
comment|/* leave a space for an error code */
name|p
operator|=
name|last
operator|-
literal|50
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'.'
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'.'
expr_stmt|;
operator|*
name|p
operator|++
operator|=
literal|'.'
expr_stmt|;
block|}
if|if
condition|(
operator|(
name|unsigned
operator|)
name|err
operator|>=
literal|0x80000000
condition|)
block|{
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
literal|" (%Xd: "
argument_list|,
name|err
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|p
operator|=
name|ngx_snprintf
argument_list|(
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|,
literal|" (%d: "
argument_list|,
name|err
argument_list|)
expr_stmt|;
block|}
name|p
operator|=
name|ngx_strerror_r
argument_list|(
name|err
argument_list|,
name|p
argument_list|,
name|last
operator|-
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|<
name|last
condition|)
block|{
operator|*
name|p
operator|++
operator|=
literal|')'
expr_stmt|;
block|}
block|}
if|if
condition|(
name|p
operator|==
name|last
condition|)
block|{
name|p
operator|--
expr_stmt|;
block|}
operator|*
name|p
operator|=
literal|'\0'
expr_stmt|;
name|MessageBox
argument_list|(
name|NULL
argument_list|,
operator|(
name|char
operator|*
operator|)
name|text
argument_list|,
name|title
argument_list|,
name|type
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_system_tray_icon (HWND window,u_long action,HICON icon,u_char * tip)
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
block|{
name|NOTIFYICONDATA
name|ni
decl_stmt|;
name|ni
operator|.
name|cbSize
operator|=
sizeof|sizeof
argument_list|(
name|NOTIFYICONDATA
argument_list|)
expr_stmt|;
name|ni
operator|.
name|hWnd
operator|=
name|window
expr_stmt|;
name|ni
operator|.
name|uID
operator|=
literal|0
expr_stmt|;
name|ni
operator|.
name|uFlags
operator|=
name|NIF_MESSAGE
operator||
name|NIF_ICON
operator||
name|NIF_TIP
expr_stmt|;
name|ni
operator|.
name|uCallbackMessage
operator|=
name|NGX_WM_TRAY
expr_stmt|;
name|ni
operator|.
name|hIcon
operator|=
name|icon
expr_stmt|;
if|if
condition|(
name|tip
condition|)
block|{
name|ngx_cpystrn
argument_list|(
operator|(
name|u_char
operator|*
operator|)
name|ni
operator|.
name|szTip
argument_list|,
name|tip
argument_list|,
literal|64
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|ni
operator|.
name|szTip
index|[
literal|0
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
if|if
condition|(
name|Shell_NotifyIcon
argument_list|(
name|action
argument_list|,
operator|&
name|ni
argument_list|)
operator|==
literal|0
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
end_function

end_unit

