begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp.c  * Copyright (C) 1999-2000 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"sys/types.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpguiconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"pdb/procedural_db.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-ins.h"
end_include

begin_include
include|#
directive|include
file|"plug-in/plug-in.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_ifndef
ifndef|#
directive|ifndef
name|G_OS_WIN32
end_ifndef

begin_define
DECL|macro|DEBUG_HELP
define|#
directive|define
name|DEBUG_HELP
end_define

begin_endif
endif|#
directive|endif
end_endif

begin_typedef
DECL|typedef|GimpIdleHelp
typedef|typedef
name|struct
name|_GimpIdleHelp
name|GimpIdleHelp
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpIdleHelp
struct|struct
name|_GimpIdleHelp
block|{
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|help_path
name|gchar
modifier|*
name|help_path
decl_stmt|;
DECL|member|help_data
name|gchar
modifier|*
name|help_data
decl_stmt|;
block|}
struct|;
end_struct

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gint
name|gimp_idle_help
parameter_list|(
name|gpointer
name|data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gboolean
name|gimp_help_internal
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|current_locale
parameter_list|,
specifier|const
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
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|current_locale
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_help (Gimp * gimp,const gchar * help_path,const gchar * help_data)
name|gimp_help
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_data
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|use_help
condition|)
block|{
name|GimpIdleHelp
modifier|*
name|idle_help
decl_stmt|;
name|idle_help
operator|=
name|g_new0
argument_list|(
name|GimpIdleHelp
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|idle_help
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
if|if
condition|(
name|help_path
operator|&&
name|strlen
argument_list|(
name|help_path
argument_list|)
condition|)
name|idle_help
operator|->
name|help_path
operator|=
name|g_strdup
argument_list|(
name|help_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_data
operator|&&
name|strlen
argument_list|(
name|help_data
argument_list|)
condition|)
name|idle_help
operator|->
name|help_data
operator|=
name|g_strdup
argument_list|(
name|help_data
argument_list|)
expr_stmt|;
name|g_idle_add
argument_list|(
name|gimp_idle_help
argument_list|,
name|idle_help
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|gimp_idle_help (gpointer data)
name|gimp_idle_help
parameter_list|(
name|gpointer
name|data
parameter_list|)
block|{
name|GimpIdleHelp
modifier|*
name|idle_help
decl_stmt|;
name|GimpHelpBrowserType
name|browser
decl_stmt|;
specifier|static
name|gchar
modifier|*
name|current_locale
init|=
literal|"C"
decl_stmt|;
name|idle_help
operator|=
operator|(
name|GimpIdleHelp
operator|*
operator|)
name|data
expr_stmt|;
name|browser
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|idle_help
operator|->
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|help_browser
expr_stmt|;
if|if
condition|(
name|idle_help
operator|->
name|help_data
operator|==
name|NULL
operator|&&
name|browser
operator|!=
name|GIMP_HELP_BROWSER_GIMP
condition|)
name|idle_help
operator|->
name|help_data
operator|=
name|g_strdup
argument_list|(
literal|"introduction.html"
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|DEBUG_HELP
if|if
condition|(
name|idle_help
operator|->
name|help_path
condition|)
name|g_print
argument_list|(
literal|"Help Path: %s\n"
argument_list|,
name|idle_help
operator|->
name|help_path
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"Help Path: NULL\n"
argument_list|)
expr_stmt|;
if|if
condition|(
name|idle_help
operator|->
name|help_data
condition|)
name|g_print
argument_list|(
literal|"Help Page: %s\n"
argument_list|,
name|idle_help
operator|->
name|help_data
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"Help Page: NULL\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
comment|/*  DEBUG_HELP  */
switch|switch
condition|(
name|browser
condition|)
block|{
case|case
name|GIMP_HELP_BROWSER_GIMP
case|:
if|if
condition|(
name|gimp_help_internal
argument_list|(
name|idle_help
operator|->
name|gimp
argument_list|,
name|idle_help
operator|->
name|help_path
argument_list|,
name|current_locale
argument_list|,
name|idle_help
operator|->
name|help_data
argument_list|)
condition|)
break|break;
case|case
name|GIMP_HELP_BROWSER_NETSCAPE
case|:
name|gimp_help_netscape
argument_list|(
name|idle_help
operator|->
name|gimp
argument_list|,
name|idle_help
operator|->
name|help_path
argument_list|,
name|current_locale
argument_list|,
name|idle_help
operator|->
name|help_data
argument_list|)
expr_stmt|;
break|break;
default|default:
break|break;
block|}
if|if
condition|(
name|idle_help
operator|->
name|help_path
condition|)
name|g_free
argument_list|(
name|idle_help
operator|->
name|help_path
argument_list|)
expr_stmt|;
if|if
condition|(
name|idle_help
operator|->
name|help_data
condition|)
name|g_free
argument_list|(
name|idle_help
operator|->
name|help_data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|idle_help
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
DECL|function|gimp_help_internal_not_found_callback (GtkWidget * widget,gboolean use_netscape,gpointer data)
name|gimp_help_internal_not_found_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gboolean
name|use_netscape
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
init|=
name|GIMP
argument_list|(
name|data
argument_list|)
decl_stmt|;
if|if
condition|(
name|use_netscape
condition|)
name|g_object_set
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"help-browser"
argument_list|,
name|GIMP_HELP_BROWSER_NETSCAPE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_main_quit
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gboolean
DECL|function|gimp_help_internal (Gimp * gimp,const gchar * help_path,const gchar * current_locale,const gchar * help_data)
name|gimp_help_internal
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|current_locale
parameter_list|,
specifier|const
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
name|gimp
argument_list|,
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
name|gimp
argument_list|,
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
name|GtkWidget
modifier|*
name|not_found
init|=
name|gimp_query_boolean_box
argument_list|(
name|_
argument_list|(
literal|"Could not find GIMP Help Browser"
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|_
argument_list|(
literal|"Could not find the GIMP Help Browser procedure.\n"
literal|"It probably was not compiled because\n"
literal|"you don't have GtkXmHTML installed."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Use Netscape instead"
argument_list|)
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|gimp_help_internal_not_found_callback
argument_list|,
name|gimp
argument_list|)
decl_stmt|;
name|gtk_widget_show
argument_list|(
name|not_found
argument_list|)
expr_stmt|;
name|gtk_main
argument_list|()
expr_stmt|;
return|return
operator|(
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
operator|->
name|help_browser
operator|!=
name|GIMP_HELP_BROWSER_NETSCAPE
operator|)
return|;
block|}
name|args
operator|=
name|g_new
argument_list|(
name|Argument
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|args
index|[
literal|0
index|]
operator|.
name|arg_type
operator|=
name|GIMP_PDB_INT32
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
name|GIMP_RUN_INTERACTIVE
expr_stmt|;
name|args
index|[
literal|1
index|]
operator|.
name|arg_type
operator|=
name|GIMP_PDB_STRING
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
operator|(
name|gpointer
operator|)
name|help_path
expr_stmt|;
name|args
index|[
literal|2
index|]
operator|.
name|arg_type
operator|=
name|GIMP_PDB_STRING
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
operator|(
name|gpointer
operator|)
name|current_locale
expr_stmt|;
name|args
index|[
literal|3
index|]
operator|.
name|arg_type
operator|=
name|GIMP_PDB_STRING
expr_stmt|;
name|args
index|[
literal|3
index|]
operator|.
name|value
operator|.
name|pdb_pointer
operator|=
operator|(
name|gpointer
operator|)
name|help_data
expr_stmt|;
name|plug_in_run
argument_list|(
name|gimp
argument_list|,
name|proc_rec
argument_list|,
name|args
argument_list|,
literal|4
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
name|gimp
argument_list|,
literal|"extension_gimp_help_browser_temp"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|help_path
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|current_locale
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|help_data
argument_list|,
name|GIMP_PDB_END
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
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_help_netscape (Gimp * gimp,const gchar * help_path,const gchar * current_locale,const gchar * help_data)
name|gimp_help_netscape
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|current_locale
parameter_list|,
specifier|const
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
if|if
condition|(
name|help_data
index|[
literal|0
index|]
operator|==
literal|'/'
condition|)
comment|/* _not_ g_path_is_absolute() */
block|{
name|url
operator|=
name|g_strconcat
argument_list|(
literal|"file:"
argument_list|,
name|help_data
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
else|else
block|{
if|if
condition|(
operator|!
name|help_path
condition|)
block|{
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
block|}
else|else
block|{
name|url
operator|=
name|g_strconcat
argument_list|(
literal|"file:"
argument_list|,
name|help_path
argument_list|,
literal|"/"
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
block|}
block|}
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
name|gimp
argument_list|,
literal|"extension_web_browser"
argument_list|,
operator|&
name|nreturn_vals
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|GIMP_RUN_NONINTERACTIVE
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|url
argument_list|,
name|GIMP_PDB_INT32
argument_list|,
name|FALSE
argument_list|,
name|GIMP_PDB_END
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

