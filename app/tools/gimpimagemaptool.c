begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagemap.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_class_init
parameter_list|(
name|GimpImageMapToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_init
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_flush
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_cancel_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_reset_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_ok_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_map_tool_preview_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_image_map_tool_get_type (void)
name|gimp_image_map_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|tool_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|tool_type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|tool_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpImageMapToolClass
argument_list|)
block|,
operator|(
name|GBaseInitFunc
operator|)
name|NULL
block|,
operator|(
name|GBaseFinalizeFunc
operator|)
name|NULL
block|,
operator|(
name|GClassInitFunc
operator|)
name|gimp_image_map_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpImageMapTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_image_map_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TOOL
argument_list|,
literal|"GimpImageMapTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|tool_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_class_init (GimpImageMapToolClass * klass)
name|gimp_image_map_tool_class_init
parameter_list|(
name|GimpImageMapToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_image_map_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_image_map_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_image_map_tool_control
expr_stmt|;
name|klass
operator|->
name|map
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|dialog
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|reset
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_init (GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_init
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_scroll_lock
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
name|image_map_tool
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|image_map_tool
operator|->
name|preview
operator|=
name|TRUE
expr_stmt|;
name|image_map_tool
operator|->
name|shell_desc
operator|=
name|NULL
expr_stmt|;
name|image_map_tool
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
name|image_map_tool
operator|->
name|main_vbox
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_tool_preview (GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_preview
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_map_tool
operator|->
name|preview
condition|)
block|{
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_map
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_finalize (GObject * object)
name|gimp_image_map_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageMapTool
modifier|*
name|image_map_tool
decl_stmt|;
name|image_map_tool
operator|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|object
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_map_tool
operator|->
name|shell
condition|)
block|{
name|gtk_widget_destroy
argument_list|(
name|image_map_tool
operator|->
name|shell
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|shell
operator|=
name|NULL
expr_stmt|;
name|image_map_tool
operator|->
name|main_vbox
operator|=
name|NULL
expr_stmt|;
block|}
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_initialize (GimpTool * tool,GimpDisplay * gdisp)
name|gimp_image_map_tool_initialize
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpImageMapTool
modifier|*
name|image_map_tool
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|image_map_tool
operator|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|tool_info
operator|=
name|tool
operator|->
name|tool_info
expr_stmt|;
comment|/*  set gdisp so the dialog can be hidden on display destruction  */
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
if|if
condition|(
operator|!
name|image_map_tool
operator|->
name|shell
condition|)
block|{
name|GtkWidget
modifier|*
name|shell
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|stock_id
decl_stmt|;
name|stock_id
operator|=
name|gimp_viewable_get_stock_id
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|tool_info
argument_list|)
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|shell
operator|=
name|shell
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|NULL
argument_list|,
name|tool_info
operator|->
name|blurb
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|tool_info
argument_list|)
operator|->
name|name
argument_list|,
name|stock_id
argument_list|,
name|image_map_tool
operator|->
name|shell_desc
argument_list|,
name|tool_manager_help_func
argument_list|,
name|NULL
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|gimp_image_map_tool_reset_clicked
argument_list|,
name|image_map_tool
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|gimp_image_map_tool_cancel_clicked
argument_list|,
name|image_map_tool
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|gimp_image_map_tool_ok_clicked
argument_list|,
name|image_map_tool
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|main_vbox
operator|=
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|vbox
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|shell
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
comment|/*  The preview toggle  */
name|toggle
operator|=
name|gtk_check_button_new_with_mnemonic
argument_list|(
name|_
argument_list|(
literal|"_Preview"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|image_map_tool
operator|->
name|preview
argument_list|)
expr_stmt|;
name|gtk_box_pack_end
argument_list|(
name|GTK_BOX
argument_list|(
name|image_map_tool
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|toggle
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
name|toggle
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|toggle
argument_list|,
literal|"toggled"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_preview_toggled
argument_list|)
argument_list|,
name|image_map_tool
argument_list|)
expr_stmt|;
comment|/*  Fill in subclass widgets  */
name|gimp_image_map_tool_dialog
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|vbox
argument_list|)
expr_stmt|;
block|}
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
name|gimp_viewable_dialog_set_viewable
argument_list|(
name|GIMP_VIEWABLE_DIALOG
argument_list|(
name|image_map_tool
operator|->
name|shell
argument_list|)
argument_list|,
name|GIMP_VIEWABLE
argument_list|(
name|drawable
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image_map_tool
operator|->
name|shell
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|image_map_tool
operator|->
name|image_map
operator|=
name|gimp_image_map_new
argument_list|(
name|TRUE
argument_list|,
name|drawable
argument_list|,
name|tool_info
operator|->
name|blurb
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_map_tool
operator|->
name|image_map
argument_list|,
literal|"flush"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_flush
argument_list|)
argument_list|,
name|image_map_tool
argument_list|)
expr_stmt|;
block|{
name|GimpDisplayShell
modifier|*
name|shell
init|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
decl_stmt|;
name|gimp_item_factory_update
argument_list|(
name|shell
operator|->
name|menubar_factory
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_item_factory_update
argument_list|(
name|shell
operator|->
name|popup_factory
argument_list|,
name|shell
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|gimp_image_map_tool_control
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolAction
name|action
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpImageMapTool
modifier|*
name|image_map_tool
decl_stmt|;
name|image_map_tool
operator|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|PAUSE
case|:
break|break;
case|case
name|RESUME
case|:
break|break;
case|case
name|HALT
case|:
if|if
condition|(
name|image_map_tool
operator|->
name|shell
condition|)
name|gimp_image_map_tool_cancel_clicked
argument_list|(
name|NULL
argument_list|,
name|image_map_tool
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|control
argument_list|(
name|tool
argument_list|,
name|action
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_map (GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|image_map_tool
argument_list|)
operator|->
name|map
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_dialog (GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|image_map_tool
argument_list|)
operator|->
name|dialog
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_reset (GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|image_map_tool
argument_list|)
operator|->
name|reset
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_flush (GimpImageMap * image_map,GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_flush
parameter_list|(
name|GimpImageMap
modifier|*
name|image_map
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gimp_display_flush_now
argument_list|(
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_cancel_clicked (GtkWidget * widget,GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_cancel_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|image_map_tool
operator|->
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_map_tool
operator|->
name|image_map
condition|)
block|{
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_map_abort
argument_list|(
name|image_map_tool
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
name|tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_reset_clicked (GtkWidget * widget,GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_reset_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|gimp_image_map_tool_reset
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_preview
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_ok_clicked (GtkWidget * widget,GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_ok_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|image_map_tool
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|image_map_tool
operator|->
name|preview
condition|)
block|{
name|gimp_image_map_tool_map
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|image_map_tool
operator|->
name|image_map
condition|)
block|{
name|gimp_image_map_commit
argument_list|(
name|image_map_tool
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|image_map
operator|=
name|NULL
expr_stmt|;
block|}
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|gimp_item_factory_update
argument_list|(
name|shell
operator|->
name|menubar_factory
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|gimp_item_factory_update
argument_list|(
name|shell
operator|->
name|popup_factory
argument_list|,
name|shell
argument_list|)
expr_stmt|;
name|tool
operator|->
name|gdisp
operator|=
name|NULL
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_preview_toggled (GtkWidget * widget,GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_preview_toggled
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|image_map_tool
operator|->
name|preview
operator|=
name|GTK_TOGGLE_BUTTON
argument_list|(
name|widget
argument_list|)
operator|->
name|active
expr_stmt|;
if|if
condition|(
name|image_map_tool
operator|->
name|preview
condition|)
block|{
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_map_tool_map
argument_list|(
name|image_map_tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
name|image_map_tool
operator|->
name|image_map
condition|)
block|{
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_image_map_clear
argument_list|(
name|image_map_tool
operator|->
name|image_map
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_preserve
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|tool
operator|->
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

end_unit

