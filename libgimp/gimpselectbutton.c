begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpselectbutton.c  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
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
comment|/**  * SECTION: gimpselectbutton  * @title: GimpSelectButton  * @short_description: The base class of the data select buttons.  *  * The base class of the brush, pattern, gradient, palette and font  * select buttons.  **/
end_comment

begin_comment
comment|/*  local function prototypes  */
end_comment

begin_function_decl
specifier|static
name|void
name|gimp_select_button_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE (GimpSelectButton,gimp_select_button,GTK_TYPE_BOX)
name|G_DEFINE_TYPE
argument_list|(
argument|GimpSelectButton
argument_list|,
argument|gimp_select_button
argument_list|,
argument|GTK_TYPE_BOX
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
name|GObjectClass
modifier|*
name|object_class
init|=
name|G_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
decl_stmt|;
name|object_class
operator|->
name|dispose
operator|=
name|gimp_select_button_dispose
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
name|gtk_orientable_set_orientation
argument_list|(
name|GTK_ORIENTABLE
argument_list|(
name|select_button
argument_list|)
argument_list|,
name|GTK_ORIENTATION_HORIZONTAL
argument_list|)
expr_stmt|;
name|select_button
operator|->
name|temp_callback
operator|=
name|NULL
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_select_button_dispose (GObject * object)
name|gimp_select_button_dispose
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|gimp_select_button_close_popup
argument_list|(
name|GIMP_SELECT_BUTTON
argument_list|(
name|object
argument_list|)
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|gimp_select_button_parent_class
argument_list|)
operator|->
name|dispose
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/**  * gimp_select_button_close_popup:  * @button: A #GimpSelectButton  *  * Closes the popup window associated with @button.  *  * Since: GIMP 2.4  */
end_comment

begin_function
name|void
DECL|function|gimp_select_button_close_popup (GimpSelectButton * button)
name|gimp_select_button_close_popup
parameter_list|(
name|GimpSelectButton
modifier|*
name|button
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_SELECT_BUTTON
argument_list|(
name|button
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|button
operator|->
name|temp_callback
condition|)
block|{
name|GimpSelectButtonClass
modifier|*
name|klass
init|=
name|GIMP_SELECT_BUTTON_GET_CLASS
argument_list|(
name|button
argument_list|)
decl_stmt|;
name|klass
operator|->
name|select_destroy
argument_list|(
name|button
operator|->
name|temp_callback
argument_list|)
expr_stmt|;
name|button
operator|->
name|temp_callback
operator|=
name|NULL
expr_stmt|;
block|}
block|}
end_function

end_unit

