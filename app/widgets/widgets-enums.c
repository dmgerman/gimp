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
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"widgets-enums.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/* enumerations from "./widgets-enums.h" */
end_comment

begin_function
name|GType
DECL|function|gimp_active_color_get_type (void)
name|gimp_active_color_get_type
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
name|GIMP_ACTIVE_COLOR_FOREGROUND
block|,
literal|"GIMP_ACTIVE_COLOR_FOREGROUND"
block|,
literal|"foreground"
block|}
block|,
block|{
name|GIMP_ACTIVE_COLOR_BACKGROUND
block|,
literal|"GIMP_ACTIVE_COLOR_BACKGROUND"
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
specifier|static
specifier|const
name|GimpEnumDesc
name|descs
index|[]
init|=
block|{
block|{
name|GIMP_ACTIVE_COLOR_FOREGROUND
block|,
name|NC_
argument_list|(
literal|"active-color"
argument_list|,
literal|"Foreground"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_ACTIVE_COLOR_BACKGROUND
block|,
name|NC_
argument_list|(
literal|"active-color"
argument_list|,
literal|"Background"
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
literal|"GimpActiveColor"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"active-color"
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
DECL|function|gimp_color_dialog_state_get_type (void)
name|gimp_color_dialog_state_get_type
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
name|GIMP_COLOR_DIALOG_OK
block|,
literal|"GIMP_COLOR_DIALOG_OK"
block|,
literal|"ok"
block|}
block|,
block|{
name|GIMP_COLOR_DIALOG_CANCEL
block|,
literal|"GIMP_COLOR_DIALOG_CANCEL"
block|,
literal|"cancel"
block|}
block|,
block|{
name|GIMP_COLOR_DIALOG_UPDATE
block|,
literal|"GIMP_COLOR_DIALOG_UPDATE"
block|,
literal|"update"
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
name|GIMP_COLOR_DIALOG_OK
block|,
literal|"GIMP_COLOR_DIALOG_OK"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_DIALOG_CANCEL
block|,
literal|"GIMP_COLOR_DIALOG_CANCEL"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_DIALOG_UPDATE
block|,
literal|"GIMP_COLOR_DIALOG_UPDATE"
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
literal|"GimpColorDialogState"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"color-dialog-state"
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
DECL|function|gimp_color_frame_mode_get_type (void)
name|gimp_color_frame_mode_get_type
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
name|GIMP_COLOR_FRAME_MODE_PIXEL
block|,
literal|"GIMP_COLOR_FRAME_MODE_PIXEL"
block|,
literal|"pixel"
block|}
block|,
block|{
name|GIMP_COLOR_FRAME_MODE_RGB
block|,
literal|"GIMP_COLOR_FRAME_MODE_RGB"
block|,
literal|"rgb"
block|}
block|,
block|{
name|GIMP_COLOR_FRAME_MODE_HSV
block|,
literal|"GIMP_COLOR_FRAME_MODE_HSV"
block|,
literal|"hsv"
block|}
block|,
block|{
name|GIMP_COLOR_FRAME_MODE_CMYK
block|,
literal|"GIMP_COLOR_FRAME_MODE_CMYK"
block|,
literal|"cmyk"
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
name|GIMP_COLOR_FRAME_MODE_PIXEL
block|,
name|NC_
argument_list|(
literal|"color-frame-mode"
argument_list|,
literal|"Pixel"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_FRAME_MODE_RGB
block|,
name|NC_
argument_list|(
literal|"color-frame-mode"
argument_list|,
literal|"RGB"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_FRAME_MODE_HSV
block|,
name|NC_
argument_list|(
literal|"color-frame-mode"
argument_list|,
literal|"HSV"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_FRAME_MODE_CMYK
block|,
name|NC_
argument_list|(
literal|"color-frame-mode"
argument_list|,
literal|"CMYK"
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
literal|"GimpColorFrameMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"color-frame-mode"
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
name|NC_
argument_list|(
literal|"color-pick-mode"
argument_list|,
literal|"Pick only"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_FOREGROUND
block|,
name|NC_
argument_list|(
literal|"color-pick-mode"
argument_list|,
literal|"Set foreground color"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_BACKGROUND
block|,
name|NC_
argument_list|(
literal|"color-pick-mode"
argument_list|,
literal|"Set background color"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_PICK_MODE_PALETTE
block|,
name|NC_
argument_list|(
literal|"color-pick-mode"
argument_list|,
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
literal|"GimpColorPickMode"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"color-pick-mode"
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
DECL|function|gimp_color_pick_state_get_type (void)
name|gimp_color_pick_state_get_type
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
name|GIMP_COLOR_PICK_STATE_NEW
block|,
literal|"GIMP_COLOR_PICK_STATE_NEW"
block|,
literal|"new"
block|}
block|,
block|{
name|GIMP_COLOR_PICK_STATE_UPDATE
block|,
literal|"GIMP_COLOR_PICK_STATE_UPDATE"
block|,
literal|"update"
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
name|GIMP_COLOR_PICK_STATE_NEW
block|,
literal|"GIMP_COLOR_PICK_STATE_NEW"
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_COLOR_PICK_STATE_UPDATE
block|,
literal|"GIMP_COLOR_PICK_STATE_UPDATE"
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
literal|"GimpColorPickState"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"color-pick-state"
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
DECL|function|gimp_cursor_format_get_type (void)
name|gimp_cursor_format_get_type
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
name|GIMP_CURSOR_FORMAT_BITMAP
block|,
literal|"GIMP_CURSOR_FORMAT_BITMAP"
block|,
literal|"bitmap"
block|}
block|,
block|{
name|GIMP_CURSOR_FORMAT_PIXBUF
block|,
literal|"GIMP_CURSOR_FORMAT_PIXBUF"
block|,
literal|"pixbuf"
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
name|GIMP_CURSOR_FORMAT_BITMAP
block|,
name|NC_
argument_list|(
literal|"cursor-format"
argument_list|,
literal|"Black& white"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_CURSOR_FORMAT_PIXBUF
block|,
name|NC_
argument_list|(
literal|"cursor-format"
argument_list|,
literal|"Fancy"
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
literal|"GimpCursorFormat"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"cursor-format"
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
DECL|function|gimp_help_browser_type_get_type (void)
name|gimp_help_browser_type_get_type
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
name|GIMP_HELP_BROWSER_GIMP
block|,
literal|"GIMP_HELP_BROWSER_GIMP"
block|,
literal|"gimp"
block|}
block|,
block|{
name|GIMP_HELP_BROWSER_WEB_BROWSER
block|,
literal|"GIMP_HELP_BROWSER_WEB_BROWSER"
block|,
literal|"web-browser"
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
name|GIMP_HELP_BROWSER_GIMP
block|,
name|NC_
argument_list|(
literal|"help-browser-type"
argument_list|,
literal|"GIMP help browser"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HELP_BROWSER_WEB_BROWSER
block|,
name|NC_
argument_list|(
literal|"help-browser-type"
argument_list|,
literal|"Web browser"
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
literal|"GimpHelpBrowserType"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"help-browser-type"
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
DECL|function|gimp_histogram_scale_get_type (void)
name|gimp_histogram_scale_get_type
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
name|GIMP_HISTOGRAM_SCALE_LINEAR
block|,
literal|"GIMP_HISTOGRAM_SCALE_LINEAR"
block|,
literal|"linear"
block|}
block|,
block|{
name|GIMP_HISTOGRAM_SCALE_LOGARITHMIC
block|,
literal|"GIMP_HISTOGRAM_SCALE_LOGARITHMIC"
block|,
literal|"logarithmic"
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
name|GIMP_HISTOGRAM_SCALE_LINEAR
block|,
name|NC_
argument_list|(
literal|"histogram-scale"
argument_list|,
literal|"Linear histogram"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_HISTOGRAM_SCALE_LOGARITHMIC
block|,
name|NC_
argument_list|(
literal|"histogram-scale"
argument_list|,
literal|"Logarithmic histogram"
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
literal|"GimpHistogramScale"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"histogram-scale"
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
DECL|function|gimp_tab_style_get_type (void)
name|gimp_tab_style_get_type
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
name|GIMP_TAB_STYLE_ICON
block|,
literal|"GIMP_TAB_STYLE_ICON"
block|,
literal|"icon"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_PREVIEW
block|,
literal|"GIMP_TAB_STYLE_PREVIEW"
block|,
literal|"preview"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_NAME
block|,
literal|"GIMP_TAB_STYLE_NAME"
block|,
literal|"name"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_BLURB
block|,
literal|"GIMP_TAB_STYLE_BLURB"
block|,
literal|"blurb"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_ICON_NAME
block|,
literal|"GIMP_TAB_STYLE_ICON_NAME"
block|,
literal|"icon-name"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_ICON_BLURB
block|,
literal|"GIMP_TAB_STYLE_ICON_BLURB"
block|,
literal|"icon-blurb"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_PREVIEW_NAME
block|,
literal|"GIMP_TAB_STYLE_PREVIEW_NAME"
block|,
literal|"preview-name"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_PREVIEW_BLURB
block|,
literal|"GIMP_TAB_STYLE_PREVIEW_BLURB"
block|,
literal|"preview-blurb"
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
name|GIMP_TAB_STYLE_ICON
block|,
name|NC_
argument_list|(
literal|"tab-style"
argument_list|,
literal|"Icon"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TAB_STYLE_PREVIEW
block|,
name|NC_
argument_list|(
literal|"tab-style"
argument_list|,
literal|"Current status"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TAB_STYLE_NAME
block|,
name|NC_
argument_list|(
literal|"tab-style"
argument_list|,
literal|"Text"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TAB_STYLE_BLURB
block|,
name|NC_
argument_list|(
literal|"tab-style"
argument_list|,
literal|"Description"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TAB_STYLE_ICON_NAME
block|,
name|NC_
argument_list|(
literal|"tab-style"
argument_list|,
literal|"Icon& text"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TAB_STYLE_ICON_BLURB
block|,
name|NC_
argument_list|(
literal|"tab-style"
argument_list|,
literal|"Icon& desc"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TAB_STYLE_PREVIEW_NAME
block|,
name|NC_
argument_list|(
literal|"tab-style"
argument_list|,
literal|"Status& text"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_TAB_STYLE_PREVIEW_BLURB
block|,
name|NC_
argument_list|(
literal|"tab-style"
argument_list|,
literal|"Status& desc"
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
literal|"GimpTabStyle"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"tab-style"
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
DECL|function|gimp_window_hint_get_type (void)
name|gimp_window_hint_get_type
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
name|GIMP_WINDOW_HINT_NORMAL
block|,
literal|"GIMP_WINDOW_HINT_NORMAL"
block|,
literal|"normal"
block|}
block|,
block|{
name|GIMP_WINDOW_HINT_UTILITY
block|,
literal|"GIMP_WINDOW_HINT_UTILITY"
block|,
literal|"utility"
block|}
block|,
block|{
name|GIMP_WINDOW_HINT_KEEP_ABOVE
block|,
literal|"GIMP_WINDOW_HINT_KEEP_ABOVE"
block|,
literal|"keep-above"
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
name|GIMP_WINDOW_HINT_NORMAL
block|,
name|NC_
argument_list|(
literal|"window-hint"
argument_list|,
literal|"Normal window"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WINDOW_HINT_UTILITY
block|,
name|NC_
argument_list|(
literal|"window-hint"
argument_list|,
literal|"Utility window"
argument_list|)
block|,
name|NULL
block|}
block|,
block|{
name|GIMP_WINDOW_HINT_KEEP_ABOVE
block|,
name|NC_
argument_list|(
literal|"window-hint"
argument_list|,
literal|"Keep above"
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
literal|"GimpWindowHint"
argument_list|,
name|values
argument_list|)
expr_stmt|;
name|gimp_type_set_translation_context
argument_list|(
name|type
argument_list|,
literal|"window-hint"
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

