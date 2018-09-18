begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppickablepopup.c  * Copyright (C) 2014 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_include
include|#
directive|include
file|"config.h"
end_include

begin_include
include|#
directive|include
file|<gegl.h>
end_include

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_include
include|#
directive|include
file|<gdk/gdkkeysyms.h>
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
file|"core/gimppickable.h"
end_include

begin_include
include|#
directive|include
file|"core/gimpviewable.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainertreeview.h"
end_include

begin_include
include|#
directive|include
file|"gimpcontainerview.h"
end_include

begin_include
include|#
directive|include
file|"gimppickablepopup.h"
end_include

begin_include
include|#
directive|include
file|"gimpviewrenderer.h"
end_include

begin_include
include|#
directive|include
file|"gimp-intl.h"
end_include

begin_enum
enum|enum
DECL|enum|__anon2b4263bb0103
block|{
DECL|enumerator|PROP_0
name|PROP_0
block|,
DECL|enumerator|PROP_CONTEXT
name|PROP_CONTEXT
block|,
DECL|enumerator|PROP_PICKABLE
name|PROP_PICKABLE
block|,
DECL|enumerator|PROP_VIEW_SIZE
name|PROP_VIEW_SIZE
block|,
DECL|enumerator|PROP_VIEW_BORDER_WIDTH
name|PROP_VIEW_BORDER_WIDTH
block|}
enum|;
end_enum

begin_struct
DECL|struct|_GimpPickablePopupPrivate
struct|struct
name|_GimpPickablePopupPrivate
block|{
DECL|member|pickable
name|GimpPickable
modifier|*
name|pickable
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|view_size
name|gint
name|view_size
decl_stmt|;
DECL|member|view_border_width
name|gint
name|view_border_width
decl_stmt|;
DECL|member|image_view
name|GtkWidget
modifier|*
name|image_view
decl_stmt|;
DECL|member|layer_view
name|GtkWidget
modifier|*
name|layer_view
decl_stmt|;
DECL|member|channel_view
name|GtkWidget
modifier|*
name|channel_view
decl_stmt|;
DECL|member|layer_label
name|GtkWidget
modifier|*
name|layer_label
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
specifier|static
name|void
name|gimp_pickable_popup_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pickable_popup_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pickable_popup_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pickable_popup_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pickable_popup_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPickablePopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|static
name|void
name|gimp_pickable_popup_item_activate
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gpointer
name|unused
parameter_list|,
name|GimpPickablePopup
modifier|*
name|popup
parameter_list|)
function_decl|;
end_function_decl

begin_macro
DECL|function|G_DEFINE_TYPE_WITH_PRIVATE (GimpPickablePopup,gimp_pickable_popup,GIMP_TYPE_POPUP)
name|G_DEFINE_TYPE_WITH_PRIVATE
argument_list|(
argument|GimpPickablePopup
argument_list|,
argument|gimp_pickable_popup
argument_list|,
argument|GIMP_TYPE_POPUP
argument_list|)
end_macro

begin_define
DECL|macro|parent_class
define|#
directive|define
name|parent_class
value|gimp_pickable_popup_parent_class
end_define

