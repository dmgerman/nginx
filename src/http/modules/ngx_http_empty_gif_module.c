begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

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
file|<ngx_http.h>
end_include

begin_function_decl
specifier|static
name|char
modifier|*
name|ngx_http_empty_gif
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_http_empty_gif_commands
specifier|static
name|ngx_command_t
name|ngx_http_empty_gif_commands
index|[]
init|=
block|{
block|{
name|ngx_string
argument_list|(
literal|"empty_gif"
argument_list|)
block|,
name|NGX_HTTP_LOC_CONF
operator||
name|NGX_CONF_NOARGS
block|,
name|ngx_http_empty_gif
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

begin_comment
comment|/* the minimal single pixel transparent GIF, 43 bytes */
end_comment

begin_decl_stmt
DECL|variable|ngx_empty_gif
specifier|static
name|u_char
name|ngx_empty_gif
index|[]
init|=
block|{
literal|'G'
block|,
literal|'I'
block|,
literal|'F'
block|,
literal|'8'
block|,
literal|'9'
block|,
literal|'a'
block|,
comment|/* header                                 */
comment|/* logical screen descriptor              */
literal|0x01
block|,
literal|0x00
block|,
comment|/* logical screen width                   */
literal|0x01
block|,
literal|0x00
block|,
comment|/* logical screen height                  */
literal|0x80
block|,
comment|/* global 1-bit color table               */
literal|0x01
block|,
comment|/* background color #1                    */
literal|0x00
block|,
comment|/* no aspect ratio                        */
comment|/* global color table                     */
literal|0x00
block|,
literal|0x00
block|,
literal|0x00
block|,
comment|/* #0: black                              */
literal|0xff
block|,
literal|0xff
block|,
literal|0xff
block|,
comment|/* #1: white                              */
comment|/* graphic control extension              */
literal|0x21
block|,
comment|/* extension introducer                   */
literal|0xf9
block|,
comment|/* graphic control label                  */
literal|0x04
block|,
comment|/* block size                             */
literal|0x01
block|,
comment|/* transparent color is given,            */
comment|/*     no disposal specified,             */
comment|/*     user input is not expected         */
literal|0x00
block|,
literal|0x00
block|,
comment|/* delay time                             */
literal|0x01
block|,
comment|/* transparent color #1                   */
literal|0x00
block|,
comment|/* block terminator                       */
comment|/* image descriptor                       */
literal|0x2c
block|,
comment|/* image separator                        */
literal|0x00
block|,
literal|0x00
block|,
comment|/* image left position                    */
literal|0x00
block|,
literal|0x00
block|,
comment|/* image top position                     */
literal|0x01
block|,
literal|0x00
block|,
comment|/* image width                            */
literal|0x01
block|,
literal|0x00
block|,
comment|/* image height                           */
literal|0x00
block|,
comment|/* no local color table, no interlaced    */
comment|/* table based image data                 */
literal|0x02
block|,
comment|/* LZW minimum code size,                 */
comment|/*     must be at least 2-bit             */
literal|0x02
block|,
comment|/* block size                             */
literal|0x4c
block|,
literal|0x01
block|,
comment|/* compressed bytes 01_001_100, 0000000_1 */
comment|/* 100: clear code                        */
comment|/* 001: 1                                 */
comment|/* 101: end of information code           */
literal|0x00
block|,
comment|/* block terminator                       */
literal|0x3B
comment|/* trailer                                */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_empty_gif_module_ctx
specifier|static
name|ngx_http_module_t
name|ngx_http_empty_gif_module_ctx
init|=
block|{
name|NULL
block|,
comment|/* preconfiguration */
name|NULL
block|,
comment|/* postconfiguration */
name|NULL
block|,
comment|/* create main configuration */
name|NULL
block|,
comment|/* init main configuration */
name|NULL
block|,
comment|/* create server configuration */
name|NULL
block|,
comment|/* merge server configuration */
name|NULL
block|,
comment|/* create location configuration */
name|NULL
comment|/* merge location configuration */
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_empty_gif_module
name|ngx_module_t
name|ngx_http_empty_gif_module
init|=
block|{
name|NGX_MODULE_V1
block|,
operator|&
name|ngx_http_empty_gif_module_ctx
block|,
comment|/* module context */
name|ngx_http_empty_gif_commands
block|,
comment|/* module directives */
name|NGX_HTTP_MODULE
block|,
comment|/* module type */
name|NULL
block|,
comment|/* init master */
name|NULL
block|,
comment|/* init module */
name|NULL
block|,
comment|/* init process */
name|NULL
block|,
comment|/* init thread */
name|NULL
block|,
comment|/* exit thread */
name|NULL
block|,
comment|/* exit process */
name|NULL
block|,
comment|/* exit master */
name|NGX_MODULE_V1_PADDING
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_http_gif_type
specifier|static
name|ngx_str_t
name|ngx_http_gif_type
init|=
name|ngx_string
argument_list|(
literal|"image/gif"
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|ngx_int_t
DECL|function|ngx_http_empty_gif_handler (ngx_http_request_t * r)
name|ngx_http_empty_gif_handler
parameter_list|(
name|ngx_http_request_t
modifier|*
name|r
parameter_list|)
block|{
name|ngx_http_complex_value_t
name|cv
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|r
operator|->
name|method
operator|&
operator|(
name|NGX_HTTP_GET
operator||
name|NGX_HTTP_HEAD
operator|)
operator|)
condition|)
block|{
return|return
name|NGX_HTTP_NOT_ALLOWED
return|;
block|}
name|ngx_memzero
argument_list|(
operator|&
name|cv
argument_list|,
sizeof|sizeof
argument_list|(
name|ngx_http_complex_value_t
argument_list|)
argument_list|)
expr_stmt|;
name|cv
operator|.
name|value
operator|.
name|len
operator|=
sizeof|sizeof
argument_list|(
name|ngx_empty_gif
argument_list|)
expr_stmt|;
name|cv
operator|.
name|value
operator|.
name|data
operator|=
name|ngx_empty_gif
expr_stmt|;
name|r
operator|->
name|headers_out
operator|.
name|last_modified_time
operator|=
literal|23349600
expr_stmt|;
return|return
name|ngx_http_send_response
argument_list|(
name|r
argument_list|,
name|NGX_HTTP_OK
argument_list|,
operator|&
name|ngx_http_gif_type
argument_list|,
operator|&
name|cv
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|char
modifier|*
DECL|function|ngx_http_empty_gif (ngx_conf_t * cf,ngx_command_t * cmd,void * conf)
name|ngx_http_empty_gif
parameter_list|(
name|ngx_conf_t
modifier|*
name|cf
parameter_list|,
name|ngx_command_t
modifier|*
name|cmd
parameter_list|,
name|void
modifier|*
name|conf
parameter_list|)
block|{
name|ngx_http_core_loc_conf_t
modifier|*
name|clcf
decl_stmt|;
name|clcf
operator|=
name|ngx_http_conf_get_module_loc_conf
argument_list|(
name|cf
argument_list|,
name|ngx_http_core_module
argument_list|)
expr_stmt|;
name|clcf
operator|->
name|handler
operator|=
name|ngx_http_empty_gif_handler
expr_stmt|;
return|return
name|NGX_CONF_OK
return|;
block|}
end_function

end_unit

