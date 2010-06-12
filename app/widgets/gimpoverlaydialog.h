begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpoverlaydialog.h  * Copyright (C) 2009-2010  Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_OVERLAY_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_OVERLAY_DIALOG_H__
define|#
directive|define
name|__GIMP_OVERLAY_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|"gimpoverlayframe.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_OVERLAY_DIALOG
define|#
directive|define
name|GIMP_TYPE_OVERLAY_DIALOG
value|(gimp_overlay_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_OVERLAY_DIALOG (obj)
define|#
directive|define
name|GIMP_OVERLAY_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_OVERLAY_DIALOG, GimpOverlayDialog))
end_define

begin_define
DECL|macro|GIMP_OVERLAY_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_OVERLAY_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_OVERLAY_DIALOG, GimpOverlayDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_OVERLAY_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_OVERLAY_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_OVERLAY_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_OVERLAY_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_OVERLAY_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_OVERLAY_DIALOG))
end_define

begin_define
DECL|macro|GIMP_OVERLAY_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_OVERLAY_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_OVERLAY_DIALOG, GimpOverlayDialogClass))
end_define

begin_typedef
DECL|typedef|GimpOverlayDialog
typedef|typedef
name|struct
name|_GimpOverlayDialog
name|GimpOverlayDialog
typedef|;
end_typedef

begin_typedef
DECL|typedef|GimpOverlayDialogClass
typedef|typedef
name|struct
name|_GimpOverlayDialogClass
name|GimpOverlayDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpOverlayDialog
struct|struct
name|_GimpOverlayDialog
block|{
DECL|member|parent_instance
name|GimpOverlayFrame
name|parent_instance
decl_stmt|;
DECL|member|action_area
name|GtkWidget
modifier|*
name|action_area
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpOverlayDialogClass
struct|struct
name|_GimpOverlayDialogClass
block|{
DECL|member|parent_class
name|GimpOverlayFrameClass
name|parent_class
decl_stmt|;
DECL|member|response
name|void
function_decl|(
modifier|*
name|response
function_decl|)
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|overlay
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
DECL|member|close
name|void
function_decl|(
modifier|*
name|close
function_decl|)
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|overlay
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_overlay_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_decl_stmt
name|GtkWidget
modifier|*
name|gimp_overlay_dialog_new
argument_list|(
name|GimpToolInfo
operator|*
name|tool_info
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

begin_function_decl
name|void
name|gimp_overlay_dialog_response
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|overlay
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_overlay_dialog_add_buttons_valist
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|overlay
parameter_list|,
name|va_list
name|args
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_overlay_dialog_add_button
parameter_list|(
name|GimpOverlayDialog
modifier|*
name|overlay
parameter_list|,
specifier|const
name|gchar
modifier|*
name|button_text
parameter_list|,
name|gint
name|response_id
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_OVERLAY_DIALOG_H__ */
end_comment

end_unit

