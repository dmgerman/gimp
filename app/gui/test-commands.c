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
file|"libgimpbase/gimpbase.h"
end_include

begin_include
include|#
directive|include
file|"libgimpmath/gimpmath.h"
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
file|"core/gimp.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpchannel.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpdatafactory.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"core/gimplayer.h"
end_include

begin_include
include|#
directive|include
file|"config/gimpconfig.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainergridview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpcontainermenuimpl.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdatafactoryview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpimagedock.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdevices.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockable.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimpdrawabletreeview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_comment
comment|/*****  Container View Test Dialogs  *****/
end_comment

begin_function
specifier|static
name|void
DECL|function|container_view_scale_callback (GtkAdjustment * adj,GimpContainerView * view)
name|container_view_scale_callback
parameter_list|(
name|GtkAdjustment
modifier|*
name|adj
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_container_view_set_preview_size
argument_list|(
name|view
argument_list|,
name|ROUND
argument_list|(
name|adj
operator|->
name|value
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|brushes_callback (GtkWidget * widget,GdkModifierType state,GimpContainerView * view)
name|brushes_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_container_view_set_container
argument_list|(
name|view
argument_list|,
name|view
operator|->
name|context
operator|->
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|patterns_callback (GtkWidget * widget,GdkModifierType state,GimpContainerView * view)
name|patterns_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_container_view_set_container
argument_list|(
name|view
argument_list|,
name|view
operator|->
name|context
operator|->
name|gimp
operator|->
name|pattern_factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradients_callback (GtkWidget * widget,GdkModifierType state,GimpContainerView * view)
name|gradients_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_container_view_set_container
argument_list|(
name|view
argument_list|,
name|view
operator|->
name|context
operator|->
name|gimp
operator|->
name|gradient_factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|palettes_callback (GtkWidget * widget,GdkModifierType state,GimpContainerView * view)
name|palettes_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_container_view_set_container
argument_list|(
name|view
argument_list|,
name|view
operator|->
name|context
operator|->
name|gimp
operator|->
name|palette_factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|images_callback (GtkWidget * widget,GdkModifierType state,GimpContainerView * view)
name|images_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GdkModifierType
name|state
parameter_list|,
name|GimpContainerView
modifier|*
name|view
parameter_list|)
block|{
name|gimp_container_view_set_container
argument_list|(
name|view
argument_list|,
name|view
operator|->
name|context
operator|->
name|gimp
operator|->
name|images
argument_list|)
expr_stmt|;
block|}
end_function

begin_comment
comment|/* static void null_callback (GtkWidget         *widget, 	       GimpContainerView *view) {   gimp_container_view_set_container (view, NULL); } */
end_comment

begin_function
specifier|static
name|void
DECL|function|container_multi_view_new (gboolean list,gchar * title,GimpContainer * container,GimpContext * context,gint preview_size)
name|container_multi_view_new
parameter_list|(
name|gboolean
name|list
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|preview_size
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dialog
decl_stmt|;
name|GtkWidget
modifier|*
name|view
decl_stmt|;
name|GtkObject
modifier|*
name|adjustment
decl_stmt|;
name|GtkWidget
modifier|*
name|scale
decl_stmt|;
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
if|if
condition|(
name|list
condition|)
block|{
name|view
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|FALSE
argument_list|,
literal|5
argument_list|,
literal|5
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|view
operator|=
name|gimp_container_grid_view_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
name|FALSE
argument_list|,
literal|5
argument_list|,
literal|5
argument_list|)
expr_stmt|;
block|}
name|dialog
operator|=
name|gimp_dialog_new
argument_list|(
name|title
argument_list|,
literal|"test"
argument_list|,
name|gimp_standard_help_func
argument_list|,
name|NULL
argument_list|,
name|GTK_WIN_POS_MOUSE
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|"Images"
argument_list|,
name|images_callback
argument_list|,
name|view
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
comment|/* 				  "NULL", null_callback, 				  view, NULL, NULL, FALSE, FALSE, 				*/
name|GTK_STOCK_CLOSE
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_brush
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
literal|32
argument_list|,
literal|32
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|preview
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|brushes_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"brush_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|preview
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_pattern
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
literal|32
argument_list|,
literal|32
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|preview
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|patterns_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"pattern_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|preview
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_gradient
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
literal|32
argument_list|,
literal|32
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|preview
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gradients_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"gradient_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|preview
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
name|preview
operator|=
name|gimp_preview_new_full
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|gimp_context_get_palette
argument_list|(
name|context
argument_list|)
argument_list|)
argument_list|,
literal|32
argument_list|,
literal|32
argument_list|,
literal|1
argument_list|,
name|FALSE
argument_list|,
name|TRUE
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
argument_list|,
name|preview
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|preview
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|preview
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
argument_list|(
name|palettes_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|context
argument_list|,
literal|"palette_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|preview
argument_list|,
name|G_CONNECT_SWAPPED
argument_list|)
expr_stmt|;
if|#
directive|if
literal|0
block|preview =     gimp_preview_new_full (GIMP_VIEWABLE (gimp_context_get_image (context)), 			   32, 32, 1, 			   FALSE, TRUE, FALSE);   gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->action_area), preview, 		      FALSE, FALSE, 0);   gtk_widget_show (preview);    g_signal_connect (preview, "clicked", 		    G_CALLBACK (images_callback), 		    view);    g_signal_connect_object (context, "pattern_changed", 			   G_CALLBACK (gimp_preview_set_viewable), 			   preview, 			   G_CONNECT_SWAPPED);
endif|#
directive|endif
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
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|view
argument_list|)
expr_stmt|;
name|adjustment
operator|=
name|gtk_adjustment_new
argument_list|(
name|preview_size
argument_list|,
literal|16
argument_list|,
literal|64
argument_list|,
literal|4
argument_list|,
literal|4
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|scale
operator|=
name|gtk_hscale_new
argument_list|(
name|GTK_ADJUSTMENT
argument_list|(
name|adjustment
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|vbox
argument_list|)
argument_list|,
name|scale
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|scale
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|adjustment
argument_list|,
literal|"value_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|container_view_scale_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dialog
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_multi_container_list_view_cmd_callback (GtkWidget * widget,gpointer data)
name|test_multi_container_list_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gimp
operator|=
name|GIMP
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|container_multi_view_new
argument_list|(
name|TRUE
argument_list|,
literal|"Multi List"
argument_list|,
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_multi_container_grid_view_cmd_callback (GtkWidget * widget,gpointer data)
name|test_multi_container_grid_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gimp
operator|=
name|GIMP
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|container_multi_view_new
argument_list|(
name|FALSE
argument_list|,
literal|"Multi Grid"
argument_list|,
name|gimp
operator|->
name|brush_factory
operator|->
name|container
argument_list|,
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|,
literal|32
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_serialize_context_cmd_callback (GtkWidget * widget,gpointer data)
name|test_serialize_context_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimp
operator|=
name|GIMP
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"test-context"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_serialize
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
argument_list|,
name|filename
argument_list|,
literal|"GIMP test-context"
argument_list|,
literal|"end of test-context"
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"Serializing Context failed:\n%s"
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
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_deserialize_context_cmd_callback (GtkWidget * widget,gpointer data)
name|test_deserialize_context_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|)
block|{
name|Gimp
modifier|*
name|gimp
decl_stmt|;
name|gchar
modifier|*
name|filename
decl_stmt|;
name|GError
modifier|*
name|error
init|=
name|NULL
decl_stmt|;
name|gimp
operator|=
name|GIMP
argument_list|(
name|data
argument_list|)
expr_stmt|;
name|filename
operator|=
name|gimp_personal_rc_file
argument_list|(
literal|"test-context"
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimp_config_deserialize
argument_list|(
name|G_OBJECT
argument_list|(
name|gimp_get_user_context
argument_list|(
name|gimp
argument_list|)
argument_list|)
argument_list|,
name|filename
argument_list|,
name|NULL
argument_list|,
operator|&
name|error
argument_list|)
condition|)
block|{
name|g_message
argument_list|(
literal|"Deserializing Context failed:\n%s"
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
name|filename
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

