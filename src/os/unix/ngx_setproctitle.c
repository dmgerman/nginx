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

begin_if
if|#
directive|if
operator|(
name|NGX_SETPROCTITLE_USES_ENV
operator|)
end_if

begin_comment
comment|/*  * To change the process title in Linux and Solaris we have to set argv[1]  * to NULL and to copy the title to the same place where the argv[0] points to.  * However, argv[0] may be too small to hold a new title.  Fortunately, Linux  * and Solaris store argv[] and environ[] one after another.  So we should  * ensure that is the continuous memory and then we allocate the new memory  * for environ[] and copy it.  After this we could use the memory starting  * from argv[0] for our process title.  *  * The Solaris's standard /bin/ps does not show the changed process title.  * You have to use "/usr/ucb/ps -w" instead.  Besides, the UCB ps dos not  * show a new title if its length less than the origin command line length.  * To avoid it we append to a new title the origin command line in the  * parenthesis.  */
end_comment

begin_decl_stmt
specifier|extern
name|char
modifier|*
modifier|*
name|environ
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|ngx_os_argv_last
specifier|static
name|char
modifier|*
name|ngx_os_argv_last
decl_stmt|;
end_decl_stmt

begin_function
name|ngx_int_t
DECL|function|ngx_init_setproctitle (ngx_log_t * log)
name|ngx_init_setproctitle
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
name|size_t
name|size
decl_stmt|;
name|ngx_uint_t
name|i
decl_stmt|;
name|size
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|environ
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
name|size
operator|+=
name|ngx_strlen
argument_list|(
name|environ
index|[
name|i
index|]
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|!
operator|(
name|p
operator|=
name|ngx_alloc
argument_list|(
name|size
argument_list|,
name|log
argument_list|)
operator|)
condition|)
block|{
return|return
name|NGX_ERROR
return|;
block|}
name|ngx_os_argv_last
operator|=
name|ngx_os_argv
index|[
literal|0
index|]
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|ngx_os_argv
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_os_argv_last
operator|==
name|ngx_os_argv
index|[
name|i
index|]
condition|)
block|{
name|ngx_os_argv_last
operator|=
name|ngx_os_argv
index|[
name|i
index|]
operator|+
name|ngx_strlen
argument_list|(
name|ngx_os_argv
index|[
name|i
index|]
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|environ
index|[
name|i
index|]
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|ngx_os_argv_last
operator|==
name|environ
index|[
name|i
index|]
condition|)
block|{
name|size
operator|=
name|ngx_strlen
argument_list|(
name|environ
index|[
name|i
index|]
argument_list|)
operator|+
literal|1
expr_stmt|;
name|ngx_os_argv_last
operator|=
name|environ
index|[
name|i
index|]
operator|+
name|size
expr_stmt|;
name|ngx_cpystrn
argument_list|(
name|p
argument_list|,
operator|(
name|u_char
operator|*
operator|)
name|environ
index|[
name|i
index|]
argument_list|,
name|size
argument_list|)
expr_stmt|;
name|environ
index|[
name|i
index|]
operator|=
operator|(
name|char
operator|*
operator|)
name|p
expr_stmt|;
name|p
operator|+=
name|size
expr_stmt|;
block|}
block|}
name|ngx_os_argv_last
operator|--
expr_stmt|;
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_setproctitle (char * title)
name|ngx_setproctitle
parameter_list|(
name|char
modifier|*
name|title
parameter_list|)
block|{
name|u_char
modifier|*
name|p
decl_stmt|;
if|#
directive|if
operator|(
name|NGX_SOLARIS
operator|)
name|ngx_int_t
name|i
decl_stmt|;
name|size_t
name|size
decl_stmt|;
endif|#
directive|endif
name|ngx_os_argv
index|[
literal|1
index|]
operator|=
name|NULL
expr_stmt|;
name|p
operator|=
name|ngx_cpystrn
argument_list|(
operator|(
name|u_char
operator|*
operator|)
name|ngx_os_argv
index|[
literal|0
index|]
argument_list|,
literal|"nginx: "
argument_list|,
name|ngx_os_argv_last
operator|-
name|ngx_os_argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_cpystrn
argument_list|(
name|p
argument_list|,
operator|(
name|u_char
operator|*
operator|)
name|title
argument_list|,
name|ngx_os_argv_last
operator|-
operator|(
name|char
operator|*
operator|)
name|p
argument_list|)
expr_stmt|;
if|#
directive|if
operator|(
name|NGX_SOLARIS
operator|)
name|size
operator|=
literal|0
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ngx_argc
condition|;
name|i
operator|++
control|)
block|{
name|size
operator|+=
name|ngx_strlen
argument_list|(
name|ngx_argv
index|[
name|i
index|]
argument_list|)
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
name|size
operator|>
operator|(
name|size_t
operator|)
operator|(
operator|(
name|char
operator|*
operator|)
name|p
operator|-
name|ngx_os_argv
index|[
literal|0
index|]
operator|)
condition|)
block|{
comment|/*          * ngx_setproctitle() is too rare operation so we use          * the non-optimized copies          */
name|p
operator|=
name|ngx_cpystrn
argument_list|(
name|p
argument_list|,
operator|(
name|u_char
operator|*
operator|)
literal|" ("
argument_list|,
name|ngx_os_argv_last
operator|-
operator|(
name|char
operator|*
operator|)
name|p
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|ngx_argc
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|=
name|ngx_cpystrn
argument_list|(
name|p
argument_list|,
operator|(
name|u_char
operator|*
operator|)
name|ngx_argv
index|[
name|i
index|]
argument_list|,
name|ngx_os_argv_last
operator|-
operator|(
name|char
operator|*
operator|)
name|p
argument_list|)
expr_stmt|;
name|p
operator|=
name|ngx_cpystrn
argument_list|(
name|p
argument_list|,
operator|(
name|u_char
operator|*
operator|)
literal|" "
argument_list|,
name|ngx_os_argv_last
operator|-
operator|(
name|char
operator|*
operator|)
name|p
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|*
operator|(
name|p
operator|-
literal|1
operator|)
operator|==
literal|' '
condition|)
block|{
operator|*
operator|(
name|p
operator|-
literal|1
operator|)
operator|=
literal|')'
expr_stmt|;
block|}
block|}
endif|#
directive|endif
if|if
condition|(
name|ngx_os_argv_last
operator|-
operator|(
name|char
operator|*
operator|)
name|p
condition|)
block|{
name|ngx_memset
argument_list|(
name|p
argument_list|,
name|NGX_SETPROCTITLE_PAD
argument_list|,
name|ngx_os_argv_last
operator|-
operator|(
name|char
operator|*
operator|)
name|p
argument_list|)
expr_stmt|;
block|}
name|ngx_log_debug1
argument_list|(
name|NGX_LOG_DEBUG_CORE
argument_list|,
name|ngx_cycle
operator|->
name|log
argument_list|,
literal|0
argument_list|,
literal|"setproctitle: \"%s\""
argument_list|,
name|ngx_os_argv
index|[
literal|0
index|]
argument_list|)
expr_stmt|;
block|}
end_function

begin_elif
elif|#
directive|elif
operator|!
name|defined
argument_list|(
name|ngx_setproctitle
argument_list|)
end_elif

begin_function
name|ngx_int_t
DECL|function|ngx_init_setproctitle (ngx_log_t * log)
name|ngx_init_setproctitle
parameter_list|(
name|ngx_log_t
modifier|*
name|log
parameter_list|)
block|{
return|return
name|NGX_OK
return|;
block|}
end_function

begin_function
name|void
DECL|function|ngx_setproctitle (char * title)
name|ngx_setproctitle
parameter_list|(
name|char
modifier|*
name|title
parameter_list|)
block|{
return|return;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

