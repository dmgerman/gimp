begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* gimpparasite.c: Copyright 1998 Jay Cox<jaycox@earthlink.net>   *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|<glib.h>
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
block|}
end_function

begin_function
name|void
DECL|function|gimp_attach_parasite (Parasite * p)
name|gimp_attach_parasite
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
DECL|function|gimp_detach_parasite (char * name)
name|gimp_detach_parasite
parameter_list|(
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
DECL|function|gimp_find_parasite (char * name)
name|gimp_find_parasite
parameter_list|(
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

end_unit

