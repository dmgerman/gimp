begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimperrordialog.c  * Copyright (C) 2004  Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_ERROR_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_ERROR_DIALOG_H__
define|#
directive|define
name|__GIMP_ERROR_DIALOG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_ERROR_DIALOG
define|#
directive|define
name|GIMP_TYPE_ERROR_DIALOG
value|(gimp_error_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_ERROR_DIALOG (obj)
define|#
directive|define
name|GIMP_ERROR_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_ERROR_DIALOG, GimpErrorDialog))
end_define

begin_define
DECL|macro|GIMP_ERROR_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_ERROR_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_ERROR_DIALOG, GimpErrorDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_ERROR_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_ERROR_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_ERROR_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_ERROR_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_ERROR_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_ERROR_DIALOG))
end_define

begin_define
DECL|macro|GIMP_ERROR_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_ERROR_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_ERROR_DIALOG, GimpErrorDialogClass))
end_define

begin_typedef
DECL|typedef|GimpErrorDialogClass
typedef|typedef
name|struct
name|_GimpErrorDialogClass
name|GimpErrorDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpErrorDialog
struct|struct
name|_GimpErrorDialog
block|{
DECL|member|parent_instance
name|GimpDialog
name|parent_instance
decl_stmt|;
DECL|member|vbox
name|GtkWidget
modifier|*
name|vbox
decl_stmt|;
DECL|member|last_box
name|GtkWidget
modifier|*
name|last_box
decl_stmt|;
DECL|member|last_domain
name|gchar
modifier|*
name|last_domain
decl_stmt|;
DECL|member|last_message
name|gchar
modifier|*
name|last_message
decl_stmt|;
DECL|member|num_messages
name|gint
name|num_messages
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpErrorDialogClass
struct|struct
name|_GimpErrorDialogClass
block|{
DECL|member|parent_class
name|GimpDialogClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_error_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_error_dialog_new
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
name|gimp_error_dialog_add
parameter_list|(
name|GimpErrorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
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

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_ERROR_DIALOG_H__ */
end_comment

end_unit

