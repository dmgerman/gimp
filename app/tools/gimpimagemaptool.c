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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<errno.h>
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
file|"core/gimpimage-pick-color.h"
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
file|"widgets/gimppropwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimptooldialog.h"
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
file|"gimpcoloroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagemaptool.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
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
name|gboolean
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
name|gboolean
name|gimp_image_map_tool_pick_color
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImageType
modifier|*
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|color_index
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
name|gimp_image_map_tool_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
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
name|gimp_image_map_tool_notify_preview
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
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
name|GIMP_TYPE_COLOR_TOOL
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
name|GimpColorToolClass
modifier|*
name|color_tool_class
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
name|color_tool_class
operator|=
name|GIMP_COLOR_TOOL_CLASS
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
name|color_tool_class
operator|->
name|pick
operator|=
name|gimp_image_map_tool_pick_color
expr_stmt|;
name|klass
operator|->
name|settings_name
operator|=
name|NULL
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
name|klass
operator|->
name|settings_load
operator|=
name|NULL
expr_stmt|;
name|klass
operator|->
name|settings_save
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
init|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
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
init|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
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

begin_define
DECL|macro|RESPONSE_RESET
define|#
directive|define
name|RESPONSE_RESET
value|1
end_define

begin_function
specifier|static
name|gboolean
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
init|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpToolInfo
modifier|*
name|tool_info
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
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
name|gimp_tool_dialog_new
argument_list|(
name|tool_info
argument_list|,
name|gdisp
operator|->
name|shell
argument_list|,
name|image_map_tool
operator|->
name|shell_desc
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|RESPONSE_RESET
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|shell
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_response
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|image_map_tool
argument_list|)
argument_list|,
literal|0
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
literal|6
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
name|gimp_prop_check_button_new
argument_list|(
name|G_OBJECT
argument_list|(
name|tool_info
operator|->
name|tool_options
argument_list|)
argument_list|,
literal|"preview"
argument_list|,
name|_
argument_list|(
literal|"_Preview"
argument_list|)
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
name|tool_info
operator|->
name|tool_options
argument_list|,
literal|"notify::preview"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_map_tool_notify_preview
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
return|return
name|TRUE
return|;
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
init|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|action
condition|)
block|{
case|case
name|HALT
case|:
if|if
condition|(
name|image_map_tool
operator|->
name|shell
condition|)
name|gtk_dialog_response
argument_list|(
name|GTK_DIALOG
argument_list|(
name|image_map_tool
operator|->
name|shell
argument_list|)
argument_list|,
name|GTK_RESPONSE_CANCEL
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
name|gboolean
DECL|function|gimp_image_map_tool_pick_color (GimpColorTool * color_tool,gint x,gint y,GimpImageType * sample_type,GimpRGB * color,gint * color_index)
name|gimp_image_map_tool_pick_color
parameter_list|(
name|GimpColorTool
modifier|*
name|color_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpImageType
modifier|*
name|sample_type
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gint
modifier|*
name|color_index
parameter_list|)
block|{
name|GimpImageMapTool
modifier|*
name|tool
init|=
name|GIMP_IMAGE_MAP_TOOL
argument_list|(
name|color_tool
argument_list|)
decl_stmt|;
operator|*
name|sample_type
operator|=
name|gimp_drawable_type
argument_list|(
name|tool
operator|->
name|drawable
argument_list|)
expr_stmt|;
return|return
name|gimp_image_pick_color_by_func
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|tool
operator|->
name|image_map
argument_list|)
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
operator|(
name|GimpImagePickColorFunc
operator|)
name|gimp_image_map_get_color_at
argument_list|,
name|color_tool
operator|->
name|options
operator|->
name|sample_average
argument_list|,
name|color_tool
operator|->
name|options
operator|->
name|average_radius
argument_list|,
name|color
argument_list|,
name|color_index
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_map (GimpImageMapTool * tool)
name|gimp_image_map_tool_map
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|map
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_dialog (GimpImageMapTool * tool)
name|gimp_image_map_tool_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|dialog
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_reset (GimpImageMapTool * tool)
name|gimp_image_map_tool_reset
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|reset
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_tool_settings_load (GimpImageMapTool * tool,gpointer file)
name|gimp_image_tool_settings_load
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
name|gpointer
name|file
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool_class
operator|->
name|settings_load
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|tool_class
operator|->
name|settings_load
argument_list|(
name|tool
argument_list|,
name|file
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_image_tool_settings_save (GimpImageMapTool * tool,gpointer file)
name|gimp_image_tool_settings_save
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
name|gpointer
name|file
parameter_list|)
block|{
name|GimpImageMapToolClass
modifier|*
name|tool_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|tool_class
operator|->
name|settings_save
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|tool_class
operator|->
name|settings_save
argument_list|(
name|tool
argument_list|,
name|file
argument_list|)
return|;
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
init|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
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
DECL|function|gimp_image_map_tool_response (GtkWidget * widget,gint response_id,GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
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
name|GimpImageMapOptions
modifier|*
name|options
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
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|RESPONSE_RESET
case|:
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
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
comment|/* Fix for bug #126524 - only set shell in the case        * where we need it */
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
name|options
operator|=
name|GIMP_IMAGE_MAP_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|options
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
name|gimp_item_factory_update
argument_list|(
name|shell
operator|->
name|menubar_factory
argument_list|,
name|shell
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|gdisp
operator|==
name|gimp_context_get_display
argument_list|(
name|gimp_get_user_context
argument_list|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|gimp
argument_list|)
argument_list|)
condition|)
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
break|break;
default|default:
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
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_map_tool_notify_preview (GObject * config,GParamSpec * pspec,GimpImageMapTool * image_map_tool)
name|gimp_image_map_tool_notify_preview
parameter_list|(
name|GObject
modifier|*
name|config
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|,
name|GimpImageMapTool
modifier|*
name|image_map_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|image_map_tool
argument_list|)
decl_stmt|;
name|GimpImageMapOptions
modifier|*
name|options
init|=
name|GIMP_IMAGE_MAP_OPTIONS
argument_list|(
name|config
argument_list|)
decl_stmt|;
if|if
condition|(
name|options
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
name|GimpImageMapOptions
modifier|*
name|options
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
name|options
operator|=
name|GIMP_IMAGE_MAP_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
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
DECL|function|settings_dialog_response (GtkWidget * dialog,gint response_id,GimpImageMapTool * tool)
name|settings_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|)
block|{
name|GimpImageMapOptions
modifier|*
name|options
decl_stmt|;
name|gboolean
name|save
decl_stmt|;
name|save
operator|=
name|GPOINTER_TO_INT
argument_list|(
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"save"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|response_id
operator|==
name|GTK_RESPONSE_OK
condition|)
block|{
specifier|const
name|gchar
modifier|*
name|filename
decl_stmt|;
name|FILE
modifier|*
name|file
decl_stmt|;
name|filename
operator|=
name|gtk_file_selection_get_filename
argument_list|(
name|GTK_FILE_SELECTION
argument_list|(
name|dialog
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
name|save
condition|?
literal|"wt"
else|:
literal|"rt"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|file
condition|)
block|{
name|g_message
argument_list|(
name|save
condition|?
name|_
argument_list|(
literal|"Could not open '%s' for writing: %s"
argument_list|)
else|:
name|_
argument_list|(
literal|"Could not open '%s' for reading: %s"
argument_list|)
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|,
name|g_strerror
argument_list|(
name|errno
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|options
operator|=
name|GIMP_IMAGE_MAP_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|options
operator|->
name|settings
argument_list|)
expr_stmt|;
name|options
operator|->
name|settings
operator|=
name|g_strdup
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
name|save
condition|)
block|{
name|gimp_image_tool_settings_save
argument_list|(
name|tool
argument_list|,
name|file
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
operator|!
name|gimp_image_tool_settings_load
argument_list|(
name|tool
argument_list|,
name|file
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"Error in reading file '%s'."
argument_list|,
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|fclose
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_map_tool_settings_dialog (GimpImageMapTool * tool,const gchar * title,gboolean save)
name|gimp_image_map_tool_settings_dialog
parameter_list|(
name|GimpImageMapTool
modifier|*
name|tool
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
name|gboolean
name|save
parameter_list|)
block|{
name|GimpImageMapOptions
modifier|*
name|options
decl_stmt|;
name|GtkFileSelection
modifier|*
name|dialog
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_MAP_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|tool
operator|->
name|settings_dialog
condition|)
block|{
name|gtk_window_present
argument_list|(
name|GTK_WINDOW
argument_list|(
name|tool
operator|->
name|settings_dialog
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|tool
operator|->
name|settings_dialog
operator|=
name|gtk_file_selection_new
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|GTK_FILE_SELECTION
argument_list|(
name|tool
operator|->
name|settings_dialog
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"save"
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|save
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_role
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimp-load-save-settings"
argument_list|)
expr_stmt|;
name|gtk_window_set_position
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|dialog
operator|->
name|button_area
argument_list|)
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|g_object_add_weak_pointer
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
operator|&
name|tool
operator|->
name|settings_dialog
argument_list|)
expr_stmt|;
name|gtk_window_set_transient_for
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|GTK_WINDOW
argument_list|(
name|tool
operator|->
name|shell
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_window_set_destroy_with_parent
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|settings_dialog_response
argument_list|)
argument_list|,
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_IMAGE_MAP_OPTIONS
argument_list|(
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|settings
condition|)
block|{
name|gtk_file_selection_set_filename
argument_list|(
name|dialog
argument_list|,
name|options
operator|->
name|settings
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|settings_name
condition|)
block|{
name|gchar
modifier|*
name|tmp
decl_stmt|;
name|tmp
operator|=
name|g_build_filename
argument_list|(
name|gimp_directory
argument_list|()
argument_list|,
name|GIMP_IMAGE_MAP_TOOL_GET_CLASS
argument_list|(
name|tool
argument_list|)
operator|->
name|settings_name
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_file_selection_set_filename
argument_list|(
name|dialog
argument_list|,
name|tmp
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|tmp
argument_list|)
expr_stmt|;
block|}
name|gimp_help_connect
argument_list|(
name|tool
operator|->
name|settings_dialog
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
operator|->
name|tool_info
operator|->
name|help_id
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|tool
operator|->
name|settings_dialog
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

