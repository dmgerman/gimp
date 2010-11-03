begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpcolordisplayeditor.h  * Copyright (C) 2003 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_COLOR_DISPLAY_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_COLOR_DISPLAY_EDITOR_H__
define|#
directive|define
name|__GIMP_COLOR_DISPLAY_EDITOR_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_COLOR_DISPLAY_EDITOR
define|#
directive|define
name|GIMP_TYPE_COLOR_DISPLAY_EDITOR
value|(gimp_color_display_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY_EDITOR (obj)
define|#
directive|define
name|GIMP_COLOR_DISPLAY_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_COLOR_DISPLAY_EDITOR, GimpColorDisplayEditor))
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_COLOR_DISPLAY_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_COLOR_DISPLAY_EDITOR, GimpColorDisplayEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_DISPLAY_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_COLOR_DISPLAY_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_COLOR_DISPLAY_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_COLOR_DISPLAY_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_COLOR_DISPLAY_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_COLOR_DISPLAY_EDITOR))
end_define

begin_define
DECL|macro|GIMP_COLOR_DISPLAY_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_COLOR_DISPLAY_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_COLOR_DISPLAY_EDITOR, GimpColorDisplayEditorClass))
end_define

begin_typedef
DECL|typedef|GimpColorDisplayEditorClass
typedef|typedef
name|struct
name|_GimpColorDisplayEditorClass
name|GimpColorDisplayEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpColorDisplayEditor
struct|struct
name|_GimpColorDisplayEditor
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
DECL|member|stack
name|GimpColorDisplayStack
modifier|*
name|stack
decl_stmt|;
DECL|member|src
name|GtkListStore
modifier|*
name|src
decl_stmt|;
DECL|member|dest
name|GtkListStore
modifier|*
name|dest
decl_stmt|;
DECL|member|src_sel
name|GtkTreeSelection
modifier|*
name|src_sel
decl_stmt|;
DECL|member|dest_sel
name|GtkTreeSelection
modifier|*
name|dest_sel
decl_stmt|;
DECL|member|selected
name|GimpColorDisplay
modifier|*
name|selected
decl_stmt|;
DECL|member|add_button
name|GtkWidget
modifier|*
name|add_button
decl_stmt|;
DECL|member|remove_button
name|GtkWidget
modifier|*
name|remove_button
decl_stmt|;
DECL|member|up_button
name|GtkWidget
modifier|*
name|up_button
decl_stmt|;
DECL|member|down_button
name|GtkWidget
modifier|*
name|down_button
decl_stmt|;
DECL|member|config_frame
name|GtkWidget
modifier|*
name|config_frame
decl_stmt|;
DECL|member|config_box
name|GtkWidget
modifier|*
name|config_box
decl_stmt|;
DECL|member|config_widget
name|GtkWidget
modifier|*
name|config_widget
decl_stmt|;
DECL|member|reset_button
name|GtkWidget
modifier|*
name|reset_button
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpColorDisplayEditorClass
struct|struct
name|_GimpColorDisplayEditorClass
block|{
DECL|member|parent_class
name|GtkBoxClass
name|parent_class
decl_stmt|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_color_display_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_color_display_editor_new
parameter_list|(
name|GimpColorDisplayStack
modifier|*
name|stack
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_COLOR_DISPLAY_EDITOR_H__  */
end_comment

end_unit

