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
file|"display-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "display-enums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_button_press_type_get_type (void)
name|gimp_button_press_type_get_type
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
name|GIMP_BUTTON_PRESS_NORMAL
block|,
literal|"GIMP_BUTTON_PRESS_NORMAL"
block|,
literal|"normal"
block|}
block|,
block|{
name|GIMP_BUTTON_PRESS_DOUBLE
block|,
literal|"GIMP_BUTTON_PRESS_DOUBLE"
block|,
literal|"double"
block|}
block|,
block|{
name|GIMP_BUTTON_PRESS_TRIPLE
block|,
literal|"GIMP_BUTTON_PRESS_TRIPLE"
block|,
literal|"triple"
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
name|GIMP_BUTTON_PRESS_NORMAL
block|,
literal|"GIMP_BUTTON_PRESS_NORMAL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BUTTON_PRESS_DOUBLE
block|,
literal|"GIMP_BUTTON_PRESS_DOUBLE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BUTTON_PRESS_TRIPLE
block|,
literal|"GIMP_BUTTON_PRESS_TRIPLE"
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
literal|"GimpButtonPressType"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"button-press-type"
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
DECL|function|gimp_button_release_type_get_type (void)
name|gimp_button_release_type_get_type
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
name|GIMP_BUTTON_RELEASE_NORMAL
block|,
literal|"GIMP_BUTTON_RELEASE_NORMAL"
block|,
literal|"normal"
block|}
block|,
block|{
name|GIMP_BUTTON_RELEASE_CANCEL
block|,
literal|"GIMP_BUTTON_RELEASE_CANCEL"
block|,
literal|"cancel"
block|}
block|,
block|{
name|GIMP_BUTTON_RELEASE_CLICK
block|,
literal|"GIMP_BUTTON_RELEASE_CLICK"
block|,
literal|"click"
block|}
block|,
block|{
name|GIMP_BUTTON_RELEASE_NO_MOTION
block|,
literal|"GIMP_BUTTON_RELEASE_NO_MOTION"
block|,
literal|"no-motion"
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
name|GIMP_BUTTON_RELEASE_NORMAL
block|,
literal|"GIMP_BUTTON_RELEASE_NORMAL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BUTTON_RELEASE_CANCEL
block|,
literal|"GIMP_BUTTON_RELEASE_CANCEL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BUTTON_RELEASE_CLICK
block|,
literal|"GIMP_BUTTON_RELEASE_CLICK"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BUTTON_RELEASE_NO_MOTION
block|,
literal|"GIMP_BUTTON_RELEASE_NO_MOTION"
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
literal|"GimpButtonReleaseType"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"button-release-type"
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
DECL|function|gimp_cursor_precision_get_type (void)
name|gimp_cursor_precision_get_type
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
name|GIMP_CURSOR_PRECISION_PIXEL_CENTER
block|,
literal|"GIMP_CURSOR_PRECISION_PIXEL_CENTER"
block|,
literal|"pixel-center"
block|}
block|,
block|{
name|GIMP_CURSOR_PRECISION_PIXEL_BORDER
block|,
literal|"GIMP_CURSOR_PRECISION_PIXEL_BORDER"
block|,
literal|"pixel-border"
block|}
block|,
block|{
name|GIMP_CURSOR_PRECISION_SUBPIXEL
block|,
literal|"GIMP_CURSOR_PRECISION_SUBPIXEL"
block|,
literal|"subpixel"
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
name|GIMP_CURSOR_PRECISION_PIXEL_CENTER
block|,
literal|"GIMP_CURSOR_PRECISION_PIXEL_CENTER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CURSOR_PRECISION_PIXEL_BORDER
block|,
literal|"GIMP_CURSOR_PRECISION_PIXEL_BORDER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CURSOR_PRECISION_SUBPIXEL
block|,
literal|"GIMP_CURSOR_PRECISION_SUBPIXEL"
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
literal|"GimpCursorPrecision"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"cursor-precision"
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
DECL|function|gimp_guides_type_get_type (void)
name|gimp_guides_type_get_type
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
name|GIMP_GUIDES_NONE
block|,
literal|"GIMP_GUIDES_NONE"
block|,
literal|"none"
block|}
block|,
block|{
name|GIMP_GUIDES_CENTER_LINES
block|,
literal|"GIMP_GUIDES_CENTER_LINES"
block|,
literal|"center-lines"
block|}
block|,
block|{
name|GIMP_GUIDES_THIRDS
block|,
literal|"GIMP_GUIDES_THIRDS"
block|,
literal|"thirds"
block|}
block|,
block|{
name|GIMP_GUIDES_FIFTHS
block|,
literal|"GIMP_GUIDES_FIFTHS"
block|,
literal|"fifths"
block|}
block|,
block|{
name|GIMP_GUIDES_GOLDEN
block|,
literal|"GIMP_GUIDES_GOLDEN"
block|,
literal|"golden"
block|}
block|,
block|{
name|GIMP_GUIDES_DIAGONALS
block|,
literal|"GIMP_GUIDES_DIAGONALS"
block|,
literal|"diagonals"
block|}
block|,
block|{
name|GIMP_GUIDES_N_LINES
block|,
literal|"GIMP_GUIDES_N_LINES"
block|,
literal|"n-lines"
block|}
block|,
block|{
name|GIMP_GUIDES_SPACING
block|,
literal|"GIMP_GUIDES_SPACING"
block|,
literal|"spacing"
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
name|GIMP_GUIDES_NONE
block|,
name|NC_
argument_list|(
literal|"guides-type"
argument_list|,
literal|"No guides"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GUIDES_CENTER_LINES
block|,
name|NC_
argument_list|(
literal|"guides-type"
argument_list|,
literal|"Center lines"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GUIDES_THIRDS
block|,
name|NC_
argument_list|(
literal|"guides-type"
argument_list|,
literal|"Rule of thirds"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GUIDES_FIFTHS
block|,
name|NC_
argument_list|(
literal|"guides-type"
argument_list|,
literal|"Rule of fifths"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GUIDES_GOLDEN
block|,
name|NC_
argument_list|(
literal|"guides-type"
argument_list|,
literal|"Golden sections"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GUIDES_DIAGONALS
block|,
name|NC_
argument_list|(
literal|"guides-type"
argument_list|,
literal|"Diagonal lines"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GUIDES_N_LINES
block|,
name|NC_
argument_list|(
literal|"guides-type"
argument_list|,
literal|"Number of lines"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_GUIDES_SPACING
block|,
name|NC_
argument_list|(
literal|"guides-type"
argument_list|,
literal|"Line spacing"
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
literal|"GimpGuidesType"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"guides-type"
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
DECL|function|gimp_handle_type_get_type (void)
name|gimp_handle_type_get_type
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
name|GIMP_HANDLE_SQUARE
block|,
literal|"GIMP_HANDLE_SQUARE"
block|,
literal|"square"
block|}
block|,
block|{
name|GIMP_HANDLE_FILLED_SQUARE
block|,
literal|"GIMP_HANDLE_FILLED_SQUARE"
block|,
literal|"filled-square"
block|}
block|,
block|{
name|GIMP_HANDLE_CIRCLE
block|,
literal|"GIMP_HANDLE_CIRCLE"
block|,
literal|"circle"
block|}
block|,
block|{
name|GIMP_HANDLE_FILLED_CIRCLE
block|,
literal|"GIMP_HANDLE_FILLED_CIRCLE"
block|,
literal|"filled-circle"
block|}
block|,
block|{
name|GIMP_HANDLE_DIAMOND
block|,
literal|"GIMP_HANDLE_DIAMOND"
block|,
literal|"diamond"
block|}
block|,
block|{
name|GIMP_HANDLE_FILLED_DIAMOND
block|,
literal|"GIMP_HANDLE_FILLED_DIAMOND"
block|,
literal|"filled-diamond"
block|}
block|,
block|{
name|GIMP_HANDLE_CROSS
block|,
literal|"GIMP_HANDLE_CROSS"
block|,
literal|"cross"
block|}
block|,
block|{
name|GIMP_HANDLE_CROSSHAIR
block|,
literal|"GIMP_HANDLE_CROSSHAIR"
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
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_HANDLE_SQUARE
block|,
literal|"GIMP_HANDLE_SQUARE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_FILLED_SQUARE
block|,
literal|"GIMP_HANDLE_FILLED_SQUARE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_CIRCLE
block|,
literal|"GIMP_HANDLE_CIRCLE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_FILLED_CIRCLE
block|,
literal|"GIMP_HANDLE_FILLED_CIRCLE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_DIAMOND
block|,
literal|"GIMP_HANDLE_DIAMOND"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_FILLED_DIAMOND
block|,
literal|"GIMP_HANDLE_FILLED_DIAMOND"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_CROSS
block|,
literal|"GIMP_HANDLE_CROSS"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_CROSSHAIR
block|,
literal|"GIMP_HANDLE_CROSSHAIR"
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
literal|"GimpHandleType"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"handle-type"
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
DECL|function|gimp_handle_anchor_get_type (void)
name|gimp_handle_anchor_get_type
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
name|GIMP_HANDLE_ANCHOR_CENTER
block|,
literal|"GIMP_HANDLE_ANCHOR_CENTER"
block|,
literal|"center"
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_NORTH
block|,
literal|"GIMP_HANDLE_ANCHOR_NORTH"
block|,
literal|"north"
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_NORTH_WEST
block|,
literal|"GIMP_HANDLE_ANCHOR_NORTH_WEST"
block|,
literal|"north-west"
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_NORTH_EAST
block|,
literal|"GIMP_HANDLE_ANCHOR_NORTH_EAST"
block|,
literal|"north-east"
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_SOUTH
block|,
literal|"GIMP_HANDLE_ANCHOR_SOUTH"
block|,
literal|"south"
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_SOUTH_WEST
block|,
literal|"GIMP_HANDLE_ANCHOR_SOUTH_WEST"
block|,
literal|"south-west"
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_SOUTH_EAST
block|,
literal|"GIMP_HANDLE_ANCHOR_SOUTH_EAST"
block|,
literal|"south-east"
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_WEST
block|,
literal|"GIMP_HANDLE_ANCHOR_WEST"
block|,
literal|"west"
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_EAST
block|,
literal|"GIMP_HANDLE_ANCHOR_EAST"
block|,
literal|"east"
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
name|GIMP_HANDLE_ANCHOR_CENTER
block|,
literal|"GIMP_HANDLE_ANCHOR_CENTER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_NORTH
block|,
literal|"GIMP_HANDLE_ANCHOR_NORTH"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_NORTH_WEST
block|,
literal|"GIMP_HANDLE_ANCHOR_NORTH_WEST"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_NORTH_EAST
block|,
literal|"GIMP_HANDLE_ANCHOR_NORTH_EAST"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_SOUTH
block|,
literal|"GIMP_HANDLE_ANCHOR_SOUTH"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_SOUTH_WEST
block|,
literal|"GIMP_HANDLE_ANCHOR_SOUTH_WEST"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_SOUTH_EAST
block|,
literal|"GIMP_HANDLE_ANCHOR_SOUTH_EAST"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_WEST
block|,
literal|"GIMP_HANDLE_ANCHOR_WEST"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_ANCHOR_EAST
block|,
literal|"GIMP_HANDLE_ANCHOR_EAST"
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
literal|"GimpHandleAnchor"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"handle-anchor"
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
DECL|function|gimp_path_style_get_type (void)
name|gimp_path_style_get_type
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
name|GIMP_PATH_STYLE_DEFAULT
block|,
literal|"GIMP_PATH_STYLE_DEFAULT"
block|,
literal|"default"
block|}
block|,
block|{
name|GIMP_PATH_STYLE_VECTORS
block|,
literal|"GIMP_PATH_STYLE_VECTORS"
block|,
literal|"vectors"
block|}
block|,
block|{
name|GIMP_PATH_STYLE_OUTLINE
block|,
literal|"GIMP_PATH_STYLE_OUTLINE"
block|,
literal|"outline"
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
name|GIMP_PATH_STYLE_DEFAULT
block|,
literal|"GIMP_PATH_STYLE_DEFAULT"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_PATH_STYLE_VECTORS
block|,
literal|"GIMP_PATH_STYLE_VECTORS"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_PATH_STYLE_OUTLINE
block|,
literal|"GIMP_PATH_STYLE_OUTLINE"
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
literal|"GimpPathStyle"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"path-style"
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
DECL|function|gimp_rectangle_constraint_get_type (void)
name|gimp_rectangle_constraint_get_type
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
name|GIMP_RECTANGLE_CONSTRAIN_NONE
block|,
literal|"GIMP_RECTANGLE_CONSTRAIN_NONE"
block|,
literal|"none"
block|}
block|,
block|{
name|GIMP_RECTANGLE_CONSTRAIN_IMAGE
block|,
literal|"GIMP_RECTANGLE_CONSTRAIN_IMAGE"
block|,
literal|"image"
block|}
block|,
block|{
name|GIMP_RECTANGLE_CONSTRAIN_DRAWABLE
block|,
literal|"GIMP_RECTANGLE_CONSTRAIN_DRAWABLE"
block|,
literal|"drawable"
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
name|GIMP_RECTANGLE_CONSTRAIN_NONE
block|,
literal|"GIMP_RECTANGLE_CONSTRAIN_NONE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_CONSTRAIN_IMAGE
block|,
literal|"GIMP_RECTANGLE_CONSTRAIN_IMAGE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_CONSTRAIN_DRAWABLE
block|,
literal|"GIMP_RECTANGLE_CONSTRAIN_DRAWABLE"
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
literal|"GimpRectangleConstraint"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"rectangle-constraint"
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
DECL|function|gimp_rectangle_fixed_rule_get_type (void)
name|gimp_rectangle_fixed_rule_get_type
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
name|GIMP_RECTANGLE_FIXED_ASPECT
block|,
literal|"GIMP_RECTANGLE_FIXED_ASPECT"
block|,
literal|"aspect"
block|}
block|,
block|{
name|GIMP_RECTANGLE_FIXED_WIDTH
block|,
literal|"GIMP_RECTANGLE_FIXED_WIDTH"
block|,
literal|"width"
block|}
block|,
block|{
name|GIMP_RECTANGLE_FIXED_HEIGHT
block|,
literal|"GIMP_RECTANGLE_FIXED_HEIGHT"
block|,
literal|"height"
block|}
block|,
block|{
name|GIMP_RECTANGLE_FIXED_SIZE
block|,
literal|"GIMP_RECTANGLE_FIXED_SIZE"
block|,
literal|"size"
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
name|GIMP_RECTANGLE_FIXED_ASPECT
block|,
name|NC_
argument_list|(
literal|"rectangle-fixed-rule"
argument_list|,
literal|"Aspect ratio"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_FIXED_WIDTH
block|,
name|NC_
argument_list|(
literal|"rectangle-fixed-rule"
argument_list|,
literal|"Width"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_FIXED_HEIGHT
block|,
name|NC_
argument_list|(
literal|"rectangle-fixed-rule"
argument_list|,
literal|"Height"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_FIXED_SIZE
block|,
name|NC_
argument_list|(
literal|"rectangle-fixed-rule"
argument_list|,
literal|"Size"
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
literal|"GimpRectangleFixedRule"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"rectangle-fixed-rule"
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
DECL|function|gimp_rectangle_precision_get_type (void)
name|gimp_rectangle_precision_get_type
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
name|GIMP_RECTANGLE_PRECISION_INT
block|,
literal|"GIMP_RECTANGLE_PRECISION_INT"
block|,
literal|"int"
block|}
block|,
block|{
name|GIMP_RECTANGLE_PRECISION_DOUBLE
block|,
literal|"GIMP_RECTANGLE_PRECISION_DOUBLE"
block|,
literal|"double"
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
name|GIMP_RECTANGLE_PRECISION_INT
block|,
literal|"GIMP_RECTANGLE_PRECISION_INT"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_PRECISION_DOUBLE
block|,
literal|"GIMP_RECTANGLE_PRECISION_DOUBLE"
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
literal|"GimpRectanglePrecision"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"rectangle-precision"
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
DECL|function|gimp_transform_function_get_type (void)
name|gimp_transform_function_get_type
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
name|GIMP_TRANSFORM_FUNCTION_MOVE
block|,
literal|"GIMP_TRANSFORM_FUNCTION_MOVE"
block|,
literal|"move"
block|}
block|,
block|{
name|GIMP_TRANSFORM_FUNCTION_SCALE
block|,
literal|"GIMP_TRANSFORM_FUNCTION_SCALE"
block|,
literal|"scale"
block|}
block|,
block|{
name|GIMP_TRANSFORM_FUNCTION_ROTATE
block|,
literal|"GIMP_TRANSFORM_FUNCTION_ROTATE"
block|,
literal|"rotate"
block|}
block|,
block|{
name|GIMP_TRANSFORM_FUNCTION_SHEAR
block|,
literal|"GIMP_TRANSFORM_FUNCTION_SHEAR"
block|,
literal|"shear"
block|}
block|,
block|{
name|GIMP_TRANSFORM_FUNCTION_PERSPECTIVE
block|,
literal|"GIMP_TRANSFORM_FUNCTION_PERSPECTIVE"
block|,
literal|"perspective"
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
name|GIMP_TRANSFORM_FUNCTION_MOVE
block|,
literal|"GIMP_TRANSFORM_FUNCTION_MOVE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_FUNCTION_SCALE
block|,
literal|"GIMP_TRANSFORM_FUNCTION_SCALE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_FUNCTION_ROTATE
block|,
literal|"GIMP_TRANSFORM_FUNCTION_ROTATE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_FUNCTION_SHEAR
block|,
literal|"GIMP_TRANSFORM_FUNCTION_SHEAR"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_FUNCTION_PERSPECTIVE
block|,
literal|"GIMP_TRANSFORM_FUNCTION_PERSPECTIVE"
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
literal|"GimpTransformFunction"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"transform-function"
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
DECL|function|gimp_transform_handle_mode_get_type (void)
name|gimp_transform_handle_mode_get_type
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
name|GIMP_HANDLE_MODE_ADD_TRANSFORM
block|,
literal|"GIMP_HANDLE_MODE_ADD_TRANSFORM"
block|,
literal|"add-transform"
block|}
block|,
block|{
name|GIMP_HANDLE_MODE_MOVE
block|,
literal|"GIMP_HANDLE_MODE_MOVE"
block|,
literal|"move"
block|}
block|,
block|{
name|GIMP_HANDLE_MODE_REMOVE
block|,
literal|"GIMP_HANDLE_MODE_REMOVE"
block|,
literal|"remove"
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
name|GIMP_HANDLE_MODE_ADD_TRANSFORM
block|,
name|NC_
argument_list|(
literal|"transform-handle-mode"
argument_list|,
literal|"Add / Transform"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_MODE_MOVE
block|,
name|NC_
argument_list|(
literal|"transform-handle-mode"
argument_list|,
literal|"Move"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HANDLE_MODE_REMOVE
block|,
name|NC_
argument_list|(
literal|"transform-handle-mode"
argument_list|,
literal|"Remove"
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
literal|"GimpTransformHandleMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"transform-handle-mode"
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
DECL|function|gimp_vector_mode_get_type (void)
name|gimp_vector_mode_get_type
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
name|GIMP_VECTOR_MODE_DESIGN
block|,
literal|"GIMP_VECTOR_MODE_DESIGN"
block|,
literal|"design"
block|}
block|,
block|{
name|GIMP_VECTOR_MODE_EDIT
block|,
literal|"GIMP_VECTOR_MODE_EDIT"
block|,
literal|"edit"
block|}
block|,
block|{
name|GIMP_VECTOR_MODE_MOVE
block|,
literal|"GIMP_VECTOR_MODE_MOVE"
block|,
literal|"move"
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
name|GIMP_VECTOR_MODE_DESIGN
block|,
name|NC_
argument_list|(
literal|"vector-mode"
argument_list|,
literal|"Design"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_VECTOR_MODE_EDIT
block|,
name|NC_
argument_list|(
literal|"vector-mode"
argument_list|,
literal|"Edit"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_VECTOR_MODE_MOVE
block|,
name|NC_
argument_list|(
literal|"vector-mode"
argument_list|,
literal|"Move"
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
literal|"GimpVectorMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"vector-mode"
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
DECL|function|gimp_zoom_focus_get_type (void)
name|gimp_zoom_focus_get_type
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
name|GIMP_ZOOM_FOCUS_BEST_GUESS
block|,
literal|"GIMP_ZOOM_FOCUS_BEST_GUESS"
block|,
literal|"best-guess"
block|}
block|,
block|{
name|GIMP_ZOOM_FOCUS_POINTER
block|,
literal|"GIMP_ZOOM_FOCUS_POINTER"
block|,
literal|"pointer"
block|}
block|,
block|{
name|GIMP_ZOOM_FOCUS_IMAGE_CENTER
block|,
literal|"GIMP_ZOOM_FOCUS_IMAGE_CENTER"
block|,
literal|"image-center"
block|}
block|,
block|{
name|GIMP_ZOOM_FOCUS_RETAIN_CENTERING_ELSE_BEST_GUESS
block|,
literal|"GIMP_ZOOM_FOCUS_RETAIN_CENTERING_ELSE_BEST_GUESS"
block|,
literal|"retain-centering-else-best-guess"
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
name|GIMP_ZOOM_FOCUS_BEST_GUESS
block|,
literal|"GIMP_ZOOM_FOCUS_BEST_GUESS"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ZOOM_FOCUS_POINTER
block|,
literal|"GIMP_ZOOM_FOCUS_POINTER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ZOOM_FOCUS_IMAGE_CENTER
block|,
literal|"GIMP_ZOOM_FOCUS_IMAGE_CENTER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ZOOM_FOCUS_RETAIN_CENTERING_ELSE_BEST_GUESS
block|,
literal|"GIMP_ZOOM_FOCUS_RETAIN_CENTERING_ELSE_BEST_GUESS"
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
literal|"GimpZoomFocus"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"zoom-focus"
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

