begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGINX_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGINX_H_INCLUDED_
define|#
directive|define
name|_NGINX_H_INCLUDED_
end_define

begin_define
DECL|macro|nginx_version
define|#
directive|define
name|nginx_version
value|1023001
end_define

begin_define
DECL|macro|NGINX_VERSION
define|#
directive|define
name|NGINX_VERSION
value|"1.23.1"
end_define

begin_define
DECL|macro|NGINX_VER
define|#
directive|define
name|NGINX_VER
value|"nginx/" NGINX_VERSION
end_define

begin_ifdef
ifdef|#
directive|ifdef
name|NGX_BUILD
end_ifdef

begin_define
DECL|macro|NGINX_VER_BUILD
define|#
directive|define
name|NGINX_VER_BUILD
value|NGINX_VER " (" NGX_BUILD ")"
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGINX_VER_BUILD
define|#
directive|define
name|NGINX_VER_BUILD
value|NGINX_VER
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|NGINX_VAR
define|#
directive|define
name|NGINX_VAR
value|"NGINX"
end_define

begin_define
DECL|macro|NGX_OLDPID_EXT
define|#
directive|define
name|NGX_OLDPID_EXT
value|".oldbin"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGINX_H_INCLUDED_ */
end_comment

end_unit

