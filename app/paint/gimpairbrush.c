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
file|<glib-object.h>
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

begin_include
include|#
directive|include
file|"gimpairbrushoptions.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

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
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
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

begin_macro
DECL|function|G_DEFINE_TYPE (GimpAirbrush,gimp_airbrush,GIMP_TYPE_PAINTBRUSH)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpAirbrush
argument_list|,
argument|gimp_airbrush
argument_list|,
argument|GIMP_TYPE_PAINTBRUSH
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_airbrush_parent_class
end_define

begin_function
name|void
name|gimp_airbrush_register
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpPaintRegisterCallback
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
name|GIMP_TYPE_AIRBRUSH
argument_list|,
name|GIMP_TYPE_AIRBRUSH_OPTIONS
argument_list|,
literal|"gimp-airbrush"
argument_list|,
name|_
argument_list|(
literal|"Airbrush"
argument_list|)
argument_list|,
literal|"gimp-tool-airbrush"
argument_list|)
expr_stmt|;
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
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|GimpPaintCoreClass
modifier|*
name|paint_core_class
init|=
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
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
name|airbrush
operator|->
name|timeout_id
operator|=
literal|0
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
name|GimpAirbrush
modifier|*
name|airbrush
init|=
name|GIMP_AIRBRUSH
argument_list|(
name|object
argument_list|)
decl_stmt|;
if|if
condition|(
name|airbrush
operator|->
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|airbrush
operator|->
name|timeout_id
argument_list|)
expr_stmt|;
name|airbrush
operator|->
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
DECL|function|gimp_airbrush_paint (GimpPaintCore * paint_core,GimpDrawable * drawable,GimpPaintOptions * paint_options,GimpPaintState paint_state,guint32 time)
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
name|GimpPaintState
name|paint_state
parameter_list|,
name|guint32
name|time
parameter_list|)
block|{
name|GimpAirbrush
modifier|*
name|airbrush
init|=
name|GIMP_AIRBRUSH
argument_list|(
name|paint_core
argument_list|)
decl_stmt|;
name|GimpAirbrushOptions
modifier|*
name|options
init|=
name|GIMP_AIRBRUSH_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|paint_state
condition|)
block|{
case|case
name|GIMP_PAINT_STATE_INIT
case|:
if|if
condition|(
name|airbrush
operator|->
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|airbrush
operator|->
name|timeout_id
argument_list|)
expr_stmt|;
name|airbrush
operator|->
name|timeout_id
operator|=
literal|0
expr_stmt|;
block|}
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|paint
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|paint_state
argument_list|,
name|time
argument_list|)
expr_stmt|;
break|break;
case|case
name|GIMP_PAINT_STATE_MOTION
case|:
if|if
condition|(
name|airbrush
operator|->
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|airbrush
operator|->
name|timeout_id
argument_list|)
expr_stmt|;
name|airbrush
operator|->
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
name|airbrush
operator|->
name|drawable
operator|=
name|drawable
expr_stmt|;
name|airbrush
operator|->
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
name|PRESSURE_SCALE
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
name|airbrush
operator|->
name|timeout_id
operator|=
name|g_timeout_add
argument_list|(
name|timeout
argument_list|,
name|gimp_airbrush_timeout
argument_list|,
name|airbrush
argument_list|)
expr_stmt|;
block|}
break|break;
case|case
name|GIMP_PAINT_STATE_FINISH
case|:
if|if
condition|(
name|airbrush
operator|->
name|timeout_id
condition|)
block|{
name|g_source_remove
argument_list|(
name|airbrush
operator|->
name|timeout_id
argument_list|)
expr_stmt|;
name|airbrush
operator|->
name|timeout_id
operator|=
literal|0
expr_stmt|;
block|}
name|GIMP_PAINT_CORE_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|paint
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|paint_state
argument_list|,
name|time
argument_list|)
expr_stmt|;
break|break;
block|}
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
name|GimpAirbrushOptions
modifier|*
name|options
init|=
name|GIMP_AIRBRUSH_OPTIONS
argument_list|(
name|paint_options
argument_list|)
decl_stmt|;
name|gdouble
name|opacity
decl_stmt|;
name|gboolean
name|saved_pressure
decl_stmt|;
name|opacity
operator|=
name|options
operator|->
name|pressure
operator|/
literal|100.0
expr_stmt|;
name|saved_pressure
operator|=
name|paint_options
operator|->
name|pressure_options
operator|->
name|hardness
expr_stmt|;
if|if
condition|(
name|saved_pressure
condition|)
name|opacity
operator|*=
name|PRESSURE_SCALE
operator|*
name|paint_core
operator|->
name|cur_coords
operator|.
name|pressure
expr_stmt|;
name|paint_options
operator|->
name|pressure_options
operator|->
name|hardness
operator|=
name|FALSE
expr_stmt|;
name|_gimp_paintbrush_motion
argument_list|(
name|paint_core
argument_list|,
name|drawable
argument_list|,
name|paint_options
argument_list|,
name|opacity
argument_list|)
expr_stmt|;
name|paint_options
operator|->
name|pressure_options
operator|->
name|hardness
operator|=
name|saved_pressure
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_airbrush_timeout (gpointer data)
name|gimp_airbrush_timeout
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpAirbrush
modifier|*
name|airbrush
init|=
name|GIMP_AIRBRUSH
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_airbrush_paint
argument_list|(
name|GIMP_PAINT_CORE
argument_list|(
name|airbrush
argument_list|)
argument_list|,
name|airbrush
operator|->
name|drawable
argument_list|,
name|airbrush
operator|->
name|paint_options
argument_list|,
name|GIMP_PAINT_STATE_MOTION
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gimp_image_flush
argument_list|(
name|gimp_item_get_image
argument_list|(
name|GIMP_ITEM
argument_list|(
name|airbrush
operator|->
name|drawable
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

end_unit

