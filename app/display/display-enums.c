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
file|"display-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./display-enums.h" */
end_comment

begin_decl_stmt
DECL|variable|gimp_cursor_mode_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_cursor_mode_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_CURSOR_MODE_TOOL_ICON
block|,
name|N_
argument_list|(
literal|"Tool Icon"
argument_list|)
block|,
literal|"tool-icon"
block|}
block|,
block|{
name|GIMP_CURSOR_MODE_TOOL_CROSSHAIR
block|,
name|N_
argument_list|(
literal|"Tool Icon with Crosshair"
argument_list|)
block|,
literal|"tool-crosshair"
block|}
block|,
block|{
name|GIMP_CURSOR_MODE_CROSSHAIR
block|,
name|N_
argument_list|(
literal|"Crosshair only"
argument_list|)
block|,
literal|"crosshair"
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
DECL|function|gimp_cursor_mode_get_type (void)
name|gimp_cursor_mode_get_type
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
literal|"GimpCursorMode"
argument_list|,
name|gimp_cursor_mode_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_display_padding_mode_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_display_padding_mode_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_DISPLAY_PADDING_MODE_DEFAULT
block|,
name|N_
argument_list|(
literal|"From Theme"
argument_list|)
block|,
literal|"default"
block|}
block|,
block|{
name|GIMP_DISPLAY_PADDING_MODE_LIGHT_CHECK
block|,
name|N_
argument_list|(
literal|"Light Check Color"
argument_list|)
block|,
literal|"light-check"
block|}
block|,
block|{
name|GIMP_DISPLAY_PADDING_MODE_DARK_CHECK
block|,
name|N_
argument_list|(
literal|"Dark Check Color"
argument_list|)
block|,
literal|"dark-check"
block|}
block|,
block|{
name|GIMP_DISPLAY_PADDING_MODE_CUSTOM
block|,
name|N_
argument_list|(
literal|"Custom Color"
argument_list|)
block|,
literal|"custom"
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
DECL|function|gimp_display_padding_mode_get_type (void)
name|gimp_display_padding_mode_get_type
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
literal|"GimpDisplayPaddingMode"
argument_list|,
name|gimp_display_padding_mode_enum_values
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

