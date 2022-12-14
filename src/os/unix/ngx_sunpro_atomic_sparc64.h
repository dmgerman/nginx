begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) Igor Sysoev  * Copyright (C) Nginx, Inc.  */
end_comment

begin_if
if|#
directive|if
operator|(
name|NGX_PTR_SIZE
operator|==
literal|4
operator|)
end_if

begin_define
DECL|macro|NGX_CASA
define|#
directive|define
name|NGX_CASA
value|ngx_casa
end_define

begin_else
else|#
directive|else
end_else

begin_define
DECL|macro|NGX_CASA
define|#
directive|define
name|NGX_CASA
value|ngx_casxa
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
name|ngx_atomic_uint_t
name|ngx_casa
parameter_list|(
name|ngx_atomic_uint_t
name|set
parameter_list|,
name|ngx_atomic_uint_t
name|old
parameter_list|,
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|ngx_atomic_uint_t
name|ngx_casxa
parameter_list|(
name|ngx_atomic_uint_t
name|set
parameter_list|,
name|ngx_atomic_uint_t
name|old
parameter_list|,
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* the code in src/os/unix/ngx_sunpro_sparc64.il */
end_comment

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_uint_t
DECL|function|ngx_atomic_cmp_set (ngx_atomic_t * lock,ngx_atomic_uint_t old,ngx_atomic_uint_t set)
name|ngx_atomic_cmp_set
parameter_list|(
name|ngx_atomic_t
modifier|*
name|lock
parameter_list|,
name|ngx_atomic_uint_t
name|old
parameter_list|,
name|ngx_atomic_uint_t
name|set
parameter_list|)
block|{
name|set
operator|=
name|NGX_CASA
argument_list|(
name|set
argument_list|,
name|old
argument_list|,
name|lock
argument_list|)
expr_stmt|;
return|return
operator|(
name|set
operator|==
name|old
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|ngx_inline
name|ngx_atomic_int_t
DECL|function|ngx_atomic_fetch_add (ngx_atomic_t * value,ngx_atomic_int_t add)
name|ngx_atomic_fetch_add
parameter_list|(
name|ngx_atomic_t
modifier|*
name|value
parameter_list|,
name|ngx_atomic_int_t
name|add
parameter_list|)
block|{
name|ngx_atomic_uint_t
name|old
decl_stmt|,
name|res
decl_stmt|;
name|old
operator|=
operator|*
name|value
expr_stmt|;
for|for
control|(
init|;
condition|;
control|)
block|{
name|res
operator|=
name|old
operator|+
name|add
expr_stmt|;
name|res
operator|=
name|NGX_CASA
argument_list|(
name|res
argument_list|,
name|old
argument_list|,
name|value
argument_list|)
expr_stmt|;
if|if
condition|(
name|res
operator|==
name|old
condition|)
block|{
return|return
name|res
return|;
block|}
name|old
operator|=
name|res
expr_stmt|;
block|}
block|}
end_function

begin_define
DECL|macro|ngx_memory_barrier ()
define|#
directive|define
name|ngx_memory_barrier
parameter_list|()
define|\
value|__asm (".volatile");                                                  \         __asm ("membar #LoadLoad | #LoadStore | #StoreStore | #StoreLoad");   \         __asm (".nonvolatile")
end_define

begin_define
DECL|macro|ngx_cpu_pause ()
define|#
directive|define
name|ngx_cpu_pause
parameter_list|()
end_define

end_unit

