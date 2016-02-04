begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Maxim Dounin  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_DLOPEN_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_DLOPEN_H_INCLUDED_
define|#
directive|define
name|_NGX_DLOPEN_H_INCLUDED_
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
DECL|macro|ngx_dlopen (path)
define|#
directive|define
name|ngx_dlopen
parameter_list|(
name|path
parameter_list|)
value|dlopen((char *) path, RTLD_NOW | RTLD_GLOBAL)
end_define

begin_define
DECL|macro|ngx_dlopen_n
define|#
directive|define
name|ngx_dlopen_n
value|"dlopen()"
end_define

begin_define
DECL|macro|ngx_dlsym (handle,symbol)
define|#
directive|define
name|ngx_dlsym
parameter_list|(
name|handle
parameter_list|,
name|symbol
parameter_list|)
value|dlsym(handle, symbol)
end_define

begin_define
DECL|macro|ngx_dlsym_n
define|#
directive|define
name|ngx_dlsym_n
value|"dlsym()"
end_define

begin_define
DECL|macro|ngx_dlclose (handle)
define|#
directive|define
name|ngx_dlclose
parameter_list|(
name|handle
parameter_list|)
value|dlclose(handle)
end_define

begin_define
DECL|macro|ngx_dlclose_n
define|#
directive|define
name|ngx_dlclose_n
value|"dlclose()"
end_define

begin_if
if|#
directive|if
operator|(
name|NGX_HAVE_DLOPEN
operator|)
end_if

begin_function_decl
name|char
modifier|*
name|ngx_dlerror
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_DLOPEN_H_INCLUDED_ */
end_comment

end_unit

