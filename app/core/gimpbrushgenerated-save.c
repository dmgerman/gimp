begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimp_brush_generated module Copyright 1998 Jay Cox<jaycox@earthlink.net>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<ctype.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

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
file|"gimpbrushgenerated.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"gimpbrush.h"
end_include

begin_include
include|#
directive|include
file|"temp_buf.h"
end_include

begin_comment
comment|/*  this needs to go away  */
end_comment

begin_include
include|#
directive|include
file|"tools/paint_core.h"
end_include

begin_define
DECL|macro|OVERSAMPLING
define|#
directive|define
name|OVERSAMPLING
value|5
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_brush_generated_class_init
parameter_list|(
name|GimpBrushGeneratedClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_generated_init
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_generated_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_brush_generated_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_brush_generated_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpBrushClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_brush_generated_get_type (void)
name|gimp_brush_generated_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
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
name|GtkTypeInfo
name|info
init|=
block|{
literal|"GimpBrushGenerated"
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushGenerated
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpBrushGeneratedClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_brush_generated_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_brush_generated_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|}
decl_stmt|;
name|type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|,
operator|&
name|info
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
DECL|function|gimp_brush_generated_class_init (GimpBrushGeneratedClass * klass)
name|gimp_brush_generated_class_init
parameter_list|(
name|GimpBrushGeneratedClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|GimpDataClass
modifier|*
name|data_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|data_class
operator|=
operator|(
name|GimpDataClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_BRUSH
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_brush_generated_destroy
expr_stmt|;
name|data_class
operator|->
name|save
operator|=
name|gimp_brush_generated_save
expr_stmt|;
name|data_class
operator|->
name|dirty
operator|=
name|gimp_brush_generated_dirty
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_generated_init (GimpBrushGenerated * brush)
name|gimp_brush_generated_init
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
block|{
name|brush
operator|->
name|radius
operator|=
literal|5.0
expr_stmt|;
name|brush
operator|->
name|hardness
operator|=
literal|0.0
expr_stmt|;
name|brush
operator|->
name|angle
operator|=
literal|0.0
expr_stmt|;
name|brush
operator|->
name|aspect_ratio
operator|=
literal|1.0
expr_stmt|;
name|brush
operator|->
name|freeze
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_generated_destroy (GtkObject * object)
name|gimp_brush_generated_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_brush_generated_save (GimpData * data)
name|gimp_brush_generated_save
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|data
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|data
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|brush
operator|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|data
argument_list|)
expr_stmt|;
comment|/*  we are (finaly) ready to try to save the generated brush file  */
if|if
condition|(
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|data
operator|->
name|filename
argument_list|,
literal|"wb"
argument_list|)
operator|)
operator|==
name|NULL
condition|)
block|{
name|g_warning
argument_list|(
literal|"Unable to save file %s"
argument_list|,
name|data
operator|->
name|filename
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/* write magic header */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"GIMP-VBR\n"
argument_list|)
expr_stmt|;
comment|/* write version */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"1.0\n"
argument_list|)
expr_stmt|;
comment|/* write name */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%.255s\n"
argument_list|,
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
operator|->
name|name
argument_list|)
expr_stmt|;
comment|/* write brush spacing */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%f\n"
argument_list|,
operator|(
name|gfloat
operator|)
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|spacing
argument_list|)
expr_stmt|;
comment|/* write brush radius */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%f\n"
argument_list|,
name|brush
operator|->
name|radius
argument_list|)
expr_stmt|;
comment|/* write brush hardness */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%f\n"
argument_list|,
name|brush
operator|->
name|hardness
argument_list|)
expr_stmt|;
comment|/* write brush aspect_ratio */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%f\n"
argument_list|,
name|brush
operator|->
name|aspect_ratio
argument_list|)
expr_stmt|;
comment|/* write brush angle */
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"%f\n"
argument_list|,
name|brush
operator|->
name|angle
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|double
DECL|function|gauss (gdouble f)
name|gauss
parameter_list|(
name|gdouble
name|f
parameter_list|)
block|{
comment|/* this aint' a real gauss function */
if|if
condition|(
name|f
operator|<
operator|-
literal|.5
condition|)
block|{
name|f
operator|=
operator|-
literal|1.0
operator|-
name|f
expr_stmt|;
return|return
operator|(
literal|2.0
operator|*
name|f
operator|*
name|f
operator|)
return|;
block|}
if|if
condition|(
name|f
operator|<
literal|.5
condition|)
return|return
operator|(
literal|1.0
operator|-
literal|2.0
operator|*
name|f
operator|*
name|f
operator|)
return|;
name|f
operator|=
literal|1.0
operator|-
name|f
expr_stmt|;
return|return
operator|(
literal|2.0
operator|*
name|f
operator|*
name|f
operator|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_brush_generated_dirty (GimpData * data)
name|gimp_brush_generated_dirty
parameter_list|(
name|GimpData
modifier|*
name|data
parameter_list|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
specifier|register
name|GimpBrush
modifier|*
name|gbrush
init|=
name|NULL
decl_stmt|;
specifier|register
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
specifier|register
name|guchar
modifier|*
name|centerp
decl_stmt|;
specifier|register
name|gdouble
name|d
decl_stmt|;
specifier|register
name|gdouble
name|exponent
decl_stmt|;
specifier|register
name|guchar
name|a
decl_stmt|;
specifier|register
name|gint
name|length
decl_stmt|;
specifier|register
name|guchar
modifier|*
name|lookup
decl_stmt|;
specifier|register
name|gdouble
name|sum
decl_stmt|,
name|c
decl_stmt|,
name|s
decl_stmt|,
name|tx
decl_stmt|,
name|ty
decl_stmt|;
name|gdouble
name|buffer
index|[
name|OVERSAMPLING
index|]
decl_stmt|;
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
name|brush
operator|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|data
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|freeze
condition|)
comment|/* if we are frozen defer rerendering till later */
return|return;
name|gbrush
operator|=
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
expr_stmt|;
if|if
condition|(
name|stingy_memory_use
operator|&&
name|gbrush
operator|->
name|mask
condition|)
name|temp_buf_unswap
argument_list|(
name|gbrush
operator|->
name|mask
argument_list|)
expr_stmt|;
if|if
condition|(
name|gbrush
operator|->
name|mask
condition|)
block|{
name|temp_buf_free
argument_list|(
name|gbrush
operator|->
name|mask
argument_list|)
expr_stmt|;
block|}
comment|/* compute the range of the brush. should do a better job than this? */
name|s
operator|=
name|sin
argument_list|(
name|gimp_deg_to_rad
argument_list|(
name|brush
operator|->
name|angle
argument_list|)
argument_list|)
expr_stmt|;
name|c
operator|=
name|cos
argument_list|(
name|gimp_deg_to_rad
argument_list|(
name|brush
operator|->
name|angle
argument_list|)
argument_list|)
expr_stmt|;
name|tx
operator|=
name|MAX
argument_list|(
name|fabs
argument_list|(
name|c
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
operator|-
name|s
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
operator|/
name|brush
operator|->
name|aspect_ratio
argument_list|)
argument_list|,
name|fabs
argument_list|(
name|c
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
operator|+
name|s
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
operator|/
name|brush
operator|->
name|aspect_ratio
argument_list|)
argument_list|)
expr_stmt|;
name|ty
operator|=
name|MAX
argument_list|(
name|fabs
argument_list|(
name|s
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
operator|+
name|c
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
operator|/
name|brush
operator|->
name|aspect_ratio
argument_list|)
argument_list|,
name|fabs
argument_list|(
name|s
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
operator|-
name|c
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
operator|/
name|brush
operator|->
name|aspect_ratio
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|radius
operator|>
name|tx
condition|)
name|width
operator|=
name|ceil
argument_list|(
name|tx
argument_list|)
expr_stmt|;
else|else
name|width
operator|=
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|radius
operator|>
name|ty
condition|)
name|height
operator|=
name|ceil
argument_list|(
name|ty
argument_list|)
expr_stmt|;
else|else
name|height
operator|=
name|ceil
argument_list|(
name|brush
operator|->
name|radius
argument_list|)
expr_stmt|;
comment|/* compute the axis for spacing */
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|x_axis
operator|.
name|x
operator|=
name|c
operator|*
name|brush
operator|->
name|radius
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|x_axis
operator|.
name|y
operator|=
operator|-
literal|1.0
operator|*
name|s
operator|*
name|brush
operator|->
name|radius
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|y_axis
operator|.
name|x
operator|=
operator|(
name|s
operator|*
name|brush
operator|->
name|radius
operator|/
name|brush
operator|->
name|aspect_ratio
operator|)
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|y_axis
operator|.
name|y
operator|=
operator|(
name|c
operator|*
name|brush
operator|->
name|radius
operator|/
name|brush
operator|->
name|aspect_ratio
operator|)
expr_stmt|;
name|gbrush
operator|->
name|mask
operator|=
name|temp_buf_new
argument_list|(
name|width
operator|*
literal|2
operator|+
literal|1
argument_list|,
name|height
operator|*
literal|2
operator|+
literal|1
argument_list|,
literal|1
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|centerp
operator|=
operator|&
name|gbrush
operator|->
name|mask
operator|->
name|data
index|[
name|height
operator|*
name|gbrush
operator|->
name|mask
operator|->
name|width
operator|+
name|width
index|]
expr_stmt|;
if|if
condition|(
operator|(
literal|1.0
operator|-
name|brush
operator|->
name|hardness
operator|)
operator|<
literal|0.000001
condition|)
name|exponent
operator|=
literal|1000000
expr_stmt|;
else|else
name|exponent
operator|=
literal|1
operator|/
operator|(
literal|1.0
operator|-
name|brush
operator|->
name|hardness
operator|)
expr_stmt|;
comment|/* set up lookup table */
name|length
operator|=
name|ceil
argument_list|(
name|sqrt
argument_list|(
literal|2
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
operator|+
literal|1
argument_list|)
operator|*
name|ceil
argument_list|(
name|brush
operator|->
name|radius
operator|+
literal|1
argument_list|)
argument_list|)
operator|+
literal|1
argument_list|)
operator|*
name|OVERSAMPLING
expr_stmt|;
name|lookup
operator|=
name|g_malloc
argument_list|(
name|length
argument_list|)
expr_stmt|;
name|sum
operator|=
literal|0.0
expr_stmt|;
for|for
control|(
name|x
operator|=
literal|0
init|;
name|x
operator|<
name|OVERSAMPLING
condition|;
name|x
operator|++
control|)
block|{
name|d
operator|=
name|fabs
argument_list|(
operator|(
name|x
operator|+
literal|0.5
operator|)
operator|/
name|OVERSAMPLING
operator|-
literal|0.5
argument_list|)
expr_stmt|;
if|if
condition|(
name|d
operator|>
name|brush
operator|->
name|radius
condition|)
name|buffer
index|[
name|x
index|]
operator|=
literal|0.0
expr_stmt|;
else|else
comment|/* buffer[x] =  (1.0 - pow (d/brush->radius, exponent)); */
name|buffer
index|[
name|x
index|]
operator|=
name|gauss
argument_list|(
name|pow
argument_list|(
name|d
operator|/
name|brush
operator|->
name|radius
argument_list|,
name|exponent
argument_list|)
argument_list|)
expr_stmt|;
name|sum
operator|+=
name|buffer
index|[
name|x
index|]
expr_stmt|;
block|}
for|for
control|(
name|x
operator|=
literal|0
init|;
name|d
operator|<
name|brush
operator|->
name|radius
operator|||
name|sum
operator|>
literal|0.00001
condition|;
name|d
operator|+=
literal|1.0
operator|/
name|OVERSAMPLING
control|)
block|{
name|sum
operator|-=
name|buffer
index|[
name|x
operator|%
name|OVERSAMPLING
index|]
expr_stmt|;
if|if
condition|(
name|d
operator|>
name|brush
operator|->
name|radius
condition|)
name|buffer
index|[
name|x
operator|%
name|OVERSAMPLING
index|]
operator|=
literal|0.0
expr_stmt|;
else|else
comment|/* buffer[x%OVERSAMPLING] =  (1.0 - pow (d/brush->radius, exponent)); */
name|buffer
index|[
name|x
operator|%
name|OVERSAMPLING
index|]
operator|=
name|gauss
argument_list|(
name|pow
argument_list|(
name|d
operator|/
name|brush
operator|->
name|radius
argument_list|,
name|exponent
argument_list|)
argument_list|)
expr_stmt|;
name|sum
operator|+=
name|buffer
index|[
name|x
operator|%
name|OVERSAMPLING
index|]
expr_stmt|;
name|lookup
index|[
name|x
operator|++
index|]
operator|=
name|RINT
argument_list|(
name|sum
operator|*
operator|(
literal|255.0
operator|/
name|OVERSAMPLING
operator|)
argument_list|)
expr_stmt|;
block|}
while|while
condition|(
name|x
operator|<
name|length
condition|)
block|{
name|lookup
index|[
name|x
operator|++
index|]
operator|=
literal|0
expr_stmt|;
block|}
comment|/* compute one half and mirror it */
for|for
control|(
name|y
operator|=
literal|0
init|;
name|y
operator|<=
name|height
condition|;
name|y
operator|++
control|)
block|{
for|for
control|(
name|x
operator|=
operator|-
name|width
init|;
name|x
operator|<=
name|width
condition|;
name|x
operator|++
control|)
block|{
name|tx
operator|=
name|c
operator|*
name|x
operator|-
name|s
operator|*
name|y
expr_stmt|;
name|ty
operator|=
name|c
operator|*
name|y
operator|+
name|s
operator|*
name|x
expr_stmt|;
name|ty
operator|*=
name|brush
operator|->
name|aspect_ratio
expr_stmt|;
name|d
operator|=
name|sqrt
argument_list|(
name|tx
operator|*
name|tx
operator|+
name|ty
operator|*
name|ty
argument_list|)
expr_stmt|;
if|if
condition|(
name|d
operator|<
name|brush
operator|->
name|radius
operator|+
literal|1
condition|)
name|a
operator|=
name|lookup
index|[
operator|(
name|gint
operator|)
name|RINT
argument_list|(
name|d
operator|*
name|OVERSAMPLING
argument_list|)
index|]
expr_stmt|;
else|else
name|a
operator|=
literal|0
expr_stmt|;
name|centerp
index|[
name|y
operator|*
name|gbrush
operator|->
name|mask
operator|->
name|width
operator|+
name|x
index|]
operator|=
name|a
expr_stmt|;
name|centerp
index|[
operator|-
literal|1
operator|*
name|y
operator|*
name|gbrush
operator|->
name|mask
operator|->
name|width
operator|-
name|x
index|]
operator|=
name|a
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|lookup
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_DATA_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dirty
condition|)
name|GIMP_DATA_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|dirty
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|gimp_viewable_invalidate_preview
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_generated_new (gfloat radius,gfloat hardness,gfloat angle,gfloat aspect_ratio)
name|gimp_brush_generated_new
parameter_list|(
name|gfloat
name|radius
parameter_list|,
name|gfloat
name|hardness
parameter_list|,
name|gfloat
name|angle
parameter_list|,
name|gfloat
name|aspect_ratio
parameter_list|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
comment|/* set up normal brush data */
name|brush
operator|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_BRUSH_GENERATED
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
literal|"Untitled"
argument_list|)
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|spacing
operator|=
literal|20
expr_stmt|;
comment|/* set up gimp_brush_generated data */
name|brush
operator|->
name|radius
operator|=
name|radius
expr_stmt|;
name|brush
operator|->
name|hardness
operator|=
name|hardness
expr_stmt|;
name|brush
operator|->
name|angle
operator|=
name|angle
expr_stmt|;
name|brush
operator|->
name|aspect_ratio
operator|=
name|aspect_ratio
expr_stmt|;
comment|/* render brush mask */
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpBrush
modifier|*
DECL|function|gimp_brush_generated_load (const gchar * filename)
name|gimp_brush_generated_load
parameter_list|(
specifier|const
name|gchar
modifier|*
name|filename
parameter_list|)
block|{
name|GimpBrushGenerated
modifier|*
name|brush
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|gchar
name|string
index|[
literal|256
index|]
decl_stmt|;
name|gfloat
name|fl
decl_stmt|;
name|gfloat
name|version
decl_stmt|;
if|if
condition|(
operator|(
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"rb"
argument_list|)
operator|)
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
comment|/* make sure the file we are reading is the right type */
name|fgets
argument_list|(
name|string
argument_list|,
literal|255
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
name|string
argument_list|,
literal|"GIMP-VBR"
argument_list|,
literal|8
argument_list|)
operator|!=
literal|0
condition|)
return|return
name|NULL
return|;
comment|/* make sure we are reading a compatible version */
name|fgets
argument_list|(
name|string
argument_list|,
literal|255
argument_list|,
name|fp
argument_list|)
expr_stmt|;
name|sscanf
argument_list|(
name|string
argument_list|,
literal|"%f"
argument_list|,
operator|&
name|version
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|version
operator|<
literal|2.0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/* create new brush */
name|brush
operator|=
name|GIMP_BRUSH_GENERATED
argument_list|(
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_BRUSH_GENERATED
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_data_set_filename
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|,
name|filename
argument_list|)
expr_stmt|;
name|gimp_brush_generated_freeze
argument_list|(
name|brush
argument_list|)
expr_stmt|;
comment|/* read name */
name|fgets
argument_list|(
name|string
argument_list|,
literal|255
argument_list|,
name|fp
argument_list|)
expr_stmt|;
if|if
condition|(
name|string
index|[
name|strlen
argument_list|(
name|string
argument_list|)
operator|-
literal|1
index|]
operator|==
literal|'\n'
condition|)
name|string
index|[
name|strlen
argument_list|(
name|string
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|0
expr_stmt|;
name|gimp_object_set_name
argument_list|(
name|GIMP_OBJECT
argument_list|(
name|brush
argument_list|)
argument_list|,
name|string
argument_list|)
expr_stmt|;
comment|/* read brush spacing */
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"%f"
argument_list|,
operator|&
name|fl
argument_list|)
expr_stmt|;
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|spacing
operator|=
name|fl
expr_stmt|;
comment|/* read brush radius */
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"%f"
argument_list|,
operator|&
name|fl
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_radius
argument_list|(
name|brush
argument_list|,
name|fl
argument_list|)
expr_stmt|;
comment|/* read brush hardness */
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"%f"
argument_list|,
operator|&
name|fl
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_hardness
argument_list|(
name|brush
argument_list|,
name|fl
argument_list|)
expr_stmt|;
comment|/* read brush aspect_ratio */
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"%f"
argument_list|,
operator|&
name|fl
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_aspect_ratio
argument_list|(
name|brush
argument_list|,
name|fl
argument_list|)
expr_stmt|;
comment|/* read brush angle */
name|fscanf
argument_list|(
name|fp
argument_list|,
literal|"%f"
argument_list|,
operator|&
name|fl
argument_list|)
expr_stmt|;
name|gimp_brush_generated_set_angle
argument_list|(
name|brush
argument_list|,
name|fl
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
name|gimp_brush_generated_thaw
argument_list|(
name|brush
argument_list|)
expr_stmt|;
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
operator|->
name|dirty
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|stingy_memory_use
condition|)
name|temp_buf_swap
argument_list|(
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
operator|->
name|mask
argument_list|)
expr_stmt|;
return|return
name|GIMP_BRUSH
argument_list|(
name|brush
argument_list|)
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_generated_freeze (GimpBrushGenerated * brush)
name|gimp_brush_generated_freeze
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|brush
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
name|brush
operator|->
name|freeze
operator|++
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_brush_generated_thaw (GimpBrushGenerated * brush)
name|gimp_brush_generated_thaw
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|brush
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|freeze
operator|>
literal|0
condition|)
name|brush
operator|->
name|freeze
operator|--
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|freeze
operator|==
literal|0
condition|)
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gfloat
DECL|function|gimp_brush_generated_set_radius (GimpBrushGenerated * brush,gfloat radius)
name|gimp_brush_generated_set_radius
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gfloat
name|radius
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|radius
operator|<
literal|0.0
condition|)
name|radius
operator|=
literal|0.0
expr_stmt|;
elseif|else
if|if
condition|(
name|radius
operator|>
literal|32767.0
condition|)
name|radius
operator|=
literal|32767.0
expr_stmt|;
if|if
condition|(
name|radius
operator|==
name|brush
operator|->
name|radius
condition|)
return|return
name|radius
return|;
name|brush
operator|->
name|radius
operator|=
name|radius
expr_stmt|;
if|if
condition|(
operator|!
name|brush
operator|->
name|freeze
condition|)
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|radius
return|;
block|}
end_function

begin_function
name|gfloat
DECL|function|gimp_brush_generated_set_hardness (GimpBrushGenerated * brush,gfloat hardness)
name|gimp_brush_generated_set_hardness
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gfloat
name|hardness
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|hardness
operator|<
literal|0.0
condition|)
name|hardness
operator|=
literal|0.0
expr_stmt|;
elseif|else
if|if
condition|(
name|hardness
operator|>
literal|1.0
condition|)
name|hardness
operator|=
literal|1.0
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|hardness
operator|==
name|hardness
condition|)
return|return
name|hardness
return|;
name|brush
operator|->
name|hardness
operator|=
name|hardness
expr_stmt|;
if|if
condition|(
operator|!
name|brush
operator|->
name|freeze
condition|)
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|hardness
return|;
block|}
end_function

