begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__INFILE_H
end_ifndef

begin_define
DECL|macro|__INFILE_H
define|#
directive|define
name|__INFILE_H
end_define

begin_include
include|#
directive|include
file|"ppmtool.h"
end_include

begin_function_decl
name|void
name|infile_copy_to_ppm
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|infile_copy_alpha_to_ppm
parameter_list|(
name|ppm_t
modifier|*
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

