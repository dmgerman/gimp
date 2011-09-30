begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimp3migration.c  * Copyright (C) 2011 Michael Natterer<mitch@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
file|"gimpwidgetstypes.h"
end_include

begin_include
include|#
directive|include
file|"gimp3migration.h"
end_include

begin_function
name|GtkWidget
modifier|*
DECL|function|gtk_box_new (GtkOrientation orientation,gint spacing)
name|gtk_box_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|,
name|gint
name|spacing
parameter_list|)
block|{
if|if
condition|(
name|orientation
operator|==
name|GTK_ORIENTATION_HORIZONTAL
condition|)
return|return
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
name|spacing
argument_list|)
return|;
else|else
return|return
name|gtk_vbox_new
argument_list|(
name|FALSE
argument_list|,
name|spacing
argument_list|)
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gtk_button_box_new (GtkOrientation orientation)
name|gtk_button_box_new
parameter_list|(
name|GtkOrientation
name|orientation
parameter_list|)
block|{
if|if
condition|(
name|orientation
operator|==
name|GTK_ORIENTATION_HORIZONTAL
condition|)
return|return
name|gtk_hbutton_box_new
argument_list|()
return|;
else|else
return|return
name|gtk_vbutton_box_new
argument_list|()
return|;
block|}
end_function

end_unit

