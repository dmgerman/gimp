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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpview.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox.h"
end_include

begin_include
include|#
directive|include
file|"gimptoolbox-image-area.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|CELL_WIDTH
define|#
directive|define
name|CELL_WIDTH
value|48
end_define

begin_define
DECL|macro|CELL_HEIGHT
define|#
directive|define
name|CELL_HEIGHT
value|48
end_define

begin_function
specifier|static
name|void
DECL|function|image_preview_clicked (GtkWidget * widget,GdkModifierType state,GimpToolbox * toolbox)
name|image_preview_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|)
block|{
name|gimp_dialog_factory_dialog_raise
argument_list|(
name|GIMP_DOCK
argument_list|(
name|toolbox
argument_list|)
operator|->
name|dialog_factory
argument_list|,
name|gtk_widget_get_screen
argument_list|(
name|widget
argument_list|)
argument_list|,
literal|"gimp-image-list|gimp-image-grid"
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_preview_drop_image (GtkWidget * widget,gint x,gint y,GimpViewable * viewable,gpointer data)
name|image_preview_drop_image
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|x
parameter_list|,
name|gint
name|y
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
init|=
name|GIMP_CONTEXT
argument_list|(
name|data
argument_list|)
decl_stmt|;
name|gimp_context_set_image
argument_list|(
name|context
argument_list|,
name|GIMP_IMAGE
argument_list|(
name|viewable
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|image_preview_set_viewable (GimpView * view,GimpViewable * old_viewable,GimpViewable * new_viewable)
name|image_preview_set_viewable
parameter_list|(
name|GimpView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|old_viewable
parameter_list|,
name|GimpViewable
modifier|*
name|new_viewable
parameter_list|)
block|{
if|if
condition|(
operator|!
name|old_viewable
operator|&&
name|new_viewable
condition|)
block|{
name|gimp_dnd_xds_source_add
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|,
operator|(
name|GimpDndDragViewableFunc
operator|)
name|gimp_view_get_viewable
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|old_viewable
operator|&&
operator|!
name|new_viewable
condition|)
block|{
name|gimp_dnd_xds_source_remove
argument_list|(
name|GTK_WIDGET
argument_list|(
name|view
argument_list|)
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_comment
comment|/*  public functions  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_toolbox_image_area_create (GimpToolbox * toolbox,gint width,gint height)
name|gimp_toolbox_image_area_create
parameter_list|(
name|GimpToolbox
modifier|*
name|toolbox
parameter_list|,
name|gint
name|width
parameter_list|,
name|gint
name|height
parameter_list|)
block|{
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|GtkWidget
modifier|*
name|image_view
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_TOOLBOX
argument_list|(
name|toolbox
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|context
operator|=
name|GIMP_DOCK
argument_list|(
name|toolbox
argument_list|)
operator|->
name|context
expr_stmt|;
name|image_view
operator|=
name|gimp_view_new_full_by_types
argument_list|(
name|GIMP_TYPE_VIEW
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|width
argument_list|,
name|height
argument_list|,
literal|0
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_view
argument_list|,
literal|"set_viewable"
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_preview_set_viewable
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_view_set_viewable
argument_list|(
name|GIMP_VIEW
argument_list|(
name|image_view
argument_list|)
argument_list|,
operator|(
name|GimpViewable
operator|*
operator|)
name|gimp_context_get_image
argument_list|(
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image_view
argument_list|)
expr_stmt|;
name|gimp_help_set_help_data
argument_list|(
name|image_view
argument_list|,
name|_
argument_list|(
literal|"The active image.\n"
literal|"Click to open the Image Dialog."
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"image_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_view_set_viewable
argument_list|)
argument_list|,
name|image_view
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|image_view
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|image_preview_clicked
argument_list|)
argument_list|,
name|toolbox
argument_list|)
expr_stmt|;
name|gimp_dnd_viewable_dest_add
argument_list|(
name|image_view
argument_list|,
name|GIMP_TYPE_IMAGE
argument_list|,
name|image_preview_drop_image
argument_list|,
name|context
argument_list|)
expr_stmt|;
return|return
name|image_view
return|;
block|}
end_function

end_unit

