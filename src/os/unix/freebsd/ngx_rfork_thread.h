begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_OS_THREAD_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_OS_THREAD_H_INCLUDED_
define|#
directive|define
name|_NGX_OS_THREAD_H_INCLUDED_
end_define

begin_typedef
DECL|typedef|ngx_os_tid_t
typedef|typedef
name|int
name|ngx_os_tid_t
typedef|;
end_typedef

begin_typedef
DECL|typedef|ngx_tid_t
typedef|typedef
name|int
name|ngx_tid_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|ngx_stacks_start
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|char
modifier|*
name|ngx_stacks_end
decl_stmt|;
end_decl_stmt

begin_decl_stmt
specifier|extern
name|size_t
name|ngx_stack_size
decl_stmt|;
end_decl_stmt

begin_function
DECL|function|ngx_gettid ()
specifier|static
specifier|inline
name|ngx_tid_t
name|ngx_gettid
parameter_list|()
block|{
name|char
modifier|*
name|sp
decl_stmt|;
asm|__asm__ ("mov %%esp,%0" : "=r" (sp));
return|return
operator|(
name|sp
operator|>
name|ngx_stacks_end
operator|)
condition|?
literal|0
else|:
operator|(
name|sp
operator|-
name|ngx_stacks_start
operator|)
operator|/
name|ngx_stack_size
operator|+
literal|1
return|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_OS_THREAD_H_INCLUDED_ */
end_comment

end_unit

