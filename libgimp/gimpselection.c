begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpselection.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_selection_float:  * @image_ID: ignored  * @drawable_ID: The drawable from which to float selection.  * @offx: x offset for translation.  * @offy: y offset for translation.  *  * Float the selection from the specified drawable with initial offsets  * as specified.  *  * This procedure determines the region of the specified drawable that  * lies beneath the current selection. The region is then cut from the  * drawable and the resulting data is made into a new layer which is  * instantiated as a floating selection. The offsets allow initial  * positioning of the new floating selection.  *  * Returns: The floated layer.  */
end_comment

begin_function
name|gint32
DECL|function|gimp_selection_float (gint32 image_ID,gint32 drawable_ID,gint offx,gint offy)
name|gimp_selection_float
parameter_list|(
name|gint32
name|image_ID
parameter_list|,
name|gint32
name|drawable_ID
parameter_list|,
name|gint
name|offx
parameter_list|,
name|gint
name|offy
parameter_list|)
block|{
return|return
name|_gimp_selection_float
argument_list|(
name|drawable_ID
argument_list|,
name|offx
argument_list|,
name|offy
argument_list|)
return|;
block|}
end_function

end_unit

