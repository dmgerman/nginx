begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
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

begin_include
include|#
directive|include
file|<ngx_event.h>
end_include

begin_decl_stmt
DECL|variable|ngx_imap_commands
specifier|static
name|ngx_command_t
name|ngx_imap_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"imap"
argument_list|)
block|,
name|NGX_MAIN_CONF
operator||
name|NGX_CONF_BLOCK
operator||
name|NGX_CONF_NOARGS
block|,
name|ngx_imap_block
block|,
literal|0
block|,
literal|0
block|,
name|NULL
block|}
block|,
name|ngx_null_command
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_imap_module_ctx
specifier|static
name|ngx_core_module_t
name|ngx_imap_module_ctx
init|=
block|{
name|ngx_string
argument_list|(
literal|"imap"
argument_list|)
block|,
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_imap_module
name|ngx_module_t
name|ngx_imap_module
init|=
block|{
name|NGX_MODULE
block|,
operator|&
name|ngx_imap_module_ctx
block|,
comment|/* module context */
name|ngx_imap_commands
block|,
comment|/* module directives */
name|NGX_CORE_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init module */
name|NULL
comment|/* init child */
block|}
decl_stmt|;
end_decl_stmt

end_unit

