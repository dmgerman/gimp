begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ITEM_FACTORY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ITEM_FACTORY_H__
define|#
directive|define
name|__GIMP_ITEM_FACTORY_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_typedef
DECL|typedef|GimpItemFactory
typedef|typedef
name|struct
name|_GimpItemFactory
name|GimpItemFactory
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpItemFactorySetupFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpItemFactorySetupFunc
function_decl|)
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpItemFactoryUpdateFunc
typedef|typedef
name|void
function_decl|(
modifier|*
name|GimpItemFactoryUpdateFunc
function_decl|)
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|update_data
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpItemFactoryEntry
typedef|typedef
name|struct
name|_GimpItemFactoryEntry
name|GimpItemFactoryEntry
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItemFactoryEntry
struct|struct
name|_GimpItemFactoryEntry
block|{
DECL|member|entry
name|GtkItemFactoryEntry
name|entry
decl_stmt|;
DECL|member|quark_string
specifier|const
name|gchar
modifier|*
name|quark_string
decl_stmt|;
DECL|member|help_id
specifier|const
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|member|description
specifier|const
name|gchar
modifier|*
name|description
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_ITEM_FACTORY
define|#
directive|define
name|GIMP_TYPE_ITEM_FACTORY
value|(gimp_item_factory_get_type ())
end_define

begin_define
DECL|macro|GIMP_ITEM_FACTORY (obj)
define|#
directive|define
name|GIMP_ITEM_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ITEM_FACTORY, GimpItemFactory))
end_define

begin_define
DECL|macro|GIMP_ITEM_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_ITEM_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ITEM_FACTORY, GimpItemFactoryClass))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_FACTORY (obj)
define|#
directive|define
name|GIMP_IS_ITEM_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ITEM_FACTORY))
end_define

begin_define
DECL|macro|GIMP_IS_ITEM_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ITEM_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ITEM_FACTORY))
end_define

begin_define
DECL|macro|GIMP_ITEM_FACTORY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ITEM_FACTORY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ITEM_FACTORY, GimpItemFactoryClass))
end_define

begin_typedef
DECL|typedef|GimpItemFactoryClass
typedef|typedef
name|struct
name|_GimpItemFactoryClass
name|GimpItemFactoryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpItemFactory
struct|struct
name|_GimpItemFactory
block|{
DECL|member|parent_instance
name|GtkItemFactory
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|update_func
name|GimpItemFactoryUpdateFunc
name|update_func
decl_stmt|;
DECL|member|update_on_popup
name|gboolean
name|update_on_popup
decl_stmt|;
DECL|member|create_tearoff
name|gboolean
name|create_tearoff
decl_stmt|;
DECL|member|title
name|gchar
modifier|*
name|title
decl_stmt|;
DECL|member|help_id
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|member|translation_trash
name|GList
modifier|*
name|translation_trash
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpItemFactoryClass
struct|struct
name|_GimpItemFactoryClass
block|{
DECL|member|parent_class
name|GtkItemFactoryClass
name|parent_class
decl_stmt|;
DECL|member|factories
name|GHashTable
modifier|*
name|factories
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_item_factory_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpItemFactory
modifier|*
name|gimp_item_factory_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GType
name|container_type
parameter_list|,
specifier|const
name|gchar
modifier|*
name|factory_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpItemFactoryUpdateFunc
name|update_func
parameter_list|,
name|gboolean
name|update_on_popup
parameter_list|,
name|guint
name|n_entries
parameter_list|,
name|GimpItemFactoryEntry
modifier|*
name|entries
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|gboolean
name|create_tearoff
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpItemFactory
modifier|*
name|gimp_item_factory_from_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_item_factories_from_path
parameter_list|(
specifier|const
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_create_item
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|,
name|GimpItemFactoryEntry
modifier|*
name|entry
parameter_list|,
specifier|const
name|gchar
modifier|*
name|textdomain
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|guint
name|callback_type
parameter_list|,
name|gboolean
name|static_entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_create_items
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|,
name|guint
name|n_entries
parameter_list|,
name|GimpItemFactoryEntry
modifier|*
name|entries
parameter_list|,
name|gpointer
name|callback_data
parameter_list|,
name|guint
name|callback_type
parameter_list|,
name|gboolean
name|static_entries
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_update
parameter_list|(
name|GimpItemFactory
modifier|*
name|item_factory
parameter_list|,
name|gpointer
name|popup_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_popup_with_data
parameter_list|(
name|GimpItemFactory
modifier|*
name|factory
parameter_list|,
name|gpointer
name|popup_data
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpMenuPositionFunc
name|position_func
parameter_list|,
name|gpointer
name|position_data
parameter_list|,
name|GtkDestroyNotify
name|popdown_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_set_active
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factories_set_active
parameter_list|(
specifier|const
name|gchar
modifier|*
name|factory_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_set_color
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gboolean
name|set_label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factories_set_color
parameter_list|(
specifier|const
name|gchar
modifier|*
name|factory_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gboolean
name|set_label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_set_label
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factories_set_label
parameter_list|(
specifier|const
name|gchar
modifier|*
name|factory_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|label
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_set_sensitive
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factories_set_sensitive
parameter_list|(
specifier|const
name|gchar
modifier|*
name|factory_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|sensitive
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_set_visible
parameter_list|(
name|GtkItemFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factories_set_visible
parameter_list|(
specifier|const
name|gchar
modifier|*
name|factory_path
parameter_list|,
specifier|const
name|gchar
modifier|*
name|path
parameter_list|,
name|gboolean
name|visible
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_item_factory_tearoff_callback
parameter_list|(
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gpointer
name|data
parameter_list|,
name|guint
name|action
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ITEM_FACTORY_H__ */
end_comment

end_unit