begin_function
name|gfloat
DECL|function|gimp_brush_generated_set_angle (GimpBrushGenerated * brush,gfloat angle)
name|gimp_brush_generated_set_angle
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gfloat
name|angle
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|angle
operator|<
literal|0.0
condition|)
name|angle
operator|=
operator|-
literal|1.0
operator|*
name|fmod
argument_list|(
name|angle
argument_list|,
literal|180.0
argument_list|)
expr_stmt|;
elseif|else
if|if
condition|(
name|angle
operator|>
literal|180.0
condition|)
name|angle
operator|=
name|fmod
argument_list|(
name|angle
argument_list|,
literal|180.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|angle
operator|==
name|angle
condition|)
return|return
name|angle
return|;
name|brush
operator|->
name|angle
operator|=
name|angle
expr_stmt|;
if|if
condition|(
operator|!
name|brush
operator|->
name|freeze
condition|)
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|angle
return|;
block|}
end_function

begin_function
name|gfloat
DECL|function|gimp_brush_generated_set_aspect_ratio (GimpBrushGenerated * brush,gfloat ratio)
name|gimp_brush_generated_set_aspect_ratio
parameter_list|(
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|,
name|gfloat
name|ratio
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
if|if
condition|(
name|ratio
operator|<
literal|1.0
condition|)
name|ratio
operator|=
literal|1.0
expr_stmt|;
elseif|else
if|if
condition|(
name|ratio
operator|>
literal|1000
condition|)
name|ratio
operator|=
literal|1000
expr_stmt|;
if|if
condition|(
name|brush
operator|->
name|aspect_ratio
operator|==
name|ratio
condition|)
return|return
name|ratio
return|;
name|brush
operator|->
name|aspect_ratio
operator|=
name|ratio
expr_stmt|;
if|if
condition|(
operator|!
name|brush
operator|->
name|freeze
condition|)
name|gimp_data_dirty
argument_list|(
name|GIMP_DATA
argument_list|(
name|brush
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|aspect_ratio
return|;
block|}
end_function

begin_function
name|gfloat
DECL|function|gimp_brush_generated_get_radius (const GimpBrushGenerated * brush)
name|gimp_brush_generated_get_radius
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|radius
return|;
block|}
end_function

begin_function
name|gfloat
DECL|function|gimp_brush_generated_get_hardness (const GimpBrushGenerated * brush)
name|gimp_brush_generated_get_hardness
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|hardness
return|;
block|}
end_function

begin_function
name|gfloat
DECL|function|gimp_brush_generated_get_angle (const GimpBrushGenerated * brush)
name|gimp_brush_generated_get_angle
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|angle
return|;
block|}
end_function

begin_function
name|gfloat
DECL|function|gimp_brush_generated_get_aspect_ratio (const GimpBrushGenerated * brush)
name|gimp_brush_generated_get_aspect_ratio
parameter_list|(
specifier|const
name|GimpBrushGenerated
modifier|*
name|brush
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_BRUSH_GENERATED
argument_list|(
name|brush
argument_list|)
argument_list|,
operator|-
literal|1.0
argument_list|)
expr_stmt|;
return|return
name|brush
operator|->
name|aspect_ratio
return|;
block|}
end_function

end_unit

