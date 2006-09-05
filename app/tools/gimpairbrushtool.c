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
file|"paint/gimpairbrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrushtool.h"
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
name|GtkWidget
modifier|*
name|gimp_airbrush_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpAirbrushTool,gimp_airbrush_tool,GIMP_TYPE_PAINTBRUSH_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpAirbrushTool
argument_list|,
argument|gimp_airbrush_tool
argument_list|,
argument|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
end_macro

begin_function
name|void
name|gimp_airbrush_tool_register
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
name|GIMP_TYPE_AIRBRUSH_TOOL
argument_list|,
name|GIMP_TYPE_AIRBRUSH_OPTIONS
argument_list|,
name|gimp_airbrush_options_gui
argument_list|,
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
operator||
name|GIMP_CONTEXT_GRADIENT_MASK
argument_list|,
literal|"gimp-airbrush-tool"
argument_list|,
name|_
argument_list|(
literal|"Airbrush"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Airbrush with variable pressure"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_Airbrush"
argument_list|)
argument_list|,
literal|"A"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_AIRBRUSH
argument_list|,
name|GIMP_STOCK_TOOL_AIRBRUSH
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_tool_class_init (GimpAirbrushToolClass * klass)
name|gimp_airbrush_tool_class_init
parameter_list|(
name|GimpAirbrushToolClass
modifier|*
name|klass
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_tool_init (GimpAirbrushTool * airbrush)
name|gimp_airbrush_tool_init
parameter_list|(
name|GimpAirbrushTool
modifier|*
name|airbrush
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|airbrush
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_AIRBRUSH
argument_list|)
expr_stmt|;
name|gimp_paint_tool_enable_color_picker
argument_list|(
name|GIMP_PAINT_TOOL
argument_list|(
name|airbrush
argument_list|)
argument_list|,
name|GIMP_COLOR_PICK_MODE_FOREGROUND
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
DECL|function|gimp_airbrush_options_gui (GimpToolOptions * tool_options)
name|gimp_airbrush_options_gui
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
name|table
operator|=
name|gtk_table_new
argument_list|(
literal|2
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_table_set_col_spacing
argument_list|(
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
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
literal|"rate"
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
literal|"Rate:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
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
name|gimp_prop_scale_entry_new
argument_list|(
name|config
argument_list|,
literal|"pressure"
argument_list|,
name|GTK_TABLE
argument_list|(
name|table
argument_list|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|_
argument_list|(
literal|"Pressure:"
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
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

