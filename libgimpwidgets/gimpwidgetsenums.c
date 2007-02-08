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
file|"gimpwidgetsenums.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./gimpwidgetsenums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_aspect_type_get_type (void)
name|gimp_aspect_type_get_type
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
name|GIMP_ASPECT_SQUARE
block|,
literal|"GIMP_ASPECT_SQUARE"
block|,
literal|"square"
block|}
block|,
block|{
name|GIMP_ASPECT_PORTRAIT
block|,
literal|"GIMP_ASPECT_PORTRAIT"
block|,
literal|"portrait"
block|}
block|,
block|{
name|GIMP_ASPECT_LANDSCAPE
block|,
literal|"GIMP_ASPECT_LANDSCAPE"
block|,
literal|"landscape"
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
name|GIMP_ASPECT_SQUARE
block|,
name|N_
argument_list|(
literal|"Square"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ASPECT_PORTRAIT
block|,
name|N_
argument_list|(
literal|"Portrait"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ASPECT_LANDSCAPE
block|,
name|N_
argument_list|(
literal|"Landscape"
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
literal|"GimpAspectType"
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
DECL|function|gimp_chain_position_get_type (void)
name|gimp_chain_position_get_type
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
name|GIMP_CHAIN_TOP
block|,
literal|"GIMP_CHAIN_TOP"
block|,
literal|"top"
block|}
block|,
block|{
name|GIMP_CHAIN_LEFT
block|,
literal|"GIMP_CHAIN_LEFT"
block|,
literal|"left"
block|}
block|,
block|{
name|GIMP_CHAIN_BOTTOM
block|,
literal|"GIMP_CHAIN_BOTTOM"
block|,
literal|"bottom"
block|}
block|,
block|{
name|GIMP_CHAIN_RIGHT
block|,
literal|"GIMP_CHAIN_RIGHT"
block|,
literal|"right"
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
name|GIMP_CHAIN_TOP
block|,
literal|"GIMP_CHAIN_TOP"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CHAIN_LEFT
block|,
literal|"GIMP_CHAIN_LEFT"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CHAIN_BOTTOM
block|,
literal|"GIMP_CHAIN_BOTTOM"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CHAIN_RIGHT
block|,
literal|"GIMP_CHAIN_RIGHT"
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
literal|"GimpChainPosition"
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
DECL|function|gimp_color_area_type_get_type (void)
name|gimp_color_area_type_get_type
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
name|GIMP_COLOR_AREA_FLAT
block|,
literal|"GIMP_COLOR_AREA_FLAT"
block|,
literal|"flat"
block|}
block|,
block|{
name|GIMP_COLOR_AREA_SMALL_CHECKS
block|,
literal|"GIMP_COLOR_AREA_SMALL_CHECKS"
block|,
literal|"small-checks"
block|}
block|,
block|{
name|GIMP_COLOR_AREA_LARGE_CHECKS
block|,
literal|"GIMP_COLOR_AREA_LARGE_CHECKS"
block|,
literal|"large-checks"
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
name|GIMP_COLOR_AREA_FLAT
block|,
literal|"GIMP_COLOR_AREA_FLAT"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_AREA_SMALL_CHECKS
block|,
literal|"GIMP_COLOR_AREA_SMALL_CHECKS"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_AREA_LARGE_CHECKS
block|,
literal|"GIMP_COLOR_AREA_LARGE_CHECKS"
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
literal|"GimpColorAreaType"
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
DECL|function|gimp_color_selector_channel_get_type (void)
name|gimp_color_selector_channel_get_type
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
name|GIMP_COLOR_SELECTOR_HUE
block|,
literal|"GIMP_COLOR_SELECTOR_HUE"
block|,
literal|"hue"
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_SATURATION
block|,
literal|"GIMP_COLOR_SELECTOR_SATURATION"
block|,
literal|"saturation"
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_VALUE
block|,
literal|"GIMP_COLOR_SELECTOR_VALUE"
block|,
literal|"value"
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_RED
block|,
literal|"GIMP_COLOR_SELECTOR_RED"
block|,
literal|"red"
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_GREEN
block|,
literal|"GIMP_COLOR_SELECTOR_GREEN"
block|,
literal|"green"
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_BLUE
block|,
literal|"GIMP_COLOR_SELECTOR_BLUE"
block|,
literal|"blue"
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_ALPHA
block|,
literal|"GIMP_COLOR_SELECTOR_ALPHA"
block|,
literal|"alpha"
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
name|GIMP_COLOR_SELECTOR_HUE
block|,
name|N_
argument_list|(
literal|"_H"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Hue"
argument_list|)
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_SATURATION
block|,
name|N_
argument_list|(
literal|"_S"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Saturation"
argument_list|)
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_VALUE
block|,
name|N_
argument_list|(
literal|"_V"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Value"
argument_list|)
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_RED
block|,
name|N_
argument_list|(
literal|"_R"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Red"
argument_list|)
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_GREEN
block|,
name|N_
argument_list|(
literal|"_G"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Green"
argument_list|)
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_BLUE
block|,
name|N_
argument_list|(
literal|"_B"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Blue"
argument_list|)
block|}
block|,
block|{
name|GIMP_COLOR_SELECTOR_ALPHA
block|,
name|N_
argument_list|(
literal|"_A"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Alpha"
argument_list|)
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
literal|"GimpColorSelectorChannel"
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
DECL|function|gimp_page_selector_target_get_type (void)
name|gimp_page_selector_target_get_type
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
name|GIMP_PAGE_SELECTOR_TARGET_LAYERS
block|,
literal|"GIMP_PAGE_SELECTOR_TARGET_LAYERS"
block|,
literal|"layers"
block|}
block|,
block|{
name|GIMP_PAGE_SELECTOR_TARGET_IMAGES
block|,
literal|"GIMP_PAGE_SELECTOR_TARGET_IMAGES"
block|,
literal|"images"
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
name|GIMP_PAGE_SELECTOR_TARGET_LAYERS
block|,
name|N_
argument_list|(
literal|"Layers"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_PAGE_SELECTOR_TARGET_IMAGES
block|,
name|N_
argument_list|(
literal|"Images"
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
literal|"GimpPageSelectorTarget"
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
DECL|function|gimp_size_entry_update_policy_get_type (void)
name|gimp_size_entry_update_policy_get_type
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
name|GIMP_SIZE_ENTRY_UPDATE_NONE
block|,
literal|"GIMP_SIZE_ENTRY_UPDATE_NONE"
block|,
literal|"none"
block|}
block|,
block|{
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
block|,
literal|"GIMP_SIZE_ENTRY_UPDATE_SIZE"
block|,
literal|"size"
block|}
block|,
block|{
name|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
block|,
literal|"GIMP_SIZE_ENTRY_UPDATE_RESOLUTION"
block|,
literal|"resolution"
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
name|GIMP_SIZE_ENTRY_UPDATE_NONE
block|,
literal|"GIMP_SIZE_ENTRY_UPDATE_NONE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SIZE_ENTRY_UPDATE_SIZE
block|,
literal|"GIMP_SIZE_ENTRY_UPDATE_SIZE"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_SIZE_ENTRY_UPDATE_RESOLUTION
block|,
literal|"GIMP_SIZE_ENTRY_UPDATE_RESOLUTION"
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
literal|"GimpSizeEntryUpdatePolicy"
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
DECL|function|gimp_zoom_type_get_type (void)
name|gimp_zoom_type_get_type
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
name|GIMP_ZOOM_IN
block|,
literal|"GIMP_ZOOM_IN"
block|,
literal|"in"
block|}
block|,
block|{
name|GIMP_ZOOM_OUT
block|,
literal|"GIMP_ZOOM_OUT"
block|,
literal|"out"
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
name|GIMP_ZOOM_IN
block|,
name|N_
argument_list|(
literal|"Zoom in"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ZOOM_OUT
block|,
name|N_
argument_list|(
literal|"Zoom out"
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
literal|"GimpZoomType"
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

