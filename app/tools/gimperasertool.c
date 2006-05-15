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
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimperaseroptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimperasertool.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions-gui.h"
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

begin_function_decl
specifier|static
name|void
name|gimp_eraser_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_eraser_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_eraser_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpEraserTool,gimp_eraser_tool,GIMP_TYPE_PAINT_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpEraserTool
argument_list|,
argument|gimp_eraser_tool
argument_list|,
argument|GIMP_TYPE_PAINT_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_eraser_tool_parent_class
end_define

begin_function
name|void
name|gimp_eraser_tool_register
parameter_list|(
name|GimpToolRegisterCallback
name|callback
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|GIMP_TYPE_ERASER_TOOL
argument_list|,
name|GIMP_TYPE_ERASER_OPTIONS
argument_list|,
name|gimp_eraser_options_gui
argument_list|,
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
argument_list|,
literal|"gimp-eraser-tool"
argument_list|,
name|_
argument_list|(
literal|"Eraser"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Erase to background or transparency"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Eraser"
argument_list|)
argument_list|,
literal|"<shift>E"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_ERASER
argument_list|,
name|GIMP_STOCK_TOOL_ERASER
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eraser_tool_class_init (GimpEraserToolClass * klass)
name|gimp_eraser_tool_class_init
parameter_list|(
name|GimpEraserToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
init|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_eraser_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_eraser_tool_cursor_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eraser_tool_init (GimpEraserTool * eraser)
name|gimp_eraser_tool_init
parameter_list|(
name|GimpEraserTool
modifier|*
name|eraser
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|eraser
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_ERASER
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggle_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_CURSOR_MODIFIER_MINUS
argument_list|)
expr_stmt|;
name|gimp_paint_tool_enable_color_picker
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|eraser
argument_list|)
argument_list|,
name|GIMP_COLOR_PICK_MODE_BACKGROUND
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eraser_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_eraser_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkModifierType
name|key
parameter_list|,
name|gboolean
name|press
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
if|if
condition|(
name|key
operator|==
name|GDK_MOD1_MASK
condition|)
block|{
name|GimpEraserOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_ERASER_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"anti-erase"
argument_list|,
operator|!
name|options
operator|->
name|anti_erase
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|modifier_key
argument_list|(
name|tool
argument_list|,
name|key
argument_list|,
name|press
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_eraser_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_eraser_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpEraserOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|GIMP_ERASER_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggled
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|options
operator|->
name|anti_erase
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|cursor_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  tool options stuff  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_eraser_options_gui (GimpToolOptions * tool_options)
name|gimp_eraser_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|button
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|config
operator|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gimp_paint_options_gui
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
comment|/* the anti_erase toggle */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Anti erase  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|GDK_MOD1_MASK
argument_list|)
argument_list|)
expr_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"anti-erase"
argument_list|,
name|str
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|button
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
name|button
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

