begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppluginmanager-locale-domain.c  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|"plug-in-types.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager.h"
end_include

begin_include
include|#
directive|include
file|"gimppluginmanager-locale-domain.h"
end_include

begin_define
DECL|macro|STD_PLUG_INS_LOCALE_DOMAIN
define|#
directive|define
name|STD_PLUG_INS_LOCALE_DOMAIN
value|GETTEXT_PACKAGE "-std-plug-ins"
end_define

begin_typedef
DECL|typedef|GimpPlugInLocaleDomain
typedef|typedef
name|struct
name|_GimpPlugInLocaleDomain
name|GimpPlugInLocaleDomain
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPlugInLocaleDomain
struct|struct
name|_GimpPlugInLocaleDomain
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
DECL|member|domain_path
name|gchar
modifier|*
name|domain_path
decl_stmt|;
block|}
struct|;
end_struct

begin_function
name|void
DECL|function|gimp_plug_in_manager_locale_domain_exit (GimpPlugInManager * manager)
name|gimp_plug_in_manager_locale_domain_exit
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|locale_domains
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
name|GimpPlugInLocaleDomain
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
name|domain_path
argument_list|)
expr_stmt|;
name|g_slice_free
argument_list|(
name|GimpPlugInLocaleDomain
argument_list|,
name|domain
argument_list|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|manager
operator|->
name|locale_domains
argument_list|)
expr_stmt|;
name|manager
operator|->
name|locale_domains
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_plug_in_manager_add_locale_domain (GimpPlugInManager * manager,const gchar * prog_name,const gchar * domain_name,const gchar * domain_path)
name|gimp_plug_in_manager_add_locale_domain
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
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
name|domain_path
parameter_list|)
block|{
name|GimpPlugInLocaleDomain
modifier|*
name|domain
decl_stmt|;
name|g_return_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
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
name|g_slice_new
argument_list|(
name|GimpPlugInLocaleDomain
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
name|domain_path
operator|=
name|g_strdup
argument_list|(
name|domain_path
argument_list|)
expr_stmt|;
name|manager
operator|->
name|locale_domains
operator|=
name|g_slist_prepend
argument_list|(
name|manager
operator|->
name|locale_domains
argument_list|,
name|domain
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|VERBOSE
name|g_print
argument_list|(
literal|"added locale domain \"%s\" for path \"%s\"\n"
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
name|domain_path
condition|?
name|gimp_filename_to_utf8
argument_list|(
name|domain
operator|->
name|domain_path
argument_list|)
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
DECL|function|gimp_plug_in_manager_get_locale_domain (GimpPlugInManager * manager,const gchar * prog_name,const gchar ** domain_path)
name|gimp_plug_in_manager_get_locale_domain
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
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
name|domain_path
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|domain_path
condition|)
operator|*
name|domain_path
operator|=
name|gimp_locale_directory
argument_list|()
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
name|manager
operator|->
name|locale_domains
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
name|GimpPlugInLocaleDomain
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
name|domain_path
operator|&&
name|domain
operator|->
name|domain_path
condition|)
operator|*
name|domain_path
operator|=
name|domain
operator|->
name|domain_path
expr_stmt|;
return|return
name|domain
operator|->
name|domain_name
return|;
block|}
block|}
return|return
name|STD_PLUG_INS_LOCALE_DOMAIN
return|;
block|}
end_function

begin_function
name|gint
DECL|function|gimp_plug_in_manager_get_locale_domains (GimpPlugInManager * manager,gchar *** locale_domains,gchar *** locale_paths)
name|gimp_plug_in_manager_get_locale_domains
parameter_list|(
name|GimpPlugInManager
modifier|*
name|manager
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|locale_domains
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|locale_paths
parameter_list|)
block|{
name|GSList
modifier|*
name|list
decl_stmt|;
name|GSList
modifier|*
name|unique
init|=
name|NULL
decl_stmt|;
name|gint
name|n_domains
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PLUG_IN_MANAGER
argument_list|(
name|manager
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|locale_domains
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|locale_paths
operator|!=
name|NULL
argument_list|,
literal|0
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|manager
operator|->
name|locale_domains
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
name|GimpPlugInLocaleDomain
modifier|*
name|domain
init|=
name|list
operator|->
name|data
decl_stmt|;
name|GSList
modifier|*
name|tmp
decl_stmt|;
for|for
control|(
name|tmp
operator|=
name|unique
init|;
name|tmp
condition|;
name|tmp
operator|=
name|tmp
operator|->
name|next
control|)
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|domain
operator|->
name|domain_name
argument_list|,
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|tmp
operator|->
name|data
argument_list|)
condition|)
break|break;
if|if
condition|(
operator|!
name|tmp
condition|)
name|unique
operator|=
name|g_slist_prepend
argument_list|(
name|unique
argument_list|,
name|domain
argument_list|)
expr_stmt|;
block|}
name|unique
operator|=
name|g_slist_reverse
argument_list|(
name|unique
argument_list|)
expr_stmt|;
name|n_domains
operator|=
name|g_slist_length
argument_list|(
name|unique
argument_list|)
operator|+
literal|1
expr_stmt|;
operator|*
name|locale_domains
operator|=
name|g_new0
argument_list|(
name|gchar
operator|*
argument_list|,
name|n_domains
operator|+
literal|1
argument_list|)
expr_stmt|;
operator|*
name|locale_paths
operator|=
name|g_new0
argument_list|(
name|gchar
operator|*
argument_list|,
name|n_domains
operator|+
literal|1
argument_list|)
expr_stmt|;
operator|(
operator|*
name|locale_domains
operator|)
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
name|STD_PLUG_INS_LOCALE_DOMAIN
argument_list|)
expr_stmt|;
operator|(
operator|*
name|locale_paths
operator|)
index|[
literal|0
index|]
operator|=
name|g_strdup
argument_list|(
name|gimp_locale_directory
argument_list|()
argument_list|)
expr_stmt|;
for|for
control|(
name|list
operator|=
name|unique
operator|,
name|i
operator|=
literal|1
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
name|GimpPlugInLocaleDomain
modifier|*
name|domain
init|=
name|list
operator|->
name|data
decl_stmt|;
operator|(
operator|*
name|locale_domains
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
name|locale_paths
operator|)
index|[
name|i
index|]
operator|=
operator|(
name|domain
operator|->
name|domain_path
condition|?
name|g_strdup
argument_list|(
name|domain
operator|->
name|domain_path
argument_list|)
else|:
name|g_strdup
argument_list|(
name|gimp_locale_directory
argument_list|()
argument_list|)
operator|)
expr_stmt|;
block|}
name|g_slist_free
argument_list|(
name|unique
argument_list|)
expr_stmt|;
return|return
name|n_domains
return|;
block|}
end_function

end_unit

