begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpProfileChooserDialog  * Copyright (C) 2006 Sven Neumann<sven@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PROFILE_CHOOSER_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PROFILE_CHOOSER_DIALOG_H__
define|#
directive|define
name|__GIMP_PROFILE_CHOOSER_DIALOG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_PROFILE_CHOOSER_DIALOG
define|#
directive|define
name|GIMP_TYPE_PROFILE_CHOOSER_DIALOG
value|(gimp_profile_chooser_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_PROFILE_CHOOSER_DIALOG (obj)
define|#
directive|define
name|GIMP_PROFILE_CHOOSER_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PROFILE_CHOOSER_DIALOG, GimpProfileChooserDialog))
end_define

begin_define
DECL|macro|GIMP_PROFILE_CHOOSER_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_PROFILE_CHOOSER_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PROFILE_CHOOSER_DIALOG, GimpProfileChooserDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_PROFILE_CHOOSER_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_PROFILE_CHOOSER_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PROFILE_CHOOSER_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_PROFILE_CHOOSER_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PROFILE_CHOOSER_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PROFILE_CHOOSER_DIALOG))
end_define

begin_define
DECL|macro|GIMP_PROFILE_CHOOSER_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PROFILE_CHOOSER_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PROFILE_CHOOSER_DIALOG, GimpProfileChooserDialogClass))
end_define

begin_typedef
DECL|typedef|GimpProfileChooserDialogClass
typedef|typedef
name|struct
name|_GimpProfileChooserDialogClass
name|GimpProfileChooserDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpProfileChooserDialog
struct|struct
name|_GimpProfileChooserDialog
block|{
DECL|member|parent_instance
name|GtkFileChooserDialog
name|parent_instance
decl_stmt|;
DECL|member|gimp
name|Gimp
modifier|*
name|gimp
decl_stmt|;
DECL|member|preview
name|GtkWidget
modifier|*
name|preview
decl_stmt|;
DECL|member|info_label
name|GtkWidget
modifier|*
name|info_label
decl_stmt|;
DECL|member|idle_id
name|guint
name|idle_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpProfileChooserDialogClass
struct|struct
name|_GimpProfileChooserDialogClass
block|{
DECL|member|parent_class
name|GtkFileChooserDialogClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_profile_chooser_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_profile_chooser_dialog_new
parameter_list|(
name|Gimp
modifier|*
name|gimp
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PROFILE_CHOOSER_DIALOG_H__ */
end_comment

end_unit

