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
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel-select.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer-floating-sel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpcanvas.h"
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
file|"display/gimpdisplayshell-transform.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectiontool.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectionoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangletool.h"
end_include

begin_include
include|#
directive|include
file|"gimprectangleoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpnewrectselecttool.h"
end_include

begin_include
include|#
directive|include
file|"gimpnewrectselectoptions.h"
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
name|gimp_new_rect_select_tool_class_init
parameter_list|(
name|GimpNewRectSelectToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_new_rect_select_tool_init
parameter_list|(
name|GimpNewRectSelectTool
modifier|*
name|rect_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_new_rect_select_tool_rectangle_tool_iface_init
parameter_list|(
name|GimpRectangleToolInterface
modifier|*
name|rectangle_iface
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GObject
modifier|*
name|gimp_new_rect_select_tool_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_new_rect_select_tool_finalize
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
name|gimp_new_rect_select_tool_control
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
name|gimp_new_rect_select_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_new_rect_select_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_new_rect_select_tool_oper_update
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
name|gboolean
name|gimp_new_rect_select_tool_execute
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rect_tool
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpSelectionToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_new_rect_select_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_new_rect_select_tool_register
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
name|GIMP_TYPE_NEW_RECT_SELECT_TOOL
argument_list|,
name|GIMP_TYPE_NEW_RECT_SELECT_OPTIONS
argument_list|,
name|gimp_new_rect_select_options_gui
argument_list|,
literal|0
argument_list|,
literal|"gimp-new-rect-select-tool"
argument_list|,
name|_
argument_list|(
literal|"New Rect Select"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select a Rectangular part of an image"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"_New Rect Select"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_HELP_TOOL_RECT_SELECT
argument_list|,
name|GIMP_STOCK_TOOL_RECT_SELECT
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_new_rect_select_tool_get_type (void)
name|gimp_new_rect_select_tool_get_type
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
name|GimpNewRectSelectToolClass
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
name|gimp_new_rect_select_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpNewRectSelectTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_new_rect_select_tool_init
block|,       }
decl_stmt|;
specifier|static
specifier|const
name|GInterfaceInfo
name|rectangle_info
init|=
block|{
operator|(
name|GInterfaceInitFunc
operator|)
name|gimp_new_rect_select_tool_rectangle_tool_iface_init
block|,
comment|/* interface_init */
name|NULL
block|,
comment|/* interface_finalize */
name|NULL
comment|/* interface_data */
block|}
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_SELECTION_TOOL
argument_list|,
literal|"GimpNewRectSelectTool"
argument_list|,
operator|&
name|tool_info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_type_add_interface_static
argument_list|(
name|tool_type
argument_list|,
name|GIMP_TYPE_RECTANGLE_TOOL
argument_list|,
operator|&
name|rectangle_info
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
DECL|function|gimp_new_rect_select_tool_class_init (GimpNewRectSelectToolClass * klass)
name|gimp_new_rect_select_tool_class_init
parameter_list|(
name|GimpNewRectSelectToolClass
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
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|constructor
operator|=
name|gimp_new_rect_select_tool_constructor
expr_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_rectangle_tool_dispose
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_new_rect_select_tool_finalize
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_rectangle_tool_set_property
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_rectangle_tool_get_property
expr_stmt|;
name|gimp_rectangle_tool_install_properties
argument_list|(
name|object_class
argument_list|)
expr_stmt|;
name|tool_class
operator|->
name|initialize
operator|=
name|gimp_rectangle_tool_initialize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_new_rect_select_tool_control
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_new_rect_select_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_new_rect_select_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_rectangle_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|key_press
operator|=
name|gimp_rectangle_tool_key_press
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_rectangle_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|oper_update
operator|=
name|gimp_new_rect_select_tool_oper_update
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_rectangle_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_rectangle_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_new_rect_select_tool_init (GimpNewRectSelectTool * new_rect_select_tool)
name|gimp_new_rect_select_tool_init
parameter_list|(
name|GimpNewRectSelectTool
modifier|*
name|new_rect_select_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|new_rect_select_tool
argument_list|)
decl_stmt|;
name|gimp_tool_control_set_tool_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|GIMP_TOOL_CURSOR_RECT_SELECT
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_new_rect_select_tool_rectangle_tool_iface_init (GimpRectangleToolInterface * rectangle_iface)
name|gimp_new_rect_select_tool_rectangle_tool_iface_init
parameter_list|(
name|GimpRectangleToolInterface
modifier|*
name|rectangle_iface
parameter_list|)
block|{
name|rectangle_iface
operator|->
name|execute
operator|=
name|gimp_new_rect_select_tool_execute
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|GObject
modifier|*
DECL|function|gimp_new_rect_select_tool_constructor (GType type,guint n_params,GObjectConstructParam * params)
name|gimp_new_rect_select_tool_constructor
parameter_list|(
name|GType
name|type
parameter_list|,
name|guint
name|n_params
parameter_list|,
name|GObjectConstructParam
modifier|*
name|params
parameter_list|)
block|{
name|GObject
modifier|*
name|object
decl_stmt|;
name|object
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructor
argument_list|(
name|type
argument_list|,
name|n_params
argument_list|,
name|params
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_constructor
argument_list|(
name|object
argument_list|)
expr_stmt|;
return|return
name|object
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_new_rect_select_tool_finalize (GObject * object)
name|gimp_new_rect_select_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
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
DECL|function|gimp_new_rect_select_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|gimp_new_rect_select_tool_control
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
name|GimpRectangleTool
modifier|*
name|rectangle
init|=
name|GIMP_RECTANGLE_TOOL
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
name|PAUSE
case|:
break|break;
case|case
name|RESUME
case|:
name|gimp_rectangle_tool_configure
argument_list|(
name|rectangle
argument_list|)
expr_stmt|;
break|break;
case|case
name|HALT
case|:
name|gimp_rectangle_tool_response
argument_list|(
name|NULL
argument_list|,
name|GIMP_RECTANGLE_MODE_EXECUTE
argument_list|,
name|rectangle
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
DECL|function|gimp_new_rect_select_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_new_rect_select_tool_button_press
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|gdisp
parameter_list|)
block|{
if|if
condition|(
name|tool
operator|->
name|gdisp
operator|&&
name|gdisp
operator|!=
name|tool
operator|->
name|gdisp
condition|)
name|gimp_rectangle_tool_response
argument_list|(
name|NULL
argument_list|,
name|GIMP_RECTANGLE_MODE_EXECUTE
argument_list|,
name|GIMP_RECTANGLE_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_button_press
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_new_rect_select_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_new_rect_select_tool_button_release
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
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
name|gdisp
parameter_list|)
block|{
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|_
argument_list|(
literal|"Click or press enter to create the selection."
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_button_release
argument_list|(
name|tool
argument_list|,
name|coords
argument_list|,
name|time
argument_list|,
name|state
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_new_rect_select_tool_oper_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_new_rect_select_tool_oper_update
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
name|gimp_rectangle_tool_oper_update
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
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  * This function is called if the user clicks and releases the left  * button without moving it.  There are five things we might want  * to do here:  * 1) If there is a floating selection, we anchor it.  * 2) If there is an existing rectangle and we are inside it, we  *    convert it into a selection.  * 3) If there is an existing rectangle and we are outside it, we  *    clear it.  * 4) If there is no rectangle and we are inside the selection, we  *    create a rectangle from the selection bounds.  * 5) If there is no rectangle and we are outside the selection,  *    we clear the selection.  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_new_rect_select_tool_execute (GimpRectangleTool * rectangle,gint x,gint y,gint w,gint h)
name|gimp_new_rect_select_tool_execute
parameter_list|(
name|GimpRectangleTool
modifier|*
name|rectangle
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
init|=
name|GIMP_TOOL
argument_list|(
name|rectangle
argument_list|)
decl_stmt|;
name|GimpSelectionOptions
modifier|*
name|options
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gint
name|max_x
decl_stmt|,
name|max_y
decl_stmt|;
name|gboolean
name|rectangle_exists
decl_stmt|;
name|gboolean
name|selected
decl_stmt|;
name|gint
name|val
decl_stmt|;
name|GimpChannel
modifier|*
name|selection_mask
decl_stmt|;
name|gint
name|x1
decl_stmt|,
name|y1
decl_stmt|;
name|gint
name|x2
decl_stmt|,
name|y2
decl_stmt|;
name|options
operator|=
name|GIMP_SELECTION_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|tool
operator|->
name|gdisp
operator|->
name|gimage
expr_stmt|;
name|max_x
operator|=
name|gimage
operator|->
name|width
expr_stmt|;
name|max_y
operator|=
name|gimage
operator|->
name|height
expr_stmt|;
name|selection_mask
operator|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
name|rectangle_exists
operator|=
operator|(
name|x
operator|<=
name|max_x
operator|&&
name|y
operator|<=
name|max_y
operator|&&
name|x
operator|+
name|w
operator|>=
literal|0
operator|&&
name|y
operator|+
name|h
operator|>=
literal|0
operator|&&
name|w
operator|>
literal|0
operator|&&
name|h
operator|>
literal|0
operator|)
expr_stmt|;
if|if
condition|(
name|x
operator|<
literal|0
condition|)
block|{
name|w
operator|+=
name|x
expr_stmt|;
name|x
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|y
operator|<
literal|0
condition|)
block|{
name|h
operator|+=
name|y
expr_stmt|;
name|y
operator|=
literal|0
expr_stmt|;
block|}
if|if
condition|(
name|x
operator|+
name|w
operator|>
name|max_x
condition|)
name|w
operator|=
name|max_x
operator|-
name|x
expr_stmt|;
if|if
condition|(
name|y
operator|+
name|h
operator|>
name|max_y
condition|)
name|h
operator|=
name|max_y
operator|-
name|y
expr_stmt|;
comment|/*  If there is a floating selection, anchor it  */
if|if
condition|(
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
condition|)
block|{
name|floating_sel_anchor
argument_list|(
name|gimp_image_floating_sel
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/* if rectangle exists, turn it into a selection */
if|if
condition|(
name|rectangle_exists
condition|)
block|{
name|GimpChannel
modifier|*
name|selection_mask
init|=
name|gimp_image_get_mask
argument_list|(
name|gimage
argument_list|)
decl_stmt|;
name|gimp_channel_select_rectangle
argument_list|(
name|selection_mask
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|w
argument_list|,
name|h
argument_list|,
name|options
operator|->
name|operation
argument_list|,
name|options
operator|->
name|feather
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|,
name|options
operator|->
name|feather_radius
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
name|val
operator|=
name|gimp_pickable_get_opacity_at
argument_list|(
name|GIMP_PICKABLE
argument_list|(
name|selection_mask
argument_list|)
argument_list|,
name|gimp_rectangle_tool_get_pressx
argument_list|(
name|rectangle
argument_list|)
argument_list|,
name|gimp_rectangle_tool_get_pressy
argument_list|(
name|rectangle
argument_list|)
argument_list|)
expr_stmt|;
name|selected
operator|=
operator|(
name|val
operator|>
literal|127
operator|)
expr_stmt|;
comment|/* if point clicked is inside selection, set rectangle to  */
comment|/* selection bounds.                                       */
if|if
condition|(
name|selected
condition|)
block|{
if|if
condition|(
operator|!
name|gimp_channel_bounds
argument_list|(
name|selection_mask
argument_list|,
operator|&
name|x1
argument_list|,
operator|&
name|y1
argument_list|,
operator|&
name|x2
argument_list|,
operator|&
name|y2
argument_list|)
condition|)
block|{
name|gimp_rectangle_tool_set_x1
argument_list|(
name|rectangle
argument_list|,
name|x1
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_y1
argument_list|(
name|rectangle
argument_list|,
name|y1
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_x2
argument_list|(
name|rectangle
argument_list|,
name|x2
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_y2
argument_list|(
name|rectangle
argument_list|,
name|y2
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gimp_rectangle_tool_set_x1
argument_list|(
name|rectangle
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_y1
argument_list|(
name|rectangle
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_x2
argument_list|(
name|rectangle
argument_list|,
name|gimage
operator|->
name|width
argument_list|)
expr_stmt|;
name|gimp_rectangle_tool_set_y2
argument_list|(
name|rectangle
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
expr_stmt|;
block|}
return|return
name|FALSE
return|;
block|}
comment|/* otherwise clear the selection */
name|gimp_channel_clear
argument_list|(
name|selection_mask
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

