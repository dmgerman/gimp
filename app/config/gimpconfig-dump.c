begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpConfig object property dumper.   * Copyright (C) 2001-2002  Sven Neumann<sven@gimp.org>  *   * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"stdlib.h"
end_include

begin_include
include|#
directive|include
file|"string.h"
end_include

begin_include
include|#
directive|include
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"config-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-serialize.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_function
name|int
DECL|function|main (int argc,char * argv[])
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
name|argv
index|[]
parameter_list|)
block|{
name|GObject
modifier|*
name|rc
decl_stmt|;
name|g_type_init
argument_list|()
expr_stmt|;
name|rc
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_RC
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"# Dump of the GIMP default configuration\n\n"
argument_list|)
expr_stmt|;
name|gimp_config_serialize_properties
argument_list|(
name|rc
argument_list|,
literal|1
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|rc
argument_list|)
expr_stmt|;
return|return
name|EXIT_SUCCESS
return|;
block|}
end_function

begin_comment
comment|/* some dummy funcs so we can properly link this beast */
end_comment

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_unit_get_identifier (GimpUnit unit)
name|gimp_unit_get_identifier
parameter_list|(
name|GimpUnit
name|unit
parameter_list|)
block|{
switch|switch
condition|(
name|unit
condition|)
block|{
case|case
name|GIMP_UNIT_PIXEL
case|:
return|return
literal|"pixels"
return|;
case|case
name|GIMP_UNIT_INCH
case|:
return|return
literal|"inches"
return|;
case|case
name|GIMP_UNIT_MM
case|:
return|return
literal|"millimeters"
return|;
case|case
name|GIMP_UNIT_POINT
case|:
return|return
literal|"points"
return|;
case|case
name|GIMP_UNIT_PICA
case|:
return|return
literal|"picas"
return|;
default|default:
return|return
name|NULL
return|;
block|}
block|}
end_function

begin_function
name|gint
DECL|function|gimp_unit_get_number_of_units (void)
name|gimp_unit_get_number_of_units
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|GIMP_UNIT_END
return|;
block|}
end_function

end_unit

