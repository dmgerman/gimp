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
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"gui-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpitemfactory.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplay.h"
end_include

begin_include
include|#
directive|include
file|"display/gimpdisplayshell.h"
end_include

begin_include
include|#
directive|include
file|"qmask-commands.h"
end_include

begin_include
include|#
directive|include
file|"qmask-menu.h"
end_include

begin_include
include|#
directive|include
file|"menus.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_decl_stmt
DECL|variable|qmask_menu_entries
name|GimpItemFactoryEntry
name|qmask_menu_entries
index|[]
init|=
block|{
block|{
block|{
name|N_
argument_list|(
literal|"/_QMask Active"
argument_list|)
block|,
name|NULL
block|,
name|qmask_toggle_cmd_callback
block|,
literal|0
block|,
literal|"<ToggleItem>"
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/---"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Mask _Selected Areas"
argument_list|)
block|,
name|NULL
block|,
name|qmask_invert_cmd_callback
block|,
name|TRUE
block|,
literal|"<RadioItem>"
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/Mask _Unselected Areas"
argument_list|)
block|,
name|NULL
block|,
name|qmask_invert_cmd_callback
block|,
name|FALSE
block|,
literal|"/Mask Selected Areas"
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|,
name|MENU_SEPARATOR
argument_list|(
literal|"/---"
argument_list|)
block|,
block|{
block|{
name|N_
argument_list|(
literal|"/_Configure Color and Opacity..."
argument_list|)
block|,
name|NULL
block|,
name|qmask_configure_cmd_callback
block|,
literal|0
block|}
block|,
name|NULL
block|,
name|NULL
block|,
name|NULL
block|}
block|}
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|gint
name|n_qmask_menu_entries
init|=
name|G_N_ELEMENTS
argument_list|(
name|qmask_menu_entries
argument_list|)
decl_stmt|;
end_decl_stmt

begin_function
name|void
DECL|function|qmask_menu_update (GtkItemFactory * factory,gpointer data)
name|qmask_menu_update
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
name|shell
operator|=
name|GIMP_DISPLAY_SHELL
argument_list|(
name|data
argument_list|)
expr_stmt|;
DECL|macro|SET_ACTIVE (menu,active)
define|#
directive|define
name|SET_ACTIVE
parameter_list|(
name|menu
parameter_list|,
name|active
parameter_list|)
define|\
value|gimp_item_factory_set_active (factory, "/" menu, (active))
DECL|macro|SET_COLOR (menu,color)
define|#
directive|define
name|SET_COLOR
parameter_list|(
name|menu
parameter_list|,
name|color
parameter_list|)
define|\
value|gimp_item_factory_set_color (factory, "/" menu, (color), FALSE)
name|SET_ACTIVE
argument_list|(
literal|"QMask Active"
argument_list|,
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_state
argument_list|)
expr_stmt|;
if|if
condition|(
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_inverted
condition|)
name|SET_ACTIVE
argument_list|(
literal|"Mask Selected Areas"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
else|else
name|SET_ACTIVE
argument_list|(
literal|"Mask Unselected Areas"
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|SET_COLOR
argument_list|(
literal|"Configure Color and Opacity..."
argument_list|,
operator|&
name|shell
operator|->
name|gdisp
operator|->
name|gimage
operator|->
name|qmask_color
argument_list|)
expr_stmt|;
undef|#
directive|undef
name|SET_SENSITIVE
undef|#
directive|undef
name|SET_COLOR
block|}
end_function

end_unit

