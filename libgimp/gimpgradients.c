begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpgradients.c  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_undef
undef|#
directive|undef
name|GIMP_DISABLE_DEPRECATED
end_undef

begin_undef
undef|#
directive|undef
name|__GIMP_GRADIENTS_H__
end_undef

begin_include
include|#
directive|include
file|"gimpgradients.h"
end_include

begin_comment
comment|/**  * gimp_gradients_get_gradient:  *  * This procedure is deprecated! Use gimp_context_get_gradient() instead.  *  * Returns: The name of the active gradient.  */
end_comment

begin_function
name|gchar
modifier|*
DECL|function|gimp_gradients_get_gradient (void)
name|gimp_gradients_get_gradient
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|gimp_context_get_gradient
argument_list|()
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_gradients_set_gradient:  * @name: The name of the gradient to set.  *  * This procedure is deprecated! Use gimp_context_set_gradient() instead.  *  * Returns: TRUE on success.  */
end_comment

begin_function
name|gboolean
DECL|function|gimp_gradients_set_gradient (const gchar * name)
name|gimp_gradients_set_gradient
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|)
block|{
return|return
name|gimp_context_set_gradient
argument_list|(
name|name
argument_list|)
return|;
block|}
end_function

end_unit

