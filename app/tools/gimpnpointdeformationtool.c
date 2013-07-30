begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  *  * gimpnpointdeformationtool.c  * Copyright (C) 2013 Marek Dvoroznak<dvoromar@gmail.com>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk/gdkkeysyms.h>
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
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-shadow.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-private.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimagemap.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpprojection.h"
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
file|"gimptooloptions-gui.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolcontrol.h"
end_include

begin_include
include|#
directive|include
file|"gimpnpointdeformationtool.h"
end_include

begin_include
include|#
directive|include
file|"gimpnpointdeformationoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|//#include<npd/npd_common.h>
end_comment

begin_function_decl
name|void
name|gimp_n_point_deformation_tool_start
parameter_list|(
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_n_point_deformation_tool_halt
parameter_list|(
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_n_point_deformation_tool_options_notify
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_n_point_deformation_tool_button_press
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
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonPressType
name|press_type
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
name|gimp_n_point_deformation_tool_button_release
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
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_n_point_deformation_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
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
name|gimp_n_point_deformation_tool_modifier_key
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
name|gimp_n_point_deformation_tool_cursor_update
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
name|gimp_n_point_deformation_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|//static void     gimp_n_point_deformation_add_handle                   (GimpNPointDeformationTool *npd_tool,
end_comment

begin_comment
comment|//                                                                       NPDPoint                  *coords);
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_n_point_deformation_tool_control
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
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_n_point_deformation_tool_oper_update
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
name|gimp_n_point_deformation_tool_motion
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
name|guint32
name|time
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpNPointDeformationTool,gimp_n_point_deformation_tool,GIMP_TYPE_DRAW_TOOL)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpNPointDeformationTool
argument_list|,
argument|gimp_n_point_deformation_tool
argument_list|,
argument|GIMP_TYPE_DRAW_TOOL
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_n_point_deformation_tool_parent_class
end_define

begin_function
name|void
name|gimp_n_point_deformation_tool_register
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
name|GIMP_TYPE_N_POINT_DEFORMATION_TOOL
argument_list|,
name|GIMP_TYPE_N_POINT_DEFORMATION_OPTIONS
argument_list|,
name|gimp_n_point_deformation_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-n-point-deformation-tool"
argument_list|,
name|_
argument_list|(
literal|"N-Point Deformation"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"N-Point Deformation Tool: Deform image using points"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_N-Point Deformation"
argument_list|)
argument_list|,
literal|"<shift>N"
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_N_POINT_DEFORMATION
argument_list|,
name|GIMP_STOCK_TOOL_N_POINT_DEFORMATION
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_class_init (GimpNPointDeformationToolClass * klass)
name|gimp_n_point_deformation_tool_class_init
parameter_list|(
name|GimpNPointDeformationToolClass
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
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
init|=
name|GIMP_DRAW_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|tool_class
operator|->
name|options_notify
operator|=
name|gimp_n_point_deformation_tool_options_notify
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_n_point_deformation_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_n_point_deformation_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_n_point_deformation_tool_key_press
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_n_point_deformation_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_n_point_deformation_tool_control
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_n_point_deformation_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_n_point_deformation_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_n_point_deformation_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_n_point_deformation_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_init (GimpNPointDeformationTool * npd_tool)
name|gimp_n_point_deformation_tool_init
parameter_list|(
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|npd_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_PERSPECTIVE
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
name|gimp_tool_control_set_wants_click
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_wants_double_click
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|TRUE
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
name|gimp_tool_control_set_handle_empty_image
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_dirty_mask
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_DIRTY_IMAGE
operator||
name|GIMP_DIRTY_IMAGE_STRUCTURE
operator||
name|GIMP_DIRTY_DRAWABLE
operator||
name|GIMP_DIRTY_SELECTION
operator||
name|GIMP_DIRTY_ACTIVE_DRAWABLE
argument_list|)
expr_stmt|;
name|npd_tool
operator|->
name|active
operator|=
name|FALSE
expr_stmt|;
comment|//  npd_tool->selected_cp = NULL;
comment|//  npd_tool->hovering_cp = NULL;
name|npd_tool
operator|->
name|selected_cps
operator|=
name|NULL
expr_stmt|;
name|npd_tool
operator|->
name|previous_cp_positions
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * display)
name|gimp_n_point_deformation_tool_control
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
name|display
parameter_list|)
block|{
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
init|=
name|GIMP_N_POINT_DEFORMATION_TOOL
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
name|GIMP_TOOL_ACTION_PAUSE
case|:
break|break;
case|case
name|GIMP_TOOL_ACTION_RESUME
case|:
break|break;
case|case
name|GIMP_TOOL_ACTION_HALT
case|:
name|gimp_n_point_deformation_tool_halt
argument_list|(
name|npd_tool
argument_list|)
expr_stmt|;
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
name|display
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_n_point_deformation_tool_start (GimpNPointDeformationTool * npd_tool,GimpDisplay * display)
name|gimp_n_point_deformation_tool_start
parameter_list|(
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|npd_tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|npd_tool
argument_list|)
decl_stmt|;
name|GeglNode
modifier|*
name|graph
decl_stmt|;
name|GeglNode
modifier|*
name|node
decl_stmt|;
name|GeglNode
modifier|*
name|source
decl_stmt|;
name|GeglNode
modifier|*
name|sink
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GeglBuffer
modifier|*
name|buf
decl_stmt|;
name|GeglBuffer
modifier|*
name|shadow
decl_stmt|;
comment|//  NPDModel      *model;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_N_POINT_DEFORMATION_TOOL
argument_list|(
name|npd_tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_tool_control
argument_list|(
name|tool
argument_list|,
name|GIMP_TOOL_ACTION_HALT
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|display
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|draw_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
name|npd_tool
operator|->
name|active
operator|=
name|TRUE
expr_stmt|;
name|image
operator|=
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
expr_stmt|;
name|drawable
operator|=
name|gimp_image_get_active_drawable
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|buf
operator|=
name|drawable
operator|->
name|private
operator|->
name|buffer
expr_stmt|;
name|shadow
operator|=
name|gegl_buffer_new
argument_list|(
name|gegl_buffer_get_extent
argument_list|(
name|buf
argument_list|)
argument_list|,
name|gegl_buffer_get_format
argument_list|(
name|buf
argument_list|)
argument_list|)
expr_stmt|;
name|graph
operator|=
name|gegl_node_new
argument_list|()
expr_stmt|;
name|source
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:buffer-source"
argument_list|,
literal|"buffer"
argument_list|,
name|buf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|node
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:npd"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|sink
operator|=
name|gegl_node_new_child
argument_list|(
name|graph
argument_list|,
literal|"operation"
argument_list|,
literal|"gegl:write-buffer"
argument_list|,
literal|"buffer"
argument_list|,
name|shadow
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_link_many
argument_list|(
name|source
argument_list|,
name|node
argument_list|,
name|sink
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|sink
argument_list|)
expr_stmt|;
comment|//  gegl_node_get (node, "model",&model, NULL);
name|gegl_node_set
argument_list|(
name|node
argument_list|,
literal|"rigidity"
argument_list|,
literal|2000
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|npd_tool
operator|->
name|buf
operator|=
name|buf
expr_stmt|;
name|npd_tool
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|npd_tool
operator|->
name|graph
operator|=
name|graph
expr_stmt|;
comment|//  npd_tool->model = model;
name|npd_tool
operator|->
name|node
operator|=
name|node
expr_stmt|;
name|npd_tool
operator|->
name|shadow
operator|=
name|shadow
expr_stmt|;
name|npd_tool
operator|->
name|sink
operator|=
name|sink
expr_stmt|;
comment|//  npd_tool->selected_cp = NULL;
block|}
end_function

begin_function
name|void
DECL|function|gimp_n_point_deformation_tool_halt (GimpNPointDeformationTool * npd_tool)
name|gimp_n_point_deformation_tool_halt
parameter_list|(
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|npd_tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|npd_tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_draw_tool_is_active
argument_list|(
name|draw_tool
argument_list|)
condition|)
name|gimp_draw_tool_stop
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|tool
operator|->
name|display
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_options_notify (GimpTool * tool,GimpToolOptions * options,const GParamSpec * pspec)
name|gimp_n_point_deformation_tool_options_notify
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GimpToolOptions
modifier|*
name|options
parameter_list|,
specifier|const
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_n_point_deformation_tool_key_press (GimpTool * tool,GdkEventKey * kevent,GimpDisplay * display)
name|gimp_n_point_deformation_tool_key_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
switch|switch
condition|(
name|kevent
operator|->
name|keyval
condition|)
block|{
case|case
name|GDK_KEY_BackSpace
case|:
return|return
name|TRUE
return|;
case|case
name|GDK_KEY_Return
case|:
case|case
name|GDK_KEY_KP_Enter
case|:
case|case
name|GDK_KEY_ISO_Enter
case|:
case|case
name|GDK_KEY_Escape
case|:
return|return
name|TRUE
return|;
default|default:
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * display)
name|gimp_n_point_deformation_tool_modifier_key
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
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_cursor_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,GimpDisplay * display)
name|gimp_n_point_deformation_tool_cursor_update
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
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_button_press (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonPressType press_type,GimpDisplay * display)
name|gimp_n_point_deformation_tool_button_press
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
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonPressType
name|press_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
init|=
name|GIMP_N_POINT_DEFORMATION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
comment|//  NPDModel                  *model;
comment|//  NPDPoint                   p;
comment|//  NPDControlPoint           *cp;
comment|//  GSList                   **selected_cps =&npd_tool->selected_cps;
comment|//  GSList                   **previous_cp_positions =&npd_tool->previous_cp_positions;
if|if
condition|(
name|display
operator|!=
name|tool
operator|->
name|display
condition|)
block|{
name|gimp_n_point_deformation_tool_start
argument_list|(
name|npd_tool
argument_list|,
name|display
argument_list|)
expr_stmt|;
block|}
comment|//  model = npd_tool->model;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
comment|//  npd_tool->selected_cp = NULL;
if|if
condition|(
name|press_type
operator|==
name|GIMP_BUTTON_PRESS_NORMAL
condition|)
block|{
comment|//      p.x = coords->x; p.y = coords->y;
comment|//      cp = npd_get_control_point_at (model,&p);
comment|//      if (cp == NULL || (cp != NULL&& !g_slist_find (*selected_cps, cp)&& !(state& GDK_SHIFT_MASK)))
comment|//        {
comment|//          g_slist_free (*selected_cps);
comment|//          *selected_cps = NULL;
comment|//          g_slist_free_full (*previous_cp_positions, g_free);
comment|//          *previous_cp_positions = NULL;
comment|//        }
comment|//
comment|//
comment|//      if (cp != NULL)
comment|//        {
comment|//          NPDPoint *cp_point_copy = g_new (NPDPoint, 1);
comment|//          *cp_point_copy = cp->point;
comment|//          npd_tool->selected_cp = cp;
comment|//          npd_tool->delta_x = cp->point.x - coords->x;
comment|//          npd_tool->delta_y = cp->point.y - coords->y;
comment|//          *selected_cps = g_slist_append (*selected_cps, cp);
comment|//          *previous_cp_positions = g_slist_append (*previous_cp_positions, cp_point_copy);
comment|//        }
name|npd_tool
operator|->
name|movement_start_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|npd_tool
operator|->
name|movement_start_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_button_release (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpButtonReleaseType release_type,GimpDisplay * display)
name|gimp_n_point_deformation_tool_button_release
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
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpButtonReleaseType
name|release_type
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
init|=
name|GIMP_N_POINT_DEFORMATION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
comment|//  NPDModel                  *model = npd_tool->model;
comment|//  NPDPoint                   p;
comment|//  NPDControlPoint           *cp;
name|GeglBuffer
modifier|*
name|buffer
decl_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|npd_tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_CLICK
condition|)
block|{
comment|//      p.x = coords->x; p.y = coords->y;
comment|//      cp = npd_get_control_point_at (model,&p);
comment|//      if (cp != NULL)
comment|//        {
comment|//          gimp_n_point_deformation_add_handle (npd_tool,&p);
comment|//        }
block|}
elseif|else
if|if
condition|(
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_NORMAL
condition|)
block|{     }
elseif|else
if|if
condition|(
name|release_type
operator|==
name|GIMP_BUTTON_RELEASE_CANCEL
condition|)
block|{     }
name|buffer
operator|=
name|npd_tool
operator|->
name|drawable
operator|->
name|private
operator|->
name|buffer
expr_stmt|;
name|gegl_node_invalidated
argument_list|(
name|npd_tool
operator|->
name|node
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gegl_node_process
argument_list|(
name|npd_tool
operator|->
name|sink
argument_list|)
expr_stmt|;
name|gegl_buffer_copy
argument_list|(
name|npd_tool
operator|->
name|shadow
argument_list|,
name|NULL
argument_list|,
name|npd_tool
operator|->
name|buf
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_drawable_update
argument_list|(
name|npd_tool
operator|->
name|drawable
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|gegl_buffer_get_width
argument_list|(
name|buffer
argument_list|)
argument_list|,
name|gegl_buffer_get_height
argument_list|(
name|buffer
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimp_display_get_image
argument_list|(
name|display
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|npd_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_oper_update (GimpTool * tool,const GimpCoords * coords,GdkModifierType state,gboolean proximity,GimpDisplay * display)
name|gimp_n_point_deformation_tool_oper_update
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
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
init|=
name|GIMP_N_POINT_DEFORMATION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
name|GimpDrawTool
modifier|*
name|draw_tool
init|=
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
if|if
condition|(
name|npd_tool
operator|->
name|active
condition|)
block|{
comment|//      NPDModel *model = npd_tool->model;
comment|//      NPDPoint p;
comment|//      p.x = coords->x; p.y = coords->y;
comment|//      npd_tool->hovering_cp = npd_get_control_point_at (model,&p);
block|}
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|npd_tool
operator|->
name|cursor_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|npd_tool
operator|->
name|cursor_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|//static void
end_comment

begin_comment
comment|//gimp_n_point_deformation_add_handle (GimpNPointDeformationTool *npd_tool,
end_comment

begin_comment
comment|//                                     NPDPoint *coords)
end_comment

begin_comment
comment|//{
end_comment

begin_comment
comment|//  NPDModel *model = npd_tool->model;
end_comment

begin_comment
comment|//  npd_add_control_point (model, coords);
end_comment

begin_comment
comment|//}
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_draw (GimpDrawTool * draw_tool)
name|gimp_n_point_deformation_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
comment|//  GimpNPointDeformationTool *npd_tool = GIMP_N_POINT_DEFORMATION_TOOL (draw_tool);
comment|//  NPDModel                  *model = npd_tool->model;
comment|//  gint                       i;
comment|//  NPDControlPoint           *cp;
comment|//  GimpHandleType             handle_type;
comment|//  g_return_if_fail (model != NULL);
comment|//  for (i = 0; i< model->control_points->len; i++)
comment|//    {
comment|//      cp =&g_array_index (model->control_points, NPDControlPoint, i);
comment|//
comment|//      if (cp == npd_tool->hovering_cp)
comment|//        handle_type = GIMP_HANDLE_FILLED_CIRCLE;
comment|//      else
comment|//        handle_type = GIMP_HANDLE_CIRCLE;
comment|//
comment|//      gimp_draw_tool_add_handle (draw_tool,
comment|//                                 handle_type,
comment|//                                 cp->point.x,
comment|//                                 cp->point.y,
comment|//                                 GIMP_TOOL_HANDLE_SIZE_CIRCLE,
comment|//                                 GIMP_TOOL_HANDLE_SIZE_CIRCLE,
comment|//                                 GIMP_HANDLE_ANCHOR_CENTER);
comment|//
comment|//      if (g_slist_find (npd_tool->selected_cps, cp) != NULL)
comment|//        {
comment|//          gimp_draw_tool_add_handle (draw_tool,
comment|//                                     GIMP_HANDLE_SQUARE,
comment|//                                     cp->point.x,
comment|//                                     cp->point.y,
comment|//                                     GIMP_TOOL_HANDLE_SIZE_CIRCLE,
comment|//                                     GIMP_TOOL_HANDLE_SIZE_CIRCLE,
comment|//                                     GIMP_HANDLE_ANCHOR_CENTER);
comment|//        }
comment|//    }
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_n_point_deformation_tool_motion (GimpTool * tool,const GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * display)
name|gimp_n_point_deformation_tool_motion
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
name|guint32
name|time
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpDisplay
modifier|*
name|display
parameter_list|)
block|{
name|GimpNPointDeformationTool
modifier|*
name|npd_tool
init|=
name|GIMP_N_POINT_DEFORMATION_TOOL
argument_list|(
name|tool
argument_list|)
decl_stmt|;
comment|//  NPDControlPoint           *selected_cp = npd_tool->selected_cp;
comment|//  GSList                    *selected_cps = npd_tool->selected_cps;
comment|//  GSList                    *previous_cp_positions = npd_tool->previous_cp_positions;
comment|//  gdouble                    movement_x = coords->x - npd_tool->movement_start_x;
comment|//  gdouble                    movement_y = coords->y - npd_tool->movement_start_y;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
comment|//  if (selected_cp != NULL)
comment|//    {
comment|//      while (selected_cps != NULL)
comment|//        {
comment|//          NPDControlPoint *cp = selected_cps->data;
comment|//          NPDPoint *p =&cp->point;
comment|//          NPDPoint *prev = previous_cp_positions->data;
comment|//          p->x = prev->x + movement_x;
comment|//          p->y = prev->y + movement_y;
comment|//
comment|//          selected_cps = g_slist_next (selected_cps);
comment|//          previous_cp_positions = g_slist_next (previous_cp_positions);
comment|//        }
comment|//    }
name|npd_tool
operator|->
name|cursor_x
operator|=
name|coords
operator|->
name|x
expr_stmt|;
name|npd_tool
operator|->
name|cursor_y
operator|=
name|coords
operator|->
name|y
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

