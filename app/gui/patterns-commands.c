begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets/widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimppattern.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpwidgets-utils.h"
end_include

begin_include
include|#
directive|include
file|"patterns-commands.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|patterns_menu_set_sensitivity
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function
name|void
DECL|function|patterns_show_context_menu (GimpContainerEditor * editor)
name|patterns_show_context_menu
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
name|gint
name|x
decl_stmt|,
name|y
decl_stmt|;
name|patterns_menu_set_sensitivity
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|item_factory
operator|=
name|menus_get_patterns_factory
argument_list|()
expr_stmt|;
name|gimp_menu_position
argument_list|(
name|GTK_MENU
argument_list|(
name|item_factory
operator|->
name|widget
argument_list|)
argument_list|,
operator|&
name|x
argument_list|,
operator|&
name|y
argument_list|)
expr_stmt|;
name|gtk_item_factory_popup_with_data
argument_list|(
name|item_factory
argument_list|,
name|editor
argument_list|,
name|NULL
argument_list|,
name|x
argument_list|,
name|y
argument_list|,
literal|3
argument_list|,
literal|0
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|patterns_menu_set_sensitivity (GimpContainerEditor * editor)
name|patterns_menu_set_sensitivity
parameter_list|(
name|GimpContainerEditor
modifier|*
name|editor
parameter_list|)
block|{
name|GimpPattern
modifier|*
name|pattern
decl_stmt|;
name|pattern
operator|=
name|gimp_context_get_pattern
argument_list|(
name|editor
operator|->
name|view
operator|->
name|context
argument_list|)
expr_stmt|;
DECL|macro|SET_SENSITIVE (menu,condition)
define|#
directive|define
name|SET_SENSITIVE
parameter_list|(
name|menu
parameter_list|,
name|condition
parameter_list|)
define|\
value|menus_set_sensitive ("<Patterns>/" menu, (condition) != 0)
name|SET_SENSITIVE
argument_list|(
literal|"Duplicate Pattern"
argument_list|,
name|pattern
operator|&&
name|GIMP_DATA_GET_CLASS
argument_list|(
name|pattern
argument_list|)
operator|->
name|duplicate
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"Edit Pattern..."
argument_list|,
name|pattern
operator|&&
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|editor
argument_list|)
operator|->
name|data_edit_func
argument_list|)
expr_stmt|;
name|SET_SENSITIVE
argument_list|(
literal|"Delete Pattern..."
argument_list|,
name|pattern
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
block|}
end_function

end_unit

