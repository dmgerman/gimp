begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasite.c  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"parasiteP.h"
end_include

begin_include
include|#
directive|include
file|"parasite.h"
end_include

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

begin_function
DECL|function|parasite_print (Parasite * p)
specifier|static
name|void
name|parasite_print
parameter_list|(
name|Parasite
modifier|*
name|p
parameter_list|)
block|{
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
block|{
name|printf
argument_list|(
literal|"(pid %d)attempt to print a null parasite\n"
argument_list|,
name|getpid
argument_list|()
argument_list|)
expr_stmt|;
return|return;
block|}
name|printf
argument_list|(
literal|"(pid %d), parasite: %X\n"
argument_list|,
name|getpid
argument_list|()
argument_list|,
name|p
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|name
condition|)
name|printf
argument_list|(
literal|"\tname: %s\n"
argument_list|,
name|p
operator|->
name|name
argument_list|)
expr_stmt|;
else|else
name|printf
argument_list|(
literal|"\tname: NULL\n"
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\tflags: %d\n"
argument_list|,
name|p
operator|->
name|flags
argument_list|)
expr_stmt|;
name|printf
argument_list|(
literal|"\tsize: %d\n"
argument_list|,
name|p
operator|->
name|size
argument_list|)
expr_stmt|;
if|if
condition|(
name|p
operator|->
name|size
operator|>
literal|0
condition|)
name|printf
argument_list|(
literal|"\tdata: %X\n"
argument_list|,
name|p
operator|->
name|data
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|Parasite
modifier|*
DECL|function|parasite_new (const char * name,guint32 flags,guint32 size,const void * data)
name|parasite_new
parameter_list|(
specifier|const
name|char
modifier|*
name|name
parameter_list|,
name|guint32
name|flags
parameter_list|,
name|guint32
name|size
parameter_list|,
specifier|const
name|void
modifier|*
name|data
parameter_list|)
block|{
name|Parasite
modifier|*
name|p
decl_stmt|;
name|p
operator|=
operator|(
name|Parasite
operator|*
operator|)
name|g_malloc
argument_list|(
sizeof|sizeof
argument_list|(
name|Parasite
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|name
condition|)
name|p
operator|->
name|name
operator|=
name|g_strdup
argument_list|(
name|name
argument_list|)
expr_stmt|;
else|else
name|p
operator|->
name|name
operator|=
name|NULL
expr_stmt|;
name|p
operator|->
name|flags
operator|=
name|flags
expr_stmt|;
name|p
operator|->
name|size
operator|=
name|size
expr_stmt|;
if|if
condition|(
name|size
condition|)
name|p
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
name|p
operator|->
name|data
operator|=
name|NULL
expr_stmt|;
return|return
name|p
return|;
block|}
end_function

begin_function
name|void
DECL|function|parasite_free (Parasite * parasite)
name|parasite_free
parameter_list|(
name|Parasite
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
name|int
DECL|function|parasite_is_type (const Parasite * parasite,const char * name)
name|parasite_is_type
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|parasite
parameter_list|,
specifier|const
name|char
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
name|Parasite
modifier|*
DECL|function|parasite_copy (const Parasite * parasite)
name|parasite_copy
parameter_list|(
specifier|const
name|Parasite
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
name|parasite_new
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
name|Parasite
modifier|*
DECL|function|parasite_error ()
name|parasite_error
parameter_list|()
block|{
specifier|static
name|Parasite
modifier|*
name|error_p
init|=
name|NULL
decl_stmt|;
if|if
condition|(
operator|!
name|error_p
condition|)
name|error_p
operator|=
name|parasite_new
argument_list|(
literal|"error"
argument_list|,
literal|0
argument_list|,
literal|0
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|error_p
return|;
block|}
end_function

begin_function
name|int
DECL|function|parasite_is_error (const Parasite * p)
name|parasite_is_error
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|p
parameter_list|)
block|{
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
return|return
name|TRUE
return|;
return|return
name|parasite_is_type
argument_list|(
name|p
argument_list|,
literal|"error"
argument_list|)
return|;
block|}
end_function

begin_function
name|int
DECL|function|parasite_is_persistant (const Parasite * p)
name|parasite_is_persistant
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|p
parameter_list|)
block|{
if|if
condition|(
name|p
operator|==
name|NULL
condition|)
return|return
name|FALSE
return|;
return|return
operator|(
name|p
operator|->
name|flags
operator|&
name|PARASITE_PERSISTANT
operator|)
return|;
block|}
end_function

end_unit

