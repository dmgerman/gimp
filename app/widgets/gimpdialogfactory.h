begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdialogfactory.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<https://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DIALOG_FACTORY_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DIALOG_FACTORY_H__
define|#
directive|define
name|__GIMP_DIALOG_FACTORY_H__
end_define

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

begin_define
DECL|macro|GIMP_DIALOG_VISIBILITY_KEY
define|#
directive|define
name|GIMP_DIALOG_VISIBILITY_KEY
value|"gimp-dialog-visibility"
end_define

begin_typedef
typedef|typedef
enum|enum
DECL|enum|__anon288469f30103
block|{
DECL|enumerator|GIMP_DIALOG_VISIBILITY_UNKNOWN
name|GIMP_DIALOG_VISIBILITY_UNKNOWN
init|=
literal|0
block|,
DECL|enumerator|GIMP_DIALOG_VISIBILITY_INVISIBLE
name|GIMP_DIALOG_VISIBILITY_INVISIBLE
block|,
DECL|enumerator|GIMP_DIALOG_VISIBILITY_VISIBLE
name|GIMP_DIALOG_VISIBILITY_VISIBLE
block|,
DECL|enumerator|GIMP_DIALOG_VISIBILITY_HIDDEN
name|GIMP_DIALOG_VISIBILITY_HIDDEN
DECL|typedef|GimpDialogVisibilityState
block|}
name|GimpDialogVisibilityState
typedef|;
end_typedef

begin_comment
comment|/* In order to support constructors of various types, these functions  * takes the union of the set of arguments required for each type of  * widget constructor. If this set becomes too big we can consider  * passing a struct or use varargs.  */
end_comment

begin_typedef
DECL|typedef|GimpDialogNewFunc
typedef|typedef
name|GtkWidget
modifier|*
function_decl|(
modifier|*
name|GimpDialogNewFunc
function_decl|)
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpUIManager
modifier|*
name|ui_manager
parameter_list|,
name|gint
name|view_size
parameter_list|)
function_decl|;
end_typedef

begin_struct
DECL|struct|_GimpDialogFactoryEntry
struct|struct
name|_GimpDialogFactoryEntry
block|{
DECL|member|identifier
name|gchar
modifier|*
name|identifier
decl_stmt|;
DECL|member|name
name|gchar
modifier|*
name|name
decl_stmt|;
DECL|member|blurb
name|gchar
modifier|*
name|blurb
decl_stmt|;
DECL|member|icon_name
name|gchar
modifier|*
name|icon_name
decl_stmt|;
DECL|member|help_id
name|gchar
modifier|*
name|help_id
decl_stmt|;
DECL|member|new_func
name|GimpDialogNewFunc
name|new_func
decl_stmt|;
DECL|member|restore_func
name|GimpDialogRestoreFunc
name|restore_func
decl_stmt|;
DECL|member|view_size
name|gint
name|view_size
decl_stmt|;
DECL|member|singleton
name|gboolean
name|singleton
decl_stmt|;
DECL|member|session_managed
name|gboolean
name|session_managed
decl_stmt|;
DECL|member|remember_size
name|gboolean
name|remember_size
decl_stmt|;
DECL|member|remember_if_open
name|gboolean
name|remember_if_open
decl_stmt|;
comment|/* If TRUE the visibility of the dialog is toggleable */
DECL|member|hideable
name|gboolean
name|hideable
decl_stmt|;
comment|/* If TRUE the entry is for a GimpImageWindow, FALSE otherwise */
DECL|member|image_window
name|gboolean
name|image_window
decl_stmt|;
comment|/* If TRUE the entry is for a dockable, FALSE otherwise */
DECL|member|dockable
name|gboolean
name|dockable
decl_stmt|;
block|}
struct|;
end_struct

begin_define
DECL|macro|GIMP_TYPE_DIALOG_FACTORY
define|#
directive|define
name|GIMP_TYPE_DIALOG_FACTORY
value|(gimp_dialog_factory_get_type ())
end_define

begin_define
DECL|macro|GIMP_DIALOG_FACTORY (obj)
define|#
directive|define
name|GIMP_DIALOG_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DIALOG_FACTORY, GimpDialogFactory))
end_define

begin_define
DECL|macro|GIMP_DIALOG_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_DIALOG_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DIALOG_FACTORY, GimpDialogFactoryClass))
end_define

