begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdialogfactory.h  * Copyright (C) 2001 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
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
file|"gimpobject.h"
end_include

begin_typedef
DECL|typedef|GimpDialogNewFunc
typedef|typedef
name|GimpDockable
modifier|*
function_decl|(
modifier|*
name|GimpDialogNewFunc
function_decl|)
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|)
function_decl|;
end_typedef

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
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_DIALOG_FACTORY, GimpDialogFactory))
end_define

begin_define
DECL|macro|GIMP_DIALOG_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_DIALOG_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DIALOG_FACTORY, GimpDialogFactoryClass))
end_define

begin_define
DECL|macro|GIMP_IS_DIALOG_FACTORY (obj)
define|#
directive|define
name|GIMP_IS_DIALOG_FACTORY
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE ((obj), GIMP_TYPE_DIALOG_FACTORY))
end_define

begin_define
DECL|macro|GIMP_IS_DIALOG_FACTORY_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DIALOG_FACTORY_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DIALOG_FACTORY))
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
DECL|member|registered_dialogs
name|GList
modifier|*
name|registered_dialogs
decl_stmt|;
DECL|member|open_docks
name|GList
modifier|*
name|open_docks
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
block|}
struct|;
end_struct

begin_function_decl
name|GtkType
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
name|GimpContext
modifier|*
name|context
parameter_list|,
name|GtkItemFactory
modifier|*
name|item_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_register
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
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpDockable
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
name|void
name|gimp_dialog_factory_add_dock
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDock
modifier|*
name|dock
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_factory_remove_dock
parameter_list|(
name|GimpDialogFactory
modifier|*
name|factory
parameter_list|,
name|GimpDock
modifier|*
name|dock
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

