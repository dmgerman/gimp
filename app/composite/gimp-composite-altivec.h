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
name|void
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
name|void
name|gimp_composite_altivec_install
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

