begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpselectbutton.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
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

begin_include
include|#
directive|include
file|"gimpuitypes.h"
end_include

begin_include
include|#
directive|include
file|"gimpselectbutton.h"
end_include

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_select_button_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSelectButton,gimp_select_button,GTK_TYPE_HBOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSelectButton
argument_list|,
argument|gimp_select_button
argument_list|,
argument|GTK_TYPE_HBOX
argument_list|)
end_macro

begin_function
specifier|static
name|void
name|gimp_select_button_class_init
parameter_list|(
name|GimpSelectButtonClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
init|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_select_button_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_select_button_init (GimpSelectButton * select_button)
name|gimp_select_button_init
parameter_list|(
name|GimpSelectButton
modifier|*
name|select_button
parameter_list|)
block|{
name|select_button
operator|->
name|temp_callback
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_select_button_close_popup:  * @select_button: A #GimpSelectButton  *  * Closes the popup window associated with @select_button.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_select_button_close_popup (GimpSelectButton * select_button)
name|gimp_select_button_close_popup
parameter_list|(
name|GimpSelectButton
modifier|*
name|select_button
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SELECT_BUTTON
argument_list|(
name|select_button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|select_button
operator|->
name|temp_callback
condition|)
block|{
name|GIMP_SELECT_BUTTON_GET_CLASS
argument_list|(
name|select_button
argument_list|)
operator|->
name|select_destroy
argument_list|(
name|select_button
operator|->
name|temp_callback
argument_list|)
expr_stmt|;
name|select_button
operator|->
name|temp_callback
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_select_button_destroy (GtkObject * object)
name|gimp_select_button_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpSelectButton
modifier|*
name|select_button
init|=
name|GIMP_SELECT_BUTTON
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|gimp_select_button_close_popup
argument_list|(
name|select_button
argument_list|)
expr_stmt|;
name|GTK_OBJECT_CLASS
argument_list|(
name|gimp_select_button_parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

