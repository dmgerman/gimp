begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_decl_stmt
name|k
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2001 Spencer Kimball, Peter Mattis, and others  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
include|#
directive|include
file|"config.h"
include|#
directive|include
file|<stdlib.h>
include|#
directive|include
file|<gtk/gtk.h>
include|#
directive|include
file|"libgimpmath/gimpmath.h"
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
include|#
directive|include
file|"apptypes.h"
include|#
directive|include
file|"cursorutil.h"
include|#
directive|include
file|"drawable.h"
include|#
directive|include
file|"floating_sel.h"
include|#
directive|include
file|"gdisplay.h"
include|#
directive|include
file|"gimage_mask.h"
include|#
directive|include
file|"gimpchannel.h"
include|#
directive|include
file|"gimpimage.h"
include|#
directive|include
file|"gimplayer.h"
include|#
directive|include
file|"gimprc.h"
include|#
directive|include
file|"gimpui.h"
include|#
directive|include
file|"info_dialog.h"
include|#
directive|include
file|"path_transform.h"
include|#
directive|include
file|"paint_funcs.h"
include|#
directive|include
file|"pixel_region.h"
include|#
directive|include
file|"undo.h"
include|#
directive|include
file|"tile_manager.h"
include|#
directive|include
file|"tile.h"
include|#
directive|include
file|"tools/tool.h"
include|#
directive|include
file|"tools/gimpdrawtool.h"
include|#
directive|include
file|"tools/gimptransformtool.h"
comment|/*#include "transform_tool.h"*/
include|#
directive|include
file|"libgimp/gimpintl.h"
name|enum
DECL|enum|__anon2b71e2a30103
DECL|enum|__anon2b71e2a30203
type|{
DECL|enumerator|TRANSFORM
DECL|enumerator|TRANSFORM
name|TRANSFORM
decl_stmt|,
DECL|enumerator|LAST_SIGNAL
DECL|enumerator|LAST_SIGNAL
name|LAST_SIGNAL
end_decl_stmt

begin_comment
unit|}
comment|/* This should be migrated to pixel_region or similar... */
end_comment

begin_comment
comment|/* PixelSurround describes a (read-only)  *  region around a pixel in a tile manager  */
end_comment

begin_struct
unit|typedef
struct|struct
name|_PixelSurround
block|{
DECL|variable|tile
DECL|variable|tile
name|Tile
modifier|*
name|tile
decl_stmt|;
DECL|variable|mgr
DECL|variable|mgr
name|TileManager
modifier|*
name|mgr
decl_stmt|;
DECL|variable|buff
DECL|variable|buff
name|guchar
modifier|*
name|buff
decl_stmt|;
DECL|variable|buff_size
DECL|variable|buff_size
name|gint
name|buff_size
decl_stmt|;
DECL|variable|bpp
DECL|variable|bpp
name|gint
name|bpp
decl_stmt|;
DECL|variable|w
DECL|variable|w
name|gint
name|w
decl_stmt|;
DECL|variable|h
DECL|variable|h
name|gint
name|h
decl_stmt|;
DECL|variable|bg
DECL|variable|bg
name|guchar
name|bg
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
DECL|variable|row_stride
DECL|variable|row_stride
name|gint
name|row_stride
decl_stmt|;
block|}
name|PixelSurround
struct|;
end_struct

begin_define
DECL|macro|BILINEAR (jk,j1k,jk1,j1k1,dx,dy)
DECL|macro|BILINEAR (jk,j1k,jk1,j1k1,dx,dy)
define|#
directive|define
name|BILINEAR
parameter_list|(
name|jk
parameter_list|,
name|j1k
parameter_list|,
name|jk1
parameter_list|,
name|j1k1
parameter_list|,
name|dx
parameter_list|,
name|dy
parameter_list|)
define|\
value|((1-dy) * (jk + dx * (j1k - jk)) + \ 		    dy  * (jk1 + dx * (j1k1 - jk1)))
end_define

begin_comment
comment|/* access interleaved pixels */
end_comment

begin_define
DECL|macro|CUBIC_ROW (dx,row,step)
DECL|macro|CUBIC_ROW (dx,row,step)
define|#
directive|define
name|CUBIC_ROW
parameter_list|(
name|dx
parameter_list|,
name|row
parameter_list|,
name|step
parameter_list|)
define|\
value|cubic(dx, (row)[0], (row)[step], (row)[step+step], (row)[step+step+step])
end_define

begin_define
DECL|macro|CUBIC_SCALED_ROW (dx,row,step,i)
DECL|macro|CUBIC_SCALED_ROW (dx,row,step,i)
define|#
directive|define
name|CUBIC_SCALED_ROW
parameter_list|(
name|dx
parameter_list|,
name|row
parameter_list|,
name|step
parameter_list|,
name|i
parameter_list|)
define|\
value|cubic(dx, (row)[0] * (row)[i], \             (row)[step] * (row)[step + i], \             (row)[step+step]* (row)[step+step + i], \             (row)[step+step+step] * (row)[step+step+step + i])
end_define

