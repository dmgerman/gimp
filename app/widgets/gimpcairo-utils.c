begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcairo-utils.c  * Copyright (C) 2007 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpcairo-utils.h"
end_include

begin_function
name|void
DECL|function|gimp_cairo_set_source_color (cairo_t * cr,GimpRGB * color)
name|gimp_cairo_set_source_color
parameter_list|(
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|cairo_set_source_rgb
argument_list|(
name|cr
argument_list|,
name|color
operator|->
name|r
argument_list|,
name|color
operator|->
name|g
argument_list|,
name|color
operator|->
name|b
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

