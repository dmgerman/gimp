begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp.c  * Copyright (C) 1999 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|HAVE_UNISTD_H
end_ifdef

begin_include
include|#
directive|include
file|<unistd.h>
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"plug_in.h"
end_include

begin_include
include|#
directive|include
file|"procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|DEBUG_HELP
define|#
directive|define
name|DEBUG_HELP
end_define

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gint
name|gimp_idle_help
parameter_list|(
name|gpointer
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_help_internal
parameter_list|(
name|gchar
modifier|*
name|current_locale
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_help_netscape
parameter_list|(
name|gchar
modifier|*
name|current_locale
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  public functions  */
end_comment

begin_comment
comment|/**********************/
end_comment

begin_comment
comment|/*  The standard help function  */
end_comment

begin_function
name|void
DECL|function|gimp_standard_help_func (gchar * help_data)
name|gimp_standard_help_func
parameter_list|(
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|gimp_help
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  the main help function  */
end_comment

begin_function
name|void
DECL|function|gimp_help (gchar * help_data)
name|gimp_help
parameter_list|(
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
if|if
condition|(
name|use_help
condition|)
block|{
if|if
condition|(
name|help_data
condition|)
name|help_data
operator|=
name|g_strdup
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
name|gtk_idle_add
argument_list|(
operator|(
name|GtkFunction
operator|)
name|gimp_idle_help
argument_list|,
operator|(
name|gpointer
operator|)
name|help_data
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*********************/
end_comment

begin_comment
comment|/*  local functions  */
end_comment

begin_comment
comment|/*********************/
end_comment

begin_function
specifier|static
name|gint
DECL|function|gimp_idle_help (gpointer help_data)
name|gimp_idle_help
parameter_list|(
name|gpointer
name|help_data
parameter_list|)
block|{
specifier|static
name|gchar
modifier|*
name|current_locale
init|=
literal|"C"
decl_stmt|;
if|if
condition|(
name|help_data
operator|==
name|NULL
operator|&&
name|help_browser
operator|!=
name|HELP_BROWSER_GIMP
condition|)
name|help_data
operator|=
name|g_strdup
argument_list|(
literal|"welcome.html"
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_HELP
name|g_print
argument_list|(
literal|"Help Page: %s\n"
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|help_data
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/*  DEBUG_HELP  */
switch|switch
condition|(
name|help_browser
condition|)
block|{
case|case
name|HELP_BROWSER_GIMP
case|:
name|gimp_help_internal
argument_list|(
name|current_locale
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|help_data
argument_list|)
expr_stmt|;
break|break;
case|case
name|HELP_BROWSER_NETSCAPE
case|:
name|gimp_help_netscape
argument_list|(
name|current_locale
argument_list|,
operator|(
name|gchar
operator|*
operator|)
name|help_data
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|help_data
condition|)
name|g_free
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_help_internal (gchar * current_locale,gchar * help_data)
name|gimp_help_internal
parameter_list|(
name|gchar
modifier|*
name|current_locale
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|proc_rec
decl_stmt|;
comment|/*  Check if a help browser is already running  */
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
literal|"extension_gimp_help_browser_temp"
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_rec
operator|==
name|NULL
condition|)
block|{
name|Argument
modifier|*
name|args
init|=
name|NULL
decl_stmt|;
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
literal|"extension_gimp_help_browser"
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_rec
operator|==
name|NULL
condition|)
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Could not find the GIMP Help Browser procedure.\n"
literal|"It probably was not compiled because\n"
literal|"you don't have GtkXmHTML installed."
argument_list|)
argument_list|)
expr_stmt|;
return|return;
block|}
name|args
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|3
argument_list|)
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|=
name|PDB_INT32
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|value
operator|.
name|pdb_int
operator|=
name|RUN_INTERACTIVE
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|=
name|PDB_STRING
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|current_locale
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|=
name|PDB_STRING
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
name|help_data
expr_stmt|;
name|plug_in_run
argument_list|(
name|proc_rec
argument_list|,
name|args
argument_list|,
literal|3
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|args
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
literal|"extension_gimp_help_browser_temp"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PDB_STRING
argument_list|,
name|current_locale
argument_list|,
name|PDB_STRING
argument_list|,
name|help_data
argument_list|,
name|PDB_END
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_help_netscape (gchar * current_locale,gchar * help_data)
name|gimp_help_netscape
parameter_list|(
name|gchar
modifier|*
name|current_locale
parameter_list|,
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|nreturn_vals
decl_stmt|;
name|gchar
modifier|*
name|url
decl_stmt|;
name|url
operator|=
name|g_strconcat
argument_list|(
literal|"file:"
argument_list|,
name|gimp_data_directory
argument_list|()
argument_list|,
literal|"/help/"
argument_list|,
name|current_locale
argument_list|,
literal|"/"
argument_list|,
name|help_data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
literal|"extension_web_browser"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|PDB_INT32
argument_list|,
name|RUN_NONINTERACTIVE
argument_list|,
name|PDB_STRING
argument_list|,
name|url
argument_list|,
name|PDB_INT32
argument_list|,
name|FALSE
argument_list|,
name|PDB_END
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|nreturn_vals
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|url
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

