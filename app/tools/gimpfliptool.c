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
file|"base/pixel-region.h"
end_include

begin_include
include|#
directive|include
file|"base/tile-manager.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
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
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay-ops.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"path_transform.h"
end_include

begin_include
include|#
directive|include
file|"gimpfliptool.h"
end_include

begin_include
include|#
directive|include
file|"tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  FIXME: Lame - 1 hacks abound since the code assumes certain values for  *  the ORIENTATION_FOO constants.  */
end_comment

begin_define
DECL|macro|FLIP_INFO
define|#
directive|define
name|FLIP_INFO
value|0
end_define

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
name|gimp_flip_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
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
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
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
name|GDisplay
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
name|FlipOptions
modifier|*
name|flip_options_new
parameter_list|(
name|void
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
DECL|variable|flip_options
specifier|static
name|FlipOptions
modifier|*
name|flip_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

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
DECL|function|gimp_flip_tool_register (Gimp * gimp)
name|gimp_flip_tool_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|tool_manager_register_tool
argument_list|(
name|gimp
argument_list|,
name|GIMP_TYPE_FLIP_TOOL
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

begin_function
name|TileManager
modifier|*
DECL|function|flip_tool_flip (GimpImage * gimage,GimpDrawable * drawable,TileManager * orig,gint flip,InternalOrientationType type)
name|flip_tool_flip
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|TileManager
modifier|*
name|orig
parameter_list|,
name|gint
name|flip
parameter_list|,
name|InternalOrientationType
name|type
parameter_list|)
block|{
name|TileManager
modifier|*
name|new
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|;
name|gint
name|orig_width
decl_stmt|;
name|gint
name|orig_height
decl_stmt|;
name|gint
name|orig_bpp
decl_stmt|;
name|gint
name|orig_x
decl_stmt|,
name|orig_y
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
name|orig
condition|)
return|return
name|NULL
return|;
name|orig_width
operator|=
name|tile_manager_width
argument_list|(
name|orig
argument_list|)
expr_stmt|;
name|orig_height
operator|=
name|tile_manager_height
argument_list|(
name|orig
argument_list|)
expr_stmt|;
name|orig_bpp
operator|=
name|tile_manager_bpp
argument_list|(
name|orig
argument_list|)
expr_stmt|;
name|tile_manager_get_offsets
argument_list|(
name|orig
argument_list|,
operator|&
name|orig_x
argument_list|,
operator|&
name|orig_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|flip
operator|>
literal|0
condition|)
block|{
name|new
operator|=
name|tile_manager_new
argument_list|(
name|orig_width
argument_list|,
name|orig_height
argument_list|,
name|orig_bpp
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|orig
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|orig_width
argument_list|,
name|orig_height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|orig_width
argument_list|,
name|orig_height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|tile_manager_set_offsets
argument_list|(
name|new
argument_list|,
name|orig_x
argument_list|,
name|orig_y
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|new
operator|=
name|tile_manager_new
argument_list|(
name|orig_width
argument_list|,
name|orig_height
argument_list|,
name|orig_bpp
argument_list|)
expr_stmt|;
name|tile_manager_set_offsets
argument_list|(
name|new
argument_list|,
name|orig_x
argument_list|,
name|orig_y
argument_list|)
expr_stmt|;
if|if
condition|(
name|type
operator|==
name|ORIENTATION_HORIZONTAL
condition|)
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|orig_width
condition|;
name|i
operator|++
control|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|orig
argument_list|,
name|i
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|orig_height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new
argument_list|,
operator|(
name|orig_width
operator|-
name|i
operator|-
literal|1
operator|)
argument_list|,
literal|0
argument_list|,
literal|1
argument_list|,
name|orig_height
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
block|}
else|else
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|orig_height
condition|;
name|i
operator|++
control|)
block|{
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|orig
argument_list|,
literal|0
argument_list|,
name|i
argument_list|,
name|orig_width
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|destPR
argument_list|,
name|new
argument_list|,
literal|0
argument_list|,
operator|(
name|orig_height
operator|-
name|i
operator|-
literal|1
operator|)
argument_list|,
name|orig_width
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
block|}
comment|/* flip locked paths */
comment|/* Note that the undo structures etc are setup before we enter this        * function.        */
if|if
condition|(
name|type
operator|==
name|ORIENTATION_HORIZONTAL
condition|)
name|path_transform_flip_horz
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
else|else
name|path_transform_flip_vert
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
return|return
name|new
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
name|GimpDrawToolClass
modifier|*
name|draw_class
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
name|draw_class
operator|=
name|GIMP_DRAW_TOOL_CLASS
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
name|cursor_update
operator|=
name|gimp_flip_tool_cursor_update
expr_stmt|;
name|tool_class
operator|->
name|modifier_key
operator|=
name|gimp_flip_tool_modifier_key
expr_stmt|;
name|draw_class
operator|->
name|draw
operator|=
name|NULL
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
name|tr_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|flip_tool
argument_list|)
expr_stmt|;
name|tr_tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|flip_tool
argument_list|)
expr_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|flip_options
condition|)
block|{
name|flip_options
operator|=
name|flip_options_new
argument_list|()
expr_stmt|;
name|tool_manager_register_tool_options
argument_list|(
name|GIMP_TYPE_FLIP_TOOL
argument_list|,
operator|(
name|GimpToolOptions
operator|*
operator|)
name|flip_options
argument_list|)
expr_stmt|;
block|}
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
name|tr_tool
operator|->
name|trans_info
index|[
name|FLIP_INFO
index|]
operator|=
operator|-
literal|1.0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_flip_tool_cursor_update (GimpTool * tool,GdkEventMotion * mevent,GDisplay * gdisp)
name|gimp_flip_tool_cursor_update
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
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
name|x
decl_stmt|,
name|y
decl_stmt|;
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
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
operator|(
name|double
operator|)
name|mevent
operator|->
name|x
argument_list|,
operator|(
name|double
operator|)
name|mevent
operator|->
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|>=
name|off_x
operator|&&
name|y
operator|>=
name|off_y
operator|&&
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
name|x
argument_list|,
name|y
argument_list|)
condition|)
block|{
if|if
condition|(
name|flip_options
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
name|flip_options
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
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
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
name|void
DECL|function|gimp_flip_tool_modifier_key (GimpTool * tool,GdkEventKey * kevent,GDisplay * gdisp)
name|gimp_flip_tool_modifier_key
parameter_list|(
name|GimpTool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
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
name|GDK_Alt_L
case|:
case|case
name|GDK_Alt_R
case|:
break|break;
case|case
name|GDK_Shift_L
case|:
case|case
name|GDK_Shift_R
case|:
break|break;
case|case
name|GDK_Control_L
case|:
case|case
name|GDK_Control_R
case|:
if|if
condition|(
name|flip_options
operator|->
name|type
operator|==
name|ORIENTATION_HORIZONTAL
condition|)
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|flip_options
operator|->
name|type_w
index|[
name|ORIENTATION_VERTICAL
operator|-
literal|1
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|flip_options
operator|->
name|type_w
index|[
name|ORIENTATION_HORIZONTAL
operator|-
literal|1
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|gimp_flip_tool_transform (GimpTransformTool * trans_tool,GDisplay * gdisp,TransformState state)
name|gimp_flip_tool_transform
parameter_list|(
name|GimpTransformTool
modifier|*
name|trans_tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|,
name|TransformState
name|state
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
name|trans_tool
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|TRANSFORM_INIT
case|:
name|transform_info
operator|=
name|NULL
expr_stmt|;
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
name|flip_tool_flip
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
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
operator|(
name|gint
operator|)
name|trans_tool
operator|->
name|trans_info
index|[
name|FLIP_INFO
index|]
argument_list|,
name|flip_options
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

begin_function
specifier|static
name|FlipOptions
modifier|*
DECL|function|flip_options_new (void)
name|flip_options_new
parameter_list|(
name|void
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
name|flip_options_reset
argument_list|)
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
operator|(
name|gpointer
operator|)
name|options
operator|->
name|type
argument_list|,
name|_
argument_list|(
literal|"Horizontal"
argument_list|)
argument_list|,
operator|(
name|gpointer
operator|)
name|ORIENTATION_HORIZONTAL
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
operator|(
name|gpointer
operator|)
name|ORIENTATION_VERTICAL
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
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|options
operator|->
name|type_w
index|[
name|options
operator|->
name|type_d
operator|-
literal|1
index|]
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

