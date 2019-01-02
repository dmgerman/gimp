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
comment|/* enumerations from "tools-enums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_bucket_fill_area_get_type (void)
name|gimp_bucket_fill_area_get_type
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
name|GIMP_BUCKET_FILL_SELECTION
block|,
literal|"GIMP_BUCKET_FILL_SELECTION"
block|,
literal|"selection"
block|}
block|,
block|{
name|GIMP_BUCKET_FILL_SIMILAR_COLORS
block|,
literal|"GIMP_BUCKET_FILL_SIMILAR_COLORS"
block|,
literal|"similar-colors"
block|}
block|,
block|{
name|GIMP_BUCKET_FILL_LINE_ART
block|,
literal|"GIMP_BUCKET_FILL_LINE_ART"
block|,
literal|"line-art"
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
name|GIMP_BUCKET_FILL_SELECTION
block|,
name|NC_
argument_list|(
literal|"bucket-fill-area"
argument_list|,
literal|"Fill whole selection"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BUCKET_FILL_SIMILAR_COLORS
block|,
name|NC_
argument_list|(
literal|"bucket-fill-area"
argument_list|,
literal|"Fill similar colors"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_BUCKET_FILL_LINE_ART
block|,
name|NC_
argument_list|(
literal|"bucket-fill-area"
argument_list|,
literal|"Fill by line art detection"
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
literal|"GimpBucketFillArea"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"bucket-fill-area"
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
name|NC_
argument_list|(
literal|"rect-select-mode"
argument_list|,
literal|"Free select"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECT_SELECT_MODE_FIXED_SIZE
block|,
name|NC_
argument_list|(
literal|"rect-select-mode"
argument_list|,
literal|"Fixed size"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_RECT_SELECT_MODE_FIXED_RATIO
block|,
name|NC_
argument_list|(
literal|"rect-select-mode"
argument_list|,
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
literal|"GimpRectSelectMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"rect-select-mode"
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
name|NC_
argument_list|(
literal|"transform-type"
argument_list|,
literal|"Layer"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_TYPE_SELECTION
block|,
name|NC_
argument_list|(
literal|"transform-type"
argument_list|,
literal|"Selection"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TRANSFORM_TYPE_PATH
block|,
name|NC_
argument_list|(
literal|"transform-type"
argument_list|,
literal|"Path"
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
literal|"GimpTransformType"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"transform-type"
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
DECL|function|gimp_tool_action_get_type (void)
name|gimp_tool_action_get_type
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
name|GIMP_TOOL_ACTION_PAUSE
block|,
literal|"GIMP_TOOL_ACTION_PAUSE"
block|,
literal|"pause"
block|}
block|,
block|{
name|GIMP_TOOL_ACTION_RESUME
block|,
literal|"GIMP_TOOL_ACTION_RESUME"
block|,
literal|"resume"
block|}
block|,
block|{
name|GIMP_TOOL_ACTION_HALT
block|,
literal|"GIMP_TOOL_ACTION_HALT"
block|,
literal|"halt"
block|}
block|,
block|{
name|GIMP_TOOL_ACTION_COMMIT
block|,
literal|"GIMP_TOOL_ACTION_COMMIT"
block|,
literal|"commit"
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
name|GIMP_TOOL_ACTION_PAUSE
block|,
literal|"GIMP_TOOL_ACTION_PAUSE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TOOL_ACTION_RESUME
block|,
literal|"GIMP_TOOL_ACTION_RESUME"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TOOL_ACTION_HALT
block|,
literal|"GIMP_TOOL_ACTION_HALT"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TOOL_ACTION_COMMIT
block|,
literal|"GIMP_TOOL_ACTION_COMMIT"
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
literal|"GimpToolAction"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"tool-action"
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
DECL|function|gimp_tool_active_modifiers_get_type (void)
name|gimp_tool_active_modifiers_get_type
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
name|GIMP_TOOL_ACTIVE_MODIFIERS_OFF
block|,
literal|"GIMP_TOOL_ACTIVE_MODIFIERS_OFF"
block|,
literal|"off"
block|}
block|,
block|{
name|GIMP_TOOL_ACTIVE_MODIFIERS_SAME
block|,
literal|"GIMP_TOOL_ACTIVE_MODIFIERS_SAME"
block|,
literal|"same"
block|}
block|,
block|{
name|GIMP_TOOL_ACTIVE_MODIFIERS_SEPARATE
block|,
literal|"GIMP_TOOL_ACTIVE_MODIFIERS_SEPARATE"
block|,
literal|"separate"
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
name|GIMP_TOOL_ACTIVE_MODIFIERS_OFF
block|,
literal|"GIMP_TOOL_ACTIVE_MODIFIERS_OFF"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TOOL_ACTIVE_MODIFIERS_SAME
block|,
literal|"GIMP_TOOL_ACTIVE_MODIFIERS_SAME"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TOOL_ACTIVE_MODIFIERS_SEPARATE
block|,
literal|"GIMP_TOOL_ACTIVE_MODIFIERS_SEPARATE"
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
literal|"GimpToolActiveModifiers"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"tool-active-modifiers"
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
DECL|function|gimp_matting_draw_mode_get_type (void)
name|gimp_matting_draw_mode_get_type
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
name|GIMP_MATTING_DRAW_MODE_FOREGROUND
block|,
literal|"GIMP_MATTING_DRAW_MODE_FOREGROUND"
block|,
literal|"foreground"
block|}
block|,
block|{
name|GIMP_MATTING_DRAW_MODE_BACKGROUND
block|,
literal|"GIMP_MATTING_DRAW_MODE_BACKGROUND"
block|,
literal|"background"
block|}
block|,
block|{
name|GIMP_MATTING_DRAW_MODE_UNKNOWN
block|,
literal|"GIMP_MATTING_DRAW_MODE_UNKNOWN"
block|,
literal|"unknown"
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
name|GIMP_MATTING_DRAW_MODE_FOREGROUND
block|,
name|NC_
argument_list|(
literal|"matting-draw-mode"
argument_list|,
literal|"Draw foreground"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_MATTING_DRAW_MODE_BACKGROUND
block|,
name|NC_
argument_list|(
literal|"matting-draw-mode"
argument_list|,
literal|"Draw background"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_MATTING_DRAW_MODE_UNKNOWN
block|,
name|NC_
argument_list|(
literal|"matting-draw-mode"
argument_list|,
literal|"Draw unknown"
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
literal|"GimpMattingDrawMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"matting-draw-mode"
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
DECL|function|gimp_warp_behavior_get_type (void)
name|gimp_warp_behavior_get_type
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
name|GIMP_WARP_BEHAVIOR_MOVE
block|,
literal|"GIMP_WARP_BEHAVIOR_MOVE"
block|,
literal|"move"
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_GROW
block|,
literal|"GIMP_WARP_BEHAVIOR_GROW"
block|,
literal|"grow"
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_SHRINK
block|,
literal|"GIMP_WARP_BEHAVIOR_SHRINK"
block|,
literal|"shrink"
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_SWIRL_CW
block|,
literal|"GIMP_WARP_BEHAVIOR_SWIRL_CW"
block|,
literal|"swirl-cw"
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_SWIRL_CCW
block|,
literal|"GIMP_WARP_BEHAVIOR_SWIRL_CCW"
block|,
literal|"swirl-ccw"
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_ERASE
block|,
literal|"GIMP_WARP_BEHAVIOR_ERASE"
block|,
literal|"erase"
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_SMOOTH
block|,
literal|"GIMP_WARP_BEHAVIOR_SMOOTH"
block|,
literal|"smooth"
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
name|GIMP_WARP_BEHAVIOR_MOVE
block|,
name|NC_
argument_list|(
literal|"warp-behavior"
argument_list|,
literal|"Move pixels"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_GROW
block|,
name|NC_
argument_list|(
literal|"warp-behavior"
argument_list|,
literal|"Grow area"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_SHRINK
block|,
name|NC_
argument_list|(
literal|"warp-behavior"
argument_list|,
literal|"Shrink area"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_SWIRL_CW
block|,
name|NC_
argument_list|(
literal|"warp-behavior"
argument_list|,
literal|"Swirl clockwise"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_SWIRL_CCW
block|,
name|NC_
argument_list|(
literal|"warp-behavior"
argument_list|,
literal|"Swirl counter-clockwise"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_ERASE
block|,
name|NC_
argument_list|(
literal|"warp-behavior"
argument_list|,
literal|"Erase warping"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WARP_BEHAVIOR_SMOOTH
block|,
name|NC_
argument_list|(
literal|"warp-behavior"
argument_list|,
literal|"Smooth warping"
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
literal|"GimpWarpBehavior"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"warp-behavior"
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

