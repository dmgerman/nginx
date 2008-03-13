begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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
DECL|macro|NGINX_VERSION
define|#
directive|define
name|NGINX_VERSION
value|"0.6.29"
end_define

begin_define
DECL|macro|NGINX_VER
define|#
directive|define
name|NGINX_VER
value|"nginx/" NGINX_VERSION
end_define

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

