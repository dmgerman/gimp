begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"tools-types.h"
end_include

begin_include
include|#
directive|include
file|"paint/gimpairbrush.h"
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
file|"widgets/gimppropwidgets.h"
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
file|"gimppainttool-paint.h"
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
name|gimp_airbrush_tool_constructed
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
name|gimp_airbrush_tool_airbrush_stamp
parameter_list|(
name|GimpAirbrush
modifier|*
name|airbrush
parameter_list|,
name|GimpAirbrushTool
modifier|*
name|airbrush_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_airbrush_tool_stamp
parameter_list|(
name|GimpAirbrushTool
modifier|*
name|airbrush_tool
parameter_list|,
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

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

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_airbrush_tool_parent_class
end_define

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
name|GIMP_CONTEXT_PROP_MASK_GRADIENT
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
literal|"Airbrush Tool: Paint using a brush, with variable pressure"
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
name|GIMP_ICON_TOOL_AIRBRUSH
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
block|{
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|constructed
operator|=
name|gimp_airbrush_tool_constructed
expr_stmt|;
block|}
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
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_tool_constructed (GObject * object)
name|gimp_airbrush_tool_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|,
literal|"stamp"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_airbrush_tool_airbrush_stamp
argument_list|)
argument_list|,
name|object
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_tool_airbrush_stamp (GimpAirbrush * airbrush,GimpAirbrushTool * airbrush_tool)
name|gimp_airbrush_tool_airbrush_stamp
parameter_list|(
name|GimpAirbrush
modifier|*
name|airbrush
parameter_list|,
name|GimpAirbrushTool
modifier|*
name|airbrush_tool
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|airbrush_tool
argument_list|)
decl_stmt|;
name|gimp_paint_tool_paint_push
argument_list|(
name|paint_tool
argument_list|,
operator|(
name|GimpPaintToolPaintFunc
operator|)
name|gimp_airbrush_tool_stamp
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_tool_stamp (GimpAirbrushTool * airbrush_tool,gpointer data)
name|gimp_airbrush_tool_stamp
parameter_list|(
name|GimpAirbrushTool
modifier|*
name|airbrush_tool
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
init|=
name|GIMP_PAINT_TOOL
argument_list|(
name|airbrush_tool
argument_list|)
decl_stmt|;
name|gimp_airbrush_stamp
argument_list|(
name|GIMP_AIRBRUSH
argument_list|(
name|paint_tool
operator|->
name|core
argument_list|)
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
name|button
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|button
operator|=
name|gimp_prop_check_button_new
argument_list|(
name|config
argument_list|,
literal|"motion-only"
argument_list|,
name|NULL
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
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"rate"
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gimp_prop_spin_scale_new
argument_list|(
name|config
argument_list|,
literal|"flow"
argument_list|,
name|NULL
argument_list|,
literal|1.0
argument_list|,
literal|10.0
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|scale
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
name|scale
argument_list|)
expr_stmt|;
return|return
name|vbox
return|;
block|}
end_function

end_unit

