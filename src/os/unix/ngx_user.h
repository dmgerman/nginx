begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
end_comment

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

begin_typedef
DECL|typedef|ngx_uid_t
typedef|typedef
name|uid_t
name|ngx_uid_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_gid_t
typedef|typedef
name|gid_t
name|ngx_gid_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_USER_H_INCLUDED_ */
end_comment

end_unit

