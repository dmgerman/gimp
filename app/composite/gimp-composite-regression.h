begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|gimp_composite_regression_h
end_ifndef

begin_define
DECL|macro|gimp_composite_regression_h
define|#
directive|define
name|gimp_composite_regression_h
end_define

begin_comment
comment|/*  * The following typedefs are temporary and only used in regression testing. 	*/
end_comment

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0108
block|{
DECL|member|v
name|guint8
name|v
decl_stmt|;
DECL|typedef|gimp_v8_t
block|}
name|gimp_v8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0208
block|{
DECL|member|v
name|guint8
name|v
decl_stmt|;
DECL|member|a
name|guint8
name|a
decl_stmt|;
DECL|typedef|gimp_va8_t
block|}
name|gimp_va8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0308
block|{
DECL|member|r
name|guint8
name|r
decl_stmt|;
DECL|member|g
name|guint8
name|g
decl_stmt|;
DECL|member|b
name|guint8
name|b
decl_stmt|;
DECL|typedef|gimp_rgb8_t
block|}
name|gimp_rgb8_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0408
block|{
DECL|member|r
name|guint8
name|r
decl_stmt|;
DECL|member|g
name|guint8
name|g
decl_stmt|;
DECL|member|b
name|guint8
name|b
decl_stmt|;
DECL|member|a
name|guint8
name|a
decl_stmt|;
DECL|typedef|gimp_rgba8_t
block|}
name|gimp_rgba8_t
typedef|;
end_typedef

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_COMPOSIE_16BIT
end_ifdef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0508
block|{
DECL|member|v
name|guint16
name|v
decl_stmt|;
DECL|typedef|gimp_v16_t
block|}
name|gimp_v16_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0608
block|{
DECL|member|v
name|guint16
name|v
decl_stmt|;
DECL|member|a
name|guint16
name|a
decl_stmt|;
DECL|typedef|gimp_va16_t
block|}
name|gimp_va16_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0708
block|{
DECL|member|r
name|guint16
name|r
decl_stmt|;
DECL|member|g
name|guint16
name|g
decl_stmt|;
DECL|member|b
name|guint16
name|b
decl_stmt|;
DECL|typedef|gimp_rgb16_t
block|}
name|gimp_rgb16_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0808
block|{
DECL|member|r
name|guint16
name|r
decl_stmt|;
DECL|member|g
name|guint16
name|g
decl_stmt|;
DECL|member|b
name|guint16
name|b
decl_stmt|;
DECL|member|a
name|guint16
name|a
decl_stmt|;
DECL|typedef|gimp_rgba16_t
block|}
name|gimp_rgba16_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_ifdef
ifdef|#
directive|ifdef
name|GIMP_COMPOSIE_32BIT
end_ifdef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0908
block|{
DECL|member|v
name|guint32
name|v
decl_stmt|;
DECL|typedef|gimp_v32_t
block|}
name|gimp_v32_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0a08
block|{
DECL|member|v
name|guint32
name|v
decl_stmt|;
DECL|member|a
name|guint32
name|a
decl_stmt|;
DECL|typedef|gimp_va32_t
block|}
name|gimp_va32_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0b08
block|{
DECL|member|r
name|guint32
name|r
decl_stmt|;
DECL|member|g
name|guint32
name|g
decl_stmt|;
DECL|member|b
name|guint32
name|b
decl_stmt|;
DECL|typedef|gimp_rgb32_t
block|}
name|gimp_rgb32_t
typedef|;
end_typedef

begin_typedef
typedef|typedef
struct|struct
DECL|struct|__anon27e5a81a0c08
block|{
DECL|member|r
name|guint32
name|r
decl_stmt|;
DECL|member|g
name|guint32
name|g
decl_stmt|;
DECL|member|b
name|guint32
name|b
decl_stmt|;
DECL|member|a
name|guint32
name|a
decl_stmt|;
DECL|typedef|gimp_rgba32_t
block|}
name|gimp_rgba32_t
typedef|;
end_typedef

begin_endif
endif|#
directive|endif
end_endif

begin_function_decl
specifier|extern
name|double
name|gimp_composite_regression_time_function
parameter_list|(
name|int
parameter_list|,
name|void
function_decl|(
modifier|*
function_decl|)
parameter_list|()
parameter_list|,
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
name|gimp_composite_regression_comp_rgba8
parameter_list|(
name|char
modifier|*
parameter_list|,
name|gimp_rgba8_t
modifier|*
parameter_list|,
name|gimp_rgba8_t
modifier|*
parameter_list|,
name|gimp_rgba8_t
modifier|*
parameter_list|,
name|gimp_rgba8_t
modifier|*
parameter_list|,
name|u_long
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
name|gimp_composite_regression_comp_va8
parameter_list|(
name|char
modifier|*
parameter_list|,
name|gimp_va8_t
modifier|*
parameter_list|,
name|gimp_va8_t
modifier|*
parameter_list|,
name|gimp_va8_t
modifier|*
parameter_list|,
name|gimp_va8_t
modifier|*
parameter_list|,
name|u_long
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|int
name|gimp_composite_regression_compare_contexts
parameter_list|(
name|char
modifier|*
parameter_list|,
name|GimpCompositeContext
modifier|*
parameter_list|,
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_regression_dump_rgba8
parameter_list|(
name|char
modifier|*
parameter_list|,
name|gimp_rgba8_t
modifier|*
parameter_list|,
name|u_long
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_regression_print_rgba8
parameter_list|(
name|gimp_rgba8_t
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_regression_print_va8
parameter_list|(
name|gimp_va8_t
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_regression_timer_report
parameter_list|(
name|char
modifier|*
parameter_list|,
name|double
parameter_list|,
name|double
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|gimp_rgba8_t
modifier|*
name|gimp_composite_regression_random_rgba8
parameter_list|(
name|unsigned
name|long
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|gimp_rgba8_t
modifier|*
name|gimp_composite_regression_fixed_rgba8
parameter_list|(
name|unsigned
name|long
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|GimpCompositeContext
modifier|*
name|gimp_composite_context_init
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|,
name|GimpCompositeOperation
parameter_list|,
name|GimpPixelFormat
parameter_list|,
name|GimpPixelFormat
parameter_list|,
name|GimpPixelFormat
parameter_list|,
name|GimpPixelFormat
parameter_list|,
name|unsigned
name|long
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|,
name|unsigned
name|char
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

