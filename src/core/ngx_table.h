begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 2002-2004 Igor Sysoev  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_TABLE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_TABLE_H_INCLUDED_
define|#
directive|define
name|_NGX_TABLE_H_INCLUDED_
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
DECL|typedef|ngx_table_t
typedef|typedef
name|ngx_array_t
name|ngx_table_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon2988e0da0108
typedef|typedef
struct|struct
block|{
DECL|member|key
name|ngx_str_t
name|key
decl_stmt|;
DECL|member|value
name|ngx_str_t
name|value
decl_stmt|;
DECL|typedef|ngx_table_elt_t
block|}
name|ngx_table_elt_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_create_table (p,n)
define|#
directive|define
name|ngx_create_table
parameter_list|(
name|p
parameter_list|,
name|n
parameter_list|)
value|ngx_create_array(p, n, 2 * sizeof(ngx_str_t))
end_define

begin_define
DECL|macro|ngx_push_table (t)
define|#
directive|define
name|ngx_push_table
parameter_list|(
name|t
parameter_list|)
value|ngx_push_array(t)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_TABLE_H_INCLUDED_ */
end_comment

end_unit

