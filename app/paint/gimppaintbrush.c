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
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"drawable.h"
end_include

begin_include
include|#
directive|include
file|"gdisplay.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"paint_funcs.h"
end_include

begin_include
include|#
directive|include
file|"selection.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimppainttool.h"
end_include

begin_include
include|#
directive|include
file|"paint_options.h"
end_include

begin_include
include|#
directive|include
file|"tools/gimppaintbrushtool.h"
end_include

begin_include
include|#
directive|include
file|"tool_options.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"pixmaps2.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

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

begin_comment
comment|/* defaults for the tool options */
end_comment

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_INCREMENTAL
define|#
directive|define
name|PAINTBRUSH_DEFAULT_INCREMENTAL
value|FALSE
end_define

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_USE_FADE
define|#
directive|define
name|PAINTBRUSH_DEFAULT_USE_FADE
value|FALSE
end_define

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_FADE_OUT
define|#
directive|define
name|PAINTBRUSH_DEFAULT_FADE_OUT
value|100.0
end_define

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_FADE_UNIT
define|#
directive|define
name|PAINTBRUSH_DEFAULT_FADE_UNIT
value|GIMP_UNIT_PIXEL
end_define

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_USE_GRADIENT
define|#
directive|define
name|PAINTBRUSH_DEFAULT_USE_GRADIENT
value|FALSE
end_define

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_GRADIENT_LENGTH
define|#
directive|define
name|PAINTBRUSH_DEFAULT_GRADIENT_LENGTH
value|100.0
end_define

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_GRADIENT_UNIT
define|#
directive|define
name|PAINTBRUSH_DEFAULT_GRADIENT_UNIT
value|GIMP_UNIT_PIXEL
end_define

begin_define
DECL|macro|PAINTBRUSH_DEFAULT_GRADIENT_TYPE
define|#
directive|define
name|PAINTBRUSH_DEFAULT_GRADIENT_TYPE
value|LOOP_TRIANGLE
end_define

begin_comment
comment|/*  the paintbrush structures  */
end_comment

