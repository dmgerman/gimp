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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<math.h>
end_include

begin_include
include|#
directive|include
file|"appenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushpixmap.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrushlist.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"errors.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gradient.h"
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
file|"palette.h"
end_include

begin_include
include|#
directive|include
file|"paintbrush.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"pixmapbrush.h"
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
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|pixmapbrush_motion
parameter_list|(
name|PaintCore
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/* static Argument *   pixmapbrush_invoker     (Argument *); */
end_comment

begin_comment
comment|/* static Argument *   pixmapbrush_extended_invoker     (Argument *); */
end_comment

begin_comment
comment|/* static Argument *   pixmapbrush_extended_gradient_invoker     (Argument *); */
end_comment

begin_function_decl
specifier|static
name|void
name|paint_line_pixmap_mask
parameter_list|(
name|GImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|,
name|unsigned
name|char
modifier|*
name|d
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|offset_x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|y2
parameter_list|,
name|int
name|bytes
parameter_list|,
name|int
name|width
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  defines  */
end_comment

begin_define
DECL|macro|PAINT_LEFT_THRESHOLD
define|#
directive|define
name|PAINT_LEFT_THRESHOLD
value|0.05
end_define

begin_typedef
DECL|typedef|PixmapPaintOptions
typedef|typedef
name|struct
name|_PixmapPaintOptions
name|PixmapPaintOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_PixmapPaintOptions
struct|struct
name|_PixmapPaintOptions
block|{
DECL|member|paint_options
name|PaintOptions
name|paint_options
decl_stmt|;
DECL|member|fade_out
name|double
name|fade_out
decl_stmt|;
DECL|member|gradient_length
name|double
name|gradient_length
decl_stmt|;
DECL|member|incremental
name|gboolean
name|incremental
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|pixmap_paint_options
specifier|static
name|PixmapPaintOptions
modifier|*
name|pixmap_paint_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|void
DECL|function|pixmapbrush_options_reset (void)
name|pixmapbrush_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|PixmapPaintOptions
modifier|*
name|options
init|=
name|pixmap_paint_options
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
block|}
end_function

begin_function
specifier|static
name|PixmapPaintOptions
modifier|*
DECL|function|pixmapbrush_options_new (void)
name|pixmapbrush_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|PixmapPaintOptions
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
comment|/*  the new options structure  */
name|options
operator|=
operator|(
name|PixmapPaintOptions
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|PixmapPaintOptions
argument_list|)
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
name|PIXMAPBRUSH
argument_list|,
name|pixmapbrush_options_reset
argument_list|)
expr_stmt|;
name|options
operator|->
name|fade_out
operator|=
literal|0.0
expr_stmt|;
name|options
operator|->
name|incremental
operator|=
name|FALSE
expr_stmt|;
name|options
operator|->
name|gradient_length
operator|=
literal|0.0
expr_stmt|;
comment|/*  the main vbox  */
comment|/*   vbox = gtk_vbox_new (FALSE, 1); */
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
comment|/*  the main label  */
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Pixmapbrush Options"
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
comment|/*  the fade-out scale  */
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
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
literal|"Fade Out"
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
return|return
name|options
return|;
block|}
end_function

begin_define
DECL|macro|USE_SPEEDSHOP_CALIPERS
define|#
directive|define
name|USE_SPEEDSHOP_CALIPERS
value|0
end_define

begin_define
DECL|macro|TIMED_BRUSH
define|#
directive|define
name|TIMED_BRUSH
value|0
end_define

begin_if
if|#
directive|if
name|USE_SPEEDSHOP_CALIPERS
end_if

