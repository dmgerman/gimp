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

begin_decl_stmt
DECL|variable|gimp_aspect_type_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_aspect_type_enum_values
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
name|N_
argument_list|(
literal|"Portrait"
argument_list|)
block|,
literal|"portrait"
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
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_aspect_type_get_type (void)
name|gimp_aspect_type_get_type
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
literal|"GimpAspectType"
argument_list|,
name|gimp_aspect_type_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_help_browser_type_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_help_browser_type_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_HELP_BROWSER_GIMP
block|,
name|N_
argument_list|(
literal|"Internal"
argument_list|)
block|,
literal|"gimp"
block|}
block|,
block|{
name|GIMP_HELP_BROWSER_NETSCAPE
block|,
name|N_
argument_list|(
literal|"Netscape"
argument_list|)
block|,
literal|"netscape"
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
DECL|function|gimp_help_browser_type_get_type (void)
name|gimp_help_browser_type_get_type
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
literal|"GimpHelpBrowserType"
argument_list|,
name|gimp_help_browser_type_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_histogram_scale_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_histogram_scale_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_HISTOGRAM_SCALE_LINEAR
block|,
name|N_
argument_list|(
literal|"Linear"
argument_list|)
block|,
literal|"linear"
block|}
block|,
block|{
name|GIMP_HISTOGRAM_SCALE_LOGARITHMIC
block|,
name|N_
argument_list|(
literal|"Logarithmic"
argument_list|)
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
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_histogram_scale_get_type (void)
name|gimp_histogram_scale_get_type
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
literal|"GimpHistogramScale"
argument_list|,
name|gimp_histogram_scale_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_tab_style_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_tab_style_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_TAB_STYLE_ICON
block|,
name|N_
argument_list|(
literal|"Icon"
argument_list|)
block|,
literal|"icon"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_NAME
block|,
name|N_
argument_list|(
literal|"Text"
argument_list|)
block|,
literal|"name"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_ICON_NAME
block|,
name|N_
argument_list|(
literal|"Icon& Text"
argument_list|)
block|,
literal|"icon-name"
block|}
block|,
block|{
name|GIMP_TAB_STYLE_ICON_BLURB
block|,
name|N_
argument_list|(
literal|"Icon& Desc"
argument_list|)
block|,
literal|"icon-blurb"
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
DECL|function|gimp_tab_style_get_type (void)
name|gimp_tab_style_get_type
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
literal|"GimpTabStyle"
argument_list|,
name|gimp_tab_style_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_view_type_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_view_type_enum_values
index|[]
init|=
block|{
block|{
name|GIMP_VIEW_TYPE_LIST
block|,
name|N_
argument_list|(
literal|"View as List"
argument_list|)
block|,
literal|"list"
block|}
block|,
block|{
name|GIMP_VIEW_TYPE_GRID
block|,
name|N_
argument_list|(
literal|"View as Grid"
argument_list|)
block|,
literal|"grid"
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
DECL|function|gimp_view_type_get_type (void)
name|gimp_view_type_get_type
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
literal|"GimpViewType"
argument_list|,
name|gimp_view_type_enum_values
argument_list|)
expr_stmt|;
return|return
name|enum_type
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|gimp_zoom_type_enum_values
specifier|static
specifier|const
name|GEnumValue
name|gimp_zoom_type_enum_values
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
literal|"in"
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
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_zoom_type_get_type (void)
name|gimp_zoom_type_get_type
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
literal|"GimpZoomType"
argument_list|,
name|gimp_zoom_type_enum_values
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

