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
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./text-enums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_text_box_mode_get_type (void)
name|gimp_text_box_mode_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_TEXT_BOX_DYNAMIC
block|,
literal|"GIMP_TEXT_BOX_DYNAMIC"
block|,
literal|"dynamic"
block|}
block|,
block|{
name|GIMP_TEXT_BOX_FIXED
block|,
literal|"GIMP_TEXT_BOX_FIXED"
block|,
literal|"fixed"
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
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTextBoxMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_text_direction_get_type (void)
name|gimp_text_direction_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_TEXT_DIRECTION_LTR
block|,
name|N_
argument_list|(
literal|"From left to right"
argument_list|)
block|,
literal|"ltr"
block|}
block|,
block|{
name|GIMP_TEXT_DIRECTION_RTL
block|,
name|N_
argument_list|(
literal|"From right to left"
argument_list|)
block|,
literal|"rtl"
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
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTextDirection"
argument_list|,
name|values
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_text_justification_get_type (void)
name|gimp_text_justification_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_TEXT_JUSTIFY_LEFT
block|,
name|N_
argument_list|(
literal|"Left justified"
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
literal|"Right justified"
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
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTextJustification"
argument_list|,
name|values
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_text_outline_get_type (void)
name|gimp_text_outline_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GEnumValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_TEXT_OUTLINE_NONE
block|,
literal|"GIMP_TEXT_OUTLINE_NONE"
block|,
literal|"none"
block|}
block|,
block|{
name|GIMP_TEXT_OUTLINE_STROKE_ONLY
block|,
literal|"GIMP_TEXT_OUTLINE_STROKE_ONLY"
block|,
literal|"stroke-only"
block|}
block|,
block|{
name|GIMP_TEXT_OUTLINE_STROKE_FILL
block|,
literal|"GIMP_TEXT_OUTLINE_STROKE_FILL"
block|,
literal|"stroke-fill"
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
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTextOutline"
argument_list|,
name|values
argument_list|)
expr_stmt|;
return|return
name|type
return|;
block|}
end_function

begin_comment
comment|/* Generated data ends here */
end_comment

end_unit

