begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* parasite.c  * Copyright (C) 1998 Jay Cox<jaycox@earthlink.net>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

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
name|NATIVE_WIN32
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

begin_ifdef
ifdef|#
directive|ifdef
name|DEBUG
end_ifdef

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
literal|"(pid %d), parasite: %p\n"
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
literal|"\tdata: %p\n"
argument_list|,
name|p
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
name|g_new
argument_list|(
name|Parasite
argument_list|,
literal|1
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
block|{
name|g_free
argument_list|(
name|p
argument_list|)
expr_stmt|;
return|return
name|NULL
return|;
block|}
name|p
operator|->
name|flags
operator|=
operator|(
name|flags
operator|&
literal|0xFF
operator|)
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
name|int
DECL|function|parasite_compare (const Parasite * a,const Parasite * b)
name|parasite_compare
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|a
parameter_list|,
specifier|const
name|Parasite
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
DECL|function|parasite_flags (const Parasite * p)
name|parasite_flags
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
literal|0
return|;
return|return
name|p
operator|->
name|flags
return|;
block|}
end_function

begin_function
name|int
DECL|function|parasite_is_persistent (const Parasite * p)
name|parasite_is_persistent
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
name|PARASITE_PERSISTENT
operator|)
return|;
block|}
end_function

begin_function
name|int
DECL|function|parasite_is_undoable (const Parasite * p)
name|parasite_is_undoable
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
name|PARASITE_UNDOABLE
operator|)
return|;
block|}
end_function

begin_function
name|int
DECL|function|parasite_has_flag (const Parasite * p,gulong flag)
name|parasite_has_flag
parameter_list|(
specifier|const
name|Parasite
modifier|*
name|p
parameter_list|,
name|gulong
name|flag
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
name|flag
operator|)
return|;
block|}
end_function

begin_function
specifier|const
name|char
modifier|*
DECL|function|parasite_name (const Parasite * p)
name|parasite_name
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
condition|)
return|return
name|p
operator|->
name|name
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
DECL|function|parasite_data (const Parasite * p)
name|void
modifier|*
name|parasite_data
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
condition|)
return|return
name|p
operator|->
name|data
return|;
return|return
name|NULL
return|;
block|}
end_function

begin_function
DECL|function|parasite_data_size (const Parasite * p)
name|long
name|parasite_data_size
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
condition|)
return|return
name|p
operator|->
name|size
return|;
return|return
literal|0
return|;
block|}
end_function

end_unit

