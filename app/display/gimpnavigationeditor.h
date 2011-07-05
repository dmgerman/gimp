begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpnavigationeditor.h  * Copyright (C) 2002 Michael Natterer<mitch@gimp.org>  *  * partly based on app/nav_window  * Copyright (C) 1999 Andy Thomas<alt@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_NAVIGATION_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_NAVIGATION_EDITOR_H__
define|#
directive|define
name|__GIMP_NAVIGATION_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"widgets/gimpeditor.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_NAVIGATION_EDITOR
define|#
directive|define
name|GIMP_TYPE_NAVIGATION_EDITOR
value|(gimp_navigation_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_EDITOR (obj)
define|#
directive|define
name|GIMP_NAVIGATION_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_NAVIGATION_EDITOR, GimpNavigationEditor))
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_NAVIGATION_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_NAVIGATION_EDITOR, GimpNavigationEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_NAVIGATION_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_NAVIGATION_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_NAVIGATION_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_NAVIGATION_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_NAVIGATION_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_NAVIGATION_EDITOR))
end_define

begin_define
DECL|macro|GIMP_NAVIGATION_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_NAVIGATION_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_NAVIGATION_EDITOR, GimpNavigationEditorClass))
end_define

begin_typedef
DECL|typedef|GimpNavigationEditorClass
typedef|typedef
name|struct
name|_GimpNavigationEditorClass
name|GimpNavigationEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpNavigationEditor
struct|struct
name|_GimpNavigationEditor
block|{
DECL|member|parent_instance
name|GimpEditor
name|parent_instance
decl_stmt|;
DECL|member|context
name|GimpContext
modifier|*
name|context
decl_stmt|;
DECL|member|shell
name|GimpDisplayShell
modifier|*
name|shell
decl_stmt|;
DECL|member|view
name|GtkWidget
modifier|*
name|view
decl_stmt|;
DECL|member|zoom_label
name|GtkWidget
modifier|*
name|zoom_label
decl_stmt|;
DECL|member|zoom_adjustment
name|GtkAdjustment
modifier|*
name|zoom_adjustment
decl_stmt|;
DECL|member|zoom_out_button
name|GtkWidget
modifier|*
name|zoom_out_button
decl_stmt|;
DECL|member|zoom_in_button
name|GtkWidget
modifier|*
name|zoom_in_button
decl_stmt|;
DECL|member|zoom_100_button
name|GtkWidget
modifier|*
name|zoom_100_button
decl_stmt|;
DECL|member|zoom_fit_in_button
name|GtkWidget
modifier|*
name|zoom_fit_in_button
decl_stmt|;
DECL|member|zoom_fill_button
name|GtkWidget
modifier|*
name|zoom_fill_button
decl_stmt|;
DECL|member|shrink_wrap_button
name|GtkWidget
modifier|*
name|shrink_wrap_button
decl_stmt|;
DECL|member|scale_timeout
name|guint
name|scale_timeout
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpNavigationEditorClass
struct|struct
name|_GimpNavigationEditorClass
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
name|gimp_navigation_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_navigation_editor_new
parameter_list|(
name|GimpMenuFactory
modifier|*
name|menu_factory
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_navigation_editor_popup
parameter_list|(
name|GimpDisplayShell
modifier|*
name|shell
parameter_list|,
name|GtkWidget
modifier|*
name|widget
parameter_list|,
name|gint
name|click_x
parameter_list|,
name|gint
name|click_y
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_NAVIGATION_EDITOR_H__  */
end_comment

end_unit

