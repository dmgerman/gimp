begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimptooldialog.h  * Copyright (C) 2003  Sven Neumann<sven@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_TOOL_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_TOOL_DIALOG_H__
define|#
directive|define
name|__GIMP_TOOL_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|"widgets/gimpviewabledialog.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_TOOL_DIALOG
define|#
directive|define
name|GIMP_TYPE_TOOL_DIALOG
value|(gimp_tool_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_TOOL_DIALOG (obj)
define|#
directive|define
name|GIMP_TOOL_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_DIALOG, GimpToolDialog))
end_define

begin_define
DECL|macro|GIMP_TOOL_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_TOOL_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_DIALOG, GimpToolDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_TOOL_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_TOOL_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_TOOL_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_DIALOG))
end_define

begin_define
DECL|macro|GIMP_TOOL_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_TOOL_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_DIALOG, GimpToolDialogClass))
end_define

begin_typedef
DECL|typedef|GimpToolDialogClass
typedef|typedef
name|struct
name|_GimpViewableDialogClass
name|GimpToolDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpToolDialog
struct|struct
name|_GimpToolDialog
block|{
DECL|member|parent_instance
name|GimpViewableDialog
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_tool_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_tool_dialog_new
argument_list|(
name|GimpToolInfo
operator|*
name|tool_info
argument_list|,
name|GtkWidget
operator|*
name|parent
argument_list|,
specifier|const
name|gchar
operator|*
name|desc
argument_list|,
operator|...
argument_list|)
name|G_GNUC_NULL_TERMINATED
decl_stmt|;
end_decl_stmt

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_TOOL_DIALOG_H__ */
end_comment

end_unit

