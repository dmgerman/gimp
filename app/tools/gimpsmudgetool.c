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
file|<gdk/gdkkeysyms.h>
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"smudge.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimplut.h"
end_include

begin_include
include|#
directive|include
file|"gimpui.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"paint_core.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
end_include

begin_include
include|#
directive|include
file|"tools.h"
end_include

begin_include
include|#
directive|include
file|"gimage.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/* default defines */
end_comment

begin_define
DECL|macro|SMUDGE_DEFAULT_RATE
define|#
directive|define
name|SMUDGE_DEFAULT_RATE
value|50.0
end_define

begin_comment
comment|/*  the smudge structures  */
end_comment

begin_typedef
DECL|typedef|SmudgeOptions
typedef|typedef
name|struct
name|_SmudgeOptions
name|SmudgeOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_SmudgeOptions
struct|struct
name|_SmudgeOptions
block|{
DECL|member|paint_options
name|PaintOptions
name|paint_options
decl_stmt|;
DECL|member|rate
name|gdouble
name|rate
decl_stmt|;
DECL|member|rate_d
name|gdouble
name|rate_d
decl_stmt|;
DECL|member|rate_w
name|GtkObject
modifier|*
name|rate_w
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
DECL|variable|accumPR
specifier|static
name|PixelRegion
name|accumPR
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|accum_data
specifier|static
name|guchar
modifier|*
name|accum_data
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  the smudge tool options  */
end_comment

begin_decl_stmt
DECL|variable|smudge_options
specifier|static
name|SmudgeOptions
modifier|*
name|smudge_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local variables */
end_comment

begin_decl_stmt
DECL|variable|non_gui_rate
specifier|static
name|gdouble
name|non_gui_rate
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  function prototypes */
end_comment

begin_function_decl
specifier|static
name|void
name|smudge_motion
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|PaintPressureOptions
modifier|*
parameter_list|,
name|gdouble
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|smudge_init
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|smudge_finish
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|smudge_nonclipped_painthit_coords
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|w
parameter_list|,
name|gint
modifier|*
name|h
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|smudge_allocate_accum_buffer
parameter_list|(
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|guchar
modifier|*
name|do_fill
parameter_list|)
function_decl|;
end_function_decl

begin_function
specifier|static
name|void
DECL|function|smudge_options_reset (void)
name|smudge_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|SmudgeOptions
modifier|*
name|options
init|=
name|smudge_options
decl_stmt|;
name|paint_options_reset
argument_list|(
operator|(
name|PaintOptions
operator|*
operator|)
name|options
argument_list|)
expr_stmt|;
name|gtk_adjustment_set_value
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|rate_w
argument_list|)
argument_list|,
name|options
operator|->
name|rate_d
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|SmudgeOptions
modifier|*
DECL|function|smudge_options_new (void)
name|smudge_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|SmudgeOptions
modifier|*
name|options
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
comment|/*  the new smudge tool options structure  */
name|options
operator|=
name|g_new
argument_list|(
name|SmudgeOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|paint_options_init
argument_list|(
operator|(
name|PaintOptions
operator|*
operator|)
name|options
argument_list|,
name|SMUDGE
argument_list|,
name|smudge_options_reset
argument_list|)
expr_stmt|;
name|options
operator|->
name|rate
operator|=
name|options
operator|->
name|rate_d
operator|=
name|SMUDGE_DEFAULT_RATE
expr_stmt|;
comment|/*  the main vbox  */
name|vbox
operator|=
operator|(
operator|(
name|ToolOptions
operator|*
operator|)
name|options
operator|)
operator|->
name|main_vbox
expr_stmt|;
comment|/*  the rate scale  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Rate:"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_misc_set_alignment
argument_list|(
name|GTK_MISC
argument_list|(
name|label
argument_list|)
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
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
name|options
operator|->
name|rate_w
operator|=
name|gtk_adjustment_new
argument_list|(
name|options
operator|->
name|rate_d
argument_list|,
literal|0.0
argument_list|,
literal|100.0
argument_list|,
literal|1.0
argument_list|,
literal|1.0
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|options
operator|->
name|rate_w
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|scale
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_scale_set_value_pos
argument_list|(
name|GTK_SCALE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_POS_TOP
argument_list|)
expr_stmt|;
name|gtk_range_set_update_policy
argument_list|(
name|GTK_RANGE
argument_list|(
name|scale
argument_list|)
argument_list|,
name|GTK_UPDATE_DELAYED
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|options
operator|->
name|rate_w
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_double_adjustment_update
argument_list|)
argument_list|,
operator|&
name|options
operator|->
name|rate
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_function
name|void
modifier|*
DECL|function|smudge_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|smudge_paint_func
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|state
parameter_list|)
block|{
comment|/* initialization fails if the user starts outside the drawable */
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|MOTION_PAINT
case|:
if|if
condition|(
operator|!
name|initialized
condition|)
name|initialized
operator|=
name|smudge_init
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
if|if
condition|(
name|initialized
condition|)
name|smudge_motion
argument_list|(
name|paint_core
argument_list|,
name|smudge_options
operator|->
name|paint_options
operator|.
name|pressure_options
argument_list|,
name|smudge_options
operator|->
name|rate
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|FINISH_PAINT
case|:
name|smudge_finish
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|initialized
operator|=
name|FALSE
expr_stmt|;
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
DECL|function|smudge_finish (PaintCore * paint_core,GimpDrawable * drawable)
name|smudge_finish
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
if|if
condition|(
name|accum_data
condition|)
block|{
name|g_free
argument_list|(
name|accum_data
argument_list|)
expr_stmt|;
name|accum_data
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|smudge_nonclipped_painthit_coords (PaintCore * paint_core,gint * x,gint * y,gint * w,gint * h)
name|smudge_nonclipped_painthit_coords
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|gint
modifier|*
name|x
parameter_list|,
name|gint
modifier|*
name|y
parameter_list|,
name|gint
modifier|*
name|w
parameter_list|,
name|gint
modifier|*
name|h
parameter_list|)
block|{
comment|/* Note: these are the brush mask size plus a border of 1 pixel */
operator|*
name|x
operator|=
operator|(
name|gint
operator|)
name|paint_core
operator|->
name|curx
operator|-
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|width
operator|/
literal|2
operator|-
literal|1
expr_stmt|;
operator|*
name|y
operator|=
operator|(
name|gint
operator|)
name|paint_core
operator|->
name|cury
operator|-
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|height
operator|/
literal|2
operator|-
literal|1
expr_stmt|;
operator|*
name|w
operator|=
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|width
operator|+
literal|2
expr_stmt|;
operator|*
name|h
operator|=
name|paint_core
operator|->
name|brush
operator|->
name|mask
operator|->
name|height
operator|+
literal|2
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|smudge_init (PaintCore * paint_core,GimpDrawable * drawable)
name|smudge_init
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
name|gint
name|was_clipped
decl_stmt|;
name|guchar
modifier|*
name|do_fill
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return
name|FALSE
return|;
comment|/*  If the image type is indexed, don't smudge  */
if|if
condition|(
operator|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXED_GIMAGE
operator|)
operator|||
operator|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXEDA_GIMAGE
operator|)
condition|)
return|return
name|FALSE
return|;
name|area
operator|=
name|paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|area
condition|)
return|return
name|FALSE
return|;
comment|/*  adjust the x and y coordinates to the upper left corner of the brush  */
name|smudge_nonclipped_painthit_coords
argument_list|(
name|paint_core
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
if|if
condition|(
name|x
operator|!=
name|area
operator|->
name|x
operator|||
name|y
operator|!=
name|area
operator|->
name|y
operator|||
name|w
operator|!=
name|area
operator|->
name|width
operator|||
name|h
operator|!=
name|area
operator|->
name|height
condition|)
name|was_clipped
operator|=
name|TRUE
expr_stmt|;
else|else
name|was_clipped
operator|=
name|FALSE
expr_stmt|;
comment|/* When clipped, accum_data may contain pixels that map to      off-canvas pixels of the under-the-brush image, particulary      when the brush image contains an edge or corner of the      image. These off-canvas pixels are not a part of the current      composite, but may be composited in later generations. do_fill      contains a copy of the color of the pixel at the center of the      brush; assumed this is a reasonable choice for off- canvas pixels      that may enter into the blend */
if|if
condition|(
name|was_clipped
condition|)
name|do_fill
operator|=
name|gimp_drawable_get_color_at
argument_list|(
name|drawable
argument_list|,
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|paint_core
operator|->
name|curx
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_width
argument_list|(
name|drawable
argument_list|)
operator|-
literal|1
argument_list|)
argument_list|,
name|CLAMP
argument_list|(
operator|(
name|gint
operator|)
name|paint_core
operator|->
name|cury
argument_list|,
literal|0
argument_list|,
name|gimp_drawable_height
argument_list|(
name|drawable
argument_list|)
operator|-
literal|1
argument_list|)
argument_list|)
expr_stmt|;
name|smudge_allocate_accum_buffer
argument_list|(
name|w
argument_list|,
name|h
argument_list|,
name|gimp_drawable_bytes
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|do_fill
argument_list|)
expr_stmt|;
name|accumPR
operator|.
name|x
operator|=
name|area
operator|->
name|x
operator|-
name|x
expr_stmt|;
name|accumPR
operator|.
name|y
operator|=
name|area
operator|->
name|y
operator|-
name|y
expr_stmt|;
name|accumPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|accumPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|accumPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|bytes
operator|*
name|w
expr_stmt|;
name|accumPR
operator|.
name|data
operator|=
name|accum_data
operator|+
name|accumPR
operator|.
name|rowstride
operator|*
name|accumPR
operator|.
name|y
operator|+
name|accumPR
operator|.
name|x
operator|*
name|accumPR
operator|.
name|bytes
expr_stmt|;
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|area
operator|->
name|x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* copy the region under the original painthit. */
name|copy_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|accumPR
argument_list|)
expr_stmt|;
name|accumPR
operator|.
name|x
operator|=
name|area
operator|->
name|x
operator|-
name|x
expr_stmt|;
name|accumPR
operator|.
name|y
operator|=
name|area
operator|->
name|y
operator|-
name|y
expr_stmt|;
name|accumPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|accumPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|accumPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|bytes
operator|*
name|w
expr_stmt|;
name|accumPR
operator|.
name|data
operator|=
name|accum_data
operator|+
name|accumPR
operator|.
name|rowstride
operator|*
name|accumPR
operator|.
name|y
operator|+
name|accumPR
operator|.
name|x
operator|*
name|accumPR
operator|.
name|bytes
expr_stmt|;
if|if
condition|(
name|do_fill
condition|)
name|g_free
argument_list|(
name|do_fill
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|smudge_allocate_accum_buffer (gint w,gint h,gint bytes,guchar * do_fill)
name|smudge_allocate_accum_buffer
parameter_list|(
name|gint
name|w
parameter_list|,
name|gint
name|h
parameter_list|,
name|gint
name|bytes
parameter_list|,
name|guchar
modifier|*
name|do_fill
parameter_list|)
block|{
comment|/*  Allocate the accumulation buffer */
name|accumPR
operator|.
name|bytes
operator|=
name|bytes
expr_stmt|;
name|accum_data
operator|=
name|g_malloc
argument_list|(
name|w
operator|*
name|h
operator|*
name|bytes
argument_list|)
expr_stmt|;
if|if
condition|(
name|do_fill
operator|!=
name|NULL
condition|)
block|{
comment|/* guchar color[3] = {0,0,0}; */
name|accumPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|accumPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|accumPR
operator|.
name|w
operator|=
name|w
expr_stmt|;
name|accumPR
operator|.
name|h
operator|=
name|h
expr_stmt|;
name|accumPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|bytes
operator|*
name|w
expr_stmt|;
name|accumPR
operator|.
name|data
operator|=
name|accum_data
expr_stmt|;
name|color_region
argument_list|(
operator|&
name|accumPR
argument_list|,
operator|(
specifier|const
name|guchar
operator|*
operator|)
name|do_fill
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|Tool
modifier|*
DECL|function|tools_new_smudge (void)
name|tools_new_smudge
parameter_list|(
name|void
parameter_list|)
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|PaintCore
modifier|*
name|private
decl_stmt|;
comment|/*  The tool options  */
if|if
condition|(
operator|!
name|smudge_options
condition|)
block|{
name|smudge_options
operator|=
name|smudge_options_new
argument_list|()
expr_stmt|;
name|tools_register
argument_list|(
name|SMUDGE
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|smudge_options
argument_list|)
expr_stmt|;
comment|/*  press all default buttons  */
name|smudge_options_reset
argument_list|()
expr_stmt|;
block|}
name|tool
operator|=
name|paint_core_new
argument_list|(
name|SMUDGE
argument_list|)
expr_stmt|;
comment|/*tool->modifier_key_func = smudge_modifier_key_func;*/
name|private
operator|=
operator|(
name|PaintCore
operator|*
operator|)
name|tool
operator|->
name|private
expr_stmt|;
name|private
operator|->
name|paint_func
operator|=
name|smudge_paint_func
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_smudge (Tool * tool)
name|tools_free_smudge
parameter_list|(
name|Tool
modifier|*
name|tool
parameter_list|)
block|{
name|paint_core_free
argument_list|(
name|tool
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|smudge_motion (PaintCore * paint_core,PaintPressureOptions * pressure_options,gdouble smudge_rate,GimpDrawable * drawable)
name|smudge_motion
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|PaintPressureOptions
modifier|*
name|pressure_options
parameter_list|,
name|gdouble
name|smudge_rate
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|)
block|{
name|GImage
modifier|*
name|gimage
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|PixelRegion
name|srcPR
decl_stmt|,
name|destPR
decl_stmt|,
name|tempPR
decl_stmt|;
name|gdouble
name|rate
decl_stmt|;
name|gint
name|opacity
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|,
name|w
decl_stmt|,
name|h
decl_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
comment|/*  If the image type is indexed, don't smudge  */
if|if
condition|(
operator|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXED_GIMAGE
operator|)
operator|||
operator|(
name|drawable_type
argument_list|(
name|drawable
argument_list|)
operator|==
name|INDEXEDA_GIMAGE
operator|)
condition|)
return|return;
name|smudge_nonclipped_painthit_coords
argument_list|(
name|paint_core
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|,
operator|&
name|w
argument_list|,
operator|&
name|h
argument_list|)
expr_stmt|;
comment|/*  Get the paint area */
comment|/*  Smudge won't scale!  */
if|if
condition|(
operator|!
operator|(
name|area
operator|=
name|paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
literal|1.0
argument_list|)
operator|)
condition|)
return|return;
comment|/* srcPR will be the pixels under the current painthit from       the drawable*/
name|pixel_region_init
argument_list|(
operator|&
name|srcPR
argument_list|,
name|drawable_data
argument_list|(
name|drawable
argument_list|)
argument_list|,
name|area
operator|->
name|x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|area
operator|->
name|width
argument_list|,
name|area
operator|->
name|height
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
comment|/* Enable pressure sensitive rate */
if|if
condition|(
name|pressure_options
operator|->
name|rate
condition|)
name|rate
operator|=
name|MIN
argument_list|(
name|smudge_rate
operator|/
literal|100.0
operator|*
name|paint_core
operator|->
name|curpressure
operator|*
literal|2.0
argument_list|,
literal|1.0
argument_list|)
expr_stmt|;
else|else
name|rate
operator|=
name|smudge_rate
operator|/
literal|100.0
expr_stmt|;
comment|/* The tempPR will be the built up buffer (for smudge) */
name|tempPR
operator|.
name|bytes
operator|=
name|accumPR
operator|.
name|bytes
expr_stmt|;
name|tempPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|rowstride
expr_stmt|;
name|tempPR
operator|.
name|x
operator|=
name|area
operator|->
name|x
operator|-
name|x
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
name|area
operator|->
name|y
operator|-
name|y
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|accum_data
operator|+
name|tempPR
operator|.
name|rowstride
operator|*
name|tempPR
operator|.
name|y
operator|+
name|tempPR
operator|.
name|x
operator|*
name|tempPR
operator|.
name|bytes
expr_stmt|;
comment|/* The dest will be the paint area we got above (= canvas_buf) */
name|destPR
operator|.
name|bytes
operator|=
name|area
operator|->
name|bytes
expr_stmt|;
name|destPR
operator|.
name|x
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|y
operator|=
literal|0
expr_stmt|;
name|destPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|destPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|destPR
operator|.
name|rowstride
operator|=
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|bytes
expr_stmt|;
name|destPR
operator|.
name|data
operator|=
name|temp_buf_data
argument_list|(
name|area
argument_list|)
expr_stmt|;
comment|/*        Smudge uses the buffer Accum.      For each successive painthit Accum is built like this 	Accum =  rate*Accum  + (1-rate)*I.      where I is the pixels under the current painthit.       Then the paint area (canvas_buf) is built as  	(Accum,1) (if no alpha),   */
name|blend_region
argument_list|(
operator|&
name|srcPR
argument_list|,
operator|&
name|tempPR
argument_list|,
operator|&
name|tempPR
argument_list|,
name|ROUND
argument_list|(
name|rate
operator|*
literal|255.0
argument_list|)
argument_list|)
expr_stmt|;
comment|/* re-init the tempPR */
name|tempPR
operator|.
name|bytes
operator|=
name|accumPR
operator|.
name|bytes
expr_stmt|;
name|tempPR
operator|.
name|rowstride
operator|=
name|accumPR
operator|.
name|rowstride
expr_stmt|;
name|tempPR
operator|.
name|x
operator|=
name|area
operator|->
name|x
operator|-
name|x
expr_stmt|;
name|tempPR
operator|.
name|y
operator|=
name|area
operator|->
name|y
operator|-
name|y
expr_stmt|;
name|tempPR
operator|.
name|w
operator|=
name|area
operator|->
name|width
expr_stmt|;
name|tempPR
operator|.
name|h
operator|=
name|area
operator|->
name|height
expr_stmt|;
name|tempPR
operator|.
name|data
operator|=
name|accum_data
operator|+
name|tempPR
operator|.
name|rowstride
operator|*
name|tempPR
operator|.
name|y
operator|+
name|tempPR
operator|.
name|x
operator|*
name|tempPR
operator|.
name|bytes
expr_stmt|;
if|if
condition|(
operator|!
name|drawable_has_alpha
argument_list|(
name|drawable
argument_list|)
condition|)
name|add_alpha_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
else|else
name|copy_region
argument_list|(
operator|&
name|tempPR
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
name|opacity
operator|=
literal|255
operator|*
name|gimp_context_get_opacity
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|pressure_options
operator|->
name|opacity
condition|)
name|opacity
operator|=
name|opacity
operator|*
literal|2.0
operator|*
name|paint_core
operator|->
name|curpressure
expr_stmt|;
comment|/*Replace the newly made paint area to the gimage*/
name|paint_core_replace_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|MIN
argument_list|(
name|opacity
argument_list|,
literal|255
argument_list|)
argument_list|,
name|OPAQUE_OPACITY
argument_list|,
name|pressure_options
operator|->
name|pressure
condition|?
name|PRESSURE
else|:
name|SOFT
argument_list|,
literal|1.0
argument_list|,
name|INCREMENTAL
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
modifier|*
DECL|function|smudge_non_gui_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|smudge_non_gui_paint_func
parameter_list|(
name|PaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|state
parameter_list|)
block|{
name|smudge_motion
argument_list|(
name|paint_core
argument_list|,
operator|&
name|non_gui_pressure_options
argument_list|,
name|non_gui_rate
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|smudge_non_gui_default (GimpDrawable * drawable,int num_strokes,double * stroke_array)
name|smudge_non_gui_default
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|int
name|num_strokes
parameter_list|,
name|double
modifier|*
name|stroke_array
parameter_list|)
block|{
name|gdouble
name|rate
init|=
name|SMUDGE_DEFAULT_RATE
decl_stmt|;
name|SmudgeOptions
modifier|*
name|options
init|=
name|smudge_options
decl_stmt|;
if|if
condition|(
name|options
condition|)
name|rate
operator|=
name|options
operator|->
name|rate
expr_stmt|;
return|return
name|smudge_non_gui
argument_list|(
name|drawable
argument_list|,
name|rate
argument_list|,
name|num_strokes
argument_list|,
name|stroke_array
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|smudge_non_gui (GimpDrawable * drawable,gdouble rate,int num_strokes,double * stroke_array)
name|smudge_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gdouble
name|rate
parameter_list|,
name|int
name|num_strokes
parameter_list|,
name|double
modifier|*
name|stroke_array
parameter_list|)
block|{
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|paint_core_init
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
name|stroke_array
index|[
literal|0
index|]
argument_list|,
name|stroke_array
index|[
literal|1
index|]
argument_list|)
condition|)
block|{
name|smudge_init
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
comment|/* Set the paint core's paint func */
name|non_gui_paint_core
operator|.
name|paint_func
operator|=
name|smudge_non_gui_paint_func
expr_stmt|;
name|non_gui_rate
operator|=
name|rate
expr_stmt|;
name|non_gui_paint_core
operator|.
name|curx
operator|=
name|non_gui_paint_core
operator|.
name|startx
operator|=
name|non_gui_paint_core
operator|.
name|lastx
operator|=
name|stroke_array
index|[
literal|0
index|]
expr_stmt|;
name|non_gui_paint_core
operator|.
name|cury
operator|=
name|non_gui_paint_core
operator|.
name|starty
operator|=
name|non_gui_paint_core
operator|.
name|lasty
operator|=
name|stroke_array
index|[
literal|1
index|]
expr_stmt|;
name|smudge_non_gui_paint_func
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|num_strokes
condition|;
name|i
operator|++
control|)
block|{
name|non_gui_paint_core
operator|.
name|curx
operator|=
name|stroke_array
index|[
name|i
operator|*
literal|2
operator|+
literal|0
index|]
expr_stmt|;
name|non_gui_paint_core
operator|.
name|cury
operator|=
name|stroke_array
index|[
name|i
operator|*
literal|2
operator|+
literal|1
index|]
expr_stmt|;
name|paint_core_interpolate
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|non_gui_paint_core
operator|.
name|lastx
operator|=
name|non_gui_paint_core
operator|.
name|curx
expr_stmt|;
name|non_gui_paint_core
operator|.
name|lasty
operator|=
name|non_gui_paint_core
operator|.
name|cury
expr_stmt|;
block|}
comment|/* Finish the painting */
name|paint_core_finish
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
comment|/* Cleanup */
name|paint_core_cleanup
argument_list|()
expr_stmt|;
name|smudge_finish
argument_list|(
operator|&
name|non_gui_paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
return|return
name|FALSE
return|;
block|}
end_function

end_unit

