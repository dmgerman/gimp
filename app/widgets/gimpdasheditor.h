begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpdasheditor.h  * Copyright (C) 2003 Simon Budig<simon@gimp.org>  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_DASH_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_DASH_EDITOR_H__
define|#
directive|define
name|__GIMP_DASH_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkdrawingarea.h>
end_include

begin_define
DECL|macro|GIMP_TYPE_DASH_EDITOR
define|#
directive|define
name|GIMP_TYPE_DASH_EDITOR
value|(gimp_dash_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_DASH_EDITOR (obj)
define|#
directive|define
name|GIMP_DASH_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DASH_EDITOR, GimpDashEditor))
end_define

begin_define
DECL|macro|GIMP_DASH_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_DASH_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DASH_EDITOR, GimpDashEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_DASH_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_DASH_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DASH_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_DASH_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_DASH_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DASH_EDITOR))
end_define

begin_define
DECL|macro|GIMP_DASH_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_DASH_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DASH_EDITOR, GimpDashEditorClass))
end_define

begin_typedef
DECL|typedef|GimpDashEditorClass
typedef|typedef
name|struct
name|_GimpDashEditorClass
name|GimpDashEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpDashEditor
struct|struct
name|_GimpDashEditor
block|{
DECL|member|parent_instance
name|GtkDrawingArea
name|parent_instance
decl_stmt|;
DECL|member|stroke_options
name|GimpStrokeOptions
modifier|*
name|stroke_options
decl_stmt|;
DECL|member|dash_length
name|gdouble
name|dash_length
decl_stmt|;
comment|/* GUI stuff */
DECL|member|n_segments
name|gint
name|n_segments
decl_stmt|;
DECL|member|segments
name|gboolean
modifier|*
name|segments
decl_stmt|;
comment|/* coordinates of the first block main dash pattern */
DECL|member|x0
name|gint
name|x0
decl_stmt|;
DECL|member|y0
name|gint
name|y0
decl_stmt|;
DECL|member|block_width
name|gint
name|block_width
decl_stmt|;
DECL|member|block_height
name|gint
name|block_height
decl_stmt|;
DECL|member|edit_mode
name|gboolean
name|edit_mode
decl_stmt|;
DECL|member|edit_button_x0
name|gint
name|edit_button_x0
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpDashEditorClass
struct|struct
name|_GimpDashEditorClass
block|{
DECL|member|parent_class
name|GtkDrawingAreaClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_dash_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_dash_editor_new
parameter_list|(
name|GimpStrokeOptions
modifier|*
name|stroke_options
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dash_editor_shift_left
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_dash_editor_shift_right
parameter_list|(
name|GimpDashEditor
modifier|*
name|editor
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_DASH_EDITOR_H__ */
end_comment

end_unit

