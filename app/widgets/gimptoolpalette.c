begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptoolpalette.c  * Copyright (C) 2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolpalette.h"
end_include

begin_include
include|#
directive|include
file|"gimpuimanager.h"
end_include

begin_include
include|#
directive|include
file|"gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpwindowstrategy.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|DEFAULT_TOOL_ICON_SIZE
define|#
directive|define
name|DEFAULT_TOOL_ICON_SIZE
value|GTK_ICON_SIZE_BUTTON
end_define

begin_define
DECL|macro|DEFAULT_BUTTON_RELIEF
define|#
directive|define
name|DEFAULT_BUTTON_RELIEF
value|GTK_RELIEF_NONE
end_define

begin_define
DECL|macro|TOOL_BUTTON_DATA_KEY
define|#
directive|define
name|TOOL_BUTTON_DATA_KEY
value|"gimp-tool-palette-item"
end_define

begin_define
DECL|macro|TOOL_INFO_DATA_KEY
define|#
directive|define
name|TOOL_INFO_DATA_KEY
value|"gimp-tool-info"
end_define

begin_typedef
DECL|typedef|GimpToolPalettePrivate
typedef|typedef
name|struct
name|_GimpToolPalettePrivate
name|GimpToolPalettePrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolPalettePrivate
struct|struct
name|_GimpToolPalettePrivate
block|{
DECL|member|toolbox
name|GimpToolbox
modifier|*
name|toolbox
decl_stmt|;
DECL|member|tool_rows
name|gint
name|tool_rows
decl_stmt|;
DECL|member|tool_columns
name|gint
name|tool_columns
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GET_PRIVATE (p)
define|#
directive|define
name|GET_PRIVATE
parameter_list|(
name|p
parameter_list|)
value|G_TYPE_INSTANCE_GET_PRIVATE (p, \                                                     GIMP_TYPE_TOOL_PALETTE, \                                                     GimpToolPalettePrivate)
end_define

begin_function_decl
specifier|static
name|void
name|gimp_tool_palette_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_palette_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|previous_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_palette_hierarchy_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|previous_toplevel
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_palette_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_palette_tool_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gint
name|index
parameter_list|,
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_tool_palette_tool_button_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_tool_palette_tool_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpToolPalette,gimp_tool_palette,GTK_TYPE_TOOL_PALETTE)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpToolPalette
argument_list|,
argument|gimp_tool_palette
argument_list|,
argument|GTK_TYPE_TOOL_PALETTE
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_tool_palette_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_tool_palette_class_init
parameter_list|(
name|GimpToolPaletteClass
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
name|widget_class
operator|->
name|size_allocate
operator|=
name|gimp_tool_palette_size_allocate
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_tool_palette_style_set
expr_stmt|;
name|widget_class
operator|->
name|hierarchy_changed
operator|=
name|gimp_tool_palette_hierarchy_changed
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"tool-icon-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_ICON_SIZE
argument_list|,
name|DEFAULT_TOOL_ICON_SIZE
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"button-relief"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_RELIEF_STYLE
argument_list|,
name|DEFAULT_BUTTON_RELIEF
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_type_class_add_private
argument_list|(
name|klass
argument_list|,
sizeof|sizeof
argument_list|(
name|GimpToolPalettePrivate
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_palette_init (GimpToolPalette * palette)
name|gimp_tool_palette_init
parameter_list|(
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
block|{
name|gtk_tool_palette_set_style
argument_list|(
name|GTK_TOOL_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|,
name|GTK_TOOLBAR_ICONS
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_palette_size_allocate (GtkWidget * widget,GtkAllocation * allocation)
name|gimp_tool_palette_size_allocate
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkAllocation
modifier|*
name|allocation
parameter_list|)
block|{
name|GimpToolPalettePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|gint
name|button_width
decl_stmt|;
name|gint
name|button_height
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|size_allocate
argument_list|(
name|widget
argument_list|,
name|allocation
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_tool_palette_get_button_size
argument_list|(
name|GIMP_TOOL_PALETTE
argument_list|(
name|widget
argument_list|)
argument_list|,
operator|&
name|button_width
argument_list|,
operator|&
name|button_height
argument_list|)
condition|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|gimp_toolbox_get_context
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
operator|->
name|gimp
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|gint
name|n_tools
decl_stmt|;
name|gint
name|tool_rows
decl_stmt|;
name|gint
name|tool_columns
decl_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_tool_info_iter
argument_list|(
name|gimp
argument_list|)
operator|,
name|n_tools
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|tool_info
operator|->
name|visible
condition|)
name|n_tools
operator|++
expr_stmt|;
block|}
name|tool_columns
operator|=
name|MAX
argument_list|(
literal|1
argument_list|,
operator|(
name|allocation
operator|->
name|width
operator|/
name|button_width
operator|)
argument_list|)
expr_stmt|;
name|tool_rows
operator|=
name|n_tools
operator|/
name|tool_columns
expr_stmt|;
if|if
condition|(
name|n_tools
operator|%
name|tool_columns
condition|)
name|tool_rows
operator|++
expr_stmt|;
if|if
condition|(
name|private
operator|->
name|tool_rows
operator|!=
name|tool_rows
operator|||
name|private
operator|->
name|tool_columns
operator|!=
name|tool_columns
condition|)
block|{
name|private
operator|->
name|tool_rows
operator|=
name|tool_rows
expr_stmt|;
name|private
operator|->
name|tool_columns
operator|=
name|tool_columns
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|widget
argument_list|,
operator|-
literal|1
argument_list|,
name|tool_rows
operator|*
name|button_height
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_palette_style_set (GtkWidget * widget,GtkStyle * previous_style)
name|gimp_tool_palette_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|previous_style
parameter_list|)
block|{
name|GimpToolPalettePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|GtkIconSize
name|tool_icon_size
decl_stmt|;
name|GtkReliefStyle
name|relief
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|previous_style
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_toolbox_get_context
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
condition|)
return|return;
name|gimp
operator|=
name|gimp_toolbox_get_context
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
operator|->
name|gimp
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"tool-icon-size"
argument_list|,
operator|&
name|tool_icon_size
argument_list|,
literal|"button-relief"
argument_list|,
operator|&
name|relief
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_tool_palette_set_icon_size
argument_list|(
name|GTK_TOOL_PALETTE
argument_list|(
name|widget
argument_list|)
argument_list|,
name|tool_icon_size
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_tool_info_iter
argument_list|(
name|gimp
argument_list|)
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
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GtkWidget
modifier|*
name|tool_button
decl_stmt|;
name|tool_button
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|TOOL_BUTTON_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_button
condition|)
block|{
name|GtkWidget
modifier|*
name|button
init|=
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|tool_button
argument_list|)
argument_list|)
decl_stmt|;
name|gtk_button_set_relief
argument_list|(
name|GTK_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|,
name|relief
argument_list|)
expr_stmt|;
block|}
block|}
name|gimp_dock_invalidate_geometry
argument_list|(
name|GIMP_DOCK
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_palette_hierarchy_changed (GtkWidget * widget,GtkWidget * previous_tolevel)
name|gimp_tool_palette_hierarchy_changed
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkWidget
modifier|*
name|previous_tolevel
parameter_list|)
block|{
name|GimpToolPalettePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|widget
argument_list|)
decl_stmt|;
name|GimpUIManager
modifier|*
name|ui_manager
decl_stmt|;
name|ui_manager
operator|=
name|gimp_dock_get_ui_manager
argument_list|(
name|GIMP_DOCK
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|ui_manager
condition|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|gimp_toolbox_get_context
argument_list|(
name|private
operator|->
name|toolbox
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
name|gimp_get_tool_info_iter
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
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
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GtkToolItem
modifier|*
name|item
decl_stmt|;
name|GtkAction
modifier|*
name|action
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|identifier
decl_stmt|;
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|item
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|TOOL_BUTTON_DATA_KEY
argument_list|)
expr_stmt|;
name|identifier
operator|=
name|gimp_object_get_name
argument_list|(
name|tool_info
argument_list|)
expr_stmt|;
name|tmp
operator|=
name|g_strndup
argument_list|(
name|identifier
operator|+
name|strlen
argument_list|(
literal|"gimp-"
argument_list|)
argument_list|,
name|strlen
argument_list|(
name|identifier
argument_list|)
operator|-
name|strlen
argument_list|(
literal|"gimp--tool"
argument_list|)
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"tools-%s"
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
name|action
operator|=
name|gimp_ui_manager_find_action
argument_list|(
name|ui_manager
argument_list|,
literal|"tools"
argument_list|,
name|name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|action
condition|)
name|gimp_widget_set_accel_help
argument_list|(
name|GTK_WIDGET
argument_list|(
name|item
argument_list|)
argument_list|,
name|action
argument_list|)
expr_stmt|;
else|else
name|gimp_help_set_help_data
argument_list|(
name|GTK_WIDGET
argument_list|(
name|item
argument_list|)
argument_list|,
name|tool_info
operator|->
name|help
argument_list|,
name|tool_info
operator|->
name|help_id
argument_list|)
expr_stmt|;
comment|/* Make sure the toolbox buttons won't grab focus, which has            * nearly no practical use, and prevents various actions until            * you click back in canvas.            */
name|gtk_widget_set_can_focus
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|item
argument_list|)
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_tool_palette_new (void)
name|gimp_tool_palette_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_TOOL_PALETTE
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_tool_palette_set_toolbox (GimpToolPalette * palette,GimpToolbox * toolbox)
name|gimp_tool_palette_set_toolbox
parameter_list|(
name|GimpToolPalette
modifier|*
name|palette
parameter_list|,
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|)
block|{
name|GimpToolPalettePrivate
modifier|*
name|private
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GtkWidget
modifier|*
name|group
decl_stmt|;
name|GSList
modifier|*
name|item_group
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOL_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TOOLBOX
argument_list|(
name|toolbox
argument_list|)
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|palette
argument_list|)
expr_stmt|;
name|private
operator|->
name|toolbox
operator|=
name|toolbox
expr_stmt|;
name|context
operator|=
name|gimp_toolbox_get_context
argument_list|(
name|toolbox
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_tool_item_group_new
argument_list|(
name|_
argument_list|(
literal|"Tools"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tool_item_group_set_label_widget
argument_list|(
name|GTK_TOOL_ITEM_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|palette
argument_list|)
argument_list|,
name|group
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|group
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp_get_tool_info_iter
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
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
name|GimpToolInfo
modifier|*
name|tool_info
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GtkToolItem
modifier|*
name|item
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|icon_name
decl_stmt|;
name|icon_name
operator|=
name|gimp_viewable_get_icon_name
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|item
operator|=
name|gtk_radio_tool_button_new
argument_list|(
name|item_group
argument_list|)
expr_stmt|;
name|gtk_tool_button_set_icon_name
argument_list|(
name|GTK_TOOL_BUTTON
argument_list|(
name|item
argument_list|)
argument_list|,
name|icon_name
argument_list|)
expr_stmt|;
name|item_group
operator|=
name|gtk_radio_tool_button_get_group
argument_list|(
name|GTK_RADIO_TOOL_BUTTON
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_tool_item_group_insert
argument_list|(
name|GTK_TOOL_ITEM_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|item
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|GTK_WIDGET
argument_list|(
name|item
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_bind_property
argument_list|(
name|tool_info
argument_list|,
literal|"visible"
argument_list|,
name|item
argument_list|,
literal|"visible-horizontal"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|)
expr_stmt|;
name|g_object_bind_property
argument_list|(
name|tool_info
argument_list|,
literal|"visible"
argument_list|,
name|item
argument_list|,
literal|"visible-vertical"
argument_list|,
name|G_BINDING_SYNC_CREATE
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|TOOL_BUTTON_DATA_KEY
argument_list|,
name|item
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|item
argument_list|)
argument_list|,
name|TOOL_INFO_DATA_KEY
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|item
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_palette_tool_button_toggled
argument_list|)
argument_list|,
name|palette
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|gtk_bin_get_child
argument_list|(
name|GTK_BIN
argument_list|(
name|item
argument_list|)
argument_list|)
argument_list|,
literal|"button-press-event"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_palette_tool_button_press
argument_list|)
argument_list|,
name|palette
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|context
operator|->
name|gimp
operator|->
name|tool_info_list
argument_list|,
literal|"reorder"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_palette_tool_reorder
argument_list|)
argument_list|,
name|palette
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"tool-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_tool_palette_tool_changed
argument_list|)
argument_list|,
name|palette
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_tool_palette_tool_changed
argument_list|(
name|context
argument_list|,
name|gimp_context_get_tool
argument_list|(
name|context
argument_list|)
argument_list|,
name|palette
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_tool_palette_get_button_size (GimpToolPalette * palette,gint * width,gint * height)
name|gimp_tool_palette_get_button_size
parameter_list|(
name|GimpToolPalette
modifier|*
name|palette
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
block|{
name|GimpToolPalettePrivate
modifier|*
name|private
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GtkWidget
modifier|*
name|tool_button
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOL_PALETTE
argument_list|(
name|palette
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|width
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|height
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|private
operator|=
name|GET_PRIVATE
argument_list|(
name|palette
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|gimp_get_tool_info
argument_list|(
name|gimp_toolbox_get_context
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
operator|->
name|gimp
argument_list|,
literal|"gimp-rect-select-tool"
argument_list|)
expr_stmt|;
name|tool_button
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|TOOL_BUTTON_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool_button
condition|)
block|{
name|GtkRequisition
name|button_requisition
decl_stmt|;
name|gtk_widget_size_request
argument_list|(
name|tool_button
argument_list|,
operator|&
name|button_requisition
argument_list|)
expr_stmt|;
operator|*
name|width
operator|=
name|button_requisition
operator|.
name|width
expr_stmt|;
operator|*
name|height
operator|=
name|button_requisition
operator|.
name|height
expr_stmt|;
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_tool_palette_tool_changed (GimpContext * context,GimpToolInfo * tool_info,GimpToolPalette * palette)
name|gimp_tool_palette_tool_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
block|{
if|if
condition|(
name|tool_info
condition|)
block|{
name|GtkWidget
modifier|*
name|tool_button
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|TOOL_BUTTON_DATA_KEY
argument_list|)
decl_stmt|;
if|if
condition|(
name|tool_button
operator|&&
operator|!
name|gtk_toggle_tool_button_get_active
argument_list|(
name|GTK_TOGGLE_TOOL_BUTTON
argument_list|(
name|tool_button
argument_list|)
argument_list|)
condition|)
block|{
name|g_signal_handlers_block_by_func
argument_list|(
name|tool_button
argument_list|,
name|gimp_tool_palette_tool_button_toggled
argument_list|,
name|palette
argument_list|)
expr_stmt|;
name|gtk_toggle_tool_button_set_active
argument_list|(
name|GTK_TOGGLE_TOOL_BUTTON
argument_list|(
name|tool_button
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_handlers_unblock_by_func
argument_list|(
name|tool_button
argument_list|,
name|gimp_tool_palette_tool_button_toggled
argument_list|,
name|palette
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_palette_tool_reorder (GimpContainer * container,GimpToolInfo * tool_info,gint index,GimpToolPalette * palette)
name|gimp_tool_palette_tool_reorder
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|,
name|gint
name|index
parameter_list|,
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
block|{
if|if
condition|(
name|tool_info
condition|)
block|{
name|GtkWidget
modifier|*
name|button
init|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
argument_list|)
argument_list|,
name|TOOL_BUTTON_DATA_KEY
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|group
init|=
name|gtk_widget_get_parent
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|gtk_tool_item_group_set_item_position
argument_list|(
name|GTK_TOOL_ITEM_GROUP
argument_list|(
name|group
argument_list|)
argument_list|,
name|GTK_TOOL_ITEM
argument_list|(
name|button
argument_list|)
argument_list|,
name|index
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_tool_palette_tool_button_toggled (GtkWidget * widget,GimpToolPalette * palette)
name|gimp_tool_palette_tool_button_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
block|{
name|GimpToolPalettePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|palette
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|tool_info
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|widget
argument_list|)
argument_list|,
name|TOOL_INFO_DATA_KEY
argument_list|)
expr_stmt|;
if|if
condition|(
name|gtk_toggle_tool_button_get_active
argument_list|(
name|GTK_TOGGLE_TOOL_BUTTON
argument_list|(
name|widget
argument_list|)
argument_list|)
condition|)
name|gimp_context_set_tool
argument_list|(
name|gimp_toolbox_get_context
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_tool_palette_tool_button_press (GtkWidget * widget,GdkEventButton * event,GimpToolPalette * palette)
name|gimp_tool_palette_tool_button_press
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkEventButton
modifier|*
name|event
parameter_list|,
name|GimpToolPalette
modifier|*
name|palette
parameter_list|)
block|{
name|GimpToolPalettePrivate
modifier|*
name|private
init|=
name|GET_PRIVATE
argument_list|(
name|palette
argument_list|)
decl_stmt|;
if|if
condition|(
name|event
operator|->
name|type
operator|==
name|GDK_2BUTTON_PRESS
operator|&&
name|event
operator|->
name|button
operator|==
literal|1
condition|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|gimp_toolbox_get_context
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
decl_stmt|;
name|GimpDock
modifier|*
name|dock
init|=
name|GIMP_DOCK
argument_list|(
name|private
operator|->
name|toolbox
argument_list|)
decl_stmt|;
name|gimp_window_strategy_show_dockable_dialog
argument_list|(
name|GIMP_WINDOW_STRATEGY
argument_list|(
name|gimp_get_window_strategy
argument_list|(
name|context
operator|->
name|gimp
argument_list|)
argument_list|)
argument_list|,
name|context
operator|->
name|gimp
argument_list|,
name|gimp_dock_get_dialog_factory
argument_list|(
name|dock
argument_list|)
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
name|gimp_widget_get_monitor
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-tool-options"
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

end_unit

