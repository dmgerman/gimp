begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library                                                     * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball                  *  * gimppatheditor.h  * Copyright (C) 1999 Michael Natterer<mitschel@cs.tu-berlin.de>  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Library General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.               *                                                                                * This library is distributed in the hope that it will be useful,                * but WITHOUT ANY WARRANTY; without even the implied warranty of                 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              * Library General Public License for more details.  *  * You should have received a copy of the GNU Library General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PATH_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PATH_EDITOR_H__
define|#
directive|define
name|__GIMP_PATH_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtk.h>
end_include

begin_ifdef
ifdef|#
directive|ifdef
name|__cplusplus
end_ifdef

begin_extern
extern|extern
literal|"C"
block|{
endif|#
directive|endif
comment|/* __cplusplus */
DECL|macro|GIMP_TYPE_PATH_EDITOR
define|#
directive|define
name|GIMP_TYPE_PATH_EDITOR
value|(gimp_path_editor_get_type ())
DECL|macro|GIMP_PATH_EDITOR (obj)
define|#
directive|define
name|GIMP_PATH_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_PATH_EDITOR, GimpPathEditor))
DECL|macro|GIMP_PATH_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_PATH_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PATH_EDITOR, GimpPathEditorClass))
DECL|macro|GIMP_IS_PATH_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_PATH_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_PATH_EDITOR))
DECL|macro|GIMP_IS_PATH_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PATH_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PATH_EDITOR))
DECL|typedef|GimpPathEditor
typedef|typedef
name|struct
name|_GimpPathEditor
name|GimpPathEditor
typedef|;
DECL|typedef|GimpPathEditorClass
typedef|typedef
name|struct
name|_GimpPathEditorClass
name|GimpPathEditorClass
typedef|;
DECL|struct|_GimpPathEditor
struct|struct
name|_GimpPathEditor
block|{
DECL|member|vbox
name|GtkVBox
name|vbox
decl_stmt|;
DECL|member|upper_hbox
name|GtkWidget
modifier|*
name|upper_hbox
decl_stmt|;
DECL|member|new_button
name|GtkWidget
modifier|*
name|new_button
decl_stmt|;
DECL|member|delete_button
name|GtkWidget
modifier|*
name|delete_button
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
DECL|member|file_selection
name|GtkWidget
modifier|*
name|file_selection
decl_stmt|;
DECL|member|dir_list
name|GtkWidget
modifier|*
name|dir_list
decl_stmt|;
DECL|member|selected_item
name|GtkWidget
modifier|*
name|selected_item
decl_stmt|;
DECL|member|number_of_items
name|gint
name|number_of_items
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpPathEditorClass
struct|struct
name|_GimpPathEditorClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
DECL|member|gimp_path_editor
name|void
function_decl|(
modifier|*
name|gimp_path_editor
function_decl|)
parameter_list|(
name|GimpPathEditor
modifier|*
name|gpe
parameter_list|)
function_decl|;
block|}
struct|;
name|guint
name|gimp_path_editor_get_type
parameter_list|(
name|void
parameter_list|)
function_decl|;
comment|/*  creates a new GimpPathEditor widget  */
name|GtkWidget
modifier|*
name|gimp_path_editor_new
parameter_list|(
name|gchar
modifier|*
name|filesel_title
parameter_list|,
name|gchar
modifier|*
name|path
parameter_list|)
function_decl|;
comment|/*  it's up to the caller to g_free() the returned string  */
name|gchar
modifier|*
name|gimp_path_editor_get_path
parameter_list|(
name|GimpPathEditor
modifier|*
name|gpe
parameter_list|)
function_decl|;
ifdef|#
directive|ifdef
name|__cplusplus
block|}
end_extern

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __cplusplus */
end_comment

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PATH_EDITOR_H__ */
end_comment

end_unit

