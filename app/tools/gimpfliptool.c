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
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable-transform.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-mask.h"
end_include

begin_include
include|#
directive|include
file|"core/gimptoolinfo.h"
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
file|"gimpfliptool.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"path_transform.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_typedef
DECL|typedef|FlipOptions
typedef|typedef
name|struct
name|_FlipOptions
name|FlipOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_FlipOptions
struct|struct
name|_FlipOptions
block|{
DECL|member|tool_options
name|GimpToolOptions
name|tool_options
decl_stmt|;
DECL|member|type
name|InternalOrientationType
name|type
decl_stmt|;
DECL|member|type_d
name|InternalOrientationType
name|type_d
decl_stmt|;
DECL|member|type_w
name|GtkWidget
modifier|*
name|type_w
index|[
literal|2
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_flip_tool_class_init
parameter_list|(
name|GimpFlipToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_flip_tool_init
parameter_list|(
name|GimpFlipTool
modifier|*
name|flip_tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_flip_tool_modifier_key
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
name|gimp_flip_tool_cursor_update
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
name|TileManager
modifier|*
name|gimp_flip_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpToolOptions
modifier|*
name|flip_options_new
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
name|flip_options_reset
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
name|GimpTransformToolClass
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
DECL|function|gimp_flip_tool_register (Gimp * gimp,GimpToolRegisterCallback callback)
name|gimp_flip_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpToolRegisterCallback
name|callback
parameter_list|)
block|{
call|(
modifier|*
name|callback
call|)
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_FLIP_TOOL
argument_list|,
name|flip_options_new
argument_list|,
name|FALSE
argument_list|,
literal|"gimp:flip_tool"
argument_list|,
name|_
argument_list|(
literal|"Flip Tool"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Flip the layer or selection"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Transform Tools/Flip"
argument_list|)
argument_list|,
literal|"<shift>F"
argument_list|,
name|NULL
argument_list|,
literal|"tools/flip.html"
argument_list|,
name|GIMP_STOCK_TOOL_FLIP
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GType
DECL|function|gimp_flip_tool_get_type (void)
name|gimp_flip_tool_get_type
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
name|GimpFlipToolClass
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
name|gimp_flip_tool_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpFlipTool
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_flip_tool_init
block|,       }
decl_stmt|;
name|tool_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_TRANSFORM_TOOL
argument_list|,
literal|"GimpFlipTool"
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

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_class_init (GimpFlipToolClass * klass)
name|gimp_flip_tool_class_init
parameter_list|(
name|GimpFlipToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|GimpTransformToolClass
modifier|*
name|trans_class
decl_stmt|;
name|tool_class
operator|=
name|GIMP_TOOL_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|trans_class
operator|=
name|GIMP_TRANSFORM_TOOL_CLASS
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
name|gimp_flip_tool_modifier_key
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_flip_tool_cursor_update
expr_stmt|;
name|trans_class
operator|->
name|transform
operator|=
name|gimp_flip_tool_transform
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_init (GimpFlipTool * flip_tool)
name|gimp_flip_tool_init
parameter_list|(
name|GimpFlipTool
modifier|*
name|flip_tool
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpTransformTool
modifier|*
name|transform_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|flip_tool
argument_list|)
expr_stmt|;
name|transform_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|flip_tool
argument_list|)
expr_stmt|;
name|tool
operator|->
name|tool_cursor
operator|=
name|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
expr_stmt|;
name|tool
operator|->
name|toggle_cursor
operator|=
name|GIMP_FLIP_VERTICAL_TOOL_CURSOR
expr_stmt|;
name|tool
operator|->
name|auto_snap_to
operator|=
name|FALSE
expr_stmt|;
comment|/*  Don't snap to guides  */
name|transform_tool
operator|->
name|use_grid
operator|=
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_modifier_key (GimpTool * tool,GdkModifierType key,gboolean press,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_flip_tool_modifier_key
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
name|FlipOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|FlipOptions
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
condition|)
block|{
switch|switch
condition|(
name|options
operator|->
name|type
condition|)
block|{
case|case
name|ORIENTATION_HORIZONTAL
case|:
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|ORIENTATION_VERTICAL
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|ORIENTATION_VERTICAL
case|:
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
literal|0
index|]
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|ORIENTATION_HORIZONTAL
argument_list|)
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_cursor_update (GimpTool * tool,GimpCoords * coords,GdkModifierType state,GimpDisplay * gdisp)
name|gimp_flip_tool_cursor_update
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
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|GdkCursorType
name|ctype
init|=
name|GIMP_BAD_CURSOR
decl_stmt|;
name|GimpToolCursorType
name|tool_cursor
init|=
name|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
decl_stmt|;
name|FlipOptions
modifier|*
name|options
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|gdisp
operator|->
name|shell
argument_list|)
expr_stmt|;
name|options
operator|=
operator|(
name|FlipOptions
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
operator|(
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|)
condition|)
block|{
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|gimp_drawable_offsets
argument_list|(
name|drawable
argument_list|,
operator|&
name|off_x
argument_list|,
operator|&
name|off_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|coords
operator|->
name|x
operator|>=
name|off_x
operator|&&
name|coords
operator|->
name|y
operator|>=
name|off_y
operator|&&
name|coords
operator|->
name|x
operator|<
operator|(
name|off_x
operator|+
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|)
operator|&&
name|coords
operator|->
name|y
operator|<
operator|(
name|off_y
operator|+
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
block|{
comment|/*  Is there a selected region? If so, is cursor inside? */
if|if
condition|(
name|gimage_mask_is_empty
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
operator|||
name|gimage_mask_value
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|coords
operator|->
name|x
argument_list|,
name|coords
operator|->
name|y
argument_list|)
condition|)
block|{
if|if
condition|(
name|options
operator|->
name|type
operator|==
name|ORIENTATION_HORIZONTAL
condition|)
name|ctype
operator|=
name|GDK_SB_H_DOUBLE_ARROW
expr_stmt|;
else|else
name|ctype
operator|=
name|GDK_SB_V_DOUBLE_ARROW
expr_stmt|;
block|}
block|}
block|}
if|if
condition|(
name|options
operator|->
name|type
operator|==
name|ORIENTATION_HORIZONTAL
condition|)
name|tool_cursor
operator|=
name|GIMP_FLIP_HORIZONTAL_TOOL_CURSOR
expr_stmt|;
else|else
name|tool_cursor
operator|=
name|GIMP_FLIP_VERTICAL_TOOL_CURSOR
expr_stmt|;
name|gimp_display_shell_install_tool_cursor
argument_list|(
name|shell
argument_list|,
name|ctype
argument_list|,
name|tool_cursor
argument_list|,
name|GIMP_CURSOR_MODIFIER_NONE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|gimp_flip_tool_transform (GimpTransformTool * trans_tool,GimpDisplay * gdisp,TransformState state)
name|gimp_flip_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|trans_tool
parameter_list|,
name|GimpDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
parameter_list|)
block|{
name|FlipOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|FlipOptions
operator|*
operator|)
name|GIMP_TOOL
argument_list|(
name|trans_tool
argument_list|)
operator|->
name|tool_info
operator|->
name|tool_options
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|TRANSFORM_INIT
case|:
break|break;
case|case
name|TRANSFORM_MOTION
case|:
break|break;
case|case
name|TRANSFORM_RECALC
case|:
break|break;
case|case
name|TRANSFORM_FINISH
case|:
return|return
name|gimp_drawable_transform_tiles_flip
argument_list|(
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|trans_tool
operator|->
name|original
argument_list|,
name|options
operator|->
name|type
argument_list|)
return|;
break|break;
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_comment
comment|/*  tool options stuff  */
end_comment

begin_function
specifier|static
name|GimpToolOptions
modifier|*
DECL|function|flip_options_new (GimpToolInfo * tool_info)
name|flip_options_new
parameter_list|(
name|GimpToolInfo
modifier|*
name|tool_info
parameter_list|)
block|{
name|FlipOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|FlipOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|tool_options_init
argument_list|(
operator|(
name|GimpToolOptions
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
name|flip_options_reset
expr_stmt|;
name|options
operator|->
name|type
operator|=
name|options
operator|->
name|type_d
operator|=
name|ORIENTATION_HORIZONTAL
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
name|options
operator|->
name|tool_options
operator|.
name|main_vbox
expr_stmt|;
comment|/*  tool toggle  */
name|frame
operator|=
name|gimp_radio_group_new2
argument_list|(
name|TRUE
argument_list|,
name|_
argument_list|(
literal|"Tool Toggle"
argument_list|)
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
name|GINT_TO_POINTER
argument_list|(
name|options
operator|->
name|type
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Horizontal"
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|ORIENTATION_HORIZONTAL
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|type_w
index|[
literal|0
index|]
argument_list|,
name|_
argument_list|(
literal|"Vertical"
argument_list|)
argument_list|,
name|GINT_TO_POINTER
argument_list|(
name|ORIENTATION_VERTICAL
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|type_w
index|[
literal|1
index|]
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
DECL|function|flip_options_reset (GimpToolOptions * tool_options)
name|flip_options_reset
parameter_list|(
name|GimpToolOptions
modifier|*
name|tool_options
parameter_list|)
block|{
name|FlipOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|FlipOptions
operator|*
operator|)
name|tool_options
expr_stmt|;
name|gimp_radio_group_set_active
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
literal|0
index|]
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
block|}
end_function

end_unit

