begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"unittest.h"
end_include

begin_include
include|#
directive|include
file|"globals.c"
end_include

begin_include
include|#
directive|include
file|"../plug_in.c"
end_include

begin_if
if|#
directive|if
literal|1
end_if

begin_include
include|#
directive|include
file|"../gimprc.c"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_define
DECL|macro|DPRINTF
define|#
directive|define
name|DPRINTF
value|if (0) printf
end_define

begin_function
specifier|static
name|void
DECL|function|plug_in_init_file2 (char * filename)
name|plug_in_init_file2
parameter_list|(
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|char
modifier|*
name|plug_in_name
decl_stmt|;
name|char
modifier|*
name|name
decl_stmt|;
name|name
operator|=
name|strrchr
argument_list|(
name|filename
argument_list|,
name|G_DIR_SEPARATOR
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
condition|)
name|name
operator|=
name|name
operator|+
literal|1
expr_stmt|;
else|else
name|name
operator|=
name|filename
expr_stmt|;
name|printf
argument_list|(
literal|"%s\n"
argument_list|,
name|g_strdup
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|int
DECL|function|main (int argc,char ** argv)
name|main
parameter_list|(
name|int
name|argc
parameter_list|,
name|char
modifier|*
modifier|*
name|argv
parameter_list|)
block|{
if|if
condition|(
name|argc
operator|<
literal|2
condition|)
block|{
name|printf
argument_list|(
literal|"ex: %s %s/plug-ins \n"
argument_list|,
name|argv
index|[
literal|0
index|]
argument_list|,
name|gimp_directory
argument_list|()
argument_list|)
expr_stmt|;
name|exit
argument_list|(
literal|0
argument_list|)
expr_stmt|;
block|}
name|g_print
argument_list|(
literal|"%s %s\n"
argument_list|,
name|_
argument_list|(
literal|"GIMP version"
argument_list|)
argument_list|,
name|GIMP_VERSION
argument_list|)
expr_stmt|;
name|plug_in_path
operator|=
name|argv
index|[
literal|1
index|]
expr_stmt|;
name|datafiles_read_directories
argument_list|(
name|plug_in_path
argument_list|,
name|plug_in_init_file2
argument_list|,
name|MODE_EXECUTABLE
argument_list|)
expr_stmt|;
return|return
literal|0
return|;
block|}
end_function

end_unit

