begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdialog.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   * Library General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DIALOG_H__
define|#
directive|define
name|__GIMP_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdialog.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_DIALOG
define|#
directive|define
name|GIMP_TYPE_DIALOG
value|(gimp_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_DIALOG (obj)
define|#
directive|define
name|GIMP_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DIALOG, GimpDialog))
end_define

begin_define
DECL|macro|GIMP_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DIALOG, GimpDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DIALOG))
end_define

begin_define
DECL|macro|GIMP_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DIALOG, GimpDialogClass))
end_define

begin_typedef
DECL|typedef|GimpDialogClass
typedef|typedef
name|struct
name|_GimpDialogClass
name|GimpDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDialog
struct|struct
name|_GimpDialog
block|{
DECL|member|parent_instance
name|GtkDialog
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDialogClass
struct|struct
name|_GimpDialogClass
block|{
DECL|member|parent_class
name|GtkDialogClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|wmclass_name
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GtkWindowPosition
name|position
parameter_list|,
name|gint
name|allow_shrink
parameter_list|,
name|gint
name|allow_grow
parameter_list|,
name|gint
name|auto_shrink
parameter_list|,
comment|/* specify action area buttons 					      * as va_list: 					      *  const gchar    *label, 					      *  GCallback       callback, 					      *  gpointer        callback_data, 					      *  GObject        *slot_object, 					      *  GtkWidget     **widget_ptr, 					      *  gboolean        default_action, 					      *  gboolean        connect_delete, 					      */
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dialog_newv
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|wmclass_name
parameter_list|,
name|GimpHelpFunc
name|help_func
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GtkWindowPosition
name|position
parameter_list|,
name|gint
name|allow_shrink
parameter_list|,
name|gint
name|allow_grow
parameter_list|,
name|gint
name|auto_shrink
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_create_action_area
parameter_list|(
name|GimpDialog
modifier|*
name|dialog
parameter_list|,
comment|/* specify action area buttons 					      * as va_list: 					      *  const gchar    *label, 					      *  GCallback       callback, 					      *  gpointer        callback_data, 					      *  GObject        *slot_object, 					      *  GtkWidget     **widget_ptr, 					      *  gboolean        default_action, 					      *  gboolean        connect_delete, 					      */
modifier|...
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dialog_create_action_areav
parameter_list|(
name|GimpDialog
modifier|*
name|dialog
parameter_list|,
name|va_list
name|args
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
comment|/* __GIMP_DIALOG_H__ */
end_comment

end_unit

