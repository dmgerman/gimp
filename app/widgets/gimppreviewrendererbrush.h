begin_unit|revision:0.9.5;language:C;cregit-version:0.0.1
begin_comment
comment|/* The GIMP -- an image manipulation program  * Copyright (C) 1995 Spencer Kimball and Peter Mattis  *  * GimpBrushPreview Widget  * Copyright (C) 2001 Michael Natterer  *  * This program is free software; you can redistribute it and/or modify  * it under the terms of the GNU General Public License as published by  * the Free Software Foundation; either version 2 of the License, or  * (at your option) any later version.  *  * This program is distributed in the hope that it will be useful,  * but WITHOUT ANY WARRANTY; without even the implied warranty of  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  * GNU General Public License for more details.  *  * You should have received a copy of the GNU General Public License  * along with this program; if not, write to the Free Software  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
end_comment

begin_ifndef
ifndef|#
directive|ifndef
name|__GIMP_BRUSH_PREVIEW_H__
end_ifndef

begin_define
DECL|macro|__GIMP_BRUSH_PREVIEW_H__
define|#
directive|define
name|__GIMP_BRUSH_PREVIEW_H__
end_define

begin_include
include|#
directive|include
file|"gimppreview.h"
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
DECL|macro|GIMP_TYPE_BRUSH_PREVIEW
define|#
directive|define
name|GIMP_TYPE_BRUSH_PREVIEW
value|(gimp_brush_preview_get_type ())
DECL|macro|GIMP_BRUSH_PREVIEW (obj)
define|#
directive|define
name|GIMP_BRUSH_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_CAST ((obj), GIMP_TYPE_BRUSH_PREVIEW, GimpBrushPreview))
DECL|macro|GIMP_BRUSH_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_BRUSH_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_CAST ((klass), GIMP_TYPE_BRUSH_PREVIEW, GimpBrushPreviewClass))
DECL|macro|GIMP_IS_BRUSH_PREVIEW (obj)
define|#
directive|define
name|GIMP_IS_BRUSH_PREVIEW
parameter_list|(
name|obj
parameter_list|)
value|(GTK_CHECK_TYPE (obj, GIMP_TYPE_BRUSH_PREVIEW))
DECL|macro|GIMP_IS_BRUSH_PREVIEW_CLASS (klass)
define|#
directive|define
name|GIMP_IS_BRUSH_PREVIEW_CLASS
parameter_list|(
name|klass
parameter_list|)
value|(GTK_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_BRUSH_PREVIEW))
DECL|typedef|GimpBrushPreviewClass
typedef|typedef
name|struct
name|_GimpBrushPreviewClass
name|GimpBrushPreviewClass
typedef|;
DECL|struct|_GimpBrushPreview
struct|struct
name|_GimpBrushPreview
block|{
DECL|member|parent_instance
name|GimpPreview
name|parent_instance
decl_stmt|;
DECL|member|pipe_timeout_id
name|guint
name|pipe_timeout_id
decl_stmt|;
DECL|member|pipe_animation_index
name|gint
name|pipe_animation_index
decl_stmt|;
block|}
struct|;
DECL|struct|_GimpBrushPreviewClass
struct|struct
name|_GimpBrushPreviewClass
block|{
DECL|member|parent_class
name|GimpPreviewClass
name|parent_class
decl_stmt|;
block|}
struct|;
name|GtkType
name|gimp_brush_preview_get_type
parameter_list|(
name|void
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
comment|/* __GIMP_BRUSH_PREVIEW_H__ */
end_comment

end_unit

