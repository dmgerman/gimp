begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* utility definitions */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|_POSIX2_RE_DUP_MAX
end_ifndef

begin_define
DECL|macro|_POSIX2_RE_DUP_MAX
define|#
directive|define
name|_POSIX2_RE_DUP_MAX
value|255
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|DUPMAX
define|#
directive|define
name|DUPMAX
value|_POSIX2_RE_DUP_MAX
end_define

begin_comment
DECL|macro|DUPMAX
comment|/* xxx is this right? */
end_comment

begin_define
DECL|macro|INFINITY
define|#
directive|define
name|INFINITY
value|(DUPMAX + 1)
end_define

begin_define
DECL|macro|NC
define|#
directive|define
name|NC
value|(CHAR_MAX - CHAR_MIN + 1)
end_define

begin_typedef
DECL|typedef|uch
typedef|typedef
name|unsigned
name|char
name|uch
typedef|;
end_typedef

begin_comment
comment|/* switch off assertions (if not already off) if no REDEBUG */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|REDEBUG
end_ifndef

begin_ifndef
ifndef|#
directive|ifndef
name|NDEBUG
end_ifndef

begin_define
DECL|macro|NDEBUG
define|#
directive|define
name|NDEBUG
end_define

begin_comment
DECL|macro|NDEBUG
comment|/* no assertions please */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<assert.h>
end_include

begin_comment
comment|/* for old systems with bcopy() but no memmove() */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|USEBCOPY
end_ifdef

begin_define
DECL|macro|memmove (d,s,c)
define|#
directive|define
name|memmove
parameter_list|(
name|d
parameter_list|,
name|s
parameter_list|,
name|c
parameter_list|)
value|bcopy(s, d, c)
end_define

begin_endif
endif|#
directive|endif
end_endif

end_unit