begin_function
specifier|static
name|void
name|gimp_pickable_popup_class_init
parameter_list|(
name|GimpPickablePopupClass
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
name|constructed
operator|=
name|gimp_pickable_popup_constructed
expr_stmt|;
name|object_class
operator|->
name|finalize
operator|=
name|gimp_pickable_popup_finalize
expr_stmt|;
name|object_class
operator|->
name|get_property
operator|=
name|gimp_pickable_popup_get_property
expr_stmt|;
name|object_class
operator|->
name|set_property
operator|=
name|gimp_pickable_popup_set_property
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_CONTEXT
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"context"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_CONTEXT
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT_ONLY
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_PICKABLE
argument_list|,
name|g_param_spec_object
argument_list|(
literal|"pickable"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
name|GIMP_TYPE_PICKABLE
argument_list|,
name|GIMP_PARAM_READABLE
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VIEW_SIZE
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"view-size"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|1
argument_list|,
name|GIMP_VIEWABLE_MAX_PREVIEW_SIZE
argument_list|,
name|GIMP_VIEW_SIZE_MEDIUM
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
name|g_object_class_install_property
argument_list|(
name|object_class
argument_list|,
name|PROP_VIEW_BORDER_WIDTH
argument_list|,
name|g_param_spec_int
argument_list|(
literal|"view-border-width"
argument_list|,
name|NULL
argument_list|,
name|NULL
argument_list|,
literal|0
argument_list|,
name|GIMP_VIEW_MAX_BORDER_WIDTH
argument_list|,
literal|1
argument_list|,
name|GIMP_PARAM_READWRITE
operator||
name|G_PARAM_CONSTRUCT
argument_list|)
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pickable_popup_init (GimpPickablePopup * popup)
name|gimp_pickable_popup_init
parameter_list|(
name|GimpPickablePopup
modifier|*
name|popup
parameter_list|)
block|{
name|popup
operator|->
name|priv
operator|=
name|gimp_pickable_popup_get_instance_private
argument_list|(
name|popup
argument_list|)
expr_stmt|;
name|popup
operator|->
name|priv
operator|->
name|view_size
operator|=
name|GIMP_VIEW_SIZE_SMALL
expr_stmt|;
name|popup
operator|->
name|priv
operator|->
name|view_border_width
operator|=
literal|1
expr_stmt|;
name|gtk_window_set_resizable
argument_list|(
name|GTK_WINDOW
argument_list|(
name|popup
argument_list|)
argument_list|,
name|FALSE
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pickable_popup_constructed (GObject * object)
name|gimp_pickable_popup_constructed
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPickablePopup
modifier|*
name|popup
init|=
name|GIMP_PICKABLE_POPUP
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
name|GtkWidget
modifier|*
name|hbox
decl_stmt|;
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
name|GtkWidget
modifier|*
name|label
decl_stmt|;
name|GtkWidget
modifier|*
name|notebook
decl_stmt|;
name|GimpImage
modifier|*
name|image
decl_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|constructed
argument_list|(
name|object
argument_list|)
expr_stmt|;
name|gimp_assert
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
name|frame
operator|=
name|gtk_frame_new
argument_list|(
name|NULL
argument_list|)
expr_stmt|;
name|gtk_frame_set_shadow_type
argument_list|(
name|GTK_FRAME
argument_list|(
name|frame
argument_list|)
argument_list|,
name|GTK_SHADOW_OUT
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|popup
argument_list|)
argument_list|,
name|frame
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|frame
argument_list|)
expr_stmt|;
name|hbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_HORIZONTAL
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_set_border_width
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|hbox
argument_list|)
argument_list|,
literal|6
argument_list|)
expr_stmt|;
name|gtk_container_add
argument_list|(
name|GTK_CONTAINER
argument_list|(
name|frame
argument_list|)
argument_list|,
name|hbox
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|hbox
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Images"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|popup
operator|->
name|priv
operator|->
name|image_view
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|context
operator|->
name|gimp
operator|->
name|images
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|view_size
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|view_border_width
argument_list|)
expr_stmt|;
name|gimp_container_box_set_size_request
argument_list|(
name|GIMP_CONTAINER_BOX
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|image_view
argument_list|)
argument_list|,
literal|4
operator|*
operator|(
name|popup
operator|->
name|priv
operator|->
name|view_size
operator|+
literal|2
operator|*
name|popup
operator|->
name|priv
operator|->
name|view_border_width
operator|)
argument_list|,
literal|4
operator|*
operator|(
name|popup
operator|->
name|priv
operator|->
name|view_size
operator|+
literal|2
operator|*
name|popup
operator|->
name|priv
operator|->
name|view_border_width
operator|)
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|image_view
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
name|popup
operator|->
name|priv
operator|->
name|image_view
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|image_view
argument_list|,
literal|"activate-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pickable_popup_item_activate
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|popup
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|vbox
operator|=
name|gtk_box_new
argument_list|(
name|GTK_ORIENTATION_VERTICAL
argument_list|,
literal|4
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|hbox
argument_list|)
argument_list|,
name|vbox
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
name|vbox
argument_list|)
expr_stmt|;
name|popup
operator|->
name|priv
operator|->
name|layer_label
operator|=
name|label
operator|=
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Select an image in the left pane"
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_label_set_xalign
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
literal|0.0
argument_list|)
expr_stmt|;
name|gtk_label_set_ellipsize
argument_list|(
name|GTK_LABEL
argument_list|(
name|label
argument_list|)
argument_list|,
name|PANGO_ELLIPSIZE_END
argument_list|)
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|label
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
name|label
argument_list|)
expr_stmt|;
name|notebook
operator|=
name|gtk_notebook_new
argument_list|()
expr_stmt|;
name|gtk_box_pack_start
argument_list|(
name|GTK_BOX
argument_list|(
name|vbox
argument_list|)
argument_list|,
name|notebook
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
name|notebook
argument_list|)
expr_stmt|;
name|popup
operator|->
name|priv
operator|->
name|layer_view
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|NULL
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|view_size
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|view_border_width
argument_list|)
expr_stmt|;
name|gtk_tree_view_set_show_expanders
argument_list|(
name|GTK_TREE_VIEW
argument_list|(
name|GIMP_CONTAINER_TREE_VIEW
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|layer_view
argument_list|)
operator|->
name|view
argument_list|)
argument_list|,
name|TRUE
argument_list|)
expr_stmt|;
name|gimp_container_box_set_size_request
argument_list|(
name|GIMP_CONTAINER_BOX
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|layer_view
argument_list|)
argument_list|,
literal|4
operator|*
operator|(
name|popup
operator|->
name|priv
operator|->
name|view_size
operator|+
literal|2
operator|*
name|popup
operator|->
name|priv
operator|->
name|view_border_width
operator|)
argument_list|,
literal|4
operator|*
operator|(
name|popup
operator|->
name|priv
operator|->
name|view_size
operator|+
literal|2
operator|*
name|popup
operator|->
name|priv
operator|->
name|view_border_width
operator|)
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|layer_view
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Layers"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|layer_view
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|layer_view
argument_list|,
literal|"activate-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pickable_popup_item_activate
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|popup
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|popup
operator|->
name|priv
operator|->
name|channel_view
operator|=
name|gimp_container_tree_view_new
argument_list|(
name|NULL
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|view_size
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|view_border_width
argument_list|)
expr_stmt|;
name|gimp_container_box_set_size_request
argument_list|(
name|GIMP_CONTAINER_BOX
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|channel_view
argument_list|)
argument_list|,
literal|4
operator|*
operator|(
name|popup
operator|->
name|priv
operator|->
name|view_size
operator|+
literal|2
operator|*
name|popup
operator|->
name|priv
operator|->
name|view_border_width
operator|)
argument_list|,
literal|4
operator|*
operator|(
name|popup
operator|->
name|priv
operator|->
name|view_size
operator|+
literal|2
operator|*
name|popup
operator|->
name|priv
operator|->
name|view_border_width
operator|)
argument_list|)
expr_stmt|;
name|gtk_notebook_append_page
argument_list|(
name|GTK_NOTEBOOK
argument_list|(
name|notebook
argument_list|)
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|channel_view
argument_list|,
name|gtk_label_new
argument_list|(
name|_
argument_list|(
literal|"Channels"
argument_list|)
argument_list|)
argument_list|)
expr_stmt|;
name|gtk_widget_show
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|channel_view
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|channel_view
argument_list|,
literal|"activate-item"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pickable_popup_item_activate
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|popup
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|g_signal_connect_object
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|,
literal|"image-changed"
argument_list|,
name|G_CALLBACK
argument_list|(
name|gimp_pickable_popup_image_changed
argument_list|)
argument_list|,
name|G_OBJECT
argument_list|(
name|popup
argument_list|)
argument_list|,
literal|0
argument_list|)
expr_stmt|;
name|image
operator|=
name|gimp_context_get_image
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
name|gimp_pickable_popup_image_changed
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|,
name|image
argument_list|,
name|popup
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pickable_popup_finalize (GObject * object)
name|gimp_pickable_popup_finalize
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|)
block|{
name|GimpPickablePopup
modifier|*
name|popup
init|=
name|GIMP_PICKABLE_POPUP
argument_list|(
name|object
argument_list|)
decl_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|popup
operator|->
name|priv
operator|->
name|pickable
argument_list|)
expr_stmt|;
name|g_clear_object
argument_list|(
operator|&
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
name|G_OBJECT_CLASS
argument_list|(
name|parent_class
argument_list|)
operator|->
name|finalize
argument_list|(
name|object
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pickable_popup_set_property (GObject * object,guint property_id,const GValue * value,GParamSpec * pspec)
name|gimp_pickable_popup_set_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
specifier|const
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpPickablePopup
modifier|*
name|popup
init|=
name|GIMP_PICKABLE_POPUP
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
if|if
condition|(
name|popup
operator|->
name|priv
operator|->
name|context
condition|)
name|g_object_unref
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
name|popup
operator|->
name|priv
operator|->
name|context
operator|=
name|g_value_dup_object
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEW_SIZE
case|:
name|popup
operator|->
name|priv
operator|->
name|view_size
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEW_BORDER_WIDTH
case|:
name|popup
operator|->
name|priv
operator|->
name|view_border_width
operator|=
name|g_value_get_int
argument_list|(
name|value
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PICKABLE
case|:
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pickable_popup_get_property (GObject * object,guint property_id,GValue * value,GParamSpec * pspec)
name|gimp_pickable_popup_get_property
parameter_list|(
name|GObject
modifier|*
name|object
parameter_list|,
name|guint
name|property_id
parameter_list|,
name|GValue
modifier|*
name|value
parameter_list|,
name|GParamSpec
modifier|*
name|pspec
parameter_list|)
block|{
name|GimpPickablePopup
modifier|*
name|popup
init|=
name|GIMP_PICKABLE_POPUP
argument_list|(
name|object
argument_list|)
decl_stmt|;
switch|switch
condition|(
name|property_id
condition|)
block|{
case|case
name|PROP_CONTEXT
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_PICKABLE
case|:
name|g_value_set_object
argument_list|(
name|value
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|pickable
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEW_SIZE
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|view_size
argument_list|)
expr_stmt|;
break|break;
case|case
name|PROP_VIEW_BORDER_WIDTH
case|:
name|g_value_set_int
argument_list|(
name|value
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|view_border_width
argument_list|)
expr_stmt|;
break|break;
default|default:
name|G_OBJECT_WARN_INVALID_PROPERTY_ID
argument_list|(
name|object
argument_list|,
name|property_id
argument_list|,
name|pspec
argument_list|)
expr_stmt|;
break|break;
block|}
block|}
end_function

begin_function
name|GtkWidget
modifier|*
DECL|function|gimp_pickable_popup_new (GimpContext * context,gint view_size,gint view_border_width)
name|gimp_pickable_popup_new
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|)
block|{
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_CONTEXT
argument_list|(
name|context
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|view_size
operator|>
literal|0
operator|&&
name|view_size
operator|<=
name|GIMP_VIEWABLE_MAX_POPUP_SIZE
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|g_return_val_if_fail
argument_list|(
name|view_border_width
operator|>=
literal|0
operator|&&
name|view_border_width
operator|<=
name|GIMP_VIEW_MAX_BORDER_WIDTH
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
return|return
name|g_object_new
argument_list|(
name|GIMP_TYPE_PICKABLE_POPUP
argument_list|,
literal|"type"
argument_list|,
name|GTK_WINDOW_POPUP
argument_list|,
literal|"context"
argument_list|,
name|context
argument_list|,
literal|"view-size"
argument_list|,
name|view_size
argument_list|,
literal|"view-border-width"
argument_list|,
name|view_border_width
argument_list|,
name|NULL
argument_list|)
return|;
block|}
end_function

begin_function
name|GimpPickable
modifier|*
DECL|function|gimp_pickable_popup_get_pickable (GimpPickablePopup * popup)
name|gimp_pickable_popup_get_pickable
parameter_list|(
name|GimpPickablePopup
modifier|*
name|popup
parameter_list|)
block|{
name|GtkWidget
modifier|*
name|focus
decl_stmt|;
name|GimpPickable
modifier|*
name|pickable
init|=
name|NULL
decl_stmt|;
name|g_return_val_if_fail
argument_list|(
name|GIMP_IS_PICKABLE_POPUP
argument_list|(
name|popup
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|focus
operator|=
name|gtk_window_get_focus
argument_list|(
name|GTK_WINDOW
argument_list|(
name|popup
argument_list|)
argument_list|)
expr_stmt|;
if|if
condition|(
name|focus
operator|&&
name|gtk_widget_is_ancestor
argument_list|(
name|focus
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|image_view
argument_list|)
condition|)
block|{
name|pickable
operator|=
name|GIMP_PICKABLE
argument_list|(
name|gimp_context_get_image
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|context
argument_list|)
argument_list|)
expr_stmt|;
block|}
elseif|else
if|if
condition|(
name|focus
operator|&&
name|gtk_widget_is_ancestor
argument_list|(
name|focus
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|layer_view
argument_list|)
condition|)
block|{
name|GList
modifier|*
name|selected
decl_stmt|;
if|if
condition|(
name|gimp_container_view_get_selected
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|layer_view
argument_list|)
argument_list|,
operator|&
name|selected
argument_list|)
condition|)
block|{
name|pickable
operator|=
name|selected
operator|->
name|data
expr_stmt|;
name|g_list_free
argument_list|(
name|selected
argument_list|)
expr_stmt|;
block|}
block|}
elseif|else
if|if
condition|(
name|focus
operator|&&
name|gtk_widget_is_ancestor
argument_list|(
name|focus
argument_list|,
name|popup
operator|->
name|priv
operator|->
name|channel_view
argument_list|)
condition|)
block|{
name|GList
modifier|*
name|selected
decl_stmt|;
if|if
condition|(
name|gimp_container_view_get_selected
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|channel_view
argument_list|)
argument_list|,
operator|&
name|selected
argument_list|)
condition|)
block|{
name|pickable
operator|=
name|selected
operator|->
name|data
expr_stmt|;
name|g_list_free
argument_list|(
name|selected
argument_list|)
expr_stmt|;
block|}
block|}
return|return
name|pickable
return|;
block|}
end_function

begin_comment
comment|/*  private functions  */
end_comment

begin_function
specifier|static
name|void
DECL|function|gimp_pickable_popup_image_changed (GimpContext * context,GimpImage * image,GimpPickablePopup * popup)
name|gimp_pickable_popup_image_changed
parameter_list|(
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpPickablePopup
modifier|*
name|popup
parameter_list|)
block|{
name|GimpContainer
modifier|*
name|layers
init|=
name|NULL
decl_stmt|;
name|GimpContainer
modifier|*
name|channels
init|=
name|NULL
decl_stmt|;
if|if
condition|(
name|image
condition|)
block|{
name|gchar
modifier|*
name|desc
decl_stmt|;
name|layers
operator|=
name|gimp_image_get_layers
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|channels
operator|=
name|gimp_image_get_channels
argument_list|(
name|image
argument_list|)
expr_stmt|;
name|desc
operator|=
name|gimp_viewable_get_description
argument_list|(
name|GIMP_VIEWABLE
argument_list|(
name|image
argument_list|)
argument_list|,
name|NULL
argument_list|)
expr_stmt|;
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|layer_label
argument_list|)
argument_list|,
name|desc
argument_list|)
expr_stmt|;
name|g_free
argument_list|(
name|desc
argument_list|)
expr_stmt|;
block|}
else|else
block|{
name|gtk_label_set_text
argument_list|(
name|GTK_LABEL
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|layer_label
argument_list|)
argument_list|,
name|_
argument_list|(
literal|"Select an image in the left pane"
argument_list|)
argument_list|)
expr_stmt|;
block|}
name|gimp_container_view_set_container
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|layer_view
argument_list|)
argument_list|,
name|layers
argument_list|)
expr_stmt|;
name|gimp_container_view_set_container
argument_list|(
name|GIMP_CONTAINER_VIEW
argument_list|(
name|popup
operator|->
name|priv
operator|->
name|channel_view
argument_list|)
argument_list|,
name|channels
argument_list|)
expr_stmt|;
block|}
end_function

begin_function
specifier|static
name|void
DECL|function|gimp_pickable_popup_item_activate (GimpContainerView * view,GimpPickable * pickable,gpointer unused,GimpPickablePopup * popup)
name|gimp_pickable_popup_item_activate
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpPickable
modifier|*
name|pickable
parameter_list|,
name|gpointer
name|unused
parameter_list|,
name|GimpPickablePopup
modifier|*
name|popup
parameter_list|)
block|{
name|g_signal_emit_by_name
argument_list|(
name|popup
argument_list|,
literal|"confirm"
argument_list|)
expr_stmt|;
block|}
end_function

end_unit

