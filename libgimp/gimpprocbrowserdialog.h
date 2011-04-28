begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimpprocbrowserdialog.c  *  * This library is free software: you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 3 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library.  If not, see  *<http://www.gnu.org/licenses/>.  */
end_comment

begin_if
if|#
directive|if
operator|!
name|defined
argument_list|(
name|__GIMP_UI_H_INSIDE__
argument_list|)
operator|&&
operator|!
name|defined
argument_list|(
name|GIMP_COMPILATION
argument_list|)
end_if

begin_error
error|#
directive|error
literal|"Only<libgimp/gimpui.h> can be included directly."
end_error

begin_endif
endif|#
directive|endif
end_endif

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROC_BROWSER_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROC_BROWSER_DIALOG_H__
define|#
directive|define
name|__GIMP_PROC_BROWSER_DIALOG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PROC_BROWSER_DIALOG
define|#
directive|define
name|GIMP_TYPE_PROC_BROWSER_DIALOG
value|(gimp_proc_browser_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_PROC_BROWSER_DIALOG (obj)
define|#
directive|define
name|GIMP_PROC_BROWSER_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROC_BROWSER_DIALOG, GimpProcBrowserDialog))
end_define

begin_define
DECL|macro|GIMP_PROC_BROWSER_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_PROC_BROWSER_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PROC_BROWSER_DIALOG, GimpProcBrowserDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_PROC_BROWSER_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_PROC_BROWSER_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROC_BROWSER_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_PROC_BROWSER_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PROC_BROWSER_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PROC_BROWSER_DIALOG))
end_define

begin_define
DECL|macro|GIMP_PROC_BROWSER_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PROC_BROWSER_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PROC_BROWSER_DIALOG, GimpProcBrowserDialogClass))
end_define

begin_typedef
DECL|typedef|GimpProcBrowserDialogClass
typedef|typedef
name|struct
name|_GimpProcBrowserDialogClass
name|GimpProcBrowserDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProcBrowserDialog
struct|struct
name|_GimpProcBrowserDialog
block|{
DECL|member|parent_instance
name|GimpDialog
name|parent_instance
decl_stmt|;
DECL|member|browser
name|GtkWidget
modifier|*
name|browser
decl_stmt|;
DECL|member|store
name|GtkListStore
modifier|*
name|store
decl_stmt|;
DECL|member|tree_view
name|GtkWidget
modifier|*
name|tree_view
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpProcBrowserDialogClass
struct|struct
name|_GimpProcBrowserDialogClass
block|{
DECL|member|parent_class
name|GimpDialogClass
name|parent_class
decl_stmt|;
DECL|member|selection_changed
name|void
function_decl|(
modifier|*
name|selection_changed
function_decl|)
parameter_list|(
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
DECL|member|row_activated
name|void
function_decl|(
modifier|*
name|row_activated
function_decl|)
parameter_list|(
name|GimpProcBrowserDialog
modifier|*
name|dialog
parameter_list|)
function_decl|;
comment|/* Padding for future expansion */
DECL|member|_gimp_reserved1
name|void
function_decl|(
modifier|*
name|_gimp_reserved1
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved2
name|void
function_decl|(
modifier|*
name|_gimp_reserved2
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved3
name|void
function_decl|(
modifier|*
name|_gimp_reserved3
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
DECL|member|_gimp_reserved4
name|void
function_decl|(
modifier|*
name|_gimp_reserved4
function_decl|)
parameter_list|(
name|void
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_proc_browser_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_proc_browser_dialog_new
argument_list|(
specifier|const
name|gchar
operator|*
name|title
argument_list|,
specifier|const
name|gchar
operator|*
name|role
argument_list|,
name|GimpHelpFunc
name|help_func
argument_list|,
specifier|const
name|gchar
operator|*
name|help_id
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_function_decl
name|gchar
modifier|*
name|gimp_proc_browser_dialog_get_selected
parameter_list|(
name|GimpProcBrowserDialog
modifier|*
name|dialog
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
comment|/* __GIMP_PROC_BROWSER_DIALOG_H__ */
end_comment

end_unit

