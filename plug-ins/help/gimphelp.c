begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * The GIMP Help plug-in  * Copyright (C) 1999-2004 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *                         Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
comment|/*  private variables  */
end_comment

begin_decl_stmt
DECL|variable|domain_hash
specifier|static
name|GHashTable
modifier|*
name|domain_hash
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_help_init (gint num_domain_names,gchar ** domain_names,gint num_domain_uris,gchar ** domain_uris)
name|gimp_help_init
parameter_list|(
name|gint
name|num_domain_names
parameter_list|,
name|gchar
modifier|*
modifier|*
name|domain_names
parameter_list|,
name|gint
name|num_domain_uris
parameter_list|,
name|gchar
modifier|*
modifier|*
name|domain_uris
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|default_env_domain_uri
decl_stmt|;
name|gchar
modifier|*
name|default_domain_uri
decl_stmt|;
name|gint
name|i
decl_stmt|;
if|if
condition|(
name|num_domain_names
operator|!=
name|num_domain_uris
condition|)
block|{
name|g_printerr
argument_list|(
literal|"help: number of names doesn't match number of URIs.\n"
argument_list|)
expr_stmt|;
return|return
name|FALSE
return|;
block|}
comment|/*  set default values  */
name|default_env_domain_uri
operator|=
name|g_getenv
argument_list|(
name|GIMP_HELP_ENV_URI
argument_list|)
expr_stmt|;
if|if
condition|(
name|default_env_domain_uri
condition|)
block|{
name|default_domain_uri
operator|=
name|g_strdup
argument_list|(
name|default_env_domain_uri
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|help_root
init|=
name|g_build_filename
argument_list|(
name|gimp_data_directory
argument_list|()
argument_list|,
name|GIMP_HELP_PREFIX
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
name|default_domain_uri
operator|=
name|g_filename_to_uri
argument_list|(
name|help_root
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|help_root
argument_list|)
expr_stmt|;
block|}
name|gimp_help_register_domain
argument_list|(
name|GIMP_HELP_DEFAULT_DOMAIN
argument_list|,
name|default_domain_uri
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|num_domain_names
condition|;
name|i
operator|++
control|)
name|gimp_help_register_domain
argument_list|(
name|domain_names
index|[
name|i
index|]
argument_list|,
name|domain_uris
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|default_domain_uri
argument_list|)
expr_stmt|;
return|return
name|TRUE
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_exit (void)
name|gimp_help_exit
parameter_list|(
name|void
parameter_list|)
block|{
if|if
condition|(
name|domain_hash
condition|)
block|{
name|g_hash_table_destroy
argument_list|(
name|domain_hash
argument_list|)
expr_stmt|;
name|domain_hash
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_help_register_domain (const gchar * domain_name,const gchar * domain_uri)
name|gimp_help_register_domain
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
name|g_return_if_fail
argument_list|(
name|domain_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|domain_uri
operator|!=
name|NULL
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help: registering help domain \"%s\" with base uri \"%s\"\n"
argument_list|,
name|domain_name
argument_list|,
name|domain_uri
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
operator|!
name|domain_hash
condition|)
name|domain_hash
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
name|gimp_help_domain_free
argument_list|)
expr_stmt|;
name|g_hash_table_insert
argument_list|(
name|domain_hash
argument_list|,
name|g_strdup
argument_list|(
name|domain_name
argument_list|)
argument_list|,
name|gimp_help_domain_new
argument_list|(
name|domain_name
argument_list|,
name|domain_uri
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GimpHelpDomain
modifier|*
DECL|function|gimp_help_lookup_domain (const gchar * domain_name)
name|gimp_help_lookup_domain
parameter_list|(
specifier|const
name|gchar
modifier|*
name|domain_name
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|domain_name
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|domain_hash
condition|)
return|return
name|g_hash_table_lookup
argument_list|(
name|domain_hash
argument_list|,
name|domain_name
argument_list|)
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|GList
modifier|*
DECL|function|gimp_help_parse_locales (const gchar * help_locales)
name|gimp_help_parse_locales
parameter_list|(
specifier|const
name|gchar
modifier|*
name|help_locales
parameter_list|)
block|{
name|GList
modifier|*
name|locales
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|list
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|s
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_locales
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
comment|/*  split the string at colons, building a list  */
name|s
operator|=
name|help_locales
expr_stmt|;
for|for
control|(
name|p
operator|=
name|strchr
argument_list|(
name|s
argument_list|,
literal|':'
argument_list|)
init|;
name|p
condition|;
name|p
operator|=
name|strchr
argument_list|(
name|s
argument_list|,
literal|':'
argument_list|)
control|)
block|{
name|gchar
modifier|*
name|new
init|=
name|g_strndup
argument_list|(
name|s
argument_list|,
name|p
operator|-
name|s
argument_list|)
decl_stmt|;
name|locales
operator|=
name|g_list_append
argument_list|(
name|locales
argument_list|,
name|new
argument_list|)
expr_stmt|;
name|s
operator|=
name|p
operator|+
literal|1
expr_stmt|;
block|}
if|if
condition|(
operator|*
name|s
condition|)
name|locales
operator|=
name|g_list_append
argument_list|(
name|locales
argument_list|,
name|g_strdup
argument_list|(
name|s
argument_list|)
argument_list|)
expr_stmt|;
comment|/*  if the list doesn't contain the default domain yet, append it  */
for|for
control|(
name|list
operator|=
name|locales
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
if|if
condition|(
name|strcmp
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|,
name|GIMP_HELP_DEFAULT_LOCALE
argument_list|)
operator|==
literal|0
condition|)
break|break;
if|if
condition|(
operator|!
name|list
condition|)
name|locales
operator|=
name|g_list_append
argument_list|(
name|locales
argument_list|,
name|g_strdup
argument_list|(
name|GIMP_HELP_DEFAULT_LOCALE
argument_list|)
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|GIMP_HELP_DEBUG
name|g_printerr
argument_list|(
literal|"help: locales: "
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|locales
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
name|g_printerr
argument_list|(
literal|"%s "
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_printerr
argument_list|(
literal|"\n"
argument_list|)
expr_stmt|;
endif|#
directive|endif
return|return
name|locales
return|;
block|}
end_function

end_unit

