begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_HTTP_CONFIG_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_HTTP_CONFIG_H_INCLUDED_
define|#
directive|define
name|_NGX_HTTP_CONFIG_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<ngx_alloc.h>
end_include

begin_include
include|#
directive|include
file|<ngx_http.h>
end_include

begin_typedef
DECL|struct|__anon289259ee0108
typedef|typedef
struct|struct
block|{
DECL|member|main_conf
name|void
modifier|*
modifier|*
name|main_conf
decl_stmt|;
DECL|member|srv_conf
name|void
modifier|*
modifier|*
name|srv_conf
decl_stmt|;
DECL|member|loc_conf
name|void
modifier|*
modifier|*
name|loc_conf
decl_stmt|;
DECL|typedef|ngx_http_conf_ctx_t
block|}
name|ngx_http_conf_ctx_t
typedef|;
end_typedef

begin_typedef
DECL|struct|__anon289259ee0208
typedef|typedef
struct|struct
block|{
DECL|member|pre_conf
name|ngx_int_t
function_decl|(
modifier|*
name|pre_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|create_main_conf
name|void
modifier|*
function_decl|(
modifier|*
name|create_main_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|init_main_conf
name|char
modifier|*
function_decl|(
modifier|*
name|init_main_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
DECL|member|create_srv_conf
name|void
modifier|*
function_decl|(
modifier|*
name|create_srv_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|merge_srv_conf
name|char
modifier|*
function_decl|(
modifier|*
name|merge_srv_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|prev
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
DECL|member|create_loc_conf
name|void
modifier|*
function_decl|(
modifier|*
name|create_loc_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|)
function_decl|;
DECL|member|merge_loc_conf
name|char
modifier|*
function_decl|(
modifier|*
name|merge_loc_conf
function_decl|)
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|void
modifier|*
name|prev
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
DECL|typedef|ngx_http_module_t
block|}
name|ngx_http_module_t
typedef|;
end_typedef

begin_define
DECL|macro|NGX_HTTP_MODULE
define|#
directive|define
name|NGX_HTTP_MODULE
value|0x50545448
end_define

begin_comment
DECL|macro|NGX_HTTP_MODULE
comment|/* "HTTP" */
end_comment

begin_define
DECL|macro|NGX_HTTP_MAIN_CONF
define|#
directive|define
name|NGX_HTTP_MAIN_CONF
value|0x02000000
end_define

begin_define
DECL|macro|NGX_HTTP_SRV_CONF
define|#
directive|define
name|NGX_HTTP_SRV_CONF
value|0x04000000
end_define

begin_define
DECL|macro|NGX_HTTP_LOC_CONF
define|#
directive|define
name|NGX_HTTP_LOC_CONF
value|0x08000000
end_define

begin_define
DECL|macro|NGX_HTTP_MAIN_CONF_OFFSET
define|#
directive|define
name|NGX_HTTP_MAIN_CONF_OFFSET
value|offsetof(ngx_http_conf_ctx_t, main_conf)
end_define

begin_define
DECL|macro|NGX_HTTP_SRV_CONF_OFFSET
define|#
directive|define
name|NGX_HTTP_SRV_CONF_OFFSET
value|offsetof(ngx_http_conf_ctx_t, srv_conf)
end_define

begin_define
DECL|macro|NGX_HTTP_LOC_CONF_OFFSET
define|#
directive|define
name|NGX_HTTP_LOC_CONF_OFFSET
value|offsetof(ngx_http_conf_ctx_t, loc_conf)
end_define

begin_define
DECL|macro|ngx_http_get_module_main_conf (r,module)
define|#
directive|define
name|ngx_http_get_module_main_conf
parameter_list|(
name|r
parameter_list|,
name|module
parameter_list|)
value|r->main_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_http_get_module_srv_conf (r,module)
define|#
directive|define
name|ngx_http_get_module_srv_conf
parameter_list|(
name|r
parameter_list|,
name|module
parameter_list|)
value|r->srv_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_http_get_module_loc_conf (r,module)
define|#
directive|define
name|ngx_http_get_module_loc_conf
parameter_list|(
name|r
parameter_list|,
name|module
parameter_list|)
value|r->loc_conf[module.ctx_index]
end_define

begin_comment
comment|/*  * ngx_http_conf_get_module_srv_conf() and ngx_http_conf_get_module_loc_conf()  * must not be used at the merge phase because cf->ctx points to http{}'s ctx  */
end_comment

begin_define
DECL|macro|ngx_http_conf_get_module_main_conf (cf,module)
define|#
directive|define
name|ngx_http_conf_get_module_main_conf
parameter_list|(
name|cf
parameter_list|,
name|module
parameter_list|)
define|\
value|((ngx_http_conf_ctx_t *) cf->ctx)->main_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_http_conf_get_module_srv_conf (cf,module)
define|#
directive|define
name|ngx_http_conf_get_module_srv_conf
parameter_list|(
name|cf
parameter_list|,
name|module
parameter_list|)
define|\
value|((ngx_http_conf_ctx_t *) cf->ctx)->srv_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_http_conf_get_module_loc_conf (cf,module)
define|#
directive|define
name|ngx_http_conf_get_module_loc_conf
parameter_list|(
name|cf
parameter_list|,
name|module
parameter_list|)
define|\
value|((ngx_http_conf_ctx_t *) cf->ctx)->loc_conf[module.ctx_index]
end_define

begin_define
DECL|macro|ngx_http_cycle_get_module_main_conf (cycle,module)
define|#
directive|define
name|ngx_http_cycle_get_module_main_conf
parameter_list|(
name|cycle
parameter_list|,
name|module
parameter_list|)
define|\
value|((ngx_http_conf_ctx_t *)                                               \            cycle->conf_ctx[ngx_http_module.index])->main_conf[module.ctx_index]
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_HTTP_CONFIG_H_INCLUDED_ */
end_comment

end_unit

