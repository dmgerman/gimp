begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * String substitution utilities for config files  * Copyright (C) 2001  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|"libgimpbase/gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"gimpconfig-path.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|SUBSTS_ALLOC
define|#
directive|define
name|SUBSTS_ALLOC
value|4
end_define

begin_function_decl
specifier|static
specifier|inline
name|gchar
modifier|*
name|extract_token
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|str
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/**  * gimp_config_path_expand:  * @path: a %NUL-terminated string in UTF-8 encoding  * @recode: whether to convert to the filesystem's encoding  * @error: return location for errors  *  * Paths as stored in the gimprc have to be treated special.  The  * string may contain special identifiers such as for example  * ${gimp_dir} that have to be substituted before use. Also the user's  * filesystem may be in a different encoding than UTF-8 (which is what  * is used for the gimprc). This function does the variable  * substitution for you and can also attempt to convert to the  * filesystem encoding.  *  * Return value: a newly allocated %NUL-terminated string  **/
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_config_path_expand (const gchar * path,gboolean recode,GError ** error)
name|gimp_config_path_expand
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|recode
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|s
decl_stmt|;
name|gchar
modifier|*
name|n
decl_stmt|;
name|gchar
modifier|*
name|token
decl_stmt|;
name|gchar
modifier|*
name|filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|expanded
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|substs
init|=
name|NULL
decl_stmt|;
name|guint
name|n_substs
init|=
literal|0
decl_stmt|;
name|gint
name|length
init|=
literal|0
decl_stmt|;
name|gint
name|i
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|path
operator|!=
name|NULL
argument_list|,
name|NULL
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
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
name|recode
condition|)
block|{
if|if
condition|(
operator|!
operator|(
name|filename
operator|=
name|g_filename_from_utf8
argument_list|(
name|path
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|error
argument_list|)
operator|)
condition|)
return|return
name|NULL
return|;
name|p
operator|=
name|filename
expr_stmt|;
block|}
else|else
block|{
name|p
operator|=
name|path
expr_stmt|;
block|}
while|while
condition|(
operator|*
name|p
condition|)
block|{
ifndef|#
directive|ifndef
name|G_OS_WIN32
if|if
condition|(
operator|*
name|p
operator|==
literal|'~'
condition|)
block|{
name|length
operator|+=
name|strlen
argument_list|(
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
name|p
operator|+=
literal|1
expr_stmt|;
block|}
elseif|else
endif|#
directive|endif
comment|/* G_OS_WIN32 */
if|if
condition|(
operator|(
name|token
operator|=
name|extract_token
argument_list|(
operator|&
name|p
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_substs
condition|;
name|i
operator|++
control|)
if|if
condition|(
name|strcmp
argument_list|(
name|substs
index|[
literal|2
operator|*
name|i
index|]
argument_list|,
name|token
argument_list|)
operator|==
literal|0
condition|)
break|break;
if|if
condition|(
name|i
operator|<
name|n_substs
condition|)
block|{
name|s
operator|=
name|substs
index|[
literal|2
operator|*
name|i
operator|+
literal|1
index|]
expr_stmt|;
block|}
else|else
block|{
name|s
operator|=
name|NULL
expr_stmt|;
if|if
condition|(
operator|!
name|s
operator|&&
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_dir"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|gimp_directory
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|s
operator|&&
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_data_dir"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|gimp_data_directory
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|s
operator|&&
operator|(
operator|(
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_plug_in_dir"
argument_list|)
operator|)
operator|==
literal|0
operator|||
operator|(
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_plugin_dir"
argument_list|)
operator|)
operator|==
literal|0
operator|)
condition|)
name|s
operator|=
name|gimp_plug_in_directory
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|s
operator|&&
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"gimp_sysconf_dir"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|gimp_sysconf_directory
argument_list|()
expr_stmt|;
if|if
condition|(
operator|!
name|s
condition|)
name|s
operator|=
name|g_getenv
argument_list|(
name|token
argument_list|)
expr_stmt|;
ifdef|#
directive|ifdef
name|G_OS_WIN32
comment|/* The default user gimprc on Windows references                * ${TEMP}, but not all Windows installations have that                * environment variable, even if it should be kinda                * standard. So special-case it.                */
if|if
condition|(
operator|!
name|s
operator|&&
name|strcmp
argument_list|(
name|token
argument_list|,
literal|"TEMP"
argument_list|)
operator|==
literal|0
condition|)
name|s
operator|=
name|g_get_tmp_dir
argument_list|()
expr_stmt|;
endif|#
directive|endif
comment|/* G_OS_WIN32 */
block|}
if|if
condition|(
operator|!
name|s
condition|)
block|{
name|g_set_error
argument_list|(
name|error
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|_
argument_list|(
literal|"Cannot expand ${%s}"
argument_list|)
argument_list|,
name|token
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|token
argument_list|)
expr_stmt|;
goto|goto
name|cleanup
goto|;
block|}
if|if
condition|(
name|n_substs
operator|%
name|SUBSTS_ALLOC
operator|==
literal|0
condition|)
name|substs
operator|=
name|g_renew
argument_list|(
name|gchar
operator|*
argument_list|,
name|substs
argument_list|,
literal|2
operator|*
operator|(
name|n_substs
operator|+
name|SUBSTS_ALLOC
operator|)
argument_list|)
expr_stmt|;
name|substs
index|[
literal|2
operator|*
name|n_substs
index|]
operator|=
name|token
expr_stmt|;
name|substs
index|[
literal|2
operator|*
name|n_substs
operator|+
literal|1
index|]
operator|=
operator|(
name|gchar
operator|*
operator|)
name|s
expr_stmt|;
name|n_substs
operator|++
expr_stmt|;
name|length
operator|+=
name|strlen
argument_list|(
name|s
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|length
operator|+=
name|g_utf8_skip
index|[
operator|(
specifier|const
name|guchar
operator|)
operator|*
name|p
index|]
expr_stmt|;
name|p
operator|=
name|g_utf8_next_char
argument_list|(
name|p
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|n_substs
operator|==
literal|0
condition|)
return|return
name|recode
condition|?
name|filename
else|:
name|g_strdup
argument_list|(
name|path
argument_list|)
return|;
name|expanded
operator|=
name|g_new
argument_list|(
name|gchar
argument_list|,
name|length
operator|+
literal|1
argument_list|)
expr_stmt|;
name|p
operator|=
name|recode
condition|?
name|filename
else|:
name|path
expr_stmt|;
name|n
operator|=
name|expanded
expr_stmt|;
while|while
condition|(
operator|*
name|p
condition|)
block|{
ifndef|#
directive|ifndef
name|G_OS_WIN32
if|if
condition|(
operator|*
name|p
operator|==
literal|'~'
condition|)
block|{
operator|*
name|n
operator|=
literal|'\0'
expr_stmt|;
name|strcat
argument_list|(
name|n
argument_list|,
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
name|n
operator|+=
name|strlen
argument_list|(
name|g_get_home_dir
argument_list|()
argument_list|)
expr_stmt|;
name|p
operator|+=
literal|1
expr_stmt|;
block|}
elseif|else
endif|#
directive|endif
comment|/* G_OS_WIN32 */
if|if
condition|(
operator|(
name|token
operator|=
name|extract_token
argument_list|(
operator|&
name|p
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_substs
condition|;
name|i
operator|++
control|)
block|{
if|if
condition|(
name|strcmp
argument_list|(
name|substs
index|[
literal|2
operator|*
name|i
index|]
argument_list|,
name|token
argument_list|)
operator|==
literal|0
condition|)
block|{
name|s
operator|=
name|substs
index|[
literal|2
operator|*
name|i
operator|+
literal|1
index|]
expr_stmt|;
operator|*
name|n
operator|=
literal|'\0'
expr_stmt|;
name|strcat
argument_list|(
name|n
argument_list|,
name|s
argument_list|)
expr_stmt|;
name|n
operator|+=
name|strlen
argument_list|(
name|s
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|g_free
argument_list|(
name|token
argument_list|)
expr_stmt|;
block|}
else|else
block|{
operator|*
name|n
operator|++
operator|=
operator|*
name|p
operator|++
expr_stmt|;
block|}
block|}
operator|*
name|n
operator|=
literal|'\0'
expr_stmt|;
name|cleanup
label|:
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|n_substs
condition|;
name|i
operator|++
control|)
name|g_free
argument_list|(
name|substs
index|[
literal|2
operator|*
name|i
index|]
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|substs
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
return|return
name|expanded
return|;
block|}
end_function

begin_function
specifier|static
specifier|inline
name|gchar
modifier|*
DECL|function|extract_token (const gchar ** str)
name|extract_token
parameter_list|(
specifier|const
name|gchar
modifier|*
modifier|*
name|str
parameter_list|)
block|{
specifier|const
name|gchar
modifier|*
name|p
decl_stmt|;
name|gchar
modifier|*
name|token
decl_stmt|;
if|if
condition|(
name|strncmp
argument_list|(
operator|*
name|str
argument_list|,
literal|"${"
argument_list|,
literal|2
argument_list|)
condition|)
return|return
name|NULL
return|;
name|p
operator|=
operator|*
name|str
operator|+
literal|2
expr_stmt|;
while|while
condition|(
operator|*
name|p
operator|&&
operator|(
operator|*
name|p
operator|!=
literal|'}'
operator|)
condition|)
name|p
operator|=
name|g_utf8_next_char
argument_list|(
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|p
condition|)
return|return
name|NULL
return|;
name|token
operator|=
name|g_strndup
argument_list|(
operator|*
name|str
operator|+
literal|2
argument_list|,
name|g_utf8_pointer_to_offset
argument_list|(
operator|*
name|str
operator|+
literal|2
argument_list|,
name|p
argument_list|)
argument_list|)
expr_stmt|;
operator|*
name|str
operator|=
name|p
operator|+
literal|1
expr_stmt|;
comment|/* after the closing bracket */
return|return
name|token
return|;
block|}
end_function

end_unit