begin_define
DECL|macro|REF_TILE (i,x,y)
DECL|macro|REF_TILE (i,x,y)
define|#
directive|define
name|REF_TILE
parameter_list|(
name|i
parameter_list|,
name|x
parameter_list|,
name|y
parameter_list|)
define|\
value|tile[i] = tile_manager_get_tile (float_tiles, x, y, TRUE, FALSE); \      src[i] = tile_data_pointer (tile[i], (x) % TILE_WIDTH, (y) % TILE_HEIGHT);
end_define

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_transform_tool_bounds
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
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
name|gimp_transform_tool_recalc
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
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
name|gimp_transform_tool_doit
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gdouble
name|gimp_transform_tool_cubic
parameter_list|(
name|gdouble
name|dx
parameter_list|,
name|gint
name|jm1
parameter_list|,
name|gint
name|j
parameter_list|,
name|gint
name|jp1
parameter_list|,
name|gint
name|jp2
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_tool_setup_grid
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_transform_tool_grid_recalc
parameter_list|(
name|GimpTransformTool
modifier|*
name|gimp_transform_tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  variables  */
end_comment

begin_decl_stmt
DECL|variable|old_trans_info
DECL|variable|old_trans_info
specifier|static
name|TranInfo
name|old_trans_info
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|transform_info
DECL|variable|transform_info
name|InfoDialog
modifier|*
name|transform_info
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|transform_info_inited
DECL|variable|transform_info_inited
specifier|static
name|gboolean
name|transform_info_inited
init|=
name|FALSE
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_transform_tool_get_type (void)
DECL|function|gimp_transform_tool_get_type (void)
name|gimp_transform_tool_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
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
name|GtkTypeInfo
name|tool_info
init|=
block|{
literal|"GimpTransformTool"
block|,
sizeof|sizeof
argument_list|(
name|GimpTransformTool
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpTransformToolClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_transform_tool_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_transform_tool_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
name|NULL
comment|/* (GtkClassInitFunc) gimp_tool_class_init, */
block|}
decl_stmt|;
name|tool_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_DRAW_TOOL
argument_list|,
operator|&
name|tool_info
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
DECL|function|gimp_transform_tool_class_init (GimpTransformToolClass * klass)
DECL|function|gimp_transform_tool_class_init (GimpTransformToolClass * klass)
name|gimp_transform_tool_class_init
parameter_list|(
name|GimpTransformToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpToolClass
modifier|*
name|tool_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|tool_class
operator|=
operator|(
name|GimpToolClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_DRAW_TOOL
argument_list|)
expr_stmt|;
name|gimp_transform_tool_signals
index|[
name|TRANSFORM
index|]
operator|=
name|gtk_signal_new
argument_list|(
literal|"transform"
argument_list|,
name|GTK_RUN_FIRST
argument_list|,
name|object_class
operator|->
name|type
argument_list|,
name|GTK_SIGNAL_OFFSET
argument_list|(
name|GimpTransformToolClass
argument_list|,
name|transform
argument_list|)
argument_list|,
name|gtk_marshal_POINTER__POINTER_INT
argument_list|,
name|GTK_TYPE_POINTER
argument_list|,
literal|2
argument_list|,
name|GTK_TYPE_POINTER
argument_list|,
name|GTK_TYPE_INT
argument_list|)
expr_stmt|;
name|gtk_object_class_add_signals
argument_list|(
name|object_class
argument_list|,
name|gimp_transform_tool_signals
argument_list|,
name|LAST_SIGNAL
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_transform_tool_destroy
expr_stmt|;
name|tool_class
operator|->
name|button_press
operator|=
name|gimp_transform_tool_button_press
expr_stmt|;
name|tool_class
operator|->
name|button_release
operator|=
name|gimp_transform_tool_button_release
expr_stmt|;
name|tool_class
operator|->
name|motion
operator|=
name|gimp_transform_tool_motion
expr_stmt|;
name|tool_class
operator|->
name|cursor_update
operator|=
name|gimp_transform_tool_cursor_update
expr_stmt|;
name|tool_class
operator|->
name|control
operator|=
name|gimp_transform_tool_control
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_transform_tool_init (GimpTransformTool * tool)
DECL|function|gimp_transform_tool_init (GimpTransformTool * tool)
name|gimp_transform_tool_init
parameter_list|(
name|GimpTransformTool
modifier|*
name|tool
parameter_list|)
block|{ }
end_function

begin_function
specifier|static
name|void
DECL|function|pixel_surround_init (PixelSurround * ps,TileManager * tm,gint w,gint h,guchar bg[MAX_CHANNELS])
DECL|function|pixel_surround_init (PixelSurround * ps,TileManager * tm,gint w,gint h,guchar bg[MAX_CHANNELS])
name|pixel_surround_init
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|,
name|TileManager
modifier|*
name|tm
parameter_list|,
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|guchar
name|bg
index|[
name|MAX_CHANNELS
index|]
parameter_list|)
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
name|MAX_CHANNELS
condition|;
operator|++
name|i
control|)
block|{
name|ps
operator|->
name|bg
index|[
name|i
index|]
operator|=
name|bg
index|[
name|i
index|]
expr_stmt|;
block|}
name|ps
operator|->
name|tile
operator|=
name|NULL
expr_stmt|;
name|ps
operator|->
name|mgr
operator|=
name|tm
expr_stmt|;
name|ps
operator|->
name|bpp
operator|=
name|tile_manager_bpp
argument_list|(
name|tm
argument_list|)
expr_stmt|;
name|ps
operator|->
name|w
operator|=
name|w
expr_stmt|;
name|ps
operator|->
name|h
operator|=
name|h
expr_stmt|;
comment|/* make sure buffer is big enough */
name|ps
operator|->
name|buff_size
operator|=
name|w
operator|*
name|h
operator|*
name|ps
operator|->
name|bpp
expr_stmt|;
name|ps
operator|->
name|buff
operator|=
name|g_malloc
argument_list|(
name|ps
operator|->
name|buff_size
argument_list|)
expr_stmt|;
name|ps
operator|->
name|row_stride
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_comment
comment|/* return a pointer to a buffer which contains all the surrounding pixels */
end_comment

begin_comment
comment|/* strategy: if we are in the middle of a tile, use the tile storage */
end_comment

begin_comment
comment|/* otherwise just copy into our own malloced buffer and return that */
end_comment

begin_function
specifier|static
name|guchar
modifier|*
DECL|function|pixel_surround_lock (PixelSurround * ps,gint x,gint y)
DECL|function|pixel_surround_lock (PixelSurround * ps,gint x,gint y)
name|pixel_surround_lock
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|)
block|{
name|gint
name|i
decl_stmt|,
name|j
decl_stmt|;
name|guchar
modifier|*
name|k
decl_stmt|;
name|guchar
modifier|*
name|ptr
decl_stmt|;
name|ps
operator|->
name|tile
operator|=
name|tile_manager_get_tile
argument_list|(
name|ps
operator|->
name|mgr
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|i
operator|=
name|x
operator|%
name|TILE_WIDTH
expr_stmt|;
name|j
operator|=
name|y
operator|%
name|TILE_HEIGHT
expr_stmt|;
comment|/* do we have the whole region? */
if|if
condition|(
name|ps
operator|->
name|tile
operator|&&
operator|(
name|i
operator|<
operator|(
name|tile_ewidth
argument_list|(
name|ps
operator|->
name|tile
argument_list|)
operator|-
name|ps
operator|->
name|w
operator|)
operator|)
operator|&&
operator|(
name|j
operator|<
operator|(
name|tile_eheight
argument_list|(
name|ps
operator|->
name|tile
argument_list|)
operator|-
name|ps
operator|->
name|h
operator|)
operator|)
condition|)
block|{
name|ps
operator|->
name|row_stride
operator|=
name|tile_ewidth
argument_list|(
name|ps
operator|->
name|tile
argument_list|)
operator|*
name|ps
operator|->
name|bpp
expr_stmt|;
comment|/* is this really the correct way? */
return|return
name|tile_data_pointer
argument_list|(
name|ps
operator|->
name|tile
argument_list|,
name|i
argument_list|,
name|j
argument_list|)
return|;
block|}
comment|/* nope, do this the hard way (for now) */
if|if
condition|(
name|ps
operator|->
name|tile
condition|)
block|{
name|tile_release
argument_list|(
name|ps
operator|->
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|ps
operator|->
name|tile
operator|=
literal|0
expr_stmt|;
block|}
comment|/* copy pixels, one by one */
comment|/* no, this is not the best way, but it's much better than before */
name|ptr
operator|=
name|ps
operator|->
name|buff
expr_stmt|;
for|for
control|(
name|j
operator|=
name|y
init|;
name|j
operator|<
name|y
operator|+
name|ps
operator|->
name|h
condition|;
operator|++
name|j
control|)
block|{
for|for
control|(
name|i
operator|=
name|x
init|;
name|i
operator|<
name|x
operator|+
name|ps
operator|->
name|w
condition|;
operator|++
name|i
control|)
block|{
name|Tile
modifier|*
name|tile
init|=
name|tile_manager_get_tile
argument_list|(
name|ps
operator|->
name|mgr
argument_list|,
name|i
argument_list|,
name|j
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
decl_stmt|;
if|if
condition|(
name|tile
condition|)
block|{
name|guchar
modifier|*
name|buff
init|=
name|tile_data_pointer
argument_list|(
name|tile
argument_list|,
name|i
operator|%
name|TILE_WIDTH
argument_list|,
name|j
operator|%
name|TILE_HEIGHT
argument_list|)
decl_stmt|;
for|for
control|(
name|k
operator|=
name|buff
init|;
name|k
operator|<
name|buff
operator|+
name|ps
operator|->
name|bpp
condition|;
operator|++
name|k
operator|,
operator|++
name|ptr
control|)
block|{
operator|*
name|ptr
operator|=
operator|*
name|k
expr_stmt|;
block|}
name|tile_release
argument_list|(
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
else|else
block|{
for|for
control|(
name|k
operator|=
name|ps
operator|->
name|bg
init|;
name|k
operator|<
name|ps
operator|->
name|bg
operator|+
name|ps
operator|->
name|bpp
condition|;
operator|++
name|k
operator|,
operator|++
name|ptr
control|)
block|{
operator|*
name|ptr
operator|=
operator|*
name|k
expr_stmt|;
block|}
block|}
block|}
block|}
name|ps
operator|->
name|row_stride
operator|=
name|ps
operator|->
name|w
operator|*
name|ps
operator|->
name|bpp
expr_stmt|;
return|return
name|ps
operator|->
name|buff
return|;
block|}
end_function

begin_function
specifier|static
name|gint
DECL|function|pixel_surround_rowstride (PixelSurround * ps)
DECL|function|pixel_surround_rowstride (PixelSurround * ps)
name|pixel_surround_rowstride
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
block|{
return|return
name|ps
operator|->
name|row_stride
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pixel_surround_release (PixelSurround * ps)
DECL|function|pixel_surround_release (PixelSurround * ps)
name|pixel_surround_release
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
block|{
comment|/* always get new tile (for now), so release the old one */
if|if
condition|(
name|ps
operator|->
name|tile
condition|)
block|{
name|tile_release
argument_list|(
name|ps
operator|->
name|tile
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|ps
operator|->
name|tile
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|pixel_surround_clear (PixelSurround * ps)
DECL|function|pixel_surround_clear (PixelSurround * ps)
name|pixel_surround_clear
parameter_list|(
name|PixelSurround
modifier|*
name|ps
parameter_list|)
block|{
if|if
condition|(
name|ps
operator|->
name|buff
condition|)
block|{
name|g_free
argument_list|(
name|ps
operator|->
name|buff
argument_list|)
expr_stmt|;
name|ps
operator|->
name|buff
operator|=
literal|0
expr_stmt|;
name|ps
operator|->
name|buff_size
operator|=
literal|0
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|transform_ok_callback (GtkWidget * widget,gpointer data)
DECL|function|transform_ok_callback (GtkWidget * widget,gpointer data)
name|transform_ok_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_transform_tool_doit
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|transform_reset_callback (GtkWidget * widget,gpointer data)
DECL|function|transform_reset_callback (GtkWidget * widget,gpointer data)
name|transform_reset_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpTransformTool
modifier|*
name|tool
decl_stmt|;
name|GimpDrawTool
modifier|*
name|dr_tool
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|tool
operator|=
name|GIMP_TRANSFORM_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|dr_tool
operator|=
name|GIMP_DRAW_TOOL
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/*  stop the current tool drawing process  */
name|gimp_draw_tool_pause
argument_list|(
name|tool
argument_list|)
expr_stmt|;
comment|/*  Restore the previous transformation info  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|TRAN_INFO_SIZE
condition|;
name|i
operator|++
control|)
name|tool
operator|->
name|trans_info
index|[
name|i
index|]
operator|=
name|old_trans_info
index|[
name|i
index|]
expr_stmt|;
comment|/*  recalculate the tool's transformation matrix  */
name|gimp_transform_tool_recalc
argument_list|(
name|tool
argument_list|,
name|tool
operator|->
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  resume drawing the current tool  */
name|gimp_draw_tool_resume
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_decl_stmt
DECL|variable|action_labels
DECL|variable|action_labels
specifier|static
specifier|const
name|gchar
modifier|*
name|action_labels
index|[]
init|=
block|{
name|N_
argument_list|(
literal|"Rotate"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Scale"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Shear"
argument_list|)
block|,
name|N_
argument_list|(
literal|"Transform"
argument_list|)
block|}
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_transform_tool_button_press (GimpTransformTool * gt_tool,GdkEventButton * bevent,GDisplay * gdisp)
DECL|function|gimp_transform_tool_button_press (GimpTransformTool * gt_tool,GdkEventButton * bevent,GDisplay * gdisp)
name|gimp_transform_tool_button_press
parameter_list|(
name|GimpTransformTool
modifier|*
name|gt_tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
name|gint
name|dist
decl_stmt|;
name|gint
name|closest_dist
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|gint
name|off_x
decl_stmt|,
name|off_y
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|gt_tool
argument_list|)
expr_stmt|;
name|gt_tool
operator|->
name|bpressed
operator|=
name|TRUE
expr_stmt|;
comment|/* ALT */
name|drawable
operator|=
name|gimp_image_active_drawable
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gt_tool
operator|->
name|function
operator|==
name|TRANSFORM_CREATING
operator|&&
name|tool
operator|->
name|state
operator|==
name|ACTIVE
condition|)
block|{
comment|/*  Save the current transformation info  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|TRAN_INFO_SIZE
condition|;
name|i
operator|++
control|)
name|old_trans_info
index|[
name|i
index|]
operator|=
name|gt_tool
operator|->
name|trans_info
index|[
name|i
index|]
expr_stmt|;
block|}
comment|/*  if we have already displayed the bounding box and handles,    *  check to make sure that the display which currently owns the    *  tool is the one which just received the button pressed event    */
if|if
condition|(
operator|(
name|gdisp
operator|==
name|tool
operator|->
name|gdisp
operator|)
operator|&&
name|gt_tool
operator|->
name|interactive
condition|)
block|{
comment|/*  start drawing the bounding box and handles...  */
name|gimp_draw_tool_start
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|gt_tool
argument_list|)
argument_list|,
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|)
expr_stmt|;
name|x
operator|=
name|bevent
operator|->
name|x
expr_stmt|;
name|y
operator|=
name|bevent
operator|->
name|y
expr_stmt|;
name|closest_dist
operator|=
name|SQR
argument_list|(
name|x
operator|-
name|gt_tool
operator|->
name|sx1
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
operator|-
name|gt_tool
operator|->
name|sy1
argument_list|)
expr_stmt|;
name|gt_tool
operator|->
name|function
operator|=
name|TRANSFORM_HANDLE_1
expr_stmt|;
name|dist
operator|=
name|SQR
argument_list|(
name|x
operator|-
name|gt_tool
operator|->
name|sx2
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
operator|-
name|gt_tool
operator|->
name|sy2
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|closest_dist
condition|)
block|{
name|closest_dist
operator|=
name|dist
expr_stmt|;
name|gt_tool
operator|->
name|function
operator|=
name|TRANSFORM_HANDLE_2
expr_stmt|;
block|}
name|dist
operator|=
name|SQR
argument_list|(
name|x
operator|-
name|gt_tool
operator|->
name|sx3
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
operator|-
name|gt_tool
operator|->
name|sy3
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|closest_dist
condition|)
block|{
name|closest_dist
operator|=
name|dist
expr_stmt|;
name|gt_tool
operator|->
name|function
operator|=
name|TRANSFORM_HANDLE_3
expr_stmt|;
block|}
name|dist
operator|=
name|SQR
argument_list|(
name|x
operator|-
name|gt_tool
operator|->
name|sx4
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
operator|-
name|gt_tool
operator|->
name|sy4
argument_list|)
expr_stmt|;
if|if
condition|(
name|dist
operator|<
name|closest_dist
condition|)
block|{
name|closest_dist
operator|=
name|dist
expr_stmt|;
name|gt_tool
operator|->
name|function
operator|=
name|TRANSFORM_HANDLE_4
expr_stmt|;
block|}
if|if
condition|(
name|tool
operator|->
name|type
operator|==
name|ROTATE
operator|&&
operator|(
name|SQR
argument_list|(
name|x
operator|-
name|gt_tool
operator|->
name|scx
argument_list|)
operator|+
name|SQR
argument_list|(
name|y
operator|-
name|gt_tool
operator|->
name|scy
argument_list|)
operator|)
operator|<=
literal|100
condition|)
block|{
name|gt_tool
operator|->
name|function
operator|=
name|TRANSFORM_HANDLE_CENTER
expr_stmt|;
block|}
comment|/*  Save the current pointer position  */
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
operator|&
name|gt_tool
operator|->
name|startx
argument_list|,
operator|&
name|gt_tool
operator|->
name|starty
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gt_tool
operator|->
name|lastx
operator|=
name|gt_tool
operator|->
name|startx
expr_stmt|;
name|gt_tool
operator|->
name|lasty
operator|=
name|gt_tool
operator|->
name|starty
expr_stmt|;
name|gdk_pointer_grab
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
return|return;
block|}
comment|/*  Initialisation stuff: if the cursor is clicked inside the current    *  selection, show the bounding box and handles...    */
name|gdisplay_untransform_coords
argument_list|(
name|gdisp
argument_list|,
name|bevent
operator|->
name|x
argument_list|,
name|bevent
operator|->
name|y
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
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
name|GIMP_IS_LAYER
argument_list|(
name|drawable
argument_list|)
operator|&&
name|gimp_layer_get_mask
argument_list|(
name|GIMP_LAYER
argument_list|(
name|drawable
argument_list|)
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Transformations do not work on\n"
literal|"layers that contain layer masks."
argument_list|)
argument_list|)
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|INACTIVE
expr_stmt|;
return|return;
block|}
comment|/*  If the tool is already active, clear the current state 	 *  and reset 	 */
if|if
condition|(
name|tool
operator|->
name|state
operator|==
name|ACTIVE
condition|)
name|gimp_transform_tool_reset
argument_list|(
name|gt_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  Set the pointer to the active display  */
name|tool
operator|->
name|gdisp
operator|=
name|gdisp
expr_stmt|;
name|tool
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|tool
operator|->
name|state
operator|=
name|ACTIVE
expr_stmt|;
comment|/*  Grab the pointer if we're in non-interactive mode  */
if|if
condition|(
operator|!
name|gt_tool
operator|->
name|interactive
condition|)
name|gdk_pointer_grab
argument_list|(
name|gdisp
operator|->
name|canvas
operator|->
name|window
argument_list|,
name|FALSE
argument_list|,
operator|(
name|GDK_POINTER_MOTION_HINT_MASK
operator||
name|GDK_BUTTON1_MOTION_MASK
operator||
name|GDK_BUTTON_RELEASE_MASK
operator|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
comment|/*  Find the transform bounds for some tools (like scale, 	 *  perspective) that actually need the bounds for 	 *  initializing 	 */
name|gimp_transform_tool_bounds
argument_list|(
name|gt_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  Calculate the grid line endpoints  */
if|if
condition|(
name|gimp_transform_tool_show_grid
argument_list|()
condition|)
name|gimp_transform_tool_setup_grid
argument_list|(
name|tool
argument_list|)
expr_stmt|;
comment|/*  Initialize the transform tool */
comment|/*FIXME*/
call|(
modifier|*
name|gt_tool
operator|->
name|trans_func
call|)
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|,
name|TRANSFORM_INIT
argument_list|)
expr_stmt|;
if|if
condition|(
name|transform_info
operator|&&
operator|!
name|transform_info_inited
condition|)
block|{
name|gimp_dialog_create_action_area
argument_list|(
name|GTK_DIALOG
argument_list|(
name|transform_info
operator|->
name|shell
argument_list|)
argument_list|,
name|gettext
argument_list|(
name|action_labels
index|[
name|tool
operator|->
name|type
operator|-
name|ROTATE
index|]
argument_list|)
argument_list|,
name|transform_ok_callback
argument_list|,
name|tool
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Reset"
argument_list|)
argument_list|,
name|transform_reset_callback
argument_list|,
name|tool
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|transform_info_inited
operator|=
name|TRUE
expr_stmt|;
block|}
comment|/*  Recalculate the transform tool  */
name|gimp_transform_tool_recalc
argument_list|(
name|gt_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  recall this function to find which handle we're dragging  */
if|if
condition|(
name|gimp_transform_tool
operator|->
name|interactive
condition|)
name|gimp_transform_tool_button_press
argument_list|(
name|gt_tool
argument_list|,
name|bevent
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_transform_tool_button_release (GimpTransformTool * gt_tool,GdkEventButton * bevent,GDisplay * gdisp)
DECL|function|gimp_transform_tool_button_release (GimpTransformTool * gt_tool,GdkEventButton * bevent,GDisplay * gdisp)
name|gimp_transform_tool_button_release
parameter_list|(
name|GimpTransformTool
modifier|*
name|gt_tool
parameter_list|,
name|GdkEventButton
modifier|*
name|bevent
parameter_list|,
name|GDisplay
modifier|*
name|gdisp
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|tool
argument_list|)
expr_stmt|;
name|gt_tool
operator|->
name|bpressed
operator|=
name|FALSE
expr_stmt|;
comment|/* ALT */
comment|/*  if we are creating, there is nothing to be done...exit  */
if|if
condition|(
name|gt_tool
operator|->
name|function
operator|==
name|TRANSFORM_CREATING
operator|&&
name|gt_tool
operator|->
name|interactive
condition|)
return|return;
comment|/*  release of the pointer grab  */
name|gdk_pointer_ungrab
argument_list|(
name|bevent
operator|->
name|time
argument_list|)
expr_stmt|;
name|gdk_flush
argument_list|()
expr_stmt|;
comment|/*  if the 3rd button isn't pressed, transform the selected mask  */
if|if
condition|(
operator|!
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_BUTTON3_MASK
operator|)
condition|)
block|{
comment|/* Shift-clicking is another way to approve the transform  */
if|if
condition|(
operator|(
name|bevent
operator|->
name|state
operator|&
name|GDK_SHIFT_MASK
operator|)
operator|||
operator|(
name|tool
operator|->
name|type
operator|==
name|FLIP
operator|)
condition|)
block|{
name|gimp_transform_tool_doit
argument_list|(
name|tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
else|else
block|{
comment|/*  Only update the paths preview */
name|path_transform_current_path
argument_list|(
name|gdisp
operator|->
name|gimage
argument_list|,
name|gt_tool
operator|->
name|transform
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
comment|/*  stop the current tool drawing process  */
name|gimp_draw_tool_pause
argument_list|(
name|GIMP_DRAW_TOOL
argument_list|(
name|gt_tool
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  Restore the previous transformation info  */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|TRAN_INFO_SIZE
condition|;
name|i
operator|++
control|)
name|gt_tool
operator|->
name|trans_info
index|[
name|i
index|]
operator|=
name|old_trans_info
index|[
name|i
index|]
expr_stmt|;
comment|/*  recalculate the tool's transformation matrix  */
name|gimp_transform_tool_recalc
argument_list|(
name|gt_tool
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  resume drawing the current tool  */
name|gimp_draw_tool_resume
argument_list|(
argument|GIMP_DRAW_TOOL(gt_tool);
comment|/* Update the paths preview */
argument|path_transform_current_path (gdisp->gimage, 				   gt_tool->transform, TRUE);     }
comment|/*  if this tool is non-interactive, make it inactive after use  */
argument|if (!gt_tool->interactive)     tool->state = INACTIVE; }  void gimp_transform_tool_doit (GimpTransformTool  *gt_tool, 		          GDisplay           *gdisp) {   GimpTool      *tool;   TileManager   *new_tiles;   TransformUndo *tu;   PathUndo      *pundo;   gboolean       new_layer;   gint           i
argument_list|,
argument|x
argument_list|,
argument|y;    gimp_add_busy_cursors ();    gimp_transform_tool = GIMP_TOOL(tool);
comment|/* undraw the tool before we muck around with the transform matrix */
argument|gimp_draw_tool_pause (GIMP_DRAW_TOOL(gt_tool));
comment|/*  We're going to dirty this image, but we want to keep the tool    *  around    */
argument|tool->preserve = TRUE;
comment|/*  Start a transform undo group  */
argument|undo_push_group_start (gdisp->gimage, TRANSFORM_CORE_UNDO);
comment|/*  With the old UI, if original is NULL, then this is the       first transformation. In the new UI, it is always so, right?  */
argument|g_assert (gt_tool->original == NULL);
comment|/* If we're in interactive mode, we need to copy the current    *  selection to the transform tool's private selection pointer, so    *  that the original source can be repeatedly modified.    */
argument|tool->drawable = gimp_image_active_drawable (gdisp->gimage);    gt_tool->original = gimp_transform_tool_cut (gdisp->gimage, 					       tool->drawable,&new_layer);    pundo = path_transform_start_undo (gdisp->gimage);
comment|/*  Send the request for the transformation to the tool...    */
comment|/* FIXME */
argument|new_tiles = (* gimp_transform_tool->trans_func) (gt_tool, gdisp, 					      TRANSFORM_FINISH);
comment|/* FIXME TOO */
argument|(* gimp_transform_tool->trans_func) (gt_tool, gdisp, TRANSFORM_INIT);    gimp_transform_tool_recalc (gt_tool, gdisp);    if (new_tiles)     {
comment|/*  paste the new transformed image to the gimage...also implement        *  undo...        */
comment|/*  FIXME: we should check if the drawable is still valid  */
argument|gimp_transform_tool_paste (gdisp->gimage, tool->drawable, 			    new_tiles, new_layer);
comment|/*  create and initialize the transform_undo structure  */
argument|tu = g_new (TransformUndo,
literal|1
argument|);       tu->tool_ID = tool->ID;       tu->tool_type = tool->type;       for (i =
literal|0
argument|; i< TRAN_INFO_SIZE; i++) 	tu->trans_info[i] = old_trans_info[i];       tu->original = NULL;       tu->path_undo = pundo;
comment|/*  Make a note of the new current drawable (since we may have        *  a floating selection, etc now.        */
argument|tool->drawable = gimp_image_active_drawable (gdisp->gimage);        undo_push_transform (gdisp->gimage, (void *) tu);     }
comment|/*  push the undo group end  */
argument|undo_push_group_end (gdisp->gimage);
comment|/*  We're done dirtying the image, and would like to be restarted    *  if the image gets dirty while the tool exists    */
argument|tool->preserve = FALSE;
comment|/*  Flush the gdisplays  */
argument|if (gdisp->disp_xoffset || gdisp->disp_yoffset)     {       gdk_window_get_size (gdisp->canvas->window,&x,&y);       if (gdisp->disp_yoffset) 	{ 	  gdisplay_expose_area (gdisp,
literal|0
argument|,
literal|0
argument|, gdisp->disp_width, 				gdisp->disp_yoffset); 	  gdisplay_expose_area (gdisp,
literal|0
argument|, gdisp->disp_yoffset + y, 				gdisp->disp_width, gdisp->disp_height); 	}       if (gdisp->disp_xoffset) 	{ 	  gdisplay_expose_area (gdisp,
literal|0
argument|,
literal|0
argument|, gdisp->disp_xoffset, 				gdisp->disp_height); 	  gdisplay_expose_area (gdisp, gdisp->disp_xoffset + x,
literal|0
argument|, 				gdisp->disp_width, gdisp->disp_height); 	}     }    gimp_remove_busy_cursors (NULL);    gdisplays_flush ();    gimp_transform_tool_reset (tool, gdisp);
comment|/*  if this tool is non-interactive, make it inactive after use  */
argument|if (!gimp_transform_tool->interactive)     tool->state = INACTIVE; }
comment|/* FIXME I haven't really touched anything after this point. */
argument|void gimp_transform_tool_motion (GimpTransformTool           *tool, 		       GdkEventMotion *mevent, 		       GDisplay       *gdisp) {   GimpTransformTool *gimp_transform_tool;    gimp_transform_tool = (GimpTransformTool *) tool->private;    if (gimp_transform_tool->bpressed == FALSE)   {
comment|/*  hey we have not got the button press yet      *  so go away.      */
argument|return;   }
comment|/*  if we are creating or this tool is non-interactive, there is    *  nothing to be done so exit.    */
argument|if (gimp_transform_tool->function == TRANSFORM_CREATING ||       !gimp_transform_tool->interactive)     return;
comment|/*  stop the current tool drawing process  */
argument|gimp_draw_tool_pause (gimp_transform_tool->core, tool);    gdisplay_untransform_coords (gdisp, mevent->x, mevent->y,&gimp_transform_tool->curx,&gimp_transform_tool->cury, TRUE,
literal|0
argument|);   gimp_transform_tool->state = mevent->state;
comment|/*  recalculate the tool's transformation matrix  */
argument|(* gimp_transform_tool->trans_func) (tool, gdisp, TRANSFORM_MOTION);    gimp_transform_tool->lastx = gimp_transform_tool->curx;   gimp_transform_tool->lasty = gimp_transform_tool->cury;
comment|/*  resume drawing the current tool  */
argument|gimp_draw_tool_resume (gimp_transform_tool->core, tool); }  void gimp_transform_tool_cursor_update (GimpTransformTool           *tool, 			      GdkEventMotion *mevent, 			      GDisplay       *gdisp) {   GimpTransformTool *gimp_transform_tool;   GimpDrawable  *drawable;   GdkCursorType  ctype = GDK_TOP_LEFT_ARROW;   gint           x
argument_list|,
argument|y;    gimp_transform_tool = (GimpTransformTool *) tool->private;    gdisplay_untransform_coords (gdisp, mevent->x, mevent->y,&x,&y, 			       FALSE, FALSE);    if ((drawable = gimp_image_active_drawable (gdisp->gimage)))     {       if (GIMP_IS_LAYER (drawable)&& 	  gimp_layer_get_mask (GIMP_LAYER (drawable))) 	{ 	  ctype = GIMP_BAD_CURSOR; 	}       else if (x>= drawable->offset_x&& 	       y>= drawable->offset_y&& 	       x< (drawable->offset_x + drawable->width)&& 	       y< (drawable->offset_y + drawable->height)) 	{ 	  if (gimage_mask_is_empty (gdisp->gimage) || 	      gimage_mask_value (gdisp->gimage, x, y)) 	    { 	      ctype = GIMP_MOUSE_CURSOR; 	    } 	}     }    gdisplay_install_tool_cursor (gdisp, 				ctype, 				tool->tool_cursor, 				GIMP_CURSOR_MODIFIER_NONE); }  void gimp_transform_tool_control (GimpTransformTool       *tool, 			GimpTransformToolAction  action, 			GDisplay   *gdisp) {   GimpTransformTool *gimp_transform_tool;    gimp_transform_tool = (GimpTransformTool *) tool->private;    switch (action)     {     case PAUSE:       gimp_draw_tool_pause (gimp_transform_tool->core, tool);       break;      case RESUME:       gimp_transform_tool_recalc (tool, gdisp);       gimp_draw_tool_resume (gimp_transform_tool->core, tool);       break;      case HALT:       gimp_transform_tool_reset (tool, gdisp);       break;      default:       break;     } }  void gimp_transform_tool_no_draw (GimpTransformTool *tool) {   return; }  void gimp_transform_tool_draw (GimpTransformTool *tool) {   GDisplay      *gdisp;   GimpTransformTool *gimp_transform_tool;   gint           x1
argument_list|,
argument|y1
argument_list|,
argument|x2
argument_list|,
argument|y2
argument_list|,
argument|x3
argument_list|,
argument|y3
argument_list|,
argument|x4
argument_list|,
argument|y4;   gint           srw
argument_list|,
argument|srh;   gint           i
argument_list|,
argument|k
argument_list|,
argument|gci;   gint           xa
argument_list|,
argument|ya
argument_list|,
argument|xb
argument_list|,
argument|yb;    gdisp          = tool->gdisp;   gimp_transform_tool = (GimpTransformTool *) tool->private;    gdisplay_transform_coords (gdisp, gimp_transform_tool->tx1, gimp_transform_tool->ty1,&gimp_transform_tool->sx1,&gimp_transform_tool->sy1, FALSE);   gdisplay_transform_coords (gdisp, gimp_transform_tool->tx2, gimp_transform_tool->ty2,&gimp_transform_tool->sx2,&gimp_transform_tool->sy2, FALSE);   gdisplay_transform_coords (gdisp, gimp_transform_tool->tx3, gimp_transform_tool->ty3,&gimp_transform_tool->sx3,&gimp_transform_tool->sy3, FALSE);   gdisplay_transform_coords (gdisp, gimp_transform_tool->tx4, gimp_transform_tool->ty4,&gimp_transform_tool->sx4,&gimp_transform_tool->sy4, FALSE);    x1 = gimp_transform_tool->sx1;  y1 = gimp_transform_tool->sy1;   x2 = gimp_transform_tool->sx2;  y2 = gimp_transform_tool->sy2;   x3 = gimp_transform_tool->sx3;  y3 = gimp_transform_tool->sy3;   x4 = gimp_transform_tool->sx4;  y4 = gimp_transform_tool->sy4;
comment|/*  find the handles' width and height  */
argument|srw =
literal|10
argument|;   srh =
literal|10
argument|;
comment|/*  draw the bounding box  */
argument|gdk_draw_line (gimp_transform_tool->core->win, gimp_transform_tool->core->gc, 		 x1, y1, x2, y2);   gdk_draw_line (gimp_transform_tool->core->win, gimp_transform_tool->core->gc, 		 x2, y2, x4, y4);   gdk_draw_line (gimp_transform_tool->core->win, gimp_transform_tool->core->gc, 		 x3, y3, x4, y4);   gdk_draw_line (gimp_transform_tool->core->win, gimp_transform_tool->core->gc, 		 x3, y3, x1, y1);
comment|/*  Draw the grid */
argument|if ((gimp_transform_tool->grid_coords != NULL)&&       (gimp_transform_tool->tgrid_coords != NULL)&&       ((tool->type != PERSPECTIVE) ||        ((gimp_transform_tool->transform[
literal|0
argument|][
literal|0
argument|]>=
literal|0.0
argument|)&& 	(gimp_transform_tool->transform[
literal|1
argument|][
literal|1
argument|]>=
literal|0.0
argument|))))     {        gci =
literal|0
argument|;       k = gimp_transform_tool->ngx + gimp_transform_tool->ngy;       for (i =
literal|0
argument|; i< k; i++) 	{ 	  gdisplay_transform_coords (gdisp, gimp_transform_tool->tgrid_coords[gci], 				     gimp_transform_tool->tgrid_coords[gci+
literal|1
argument|],&xa,&ya, FALSE); 	  gdisplay_transform_coords (gdisp, gimp_transform_tool->tgrid_coords[gci+
literal|2
argument|], 				     gimp_transform_tool->tgrid_coords[gci+
literal|3
argument|],&xb,&yb, FALSE);  	  gdk_draw_line (gimp_transform_tool->core->win, gimp_transform_tool->core->gc, 			 xa, ya, xb, yb); 	  gci +=
literal|4
argument|; 	}     }
comment|/*  draw the tool handles  */
argument|gdk_draw_rectangle (gimp_transform_tool->core->win, gimp_transform_tool->core->gc,
literal|0
argument|, 		      x1 - (srw>>
literal|1
argument|), y1 - (srh>>
literal|1
argument|), srw, srh);   gdk_draw_rectangle (gimp_transform_tool->core->win, gimp_transform_tool->core->gc,
literal|0
argument|, 		      x2 - (srw>>
literal|1
argument|), y2 - (srh>>
literal|1
argument|), srw, srh);   gdk_draw_rectangle (gimp_transform_tool->core->win, gimp_transform_tool->core->gc,
literal|0
argument|, 		      x3 - (srw>>
literal|1
argument|), y3 - (srh>>
literal|1
argument|), srw, srh);   gdk_draw_rectangle (gimp_transform_tool->core->win, gimp_transform_tool->core->gc,
literal|0
argument|, 		      x4 - (srw>>
literal|1
argument|), y4 - (srh>>
literal|1
argument|), srw, srh);
comment|/*  draw the center  */
argument|if (tool->type == ROTATE)     {       gdisplay_transform_coords (gdisp, gimp_transform_tool->tcx, gimp_transform_tool->tcy,&gimp_transform_tool->scx,&gimp_transform_tool->scy, FALSE);        gdk_draw_arc (gimp_transform_tool->core->win, gimp_transform_tool->core->gc,
literal|1
argument|, 		    gimp_transform_tool->scx - (srw>>
literal|1
argument|), 		    gimp_transform_tool->scy - (srh>>
literal|1
argument|), 		    srw, srh,
literal|0
argument|,
literal|23040
argument|);     }    if (transform_tool_showpath ())     {       GimpMatrix3 tmp_matrix;        if (transform_tool_direction () == TRANSFORM_CORRECTIVE) 	{ 	  gimp_matrix3_invert (gimp_transform_tool->transform, tmp_matrix); 	}       else 	{ 	  gimp_matrix3_duplicate (gimp_transform_tool->transform, tmp_matrix); 	}        path_transform_draw_current (gdisp, gimp_transform_tool->core, tmp_matrix);     } }  GimpTransformTool * gimp_transform_tool_new (GimpTransformToolType type, 		    gint     interactive) {   GimpTransformTool          *tool;   GimpTransformTool *private;   gint           i;    tool = tools_new_tool (type);   private = g_new0 (GimpTransformTool,
literal|1
argument|);    private->interactive = interactive;    if (interactive)     private->core = gimp_draw_tool_new (gimp_transform_tool_draw);   else     private->core = gimp_draw_tool_new (gimp_transform_tool_no_draw);    private->function = TRANSFORM_CREATING;   private->original = NULL;    private->bpressed = FALSE;    for (i =
literal|0
argument|; i< TRAN_INFO_SIZE; i++)     private->trans_info[i] =
literal|0
argument|;    private->grid_coords = private->tgrid_coords = NULL;    tool->scroll_lock = TRUE;
comment|/*  Disallow scrolling  */
argument|tool->preserve    = FALSE;
comment|/*  Don't preserve on drawable change  */
argument|tool->private = (void *) private;     return tool; }  void gimp_transform_tool_free (GimpTransformTool *tool) {   GimpTransformTool *gimp_transform_tool;    gimp_transform_tool = (GimpTransformTool *) tool->private;
comment|/*  Make sure the selection core is not visible  */
argument|if (tool->state == ACTIVE)     gimp_draw_tool_stop (gimp_transform_tool->core, tool);
comment|/*  Free the selection core  */
argument|gimp_draw_tool_free (gimp_transform_tool->core);
comment|/*  Free up the original selection if it exists  */
argument|if (gimp_transform_tool->original)     tile_manager_destroy (gimp_transform_tool->original);
comment|/*  If there is an information dialog, free it up  */
argument|if (transform_info)     info_dialog_free (transform_info);    transform_info        = NULL;   transform_info_inited = FALSE;
comment|/*  Free the grid line endpoint arrays if they exist */
argument|if (gimp_transform_tool->grid_coords != NULL)     g_free (gimp_transform_tool->grid_coords);    if (gimp_transform_tool->tgrid_coords != NULL)     g_free (gimp_transform_tool->tgrid_coords);
comment|/*  Finally, free the transform tool itself  */
argument|g_free (gimp_transform_tool); }  void gimp_transform_tool_transform_bounding_box (GimpTransformTool *tool) {   GimpTransformTool *gimp_transform_tool;   gint           i
argument_list|,
argument|k;   gint           gci;    gimp_transform_tool = (GimpTransformTool *) tool->private;    gimp_matrix3_transform_point (gimp_transform_tool->transform, 				gimp_transform_tool->x1, gimp_transform_tool->y1,&gimp_transform_tool->tx1,&gimp_transform_tool->ty1);   gimp_matrix3_transform_point (gimp_transform_tool->transform, 				gimp_transform_tool->x2, gimp_transform_tool->y1,&gimp_transform_tool->tx2,&gimp_transform_tool->ty2);   gimp_matrix3_transform_point (gimp_transform_tool->transform, 				gimp_transform_tool->x1, gimp_transform_tool->y2,&gimp_transform_tool->tx3,&gimp_transform_tool->ty3);   gimp_matrix3_transform_point (gimp_transform_tool->transform, 				gimp_transform_tool->x2, gimp_transform_tool->y2,&gimp_transform_tool->tx4,&gimp_transform_tool->ty4);    if (tool->type == ROTATE)     gimp_matrix3_transform_point (gimp_transform_tool->transform, 				  gimp_transform_tool->cx, gimp_transform_tool->cy,&gimp_transform_tool->tcx,&gimp_transform_tool->tcy);    if (gimp_transform_tool->grid_coords != NULL&&       gimp_transform_tool->tgrid_coords != NULL)     {       gci =
literal|0
argument|;       k  = (gimp_transform_tool->ngx + gimp_transform_tool->ngy) *
literal|2
argument|;       for (i =
literal|0
argument|; i< k; i++) 	{ 	  gimp_matrix3_transform_point (gimp_transform_tool->transform, 					gimp_transform_tool->grid_coords[gci], 					gimp_transform_tool->grid_coords[gci+
literal|1
argument|],&(gimp_transform_tool->tgrid_coords[gci]),&(gimp_transform_tool->tgrid_coords[gci+
literal|1
argument|])); 	  gci +=
literal|2
argument|; 	}     } }  void gimp_transform_tool_reset (GimpTransformTool     *tool, 		      GDisplay *gdisp) {   GimpTransformTool *gimp_transform_tool;    gimp_transform_tool = (GimpTransformTool *) tool->private;    if (gimp_transform_tool->original)     tile_manager_destroy (gimp_transform_tool->original);   gimp_transform_tool->original = NULL;
comment|/*  inactivate the tool  */
argument|gimp_transform_tool->function = TRANSFORM_CREATING;   gimp_draw_tool_stop (gimp_transform_tool->core, tool);   info_dialog_popdown (transform_info);    tool->state    = INACTIVE;   tool->gdisp    = NULL;   tool->drawable = NULL; }  static void gimp_transform_tool_bounds (GimpTransformTool     *tool, 		       GDisplay *gdisp) {   GimpTransformTool *gimp_transform_tool;   TileManager   *tiles;   GimpDrawable  *drawable;   gint           offset_x
argument_list|,
argument|offset_y;    gimp_transform_tool = (GimpTransformTool *) tool->private;   tiles          = gimp_transform_tool->original;   drawable       = gimp_image_active_drawable (gdisp->gimage);
comment|/*  find the boundaries  */
argument|if (tiles)     {       tile_manager_get_offsets (tiles,&gimp_transform_tool->x1,&gimp_transform_tool->y1);       gimp_transform_tool->x2 = gimp_transform_tool->x1 + tile_manager_width (tiles);       gimp_transform_tool->y2 = gimp_transform_tool->y1 + tile_manager_height (tiles);     }   else     {       gimp_drawable_offsets (drawable,&offset_x,&offset_y);       gimp_drawable_mask_bounds (drawable,&gimp_transform_tool->x1,&gimp_transform_tool->y1,&gimp_transform_tool->x2,&gimp_transform_tool->y2);       gimp_transform_tool->x1 += offset_x;       gimp_transform_tool->y1 += offset_y;       gimp_transform_tool->x2 += offset_x;       gimp_transform_tool->y2 += offset_y;     }   gimp_transform_tool->cx = (gimp_transform_tool->x1 + gimp_transform_tool->x2) /
literal|2
argument|;   gimp_transform_tool->cy = (gimp_transform_tool->y1 + gimp_transform_tool->y2) /
literal|2
argument|;
comment|/*  changing the bounds invalidates any grid we may have  */
argument|gimp_transform_tool_grid_recalc (gimp_transform_tool); }  void gimp_transform_tool_grid_density_changed (void) {   GimpTransformTool *gimp_transform_tool;
comment|/* EEEEEEEK!!! */
argument|gimp_transform_tool = GIMP_TRANSFORM_TOOL(active_tool);    if (gimp_transform_tool->function == TRANSFORM_CREATING)     return;    gimp_draw_tool_pause (gimp_transform_tool->core, active_tool);   gimp_transform_tool_grid_recalc (gimp_transform_tool);   gimp_transform_tool_transform_bounding_box (active_tool);   gimp_draw_tool_resume (gimp_transform_tool->core, active_tool); }  void gimp_transform_tool_showpath_changed (gint type) {   GimpTransformTool *gimp_transform_tool;    gimp_transform_tool = (GimpTransformTool *) active_tool->private;    if (gimp_transform_tool->function == TRANSFORM_CREATING)     return;    if (type)     gimp_draw_tool_pause (gimp_transform_tool->core, active_tool);   else     gimp_draw_tool_resume (gimp_transform_tool->core, active_tool); }  static void gimp_transform_tool_grid_recalc (GimpTransformTool *gimp_transform_tool) {   if (gimp_transform_tool->grid_coords != NULL)     {       g_free (gimp_transform_tool->grid_coords);       gimp_transform_tool->grid_coords = NULL;     }   if (gimp_transform_tool->tgrid_coords != NULL)     {       g_free (gimp_transform_tool->tgrid_coords);       gimp_transform_tool->tgrid_coords = NULL;     }   if (transform_tool_show_grid ())     gimp_transform_tool_setup_grid (active_tool); }  static void gimp_transform_tool_setup_grid (GimpTransformTool *tool) {   GimpTransformTool *gimp_transform_tool;   gint           i
argument_list|,
argument|gci;   gdouble       *coords;    gimp_transform_tool = (GimpTransformTool *) tool->private;
comment|/*  We use the transform_tool_grid_size function only here, even    *  if the user changes the grid size in the middle of an    *  operation, nothing happens.    */
argument|gimp_transform_tool->ngx =     (gimp_transform_tool->x2 - gimp_transform_tool->x1) / transform_tool_grid_size ();   if (gimp_transform_tool->ngx>
literal|0
argument|)     gimp_transform_tool->ngx--;   gimp_transform_tool->ngy =     (gimp_transform_tool->y2 - gimp_transform_tool->y1) / transform_tool_grid_size ();   if (gimp_transform_tool->ngy>
literal|0
argument|)     gimp_transform_tool->ngy--;    gimp_transform_tool->grid_coords = coords =     g_new (double, (gimp_transform_tool->ngx + gimp_transform_tool->ngy) *
literal|4
argument|);    gimp_transform_tool->tgrid_coords =     g_new (double, (gimp_transform_tool->ngx + gimp_transform_tool->ngy) *
literal|4
argument|);    gci =
literal|0
argument|;   for (i =
literal|1
argument|; i<= gimp_transform_tool->ngx; i++)     {       coords[gci] = gimp_transform_tool->x1 + 	((double) i)/(gimp_transform_tool->ngx +
literal|1
argument|) * 	(gimp_transform_tool->x2 - gimp_transform_tool->x1);       coords[gci+
literal|1
argument|] = gimp_transform_tool->y1;       coords[gci+
literal|2
argument|] = coords[gci];       coords[gci+
literal|3
argument|] = gimp_transform_tool->y2;       gci +=
literal|4
argument|;     }   for (i =
literal|1
argument|; i<= gimp_transform_tool->ngy; i++)     {       coords[gci] = gimp_transform_tool->x1;       coords[gci+
literal|1
argument|] = gimp_transform_tool->y1 + 	((double) i)/(gimp_transform_tool->ngy +
literal|1
argument|) * 	(gimp_transform_tool->y2 - gimp_transform_tool->y1);       coords[gci+
literal|2
argument|] = gimp_transform_tool->x2;       coords[gci+
literal|3
argument|] = coords[gci+
literal|1
argument|];       gci +=
literal|4
argument|;     } }  static void gimp_transform_tool_recalc (GimpTransformTool     *tool, 		       GDisplay *gdisp) {   GimpTransformTool *gimp_transform_tool;    gimp_transform_tool = (GimpTransformTool *) tool->private;    gimp_transform_tool_bounds (tool, gdisp);    (* gimp_transform_tool->trans_func) (tool, gdisp, TRANSFORM_RECALC); }
comment|/*  Actually carry out a transformation  */
argument|TileManager * gimp_transform_tool_do (GImage           *gimage,                    GimpDrawable     *drawable,                    TileManager      *float_tiles,                    gboolean          interpolation,                    GimpMatrix3       matrix,                    GimpProgressFunc  progress_callback,                    gpointer          progress_data) {   PixelRegion  destPR;   TileManager *tiles;   GimpMatrix3  m;   GimpMatrix3  im;   gint         itx
argument_list|,
argument|ity;   gint         tx1
argument_list|,
argument|ty1
argument_list|,
argument|tx2
argument_list|,
argument|ty2;   gint         width
argument_list|,
argument|height;   gint         alpha;   gint         bytes
argument_list|,
argument|b;   gint         x
argument_list|,
argument|y;   gint         sx
argument_list|,
argument|sy;   gint         x1
argument_list|,
argument|y1
argument_list|,
argument|x2
argument_list|,
argument|y2;   gdouble      xinc
argument_list|,
argument|yinc
argument_list|,
argument|winc;   gdouble      tx
argument_list|,
argument|ty
argument_list|,
argument|tw;   gdouble      ttx =
literal|0.0
argument_list|,
argument|tty =
literal|0.0
argument|;   guchar      *dest;   guchar      *d;   guchar      *src[
literal|16
argument|];   Tile        *tile[
literal|16
argument|];   guchar       bg_col[MAX_CHANNELS];   gint         i;   gdouble      a_val
argument_list|,
argument|a_recip;   gint         newval;    PixelSurround surround;    alpha =
literal|0
argument|;
comment|/*  turn interpolation off for simple transformations (e.g. rot90)  */
argument|if (gimp_matrix3_is_simple (matrix) ||       interpolation_type == NEAREST_NEIGHBOR_INTERPOLATION)     interpolation = FALSE;
comment|/*  Get the background color  */
argument|gimp_image_get_background (gimage, drawable, bg_col);    switch (gimp_drawable_type (drawable))     {     case RGB_GIMAGE: case RGBA_GIMAGE:       bg_col[ALPHA_PIX] = TRANSPARENT_OPACITY;       alpha = ALPHA_PIX;       break;     case GRAY_GIMAGE: case GRAYA_GIMAGE:       bg_col[ALPHA_G_PIX] = TRANSPARENT_OPACITY;       alpha = ALPHA_G_PIX;       break;     case INDEXED_GIMAGE: case INDEXEDA_GIMAGE:       bg_col[ALPHA_I_PIX] = TRANSPARENT_OPACITY;       alpha = ALPHA_I_PIX;
comment|/*  If the gimage is indexed color, ignore smoothing value  */
argument|interpolation = FALSE;       break;     default:       g_assert_not_reached ();       break;     }
comment|/*  enable rotating un-floated non-layers  */
argument|if (tile_manager_bpp (float_tiles) ==
literal|1
argument|)     {       bg_col[
literal|0
argument|] = OPAQUE_OPACITY;
comment|/*  setting alpha = 0 will cause the channel's value to be treated        *  as alpha and the color channel loops never to be entered        */
argument|alpha =
literal|0
argument|;     }    if (transform_tool_direction () == TRANSFORM_CORRECTIVE)     {
comment|/*  keep the original matrix here, so we dont need to recalculate 	  the inverse later  */
argument|gimp_matrix3_duplicate (matrix, m);       gimp_matrix3_invert (matrix, im);       matrix = im;     }   else     {
comment|/*  Find the inverse of the transformation matrix  */
argument|gimp_matrix3_invert (matrix, m);     }    path_transform_current_path (gimage, matrix, FALSE);    tile_manager_get_offsets (float_tiles,&x1,&y1);   x2 = x1 + tile_manager_width (float_tiles);   y2 = y1 + tile_manager_height (float_tiles);
comment|/*  Find the bounding coordinates  */
argument|if (alpha ==
literal|0
argument||| (active_tool&& transform_tool_clip ()))     {       tx1 = x1;       ty1 = y1;       tx2 = x2;       ty2 = y2;     }   else     {       gdouble dx1
argument_list|,
argument|dy1
argument_list|,
argument|dx2
argument_list|,
argument|dy2
argument_list|,
argument|dx3
argument_list|,
argument|dy3
argument_list|,
argument|dx4
argument_list|,
argument|dy4;        gimp_matrix3_transform_point (matrix, x1, y1,&dx1,&dy1);       gimp_matrix3_transform_point (matrix, x2, y1,&dx2,&dy2);       gimp_matrix3_transform_point (matrix, x1, y2,&dx3,&dy3);       gimp_matrix3_transform_point (matrix, x2, y2,&dx4,&dy4);        tx1 = MIN (dx1, dx2);       tx1 = MIN (tx1, dx3);       tx1 = MIN (tx1, dx4);       ty1 = MIN (dy1, dy2);       ty1 = MIN (ty1, dy3);       ty1 = MIN (ty1, dy4);       tx2 = MAX (dx1, dx2);       tx2 = MAX (tx2, dx3);       tx2 = MAX (tx2, dx4);       ty2 = MAX (dy1, dy2);       ty2 = MAX (ty2, dy3);       ty2 = MAX (ty2, dy4);     }
comment|/*  Get the new temporary buffer for the transformed result  */
argument|tiles = tile_manager_new ((tx2 - tx1), (ty2 - ty1), 			    tile_manager_bpp (float_tiles));   pixel_region_init (&destPR, tiles,
literal|0
argument|,
literal|0
argument|, (tx2 - tx1), (ty2 - ty1), TRUE);   tile_manager_set_offsets (tiles, tx1, ty1);
comment|/* initialise the pixel_surround accessor */
argument|if (interpolation)     {       if (interpolation_type == CUBIC_INTERPOLATION) 	{ 	  pixel_surround_init (&surround, float_tiles,
literal|4
argument|,
literal|4
argument|, bg_col); 	}       else 	{ 	  pixel_surround_init (&surround, float_tiles,
literal|2
argument|,
literal|2
argument|, bg_col); 	}     }   else     {
comment|/* not actually useful, keeps the code cleaner */
argument|pixel_surround_init (&surround, float_tiles,
literal|1
argument|,
literal|1
argument|, bg_col);     }    width  = tile_manager_width (tiles);   height = tile_manager_height (tiles);   bytes  = tile_manager_bpp (tiles);    dest = g_new (guchar, width * bytes);    xinc = m[
literal|0
argument|][
literal|0
argument|];   yinc = m[
literal|1
argument|][
literal|0
argument|];   winc = m[
literal|2
argument|][
literal|0
argument|];
comment|/* these loops could be rearranged, depending on which bit of code    * you'd most like to write more than once.    */
argument|for (y = ty1; y< ty2; y++)     {       if (progress_callback&& !(y&
literal|0xf
argument|)) 	(* progress_callback) (ty1, ty2, y, progress_data);
comment|/* set up inverse transform steps */
argument|tx = xinc * tx1 + m[
literal|0
argument|][
literal|1
argument|] * y + m[
literal|0
argument|][
literal|2
argument|];       ty = yinc * tx1 + m[
literal|1
argument|][
literal|1
argument|] * y + m[
literal|1
argument|][
literal|2
argument|];       tw = winc * tx1 + m[
literal|2
argument|][
literal|1
argument|] * y + m[
literal|2
argument|][
literal|2
argument|];        d = dest;       for (x = tx1; x< tx2; x++) 	{
comment|/*  normalize homogeneous coords  */
argument|if (tw ==
literal|0.0
argument|) 	    { 	      g_warning (
literal|"homogeneous coordinate = 0...\n"
argument|); 	    } 	  else if (tw !=
literal|1.0
argument|) 	    { 	      ttx = tx / tw; 	      tty = ty / tw; 	    } 	  else 	    { 	      ttx = tx; 	      tty = ty; 	    }
comment|/*  Set the destination pixels  */
argument|if (interpolation)        	    {               if (interpolation_type == CUBIC_INTERPOLATION)        	        {
comment|/*  ttx& tty are the subpixel coordinates of the point in 		   *  the original selection's floating buffer. 		   *  We need the four integer pixel coords around them: 		   *  itx to itx + 3, ity to ity + 3                    */
argument|itx = floor (ttx);                   ity = floor (tty);
comment|/* check if any part of our region overlaps the buffer */
argument|if ((itx +
literal|2
argument|)>= x1&& (itx -
literal|1
argument|)< x2&&                       (ity +
literal|2
argument|)>= y1&& (ity -
literal|1
argument|)< y2 )                     {                       guchar  *data;                       gint     row;                       gdouble  dx
argument_list|,
argument|dy;                       guchar  *start;
comment|/* lock the pixel surround */
argument|data = pixel_surround_lock (&surround, 						  itx -
literal|1
argument|- x1, ity -
literal|1
argument|- y1);                        row = pixel_surround_rowstride (&surround);
comment|/* the fractional error */
argument|dx = ttx - itx;                       dy = tty - ity;
comment|/* calculate alpha of result */
argument|start =&data[alpha]; 		      a_val = cubic (dy, 				     CUBIC_ROW (dx, start, bytes), 				     CUBIC_ROW (dx, start + row, bytes), 				     CUBIC_ROW (dx, start + row + row, bytes), 				     CUBIC_ROW (dx, start + row + row + row, bytes));  		      if (a_val<=
literal|0.0
argument|) 			{ 			  a_recip =
literal|0.0
argument|; 			  d[alpha] =
literal|0
argument|; 			} 		      else if (a_val>
literal|255.0
argument|) 			{ 			  a_recip =
literal|1.0
argument|/ a_val; 			  d[alpha] =
literal|255
argument|; 			} 		      else 			{ 			  a_recip =
literal|1.0
argument|/ a_val; 			  d[alpha] = RINT(a_val); 			}
comment|/*  for colour channels c, 		       *  result = bicubic (c * alpha) / bicubic (alpha) 		       * 		       *  never entered for alpha == 0 		       */
argument|for (i = -alpha; i<
literal|0
argument|; ++i) 			{ 			  start =&data[alpha]; 			  newval = 			    RINT (a_recip * 				  cubic (dy, 					 CUBIC_SCALED_ROW (dx, start, bytes, i), 					 CUBIC_SCALED_ROW (dx, start + row, bytes, i), 					 CUBIC_SCALED_ROW (dx, start + row + row, bytes, i), 					 CUBIC_SCALED_ROW (dx, start + row + row + row, bytes, i))); 			  if (newval<=
literal|0
argument|) 			    { 			      *d++ =
literal|0
argument|; 			    } 			  else if (newval>
literal|255
argument|) 			    { 			      *d++ =
literal|255
argument|; 			    } 			  else 			    { 			      *d++ = newval; 			    } 			}
comment|/*  alpha already done  */
argument|d++;  		      pixel_surround_release (&surround); 		    }                   else
comment|/* not in source range */
argument|{
comment|/*  increment the destination pointers  */
argument|for (b =
literal|0
argument|; b< bytes; b++)                         *d++ = bg_col[b];                     }                 }         	      else
comment|/*  linear  */
argument|{                   itx = floor (ttx);                   ity = floor (tty);
comment|/*  expand source area to cover interpolation region 		   *  (which runs from itx to itx + 1, same in y) 		   */
argument|if ((itx +
literal|1
argument|)>= x1&& itx< x2&&                       (ity +
literal|1
argument|)>= y1&& ity< y2 )                     {                       guchar  *data;                       gint     row;                       double   dx
argument_list|,
argument|dy;                       guchar  *chan;
comment|/* lock the pixel surround */
argument|data = pixel_surround_lock (&surround, itx - x1, ity - y1);                        row = pixel_surround_rowstride (&surround);
comment|/* the fractional error */
argument|dx = ttx - itx;                       dy = tty - ity;
comment|/* calculate alpha value of result pixel */
argument|chan =&data[alpha]; 		      a_val = BILINEAR (chan[
literal|0
argument|], chan[bytes], chan[row], 					chan[row+bytes], dx, dy); 		      if (a_val<=
literal|0.0
argument|) 			{ 			  a_recip =
literal|0.0
argument|; 			  d[alpha] =
literal|0.0
argument|; 			} 		      else if (a_val>=
literal|255.0
argument|) 			{ 			  a_recip =
literal|1.0
argument|/ a_val; 			  d[alpha] =
literal|255
argument|; 			} 		      else 			{ 			  a_recip =
literal|1.0
argument|/ a_val; 			  d[alpha] = RINT (a_val); 			}
comment|/*  for colour channels c, 		       *  result = bilinear (c * alpha) / bilinear (alpha) 		       * 		       *  never entered for alpha == 0 		       */
argument|for (i = -alpha; i<
literal|0
argument|; ++i) 			{ 			  chan =&data[alpha]; 			  newval = 			    RINT (a_recip * 				  BILINEAR (chan[
literal|0
argument|] * chan[i], 					    chan[bytes] * chan[bytes+i], 					    chan[row] * chan[row+i], 					    chan[row+bytes] * chan[row+bytes+i], 					    dx, dy)); 			  if (newval<=
literal|0
argument|) 			    { 			      *d++ =
literal|0
argument|; 			    } 			  else if (newval>
literal|255
argument|) 			    { 			      *d++ =
literal|255
argument|; 			    } 			  else 			    { 			      *d++ = newval; 			    } 			}
comment|/*  alpha already done  */
argument|d++;                        pixel_surround_release (&surround); 		    }                    else
comment|/* not in source range */
argument|{
comment|/*  increment the destination pointers  */
argument|for (b =
literal|0
argument|; b< bytes; b++)                         *d++ = bg_col[b];                     } 		} 	    }           else
comment|/*  no interpolation  */
argument|{               itx = floor (ttx);               ity = floor (tty);                if (itx>= x1&& itx< x2&&                   ity>= y1&& ity< y2 )                 {
comment|/*  x, y coordinates into source tiles  */
argument|sx = itx - x1;                   sy = ity - y1;                    REF_TILE (
literal|0
argument|, sx, sy);                    for (b =
literal|0
argument|; b< bytes; b++)                     *d++ = src[
literal|0
argument|][b];                    tile_release (tile[
literal|0
argument|], FALSE); 		}               else
comment|/* not in source range */
argument|{
comment|/*  increment the destination pointers  */
argument|for (b =
literal|0
argument|; b< bytes; b++)                     *d++ = bg_col[b];                 } 	    }
comment|/*  increment the transformed coordinates  */
argument|tx += xinc; 	  ty += yinc; 	  tw += winc; 	}
comment|/*  set the pixel region row  */
argument|pixel_region_set_row (&destPR,
literal|0
argument|, (y - ty1), width, dest);     }    pixel_surround_clear (&surround);    g_free (dest);   return tiles; }  TileManager * gimp_transform_tool_cut (GImage       *gimage, 		    GimpDrawable *drawable, 		    gboolean     *new_layer) {   TileManager *tiles;
comment|/*  extract the selected mask if there is a selection  */
argument|if (! gimage_mask_is_empty (gimage))     {
comment|/* set the keep_indexed flag to FALSE here, since we use 	 gimp_layer_new_from_tiles() later which assumes that the tiles 	 are either RGB or GRAY.  Eeek!!!              (Sven)        */
argument|tiles = gimage_mask_extract (gimage, drawable, TRUE, FALSE, TRUE);       *new_layer = TRUE;     }
comment|/*  otherwise, just copy the layer  */
argument|else     {       if (GIMP_IS_LAYER (drawable)) 	tiles = gimage_mask_extract (gimage, drawable, FALSE, TRUE, TRUE);       else 	tiles = gimage_mask_extract (gimage, drawable, FALSE, TRUE, FALSE);       *new_layer = FALSE;     }    return tiles; }
comment|/*  Paste a transform to the gdisplay  */
argument|gboolean gimp_transform_tool_paste (GImage       *gimage, 		      GimpDrawable *drawable, 		      TileManager  *tiles, 		      gboolean      new_layer) {   GimpLayer   *layer   = NULL;   GimpChannel *channel = NULL;   GimpLayer   *floating_layer;    if (new_layer)     {       layer = 	gimp_layer_new_from_tiles (gimage, 				   gimp_drawable_type_with_alpha (drawable), 				   tiles, 				   _(
literal|"Transformation"
argument|), 				   OPAQUE_OPACITY, NORMAL_MODE);       if (! layer)         {           g_warning (
literal|"gimp_transform_tool_paste: gimp_layer_new_frome_tiles() failed"
argument|);           return FALSE;         }        tile_manager_get_offsets (tiles,&(GIMP_DRAWABLE (layer)->offset_x),&(GIMP_DRAWABLE (layer)->offset_y));
comment|/*  Start a group undo  */
argument|undo_push_group_start (gimage, EDIT_PASTE_UNDO);        floating_sel_attach (layer, drawable);
comment|/*  End the group undo  */
argument|undo_push_group_end (gimage);
comment|/*  Free the tiles  */
argument|tile_manager_destroy (tiles);        return TRUE;     }   else     {       if (GIMP_IS_LAYER (drawable)) 	layer = GIMP_LAYER (drawable);       else if (GIMP_IS_CHANNEL (drawable)) 	channel = GIMP_CHANNEL (drawable);       else 	return FALSE;        if (layer) 	gimp_layer_add_alpha (layer);        floating_layer = gimp_image_floating_sel (gimage);        if (floating_layer) 	floating_sel_relax (floating_layer, TRUE);        gdisplays_update_area (gimage, 			     drawable->offset_x, 			     drawable->offset_y, 			     drawable->width, 			     drawable->height);
comment|/*  Push an undo  */
argument|if (layer) 	undo_push_layer_mod (gimage, layer);       else if (channel) 	undo_push_channel_mod (gimage, channel);
comment|/*  set the current layer's data  */
argument|drawable->tiles = tiles;
comment|/*  Fill in the new layer's attributes  */
argument|drawable->width    = tile_manager_width (tiles);       drawable->height   = tile_manager_height (tiles);       drawable->bytes    = tile_manager_bpp (tiles);       tile_manager_get_offsets (tiles,&drawable->offset_x,&drawable->offset_y);        if (floating_layer) 	floating_sel_rigor (floating_layer, TRUE);        drawable_update (drawable,
literal|0
argument|,
literal|0
argument|, 		       gimp_drawable_width (drawable), 		       gimp_drawable_height (drawable));
comment|/*  if we were operating on the floating selection, then it's boundary         *  and previews need invalidating        */
argument|if (drawable == (GimpDrawable *) floating_layer) 	floating_sel_invalidate (floating_layer);        return TRUE;     } }
comment|/* Note: cubic function no longer clips result */
argument|static gdouble cubic (gdouble dx,        gint    jm1,        gint    j,        gint    jp1,        gint    jp2) {   gdouble result;
if|#
directive|if
literal|0
comment|/* Equivalent to Gimp 1.1.1 and earlier - some ringing */
argument|result = ((( ( - jm1 + j - jp1 + jp2 ) * dx +                ( jm1 + jm1 - j - j + jp1 - jp2 ) ) * dx +                ( - jm1 + jp1 ) ) * dx + j );
comment|/* Recommended by Mitchell and Netravali - too blurred? */
argument|result = ((( ( - 7 * jm1 + 21 * j - 21 * jp1 + 7 * jp2 ) * dx +                ( 15 * jm1 - 36 * j + 27 * jp1 - 6 * jp2 ) ) * dx +                ( - 9 * jm1 + 9 * jp1 ) ) * dx + (jm1 + 16 * j + jp1) ) / 18.0;
else|#
directive|else
comment|/* Catmull-Rom - not bad */
argument|result = ((( ( - jm1 +
literal|3
argument|* j -
literal|3
argument|* jp1 + jp2 ) * dx +                (
literal|2
argument|* jm1 -
literal|5
argument|* j +
literal|4
argument|* jp1 - jp2 ) ) * dx +                ( - jm1 + jp1 ) ) * dx + (j + j) ) /
literal|2.0
argument|;
endif|#
directive|endif
argument|return result; }
end_function

end_unit

