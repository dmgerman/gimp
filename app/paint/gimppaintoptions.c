begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"paint-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimppaintoptions.h"
end_include

begin_define
DECL|macro|DEFAULT_INCREMENTAL
define|#
directive|define
name|DEFAULT_INCREMENTAL
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_OPACITY
define|#
directive|define
name|DEFAULT_OPACITY
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_PRESSURE
define|#
directive|define
name|DEFAULT_PRESSURE
value|TRUE
end_define

begin_define
DECL|macro|DEFAULT_RATE
define|#
directive|define
name|DEFAULT_RATE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_SIZE
define|#
directive|define
name|DEFAULT_SIZE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_COLOR
define|#
directive|define
name|DEFAULT_COLOR
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_USE_FADE
define|#
directive|define
name|DEFAULT_USE_FADE
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_FADE_OUT
define|#
directive|define
name|DEFAULT_FADE_OUT
value|100.0
end_define

begin_define
DECL|macro|DEFAULT_FADE_UNIT
define|#
directive|define
name|DEFAULT_FADE_UNIT
value|GIMP_UNIT_PIXEL
end_define

begin_define
DECL|macro|DEFAULT_USE_GRADIENT
define|#
directive|define
name|DEFAULT_USE_GRADIENT
value|FALSE
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_LENGTH
define|#
directive|define
name|DEFAULT_GRADIENT_LENGTH
value|100.0
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_UNIT
define|#
directive|define
name|DEFAULT_GRADIENT_UNIT
value|GIMP_UNIT_PIXEL
end_define

begin_define
DECL|macro|DEFAULT_GRADIENT_TYPE
define|#
directive|define
name|DEFAULT_GRADIENT_TYPE
value|GIMP_GRADIENT_LOOP_TRIANGLE
end_define

begin_function_decl
specifier|static
name|GimpPressureOptions
modifier|*
name|gimp_pressure_options_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|GimpGradientOptions
modifier|*
name|gimp_gradient_options_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpPaintOptions
modifier|*
DECL|function|gimp_paint_options_new (GimpContext * context)
name|gimp_paint_options_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|GimpPaintOptions
modifier|*
name|options
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|options
operator|=
name|g_new0
argument_list|(
name|GimpPaintOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gimp_paint_options_init
argument_list|(
name|options
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|options
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_paint_options_init (GimpPaintOptions * options,GimpContext * context)
name|gimp_paint_options_init
parameter_list|(
name|GimpPaintOptions
modifier|*
name|options
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|options
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|options
operator|->
name|opacity_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|paint_mode_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|context
operator|=
name|context
expr_stmt|;
name|options
operator|->
name|incremental_w
operator|=
name|NULL
expr_stmt|;
name|options
operator|->
name|incremental
operator|=
name|options
operator|->
name|incremental_d
operator|=
name|DEFAULT_INCREMENTAL
expr_stmt|;
name|options
operator|->
name|incremental_save
operator|=
name|DEFAULT_INCREMENTAL
expr_stmt|;
name|options
operator|->
name|pressure_options
operator|=
name|gimp_pressure_options_new
argument_list|()
expr_stmt|;
name|options
operator|->
name|gradient_options
operator|=
name|gimp_gradient_options_new
argument_list|()
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|GimpPressureOptions
modifier|*
DECL|function|gimp_pressure_options_new (void)
name|gimp_pressure_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpPressureOptions
modifier|*
name|pressure
decl_stmt|;
name|pressure
operator|=
name|g_new0
argument_list|(
name|GimpPressureOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|pressure
operator|->
name|opacity
operator|=
name|pressure
operator|->
name|opacity_d
operator|=
name|DEFAULT_OPACITY
expr_stmt|;
name|pressure
operator|->
name|pressure
operator|=
name|pressure
operator|->
name|pressure_d
operator|=
name|DEFAULT_PRESSURE
expr_stmt|;
name|pressure
operator|->
name|rate
operator|=
name|pressure
operator|->
name|rate_d
operator|=
name|DEFAULT_RATE
expr_stmt|;
name|pressure
operator|->
name|size
operator|=
name|pressure
operator|->
name|size_d
operator|=
name|DEFAULT_SIZE
expr_stmt|;
name|pressure
operator|->
name|color
operator|=
name|pressure
operator|->
name|color_d
operator|=
name|DEFAULT_COLOR
expr_stmt|;
name|pressure
operator|->
name|opacity_w
operator|=
name|NULL
expr_stmt|;
name|pressure
operator|->
name|pressure_w
operator|=
name|NULL
expr_stmt|;
name|pressure
operator|->
name|rate_w
operator|=
name|NULL
expr_stmt|;
name|pressure
operator|->
name|size_w
operator|=
name|NULL
expr_stmt|;
name|pressure
operator|->
name|color_w
operator|=
name|NULL
expr_stmt|;
return|return
name|pressure
return|;
block|}
end_function

begin_function
specifier|static
name|GimpGradientOptions
modifier|*
DECL|function|gimp_gradient_options_new (void)
name|gimp_gradient_options_new
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpGradientOptions
modifier|*
name|gradient
decl_stmt|;
name|gradient
operator|=
name|g_new0
argument_list|(
name|GimpGradientOptions
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|gradient
operator|->
name|use_fade
operator|=
name|gradient
operator|->
name|use_fade_d
operator|=
name|DEFAULT_USE_FADE
expr_stmt|;
name|gradient
operator|->
name|fade_out
operator|=
name|gradient
operator|->
name|fade_out_d
operator|=
name|DEFAULT_FADE_OUT
expr_stmt|;
name|gradient
operator|->
name|fade_unit
operator|=
name|gradient
operator|->
name|fade_unit_d
operator|=
name|DEFAULT_FADE_UNIT
expr_stmt|;
name|gradient
operator|->
name|use_gradient
operator|=
name|gradient
operator|->
name|use_gradient_d
operator|=
name|DEFAULT_USE_GRADIENT
expr_stmt|;
name|gradient
operator|->
name|gradient_length
operator|=
name|gradient
operator|->
name|gradient_length_d
operator|=
name|DEFAULT_GRADIENT_LENGTH
expr_stmt|;
name|gradient
operator|->
name|gradient_unit
operator|=
name|gradient
operator|->
name|gradient_unit_d
operator|=
name|DEFAULT_GRADIENT_UNIT
expr_stmt|;
name|gradient
operator|->
name|gradient_type
operator|=
name|gradient
operator|->
name|gradient_type_d
operator|=
name|DEFAULT_GRADIENT_TYPE
expr_stmt|;
name|gradient
operator|->
name|use_fade_w
operator|=
name|NULL
expr_stmt|;
name|gradient
operator|->
name|fade_out_w
operator|=
name|NULL
expr_stmt|;
name|gradient
operator|->
name|fade_unit_w
operator|=
name|NULL
expr_stmt|;
name|gradient
operator|->
name|use_gradient_w
operator|=
name|NULL
expr_stmt|;
name|gradient
operator|->
name|gradient_length_w
operator|=
name|NULL
expr_stmt|;
name|gradient
operator|->
name|gradient_unit_w
operator|=
name|NULL
expr_stmt|;
name|gradient
operator|->
name|gradient_type_w
operator|=
name|NULL
expr_stmt|;
return|return
name|gradient
return|;
block|}
end_function

end_unit

