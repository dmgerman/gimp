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
file|<glib.h>
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
file|"app_procs.h"
end_include

begin_include
include|#
directive|include
file|"parasitelist.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasite.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/parasite.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpenv.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_decl_stmt
DECL|variable|parasites
specifier|static
name|ParasiteList
modifier|*
name|parasites
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|gimp_init_parasites ()
name|gimp_init_parasites
parameter_list|()
block|{
name|g_return_if_fail
argument_list|(
name|parasites
operator|==
name|NULL
argument_list|)
expr_stmt|;
name|parasites
operator|=
name|parasite_list_new
argument_list|()
expr_stmt|;
name|gimp_parasiterc_load
argument_list|()
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasite_attach (Parasite * p)
name|gimp_parasite_attach
parameter_list|(
name|Parasite
modifier|*
name|p
parameter_list|)
block|{
name|parasite_list_add
argument_list|(
name|parasites
argument_list|,
name|p
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasite_detach (const char * name)
name|gimp_parasite_detach
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|)
block|{
name|parasite_list_remove
argument_list|(
name|parasites
argument_list|,
name|name
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Parasite
modifier|*
DECL|function|gimp_parasite_find (const char * name)
name|gimp_parasite_find
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|)
block|{
return|return
name|parasite_list_find
argument_list|(
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
DECL|function|list_func (char * key,Parasite * p,char *** cur)
name|list_func
parameter_list|(
name|char
modifier|*
name|key
parameter_list|,
name|Parasite
modifier|*
name|p
parameter_list|,
name|char
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
name|char
modifier|*
modifier|*
DECL|function|gimp_parasite_list (gint * count)
name|gimp_parasite_list
parameter_list|(
name|gint
modifier|*
name|count
parameter_list|)
block|{
name|gchar
modifier|*
modifier|*
name|list
decl_stmt|,
modifier|*
modifier|*
name|cur
decl_stmt|;
operator|*
name|count
operator|=
name|parasite_list_length
argument_list|(
name|parasites
argument_list|)
expr_stmt|;
name|cur
operator|=
name|list
operator|=
operator|(
name|char
operator|*
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|char
operator|*
argument_list|)
operator|*
operator|*
name|count
argument_list|)
expr_stmt|;
name|parasite_list_foreach
argument_list|(
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
DECL|function|save_func (char * key,Parasite * p,FILE * fp)
name|save_func
parameter_list|(
name|char
modifier|*
name|key
parameter_list|,
name|Parasite
modifier|*
name|p
parameter_list|,
name|FILE
modifier|*
name|fp
parameter_list|)
block|{
if|if
condition|(
name|parasite_is_persistent
argument_list|(
name|p
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
name|parasite_name
argument_list|(
name|p
argument_list|)
argument_list|,
name|parasite_flags
argument_list|(
name|p
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
name|parasite_data
argument_list|(
name|p
argument_list|)
operator|,
name|l
operator|=
name|parasite_data_size
argument_list|(
name|p
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
DECL|function|gimp_parasiterc_save (void)
name|gimp_parasiterc_save
parameter_list|(
name|void
parameter_list|)
block|{
name|char
modifier|*
name|filename
decl_stmt|;
name|FILE
modifier|*
name|fp
decl_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"#parasiterc.tmp~"
argument_list|)
expr_stmt|;
name|fp
operator|=
name|fopen
argument_list|(
name|filename
argument_list|,
literal|"w"
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|filename
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|fp
condition|)
return|return;
name|fprintf
argument_list|(
name|fp
argument_list|,
name|_
argument_list|(
literal|"# GIMP parasiterc\n"
literal|"# This file will be entirely rewritten every time you quit the gimp.\n\n"
argument_list|)
argument_list|)
expr_stmt|;
name|parasite_list_foreach
argument_list|(
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
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc.bak"
argument_list|)
argument_list|)
expr_stmt|;
name|rename
argument_list|(
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc"
argument_list|)
argument_list|,
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc.bak"
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
if|if
condition|(
name|rename
argument_list|(
name|gimp_personal_rc_file
argument_list|(
literal|"#parasiterc.tmp~"
argument_list|)
argument_list|,
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc"
argument_list|)
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
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc.bak"
argument_list|)
argument_list|,
name|gimp_personal_rc_file
argument_list|(
literal|"parasiterc"
argument_list|)
argument_list|)
expr_stmt|;
endif|#
directive|endif
name|unlink
argument_list|(
name|gimp_personal_rc_file
argument_list|(
literal|"#parasiterc.tmp~"
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasiterc_load (void)
name|gimp_parasiterc_load
parameter_list|(
name|void
parameter_list|)
block|{
name|char
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
name|app_init_update_status
argument_list|(
name|NULL
argument_list|,
name|filename
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|parse_gimprc_file
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

end_unit

