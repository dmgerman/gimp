begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1999 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PAINT_OPTIONS_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PAINT_OPTIONS_H__
define|#
directive|define
name|__GIMP_PAINT_OPTIONS_H__
end_define

begin_include
include|#
directive|include
file|"tools/tools-types.h"
end_include

begin_comment
comment|/* temp hack */
end_comment

begin_include
include|#
directive|include
file|"tools/tool_options.h"
end_include

begin_comment
comment|/* temp hack */
end_comment

begin_typedef
DECL|typedef|GimpPressureOptions
typedef|typedef
name|struct
name|_GimpPressureOptions
name|GimpPressureOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPressureOptions
struct|struct
name|_GimpPressureOptions
block|{
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|opacity
name|gboolean
name|opacity
decl_stmt|;
DECL|member|opacity_d
name|gboolean
name|opacity_d
decl_stmt|;
DECL|member|opacity_w
name|GtkWidget
modifier|*
name|opacity_w
decl_stmt|;
DECL|member|pressure
name|gboolean
name|pressure
decl_stmt|;
DECL|member|pressure_d
name|gboolean
name|pressure_d
decl_stmt|;
DECL|member|pressure_w
name|GtkWidget
modifier|*
name|pressure_w
decl_stmt|;
DECL|member|rate
name|gboolean
name|rate
decl_stmt|;
DECL|member|rate_d
name|gboolean
name|rate_d
decl_stmt|;
DECL|member|rate_w
name|GtkWidget
modifier|*
name|rate_w
decl_stmt|;
DECL|member|size
name|gboolean
name|size
decl_stmt|;
DECL|member|size_d
name|gboolean
name|size_d
decl_stmt|;
DECL|member|size_w
name|GtkWidget
modifier|*
name|size_w
decl_stmt|;
DECL|member|color
name|gboolean
name|color
decl_stmt|;
DECL|member|color_d
name|gboolean
name|color_d
decl_stmt|;
DECL|member|color_w
name|GtkWidget
modifier|*
name|color_w
decl_stmt|;
block|}
struct|;
end_struct

begin_typedef
DECL|typedef|GimpGradientOptions
typedef|typedef
name|struct
name|_GimpGradientOptions
name|GimpGradientOptions
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGradientOptions
struct|struct
name|_GimpGradientOptions
block|{
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|use_fade
name|gboolean
name|use_fade
decl_stmt|;
DECL|member|use_fade_d
name|gboolean
name|use_fade_d
decl_stmt|;
DECL|member|use_fade_w
name|GtkWidget
modifier|*
name|use_fade_w
decl_stmt|;
DECL|member|fade_out
name|gdouble
name|fade_out
decl_stmt|;
DECL|member|fade_out_d
name|gdouble
name|fade_out_d
decl_stmt|;
DECL|member|fade_out_w
name|GtkObject
modifier|*
name|fade_out_w
decl_stmt|;
DECL|member|fade_unit
name|GimpUnit
name|fade_unit
decl_stmt|;
DECL|member|fade_unit_d
name|GimpUnit
name|fade_unit_d
decl_stmt|;
DECL|member|fade_unit_w
name|GtkWidget
modifier|*
name|fade_unit_w
decl_stmt|;
DECL|member|use_gradient
name|gboolean
name|use_gradient
decl_stmt|;
DECL|member|use_gradient_d
name|gboolean
name|use_gradient_d
decl_stmt|;
DECL|member|use_gradient_w
name|GtkWidget
modifier|*
name|use_gradient_w
decl_stmt|;
DECL|member|gradient_length
name|gdouble
name|gradient_length
decl_stmt|;
DECL|member|gradient_length_d
name|gdouble
name|gradient_length_d
decl_stmt|;
DECL|member|gradient_length_w
name|GtkObject
modifier|*
name|gradient_length_w
decl_stmt|;
DECL|member|gradient_unit
name|GimpUnit
name|gradient_unit
decl_stmt|;
DECL|member|gradient_unit_d
name|GimpUnit
name|gradient_unit_d
decl_stmt|;
DECL|member|gradient_unit_w
name|GtkWidget
modifier|*
name|gradient_unit_w
decl_stmt|;
DECL|member|gradient_type
name|gint
name|gradient_type
decl_stmt|;
DECL|member|gradient_type_d
name|gint
name|gradient_type_d
decl_stmt|;
DECL|member|gradient_type_w
name|GtkWidget
modifier|*
name|gradient_type_w
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPaintOptions
struct|struct
name|_GimpPaintOptions
block|{
DECL|member|tool_options
name|GimpToolOptions
name|tool_options
decl_stmt|;
comment|/*  vbox for the common paint options  */
DECL|member|paint_vbox
name|GtkWidget
modifier|*
name|paint_vbox
decl_stmt|;
comment|/*  a widget to be shown if we are in global mode  */
DECL|member|global
name|GtkWidget
modifier|*
name|global
decl_stmt|;
comment|/*  options used by all paint tools  */
DECL|member|opacity_w
name|GtkObject
modifier|*
name|opacity_w
decl_stmt|;
DECL|member|paint_mode_w
name|GtkWidget
modifier|*
name|paint_mode_w
decl_stmt|;
comment|/*  this tool's private context  */
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
comment|/*  the incremental toggle  */
DECL|member|incremental
name|gboolean
name|incremental
decl_stmt|;
DECL|member|incremental_d
name|gboolean
name|incremental_d
decl_stmt|;
DECL|member|incremental_w
name|GtkWidget
modifier|*
name|incremental_w
decl_stmt|;
DECL|member|incremental_save
name|gboolean
name|incremental_save
decl_stmt|;
comment|/*  the pressure-sensitivity options  */
DECL|member|pressure_options
name|GimpPressureOptions
modifier|*
name|pressure_options
decl_stmt|;
comment|/*  the fade out and gradient options  */
DECL|member|gradient_options
name|GimpGradientOptions
modifier|*
name|gradient_options
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  paint tool options functions  */
end_comment

begin_function_decl
name|GimpPaintOptions
modifier|*
name|gimp_paint_options_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_paint_options_init
parameter_list|(
name|GimpPaintOptions
modifier|*
name|options
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PAINT_OPTIONS_H__  */
end_comment

end_unit

