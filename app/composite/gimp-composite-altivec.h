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

begin_ifdef
ifdef|#
directive|ifdef
name|ARCH_PPC
end_ifdef

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
comment|/* __GNUC__> 3 */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* ARCH_PPC */
end_comment

begin_endif
endif|#
directive|endif
end_endif

end_unit

