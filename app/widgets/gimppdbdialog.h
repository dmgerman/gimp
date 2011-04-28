begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimppdbdialog.h  * Copyright (C) 2004 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PDB_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PDB_DIALOG_H__
define|#
directive|define
name|__GIMP_PDB_DIALOG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_PDB_DIALOG
define|#
directive|define
name|GIMP_TYPE_PDB_DIALOG
value|(gimp_pdb_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_PDB_DIALOG (obj)
define|#
directive|define
name|GIMP_PDB_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PDB_DIALOG, GimpPdbDialog))
end_define

begin_define
DECL|macro|GIMP_PDB_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_PDB_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PDB_DIALOG, GimpPdbDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_PDB_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PDB_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_PDB_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PDB_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PDB_DIALOG))
end_define

begin_define
DECL|macro|GIMP_PDB_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PDB_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PDB_DIALOG, GimpPdbDialogClass))
end_define

begin_typedef
DECL|typedef|GimpPdbDialogClass
typedef|typedef
name|struct
name|_GimpPdbDialogClass
name|GimpPdbDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPdbDialog
struct|struct
name|_GimpPdbDialog
block|{
DECL|member|parent_instance
name|GimpDialog
name|parent_instance
decl_stmt|;
DECL|member|pdb
name|GimpPDB
modifier|*
name|pdb
decl_stmt|;
comment|/*  The context we were created with. This is the context the plug-in    *  exists in and must be used when calling the plug-in.    */
DECL|member|caller_context
name|GimpContext
modifier|*
name|caller_context
decl_stmt|;
comment|/*  The dialog's private context, serves just as model for the    *  select widgets and must not be used when calling the plug-in.    */
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|select_type
name|GType
name|select_type
decl_stmt|;
DECL|member|initial_object
name|GimpObject
modifier|*
name|initial_object
decl_stmt|;
DECL|member|callback_name
name|gchar
modifier|*
name|callback_name
decl_stmt|;
DECL|member|callback_busy
name|gboolean
name|callback_busy
decl_stmt|;
DECL|member|menu_factory
name|GimpMenuFactory
modifier|*
name|menu_factory
decl_stmt|;
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPdbDialogClass
struct|struct
name|_GimpPdbDialogClass
block|{
DECL|member|parent_class
name|GimpDialogClass
name|parent_class
decl_stmt|;
DECL|member|dialogs
name|GList
modifier|*
name|dialogs
decl_stmt|;
DECL|member|run_callback
name|GValueArray
modifier|*
function_decl|(
modifier|*
name|run_callback
function_decl|)
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|GimpObject
modifier|*
name|object
parameter_list|,
name|gboolean
name|closing
parameter_list|,
name|GError
modifier|*
modifier|*
name|error
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_pdb_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_pdb_dialog_run_callback
parameter_list|(
name|GimpPdbDialog
modifier|*
name|dialog
parameter_list|,
name|gboolean
name|closing
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GimpPdbDialog
modifier|*
name|gimp_pdb_dialog_get_by_callback
parameter_list|(
name|GimpPdbDialogClass
modifier|*
name|klass
parameter_list|,
specifier|const
name|gchar
modifier|*
name|callback_name
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
comment|/* __GIMP_PDB_DIALOG_H__ */
end_comment

end_unit

