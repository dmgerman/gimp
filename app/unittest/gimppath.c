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

begin_function
DECL|function|show_personal (const char * filename)
name|void
name|show_personal
parameter_list|(
specifier|const
name|char
modifier|*
name|filename
parameter_list|)
block|{
name|char
modifier|*
name|full_filename
init|=
name|gimp_personal_rc_file
argument_list|(
name|filename
argument_list|)
decl_stmt|;
name|g_print
argument_list|(
literal|"%-50s = gimp_personal_rc_file(\"%s\");\n"
argument_list|,
name|full_filename
argument_list|,
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|show_personal_files (void)
name|void
name|show_personal_files
parameter_list|(
name|void
parameter_list|)
block|{
name|show_personal
argument_list|(
literal|"devicerc"
argument_list|)
expr_stmt|;
name|show_personal
argument_list|(
literal|"ideas"
argument_list|)
expr_stmt|;
name|show_personal
argument_list|(
literal|"parasiterc"
argument_list|)
expr_stmt|;
name|show_personal
argument_list|(
literal|"gimprc"
argument_list|)
expr_stmt|;
name|show_personal
argument_list|(
literal|"unitrc"
argument_list|)
expr_stmt|;
name|show_personal
argument_list|(
literal|"menurc"
argument_list|)
expr_stmt|;
name|show_personal
argument_list|(
literal|"pluginrc"
argument_list|)
expr_stmt|;
name|show_personal
argument_list|(
literal|"sessionrc"
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
DECL|function|show_gimp_dirs (void)
name|void
name|show_gimp_dirs
parameter_list|(
name|void
parameter_list|)
block|{
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
name|g_print
argument_list|(
literal|"%-50s = g_get_home_dir();\n"
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%-50s = g_getenv(\"GIMP_DIRECTORY\");\n"
argument_list|,
name|g_getenv
argument_list|(
literal|"GIMP_DIRECTORY"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%-50s = g_getenv(\"GIMP_DATADIR\");\n"
argument_list|,
name|g_getenv
argument_list|(
literal|"GIMP_DATADIR"
argument_list|)
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%-50s = gimp_directory();\n"
argument_list|,
name|gimp_directory
argument_list|()
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%-50s = gimp_data_directory();\n"
argument_list|,
name|gimp_data_directory
argument_list|()
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%-50s = gimp_gtkrc();\n"
argument_list|,
name|gimp_gtkrc
argument_list|()
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"%-50s = gimp_system_rc_file();\n"
argument_list|,
name|gimp_system_rc_file
argument_list|()
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
name|show_gimp_dirs
argument_list|()
expr_stmt|;
name|show_personal_files
argument_list|()
expr_stmt|;
block|}
end_function

end_unit

