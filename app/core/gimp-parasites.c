begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpparasite.c: Copyright 1998 Jay Cox<jaycox@earthlink.net>   *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<stdio.h>
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
file|"libgimpbase/gimpbase.h"
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
file|"gimpparasite.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasitelist.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_function
name|void
DECL|function|gimp_parasites_init (Gimp * gimp)
name|gimp_parasites_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|gimp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
name|gimp
operator|->
name|parasites
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|parasites
operator|=
name|gimp_parasite_list_new
argument_list|()
expr_stmt|;
name|gtk_object_ref
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_object_sink
argument_list|(
name|GTK_OBJECT
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasites_exit (Gimp * gimp)
name|gimp_parasites_exit
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|gimp
operator|!=
name|NULL
argument_list|)
expr_stmt|;
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
name|gimp
operator|->
name|parasites
condition|)
block|{
name|g_object_unref
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp
operator|->
name|parasites
argument_list|)
argument_list|)
expr_stmt|;
name|gimp
operator|->
name|parasites
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasite_attach (Gimp * gimp,GimpParasite * parasite)
name|gimp_parasite_attach
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
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
DECL|function|list_func (gchar * key,GimpParasite * p,gchar *** cur)
name|list_func
parameter_list|(
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|p
parameter_list|,
name|gchar
modifier|*
modifier|*
modifier|*
name|cur
parameter_list|)
block|{
operator|*
operator|(
operator|*
name|cur
operator|)
operator|++
operator|=
operator|(
name|char
operator|*
operator|)
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
name|cur
decl_stmt|;
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
name|cur
operator|=
name|list
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
name|cur
argument_list|)
expr_stmt|;
return|return
name|list
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|save_func (gchar * key,GimpParasite * parasite,FILE * fp)
name|save_func
parameter_list|(
name|gchar
modifier|*
name|key
parameter_list|,
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
block|{
if|if
condition|(
name|gimp_parasite_is_persistent
argument_list|(
name|parasite
argument_list|)
condition|)
block|{
name|gchar
modifier|*
name|s
decl_stmt|;
name|guint32
name|l
decl_stmt|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"(parasite \"%s\" %lu \""
argument_list|,
name|gimp_parasite_name
argument_list|(
name|parasite
argument_list|)
argument_list|,
name|gimp_parasite_flags
argument_list|(
name|parasite
argument_list|)
argument_list|)
expr_stmt|;
comment|/*        * the current methodology is: never move the parasiterc from one        * system to another. If you want to do this you should probably        * write out parasites which contain any non-alphanumeric(+some)        * characters as \xHH sequences altogether.        */
for|for
control|(
name|s
operator|=
operator|(
name|gchar
operator|*
operator|)
name|gimp_parasite_data
argument_list|(
name|parasite
argument_list|)
operator|,
name|l
operator|=
name|gimp_parasite_data_size
argument_list|(
name|parasite
argument_list|)
init|;
name|l
condition|;
name|l
operator|--
operator|,
name|s
operator|++
control|)
block|{
switch|switch
condition|(
operator|*
name|s
condition|)
block|{
case|case
literal|'\\'
case|:
name|fputs
argument_list|(
literal|"\\\\"
argument_list|,
name|fp
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'\0'
case|:
name|fputs
argument_list|(
literal|"\\0"
argument_list|,
name|fp
argument_list|)
expr_stmt|;
break|break;
case|case
literal|'"'
case|:
name|fputs
argument_list|(
literal|"\\\""
argument_list|,
name|fp
argument_list|)
expr_stmt|;
break|break;
comment|/* disabled, not portable!  */
comment|/*              case '\n': fputs ("\\n", fp); break;*/
comment|/*              case '\r': fputs ("\\r", fp); break;*/
case|case
literal|26
case|:
name|fputs
argument_list|(
literal|"\\z"
argument_list|,
name|fp
argument_list|)
expr_stmt|;
break|break;
default|default  :
name|fputc
argument_list|(
operator|*
name|s
argument_list|,
name|fp
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
name|fputs
argument_list|(
literal|"\")\n\n"
argument_list|,
name|fp
argument_list|)
expr_stmt|;
block|}
block|}
end_function

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
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc"
argument_list|)
expr_stmt|;
name|gimprc_parse_file
argument_list|(
name|filename
argument_list|)
expr_stmt|;
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
name|gchar
modifier|*
name|tmp_filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|bak_filename
init|=
name|NULL
decl_stmt|;
name|gchar
modifier|*
name|rc_filename
init|=
name|NULL
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|tmp_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"#parasiterc.tmp~"
argument_list|)
expr_stmt|;
name|bak_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc.bak"
argument_list|)
expr_stmt|;
name|rc_filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc"
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|tmp_filename
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
goto|goto
name|cleanup
goto|;
name|fprintf
argument_list|(
name|fp
argument_list|,
literal|"# GIMP parasiterc\n"
literal|"# This file will be entirely rewritten every time you "
literal|"quit the gimp.\n\n"
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
name|save_func
argument_list|,
name|fp
argument_list|)
expr_stmt|;
name|fclose
argument_list|(
name|fp
argument_list|)
expr_stmt|;
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|__EMX__
argument_list|)
comment|/* First rename the old parasiterc out of the way */
name|unlink
argument_list|(
name|bak_filename
argument_list|)
expr_stmt|;
name|rename
argument_list|(
name|rc_filename
argument_list|,
name|bak_filename
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|rename
argument_list|(
name|tmp_filename
argument_list|,
name|rc_filename
argument_list|)
operator|!=
literal|0
condition|)
block|{
if|#
directive|if
name|defined
argument_list|(
name|G_OS_WIN32
argument_list|)
operator|||
name|defined
argument_list|(
name|__EMX__
argument_list|)
comment|/* Rename the old parasiterc back */
name|rename
argument_list|(
name|bak_filename
argument_list|,
name|rc_filename
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|unlink
argument_list|(
name|tmp_filename
argument_list|)
expr_stmt|;
block|}
name|cleanup
label|:
name|g_free
argument_list|(
name|tmp_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|bak_filename
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|rc_filename
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

