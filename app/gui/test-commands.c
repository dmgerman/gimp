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
file|"core/core-types.h"
end_include

begin_include
include|#
directive|include
file|"tools/tools-types.h"
end_include

begin_include
include|#
directive|include
file|"widgets/widgets-types.h"
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
file|"widgets/gimpcontainerlistview.h"
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
file|"widgets/gimpdrawablelistview.h"
end_include

begin_include
include|#
directive|include
file|"widgets/gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"tools/tool_manager.h"
end_include

begin_include
include|#
directive|include
file|"dialogs.h"
end_include

begin_include
include|#
directive|include
file|"gradient-editor.h"
end_include

begin_include
include|#
directive|include
file|"context_manager.h"
end_include

begin_include
include|#
directive|include
file|"gimprc.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|return_if_no_display (gdisp)
define|#
directive|define
name|return_if_no_display
parameter_list|(
name|gdisp
parameter_list|)
define|\
value|gdisp = gdisplay_active (); \         if (!gdisp) return
end_define

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
DECL|function|brushes_callback (GtkWidget * widget,GimpContainerView * view)
name|brushes_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|global_brush_factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|patterns_callback (GtkWidget * widget,GimpContainerView * view)
name|patterns_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|global_pattern_factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gradients_callback (GtkWidget * widget,GimpContainerView * view)
name|gradients_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|global_gradient_factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|palettes_callback (GtkWidget * widget,GimpContainerView * view)
name|palettes_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|global_palette_factory
operator|->
name|container
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|images_callback (GtkWidget * widget,GimpContainerView * view)
name|images_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
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
name|image_context
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
DECL|function|container_view_new (gboolean list,gchar * title,GimpContainer * container,GimpContext * context,gint preview_size)
name|container_view_new
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
if|if
condition|(
name|list
condition|)
block|{
name|view
operator|=
name|gimp_container_list_view_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
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
literal|"_delete_event_"
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_WIDGET
argument_list|(
name|g_list_nth_data
argument_list|(
name|gtk_container_children
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GTK_BIN
argument_list|(
name|dialog
argument_list|)
operator|->
name|child
argument_list|)
argument_list|)
argument_list|,
literal|0
argument_list|)
argument_list|)
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
literal|256
argument_list|,
literal|16
argument_list|,
literal|16
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
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
specifier|static
name|void
DECL|function|data_factory_view_new (GimpViewType view_type,gchar * title,GimpDataFactory * factory,GimpDataEditFunc edit_func,GimpContext * context,gint preview_size)
name|data_factory_view_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|,
name|gchar
modifier|*
name|title
parameter_list|,
name|GimpDataFactory
modifier|*
name|factory
parameter_list|,
name|GimpDataEditFunc
name|edit_func
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
literal|"_delete_event_"
argument_list|,
name|gtk_widget_destroy
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|NULL
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_widget_hide
argument_list|(
name|GTK_DIALOG
argument_list|(
name|dialog
argument_list|)
operator|->
name|action_area
argument_list|)
expr_stmt|;
name|view
operator|=
name|gimp_data_factory_view_new
argument_list|(
name|view_type
argument_list|,
name|factory
argument_list|,
name|edit_func
argument_list|,
name|context
argument_list|,
name|preview_size
argument_list|,
literal|5
argument_list|,
literal|5
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
literal|256
argument_list|,
literal|16
argument_list|,
literal|16
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|container_view_scale_callback
argument_list|)
argument_list|,
name|GIMP_DATA_FACTORY_VIEW
argument_list|(
name|view
argument_list|)
operator|->
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
name|gimp_container_list_view_new
argument_list|(
name|container
argument_list|,
name|context
argument_list|,
name|preview_size
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
literal|"_delete_event_"
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|brushes_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"brush_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|patterns_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"pattern_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gradients_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"gradient_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|palettes_callback
argument_list|)
argument_list|,
name|view
argument_list|)
expr_stmt|;
name|gtk_signal_connect_object_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"palette_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_preview_set_viewable
argument_list|)
argument_list|,
name|GTK_OBJECT
argument_list|(
name|preview
argument_list|)
argument_list|)
expr_stmt|;
comment|/*   preview =     gimp_preview_new_full (GIMP_VIEWABLE (gimp_context_get_image (context)), 			   32, 32, 1, 			   FALSE, TRUE, FALSE);   gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog)->action_area), preview, 		      FALSE, FALSE, 0);   gtk_widget_show (preview);    gtk_signal_connect (GTK_OBJECT (preview), "clicked", 		      GTK_SIGNAL_FUNC (images_callback), 		      view);    gtk_signal_connect_object_while_alive     (GTK_OBJECT (context),      "pattern_changed",      GTK_SIGNAL_FUNC (gimp_preview_set_viewable),      GTK_OBJECT (preview));   */
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
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|adjustment
argument_list|)
argument_list|,
literal|"value_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
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
DECL|function|test_image_container_list_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_image_container_list_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|container_view_new
argument_list|(
name|TRUE
argument_list|,
literal|"Image List"
argument_list|,
name|image_context
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|64
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_image_container_grid_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_image_container_grid_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|container_view_new
argument_list|(
name|FALSE
argument_list|,
literal|"Image Grid"
argument_list|,
name|image_context
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|64
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_brush_container_list_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_brush_container_list_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
literal|"Brush List"
argument_list|,
name|global_brush_factory
argument_list|,
name|NULL
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_pattern_container_list_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_pattern_container_list_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
literal|"Pattern List"
argument_list|,
name|global_pattern_factory
argument_list|,
name|NULL
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_gradient_container_list_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_gradient_container_list_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
literal|"Gradient List"
argument_list|,
name|global_gradient_factory
argument_list|,
name|NULL
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_palette_container_list_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_palette_container_list_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|,
literal|"Palette List"
argument_list|,
name|global_palette_factory
argument_list|,
name|NULL
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_brush_container_grid_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_brush_container_grid_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_GRID
argument_list|,
literal|"Brush Grid"
argument_list|,
name|global_brush_factory
argument_list|,
name|NULL
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|32
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_pattern_container_grid_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_pattern_container_grid_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_GRID
argument_list|,
literal|"Pattern Grid"
argument_list|,
name|global_pattern_factory
argument_list|,
name|NULL
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_gradient_container_grid_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_gradient_container_grid_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_GRID
argument_list|,
literal|"Gradient Grid"
argument_list|,
name|global_gradient_factory
argument_list|,
name|NULL
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_palette_container_grid_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_palette_container_grid_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|data_factory_view_new
argument_list|(
name|GIMP_VIEW_TYPE_GRID
argument_list|,
literal|"Palette Grid"
argument_list|,
name|global_palette_factory
argument_list|,
name|NULL
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_multi_container_list_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_multi_container_list_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|container_multi_view_new
argument_list|(
name|TRUE
argument_list|,
literal|"Multi List"
argument_list|,
name|global_brush_factory
operator|->
name|container
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|24
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_multi_container_grid_view_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_multi_container_grid_view_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|container_multi_view_new
argument_list|(
name|FALSE
argument_list|,
literal|"Multi Grid"
argument_list|,
name|global_brush_factory
operator|->
name|container
argument_list|,
name|gimp_context_get_user
argument_list|()
argument_list|,
literal|32
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|test_dock_new (GimpViewType view_type)
name|test_dock_new
parameter_list|(
name|GimpViewType
name|view_type
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|dock
decl_stmt|;
name|GtkWidget
modifier|*
name|dockbook
decl_stmt|;
name|GtkWidget
modifier|*
name|dockable
decl_stmt|;
name|dock
operator|=
name|gimp_dialog_factory_dock_new
argument_list|(
name|global_dock_factory
argument_list|)
expr_stmt|;
name|dockbook
operator|=
name|gimp_dockbook_new
argument_list|()
expr_stmt|;
name|gimp_dock_add_book
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKBOOK
argument_list|(
name|dockbook
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dock_factory
argument_list|,
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|?
literal|"gimp:brush-list"
else|:
literal|"gimp:brush-grid"
argument_list|)
expr_stmt|;
name|gimp_dock_add
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dock_factory
argument_list|,
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|?
literal|"gimp:pattern-list"
else|:
literal|"gimp:pattern-grid"
argument_list|)
expr_stmt|;
name|gimp_dock_add
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dock_factory
argument_list|,
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|?
literal|"gimp:gradient-list"
else|:
literal|"gimp:gradient-grid"
argument_list|)
expr_stmt|;
name|gimp_dock_add
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dock_factory
argument_list|,
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|?
literal|"gimp:palette-list"
else|:
literal|"gimp:palette-grid"
argument_list|)
expr_stmt|;
name|gimp_dock_add
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|dockable
operator|=
name|gimp_dialog_factory_dialog_new
argument_list|(
name|global_dock_factory
argument_list|,
name|view_type
operator|==
name|GIMP_VIEW_TYPE_LIST
condition|?
literal|"gimp:tool-list"
else|:
literal|"gimp:tool-grid"
argument_list|)
expr_stmt|;
name|gimp_dock_add
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
argument_list|,
name|GIMP_DOCKABLE
argument_list|(
name|dockable
argument_list|)
argument_list|,
operator|-
literal|1
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dock
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_list_dock_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_list_dock_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|test_dock_new
argument_list|(
name|GIMP_VIEW_TYPE_LIST
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|test_grid_dock_cmd_callback (GtkWidget * widget,gpointer client_data)
name|test_grid_dock_cmd_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|client_data
parameter_list|)
block|{
name|test_dock_new
argument_list|(
name|GIMP_VIEW_TYPE_GRID
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

