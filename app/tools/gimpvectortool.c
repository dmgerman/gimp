begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Vector tool  * Copyright (C) 1999 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplist.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpanchor.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpvectors.h"
end_include

begin_include
include|#
directive|include
file|"vectors/gimpbezierstroke.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-foreach.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectoroptions.h"
end_include

begin_include
include|#
directive|include
file|"gimpvectortool.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|TARGET
define|#
directive|define
name|TARGET
value|9
end_define

begin_define
DECL|macro|ARC_RADIUS
define|#
directive|define
name|ARC_RADIUS
value|30
end_define

begin_define
DECL|macro|STATUSBAR_SIZE
define|#
directive|define
name|STATUSBAR_SIZE
value|128
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_vector_tool_class_init
parameter_list|(
name|GimpVectorToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vector_tool_init
parameter_list|(
name|GimpVectorTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_vector_tool_finalize
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
name|gimp_vector_tool_control
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
name|gimp_vector_tool_button_press
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
name|gimp_vector_tool_button_release
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
name|gimp_vector_tool_motion
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
name|gimp_vector_tool_cursor_update
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
name|void
name|gimp_vector_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
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

begin_function
name|void
DECL|function|gimp_vector_tool_register (GimpToolRegisterCallback callback,gpointer data)
name|gimp_vector_tool_register
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
name|GIMP_TYPE_VECTOR_TOOL
argument_list|,
name|GIMP_TYPE_VECTOR_OPTIONS
argument_list|,
name|gimp_vector_options_gui
argument_list|,
name|FALSE
argument_list|,
literal|"gimp-vector-tool"
argument_list|,
name|_
argument_list|(
literal|"Vectors"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"the most promising path tool prototype... :-)"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Vectors"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|"tools/vector.html"
argument_list|,
name|GIMP_STOCK_TOOL_PATH
argument_list|,
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_vector_tool_get_type (void)
name|gimp_vector_tool_get_type
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
name|GimpVectorToolClass
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
name|gimp_vector_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpVectorTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_vector_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_SELECTION_TOOL
argument_list|,
literal|"GimpVectorTool"
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
DECL|function|gimp_vector_tool_class_init (GimpVectorToolClass * klass)
name|gimp_vector_tool_class_init
parameter_list|(
name|GimpVectorToolClass
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
name|GimpDrawToolClass
modifier|*
name|draw_tool_class
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
name|draw_tool_class
operator|=
name|GIMP_DRAW_TOOL_CLASS
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
name|gimp_vector_tool_finalize
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_vector_tool_control
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_vector_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_vector_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_vector_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_vector_tool_cursor_update
expr_stmt|;
name|draw_tool_class
operator|->
name|draw
operator|=
name|gimp_vector_tool_draw
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vector_tool_init (GimpVectorTool * vector_tool)
name|gimp_vector_tool_init
parameter_list|(
name|GimpVectorTool
modifier|*
name|vector_tool
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
name|vector_tool
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
name|vector_tool
operator|->
name|function
operator|=
name|VECTORS_CREATING
expr_stmt|;
name|vector_tool
operator|->
name|last_x
operator|=
literal|0
expr_stmt|;
name|vector_tool
operator|->
name|last_y
operator|=
literal|0
expr_stmt|;
name|vector_tool
operator|->
name|cur_anchor
operator|=
name|NULL
expr_stmt|;
name|vector_tool
operator|->
name|cur_stroke
operator|=
name|NULL
expr_stmt|;
name|vector_tool
operator|->
name|vectors
operator|=
name|NULL
expr_stmt|;
name|vector_tool
operator|->
name|active_anchors
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vector_tool_finalize (GObject * object)
name|gimp_vector_tool_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpVectorTool
modifier|*
name|vector_tool
init|=
name|GIMP_VECTOR_TOOL
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|vector_tool
operator|->
name|vectors
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|vector_tool
operator|->
name|vectors
argument_list|,
name|gimp_vector_tool_clear_vectors
argument_list|,
name|vector_tool
argument_list|)
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
DECL|function|gimp_vector_tool_control (GimpTool * tool,GimpToolAction action,GimpDisplay * gdisp)
name|gimp_vector_tool_control
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
name|GimpVectorTool
modifier|*
name|vector_tool
decl_stmt|;
name|vector_tool
operator|=
name|GIMP_VECTOR_TOOL
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
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_tool_control_halt
argument_list|(
name|tool
operator|->
name|control
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
DECL|function|gimp_vector_tool_button_press (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_vector_tool_button_press
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
name|GimpVectorTool
modifier|*
name|vector_tool
decl_stmt|;
name|GimpVectorOptions
modifier|*
name|options
decl_stmt|;
name|GimpAnchor
modifier|*
name|anchor
init|=
name|NULL
decl_stmt|;
name|GimpStroke
modifier|*
name|stroke
init|=
name|NULL
decl_stmt|;
name|vector_tool
operator|=
name|GIMP_VECTOR_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_VECTOR_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
comment|/*  if we are changing displays, pop the statusbar of the old one  */
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
operator|&&
name|gdisp
operator|!=
name|tool
operator|->
name|gdisp
condition|)
block|{
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|vector_tool
operator|->
name|vectors
operator|&&
name|gdisp
operator|->
name|gimage
operator|!=
name|GIMP_ITEM
argument_list|(
name|vector_tool
operator|->
name|vectors
argument_list|)
operator|->
name|gimage
condition|)
name|gimp_vector_tool_clear_vectors
argument_list|(
name|vector_tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|vector_tool
operator|->
name|vectors
operator|&&
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
operator|&&
name|gdisp
operator|==
name|tool
operator|->
name|gdisp
condition|)
block|{
comment|/*  if the cursor is in one of the handles,        *  the new function will be moving or adding a new point or guide        */
name|anchor
operator|=
name|gimp_vectors_anchor_get
argument_list|(
name|vector_tool
operator|->
name|vectors
argument_list|,
name|coords
argument_list|,
operator|&
name|stroke
argument_list|)
expr_stmt|;
if|if
condition|(
name|anchor
operator|&&
name|gimp_draw_tool_on_handle
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gdisp
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
name|GIMP_HANDLE_CIRCLE
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|x
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|y
argument_list|,
name|TARGET
argument_list|,
name|TARGET
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|FALSE
argument_list|)
condition|)
block|{
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|vector_tool
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|anchor
operator|->
name|type
operator|==
name|GIMP_HANDLE_ANCHOR
condition|)
name|gimp_stroke_anchor_select
argument_list|(
name|stroke
argument_list|,
name|anchor
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* doublecheck if there are control handles at this anchor */
name|anchor
operator|=
name|gimp_vectors_anchor_get
argument_list|(
name|vector_tool
operator|->
name|vectors
argument_list|,
name|coords
argument_list|,
operator|&
name|stroke
argument_list|)
expr_stmt|;
name|vector_tool
operator|->
name|function
operator|=
name|VECTORS_MOVING
expr_stmt|;
name|vector_tool
operator|->
name|cur_stroke
operator|=
name|stroke
expr_stmt|;
name|vector_tool
operator|->
name|cur_anchor
operator|=
name|anchor
expr_stmt|;
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|vector_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
operator|!
name|vector_tool
operator|->
name|vectors
operator|||
name|vector_tool
operator|->
name|function
operator|==
name|VECTORS_CREATING
condition|)
block|{
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
block|{
comment|/* reset everything */
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|vector_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
operator|!
name|vector_tool
operator|->
name|vectors
condition|)
block|{
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|vectors
operator|=
name|gimp_vectors_new
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Unnamed"
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_image_add_vectors
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|vectors
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|vector_tool
operator|->
name|vectors
operator|=
name|vectors
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|vectors
argument_list|,
literal|"removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vector_tool_clear_vectors
argument_list|)
argument_list|,
name|vector_tool
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
name|stroke
operator|=
name|gimp_bezier_stroke_new
argument_list|(
name|coords
argument_list|)
expr_stmt|;
name|anchor
operator|=
name|gimp_stroke_anchor_get
argument_list|(
name|stroke
argument_list|,
name|coords
argument_list|)
expr_stmt|;
name|gimp_vectors_stroke_add
argument_list|(
name|vector_tool
operator|->
name|vectors
argument_list|,
name|stroke
argument_list|)
expr_stmt|;
name|vector_tool
operator|->
name|cur_stroke
operator|=
name|stroke
expr_stmt|;
name|vector_tool
operator|->
name|cur_anchor
operator|=
name|anchor
expr_stmt|;
name|gimp_stroke_anchor_select
argument_list|(
name|stroke
argument_list|,
name|anchor
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|vector_tool
operator|->
name|function
operator|=
name|VECTORS_MOVING
expr_stmt|;
comment|/*  set the gdisplay  */
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
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
block|{
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
comment|/*  start drawing the vector tool  */
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|vector_tool
operator|->
name|function
operator|==
name|VECTORS_ADDING
condition|)
block|{
if|if
condition|(
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
condition|)
block|{
comment|/* reset everything */
name|gimp_draw_tool_stop
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|vector_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|anchor
operator|=
name|gimp_bezier_stroke_extend
argument_list|(
name|GIMP_BEZIER_STROKE
argument_list|(
name|vector_tool
operator|->
name|cur_stroke
argument_list|)
argument_list|,
name|coords
argument_list|,
name|vector_tool
operator|->
name|cur_anchor
argument_list|,
name|EXTEND_EDITABLE
argument_list|)
expr_stmt|;
if|if
condition|(
name|anchor
condition|)
name|vector_tool
operator|->
name|cur_anchor
operator|=
name|anchor
expr_stmt|;
comment|/*  set the gdisplay  */
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
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
block|{
name|gimp_tool_pop_status
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gimp_tool_push_status
argument_list|(
name|tool
argument_list|,
literal|""
argument_list|)
expr_stmt|;
block|}
comment|/*  start drawing the vector tool  */
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vector_tool_button_release (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_vector_tool_button_release
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
name|GimpVectorTool
modifier|*
name|vector_tool
decl_stmt|;
name|GimpViewable
modifier|*
name|viewable
decl_stmt|;
name|vector_tool
operator|=
name|GIMP_VECTOR_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|vector_tool
operator|->
name|function
operator|=
name|VECTORS_ADDING
expr_stmt|;
comment|/* THIS DOES NOT BELONG HERE! */
if|if
condition|(
name|vector_tool
operator|->
name|vectors
condition|)
block|{
name|viewable
operator|=
name|GIMP_VIEWABLE
argument_list|(
name|vector_tool
operator|->
name|vectors
argument_list|)
expr_stmt|;
name|gimp_viewable_invalidate_preview
argument_list|(
name|viewable
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vector_tool_motion (GimpTool * tool,GimpCoords * coords,guint32 time,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_vector_tool_motion
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
name|GimpVectorTool
modifier|*
name|vector_tool
decl_stmt|;
name|GimpVectorOptions
modifier|*
name|options
decl_stmt|;
name|GimpAnchor
modifier|*
name|anchor
decl_stmt|;
name|vector_tool
operator|=
name|GIMP_VECTOR_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|options
operator|=
name|GIMP_VECTOR_OPTIONS
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|tool_options
argument_list|)
expr_stmt|;
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|vector_tool
argument_list|)
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|vector_tool
operator|->
name|function
condition|)
block|{
case|case
name|VECTORS_MOVING
case|:
comment|/* if we are moving the start point and only have two,        * make it the end point  */
name|anchor
operator|=
name|vector_tool
operator|->
name|cur_anchor
expr_stmt|;
if|if
condition|(
name|anchor
condition|)
name|gimp_stroke_anchor_move_absolute
argument_list|(
name|vector_tool
operator|->
name|cur_stroke
argument_list|,
name|vector_tool
operator|->
name|cur_anchor
argument_list|,
name|coords
argument_list|,
literal|0
argument_list|)
expr_stmt|;
default|default:
break|break;
block|}
name|gimp_draw_tool_resume
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|vector_tool
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_vector_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_vector_tool_cursor_update
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
name|GimpVectorTool
modifier|*
name|vector_tool
decl_stmt|;
name|gboolean
name|in_handle
init|=
name|FALSE
decl_stmt|;
name|GdkCursorType
name|ctype
init|=
name|GIMP_MOUSE_CURSOR
decl_stmt|;
name|GimpCursorModifier
name|cmodifier
init|=
name|GIMP_CURSOR_MODIFIER_NONE
decl_stmt|;
name|GimpAnchor
modifier|*
name|anchor
decl_stmt|;
name|vector_tool
operator|=
name|GIMP_VECTOR_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
if|if
condition|(
name|vector_tool
operator|->
name|vectors
operator|&&
name|gimp_tool_control_is_active
argument_list|(
name|tool
operator|->
name|control
argument_list|)
operator|&&
name|tool
operator|->
name|gdisp
operator|==
name|gdisp
condition|)
block|{
name|anchor
operator|=
name|gimp_vectors_anchor_get
argument_list|(
name|vector_tool
operator|->
name|vectors
argument_list|,
name|coords
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|anchor
operator|&&
name|gimp_draw_tool_on_handle
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|tool
argument_list|)
argument_list|,
name|gdisp
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|,
name|GIMP_HANDLE_CIRCLE
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|x
argument_list|,
name|anchor
operator|->
name|position
operator|.
name|y
argument_list|,
name|TARGET
argument_list|,
name|TARGET
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|FALSE
argument_list|)
condition|)
block|{
name|in_handle
operator|=
name|TRUE
expr_stmt|;
name|cmodifier
operator|=
name|GIMP_CURSOR_MODIFIER_MOVE
expr_stmt|;
block|}
block|}
name|gimp_tool_control_set_cursor
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|ctype
argument_list|)
expr_stmt|;
name|gimp_tool_control_set_cursor_modifier
argument_list|(
name|tool
operator|->
name|control
argument_list|,
name|cmodifier
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

begin_function
specifier|static
name|void
DECL|function|gimp_vector_tool_draw (GimpDrawTool * draw_tool)
name|gimp_vector_tool_draw
parameter_list|(
name|GimpDrawTool
modifier|*
name|draw_tool
parameter_list|)
block|{
name|GimpVectorTool
modifier|*
name|vector_tool
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpAnchor
modifier|*
name|cur_anchor
init|=
name|NULL
decl_stmt|;
name|GimpStroke
modifier|*
name|cur_stroke
init|=
name|NULL
decl_stmt|;
name|GimpVectors
modifier|*
name|vectors
decl_stmt|;
name|GArray
modifier|*
name|coords
decl_stmt|;
name|gboolean
name|closed
decl_stmt|;
name|GList
modifier|*
name|draw_anchors
decl_stmt|,
modifier|*
name|ptr
decl_stmt|;
name|vector_tool
operator|=
name|GIMP_VECTOR_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
name|vectors
operator|=
name|vector_tool
operator|->
name|vectors
expr_stmt|;
if|if
condition|(
operator|!
name|vectors
condition|)
return|return;
while|while
condition|(
operator|(
name|cur_stroke
operator|=
name|gimp_vectors_stroke_get_next
argument_list|(
name|vectors
argument_list|,
name|cur_stroke
argument_list|)
operator|)
condition|)
block|{
comment|/* anchor handles */
name|cur_anchor
operator|=
name|NULL
expr_stmt|;
name|draw_anchors
operator|=
name|gimp_stroke_get_draw_anchors
argument_list|(
name|cur_stroke
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|draw_anchors
expr_stmt|;
while|while
condition|(
name|ptr
condition|)
block|{
name|cur_anchor
operator|=
operator|(
name|GimpAnchor
operator|*
operator|)
name|ptr
operator|->
name|data
expr_stmt|;
if|if
condition|(
name|cur_anchor
operator|->
name|type
operator|==
name|GIMP_HANDLE_ANCHOR
condition|)
block|{
name|gimp_draw_tool_draw_handle
argument_list|(
name|draw_tool
argument_list|,
name|cur_anchor
operator|->
name|selected
condition|?
name|GIMP_HANDLE_CIRCLE
else|:
name|GIMP_HANDLE_FILLED_CIRCLE
argument_list|,
name|cur_anchor
operator|->
name|position
operator|.
name|x
argument_list|,
name|cur_anchor
operator|->
name|position
operator|.
name|y
argument_list|,
name|TARGET
argument_list|,
name|TARGET
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|ptr
operator|=
name|ptr
operator|->
name|next
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|draw_anchors
argument_list|)
expr_stmt|;
comment|/* control handles */
name|draw_anchors
operator|=
name|gimp_stroke_get_draw_controls
argument_list|(
name|cur_stroke
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|draw_anchors
expr_stmt|;
while|while
condition|(
name|ptr
condition|)
block|{
name|cur_anchor
operator|=
operator|(
name|GimpAnchor
operator|*
operator|)
name|ptr
operator|->
name|data
expr_stmt|;
name|gimp_draw_tool_draw_handle
argument_list|(
name|draw_tool
argument_list|,
name|GIMP_HANDLE_SQUARE
argument_list|,
name|cur_anchor
operator|->
name|position
operator|.
name|x
argument_list|,
name|cur_anchor
operator|->
name|position
operator|.
name|y
argument_list|,
name|TARGET
operator|-
literal|2
argument_list|,
name|TARGET
operator|-
literal|2
argument_list|,
name|GTK_ANCHOR_CENTER
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|ptr
operator|=
name|ptr
operator|->
name|next
expr_stmt|;
block|}
name|g_list_free
argument_list|(
name|draw_anchors
argument_list|)
expr_stmt|;
comment|/* the lines to the control handles */
name|coords
operator|=
name|gimp_stroke_get_draw_lines
argument_list|(
name|cur_stroke
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|->
name|len
operator|%
literal|2
operator|==
literal|0
condition|)
block|{
name|gint
name|i
decl_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|coords
operator|->
name|len
condition|;
name|i
operator|+=
literal|2
control|)
name|gimp_draw_tool_draw_strokes
argument_list|(
name|draw_tool
argument_list|,
operator|&
operator|(
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
name|i
argument_list|)
operator|)
argument_list|,
literal|2
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
comment|/* the stroke itself */
name|coords
operator|=
name|gimp_stroke_interpolate
argument_list|(
name|cur_stroke
argument_list|,
literal|1.0
argument_list|,
operator|&
name|closed
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|->
name|len
condition|)
name|gimp_draw_tool_draw_strokes
argument_list|(
name|draw_tool
argument_list|,
operator|&
operator|(
name|g_array_index
argument_list|(
name|coords
argument_list|,
name|GimpCoords
argument_list|,
literal|0
argument_list|)
operator|)
argument_list|,
name|coords
operator|->
name|len
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_array_free
argument_list|(
name|coords
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_vector_tool_clear_vectors (GimpVectorTool * vector_tool)
name|gimp_vector_tool_clear_vectors
parameter_list|(
name|GimpVectorTool
modifier|*
name|vector_tool
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTOR_TOOL
argument_list|(
name|vector_tool
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_vector_tool_set_vectors
argument_list|(
name|vector_tool
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_vector_tool_set_vectors (GimpVectorTool * vector_tool,GimpVectors * vectors)
name|gimp_vector_tool_set_vectors
parameter_list|(
name|GimpVectorTool
modifier|*
name|vector_tool
parameter_list|,
name|GimpVectors
modifier|*
name|vectors
parameter_list|)
block|{
name|GimpDrawTool
modifier|*
name|draw_tool
decl_stmt|;
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpItem
modifier|*
name|item
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_VECTOR_TOOL
argument_list|(
name|vector_tool
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|vectors
operator|==
name|NULL
operator|||
name|GIMP_IS_VECTORS
argument_list|(
name|vectors
argument_list|)
argument_list|)
expr_stmt|;
name|draw_tool
operator|=
name|GIMP_DRAW_TOOL
argument_list|(
name|vector_tool
argument_list|)
expr_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|vector_tool
argument_list|)
expr_stmt|;
name|item
operator|=
name|GIMP_ITEM
argument_list|(
name|vectors
argument_list|)
expr_stmt|;
if|if
condition|(
name|vectors
operator|==
name|vector_tool
operator|->
name|vectors
condition|)
return|return;
if|if
condition|(
name|draw_tool
operator|->
name|gdisp
condition|)
block|{
if|if
condition|(
name|item
operator|&&
name|draw_tool
operator|->
name|gdisp
operator|->
name|gimage
operator|==
name|item
operator|->
name|gimage
condition|)
name|gimp_draw_tool_pause
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
else|else
name|gimp_draw_tool_stop
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|vector_tool
operator|->
name|vectors
condition|)
block|{
name|g_signal_handlers_disconnect_by_func
argument_list|(
name|vector_tool
operator|->
name|vectors
argument_list|,
name|gimp_vector_tool_clear_vectors
argument_list|,
name|vector_tool
argument_list|)
expr_stmt|;
block|}
name|vector_tool
operator|->
name|vectors
operator|=
name|vectors
expr_stmt|;
name|vector_tool
operator|->
name|cur_stroke
operator|=
name|NULL
expr_stmt|;
name|vector_tool
operator|->
name|cur_anchor
operator|=
name|NULL
expr_stmt|;
name|vector_tool
operator|->
name|active_anchors
operator|=
name|NULL
expr_stmt|;
name|vector_tool
operator|->
name|function
operator|=
name|VECTORS_CREATING
expr_stmt|;
if|if
condition|(
name|vector_tool
operator|->
name|vectors
condition|)
block|{
name|g_signal_connect_object
argument_list|(
name|vectors
argument_list|,
literal|"removed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_vector_tool_clear_vectors
argument_list|)
argument_list|,
name|vector_tool
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|item
operator|&&
name|draw_tool
operator|->
name|gdisp
operator|&&
name|draw_tool
operator|->
name|gdisp
operator|->
name|gimage
operator|==
name|item
operator|->
name|gimage
condition|)
block|{
name|gimp_draw_tool_resume
argument_list|(
name|draw_tool
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|item
operator|&&
name|tool
operator|->
name|gdisp
operator|&&
name|tool
operator|->
name|gdisp
operator|->
name|gimage
operator|==
name|item
operator|->
name|gimage
condition|)
block|{
name|gimp_draw_tool_start
argument_list|(
name|draw_tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GimpDisplay
modifier|*
name|gdisp
decl_stmt|;
name|context
operator|=
name|gimp_get_current_context
argument_list|(
name|tool
operator|->
name|tool_info
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|gdisp
operator|=
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|item
operator|&&
name|gdisp
operator|->
name|gimage
operator|!=
name|item
operator|->
name|gimage
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
name|gdisp
operator|=
name|NULL
expr_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|item
operator|->
name|gimage
operator|->
name|gimp
operator|->
name|displays
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
if|if
condition|(
operator|(
operator|(
name|GimpDisplay
operator|*
operator|)
name|list
operator|->
name|data
operator|)
operator|->
name|gimage
operator|==
name|item
operator|->
name|gimage
condition|)
block|{
name|gimp_context_set_display
argument_list|(
name|context
argument_list|,
operator|(
name|GimpDisplay
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|gdisp
operator|=
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
if|if
condition|(
operator|!
name|gdisp
condition|)
return|return;
block|}
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|gimp_tool_control_activate
argument_list|(
name|tool
operator|->
name|control
argument_list|)
expr_stmt|;
name|gimp_draw_tool_start
argument_list|(
name|draw_tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

