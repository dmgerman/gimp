begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|gimp_composite_altivec_h
end_ifndef

begin_define
DECL|macro|gimp_composite_altivec_h
define|#
directive|define
name|gimp_composite_altivec_h
end_define

begin_function_decl
specifier|extern
name|gboolean
name|gimp_composite_altivec_init
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
name|gimp_composite_altivec_install
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_if
if|#
directive|if
name|defined
argument_list|(
name|USE_ALTIVEC
argument_list|)
end_if

begin_if
if|#
directive|if
name|defined
argument_list|(
name|ARCH_PPC
argument_list|)
end_if

begin_if
if|#
directive|if
name|__GNUC__
operator|>=
literal|3
end_if

begin_define
DECL|macro|COMPILE_ALTIVEC_IS_OKAY
define|#
directive|define
name|COMPILE_ALTIVEC_IS_OKAY
value|(1)
end_define

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
comment|/* defined(ARCH_PPC) */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* defined(USE_ALTIVEC) */
end_comment

begin_ifdef
ifdef|#
directive|ifdef
name|COMPILE_ALTIVEC_IS_OKAY
end_ifdef

begin_function_decl
specifier|extern
name|void
name|gimp_composite_addition_rgba8_rgba8_rgba8_altivec
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
name|gimp_composite_subtract_rgba8_rgba8_rgba8_altivec
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
name|gimp_composite_swap_rgba8_rgba8_rgba8_altivec
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
name|gimp_composite_difference_rgba8_rgba8_rgba8_altivec
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
name|gimp_composite_darken_rgba8_rgba8_rgba8_altivec
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
name|gimp_composite_lighten_rgba8_rgba8_rgba8_altivec
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

begin_comment
comment|/* COMPILE_IS_OKAY */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

