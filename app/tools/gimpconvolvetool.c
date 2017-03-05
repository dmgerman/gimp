begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"paint/gimpconvolveoptions.h"
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
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"gimpconvolvetool.h"
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
name|gimp_convolve_tool_modifier_key
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
name|gimp_convolve_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|gimp_convolve_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|gimp_convolve_tool_status_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpConvolveType
name|type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GtkWidget
modifier|*
name|gimp_convolve_options_gui
parameter_list|(
name|GimpToolOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpConvolveTool,gimp_convolve_tool,GIMP_TYPE_BRUSH_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpConvolveTool
argument_list|,
argument|gimp_convolve_tool
argument_list|,
argument|GIMP_TYPE_BRUSH_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_convolve_tool_parent_class
end_define

begin_function
name|void
name|gimp_convolve_tool_register
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
name|GIMP_TYPE_CONVOLVE_TOOL
argument_list|,
name|GIMP_TYPE_CONVOLVE_OPTIONS
argument_list|,
name|gimp_convolve_options_gui
argument_list|,
name|GIMP_PAINT_OPTIONS_CONTEXT_MASK
argument_list|,
literal|"gimp-convolve-tool"
argument_list|,
name|_
argument_list|(
literal|"Blur / Sharpen"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Blur / Sharpen Tool: Selective blurring or unblurring using a brush"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"Bl_ur / Sharpen"
argument_list|)
argument_list|,
literal|"<shift>U"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_CONVOLVE
argument_list|,
name|GIMP_ICON_TOOL_BLUR
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_tool_class_init (GimpConvolveToolClass * klass)
name|gimp_convolve_tool_class_init
parameter_list|(
name|GimpConvolveToolClass
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
name|gimp_convolve_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_convolve_tool_cursor_update
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_convolve_tool_oper_update
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_tool_init (GimpConvolveTool * convolve)
name|gimp_convolve_tool_init
parameter_list|(
name|GimpConvolveTool
modifier|*
name|convolve
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|convolve
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_BLUR
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
name|gimp_convolve_tool_status_update
argument_list|(
name|tool
argument_list|,
name|GIMP_CONVOLVE_BLUR
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_convolve_tool_modifier_key
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
name|GimpConvolveTool
modifier|*
name|convolve
init|=
name|GIMP_CONVOLVE_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpConvolveOptions
modifier|*
name|options
init|=
name|GIMP_CONVOLVE_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GdkModifierType
name|line_mask
init|=
name|GIMP_PAINT_TOOL_LINE_MASK
decl_stmt|;
name|GdkModifierType
name|toggle_mask
init|=
name|gimp_get_toggle_behavior_mask
argument_list|()
decl_stmt|;
if|if
condition|(
operator|(
operator|(
name|key
operator|==
name|toggle_mask
operator|)
operator|&&
operator|!
operator|(
name|state
operator|&
name|line_mask
operator|)
operator|&&
comment|/* leave stuff untouched in line draw mode */
name|press
operator|!=
name|convolve
operator|->
name|toggled
operator|)
operator|||
operator|(
name|key
operator|==
name|line_mask
operator|&&
comment|/* toggle back after keypresses CTRL(hold)->  */
operator|!
name|press
operator|&&
comment|/* SHIFT(hold)->CTRL(release)->SHIFT(release) */
name|convolve
operator|->
name|toggled
operator|&&
operator|!
operator|(
name|state
operator|&
name|toggle_mask
operator|)
operator|)
condition|)
block|{
name|convolve
operator|->
name|toggled
operator|=
name|press
expr_stmt|;
switch|switch
condition|(
name|options
operator|->
name|type
condition|)
block|{
case|case
name|GIMP_CONVOLVE_BLUR
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"type"
argument_list|,
name|GIMP_CONVOLVE_SHARPEN
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CONVOLVE_SHARPEN
case|:
name|g_object_set
argument_list|(
name|options
argument_list|,
literal|"type"
argument_list|,
name|GIMP_CONVOLVE_BLUR
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_convolve_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_convolve_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|GimpConvolveOptions
modifier|*
name|options
init|=
name|GIMP_CONVOLVE_TOOL_GET_OPTIONS
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
name|options
operator|->
name|type
operator|==
name|GIMP_CONVOLVE_SHARPEN
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
DECL|function|gimp_convolve_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_convolve_tool_oper_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
specifier|const
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
name|GimpConvolveOptions
modifier|*
name|options
init|=
name|GIMP_CONVOLVE_TOOL_GET_OPTIONS
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|gimp_convolve_tool_status_update
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
DECL|function|gimp_convolve_tool_status_update (GimpTool * tool,GimpConvolveType type)
name|gimp_convolve_tool_status_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpConvolveType
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
name|GIMP_CONVOLVE_BLUR
case|:
name|paint_tool
operator|->
name|status
operator|=
name|_
argument_list|(
literal|"Click to blur"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_line
operator|=
name|_
argument_list|(
literal|"Click to blur the line"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_ctrl
operator|=
name|_
argument_list|(
literal|"%s to sharpen"
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_CONVOLVE_SHARPEN
case|:
name|paint_tool
operator|->
name|status
operator|=
name|_
argument_list|(
literal|"Click to sharpen"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_line
operator|=
name|_
argument_list|(
literal|"Click to sharpen the line"
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|status_ctrl
operator|=
name|_
argument_list|(
literal|"%s to blur"
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
DECL|function|gimp_convolve_options_gui (GimpToolOptions * tool_options)
name|gimp_convolve_options_gui
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
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|GdkModifierType
name|toggle_mask
decl_stmt|;
name|toggle_mask
operator|=
name|gimp_get_toggle_behavior_mask
argument_list|()
expr_stmt|;
comment|/*  the type radio box  */
name|str
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Convolve Type  (%s)"
argument_list|)
argument_list|,
name|gimp_get_mod_string
argument_list|(
name|toggle_mask
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
comment|/*  the rate scale  */
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
return|return
name|vbox
return|;
block|}
end_function

end_unit

