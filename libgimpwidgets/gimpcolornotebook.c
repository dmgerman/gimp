begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpcolornotebook.c  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * based on color_notebook module  * Copyright (C) 1998 Austin Donnelly<austin@greenend.org.uk>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolornotebook.h"
end_include

begin_include
include|#
directive|include
file|"gimpcolorscales.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgetsmarshal.h"
end_include

begin_include
include|#
directive|include
file|"gimp3migration.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/libgimp-intl.h"
end_include

begin_comment
comment|/**  * SECTION: gimpcolornotebook  * @title: GimpColorNotebook  * @short_description: A #GimpColorSelector implementation.  *  * The #GimpColorNotebook widget is an implementation of a  * #GimpColorSelector. It serves as a container for  * #GimpColorSelectors.  **/
end_comment

begin_define
DECL|macro|DEFAULT_TAB_BORDER
define|#
directive|define
name|DEFAULT_TAB_BORDER
value|0
end_define

begin_define
DECL|macro|DEFAULT_TAB_ICON_SIZE
define|#
directive|define
name|DEFAULT_TAB_ICON_SIZE
value|GTK_ICON_SIZE_BUTTON
end_define

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_togg_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_togg_sensitive
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_set_show_alpha
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_set_channel
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_switch_page
parameter_list|(
name|GtkNotebook
modifier|*
name|gtk_notebook
parameter_list|,
name|gpointer
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_color_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|page
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_channel_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|page
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_color_notebook_add_page
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|,
name|GType
name|page_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_color_notebook_remove_selector
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpColorNotebook,gimp_color_notebook,GIMP_TYPE_COLOR_SELECTOR)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpColorNotebook
argument_list|,
argument|gimp_color_notebook
argument_list|,
argument|GIMP_TYPE_COLOR_SELECTOR
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_color_notebook_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_color_notebook_class_init
parameter_list|(
name|GimpColorNotebookClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkWidgetClass
modifier|*
name|widget_class
init|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpColorSelectorClass
modifier|*
name|selector_class
init|=
name|GIMP_COLOR_SELECTOR_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_color_notebook_style_set
expr_stmt|;
name|selector_class
operator|->
name|name
operator|=
literal|"Notebook"
expr_stmt|;
name|selector_class
operator|->
name|help_id
operator|=
literal|"gimp-colorselector-notebook"
expr_stmt|;
name|selector_class
operator|->
name|set_toggles_visible
operator|=
name|gimp_color_notebook_togg_visible
expr_stmt|;
name|selector_class
operator|->
name|set_toggles_sensitive
operator|=
name|gimp_color_notebook_togg_sensitive
expr_stmt|;
name|selector_class
operator|->
name|set_show_alpha
operator|=
name|gimp_color_notebook_set_show_alpha
expr_stmt|;
name|selector_class
operator|->
name|set_color
operator|=
name|gimp_color_notebook_set_color
expr_stmt|;
name|selector_class
operator|->
name|set_channel
operator|=
name|gimp_color_notebook_set_channel
expr_stmt|;
name|selector_class
operator|->
name|set_config
operator|=
name|gimp_color_notebook_set_config
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"tab-border"
argument_list|,
name|NULL
argument_list|,
literal|"Width of the border around the tab contents"
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_TAB_BORDER
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"tab-icon-size"
argument_list|,
name|NULL
argument_list|,
literal|"Size for icons displayed in the tab"
argument_list|,
name|GTK_TYPE_ICON_SIZE
argument_list|,
name|DEFAULT_TAB_ICON_SIZE
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_init (GimpColorNotebook * notebook)
name|gimp_color_notebook_init
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|GType
modifier|*
name|selector_types
decl_stmt|;
name|guint
name|n_selector_types
decl_stmt|;
name|guint
name|i
decl_stmt|;
name|notebook
operator|->
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_notebook_popup_enable
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|notebook
operator|->
name|notebook
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|,
literal|"switch-page"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_notebook_switch_page
argument_list|)
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|,
literal|"remove"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_notebook_remove_selector
argument_list|)
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|selector_types
operator|=
name|g_type_children
argument_list|(
name|GIMP_TYPE_COLOR_SELECTOR
argument_list|,
operator|&
name|n_selector_types
argument_list|)
expr_stmt|;
if|if
condition|(
name|n_selector_types
operator|==
literal|2
condition|)
block|{
name|gtk_notebook_set_show_tabs
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_notebook_set_show_border
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_selector_types
condition|;
name|i
operator|++
control|)
block|{
comment|/*  skip ourselves  */
if|if
condition|(
name|g_type_is_a
argument_list|(
name|selector_types
index|[
name|i
index|]
argument_list|,
name|GIMP_TYPE_COLOR_NOTEBOOK
argument_list|)
condition|)
continue|continue;
comment|/*  skip the "Scales" color selector  */
if|if
condition|(
name|g_type_is_a
argument_list|(
name|selector_types
index|[
name|i
index|]
argument_list|,
name|GIMP_TYPE_COLOR_SCALES
argument_list|)
condition|)
continue|continue;
name|gimp_color_notebook_add_page
argument_list|(
name|notebook
argument_list|,
name|selector_types
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|g_free
argument_list|(
name|selector_types
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_color_notebook_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
init|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|tab_border
decl_stmt|;
name|GtkIconSize
name|icon_size
decl_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"tab-border"
argument_list|,
operator|&
name|tab_border
argument_list|,
literal|"tab-icon_size"
argument_list|,
operator|&
name|icon_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|,
literal|"tab-border"
argument_list|,
name|tab_border
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|notebook
operator|->
name|selectors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|selector_class
operator|->
name|icon_name
argument_list|,
name|icon_size
argument_list|)
expr_stmt|;
name|gtk_notebook_set_tab_label
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|list
operator|->
name|data
argument_list|)
argument_list|,
name|image
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_togg_visible (GimpColorSelector * selector,gboolean visible)
name|gimp_color_notebook_togg_visible
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|visible
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
init|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|notebook
operator|->
name|selectors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorSelector
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_color_selector_set_toggles_visible
argument_list|(
name|child
argument_list|,
name|visible
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_togg_sensitive (GimpColorSelector * selector,gboolean sensitive)
name|gimp_color_notebook_togg_sensitive
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
init|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|notebook
operator|->
name|selectors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorSelector
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_color_selector_set_toggles_sensitive
argument_list|(
name|child
argument_list|,
name|sensitive
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_set_show_alpha (GimpColorSelector * selector,gboolean show_alpha)
name|gimp_color_notebook_set_show_alpha
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
init|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|notebook
operator|->
name|selectors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorSelector
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_color_selector_set_show_alpha
argument_list|(
name|child
argument_list|,
name|show_alpha
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_set_color (GimpColorSelector * selector,const GimpRGB * rgb,const GimpHSV * hsv)
name|gimp_color_notebook_set_color
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
init|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|gimp_color_notebook_color_changed
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_color
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|rgb
argument_list|,
name|hsv
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|gimp_color_notebook_color_changed
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_set_channel (GimpColorSelector * selector,GimpColorSelectorChannel channel)
name|gimp_color_notebook_set_channel
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
init|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|gimp_color_notebook_channel_changed
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_channel
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|channel
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|gimp_color_notebook_channel_changed
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_set_config (GimpColorSelector * selector,GimpColorConfig * config)
name|gimp_color_notebook_set_config
parameter_list|(
name|GimpColorSelector
modifier|*
name|selector
parameter_list|,
name|GimpColorConfig
modifier|*
name|config
parameter_list|)
block|{
name|GimpColorNotebook
modifier|*
name|notebook
init|=
name|GIMP_COLOR_NOTEBOOK
argument_list|(
name|selector
argument_list|)
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|notebook
operator|->
name|selectors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorSelector
modifier|*
name|child
init|=
name|list
operator|->
name|data
decl_stmt|;
name|gimp_color_selector_set_config
argument_list|(
name|child
argument_list|,
name|config
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_switch_page (GtkNotebook * gtk_notebook,gpointer page,guint page_num,GimpColorNotebook * notebook)
name|gimp_color_notebook_switch_page
parameter_list|(
name|GtkNotebook
modifier|*
name|gtk_notebook
parameter_list|,
name|gpointer
name|page
parameter_list|,
name|guint
name|page_num
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|notebook
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|page_widget
decl_stmt|;
name|page_widget
operator|=
name|gtk_notebook_get_nth_page
argument_list|(
name|gtk_notebook
argument_list|,
name|page_num
argument_list|)
expr_stmt|;
name|notebook
operator|->
name|cur_page
operator|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|page_widget
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|gimp_color_notebook_color_changed
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|g_signal_handlers_block_by_func
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|gimp_color_notebook_channel_changed
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_color
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|selector
operator|->
name|hsv
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_channel
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|selector
operator|->
name|channel
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|gimp_color_notebook_color_changed
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|notebook
operator|->
name|cur_page
argument_list|,
name|gimp_color_notebook_channel_changed
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_color_changed (GimpColorSelector * page,const GimpRGB * rgb,const GimpHSV * hsv,GimpColorNotebook * notebook)
name|gimp_color_notebook_color_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|page
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|rgb
parameter_list|,
specifier|const
name|GimpHSV
modifier|*
name|hsv
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|notebook
argument_list|)
decl_stmt|;
name|selector
operator|->
name|rgb
operator|=
operator|*
name|rgb
expr_stmt|;
name|selector
operator|->
name|hsv
operator|=
operator|*
name|hsv
expr_stmt|;
name|gimp_color_selector_color_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_channel_changed (GimpColorSelector * page,GimpColorSelectorChannel channel,GimpColorNotebook * notebook)
name|gimp_color_notebook_channel_changed
parameter_list|(
name|GimpColorSelector
modifier|*
name|page
parameter_list|,
name|GimpColorSelectorChannel
name|channel
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|notebook
argument_list|)
decl_stmt|;
name|selector
operator|->
name|channel
operator|=
name|channel
expr_stmt|;
name|gimp_color_selector_channel_changed
argument_list|(
name|selector
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_color_notebook_add_page (GimpColorNotebook * notebook,GType page_type)
name|gimp_color_notebook_add_page
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|,
name|GType
name|page_type
parameter_list|)
block|{
name|GimpColorSelector
modifier|*
name|selector
init|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|notebook
argument_list|)
decl_stmt|;
name|GimpColorSelectorClass
modifier|*
name|selector_class
decl_stmt|;
name|GtkWidget
modifier|*
name|page
decl_stmt|;
name|GtkWidget
modifier|*
name|menu_widget
decl_stmt|;
name|GtkWidget
modifier|*
name|image
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|page
operator|=
name|gimp_color_selector_new
argument_list|(
name|page_type
argument_list|,
operator|&
name|selector
operator|->
name|rgb
argument_list|,
operator|&
name|selector
operator|->
name|hsv
argument_list|,
name|selector
operator|->
name|channel
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|page
condition|)
return|return
name|NULL
return|;
name|selector_class
operator|=
name|GIMP_COLOR_SELECTOR_GET_CLASS
argument_list|(
name|page
argument_list|)
expr_stmt|;
name|gimp_color_selector_set_show_alpha
argument_list|(
name|GIMP_COLOR_SELECTOR
argument_list|(
name|page
argument_list|)
argument_list|,
name|GIMP_COLOR_SELECTOR
argument_list|(
name|notebook
argument_list|)
operator|->
name|show_alpha
argument_list|)
expr_stmt|;
name|menu_widget
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|selector_class
operator|->
name|icon_name
argument_list|,
name|GTK_ICON_SIZE_MENU
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|menu_widget
argument_list|)
argument_list|,
name|image
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|gettext
argument_list|(
name|selector_class
operator|->
name|name
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|menu_widget
argument_list|)
argument_list|,
name|label
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|label
argument_list|)
expr_stmt|;
name|image
operator|=
name|gtk_image_new_from_icon_name
argument_list|(
name|selector_class
operator|->
name|icon_name
argument_list|,
name|DEFAULT_TAB_ICON_SIZE
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page_menu
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|)
argument_list|,
name|page
argument_list|,
name|image
argument_list|,
name|menu_widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|notebook
operator|->
name|cur_page
condition|)
name|notebook
operator|->
name|cur_page
operator|=
name|GIMP_COLOR_SELECTOR
argument_list|(
name|page
argument_list|)
expr_stmt|;
name|notebook
operator|->
name|selectors
operator|=
name|g_list_append
argument_list|(
name|notebook
operator|->
name|selectors
argument_list|,
name|page
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|page
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|page
argument_list|,
literal|"color-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_notebook_color_changed
argument_list|)
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|page
argument_list|,
literal|"channel-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_color_notebook_channel_changed
argument_list|)
argument_list|,
name|notebook
argument_list|)
expr_stmt|;
return|return
name|page
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_color_notebook_remove_selector (GtkContainer * container,GtkWidget * widget,GimpColorNotebook * notebook)
name|gimp_color_notebook_remove_selector
parameter_list|(
name|GtkContainer
modifier|*
name|container
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|)
block|{
name|notebook
operator|->
name|selectors
operator|=
name|g_list_remove
argument_list|(
name|notebook
operator|->
name|selectors
argument_list|,
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|notebook
operator|->
name|selectors
condition|)
name|notebook
operator|->
name|cur_page
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_color_notebook_set_has_page:  * @notebook:  A #GimpColorNotebook widget.  * @page_type: The #GType of the notebook page to add or remove.  * @has_page:  Whether the page should be added or removed.  *  * This function adds and removed pages to / from a #GimpColorNotebook.  * The @page_type passed must be a #GimpColorSelector subtype.  *  * Return value: The new page widget, if @has_page was #TRUE, or #NULL  *               if @has_page was #FALSE.  **/
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_color_notebook_set_has_page (GimpColorNotebook * notebook,GType page_type,gboolean has_page)
name|gimp_color_notebook_set_has_page
parameter_list|(
name|GimpColorNotebook
modifier|*
name|notebook
parameter_list|,
name|GType
name|page_type
parameter_list|,
name|gboolean
name|has_page
parameter_list|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_COLOR_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|g_type_is_a
argument_list|(
name|page_type
argument_list|,
name|GIMP_TYPE_COLOR_SELECTOR
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
operator|!
name|g_type_is_a
argument_list|(
name|page_type
argument_list|,
name|GIMP_TYPE_COLOR_NOTEBOOK
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|notebook
operator|->
name|selectors
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpColorSelector
modifier|*
name|page
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|G_TYPE_FROM_INSTANCE
argument_list|(
name|page
argument_list|)
operator|==
name|page_type
condition|)
block|{
if|if
condition|(
name|has_page
condition|)
return|return
name|GTK_WIDGET
argument_list|(
name|page
argument_list|)
return|;
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|notebook
operator|->
name|notebook
argument_list|)
argument_list|,
name|GTK_WIDGET
argument_list|(
name|page
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
if|if
condition|(
operator|!
name|has_page
condition|)
return|return
name|NULL
return|;
return|return
name|gimp_color_notebook_add_page
argument_list|(
name|notebook
argument_list|,
name|page_type
argument_list|)
return|;
block|}
end_function

end_unit

