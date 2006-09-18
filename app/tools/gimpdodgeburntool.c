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
file|"paint/gimpdodgeburnoptions.h"
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
file|"gimpdodgeburntool.h"
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
name|gimp_dodge_burn_tool_modifier_key
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
name|gimp_dodge_burn_tool_cursor_update
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
name|void
name|gimp_dodge_burn_tool_oper_update
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
name|gboolean
name|proximity
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
name|gimp_dodge_burn_tool_status_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDodgeBurnType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_dodge_burn_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpDodgeBurnTool,gimp_dodge_burn_tool,GIMP_TYPE_BRUSH_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpDodgeBurnTool
argument_list|,
argument|gimp_dodge_burn_tool
argument_list|,
argument|GIMP_TYPE_BRUSH_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_dodge_burn_tool_parent_class
end_define

begin_function
name|void
name|gimp_dodge_burn_tool_register
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
name|GIMP_TYPE_DODGE_BURN_TOOL
argument_list|,
name|GIMP_TYPE_DODGE_BURN_OPTIONS
argument_list|,
name|gimp_dodge_burn_options_gui
argument_list|,
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
argument_list|,
literal|"gimp-dodge-burn-tool"
argument_list|,
name|_
argument_list|(
literal|"Dodge/Burn"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Dodge/Burn Tool: Selectively lighten or darken using a brush"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Dod_ge-Burn"
argument_list|)
argument_list|,
literal|"<shift>D"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_DODGE_BURN
argument_list|,
name|GIMP_STOCK_TOOL_DODGE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_tool_class_init (GimpDodgeBurnToolClass * klass)
name|gimp_dodge_burn_tool_class_init
parameter_list|(
name|GimpDodgeBurnToolClass
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
name|gimp_dodge_burn_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_dodge_burn_tool_cursor_update
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_dodge_burn_tool_oper_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_tool_init (GimpDodgeBurnTool * dodgeburn)
name|gimp_dodge_burn_tool_init
parameter_list|(
name|GimpDodgeBurnTool
modifier|*
name|dodgeburn
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|dodgeburn
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_DODGE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggle_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_BURN
argument_list|)
expr_stmt|;
name|gimp_dodge_burn_tool_status_update
argument_list|(
name|tool
argument_list|,
name|GIMP_BURN
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_dodge_burn_tool_modifier_key
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
name|GimpDodgeBurnOptions
modifier|*
name|options
init|=
name|GIMP_DODGE_BURN_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|key
operator|==
name|GDK_CONTROL_MASK
operator|&&
operator|!
operator|(
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
condition|)
comment|/* leave stuff untouched in line draw mode */
block|{
switch|switch
condition|(
name|options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_DODGE
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"type"
argument_list|,
name|GIMP_BURN
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BURN
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"type"
argument_list|,
name|GIMP_DODGE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
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
DECL|function|gimp_dodge_burn_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_dodge_burn_tool_cursor_update
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
name|GimpDodgeBurnOptions
modifier|*
name|options
init|=
name|GIMP_DODGE_BURN_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_toggled
argument_list|(
name|tool
operator|->
name|control
argument_list|,
operator|(
name|options
operator|->
name|type
operator|==
name|GIMP_BURN
operator|)
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

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_tool_oper_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_dodge_burn_tool_oper_update
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
name|gboolean
name|proximity
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpDodgeBurnOptions
modifier|*
name|options
init|=
name|GIMP_DODGE_BURN_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_dodge_burn_tool_status_update
argument_list|(
name|tool
argument_list|,
name|options
operator|->
name|type
argument_list|)
expr_stmt|;
name|GIMP_TOOL_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|oper_update
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|state
argument_list|,
name|proximity
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodge_burn_tool_status_update (GimpTool * tool,GimpDodgeBurnType type)
name|gimp_dodge_burn_tool_status_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpDodgeBurnType
name|type
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_DODGE
case|:
name|paint_tool
operator|->
name|status
operator|=
name|_
argument_list|(
literal|"Click to dodge"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_line
operator|=
name|_
argument_list|(
literal|"Click to dodge the line"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_ctrl
operator|=
name|_
argument_list|(
literal|"%s to burn"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BURN
case|:
name|paint_tool
operator|->
name|status
operator|=
name|_
argument_list|(
literal|"Click to burn"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_line
operator|=
name|_
argument_list|(
literal|"Click to burn the line"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_ctrl
operator|=
name|_
argument_list|(
literal|"%s to dodge"
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_comment
comment|/*  tool options stuff  */
end_comment

begin_function
specifier|static
name|GtkWidget
modifier|*
DECL|function|gimp_dodge_burn_options_gui (GimpToolOptions * tool_options)
name|gimp_dodge_burn_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GObject
modifier|*
name|config
init|=
name|G_OBJECT
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
init|=
name|gimp_paint_options_gui
argument_list|(
name|tool_options
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|table
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
comment|/* the type (dodge or burn) */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Type  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|GDK_CONTROL_MASK
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"type"
argument_list|,
name|str
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str
argument_list|)
expr_stmt|;
comment|/*  mode (highlights, midtones, or shadows)  */
name|frame
operator|=
name|gimp_prop_enum_radio_frame_new
argument_list|(
name|config
argument_list|,
literal|"mode"
argument_list|,
name|_
argument_list|(
literal|"Mode"
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|frame
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
name|frame
argument_list|)
expr_stmt|;
comment|/*  the exposure scale  */
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|1
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacings
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|table
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
name|table
argument_list|)
expr_stmt|;
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"exposure"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Exposure:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

