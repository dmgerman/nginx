begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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
DECL|macro|NGINX_VER
define|#
directive|define
name|NGINX_VER
value|"nginx/0.0.3"
end_define

begin_define
DECL|macro|NGINX_CONF
define|#
directive|define
name|NGINX_CONF
value|(u_char *) "nginx.conf"
end_define

begin_define
DECL|macro|NGINX_PID
define|#
directive|define
name|NGINX_PID
value|"nginx.pid"
end_define

begin_define
DECL|macro|NGINX_NEW_PID_EXT
define|#
directive|define
name|NGINX_NEW_PID_EXT
value|".newbin"
end_define

begin_define
DECL|macro|NGINX_NEW_PID
define|#
directive|define
name|NGINX_NEW_PID
value|NGINX_PID NGINX_NEW_PID_EXT
end_define

begin_define
DECL|macro|NGINX_VAR
define|#
directive|define
name|NGINX_VAR
value|"NGINX"
end_define

begin_decl_stmt
specifier|extern
name|ngx_module_t
name|ngx_core_module
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGINX_H_INCLUDED_ */
end_comment

end_unit

