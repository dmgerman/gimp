begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|gimp_composite_mmx_h
end_ifndef

begin_define
DECL|macro|gimp_composite_mmx_h
define|#
directive|define
name|gimp_composite_mmx_h
end_define

begin_function_decl
specifier|extern
name|gboolean
name|gimp_composite_mmx_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*         * The function gimp_composite_*_install() is defined in the code         * generated by make-install.py I hate to have make-install.py create         * a .h file just for that declaration, so I do it here.  */
end_comment

begin_function_decl
specifier|extern
name|gboolean
name|gimp_composite_mmx_install
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  * Rummage through the compile-time environment to ensure this file  * can actually be compiled like we expect it to.  If all is okay,  * define the manifest constant COMPILE_MMX_IS_OKAY.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__INTEL_COMPILER
argument_list|)
operator|||
name|defined
argument_list|(
name|USE_INTEL_COMPILER_ANYWAY
argument_list|)
end_if

begin_if
if|#
directive|if
name|defined
argument_list|(
name|USE_MMX
argument_list|)
end_if

begin_if
if|#
directive|if
name|defined
argument_list|(
name|ARCH_X86
argument_list|)
end_if

begin_if
if|#
directive|if
name|__GNUC__
operator|>=
literal|3
end_if

begin_if
if|#
directive|if
name|defined
argument_list|(
name|ARCH_X86_64
argument_list|)
operator|||
operator|(
operator|!
name|defined
argument_list|(
name|PIC
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|__PIC__
argument_list|)
operator|)
end_if

begin_define
DECL|macro|COMPILE_MMX_IS_OKAY
define|#
directive|define
name|COMPILE_MMX_IS_OKAY
value|(1)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(ARCH_X86_64) || (!defined(PIC)&& !defined(__PIC__)) */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GNUC__>= 3 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(ARCH_X86) */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(USE_MMX) */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* !defined(__INTEL_COMPILER) */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|COMPILE_MMX_IS_OKAY
end_ifdef

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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_grain_extract_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_grain_merge_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|extern
name|void
name|gimp_composite_scale_rgba8_rgba8_rgba8_mmx
parameter_list|(
name|GimpCompositeContext
modifier|*
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
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
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*extern void gimp_composite_multiply_va8_va8_va8_mmx (GimpCompositeContext *ctx);*/
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* COMPILE_IS_OKAY */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

