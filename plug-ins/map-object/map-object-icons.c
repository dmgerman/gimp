begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
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
file|"map-object-icons.h"
end_include

begin_include
include|#
directive|include
file|"../lighting/images/lighting-icon-images.h"
end_include

begin_function
name|void
DECL|function|mapobject_icons_init (void)
name|mapobject_icons_init
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|gboolean
name|initialized
init|=
name|FALSE
decl_stmt|;
name|GtkIconTheme
modifier|*
name|icon_theme
decl_stmt|;
if|if
condition|(
name|initialized
condition|)
return|return;
name|initialized
operator|=
name|TRUE
expr_stmt|;
name|icon_theme
operator|=
name|gtk_icon_theme_get_default
argument_list|()
expr_stmt|;
name|gtk_icon_theme_add_resource_path
argument_list|(
name|icon_theme
argument_list|,
literal|"/org/gimp/lighting/icons"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

