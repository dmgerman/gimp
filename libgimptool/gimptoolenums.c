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
file|"libgimpproxy/gimpproxytypes.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolenums.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./gimptoolenums.h" */
end_comment

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
DECL|variable|select_ops_enum_values
specifier|static
specifier|const
name|GEnumValue
name|select_ops_enum_values
index|[]
init|=
block|{
block|{
name|SELECTION_ADD
block|,
literal|"SELECTION_ADD"
block|,
literal|"add"
block|}
block|,
block|{
name|SELECTION_SUBTRACT
block|,
literal|"SELECTION_SUBTRACT"
block|,
literal|"subtract"
block|}
block|,
block|{
name|SELECTION_REPLACE
block|,
literal|"SELECTION_REPLACE"
block|,
literal|"replace"
block|}
block|,
block|{
name|SELECTION_INTERSECT
block|,
literal|"SELECTION_INTERSECT"
block|,
literal|"intersect"
block|}
block|,
block|{
name|SELECTION_MOVE_MASK
block|,
literal|"SELECTION_MOVE_MASK"
block|,
literal|"move-mask"
block|}
block|,
block|{
name|SELECTION_MOVE
block|,
literal|"SELECTION_MOVE"
block|,
literal|"move"
block|}
block|,
block|{
name|SELECTION_ANCHOR
block|,
literal|"SELECTION_ANCHOR"
block|,
literal|"anchor"
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
DECL|function|select_ops_get_type (void)
name|select_ops_get_type
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
literal|"SelectOps"
argument_list|,
name|select_ops_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_tool_state_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_tool_state_enum_values
index|[]
init|=
block|{
block|{
name|INACTIVE
block|,
literal|"INACTIVE"
block|,
literal|"inactive"
block|}
block|,
block|{
name|ACTIVE
block|,
literal|"ACTIVE"
block|,
literal|"active"
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
DECL|function|gimp_tool_state_get_type (void)
name|gimp_tool_state_get_type
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
literal|"GimpToolState"
argument_list|,
name|gimp_tool_state_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_tool_action_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_tool_action_enum_values
index|[]
init|=
block|{
block|{
name|PAUSE
block|,
literal|"PAUSE"
block|,
literal|"pause"
block|}
block|,
block|{
name|RESUME
block|,
literal|"RESUME"
block|,
literal|"resume"
block|}
block|,
block|{
name|HALT
block|,
literal|"HALT"
block|,
literal|"halt"
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
DECL|function|gimp_tool_action_get_type (void)
name|gimp_tool_action_get_type
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
literal|"GimpToolAction"
argument_list|,
name|gimp_tool_action_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_motion_mode_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_motion_mode_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_MOTION_MODE_EXACT
block|,
literal|"GIMP_MOTION_MODE_EXACT"
block|,
literal|"exact"
block|}
block|,
block|{
name|GIMP_MOTION_MODE_HINT
block|,
literal|"GIMP_MOTION_MODE_HINT"
block|,
literal|"hint"
block|}
block|,
block|{
name|GIMP_MOTION_MODE_COMPRESS
block|,
literal|"GIMP_MOTION_MODE_COMPRESS"
block|,
literal|"compress"
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
DECL|function|gimp_motion_mode_get_type (void)
name|gimp_motion_mode_get_type
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
literal|"GimpMotionMode"
argument_list|,
name|gimp_motion_mode_enum_values
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

begin_decl_stmt
DECL|variable|transform_action_enum_values
specifier|static
specifier|const
name|GEnumValue
name|transform_action_enum_values
index|[]
init|=
block|{
block|{
name|TRANSFORM_CREATING
block|,
literal|"TRANSFORM_CREATING"
block|,
literal|"creating"
block|}
block|,
block|{
name|TRANSFORM_HANDLE_1
block|,
literal|"TRANSFORM_HANDLE_1"
block|,
literal|"handle-1"
block|}
block|,
block|{
name|TRANSFORM_HANDLE_2
block|,
literal|"TRANSFORM_HANDLE_2"
block|,
literal|"handle-2"
block|}
block|,
block|{
name|TRANSFORM_HANDLE_3
block|,
literal|"TRANSFORM_HANDLE_3"
block|,
literal|"handle-3"
block|}
block|,
block|{
name|TRANSFORM_HANDLE_4
block|,
literal|"TRANSFORM_HANDLE_4"
block|,
literal|"handle-4"
block|}
block|,
block|{
name|TRANSFORM_HANDLE_CENTER
block|,
literal|"TRANSFORM_HANDLE_CENTER"
block|,
literal|"handle-center"
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
DECL|function|transform_action_get_type (void)
name|transform_action_get_type
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
literal|"TransformAction"
argument_list|,
name|transform_action_enum_values
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

