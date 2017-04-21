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
file|"operations-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "operations-enums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_layer_color_space_get_type (void)
name|gimp_layer_color_space_get_type
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
name|GIMP_LAYER_COLOR_SPACE_AUTO
block|,
literal|"GIMP_LAYER_COLOR_SPACE_AUTO"
block|,
literal|"auto"
block|}
block|,
block|{
name|GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
block|,
literal|"GIMP_LAYER_COLOR_SPACE_RGB_LINEAR"
block|,
literal|"rgb-linear"
block|}
block|,
block|{
name|GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
block|,
literal|"GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL"
block|,
literal|"rgb-perceptual"
block|}
block|,
block|{
name|GIMP_LAYER_COLOR_SPACE_LAB
block|,
literal|"GIMP_LAYER_COLOR_SPACE_LAB"
block|,
literal|"lab"
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
name|GIMP_LAYER_COLOR_SPACE_AUTO
block|,
name|NC_
argument_list|(
literal|"layer-color-space"
argument_list|,
literal|"Auto"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_COLOR_SPACE_RGB_LINEAR
block|,
name|NC_
argument_list|(
literal|"layer-color-space"
argument_list|,
literal|"RGB (linear)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_COLOR_SPACE_RGB_PERCEPTUAL
block|,
name|NC_
argument_list|(
literal|"layer-color-space"
argument_list|,
literal|"RGB (perceptual)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_COLOR_SPACE_LAB
block|,
name|NC_
argument_list|(
literal|"layer-color-space"
argument_list|,
literal|"LAB"
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
literal|"GimpLayerColorSpace"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"layer-color-space"
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
DECL|function|gimp_layer_composite_mode_get_type (void)
name|gimp_layer_composite_mode_get_type
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
name|GIMP_LAYER_COMPOSITE_AUTO
block|,
literal|"GIMP_LAYER_COMPOSITE_AUTO"
block|,
literal|"auto"
block|}
block|,
block|{
name|GIMP_LAYER_COMPOSITE_SRC_OVER
block|,
literal|"GIMP_LAYER_COMPOSITE_SRC_OVER"
block|,
literal|"src-over"
block|}
block|,
block|{
name|GIMP_LAYER_COMPOSITE_SRC_ATOP
block|,
literal|"GIMP_LAYER_COMPOSITE_SRC_ATOP"
block|,
literal|"src-atop"
block|}
block|,
block|{
name|GIMP_LAYER_COMPOSITE_DST_ATOP
block|,
literal|"GIMP_LAYER_COMPOSITE_DST_ATOP"
block|,
literal|"dst-atop"
block|}
block|,
block|{
name|GIMP_LAYER_COMPOSITE_SRC_IN
block|,
literal|"GIMP_LAYER_COMPOSITE_SRC_IN"
block|,
literal|"src-in"
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
name|GIMP_LAYER_COMPOSITE_AUTO
block|,
name|NC_
argument_list|(
literal|"layer-composite-mode"
argument_list|,
literal|"Auto"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_COMPOSITE_SRC_OVER
block|,
name|NC_
argument_list|(
literal|"layer-composite-mode"
argument_list|,
literal|"Source over"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_COMPOSITE_SRC_ATOP
block|,
name|NC_
argument_list|(
literal|"layer-composite-mode"
argument_list|,
literal|"Source atop"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_COMPOSITE_DST_ATOP
block|,
name|NC_
argument_list|(
literal|"layer-composite-mode"
argument_list|,
literal|"Destination atop"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_COMPOSITE_SRC_IN
block|,
name|NC_
argument_list|(
literal|"layer-composite-mode"
argument_list|,
literal|"Source in"
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
literal|"GimpLayerCompositeMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"layer-composite-mode"
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
DECL|function|gimp_layer_mode_get_type (void)
name|gimp_layer_mode_get_type
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
name|GIMP_LAYER_MODE_NORMAL_LEGACY
block|,
literal|"GIMP_LAYER_MODE_NORMAL_LEGACY"
block|,
literal|"normal-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DISSOLVE
block|,
literal|"GIMP_LAYER_MODE_DISSOLVE"
block|,
literal|"dissolve"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_BEHIND_LEGACY
block|,
literal|"GIMP_LAYER_MODE_BEHIND_LEGACY"
block|,
literal|"behind-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
block|,
literal|"GIMP_LAYER_MODE_MULTIPLY_LEGACY"
block|,
literal|"multiply-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SCREEN_LEGACY
block|,
literal|"GIMP_LAYER_MODE_SCREEN_LEGACY"
block|,
literal|"screen-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
block|,
literal|"GIMP_LAYER_MODE_OVERLAY_LEGACY"
block|,
literal|"overlay-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
block|,
literal|"GIMP_LAYER_MODE_DIFFERENCE_LEGACY"
block|,
literal|"difference-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_ADDITION_LEGACY
block|,
literal|"GIMP_LAYER_MODE_ADDITION_LEGACY"
block|,
literal|"addition-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
block|,
literal|"GIMP_LAYER_MODE_SUBTRACT_LEGACY"
block|,
literal|"subtract-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
block|,
literal|"GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY"
block|,
literal|"darken-only-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
block|,
literal|"GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY"
block|,
literal|"lighten-only-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
block|,
literal|"GIMP_LAYER_MODE_HSV_HUE_LEGACY"
block|,
literal|"hsv-hue-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
block|,
literal|"GIMP_LAYER_MODE_HSV_SATURATION_LEGACY"
block|,
literal|"hsv-saturation-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSL_COLOR_LEGACY
block|,
literal|"GIMP_LAYER_MODE_HSL_COLOR_LEGACY"
block|,
literal|"hsl-color-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
block|,
literal|"GIMP_LAYER_MODE_HSV_VALUE_LEGACY"
block|,
literal|"hsv-value-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
block|,
literal|"GIMP_LAYER_MODE_DIVIDE_LEGACY"
block|,
literal|"divide-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DODGE_LEGACY
block|,
literal|"GIMP_LAYER_MODE_DODGE_LEGACY"
block|,
literal|"dodge-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_BURN_LEGACY
block|,
literal|"GIMP_LAYER_MODE_BURN_LEGACY"
block|,
literal|"burn-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
block|,
literal|"GIMP_LAYER_MODE_HARDLIGHT_LEGACY"
block|,
literal|"hardlight-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
block|,
literal|"GIMP_LAYER_MODE_SOFTLIGHT_LEGACY"
block|,
literal|"softlight-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
block|,
literal|"GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY"
block|,
literal|"grain-extract-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
block|,
literal|"GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY"
block|,
literal|"grain-merge-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_COLOR_ERASE_LEGACY
block|,
literal|"GIMP_LAYER_MODE_COLOR_ERASE_LEGACY"
block|,
literal|"color-erase-legacy"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_OVERLAY
block|,
literal|"GIMP_LAYER_MODE_OVERLAY"
block|,
literal|"overlay"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LCH_HUE
block|,
literal|"GIMP_LAYER_MODE_LCH_HUE"
block|,
literal|"lch-hue"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LCH_CHROMA
block|,
literal|"GIMP_LAYER_MODE_LCH_CHROMA"
block|,
literal|"lch-chroma"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LCH_COLOR
block|,
literal|"GIMP_LAYER_MODE_LCH_COLOR"
block|,
literal|"lch-color"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
block|,
literal|"GIMP_LAYER_MODE_LCH_LIGHTNESS"
block|,
literal|"lch-lightness"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_NORMAL
block|,
literal|"GIMP_LAYER_MODE_NORMAL"
block|,
literal|"normal"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_BEHIND
block|,
literal|"GIMP_LAYER_MODE_BEHIND"
block|,
literal|"behind"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_MULTIPLY
block|,
literal|"GIMP_LAYER_MODE_MULTIPLY"
block|,
literal|"multiply"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SCREEN
block|,
literal|"GIMP_LAYER_MODE_SCREEN"
block|,
literal|"screen"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DIFFERENCE
block|,
literal|"GIMP_LAYER_MODE_DIFFERENCE"
block|,
literal|"difference"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_ADDITION
block|,
literal|"GIMP_LAYER_MODE_ADDITION"
block|,
literal|"addition"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SUBTRACT
block|,
literal|"GIMP_LAYER_MODE_SUBTRACT"
block|,
literal|"subtract"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DARKEN_ONLY
block|,
literal|"GIMP_LAYER_MODE_DARKEN_ONLY"
block|,
literal|"darken-only"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
block|,
literal|"GIMP_LAYER_MODE_LIGHTEN_ONLY"
block|,
literal|"lighten-only"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_HUE
block|,
literal|"GIMP_LAYER_MODE_HSV_HUE"
block|,
literal|"hsv-hue"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_SATURATION
block|,
literal|"GIMP_LAYER_MODE_HSV_SATURATION"
block|,
literal|"hsv-saturation"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSL_COLOR
block|,
literal|"GIMP_LAYER_MODE_HSL_COLOR"
block|,
literal|"hsl-color"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_VALUE
block|,
literal|"GIMP_LAYER_MODE_HSV_VALUE"
block|,
literal|"hsv-value"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DIVIDE
block|,
literal|"GIMP_LAYER_MODE_DIVIDE"
block|,
literal|"divide"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DODGE
block|,
literal|"GIMP_LAYER_MODE_DODGE"
block|,
literal|"dodge"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_BURN
block|,
literal|"GIMP_LAYER_MODE_BURN"
block|,
literal|"burn"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HARDLIGHT
block|,
literal|"GIMP_LAYER_MODE_HARDLIGHT"
block|,
literal|"hardlight"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SOFTLIGHT
block|,
literal|"GIMP_LAYER_MODE_SOFTLIGHT"
block|,
literal|"softlight"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
block|,
literal|"GIMP_LAYER_MODE_GRAIN_EXTRACT"
block|,
literal|"grain-extract"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GRAIN_MERGE
block|,
literal|"GIMP_LAYER_MODE_GRAIN_MERGE"
block|,
literal|"grain-merge"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_VIVID_LIGHT
block|,
literal|"GIMP_LAYER_MODE_VIVID_LIGHT"
block|,
literal|"vivid-light"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_PIN_LIGHT
block|,
literal|"GIMP_LAYER_MODE_PIN_LIGHT"
block|,
literal|"pin-light"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LINEAR_LIGHT
block|,
literal|"GIMP_LAYER_MODE_LINEAR_LIGHT"
block|,
literal|"linear-light"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HARD_MIX
block|,
literal|"GIMP_LAYER_MODE_HARD_MIX"
block|,
literal|"hard-mix"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_EXCLUSION
block|,
literal|"GIMP_LAYER_MODE_EXCLUSION"
block|,
literal|"exclusion"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LINEAR_BURN
block|,
literal|"GIMP_LAYER_MODE_LINEAR_BURN"
block|,
literal|"linear-burn"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
block|,
literal|"GIMP_LAYER_MODE_LUMA_DARKEN_ONLY"
block|,
literal|"luma-darken-only"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
block|,
literal|"GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY"
block|,
literal|"luma-lighten-only"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LUMINANCE
block|,
literal|"GIMP_LAYER_MODE_LUMINANCE"
block|,
literal|"luminance"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_COLOR_ERASE
block|,
literal|"GIMP_LAYER_MODE_COLOR_ERASE"
block|,
literal|"color-erase"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_ERASE
block|,
literal|"GIMP_LAYER_MODE_ERASE"
block|,
literal|"erase"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_MERGE
block|,
literal|"GIMP_LAYER_MODE_MERGE"
block|,
literal|"merge"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SPLIT
block|,
literal|"GIMP_LAYER_MODE_SPLIT"
block|,
literal|"split"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_PASS_THROUGH
block|,
literal|"GIMP_LAYER_MODE_PASS_THROUGH"
block|,
literal|"pass-through"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_REPLACE
block|,
literal|"GIMP_LAYER_MODE_REPLACE"
block|,
literal|"replace"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_ANTI_ERASE
block|,
literal|"GIMP_LAYER_MODE_ANTI_ERASE"
block|,
literal|"anti-erase"
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
name|GIMP_LAYER_MODE_NORMAL_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Normal (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DISSOLVE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Dissolve"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_BEHIND_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Behind (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_MULTIPLY_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Multiply (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SCREEN_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Screen (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_OVERLAY_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Old broken Overlay"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DIFFERENCE_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Difference (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_ADDITION_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Addition (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SUBTRACT_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Subtract (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DARKEN_ONLY_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Darken only (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LIGHTEN_ONLY_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Lighten only (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_HUE_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Hue (HSV) (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_SATURATION_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Saturation (HSV) (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSL_COLOR_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Color (HSL) (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_VALUE_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Value (HSV) (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DIVIDE_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Divide (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DODGE_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Dodge (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_BURN_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Burn (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HARDLIGHT_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Hard light (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SOFTLIGHT_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Soft light (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GRAIN_EXTRACT_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Grain extract (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GRAIN_MERGE_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Grain merge (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_COLOR_ERASE_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Color erase (legacy)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_OVERLAY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Overlay"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LCH_HUE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Hue (LCH)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LCH_CHROMA
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Chroma (LCH)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LCH_COLOR
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Color (LCH)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LCH_LIGHTNESS
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Lightness (LCH)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_NORMAL
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Normal"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_BEHIND
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Behind"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_MULTIPLY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Multiply"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SCREEN
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Screen"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DIFFERENCE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Difference"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_ADDITION
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Addition"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SUBTRACT
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Subtract"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DARKEN_ONLY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Darken only"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LIGHTEN_ONLY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Lighten only"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_HUE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Hue (HSV)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_SATURATION
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Saturation (HSV)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSL_COLOR
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Color (HSL)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HSV_VALUE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Value (HSV)"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DIVIDE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Divide"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_DODGE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Dodge"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_BURN
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Burn"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HARDLIGHT
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Hard light"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SOFTLIGHT
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Soft light"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GRAIN_EXTRACT
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Grain extract"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GRAIN_MERGE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Grain merge"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_VIVID_LIGHT
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Vivid light"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_PIN_LIGHT
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Pin light"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LINEAR_LIGHT
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Linear light"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_HARD_MIX
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Hard mix"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_EXCLUSION
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Exclusion"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LINEAR_BURN
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Linear burn"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LUMA_DARKEN_ONLY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Luma/Luminance darken only"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LUMA_LIGHTEN_ONLY
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Luma/Luminance lighten only"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_LUMINANCE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Luminance"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_COLOR_ERASE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Color erase"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_ERASE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Erase"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_MERGE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Merge"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_SPLIT
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Split"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_PASS_THROUGH
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Pass through"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_REPLACE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Replace"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_ANTI_ERASE
block|,
name|NC_
argument_list|(
literal|"layer-mode"
argument_list|,
literal|"Anti erase"
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
literal|"GimpLayerMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"layer-mode"
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
DECL|function|gimp_layer_mode_group_get_type (void)
name|gimp_layer_mode_group_get_type
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
name|GIMP_LAYER_MODE_GROUP_DEFAULT
block|,
literal|"GIMP_LAYER_MODE_GROUP_DEFAULT"
block|,
literal|"default"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GROUP_LEGACY
block|,
literal|"GIMP_LAYER_MODE_GROUP_LEGACY"
block|,
literal|"legacy"
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
name|GIMP_LAYER_MODE_GROUP_DEFAULT
block|,
name|NC_
argument_list|(
literal|"layer-mode-group"
argument_list|,
literal|"Default"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_GROUP_LEGACY
block|,
name|NC_
argument_list|(
literal|"layer-mode-group"
argument_list|,
literal|"Legacy"
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
literal|"GimpLayerModeGroup"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"layer-mode-group"
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
DECL|function|gimp_layer_mode_context_get_type (void)
name|gimp_layer_mode_context_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
specifier|const
name|GFlagsValue
name|values
index|[]
init|=
block|{
block|{
name|GIMP_LAYER_MODE_CONTEXT_LAYER
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_LAYER"
block|,
literal|"layer"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_CONTEXT_GROUP
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_GROUP"
block|,
literal|"group"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_CONTEXT_PAINT
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_PAINT"
block|,
literal|"paint"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_CONTEXT_FADE
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_FADE"
block|,
literal|"fade"
block|}
block|,
block|{
name|GIMP_LAYER_MODE_CONTEXT_ALL
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_ALL"
block|,
literal|"all"
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
name|GimpFlagsDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_LAYER_MODE_CONTEXT_LAYER
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_LAYER"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_CONTEXT_GROUP
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_GROUP"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_CONTEXT_PAINT
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_PAINT"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_CONTEXT_FADE
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_FADE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_LAYER_MODE_CONTEXT_ALL
block|,
literal|"GIMP_LAYER_MODE_CONTEXT_ALL"
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
name|g_flags_register_static
argument_list|(
literal|"GimpLayerModeContext"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"layer-mode-context"
argument_list|)
expr_stmt|;
name|gimp_flags_set_value_descriptions
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

