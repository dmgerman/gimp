begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|BISON_Y_TAB_H
end_ifndef

begin_define
DECL|macro|BISON_Y_TAB_H
define|#
directive|define
name|BISON_Y_TAB_H
end_define

begin_ifndef
ifndef|#
directive|ifndef
name|YYSTYPE
end_ifndef

begin_typedef
DECL|union|__anon2b6da605010a
typedef|typedef
union|union
block|{
DECL|member|val
name|int
name|val
decl_stmt|;
DECL|member|value
name|double
name|value
decl_stmt|;
DECL|member|id
name|char
name|id
index|[
literal|256
index|]
decl_stmt|;
DECL|typedef|yystype
block|}
name|yystype
typedef|;
end_typedef

begin_define
DECL|macro|YYSTYPE
define|#
directive|define
name|YYSTYPE
value|yystype
end_define

begin_define
DECL|macro|YYSTYPE_IS_TRIVIAL
define|#
directive|define
name|YYSTYPE_IS_TRIVIAL
value|1
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|RECTANGLE
define|#
directive|define
name|RECTANGLE
value|257
end_define

begin_define
DECL|macro|POLYGON
define|#
directive|define
name|POLYGON
value|258
end_define

begin_define
DECL|macro|CIRCLE
define|#
directive|define
name|CIRCLE
value|259
end_define

begin_define
DECL|macro|DEFAULT
define|#
directive|define
name|DEFAULT
value|260
end_define

begin_define
DECL|macro|AUTHOR
define|#
directive|define
name|AUTHOR
value|261
end_define

begin_define
DECL|macro|TITLE
define|#
directive|define
name|TITLE
value|262
end_define

begin_define
DECL|macro|DESCRIPTION
define|#
directive|define
name|DESCRIPTION
value|263
end_define

begin_define
DECL|macro|BEGIN_COMMENT
define|#
directive|define
name|BEGIN_COMMENT
value|264
end_define

begin_define
DECL|macro|FLOAT
define|#
directive|define
name|FLOAT
value|265
end_define

begin_define
DECL|macro|LINK
define|#
directive|define
name|LINK
value|266
end_define

begin_define
DECL|macro|COMMENT
define|#
directive|define
name|COMMENT
value|267
end_define

begin_decl_stmt
specifier|extern
name|YYSTYPE
name|ncsa_lval
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* not BISON_Y_TAB_H */
end_comment

end_unit

