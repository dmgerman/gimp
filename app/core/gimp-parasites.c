begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpparasite.c: Copyright 1998 Jay Cox<jaycox@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimp-parasites.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasitelist.h"
end_include

begin_function
name|void
DECL|function|gimp_parasite_attach (Gimp * gimp,const GimpParasite * parasite)
name|gimp_parasite_attach
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|parasite
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
name|g_return_if_fail
argument_list|(
name|parasite
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_parasite_list_add
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasite_detach (Gimp * gimp,const gchar * name)
name|gimp_parasite_detach
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
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
name|g_return_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|gimp_parasite_list_remove
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|const
name|GimpParasite
modifier|*
DECL|function|gimp_parasite_find (Gimp * gimp,const gchar * name)
name|gimp_parasite_find
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
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
name|g_return_val_if_fail
argument_list|(
name|name
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|gimp_parasite_list_find
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|,
name|name
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|list_func (const gchar * key,GimpParasite * parasite,gchar *** current)
name|list_func
parameter_list|(
specifier|const
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|current
parameter_list|)
block|{
operator|*
operator|(
operator|*
name|current
operator|)
operator|++
operator|=
name|g_strdup
argument_list|(
name|key
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gchar
modifier|*
modifier|*
DECL|function|gimp_parasite_list (Gimp * gimp,gint * count)
name|gimp_parasite_list
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
modifier|*
name|count
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|list
decl_stmt|;
name|gchar
modifier|*
modifier|*
name|current
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
name|g_return_val_if_fail
argument_list|(
name|count
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
operator|*
name|count
operator|=
name|gimp_parasite_list_length
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|)
expr_stmt|;
name|list
operator|=
name|current
operator|=
name|g_new
argument_list|(
name|gchar
operator|*
argument_list|,
operator|*
name|count
argument_list|)
expr_stmt|;
name|gimp_parasite_list_foreach
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|,
operator|(
name|GHFunc
operator|)
name|list_func
argument_list|,
operator|&
name|current
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_comment
comment|/*  FIXME: this doesn't belong here  */
end_comment

begin_function
name|void
DECL|function|gimp_parasite_shift_parent (GimpParasite * parasite)
name|gimp_parasite_shift_parent
parameter_list|(
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|parasite
operator|!=
name|NULL
argument_list|)
expr_stmt|;
name|parasite
operator|->
name|flags
operator|=
operator|(
name|parasite
operator|->
name|flags
operator|>>
literal|8
operator|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/*  parasiterc functions  */
end_comment

begin_function
name|void
DECL|function|gimp_parasiterc_load (Gimp * gimp)
name|gimp_parasiterc_load
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|gchar
modifier|*
name|filename
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
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc"
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
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|)
argument_list|,
name|filename
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
operator|!=
name|GIMP_CONFIG_ERROR_OPEN_ENOENT
condition|)
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasiterc_save (Gimp * gimp)
name|gimp_parasiterc_save
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
literal|"GIMP parasiterc\n"
literal|"\n"
literal|"This file will be entirely rewritten every time you quit the gimp."
decl_stmt|;
specifier|const
name|gchar
modifier|*
name|footer
init|=
literal|"end of parasiterc"
decl_stmt|;
name|gchar
modifier|*
name|filename
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
name|GIMP_IS_PARASITE_LIST
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|)
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc"
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
name|gimp_filename_to_utf8
argument_list|(
name|filename
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize_to_file
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|)
argument_list|,
name|filename
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
name|gimp_message
argument_list|(
name|gimp
argument_list|,
name|NULL
argument_list|,
name|GIMP_MESSAGE_ERROR
argument_list|,
literal|"%s"
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
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

