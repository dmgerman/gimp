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
file|<glib.h>
end_include

begin_include
include|#
directive|include
file|"libgimpcolor/gimpcolor.h"
end_include

begin_include
include|#
directive|include
file|"apptypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"libgimp_glue.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_palette_set_foreground (const GimpRGB * color)
name|gimp_palette_set_foreground
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_foreground
argument_list|(
name|NULL
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_palette_get_foreground (GimpRGB * color)
name|gimp_palette_get_foreground
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_get_foreground
argument_list|(
name|NULL
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_palette_set_background (const GimpRGB * color)
name|gimp_palette_set_background
parameter_list|(
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_background
argument_list|(
name|NULL
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_palette_get_background (GimpRGB * color)
name|gimp_palette_get_background
parameter_list|(
name|GimpRGB
modifier|*
name|color
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|color
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_get_background
argument_list|(
name|NULL
argument_list|,
name|color
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

end_unit

