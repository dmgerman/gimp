begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995-1997 Spencer Kimball and Peter Mattis  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_GUI_H__
end_ifndef

begin_define
DECL|macro|__GIMP_GUI_H__
define|#
directive|define
name|__GIMP_GUI_H__
end_define

begin_typedef
DECL|typedef|GimpGui
typedef|typedef
name|struct
name|_GimpGui
name|GimpGui
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpGui
struct|struct
name|_GimpGui
block|{
DECL|member|threads_enter
name|void
function_decl|(
modifier|*
name|threads_enter
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|threads_leave
name|void
function_decl|(
modifier|*
name|threads_leave
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|set_busy
name|void
function_decl|(
modifier|*
name|set_busy
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|unset_busy
name|void
function_decl|(
modifier|*
name|unset_busy
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|message
name|void
function_decl|(
modifier|*
name|message
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
DECL|member|help
name|void
function_decl|(
modifier|*
name|help
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
DECL|member|get_program_class
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_program_class
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|get_display_name
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_display_name
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|gdisp_ID
parameter_list|,
name|gint
modifier|*
name|monitor_number
parameter_list|)
function_decl|;
DECL|member|get_theme_dir
specifier|const
name|gchar
modifier|*
function_decl|(
modifier|*
name|get_theme_dir
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
DECL|member|display_get_by_id
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|display_get_by_id
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
function_decl|;
DECL|member|display_get_id
name|gint
function_decl|(
modifier|*
name|display_get_id
function_decl|)
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|display_create
name|GimpObject
modifier|*
function_decl|(
modifier|*
name|display_create
function_decl|)
parameter_list|(
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
DECL|member|display_delete
name|void
function_decl|(
modifier|*
name|display_delete
function_decl|)
parameter_list|(
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
DECL|member|displays_reconnect
name|void
function_decl|(
modifier|*
name|displays_reconnect
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|old_image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
DECL|member|menus_init
name|void
function_decl|(
modifier|*
name|menus_init
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GSList
modifier|*
name|plug_in_defs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|std_domain
parameter_list|)
function_decl|;
DECL|member|menus_create
name|void
function_decl|(
modifier|*
name|menus_create
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
function_decl|;
DECL|member|menus_delete
name|void
function_decl|(
modifier|*
name|menus_delete
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
DECL|member|progress_new
name|GimpProgress
modifier|*
function_decl|(
modifier|*
name|progress_new
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|)
function_decl|;
DECL|member|progress_free
name|void
function_decl|(
modifier|*
name|progress_free
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
DECL|member|pdb_dialog_new
name|gboolean
function_decl|(
modifier|*
name|pdb_dialog_new
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
DECL|member|pdb_dialog_set
name|gboolean
function_decl|(
modifier|*
name|pdb_dialog_set
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
DECL|member|pdb_dialog_close
name|gboolean
function_decl|(
modifier|*
name|pdb_dialog_close
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
function_decl|;
DECL|member|pdb_dialogs_check
name|void
function_decl|(
modifier|*
name|pdb_dialogs_check
function_decl|)
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_function_decl
name|void
name|gimp_gui_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_threads_enter
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_threads_leave
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_get_display_by_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gint
name|gimp_get_display_ID
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpObject
modifier|*
name|gimp_create_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|gimage
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|scale
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_delete_display
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpObject
modifier|*
name|display
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_reconnect_displays
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpImage
modifier|*
name|old_image
parameter_list|,
name|GimpImage
modifier|*
name|new_image
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_set_busy_until_idle
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_unset_busy
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_message
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_help
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_domain
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_menus_init
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GSList
modifier|*
name|plug_in_defs
parameter_list|,
specifier|const
name|gchar
modifier|*
name|std_plugins_domain
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_menus_create_entry
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|,
specifier|const
name|gchar
modifier|*
name|menu_path
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_menus_delete_entry
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|PlugInProcDef
modifier|*
name|proc_def
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpProgress
modifier|*
name|gimp_new_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|display_ID
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_free_progress
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpProgress
modifier|*
name|progress
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_program_class
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gchar
modifier|*
name|gimp_get_display_name
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|gint
name|gdisp_ID
parameter_list|,
name|gint
modifier|*
name|monitor_number
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
specifier|const
name|gchar
modifier|*
name|gimp_get_theme_dir
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_dialog_set
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|object_name
parameter_list|,
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_pdb_dialog_close
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
name|GimpContainer
modifier|*
name|container
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_pdb_dialogs_check
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_GUI_H__ */
end_comment

end_unit

