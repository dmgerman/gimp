begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdialogfactory.h  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|<stdio.h>
end_include

begin_include
include|#
directive|include
file|"core/gimpobject.h"
end_include

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
parameter_list|)
function_decl|;
end_typedef

begin_typedef
DECL|typedef|GimpDialogFactoryEntry
typedef|typedef
name|struct
name|_GimpDialogFactoryEntry
name|GimpDialogFactoryEntry
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpSessionInfo
typedef|typedef
name|struct
name|_GimpSessionInfo
name|GimpSessionInfo
typedef|;
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
DECL|member|new_func
name|GimpDialogNewFunc
name|new_func
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
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpSessionInfo
struct|struct
name|_GimpSessionInfo
block|{
DECL|member|x
name|gint
name|x
decl_stmt|;
DECL|member|y
name|gint
name|y
decl_stmt|;
DECL|member|width
name|gint
name|width
decl_stmt|;
DECL|member|height
name|gint
name|height
decl_stmt|;
DECL|member|widget
name|GtkWidget
modifier|*
name|widget
decl_stmt|;
comment|/*  only valid while restoring and saving the session  */
DECL|member|open
name|gboolean
name|open
decl_stmt|;
comment|/*  GList of gchar* of optional additional dialog specific info  */
DECL|member|aux_info
name|GList
modifier|*
name|aux_info
decl_stmt|;
comment|/*  only one of these is valid  */
DECL|member|toplevel_entry
name|GimpDialogFactoryEntry
modifier|*
name|toplevel_entry
decl_stmt|;
DECL|member|dockable_entry
name|GimpDialogFactoryEntry
modifier|*
name|dockable_entry
decl_stmt|;
DECL|member|sub_dialogs
name|GList
modifier|*
name|sub_dialogs
decl_stmt|;
comment|/*  GList of GLists of entries  */
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
DECL|typedef|GimpDialogFactoryClass
typedef|typedef
name|struct
name|_GimpDialogFactoryClass
name|GimpDialogFactoryClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDialogFactory
struct|struct
name|_GimpDialogFactory
block|{
DECL|member|parent_instance
name|GimpObject
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|item_factory
name|GtkItemFactory
modifier|*
name|item_factory
decl_stmt|;
comment|/*< private>*/
DECL|member|new_dock_func
name|GimpDialogNewFunc
name|new_dock_func
decl_stmt|;
DECL|member|registered_dialogs
name|GList
modifier|*
name|registered_dialogs
decl_stmt|;
DECL|member|session_infos
name|GList
modifier|*
name|session_infos
decl_stmt|;
DECL|member|open_dialogs
name|GList
modifier|*
name|open_dialogs
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
DECL|member|factories
name|GHashTable
modifier|*
name|factories
decl_stmt|;
block|}
struct|;
end_struct

begin_function_decl
name|GType
name|gimp_dialog_factory_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

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
name|GtkItemFactory
modifier|*
name|item_factory
parameter_list|,
name|GimpDialogNewFunc
name|new_dock_func
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDialogFactory
modifier|*
name|gimp_dialog_factory_from_name
parameter_list|(
specifier|const
name|gchar
modifier|*
name|name
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
name|GimpDialogNewFunc
name|new_func
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
name|gimp_dialog_factory_dialog_new
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
name|gimp_dialog_factory_dialog_raise
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dialog_factory_dock_new
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
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
name|gimp_dialog_factories_session_save
parameter_list|(
name|FILE
modifier|*
name|file
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factories_session_restore
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factories_toggle
parameter_list|(
name|GimpDialogFactory
modifier|*
name|toolbox_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|toolbox_identifier
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factories_idle
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factories_unidle
parameter_list|(
name|void
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

