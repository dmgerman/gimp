begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * Copyright (C) 2003  Henrik Brix Andersen<brix@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"libgimpbase/gimplimits.h"
end_include

begin_include
include|#
directive|include
file|"libgimpwidgets/gimpwidgets.h"
end_include

begin_include
include|#
directive|include
file|"dialogs-types.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig-utils.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpcoreconfig.h"
end_include

begin_include
include|#
directive|include
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-grid.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage-undo-push.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpgrid.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpgrideditor.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimphelp-ids.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"grid-dialog.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_define
DECL|macro|GRID_RESPONSE_RESET
define|#
directive|define
name|GRID_RESPONSE_RESET
value|1
end_define

begin_define
DECL|macro|GRID_COLOR_SIZE
define|#
directive|define
name|GRID_COLOR_SIZE
value|20
end_define

begin_comment
comment|/*  local functions  */
end_comment

begin_function_decl
specifier|static
name|void
name|grid_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  public function  */
end_comment

begin_function
name|GtkWidget
modifier|*
DECL|function|grid_dialog_new (GimpImage * gimage,GtkWidget * parent)
name|grid_dialog_new
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|)
block|{
name|GimpGrid
modifier|*
name|grid
decl_stmt|;
name|GimpGrid
modifier|*
name|grid_backup
decl_stmt|;
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|editor
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|parent
operator|==
name|NULL
operator|||
name|GTK_IS_WIDGET
argument_list|(
name|parent
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|grid
operator|=
name|gimp_image_get_grid
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
name|grid_backup
operator|=
name|gimp_config_duplicate
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|grid
argument_list|)
argument_list|)
expr_stmt|;
name|dialog
operator|=
name|gimp_viewable_dialog_new
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Configure Grid"
argument_list|)
argument_list|,
literal|"gimp-grid-configure"
argument_list|,
name|GIMP_STOCK_GRID
argument_list|,
name|_
argument_list|(
literal|"Configure Image Grid"
argument_list|)
argument_list|,
name|parent
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|GIMP_HELP_IMAGE_GRID
argument_list|,
name|GIMP_STOCK_RESET
argument_list|,
name|GRID_RESPONSE_RESET
argument_list|,
name|GTK_STOCK_CANCEL
argument_list|,
name|GTK_RESPONSE_CANCEL
argument_list|,
name|GTK_STOCK_OK
argument_list|,
name|GTK_RESPONSE_OK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|dialog
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dialog
argument_list|,
literal|"response"
argument_list|,
name|G_CALLBACK
argument_list|(
name|grid_dialog_response
argument_list|)
argument_list|,
name|dialog
argument_list|)
expr_stmt|;
name|editor
operator|=
name|gimp_grid_editor_new
argument_list|(
name|grid
argument_list|,
name|gimage
operator|->
name|xresolution
argument_list|,
name|gimage
operator|->
name|yresolution
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|editor
argument_list|)
argument_list|,
literal|12
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|editor
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|editor
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimage"
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
name|g_object_set_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid"
argument_list|,
name|grid
argument_list|)
expr_stmt|;
name|g_object_set_data_full
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid-backup"
argument_list|,
name|grid_backup
argument_list|,
operator|(
name|GDestroyNotify
operator|)
name|g_object_unref
argument_list|)
expr_stmt|;
return|return
name|dialog
return|;
block|}
end_function

begin_comment
comment|/*  local functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|grid_dialog_response (GtkWidget * widget,gint response_id,GtkWidget * dialog)
name|grid_dialog_response
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|response_id
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|GimpImage
modifier|*
name|grid
decl_stmt|;
name|GimpGrid
modifier|*
name|grid_backup
decl_stmt|;
name|gimage
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"gimage"
argument_list|)
expr_stmt|;
name|grid
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid"
argument_list|)
expr_stmt|;
name|grid_backup
operator|=
name|g_object_get_data
argument_list|(
name|G_OBJECT
argument_list|(
name|dialog
argument_list|)
argument_list|,
literal|"grid-backup"
argument_list|)
expr_stmt|;
switch|switch
condition|(
name|response_id
condition|)
block|{
case|case
name|GRID_RESPONSE_RESET
case|:
name|gimp_config_sync
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|gimage
operator|->
name|gimp
operator|->
name|config
operator|->
name|default_grid
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|grid
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
break|break;
case|case
name|GTK_RESPONSE_OK
case|:
if|if
condition|(
operator|!
name|gimp_config_is_equal_to
argument_list|(
name|GIMP_CONFIG
argument_list|(
name|grid_backup
argument_list|)
argument_list|,
name|GIMP_CONFIG
argument_list|(
name|grid
argument_list|)
argument_list|)
condition|)
block|{
name|gimp_image_undo_push_image_grid
argument_list|(
name|gimage
argument_list|,
name|_
argument_list|(
literal|"Grid"
argument_list|)
argument_list|,
name|grid_backup
argument_list|)
expr_stmt|;
block|}
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
break|break;
default|default:
name|gimp_image_set_grid
argument_list|(
name|GIMP_IMAGE
argument_list|(
name|gimage
argument_list|)
argument_list|,
name|grid_backup
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_widget_destroy
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

