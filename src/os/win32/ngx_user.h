begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_USER_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_USER_H_INCLUDED_
define|#
directive|define
name|_NGX_USER_H_INCLUDED_
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

begin_comment
comment|/* STUB */
end_comment

begin_define
DECL|macro|ngx_uid_t
define|#
directive|define
name|ngx_uid_t
value|ngx_int_t
end_define

begin_define
DECL|macro|ngx_gid_t
define|#
directive|define
name|ngx_gid_t
value|ngx_int_t
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_USER_H_INCLUDED_ */
end_comment

end_unit

