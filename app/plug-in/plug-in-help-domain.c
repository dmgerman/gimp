begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * plug-in-help-domain.c  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"plug-in-help-domain.h"
end_include

begin_typedef
DECL|typedef|PlugInHelpDomain
typedef|typedef
name|struct
name|_PlugInHelpDomain
name|PlugInHelpDomain
typedef|;
end_typedef

begin_struct
DECL|struct|_PlugInHelpDomain
struct|struct
name|_PlugInHelpDomain
block|{
DECL|member|prog_name
name|gchar
modifier|*
name|prog_name
decl_stmt|;
DECL|member|domain_name
name|gchar
modifier|*
name|domain_name
decl_stmt|;
DECL|member|domain_uri
name|gchar
modifier|*
name|domain_uri
decl_stmt|;
block|}
struct|;
end_struct

begin_function
name|void
DECL|function|plug_in_help_domain_exit (Gimp * gimp)
name|plug_in_help_domain_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|plug_in_help_domains
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|PlugInHelpDomain
modifier|*
name|domain
init|=
name|list
operator|->
name|data
decl_stmt|;
name|g_free
argument_list|(
name|domain
operator|->
name|prog_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
operator|->
name|domain_name
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
operator|->
name|domain_uri
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|domain
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|gimp
operator|->
name|plug_in_help_domains
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|plug_in_help_domains
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|plug_in_help_domain_add (Gimp * gimp,const gchar * prog_name,const gchar * domain_name,const gchar * domain_uri)
name|plug_in_help_domain_add
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
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
name|PlugInHelpDomain
modifier|*
name|domain
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|prog_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|g_return_if_fail
argument_list|(
name|domain_name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|domain
operator|=
name|g_new
argument_list|(
name|PlugInHelpDomain
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|domain
operator|->
name|prog_name
operator|=
name|g_strdup
argument_list|(
name|prog_name
argument_list|)
expr_stmt|;
name|domain
operator|->
name|domain_name
operator|=
name|g_strdup
argument_list|(
name|domain_name
argument_list|)
expr_stmt|;
name|domain
operator|->
name|domain_uri
operator|=
name|g_strdup
argument_list|(
name|domain_uri
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|plug_in_help_domains
operator|=
name|g_slist_prepend
argument_list|(
name|gimp
operator|->
name|plug_in_help_domains
argument_list|,
name|domain
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|VERBOSE
name|g_print
argument_list|(
literal|"added help domain \"%s\" for base uri \"%s\"\n"
argument_list|,
name|domain
operator|->
name|domain_name
condition|?
name|domain
operator|->
name|domain_name
else|:
literal|"(null)"
argument_list|,
name|domain
operator|->
name|domain_uri
condition|?
name|domain
operator|->
name|domain_uri
else|:
literal|"(null)"
argument_list|)
expr_stmt|;
endif|#
directive|endif
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|plug_in_help_domain (Gimp * gimp,const gchar * prog_name,const gchar ** domain_uri)
name|plug_in_help_domain
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|prog_name
parameter_list|,
specifier|const
name|gchar
modifier|*
modifier|*
name|domain_uri
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|domain_uri
condition|)
operator|*
name|domain_uri
operator|=
name|NULL
expr_stmt|;
comment|/*  A NULL prog_name is GIMP itself, return the default domain  */
if|if
condition|(
operator|!
name|prog_name
condition|)
return|return
name|NULL
return|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|plug_in_help_domains
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
control|)
block|{
name|PlugInHelpDomain
modifier|*
name|domain
init|=
name|list
operator|->
name|data
decl_stmt|;
if|if
condition|(
name|domain
operator|&&
name|domain
operator|->
name|prog_name
operator|&&
operator|!
name|strcmp
argument_list|(
name|domain
operator|->
name|prog_name
argument_list|,
name|prog_name
argument_list|)
condition|)
block|{
if|if
condition|(
name|domain_uri
operator|&&
name|domain
operator|->
name|domain_uri
condition|)
operator|*
name|domain_uri
operator|=
name|domain
operator|->
name|domain_uri
expr_stmt|;
return|return
name|domain
operator|->
name|domain_name
return|;
block|}
block|}
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gint
DECL|function|plug_in_help_domains (Gimp * gimp,gchar *** help_domains,gchar *** help_uris)
name|plug_in_help_domains
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|help_domains
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|help_uris
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|gint
name|n_domains
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_GIMP
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_domains
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|help_uris
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|n_domains
operator|=
name|g_slist_length
argument_list|(
name|gimp
operator|->
name|plug_in_help_domains
argument_list|)
expr_stmt|;
operator|*
name|help_domains
operator|=
name|g_new0
argument_list|(
name|gchar
operator|*
argument_list|,
name|n_domains
argument_list|)
expr_stmt|;
operator|*
name|help_uris
operator|=
name|g_new0
argument_list|(
name|gchar
operator|*
argument_list|,
name|n_domains
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|gimp
operator|->
name|plug_in_help_domains
operator|,
name|i
operator|=
literal|0
init|;
name|list
condition|;
name|list
operator|=
name|list
operator|->
name|next
operator|,
name|i
operator|++
control|)
block|{
name|PlugInHelpDomain
modifier|*
name|domain
init|=
name|list
operator|->
name|data
decl_stmt|;
operator|(
operator|*
name|help_domains
operator|)
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|domain
operator|->
name|domain_name
argument_list|)
expr_stmt|;
operator|(
operator|*
name|help_uris
operator|)
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|domain
operator|->
name|domain_uri
argument_list|)
expr_stmt|;
block|}
return|return
name|n_domains
return|;
block|}
end_function

end_unit

