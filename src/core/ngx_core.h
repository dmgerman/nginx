begin_unit|revision:1.0.0;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|_NGX_CORE_H_INCLUDED_
end_ifndef

begin_define
DECL|macro|_NGX_CORE_H_INCLUDED_
define|#
directive|define
name|_NGX_CORE_H_INCLUDED_
end_define

begin_define
DECL|macro|NGX_OK
define|#
directive|define
name|NGX_OK
value|0
end_define

begin_define
DECL|macro|NGX_ERROR
define|#
directive|define
name|NGX_ERROR
value|-1
end_define

begin_define
DECL|macro|NGX_AGAIN
define|#
directive|define
name|NGX_AGAIN
value|-2
end_define

begin_define
DECL|macro|NGX_DONE
define|#
directive|define
name|NGX_DONE
value|-3
end_define

begin_comment
comment|/* #define  NGX_BUSY       -3 */
end_comment

begin_define
DECL|macro|NGX_DECLINED
define|#
directive|define
name|NGX_DECLINED
value|-4
end_define

begin_comment
comment|/* #define  NGX_ALERT      -5 */
end_comment

begin_define
DECL|macro|NGX_MAXHOSTNAMELEN
define|#
directive|define
name|NGX_MAXHOSTNAMELEN
value|32
end_define

begin_comment
comment|/* #define NGX_MAXHOSTNAMELEN MAXHOSTNAMELEN */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* _NGX_CORE_H_INCLUDED_ */
end_comment

end_unit

