begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COMPOSITE_UTIL_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COMPOSITE_UTIL_H__
define|#
directive|define
name|__GIMP_COMPOSITE_UTIL_H__
end_define

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d4799e0108
block|{
DECL|member|r
name|guchar
name|r
decl_stmt|;
DECL|member|g
name|guchar
name|g
decl_stmt|;
DECL|member|b
name|guchar
name|b
decl_stmt|;
DECL|member|a
name|guchar
name|a
decl_stmt|;
DECL|typedef|rgba8_t
block|}
name|rgba8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d4799e0208
block|{
DECL|member|r
name|guchar
name|r
decl_stmt|;
DECL|member|g
name|guchar
name|g
decl_stmt|;
DECL|member|b
name|guchar
name|b
decl_stmt|;
DECL|typedef|rgb8_t
block|}
name|rgb8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d4799e0308
block|{
DECL|member|v
name|guchar
name|v
decl_stmt|;
DECL|typedef|v8_t
block|}
name|v8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27d4799e0408
block|{
DECL|member|v
name|guchar
name|v
decl_stmt|;
DECL|member|a
name|guchar
name|a
decl_stmt|;
DECL|typedef|va8_t
block|}
name|va8_t
typedef|;
end_typedef

begin_decl_stmt
specifier|extern
name|int
name|gimp_composite_bpp
index|[]
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COMPOSITE_UTIL_H__ */
end_comment

end_unit

