begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcontainerview.h  * Copyright (C) 2001-2010 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CONTAINER_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CONTAINER_VIEW_H__
define|#
directive|define
name|__GIMP_CONTAINER_VIEW_H__
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon298c78cd0103
block|{
DECL|enumerator|GIMP_CONTAINER_VIEW_PROP_0
name|GIMP_CONTAINER_VIEW_PROP_0
block|,
DECL|enumerator|GIMP_CONTAINER_VIEW_PROP_CONTAINER
name|GIMP_CONTAINER_VIEW_PROP_CONTAINER
block|,
DECL|enumerator|GIMP_CONTAINER_VIEW_PROP_CONTEXT
name|GIMP_CONTAINER_VIEW_PROP_CONTEXT
block|,
DECL|enumerator|GIMP_CONTAINER_VIEW_PROP_SELECTION_MODE
name|GIMP_CONTAINER_VIEW_PROP_SELECTION_MODE
block|,
DECL|enumerator|GIMP_CONTAINER_VIEW_PROP_REORDERABLE
name|GIMP_CONTAINER_VIEW_PROP_REORDERABLE
block|,
DECL|enumerator|GIMP_CONTAINER_VIEW_PROP_VIEW_SIZE
name|GIMP_CONTAINER_VIEW_PROP_VIEW_SIZE
block|,
DECL|enumerator|GIMP_CONTAINER_VIEW_PROP_VIEW_BORDER_WIDTH
name|GIMP_CONTAINER_VIEW_PROP_VIEW_BORDER_WIDTH
block|,
DECL|enumerator|GIMP_CONTAINER_VIEW_PROP_LAST
name|GIMP_CONTAINER_VIEW_PROP_LAST
init|=
name|GIMP_CONTAINER_VIEW_PROP_VIEW_BORDER_WIDTH
DECL|typedef|GimpContainerViewProp
block|}
name|GimpContainerViewProp
typedef|;
end_typedef

begin_define
DECL|macro|GIMP_TYPE_CONTAINER_VIEW
define|#
directive|define
name|GIMP_TYPE_CONTAINER_VIEW
value|(gimp_container_view_interface_get_type ())
end_define

begin_define
DECL|macro|GIMP_CONTAINER_VIEW (obj)
define|#
directive|define
name|GIMP_CONTAINER_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CONTAINER_VIEW, GimpContainerView))
end_define

begin_define
DECL|macro|GIMP_IS_CONTAINER_VIEW (obj)
define|#
directive|define
name|GIMP_IS_CONTAINER_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CONTAINER_VIEW))
end_define

begin_define
DECL|macro|GIMP_CONTAINER_VIEW_GET_INTERFACE (obj)
define|#
directive|define
name|GIMP_CONTAINER_VIEW_GET_INTERFACE
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_INTERFACE ((obj), GIMP_TYPE_CONTAINER_VIEW, GimpContainerViewInterface))
end_define

begin_typedef
DECL|typedef|GimpContainerViewInterface
typedef|typedef
name|struct
name|_GimpContainerViewInterface
name|GimpContainerViewInterface
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpContainerViewInterface
struct|struct
name|_GimpContainerViewInterface
block|{
DECL|member|base_iface
name|GTypeInterface
name|base_iface
decl_stmt|;
comment|/*  signals  */
DECL|member|select_item
name|gboolean
function_decl|(
modifier|*
name|select_item
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|activate_item
name|void
function_decl|(
modifier|*
name|activate_item
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|context_item
name|void
function_decl|(
modifier|*
name|context_item
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
comment|/*  virtual functions  */
DECL|member|set_container
name|void
function_decl|(
modifier|*
name|set_container
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
DECL|member|set_context
name|void
function_decl|(
modifier|*
name|set_context
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
DECL|member|set_selection_mode
name|void
function_decl|(
modifier|*
name|set_selection_mode
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GtkSelectionMode
name|mode
parameter_list|)
function_decl|;
DECL|member|insert_item
name|gpointer
function_decl|(
modifier|*
name|insert_item
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|parent_insert_data
parameter_list|,
name|gint
name|index
parameter_list|)
function_decl|;
DECL|member|insert_item_after
name|void
function_decl|(
modifier|*
name|insert_item_after
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|remove_item
name|void
function_decl|(
modifier|*
name|remove_item
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|reorder_item
name|void
function_decl|(
modifier|*
name|reorder_item
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gint
name|new_index
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|rename_item
name|void
function_decl|(
modifier|*
name|rename_item
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|object
parameter_list|,
name|gpointer
name|insert_data
parameter_list|)
function_decl|;
DECL|member|clear_items
name|void
function_decl|(
modifier|*
name|clear_items
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
DECL|member|set_view_size
name|void
function_decl|(
modifier|*
name|set_view_size
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
DECL|member|get_selected
name|gint
function_decl|(
modifier|*
name|get_selected
function_decl|)
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GList
modifier|*
modifier|*
name|items
parameter_list|)
function_decl|;
comment|/*  the destroy notifier for private->hash_table's values  */
DECL|member|insert_data_free
name|GDestroyNotify
name|insert_data_free
decl_stmt|;
DECL|member|model_is_tree
name|gboolean
name|model_is_tree
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_container_view_interface_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpContainer
modifier|*
name|gimp_container_view_get_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_set_container
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_container_view_get_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_set_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkSelectionMode
name|gimp_container_view_get_selection_mode
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_set_selection_mode
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GtkSelectionMode
name|mode
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_container_view_get_view_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|gint
modifier|*
name|view_border_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_set_view_size
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gint
name|view_border_width
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_view_get_reorderable
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_set_reorderable
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|gboolean
name|reorderable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_container_view_get_dnd_widget
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_set_dnd_widget
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GtkWidget
modifier|*
name|dnd_widget
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_enable_dnd
parameter_list|(
name|GimpContainerView
modifier|*
name|editor
parameter_list|,
name|GtkButton
modifier|*
name|button
parameter_list|,
name|GType
name|children_type
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_view_select_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_activate_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_context_item
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_container_view_get_selected
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GList
modifier|*
modifier|*
name|list
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  protected  */
end_comment

begin_function_decl
name|gpointer
name|gimp_container_view_lookup
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_view_item_selected
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_container_view_multi_selected
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GList
modifier|*
name|items
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_item_activated
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_item_context
parameter_list|(
name|GimpContainerView
modifier|*
name|view
parameter_list|,
name|GimpViewable
modifier|*
name|item
parameter_list|)
function_decl|;
end_function_decl

begin_comment
comment|/*  convenience functions  */
end_comment

begin_function_decl
name|void
name|gimp_container_view_install_properties
parameter_list|(
name|GObjectClass
modifier|*
name|klass
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_container_view_set_property
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
name|void
name|gimp_container_view_get_property
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

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_CONTAINER_VIEW_H__  */
end_comment

end_unit

