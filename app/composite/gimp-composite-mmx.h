begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|gimp_composite_context_h
end_ifndef

begin_define
DECL|macro|gimp_composite_context_h
define|#
directive|define
name|gimp_composite_context_h
end_define

begin_function_decl
specifier|extern
name|void
name|gimp_composite_mmx_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_ifdef
ifdef|#
directive|ifdef
name|USE_MMX
end_ifdef

begin_if
if|#
directive|if
name|__GNUC__
operator|>=
literal|3
end_if

begin_comment
comment|/*  *  */
end_comment

begin_function_decl
specifier|extern
name|void
name|gimp_composite_addition_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_burn_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_coloronly_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_darken_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_difference_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_dissolve_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_divide_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_dodge_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_grainextract_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_grainmerge_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_hardlight_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_hueonly_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_lighten_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_multiply_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_overlay_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_replace_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_saturationonly_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_screen_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_softlight_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_subtract_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_swap_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_valueonly_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_addition_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_burn_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_coloronly_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_darken_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_difference_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_dissolve_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_divide_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_dodge_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_grainextract_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_grainmerge_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_hardlight_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_hueonly_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_lighten_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_multiply_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_overlay_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_replace_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_saturationonly_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_screen_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_softlight_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_subtract_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_swap_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_valueonly_va8_va8_va8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GNUC__> 3 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* USE_MMX */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