begin_typedef
DECL|typedef|PaintbrushOptions
typedef|typedef
name|struct
name|_PaintbrushOptions
name|PaintbrushOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_PaintbrushOptions
struct|struct
name|_PaintbrushOptions
block|{
DECL|member|paint_options
name|PaintOptions
name|paint_options
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  the paint brush tool options  */
end_comment

begin_decl_stmt
DECL|variable|paintbrush_options
specifier|static
name|PaintbrushOptions
modifier|*
name|paintbrush_options
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  local variables  */
end_comment

begin_decl_stmt
DECL|variable|non_gui_incremental
specifier|static
name|gdouble
name|non_gui_incremental
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintToolClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  forward function declarations  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_tool_motion
parameter_list|(
name|GimpPaintTool
modifier|*
parameter_list|,
name|GimpDrawable
modifier|*
parameter_list|,
name|PaintPressureOptions
modifier|*
parameter_list|,
name|PaintGradientOptions
modifier|*
parameter_list|,
name|gdouble
parameter_list|,
name|gdouble
parameter_list|,
name|PaintApplicationMode
parameter_list|,
name|GradientPaintMode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_tool_paint
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PaintState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_tool_class_init
parameter_list|(
name|GimpPaintbrushToolClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_paintbrush_tool_init
parameter_list|(
name|GimpPaintbrushTool
modifier|*
name|tool
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  functions  */
end_comment

begin_function
name|GtkType
DECL|function|gimp_paintbrush_tool_get_type (void)
name|gimp_paintbrush_tool_get_type
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
literal|"GimpPaintbrushTool"
block|,
sizeof|sizeof
argument_list|(
name|GimpPaintbrushTool
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpPaintbrushToolClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_paintbrush_tool_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_paintbrush_tool_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
name|NULL
block|}
decl_stmt|;
name|tool_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_PAINT_TOOL
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
DECL|function|gimp_paintbrush_tool_options_reset (void)
name|gimp_paintbrush_tool_options_reset
parameter_list|(
name|void
parameter_list|)
block|{
name|PaintbrushOptions
modifier|*
name|options
init|=
name|paintbrush_options
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
name|PaintbrushOptions
modifier|*
DECL|function|gimp_paintbrush_tool_options_new (void)
name|gimp_paintbrush_tool_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|PaintbrushOptions
modifier|*
name|options
decl_stmt|;
comment|/*  the new paint tool options structure  */
name|options
operator|=
name|g_new0
argument_list|(
name|PaintbrushOptions
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
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|,
name|gimp_paintbrush_tool_options_reset
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
DECL|function|gimp_paintbrush_tool_paint (GimpPaintTool * paint_tool,GimpDrawable * drawable,PaintState state)
name|gimp_paintbrush_tool_paint
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PaintState
name|state
parameter_list|)
block|{
name|PaintPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
name|PaintGradientOptions
modifier|*
name|gradient_options
decl_stmt|;
name|gboolean
name|incremental
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gdouble
name|fade_out
decl_stmt|;
name|gdouble
name|gradient_length
decl_stmt|;
name|gdouble
name|unit_factor
decl_stmt|;
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|gimage
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
condition|)
return|return;
if|if
condition|(
name|paintbrush_options
condition|)
block|{
name|pressure_options
operator|=
name|paintbrush_options
operator|->
name|paint_options
operator|.
name|pressure_options
expr_stmt|;
name|gradient_options
operator|=
name|paintbrush_options
operator|->
name|paint_options
operator|.
name|gradient_options
expr_stmt|;
name|incremental
operator|=
name|paintbrush_options
operator|->
name|paint_options
operator|.
name|incremental
expr_stmt|;
block|}
else|else
block|{
name|pressure_options
operator|=
operator|&
name|non_gui_pressure_options
expr_stmt|;
name|gradient_options
operator|=
operator|&
name|non_gui_gradient_options
expr_stmt|;
name|incremental
operator|=
name|non_gui_incremental
expr_stmt|;
block|}
switch|switch
condition|(
name|state
condition|)
block|{
case|case
name|INIT_PAINT
case|:
break|break;
case|case
name|MOTION_PAINT
case|:
switch|switch
condition|(
name|gradient_options
operator|->
name|fade_unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
name|fade_out
operator|=
name|gradient_options
operator|->
name|fade_out
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_PERCENT
case|:
name|fade_out
operator|=
operator|(
name|MAX
argument_list|(
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
operator|*
name|gradient_options
operator|->
name|fade_out
operator|/
literal|100
operator|)
expr_stmt|;
break|break;
default|default:
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|gradient_options
operator|->
name|fade_unit
argument_list|)
expr_stmt|;
name|fade_out
operator|=
operator|(
name|gradient_options
operator|->
name|fade_out
operator|*
name|MAX
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|/
name|unit_factor
operator|)
expr_stmt|;
break|break;
block|}
switch|switch
condition|(
name|gradient_options
operator|->
name|gradient_unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
name|gradient_length
operator|=
name|gradient_options
operator|->
name|gradient_length
expr_stmt|;
break|break;
case|case
name|GIMP_UNIT_PERCENT
case|:
name|gradient_length
operator|=
operator|(
name|MAX
argument_list|(
name|gimage
operator|->
name|width
argument_list|,
name|gimage
operator|->
name|height
argument_list|)
operator|*
name|gradient_options
operator|->
name|gradient_length
operator|/
literal|100
operator|)
expr_stmt|;
break|break;
default|default:
name|unit_factor
operator|=
name|gimp_unit_get_factor
argument_list|(
name|gradient_options
operator|->
name|gradient_unit
argument_list|)
expr_stmt|;
name|gradient_length
operator|=
operator|(
name|gradient_options
operator|->
name|gradient_length
operator|*
name|MAX
argument_list|(
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
operator|/
name|unit_factor
operator|)
expr_stmt|;
break|break;
block|}
name|gimp_paintbrush_tool_motion
argument_list|(
name|paint_tool
argument_list|,
name|drawable
argument_list|,
name|pressure_options
argument_list|,
name|gradient_options
argument_list|,
name|gradient_options
operator|->
name|use_fade
condition|?
name|fade_out
else|:
literal|0
argument_list|,
name|gradient_options
operator|->
name|use_gradient
condition|?
name|gradient_length
else|:
literal|0
argument_list|,
name|incremental
argument_list|,
name|gradient_options
operator|->
name|gradient_type
argument_list|)
expr_stmt|;
break|break;
case|case
name|FINISH_PAINT
case|:
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
name|GimpTool
modifier|*
DECL|function|gimp_paintbrush_tool_new (void)
name|gimp_paintbrush_tool_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paintbrush_tool_init (GimpPaintbrushTool * paintbrush)
name|gimp_paintbrush_tool_init
parameter_list|(
name|GimpPaintbrushTool
modifier|*
name|paintbrush
parameter_list|)
block|{
name|GimpTool
modifier|*
name|tool
decl_stmt|;
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|tool
operator|=
name|GIMP_TOOL
argument_list|(
name|paintbrush
argument_list|)
expr_stmt|;
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|paintbrush
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|paintbrush_options
condition|)
block|{
name|paintbrush_options
operator|=
name|gimp_paintbrush_tool_options_new
argument_list|()
expr_stmt|;
name|tool_manager_register_tool_options
argument_list|(
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|,
operator|(
name|ToolOptions
operator|*
operator|)
name|paintbrush_options
argument_list|)
expr_stmt|;
block|}
name|tool
operator|->
name|tool_cursor
operator|=
name|GIMP_PAINTBRUSH_TOOL_CURSOR
expr_stmt|;
name|paint_tool
operator|->
name|pick_colors
operator|=
name|TRUE
expr_stmt|;
name|paint_tool
operator|->
name|flags
operator||=
name|TOOL_CAN_HANDLE_CHANGING_BRUSH
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paintbrush_tool_class_init (GimpPaintbrushToolClass * klass)
name|gimp_paintbrush_tool_class_init
parameter_list|(
name|GimpPaintbrushToolClass
modifier|*
name|klass
parameter_list|)
block|{
name|GimpPaintToolClass
modifier|*
name|paint_tool_class
decl_stmt|;
name|paint_tool_class
operator|=
operator|(
name|GimpPaintToolClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_PAINT_TOOL
argument_list|)
expr_stmt|;
name|paint_tool_class
operator|->
name|paint
operator|=
name|gimp_paintbrush_tool_paint
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_paintbrush_tool_register (void)
name|gimp_paintbrush_tool_register
parameter_list|(
name|void
parameter_list|)
block|{
name|tool_manager_register_tool
argument_list|(
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|,
name|TRUE
argument_list|,
literal|"gimp:paintbrush_tool"
argument_list|,
name|_
argument_list|(
literal|"Paintbrush"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Paint fuzzy brush strokes"
argument_list|)
argument_list|,
name|N_
argument_list|(
literal|"/Tools/Paint Tools/Paintbrush"
argument_list|)
argument_list|,
literal|"P"
argument_list|,
name|NULL
argument_list|,
literal|"tools/paintbrush.html"
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|*
operator|)
name|paint_bits
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_paintbrush_tool_motion (GimpPaintTool * paint_tool,GimpDrawable * drawable,PaintPressureOptions * pressure_options,PaintGradientOptions * gradient_options,double fade_out,double gradient_length,PaintApplicationMode incremental,GradientPaintMode gradient_type)
name|gimp_paintbrush_tool_motion
parameter_list|(
name|GimpPaintTool
modifier|*
name|paint_tool
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|PaintPressureOptions
modifier|*
name|pressure_options
parameter_list|,
name|PaintGradientOptions
modifier|*
name|gradient_options
parameter_list|,
name|double
name|fade_out
parameter_list|,
name|double
name|gradient_length
parameter_list|,
name|PaintApplicationMode
name|incremental
parameter_list|,
name|GradientPaintMode
name|gradient_type
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|gdouble
name|x
decl_stmt|,
name|paint_left
decl_stmt|;
name|gdouble
name|position
decl_stmt|;
name|guchar
name|local_blend
init|=
name|OPAQUE_OPACITY
decl_stmt|;
name|guchar
name|temp_blend
init|=
name|OPAQUE_OPACITY
decl_stmt|;
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|GimpRGB
name|color
decl_stmt|;
name|gint
name|mode
decl_stmt|;
name|gint
name|opacity
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|PaintApplicationMode
name|paint_appl_mode
init|=
name|incremental
condition|?
name|INCREMENTAL
else|:
name|CONSTANT
decl_stmt|;
name|position
operator|=
literal|0.0
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|gimage
operator|=
name|gimp_drawable_gimage
argument_list|(
name|drawable
argument_list|)
operator|)
condition|)
return|return;
if|if
condition|(
name|pressure_options
operator|->
name|size
condition|)
name|scale
operator|=
name|paint_tool
operator|->
name|curpressure
expr_stmt|;
else|else
name|scale
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|pressure_options
operator|->
name|color
condition|)
name|gradient_length
operator|=
literal|1.0
expr_stmt|;
comment|/* not really used, only for if cases */
comment|/*  Get a region which can be used to paint to  */
if|if
condition|(
operator|!
operator|(
name|area
operator|=
name|gimp_paint_tool_get_paint_area
argument_list|(
name|paint_tool
argument_list|,
name|drawable
argument_list|,
name|scale
argument_list|)
operator|)
condition|)
return|return;
comment|/*  factor in the fade out value  */
if|if
condition|(
name|fade_out
condition|)
block|{
comment|/*  Model the amount of paint left as a gaussian curve  */
name|x
operator|=
operator|(
operator|(
name|double
operator|)
name|paint_tool
operator|->
name|pixel_dist
operator|/
name|fade_out
operator|)
expr_stmt|;
name|paint_left
operator|=
name|exp
argument_list|(
operator|-
name|x
operator|*
name|x
operator|*
literal|5.541
argument_list|)
expr_stmt|;
comment|/*  ln (1/255)  */
name|local_blend
operator|=
call|(
name|int
call|)
argument_list|(
literal|255
operator|*
name|paint_left
argument_list|)
expr_stmt|;
block|}
if|if
condition|(
name|local_blend
condition|)
block|{
comment|/*  set the alpha channel  */
name|temp_blend
operator|=
name|local_blend
expr_stmt|;
name|mode
operator|=
name|gradient_type
expr_stmt|;
if|if
condition|(
name|gradient_length
condition|)
block|{
if|if
condition|(
name|pressure_options
operator|->
name|color
condition|)
name|gimp_gradient_get_color_at
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|NULL
argument_list|)
argument_list|,
name|paint_tool
operator|->
name|curpressure
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
else|else
name|gimp_paint_tool_get_color_from_gradient
argument_list|(
name|paint_tool
argument_list|,
name|gradient_length
argument_list|,
operator|&
name|color
argument_list|,
name|mode
argument_list|)
expr_stmt|;
name|temp_blend
operator|=
call|(
name|gint
call|)
argument_list|(
operator|(
name|color
operator|.
name|a
operator|*
name|local_blend
operator|)
argument_list|)
expr_stmt|;
name|gimp_rgb_get_uchar
argument_list|(
operator|&
name|color
argument_list|,
operator|&
name|col
index|[
name|RED_PIX
index|]
argument_list|,
operator|&
name|col
index|[
name|GREEN_PIX
index|]
argument_list|,
operator|&
name|col
index|[
name|BLUE_PIX
index|]
argument_list|)
expr_stmt|;
name|col
index|[
name|ALPHA_PIX
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
comment|/* always use incremental mode with gradients */
comment|/* make the gui cool later */
name|paint_appl_mode
operator|=
name|INCREMENTAL
expr_stmt|;
name|color_pixels
argument_list|(
name|temp_buf_data
argument_list|(
name|area
argument_list|)
argument_list|,
name|col
argument_list|,
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|height
argument_list|,
name|area
operator|->
name|bytes
argument_list|)
expr_stmt|;
block|}
comment|/* we check to see if this is a pixmap, if so composite the 	 pixmap image into the are instead of the color */
elseif|else
if|if
condition|(
name|paint_tool
operator|->
name|brush
operator|&&
name|paint_tool
operator|->
name|brush
operator|->
name|pixmap
condition|)
block|{
name|gimp_paint_tool_color_area_with_pixmap
argument_list|(
name|paint_tool
argument_list|,
name|gimage
argument_list|,
name|drawable
argument_list|,
name|area
argument_list|,
name|scale
argument_list|,
name|SOFT
argument_list|)
expr_stmt|;
name|paint_appl_mode
operator|=
name|INCREMENTAL
expr_stmt|;
block|}
else|else
block|{
name|gimp_image_get_foreground
argument_list|(
name|gimage
argument_list|,
name|drawable
argument_list|,
name|col
argument_list|)
expr_stmt|;
name|col
index|[
name|area
operator|->
name|bytes
operator|-
literal|1
index|]
operator|=
name|OPAQUE_OPACITY
expr_stmt|;
name|color_pixels
argument_list|(
name|temp_buf_data
argument_list|(
name|area
argument_list|)
argument_list|,
name|col
argument_list|,
name|area
operator|->
name|width
operator|*
name|area
operator|->
name|height
argument_list|,
name|area
operator|->
name|bytes
argument_list|)
expr_stmt|;
block|}
name|opacity
operator|=
operator|(
name|gdouble
operator|)
name|temp_blend
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
name|paint_tool
operator|->
name|curpressure
expr_stmt|;
name|gimp_paint_tool_paste_canvas
argument_list|(
name|paint_tool
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
name|gimp_context_get_opacity
argument_list|(
name|NULL
argument_list|)
operator|*
literal|255
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|NULL
argument_list|)
argument_list|,
name|pressure_options
operator|->
name|pressure
condition|?
name|PRESSURE
else|:
name|SOFT
argument_list|,
name|scale
argument_list|,
name|paint_appl_mode
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_decl_stmt
DECL|variable|non_gui_paintbrush
specifier|static
name|GimpPaintbrushTool
modifier|*
name|non_gui_paintbrush
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|gboolean
DECL|function|gimp_paintbrush_tool_non_gui_default (GimpDrawable * drawable,gint num_strokes,double * stroke_array)
name|gimp_paintbrush_tool_non_gui_default
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
name|double
modifier|*
name|stroke_array
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
name|non_gui_paintbrush
condition|)
block|{
name|non_gui_paintbrush
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
expr_stmt|;
block|}
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|non_gui_paintbrush
argument_list|)
expr_stmt|;
comment|/* Hmmm... PDB paintbrush should have gradient type added to it!    * thats why the code below is duplicated.    */
if|if
condition|(
name|gimp_paint_tool_start
argument_list|(
name|paint_tool
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
name|paint_tool
operator|->
name|startx
operator|=
name|paint_tool
operator|->
name|lastx
operator|=
name|stroke_array
index|[
literal|0
index|]
expr_stmt|;
name|paint_tool
operator|->
name|starty
operator|=
name|paint_tool
operator|->
name|lasty
operator|=
name|stroke_array
index|[
literal|1
index|]
expr_stmt|;
name|gimp_paint_tool_paint
argument_list|(
name|paint_tool
argument_list|,
name|drawable
argument_list|,
name|MOTION_PAINT
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
name|paint_tool
operator|->
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
name|paint_tool
operator|->
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
name|gimp_paint_tool_interpolate
argument_list|(
name|paint_tool
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|lastx
operator|=
name|paint_tool
operator|->
name|curx
expr_stmt|;
name|paint_tool
operator|->
name|lasty
operator|=
name|paint_tool
operator|->
name|cury
expr_stmt|;
block|}
comment|/* Finish the painting */
name|gimp_paint_tool_finish
argument_list|(
name|paint_tool
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
block|{
return|return
name|FALSE
return|;
block|}
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_paintbrush_tool_non_gui (GimpDrawable * drawable,gint num_strokes,gdouble * stroke_array,gdouble fade_out,gint method,gdouble gradient_length)
name|gimp_paintbrush_tool_non_gui
parameter_list|(
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|gint
name|num_strokes
parameter_list|,
name|gdouble
modifier|*
name|stroke_array
parameter_list|,
name|gdouble
name|fade_out
parameter_list|,
name|gint
name|method
parameter_list|,
name|gdouble
name|gradient_length
parameter_list|)
block|{
name|GimpPaintTool
modifier|*
name|paint_tool
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
operator|!
name|non_gui_paintbrush
condition|)
block|{
name|non_gui_paintbrush
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_PAINTBRUSH_TOOL
argument_list|)
expr_stmt|;
block|}
name|paint_tool
operator|=
name|GIMP_PAINT_TOOL
argument_list|(
name|non_gui_paintbrush
argument_list|)
expr_stmt|;
comment|/* Code duplicated above */
if|if
condition|(
name|gimp_paint_tool_start
argument_list|(
name|paint_tool
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
name|non_gui_gradient_options
operator|.
name|fade_out
operator|=
name|fade_out
expr_stmt|;
name|non_gui_gradient_options
operator|.
name|gradient_length
operator|=
name|gradient_length
expr_stmt|;
name|non_gui_gradient_options
operator|.
name|gradient_type
operator|=
name|LOOP_TRIANGLE
expr_stmt|;
name|non_gui_incremental
operator|=
name|method
expr_stmt|;
name|paint_tool
operator|->
name|startx
operator|=
name|paint_tool
operator|->
name|lastx
operator|=
name|stroke_array
index|[
literal|0
index|]
expr_stmt|;
name|paint_tool
operator|->
name|starty
operator|=
name|paint_tool
operator|->
name|lasty
operator|=
name|stroke_array
index|[
literal|1
index|]
expr_stmt|;
if|if
condition|(
name|num_strokes
operator|==
literal|1
condition|)
name|gimp_paint_tool_paint
argument_list|(
name|paint_tool
argument_list|,
name|drawable
argument_list|,
name|MOTION_PAINT
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
name|paint_tool
operator|->
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
name|paint_tool
operator|->
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
name|gimp_paint_tool_interpolate
argument_list|(
name|paint_tool
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
name|paint_tool
operator|->
name|lastx
operator|=
name|paint_tool
operator|->
name|curx
expr_stmt|;
name|paint_tool
operator|->
name|lasty
operator|=
name|paint_tool
operator|->
name|cury
expr_stmt|;
block|}
comment|/* Finish the painting */
name|gimp_paint_tool_finish
argument_list|(
name|paint_tool
argument_list|,
name|drawable
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
else|else
block|{
return|return
name|FALSE
return|;
block|}
block|}
end_function

end_unit

