begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpstroke-new.c  * Copyright (C) 2006 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"vectors-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcoords.h"
end_include

begin_include
include|#
directive|include
file|"gimpstroke-new.h"
end_include

begin_include
include|#
directive|include
file|"gimpbezierstroke.h"
end_include

begin_function
name|GimpStroke
modifier|*
DECL|function|gimp_stroke_new_from_coords (GimpVectorsStrokeType type,const GimpCoords * coords,gint n_coords,gboolean closed)
name|gimp_stroke_new_from_coords
parameter_list|(
name|GimpVectorsStrokeType
name|type
parameter_list|,
specifier|const
name|GimpCoords
modifier|*
name|coords
parameter_list|,
name|gint
name|n_coords
parameter_list|,
name|gboolean
name|closed
parameter_list|)
block|{
switch|switch
condition|(
name|type
condition|)
block|{
case|case
name|GIMP_VECTORS_STROKE_TYPE_BEZIER
case|:
return|return
name|gimp_bezier_stroke_new_from_coords
argument_list|(
name|coords
argument_list|,
name|n_coords
argument_list|,
name|closed
argument_list|)
return|;
break|break;
default|default:
name|g_warning
argument_list|(
literal|"unknown type in gimp_stroke_new_from_coords(): %d"
argument_list|,
name|type
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
block|}
end_function

end_unit

