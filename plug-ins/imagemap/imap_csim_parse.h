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
DECL|union|__anon29fa6dc1010a
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
DECL|macro|IMG
define|#
directive|define
name|IMG
value|257
end_define

begin_define
DECL|macro|SRC
define|#
directive|define
name|SRC
value|258
end_define

begin_define
DECL|macro|WIDTH
define|#
directive|define
name|WIDTH
value|259
end_define

begin_define
DECL|macro|HEIGHT
define|#
directive|define
name|HEIGHT
value|260
end_define

begin_define
DECL|macro|BORDER
define|#
directive|define
name|BORDER
value|261
end_define

begin_define
DECL|macro|USEMAP
define|#
directive|define
name|USEMAP
value|262
end_define

begin_define
DECL|macro|START_MAP
define|#
directive|define
name|START_MAP
value|263
end_define

begin_define
DECL|macro|END_MAP
define|#
directive|define
name|END_MAP
value|264
end_define

begin_define
DECL|macro|NAME
define|#
directive|define
name|NAME
value|265
end_define

begin_define
DECL|macro|AREA
define|#
directive|define
name|AREA
value|266
end_define

begin_define
DECL|macro|SHAPE
define|#
directive|define
name|SHAPE
value|267
end_define

begin_define
DECL|macro|COORDS
define|#
directive|define
name|COORDS
value|268
end_define

begin_define
DECL|macro|ALT
define|#
directive|define
name|ALT
value|269
end_define

begin_define
DECL|macro|HREF
define|#
directive|define
name|HREF
value|270
end_define

begin_define
DECL|macro|NOHREF
define|#
directive|define
name|NOHREF
value|271
end_define

begin_define
DECL|macro|TARGET
define|#
directive|define
name|TARGET
value|272
end_define

begin_define
DECL|macro|ONMOUSEOVER
define|#
directive|define
name|ONMOUSEOVER
value|273
end_define

begin_define
DECL|macro|ONMOUSEOUT
define|#
directive|define
name|ONMOUSEOUT
value|274
end_define

begin_define
DECL|macro|ONFOCUS
define|#
directive|define
name|ONFOCUS
value|275
end_define

begin_define
DECL|macro|ONBLUR
define|#
directive|define
name|ONBLUR
value|276
end_define

begin_define
DECL|macro|AUTHOR
define|#
directive|define
name|AUTHOR
value|277
end_define

begin_define
DECL|macro|DESCRIPTION
define|#
directive|define
name|DESCRIPTION
value|278
end_define

begin_define
DECL|macro|BEGIN_COMMENT
define|#
directive|define
name|BEGIN_COMMENT
value|279
end_define

begin_define
DECL|macro|END_COMMENT
define|#
directive|define
name|END_COMMENT
value|280
end_define

begin_define
DECL|macro|FLOAT
define|#
directive|define
name|FLOAT
value|281
end_define

begin_define
DECL|macro|STRING
define|#
directive|define
name|STRING
value|282
end_define

begin_decl_stmt
specifier|extern
name|YYSTYPE
name|csim_lval
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

