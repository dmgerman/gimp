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
file|"core/core-enums.h"
end_include

begin_include
include|#
directive|include
file|"tools-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./tools-enums.h" */
end_comment

begin_decl_stmt
DECL|variable|gimp_color_pick_mode_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_color_pick_mode_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_COLOR_PICK_MODE_FOREGROUND
block|,
name|N_
argument_list|(
literal|"Pick Foreground Color"
argument_list|)
block|,
literal|"foreground"
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_BACKGROUND
block|,
name|N_
argument_list|(
literal|"Pick Background Color"
argument_list|)
block|,
literal|"background"
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
DECL|function|gimp_color_pick_mode_get_type (void)
name|gimp_color_pick_mode_get_type
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
literal|"GimpColorPickMode"
argument_list|,
name|gimp_color_pick_mode_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_crop_type_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_crop_type_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_CROP
block|,
name|N_
argument_list|(
literal|"Crop"
argument_list|)
block|,
literal|"crop"
block|}
block|,
block|{
name|GIMP_RESIZE
block|,
name|N_
argument_list|(
literal|"Resize"
argument_list|)
block|,
literal|"resize"
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
DECL|function|gimp_crop_type_get_type (void)
name|gimp_crop_type_get_type
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
literal|"GimpCropType"
argument_list|,
name|gimp_crop_type_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_rect_select_mode_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_rect_select_mode_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_RECT_SELECT_MODE_FREE
block|,
name|N_
argument_list|(
literal|"Free Select"
argument_list|)
block|,
literal|"free"
block|}
block|,
block|{
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
block|,
name|N_
argument_list|(
literal|"Fixed Size"
argument_list|)
block|,
literal|"fixed-size"
block|}
block|,
block|{
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
block|,
name|N_
argument_list|(
literal|"Fixed Aspect Ratio"
argument_list|)
block|,
literal|"fixed-ratio"
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
DECL|function|gimp_rect_select_mode_get_type (void)
name|gimp_rect_select_mode_get_type
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
literal|"GimpRectSelectMode"
argument_list|,
name|gimp_rect_select_mode_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_transform_type_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_transform_type_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_TRANSFORM_TYPE_LAYER
block|,
name|N_
argument_list|(
literal|"Transform Active Layer"
argument_list|)
block|,
literal|"layer"
block|}
block|,
block|{
name|GIMP_TRANSFORM_TYPE_SELECTION
block|,
name|N_
argument_list|(
literal|"Transform Selection"
argument_list|)
block|,
literal|"selection"
block|}
block|,
block|{
name|GIMP_TRANSFORM_TYPE_PATH
block|,
name|N_
argument_list|(
literal|"Transform Active Path"
argument_list|)
block|,
literal|"path"
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
DECL|function|gimp_transform_type_get_type (void)
name|gimp_transform_type_get_type
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
literal|"GimpTransformType"
argument_list|,
name|gimp_transform_type_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_vector_mode_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_vector_mode_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_VECTOR_MODE_DESIGN
block|,
name|N_
argument_list|(
literal|"Design"
argument_list|)
block|,
literal|"design"
block|}
block|,
block|{
name|GIMP_VECTOR_MODE_EDIT
block|,
name|N_
argument_list|(
literal|"Edit"
argument_list|)
block|,
literal|"edit"
block|}
block|,
block|{
name|GIMP_VECTOR_MODE_MOVE
block|,
name|N_
argument_list|(
literal|"Move"
argument_list|)
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
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_vector_mode_get_type (void)
name|gimp_vector_mode_get_type
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
literal|"GimpVectorMode"
argument_list|,
name|gimp_vector_mode_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_transform_grid_type_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_transform_grid_type_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_TRANSFORM_GRID_TYPE_NONE
block|,
name|N_
argument_list|(
literal|"Don't Show Grid"
argument_list|)
block|,
literal|"none"
block|}
block|,
block|{
name|GIMP_TRANSFORM_GRID_TYPE_N_LINES
block|,
name|N_
argument_list|(
literal|"Number of Grid Lines"
argument_list|)
block|,
literal|"n-lines"
block|}
block|,
block|{
name|GIMP_TRANSFORM_GRID_TYPE_SPACING
block|,
name|N_
argument_list|(
literal|"Grid Line Spacing"
argument_list|)
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
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_transform_grid_type_get_type (void)
name|gimp_transform_grid_type_get_type
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
literal|"GimpTransformGridType"
argument_list|,
name|gimp_transform_grid_type_enum_values
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

