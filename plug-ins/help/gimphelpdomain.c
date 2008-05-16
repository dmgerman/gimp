begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2008 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_comment
comment|/*  This code is written so that it can also be compiled standalone.  *  It shouldn't depend on libgimp.  */
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
file|<glib-object.h>
end_include

begin_include
include|#
directive|include
file|<gio/gio.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"gimphelp.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|DISABLE_NLS
end_ifdef

begin_define
DECL|macro|_ (String)
define|#
directive|define
name|_
parameter_list|(
name|String
parameter_list|)
value|(String)
end_define

begin_else
else|#
directive|else
end_else

begin_include
include|#
directive|include
file|"libgimp/stdplugins-intl.h"
end_include

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|gboolean
name|domain_locale_parse
parameter_list|(
name|GimpHelpDomain
modifier|*
name|domain
parameter_list|,
name|GimpHelpLocale
modifier|*
name|locale
parameter_list|,
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GimpHelpDomain
modifier|*
DECL|function|gimp_help_domain_new (const gchar * domain_name,const gchar * domain_uri)
name|gimp_help_domain_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain_uri
parameter_list|)
block|{
name|GimpHelpDomain
modifier|*
name|domain
init|=
name|g_slice_new0
argument_list|(
name|GimpHelpDomain
argument_list|)
decl_stmt|;
name|domain
operator|->
name|help_domain
operator|=
name|g_strdup
argument_list|(
name|domain_name
argument_list|)
expr_stmt|;
name|domain
operator|->
name|help_uri
operator|=
name|g_strdup
argument_list|(
name|domain_uri
argument_list|)
expr_stmt|;
if|if
condition|(
name|domain_uri
condition|)
block|{
comment|/*  strip trailing slash  */
if|if
condition|(
name|g_str_has_suffix
argument_list|(
name|domain
operator|->
name|help_uri
argument_list|,
literal|"/"
argument_list|)
condition|)
name|domain
operator|->
name|help_uri
index|[
name|strlen
argument_list|(
name|domain
operator|->
name|help_uri
argument_list|)
operator|-
literal|1
index|]
operator|=
literal|'\0'
expr_stmt|;
block|}
return|return
name|domain
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_domain_free (GimpHelpDomain * domain)
name|gimp_help_domain_free
parameter_list|(
name|GimpHelpDomain
modifier|*
name|domain
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|domain
operator|->
name|help_locales
condition|)
name|g_hash_table_destroy
argument_list|(
name|domain
operator|->
name|help_locales
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
operator|->
name|help_domain
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
operator|->
name|help_uri
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpHelpDomain
argument_list|,
name|domain
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpHelpLocale
modifier|*
DECL|function|gimp_help_domain_lookup_locale (GimpHelpDomain * domain,const gchar * locale_id,GimpHelpProgress * progress)
name|gimp_help_domain_lookup_locale
parameter_list|(
name|GimpHelpDomain
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|locale_id
parameter_list|,
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|)
block|{
name|GimpHelpLocale
modifier|*
name|locale
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|domain
operator|->
name|help_locales
condition|)
name|locale
operator|=
name|g_hash_table_lookup
argument_list|(
name|domain
operator|->
name|help_locales
argument_list|,
name|locale_id
argument_list|)
expr_stmt|;
else|else
name|domain
operator|->
name|help_locales
operator|=
name|g_hash_table_new_full
argument_list|(
name|g_str_hash
argument_list|,
name|g_str_equal
argument_list|,
name|g_free
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|gimp_help_locale_free
argument_list|)
expr_stmt|;
if|if
condition|(
name|locale
condition|)
return|return
name|locale
return|;
name|locale
operator|=
name|gimp_help_locale_new
argument_list|(
name|locale_id
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|domain
operator|->
name|help_locales
argument_list|,
name|g_strdup
argument_list|(
name|locale_id
argument_list|)
argument_list|,
name|locale
argument_list|)
expr_stmt|;
name|domain_locale_parse
argument_list|(
name|domain
argument_list|,
name|locale
argument_list|,
name|progress
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|locale
return|;
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|gimp_help_domain_map (GimpHelpDomain * domain,GList * help_locales,const gchar * help_id,GimpHelpProgress * progress,GimpHelpLocale ** ret_locale,gboolean * fatal_error)
name|gimp_help_domain_map
parameter_list|(
name|GimpHelpDomain
modifier|*
name|domain
parameter_list|,
name|GList
modifier|*
name|help_locales
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|,
name|GimpHelpLocale
modifier|*
modifier|*
name|ret_locale
parameter_list|,
name|gboolean
modifier|*
name|fatal_error
parameter_list|)
block|{
name|GimpHelpLocale
modifier|*
name|locale
init|=
name|NULL
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|ref
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_locales
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_id
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|fatal_error
condition|)
operator|*
name|fatal_error
operator|=
name|FALSE
expr_stmt|;
comment|/*  first pass: look for a reference matching the help_id  */
for|for
control|(
name|list
operator|=
name|help_locales
init|;
name|list
operator|&&
operator|!
name|ref
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|locale
operator|=
name|gimp_help_domain_lookup_locale
argument_list|(
name|domain
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|,
name|progress
argument_list|)
expr_stmt|;
name|ref
operator|=
name|gimp_help_locale_map
argument_list|(
name|locale
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
comment|/*  second pass: look for a fallback                 */
for|for
control|(
name|list
operator|=
name|help_locales
init|;
name|list
operator|&&
operator|!
name|ref
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|locale
operator|=
name|gimp_help_domain_lookup_locale
argument_list|(
name|domain
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|,
name|progress
argument_list|)
expr_stmt|;
name|ref
operator|=
name|locale
operator|->
name|help_missing
expr_stmt|;
block|}
if|if
condition|(
name|ret_locale
condition|)
operator|*
name|ret_locale
operator|=
name|locale
expr_stmt|;
if|if
condition|(
name|ref
condition|)
block|{
return|return
name|g_strconcat
argument_list|(
name|domain
operator|->
name|help_uri
argument_list|,
literal|"/"
argument_list|,
name|locale
operator|->
name|locale_id
argument_list|,
literal|"/"
argument_list|,
name|ref
argument_list|,
name|NULL
argument_list|)
return|;
block|}
else|else
comment|/*  try to assemble a useful error message  */
block|{
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help: help_id lookup and all fallbacks failed for '%s'\n"
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|locale
operator|=
name|gimp_help_domain_lookup_locale
argument_list|(
name|domain
argument_list|,
name|GIMP_HELP_DEFAULT_LOCALE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|domain_locale_parse
argument_list|(
name|domain
argument_list|,
name|locale
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
switch|switch
condition|(
name|error
operator|->
name|code
condition|)
block|{
case|case
name|G_IO_ERROR_NOT_FOUND
case|:
name|g_message
argument_list|(
literal|"%s\n\n%s"
argument_list|,
name|_
argument_list|(
literal|"The GIMP user manual is not available."
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Please install the additional help package or use "
literal|"the online user manual at http://docs.gimp.org/."
argument_list|)
argument_list|)
expr_stmt|;
break|break;
case|case
name|G_IO_ERROR_CANCELLED
case|:
break|break;
default|default:
name|g_message
argument_list|(
literal|"%s\n\n%s\n\n%s"
argument_list|,
name|_
argument_list|(
literal|"There is a problem with the GIMP user manual."
argument_list|)
argument_list|,
name|error
operator|->
name|message
argument_list|,
name|_
argument_list|(
literal|"Please check your installation."
argument_list|)
argument_list|)
expr_stmt|;
break|break;
block|}
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
if|if
condition|(
name|fatal_error
condition|)
operator|*
name|fatal_error
operator|=
name|TRUE
expr_stmt|;
block|}
else|else
block|{
name|g_message
argument_list|(
name|_
argument_list|(
literal|"Help ID '%s' unknown"
argument_list|)
argument_list|,
name|help_id
argument_list|)
expr_stmt|;
block|}
return|return
name|NULL
return|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|gboolean
DECL|function|domain_locale_parse (GimpHelpDomain * domain,GimpHelpLocale * locale,GimpHelpProgress * progress,GError ** error)
name|domain_locale_parse
parameter_list|(
name|GimpHelpDomain
modifier|*
name|domain
parameter_list|,
name|GimpHelpLocale
modifier|*
name|locale
parameter_list|,
name|GimpHelpProgress
modifier|*
name|progress
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
name|gchar
modifier|*
name|uri
decl_stmt|;
name|gboolean
name|success
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|domain
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|locale
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|error
operator|==
name|NULL
operator|||
operator|*
name|error
operator|==
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|uri
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s/%s/gimp-help.xml"
argument_list|,
name|domain
operator|->
name|help_uri
argument_list|,
name|locale
operator|->
name|locale_id
argument_list|)
expr_stmt|;
name|success
operator|=
name|gimp_help_locale_parse
argument_list|(
name|locale
argument_list|,
name|uri
argument_list|,
name|domain
operator|->
name|help_domain
argument_list|,
name|progress
argument_list|,
name|error
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|uri
argument_list|)
expr_stmt|;
return|return
name|success
return|;
block|}
end_function

end_unit

