begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpText  * Copyright (C) 2002-2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<pango/pangocairo.h>
end_include

begin_include
include|#
directive|include
file|"text-types.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout.h"
end_include

begin_include
include|#
directive|include
file|"gimptextlayout-render.h"
end_include

begin_function
name|void
DECL|function|gimp_text_layout_render (GimpTextLayout * layout,cairo_t * cr,GimpTextDirection base_dir,gboolean path)
name|gimp_text_layout_render
parameter_list|(
name|GimpTextLayout
modifier|*
name|layout
parameter_list|,
name|cairo_t
modifier|*
name|cr
parameter_list|,
name|GimpTextDirection
name|base_dir
parameter_list|,
name|gboolean
name|path
parameter_list|)
block|{
name|PangoLayout
modifier|*
name|pango_layout
decl_stmt|;
name|cairo_matrix_t
name|trafo
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_TEXT_LAYOUT
argument_list|(
name|layout
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|cr
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|cairo_save
argument_list|(
name|cr
argument_list|)
expr_stmt|;
name|gimp_text_layout_get_offsets
argument_list|(
name|layout
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|cairo_translate
argument_list|(
name|cr
argument_list|,
name|x
argument_list|,
name|y
argument_list|)
expr_stmt|;
name|gimp_text_layout_get_transform
argument_list|(
name|layout
argument_list|,
operator|&
name|trafo
argument_list|)
expr_stmt|;
name|cairo_transform
argument_list|(
name|cr
argument_list|,
operator|&
name|trafo
argument_list|)
expr_stmt|;
name|pango_layout
operator|=
name|gimp_text_layout_get_pango_layout
argument_list|(
name|layout
argument_list|)
expr_stmt|;
if|if
condition|(
name|path
condition|)
name|pango_cairo_layout_path
argument_list|(
name|cr
argument_list|,
name|pango_layout
argument_list|)
expr_stmt|;
else|else
name|pango_cairo_show_layout
argument_list|(
name|cr
argument_list|,
name|pango_layout
argument_list|)
expr_stmt|;
name|cairo_restore
argument_list|(
name|cr
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

