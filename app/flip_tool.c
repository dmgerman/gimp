begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<stdlib.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"cursorutil.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"flip_tool.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimage_mask.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"path_transform.h"
end_include

begin_include
include|#
directive|include
file|"undo.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_include
include|#
directive|include
file|"tile_manager_pvt.h"
end_include

begin_comment
comment|/* ick. */
end_comment

begin_define
DECL|macro|FLIP_INFO
define|#
directive|define
name|FLIP_INFO
value|0
end_define

begin_comment
comment|/*  the flip structures  */
end_comment

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
name|ToolOptions
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

begin_comment
comment|/*  functions  */
end_comment

begin_comment
comment|/*  FIXME: Lame - 1 hacks abound since the code assumes certain values for  *  the ORIENTATION_FOO constants.  */
end_comment

begin_function
specifier|static
name|void
DECL|function|flip_options_reset (void)
name|flip_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|FlipOptions
modifier|*
name|options
init|=
name|flip_options
decl_stmt|;
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
comment|/*  the new flip tool options structure  */
name|options
operator|=
name|g_new
argument_list|(
name|FlipOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|tool_options_init
argument_list|(
operator|(
name|ToolOptions
operator|*
operator|)
name|options
argument_list|,
name|_
argument_list|(
literal|"Flip Tool"
argument_list|)
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
name|gimp_radio_button_update
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
DECL|function|flip_modifier_key_func (Tool * tool,GdkEventKey * kevent,gpointer gdisp_ptr)
name|flip_modifier_key_func
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventKey
modifier|*
name|kevent
parameter_list|,
name|gpointer
name|gdisp_ptr
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
name|TileManager
modifier|*
DECL|function|flip_tool_transform (Tool * tool,gpointer gdisp_ptr,TransformState state)
name|flip_tool_transform
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|,
name|TransformState
name|state
parameter_list|)
block|{
name|TransformCore
modifier|*
name|transform_core
decl_stmt|;
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|transform_core
operator|=
operator|(
name|TransformCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|INIT
case|:
name|transform_info
operator|=
name|NULL
expr_stmt|;
break|break;
case|case
name|MOTION
case|:
break|break;
case|case
name|RECALC
case|:
break|break;
case|case
name|FINISH
case|:
comment|/*      transform_core->trans_info[FLIP] *= -1.0;*/
return|return
name|flip_tool_flip
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gimage_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
argument_list|,
name|transform_core
operator|->
name|original
argument_list|,
operator|(
name|int
operator|)
name|transform_core
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
name|void
DECL|function|flip_cursor_update (Tool * tool,GdkEventMotion * mevent,gpointer gdisp_ptr)
name|flip_cursor_update
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|GdkEventMotion
modifier|*
name|mevent
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|)
block|{
name|GDisplay
modifier|*
name|gdisp
decl_stmt|;
name|Drawable
modifier|*
name|drawable
decl_stmt|;
name|GdkCursorType
name|ctype
init|=
name|GDK_TOP_LEFT_ARROW
decl_stmt|;
name|gdisp
operator|=
operator|(
name|GDisplay
operator|*
operator|)
name|gdisp_ptr
expr_stmt|;
if|if
condition|(
operator|(
name|drawable
operator|=
name|gimage_get_active_drawable
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
name|drawable_offsets
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
name|drawable_width
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
name|drawable_height
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
name|gdisplay_install_tool_cursor
argument_list|(
name|gdisp
argument_list|,
name|ctype
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_flip (void)
name|tools_new_flip
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|TransformCore
modifier|*
name|private
decl_stmt|;
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
name|tools_register
argument_list|(
name|FLIP
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|flip_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|=
name|transform_core_new
argument_list|(
name|FLIP
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|private
operator|=
name|tool
operator|->
name|private
expr_stmt|;
name|private
operator|->
name|trans_func
operator|=
name|flip_tool_transform
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|FLIP_INFO
index|]
operator|=
operator|-
literal|1.0
expr_stmt|;
name|tool
operator|->
name|modifier_key_func
operator|=
name|flip_modifier_key_func
expr_stmt|;
name|tool
operator|->
name|cursor_update_func
operator|=
name|flip_cursor_update
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_flip_tool (Tool * tool)
name|tools_free_flip_tool
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|transform_core_free
argument_list|(
name|tool
argument_list|)
expr_stmt|;
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
name|orig
operator|->
name|width
argument_list|,
name|orig
operator|->
name|height
argument_list|,
name|orig
operator|->
name|bpp
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
name|orig
operator|->
name|width
argument_list|,
name|orig
operator|->
name|height
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
name|orig
operator|->
name|width
argument_list|,
name|orig
operator|->
name|height
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
name|new
operator|->
name|x
operator|=
name|orig
operator|->
name|x
expr_stmt|;
name|new
operator|->
name|y
operator|=
name|orig
operator|->
name|y
expr_stmt|;
block|}
else|else
block|{
name|new
operator|=
name|tile_manager_new
argument_list|(
name|orig
operator|->
name|width
argument_list|,
name|orig
operator|->
name|height
argument_list|,
name|orig
operator|->
name|bpp
argument_list|)
expr_stmt|;
name|new
operator|->
name|x
operator|=
name|orig
operator|->
name|x
expr_stmt|;
name|new
operator|->
name|y
operator|=
name|orig
operator|->
name|y
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
name|orig
operator|->
name|width
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
name|orig
operator|->
name|height
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
name|orig
operator|->
name|width
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
name|orig
operator|->
name|height
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
name|orig
operator|->
name|height
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
name|orig
operator|->
name|width
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
name|orig
operator|->
name|height
operator|-
name|i
operator|-
literal|1
operator|)
argument_list|,
name|orig
operator|->
name|width
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

end_unit

