begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpimagedock.c  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"core/gimp.h"
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
file|"core/gimplist.h"
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
file|"libgimp/gimpintl.h"
end_include

begin_define
DECL|macro|DEFAULT_MINIMAL_WIDTH
define|#
directive|define
name|DEFAULT_MINIMAL_WIDTH
value|250
end_define

begin_define
DECL|macro|DEFAULT_MENU_PREVIEW_SIZE
define|#
directive|define
name|DEFAULT_MENU_PREVIEW_SIZE
value|GTK_ICON_SIZE_SMALL_TOOLBAR
end_define

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
name|gimp_image_dock_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_image_dock_factory_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpObject
modifier|*
name|gdisp
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
name|GType
DECL|function|gimp_image_dock_get_type (void)
name|gimp_image_dock_get_type
parameter_list|(
name|void
parameter_list|)
block|{
specifier|static
name|GType
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
name|GTypeInfo
name|dock_info
init|=
block|{
sizeof|sizeof
argument_list|(
name|GimpImageDockClass
argument_list|)
block|,
name|NULL
block|,
comment|/* base_init */
name|NULL
block|,
comment|/* base_finalize */
operator|(
name|GClassInitFunc
operator|)
name|gimp_image_dock_class_init
block|,
name|NULL
block|,
comment|/* class_finalize */
name|NULL
block|,
comment|/* class_data */
sizeof|sizeof
argument_list|(
name|GimpImageDock
argument_list|)
block|,
literal|0
block|,
comment|/* n_preallocs */
operator|(
name|GInstanceInitFunc
operator|)
name|gimp_image_dock_init
block|,       }
decl_stmt|;
name|dock_type
operator|=
name|g_type_register_static
argument_list|(
name|GIMP_TYPE_DOCK
argument_list|,
literal|"GimpImageDock"
argument_list|,
operator|&
name|dock_info
argument_list|,
literal|0
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
name|GtkWidgetClass
modifier|*
name|widget_class
decl_stmt|;
name|object_class
operator|=
name|GTK_OBJECT_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|widget_class
operator|=
name|GTK_WIDGET_CLASS
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|parent_class
operator|=
name|g_type_class_peek_parent
argument_list|(
name|klass
argument_list|)
expr_stmt|;
name|object_class
operator|->
name|destroy
operator|=
name|gimp_image_dock_destroy
expr_stmt|;
name|widget_class
operator|->
name|style_set
operator|=
name|gimp_image_dock_style_set
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"minimal_width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|G_MAXINT
argument_list|,
name|DEFAULT_MINIMAL_WIDTH
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_class_install_style_property
argument_list|(
name|widget_class
argument_list|,
name|g_param_spec_enum
argument_list|(
literal|"menu_preview_size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GTK_TYPE_ICON_SIZE
argument_list|,
name|DEFAULT_MENU_PREVIEW_SIZE
argument_list|,
name|G_PARAM_READABLE
argument_list|)
argument_list|)
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
name|dock
operator|->
name|image_container
operator|=
name|NULL
expr_stmt|;
name|dock
operator|->
name|display_container
operator|=
name|NULL
expr_stmt|;
name|dock
operator|->
name|show_image_menu
operator|=
name|FALSE
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
if|if
condition|(
name|dock
operator|->
name|show_image_menu
condition|)
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
name|g_signal_connect
argument_list|(
name|dock
operator|->
name|option_menu
argument_list|,
literal|"destroy"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gtk_widget_destroyed
argument_list|)
argument_list|,
operator|&
name|dock
operator|->
name|option_menu
argument_list|)
expr_stmt|;
name|dock
operator|->
name|auto_button
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
name|dock
operator|->
name|auto_button
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
name|dock
operator|->
name|auto_button
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
name|dock
operator|->
name|auto_button
argument_list|)
expr_stmt|;
name|g_signal_connect
argument_list|(
name|dock
operator|->
name|auto_button
argument_list|,
literal|"clicked"
argument_list|,
name|G_CALLBACK
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
if|if
condition|(
name|GIMP_DOCK
argument_list|(
name|dock
argument_list|)
operator|->
name|main_vbox
operator|&&
name|dock
operator|->
name|option_menu
operator|&&
name|dock
operator|->
name|option_menu
operator|->
name|parent
condition|)
block|{
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
block|}
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
name|void
DECL|function|gimp_image_dock_style_set (GtkWidget * widget,GtkStyle * prev_style)
name|gimp_image_dock_style_set
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|GtkStyle
modifier|*
name|prev_style
parameter_list|)
block|{
name|GimpImageDock
modifier|*
name|image_dock
decl_stmt|;
name|gint
name|minimal_width
decl_stmt|;
name|GtkIconSize
name|menu_preview_size
decl_stmt|;
name|gint
name|menu_preview_width
init|=
literal|18
decl_stmt|;
name|gint
name|menu_preview_height
init|=
literal|18
decl_stmt|;
name|gint
name|focus_line_width
decl_stmt|;
name|gint
name|focus_padding
decl_stmt|;
name|gint
name|ythickness
decl_stmt|;
name|image_dock
operator|=
name|GIMP_IMAGE_DOCK
argument_list|(
name|widget
argument_list|)
expr_stmt|;
if|if
condition|(
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
condition|)
name|GTK_WIDGET_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|style_set
argument_list|(
name|widget
argument_list|,
name|prev_style
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|widget
argument_list|,
literal|"minimal_width"
argument_list|,
operator|&
name|minimal_width
argument_list|,
literal|"menu_preview_size"
argument_list|,
operator|&
name|menu_preview_size
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup
argument_list|(
name|menu_preview_size
argument_list|,
operator|&
name|menu_preview_width
argument_list|,
operator|&
name|menu_preview_height
argument_list|)
expr_stmt|;
name|gtk_widget_style_get
argument_list|(
name|image_dock
operator|->
name|auto_button
argument_list|,
literal|"focus_line_width"
argument_list|,
operator|&
name|focus_line_width
argument_list|,
literal|"focus_padding"
argument_list|,
operator|&
name|focus_padding
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|ythickness
operator|=
name|image_dock
operator|->
name|auto_button
operator|->
name|style
operator|->
name|ythickness
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|widget
argument_list|,
name|minimal_width
argument_list|,
operator|-
literal|1
argument_list|)
expr_stmt|;
name|gimp_container_menu_set_preview_size
argument_list|(
name|GIMP_CONTAINER_MENU
argument_list|(
name|image_dock
operator|->
name|menu
argument_list|)
argument_list|,
name|menu_preview_height
argument_list|)
expr_stmt|;
name|gtk_widget_set_size_request
argument_list|(
name|image_dock
operator|->
name|auto_button
argument_list|,
operator|-
literal|1
argument_list|,
name|menu_preview_height
operator|+
literal|2
operator|*
operator|(
literal|1
comment|/* CHILD_SPACING */
operator|+
name|ythickness
operator|+
name|focus_padding
operator|+
name|focus_line_width
operator|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_image_dock_new (GimpDialogFactory * dialog_factory,GimpContainer * image_container,GimpContainer * display_container)
name|gimp_image_dock_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
name|GimpContainer
modifier|*
name|image_container
parameter_list|,
name|GimpContainer
modifier|*
name|display_container
parameter_list|)
block|{
name|GimpImageDock
modifier|*
name|image_dock
decl_stmt|;
name|GimpContext
modifier|*
name|context
decl_stmt|;
name|gchar
modifier|*
name|title
decl_stmt|;
name|gint
name|menu_preview_width
decl_stmt|;
name|gint
name|menu_preview_height
decl_stmt|;
specifier|static
name|gint
name|dock_counter
init|=
literal|1
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_DIALOG_FACTORY
argument_list|(
name|dialog_factory
argument_list|)
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
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTAINER
argument_list|(
name|display_container
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|image_dock
operator|=
name|g_object_new
argument_list|(
name|GIMP_TYPE_IMAGE_DOCK
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|title
operator|=
name|g_strdup_printf
argument_list|(
name|_
argument_list|(
literal|"Gimp Dock #%d"
argument_list|)
argument_list|,
name|dock_counter
operator|++
argument_list|)
expr_stmt|;
name|gtk_window_set_title
argument_list|(
name|GTK_WINDOW
argument_list|(
name|image_dock
argument_list|)
argument_list|,
name|title
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|title
argument_list|)
expr_stmt|;
name|image_dock
operator|->
name|image_container
operator|=
name|image_container
expr_stmt|;
name|image_dock
operator|->
name|display_container
operator|=
name|display_container
expr_stmt|;
name|context
operator|=
name|gimp_context_new
argument_list|(
name|dialog_factory
operator|->
name|context
operator|->
name|gimp
argument_list|,
literal|"Dock Context"
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gimp_dock_construct
argument_list|(
name|GIMP_DOCK
argument_list|(
name|image_dock
argument_list|)
argument_list|,
name|dialog_factory
argument_list|,
name|context
argument_list|)
expr_stmt|;
name|gimp_context_define_properties
argument_list|(
name|context
argument_list|,
name|GIMP_CONTEXT_ALL_PROPS_MASK
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
name|context
argument_list|,
name|dialog_factory
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
block|{
if|if
condition|(
name|gimp_context_get_display
argument_list|(
name|dialog_factory
operator|->
name|context
argument_list|)
condition|)
name|gimp_context_copy_property
argument_list|(
name|dialog_factory
operator|->
name|context
argument_list|,
name|context
argument_list|,
name|GIMP_CONTEXT_PROP_DISPLAY
argument_list|)
expr_stmt|;
else|else
name|gimp_context_copy_property
argument_list|(
name|dialog_factory
operator|->
name|context
argument_list|,
name|context
argument_list|,
name|GIMP_CONTEXT_PROP_IMAGE
argument_list|)
expr_stmt|;
block|}
name|g_signal_connect_object
argument_list|(
name|dialog_factory
operator|->
name|context
argument_list|,
literal|"display_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_dock_factory_display_changed
argument_list|)
argument_list|,
name|image_dock
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|dialog_factory
operator|->
name|context
argument_list|,
literal|"image_changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_image_dock_factory_image_changed
argument_list|)
argument_list|,
name|image_dock
argument_list|,
literal|0
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
name|gimp_image_dock_image_changed
argument_list|)
argument_list|,
name|image_dock
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|gtk_icon_size_lookup
argument_list|(
name|DEFAULT_MENU_PREVIEW_SIZE
argument_list|,
operator|&
name|menu_preview_width
argument_list|,
operator|&
name|menu_preview_height
argument_list|)
expr_stmt|;
name|image_dock
operator|->
name|menu
operator|=
name|gimp_container_menu_new
argument_list|(
name|image_container
argument_list|,
name|context
argument_list|,
name|menu_preview_height
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
name|g_object_unref
argument_list|(
name|context
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
name|void
DECL|function|gimp_image_dock_set_auto_follow_active (GimpImageDock * image_dock,gboolean auto_follow_active)
name|gimp_image_dock_set_auto_follow_active
parameter_list|(
name|GimpImageDock
modifier|*
name|image_dock
parameter_list|,
name|gboolean
name|auto_follow_active
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_DOCK
argument_list|(
name|image_dock
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_toggle_button_set_active
argument_list|(
name|GTK_TOGGLE_BUTTON
argument_list|(
name|image_dock
operator|->
name|auto_button
argument_list|)
argument_list|,
name|auto_follow_active
condition|?
name|TRUE
else|:
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
name|void
DECL|function|gimp_image_dock_set_show_image_menu (GimpImageDock * image_dock,gboolean show)
name|gimp_image_dock_set_show_image_menu
parameter_list|(
name|GimpImageDock
modifier|*
name|image_dock
parameter_list|,
name|gboolean
name|show
parameter_list|)
block|{
name|g_return_if_fail
argument_list|(
name|GIMP_IS_IMAGE_DOCK
argument_list|(
name|image_dock
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|show
condition|)
name|gtk_widget_show
argument_list|(
name|image_dock
operator|->
name|option_menu
operator|->
name|parent
argument_list|)
expr_stmt|;
else|else
name|gtk_widget_hide
argument_list|(
name|image_dock
operator|->
name|option_menu
operator|->
name|parent
argument_list|)
expr_stmt|;
name|image_dock
operator|->
name|show_image_menu
operator|=
name|show
condition|?
name|TRUE
else|:
name|FALSE
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_image_dock_factory_display_changed (GimpContext * context,GimpObject * gdisp,GimpDock * dock)
name|gimp_image_dock_factory_display_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpObject
modifier|*
name|gdisp
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
name|gdisp
operator|&&
name|image_dock
operator|->
name|auto_follow_active
condition|)
block|{
name|gimp_context_set_display
argument_list|(
name|dock
operator|->
name|context
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
block|}
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
comment|/*  won't do anything if we already set the display above        */
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
name|context
argument_list|,
name|gimage
argument_list|)
expr_stmt|;
comment|/*  stop the emission of the original signal (the emission of 	   *  the recursive signal is finished) 	   */
name|g_signal_stop_emission_by_name
argument_list|(
name|context
argument_list|,
literal|"image_changed"
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|image_dock
operator|->
name|display_container
operator|->
name|num_children
operator|>
literal|0
condition|)
block|{
name|GimpObject
modifier|*
name|gdisp
decl_stmt|;
name|gboolean
name|find_display
init|=
name|TRUE
decl_stmt|;
name|gdisp
operator|=
name|gimp_context_get_display
argument_list|(
name|context
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp
condition|)
block|{
name|GimpImage
modifier|*
name|gdisp_gimage
decl_stmt|;
name|g_object_get
argument_list|(
name|gdisp
argument_list|,
literal|"image"
argument_list|,
operator|&
name|gdisp_gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gdisp_gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp_gimage
operator|==
name|gimage
condition|)
name|find_display
operator|=
name|FALSE
expr_stmt|;
block|}
if|if
condition|(
name|find_display
condition|)
block|{
name|GList
modifier|*
name|list
decl_stmt|;
for|for
control|(
name|list
operator|=
name|GIMP_LIST
argument_list|(
name|image_dock
operator|->
name|display_container
argument_list|)
operator|->
name|list
init|;
name|list
condition|;
name|list
operator|=
name|g_list_next
argument_list|(
name|list
argument_list|)
control|)
block|{
name|GimpImage
modifier|*
name|gdisp_gimage
decl_stmt|;
name|gdisp
operator|=
name|GIMP_OBJECT
argument_list|(
name|list
operator|->
name|data
argument_list|)
expr_stmt|;
name|g_object_get
argument_list|(
name|gdisp
argument_list|,
literal|"image"
argument_list|,
operator|&
name|gdisp_gimage
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_object_unref
argument_list|(
name|gdisp_gimage
argument_list|)
expr_stmt|;
if|if
condition|(
name|gdisp_gimage
operator|==
name|gimage
condition|)
block|{
comment|/*  this invokes this function recursively but we don't enter                    *  the if(find_display) branch the second time                    */
name|gimp_context_set_display
argument_list|(
name|context
argument_list|,
name|gdisp
argument_list|)
expr_stmt|;
comment|/*  don't stop signal emission here because the context's                    *  image was not changed by the recursive call                    */
break|break;
block|}
block|}
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
if|if
condition|(
name|gimp_context_get_display
argument_list|(
name|dock
operator|->
name|dialog_factory
operator|->
name|context
argument_list|)
condition|)
name|gimp_context_copy_property
argument_list|(
name|dock
operator|->
name|dialog_factory
operator|->
name|context
argument_list|,
name|dock
operator|->
name|context
argument_list|,
name|GIMP_CONTEXT_PROP_DISPLAY
argument_list|)
expr_stmt|;
else|else
name|gimp_context_copy_property
argument_list|(
name|dock
operator|->
name|dialog_factory
operator|->
name|context
argument_list|,
name|dock
operator|->
name|context
argument_list|,
name|GIMP_CONTEXT_PROP_IMAGE
argument_list|)
expr_stmt|;
block|}
block|}
end_function

end_unit