begin_include
include|#
directive|include
file|<SpeedShop/api.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|void
modifier|*
DECL|function|pixmap_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|pixmap_paint_func
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
if|#
directive|if
name|TIMED_BRUSH
specifier|static
name|GTimer
modifier|*
name|timer
decl_stmt|;
endif|#
directive|endif
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|INIT_PAINT
case|:
if|#
directive|if
name|TIMED_BRUSH
name|timer
operator|=
name|g_timer_new
argument_list|()
expr_stmt|;
name|g_timer_start
argument_list|(
name|timer
argument_list|)
expr_stmt|;
if|#
directive|if
name|USE_SPEEDSHOP_CALIPERS
name|ssrt_caliper_point
argument_list|(
literal|0
argument_list|,
literal|"Painting"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SPEEDSHOP_CALIPERS */
endif|#
directive|endif
comment|/* TIMED_BRUSH */
break|break;
case|case
name|MOTION_PAINT
case|:
name|pixmapbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
break|break;
case|case
name|FINISH_PAINT
case|:
if|#
directive|if
name|TIMED_BRUSH
if|#
directive|if
name|USE_SPEEDSHOP_CALIPERS
name|ssrt_caliper_point
argument_list|(
literal|0
argument_list|,
literal|"Not Painting Anymore"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* USE_SPEEDSHOP_CALIPERS */
name|g_timer_stop
argument_list|(
name|timer
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"painting took %f:\n"
argument_list|,
name|g_timer_elapsed
argument_list|(
name|timer
argument_list|,
name|NULL
argument_list|)
argument_list|)
expr_stmt|;
name|g_timer_destroy
argument_list|(
name|timer
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/* TIMED_BRUSH */
break|break;
default|default :
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
DECL|function|tools_new_pixmapbrush ()
name|tools_new_pixmapbrush
parameter_list|()
block|{
name|Tool
modifier|*
name|tool
decl_stmt|;
name|PaintCore
modifier|*
name|private
decl_stmt|;
if|if
condition|(
operator|!
name|pixmap_paint_options
condition|)
block|{
name|pixmap_paint_options
operator|=
name|pixmapbrush_options_new
argument_list|()
expr_stmt|;
name|tools_register
argument_list|(
name|PIXMAPBRUSH
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|pixmap_paint_options
argument_list|)
expr_stmt|;
name|pixmapbrush_options_reset
argument_list|()
expr_stmt|;
block|}
name|tool
operator|=
name|paint_core_new
argument_list|(
name|PIXMAPBRUSH
argument_list|)
expr_stmt|;
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
name|pixmap_paint_func
expr_stmt|;
return|return
name|tool
return|;
block|}
end_function

begin_function
name|void
DECL|function|tools_free_pixmapbrush (Tool * tool)
name|tools_free_pixmapbrush
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
DECL|function|pixmapbrush_motion (PaintCore * paint_core,GimpDrawable * drawable)
name|pixmapbrush_motion
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
name|GimpBrushPixmap
modifier|*
name|brush
init|=
literal|0
decl_stmt|;
name|TempBuf
modifier|*
name|pixmap_data
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|double
name|position
decl_stmt|;
name|unsigned
name|char
modifier|*
name|d
decl_stmt|;
name|int
name|y
decl_stmt|;
comment|/*  unsigned char col[MAX_CHANNELS]; */
name|void
modifier|*
name|pr
decl_stmt|;
name|PixelRegion
name|destPR
decl_stmt|;
name|int
name|opacity
decl_stmt|;
name|int
name|offset_x
init|=
literal|0
decl_stmt|;
name|int
name|offset_y
init|=
literal|0
decl_stmt|;
name|pr
operator|=
name|NULL
expr_stmt|;
comment|/* FIXME: this code doesnt work quite right at the far top and      and left sides. need to handle those cases better */
comment|/* if we dont get a pixmap brush, aieeee!  */
comment|/* FIXME */
if|if
condition|(
operator|!
operator|(
name|GIMP_IS_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
operator|)
condition|)
return|return;
name|brush
operator|=
name|GIMP_BRUSH_PIXMAP
argument_list|(
name|paint_core
operator|->
name|brush
argument_list|)
expr_stmt|;
name|pixmap_data
operator|=
name|gimp_brush_pixmap_get_pixmap
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|position
operator|=
literal|0.0
expr_stmt|;
comment|/*  We always need a destination image */
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
comment|/*  Get a region which can be used to p\\aint to  */
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
argument_list|)
operator|)
condition|)
return|return;
comment|/* stolen from clone.c */
comment|/* this should be a similar thing to want to do, right? */
comment|/* if I understand correctly, this just initilizes the dest      pixel region to the same bitdepth, height and width of      the drawable (area), then copies the apprriate data      from area to destPR.data */
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
name|destPR
operator|.
name|bytes
operator|*
name|area
operator|->
name|width
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
comment|/* register this pixel region */
name|pr
operator|=
name|pixel_regions_register
argument_list|(
literal|1
argument_list|,
operator|&
name|destPR
argument_list|)
expr_stmt|;
for|for
control|(
init|;
name|pr
operator|!=
name|NULL
condition|;
name|pr
operator|=
name|pixel_regions_process
argument_list|(
name|pr
argument_list|)
control|)
block|{
name|d
operator|=
name|destPR
operator|.
name|data
expr_stmt|;
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<
name|destPR
operator|.
name|h
condition|;
name|y
operator|++
control|)
block|{
comment|/* 	  printf(" brush->width: %i offset_x: %i", brush->pixmap_mask->width, offset_x); */
comment|/* 	  printf(" area->y: %i destPR.h: %i area->x: %i destPR.w: %i ",area->y, destPR.h, area->x, destPR.w);  */
name|paint_line_pixmap_mask
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|brush
argument_list|,
name|d
argument_list|,
name|area
operator|->
name|x
argument_list|,
name|offset_x
argument_list|,
name|area
operator|->
name|y
argument_list|,
name|y
argument_list|,
name|destPR
operator|.
name|bytes
argument_list|,
name|destPR
operator|.
name|w
argument_list|)
expr_stmt|;
name|d
operator|+=
name|destPR
operator|.
name|rowstride
expr_stmt|;
block|}
block|}
comment|/*          printf("temp_blend: %u grad_len: %f distance: %f \n",temp_blend, gradient_length, distance); */
comment|/* remove these once things are stable */
comment|/* printf("opacity: %i ", (int) (gimp_context_get_opacity (NULL) * 255)); */
comment|/*    printf("r: %i g: %i b: %i a: %i\n", col[0], col[1], col[2], col[3]); */
comment|/* steal the pressure sensiteive code from clone.c */
name|opacity
operator|=
literal|255
operator|*
name|gimp_context_get_opacity
argument_list|(
name|NULL
argument_list|)
operator|*
operator|(
name|paint_core
operator|->
name|curpressure
operator|/
literal|0.5
operator|)
expr_stmt|;
if|if
condition|(
name|opacity
operator|>
literal|255
condition|)
name|opacity
operator|=
literal|255
expr_stmt|;
name|paint_core_paste_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|opacity
argument_list|,
call|(
name|int
call|)
argument_list|(
name|gimp_context_get_opacity
argument_list|(
name|NULL
argument_list|)
operator|*
literal|255
argument_list|)
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|NULL
argument_list|)
argument_list|,
name|SOFT
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
DECL|function|pixmapbrush_non_gui_paint_func (PaintCore * paint_core,GimpDrawable * drawable,int state)
name|pixmapbrush_non_gui_paint_func
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
name|pixmapbrush_motion
argument_list|(
name|paint_core
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
specifier|static
name|void
DECL|function|paint_line_pixmap_mask (GImage * dest,GimpDrawable * drawable,GimpBrushPixmap * brush,unsigned char * d,int x,int offset_x,int y,int y2,int bytes,int width)
name|paint_line_pixmap_mask
parameter_list|(
name|GImage
modifier|*
name|dest
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpBrushPixmap
modifier|*
name|brush
parameter_list|,
name|unsigned
name|char
modifier|*
name|d
parameter_list|,
name|int
name|x
parameter_list|,
name|int
name|offset_x
parameter_list|,
name|int
name|y
parameter_list|,
name|int
name|y2
parameter_list|,
name|int
name|bytes
parameter_list|,
name|int
name|width
parameter_list|)
block|{
name|unsigned
name|char
modifier|*
name|pat
decl_stmt|,
modifier|*
name|p
decl_stmt|;
name|int
name|color
decl_stmt|,
name|alpha
decl_stmt|;
name|int
name|i
decl_stmt|;
comment|/*  Make sure x, y are positive  */
while|while
condition|(
name|x
operator|<
literal|0
condition|)
name|x
operator|+=
name|brush
operator|->
name|pixmap_mask
operator|->
name|width
expr_stmt|;
while|while
condition|(
name|y
operator|<
literal|0
condition|)
name|y
operator|+=
name|brush
operator|->
name|pixmap_mask
operator|->
name|height
expr_stmt|;
comment|/* point to the approriate scanline */
comment|/* use "pat" here because i'm c&p from pattern clone */
name|pat
operator|=
name|temp_buf_data
argument_list|(
name|brush
operator|->
name|pixmap_mask
argument_list|)
operator|+
operator|(
name|y2
operator|*
name|brush
operator|->
name|pixmap_mask
operator|->
name|width
operator|*
name|brush
operator|->
name|pixmap_mask
operator|->
name|bytes
operator|)
expr_stmt|;
comment|/*   dest = d +  (y * brush->pixmap_mask->width * brush->pixmap_mask->bytes); */
name|color
operator|=
name|RGB
expr_stmt|;
name|alpha
operator|=
name|bytes
operator|-
literal|1
expr_stmt|;
comment|/*  printf("x: %i y: %i y2: %i   \n",x,y,y2); */
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|width
condition|;
name|i
operator|++
control|)
block|{
name|p
operator|=
name|pat
operator|+
operator|(
operator|(
name|i
operator|+
name|offset_x
operator|)
operator|%
name|brush
operator|->
name|pixmap_mask
operator|->
name|width
operator|)
operator|*
name|brush
operator|->
name|pixmap_mask
operator|->
name|bytes
expr_stmt|;
comment|/* printf("d->r: %i d->g: %i d->b: %i d->a: %i\n",(int)d[0], (int)d[1], (int)d[2], (int)d[3]); */
name|gimage_transform_color
argument_list|(
name|dest
argument_list|,
name|drawable
argument_list|,
name|p
argument_list|,
name|d
argument_list|,
name|color
argument_list|)
expr_stmt|;
name|d
index|[
name|alpha
index|]
operator|=
literal|255
expr_stmt|;
name|d
operator|+=
name|bytes
expr_stmt|;
block|}
block|}
end_function

end_unit

