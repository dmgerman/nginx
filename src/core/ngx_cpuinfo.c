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

begin_if
if|#
directive|if
operator|(
operator|(
name|__i386__
operator|||
name|__amd64__
operator|)
operator|&&
operator|(
name|__GNUC__
operator|||
name|__INTEL_COMPILER
operator|)
operator|)
end_if

begin_function_decl
specifier|static
name|ngx_inline
name|void
name|ngx_cpuid
parameter_list|(
name|uint32_t
name|i
parameter_list|,
name|uint32_t
modifier|*
name|buf
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|(
name|__i386__
operator|)
end_if

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_cpuid (uint32_t i,uint32_t * buf)
name|ngx_cpuid
parameter_list|(
name|uint32_t
name|i
parameter_list|,
name|uint32_t
modifier|*
name|buf
parameter_list|)
block|{
comment|/*      * we could not use %ebx as output parameter if gcc builds PIC,      * and we could not save %ebx on stack, because %esp is used,      * when the -fomit-frame-pointer optimization is specified.      */
asm|__asm__ (      "    mov    %%ebx, %%esi;  "      "    cpuid;                "     "    mov    %%eax, (%1);   "     "    mov    %%ebx, 4(%1);  "     "    mov    %%edx, 8(%1);  "     "    mov    %%ecx, 12(%1); "      "    mov    %%esi, %%ebx;  "      : : "a" (i), "D" (buf) : "ecx", "edx", "esi", "memory" );
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_comment
comment|/* __amd64__ */
end_comment

begin_function
specifier|static
name|ngx_inline
name|void
DECL|function|ngx_cpuid (uint32_t i,uint32_t * buf)
name|ngx_cpuid
parameter_list|(
name|uint32_t
name|i
parameter_list|,
name|uint32_t
modifier|*
name|buf
parameter_list|)
block|{
name|uint32_t
name|eax
decl_stmt|,
name|ebx
decl_stmt|,
name|ecx
decl_stmt|,
name|edx
decl_stmt|;
asm|__asm__ (          "cpuid"      : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx) : "a" (i) );
name|buf
index|[
literal|0
index|]
operator|=
name|eax
expr_stmt|;
name|buf
index|[
literal|1
index|]
operator|=
name|ebx
expr_stmt|;
name|buf
index|[
literal|2
index|]
operator|=
name|edx
expr_stmt|;
name|buf
index|[
literal|3
index|]
operator|=
name|ecx
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* auto detect the L2 cache line size of modern and widespread CPUs */
end_comment

begin_function
name|void
DECL|function|ngx_cpuinfo (void)
name|ngx_cpuinfo
parameter_list|(
name|void
parameter_list|)
block|{
name|u_char
modifier|*
name|vendor
decl_stmt|;
name|uint32_t
name|vbuf
index|[
literal|5
index|]
decl_stmt|,
name|cpu
index|[
literal|4
index|]
decl_stmt|,
name|model
decl_stmt|;
name|vbuf
index|[
literal|0
index|]
operator|=
literal|0
expr_stmt|;
name|vbuf
index|[
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|vbuf
index|[
literal|2
index|]
operator|=
literal|0
expr_stmt|;
name|vbuf
index|[
literal|3
index|]
operator|=
literal|0
expr_stmt|;
name|vbuf
index|[
literal|4
index|]
operator|=
literal|0
expr_stmt|;
name|ngx_cpuid
argument_list|(
literal|0
argument_list|,
name|vbuf
argument_list|)
expr_stmt|;
name|vendor
operator|=
operator|(
name|u_char
operator|*
operator|)
operator|&
name|vbuf
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|vbuf
index|[
literal|0
index|]
operator|==
literal|0
condition|)
block|{
return|return;
block|}
name|ngx_cpuid
argument_list|(
literal|1
argument_list|,
name|cpu
argument_list|)
expr_stmt|;
if|if
condition|(
name|ngx_strcmp
argument_list|(
name|vendor
argument_list|,
literal|"GenuineIntel"
argument_list|)
operator|==
literal|0
condition|)
block|{
switch|switch
condition|(
operator|(
name|cpu
index|[
literal|0
index|]
operator|&
literal|0xf00
operator|)
operator|>>
literal|8
condition|)
block|{
comment|/* Pentium */
case|case
literal|5
case|:
name|ngx_cacheline_size
operator|=
literal|32
expr_stmt|;
break|break;
comment|/* Pentium Pro, II, III */
case|case
literal|6
case|:
name|ngx_cacheline_size
operator|=
literal|32
expr_stmt|;
name|model
operator|=
operator|(
operator|(
name|cpu
index|[
literal|0
index|]
operator|&
literal|0xf0000
operator|)
operator|>>
literal|8
operator|)
operator||
operator|(
name|cpu
index|[
literal|0
index|]
operator|&
literal|0xf0
operator|)
expr_stmt|;
if|if
condition|(
name|model
operator|>=
literal|0xd0
condition|)
block|{
comment|/* Intel Core, Core 2, Atom */
name|ngx_cacheline_size
operator|=
literal|64
expr_stmt|;
block|}
break|break;
comment|/*          * Pentium 4, although its cache line size is 64 bytes,          * it prefetches up to two cache lines during memory read          */
case|case
literal|15
case|:
name|ngx_cacheline_size
operator|=
literal|128
expr_stmt|;
break|break;
block|}
block|}
if|else if
condition|(
name|ngx_strcmp
argument_list|(
name|vendor
argument_list|,
literal|"AuthenticAMD"
argument_list|)
operator|==
literal|0
condition|)
block|{
name|ngx_cacheline_size
operator|=
literal|64
expr_stmt|;
block|}
block|}
end_function

begin_else
else|#
directive|else
end_else

begin_function
name|void
DECL|function|ngx_cpuinfo (void)
name|ngx_cpuinfo
parameter_list|(
name|void
parameter_list|)
block|{
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

end_unit

