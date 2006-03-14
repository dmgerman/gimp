begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/* NOTE: This file is autogenerated by pdbgen.pl. */
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
file|"pdb-types.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer-filter.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"text/gimp-fonts.h"
end_include

begin_decl_stmt
DECL|variable|fonts_refresh_proc
specifier|static
name|ProcRecord
name|fonts_refresh_proc
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fonts_get_list_proc
specifier|static
name|ProcRecord
name|fonts_get_list_proc
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|register_fonts_procs (Gimp * gimp)
name|register_fonts_procs
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|fonts_refresh_proc
argument_list|)
expr_stmt|;
name|procedural_db_register
argument_list|(
name|gimp
argument_list|,
operator|&
name|fonts_get_list_proc
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|fonts_refresh_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|fonts_refresh_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gimp_fonts_load
argument_list|(
name|gimp
argument_list|)
expr_stmt|;
return|return
name|procedural_db_return_args
argument_list|(
operator|&
name|fonts_refresh_proc
argument_list|,
name|TRUE
argument_list|)
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|fonts_refresh_proc
specifier|static
name|ProcRecord
name|fonts_refresh_proc
init|=
block|{
literal|"gimp-fonts-refresh"
block|,
literal|"gimp-fonts-refresh"
block|,
literal|"Refresh current fonts. This function always succeeds."
block|,
literal|"This procedure retrieves all fonts currently in the user's font path and updates the font dialogs accordingly."
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"Sven Neumann"
block|,
literal|"2003"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|0
block|,
name|NULL
block|,
literal|0
block|,
name|NULL
block|,
block|{
block|{
name|fonts_refresh_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_function
specifier|static
name|Argument
modifier|*
DECL|function|fonts_get_list_invoker (Gimp * gimp,GimpContext * context,GimpProgress * progress,Argument * args)
name|fonts_get_list_invoker
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|,
name|Argument
modifier|*
name|args
parameter_list|)
block|{
name|gboolean
name|success
init|=
name|TRUE
decl_stmt|;
name|Argument
modifier|*
name|return_args
decl_stmt|;
name|gchar
modifier|*
name|filter
decl_stmt|;
name|gint32
name|num_fonts
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|font_list
init|=
name|NULL
decl_stmt|;
name|filter
operator|=
operator|(
name|gchar
operator|*
operator|)
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_pointer
expr_stmt|;
if|if
condition|(
name|filter
operator|&&
operator|!
name|g_utf8_validate
argument_list|(
name|filter
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|)
condition|)
name|success
operator|=
name|FALSE
expr_stmt|;
if|if
condition|(
name|success
condition|)
name|font_list
operator|=
name|gimp_container_get_filtered_name_array
argument_list|(
name|gimp
operator|->
name|fonts
argument_list|,
name|filter
argument_list|,
operator|&
name|num_fonts
argument_list|)
expr_stmt|;
name|return_args
operator|=
name|procedural_db_return_args
argument_list|(
operator|&
name|fonts_get_list_proc
argument_list|,
name|success
argument_list|)
expr_stmt|;
if|if
condition|(
name|success
condition|)
block|{
name|return_args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|num_fonts
expr_stmt|;
name|return_args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|font_list
expr_stmt|;
block|}
return|return
name|return_args
return|;
block|}
end_function

begin_decl_stmt
DECL|variable|fonts_get_list_inargs
specifier|static
name|ProcArg
name|fonts_get_list_inargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_STRING
block|,
literal|"filter"
block|,
literal|"An optional regular expression used to filter the list"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fonts_get_list_outargs
specifier|static
name|ProcArg
name|fonts_get_list_outargs
index|[]
init|=
block|{
block|{
name|GIMP_PDB_INT32
block|,
literal|"num-fonts"
block|,
literal|"The number of available fonts"
block|}
block|,
block|{
name|GIMP_PDB_STRINGARRAY
block|,
literal|"font-list"
block|,
literal|"The list of font names"
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
DECL|variable|fonts_get_list_proc
specifier|static
name|ProcRecord
name|fonts_get_list_proc
init|=
block|{
literal|"gimp-fonts-get-list"
block|,
literal|"gimp-fonts-get-list"
block|,
literal|"Retrieve the list of loaded fonts."
block|,
literal|"This procedure returns a list of the fonts that are currently available."
block|,
literal|"Sven Neumann<sven@gimp.org>"
block|,
literal|"Sven Neumann"
block|,
literal|"2003"
block|,
name|NULL
block|,
name|GIMP_INTERNAL
block|,
literal|1
block|,
name|fonts_get_list_inargs
block|,
literal|2
block|,
name|fonts_get_list_outargs
block|,
block|{
block|{
name|fonts_get_list_invoker
block|}
block|}
block|}
decl_stmt|;
end_decl_stmt

end_unit

