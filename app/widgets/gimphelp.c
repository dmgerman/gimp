begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimphelp.c  * Copyright (C) 1999-2004 Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
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
file|"core/gimp-utils.h"
end_include

begin_include
include|#
directive|include
file|"pdb/gimpprocedure.h"
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
file|"plug-in/plug-in-run.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"gimpmessagebox.h"
end_include

begin_include
include|#
directive|include
file|"gimpmessagedialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_comment
comment|/*  #define GIMP_HELP_DEBUG  */
end_comment

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
DECL|member|help_domain
name|gchar
modifier|*
name|help_domain
decl_stmt|;
DECL|member|help_locales
name|gchar
modifier|*
name|help_locales
decl_stmt|;
DECL|member|help_id
name|gchar
modifier|*
name|help_id
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
name|gimp_help_browser
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_help_browser_error
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|primary
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_help_call
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|gchar
modifier|*
name|gimp_help_get_locales
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|void
DECL|function|gimp_help_show (Gimp * gimp,const gchar * help_domain,const gchar * help_id)
name|gimp_help_show
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|GimpGuiConfig
modifier|*
name|config
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|config
operator|=
name|GIMP_GUI_CONFIG
argument_list|(
name|gimp
operator|->
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
name|config
operator|->
name|use_help
condition|)
block|{
name|GimpIdleHelp
modifier|*
name|idle_help
init|=
name|g_new0
argument_list|(
name|GimpIdleHelp
argument_list|,
literal|1
argument_list|)
decl_stmt|;
name|idle_help
operator|->
name|gimp
operator|=
name|gimp
expr_stmt|;
if|if
condition|(
name|help_domain
operator|&&
name|strlen
argument_list|(
name|help_domain
argument_list|)
condition|)
name|idle_help
operator|->
name|help_domain
operator|=
name|g_strdup
argument_list|(
name|help_domain
argument_list|)
expr_stmt|;
name|idle_help
operator|->
name|help_locales
operator|=
name|gimp_help_get_locales
argument_list|(
name|config
argument_list|)
expr_stmt|;
if|if
condition|(
name|help_id
operator|&&
name|strlen
argument_list|(
name|help_id
argument_list|)
condition|)
name|idle_help
operator|->
name|help_id
operator|=
name|g_strdup
argument_list|(
name|help_id
argument_list|)
expr_stmt|;
name|g_idle_add
argument_list|(
name|gimp_idle_help
argument_list|,
name|idle_help
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp
operator|->
name|be_verbose
condition|)
name|g_print
argument_list|(
literal|"HELP: request for help-id '%s' from help-domain '%s'\n"
argument_list|,
name|help_id
condition|?
name|help_id
else|:
literal|"(null)"
argument_list|,
name|help_domain
condition|?
name|help_domain
else|:
literal|"(null)"
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
init|=
name|data
decl_stmt|;
name|GimpGuiConfig
modifier|*
name|config
init|=
name|GIMP_GUI_CONFIG
argument_list|(
name|idle_help
operator|->
name|gimp
operator|->
name|config
argument_list|)
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|procedure
init|=
name|NULL
decl_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"Help Domain: %s\n"
argument_list|,
name|idle_help
operator|->
name|help_domain
condition|?
name|idle_help
operator|->
name|help_domain
else|:
literal|"NULL"
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"Help ID: %s\n\n"
argument_list|,
name|idle_help
operator|->
name|help_id
condition|?
name|idle_help
operator|->
name|help_id
else|:
literal|"NULL"
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|config
operator|->
name|help_browser
operator|==
name|GIMP_HELP_BROWSER_GIMP
condition|)
block|{
if|if
condition|(
name|gimp_help_browser
argument_list|(
name|idle_help
operator|->
name|gimp
argument_list|)
condition|)
name|procedure
operator|=
literal|"extension-gimp-help-browser-temp"
expr_stmt|;
block|}
if|if
condition|(
name|config
operator|->
name|help_browser
operator|==
name|GIMP_HELP_BROWSER_WEB_BROWSER
condition|)
block|{
comment|/*  FIXME: should check for procedure availability  */
name|procedure
operator|=
literal|"plug-in-web-browser"
expr_stmt|;
block|}
if|if
condition|(
name|procedure
condition|)
name|gimp_help_call
argument_list|(
name|idle_help
operator|->
name|gimp
argument_list|,
name|procedure
argument_list|,
name|idle_help
operator|->
name|help_domain
argument_list|,
name|idle_help
operator|->
name|help_locales
argument_list|,
name|idle_help
operator|->
name|help_id
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|idle_help
operator|->
name|help_domain
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|idle_help
operator|->
name|help_locales
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|idle_help
operator|->
name|help_id
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
name|gboolean
DECL|function|gimp_help_browser (Gimp * gimp)
name|gimp_help_browser
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
specifier|static
name|gboolean
name|busy
init|=
name|FALSE
decl_stmt|;
name|ProcRecord
modifier|*
name|proc_rec
decl_stmt|;
if|if
condition|(
name|busy
condition|)
return|return
name|TRUE
return|;
name|busy
operator|=
name|TRUE
expr_stmt|;
comment|/*  Check if a help browser is already running  */
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
literal|"extension-gimp-help-browser-temp"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_rec
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
literal|"extension-gimp-help-browser"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_rec
condition|)
block|{
name|gimp_help_browser_error
argument_list|(
name|gimp
argument_list|,
name|_
argument_list|(
literal|"Help browser not found"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Could not find GIMP help browser."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"The GIMP help browser plug-in appears "
literal|"to be missing from your installation."
argument_list|)
argument_list|)
expr_stmt|;
name|busy
operator|=
name|FALSE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|proc_rec
argument_list|)
expr_stmt|;
name|g_value_set_enum
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|GIMP_RUN_INTERACTIVE
argument_list|)
expr_stmt|;
name|plug_in_run
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|,
name|proc_rec
argument_list|,
name|args
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|args
argument_list|,
literal|1
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
comment|/*  Check if the help browser started properly  */
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
literal|"extension-gimp-help-browser-temp"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_rec
condition|)
block|{
name|gimp_help_browser_error
argument_list|(
name|gimp
argument_list|,
name|_
argument_list|(
literal|"Help browser doesn't start"
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Could not start the GIMP help browser plug-in."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|busy
operator|=
name|FALSE
expr_stmt|;
return|return
name|FALSE
return|;
block|}
name|busy
operator|=
name|FALSE
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_help_browser_error (Gimp * gimp,const gchar * title,const gchar * primary,const gchar * text)
name|gimp_help_browser_error
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|primary
parameter_list|,
specifier|const
name|gchar
modifier|*
name|text
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|dialog
operator|=
name|gimp_message_dialog_new
argument_list|(
name|title
argument_list|,
name|GIMP_STOCK_WARNING
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|_
argument_list|(
literal|"Use _web browser instead"
argument_list|)
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_message_box_set_primary_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|primary
argument_list|)
expr_stmt|;
name|gimp_message_box_set_text
argument_list|(
name|GIMP_MESSAGE_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|box
argument_list|,
name|text
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimp_dialog_run
argument_list|(
name|GIMP_DIALOG
argument_list|(
name|dialog
argument_list|)
argument_list|)
operator|==
name|GTK_RESPONSE_OK
condition|)
name|g_object_set
argument_list|(
name|gimp
operator|->
name|config
argument_list|,
literal|"help-browser"
argument_list|,
name|GIMP_HELP_BROWSER_WEB_BROWSER
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_help_call (Gimp * gimp,const gchar * procedure,const gchar * help_domain,const gchar * help_locales,const gchar * help_id)
name|gimp_help_call
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|procedure
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
block|{
name|ProcRecord
modifier|*
name|proc_rec
decl_stmt|;
comment|/*  Check if a help parser is already running  */
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
literal|"extension-gimp-help-temp"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_rec
condition|)
block|{
name|Argument
modifier|*
name|args
init|=
name|NULL
decl_stmt|;
name|gint
name|n_domains
init|=
literal|0
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|help_domains
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|help_uris
init|=
name|NULL
decl_stmt|;
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
literal|"extension-gimp-help"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|proc_rec
condition|)
comment|/*  FIXME: error msg  */
return|return;
name|n_domains
operator|=
name|plug_ins_help_domains
argument_list|(
name|gimp
argument_list|,
operator|&
name|help_domains
argument_list|,
operator|&
name|help_uris
argument_list|)
expr_stmt|;
name|args
operator|=
name|gimp_procedure_get_arguments
argument_list|(
name|proc_rec
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|args
index|[
literal|0
index|]
operator|.
name|value
argument_list|,
name|n_domains
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|args
index|[
literal|1
index|]
operator|.
name|value
argument_list|,
name|help_domains
argument_list|)
expr_stmt|;
name|g_value_set_int
argument_list|(
operator|&
name|args
index|[
literal|2
index|]
operator|.
name|value
argument_list|,
name|n_domains
argument_list|)
expr_stmt|;
name|g_value_set_pointer
argument_list|(
operator|&
name|args
index|[
literal|3
index|]
operator|.
name|value
argument_list|,
name|help_uris
argument_list|)
expr_stmt|;
name|plug_in_run
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
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
operator|-
literal|1
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|args
argument_list|,
literal|4
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
comment|/*  Check if the help parser started properly  */
name|proc_rec
operator|=
name|procedural_db_lookup
argument_list|(
name|gimp
argument_list|,
literal|"extension-gimp-help-temp"
argument_list|)
expr_stmt|;
if|if
condition|(
name|proc_rec
condition|)
block|{
name|Argument
modifier|*
name|return_vals
decl_stmt|;
name|gint
name|n_return_vals
decl_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"Calling help via %s: %s %s %s\n"
argument_list|,
name|procedure
argument_list|,
name|help_domain
condition|?
name|help_domain
else|:
literal|"(null)"
argument_list|,
name|help_locales
condition|?
name|help_locales
else|:
literal|"(null)"
argument_list|,
name|help_id
condition|?
name|help_id
else|:
literal|"(null)"
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|return_vals
operator|=
name|procedural_db_run_proc
argument_list|(
name|gimp
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|,
literal|"extension-gimp-help-temp"
argument_list|,
operator|&
name|n_return_vals
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|procedure
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|help_domain
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|help_locales
argument_list|,
name|GIMP_PDB_STRING
argument_list|,
name|help_id
argument_list|,
name|GIMP_PDB_END
argument_list|)
expr_stmt|;
name|procedural_db_destroy_args
argument_list|(
name|return_vals
argument_list|,
name|n_return_vals
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_help_get_locales (GimpGuiConfig * config)
name|gimp_help_get_locales
parameter_list|(
name|GimpGuiConfig
modifier|*
name|config
parameter_list|)
block|{
if|if
condition|(
name|config
operator|->
name|help_locales
operator|&&
name|strlen
argument_list|(
name|config
operator|->
name|help_locales
argument_list|)
condition|)
return|return
name|g_strdup
argument_list|(
name|config
operator|->
name|help_locales
argument_list|)
return|;
return|return
name|g_strjoinv
argument_list|(
literal|":"
argument_list|,
operator|(
name|gchar
operator|*
operator|*
operator|)
name|g_get_language_names
argument_list|()
argument_list|)
return|;
block|}
end_function

end_unit

