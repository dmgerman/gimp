begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library   * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpparasite.c  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<string.h>
end_include

begin_include
include|#
directive|include
file|<glib.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|G_OS_WIN32
end_ifdef

begin_include
include|#
directive|include
file|<process.h>
end_include

begin_comment
comment|/* For _getpid() */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_include
include|#
directive|include
file|"gimpbasetypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpparasite.h"
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|DEBUG
end_ifdef

begin_function
specifier|static
name|void
DECL|function|gimp_parasite_print (GimpParasite * parasite)
name|gimp_parasite_print
parameter_list|(
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
operator|==
name|NULL
condition|)
block|{
name|g_print
argument_list|(
literal|"pid %d: attempt to print a null parasite\n"
argument_list|,
name|getpid
argument_list|()
argument_list|)
expr_stmt|;
return|return;
block|}
name|g_print
argument_list|(
literal|"pid %d: parasite: %p\n"
argument_list|,
name|getpid
argument_list|()
argument_list|,
name|parasite
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
operator|->
name|name
condition|)
name|g_print
argument_list|(
literal|"\tname: %s\n"
argument_list|,
name|parasite
operator|->
name|name
argument_list|)
expr_stmt|;
else|else
name|g_print
argument_list|(
literal|"\tname: NULL\n"
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\tflags: %d\n"
argument_list|,
name|parasite
operator|->
name|flags
argument_list|)
expr_stmt|;
name|g_print
argument_list|(
literal|"\tsize: %d\n"
argument_list|,
name|parasite
operator|->
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
operator|->
name|size
operator|>
literal|0
condition|)
name|g_print
argument_list|(
literal|"\tdata: %p\n"
argument_list|,
name|parasite
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_endif
endif|#
directive|endif
end_endif

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_parasite_new (const gchar * name,guint32 flags,guint32 size,gconstpointer data)
name|gimp_parasite_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|guint32
name|flags
parameter_list|,
name|guint32
name|size
parameter_list|,
name|gconstpointer
name|data
parameter_list|)
block|{
name|GimpParasite
modifier|*
name|parasite
decl_stmt|;
if|if
condition|(
operator|!
name|name
condition|)
return|return
name|NULL
return|;
name|parasite
operator|=
name|g_new
argument_list|(
name|GimpParasite
argument_list|,
literal|1
argument_list|)
expr_stmt|;
name|parasite
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
name|parasite
operator|->
name|flags
operator|=
operator|(
name|flags
operator|&
literal|0xFF
operator|)
expr_stmt|;
name|parasite
operator|->
name|size
operator|=
name|size
expr_stmt|;
if|if
condition|(
name|size
condition|)
name|parasite
operator|->
name|data
operator|=
name|g_memdup
argument_list|(
name|data
argument_list|,
name|size
argument_list|)
expr_stmt|;
else|else
name|parasite
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
return|return
name|parasite
return|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_parasite_free (GimpParasite * parasite)
name|gimp_parasite_free
parameter_list|(
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
operator|==
name|NULL
condition|)
return|return;
if|if
condition|(
name|parasite
operator|->
name|name
condition|)
name|g_free
argument_list|(
name|parasite
operator|->
name|name
argument_list|)
expr_stmt|;
if|if
condition|(
name|parasite
operator|->
name|data
condition|)
name|g_free
argument_list|(
name|parasite
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|parasite
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_parasite_is_type (const GimpParasite * parasite,const gchar * name)
name|gimp_parasite_is_type
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
if|if
condition|(
operator|!
name|parasite
operator|||
operator|!
name|parasite
operator|->
name|name
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
name|strcmp
argument_list|(
name|parasite
operator|->
name|name
argument_list|,
name|name
argument_list|)
operator|==
literal|0
operator|)
return|;
block|}
end_function

begin_function
name|GimpParasite
modifier|*
DECL|function|gimp_parasite_copy (const GimpParasite * parasite)
name|gimp_parasite_copy
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
operator|==
name|NULL
condition|)
return|return
name|NULL
return|;
return|return
name|gimp_parasite_new
argument_list|(
name|parasite
operator|->
name|name
argument_list|,
name|parasite
operator|->
name|flags
argument_list|,
name|parasite
operator|->
name|size
argument_list|,
name|parasite
operator|->
name|data
argument_list|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_parasite_compare (const GimpParasite * a,const GimpParasite * b)
name|gimp_parasite_compare
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|a
parameter_list|,
specifier|const
name|GimpParasite
modifier|*
name|b
parameter_list|)
block|{
if|if
condition|(
name|a
operator|&&
name|b
operator|&&
name|a
operator|->
name|name
operator|&&
name|b
operator|->
name|name
operator|&&
name|strcmp
argument_list|(
name|a
operator|->
name|name
argument_list|,
name|b
operator|->
name|name
argument_list|)
operator|==
literal|0
operator|&&
name|a
operator|->
name|flags
operator|==
name|b
operator|->
name|flags
operator|&&
name|a
operator|->
name|size
operator|==
name|b
operator|->
name|size
condition|)
block|{
if|if
condition|(
name|a
operator|->
name|data
operator|==
name|NULL
operator|&&
name|b
operator|->
name|data
operator|==
name|NULL
condition|)
return|return
name|TRUE
return|;
elseif|else
if|if
condition|(
name|a
operator|->
name|data
operator|&&
name|b
operator|->
name|data
operator|&&
name|memcmp
argument_list|(
name|a
operator|->
name|data
argument_list|,
name|b
operator|->
name|data
argument_list|,
name|a
operator|->
name|size
argument_list|)
operator|==
literal|0
condition|)
return|return
name|TRUE
return|;
block|}
return|return
name|FALSE
return|;
block|}
end_function

begin_function
name|gulong
DECL|function|gimp_parasite_flags (const GimpParasite * parasite)
name|gimp_parasite_flags
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
operator|==
name|NULL
condition|)
return|return
literal|0
return|;
return|return
name|parasite
operator|->
name|flags
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_parasite_is_persistent (const GimpParasite * parasite)
name|gimp_parasite_is_persistent
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
name|parasite
operator|->
name|flags
operator|&
name|GIMP_PARASITE_PERSISTENT
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_parasite_is_undoable (const GimpParasite * parasite)
name|gimp_parasite_is_undoable
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
name|parasite
operator|->
name|flags
operator|&
name|GIMP_PARASITE_UNDOABLE
operator|)
return|;
block|}
end_function

begin_function
name|gboolean
DECL|function|gimp_parasite_has_flag (const GimpParasite * parasite,gulong flag)
name|gimp_parasite_has_flag
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|,
name|gulong
name|flag
parameter_list|)
block|{
if|if
condition|(
name|parasite
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
name|parasite
operator|->
name|flags
operator|&
name|flag
operator|)
return|;
block|}
end_function

begin_function
specifier|const
name|gchar
modifier|*
DECL|function|gimp_parasite_name (const GimpParasite * parasite)
name|gimp_parasite_name
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
condition|)
return|return
name|parasite
operator|->
name|name
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|gconstpointer
DECL|function|gimp_parasite_data (const GimpParasite * parasite)
name|gimp_parasite_data
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
condition|)
return|return
name|parasite
operator|->
name|data
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
name|glong
DECL|function|gimp_parasite_data_size (const GimpParasite * parasite)
name|gimp_parasite_data_size
parameter_list|(
specifier|const
name|GimpParasite
modifier|*
name|parasite
parameter_list|)
block|{
if|if
condition|(
name|parasite
condition|)
return|return
name|parasite
operator|->
name|size
return|;
return|return
literal|0
return|;
block|}
end_function

end_unit

