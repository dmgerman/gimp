begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball  *  * gimpedit.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
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
comment|/**  * gimp_edit_paste_as_new:  *  * Paste buffer to a new image.  *  * This procedure pastes a copy of the internal GIMP edit buffer to a  * new image. The GIMP edit buffer will be empty unless a call was  * previously made to either gimp_edit_cut() or gimp_edit_copy(). This  * procedure returns the new image or -1 if the edit buffer was empty.  *  * Deprecated: Use gimp_edit_paste_as_new_image() instead.  *  * Returns: The new image.  *  * Since: 2.4  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_edit_paste_as_new (void)
name|gimp_edit_paste_as_new
parameter_list|(
name|void
parameter_list|)
block|{
return|return
name|gimp_edit_paste_as_new_image
argument_list|()
return|;
block|}
end_function

begin_comment
comment|/**  * gimp_edit_named_paste_as_new:  * @buffer_name: The name of the buffer to paste.  *  * Paste named buffer to a new image.  *  * This procedure works like gimp_edit_paste_as_new_image() but pastes a  * named buffer instead of the global buffer.  *  * Deprecated: Use gimp_edit_named_paste_as_new_image() instead.  *  * Returns: The new image.  *  * Since: 2.4  **/
end_comment

begin_function
name|gint32
DECL|function|gimp_edit_named_paste_as_new (const gchar * buffer_name)
name|gimp_edit_named_paste_as_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|buffer_name
parameter_list|)
block|{
return|return
name|gimp_edit_named_paste_as_new_image
argument_list|(
name|buffer_name
argument_list|)
return|;
block|}
end_function

end_unit

