begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/*  * This is a plug-in for GIMP.  *  * Generates clickable image maps.  *  * Copyright (C) 1998-1999 Maurits Rijk  lpeek.mrijk@consunet.nl  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  *  */
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
file|"imap_string.h"
end_include

begin_function
name|gchar
modifier|*
DECL|function|g_strreplace (gchar ** old_str,const gchar * new_str)
name|g_strreplace
parameter_list|(
name|gchar
modifier|*
modifier|*
name|old_str
parameter_list|,
specifier|const
name|gchar
modifier|*
name|new_str
parameter_list|)
block|{
if|if
condition|(
operator|*
name|old_str
operator|!=
name|new_str
condition|)
block|{
name|g_free
argument_list|(
operator|*
name|old_str
argument_list|)
expr_stmt|;
operator|*
name|old_str
operator|=
name|g_strdup
argument_list|(
name|new_str
argument_list|)
expr_stmt|;
block|}
return|return
operator|*
name|old_str
return|;
block|}
end_function

end_unit

