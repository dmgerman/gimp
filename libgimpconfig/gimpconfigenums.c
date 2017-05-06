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
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfigenums.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "gimpconfigenums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_color_management_mode_get_type (void)
name|gimp_color_management_mode_get_type
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
name|GIMP_COLOR_MANAGEMENT_OFF
block|,
literal|"GIMP_COLOR_MANAGEMENT_OFF"
block|,
literal|"off"
block|}
block|,
block|{
name|GIMP_COLOR_MANAGEMENT_DISPLAY
block|,
literal|"GIMP_COLOR_MANAGEMENT_DISPLAY"
block|,
literal|"display"
block|}
block|,
block|{
name|GIMP_COLOR_MANAGEMENT_SOFTPROOF
block|,
literal|"GIMP_COLOR_MANAGEMENT_SOFTPROOF"
block|,
literal|"softproof"
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
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_COLOR_MANAGEMENT_OFF
block|,
name|NC_
argument_list|(
literal|"color-management-mode"
argument_list|,
literal|"No color management"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_MANAGEMENT_DISPLAY
block|,
name|NC_
argument_list|(
literal|"color-management-mode"
argument_list|,
literal|"Color-managed display"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_MANAGEMENT_SOFTPROOF
block|,
name|NC_
argument_list|(
literal|"color-management-mode"
argument_list|,
literal|"Soft-proofing"
argument_list|)
block|,
name|NULL
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
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpColorManagementMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"color-management-mode"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_color_rendering_intent_get_type (void)
name|gimp_color_rendering_intent_get_type
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
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
block|,
literal|"GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL"
block|,
literal|"perceptual"
block|}
block|,
block|{
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
block|,
literal|"GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC"
block|,
literal|"relative-colorimetric"
block|}
block|,
block|{
name|GIMP_COLOR_RENDERING_INTENT_SATURATION
block|,
literal|"GIMP_COLOR_RENDERING_INTENT_SATURATION"
block|,
literal|"saturation"
block|}
block|,
block|{
name|GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC
block|,
literal|"GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC"
block|,
literal|"absolute-colorimetric"
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
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_COLOR_RENDERING_INTENT_PERCEPTUAL
block|,
name|NC_
argument_list|(
literal|"color-rendering-intent"
argument_list|,
literal|"Perceptual"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_RENDERING_INTENT_RELATIVE_COLORIMETRIC
block|,
name|NC_
argument_list|(
literal|"color-rendering-intent"
argument_list|,
literal|"Relative colorimetric"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_RENDERING_INTENT_SATURATION
block|,
name|NC_
argument_list|(
literal|"color-rendering-intent"
argument_list|,
literal|"Saturation"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_RENDERING_INTENT_ABSOLUTE_COLORIMETRIC
block|,
name|NC_
argument_list|(
literal|"color-rendering-intent"
argument_list|,
literal|"Absolute colorimetric"
argument_list|)
block|,
name|NULL
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
name|G_UNLIKELY
argument_list|(
operator|!
name|type
argument_list|)
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpColorRenderingIntent"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_domain
argument_list|(
name|type
argument_list|,
name|GETTEXT_PACKAGE
literal|"-libgimp"
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"color-rendering-intent"
argument_list|)
expr_stmt|;
name|gimp_enum_set_value_descriptions
argument_list|(
name|type
argument_list|,
name|descs
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_comment
comment|/* Generated data ends here */
end_comment

end_unit

