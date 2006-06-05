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
file|"libgimpbase/gimpbase.h"
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

begin_function
name|GType
DECL|function|gimp_color_pick_mode_get_type (void)
name|gimp_color_pick_mode_get_type
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
name|GIMP_COLOR_PICK_MODE_NONE
block|,
literal|"GIMP_COLOR_PICK_MODE_NONE"
block|,
literal|"none"
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_FOREGROUND
block|,
literal|"GIMP_COLOR_PICK_MODE_FOREGROUND"
block|,
literal|"foreground"
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_BACKGROUND
block|,
literal|"GIMP_COLOR_PICK_MODE_BACKGROUND"
block|,
literal|"background"
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_PALETTE
block|,
literal|"GIMP_COLOR_PICK_MODE_PALETTE"
block|,
literal|"palette"
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
name|GIMP_COLOR_PICK_MODE_NONE
block|,
name|N_
argument_list|(
literal|"Pick only"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_FOREGROUND
block|,
name|N_
argument_list|(
literal|"Set foreground color"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_BACKGROUND
block|,
name|N_
argument_list|(
literal|"Set background color"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_PALETTE
block|,
name|N_
argument_list|(
literal|"Add to palette"
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
operator|!
name|type
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpColorPickMode"
argument_list|,
name|values
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
DECL|function|gimp_rectangle_guide_get_type (void)
name|gimp_rectangle_guide_get_type
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
name|GIMP_RECTANGLE_GUIDE_NONE
block|,
literal|"GIMP_RECTANGLE_GUIDE_NONE"
block|,
literal|"none"
block|}
block|,
block|{
name|GIMP_RECTANGLE_GUIDE_CENTER_LINES
block|,
literal|"GIMP_RECTANGLE_GUIDE_CENTER_LINES"
block|,
literal|"center-lines"
block|}
block|,
block|{
name|GIMP_RECTANGLE_GUIDE_THIRDS
block|,
literal|"GIMP_RECTANGLE_GUIDE_THIRDS"
block|,
literal|"thirds"
block|}
block|,
block|{
name|GIMP_RECTANGLE_GUIDE_GOLDEN
block|,
literal|"GIMP_RECTANGLE_GUIDE_GOLDEN"
block|,
literal|"golden"
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
name|GIMP_RECTANGLE_GUIDE_NONE
block|,
name|N_
argument_list|(
literal|"No guides"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_GUIDE_CENTER_LINES
block|,
name|N_
argument_list|(
literal|"Center lines"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_GUIDE_THIRDS
block|,
name|N_
argument_list|(
literal|"Rule of thirds"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECTANGLE_GUIDE_GOLDEN
block|,
name|N_
argument_list|(
literal|"Golden sections"
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
operator|!
name|type
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpRectangleGuide"
argument_list|,
name|values
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
DECL|function|gimp_crop_mode_get_type (void)
name|gimp_crop_mode_get_type
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
name|GIMP_CROP_MODE_CROP
block|,
literal|"GIMP_CROP_MODE_CROP"
block|,
literal|"crop"
block|}
block|,
block|{
name|GIMP_CROP_MODE_RESIZE
block|,
literal|"GIMP_CROP_MODE_RESIZE"
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
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_CROP_MODE_CROP
block|,
name|N_
argument_list|(
literal|"Crop"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CROP_MODE_RESIZE
block|,
name|N_
argument_list|(
literal|"Resize"
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
operator|!
name|type
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpCropMode"
argument_list|,
name|values
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
DECL|function|gimp_rect_select_mode_get_type (void)
name|gimp_rect_select_mode_get_type
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
name|GIMP_RECT_SELECT_MODE_FREE
block|,
literal|"GIMP_RECT_SELECT_MODE_FREE"
block|,
literal|"free"
block|}
block|,
block|{
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
block|,
literal|"GIMP_RECT_SELECT_MODE_FIXED_SIZE"
block|,
literal|"fixed-size"
block|}
block|,
block|{
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
block|,
literal|"GIMP_RECT_SELECT_MODE_FIXED_RATIO"
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
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_RECT_SELECT_MODE_FREE
block|,
name|N_
argument_list|(
literal|"Free select"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
block|,
name|N_
argument_list|(
literal|"Fixed size"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
block|,
name|N_
argument_list|(
literal|"Fixed aspect ratio"
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
operator|!
name|type
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpRectSelectMode"
argument_list|,
name|values
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
DECL|function|gimp_transform_type_get_type (void)
name|gimp_transform_type_get_type
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
name|GIMP_TRANSFORM_TYPE_LAYER
block|,
literal|"GIMP_TRANSFORM_TYPE_LAYER"
block|,
literal|"layer"
block|}
block|,
block|{
name|GIMP_TRANSFORM_TYPE_SELECTION
block|,
literal|"GIMP_TRANSFORM_TYPE_SELECTION"
block|,
literal|"selection"
block|}
block|,
block|{
name|GIMP_TRANSFORM_TYPE_PATH
block|,
literal|"GIMP_TRANSFORM_TYPE_PATH"
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
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_TRANSFORM_TYPE_LAYER
block|,
name|N_
argument_list|(
literal|"Transform layer"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_TYPE_SELECTION
block|,
name|N_
argument_list|(
literal|"Transform selection"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_TYPE_PATH
block|,
name|N_
argument_list|(
literal|"Transform path"
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
operator|!
name|type
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTransformType"
argument_list|,
name|values
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
name|N_
argument_list|(
literal|"Design"
argument_list|)
block|,
name|NULL
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
name|NULL
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
operator|!
name|type
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
DECL|function|gimp_transform_preview_type_get_type (void)
name|gimp_transform_preview_type_get_type
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
name|GIMP_TRANSFORM_PREVIEW_TYPE_OUTLINE
block|,
literal|"GIMP_TRANSFORM_PREVIEW_TYPE_OUTLINE"
block|,
literal|"outline"
block|}
block|,
block|{
name|GIMP_TRANSFORM_PREVIEW_TYPE_GRID
block|,
literal|"GIMP_TRANSFORM_PREVIEW_TYPE_GRID"
block|,
literal|"grid"
block|}
block|,
block|{
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE
block|,
literal|"GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE"
block|,
literal|"image"
block|}
block|,
block|{
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE_GRID
block|,
literal|"GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE_GRID"
block|,
literal|"image-grid"
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
name|GIMP_TRANSFORM_PREVIEW_TYPE_OUTLINE
block|,
name|N_
argument_list|(
literal|"Outline"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_PREVIEW_TYPE_GRID
block|,
name|N_
argument_list|(
literal|"Grid"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE
block|,
name|N_
argument_list|(
literal|"Image"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_PREVIEW_TYPE_IMAGE_GRID
block|,
name|N_
argument_list|(
literal|"Image + Grid"
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
operator|!
name|type
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTransformPreviewType"
argument_list|,
name|values
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
DECL|function|gimp_transform_grid_type_get_type (void)
name|gimp_transform_grid_type_get_type
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
name|GIMP_TRANSFORM_GRID_TYPE_N_LINES
block|,
literal|"GIMP_TRANSFORM_GRID_TYPE_N_LINES"
block|,
literal|"n-lines"
block|}
block|,
block|{
name|GIMP_TRANSFORM_GRID_TYPE_SPACING
block|,
literal|"GIMP_TRANSFORM_GRID_TYPE_SPACING"
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
name|GIMP_TRANSFORM_GRID_TYPE_N_LINES
block|,
name|N_
argument_list|(
literal|"Number of grid lines"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_GRID_TYPE_SPACING
block|,
name|N_
argument_list|(
literal|"Grid line spacing"
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
operator|!
name|type
condition|)
block|{
name|type
operator|=
name|g_enum_register_static
argument_list|(
literal|"GimpTransformGridType"
argument_list|,
name|values
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

