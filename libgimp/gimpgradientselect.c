begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2000 Peter Mattis and Spencer Kimball  *  * gimpgradientselect.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|gchar
modifier|*
DECL|function|gimp_gradients_get_gradient_data (gchar * name,gint * width,gint sample_size,gdouble ** grad_data)
name|gimp_gradients_get_gradient_data
parameter_list|(
name|gchar
modifier|*
name|name
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
name|sample_size
parameter_list|,
name|gdouble
modifier|*
modifier|*
name|grad_data
parameter_list|)
block|{
return|return
name|_gimp_gradients_get_gradient_data
argument_list|(
name|name
argument_list|,
name|sample_size
argument_list|,
name|width
argument_list|,
name|grad_data
argument_list|)
return|;
block|}
end_function

end_unit

