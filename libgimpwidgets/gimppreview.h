begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* LIBGIMP - The GIMP Library  * Copyright (C) 1995-1997 Peter Mattis and Spencer Kimball  *  * gimppreview.h  *  * This library is free software; you can redistribute it and/or  * modify it under the terms of the GNU Lesser General Public  * License as published by the Free Software Foundation; either  * version 2 of the License, or (at your option) any later version.  *  * This library is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  * Lesser General Public License for more details.  *  * You should have received a copy of the GNU Lesser General Public  * License along with this library; if not, write to the  * Free Software Foundation, Inc., 59 Temple Place - Suite 330,  * Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_PREVIEW_H__
define|#
directive|define
name|__GIMP_PREVIEW_H__
end_define

begin_include
include|#
directive|include
file|<gtk/gtkvbox.h>
end_include

begin_macro
name|G_BEGIN_DECLS
end_macro

begin_comment
comment|/* For information look into the C source or the html documentation */
end_comment

begin_define
DECL|macro|GIMP_TYPE_PREVIEW
define|#
directive|define
name|GIMP_TYPE_PREVIEW
value|(gimp_preview_get_type ())
end_define

begin_define
DECL|macro|GIMP_PREVIEW (obj)
define|#
directive|define
name|GIMP_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_PREVIEW, GimpPreview))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_PREVIEW, GimpPreviewClass))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_IS_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_PREVIEW))
end_define

begin_define
DECL|macro|GIMP_PREVIEW_GET_CLASS (obj)
define|#
directive|define
name|GIMP_PREVIEW_GET_CLASS
parameter_list|(
name|obj
parameter_list|)
value|(G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_PREVIEW, GimpPreviewClass))
end_define

begin_typedef
DECL|typedef|GimpPreviewClass
typedef|typedef
name|struct
name|_GimpPreviewClass
name|GimpPreviewClass
typedef|;
end_typedef

begin_struct
DECL|struct|_GimpPreview
struct|struct
name|_GimpPreview
block|{
DECL|member|parent_instance
name|GtkVBox
name|parent_instance
decl_stmt|;
DECL|member|update_preview
name|gboolean
name|update_preview
decl_stmt|;
comment|/*< protected>*/
DECL|member|area
name|GtkWidget
modifier|*
name|area
decl_stmt|;
DECL|member|table
name|GtkWidget
modifier|*
name|table
decl_stmt|;
DECL|member|frame
name|GtkWidget
modifier|*
name|frame
decl_stmt|;
DECL|member|toggle
name|GtkWidget
modifier|*
name|toggle
decl_stmt|;
DECL|member|cursor_busy
name|GdkCursor
modifier|*
name|cursor_busy
decl_stmt|;
comment|/*< private>*/
DECL|member|xmin
DECL|member|xmax
DECL|member|ymin
DECL|member|ymax
name|gint
name|xmin
decl_stmt|,
name|xmax
decl_stmt|,
name|ymin
decl_stmt|,
name|ymax
decl_stmt|;
DECL|member|width
DECL|member|height
name|gint
name|width
decl_stmt|,
name|height
decl_stmt|;
DECL|member|timeout_id
name|guint
name|timeout_id
decl_stmt|;
block|}
struct|;
end_struct

begin_struct
DECL|struct|_GimpPreviewClass
struct|struct
name|_GimpPreviewClass
block|{
DECL|member|parent_class
name|GtkVBoxClass
name|parent_class
decl_stmt|;
comment|/* virtuals */
DECL|member|draw
name|void
function_decl|(
modifier|*
name|draw
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
DECL|member|set_cursor
name|void
function_decl|(
modifier|*
name|set_cursor
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
comment|/* signal */
DECL|member|invalidated
name|void
function_decl|(
modifier|*
name|invalidated
function_decl|)
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
block|}
struct|;
end_struct

begin_decl_stmt
name|GType
name|gimp_preview_get_type
argument_list|(
name|void
argument_list|)
name|G_GNUC_CONST
decl_stmt|;
end_decl_stmt

begin_function_decl
name|void
name|gimp_preview_set_update
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gboolean
name|update
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|gboolean
name|gimp_preview_get_update
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_set_bounds
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
name|xmin
parameter_list|,
name|gint
name|ymin
parameter_list|,
name|gint
name|xmax
parameter_list|,
name|gint
name|ymax
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_get_size
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|,
name|gint
modifier|*
name|width
parameter_list|,
name|gint
modifier|*
name|height
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_draw
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_function_decl
name|void
name|gimp_preview_invalidate
parameter_list|(
name|GimpPreview
modifier|*
name|preview
parameter_list|)
function_decl|;
end_function_decl

begin_macro
name|G_END_DECLS
end_macro

begin_endif
endif|#
directive|endif
end_endif

begin_comment
comment|/* __GIMP_PREVIEW_H__ */
end_comment

end_unit

