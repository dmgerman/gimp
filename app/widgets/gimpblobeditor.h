begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * gimpblobeditor.h  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BLOB_EDITOR_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BLOB_EDITOR_H__
define|#
directive|define
name|__GIMP_BLOB_EDITOR_H__
end_define

begin_include
include|#
directive|include
file|"gtk/gtkdrawingarea.h"
end_include

begin_define
DECL|macro|GIMP_TYPE_BLOB_EDITOR
define|#
directive|define
name|GIMP_TYPE_BLOB_EDITOR
value|(gimp_blob_editor_get_type ())
end_define

begin_define
DECL|macro|GIMP_BLOB_EDITOR (obj)
define|#
directive|define
name|GIMP_BLOB_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_BLOB_EDITOR, GimpBlobEditor))
end_define

begin_define
DECL|macro|GIMP_BLOB_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_BLOB_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BLOB_EDITOR, GimpBlobEditorClass))
end_define

begin_define
DECL|macro|GIMP_IS_BLOB_EDITOR (obj)
define|#
directive|define
name|GIMP_IS_BLOB_EDITOR
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_BLOB_EDITOR))
end_define

begin_define
DECL|macro|GIMP_IS_BLOB_EDITOR_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BLOB_EDITOR_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BLOB_EDITOR))
end_define

begin_define
DECL|macro|GIMP_BLOB_EDITOR_GET_CLASS (obj)
define|#
directive|define
name|GIMP_BLOB_EDITOR_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_BLOB_EDITOR, GimpBlobEditorClass))
end_define

begin_typedef
DECL|typedef|GimpBlobEditorClass
typedef|typedef
name|struct
name|_GimpBlobEditorClass
name|GimpBlobEditorClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpBlobEditor
struct|struct
name|_GimpBlobEditor
block|{
DECL|member|parent_instance
name|GtkDrawingArea
name|parent_instance
decl_stmt|;
DECL|member|type
name|GimpInkBlobType
name|type
decl_stmt|;
DECL|member|aspect
name|gdouble
name|aspect
decl_stmt|;
DECL|member|angle
name|gdouble
name|angle
decl_stmt|;
comment|/*<  private>*/
DECL|member|active
name|gboolean
name|active
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpBlobEditorClass
struct|struct
name|_GimpBlobEditorClass
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
name|gimp_blob_editor_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|GtkWidget
modifier|*
name|gimp_blob_editor_new
parameter_list|(
name|GimpInkBlobType
name|type
parameter_list|,
name|gdouble
name|aspect
parameter_list|,
name|gdouble
name|angle
parameter_list|)
function_decl|;
end_function_decl

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/*  __GIMP_BLOB_EDITOR_H__  */
end_comment

end_unit

