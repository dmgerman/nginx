begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  */
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

begin_function_decl
specifier|static
name|void
modifier|*
name|ngx_libc_cdecl
name|ngx_regex_malloc
parameter_list|(
name|size_t
name|size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|ngx_libc_cdecl
name|ngx_regex_free
parameter_list|(
name|void
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|ngx_pcre_pool
specifier|static
name|ngx_pool_t
modifier|*
name|ngx_pcre_pool
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|ngx_regex_init (void)
name|ngx_regex_init
parameter_list|(
name|void
parameter_list|)
block|{
name|pcre_malloc
operator|=
name|ngx_regex_malloc
expr_stmt|;
name|pcre_free
operator|=
name|ngx_regex_free
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_regex_malloc_init (ngx_pool_t * pool)
name|ngx_regex_malloc_init
parameter_list|(
name|ngx_pool_t
modifier|*
name|pool
parameter_list|)
block|{
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
name|ngx_core_tls_t
modifier|*
name|tls
decl_stmt|;
if|if
condition|(
name|ngx_threaded
condition|)
block|{
name|tls
operator|=
name|ngx_thread_get_tls
argument_list|(
name|ngx_core_tls_key
argument_list|)
expr_stmt|;
name|tls
operator|->
name|pool
operator|=
name|pool
expr_stmt|;
return|return;
block|}
endif|#
directive|endif
name|ngx_pcre_pool
operator|=
name|pool
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_regex_malloc_done (void)
name|ngx_regex_malloc_done
parameter_list|(
name|void
parameter_list|)
block|{
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
name|ngx_core_tls_t
modifier|*
name|tls
decl_stmt|;
if|if
condition|(
name|ngx_threaded
condition|)
block|{
name|tls
operator|=
name|ngx_thread_get_tls
argument_list|(
name|ngx_core_tls_key
argument_list|)
expr_stmt|;
name|tls
operator|->
name|pool
operator|=
name|NULL
expr_stmt|;
return|return;
block|}
endif|#
directive|endif
name|ngx_pcre_pool
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_regex_compile (ngx_regex_compile_t * rc)
name|ngx_regex_compile
parameter_list|(
name|ngx_regex_compile_t
modifier|*
name|rc
parameter_list|)
block|{
name|int
name|n
decl_stmt|,
name|erroff
decl_stmt|;
name|char
modifier|*
name|p
decl_stmt|;
specifier|const
name|char
modifier|*
name|errstr
decl_stmt|;
name|ngx_regex_t
modifier|*
name|re
decl_stmt|;
name|ngx_regex_malloc_init
argument_list|(
name|rc
operator|->
name|pool
argument_list|)
expr_stmt|;
name|re
operator|=
name|pcre_compile
argument_list|(
operator|(
specifier|const
name|char
operator|*
operator|)
name|rc
operator|->
name|pattern
operator|.
name|data
argument_list|,
operator|(
name|int
operator|)
name|rc
operator|->
name|options
argument_list|,
operator|&
name|errstr
argument_list|,
operator|&
name|erroff
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* ensure that there is no current pool */
name|ngx_regex_malloc_done
argument_list|()
expr_stmt|;
if|if
condition|(
name|re
operator|==
name|NULL
condition|)
block|{
if|if
condition|(
operator|(
name|size_t
operator|)
name|erroff
operator|==
name|rc
operator|->
name|pattern
operator|.
name|len
condition|)
block|{
name|rc
operator|->
name|err
operator|.
name|len
operator|=
name|ngx_snprintf
argument_list|(
name|rc
operator|->
name|err
operator|.
name|data
argument_list|,
name|rc
operator|->
name|err
operator|.
name|len
argument_list|,
literal|"pcre_compile() failed: %s in \"%V\""
argument_list|,
name|errstr
argument_list|,
operator|&
name|rc
operator|->
name|pattern
argument_list|)
operator|-
name|rc
operator|->
name|err
operator|.
name|data
expr_stmt|;
block|}
else|else
block|{
name|rc
operator|->
name|err
operator|.
name|len
operator|=
name|ngx_snprintf
argument_list|(
name|rc
operator|->
name|err
operator|.
name|data
argument_list|,
name|rc
operator|->
name|err
operator|.
name|len
argument_list|,
literal|"pcre_compile() failed: %s in \"%V\" at \"%s\""
argument_list|,
name|errstr
argument_list|,
operator|&
name|rc
operator|->
name|pattern
argument_list|,
name|rc
operator|->
name|pattern
operator|.
name|data
operator|+
name|erroff
argument_list|)
operator|-
name|rc
operator|->
name|err
operator|.
name|data
expr_stmt|;
block|}
return|return
name|NGX_ERROR
return|;
block|}
name|rc
operator|->
name|regex
operator|=
name|re
expr_stmt|;
name|n
operator|=
name|pcre_fullinfo
argument_list|(
name|re
argument_list|,
name|NULL
argument_list|,
name|PCRE_INFO_CAPTURECOUNT
argument_list|,
operator|&
name|rc
operator|->
name|captures
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|<
literal|0
condition|)
block|{
name|p
operator|=
literal|"pcre_fullinfo(\"%V\", PCRE_INFO_CAPTURECOUNT) failed: %d"
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
if|if
condition|(
name|rc
operator|->
name|captures
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|n
operator|=
name|pcre_fullinfo
argument_list|(
name|re
argument_list|,
name|NULL
argument_list|,
name|PCRE_INFO_NAMECOUNT
argument_list|,
operator|&
name|rc
operator|->
name|named_captures
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|<
literal|0
condition|)
block|{
name|p
operator|=
literal|"pcre_fullinfo(\"%V\", PCRE_INFO_NAMECOUNT) failed: %d"
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
if|if
condition|(
name|rc
operator|->
name|named_captures
operator|==
literal|0
condition|)
block|{
return|return
name|NGX_OK
return|;
block|}
name|n
operator|=
name|pcre_fullinfo
argument_list|(
name|re
argument_list|,
name|NULL
argument_list|,
name|PCRE_INFO_NAMEENTRYSIZE
argument_list|,
operator|&
name|rc
operator|->
name|name_size
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|<
literal|0
condition|)
block|{
name|p
operator|=
literal|"pcre_fullinfo(\"%V\", PCRE_INFO_NAMEENTRYSIZE) failed: %d"
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
name|n
operator|=
name|pcre_fullinfo
argument_list|(
name|re
argument_list|,
name|NULL
argument_list|,
name|PCRE_INFO_NAMETABLE
argument_list|,
operator|&
name|rc
operator|->
name|names
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|<
literal|0
condition|)
block|{
name|p
operator|=
literal|"pcre_fullinfo(\"%V\", PCRE_INFO_NAMETABLE) failed: %d"
expr_stmt|;
goto|goto
name|failed
goto|;
block|}
return|return
name|NGX_OK
return|;
name|failed
label|:
name|rc
operator|->
name|err
operator|.
name|len
operator|=
name|ngx_snprintf
argument_list|(
name|rc
operator|->
name|err
operator|.
name|data
argument_list|,
name|rc
operator|->
name|err
operator|.
name|len
argument_list|,
name|p
argument_list|,
operator|&
name|rc
operator|->
name|pattern
argument_list|,
name|n
argument_list|)
operator|-
name|rc
operator|->
name|err
operator|.
name|data
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|ngx_int_t
DECL|function|ngx_regex_exec_array (ngx_array_t * a,ngx_str_t * s,ngx_log_t * log)
name|ngx_regex_exec_array
parameter_list|(
name|ngx_array_t
modifier|*
name|a
parameter_list|,
name|ngx_str_t
modifier|*
name|s
parameter_list|,
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|ngx_int_t
name|n
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|ngx_regex_elt_t
modifier|*
name|re
decl_stmt|;
name|re
operator|=
name|a
operator|->
name|elts
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|a
operator|->
name|nelts
condition|;
name|i
operator|++
control|)
block|{
name|n
operator|=
name|ngx_regex_exec
argument_list|(
name|re
index|[
name|i
index|]
operator|.
name|regex
argument_list|,
name|s
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
if|if
condition|(
name|n
operator|==
name|NGX_REGEX_NO_MATCHED
condition|)
block|{
continue|continue;
block|}
if|if
condition|(
name|n
operator|<
literal|0
condition|)
block|{
name|ngx_log_error
argument_list|(
name|NGX_LOG_ALERT
argument_list|,
name|log
argument_list|,
literal|0
argument_list|,
name|ngx_regex_exec_n
literal|" failed: %i on \"%V\" using \"%s\""
argument_list|,
name|n
argument_list|,
name|s
argument_list|,
name|re
index|[
name|i
index|]
operator|.
name|name
argument_list|)
expr_stmt|;
return|return
name|NGX_ERROR
return|;
block|}
comment|/* match */
return|return
name|NGX_OK
return|;
block|}
return|return
name|NGX_DECLINED
return|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
name|ngx_libc_cdecl
DECL|function|ngx_regex_malloc (size_t size)
name|ngx_regex_malloc
parameter_list|(
name|size_t
name|size
parameter_list|)
block|{
name|ngx_pool_t
modifier|*
name|pool
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_THREADS
operator|)
name|ngx_core_tls_t
modifier|*
name|tls
decl_stmt|;
if|if
condition|(
name|ngx_threaded
condition|)
block|{
name|tls
operator|=
name|ngx_thread_get_tls
argument_list|(
name|ngx_core_tls_key
argument_list|)
expr_stmt|;
name|pool
operator|=
name|tls
operator|->
name|pool
expr_stmt|;
block|}
else|else
block|{
name|pool
operator|=
name|ngx_pcre_pool
expr_stmt|;
block|}
else|#
directive|else
name|pool
operator|=
name|ngx_pcre_pool
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|pool
condition|)
block|{
return|return
name|ngx_palloc
argument_list|(
name|pool
argument_list|,
name|size
argument_list|)
return|;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
specifier|static
name|void
name|ngx_libc_cdecl
DECL|function|ngx_regex_free (void * p)
name|ngx_regex_free
parameter_list|(
name|void
modifier|*
name|p
parameter_list|)
block|{
return|return;
block|}
end_function

end_unit

