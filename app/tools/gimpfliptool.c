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
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"transform_core.h"
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
DECL|macro|FLIP
define|#
directive|define
name|FLIP
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
DECL|member|type
name|ToolType
name|type
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|Tool
modifier|*
name|tools_new_flip_horz
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Tool
modifier|*
name|tools_new_flip_vert
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TileManager
modifier|*
name|flip_tool_flip_horz
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|TileManager
modifier|*
name|flip_tool_flip_vert
parameter_list|(
name|GImage
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|TileManager
modifier|*
parameter_list|,
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|flip_change_type
parameter_list|(
name|int
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|Argument
modifier|*
name|flip_invoker
parameter_list|(
name|Argument
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  Static variables  */
end_comment

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

begin_function
specifier|static
name|void
DECL|function|flip_type_callback (GtkWidget * w,gpointer client_data)
name|flip_type_callback
parameter_list|(
name|GtkWidget
modifier|*
name|w
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|flip_change_type
argument_list|(
operator|(
name|long
operator|)
name|client_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|FlipOptions
modifier|*
DECL|function|create_flip_options (void)
name|create_flip_options
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
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_box
decl_stmt|;
name|GtkWidget
modifier|*
name|radio_button
decl_stmt|;
name|GSList
modifier|*
name|group
init|=
name|NULL
decl_stmt|;
name|int
name|i
decl_stmt|;
name|char
modifier|*
name|button_names
index|[
literal|2
index|]
init|=
block|{
name|N_
argument_list|(
literal|"Horizontal"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Vertical"
argument_list|)
block|,   }
decl_stmt|;
comment|/*  the new options structure  */
name|options
operator|=
operator|(
name|FlipOptions
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|FlipOptions
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|type
operator|=
name|FLIP_HORZ
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
literal|1
argument_list|)
expr_stmt|;
comment|/*  the main label  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Flip Tool Options"
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
name|label
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
name|label
argument_list|)
expr_stmt|;
name|radio_box
operator|=
name|gtk_vbox_new
argument_list|(
name|FALSE
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
name|radio_box
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
comment|/*  the radio buttons  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
literal|2
condition|;
name|i
operator|++
control|)
block|{
name|radio_button
operator|=
name|gtk_radio_button_new_with_label
argument_list|(
name|group
argument_list|,
name|gettext
argument_list|(
name|button_names
index|[
name|i
index|]
argument_list|)
argument_list|)
expr_stmt|;
name|group
operator|=
name|gtk_radio_button_group
argument_list|(
name|GTK_RADIO_BUTTON
argument_list|(
name|radio_button
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|radio_box
argument_list|)
argument_list|,
name|radio_button
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|radio_button
argument_list|)
argument_list|,
literal|"toggled"
argument_list|,
operator|(
name|GtkSignalFunc
operator|)
name|flip_type_callback
argument_list|,
call|(
name|gpointer
call|)
argument_list|(
call|(
name|long
call|)
argument_list|(
name|FLIP_HORZ
operator|+
name|i
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|radio_button
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_show
argument_list|(
name|radio_box
argument_list|)
expr_stmt|;
comment|/*  Register this selection options widget with the main tools options dialog  */
name|tools_register_options
argument_list|(
name|FLIP_HORZ
argument_list|,
name|vbox
argument_list|)
expr_stmt|;
name|tools_register_options
argument_list|(
name|FLIP_VERT
argument_list|,
name|vbox
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
modifier|*
DECL|function|flip_tool_transform_horz (Tool * tool,gpointer gdisp_ptr,int state)
name|flip_tool_transform_horz
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|,
name|int
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
name|transform_core
operator|->
name|trans_info
index|[
name|FLIP
index|]
operator|*=
operator|-
literal|1.0
expr_stmt|;
return|return
name|flip_tool_flip_horz
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
name|transform_core
operator|->
name|trans_info
index|[
name|FLIP
index|]
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
modifier|*
DECL|function|flip_tool_transform_vert (Tool * tool,gpointer gdisp_ptr,int state)
name|flip_tool_transform_vert
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|,
name|gpointer
name|gdisp_ptr
parameter_list|,
name|int
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
name|transform_core
operator|->
name|trans_info
index|[
name|FLIP
index|]
operator|*=
operator|-
literal|1.0
expr_stmt|;
return|return
name|flip_tool_flip_vert
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
name|transform_core
operator|->
name|trans_info
index|[
name|FLIP
index|]
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
name|Tool
modifier|*
DECL|function|tools_new_flip ()
name|tools_new_flip
parameter_list|()
block|{
if|if
condition|(
operator|!
name|flip_options
condition|)
name|flip_options
operator|=
name|create_flip_options
argument_list|()
expr_stmt|;
switch|switch
condition|(
name|flip_options
operator|->
name|type
condition|)
block|{
case|case
name|FLIP_HORZ
case|:
return|return
name|tools_new_flip_horz
argument_list|()
return|;
break|break;
case|case
name|FLIP_VERT
case|:
return|return
name|tools_new_flip_vert
argument_list|()
return|;
break|break;
default|default:
return|return
name|NULL
return|;
break|break;
block|}
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
specifier|static
name|Tool
modifier|*
DECL|function|tools_new_flip_horz ()
name|tools_new_flip_horz
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|TransformCore
modifier|*
name|private
decl_stmt|;
name|tool
operator|=
name|transform_core_new
argument_list|(
name|FLIP_HORZ
argument_list|,
name|NON_INTERACTIVE
argument_list|)
expr_stmt|;
name|private
operator|=
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  set the rotation specific transformation attributes  */
name|private
operator|->
name|trans_func
operator|=
name|flip_tool_transform_horz
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|FLIP
index|]
operator|=
literal|1.0
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
specifier|static
name|Tool
modifier|*
DECL|function|tools_new_flip_vert ()
name|tools_new_flip_vert
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|TransformCore
modifier|*
name|private
decl_stmt|;
name|tool
operator|=
name|transform_core_new
argument_list|(
name|FLIP_VERT
argument_list|,
name|NON_INTERACTIVE
argument_list|)
expr_stmt|;
name|private
operator|=
name|tool
operator|->
name|private
expr_stmt|;
comment|/*  set the rotation specific transformation attributes  */
name|private
operator|->
name|trans_func
operator|=
name|flip_tool_transform_vert
expr_stmt|;
name|private
operator|->
name|trans_info
index|[
name|FLIP
index|]
operator|=
literal|1.0
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|flip_tool_flip_horz (GImage * gimage,GimpDrawable * drawable,TileManager * orig,int flip)
name|flip_tool_flip_horz
parameter_list|(
name|GImage
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
name|int
name|flip
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
name|int
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
block|}
return|return
name|new
return|;
block|}
end_function

begin_function
specifier|static
name|TileManager
modifier|*
DECL|function|flip_tool_flip_vert (GImage * gimage,GimpDrawable * drawable,TileManager * orig,int flip)
name|flip_tool_flip_vert
parameter_list|(
name|GImage
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
name|int
name|flip
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
name|int
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
block|}
return|return
name|new
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|flip_change_type (int new_type)
name|flip_change_type
parameter_list|(
name|int
name|new_type
parameter_list|)
block|{
if|if
condition|(
name|flip_options
operator|->
name|type
operator|!=
name|new_type
condition|)
block|{
comment|/*  change the type, free the old tool, create the new tool  */
name|flip_options
operator|->
name|type
operator|=
name|new_type
expr_stmt|;
name|tools_select
argument_list|(
name|flip_options
operator|->
name|type
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  The flip procedure definition  */
end_comment

begin_decl_stmt
DECL|variable|flip_args
name|ProcArg
name|flip_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
name|N_
argument_list|(
literal|"the affected drawable"
argument_list|)
block|}
block|,
block|{
name|PDB_INT32
block|,
literal|"flip_type"
block|,
name|N_
argument_list|(
literal|"Type of flip: { HORIZONTAL (0), VERTICAL (1) }"
argument_list|)
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|flip_out_args
name|ProcArg
name|flip_out_args
index|[]
init|=
block|{
block|{
name|PDB_DRAWABLE
block|,
literal|"drawable"
block|,
name|N_
argument_list|(
literal|"the flipped drawable"
argument_list|)
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|flip_proc
name|ProcRecord
name|flip_proc
init|=
block|{
literal|"gimp_flip"
block|,
name|N_
argument_list|(
literal|"Flip the specified drawable about its center either vertically or horizontally"
argument_list|)
block|,
name|N_
argument_list|(
literal|"This tool flips the specified drawable if no selection exists.  If a selection exists, the portion of the drawable which lies under the selection is cut from the drawable and made into a floating selection which is then flipd by the specified amount.  The return value is the ID of the flipped drawable.  If there was no selection, this will be equal to the drawable ID supplied as input.  Otherwise, this will be the newly created and flipd drawable.  The flip type parameter indicates whether the flip will be applied horizontally or vertically."
argument_list|)
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"Spencer Kimball& Peter Mattis"
block|,
literal|"1995-1996"
block|,
name|PDB_INTERNAL
block|,
comment|/*  Input arguments  */
literal|2
block|,
name|flip_args
block|,
comment|/*  Output arguments  */
literal|1
block|,
name|flip_out_args
block|,
comment|/*  Exec method  */
block|{
block|{
name|flip_invoker
block|}
block|}
block|, }
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|flip_invoker (Argument * args)
name|flip_invoker
parameter_list|(
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|int
name|success
init|=
name|TRUE
decl_stmt|;
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|int
name|flip_type
decl_stmt|;
name|int
name|int_value
decl_stmt|;
name|TileManager
modifier|*
name|float_tiles
decl_stmt|;
name|TileManager
modifier|*
name|new_tiles
decl_stmt|;
name|int
name|new_layer
decl_stmt|;
name|Layer
modifier|*
name|layer
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|drawable
operator|=
name|NULL
expr_stmt|;
name|flip_type
operator|=
literal|0
expr_stmt|;
name|new_tiles
operator|=
name|NULL
expr_stmt|;
name|layer
operator|=
name|NULL
expr_stmt|;
comment|/*  the drawable  */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
name|drawable
operator|=
name|drawable_get_ID
argument_list|(
name|int_value
argument_list|)
expr_stmt|;
if|if
condition|(
name|drawable
operator|==
name|NULL
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
else|else
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
block|}
comment|/*  flip type */
if|if
condition|(
name|success
condition|)
block|{
name|int_value
operator|=
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
expr_stmt|;
switch|switch
condition|(
name|int_value
condition|)
block|{
case|case
literal|0
case|:
name|flip_type
operator|=
literal|0
expr_stmt|;
break|break;
case|case
literal|1
case|:
name|flip_type
operator|=
literal|1
expr_stmt|;
break|break;
default|default:
name|success
operator|=
name|FALSE
expr_stmt|;
block|}
block|}
comment|/*  call the flip procedure  */
if|if
condition|(
name|success
condition|)
block|{
comment|/*  Start a transform undo group  */
name|undo_push_group_start
argument_list|(
name|gimage
argument_list|,
name|TRANSFORM_CORE_UNDO
argument_list|)
expr_stmt|;
comment|/*  Cut/Copy from the specified drawable  */
name|float_tiles
operator|=
name|transform_core_cut
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
operator|&
name|new_layer
argument_list|)
expr_stmt|;
comment|/*  flip the buffer  */
switch|switch
condition|(
name|flip_type
condition|)
block|{
case|case
literal|0
case|:
comment|/* horz */
name|new_tiles
operator|=
name|flip_tool_flip_horz
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|float_tiles
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
break|break;
case|case
literal|1
case|:
comment|/* vert */
name|new_tiles
operator|=
name|flip_tool_flip_vert
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|float_tiles
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
break|break;
block|}
comment|/*  free the cut/copied buffer  */
name|tile_manager_destroy
argument_list|(
name|float_tiles
argument_list|)
expr_stmt|;
if|if
condition|(
name|new_tiles
condition|)
name|success
operator|=
operator|(
name|layer
operator|=
name|transform_core_paste
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|new_tiles
argument_list|,
name|new_layer
argument_list|)
operator|)
operator|!=
name|NULL
expr_stmt|;
else|else
name|success
operator|=
name|FALSE
expr_stmt|;
comment|/*  push the undo group end  */
name|undo_push_group_end
argument_list|(
name|gimage
argument_list|)
expr_stmt|;
block|}
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|flip_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|drawable_ID
argument_list|(
name|GIMP_DRAWABLE
argument_list|(
name|layer
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|return_args
return|;
block|}
end_function

end_unit

