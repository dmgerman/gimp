begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* dynload.h */
end_comment

begin_comment
comment|/* Original Copyright (c) 1999 Alexander Shendi     */
end_comment

begin_comment
comment|/* Modifications for NT and dl_* interface: D. Souflis */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|DYNLOAD_H
end_ifndef

begin_define
DECL|macro|DYNLOAD_H
define|#
directive|define
name|DYNLOAD_H
end_define

begin_include
include|#
directive|include
file|"scheme-private.h"
end_include

begin_function_decl
name|SCHEME_EXPORT
name|pointer
name|scm_load_ext
parameter_list|(
name|scheme
modifier|*
name|sc
parameter_list|,
name|pointer
name|arglist
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

