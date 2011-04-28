begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpviewabledialog.h  * Copyright (C) 2000 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_VIEWABLE_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_VIEWABLE_DIALOG_H__
define|#
directive|define
name|__GIMP_VIEWABLE_DIALOG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_VIEWABLE_DIALOG
define|#
directive|define
name|GIMP_TYPE_VIEWABLE_DIALOG
value|(gimp_viewable_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_DIALOG (obj)
define|#
directive|define
name|GIMP_VIEWABLE_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_VIEWABLE_DIALOG, GimpViewableDialog))
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_VIEWABLE_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_VIEWABLE_DIALOG, GimpViewableDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_VIEWABLE_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_VIEWABLE_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_VIEWABLE_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_VIEWABLE_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_VIEWABLE_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_VIEWABLE_DIALOG))
end_define

begin_define
DECL|macro|GIMP_VIEWABLE_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_VIEWABLE_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_VIEWABLE_DIALOG, GimpViewableDialogClass))
end_define

begin_typedef
DECL|typedef|GimpViewableDialogClass
typedef|typedef
name|struct
name|_GimpViewableDialogClass
name|GimpViewableDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpViewableDialog
struct|struct
name|_GimpViewableDialog
block|{
DECL|member|parent_instance
name|GimpDialog
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|icon
name|GtkWidget
modifier|*
name|icon
decl_stmt|;
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
DECL|member|desc_label
name|GtkWidget
modifier|*
name|desc_label
decl_stmt|;
DECL|member|viewable_label
name|GtkWidget
modifier|*
name|viewable_label
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpViewableDialogClass
struct|struct
name|_GimpViewableDialogClass
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
name|gimp_viewable_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_viewable_dialog_new
argument_list|(
name|GimpViewable
operator|*
name|viewable
argument_list|,
name|GimpContext
operator|*
name|context
argument_list|,
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
specifier|const
name|gchar
operator|*
name|stock_id
argument_list|,
specifier|const
name|gchar
operator|*
name|desc
argument_list|,
name|GtkWidget
operator|*
name|parent
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
name|void
name|gimp_viewable_dialog_set_viewable
parameter_list|(
name|GimpViewableDialog
modifier|*
name|dialog
parameter_list|,
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
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
comment|/* __GIMP_VIEWABLE_DIALOG_H__ */
end_comment

end_unit

