begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_include
include|#
directive|include
file|"output.h"
end_include

begin_function
DECL|function|output_def (Def * d)
name|void
name|output_def
parameter_list|(
name|Def
modifier|*
name|d
parameter_list|)
block|{
name|TypeName
modifier|*
name|t
init|=
operator|&
name|d
operator|->
name|type
operator|->
name|name
decl_stmt|;
comment|/* GTK_TYPE_FOO macro */
name|pr
argument_list|(
name|type_hdr
argument_list|,
literal|"#define %3 \\\n"
literal|" (%2 ? %2 : %2())\n"
argument_list|,
name|pr_macro_name
argument_list|,
name|t
argument_list|,
literal|"TYPE"
argument_list|,
name|NULL
argument_list|,
name|pr_internal_varname
argument_list|,
name|t
argument_list|,
literal|"type"
argument_list|,
name|pr_internal_varname
argument_list|,
name|t
argument_list|,
literal|"type"
argument_list|,
name|pr_internal_varname
argument_list|,
name|t
argument_list|,
literal|"init_type"
argument_list|)
expr_stmt|;
name|output_var
argument_list|(
name|d
argument_list|,
name|type_gtk_type
argument_list|,
literal|"type"
argument_list|,
name|type_hdr
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

