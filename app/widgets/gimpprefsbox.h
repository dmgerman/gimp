begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* GIMP - The GNU Image Manipulation Program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpprefsbox.h  * Copyright (C) 2013 Michael Natterer<mitch@gimp.org>  *  * This program is free software: you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 3 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program.  If not, see<http://www.gnu.org/licenses/>.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREFS_BOX_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREFS_BOX_H__
define|#
directive|define
name|__GIMP_PREFS_BOX_H__
end_define

begin_define
DECL|macro|GIMP_TYPE_PREFS_BOX
define|#
directive|define
name|GIMP_TYPE_PREFS_BOX
value|(gimp_prefs_box_get_type ())
end_define

begin_define
DECL|macro|GIMP_PREFS_BOX (obj)
define|#
directive|define
name|GIMP_PREFS_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PREFS_BOX, GimpPrefsBox))
end_define

begin_define
DECL|macro|GIMP_PREFS_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_PREFS_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREFS_BOX, GimpPrefsBoxClass))
end_define

begin_define
DECL|macro|GIMP_IS_PREFS_BOX (obj)
define|#
directive|define
name|GIMP_IS_PREFS_BOX
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PREFS_BOX))
end_define

begin_define
DECL|macro|GIMP_IS_PREFS_BOX_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREFS_BOX_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREFS_BOX))
end_define

begin_define
DECL|macro|GIMP_PREFS_BOX_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PREFS_BOX_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PREFS_BOX, GimpPrefsBoxClass))
end_define

begin_typedef
DECL|typedef|GimpPrefsBoxClass
typedef|typedef
name|struct
name|_GimpPrefsBoxClass
name|GimpPrefsBoxClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPrefsBox
struct|struct
name|_GimpPrefsBox
block|{
DECL|member|parent_instance
name|GtkBox
name|parent_instance
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPrefsBoxClass
struct|struct
name|_GimpPrefsBoxClass
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
name|gimp_prefs_box_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prefs_box_new
parameter_list|(
name|void
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prefs_box_add_page
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|,
specifier|const
name|gchar
modifier|*
name|icon_name
parameter_list|,
specifier|const
name|gchar
modifier|*
name|notebook_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|tree_label
parameter_list|,
specifier|const
name|gchar
modifier|*
name|help_id
parameter_list|,
name|GtkTreeIter
modifier|*
name|parent
parameter_list|,
name|GtkTreeIter
modifier|*
name|iter
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_prefs_box_set_page_scrollable
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|,
name|GtkWidget
modifier|*
name|page
parameter_list|,
name|gboolean
name|scrollable
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prefs_box_get_tree_view
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prefs_box_get_notebook
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_prefs_box_get_image
parameter_list|(
name|GimpPrefsBox
modifier|*
name|box
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_PREFS_BOX_H__  */
end_comment

end_unit

