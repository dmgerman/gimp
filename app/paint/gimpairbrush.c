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
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"base/temp-buf.h"
end_include

begin_include
include|#
directive|include
file|"paint-funcs/paint-funcs.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdrawable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgradient.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpairbrush.h"
end_include

begin_define
DECL|macro|AIRBRUSH_DEFAULT_RATE
define|#
directive|define
name|AIRBRUSH_DEFAULT_RATE
value|80.0
end_define

begin_define
DECL|macro|AIRBRUSH_DEFAULT_PRESSURE
define|#
directive|define
name|AIRBRUSH_DEFAULT_PRESSURE
value|10.0
end_define

begin_typedef
DECL|typedef|AirbrushTimeout
typedef|typedef
name|struct
name|_AirbrushTimeout
name|AirbrushTimeout
typedef|;
end_typedef

begin_struct
DECL|struct|_AirbrushTimeout
struct|struct
name|_AirbrushTimeout
block|{
DECL|member|paint_core
name|GimpPaintCore
modifier|*
name|paint_core
decl_stmt|;
DECL|member|drawable
name|GimpDrawable
modifier|*
name|drawable
decl_stmt|;
DECL|member|paint_options
name|GimpPaintOptions
modifier|*
name|paint_options
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_airbrush_class_init
parameter_list|(
name|GimpAirbrushClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_airbrush_init
parameter_list|(
name|GimpAirbrush
modifier|*
name|airbrush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_airbrush_finalize
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
name|gimp_airbrush_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPaintCoreState
name|paint_state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_airbrush_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_airbrush_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|timeout_id
specifier|static
name|guint
name|timeout_id
init|=
literal|0
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|airbrush_timeout
specifier|static
name|AirbrushTimeout
name|airbrush_timeout
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpPaintCoreClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GType
DECL|function|gimp_airbrush_get_type (void)
name|gimp_airbrush_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
name|type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|type
condition|)
block|{
specifier|static
specifier|const
name|GTypeInfo
name|info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpAirbrushClass
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
name|gimp_airbrush_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data     */
sizeof|sizeof
argument_list|(
name|GimpAirbrush
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs    */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_airbrush_init
block|,       }
decl_stmt|;
name|type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_PAINT_CORE
argument_list|,
literal|"GimpAirbrush"
argument_list|,
operator|&
name|info
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
return|return
name|type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_class_init (GimpAirbrushClass * klass)
name|gimp_airbrush_class_init
parameter_list|(
name|GimpAirbrushClass
modifier|*
name|klass
parameter_list|)
block|{
name|GObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
decl_stmt|;
name|object_class
operator|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|paint_core_class
operator|=
name|GIMP_PAINT_CORE_CLASS
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
name|gimp_airbrush_finalize
expr_stmt|;
name|paint_core_class
operator|->
name|paint
operator|=
name|gimp_airbrush_paint
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_init (GimpAirbrush * airbrush)
name|gimp_airbrush_init
parameter_list|(
name|GimpAirbrush
modifier|*
name|airbrush
parameter_list|)
block|{
name|GimpPaintCore
modifier|*
name|paint_core
decl_stmt|;
name|paint_core
operator|=
name|GIMP_PAINT_CORE
argument_list|(
name|airbrush
argument_list|)
expr_stmt|;
name|paint_core
operator|->
name|flags
operator||=
name|CORE_HANDLES_CHANGING_BRUSH
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_finalize (GObject * object)
name|gimp_airbrush_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|timeout_id
argument_list|)
expr_stmt|;
name|timeout_id
operator|=
literal|0
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
DECL|function|gimp_airbrush_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintCoreState paint_state)
name|gimp_airbrush_paint
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|,
name|GimpPaintCoreState
name|paint_state
parameter_list|)
block|{
name|GimpAirbrushOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
operator|(
name|GimpAirbrushOptions
operator|*
operator|)
name|paint_options
expr_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|INIT_PAINT
case|:
if|if
condition|(
name|timeout_id
condition|)
block|{
name|g_warning
argument_list|(
literal|"killing stray timer, please report to lewing@gimp.org"
argument_list|)
expr_stmt|;
name|g_source_remove
argument_list|(
name|timeout_id
argument_list|)
expr_stmt|;
name|timeout_id
operator|=
literal|0
expr_stmt|;
block|}
break|break;
case|case
name|MOTION_PAINT
case|:
if|if
condition|(
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|timeout_id
argument_list|)
expr_stmt|;
name|timeout_id
operator|=
literal|0
expr_stmt|;
block|}
name|gimp_airbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|)
expr_stmt|;
if|if
condition|(
name|options
operator|->
name|rate
operator|!=
literal|0.0
condition|)
block|{
name|gdouble
name|timeout
decl_stmt|;
name|airbrush_timeout
operator|.
name|paint_core
operator|=
name|paint_core
expr_stmt|;
name|airbrush_timeout
operator|.
name|drawable
operator|=
name|drawable
expr_stmt|;
name|airbrush_timeout
operator|.
name|paint_options
operator|=
name|paint_options
expr_stmt|;
name|timeout
operator|=
operator|(
name|paint_options
operator|->
name|pressure_options
operator|->
name|rate
condition|?
operator|(
literal|10000
operator|/
operator|(
name|options
operator|->
name|rate
operator|*
literal|2.0
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
operator|)
operator|)
else|:
operator|(
literal|10000
operator|/
name|options
operator|->
name|rate
operator|)
operator|)
expr_stmt|;
name|timeout_id
operator|=
name|g_timeout_add
argument_list|(
name|timeout
argument_list|,
name|gimp_airbrush_timeout
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|FINISH_PAINT
case|:
if|if
condition|(
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|timeout_id
argument_list|)
expr_stmt|;
name|timeout_id
operator|=
literal|0
expr_stmt|;
block|}
break|break;
default|default:
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_airbrush_timeout (gpointer client_data)
name|gimp_airbrush_timeout
parameter_list|(
name|gpointer
name|client_data
parameter_list|)
block|{
name|gdouble
name|rate
decl_stmt|;
name|gimp_airbrush_motion
argument_list|(
name|airbrush_timeout
operator|.
name|paint_core
argument_list|,
name|airbrush_timeout
operator|.
name|drawable
argument_list|,
name|airbrush_timeout
operator|.
name|paint_options
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|__GNUC__
warning|#
directive|warning
warning|: FIXME: gdisplays_flush()
endif|#
directive|endif
name|gdisplays_flush
argument_list|()
expr_stmt|;
name|rate
operator|=
operator|(
operator|(
name|GimpAirbrushOptions
operator|*
operator|)
name|airbrush_timeout
operator|.
name|paint_options
operator|)
operator|->
name|rate
expr_stmt|;
comment|/*  restart the timer  */
if|if
condition|(
name|rate
operator|!=
literal|0.0
condition|)
block|{
if|if
condition|(
name|airbrush_timeout
operator|.
name|paint_options
operator|->
name|pressure_options
operator|->
name|rate
condition|)
block|{
if|if
condition|(
name|timeout_id
condition|)
name|g_source_remove
argument_list|(
name|timeout_id
argument_list|)
expr_stmt|;
name|timeout_id
operator|=
name|g_timeout_add
argument_list|(
operator|(
literal|10000
operator|/
operator|(
name|rate
operator|*
literal|2.0
operator|*
name|airbrush_timeout
operator|.
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
operator|)
operator|)
argument_list|,
name|gimp_airbrush_timeout
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_airbrush_motion (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options)
name|gimp_airbrush_motion
parameter_list|(
name|GimpPaintCore
modifier|*
name|paint_core
parameter_list|,
name|GimpDrawable
modifier|*
name|drawable
parameter_list|,
name|GimpPaintOptions
modifier|*
name|paint_options
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|TempBuf
modifier|*
name|area
decl_stmt|;
name|guchar
name|col
index|[
name|MAX_CHANNELS
index|]
decl_stmt|;
name|gdouble
name|scale
decl_stmt|;
name|PaintApplicationMode
name|paint_appl_mode
decl_stmt|;
name|gdouble
name|pressure
decl_stmt|;
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
name|context
operator|=
name|gimp_get_current_context
argument_list|(
name|gimage
operator|->
name|gimp
argument_list|)
expr_stmt|;
name|paint_appl_mode
operator|=
name|paint_options
operator|->
name|incremental
condition|?
name|INCREMENTAL
else|:
name|CONSTANT
expr_stmt|;
name|pressure
operator|=
operator|(
operator|(
name|GimpAirbrushOptions
operator|*
operator|)
name|paint_options
operator|)
operator|->
name|pressure
expr_stmt|;
if|if
condition|(
name|paint_options
operator|->
name|pressure_options
operator|->
name|size
condition|)
name|scale
operator|=
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
else|else
name|scale
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
operator|!
operator|(
name|area
operator|=
name|gimp_paint_core_get_paint_area
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|scale
argument_list|)
operator|)
condition|)
return|return;
comment|/*  color the pixels  */
if|if
condition|(
name|paint_options
operator|->
name|pressure_options
operator|->
name|color
condition|)
block|{
name|GimpRGB
name|color
decl_stmt|;
name|gimp_gradient_get_color_at
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
argument_list|,
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
argument_list|,
operator|&
name|color
argument_list|)
expr_stmt|;
name|gimp_rgba_get_uchar
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
argument_list|,
operator|&
name|col
index|[
name|ALPHA_PIX
index|]
argument_list|)
expr_stmt|;
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
elseif|else
if|if
condition|(
name|paint_core
operator|->
name|brush
operator|&&
name|paint_core
operator|->
name|brush
operator|->
name|pixmap
condition|)
block|{
name|paint_appl_mode
operator|=
name|INCREMENTAL
expr_stmt|;
name|gimp_paint_core_color_area_with_pixmap
argument_list|(
name|paint_core
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
if|if
condition|(
name|paint_options
operator|->
name|pressure_options
operator|->
name|pressure
condition|)
name|pressure
operator|=
name|pressure
operator|*
literal|2.0
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
comment|/*  paste the newly painted area to the image  */
name|gimp_paint_core_paste_canvas
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|MIN
argument_list|(
name|pressure
argument_list|,
literal|255
argument_list|)
argument_list|,
name|gimp_context_get_opacity
argument_list|(
name|context
argument_list|)
operator|*
literal|255
argument_list|,
name|gimp_context_get_paint_mode
argument_list|(
name|context
argument_list|)
argument_list|,
name|SOFT
argument_list|,
name|scale
argument_list|,
name|paint_appl_mode
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  paint options stuff  */
end_comment

begin_function
name|GimpAirbrushOptions
modifier|*
DECL|function|gimp_airbrush_options_new (void)
name|gimp_airbrush_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpAirbrushOptions
modifier|*
name|options
decl_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|GimpAirbrushOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_paint_options_init
argument_list|(
operator|(
name|GimpPaintOptions
operator|*
operator|)
name|options
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
name|AIRBRUSH_DEFAULT_RATE
expr_stmt|;
name|options
operator|->
name|pressure
operator|=
name|options
operator|->
name|pressure_d
operator|=
name|AIRBRUSH_DEFAULT_PRESSURE
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

end_unit

