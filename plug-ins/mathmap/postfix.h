begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"exprtree.h"
end_include

begin_typedef
DECL|typedef|stackfunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|stackfunc
function_decl|)
parameter_list|(
name|double
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|struct|_postfix
typedef|typedef
struct|struct
name|_postfix
block|{
DECL|member|func
name|stackfunc
name|func
decl_stmt|;
DECL|member|arg
name|double
name|arg
decl_stmt|;
DECL|typedef|postfix
block|}
name|postfix
typedef|;
end_typedef

begin_function_decl
name|void
name|make_postfix
parameter_list|(
name|exprtree
modifier|*
name|tree
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|double
name|eval_postfix
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

end_unit

