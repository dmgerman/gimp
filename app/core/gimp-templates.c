begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
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
file|<gdk-pixbuf/gdk-pixbuf.h>
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpconfig/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"core-types.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_include
include|#
directive|include
file|"gimp-templates.h"
end_include

begin_include
include|#
directive|include
file|"gimplist.h"
end_include

begin_include
include|#
directive|include
file|"gimptemplate.h"
end_include

begin_comment
comment|/* functions to load and save the gimp templates files */
end_comment

begin_function
name|void
DECL|function|gimp_templates_load (Gimp * gimp)
name|gimp_templates_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|GFile
modifier|*
name|file
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
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
name|GIMP_IS_LIST
argument_list|(
name|gimp
operator|->
name|templates
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
literal|"templaterc"
argument_list|,
name|NULL
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
literal|"Parsing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|templates
argument_list|)
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
if|if
condition|(
name|error
operator|->
name|code
operator|==
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
block|{
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_sysconf_directory_file
argument_list|(
literal|"templaterc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|templates
argument_list|)
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
block|}
else|else
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
block|}
name|g_clear_error
argument_list|(
operator|&
name|error
argument_list|)
expr_stmt|;
block|}
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|gimp
operator|->
name|templates
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_templates_save (Gimp * gimp)
name|gimp_templates_save
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|header
init|=
literal|"GIMP templaterc\n"
literal|"\n"
literal|"This file will be entirely rewritten each time you exit."
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|footer
init|=
literal|"end of templaterc"
decl_stmt|;
name|GFile
modifier|*
name|file
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
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
name|GIMP_IS_LIST
argument_list|(
name|gimp
operator|->
name|templates
argument_list|)
argument_list|)
expr_stmt|;
name|file
operator|=
name|gimp_directory_file
argument_list|(
literal|"templaterc"
argument_list|,
name|NULL
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
literal|"Writing '%s'\n"
argument_list|,
name|gimp_file_get_utf8_name
argument_list|(
name|file
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_to_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|templates
argument_list|)
argument_list|,
name|file
argument_list|,
name|header
argument_list|,
name|footer
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|gimp_message_literal
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
name|error
operator|->
name|message
argument_list|)
expr_stmt|;
name|g_error_free
argument_list|(
name|error
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  just like gimp_list_get_child_by_name() but matches case-insensitive  *  and dpi/ppi-insensitive  */
end_comment

begin_function
specifier|static
name|GimpObject
modifier|*
DECL|function|gimp_templates_migrate_get_child_by_name (GimpContainer * container,const gchar * name)
name|gimp_templates_migrate_get_child_by_name
parameter_list|(
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
name|GimpList
modifier|*
name|list
init|=
name|GIMP_LIST
argument_list|(
name|container
argument_list|)
decl_stmt|;
name|GimpObject
modifier|*
name|retval
init|=
name|NULL
decl_stmt|;
name|GList
modifier|*
name|glist
decl_stmt|;
for|for
control|(
name|glist
operator|=
name|list
operator|->
name|queue
operator|->
name|head
init|;
name|glist
condition|;
name|glist
operator|=
name|g_list_next
argument_list|(
name|glist
argument_list|)
control|)
block|{
name|GimpObject
modifier|*
name|object
init|=
name|glist
operator|->
name|data
decl_stmt|;
name|gchar
modifier|*
name|str1
init|=
name|g_ascii_strdown
argument_list|(
name|gimp_object_get_name
argument_list|(
name|object
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|str2
init|=
name|g_ascii_strdown
argument_list|(
name|name
argument_list|,
operator|-
literal|1
argument_list|)
decl_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|str1
argument_list|,
name|str2
argument_list|)
condition|)
block|{
name|retval
operator|=
name|object
expr_stmt|;
block|}
else|else
block|{
name|gchar
modifier|*
name|dpi
init|=
name|strstr
argument_list|(
name|str1
argument_list|,
literal|"dpi"
argument_list|)
decl_stmt|;
if|if
condition|(
name|dpi
condition|)
block|{
name|strncpy
argument_list|(
name|dpi
argument_list|,
literal|"ppi"
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"replaced: %s\n"
argument_list|,
name|str1
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|strcmp
argument_list|(
name|str1
argument_list|,
name|str2
argument_list|)
condition|)
name|retval
operator|=
name|object
expr_stmt|;
block|}
block|}
name|g_free
argument_list|(
name|str1
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|str2
argument_list|)
expr_stmt|;
block|}
return|return
name|retval
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_templates_migrate:  * @olddir: the old user directory  *  * Migrating the templaterc from GIMP 2.0 to GIMP 2.2 needs this special  * hack since we changed the way that units are handled. This function  * merges the user's templaterc with the systemwide templaterc. The goal  * is to replace the unit for a couple of default templates with "pixels".  **/
end_comment

begin_function
name|void
DECL|function|gimp_templates_migrate (const gchar * olddir)
name|gimp_templates_migrate
parameter_list|(
specifier|const
name|gchar
modifier|*
name|olddir
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|templates
init|=
name|gimp_list_new
argument_list|(
name|GIMP_TYPE_TEMPLATE
argument_list|,
name|TRUE
argument_list|)
decl_stmt|;
name|GFile
modifier|*
name|file
init|=
name|gimp_directory_file
argument_list|(
literal|"templaterc"
argument_list|,
name|NULL
argument_list|)
decl_stmt|;
if|if
condition|(
name|gimp_config_deserialize_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|templates
argument_list|)
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
condition|)
block|{
name|GFile
modifier|*
name|sysconf_file
decl_stmt|;
name|sysconf_file
operator|=
name|gimp_sysconf_directory_file
argument_list|(
literal|"templaterc"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|olddir
operator|&&
operator|(
name|strstr
argument_list|(
name|olddir
argument_list|,
literal|"2.0"
argument_list|)
operator|||
name|strstr
argument_list|(
name|olddir
argument_list|,
literal|"2.2"
argument_list|)
operator|)
condition|)
block|{
comment|/* We changed the spelling of a couple of template names:            *            * - from upper to lower case between 2.0 and 2.2            * - from "dpi" to "ppi" between 2.2 and 2.4            */
name|GimpContainerClass
modifier|*
name|class
init|=
name|GIMP_CONTAINER_GET_CLASS
argument_list|(
name|templates
argument_list|)
decl_stmt|;
name|gpointer
name|func
init|=
name|class
operator|->
name|get_child_by_name
decl_stmt|;
name|class
operator|->
name|get_child_by_name
operator|=
name|gimp_templates_migrate_get_child_by_name
expr_stmt|;
name|gimp_config_deserialize_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|templates
argument_list|)
argument_list|,
name|sysconf_file
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|class
operator|->
name|get_child_by_name
operator|=
name|func
expr_stmt|;
block|}
else|else
block|{
name|gimp_config_deserialize_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|templates
argument_list|)
argument_list|,
name|sysconf_file
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|sysconf_file
argument_list|)
expr_stmt|;
name|gimp_list_reverse
argument_list|(
name|GIMP_LIST
argument_list|(
name|templates
argument_list|)
argument_list|)
expr_stmt|;
name|gimp_config_serialize_to_gfile
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|templates
argument_list|)
argument_list|,
name|file
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
name|g_object_unref
argument_list|(
name|file
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

