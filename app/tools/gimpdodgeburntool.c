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
file|"paint/gimpdodgeburn.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpenummenu.h"
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
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_dodgeburn_tool_class_init
parameter_list|(
name|GimpDodgeBurnToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dodgeburn_tool_init
parameter_list|(
name|GimpDodgeBurnTool
modifier|*
name|dodgeburn
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dodgeburn_tool_modifier_key
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
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dodgeburn_tool_cursor_update
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
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpToolOptions
modifier|*
name|gimp_dodgeburn_tool_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_dodgeburn_tool_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_dodgeburn_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_dodgeburn_tool_register
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
name|GIMP_TYPE_DODGEBURN_TOOL
argument_list|,
name|gimp_dodgeburn_tool_options_new
argument_list|,
name|TRUE
argument_list|,
literal|"gimp-dodgeburn-tool"
argument_list|,
name|_
argument_list|(
literal|"Dodge/Burn"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Dodge or Burn strokes"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Paint Tools/DodgeBurn"
argument_list|)
argument_list|,
literal|"<shift>D"
argument_list|,
name|NULL
argument_list|,
literal|"tools/dodgeburn.html"
argument_list|,
name|GIMP_STOCK_TOOL_DODGE
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_dodgeburn_tool_get_type (void)
name|gimp_dodgeburn_tool_get_type
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
name|GimpDodgeBurnToolClass
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
name|gimp_dodgeburn_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpDodgeBurnTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_dodgeburn_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_TOOL
argument_list|,
literal|"GimpDodgeBurnTool"
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
DECL|function|gimp_dodgeburn_tool_class_init (GimpDodgeBurnToolClass * klass)
name|gimp_dodgeburn_tool_class_init
parameter_list|(
name|GimpDodgeBurnToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
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
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_dodgeburn_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_dodgeburn_tool_cursor_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodgeburn_tool_init (GimpDodgeBurnTool * dodgeburn)
name|gimp_dodgeburn_tool_init
parameter_list|(
name|GimpDodgeBurnTool
modifier|*
name|dodgeburn
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|dodgeburn
argument_list|)
expr_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|dodgeburn
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_DODGE_TOOL_CURSOR
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_toggle_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_BURN_TOOL_CURSOR
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|core
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_DODGEBURN
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodgeburn_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_dodgeburn_tool_modifier_key
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
name|gdisp
parameter_list|)
block|{
name|GimpDodgeBurnOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|GimpDodgeBurnOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
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
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_BURN
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_BURN
case|:
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|GIMP_DODGE
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
name|gimp_tool_control_set_toggle
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodgeburn_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_dodgeburn_tool_cursor_update
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
name|gdisp
parameter_list|)
block|{
name|GimpDodgeBurnOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|GimpDodgeBurnOptions
operator|*
operator|)
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
name|gimp_tool_control_set_toggle
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
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  tool options stuff  */
end_comment

begin_function
specifier|static
name|GimpToolOptions
modifier|*
DECL|function|gimp_dodgeburn_tool_options_new (GimpToolInfo * tool_info)
name|gimp_dodgeburn_tool_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|GimpDodgeBurnOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
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
name|options
operator|=
name|gimp_dodgeburn_options_new
argument_list|(
name|tool_info
operator|->
name|context
argument_list|)
expr_stmt|;
name|paint_options_init
argument_list|(
operator|(
name|GimpPaintOptions
operator|*
operator|)
name|options
argument_list|,
name|tool_info
argument_list|)
expr_stmt|;
operator|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|reset_func
operator|=
name|gimp_dodgeburn_tool_options_reset
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
operator|(
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|main_vbox
expr_stmt|;
comment|/* the type (dodge or burn) */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Type  %s"
argument_list|)
argument_list|,
name|gimp_get_mod_name_control
argument_list|()
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gimp_enum_radio_frame_new
argument_list|(
name|GIMP_TYPE_DODGE_BURN_TYPE
argument_list|,
name|gtk_label_new
argument_list|(
name|str
argument_list|)
argument_list|,
literal|2
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|type
argument_list|,
operator|&
name|options
operator|->
name|type_w
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|type
argument_list|)
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
name|gimp_enum_radio_frame_new
argument_list|(
name|GIMP_TYPE_TRANSFER_MODE
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Mode"
argument_list|)
argument_list|)
argument_list|,
literal|2
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_radio_button_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|mode
argument_list|,
operator|&
name|options
operator|->
name|mode_w
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|mode_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|mode
argument_list|)
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
name|options
operator|->
name|exposure_w
operator|=
name|gimp_scale_entry_new
argument_list|(
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
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|,
name|options
operator|->
name|exposure
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|,
literal|0.0
argument_list|,
literal|0.0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|options
operator|->
name|exposure_w
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|exposure
argument_list|)
expr_stmt|;
return|return
operator|(
name|GimpToolOptions
operator|*
operator|)
name|options
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_dodgeburn_tool_options_reset (GimpToolOptions * tool_options)
name|gimp_dodgeburn_tool_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|GimpDodgeBurnOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|GimpDodgeBurnOptions
operator|*
operator|)
name|tool_options
expr_stmt|;
name|paint_options_reset
argument_list|(
name|tool_options
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|exposure_w
argument_list|)
argument_list|,
name|options
operator|->
name|exposure_d
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|type_d
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|mode_w
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|mode_d
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

