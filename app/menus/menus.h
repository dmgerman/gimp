begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__MENUS_H__
end_ifndef

begin_define
DECL|macro|__MENUS_H__
define|#
directive|define
name|__MENUS_H__
end_define

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
DECL|member|help_page
specifier|const
name|gchar
modifier|*
name|help_page
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

begin_decl_stmt
specifier|extern
name|GSList
modifier|*
name|last_opened_raw_filenames
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkItemFactory
modifier|*
name|menus_get_toolbox_factory
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkItemFactory
modifier|*
name|menus_get_image_factory
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkItemFactory
modifier|*
name|menus_get_load_factory
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkItemFactory
modifier|*
name|menus_get_save_factory
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkItemFactory
modifier|*
name|menus_get_layers_factory
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkItemFactory
modifier|*
name|menus_get_channels_factory
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkItemFactory
modifier|*
name|menus_get_paths_factory
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkItemFactory
modifier|*
name|menus_get_dialogs_factory
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_create_item_from_full_path
parameter_list|(
name|GimpItemFactoryEntry
modifier|*
name|entry
parameter_list|,
name|gchar
modifier|*
name|domain_name
parameter_list|,
name|gpointer
name|callback_data
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_reorder_plugins
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_quit
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_set_sensitive
parameter_list|(
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
name|menus_set_state
parameter_list|(
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
name|menus_destroy
parameter_list|(
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|menus_last_opened_add
parameter_list|(
name|gchar
modifier|*
name|filename
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __MENUS_H__ */
end_comment

end_unit

