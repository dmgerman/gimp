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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"gimprc-utils.h"
end_include

begin_function
name|gchar
modifier|*
DECL|function|gimp_rc_build_data_path (const gchar * name)
name|gimp_rc_build_data_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
literal|"${gimp_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
literal|"${gimp_data_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_rc_build_writable_path (const gchar * name)
name|gimp_rc_build_writable_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
literal|"${gimp_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_rc_build_plug_in_path (const gchar * name)
name|gimp_rc_build_plug_in_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|g_strconcat
argument_list|(
literal|"${gimp_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|G_SEARCHPATH_SEPARATOR_S
argument_list|,
literal|"${gimp_plug_in_dir}"
argument_list|,
name|G_DIR_SEPARATOR_S
argument_list|,
name|name
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

end_unit

