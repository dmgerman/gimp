begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|gimp_composite_sse2_h
end_ifndef

begin_define
DECL|macro|gimp_composite_sse2_h
define|#
directive|define
name|gimp_composite_sse2_h
end_define

begin_function_decl
specifier|extern
name|gboolean
name|gimp_composite_sse2_init
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* 	* The function gimp_composite_*_install() is defined in the code generated by make-install.py 	* I hate to create a .h file just for that declaration, so I do it here (for now).  */
end_comment

begin_function_decl
specifier|extern
name|gboolean
name|gimp_composite_sse2_install
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__INTEL_COMPILER
argument_list|)
end_if

begin_if
if|#
directive|if
name|defined
argument_list|(
name|USE_SSE
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
operator|!
name|defined
argument_list|(
name|PIC
argument_list|)
end_if

begin_define
DECL|macro|COMPILE_SSE2_OKAY
define|#
directive|define
name|COMPILE_SSE2_OKAY
value|(1)
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(ARCH_X86_64) || !defined(PIC) */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GNUC__>= 3*/
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
comment|/* defined(USE_SSE) */
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
name|COMPILE_SSE2_OKAY
end_ifdef

begin_function_decl
specifier|extern
name|void
name|gimp_composite_addition_rgba8_rgba8_rgba8_sse2
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
name|gimp_composite_darken_rgba8_rgba8_rgba8_sse2
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
name|gimp_composite_difference_rgba8_rgba8_rgba8_sse2
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
name|gimp_composite_grain_extract_rgba8_rgba8_rgba8_sse2
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
name|gimp_composite_lighten_rgba8_rgba8_rgba8_sse2
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
name|gimp_composite_subtract_rgba8_rgba8_rgba8_sse2
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
name|gimp_composite_swap_rgba8_rgba8_rgba8_sse2
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
name|gimp_composite_dodge_rgba8_rgba8_rgba8_sse2
parameter_list|(
name|GimpCompositeContext
modifier|*
name|ctx
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_endif
endif|#
directive|endif
end_endif

end_unit

