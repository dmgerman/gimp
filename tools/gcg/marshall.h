begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_ifndef
ifndef|#
directive|ifndef
name|__MARSHALL_H__
end_ifndef

begin_define
DECL|macro|__MARSHALL_H__
define|#
directive|define
name|__MARSHALL_H__
end_define

begin_include
include|#
directive|include
file|"gcg.h"
end_include

begin_include
include|#
directive|include
file|"pnode.h"
end_include

begin_function_decl
name|PNode
modifier|*
name|p_gtype_name
parameter_list|(
name|GtkType
name|t
parameter_list|,
name|gboolean
name|abbr
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PNode
modifier|*
name|p_gtabbr
parameter_list|(
name|gpointer
name|p
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkType
name|marshalling_type
parameter_list|(
name|Type
modifier|*
name|t
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PNode
modifier|*
name|p_signal_marshaller_name
parameter_list|(
name|Method
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PNode
modifier|*
name|p_signal_demarshaller_name
parameter_list|(
name|Method
modifier|*
name|s
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|PNode
modifier|*
name|p_arg_marsh
parameter_list|(
name|gpointer
name|p
parameter_list|,
name|gpointer
name|d
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

end_unit

