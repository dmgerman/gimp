begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpplugin.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<string.h>
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_function
name|gboolean
DECL|function|gimp_plugin_icon_register (const gchar * procedure_name,GimpIconType icon_type,const guint8 * icon_data)
name|gimp_plugin_icon_register
parameter_list|(
specifier|const
name|gchar
modifier|*
name|procedure_name
parameter_list|,
name|GimpIconType
name|icon_type
parameter_list|,
specifier|const
name|guint8
modifier|*
name|icon_data
parameter_list|)
block|{
name|gint
name|icon_data_length
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|procedure_name
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|icon_data
operator|!=
name|NULL
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|icon_type
condition|)
block|{
case|case
name|GIMP_ICON_TYPE_STOCK_ID
case|:
case|case
name|GIMP_ICON_TYPE_IMAGE_FILE
case|:
name|icon_data_length
operator|=
name|strlen
argument_list|(
operator|(
specifier|const
name|gchar
operator|*
operator|)
name|icon_data
argument_list|)
operator|+
literal|1
expr_stmt|;
break|break;
case|case
name|GIMP_ICON_TYPE_INLINE_PIXBUF
case|:
name|g_return_val_if_fail
argument_list|(
name|g_ntohl
argument_list|(
operator|*
operator|(
operator|(
name|gint32
operator|*
operator|)
name|icon_data
operator|)
argument_list|)
operator|==
literal|0x47646b50
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|icon_data_length
operator|=
name|g_ntohl
argument_list|(
operator|*
operator|(
operator|(
name|gint32
operator|*
operator|)
operator|(
name|icon_data
operator|+
literal|4
operator|)
operator|)
argument_list|)
expr_stmt|;
break|break;
default|default:
name|g_return_val_if_reached
argument_list|(
name|FALSE
argument_list|)
expr_stmt|;
block|}
return|return
name|_gimp_plugin_icon_register
argument_list|(
name|procedure_name
argument_list|,
name|icon_type
argument_list|,
name|icon_data_length
argument_list|,
name|icon_data
argument_list|)
return|;
block|}
end_function

end_unit

