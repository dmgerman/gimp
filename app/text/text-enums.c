begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Generated data (by gimp-mkenums) */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"text-enums.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/* enumerations from "./text-enums.h" */
end_comment

begin_decl_stmt
DECL|variable|gimp_text_justification_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_text_justification_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_TEXT_JUSTIFY_LEFT
block|,
name|N_
argument_list|(
literal|"Left Justified"
argument_list|)
block|,
literal|"left"
block|}
block|,
block|{
name|GIMP_TEXT_JUSTIFY_RIGHT
block|,
name|N_
argument_list|(
literal|"Right Justified"
argument_list|)
block|,
literal|"right"
block|}
block|,
block|{
name|GIMP_TEXT_JUSTIFY_CENTER
block|,
name|N_
argument_list|(
literal|"Centered"
argument_list|)
block|,
literal|"center"
block|}
block|,
block|{
name|GIMP_TEXT_JUSTIFY_FILL
block|,
name|N_
argument_list|(
literal|"Filled"
argument_list|)
block|,
literal|"fill"
block|}
block|,
block|{
literal|0
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_text_justification_get_type (void)
name|gimp_text_justification_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|enum_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|enum_type
condition|)
name|enum_type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTextJustification"
argument_list|,
name|gimp_text_justification_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_comment
comment|/* Generated data ends here */
end_comment

end_unit

