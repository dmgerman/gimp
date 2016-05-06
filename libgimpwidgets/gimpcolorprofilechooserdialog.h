begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpColorProfileChooserDialog  * Copyright (C) 2006-2014 Sven Neumann<sven@gimp.org>  *                         Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_PROFILE_CHOOSER_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_PROFILE_CHOOSER_DIALOG_H__
define|#
directive|define
name|__GIMP_COLOR_PROFILE_CHOOSER_DIALOG_H__
end_define

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_define
DECL|macro|GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG
define|#
directive|define
name|GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG
value|(gimp_color_profile_chooser_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_PROFILE_CHOOSER_DIALOG (obj)
define|#
directive|define
name|GIMP_COLOR_PROFILE_CHOOSER_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG, GimpColorProfileChooserDialog))
end_define

begin_define
DECL|macro|GIMP_COLOR_PROFILE_CHOOSER_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_PROFILE_CHOOSER_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG, GimpColorProfileChooserDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PROFILE_CHOOSER_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_COLOR_PROFILE_CHOOSER_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_PROFILE_CHOOSER_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_PROFILE_CHOOSER_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG))
end_define

begin_define
DECL|macro|GIMP_COLOR_PROFILE_CHOOSER_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_PROFILE_CHOOSER_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_PROFILE_CHOOSER_DIALOG, GimpColorProfileChooserDialogClass))
end_define

begin_typedef
DECL|typedef|GimpColorProfileChooserDialogClass
typedef|typedef
name|struct
name|_GimpColorProfileChooserDialogClass
name|GimpColorProfileChooserDialogClass
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpColorProfileChooserDialogPrivate
typedef|typedef
name|struct
name|_GimpColorProfileChooserDialogPrivate
name|GimpColorProfileChooserDialogPrivate
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorProfileChooserDialog
struct|struct
name|_GimpColorProfileChooserDialog
block|{
DECL|member|parent_instance
name|GtkFileChooserDialog
name|parent_instance
decl_stmt|;
DECL|member|priv
name|GimpColorProfileChooserDialogPrivate
modifier|*
name|priv
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorProfileChooserDialogClass
struct|struct
name|_GimpColorProfileChooserDialogClass
block|{
DECL|member|parent_class
name|GtkFileChooserDialogClass
name|parent_class
decl_stmt|;
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
name|gimp_color_profile_chooser_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_profile_chooser_dialog_new
parameter_list|(
specifier|const
name|gchar
modifier|*
name|title
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
comment|/* __GIMP_COLOR_PROFILE_CHOOSER_DIALOG_H__ */
end_comment

end_unit