begin_define
DECL|macro|GIMP_IS_DIALOG_FACTORY (obj)
define|#
directive|define
name|GIMP_IS_DIALOG_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DIALOG_FACTORY))
end_define

begin_define
DECL|macro|GIMP_IS_DIALOG_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DIALOG_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DIALOG_FACTORY))
end_define

begin_define
DECL|macro|GIMP_DIALOG_FACTORY_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DIALOG_FACTORY_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DIALOG_FACTORY, GimpDialogFactoryClass))
end_define

begin_typedef
DECL|typedef|GimpDialogFactoryPrivate
typedef|typedef
name|struct
name|_GimpDialogFactoryPrivate
name|GimpDialogFactoryPrivate
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpDialogFactoryClass
typedef|typedef
name|struct
name|_GimpDialogFactoryClass
name|GimpDialogFactoryClass
typedef|;
end_typedef

begin_comment
comment|/**  * GimpDialogFactory:  *  * A factory with the main purpose of creating toplevel windows and  * position them according to the session information kept within the  * factory. Over time it has accumulated more functionality than this.  */
end_comment

begin_struct
DECL|struct|_GimpDialogFactory
struct|struct
name|_GimpDialogFactory
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|p
name|GimpDialogFactoryPrivate
modifier|*
name|p
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDialogFactoryClass
struct|struct
name|_GimpDialogFactoryClass
block|{
DECL|member|parent_class
name|GimpObjectClass
name|parent_class
decl_stmt|;
DECL|member|dock_window_added
name|void
function_decl|(
modifier|*
name|dock_window_added
function_decl|)
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
DECL|member|dock_window_removed
name|void
function_decl|(
modifier|*
name|dock_window_removed
function_decl|)
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDockWindow
modifier|*
name|dock_window
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dialog_factory_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GimpDialogFactory
modifier|*
name|gimp_dialog_factory_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_register_entry
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
specifier|const
name|gchar
modifier|*
name|name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|blurb
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GimpDialogNewFunc
name|new_func
parameter_list|,
name|GimpDialogRestoreFunc
name|restore_func
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gboolean
name|singleton
parameter_list|,
name|gboolean
name|session_managed
parameter_list|,
name|gboolean
name|remember_size
parameter_list|,
name|gboolean
name|remember_if_open
parameter_list|,
name|gboolean
name|hideable
parameter_list|,
name|gboolean
name|image_window
parameter_list|,
name|gboolean
name|dockable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogFactoryEntry
modifier|*
name|gimp_dialog_factory_find_entry
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpSessionInfo
modifier|*
name|gimp_dialog_factory_find_session_info
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dialog_factory_find_widget
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifiers
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dialog_factory_dialog_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|,
name|GimpUIManager
modifier|*
name|ui_manager
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
name|view_size
parameter_list|,
name|gboolean
name|present
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpContext
modifier|*
name|gimp_dialog_factory_get_context
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpMenuFactory
modifier|*
name|gimp_dialog_factory_get_menu_factory
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_dialog_factory_get_open_dialogs
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GList
modifier|*
name|gimp_dialog_factory_get_session_infos
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_add_session_info
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpSessionInfo
modifier|*
name|info
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dialog_factory_dialog_raise
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifiers
parameter_list|,
name|gint
name|view_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dialog_factory_dockable_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|gint
name|view_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_add_dialog
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_add_foreign
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_position_dialog
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|identifier
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_remove_dialog
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_hide_dialog
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_save
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpConfigWriter
modifier|*
name|writer
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_restore
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GdkMonitor
modifier|*
name|monitor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_set_state
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDialogsState
name|state
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogsState
name|gimp_dialog_factory_get_state
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_show_with_display
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_hide_with_display
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_set_busy
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_unset_busy
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogFactory
modifier|*
name|gimp_dialog_factory_from_widget
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
name|GimpDialogFactoryEntry
modifier|*
modifier|*
name|entry
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_set_has_min_size
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|,
name|gboolean
name|has_min_size
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_dialog_factory_get_has_min_size
parameter_list|(
name|GtkWindow
modifier|*
name|window
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogFactory
modifier|*
name|gimp_dialog_factory_get_singleton
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_set_singleton
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_DIALOG_FACTORY_H__  */
end_comment

end_unit

