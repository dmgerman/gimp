begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* Functions for bulding and parsing string representations of  * various standard parasite types.  *  * Copyright (C) 1999 Tor Lillqvist<tml@iki.fi>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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
file|<stdlib.h>
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

begin_include
include|#
directive|include
file|"libgimp/parasiteio.h"
end_include

begin_function
name|void
DECL|function|pixpipeparams_init (PixPipeParams * params)
name|pixpipeparams_init
parameter_list|(
name|PixPipeParams
modifier|*
name|params
parameter_list|)
block|{
name|int
name|i
decl_stmt|;
name|params
operator|->
name|step
operator|=
literal|100
expr_stmt|;
name|params
operator|->
name|ncells
operator|=
literal|1
expr_stmt|;
name|params
operator|->
name|cellwidth
operator|=
literal|1
expr_stmt|;
name|params
operator|->
name|cellheight
operator|=
literal|1
expr_stmt|;
name|params
operator|->
name|dim
operator|=
literal|1
expr_stmt|;
name|params
operator|->
name|cols
operator|=
literal|1
expr_stmt|;
name|params
operator|->
name|rows
operator|=
literal|1
expr_stmt|;
name|params
operator|->
name|placement
operator|=
literal|"constant"
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|PIXPIPE_MAXDIM
condition|;
name|i
operator|++
control|)
name|params
operator|->
name|selection
index|[
name|i
index|]
operator|=
literal|"random"
expr_stmt|;
name|params
operator|->
name|rank
index|[
literal|0
index|]
operator|=
literal|1
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|1
init|;
name|i
operator|<
name|PIXPIPE_MAXDIM
condition|;
name|i
operator|++
control|)
name|params
operator|->
name|rank
index|[
name|i
index|]
operator|=
literal|0
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|pixpipeparams_parse (gchar * string,PixPipeParams * params)
name|pixpipeparams_parse
parameter_list|(
name|gchar
modifier|*
name|string
parameter_list|,
name|PixPipeParams
modifier|*
name|params
parameter_list|)
block|{
name|guchar
modifier|*
name|p
decl_stmt|,
modifier|*
name|q
decl_stmt|,
modifier|*
name|r
decl_stmt|;
comment|/* Don't you love single-char identifiers?  */
name|gint
name|i
decl_stmt|;
name|q
operator|=
name|string
expr_stmt|;
while|while
condition|(
operator|(
name|p
operator|=
name|strtok
argument_list|(
name|q
argument_list|,
literal|" \r\n"
argument_list|)
operator|)
operator|!=
name|NULL
condition|)
block|{
name|q
operator|=
name|NULL
expr_stmt|;
name|r
operator|=
name|strchr
argument_list|(
name|p
argument_list|,
literal|':'
argument_list|)
expr_stmt|;
if|if
condition|(
name|r
condition|)
operator|*
name|r
operator|=
literal|0
expr_stmt|;
if|if
condition|(
name|strcmp
argument_list|(
name|p
argument_list|,
literal|"ncells"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
condition|)
name|params
operator|->
name|ncells
operator|=
name|atoi
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|p
argument_list|,
literal|"step"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
condition|)
name|params
operator|->
name|step
operator|=
name|atoi
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|p
argument_list|,
literal|"dim"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
condition|)
name|params
operator|->
name|dim
operator|=
name|atoi
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|p
argument_list|,
literal|"cols"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
condition|)
name|params
operator|->
name|cols
operator|=
name|atoi
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|p
argument_list|,
literal|"rows"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
condition|)
name|params
operator|->
name|rows
operator|=
name|atoi
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|p
argument_list|,
literal|"cellwidth"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
condition|)
name|params
operator|->
name|cellwidth
operator|=
name|atoi
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|p
argument_list|,
literal|"cellheight"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
condition|)
name|params
operator|->
name|cellheight
operator|=
name|atoi
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strcmp
argument_list|(
name|p
argument_list|,
literal|"placement"
argument_list|)
operator|==
literal|0
condition|)
block|{
if|if
condition|(
name|r
condition|)
name|params
operator|->
name|placement
operator|=
name|g_strdup
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|p
argument_list|,
literal|"rank"
argument_list|,
name|strlen
argument_list|(
literal|"rank"
argument_list|)
argument_list|)
operator|==
literal|0
operator|&&
name|r
condition|)
block|{
if|if
condition|(
name|r
condition|)
block|{
name|i
operator|=
name|atoi
argument_list|(
name|p
operator|+
name|strlen
argument_list|(
literal|"rank"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|>=
literal|0
operator|&&
name|i
operator|<
name|params
operator|->
name|dim
condition|)
name|params
operator|->
name|rank
index|[
name|i
index|]
operator|=
name|atoi
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|strncmp
argument_list|(
name|p
argument_list|,
literal|"sel"
argument_list|,
name|strlen
argument_list|(
literal|"sel"
argument_list|)
argument_list|)
operator|==
literal|0
operator|&&
name|r
condition|)
block|{
if|if
condition|(
name|r
condition|)
block|{
name|i
operator|=
name|atoi
argument_list|(
name|p
operator|+
name|strlen
argument_list|(
literal|"sel"
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|i
operator|>=
literal|0
operator|&&
name|i
operator|<
name|params
operator|->
name|dim
condition|)
name|params
operator|->
name|selection
index|[
name|i
index|]
operator|=
name|g_strdup
argument_list|(
name|r
operator|+
literal|1
argument_list|)
expr_stmt|;
block|}
block|}
if|if
condition|(
name|r
condition|)
operator|*
name|r
operator|=
literal|':'
expr_stmt|;
block|}
block|}
end_function

begin_function
name|gchar
modifier|*
DECL|function|pixpipeparams_build (PixPipeParams * params)
name|pixpipeparams_build
parameter_list|(
name|PixPipeParams
modifier|*
name|params
parameter_list|)
block|{
name|GString
modifier|*
name|s
init|=
name|g_string_new
argument_list|(
name|NULL
argument_list|)
decl_stmt|;
name|gchar
modifier|*
name|str
decl_stmt|;
name|int
name|i
decl_stmt|;
name|g_string_sprintf
argument_list|(
name|s
argument_list|,
literal|"ncells:%d cellwidth:%d cellheight:%d "
literal|"step:%d dim:%d cols:%d rows:%d placement:%s"
argument_list|,
name|params
operator|->
name|ncells
argument_list|,
name|params
operator|->
name|cellwidth
argument_list|,
name|params
operator|->
name|cellheight
argument_list|,
name|params
operator|->
name|step
argument_list|,
name|params
operator|->
name|dim
argument_list|,
name|params
operator|->
name|cols
argument_list|,
name|params
operator|->
name|rows
argument_list|,
name|params
operator|->
name|placement
argument_list|)
expr_stmt|;
for|for
control|(
name|i
operator|=
literal|0
init|;
name|i
operator|<
name|params
operator|->
name|dim
condition|;
name|i
operator|++
control|)
block|{
name|g_string_sprintfa
argument_list|(
name|s
argument_list|,
literal|" rank%d:%d"
argument_list|,
name|i
argument_list|,
name|params
operator|->
name|rank
index|[
name|i
index|]
argument_list|)
expr_stmt|;
name|g_string_sprintfa
argument_list|(
name|s
argument_list|,
literal|" sel%d:%s"
argument_list|,
name|i
argument_list|,
name|params
operator|->
name|selection
index|[
name|i
index|]
argument_list|)
expr_stmt|;
block|}
name|str
operator|=
name|s
operator|->
name|str
expr_stmt|;
name|g_string_free
argument_list|(
name|s
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
return|return
name|str
return|;
block|}
end_function

end_unit

