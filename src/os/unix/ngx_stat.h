begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_STAT_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_STAT_H_INCLUDED_
define|#
directive|define
name|_NGX_STAT_H_INCLUDED_
end_define

begin_include
include|#
directive|include
file|<sys/types.h>
end_include

begin_include
include|#
directive|include
file|<sys/stat.h>
end_include

begin_typedef
DECL|typedef|ngx_stat_t
typedef|typedef
name|struct
name|stat
name|ngx_stat_t
typedef|;
end_typedef

begin_define
DECL|macro|ngx_is_dir (sb)
define|#
directive|define
name|ngx_is_dir
parameter_list|(
name|sb
parameter_list|)
value|(S_ISDIR(sb.st_mode))
end_define

begin_define
DECL|macro|ngx_stat (file,sb)
define|#
directive|define
name|ngx_stat
parameter_list|(
name|file
parameter_list|,
name|sb
parameter_list|)
value|stat(file, sb)
end_define

begin_define
DECL|macro|ngx_stat_n
define|#
directive|define
name|ngx_stat_n
value|"stat"
end_define

begin_define
DECL|macro|ngx_fstat (file,fd,sb)
define|#
directive|define
name|ngx_fstat
parameter_list|(
name|file
parameter_list|,
name|fd
parameter_list|,
name|sb
parameter_list|)
value|fstat(fd, sb)
end_define

begin_define
DECL|macro|ngx_fstat_n
define|#
directive|define
name|ngx_fstat_n
value|"stat"
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_STAT_H_INCLUDED_ */
end_comment

end_unit

