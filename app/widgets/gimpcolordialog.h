begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcolordialog.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_DIALOG_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_DIALOG_H__
define|#
directive|define
name|__GIMP_COLOR_DIALOG_H__
end_define

begin_include
include|#
directive|include
file|"gimpviewabledialog.h"
end_include

begin_include
include|#
directive|include
file|"gui/color-history.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_COLOR_DIALOG
define|#
directive|define
name|GIMP_TYPE_COLOR_DIALOG
value|(gimp_color_dialog_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_DIALOG (obj)
define|#
directive|define
name|GIMP_COLOR_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_DIALOG, GimpColorDialog))
end_define

begin_define
DECL|macro|GIMP_COLOR_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_DIALOG, GimpColorDialogClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_DIALOG (obj)
define|#
directive|define
name|GIMP_IS_COLOR_DIALOG
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_DIALOG))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_DIALOG_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_DIALOG_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_DIALOG))
end_define

begin_define
DECL|macro|GIMP_COLOR_DIALOG_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_DIALOG_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_DIALOG, GimpColorDialogClass))
end_define

begin_typedef
DECL|typedef|GimpColorDialogClass
typedef|typedef
name|struct
name|_GimpColorDialogClass
name|GimpColorDialogClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorDialog
struct|struct
name|_GimpColorDialog
block|{
DECL|member|parent_instance
name|GimpViewableDialog
name|parent_instance
decl_stmt|;
DECL|member|wants_updates
name|gboolean
name|wants_updates
decl_stmt|;
DECL|member|selection
name|GtkWidget
modifier|*
name|selection
decl_stmt|;
DECL|member|history
name|GtkWidget
modifier|*
name|history
index|[
name|COLOR_HISTORY_SIZE
index|]
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorDialogClass
struct|struct
name|_GimpColorDialogClass
block|{
DECL|member|parent_class
name|GimpViewableDialogClass
name|parent_class
decl_stmt|;
DECL|member|update
name|void
function_decl|(
modifier|*
name|update
function_decl|)
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|GimpColorDialogState
name|state
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_dialog_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_dialog_new
parameter_list|(
name|GimpViewable
modifier|*
name|viewable
parameter_list|,
name|GimpContext
modifier|*
name|context
parameter_list|,
specifier|const
name|gchar
modifier|*
name|title
parameter_list|,
specifier|const
name|gchar
modifier|*
name|stock_id
parameter_list|,
specifier|const
name|gchar
modifier|*
name|desc
parameter_list|,
name|GtkWidget
modifier|*
name|parent
parameter_list|,
name|GimpDialogFactory
modifier|*
name|dialog_factory
parameter_list|,
specifier|const
name|gchar
modifier|*
name|dialog_identifier
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|,
name|gboolean
name|wants_update
parameter_list|,
name|gboolean
name|show_alpha
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_dialog_set_color
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
specifier|const
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_color_dialog_get_color
parameter_list|(
name|GimpColorDialog
modifier|*
name|dialog
parameter_list|,
name|GimpRGB
modifier|*
name|color
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_COLOR_DIALOG_H__ */
end_comment

end_unit

