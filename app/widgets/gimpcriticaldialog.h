begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcriticaldialog.h  * Copyright (C) 2018  Jehan<jehan@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CRITICAL_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CRITICAL_DIALOG_H__
define|#
directive|define
name|__GIMP_CRITICAL_DIALOG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_CRITICAL_DIALOG
define|#
directive|define
name|GIMP_TYPE_CRITICAL_DIALOG
value|(gimp_critical_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_CRITICAL_DIALOG (obj)
define|#
directive|define
name|GIMP_CRITICAL_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CRITICAL_DIALOG, GimpCriticalDialog))
end_define

begin_define
DECL|macro|GIMP_CRITICAL_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_CRITICAL_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CRITICAL_DIALOG, GimpCriticalDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_CRITICAL_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_CRITICAL_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CRITICAL_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_CRITICAL_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CRITICAL_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CRITICAL_DIALOG))
end_define

begin_define
DECL|macro|GIMP_CRITICAL_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CRITICAL_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CRITICAL_DIALOG, GimpCriticalDialogClass))
end_define

begin_typedef
DECL|typedef|GimpCriticalDialogClass
typedef|typedef
name|struct
name|_GimpCriticalDialogClass
name|GimpCriticalDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCriticalDialog
struct|struct
name|_GimpCriticalDialog
block|{
DECL|member|parent_instance
name|GtkDialog
name|parent_instance
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|top_label
name|GtkWidget
modifier|*
name|top_label
decl_stmt|;
DECL|member|bottom_label
name|GtkWidget
modifier|*
name|bottom_label
decl_stmt|;
DECL|member|details
name|GtkWidget
modifier|*
name|details
decl_stmt|;
DECL|member|program
name|gchar
modifier|*
name|program
decl_stmt|;
DECL|member|pid
name|gint
name|pid
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCriticalDialogClass
struct|struct
name|_GimpCriticalDialogClass
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
name|gimp_critical_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_critical_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_critical_dialog_add
parameter_list|(
name|GtkWidget
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|message
parameter_list|,
specifier|const
name|gchar
modifier|*
name|trace
parameter_list|,
name|gboolean
name|is_fatal
parameter_list|,
specifier|const
name|gchar
modifier|*
name|program
parameter_list|,
name|gint
name|pid
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
comment|/* __GIMP_CRITICAL_DIALOG_H__ */
end_comment

end_unit

