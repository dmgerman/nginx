begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_PARSE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_PARSE_H_INCLUDED_
define|#
directive|define
name|_NGX_PARSE_H_INCLUDED_
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
DECL|macro|NGX_PARSE_LARGE_TIME
define|#
directive|define
name|NGX_PARSE_LARGE_TIME
value|-2
end_define

begin_function_decl
name|int
name|ngx_parse_size
parameter_list|(
name|ngx_str_t
modifier|*
name|line
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|int
name|ngx_parse_time
parameter_list|(
name|ngx_str_t
modifier|*
name|line
parameter_list|,
name|int
name|sec
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_PARSE_H_INCLUDED_ */
end_comment

end_unit

