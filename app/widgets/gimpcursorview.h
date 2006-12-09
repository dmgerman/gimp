begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcursorview.h  * Copyright (C) 2005 Michael Natterer<mitch@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_CURSOR_VIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_CURSOR_VIEW_H__
define|#
directive|define
name|__GIMP_CURSOR_VIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimpeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_CURSOR_VIEW
define|#
directive|define
name|GIMP_TYPE_CURSOR_VIEW
value|(gimp_cursor_view_get_type ())
end_define

begin_define
DECL|macro|GIMP_CURSOR_VIEW (obj)
define|#
directive|define
name|GIMP_CURSOR_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_CURSOR_VIEW, GimpCursorView))
end_define

begin_define
DECL|macro|GIMP_CURSOR_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_CURSOR_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_CURSOR_VIEW, GimpCursorViewClass))
end_define

begin_define
DECL|macro|GIMP_IS_CURSOR_VIEW (obj)
define|#
directive|define
name|GIMP_IS_CURSOR_VIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_CURSOR_VIEW))
end_define

begin_define
DECL|macro|GIMP_IS_CURSOR_VIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_CURSOR_VIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_CURSOR_VIEW))
end_define

begin_define
DECL|macro|GIMP_CURSOR_VIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_CURSOR_VIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_CURSOR_VIEW, GimpCursorViewClass))
end_define

begin_typedef
DECL|typedef|GimpCursorViewClass
typedef|typedef
name|struct
name|_GimpCursorViewClass
name|GimpCursorViewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpCursorView
struct|struct
name|_GimpCursorView
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|coord_hbox
name|GtkWidget
modifier|*
name|coord_hbox
decl_stmt|;
DECL|member|color_hbox
name|GtkWidget
modifier|*
name|color_hbox
decl_stmt|;
DECL|member|pixel_x_label
name|GtkWidget
modifier|*
name|pixel_x_label
decl_stmt|;
DECL|member|pixel_y_label
name|GtkWidget
modifier|*
name|pixel_y_label
decl_stmt|;
DECL|member|unit_x_label
name|GtkWidget
modifier|*
name|unit_x_label
decl_stmt|;
DECL|member|unit_y_label
name|GtkWidget
modifier|*
name|unit_y_label
decl_stmt|;
DECL|member|color_frame_1
name|GtkWidget
modifier|*
name|color_frame_1
decl_stmt|;
DECL|member|color_frame_2
name|GtkWidget
modifier|*
name|color_frame_2
decl_stmt|;
DECL|member|sample_merged
name|gboolean
name|sample_merged
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpCursorViewClass
struct|struct
name|_GimpCursorViewClass
block|{
DECL|member|parent_class
name|GimpEditorClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_cursor_view_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_cursor_view_new
parameter_list|(
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cursor_view_set_sample_merged
parameter_list|(
name|GimpCursorView
modifier|*
name|view
parameter_list|,
name|gboolean
name|sample_merged
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_cursor_view_get_sample_merged
parameter_list|(
name|GimpCursorView
modifier|*
name|view
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_cursor_view_update_cursor
parameter_list|(
name|GimpCursorView
modifier|*
name|view
parameter_list|,
name|GimpImage
modifier|*
name|image
parameter_list|,
name|GimpUnit
name|unit
parameter_list|,
name|gdouble
name|x
parameter_list|,
name|gdouble
name|y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_CURSOR_VIEW_H__ */
end_comment

end_unit

