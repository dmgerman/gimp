begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagedock.c  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"widgets-types.h"
end_include

begin_include
include|#
directive|include
file|"gimpdialogfactory.h"
end_include

begin_include
include|#
directive|include
file|"gimpimagedock.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainermenuimpl.h"
end_include

begin_include
include|#
directive|include
file|"gimpdnd.h"
end_include

begin_include
include|#
directive|include
file|"gimpdockbook.h"
end_include

begin_include
include|#
directive|include
file|"gimpmenuitem.h"
end_include

begin_include
include|#
directive|include
file|"gimppreview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainer.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontext.h"
end_include

begin_include
include|#
directive|include
file|"gimpimage.h"
end_include

begin_include
include|#
directive|include
file|"libgimp/gimpintl.h"
end_include

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_class_init
parameter_list|(
name|GimpImageDockClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_init
parameter_list|(
name|GimpImageDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_factory_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_auto_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_decl_stmt
DECL|variable|parent_class
specifier|static
name|GimpDockClass
modifier|*
name|parent_class
init|=
name|NULL
decl_stmt|;
end_decl_stmt

begin_function
name|GtkType
DECL|function|gimp_image_dock_get_type (void)
name|gimp_image_dock_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GtkType
name|dock_type
init|=
literal|0
decl_stmt|;
if|if
condition|(
operator|!
name|dock_type
condition|)
block|{
specifier|static
specifier|const
name|GtkTypeInfo
name|dock_info
init|=
block|{
literal|"GimpImageDock"
block|,
sizeof|sizeof
argument_list|(
name|GimpImageDock
argument_list|)
block|,
sizeof|sizeof
argument_list|(
name|GimpImageDockClass
argument_list|)
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|gimp_image_dock_class_init
block|,
operator|(
name|GtkObjectInitFunc
operator|)
name|gimp_image_dock_init
block|,
comment|/* reserved_1 */
name|NULL
block|,
comment|/* reserved_2 */
name|NULL
block|,
operator|(
name|GtkClassInitFunc
operator|)
name|NULL
block|,       }
decl_stmt|;
name|dock_type
operator|=
name|gtk_type_unique
argument_list|(
name|GIMP_TYPE_DOCK
argument_list|,
operator|&
name|dock_info
argument_list|)
expr_stmt|;
block|}
return|return
name|dock_type
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_class_init (GimpImageDockClass * klass)
name|gimp_image_dock_class_init
parameter_list|(
name|GimpImageDockClass
modifier|*
name|klass
parameter_list|)
block|{
name|GtkObjectClass
modifier|*
name|object_class
decl_stmt|;
name|object_class
operator|=
operator|(
name|GtkObjectClass
operator|*
operator|)
name|klass
expr_stmt|;
name|parent_class
operator|=
name|gtk_type_class
argument_list|(
name|GIMP_TYPE_DOCK
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_image_dock_destroy
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_init (GimpImageDock * dock)
name|gimp_image_dock_init
parameter_list|(
name|GimpImageDock
modifier|*
name|dock
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
name|dock
operator|->
name|image_container
operator|=
name|NULL
expr_stmt|;
name|dock
operator|->
name|auto_follow_active
operator|=
name|TRUE
expr_stmt|;
name|hbox
operator|=
name|gtk_hbox_new
argument_list|(
name|FALSE
argument_list|,
literal|2
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
name|FALSE
argument_list|,
name|FALSE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_box_reorder_child
argument_list|(
name|GTK_BOX
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|hbox
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|dock
operator|->
name|option_menu
operator|=
name|gtk_option_menu_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|dock
operator|->
name|option_menu
argument_list|,
name|TRUE
argument_list|,
name|TRUE
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|dock
operator|->
name|option_menu
argument_list|)
expr_stmt|;
name|toggle
operator|=
name|gtk_toggle_button_new_with_label
argument_list|(
name|_
argument_list|(
literal|"Auto"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|toggle
argument_list|)
argument_list|,
name|dock
operator|->
name|auto_follow_active
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|toggle
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
name|toggle
argument_list|)
expr_stmt|;
name|gtk_signal_connect
argument_list|(
name|GTK_OBJECT
argument_list|(
name|toggle
argument_list|)
argument_list|,
literal|"clicked"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_image_dock_auto_clicked
argument_list|)
argument_list|,
name|dock
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_destroy (GtkObject * object)
name|gimp_image_dock_destroy
parameter_list|(
name|GtkObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpImageDock
modifier|*
name|dock
decl_stmt|;
name|dock
operator|=
name|GIMP_IMAGE_DOCK
argument_list|(
name|object
argument_list|)
expr_stmt|;
comment|/*  remove the image menu and the auto button manually here because    *  of weird cross-connections with GimpDock's context    */
name|gtk_container_remove
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|main_vbox
argument_list|)
argument_list|,
name|dock
operator|->
name|option_menu
operator|->
name|parent
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
condition|)
name|GTK_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|destroy
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|gchar
modifier|*
DECL|function|gimp_image_dock_image_name_func (GtkWidget * widget)
name|gimp_image_dock_image_name_func
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|)
block|{
name|GimpMenuItem
modifier|*
name|menu_item
decl_stmt|;
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gchar
modifier|*
name|name
decl_stmt|;
name|menu_item
operator|=
name|GIMP_MENU_ITEM
argument_list|(
name|widget
argument_list|)
expr_stmt|;
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|GIMP_PREVIEW
argument_list|(
name|menu_item
operator|->
name|preview
argument_list|)
operator|->
name|viewable
argument_list|)
expr_stmt|;
name|name
operator|=
name|g_strdup_printf
argument_list|(
literal|"%s-%d"
argument_list|,
name|g_basename
argument_list|(
name|gimp_image_filename
argument_list|(
name|gimage
argument_list|)
argument_list|)
argument_list|,
name|gimp_image_get_ID
argument_list|(
name|gimage
argument_list|)
argument_list|)
expr_stmt|;
return|return
name|name
return|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_image_dock_new (GimpDialogFactory * factory,GimpContainer * image_container)
name|gimp_image_dock_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpContainer
modifier|*
name|image_container
parameter_list|)
block|{
name|GimpImageDock
modifier|*
name|image_dock
decl_stmt|;
name|GimpDock
modifier|*
name|dock
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|factory
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|factory
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|image_container
operator|!=
name|NULL
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|image_container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_dock
operator|=
name|gtk_type_new
argument_list|(
name|GIMP_TYPE_IMAGE_DOCK
argument_list|)
expr_stmt|;
name|dock
operator|=
name|GIMP_DOCK
argument_list|(
name|image_dock
argument_list|)
expr_stmt|;
name|image_dock
operator|->
name|image_container
operator|=
name|image_container
expr_stmt|;
name|dock
operator|->
name|factory
operator|=
name|factory
expr_stmt|;
name|dock
operator|->
name|context
operator|=
name|gimp_context_new
argument_list|(
literal|"Dock Context"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_context_define_args
argument_list|(
name|dock
operator|->
name|context
argument_list|,
name|GIMP_CONTEXT_ALL_ARGS_MASK
operator|&
operator|~
operator|(
name|GIMP_CONTEXT_IMAGE_MASK
operator||
name|GIMP_CONTEXT_DISPLAY_MASK
operator|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
name|gimp_context_set_parent
argument_list|(
name|dock
operator|->
name|context
argument_list|,
name|factory
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_dock
operator|->
name|auto_follow_active
condition|)
name|gimp_context_copy_arg
argument_list|(
name|factory
operator|->
name|context
argument_list|,
name|dock
operator|->
name|context
argument_list|,
name|GIMP_CONTEXT_ARG_IMAGE
argument_list|)
expr_stmt|;
name|gtk_signal_connect_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|factory
operator|->
name|context
argument_list|)
argument_list|,
literal|"image_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_image_dock_factory_image_changed
argument_list|)
argument_list|,
name|dock
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_signal_connect_while_alive
argument_list|(
name|GTK_OBJECT
argument_list|(
name|dock
operator|->
name|context
argument_list|)
argument_list|,
literal|"image_changed"
argument_list|,
name|GTK_SIGNAL_FUNC
argument_list|(
name|gimp_image_dock_image_changed
argument_list|)
argument_list|,
name|dock
argument_list|,
name|GTK_OBJECT
argument_list|(
name|dock
argument_list|)
argument_list|)
expr_stmt|;
name|image_dock
operator|->
name|menu
operator|=
name|gimp_container_menu_new
argument_list|(
name|NULL
argument_list|,
name|dock
operator|->
name|context
argument_list|,
literal|24
argument_list|)
expr_stmt|;
name|gimp_container_menu_set_name_func
argument_list|(
name|GIMP_CONTAINER_MENU
argument_list|(
name|image_dock
operator|->
name|menu
argument_list|)
argument_list|,
name|gimp_image_dock_image_name_func
argument_list|)
expr_stmt|;
name|gimp_container_menu_set_container
argument_list|(
name|GIMP_CONTAINER_MENU
argument_list|(
name|image_dock
operator|->
name|menu
argument_list|)
argument_list|,
name|image_container
argument_list|)
expr_stmt|;
name|gtk_option_menu_set_menu
argument_list|(
name|GTK_OPTION_MENU
argument_list|(
name|image_dock
operator|->
name|option_menu
argument_list|)
argument_list|,
name|image_dock
operator|->
name|menu
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|image_dock
operator|->
name|menu
argument_list|)
expr_stmt|;
return|return
name|GTK_WIDGET
argument_list|(
name|image_dock
argument_list|)
return|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_factory_image_changed (GimpContext * context,GimpImage * gimage,GimpDock * dock)
name|gimp_image_dock_factory_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GimpImageDock
modifier|*
name|image_dock
decl_stmt|;
name|image_dock
operator|=
name|GIMP_IMAGE_DOCK
argument_list|(
name|dock
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
operator|&&
name|image_dock
operator|->
name|auto_follow_active
condition|)
block|{
name|gimp_context_set_image
argument_list|(
name|dock
operator|->
name|context
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_image_changed (GimpContext * context,GimpImage * gimage,GimpDock * dock)
name|gimp_image_dock_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GimpImageDock
modifier|*
name|image_dock
decl_stmt|;
name|image_dock
operator|=
name|GIMP_IMAGE_DOCK
argument_list|(
name|dock
argument_list|)
expr_stmt|;
if|if
condition|(
operator|!
name|gimage
operator|&&
name|image_dock
operator|->
name|image_container
operator|->
name|num_children
operator|>
literal|0
condition|)
block|{
name|gimage
operator|=
name|GIMP_IMAGE
argument_list|(
name|gimp_container_get_child_by_index
argument_list|(
name|image_dock
operator|->
name|image_container
argument_list|,
literal|0
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
block|{
comment|/*  this invokes this function recursively but we don't enter 	   *  the if() branch the second time 	   */
name|gimp_context_set_image
argument_list|(
name|dock
operator|->
name|context
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
comment|/*  stop the emission of the original signal (the emission of 	   *  the recursive signal is finished) 	   */
name|gtk_signal_emit_stop_by_name
argument_list|(
name|GTK_OBJECT
argument_list|(
name|context
argument_list|)
argument_list|,
literal|"image_changed"
argument_list|)
expr_stmt|;
block|}
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_auto_clicked (GtkWidget * widget,GimpDock * dock)
name|gimp_image_dock_auto_clicked
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
block|{
name|GimpImageDock
modifier|*
name|image_dock
decl_stmt|;
name|image_dock
operator|=
name|GIMP_IMAGE_DOCK
argument_list|(
name|dock
argument_list|)
expr_stmt|;
name|gimp_toggle_button_update
argument_list|(
name|widget
argument_list|,
operator|&
name|image_dock
operator|->
name|auto_follow_active
argument_list|)
expr_stmt|;
if|if
condition|(
name|image_dock
operator|->
name|auto_follow_active
condition|)
block|{
name|GimpImage
modifier|*
name|gimage
decl_stmt|;
name|gimage
operator|=
name|gimp_context_get_image
argument_list|(
name|dock
operator|->
name|factory
operator|->
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|gimage
condition|)
name|gimp_context_set_image
argument_list|(
name|dock
operator|->
name|context
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

