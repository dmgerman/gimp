begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2005 Peter Mattis and Spencer Kimball  *  * gimpgimprc.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|"gimp.h"
end_include

begin_comment
comment|/**  * gimp_get_color_configuration:  *  * Retrieve a copy of the current color management configuration.  *  * Returns: A copy of the core's #GimpColorConfig. You should unref  *          this copy if you don't need it any longer.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|GimpColorConfig
modifier|*
DECL|function|gimp_get_color_configuration (void)
name|gimp_get_color_configuration
parameter_list|(
name|void
parameter_list|)
block|{
name|GimpColorConfig
modifier|*
name|config
decl_stmt|;
name|gchar
modifier|*
name|text
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|text
operator|=
name|_gimp_get_color_configuration
argument_list|()
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|text
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|config
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_COLOR_CONFIG
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize_string
argument_list|(
name|config
argument_list|,
name|text
argument_list|,
operator|-
literal|1
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_warning
argument_list|(
literal|"failed to deserialize color configuration: %s"
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
name|text
argument_list|)
expr_stmt|;
return|return
name|config
return|;
block|}
end_function

end_unit

